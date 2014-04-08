#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{


	class ComponentCollection : public ComponentContainer
	{
		METACLASS_CHILDDATA(ComponentCollection, ComponentContainer, "Collection")
		#include "Core/Components/Component_Include.ext"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(TUID<Component>::CachedReference)
			CLASSFACTORY_REGISTERXML_1ARG(TUID<Component>::CachedReference)
		}
		STATIC_INITIALISE_END

	public:
		ComponentCollection(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
		{}
		ComponentCollection(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
		{}

		virtual bool IsCollection() const { return true; }

	};
};