#pragma once

#include "Core/Components/ComponentCollection.hpp"

namespace KGE
{
	class ComponentState : public ComponentCollection
	{
		METACLASS_CHILDDATA(ComponentState, ComponentCollection, "State")
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