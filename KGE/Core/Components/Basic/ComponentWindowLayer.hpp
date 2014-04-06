#pragma once

#include "Core/Components/Basic/ComponentLayer.hpp"

namespace KGE
{
	class ComponentWindowLayer : public ComponentLayer
	{
		METACLASS_CHILDDATA(ComponentWindowLayer, ComponentLayer, "WindowLayer")
		#include "Core/Components/Component_Include.hpp"
		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(ComponentContainer*)
			CLASSFACTORY_REGISTERXML_1ARG(ComponentContainer*)
			XMLPARSER_REGISTERATTRIBUTE("Fullscreen", ProcessFullscreen);
			XMLPARSER_REGISTERATTRIBUTE("XResolution", ProcessXResolution);
			XMLPARSER_REGISTERATTRIBUTE("YResolution", ProcessYResolution);
		}
		STATIC_INITIALISE_END

	public:
		struct Hasher
		{
			size_t operator()(const ComponentWindowLayer* pxLayer) const
			{
				TUID<Component>::Hasher xHasher;
				return pxLayer ? xHasher(pxLayer->GetTUID()) : 0;
			}
		};

		ComponentWindowLayer(ComponentContainer* pxParent);
		ComponentWindowLayer(xml_node<char>& xNode, ComponentContainer* pxParent);
		virtual ~ComponentWindowLayer();

		static void HandleInputAll();
		static void RenderAll();

		virtual void HandleInput();
		virtual void Render();

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);

	protected:
		virtual void ProcessFullscreen(xml_attribute<char>& xName);
		virtual void ProcessXResolution(xml_attribute<char>& xName);
		virtual void ProcessYResolution(xml_attribute<char>& xName);

		static unordered_set<ComponentWindowLayer*, Hasher> s_xAllWindows;

		sf::RenderWindow* m_pxWindow;
		bool m_bFullscreen;
		bool m_bNativeResolution;
		int m_iXResolution;
		int m_iYResolution;
	};
};