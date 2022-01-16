#ifndef TRANSLITERATOR_PROFILE_H
#define TRANSLITERATOR_PROFILE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "types.hpp"
#include "language.hpp"

struct profile
{
    profile()
    {
    }

    profile(const profile& right) :
        m_profile_name(right.m_profile_name),
        m_lang_name(right.m_lang_name),
        m_translation(right.m_translation)
    {
    }

    ~profile()
    {
    }

    profile& operator=(const profile& right)
    {
        m_profile_name = right.m_profile_name;
        m_lang_name = right.m_lang_name;
        m_translation = right.m_translation;

        return *this;
    }

    // Profile Name
    lang_string m_profile_name;

    // Language Name
    array<lang_string, language::size> m_lang_name;

    // Translation
    lang_map m_translation;
};

#endif // TRANSLITERATOR_PROFILE_H
