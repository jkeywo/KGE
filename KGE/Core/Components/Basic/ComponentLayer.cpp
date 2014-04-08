#include "KGE.hpp"
#include "Core/Components/Basic/ComponentLayer.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(ComponentLayer);

	bool ComponentLayer::HandleInput(sf::Event& xEvent, sf::Window* pxWindow)
	{
		FOREACH_R(xIt, m_xHandleInputList.get<1>())
		{
			if ((*xIt)->HandleInput(xEvent, pxWindow))
			{
				return true;
			}
		}
		return false;
	}
	void ComponentLayer::RegisterHandleInput(Component* pxComponent)
	{
		m_xHandleInputList.insert(pxComponent);
	}
	void ComponentLayer::UnregisterHandleInput(Component* pxComponent)
	{
		m_xHandleInputList.erase(pxComponent);
	}

	void ComponentLayer::Render(sf::RenderTarget& xTarget)
	{
		FOREACH(xIt, m_xRenderList.get<1>())
		{
			(*xIt)->Render(xTarget);
		}
	}
	void ComponentLayer::RegisterRender(Component* pxComponent)
	{
		m_xRenderList.insert(pxComponent);
	}
	void ComponentLayer::UnregisterRender(Component* pxComponent)
	{
		m_xRenderList.erase(pxComponent);
	}

	void ComponentLayer::OnActivate(eventparams_t& xEventParameters)
	{
		parent_t::OnActivate(xEventParameters);
		if (m_xParent())
		{
			ComponentLayer* pxLayer = m_xParent()->GetLayer();
			if (pxLayer)
			{
				pxLayer->RegisterHandleInput(this);
				pxLayer->RegisterRender(this);
			}
		}
	}
	void ComponentLayer::OnDeactivate(eventparams_t& xEventParameters)
	{
		parent_t::OnDeactivate(xEventParameters);
		if (m_xParent())
		{
			ComponentLayer* pxLayer = m_xParent()->GetLayer();
			if (pxLayer)
			{
				pxLayer->UnregisterHandleInput(this);
				pxLayer->UnregisterRender(this);
			}
		}
	}
};