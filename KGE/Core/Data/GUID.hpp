#pragma once

namespace KGE
{
	class GUID
	{
	public:
		static const unsigned int UNSET = 0;

		// allows GUIDs to be used as keys in collections
		struct Hasher
		{
			size_t operator()( const GUID& xGuid ) const
			{
				return xGuid.GetValue();
			}
		};

		///////////////////////////////////////////////////////////////////////////
		// Stores a list of GUIDs for a particular type
		template< typename TGuid >
		class Manager
		{
		public:
			static void SetRange( unsigned int uMin, unsigned int uMax )
			{
				GetInstance().m_uMinGuid = uMin;
				GetInstance().m_uMaxGuid = uMax;
				GetInstance().CheckRange();
			}
			static void ResetNext()
			{
				GetInstance().m_uNextGuid = GetInstance().m_uMinGuid;
			}
			static TGuid* GetGUIDReference(GUID uGuid)
			{
				return GetInstance().m_xGuidReferences[uGuid];
			}
			static std::map<GUID, TGuid*>& GetList()
			{
				return GetInstance().m_xGuidReferences;
			}

			static GUID RegisterObject( TGuid& xObject )
			{
				Manager& xInstance = GetInstance();
				while( xInstance.m_xGuidReferences.count( GUID(xInstance.m_uNextGuid) ) )
				{
					xInstance.m_uNextGuid++;
				}
				GUID xGuid( xInstance.m_uNextGuid++ );
				xInstance.m_xGuidReferences[xGuid] = &xObject;
				return xGuid;
			}
			static void UnregisterObject(GUID xGUID)
			{
				GetInstance().m_xGuidReferences.erase( xGUID );
			}
			static void UnregisterObject(TGuid& xObject)
			{
				for( std::map<GUID, TGuid*>::iterator xIt( GetInstance().m_xGuidReferences.GetBegin() ); !xIt.IsDone(); xIt.Next()  )
				{
					if( xIt.GetData() == &xObject )
					{
						GetInstance().m_xGuidReferences.Erase( xIt );
						return;
					}
				}
			}

		protected:
			Manager() : m_xGuidReferences(), m_uNextGuid(UNSET+1), m_uMinGuid(UNSET+1), m_uMaxGuid(UINT_MAX) {}

			void CheckRange()
			{
				if( m_uNextGuid < m_uMinGuid || m_uNextGuid > m_uMaxGuid )
				{
					m_uNextGuid = m_uMinGuid;
				}
			}
			std::map<GUID, TGuid*> m_xGuidReferences;
			unsigned int m_uNextGuid;
			unsigned int m_uMinGuid;
			unsigned int m_uMaxGuid;

			static Manager& GetInstance(void)	{ static Manager< TGuid > xInstance; return(xInstance); }
		};

		///////////////////////////////////////////////////////////////////////////
		// Stores a GUI and a cache of the object it points to
		// Useful for moving GUIDs around a network or saving them between sessions
		template< typename TGuid >
		class CachedReference
		{
		public:
			CachedReference() : m_xTargetGUID(), m_pxTargetObject( NULL ) {}
			CachedReference( GUID xTarget ) : m_xTargetGUID(xTarget), m_pxTargetObject( NULL ) {}
			CachedReference( const CachedReference& xCopy ) : m_xTargetGUID( xCopy.m_xTargetGUID ), m_pxTargetObject( xCopy.m_pxTargetObject ) {}
			void SetTarget( GUID xTarget ) { m_xTargetGUID = xTarget; m_pxTargetObject = NULL; }
			void Clear() { m_pxTargetObject = NULL; }
			GUID GetTarget() const { return m_xTargetGUID; }
			TGuid* operator()() const
			{
				if(!m_pxTargetObject && m_xTargetGUID != UNSET )
				{
					m_pxTargetObject = Manager<TGuid>::GetGUIDReference( m_xTargetGUID );
				}
				return m_pxTargetObject;
			}

		protected:
			GUID m_xTargetGUID;
			mutable TGuid* m_pxTargetObject;
		};


		GUID() : m_uGuid( UNSET ) {  }
		GUID( unsigned int uGuid ) : m_uGuid( uGuid ) {  }
		GUID( const GUID& xCopy ) : m_uGuid( xCopy.m_uGuid ) {  }

		void operator=(const GUID& b) { m_uGuid = b.m_uGuid; }
		bool operator==(const GUID& b) const { return m_uGuid == b.m_uGuid; }
		bool operator!=(const GUID& b) const { return m_uGuid != b.m_uGuid; }
		bool operator<(const GUID& b) const { return m_uGuid < b.m_uGuid; }

		unsigned int GetValue() const { return m_uGuid; }

		void Invalidate() { m_uGuid = UNSET; }
		bool IsInvalid() const { return m_uGuid == UNSET; }

	protected:
		unsigned int m_uGuid;
	};

	

};



