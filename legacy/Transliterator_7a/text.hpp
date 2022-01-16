#ifndef TRANSLITERATOR_TEXT_H
#define TRANSLITERATOR_TEXT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "types.hpp"
#include "language.hpp"

class text
{
public:
    static text& instance();

    typedef array<vector<lang_char>, language::size> text_type;
    text_type& get_text();

private:
    // Text
    text_type m_text;
};

#endif // TRANSLITERATOR_TEXT_H
