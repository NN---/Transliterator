#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile6(profile& p)
{
    // Profile Name
    p.m_profile_name = L"Dos <-> Win";

    // Lang Name
    p.m_lang_name[0] = L"DOS";
    p.m_lang_name[1] = L"Win";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"\xA0", L"�", bimap_direction::all_to_all),
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
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�", L"�", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}