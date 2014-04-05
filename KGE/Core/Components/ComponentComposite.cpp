#include "KGE.hpp"
#include "Core/Components/ComponentComposite.hpp"

#include "Core/Components/Basic/ComponentLayer.hpp"
#include "Core/Components/Basic/ComponentUpdater.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(ComponentComposite);

	Data ComponentComposite::GetProperty(const Hash& xHash)
	{
		FOREACH(xIt, m_xComponents)
		{
			Data xRet = (*xIt)->GetProperty(xHash);
			if (xRet.GetType() != Data::UNSET)
			{
				return xRet;
			}
		}
		propertycollection_t::iterator xIt = m_xProperties.find(xHash);
		if (xIt != m_xProperties.end())
		{
			return xIt->second->GetData();
		}
		return Data();
	}
	bool ComponentComposite::SetProperty(const Hash& xHash, Data xData)
	{
		FOREACH(xIt, m_xComponents)
		{
			if ((*xIt)->SetProperty(xHash, xData))
			{
				return true;
			}
		}
		propertycollection_t::iterator xIt = m_xProperties.find(xHash);
		if (xIt != m_xProperties.end())
		{
			xIt->second->SetData(xData);
			return true;
		}
		return false;
	}
	void ComponentComposite::OnEvent(const KGE::Hash& xEventHash, KGE::eventparams_t& xEventParameters)
	{
		KGE::Event<root_t>::collection_t::iterator xIt = m_xEvents.find(xEventHash);
		if (xIt != m_xEvents.end())
		{
			xIt->second->Execute(xEventParameters);
		}
		FOREACH(xIt, m_xComponents)
		{
			(*xIt)->OnEvent(xEventHash, xEventParameters);
		}
	}

	ComponentUpdater* ComponentComposite::GetUpdater()
	{
		FOREACH(xIt, m_xComponents)
		{
			if ((*xIt)->IsBaseOrDerivedClass(ComponentUpdater::Static_GetClassHash()))
			{
				return static_cast<ComponentUpdater*>(*xIt);
			}
		}
		return parent_t::GetUpdater();
	}
	ComponentLayer* ComponentComposite::GetLayer()
	{
		FOREACH(xIt, m_xComponents)
		{
			if ((*xIt)->IsBaseOrDerivedClass(ComponentLayer::Static_GetClassHash()))
			{
				return static_cast<ComponentLayer*>(*xIt);
			}
		}
		return parent_t::GetLayer();
	}

};