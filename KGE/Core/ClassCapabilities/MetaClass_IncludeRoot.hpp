
// include in a root class to setup metadata and enable it in all its decedents

#ifndef THIS_T
static_assert(false, "THIS_T must be defined");
#endif

public:
	typedef THIS_T root_t;
	virtual const KGE::Hash& GetClassHash() const = 0;
	virtual bool IsBaseOrDerivedClass(const KGE::Hash& xClassHash) const { return false; }

	const KGE::TUID<root_t>& GetTUID() const { return m_xTUID; }
	KGE::TUID<root_t>::CachedReference GetTUIDReference() const { return m_xTUID.GetCachedReference(); }

protected:
	KGE::TUID<root_t> m_xTUID;

#ifdef PRESERVE_DEFINES
#undef PRESERVE_DEFINES
#else
#undef THIS_T
#endif