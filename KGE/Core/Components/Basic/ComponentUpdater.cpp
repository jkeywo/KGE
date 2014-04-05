#include "KGE.hpp"
#include "Core/Components/Basic/ComponentUpdater.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(ComponentUpdater);

	unordered_set<ComponentUpdater*, ComponentUpdater::Hasher> ComponentUpdater::s_xAllUpdaters;

	void ComponentUpdater::UpdateAll(float fDT)
	{
		FOREACH(xIt, s_xAllUpdaters)
		{
			(*xIt)->Update(fDT);
		}
	}

	void ComponentUpdater::Update(float fDT)
	{
		FOREACH(xIt, m_xUpdateList.get<1>())
		{
			(*xIt)->Update(fDT);
		}
	}
	void ComponentUpdater::RegisterUpdate(Component* pxComponent)
	{
		m_xUpdateList.insert(pxComponent);
	}
	void ComponentUpdater::UnregisterUpdate(Component* pxComponent)
	{
		m_xUpdateList.erase(pxComponent);
	}

	void ComponentUpdater::OnActivate(eventparams_t& xEventParameters)
	{
		parent_t::OnActivate(xEventParameters);
		s_xAllUpdaters.insert(this);
	}
	void ComponentUpdater::OnDeactivate(eventparams_t& xEventParameters)
	{
		parent_t::OnDeactivate(xEventParameters);
		s_xAllUpdaters.erase(this);
	}
};