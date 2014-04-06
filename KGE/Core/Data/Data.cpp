#include "KGE.hpp"
#include "Core/Data/Data.hpp"

namespace KGE
{
	bool* Data::AsBool()
	{
		return m_eType == BOOL ? &m_xProperty.b : NULL;
	}
	int* Data::AsInt()
	{
		return m_eType == INT ? &m_xProperty.i : NULL;
	}
	unsigned int* Data::AsUInt()
	{
		return m_eType == UINT ? &m_xProperty.u : NULL;
	}
	float* Data::AsFloat()
	{
		return m_eType == FLOAT ? &m_xProperty.f : NULL;
	}
	string* Data::AsString()
	{
		return m_eType == STRING ? &m_xPropertyS : NULL;
	}
	Component* Data::AsComponent()
	{
		return m_eType == COMPONENT ? m_xProperty.c : NULL;
	}
	Hash* Data::AsHash()
	{
		return m_eType == HASH ? &m_xPropertyH : NULL;
	}
	Vec2f* Data::AsVec2f()
	{
		return m_eType == VEC2F ? &m_xPropertyV : NULL;
	}
	sf::RenderTarget* Data::AsRenderTarget()
	{
		return m_eType == RENDERTARGET ? m_xProperty.rt : NULL;
	}
	sf::Window* Data::AsWindow()
	{
		return m_eType == WINDOW ? m_xProperty.w : NULL;
	}
	sf::Event* Data::AsEvent()
	{
		return m_eType == EVENT ? m_xProperty.e : NULL;
	}

	bool Data::operator!=(const Data& xRHS) const
	{
		return !operator==(xRHS);
	}
	bool Data::operator==(const Data& xRHS) const
	{
		if (m_eType != xRHS.m_eType)
		{
			return false;
		}
		switch (m_eType)
		{
		case UNSET:			return false;
		case BOOL:			return m_xProperty.b == xRHS.m_xProperty.b;
		case INT:			return m_xProperty.i == xRHS.m_xProperty.i;
		case UINT:			return m_xProperty.u == xRHS.m_xProperty.u;
		case FLOAT:			return m_xProperty.f == xRHS.m_xProperty.f;
		case STRING:		return m_xPropertyS == xRHS.m_xPropertyS;
		case COMPONENT:		return m_xProperty.c == xRHS.m_xProperty.c;
		case HASH:			return m_xPropertyH == xRHS.m_xPropertyH;
		case VEC2F:			return m_xPropertyV == xRHS.m_xPropertyV;
		case RENDERTARGET:	return m_xProperty.rt == xRHS.m_xProperty.rt;
		case WINDOW:		return m_xProperty.w == xRHS.m_xProperty.w;
		case EVENT:			return m_xProperty.e == xRHS.m_xProperty.e;
		}
		return false;
	}


};