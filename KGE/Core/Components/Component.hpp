#pragma once

#include "Core/ClassCapabilities/MetaClass.hpp"
#include "Core/ClassCapabilities/ClassFactory.hpp"
#include "Core/ClassCapabilities/Events.hpp"
#include "Core/ClassCapabilities/Properties.hpp"
#include "Core/ClassCapabilities/XMLParser.hpp"

namespace KGE
{
	class ComponentContainer;
	class ComponentUpdater;
	class ComponentLayer;

	class Component
	{
		METACLASS_ROOTDATA(Component)
		#define SUPPORT_XML
		#define SUPPORT_EVENTS
		#define SUPPORT_PROPERTIES
		#define SUPPORT_CLASSFACTORY_1ARG		ComponentContainer*
		#define SUPPORT_CLASSFACTORY_XML_1ARG	ComponentContainer*
		#include "Core/ClassCapabilities/MetaClass_IncludeRoot.hpp"	
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

		virtual ComponentUpdater* GetUpdater();
		virtual ComponentLayer* GetLayer();

		virtual float GetPriority() { return 0.0f; }
		const Hash& GetName() { return m_xName; }
		State GetState() { return m_eState; }

		virtual void OnCreate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnActivate(eventparams_t& xEventParameters) { m_eState = Active; }
		virtual void OnDeactivate(eventparams_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnDestroy(eventparams_t& xEventParameters) { m_eState = Destroyed; s_xDestroyedComponents.push_back(this); }

		virtual bool HandleInput(sf::Event& xEvent, sf::Window* pxWindow ) { return false; }
		virtual void Render(sf::RenderTarget& xTarget) {}
		virtual void Update(float fDT) {}

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
		METACLASS_CHILDDATA(ComponentContainer, Component, "ComponentContainer")
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