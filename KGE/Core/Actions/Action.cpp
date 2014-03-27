#include "KGE.hpp"
#include "Core/Actions/Action.hpp"

namespace KGE
{
	STATIC_INITIALISE_RUN(Action)

	Action::Action()
		: m_fPriority(0.0f)
		, m_xTUID(*this)
	{
	}
	Action::Action(xml_node<char>& xNode)
		: m_fPriority(0.0f)
		, m_xTUID(*this)
	{
	}
	Action::~Action()
	{	
	}

	void Action::ProcessPriority( xml_attribute<char>& xPriority )
	{
		stringstream xIn( xPriority.value() );
		xIn >> m_fPriority;
	}
};