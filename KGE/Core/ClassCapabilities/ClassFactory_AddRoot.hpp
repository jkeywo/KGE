
// inclue to make the current class a valid ClassFactory root

#ifndef THIS_T
static_assert(false, "THIS_T must be defined");
#endif

public:
	typedef THIS_T root_t;
	virtual const KGE::Hash& GetClassHash() const = 0;
	virtual bool IsBaseOrDerivedClass(const KGE::Hash& xClassHash) const { return false; }

#ifdef PRESERVE_DEFINES
	#undef PRESERVE_DEFINES
#else
	#undef THIS_T
#endif