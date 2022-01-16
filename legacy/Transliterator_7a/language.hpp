#ifndef TRANSLITERATOR_LANGUAGE_H
#define TRANSLITERATOR_LANGUAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

struct language
{
    // Size language
    static const size_t size = 2;

    enum type
    {
        top,
        bottom
    };

    static void init();

    // Cannot use settings::language_count because of recursive include
    static const size_t language_count = 3;
    static const array<translations::language_type, language_count> s_languages;

private:
    typedef const pair<translations::id_type, const TCHAR*> id_text_type;
    
    // Automatic insert
    template<size_t N>
    static void insert_translation(translations::lang_to_translation& translation,
                                   size_t lang,
                                   const array<language::id_text_type, N>& idtext)
    {
        typedef translations::lang_to_translation::value_type translation_value_type;
        typedef translations::id_to_text id_to_text;

        id_to_text id_text_temp(idtext.begin(), idtext.end());
        translation_value_type translation_value(s_languages[lang], id_text_temp);

        translation.insert(translation_value);
    }

    template<size_t NText, size_t NOther>
    static void insert_language(size_t lang,
                                const array<language::id_text_type, NText>& text,
                                const array<language::id_text_type, NOther>& other)
    {
        insert_translation(translations::text(), lang, text);
        insert_translation(translations::other(), lang, other);
    }

    // Translations
    static const size_t text_size = 45;
    static const size_t other_size = 1;

    // English
    static const array<id_text_type, text_size> english_text;
    static const array<id_text_type, other_size> english_other;

    //static const id_text russian_text[];
    //static const id_text russian_other[];

    //static const id_text translit_text[];
    //static const id_text translit_other[];
};

#endif // TRANSLITERATOR_LANGUAGE_H
