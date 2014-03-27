#pragma once


#include "Core/ClassCapabilities/ClassFactory.hpp"
#include "Core/ClassCapabilities/Events.hpp"
#include "Core/ClassCapabilities/XMLParser.hpp"

namespace KGE
{
	class Component;

	class Action
	{
		#define THIS_T Action
		#include "Core/ClassCapabilities/MetaClass_IncludeRoot.hpp"
		CAPABILITYROOT_CLASSFACTORY_ADD
		CAPABILITYROOT_CLASSFACTORY_ADDXML
		CAPABILITYROOT_PROCESSXML

		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE( "Priority", ProcessPriority );
		}
		STATIC_INITIALISE_END

	public:
		Action();
		Action(xml_node<char>& xNode);
		virtual ~Action();

		virtual void Activate( Component* pxSource, eventparams_t& xParams ) = 0;

		virtual void SetPriority(float fPriority) { m_fPriority = fPriority; }
		virtual float GetPriority() const { return m_fPriority; }

	protected:
		virtual void ProcessPriority( xml_attribute<char>& xPriority );

		float m_fPriority;
	};
};