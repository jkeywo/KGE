#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{
	class ComponentComposite : public ComponentContainer
	{
		METACLASS_CHILDDATA(ComponentComposite, ComponentContainer, "Composite")
		#include "Core/Components/Component_Include.ext"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(TUID<Component>::CachedReference)
			CLASSFACTORY_REGISTERXML_1ARG(TUID<Component>::CachedReference)
		}
		STATIC_INITIALISE_END

	public:
		ComponentComposite(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
		{}
		ComponentComposite(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
		{}

		virtual bool IsComposite() const { return true; }

		virtual Data GetProperty(const Hash& xHash);
		virtual bool SetProperty(const Hash& xHash, Data xData);
		virtual void OnEvent(const KGE::Hash& xEventHash, KGE::eventparams_t& xEventParameters);

		virtual ComponentUpdater* GetUpdater();
		virtual ComponentLayer* GetLayer();

	};
};