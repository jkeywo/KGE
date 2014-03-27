#pragma once

#include "Core/ClassCapabilities/ClassFactory.hpp"
#include "Core/ClassCapabilities/Events.hpp"
#include "Core/ClassCapabilities/Properties.hpp"
#include "Core/ClassCapabilities/XMLParser.hpp"

namespace KGE
{
	class ComponentContainer;

	class Component
	{
		#define THIS_T Component
		#include "Core/ClassCapabilities/MetaClass_IncludeRoot.hpp"
		CAPABILITYROOT_PROCESSXML
		#include "Core/ClassCapabilities/Properties_IncludeRoot.hpp"
		#include "Core/ClassCapabilities/Events_IncludeRoot.hpp"
		
		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE( "Name", ProcessName );
			XMLPARSER_REGISTERCHILDNODE( "OnCreate", ProcessOnCreate );
			XMLPARSER_REGISTERCHILDNODE( "OnActivate", ProcessOnActivate );
			XMLPARSER_REGISTERCHILDNODE( "OnDeactivate", ProcessOnDeactivate );
			XMLPARSER_REGISTERCHILDNODE( "OnDestroy", ProcessOnDestroy );
		}
		STATIC_INITIALISE_END

	public:
		typedef KGE::ClassFactory1Arg<root_t, ComponentContainer*> classfactory1arg_t;	
		static root_t* Create(const Hash& xHash, ComponentContainer* pxParent)
		{
			root_t* pxReturn = classfactory1arg_t::Get().Create(xHash, pxParent);
			if (pxReturn)
			{
				eventparams_t xEventParameters;
				pxReturn->OnEvent(KGE::Hash("OnCreate"), xEventParameters);
			}
			return pxReturn;
		}
		typedef KGE::ClassFactoryXML1Arg<root_t, ComponentContainer*> classfactoryxml1arg_t;
		static this_t* Create(xml_node<char>& xNode, ComponentContainer* pxParent)
		{
			root_t* pxReturn = classfactoryxml1arg_t::Get().Create(xNode, pxParent);
			if (pxReturn)
			{
				eventparams_t xEventParameters;
				pxReturn->OnEvent(KGE::Hash("OnCreate"), xEventParameters);
			}
			return pxReturn;
		}

		static void DeleteDestroyed();

		enum State
		{
			Unset,
			Active,
			Dormant,
			Destroyed,
		};
		Component(ComponentContainer* pxParent);
		Component(xml_node<char>& xNode, ComponentContainer* pxParent);
		virtual ~Component();

		Component* GetComponentByPath(const string& xPath);
		template<class TYPE_T> TYPE_T* GetParentByType() { return static_cast<TYPE_T*>( GetParentByType( TYPE_T::Static_GetClassHash() ) ); }
		Component* GetParentByType(const Hash& xType);
		Component* GetParentByName(const Hash& xName);

	protected:
		virtual void OnCreate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnActivate(eventparams_t& xEventParameters) { m_eState = Active; }
		virtual void OnDeactivate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnDestroy(eventparams_t& xEventParameters) { m_eState = Destroyed; s_xDestroyedComponents.push_back(this); }

		void RegisterEvents();

		virtual void ProcessName( xml_attribute<char>& xName );
		virtual void ProcessOnCreate( xml_node<char>& xName );
		virtual void ProcessOnActivate( xml_node<char>& xName );
		virtual void ProcessOnDeactivate( xml_node<char>& xName );
		virtual void ProcessOnDestroy( xml_node<char>& xName );

		static list<Component*> s_xDestroyedComponents;

		State m_eState;
		ComponentContainer* m_pxParent;
		xml_node<char>* m_pxXMLNode;
		Hash m_xName;
	};

	class ComponentContainer : public Component
	{
		#define THIS_T ComponentContainer
		#define PARENT_T Component
		#define HASHSTRING_T "ComponentContainer"
		#include "Core/Components/Component_Include.hpp"

	public:
		ComponentContainer(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{}
		ComponentContainer(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{}
	};
};