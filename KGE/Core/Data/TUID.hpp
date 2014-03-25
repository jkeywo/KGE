#pragma once

namespace KGE
{
	template< typename TObject >
	class TUID
	{
	public:
		static const unsigned int UNSET = 0;

	protected:
		///////////////////////////////////////////////////////////////////////////
		// Static system for TUID management and lists
		struct Manager
		{
			Manager() : NextTUID(UNSET + 1) {}
			std::map<u_int, TUID*> TUIDReferences;
			u_int NextTUID;
		};
		static Manager& GetManager()	{ static Manager xInstance; return(xInstance); }

		///////////////////////////////////////////////////////////////////////////
		// Stores a TUID and a cache of the object it points to
		// Useful for moving TUIDs around a network or saving them between sessions
	public:
		class CachedReference
		{
		public:
			CachedReference() : m_uTargetTUID( UNSET ), m_pxTargetObject( NULL ) {}
			CachedReference(const TUID& xTarget) : m_uTargetTUID(xTarget.m_uTUID), m_pxTargetObject(&xTarget.m_xTarget) {}
			CachedReference( const CachedReference& xCopy ) : m_uTargetTUID( xCopy.m_uTargetTUID ), m_pxTargetObject( xCopy.m_pxTargetObject ) {}
			
			void SetTarget(const TUID& xTarget) { m_uTargetTUID = xTarget.m_uTUID; m_pxTargetObject = &xTarget.m_xTarget; }
			void SetTarget(u_int uTarget) { m_uTargetTUID = uTarget; m_pxTargetObject = NULL; }
			void Clear() { m_pxTargetObject = NULL; }
			TObject* operator()() const
			{
				if( m_uTargetTUID == UNSET )
				{
					m_pxTargetObject = NULL;
				}
				if( !m_pxTargetObject )
				{
					Manager& xInstance = GetManager();
					std::map<u_int, TUID*>::iterator xIt = xInstance.TUIDReferences.find(m_uTargetTUID);
					if (xIt != xInstance.TUIDReferences.end())
					{
						m_pxTargetObject = &xIt->second->m_xTarget;
					}
				}
				return m_pxTargetObject;
			}
			// TODO save to stream
			// TODO load from stream

		protected:
			u_int m_uTargetTUID;
			mutable TObject* m_pxTargetObject;
		};

	public:
		///////////////////////////////////////////////////////////////////////////
		// allows TUIDs to be used as keys in collections
		struct Hasher
		{
			size_t operator()( const TUID& xTUID ) const
			{
				return xTUID.m_uTUID;
			}
		};

		TUID(TObject& xTarget) : m_uTUID(UNSET), m_xTarget(xTarget)
		{
			Manager& xInstance = GetManager();
			while (xInstance.TUIDReferences.find(xInstance.NextTUID) != xInstance.TUIDReferences.end())
			{
				xInstance.NextTUID++;
			}
			m_uTUID = xInstance.NextTUID++;
			xInstance.TUIDReferences.insert(pair<u_int, TUID*>(m_uTUID, this));
		}
		// TODO load from stream
		~TUID()
		{
			Manager& xInstance = GetManager();
			std::map<u_int, TUID*>::iterator xIt = xInstance.TUIDReferences.find(m_uTUID);
			if (xIt != xInstance.TUIDReferences.end())
			{
				// TODO clear cached references
				xInstance.TUIDReferences.erase(xIt);
			}
		}

		CachedReference GetCachedReference() const { return CachedReference(*this); }

		void Invalidate() { m_uTUID = UNSET; }
		bool IsInvalid() const { return m_uTUID == UNSET; }

		void operator=(const TUID& b) { m_uTUID = b.m_uTUID; }
		bool operator==(const TUID& b) const { return m_uTUID == b.m_uTUID; }
		bool operator!=(const TUID& b) const { return m_uTUID != b.m_uTUID; }
		bool operator<(const TUID& b) const { return m_uTUID < b.m_uTUID; }
		// TODO save to stream

	protected:
		// only managers and cached references get access to the internals of a TUID
		friend struct Manager;
		friend class CachedReference;
		TUID(const TUID& xCopy) : m_uTUID(xCopy.m_uTUID), m_xTarget(xCopy.m_xTarget) {}

		TObject& m_xTarget;
		u_int m_uTUID;

	};

	

};



