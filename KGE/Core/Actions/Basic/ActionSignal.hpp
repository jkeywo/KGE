#pragma once
#include "Core/Actions/Action.hpp"

namespace KGE
{
	class ActionSignal : public Action
	{
		#define THIS_T ActionSignal
		#define PARENT_T Action
		#define HASHSTRING_T "Signal"
		#include "Core/ClassCapabilities/MetaClass_Include.hpp"
		CAPABILITY_CLASSFACTORY_ADD
		CAPABILITY_CLASSFACTORY_ADDXML
		CAPABILITY_PROCESSXML

		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE( "Target", ProcessTarget );
			XMLPARSER_REGISTERATTRIBUTE( "Event", ProcessEvent );
			XMLPARSER_REGISTERCHILDNODE( "Parameter", ProcessParameter );
		}
		STATIC_INITIALISE_END

	public:
		ActionSignal();
		ActionSignal(xml_node<char>& xNode);
		virtual ~ActionSignal();

		virtual void Activate( Component* pxSource, eventparams_t& xParams );

	protected:
		virtual void ProcessTarget( xml_attribute<char>& xTarget );
		virtual void ProcessEvent( xml_attribute<char>& xEvent );
		virtual void ProcessParameter( xml_node<char>& xPriority );

		string m_szTargetPath;
		Hash m_xTargetEvent;
		eventparams_t m_xParameters;
	};
};