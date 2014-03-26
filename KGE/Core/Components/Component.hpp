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
		CAPABILITYROOT_CLASSFACTORY_ADD1ARG(ComponentContainer*)
		CAPABILITYROOT_CLASSFACTORY_ADDXML1ARG(ComponentContainer*)
		CAPABILITYROOT_PROCESSXML
		#include "Core/ClassCapabilities/Properties_IncludeRoot.hpp"
		#include "Core/ClassCapabilities/Events_IncludeRoot.hpp"

	public:
		enum State
		{
			Unset,
			Active,
			Dormant,
			Destroyed,
		};
		Component(ComponentContainer* pxParent)
			: m_xTUID(*this)
			, m_pxParent(pxParent)
			, m_eState(Unset)
			, m_pxXMLNode(NULL)
		{
			RegisterEvents();
		}
		Component(xml_node<char>& xNode, ComponentContainer* pxParent)
			: m_xTUID(*this)
			, m_pxParent(pxParent)
			, m_eState(Unset)
			, m_pxXMLNode(&xNode)
		{
			RegisterEvents();
		}
		virtual ~Component()
		{
			ClearProperties();
			ClearEvents();
		}

	protected:
		virtual void OnCreate(Event<root_t>::params_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnActivate(Event<root_t>::params_t& xEventParameters) { m_eState = Active; }
		virtual void OnDeactivate(Event<root_t>::params_t& xEventParameters) { m_eState = Dormant; }
		virtual void OnDestroy(Event<root_t>::params_t& xEventParameters) { m_eState = Destroyed; }

		void RegisterEvents()
		{
			RegisterEvent(Hash("OnCreate"), boost::bind( &root_t::OnCreate, this, _1 ) );
			RegisterEvent(Hash("OnActivate"), boost::bind( &root_t::OnActivate, this, _1 ) );
			RegisterEvent(Hash("OnDeactivate"), boost::bind( &root_t::OnDeactivate, this, _1 ) );
			RegisterEvent(Hash("OnDestroy"), boost::bind( &root_t::OnDestroy, this, _1 ) );
		}

		State m_eState;
		ComponentContainer* m_pxParent;
		xml_node<char>* m_pxXMLNode;
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