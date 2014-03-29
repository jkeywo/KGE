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

		void OnEventByPath(const char* szPath, eventparams_t& xEventParameters);
		Data GetPropertyByPath(const char* szPath);
		template<class TYPE_T> TYPE_T* GetParentByType() { return static_cast<TYPE_T*>(GetParentByType(TYPE_T::Static_GetClassHash())); }
		Component* GetParentByType(const Hash& xType);
		Component* GetParentByName(const Hash& xName);

		virtual float GetPriority() { return 0.0f; }

		virtual void OnCreate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnActivate(eventparams_t& xEventParameters) { m_eState = Active; }
		virtual void OnDeactivate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnDestroy(eventparams_t& xEventParameters) { m_eState = Destroyed; s_xDestroyedComponents.push_back(this); }

	protected:
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

	typedef multi_index_container<
			Component*,
			indexed_by
			<
				ordered_unique< multi_index::identity<Component*> >,
				ordered_non_unique< multi_index::mem_fun<Component, float, &Component::GetPriority> >
			>
		> componentcontainer_t;

	class ComponentContainer : public Component
	{
		#define THIS_T ComponentContainer
		#define PARENT_T Component
		#define HASHSTRING_T "ComponentContainer"
		#include "Core/Components/Component_Include.hpp"

		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERCHILDNODE("Component", PopulateComponent);
		}
		STATIC_INITIALISE_END
	public:
		ComponentContainer(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{}
		ComponentContainer(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{}
		virtual ~ComponentContainer() {}

		virtual bool IsComposite() const { return false; }
		virtual bool IsCollection() const { return false; }

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);
		virtual void OnDestroy(eventparams_t& xEventParameters);

	protected:
		void PopulateComponent(xml_node<char>& xComponentNode);

		componentcontainer_t m_xComponents;
	};
};