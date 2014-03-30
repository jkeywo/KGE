#pragma once
#include "Core/Actions/Action.hpp"

namespace KGE
{
	class ActionSignal : public Action
	{
		METACLASS_CHILDDATA(ActionSignal, Action, "Signal")
		#include "Core/Actions/Action_Include.hpp"

		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE( "Event", ProcessEvent );
			XMLPARSER_REGISTERCHILDNODE( "Parameter", ProcessParameter );
		}
		STATIC_INITIALISE_END

	public:
		ActionSignal();
		ActionSignal(xml_node<char>& xNode);
		virtual ~ActionSignal();

		virtual void Activate(eventparams_t& xParams);

	protected:
		virtual void ProcessEvent( xml_attribute<char>& xEvent );
		virtual void ProcessParameter( xml_node<char>& xPriority );

		const char* m_szEventPath;
		eventparams_t m_xParameters;
	};

};