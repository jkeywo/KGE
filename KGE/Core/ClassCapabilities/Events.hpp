#pragma once

#include "Core/ClassCapabilities/EventSignal.hpp"
#include "Core/Data/CommonHashes.hpp"

namespace KGE
{
	template<class owner_t>
	class Event
	{
	public:
		typedef unordered_map<Hash, Event<owner_t>*, Hash::Hasher> collection_t;
		typedef pair<Hash, Event<owner_t>*> collectionpair_t;

		Event(const Hash& xHash, owner_t& xCaller, std::function<void(eventparams_t&)> xCallback)
			: m_xHash(xHash)
			, m_xCaller(xCaller)
			, m_xCallback(xCallback)
		{
		}
		virtual ~Event()
		{
		}

		void RegisterSignal(EventSignal<owner_t>* pxSignal)
		{
			m_xSignals.insert(pxSignal);
		}
		void UnregisterSignal(EventSignal<owner_t>* pxSignal)
		{
			m_xSignals.erase(pxSignal);
		}
		void Execute(eventparams_t& xEventParameters)
		{
			xEventParameters.insert(eventparamspair_t(g_xHASH_SOURCE, Data(&m_xCaller)));
			bool bCallbackDone = false;
			FOREACH(xIt, m_xSignals)
			{
				EventSignal<owner_t>* pxSignal = (*xIt);
				if (!bCallbackDone && pxSignal->GetPriority() < 0.0f)
				{
					m_xCallback(xEventParameters);
					bCallbackDone = true;
				}
				pxSignal->Execute(xEventParameters);
			}
			if (!bCallbackDone)
			{
				m_xCallback(xEventParameters);
			}
		}
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
		owner_t& m_xCaller;
		std::function<void(eventparams_t&)> m_xCallback;
		std::set<EventSignal<owner_t>*, typename EventSignal<owner_t>::Comparer> m_xSignals;
	};
};