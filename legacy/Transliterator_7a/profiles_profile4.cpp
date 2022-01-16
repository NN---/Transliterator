#include "stdafx.hpp"
#include "profiles.hpp"

void profiles::init_profile4(profile& p)
{
    // Profile Name
    p.m_profile_name = L"Symbols";

    // Lang Name
    p.m_lang_name[0] = L"Symbols";
    p.m_lang_name[1] = L"Cyrillic";

    // Translation
    static const lang_type_nc translation[] =
    {
        lang_type_nc(L"a",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"A",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"6",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"6",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"B",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"�",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"r",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"r",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"D",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"D",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"e",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"E",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"e",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"E",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L">|<",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"}|{",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L">-|-<", L"�", bimap_direction::left_to_right),
        lang_type_nc(L"}-|-{", L"�", bimap_direction::left_to_right),
        lang_type_nc(L"3",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"3",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"u",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"U",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"u'",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"U'",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"u`",    L"�", bimap_direction::left_to_right),
        lang_type_nc(L"U`",    L"�", bimap_direction::left_to_right),
        lang_type_nc(L"k",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"K",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"/\\",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"JI",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"m",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"M",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"H",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"H",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"o",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"O",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"n",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"n",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"p",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"P",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"c",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"C",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"T",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"T",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"y",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"Y",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"f",     L"�", bimap_direction::left_to_right),
        lang_type_nc(L"F",     L"�", bimap_direction::left_to_right),
        lang_type_nc(L"(|)",   L"�", bimap_direction::left_to_right),
        lang_type_nc(L"(I)",   L"�", bimap_direction::left_to_right),
        lang_type_nc(L"<|>",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"<I>",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"x",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"X",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"L|",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"L|",    L"�", bimap_direction::right_to_left),
        lang_type_nc(L"4",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"4",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"LLI",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"w",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"LL|",   L"�", bimap_direction::all_to_all),
        lang_type_nc(L"LL|",   L"�", bimap_direction::right_to_left),
        lang_type_nc(L"\\",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"\\\\",  L"�", bimap_direction::right_to_left),
        lang_type_nc(L"bI",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"bI",    L"�", bimap_direction::right_to_left),
        lang_type_nc(L"b",     L"�", bimap_direction::all_to_all),
        lang_type_nc(L"b",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"e",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"E",     L"�", bimap_direction::right_to_left),
        lang_type_nc(L"IO",    L"�", bimap_direction::right_to_left),
        lang_type_nc(L"I-O",   L"�", bimap_direction::left_to_right),
        lang_type_nc(L"I-O",   L"�", bimap_direction::right_to_left),
        lang_type_nc(L"9I",    L"�", bimap_direction::all_to_all),
        lang_type_nc(L"9I",    L"�", bimap_direction::right_to_left),
    };

    p.m_translation.insert(translation, end(translation));
}