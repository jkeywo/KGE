#pragma once

#include "Core/ClassCapabilities/MetaClass.hpp"
#include "Core/ClassCapabilities/XMLParser.hpp"

#include "Core/Data/CommonHashes.hpp"

namespace KGE
{
	typedef unordered_map<Hash, Data, Hash::Hasher> eventparams_t;
	typedef pair<Hash, Data> eventparamspair_t;

	template<class owner_t>
	class Event;

	template<class owner_t>
	class EventSignal
	{
		METACLASS_ROOTDATA(EventSignal<owner_t>)
		#include "Core/ClassCapabilities/XMLParser_IncludeRoot.ext"
		STATIC_INITIALISE_START
		{
			XMLPARSER_REGISTERATTRIBUTE("Trigger",	ProcessTrigger);
			XMLPARSER_REGISTERATTRIBUTE("Target",	ProcessTarget);
			XMLPARSER_REGISTERCHILDNODE("Parameter", ProcessParameter);
			XMLPARSER_REGISTERATTRIBUTE("Priority", ProcessPriority);
		}
		STATIC_INITIALISE_END

	public:
		struct Comparer
		{
			bool operator()(const EventSignal* pxLHS, const EventSignal* pxRHS) const { return pxLHS->GetPriority() < pxRHS->GetPriority(); }
		};

		
		EventSignal(owner_t& xOwner)
			: m_xOwner(xOwner)
			, m_szTriggerPath(NULL)
			, m_szTargetPath(NULL)
		{
		}
		EventSignal(xml_node<char>& xNode, owner_t& xOwner)
			: m_xOwner(xOwner)
			, m_szTriggerPath(NULL)
			, m_szTargetPath(NULL)
		{
		}
		~EventSignal()
		{
		}

		void Activate()
		{
			m_pxTriggerEvent = m_xOwner.GetEventByPath(m_szTargetPath);
			m_pxTriggerEvent->RegisterSignal(this);
			m_pxTargetEvent = m_xOwner.GetEventByPath(m_szTargetPath);
		}
		void Deactivate()
		{
			m_pxTriggerEvent->UnregisterSignal(this);
			m_pxTriggerEvent = NULL;
			m_pxTargetEvent = NULL;
		}

		void Execute(eventparams_t& xParams)
		{
			if (m_pxTargetEvent)
			{
				m_pxTargetEvent->Execute(m_xParameters);
			}
		}


		void SetPriority(float fPriority) { m_fPriority = fPriority; }
		float GetPriority() const { return m_fPriority; }

	protected:
		void ProcessTrigger(xml_attribute<char>& xEvent)
		{
			m_szTriggerPath = xEvent.value();
		}
		void ProcessTarget(xml_attribute<char>& xEvent)
		{
			m_szTargetPath = xEvent.value();
		}
		void ProcessParameter(xml_node<char>& xParameter)
		{
			const char* szName = XMLHelpers::GetAttributeValue(xParameter, "name");
			string szValue = XMLHelpers::GetAttributeValue(xParameter, "value");
			m_xParameters.insert(eventparamspair_t(Hash(szName), Data(szValue)));
		}
		void ProcessPriority(xml_attribute<char>& xPriority)
		{
			stringstream xIn(xPriority.value());
			xIn >> m_fPriority;
		}

		owner_t& m_xOwner;
		float m_fPriority;
		const char* m_szTriggerPath;
		Event<owner_t>* m_pxTriggerEvent;
		const char* m_szTargetPath;
		Event<owner_t>* m_pxTargetEvent;
		eventparams_t m_xParameters;
	};

	template<class owner_t>	typename STATIC_INITIALISE_RUN(EventSignal<owner_t>)

};