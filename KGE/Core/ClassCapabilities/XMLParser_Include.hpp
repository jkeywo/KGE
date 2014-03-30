
private:																			
	typedef KGE::XMLParser<this_t> xmlparser_t;
public:
	virtual void Internal_ProcessXMLAttributes(const xml_node<char>& xNode)
	{
		parent_t::Internal_ProcessXMLAttributes(xNode);
		xmlparser_t::Get().ProcessXMLAttributes(xNode, this);
	}
	virtual void Internal_ProcessXMLChildNodes(const xml_node<char>& xNode)
	{
		parent_t::Internal_ProcessXMLChildNodes(xNode);
		xmlparser_t::Get().ProcessXMLChildNodes(xNode, this);
	}