#pragma once

namespace KGE
{
	template<class owner_t>
	class Event
	{
	public:
		typedef unordered_map<Hash, Event<owner_t>*, Hash::Hasher> collection_t;
		typedef pair<Hash, Event<owner_t>*> collectionpair_t;

		typedef unordered_map<Hash, Data, Hash::Hasher> params_t;
		typedef pair<Hash, Data> paramspair_t;

		Event(const Hash& xHash, owner_t& xCaller, std::function<void(params_t&)> xCallback)
			: m_xHash(xHash)
			, m_xCaller(xCaller)
			, m_xCallback(xCallback)
		{
		}
		virtual ~Event()
		{
		}

		// register signal
		// unregister signal

		virtual void Execute(params_t& xEventParameters)
		{
			m_xCallback(xEventParameters);
			// call signals
		}
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
		owner_t& m_xCaller;
		std::function<void(params_t&)> m_xCallback;
		// signal list
	};
};