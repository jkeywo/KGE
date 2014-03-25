
public:
	void OnEvent(const KGE::Hash& xEventHash, map<KGE::Hash, KGE::Data, KGE::Hash::Hasher>& xEventParameters)
	{
		/*map<KGE::Hash, KGE::Event*, KGE::Hash::Hasher>::iterator xIt = m_xEvents.find(xEventHash);
		if (xIt != m_xEvents.end())
		{
			xIt->second->Execute( xEventParameters );
		}*/
	}

protected:
	void RegisterEvent(KGE::Event* pxEvent)
	{
		//m_xEvents.insert(pair<KGE::Hash, KGE::Event*>(pxEvent->GetHash(), pxEvent));
	}
	void ClearEvents()
	{
		while (m_xEvents.begin() != m_xEvents.end())
		{
			delete m_xEvents.begin()->second;
			m_xEvents.erase(m_xEvents.begin());
		}
	}
	map<KGE::Hash, KGE::Event*, KGE::Hash::Hasher> m_xEvents;
	