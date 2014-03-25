#pragma once

#include "Core/Data/Data.hpp"
#include "Core/Data/Hash.hpp"

namespace KGE
{
	class Property
	{
	public:
		struct Compare
		{
			bool operator() (const Property* x, const Property* y) const { return x->m_xHash < y->m_xHash; }
		};

		Property(const Hash& xHash)
			: m_xHash(xHash)
		{
		}
		virtual ~Property()
		{
		}
		virtual Data GetData() = 0;
		virtual void SetData(Data xData) = 0;
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
	};


};