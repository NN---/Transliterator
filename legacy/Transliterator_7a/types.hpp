#ifndef TRANSLITERATOR_TYPES_H
#define TRANSLITERATOR_TYPES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

// Char
typedef wchar_t lang_char;
typedef TCHAR lang_tchar;

// String
typedef wnd_wstring_shell lang_string;
typedef lang_string::traits_type lang_string_traits;
typedef wnd_tstring_shell lang_tstring;
typedef lang_tstring::traits_type lang_tstring_traits;

// Lang map
typedef bimap_from<lang_string, lang_string> lang_map;

// Lang type
typedef lang_map::value_type lang_type;

// Lang type non constructible
typedef triple<
    const lang_char*,
    const lang_char*,
    bimap_direction::type
> lang_type_nc;

// Vector
typedef vector<lang_char> lang_vector;
typedef vector<lang_tchar> lang_tvector;

#endif // TRANSLITERATOR_TYPES_H
