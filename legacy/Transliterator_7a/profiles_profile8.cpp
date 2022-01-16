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
        lang_type_nc(L"\x5d0", L"à", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d1", L"á", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d2", L"â", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d3", L"ã", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d4", L"ä", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d5", L"å", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d6", L"æ", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d7", L"ç", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d8", L"è", bimap_direction::all_to_all),
        lang_type_nc(L"\x5d9", L"é", bimap_direction::all_to_all),
        lang_type_nc(L"\x5da", L"ê", bimap_direction::all_to_all),
        lang_type_nc(L"\x5db", L"ë", bimap_direction::all_to_all),
        lang_type_nc(L"\x5dc", L"ì", bimap_direction::all_to_all),
        lang_type_nc(L"\x5dd", L"í", bimap_direction::all_to_all),
        lang_type_nc(L"\x5de", L"î", bimap_direction::all_to_all),
        lang_type_nc(L"\x5df", L"ï", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e0", L"ð", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e1", L"ñ", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e2", L"ò", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e3", L"ó", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e4", L"ô", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e5", L"õ", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e6", L"ö", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e7", L"÷", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e8", L"ø", bimap_direction::all_to_all),
        lang_type_nc(L"\x5e9", L"ù", bimap_direction::all_to_all),
        lang_type_nc(L"\x5ea", L"ú", bimap_direction::all_to_all),
        lang_type_nc(L"\xf894", L"û", bimap_direction::all_to_all),
        lang_type_nc(L"\xf895", L"ü", bimap_direction::all_to_all),
        lang_type_nc(L"\x200e", L"ý", bimap_direction::all_to_all),
        lang_type_nc(L"\x200f", L"þ", bimap_direction::all_to_all),
        lang_type_nc(L"\xf896", L"ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"\xb8", L"¸", bimap_direction::all_to_all),
        lang_type_nc(L"\xb3", L"³", bimap_direction::all_to_all),
        lang_type_nc(L"\xbf", L"¿", bimap_direction::all_to_all),
        lang_type_nc(L"\xa2", L"¢", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}