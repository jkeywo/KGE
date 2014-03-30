#pragma once

#include "Core/ClassCapabilities/MetaClass.hpp"
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
		METACLASS_ROOTDATA(Action)
		#define SUPPORT_XML
		#define SUPPORT_CLASSFACTORY_0ARG
		#define SUPPORT_CLASSFACTORY_XML_0ARG
		#include "Core/ClassCapabilities/MetaClass_IncludeRoot.hpp"
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