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
        lang_type_nc(L"a",     L"à", bimap_direction::all_to_all),
        lang_type_nc(L"A",     L"À", bimap_direction::all_to_all),
        lang_type_nc(L"6",     L"á", bimap_direction::all_to_all),
        lang_type_nc(L"6",     L"Á", bimap_direction::right_to_left),
        lang_type_nc(L"B",     L"Â", bimap_direction::all_to_all),
        lang_type_nc(L"Â",     L"â", bimap_direction::right_to_left),
        lang_type_nc(L"r",     L"ã", bimap_direction::all_to_all),
        lang_type_nc(L"r",     L"Ã", bimap_direction::right_to_left),
        lang_type_nc(L"D",     L"ä", bimap_direction::all_to_all),
        lang_type_nc(L"D",     L"Ä", bimap_direction::right_to_left),
        lang_type_nc(L"e",     L"å", bimap_direction::all_to_all),
        lang_type_nc(L"E",     L"Å", bimap_direction::all_to_all),
        lang_type_nc(L"e",     L"¸", bimap_direction::right_to_left),
        lang_type_nc(L"E",     L"¨", bimap_direction::right_to_left),
        lang_type_nc(L">|<",   L"æ", bimap_direction::all_to_all),
        lang_type_nc(L"}|{",   L"Æ", bimap_direction::all_to_all),
        lang_type_nc(L">-|-<", L"æ", bimap_direction::left_to_right),
        lang_type_nc(L"}-|-{", L"Æ", bimap_direction::left_to_right),
        lang_type_nc(L"3",     L"ç", bimap_direction::all_to_all),
        lang_type_nc(L"3",     L"Ç", bimap_direction::right_to_left),
        lang_type_nc(L"u",     L"è", bimap_direction::all_to_all),
        lang_type_nc(L"U",     L"È", bimap_direction::right_to_left),
        lang_type_nc(L"u'",    L"é", bimap_direction::all_to_all),
        lang_type_nc(L"U'",    L"É", bimap_direction::all_to_all),
        lang_type_nc(L"u`",    L"é", bimap_direction::left_to_right),
        lang_type_nc(L"U`",    L"É", bimap_direction::left_to_right),
        lang_type_nc(L"k",     L"ê", bimap_direction::all_to_all),
        lang_type_nc(L"K",     L"Ê", bimap_direction::all_to_all),
        lang_type_nc(L"/\\",   L"ë", bimap_direction::all_to_all),
        lang_type_nc(L"JI",    L"Ë", bimap_direction::all_to_all),
        lang_type_nc(L"m",     L"ì", bimap_direction::all_to_all),
        lang_type_nc(L"M",     L"Ì", bimap_direction::all_to_all),
        lang_type_nc(L"H",     L"í", bimap_direction::all_to_all),
        lang_type_nc(L"H",     L"Í", bimap_direction::right_to_left),
        lang_type_nc(L"o",     L"î", bimap_direction::all_to_all),
        lang_type_nc(L"O",     L"Î", bimap_direction::all_to_all),
        lang_type_nc(L"n",     L"ï", bimap_direction::all_to_all),
        lang_type_nc(L"n",     L"Ï", bimap_direction::right_to_left),
        lang_type_nc(L"p",     L"ð", bimap_direction::all_to_all),
        lang_type_nc(L"P",     L"Ð", bimap_direction::all_to_all),
        lang_type_nc(L"c",     L"ñ", bimap_direction::all_to_all),
        lang_type_nc(L"C",     L"Ñ", bimap_direction::all_to_all),
        lang_type_nc(L"T",     L"ò", bimap_direction::all_to_all),
        lang_type_nc(L"T",     L"Ò", bimap_direction::right_to_left),
        lang_type_nc(L"y",     L"ó", bimap_direction::all_to_all),
        lang_type_nc(L"Y",     L"Ó", bimap_direction::all_to_all),
        lang_type_nc(L"f",     L"ô", bimap_direction::left_to_right),
        lang_type_nc(L"F",     L"Ô", bimap_direction::left_to_right),
        lang_type_nc(L"(|)",   L"ô", bimap_direction::left_to_right),
        lang_type_nc(L"(I)",   L"Ô", bimap_direction::left_to_right),
        lang_type_nc(L"<|>",   L"ô", bimap_direction::all_to_all),
        lang_type_nc(L"<I>",   L"Ô", bimap_direction::all_to_all),
        lang_type_nc(L"x",     L"õ", bimap_direction::all_to_all),
        lang_type_nc(L"X",     L"Õ", bimap_direction::all_to_all),
        lang_type_nc(L"L|",    L"ö", bimap_direction::all_to_all),
        lang_type_nc(L"L|",    L"Ö", bimap_direction::right_to_left),
        lang_type_nc(L"4",     L"÷", bimap_direction::all_to_all),
        lang_type_nc(L"4",     L"×", bimap_direction::right_to_left),
        lang_type_nc(L"LLI",   L"Ø", bimap_direction::all_to_all),
        lang_type_nc(L"w",     L"ø", bimap_direction::all_to_all),
        lang_type_nc(L"LL|",   L"ù", bimap_direction::all_to_all),
        lang_type_nc(L"LL|",   L"Ù", bimap_direction::right_to_left),
        lang_type_nc(L"\\",    L"ú", bimap_direction::all_to_all),
        lang_type_nc(L"\\\\",  L"Ú", bimap_direction::right_to_left),
        lang_type_nc(L"bI",    L"û", bimap_direction::all_to_all),
        lang_type_nc(L"bI",    L"Û", bimap_direction::right_to_left),
        lang_type_nc(L"b",     L"ü", bimap_direction::all_to_all),
        lang_type_nc(L"b",     L"Ü", bimap_direction::right_to_left),
        lang_type_nc(L"e",     L"ý", bimap_direction::right_to_left),
        lang_type_nc(L"E",     L"Ý", bimap_direction::right_to_left),
        lang_type_nc(L"IO",    L"þ", bimap_direction::right_to_left),
        lang_type_nc(L"I-O",   L"þ", bimap_direction::left_to_right),
        lang_type_nc(L"I-O",   L"Þ", bimap_direction::right_to_left),
        lang_type_nc(L"9I",    L"ÿ", bimap_direction::all_to_all),
        lang_type_nc(L"9I",    L"ß", bimap_direction::right_to_left),
    };

    p.m_translation.insert(translation, end(translation));
}