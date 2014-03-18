#pragma once

namespace KGE
{
	template< typename TObject >
	class GUID
	{
	public:
		static const unsigned int UNSET = 0;

		///////////////////////////////////////////////////////////////////////////
		// Static system for GUID management and lists
	public:
		static void SetRange( unsigned int uMin, unsigned int uMax )
		{
			GetManager().MinGuid = uMin;
			GetManager().MaxGuid = uMax;
			GetManager().CheckRange();
		}
		static void ResetNext()
		{
			GetManager().NextGUID = GetManager().MinGuid;
		}
		static TObject* GetObjectByGUID(const GUID& uGuid)
		{
			return GetManager().GuidReferences[uGuid];
		}
		static const GUID& RegisterObject( TObject& xObject )
		{
			Manager& xInstance = GetManager();
			while( xInstance.GuidReferences.find( xInstance.NextGUID ) != xInstance.GuidReferences.end() )
			{
				xInstance.NextGUID++;
			}
			GUID xGUID( xInstance.NextGUID++ );
			xInstance.GuidReferences[xGUID.m_uGuid] = &xObject;
			return reinterpret_cast<const GUID&>(xInstance.GuidReferences.find( xGUID.m_uGuid )->first);
		}
		static void UnregisterObject(const GUID& xGUID)
		{
			std::map<GUID, TObject*>::iterator xIt = xInstance.GuidReferences.find( xGUID.m_uGuid );
			if(xIt != xInstance.GuidReferences.end())
			{
				GetManager().GuidReferences.erase(xIt);
			}
		}
		static void UnregisterObject(TObject& xObject)
		{
			foreach( xIt, GetManager().GuidReferences )
			{
				if( xIt.GetData() == &xObject )
				{
					GetManager().GuidReferences.erase( xIt );
					return;
				}
			}
		}	
	protected:
		static std::map<u_int, TObject*>& GetList()
		{
			return GetManager().GuidReferences;
		}
		static TObject* GetObjectByUInt(u_int uGUIDValue)
		{
			return GetManager().GuidReferences[uGUIDValue];
		}
		struct Manager
		{
			Manager() : GuidReferences(), NextGUID(UNSET+1), MinGuid(UNSET+1), MaxGuid(UINT_MAX) {}

			void CheckRange()
			{
				if( NextGUID < MinGuid || NextGUID > MaxGuid )
				{
					NextGUID = MinGuid;
				}
			}
			std::map<u_int, TObject*> GuidReferences;
			u_int NextGUID;
			u_int MinGuid;
			u_int MaxGuid;
		};
		static Manager& GetManager()	{ static Manager xInstance; return(xInstance); }

		///////////////////////////////////////////////////////////////////////////
		// Stores a GUI and a cache of the object it points to
		// Useful for moving GUIDs around a network or saving them between sessions
	public:
		class CachedReference
		{
		public:
			CachedReference() : m_uTargetGUID( UNSET ), m_pxTargetObject( NULL ) {}
			CachedReference( const GUID& xTarget ) : m_uTargetGUID(xTarget.m_uGuid), m_pxTargetObject( NULL ) {}
			CachedReference( const CachedReference& xCopy ) : m_uTargetGUID( xCopy.m_uTargetGUID ), m_pxTargetObject( xCopy.m_pxTargetObject ) {}
			void SetTarget( const GUID& xTarget ) { m_uTargetGUID = xTarget.m_uGuid; m_pxTargetObject = NULL; }
			void Clear() { m_pxTargetObject = NULL; }
			TObject* operator()() const
			{
				if( m_uTargetGUID == UNSET )
				{
					m_pxTargetObject = NULL;
				}
				if( !m_pxTargetObject )
				{
					m_pxTargetObject = GUID::GetObjectByUInt( m_uTargetGUID );
				}
				return m_pxTargetObject;
			}

		protected:
			u_int m_uTargetGUID;
			mutable TObject* m_pxTargetObject;
		};

		///////////////////////////////////////////////////////////////////////////
		// allows GUIDs to be used as keys in collections
	public:
		struct Hasher
		{
			size_t operator()( const GUID& xGuid ) const
			{
				return xGuid.GetValue();
			}
		};

		///////////////////////////////////////////////////////////////////////////
		// GUID functions

		void operator=(const GUID& b) { m_uGuid = b.m_uGuid; }
		bool operator==(const GUID& b) const { return m_uGuid == b.m_uGuid; }
		bool operator!=(const GUID& b) const { return m_uGuid != b.m_uGuid; }
		bool operator<(const GUID& b) const { return m_uGuid < b.m_uGuid; }

		CachedReference GetCachedReference() const { return CachedReference(*this); }

		void Invalidate() { m_uGuid = UNSET; }
		bool IsInvalid() const { return m_uGuid == UNSET; }

	protected:
		// only managers and cached references get access to the internals of a GUID
		friend struct Manager;
		friend class CachedReference;
		GUID() : m_uGuid( UNSET ) {  }
		GUID( unsigned int uGuid ) : m_uGuid( uGuid ) {}
		GUID( const GUID& xCopy ) : m_uGuid( xCopy.m_uGuid ) {}

		u_int m_uGuid;
	};

	

};



