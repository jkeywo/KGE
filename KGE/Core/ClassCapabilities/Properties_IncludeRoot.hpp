
public:
	typedef unordered_map<KGE::Hash, KGE::Property*, KGE::Hash::Hasher> propertycollection_t;
	typedef pair<KGE::Hash, KGE::Property*> propertycollectionpair_t;
	virtual Data GetProperty(const Hash& xHash)
	{
		propertycollection_t::iterator xIt = m_xProperties.find(xHash);
		if (xIt != m_xProperties.end())
		{
			return xIt->second->GetData();
		}
		return Data();
	}
	virtual bool SetProperty(const Hash& xHash, Data xData)
	{
		propertycollection_t::iterator xIt = m_xProperties.find(xHash);
		if (xIt != m_xProperties.end())
		{
			xIt->second->SetData(xData);
			return true;
		}
		return false;
	}

protected:
	void RegisterProperty(Property* pxProperty)
	{
		m_xProperties.insert(propertycollectionpair_t(pxProperty->GetHash(), pxProperty));
	}
	void ClearProperties()
	{
		while (m_xProperties.begin() != m_xProperties.end())
		{
			delete m_xProperties.begin()->second;
			m_xProperties.erase(m_xProperties.begin());
		}
	}
	propertycollection_t m_xProperties;
