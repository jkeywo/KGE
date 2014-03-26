
public:
	Data GetProperty(const Hash& xHash)
	{

	}

protected:
	void RegisterProperty(Property* pxProperty)
	{
		m_xProperties.insert(pxProperty);
	}
	void ClearProperties()
	{
		while (m_xProperties.begin() != m_xProperties.end())
		{
			delete (*m_xProperties.begin());
			m_xProperties.erase(m_xProperties.begin());
		}
	}
	unordered_set<KGE::Property*, KGE::Property::Hasher> m_xProperties;
