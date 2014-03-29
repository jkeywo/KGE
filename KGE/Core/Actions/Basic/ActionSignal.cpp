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

	void ActionSignal::Activate(eventparams_t& xParams)
	{
		eventparams_t::iterator xIt = xParams.find(g_xHASH_SOURCE);
		if (xIt != xParams.end() && xIt->second.AsComponent())
		{
			xIt->second.AsComponent()->OnEventByPath(m_szEventPath, m_xParameters);
		}
	}

	void ActionSignal::ProcessEvent(xml_attribute<char>& xEvent)
	{
		m_szEventPath = xEvent.value();
	}
	void ActionSignal::ProcessParameter(xml_node<char>& xParameter)
	{
		const char* szName = XMLHelpers::GetAttributeValue(xParameter, "name");
		string szValue = XMLHelpers::GetAttributeValue(xParameter, "value");
		m_xParameters.insert( eventparamspair_t( Hash(szName), Data( szValue ) ) );
	}
};
