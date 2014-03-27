#pragma once

namespace KGE
{
	typedef unordered_map<Hash, Data, Hash::Hasher> eventparams_t;
	typedef pair<Hash, Data> eventparamspair_t;

	class Action;

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

		// register action
		virtual void RegisterAction( Action* pxAction ) {}
		// unregister action

		virtual void Execute(eventparams_t& xEventParameters)
		{
			m_xCallback(xEventParameters);
			// call actions
		}
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
		owner_t& m_xCaller;
		std::function<void(eventparams_t&)> m_xCallback;
		// action list
	};
};