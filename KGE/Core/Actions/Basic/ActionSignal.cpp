#include "KGE.hpp"
#include "Core/Actions/Basic/ActionSignal.hpp"

#include "Core/Components/Component.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(ActionSignal)

	ActionSignal::ActionSignal()
		: parent_t()
	{
	}
	ActionSignal::ActionSignal(xml_node<char>& xNode)
		: parent_t(xNode)
	{
	}
	ActionSignal::~ActionSignal()
	{
	}

	void ActionSignal::Activate( Component* pxSource, eventparams_t& xParams )
	{
		Component* pxTarget = pxSource->GetComponentByPath(m_szTargetPath);
		if(pxTarget)
		{
			pxTarget->OnEvent(m_xTargetEvent, m_xParameters);
		}
	}

	void ActionSignal::ProcessTarget( xml_attribute<char>& xTarget )
	{
		m_szTargetPath = xTarget.value();
	}
	void ActionSignal::ProcessEvent( xml_attribute<char>& xEvent )
	{
		m_xTargetEvent = Hash( xEvent.value() );
	}
	void ActionSignal::ProcessParameter( xml_node<char>& xParameter )
	{
		const char* szName = XMLHelpers::GetAttributeValue(xParameter, "name");
		string szValue = XMLHelpers::GetAttributeValue(xParameter, "value");
		m_xParameters.insert( eventparamspair_t( Hash(szName), Data( szValue ) ) );
	}
};
