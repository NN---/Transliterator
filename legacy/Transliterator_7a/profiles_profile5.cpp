#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile5(profile& p)
{
    // Profile Name
    p.m_profile_name = L"QWERTY";

    // Lang Name
    p.m_lang_name[0] = L"QWERTY";
    p.m_lang_name[1] = L"������";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"`",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"~",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"@",  L"\"", bimap_direction::all_to_all),
        lang_type_nc(L"#",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"$",  L";", bimap_direction::all_to_all),
        lang_type_nc(L"^",  L":", bimap_direction::all_to_all),
        lang_type_nc(L"&",  L"?", bimap_direction::all_to_all),
        lang_type_nc(L"|",  L"/", bimap_direction::all_to_all),
        lang_type_nc(L"q",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"w",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"e",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"r",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"t",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"y",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"u",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"i",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"o",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"p",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"[",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"{",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"]",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"}",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"a",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"s",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"d",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"f",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"g",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"h",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"j",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"k",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"l",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L";",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L":",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"'",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\"", L"�", bimap_direction::all_to_all),
        lang_type_nc(L"z",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"x",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"c",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"v",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"b",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"n",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"m",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L",",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"<",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L".",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L">",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"/",  L".", bimap_direction::all_to_all),
        lang_type_nc(L"?",  L",", bimap_direction::all_to_all),
        lang_type_nc(L"Q",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"W",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"E",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"R",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"T",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"Y",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"U",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"I",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"O",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"P",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"A",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"S",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"D",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"F",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"G",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"H",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"J",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"K",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"L",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"Z",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"X",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"C",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"V",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"B",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"N",  L"�", bimap_direction::all_to_all),
        lang_type_nc(L"M",  L"�", bimap_direction::all_to_all),
    };

    p.m_translation.insert(translation, end(translation));
}