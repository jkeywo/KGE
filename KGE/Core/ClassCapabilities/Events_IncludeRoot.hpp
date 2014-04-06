	
public:
	virtual void OnEvent(const KGE::Hash& xEventHash, KGE::eventparams_t& xEventParameters)
	{
		KGE::Event<root_t>::collection_t::iterator xIt = m_xEvents.find(xEventHash);
		if (xIt != m_xEvents.end())
		{
			xIt->second->Execute( xEventParameters );
		}
	}

protected:
	void RegisterEvent(const Hash& xHash, std::function<void(KGE::eventparams_t&)> xCallback)
	{
		RegisterEvent(new KGE::Event<root_t>(xHash, *this, xCallback));
	}
	void RegisterEvent(KGE::Event<root_t>* pxEvent)
	{
		m_xEvents.insert(KGE::Event<root_t>::collectionpair_t(pxEvent->GetHash(), pxEvent));
	}
	void RegisterEventAction(const Hash& xEventHash, KGE::Action* pxAction)
	{
		KGE::Event<root_t>::collection_t::iterator xIt = m_xEvents.find(xEventHash);
		if( xIt != m_xEvents.end() )
		{
			xIt->second->RegisterAction( pxAction );
		}
	}
	void ClearEvents()
	{
		while (m_xEvents.begin() != m_xEvents.end())
		{
			KGE::Event<root_t>* pxEvent = m_xEvents.begin()->second;
			delete pxEvent;
			m_xEvents.erase(m_xEvents.begin());
		}
	}
	KGE::Event<root_t>::collection_t m_xEvents;