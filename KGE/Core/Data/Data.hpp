#pragma once

namespace KGE
{
	class Component;
	class Hash;

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
			COMPONENT,
			HASH,
			// VEC2,
		};
		Data() : m_eType(UNSET) {}
		Data(bool bValue) : m_eType(BOOL) { m_xProperty.b = bValue; }
		Data(int iValue) : m_eType(INT) { m_xProperty.i = iValue; }
		Data(u_int uValue) : m_eType(UINT) { m_xProperty.u = uValue; }
		Data(float fValue) : m_eType(FLOAT) { m_xProperty.f = fValue; }
		Data(const string& szValue) : m_eType(STRING) { m_xPropertyS = szValue; }
		Data(Component* pxValue) : m_eType(COMPONENT) { m_xProperty.c = pxValue; }
		Data(const Hash& xValue) : m_eType(HASH) { m_xPropertyH = xValue; }
		Data(const Data& xCopy) : m_eType(xCopy.m_eType) { m_xProperty = xCopy.m_xProperty; }
		virtual ~Data() {}

		virtual bool* AsBool();
		virtual int* AsInt();
		virtual u_int* AsUInt();
		virtual float* AsFloat();
		virtual string* AsString();
		virtual Component* AsComponent();
		virtual Hash* AsHash();
		template<typename type_t> type_t* AsType() { return NULL; }
		template<> bool* AsType<bool>() { return AsBool(); }
		template<> int* AsType<int>() { return AsInt(); }
		template<> u_int* AsType<u_int>() { return AsUInt(); }
		template<> float* AsType<float>() { return AsFloat(); }
		template<> string* AsType<string>() { return AsString(); }
		template<> Component* AsType<Component>() { return AsComponent(); }
		template<> Hash* AsType<Hash>() { return AsHash(); }
		virtual DATA_TYPES GetType() const			{ return m_eType; }

		bool operator!=(const Data& xRHS) const;
		bool operator==(const Data& xRHS) const;

	protected:
		union
		{
			bool b;
			int i;
			u_int u;
			float f;
			Component* c;
		} m_xProperty;
		string m_xPropertyS;
		Hash m_xPropertyH;
		DATA_TYPES m_eType;
	};
};