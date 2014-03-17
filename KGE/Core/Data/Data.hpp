#pragma once

namespace KGE
{
	class Data
	{
	public:
		enum DATA_TYPES
		{
			UNSET = 0,
			BOOL,
			INT,
			UINT,
			FLOAT,
			STRING,
			// COMPONENT,
			// HASH,
			// VEC2,
		};
		Data() : m_eType(UNSET) {}
		Data(bool bValue) : m_eType(BOOL) { m_xProperty.b = bValue; }
		Data(int iValue) : m_eType(INT) { m_xProperty.i = iValue; }
		Data(float fValue) : m_eType(FLOAT) { m_xProperty.f = fValue; }
		Data(const string& szValue) : m_eType(STRING) { m_xPropertyS = szValue; }
		Data(const Data& xCopy) : m_eType(xCopy.m_eType) { m_xProperty = xCopy.m_xProperty; }
		virtual ~Data() {}

		virtual bool* AsBool();
		virtual int* AsInt();
		virtual unsigned int* AsUInt();
		virtual float* AsFloat();
		virtual string* AsString();
		virtual DATA_TYPES GetType() const			{ return m_eType; }

		bool operator!=(const Data& xRHS) const;
		bool operator==(const Data& xRHS) const;

	protected:
		union
		{
			bool b;
			int i;
			unsigned int u;
			float f;
		} m_xProperty;
		string m_xPropertyS;
		DATA_TYPES m_eType;
	};
};