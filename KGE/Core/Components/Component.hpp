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
		#define SUPPORT_CLASSFACTORY_1ARG		TUID<Component>::CachedReference
		#define SUPPORT_CLASSFACTORY_XML_1ARG	TUID<Component>::CachedReference
		#include "Core/ClassCapabilities/MetaClass_IncludeRoot.ext"	
		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE( "Name", ProcessName );
			XMLPARSER_REGISTERCHILDNODE( "Signal", ProcessSignal );
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
		Component(TUID<Component>::CachedReference xParent);
		Component(xml_node<char>& xNode, TUID<Component>::CachedReference xParent);
		virtual ~Component();

		void OnEventByPath(const char* szPath, eventparams_t& xEventParameters);
		Event<Component>* GetEventByPath(const char* szPath);
		Data GetPropertyByPath(const char* szPath);
		template<class TYPE_T> TYPE_T* GetParentByType() { return static_cast<TYPE_T*>(GetParentByType(TYPE_T::Static_GetClassHash())); }
		Component* GetParentByType(const Hash& xType);
		Component* GetParentByName(const Hash& xName);

		virtual ComponentUpdater* GetUpdater();
		virtual ComponentLayer* GetLayer();

		virtual float GetPriority() { return 0.0f; }
		const Hash& GetName() { return m_xName; }
		State GetState() { return m_eState; }
		virtual bool IsComposite() const { return false; }
		virtual bool IsCollection() const { return false; }

		virtual void OnCreate(eventparams_t& xEventParameters);
		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);
		virtual void OnDestroy(eventparams_t& xEventParameters);

		virtual bool HandleInput(sf::Event& xEvent, sf::Window* pxWindow) { return false; }
		virtual void Render(sf::RenderTarget& xTarget) {}
		virtual void Update(float fDT) {}

	protected:
		void RegisterEvents();

		virtual void ProcessName( xml_attribute<char>& xName );
		virtual void ProcessSignal(xml_node<char>& xName);

		static list<Component*> s_xDestroyedComponents;

		State m_eState;
		TUID<Component>::CachedReference m_xParent;
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
		#include "Core/Components/Component_Include.ext"
		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERCHILDNODE("Component", PopulateComponent);
		}
		STATIC_INITIALISE_END

	public:
		ComponentContainer(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
		{}
		ComponentContainer(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
		{}
		virtual ~ComponentContainer() {}

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);
		virtual void OnDestroy(eventparams_t& xEventParameters);

	protected:
		void PopulateComponent(xml_node<char>& xComponentNode);

		componentcontainer_t m_xComponents;
	};
};