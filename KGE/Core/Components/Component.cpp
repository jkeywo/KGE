#include "KGE.hpp"
#include "Core/Components/Component.hpp"

#include "Core/ClassCapabilities/EventSignal.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(Component)
	list<Component*> Component::s_xDestroyedComponents;

	void Component::DeleteDestroyed()
	{
		while (s_xDestroyedComponents.begin() != s_xDestroyedComponents.end())
		{
			Component* pxDelete = s_xDestroyedComponents.front();
			assert(pxDelete->m_eState == Destroyed);
			delete pxDelete;
			s_xDestroyedComponents.erase(s_xDestroyedComponents.begin());
		}
	}

	Component::Component(TUID<Component>::CachedReference xParent)
		: m_xTUID(*this)
		, m_xParent(xParent)
		, m_eState(Unset)
		, m_pxXMLNode(NULL)
	{
		RegisterEvents();
	}
	Component::Component(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
		: m_xTUID(*this)
		, m_xParent(xParent)
		, m_eState(Unset)
		, m_pxXMLNode(&xNode)
	{
		RegisterEvents();
	}
	Component::~Component()
	{
		ClearProperties();
		ClearEvents();
	}

	void Component::OnEventByPath(const char* szPath, eventparams_t& xEventParameters)
	{
		Event<Component>* pxEvent = GetEventByPath(szPath);
		if (pxEvent)
		{
			pxEvent->Execute(xEventParameters);
		}
	}
	Event<Component>* Component::GetEventByPath(const char* szPath)
	{
		Hash xToken;
		bool bStringEnd = false;
		Component* pxTarget = this;
		// are we looking for a parent by type?
		if ((*szPath) == '_')
		{
			szPath++;
			bStringEnd = xToken.FromToken('.', szPath);
			pxTarget = Component::GetParentByType(xToken);
			if (bStringEnd)
			{
				assert(false);
				return NULL;
			}
		}
		bStringEnd = xToken.FromToken('.', szPath);
		if (bStringEnd)
		{
			// this should be an event
			return pxTarget->GetEvent(xToken);
		}
		else
		{
			// this should be a property or parent then
			Data xData = pxTarget->GetProperty(xToken);
			if (xData.GetType() == Data::UNSET)
			{
				// no property found, are we looking for a parent by name?
				Component* pxParent = pxTarget->GetParentByType(xToken);
				if (pxParent)
				{
					xData = Data(pxParent);
				}
			}
			// there is more to process, lets hope we have a component now...
			assert(xData.GetType() == Data::COMPONENT);
			if (xData.AsComponent())
			{
				return xData.AsComponent()->GetEventByPath(szPath);
			}
		}
		return NULL;
	}

	Data Component::GetPropertyByPath(const char* szPath)
	{
		Hash xToken;
		bool bStringEnd = false;
		Component* pxTarget = this;
		// are we looking for a parent by type?
		if ((*szPath) == '_')
		{
			szPath++;
			bStringEnd = xToken.FromToken('.', szPath);
			pxTarget = Component::GetParentByType(xToken);
			if (bStringEnd)
			{
				return Data(pxTarget);
			}
		}
		// are we looking for a property?
		bStringEnd = xToken.FromToken('.', szPath);
		Data xData = pxTarget->GetProperty(xToken);
		if (xData.GetType() == Data::UNSET)
		{
			// no property found, are we looking for a parent by name?
			Component* pxParent = pxTarget->GetParentByType(xToken);
			if (pxParent)
			{
				xData = Data(pxParent);
			}
		}
		if (bStringEnd)
		{
			return xData;
		}
		// there is more to process, lets hope we have a component now...
		assert(xData.GetType() == Data::COMPONENT);
		if(xData.AsComponent())
		{
			return xData.AsComponent()->GetPropertyByPath(szPath);
		}
		return Data();
	}
	Component* Component::GetParentByType(const Hash& xType)
	{
		if (m_xParent())
		{
			if (m_xParent()->IsBaseOrDerivedClass(xType))
			{
				return m_xParent();
			}
			return m_xParent()->GetParentByType(xType);
		}
		return NULL;
	}
	Component* Component::GetParentByName(const Hash& xName)
	{
		if (m_xParent())
		{
			if (m_xParent()->GetName() == xName)
			{
				return m_xParent();
			}
			return m_xParent()->GetParentByName(xName);
		}
		return NULL;
	}

	ComponentUpdater* Component::GetUpdater()
	{
		return m_xParent() ? m_xParent()->GetUpdater() : NULL;
	}
	ComponentLayer* Component::GetLayer()
	{
		return m_xParent() ? m_xParent()->GetLayer() : NULL;
	}
	
	void Component::RegisterEvents()
	{
		RegisterEvent(g_xHASH_ONCREATE, boost::bind(&root_t::OnCreate, this, _1));
		RegisterEvent(g_xHASH_ONACTIVATE, boost::bind(&root_t::OnActivate, this, _1));
		RegisterEvent(g_xHASH_ONDEACTIVATE, boost::bind(&root_t::OnDeactivate, this, _1));
		RegisterEvent(g_xHASH_ONDESTROY, boost::bind(&root_t::OnDestroy, this, _1));
	}

	void Component::OnCreate(eventparams_t& xEventParameters) 
	{ 
		m_eState = Dormant;
	}
	void Component::OnActivate(eventparams_t& xEventParameters) 
	{ 
		m_eState = Active;
		ActivateSignals();
	}
	void Component::OnDeactivate(eventparams_t& xEventParameters) 
	{ 
		m_eState = Dormant;
		DeactivateSignals();
	}
	void Component::OnDestroy(eventparams_t& xEventParameters)
	{
		if (m_eState == Destroyed)
		{
			return;
		}
		else if (m_eState == Active)
		{
			OnDeactivate(xEventParameters);
		}
		m_eState = Destroyed;
		s_xDestroyedComponents.push_back(this);
	}

	void Component::ProcessName( xml_attribute<char>& xName )
	{
		m_xName = Hash( xName.value() );
	}
	void Component::ProcessSignal(xml_node<char>& xEvent)
	{
		RegisterEventSignal(new EventSignal<root_t>(xEvent, *this));
	}

	/////////////////////////////////////////////////////////////////////////
	//	ComponentContainer

	STATIC_INITIALISE_RUN(ComponentContainer)

	void ComponentContainer::OnActivate(eventparams_t& xEventParameters)
	{
		parent_t::OnActivate(xEventParameters);
		FOREACH(xIt, m_xComponents)
		{
			(*xIt)->OnActivate(xEventParameters);
		}
	}
	void ComponentContainer::OnDeactivate(eventparams_t& xEventParameters)
	{
		parent_t::OnDeactivate(xEventParameters);
		FOREACH(xIt, m_xComponents)
		{
			(*xIt)->OnDeactivate(xEventParameters);
		}
	}
	void ComponentContainer::OnDestroy(eventparams_t& xEventParameters)
	{
		parent_t::OnDestroy(xEventParameters);
		FOREACH(xIt, m_xComponents)
		{
			(*xIt)->OnDestroy(xEventParameters);
		}
	}

	void ComponentContainer::PopulateComponent(xml_node<char>& xComponentNode)
	{
		Component* pxRootObject = Component::Create(xComponentNode, m_xTUID.GetCachedReference());
		if (pxRootObject)
		{
			m_xComponents.insert(pxRootObject);
		}
	}


};