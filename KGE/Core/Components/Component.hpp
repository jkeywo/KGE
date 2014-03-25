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
		Component(ComponentContainer* pxParent)
			: m_xTUID(*this)
		{}
		Component(xml_node<char>& xNode, ComponentContainer* pxParent)
			: m_xTUID(*this)
		{}
		virtual ~Component()
		{
			ClearProperties();
			ClearEvents();
		}
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