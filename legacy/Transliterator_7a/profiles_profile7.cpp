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
        lang_type_nc(L"Á", L"à", bimap_direction::all_to_all),
        lang_type_nc(L"Â", L"á", bimap_direction::all_to_all),
        lang_type_nc(L"×", L"â", bimap_direction::all_to_all),
        lang_type_nc(L"Ç", L"ã", bimap_direction::all_to_all),
        lang_type_nc(L"Ä", L"ä", bimap_direction::all_to_all),
        lang_type_nc(L"Å", L"å", bimap_direction::all_to_all),
        lang_type_nc(L"Ö", L"æ", bimap_direction::all_to_all),
        lang_type_nc(L"Ú", L"ç", bimap_direction::all_to_all),
        lang_type_nc(L"É", L"è", bimap_direction::all_to_all),
        lang_type_nc(L"Ê", L"é", bimap_direction::all_to_all),
        lang_type_nc(L"Ë", L"ê", bimap_direction::all_to_all),
        lang_type_nc(L"Ì", L"ë", bimap_direction::all_to_all),
        lang_type_nc(L"Í", L"ì", bimap_direction::all_to_all),
        lang_type_nc(L"Î", L"í", bimap_direction::all_to_all),
        lang_type_nc(L"Ï", L"î", bimap_direction::all_to_all),
        lang_type_nc(L"Ð", L"ï", bimap_direction::all_to_all),
        lang_type_nc(L"Ò", L"ð", bimap_direction::all_to_all),
        lang_type_nc(L"Ó", L"ñ", bimap_direction::all_to_all),
        lang_type_nc(L"Ô", L"ò", bimap_direction::all_to_all),
        lang_type_nc(L"Õ", L"ó", bimap_direction::all_to_all),
        lang_type_nc(L"Æ", L"ô", bimap_direction::all_to_all),
        lang_type_nc(L"È", L"õ", bimap_direction::all_to_all),
        lang_type_nc(L"Ã", L"ö", bimap_direction::all_to_all),
        lang_type_nc(L"Þ", L"÷", bimap_direction::all_to_all),
        lang_type_nc(L"Û", L"ø", bimap_direction::all_to_all),
        lang_type_nc(L"Ý", L"ù", bimap_direction::all_to_all),
        lang_type_nc(L"ß", L"ú", bimap_direction::all_to_all),
        lang_type_nc(L"Ù", L"û", bimap_direction::all_to_all),
        lang_type_nc(L"Ø", L"ü", bimap_direction::all_to_all),
        lang_type_nc(L"Ü", L"ý", bimap_direction::all_to_all),
        lang_type_nc(L"À", L"þ", bimap_direction::all_to_all),
        lang_type_nc(L"Ñ", L"ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"á", L"À", bimap_direction::all_to_all),
        lang_type_nc(L"â", L"Á", bimap_direction::all_to_all),
        lang_type_nc(L"÷", L"Â", bimap_direction::all_to_all),
        lang_type_nc(L"ç", L"Ã", bimap_direction::all_to_all),
        lang_type_nc(L"ä", L"Ä", bimap_direction::all_to_all),
        lang_type_nc(L"å", L"Å", bimap_direction::all_to_all),
        lang_type_nc(L"ö", L"Æ", bimap_direction::all_to_all),
        lang_type_nc(L"ú", L"Ç", bimap_direction::all_to_all),
        lang_type_nc(L"é", L"È", bimap_direction::all_to_all),
        lang_type_nc(L"ê", L"É", bimap_direction::all_to_all),
        lang_type_nc(L"ë", L"Ê", bimap_direction::all_to_all),
        lang_type_nc(L"ì", L"Ë", bimap_direction::all_to_all),
        lang_type_nc(L"í", L"Ì", bimap_direction::all_to_all),
        lang_type_nc(L"î", L"Í", bimap_direction::all_to_all),
        lang_type_nc(L"ï", L"Î", bimap_direction::all_to_all),
        lang_type_nc(L"ð", L"Ï", bimap_direction::all_to_all),
        lang_type_nc(L"ò", L"Ð", bimap_direction::all_to_all),
        lang_type_nc(L"ó", L"Ñ", bimap_direction::all_to_all),
        lang_type_nc(L"ô", L"Ò", bimap_direction::all_to_all),
        lang_type_nc(L"õ", L"Ó", bimap_direction::all_to_all),
        lang_type_nc(L"æ", L"Ô", bimap_direction::all_to_all),
        lang_type_nc(L"è", L"Õ", bimap_direction::all_to_all),
        lang_type_nc(L"ã", L"Ö", bimap_direction::all_to_all),
        lang_type_nc(L"þ", L"×", bimap_direction::all_to_all),
        lang_type_nc(L"û", L"Ø", bimap_direction::all_to_all),
        lang_type_nc(L"ý", L"Ù", bimap_direction::all_to_all),
        lang_type_nc(L"ÿ", L"Ú", bimap_direction::all_to_all),
        lang_type_nc(L"ù", L"Û", bimap_direction::all_to_all),
        lang_type_nc(L"ø", L"Ü", bimap_direction::all_to_all),
        lang_type_nc(L"ü", L"Ý", bimap_direction::all_to_all),
        lang_type_nc(L"à", L"Þ", bimap_direction::all_to_all),
        lang_type_nc(L"ñ", L"ß", bimap_direction::all_to_all),
        //lang_type_nc(L"Ó", L"¸", bimap_direction::all_to_all),
        //lang_type_nc(L"Ò", L"¨", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}