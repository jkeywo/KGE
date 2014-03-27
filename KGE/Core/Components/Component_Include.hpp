
#include "Core/ClassCapabilities/MetaClass_Include.hpp"

public:	
	static this_t* Create(const Hash& xHash, ComponentContainer* pxParent)
	{
		root_t* pxReturn = classfactory1arg_t::Get().Create(xHash, pxParent);
		if (pxReturn && pxReturn->IsBaseOrDerivedClass(this_t::Static_GetClassHash()))
		{
			eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::Hash("OnCreate"), xEventParameters);
			return static_cast<this_t*>(pxReturn);
		}
		delete pxReturn;
		return NULL;
	}
	static this_t* Create(xml_node<char>& xNode, ComponentContainer* pxParent)
	{
		root_t* pxReturn = classfactoryxml1arg_t::Get().Create(xNode, pxParent);
		if (pxReturn && pxReturn->IsBaseOrDerivedClass(this_t::Static_GetClassHash()))
		{
			eventparams_t xEventParameters;
			pxReturn->OnEvent(KGE::Hash("OnCreate"), xEventParameters);
			return static_cast<this_t*>(pxReturn);
		}
		delete pxReturn;
		return NULL;
	}

CAPABILITY_PROCESSXML
