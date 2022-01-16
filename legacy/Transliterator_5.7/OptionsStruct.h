#ifndef __OPTIONSSTRUCT_H__
#define __OPTIONSSTRUCT_H__

struct OptionsStruct
{
	Language m_Language;
	Options m_Options;
	Ignore m_Ignore;

	void Set(Language& rL,Options& rO,Ignore& rI)
	{
		Set(rL);
		Set(rO);
		Set(rI);
	}

	void Set(Language& r) { m_Language=r; }
	void Set(Options& r) { m_Options=r; }
	void Set(Ignore& r) { m_Ignore=r; }

	void Get(Language& rL,Options& rO,Ignore& rI)
	{
		Get(rL);
		Get(rO);
		Get(rI);
	}

	void Get(Language& r) { r=m_Language; }
	void Get(Options& r) { r=m_Options; }
	void Get(Ignore& r) { r=m_Ignore; }

	void Reset()
	{
		m_Language.ResetUser();
		m_Options.Reset();
		m_Ignore.Reset();
	}
};

#endif // __OptionsStruct_H__
