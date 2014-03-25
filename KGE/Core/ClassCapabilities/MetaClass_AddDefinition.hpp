
// include to add metadata to the current class, must inherit from a class that has included MetaClass_AddRoot

#ifndef THIS_T
static_assert(false, "THIS_T must be defined");
#endif
#ifndef PARENT_T
static_assert(false, "PARENT_T must be defined");
#endif
#ifndef HASHSTRING_T
static_assert(false, "HASHSTRING_T must be defined");
#endif

private:
	typedef PARENT_T parent_t;
	typedef THIS_T this_t;
public:
	static const KGE::Hash& Static_GetClassHash()
	{
		static KGE::Hash xHash( HASHSTRING_T );
		return xHash;
	}
	virtual const KGE::Hash& GetClassHash() const
	{ 
		return this_t::Static_GetClassHash();
	}
	virtual bool IsBaseOrDerivedClass(const KGE::Hash& xClassHash) const
	{
		return Static_GetClassHash() == xClassHash ? true : parent_t::IsBaseOrDerivedClass(xClassHash);
	}

#ifdef PRESERVE_DEFINES
#undef PRESERVE_DEFINES
#else
#undef THIS_T
#undef PARENT_T
#undef HASHSTRING_T
#endif
