#pragma once

namespace KGE
{
	class Event
	{
	public:
		Event(const Hash& xHash)
			: m_xHash(xHash)
		{
		}
		virtual ~Event()
		{
		}
		virtual void Execute(map<KGE::Hash, KGE::Data, KGE::Hash::Hasher>& xEventParameters) = 0;
		virtual const Hash& GetHash() const { return m_xHash; }
	protected:
		Hash m_xHash;
	};
};