#ifndef __IGNORE_H__
#define __IGNORE_H__

class Ignore
{
	IgnoreMap m_map;
public:
	unsigned GetLast() const { return m_map.GetLast(); }
	
	IgnoreType& GetAt(unsigned nItem) { return m_map[nItem]; }
	const IgnoreType& GetAt(unsigned nItem) const { return m_map[nItem]; }
	IgnoreType& operator[](unsigned nItem) { return GetAt(nItem); }
	const IgnoreType& operator[](unsigned nItem) const { return GetAt(nItem); }

	void Add(const IgnoreType& t) { m_map.Add(t); }
	void Remove(const IgnoreType& t) { m_map.Remove(t); }
	void RemoveAt(unsigned nItem) { m_map.RemoveAt(nItem); }
	void RemoveAll() { m_map.RemoveAll(); }

	void Reset() { m_map.RemoveAll(); }

	unsigned Find(const IgnoreType& t) { return m_map.Find(t); }

	const Ignore& operator=(const Ignore& ignore)
	{
		m_map.SetData(ignore.m_map);
		return *this;
	}

	bool operator!=(const Ignore& ignore) const
	{ return m_map.Compare(ignore.m_map); }
	bool operator==(const Ignore& ignore) const
	{ return !operator!=(ignore); }
};



#endif // __IGNORE_H__