#ifndef __LANGPROFILE_H___
#define __LANGPROFILE_H___

#pragma once

#include "types.h"

struct LangProfile
{
	// Array
	LangArray m_aTranslation;
	// Language
	enum { LangTop, LangBottom };
	LangStringT m_astrLang[2];
	// Ignore
	enum
	{
		BeginTop,
		EndTop,
		BeginBottom,
		EndBottom,
		nIgnore
	};
	LangString m_astrIgnore[nIgnore];
	// IgnoreText
	IgnoreTextArray m_aIgnoreText;
	
	// Default
	static const wchar_t* DefaultIgnore() {	return L"**"; }

	// Reset
	void ResetTranslation() { m_aTranslation.clear(); }
	void ResetLang()
	{
		m_astrLang[LangTop] = "LangTop";
		m_astrLang[LangBottom] = "LangBottom";
	}
	void ResetIgnore()
	{
		for(size_t i=0; i<NN_ARRAY_LENGTH(m_astrIgnore); ++i)
			m_astrIgnore[i] = DefaultIgnore();
	}
	void ResetIgnoreText() { m_aIgnoreText.clear(); }

	// operator
	const LangProfile& operator = (const LangProfile& r)
	{
		// LangName
		for(size_t i=0; i<NN_ARRAY_LENGTH(m_astrLang); ++i)
			m_astrLang[i] = r.m_astrLang[i];

		// Ignore
		for(size_t i=0; i<NN_ARRAY_LENGTH(m_astrIgnore); ++i)
			m_astrIgnore[i] = r.m_astrIgnore[i];
		
		// Translation
		m_aTranslation.assign(
			r.m_aTranslation.begin(),
			r.m_aTranslation.end());

		// Ignore Text
		m_aIgnoreText.assign(
			r.m_aIgnoreText.begin(),
			r.m_aIgnoreText.end());

		return *this;
	}
};

#endif // __LANGPROFILE_H___
