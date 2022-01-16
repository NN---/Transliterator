#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile5(profile& p)
{
    // Profile Name
    p.m_profile_name = L"QWERTY";

    // Lang Name
    p.m_lang_name[0] = L"QWERTY";
    p.m_lang_name[1] = L"ÉÖÓÊÅÍ";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"`",  L"¸", bimap_direction::all_to_all),
        lang_type_nc(L"~",  L"¨", bimap_direction::all_to_all),
        lang_type_nc(L"@",  L"\"", bimap_direction::all_to_all),
        lang_type_nc(L"#",  L"¹", bimap_direction::all_to_all),
        lang_type_nc(L"$",  L";", bimap_direction::all_to_all),
        lang_type_nc(L"^",  L":", bimap_direction::all_to_all),
        lang_type_nc(L"&",  L"?", bimap_direction::all_to_all),
        lang_type_nc(L"|",  L"/", bimap_direction::all_to_all),
        lang_type_nc(L"q",  L"é", bimap_direction::all_to_all),
        lang_type_nc(L"w",  L"ö", bimap_direction::all_to_all),
        lang_type_nc(L"e",  L"ó", bimap_direction::all_to_all),
        lang_type_nc(L"r",  L"ê", bimap_direction::all_to_all),
        lang_type_nc(L"t",  L"å", bimap_direction::all_to_all),
        lang_type_nc(L"y",  L"í", bimap_direction::all_to_all),
        lang_type_nc(L"u",  L"ã", bimap_direction::all_to_all),
        lang_type_nc(L"i",  L"ø", bimap_direction::all_to_all),
        lang_type_nc(L"o",  L"ù", bimap_direction::all_to_all),
        lang_type_nc(L"p",  L"ç", bimap_direction::all_to_all),
        lang_type_nc(L"[",  L"õ", bimap_direction::all_to_all),
        lang_type_nc(L"{",  L"Õ", bimap_direction::all_to_all),
        lang_type_nc(L"]",  L"ú", bimap_direction::all_to_all),
        lang_type_nc(L"}",  L"Ú", bimap_direction::all_to_all),
        lang_type_nc(L"a",  L"ô", bimap_direction::all_to_all),
        lang_type_nc(L"s",  L"û", bimap_direction::all_to_all),
        lang_type_nc(L"d",  L"â", bimap_direction::all_to_all),
        lang_type_nc(L"f",  L"à", bimap_direction::all_to_all),
        lang_type_nc(L"g",  L"ï", bimap_direction::all_to_all),
        lang_type_nc(L"h",  L"ð", bimap_direction::all_to_all),
        lang_type_nc(L"j",  L"î", bimap_direction::all_to_all),
        lang_type_nc(L"k",  L"ë", bimap_direction::all_to_all),
        lang_type_nc(L"l",  L"ä", bimap_direction::all_to_all),
        lang_type_nc(L";",  L"æ", bimap_direction::all_to_all),
        lang_type_nc(L":",  L"Æ", bimap_direction::all_to_all),
        lang_type_nc(L"'",  L"ý", bimap_direction::all_to_all),
        lang_type_nc(L"\"", L"Ý", bimap_direction::all_to_all),
        lang_type_nc(L"z",  L"ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"x",  L"÷", bimap_direction::all_to_all),
        lang_type_nc(L"c",  L"ñ", bimap_direction::all_to_all),
        lang_type_nc(L"v",  L"ì", bimap_direction::all_to_all),
        lang_type_nc(L"b",  L"è", bimap_direction::all_to_all),
        lang_type_nc(L"n",  L"ò", bimap_direction::all_to_all),
        lang_type_nc(L"m",  L"ü", bimap_direction::all_to_all),
        lang_type_nc(L",",  L"á", bimap_direction::all_to_all),
        lang_type_nc(L"<",  L"Á", bimap_direction::all_to_all),
        lang_type_nc(L".",  L"þ", bimap_direction::all_to_all),
        lang_type_nc(L">",  L"Þ", bimap_direction::all_to_all),
        lang_type_nc(L"/",  L".", bimap_direction::all_to_all),
        lang_type_nc(L"?",  L",", bimap_direction::all_to_all),
        lang_type_nc(L"Q",  L"É", bimap_direction::all_to_all),
        lang_type_nc(L"W",  L"Ö", bimap_direction::all_to_all),
        lang_type_nc(L"E",  L"Ó", bimap_direction::all_to_all),
        lang_type_nc(L"R",  L"Ê", bimap_direction::all_to_all),
        lang_type_nc(L"T",  L"Å", bimap_direction::all_to_all),
        lang_type_nc(L"Y",  L"Í", bimap_direction::all_to_all),
        lang_type_nc(L"U",  L"Ã", bimap_direction::all_to_all),
        lang_type_nc(L"I",  L"Ø", bimap_direction::all_to_all),
        lang_type_nc(L"O",  L"Ù", bimap_direction::all_to_all),
        lang_type_nc(L"P",  L"Ç", bimap_direction::all_to_all),
        lang_type_nc(L"A",  L"Ô", bimap_direction::all_to_all),
        lang_type_nc(L"S",  L"Û", bimap_direction::all_to_all),
        lang_type_nc(L"D",  L"Â", bimap_direction::all_to_all),
        lang_type_nc(L"F",  L"À", bimap_direction::all_to_all),
        lang_type_nc(L"G",  L"Ï", bimap_direction::all_to_all),
        lang_type_nc(L"H",  L"Ð", bimap_direction::all_to_all),
        lang_type_nc(L"J",  L"Î", bimap_direction::all_to_all),
        lang_type_nc(L"K",  L"Ë", bimap_direction::all_to_all),
        lang_type_nc(L"L",  L"Ä", bimap_direction::all_to_all),
        lang_type_nc(L"Z",  L"ß", bimap_direction::all_to_all),
        lang_type_nc(L"X",  L"×", bimap_direction::all_to_all),
        lang_type_nc(L"C",  L"Ñ", bimap_direction::all_to_all),
        lang_type_nc(L"V",  L"Ì", bimap_direction::all_to_all),
        lang_type_nc(L"B",  L"È", bimap_direction::all_to_all),
        lang_type_nc(L"N",  L"Ò", bimap_direction::all_to_all),
        lang_type_nc(L"M",  L"Ü", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}