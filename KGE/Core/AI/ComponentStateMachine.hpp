#pragma once

#include "Core/Components/ComponentComposite.hpp"

namespace KGE
{
	class ComponentState;

	class ComponentStateMachine : public ComponentComposite
	{
		METACLASS_CHILDDATA(ComponentStateMachine, ComponentComposite, "StateMachine")
		#include "Core/Components/Component_Include.ext"
		STATIC_INITIALISE_START
		{
			CLASSFACTORY_REGISTER_1ARG(TUID<KGE::Component>::CachedReference);
			CLASSFACTORY_REGISTERXML_1ARG(TUID<KGE::Component>::CachedReference);
			XMLPARSER_REGISTERATTRIBUTE("Initial", PopulateInitialState);
			XMLPARSER_REGISTERCHILDNODE("State", PopulateState);
		}
		STATIC_INITIALISE_END

	public:
		ComponentStateMachine(TUID<Component>::CachedReference xParent)
			: parent_t(xParent)
			, m_xInitialState()
			, m_pxCurrentState(NULL)
		{
			RegisterEvents();
		}
		ComponentStateMachine(xml_node<char>& xNode, TUID<Component>::CachedReference xParent)
			: parent_t(xNode, xParent)
			, m_xInitialState()
			, m_pxCurrentState(NULL)
		{
			RegisterEvents();
		}
		virtual ~ComponentStateMachine()
		{
		}

		virtual void OnActivate(eventparams_t& xEventParameters);
		virtual void OnDeactivate(eventparams_t& xEventParameters);
		virtual void OnDestroy(eventparams_t& xEventParameters);
		virtual void OnChangeState(eventparams_t& xEventParameters);

		virtual void SetState( const Hash& xStateHash );

	protected:
		void RegisterEvents();

		virtual void PopulateInitialState(xml_attribute<char>& xInitialState);
		virtual void PopulateState(xml_node<char>& xState);

		Hash m_xInitialState;
		ComponentState* m_pxCurrentState;
		unordered_map< Hash, xml_node<char>*, Hash::Hasher > m_xStates;
	};
};