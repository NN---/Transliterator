#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile8(profile& p)
{
    // Profile Name
    p.m_profile_name = L"Heb <-> Cyr";

    // Lang Name
    p.m_lang_name[0] = L"Hebrew";
    p.m_lang_name[1] = L"Cyrillic";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"\x5d0", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d1", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d2", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d3", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d4", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d5", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d6", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d7", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d8", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d9", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5da", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5db", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5dc", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5dd", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5de", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5df", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e0", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e1", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e2", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e3", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e4", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e5", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e6", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e7", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e8", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e9", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x5ea", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xf894", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xf895", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x200e", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\x200f", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xf896", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xb8", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xb3", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xbf", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\xa2", L"�", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}