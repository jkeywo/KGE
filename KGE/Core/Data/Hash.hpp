#pragma once

// Defines
#ifdef _DEBUG
#define DEBUG_STORE_STRING(STRING) , m_szHashString(STRING)
#define DEBUG_SET_STRING(STRING) m_szHashString = STRING;
#define DEBUG_APPEND_STRING(STRING) m_szHashString.append(STRING);
#define DEBUG_CLEAR_STRING m_szHashString.clear();
#define CHECKED_HASH(HASH, STRING) KGE::Hash(HASH, STRING)
#else
#define DEBUG_STORE_STRING(STRING)
#define DEBUG_SET_STRING(STRING)
#define DEBUG_APPEND_STRING(STRING)
#define DEBUG_CLEAR_STRING
#define CHECKED_HASH(HASH, STRING) KGE::Hash(HASH)
#endif

namespace KGE
{
	class Hash
	{
	public:
		static const unsigned int UNSET = 0;

		Hash() : m_uHash(UNSET) { DEBUG_CLEAR_STRING }
		Hash(const string& szHashString) : m_uHash(UNSET) DEBUG_STORE_STRING(szHashString) { SetHash(szHashString); }
		Hash(unsigned int uHashValue) : m_uHash(uHashValue) { DEBUG_CLEAR_STRING }
		Hash(const Hash& xCopy) : m_uHash(xCopy.m_uHash) DEBUG_STORE_STRING(xCopy.m_szHashString) {}
#ifdef _DEBUG
		// Includes a check to see if the string matches a specified hash ID
		Hash(unsigned int uHashValue, string szHashString)
			: m_uHash(UNSET) DEBUG_STORE_STRING(szHashString)
		{
			SetHash(szHashString);
		}

		string GetDebugString() const { return m_szHashString; }
#endif

		struct Hasher
		{
			size_t operator()( const Hash& xHash ) const
			{
				return xHash.GetHash();
			}
		};

		void operator=(const Hash& b) { m_uHash = b.m_uHash; DEBUG_SET_STRING(b.m_szHashString) }
		void operator=(const string& b) { SetHash(b); DEBUG_SET_STRING(b) }
		void operator+=(const string& b) { ConcatenateHash(b); DEBUG_APPEND_STRING(b) }
		bool operator==(const Hash& b) const { return m_uHash == b.m_uHash; }
		bool operator!=(const Hash& b) const { return m_uHash != b.m_uHash; }
		bool operator<(const Hash& b) const { return m_uHash < b.m_uHash; }
		Hash operator+(const string& b) const { Hash xRet(*this); xRet += b; return xRet; }
		template<typename IN_T> Hash& operator<<(const IN_T& xIn)
		{
			for (int i = 0; i < sizeof(IN_T); i++)
			{
				ConcatenateHash(static_cast<char*>(&xIn)[i]);
			}
			DEBUG_CLEAR_STRING
			return *this;
		}

		unsigned int GetHash() const { return m_uHash; }

		void Invalidate() { m_uHash = UNSET; DEBUG_CLEAR_STRING }
		bool IsInvalid() const { return m_uHash == UNSET; }

	protected:
		void SetHash(const string& szHashString)
		{
			m_uHash = UNSET;
			ConcatenateHash(szHashString);
		}
		void ConcatenateHash(const std::string& szHashString)
		{
			char c;
			int i = 0;
			while(c = szHashString[i++])
			{
				ConcatenateHash(c);
			}
		}
		void ConcatenateHash(char cChar)
		{
			m_uHash = ((m_uHash << 5) + m_uHash) + cChar;
		}
		unsigned int m_uHash;
#ifdef _DEBUG
		string m_szHashString;
#endif
	};

};

// clean up our defines
#undef DEBUG_STORE_STRING
#undef DEBUG_SET_STRING
#undef DEBUG_APPEND_STRING
#undef DEBUG_CLEAR_STRING
// #undef CHECKED_HASH // <-- Global define
