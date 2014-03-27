#pragma once
#include "Core/Actions/Action.hpp"

namespace KGE
{
	class ActionLua : public Action
	{
		#define THIS_T ActionLua
		#define PARENT_T Action
		#define HASHSTRING_T "Lua"
		#include "Core/ClassCapabilities/MetaClass_Include.hpp"
		CAPABILITY_CLASSFACTORY_ADD
		CAPABILITY_CLASSFACTORY_ADDXML
		CAPABILITY_PROCESSXML

	public:
		ActionLua();
		ActionLua(xml_node<char>& xNode);
		virtual ~ActionLua();

		virtual void Activate( Component* pxSource, eventparams_t& xParams );

	protected:
		string m_szLuaCode;
	};
};