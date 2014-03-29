#pragma once


#include "Core/ClassCapabilities/ClassFactory.hpp"
#include "Core/ClassCapabilities/XMLParser.hpp"
#include "Core/Data/CommonHashes.hpp"

namespace KGE
{
	class Component;
	typedef unordered_map<Hash, Data, Hash::Hasher> eventparams_t;
	typedef pair<Hash, Data> eventparamspair_t;

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
		struct Comparer
		{
			bool operator()(const Action* pxLHS, const Action* pxRHS) const { return pxLHS->GetPriority() < pxRHS->GetPriority(); }
		};

		Action()
			: m_fPriority(0.0f)
			, m_xTUID(*this)
		{
		}
		Action(xml_node<char>& xNode)
			: m_fPriority(0.0f)
			, m_xTUID(*this)
		{
		}
		virtual ~Action()
		{
		}

		virtual void Activate(eventparams_t& xParams) = 0;

		virtual void SetPriority(float fPriority) { m_fPriority = fPriority; }
		virtual float GetPriority() const { return m_fPriority; }

	protected:
		void ProcessPriority(xml_attribute<char>& xPriority)
		{
			stringstream xIn(xPriority.value());
			xIn >> m_fPriority;
		}
		float m_fPriority;
	};
};