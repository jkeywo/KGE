#pragma once

#include "Core/Components/ComponentCollection.hpp"

namespace KGE
{
	class ComponentState : public ComponentCollection
	{
		#define THIS_T ComponentState
		#define PARENT_T ComponentCollection
		#define HASHSTRING_T "State"
		#include "Core/Components/Component_Include.hpp"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(ComponentContainer*)
			CLASSFACTORY_REGISTERXML_1ARG(ComponentContainer*)
		}
		STATIC_INITIALISE_END

	public:
		ComponentState(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{
		}
		ComponentState(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{
		}
		virtual ~ComponentState()
		{
		}

	};
};