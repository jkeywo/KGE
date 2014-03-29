#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{


	class ComponentCollection : public ComponentContainer
	{
		#define THIS_T ComponentCollection
		#define PARENT_T ComponentContainer
		#define HASHSTRING_T "ComponentCollection"
		#include "Core/Components/Component_Include.hpp"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(ComponentContainer*)
			CLASSFACTORY_REGISTERXML_1ARG(ComponentContainer*)
		}
		STATIC_INITIALISE_END

	public:
		ComponentCollection(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{}
		ComponentCollection(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{}

		virtual bool IsCollection() const { return true; }

	};
};