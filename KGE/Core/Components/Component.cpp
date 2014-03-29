#include "KGE.hpp"
#include "Core/Components/Component.hpp"

#include "Core/Actions/Action.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(Component)
	list<Component*> Component::s_xDestroyedComponents;

	void Component::DeleteDestroyed()
	{
		while( s_xDestroyedComponents.front() )
		{
			assert( s_xDestroyedComponents.front()->m_eState == Destroyed );
			delete s_xDestroyedComponents.front();
		}
	}

	Component::Component(ComponentContainer* pxParent)
		: m_xTUID(*this)
		, m_pxParent(pxParent)
		, m_eState(Unset)
		, m_pxXMLNode(NULL)
	{
		RegisterEvents();
	}
	Component::Component(xml_node<char>& xNode, ComponentContainer* pxParent)
		: m_xTUID(*this)
		, m_pxParent(pxParent)
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
				return;
			}
		}
		bStringEnd = xToken.FromToken('.', szPath);
		if (bStringEnd)
		{
			// this should be an event
			pxTarget->OnEvent(xToken, xEventParameters);
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
				return xData.AsComponent()->OnEventByPath(szPath, xEventParameters);
			}
		}
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
		return NULL;
	}
	Component* Component::GetParentByName(const Hash& xName)
	{
		return NULL;
	}
	
	void Component::RegisterEvents()
	{
		RegisterEvent(Hash("OnCreate"), boost::bind( &root_t::OnCreate, this, _1 ) );
		RegisterEvent(Hash("OnActivate"), boost::bind( &root_t::OnActivate, this, _1 ) );
		RegisterEvent(Hash("OnDeactivate"), boost::bind( &root_t::OnDeactivate, this, _1 ) );
		RegisterEvent(Hash("OnDestroy"), boost::bind( &root_t::OnDestroy, this, _1 ) );
	}

	void Component::ProcessName( xml_attribute<char>& xName )
	{
		m_xName = Hash( xName.value() );
	}
	void Component::ProcessOnCreate( xml_node<char>& xEvent )
	{
		Action* pxAction = Action::Create(xEvent);
		if(pxAction)
		{
			RegisterEventAction(Hash("OnCreate"), pxAction);
		}
	}
	void Component::ProcessOnActivate( xml_node<char>& xEvent )
	{
		Action* pxAction = Action::Create(xEvent);
		if(pxAction)
		{
			RegisterEventAction(Hash("OnActivate"), pxAction);
		}
	}
	void Component::ProcessOnDeactivate( xml_node<char>& xEvent )
	{
		Action* pxAction = Action::Create(xEvent);
		if(pxAction)
		{
			RegisterEventAction(Hash("OnDeactivate"), pxAction);
		}
	}
	void Component::ProcessOnDestroy( xml_node<char>& xEvent )
	{
		Action* pxAction = Action::Create(xEvent);
		if(pxAction)
		{
			RegisterEventAction(Hash("OnDestroy"), pxAction);
		}
	}

	/////////////////////////////////////////////////////////////////////////
	//	ComponentContainer

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
		Component* pxRootObject = Component::Create(xComponentNode, this);
		if (pxRootObject)
		{
			m_xComponents.insert(pxRootObject);
		}
	}


};