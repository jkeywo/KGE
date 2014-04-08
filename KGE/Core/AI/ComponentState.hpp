#pragma once

#include "Core/Components/ComponentCollection.hpp"

namespace KGE
{
	class ComponentState : public ComponentCollection
	{
		METACLASS_CHILDDATA(ComponentState, ComponentCollection, "State")
		#include "Core/Components/Component_Include.ext"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(TUID<KGE::Component>::CachedReference)
			CLASSFACTORY_REGISTERXML_1ARG(TUID<KGE::Component>::CachedReference)
		}
		STATIC_INITIALISE_END

	public:
		ComponentState(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
		{
		}
		ComponentState(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
		{
		}
		virtual ~ComponentState()
		{
		}

	};
};