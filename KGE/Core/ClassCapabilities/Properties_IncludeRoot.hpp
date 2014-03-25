
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
	set<KGE::Property*, KGE::Property::Compare> m_xProperties;
