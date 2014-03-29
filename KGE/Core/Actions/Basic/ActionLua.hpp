#pragma once
#include "Core/Actions/Action.hpp"

namespace KGE
{
	class ActionLua : public Action
	{
		#define THIS_T ActionLua
		#define PARENT_T Action
		#define HASHSTRING_T "Lua"
		#include "Core/Actions/Action_Include.hpp"

	public:
		ActionLua();
		ActionLua(xml_node<char>& xNode);
		virtual ~ActionLua();

		virtual void Activate(eventparams_t& xParams)
		{
		}

	protected:
		string m_szLuaCode;
	};
};