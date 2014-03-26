	
public:
	void OnEvent(const KGE::Hash& xEventHash, KGE::Event<root_t>::params_t& xEventParameters)
	{
		KGE::Event<root_t>::collection_t::iterator xIt = m_xEvents.find(xEventHash);
		if (xIt != m_xEvents.end())
		{
			xIt->second->Execute( xEventParameters );
		}
	}

protected:
	void RegisterEvent(const Hash& xHash, std::function<void(KGE::Event<root_t>::params_t&)> xCallback)
	{
		RegisterEvent(new KGE::Event<root_t>(xHash, *this, xCallback));
	}
	void RegisterEvent(KGE::Event<root_t>* pxEvent)
	{
		m_xEvents.insert(KGE::Event<root_t>::collectionpair_t(pxEvent->GetHash(), pxEvent));
	}
	void ClearEvents()
	{
		while (m_xEvents.begin() != m_xEvents.end())
		{
			delete m_xEvents.begin()->second;
			m_xEvents.erase(m_xEvents.begin());
		}
	}
	KGE::Event<root_t>::collection_t m_xEvents;