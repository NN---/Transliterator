#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile7(profile& p)
{
    // Profile Name
    p.m_profile_name = L"KOI8-R <-> Win";

    // Lang Name
    p.m_lang_name[0] = L"KOI8-R";
    p.m_lang_name[1] = L"Win";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        //lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        //lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}