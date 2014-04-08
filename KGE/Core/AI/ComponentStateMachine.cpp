#include "KGE.hpp"
#include "Core/AI/ComponentStateMachine.hpp"

#include "Core/AI/ComponentState.hpp"

namespace KGE
{
	void ComponentStateMachine::OnActivate(eventparams_t& xEventParameters)
	{
		parent_t::OnActivate(xEventParameters);
		// activate initial state
		SetState(m_xInitialState);
	}
	void ComponentStateMachine::OnDeactivate(eventparams_t& xEventParameters)
	{
		parent_t::OnDeactivate(xEventParameters);
		// deactivate and destroy state
		if (m_pxCurrentState)
		{
			m_pxCurrentState->OnDeactivate(xEventParameters);
			m_pxCurrentState->OnDestroy(xEventParameters);
			m_pxCurrentState = NULL;
		}
	}
	void ComponentStateMachine::OnDestroy(eventparams_t& xEventParameters)
	{
		parent_t::OnDestroy(xEventParameters);
		// destroy state, if it exists
	}
	void ComponentStateMachine::OnChangeState(eventparams_t& xEventParameters)
	{
		eventparams_t::iterator xIt = xEventParameters.find(Hash("state"));
		if (xIt != xEventParameters.end() && xIt->second.AsHash())
		{
			SetState( *xIt->second.AsHash() );
		}
	}

	void ComponentStateMachine::SetState(const Hash& xStateHash)
	{
		eventparams_t xEventParameters;
		if (m_pxCurrentState)
		{
			m_pxCurrentState->OnDeactivate(xEventParameters);
			m_pxCurrentState->OnDestroy(xEventParameters);
		}

		unordered_map< Hash, xml_node<char>*, Hash::Hasher >::iterator xIt = m_xStates.find(m_xInitialState);
		if (xIt != m_xStates.end())
		{
			m_pxCurrentState = ComponentState::Create(*xIt->second, m_xTUID.GetCachedReference());
			m_pxCurrentState->OnActivate(xEventParameters);
		}
	}

	void ComponentStateMachine::RegisterEvents()
	{
		RegisterEvent(Hash("OnChangeState"), boost::bind(&this_t::OnChangeState, this, _1));
	}

	void ComponentStateMachine::PopulateInitialState(xml_attribute<char>& xInitialState)
	{
		m_xInitialState = Hash(xInitialState.value());
	}
	void ComponentStateMachine::PopulateState(xml_node<char>& xStateNode)
	{
		const char* szName = XMLHelpers::GetAttributeValue(xStateNode, "Name");
		if (szName)
		{
			m_xStates.insert(pair<Hash, xml_node<char>*>(Hash(szName), &xStateNode));
		}
	}
};