#pragma once

#include "Core/Actions/Action.hpp"
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

		void RegisterAction(Action* pxAction)
		{
			m_xActions.insert(pxAction);
		}
		void Execute(eventparams_t& xEventParameters)
		{
			xEventParameters.insert(eventparamspair_t(g_xHASH_SOURCE, Data(&m_xCaller)));
			bool bCallbackDone = false;
			FOREACH(xIt, m_xActions)
			{
				Action* pxAction = (*xIt);
				if (!bCallbackDone && pxAction->GetPriority() < 0.0f)
				{
					m_xCallback(xEventParameters);
					bCallbackDone = true;
				}
				pxAction->Activate(xEventParameters);
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
		std::set<Action*, typename Action::Comparer> m_xActions;
	};
};