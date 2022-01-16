#include "stdafx.hpp"
#include "language.hpp"
#include "settings.hpp"

const array<
    translations::language_type,
    settings::language_count
> language::s_languages =
{
    MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
    MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT),
    MAKELANGID(LANG_RUSSIAN, SUBLANG_DEFAULT + 0x30)
};

// Translation init
void language::init()
{
    insert_language(settings::language_english, english_text, english_other);
    //insert_language(settings::language_russian, russian_text, russian_other);
    //insert_language(settings::language_translit, translit_text, translit_other);
}
