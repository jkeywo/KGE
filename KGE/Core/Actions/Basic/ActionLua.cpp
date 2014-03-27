#include "KGE.hpp"
#include "Core/Actions/Basic/ActionLua.hpp"

namespace KGE
{

	ActionLua::ActionLua()
		: parent_t()
	{
	}
	ActionLua::ActionLua(xml_node<char>& xNode)
		: parent_t(xNode)
	{
		m_szLuaCode = xNode.value();
	}
	ActionLua::~ActionLua()
	{
	}

	void ActionLua::Activate( Component* pxSource, eventparams_t& xParams )
	{
		//m_szLuaCode;
	}
};
