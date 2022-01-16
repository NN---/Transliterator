#include "stdafx.hpp"
#include "window_text.hpp"

namespace window_text
{

// Unicode CP
static const UINT unicode_cp = 1200;

void get_window_text(HWND wnd, lang_vector& text)
{
    CWindow ctrl(wnd);

    text.resize(ctrl.GetWindowTextLength() + 1);
    ctrl.GetWindowText(&text[0], text.size() - 1)
}

void get_edit_text(HWND wnd, lang_vector& text)
{
    CEdit ctrl(wnd);

    text.resize(ctrl.GetWindowTextLength() + 1);

}

void get_rich_text(HWND wnd, lang_vector& text)
{
    CRichEditCtrl ctrl(wnd);

    text.resize(ctrl.GetWindowTextLength() + 1);
    ctrl.GetTextEx(reinterpret_cast<LPTSTR>(&text[0]),
                   (text.size() - 1)* sizeof(lang_vector::value_type),
                   GT_DEFAULT,
                   unicode_cp);
}

struct class_name_to_f
{
    const lang_tchar* m_class_name;
    void (*m_f)(HWND, lang_vector&);
};

typedef array<class_name_to_f, 4> class_name_to_f_t;
static const class_name_to_f_t c_to_f =
{
    _T("EDIT"), &get_edit_text,
    _T("RichEdit"), &get_edit_text,
    _T("RichEdit20A"), &get_rich_text,
    _T("RichEdit20W"), &get_rich_text,
};

void get(HWND wnd, lang_vector& text)
{
    array<lang_tchar, 128> class_name;
    ::GetClassName(wnd, &class_name[0], class_name.size());

    NN_FOREACH(class_name_to_f_t::const_iterator, it, c_to_f)
        if(StrCmpI(&class_name[0], &it->m_class_name[0]) == 0)
        {
            it->m_f(wnd, text);
            break;
        }
}

void set(HWND wnd, const lang_vector& text)
{

}

void set(HWND wnd, const lang_string& text)
{

}

} // namespace window_text