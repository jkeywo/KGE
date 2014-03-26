#pragma once

#include "Core/Data/Data.hpp"
#include "Core/Data/Hash.hpp"

namespace KGE
{
	class Property
	{
	public:
		struct Hasher
		{
			size_t operator()(const Property* pxProperty) const { return pxProperty->m_xHash.GetHash(); }
		};

		Property(const Hash& xHash)
			: m_xHash(xHash)
		{
		}
		virtual ~Property()
		{
		}
		virtual Data GetData() const = 0;
		virtual void SetData(Data xData) = 0;
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
	};

	// Property Data Value
	class PropertyDataByValue : public Property
	{
		typedef Property parent_t;
	public:
		PropertyDataByValue(const Hash& xHash, const Data& xInitialData)
			: parent_t(xHash)
			, m_xData(xInitialData)
		{
		}
		virtual ~PropertyDataByValue()
		{
		}
		virtual Data GetData() const { return m_xData; }
		virtual void SetData(Data xData) { m_xData = xData; }
	protected:
		Data m_xData;
	};
	// Property Data Reference
	class PropertyDataByReference : public Property
	{
		typedef Property parent_t;
	public:
		PropertyDataByReference(const Hash& xHash, Data& xInitialData)
			: parent_t(xHash)
			, m_xData(xInitialData)
		{
		}
		virtual ~PropertyDataByReference()
		{
		}
		virtual Data GetData() const { return m_xData; }
		virtual void SetData(Data xData) { m_xData = xData; }
	protected:
		Data& m_xData;
	};
	// Property Data Callback
	class PropertyDataByCallback : public Property
	{
		typedef Property parent_t;
	public:
		PropertyDataByCallback(const Hash& xHash, std::function<Data()>& xGet, std::function<void(Data)>& xSet )
			: parent_t(xHash)
			, m_xGet(xGet)
			, m_xSet(xSet)
		{
		}
		virtual ~PropertyDataByCallback()
		{
		}
		virtual Data GetData() const { return m_xGet(); }
		virtual void SetData(Data xData) { m_xSet(xData); }
	protected:
		std::function<Data()>& m_xGet;
		std::function<void(Data)>& m_xSet;
	};
	// Property Typed Value
	template< typename type_t >
	class PropertyTypedByValue : public Property
	{
		typedef Property parent_t;
	public:
		PropertyTypedByValue(const Hash& xHash, type_t xInitialData)
			: parent_t(xHash)
			, m_xData(xInitialData)
		{
		}
		virtual ~PropertyTypedByValue()
		{
		}
		virtual Data GetData() const { return Data(m_xData); }
		virtual void SetData(Data xData) { type_t* pxData = xData.AsType<type_t>(); if(pxData) m_xData = *pxData; }
	protected:
		type_t m_xData;
	};
	// Property Typed Reference
	template< typename type_t >
	class PropertyTypedByReference : public Property
	{
		typedef Property parent_t;
	public:
		PropertyTypedByReference(const Hash& xHash, type_t xInitialData)
			: parent_t(xHash)
			, m_xData(xInitialData)
		{
		}
		virtual ~PropertyTypedByReference()
		{
		}
		virtual Data GetData() const { return Data(m_xData); }
		virtual void SetData(Data xData) { type_t* pxData = xData.AsType<type_t>(); if(pxData) m_xData = *pxData; }
	protected:
		type_t& m_xData;
	};
	// Property Typed Callback
	template< typename type_t >
	class PropertyTypedByCallback : public Property
	{
		typedef Property parent_t;
	public:
		PropertyTypedByCallback(const Hash& xHash, std::function<type_t()>& xGet, std::function<void(type_t)>& xSet )
			: parent_t(xHash)
			, m_xGet(xGet)
			, m_xSet(xSet)
		{
		}
		virtual ~PropertyTypedByCallback()
		{
		}
		virtual Data GetData() const { return Data( m_xGet() ); }
		virtual void SetData(Data xData) { type_t* pxData = xData.AsType<type_t>(); if( pxData ) m_xSet(*pxData); }
	protected:
		std::function<type_t()>& m_xGet;
		std::function<void(type_t)>& m_xSet;
	};

#define CREATE_PROPERTYCLASS_FOR_TYPE( TYPE_TITLE, TYPE_NAME )							\
	class Property##TYPE_TITLE##ByValue : public PropertyTypedByValue<TYPE_NAME>		\
	{																					\
		typedef PropertyTypedByValue<TYPE_NAME> parent_t;								\
	public:																				\
		Property##TYPE_TITLE##ByValue(const Hash& xHash, TYPE_NAME xInitialData)		\
		: parent_t(xHash, xInitialData)	{ }												\
		virtual ~Property##TYPE_TITLE##ByValue() { }									\
	};																					\
	class Property##TYPE_TITLE##ByReference : public PropertyTypedByReference<TYPE_NAME>\
	{																					\
		typedef PropertyTypedByReference<TYPE_NAME> parent_t;							\
	public:																				\
		Property##TYPE_TITLE##ByReference(const Hash& xHash, TYPE_NAME xInitialData)	\
		: parent_t(xHash, xInitialData)	{ }												\
		virtual ~Property##TYPE_TITLE##ByReference() { }								\
	};																					\
	class Property##TYPE_TITLE##ByCallback : public PropertyTypedByCallback<TYPE_NAME>	\
	{																					\
		typedef PropertyTypedByCallback<TYPE_NAME> parent_t;							\
	public:																				\
		Property##TYPE_TITLE##ByCallback(const Hash& xHash, std::function<TYPE_NAME()>& xGet, std::function<void(TYPE_NAME)>& xSet)	\
		: parent_t(xHash, xGet, xSet)	{ }												\
		virtual ~Property##TYPE_TITLE##ByCallback() { }									\
	};

	CREATE_PROPERTYCLASS_FOR_TYPE(Bool, bool)
	CREATE_PROPERTYCLASS_FOR_TYPE(Int, int)
	CREATE_PROPERTYCLASS_FOR_TYPE(UInt, u_int)
	CREATE_PROPERTYCLASS_FOR_TYPE(Float, float)
	CREATE_PROPERTYCLASS_FOR_TYPE(String, string)

#undef CREATE_PROPERTYCLASS_FOR_TYPE

};