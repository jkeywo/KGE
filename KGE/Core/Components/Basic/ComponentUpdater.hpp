#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{
	class ComponentUpdater : public Component
	{
		METACLASS_CHILDDATA(ComponentUpdater, Component, "Updater")
		#include "Core/Components/Component_Include.hpp"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(ComponentContainer*)
			CLASSFACTORY_REGISTERXML_1ARG(ComponentContainer*)
		}
		STATIC_INITIALISE_END

	public:
		struct Hasher
		{
			size_t operator()(const ComponentUpdater* pxUpdater) const
			{
				TUID<Component>::Hasher xHasher;
				return pxUpdater ? xHasher(pxUpdater->GetTUID()) : 0;
			}
		};

		ComponentUpdater(ComponentContainer* pxParent)
			: parent_t(pxParent)
		{}
		ComponentUpdater(xml_node<char>& xNode, ComponentContainer* pxParent)
			: parent_t(xNode, pxParent)
		{}
		virtual ~ComponentUpdater()
		{}

		virtual ComponentUpdater* GetUpdater() { return this; }

		static void UpdateAll(float fDT);

		virtual void Update(float fDT);
		virtual void RegisterUpdate(Component* pxComponent);
		virtual void UnregisterUpdate(Component* pxComponent);

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);

	protected:
		static unordered_set<ComponentUpdater*, Hasher> s_xAllUpdaters;
		componentcontainer_t m_xUpdateList;
	};
};