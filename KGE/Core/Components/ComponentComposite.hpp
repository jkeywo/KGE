#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{
	class ComponentComposite : public ComponentContainer
	{
		#define THIS_T ComponentComposite
		#define PARENT_T ComponentContainer
		#define HASHSTRING_T "ComponentComposite"
		#include "Core/Components/Component_Include.hpp"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(ComponentContainer*)
			CLASSFACTORY_REGISTERXML_1ARG(ComponentContainer*)
		}
		STATIC_INITIALISE_END

	public:
		ComponentComposite(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{}
		ComponentComposite(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{}

		virtual bool IsComposite() const { return true; }

	};
};