#include "stdafx.hpp"
#include "text.hpp"

text& text::instance()
{
    static text s;
    return s;
}

text::text_type& text::get_text()
{
    return m_text;
}
