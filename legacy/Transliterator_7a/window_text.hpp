#ifndef TRANSLITERATOR_WINDOW_TEXT_H
#define TRANSLITERATOR_WINDOW_TEXT_H

#include "types.hpp"

namespace window_text
{

void get(HWND wnd, lang_vector& text);
void set(HWND wnd, const lang_vector& text);
void set(HWND wnd, const lang_string& text);

} // namespace window_text

#endif // TRANSLITERATOR_WINDOW_TEXT_H
