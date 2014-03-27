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

	Component* Component::GetComponentByPath(const string& xPath)
	{
		return NULL;
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

};