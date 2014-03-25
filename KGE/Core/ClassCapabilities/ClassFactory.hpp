#pragma once

// Class factories can only be used with classes that use the MetaClass #includes

#define CAPABILITYROOT_CLASSFACTORY_ADD												\
public:																				\
	typedef KGE::ClassFactory<root_t> classfactory_t								\
	static root_t* Create( const Hash& xHash ) { return classfactory_t::Get().Create(xHash); }
#define CAPABILITYROOT_CLASSFACTORY_ADDXML											\
public:																				\
	typedef KGE::ClassFactoryXML<root_t> classfactoryxml_t							\
	static root_t* Create( xml_node<char>& xNode ) { return classfactoryxml_t::Get().Create(xNode); }
#define CAPABILITYROOT_CLASSFACTORY_ADD1ARG(ARG0)									\
public:																				\
	typedef KGE::ClassFactory1Arg<root_t,ARG0> classfactory1arg_t					\
	static root_t* Create( const Hash& xHash, ARG0 xArg0 ) { return classfactory1arg_t::Get().Create(xHash, xArg0); }
#define CAPABILITYROOT_CLASSFACTORY_ADDXML1ARG(ARG0)								\
public:																				\
	typedef KGE::ClassFactoryXML1Arg<root_t,ARG0> classfactoryxml1arg_t				\
	static root_t* Create( xml_node<char>& xNode, ARG0 xArg0 ) { return classfactoryxml1arg_t::Get().Create(xNode, xArg0); }
#define CAPABILITYROOT_CLASSFACTORY_ADD2ARGS(ARG0, ARG1)							\
public:																				\
	typedef KGE::ClassFactory2Args<root_t,ARG0,ARG1> classfactory2args_t			\
	static root_t* Create( const Hash& xHash, ARG0 xArg0, ARG1 xArg1 ) { return classfactory2args_t::Get().Create(xHash, xArg0, xArg1); }

#define CAPABILITY_CLASSFACTORY_ADD													\
public:																				\
	static this_t* Create( const Hash& xHash ) { root_t* pxRet = classfactory_t::Get().Create(xHash); if(pxRet->IsBaseOrDerivedClass(this_t::Static_GetClassHash())) return static_cast<thit_t*>(pxRet) delete pxRet; return NULL; }
#define CAPABILITY_CLASSFACTORY_ADDXML												\
public:																				\
	static this_t* Create( xml_node<char>& xNode ) { root_t* pxRet = classfactoryxml_t::Get().Create(xNode); if(pxRet->IsBaseOrDerivedClass(this_t::Static_GetClassHash())) return static_cast<thit_t*>(pxRet) delete pxRet; return NULL; }
#define CAPABILITY_CLASSFACTORY_ADD1ARG(ARG0)										\
public:																				\
	static this_t* Create( const Hash& xHash, ARG0 xArg0 ) { root_t* pxRet = classfactory1arg_t::Get().Create(xHash, xArg0); if(pxRet->IsBaseOrDerivedClass(this_t::Static_GetClassHash())) return static_cast<thit_t*>(pxRet) delete pxRet; return NULL; }
#define CAPABILITY_CLASSFACTORY_ADDXML1ARG(ARG0)									\
public:																				\
	static this_t* Create( xml_node<char>& xNode, ARG0 xArg0 ) { root_t* pxRet = classfactoryxml1arg_t::Get().Create(xNode, xArg0); if(pxRet->IsBaseOrDerivedClass(this_t::Static_GetClassHash())) return static_cast<thit_t*>(pxRet) delete pxRet; return NULL; }
#define CAPABILITY_CLASSFACTORY_ADD2ARGS(ARG0, ARG1)								\
public:																				\
	static this_t* Create( const Hash& xHash, ARG0 xArg0, ARG1 xArg1 ) { root_t* pxRet = classfactory2args_t::Get().Create(xHash, xArg0, xArg1); if(pxRet->IsBaseOrDerivedClass(this_t::Static_GetClassHash())) return static_cast<thit_t*>(pxRet) delete pxRet; return NULL; }


// for registering classes inside static initialiser
#define CLASSFACTORY_REGISTER					KGE::ClassFactory<root_t>::Get().Register( this_t::Static_GetClassHash(), new KGE::CreateFunctor<root_t, this_t>() );
#define CLASSFACTORY_REGISTERXML				KGE::ClassFactoryXML<root_t>::Get().Register( this_t::Static_GetClassHash(), new KGE::CreateFunctorXML<root_t, this_t>() );
#define CLASSFACTORY_REGISTER_1ARG(ARG0)		KGE::ClassFactory1Arg<root_t, ARG0>::Get().Register( this_t::Static_GetClassHash(), new KGE::CreateFunctor1Arg<root_t, this_t, ARG0>() );
#define CLASSFACTORY_REGISTERXML_1ARG(ARG0)		KGE::ClassFactoryXML1Arg<root_t, ARG0>::Get().Register( this_t::Static_GetClassHash(), new KGE::CreateFunctorXML1Arg<root_t, this_t, ARG0>() );
#define CLASSFACTORY_REGISTER_2ARGS(ARG0, ARG1)	KGE::ClassFactory2Args<root_t, ARG0, ARG1>::Get().Register( this_t::Static_GetClassHash(), new KGE::CreateFunctor2Args<root_t, this_t, ARG0, ARG1>() );

namespace KGE
{
	// ************ NO XML + NO ARGS *****************
	template<class root_t>
	class CreateFunctorBase
	{
	public:
		virtual root_t* operator()() = 0;
	};
	template<class root_t>
	class ClassFactory
	{
	public:
		typedef CreateFunctorBase<root_t> Functor;

		static ClassFactory& Get() { static ClassFactory xSingleton; return xSingleton; }
		void Register(const Hash& xHash, Functor* pxCreateFunctor)
		{
			m_xCreateFunctors.insert(FunctorPair(xHash, pxCreateFunctor));
		}
		root_t* Create(const Hash& xHash)
		{
			FunctorCollection::iterator xIt = m_xCreateFunctors.find(xHash);
			if (xIt != m_xCreateFunctors.end() && xIt->second != NULL)
			{
				return (*xIt->second)();
			}
			return NULL;
		}
	protected:
		ClassFactory() {}

		typedef unordered_map< Hash, Functor*, Hash::Hasher > FunctorCollection;
		typedef pair< Hash, Functor* > FunctorPair;

		FunctorCollection m_xCreateFunctors;
	};
	template<class root_t, class this_t>
	class CreateFunctor : public CreateFunctorBase<root_t>
	{
	public:
		virtual root_t* operator()() { return new this_t(); }
	};

	// ************ XML + NO ARGS *****************
	template<class root_t>
	class CreateFunctorXMLBase
	{
	public:
		virtual root_t* operator()(xml_node<char>& xNode) = 0;
	};
	template<class root_t>
	class ClassFactoryXML
	{
	public:
		typedef CreateFunctorXMLBase<root_t> Functor;

		static ClassFactoryXML& Get() { static ClassFactoryXML xSingleton; return xSingleton; }
		void Register(const Hash& xHash, Functor* pxCreateFunctor)
		{
			m_xCreateFunctors.insert(FunctorPair(xHash, pxCreateFunctor));
		}
		root_t* Create(xml_node<char>& xNode)
		{
			Hash xHash = Hash(XMLHandler::GetAttributeValue(xNode, "Type"));
			FunctorCollection::iterator xIt = m_xCreateFunctors.find(xHash);
			if (xIt != m_xCreateFunctors.end() && xIt->second != NULL)
			{
				root_t* pxReturn = (*xIt->second)(xNode);
				pxReturn->ProcessXML(xNode);
				return pxReturn;
			}
			return NULL;
		}
	protected:
		ClassFactoryXML() {}

		typedef unordered_map< Hash, Functor*, Hash::Hasher > FunctorCollection;
		typedef pair< Hash, Functor* > FunctorPair;

		FunctorCollection m_xCreateFunctors;
	};
	template<class root_t, class this_t>
	class CreateFunctorXML : public CreateFunctorXMLBase<root_t>
	{
	public:
		virtual root_t* operator()(xml_node<char>& xNode) { return new this_t(xNode); }
	};

	// ************ NO XML + 1 ARG *****************
	template<class root_t, typename arg0_t>
	class CreateFunctor1ArgBase
	{
	public:
		virtual root_t* operator()(arg0_t xArg0) = 0;
	};
	template<class root_t, typename arg0_t>
	class ClassFactory1Arg
	{
	public:
		typedef CreateFunctor1ArgBase<root_t, arg0_t> Functor;

		static ClassFactory1Arg& Get() { static ClassFactory1Arg xSingleton; return xSingleton; }
		void Register(const Hash& xHash, Functor* pxCreateFunctor)
		{
			m_xCreateFunctors.insert(FunctorPair(xHash, pxCreateFunctor));
		}
		root_t* Create(const Hash& xHash, arg0_t xArg0)
		{
			FunctorCollection::iterator xIt = m_xCreateFunctors.find(xHash);
			if (xIt != m_xCreateFunctors.end() && xIt->second != NULL)
			{
				return (*xIt->second)(xArg0);
			}
			return NULL;
		}
	protected:
		ClassFactory1Arg() {}

		typedef unordered_map< Hash, Functor*, Hash::Hasher > FunctorCollection;
		typedef pair< Hash, Functor* > FunctorPair;

		FunctorCollection m_xCreateFunctors;
	};
	template<class root_t, class this_t, typename arg0_t>
	class CreateFunctor1Arg : public CreateFunctor1ArgBase<root_t, arg0_t>
	{
	public:
		virtual root_t* operator()(arg0_t xArg0) { return new this_t(xArg0); }
	};

	// ************ XML + 1 ARG *****************
	template<class root_t, typename arg0_t>
	class CreateFunctorXML1ArgBase
	{
	public:
		virtual root_t* operator()(xml_node<char>& xNode, arg0_t xArg0) = 0;
	};
	template<class root_t, typename arg0_t>
	class ClassFactoryXML1Arg
	{
	public:
		typedef CreateFunctorXML1ArgBase<root_t, arg0_t> Functor;

		static ClassFactoryXML1Arg& Get() { static ClassFactoryXML1Arg xSingleton; return xSingleton; }
		void Register(const Hash& xHash, Functor* pxCreateFunctor)
		{
			m_xCreateFunctors.insert(FunctorPair(xHash, pxCreateFunctor));
		}
		root_t* Create(xml_node<char>& xNode, arg0_t xArg0)
		{
			Hash xHash = Hash(XMLHandler::GetAttributeValue(xNode, "Type"));
			FunctorCollection::iterator xIt = m_xCreateFunctors.find(xHash);
			if (xIt != m_xCreateFunctors.end() && xIt->second != NULL)
			{
				root_t* pxReturn = (*xIt->second)(xNode, xArg0);
				pxReturn->ProcessXML(xNode);
				return pxReturn;
			}
			return NULL;
		}
	protected:
		ClassFactoryXML1Arg() {}

		typedef unordered_map< Hash, Functor*, Hash::Hasher > FunctorCollection;
		typedef pair< Hash, Functor* > FunctorPair;

		FunctorCollection m_xCreateFunctors;
	};
	template<class root_t, class this_t, typename arg0_t>
	class CreateFunctorXML1Arg : public CreateFunctorXML1ArgBase<root_t, arg0_t>
	{
	public:
		virtual root_t* operator()(xml_node<char>& xNode, arg0_t xArg0) { return new this_t(xNode, xArg0); }
	};

	// ************ NO XML + 2 ARGS *****************
	template<class root_t, typename arg0_t, typename arg1_t>
	class CreateFunctor2ArgsBase
	{
	public:
		virtual root_t* operator()(arg0_t xArg0, arg1_t xArg1) = 0;
	};
	template<class root_t, typename arg0_t, typename arg1_t>
	class ClassFactory2Args
	{
	public:
		typedef CreateFunctor2ArgsBase<root_t, arg0_t, arg1_t> Functor;

		static ClassFactory2Args& Get() { static ClassFactory2Args xSingleton; return xSingleton; }
		void Register(const Hash& xHash, Functor* pxCreateFunctor)
		{
			m_xCreateFunctors.insert(FunctorPair(xHash, pxCreateFunctor));
		}
		root_t* Create(const Hash& xHash, arg0_t xArg0, arg1_t xArg1)
		{
			FunctorCollection::iterator xIt = m_xCreateFunctors.find(xHash);
			if (xIt != m_xCreateFunctors.end() && xIt->second != NULL)
			{
				return (*xIt->second)(xArg0, xArg1);
			}
			return NULL;
		}
	protected:
		ClassFactory2Args() {}

		typedef unordered_map< Hash, Functor*, Hash::Hasher > FunctorCollection;
		typedef pair< Hash, Functor* > FunctorPair;

		FunctorCollection m_xCreateFunctors;
	};
	template<class root_t, class this_t, typename arg0_t, typename arg1_t>
	class CreateFunctor2Args : public CreateFunctor2ArgsBase<root_t, arg0_t, arg1_t>
	{
	public:
		virtual root_t* operator()(arg0_t xArg0, arg1_t xArg1) { return new this_t(xArg0, xArg1); }
	};
};
