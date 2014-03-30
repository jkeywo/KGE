#pragma once

#define METACLASS_ROOTDATA( THIS_T )	\
private:								\
	typedef THIS_T this_t;				\
public:									\
	typedef THIS_T root_t;

#define METACLASS_CHILDDATA( THIS_T, PARENT_T, HASHSTRING )	\
private:													\
	typedef PARENT_T parent_t;								\
	typedef THIS_T this_t;									\
public:														\
	static const KGE::Hash& Static_GetClassHash()			\
	{														\
		static KGE::Hash xHash(HASHSTRING);					\
		return xHash;										\
	}

