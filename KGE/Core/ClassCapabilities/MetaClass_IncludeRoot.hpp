
// include in a root class to setup metadata and enable it in all its decedents

public:
	virtual const KGE::Hash& GetClassHash() const = 0;
	virtual bool IsBaseOrDerivedClass(const KGE::Hash& xClassHash) const { return false; }

	const KGE::TUID<root_t>& GetTUID() const { return m_xTUID; }
	KGE::TUID<root_t>::CachedReference GetTUIDReference() const { return m_xTUID.GetCachedReference(); }

protected:
	KGE::TUID<root_t> m_xTUID;

#ifdef SUPPORT_CLASSFACTORY_0ARG
public:
	typedef KGE::ClassFactory<root_t> classfactory_t;
	static root_t* Create( const KGE::Hash& xHash )
	{ 
		root_t* pxReturn = classfactory_t::Get().Create(xHash);
#ifdef SUPPORT_EVENTS
		if (pxReturn)
		{
			KGE::eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::g_xHASH_ONCREATE, xEventParameters);
		}
#endif
		return pxReturn;
	}
#endif
#ifdef SUPPORT_CLASSFACTORY_XML_0ARG
public:	
	typedef KGE::ClassFactoryXML<root_t> classfactoryxml_t;
	static root_t* Create( xml_node<char>& xNode ) 
	{ 
		root_t* pxReturn = classfactoryxml_t::Get().Create(xNode); 
#ifdef SUPPORT_EVENTS
		if (pxReturn)
		{
			KGE::eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::g_xHASH_ONCREATE, xEventParameters);
		}
#endif
		return pxReturn;
	}
#endif
#ifdef SUPPORT_CLASSFACTORY_1ARG
public:
	typedef KGE::ClassFactory1Arg<root_t, SUPPORT_CLASSFACTORY_1ARG> classfactory1arg_t;
	static root_t* Create(const KGE::Hash& xHash, SUPPORT_CLASSFACTORY_1ARG xArg0)
	{ 
		root_t* pxReturn = classfactory1arg_t::Get().Create(xHash, xArg0); 
#ifdef SUPPORT_EVENTS
		if (pxReturn)
		{
			KGE::eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::g_xHASH_ONCREATE, xEventParameters);
		}
#endif
		return pxReturn;
	}
#endif
#ifdef SUPPORT_CLASSFACTORY_XML_1ARG
public:
	typedef KGE::ClassFactoryXML1Arg<root_t, SUPPORT_CLASSFACTORY_XML_1ARG> classfactoryxml1arg_t;
	static root_t* Create( xml_node<char>& xNode, SUPPORT_CLASSFACTORY_XML_1ARG xArg0 )
	{ 
		root_t* pxReturn = classfactoryxml1arg_t::Get().Create(xNode, xArg0); 
#ifdef SUPPORT_EVENTS
		if (pxReturn)
		{
			KGE::eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::g_xHASH_ONCREATE, xEventParameters);
		}
#endif
		return pxReturn;
	}
#endif

#ifdef SUPPORT_XML
#include "Core/ClassCapabilities/XMLParser_IncludeRoot.hpp"
#endif
#ifdef SUPPORT_EVENTS
#include "Core/ClassCapabilities/Events_IncludeRoot.hpp"
#endif
#ifdef SUPPORT_PROPERTIES
#include "Core/ClassCapabilities/Properties_IncludeRoot.hpp"
#endif

#undef SUPPORT_XML
#undef SUPPORT_EVENTS
#undef SUPPORT_PROPERTIES
#undef SUPPORT_CLASSFACTORY_0ARG
#undef SUPPORT_CLASSFACTORY_XML_0ARG
#undef SUPPORT_CLASSFACTORY_1ARG
#undef SUPPORT_CLASSFACTORY_XML_1ARG
