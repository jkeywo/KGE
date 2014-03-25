#pragma once

#define CAPABILIITYROOT_PROCESSXML													\
public:																				\
	virtual void ProcessXML(const xml_node<char>& xNode)							\
	{																				\
		Internal_ProcessXMLAttributes(xNode);										\
		Internal_PostAttributeProcessXML(xNode);									\
		Internal_ProcessXMLChildNodes(xNode);										\
		Internal_PostChildNodeProcessXML(xNode);									\
	}																				\
protected:																			\
	virtual void Internal_ProcessXMLAttributes(const xml_node<char>& xNode) {}		\
	virtual void Internal_PostAttributeProcessXML(const xml_node<char>& xNode) {}	\
	virtual void Internal_ProcessXMLChildNodes(const xml_node<char>& xNode) {}		\
	virtual void Internal_PostChildNodeProcessXML(const xml_node<char>& xNode) {}

#define CAPABILITY_XMLPARSER														\
private:																			\
	typedef KGE::XMLParser<root_t, parent_t, this_t> xmlparser_t;					\
public:																				\
	virtual void Internal_ProcessXMLAttributes(const xml_node<char>& xNode)			\
	{																				\
		parent_t::Internal_ProcessXMLAttributes(xNode);								\
		xmlparser_t::Get().ProcessXMLAttributes(xNode, this);						\
	}																				\
	virtual void Internal_ProcessXMLChildNodes(const xml_node<char>& xNode)			\
	{																				\
		parent_t::Internal_ProcessXMLChildNodes(xNode);								\
		xmlparser_t::Get().ProcessXMLChildNodes(xNode, this);						\
	}

// put in static initialisation
#define XMLPARSER_REGISTERATTRIBUTE( NAME, FUNCTION )	xmlparser_t::Get().RegisterXMLAttribute( KGE::Hash(NAME), &this_t::FUNCTION )
#define XMLPARSER_REGISTERCHILDNODE( NAME, FUNCTION )	xmlparser_t::Get().RegisterXMLChild( KGE::Hash(NAME), &this_t::FUNCTION )

namespace KGE
{	
	class XMLHelpers
	{
	public:
		static const char* GetAttributeValue(xml_node<char>& xObject, const char* szAttribute)
		{
			xml_attribute<char>* pxCurrentAttribute = xObject.first_attribute();
			while (pxCurrentAttribute != NULL)
			{
				if (strcmp(pxCurrentAttribute->name(), szAttribute) == 0)
				{
					return pxCurrentAttribute->value();
				}
				pxCurrentAttribute = pxCurrentAttribute->next_attribute();
			}
			return NULL;
		}
	};

	////////////////////////////////////////////////////////////////
	template< class parent_t > class XMLAttributeHandler;
	template< class parent_t > class XMLChildHandler;

	template< class root_t, class parent_t, class this_t >
	class XMLParser
	{
	public:
		typedef void( this_t::*AttributeCallbackFnPtr )(xml_attribute<char>&);
		typedef void( this_t::*NodeCallbackFnPtr )(xml_node<char>&);

		static XMLParser& Get() { static XMLParser xSingleton; return xSingleton; }

		void RegisterXMLAttribute( Hash xHash, AttributeCallbackFnPtr pxHandler )
		{
			m_xAtributes.insert(AttributePair(xHash, pxHandler));
		}
		void RegisterXMLChild( Hash xHash, NodeCallbackFnPtr const pxHandler)
		{
			m_xChildren.insert(ChildPair(xHash, pxHandler));
		}

		void ProcessXMLAttributes( const xml_node<char>& xNode, this_t* pxThis ) const
		{
			// for each attribute
			xml_attribute<char>* pxCurrentAttribute = xNode.first_attribute();
			while (pxCurrentAttribute != NULL)
			{
				ash xType = Hash(pxCurrentAttribute->name());
				AttributeCollection::const_iterator xIt = m_xAtributes.find(xType);
				if (xIt != m_xAtributes.end())
				{
					(pxThis->*(xIt->second))(*pxCurrentAttribute);
				}
				pxCurrentAttribute = pxCurrentAttribute->next_attribute();
			}
		}
		void ProcessXMLChildNodes( const xml_node<char>& xNode, this_t* pxThis ) const
		{
			// for each child
			xml_node<char>* pxCurrentChild = xNode.first_node();
			while (pxCurrentChild != NULL)
			{
				Hash xType = Hash(pxCurrentChild->name());
				ChildCollection::const_iterator xIt = m_xChildren.find(xType);
				if (xIt != m_xChildren.end())
				{
					(pxThis->*(xIt->second))(*pxCurrentChild);
				}
				pxCurrentChild = pxCurrentChild->next_sibling();
			}
		}

	protected:
		typedef unordered_map< Hash, AttributeCallbackFnPtr, Hash::Hasher >	AttributeCollection;
		typedef pair< Hash, AttributeCallbackFnPtr >						AttributePair;
		AttributeCollection m_xAtributes;

		typedef unordered_map< Hash, NodeCallbackFnPtr, Hash::Hasher >		ChildCollection;
		typedef pair< Hash, NodeCallbackFnPtr >								ChildPair;
		ChildCollection m_xChildren;
	};

	template< class parent_t >
	class XMLAttributeHandler
	{
	public:
		typedef void( parent_t::*AttributeCallbackFnPtr )(xml_attribute<char>&);

		XMLAttributeHandler( Hash xNameHash, AttributeCallbackFnPtr pxCallback )
			: m_pxCallback(pxCallback)
		{
			XMLNodeHandler<parent_t>::Get().AddHandler(xNameHash, this);
		}
		void Process(xml_attribute<char>& xAttribute, parent_t* pxThis) const
		{
			(pxThis->*m_pxCallback)(xAttribute);
		}

	protected:
		AttributeCallbackFnPtr m_pxCallback;
	};

	template< class parent_t >
	class XMLChildHandler
	{
	public:
		typedef void( parent_t::*NodeCallbackFnPtr )(xml_node<char>&);

		XMLChildHandler( Hash xNameHash, NodeCallbackFnPtr pxCallback )
			: m_pxCallback(pxCallback)
		{
			XMLNodeHandler<parent_t>::Get().AddHandler(xNameHash, this);
		}
		void Process(xml_node<char>& xNode, parent_t* pxThis) const
		{
			(pxThis->*m_pxCallback)(xNode);
		}
	protected:
		NodeCallbackFnPtr m_pxCallback;
	};
};