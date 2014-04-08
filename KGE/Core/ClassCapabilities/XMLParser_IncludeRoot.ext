
private:
	typedef KGE::XMLParser<this_t> xmlparser_t;
public:
	virtual void ProcessXML(const xml_node<char>& xNode)
	{
		Internal_ProcessXMLAttributes(xNode);
		Internal_PostAttributeProcessXML(xNode);
		Internal_ProcessXMLChildNodes(xNode);
		Internal_PostChildNodeProcessXML(xNode);
	}
protected:
	virtual void Internal_ProcessXMLAttributes(const xml_node<char>& xNode) 
	{
	}
	virtual void Internal_PostAttributeProcessXML(const xml_node<char>& xNode)
	{ 
		xmlparser_t::Get().ProcessXMLAttributes(xNode, this); 
	}
	virtual void Internal_ProcessXMLChildNodes(const xml_node<char>& xNode) 
	{
	}
	virtual void Internal_PostChildNodeProcessXML(const xml_node<char>& xNode)
	{ 
		xmlparser_t::Get().ProcessXMLChildNodes(xNode, this); 
	}
