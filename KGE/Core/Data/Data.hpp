#pragma once

#include "Core/Maths/Vec2f.hpp"

namespace KGE
{
	class Component;
	class Hash;

	/// 
	/// KGE::Data
	/// This wrapper class designed to store any type of data. To find the data types supported, please see the KGE::Data::DATA_TYPES enum values.
	/// An instance of this class can only store one type of data, thus retrieving an int as a bool is NOT supported. the getters of this class
	/// always return a pointer to the data, and if the requested type does not match the type of the stored data, NULL is returned.
	///
	class Data
	{
	public:
		/// Data types that the class supports.
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
			VEC2F,
			RENDERTARGET,
			WINDOW,
			EVENT,
		};

		Data() : m_eType(UNSET) {}
		Data(bool bValue) : m_eType(BOOL) { m_xProperty.b = bValue; }
		Data(int iValue) : m_eType(INT) { m_xProperty.i = iValue; }
		Data(u_int uValue) : m_eType(UINT) { m_xProperty.u = uValue; }
		Data(float fValue) : m_eType(FLOAT) { m_xProperty.f = fValue; }
		Data(const string& szValue) : m_eType(STRING) { m_xPropertyS = szValue; }
		Data(Component* pxValue) : m_eType(COMPONENT) { m_xProperty.c = pxValue; }
		Data(const Hash& xValue) : m_eType(HASH) { m_xPropertyH = xValue; }
		Data(const Vec2f& xValue) : m_eType(VEC2F) { m_xPropertyV = xValue; }
		Data(sf::RenderTarget* pxValue) : m_eType(RENDERTARGET) { m_xProperty.rt = pxValue; }
		Data(sf::Window* pxValue) : m_eType(WINDOW) { m_xProperty.w = pxValue; }
		Data(sf::Event* pxValue) : m_eType(EVENT) { m_xProperty.e = pxValue; }
		Data(const Data& xCopy) : m_eType(xCopy.m_eType) { m_xProperty = xCopy.m_xProperty; }
		virtual ~Data() {}

		virtual bool* AsBool();
		virtual int* AsInt();
		virtual u_int* AsUInt();
		virtual float* AsFloat();
		virtual string* AsString();
		virtual Component* AsComponent();
		virtual Hash* AsHash();
		virtual Vec2f* AsVec2f();
		virtual sf::RenderTarget* AsRenderTarget();
		virtual sf::Window* AsWindow();
		virtual sf::Event* AsEvent();
		template<typename type_t> type_t* AsType() { return NULL; }
		template<> bool* AsType<bool>() { return AsBool(); }
		template<> int* AsType<int>() { return AsInt(); }
		template<> u_int* AsType<u_int>() { return AsUInt(); }
		template<> float* AsType<float>() { return AsFloat(); }
		template<> string* AsType<string>() { return AsString(); }
		template<> Component* AsType<Component>() { return AsComponent(); }
		template<> Hash* AsType<Hash>() { return AsHash(); }
		template<> Vec2f* AsType<Vec2f>() { return AsVec2f(); }
		template<> sf::RenderTarget* AsType<sf::RenderTarget>() { return AsRenderTarget(); }
		template<> sf::Window* AsType<sf::Window>() { return AsWindow(); }
		template<> sf::Event* AsType<sf::Event>() { return AsEvent(); }
		virtual DATA_TYPES GetType() const			{ return m_eType; }

		/// Overloaded inequality operator: implemented in terms of the equality operator.
		bool operator!=(const Data& xRHS) const;
		/// Overloaded equality operator: returns false if both Data instances store different types or
		// if one is of UNSET type.
		bool operator==(const Data& xRHS) const;

	protected:
		union
		{
			bool b;
			int i;
			u_int u;
			float f;
			Component* c;
			sf::RenderTarget* rt;
			sf::Window* w;
			sf::Event* e;
		} m_xProperty;
		// ** todo ** refactor these to be dynamically allocated and stored within the union **
		string m_xPropertyS;
		Hash m_xPropertyH;
		Vec2f m_xPropertyV;
		// ** ** **
		DATA_TYPES m_eType;
	};
};