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
        lang_type_nc(L"\xA0", L"‡", bimap_direction::all_to_all),
        lang_type_nc(L"°", L"·", bimap_direction::all_to_all),
        lang_type_nc(L"¢", L"‚", bimap_direction::all_to_all),
        lang_type_nc(L"£", L"„", bimap_direction::all_to_all),
        lang_type_nc(L"§", L"‰", bimap_direction::all_to_all),
        lang_type_nc(L"•", L"Â", bimap_direction::all_to_all),
        lang_type_nc(L"¶", L"Ê", bimap_direction::all_to_all),
        lang_type_nc(L"ß", L"Á", bimap_direction::all_to_all),
        lang_type_nc(L"®", L"Ë", bimap_direction::all_to_all),
        lang_type_nc(L"©", L"È", bimap_direction::all_to_all),
        lang_type_nc(L"™", L"Í", bimap_direction::all_to_all),
        lang_type_nc(L"´", L"Î", bimap_direction::all_to_all),
        lang_type_nc(L"¨", L"Ï", bimap_direction::all_to_all),
        lang_type_nc(L"≠", L"Ì", bimap_direction::all_to_all),
        lang_type_nc(L"Æ", L"Ó", bimap_direction::all_to_all),
        lang_type_nc(L"Ø", L"Ô", bimap_direction::all_to_all),
        lang_type_nc(L"‡", L"", bimap_direction::all_to_all),
        lang_type_nc(L"·", L"Ò", bimap_direction::all_to_all),
        lang_type_nc(L"‚", L"Ú", bimap_direction::all_to_all),
        lang_type_nc(L"„", L"Û", bimap_direction::all_to_all),
        lang_type_nc(L"‰", L"Ù", bimap_direction::all_to_all),
        lang_type_nc(L"Â", L"ı", bimap_direction::all_to_all),
        lang_type_nc(L"Ê", L"ˆ", bimap_direction::all_to_all),
        lang_type_nc(L"Á", L"˜", bimap_direction::all_to_all),
        lang_type_nc(L"Ë", L"¯", bimap_direction::all_to_all),
        lang_type_nc(L"È", L"˘", bimap_direction::all_to_all),
        lang_type_nc(L"Í", L"˙", bimap_direction::all_to_all),
        lang_type_nc(L"Î", L"˚", bimap_direction::all_to_all),
        lang_type_nc(L"Ï", L"¸", bimap_direction::all_to_all),
        lang_type_nc(L"Ì", L"˝", bimap_direction::all_to_all),
        lang_type_nc(L"Ó", L"˛", bimap_direction::all_to_all),
        lang_type_nc(L"Ô", L"ˇ", bimap_direction::all_to_all),
        lang_type_nc(L"Ä", L"¿", bimap_direction::all_to_all),
        lang_type_nc(L"Å", L"¡", bimap_direction::all_to_all),
        lang_type_nc(L"Ç", L"¬", bimap_direction::all_to_all),
        lang_type_nc(L"É", L"√", bimap_direction::all_to_all),
        lang_type_nc(L"Ñ", L"ƒ", bimap_direction::all_to_all),
        lang_type_nc(L"Ö", L"≈", bimap_direction::all_to_all),
        lang_type_nc(L"Ü", L"∆", bimap_direction::all_to_all),
        lang_type_nc(L"á", L"«", bimap_direction::all_to_all),
        lang_type_nc(L"à", L"»", bimap_direction::all_to_all),
        lang_type_nc(L"â", L"…", bimap_direction::all_to_all),
        lang_type_nc(L"ä", L" ", bimap_direction::all_to_all),
        lang_type_nc(L"ã", L"À", bimap_direction::all_to_all),
        lang_type_nc(L"å", L"Ã", bimap_direction::all_to_all),
        lang_type_nc(L"ç", L"Õ", bimap_direction::all_to_all),
        lang_type_nc(L"é", L"Œ", bimap_direction::all_to_all),
        lang_type_nc(L"è", L"œ", bimap_direction::all_to_all),
        lang_type_nc(L"ê", L"–", bimap_direction::all_to_all),
        lang_type_nc(L"ë", L"—", bimap_direction::all_to_all),
        lang_type_nc(L"í", L"“", bimap_direction::all_to_all),
        lang_type_nc(L"ì", L"”", bimap_direction::all_to_all),
        lang_type_nc(L"î", L"‘", bimap_direction::all_to_all),
        lang_type_nc(L"ï", L"’", bimap_direction::all_to_all),
        lang_type_nc(L"ñ", L"÷", bimap_direction::all_to_all),
        lang_type_nc(L"ó", L"◊", bimap_direction::all_to_all),
        lang_type_nc(L"ò", L"ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"ô", L"Ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"ö", L"⁄", bimap_direction::all_to_all),
        lang_type_nc(L"õ", L"€", bimap_direction::all_to_all),
        lang_type_nc(L"ú", L"‹", bimap_direction::all_to_all),
        lang_type_nc(L"ù", L"›", bimap_direction::all_to_all),
        lang_type_nc(L"û", L"ﬁ", bimap_direction::all_to_all),
        lang_type_nc(L"ü", L"ﬂ", bimap_direction::all_to_all),
        lang_type_nc(L"Ò", L"∏", bimap_direction::all_to_all),
        lang_type_nc(L"", L"®", bimap_direction::all_to_all),
        lang_type_nc(L"Û", L"∫", bimap_direction::all_to_all),
        lang_type_nc(L"Ú", L"™", bimap_direction::all_to_all),
        lang_type_nc(L"ı", L"ø", bimap_direction::all_to_all),
        lang_type_nc(L"Ù", L"Ø", bimap_direction::all_to_all),
        lang_type_nc(L"˜", L"¢", bimap_direction::all_to_all),
        lang_type_nc(L"ˆ", L"°", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}