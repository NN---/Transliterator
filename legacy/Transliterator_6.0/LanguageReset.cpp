#include "stdafx.h"

#include "language.h"

void Language::ResetProfile(unsigned nProfile,LangProfile& rProfile)
{
	typedef void (*ResetFunc)(LangProfile&);

	static const ResetFunc aResetFunc[nProfiles] = 
	{
		&Language::Reset1,
		&Language::Reset2,
		&Language::Reset3,
		&Language::Reset4,
		&Language::Reset5,
		&Language::Reset6,
		&Language::Reset7,
		&Language::Reset8,
		&Language::Reset9,
		&Language::Reset10,
	};
	(*aResetFunc[nProfile])(rProfile);
}

void Language::ResetTranslation(unsigned nProfile,LangProfile& rProfile)
{
	typedef void (*ResetTranslationFunc)(LangProfile&);

	static const ResetTranslationFunc aResetTranslationFunc[nProfiles] = 
	{
		&Language::ResetTranslation1,
		&Language::ResetTranslation2,
		&Language::ResetTranslation3,
		&Language::ResetTranslation4,
		&Language::ResetTranslation5,
		&Language::ResetTranslation6,
		&Language::ResetTranslation7,
		&Language::ResetTranslation8,
		&Language::ResetTranslation9,
		&Language::ResetTranslation10,
	};
	(*aResetTranslationFunc[nProfile])(rProfile);
}

void Language::ResetIgnore(unsigned nProfile,LangProfile& rProfile)
{
	typedef void (*ResetIgnoreFunc)(LangProfile&);

	static const ResetIgnoreFunc aResetIgnoreFunc[nProfiles] = 
	{
		&Language::ResetIgnore1,
		&Language::ResetIgnore2,
		&Language::ResetIgnore3,
		&Language::ResetIgnore4,
		&Language::ResetIgnore5,
		&Language::ResetIgnore6,
		&Language::ResetIgnore7,
		&Language::ResetIgnore8,
		&Language::ResetIgnore9,
		&Language::ResetIgnore10,
	};
	(*aResetIgnoreFunc[nProfile])(rProfile);
}

void Language::ResetIgnoreText(unsigned nProfile,LangProfile& rProfile)
{
	typedef void (*ResetIgnoreTextFunc)(LangProfile&);

	static const ResetIgnoreTextFunc aResetIgnoreTextFunc[nProfiles] = 
	{
		&Language::ResetIgnoreText1,
		&Language::ResetIgnoreText2,
		&Language::ResetIgnoreText3,
		&Language::ResetIgnoreText4,
		&Language::ResetIgnoreText5,
		&Language::ResetIgnoreText6,
		&Language::ResetIgnoreText7,
		&Language::ResetIgnoreText8,
		&Language::ResetIgnoreText9,
		&Language::ResetIgnoreText10,
	};
	(*aResetIgnoreTextFunc[nProfile])(rProfile);
}

void Language::ResetName(unsigned nProfile,LangProfile& rProfile)
{
	typedef void (*ResetNameFunc)(LangProfile&);

	static const ResetNameFunc aResetNameFunc[nProfiles] = 
	{
		&Language::ResetName1,
		&Language::ResetName2,
		&Language::ResetName3,
		&Language::ResetName4,
		&Language::ResetName5,
		&Language::ResetName6,
		&Language::ResetName7,
		&Language::ResetName8,
		&Language::ResetName9,
		&Language::ResetName10,
	};
	(*aResetNameFunc[nProfile])(rProfile);
}

void Language::Reset()
{
	for(unsigned i = 0;i<nProfiles; ++i)
		ResetProfile(i,*GetProfile(i));
}