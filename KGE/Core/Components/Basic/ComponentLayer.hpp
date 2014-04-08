#pragma once

#include "Core/Components/Component.hpp"

namespace KGE
{
	class ComponentLayer : public Component
	{
		METACLASS_CHILDDATA(ComponentLayer, Component, "Layer")
		#include "Core/Components/Component_Include.ext"

		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(TUID<Component>::CachedReference)
			CLASSFACTORY_REGISTERXML_1ARG(TUID<Component>::CachedReference)
		}
		STATIC_INITIALISE_END

	public:
		typedef std::function<bool(sf::Event& xEvent)> handleinputcallback_t;
		typedef std::function<void(sf::RenderTarget&)> rendercallback_t;

		ComponentLayer(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
		{}
		ComponentLayer(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
		{}

		virtual ComponentLayer* GetLayer() { return this; }

		virtual bool HandleInput(sf::Event& xEvent, sf::Window* pxWindow);
		virtual void RegisterHandleInput(Component* pxComponent);
		virtual void UnregisterHandleInput(Component* pxComponent);

		virtual void Render(sf::RenderTarget& xTarget);
		virtual void RegisterRender(Component* pxComponent);
		virtual void UnregisterRender(Component* pxComponent);

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);

	protected:
		componentcontainer_t m_xHandleInputList;
		componentcontainer_t m_xRenderList;
	};
};