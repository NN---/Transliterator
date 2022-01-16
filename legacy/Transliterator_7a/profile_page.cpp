#include "stdafx.hpp"
#include "resource.hpp"
#include "settings.hpp"
#include "profiles.hpp"
#include "types.hpp"
#include "translation.hpp"
#include "text.hpp"
#include "profile_page.hpp"

const CRect profile_page::s_delta_rect(5, 15, 5 ,5);

// Unicode CP
static const UINT unicode_cp = 1200;

void profile_page::DlgResize_UpdateLayout(int cxWidth, int cyHeight)
{
    CDialogResize<profile_page>::DlgResize_UpdateLayout(cxWidth, cyHeight);
    update_layout();
}

void profile_page::dialog_lang_language_changed()
{
    // Update language
    update_lang();
}

void profile_page::profile_changed()
{
    update_translation();
    update_lang();
}

lang_tstring profile_page::caption()
{
    return convert_cast<lang_tstring>(profiles::instance().get_profile().m_profile_name);
}

void profile_page::init_controls()
{
    // Create
    DWORD style(WS_TABSTOP     |
                WS_BORDER      |
                WS_CHILD       |
                WS_VISIBLE     |
                WS_VSCROLL     |
                ES_WANTRETURN  |
                ES_MULTILINE   |
                ES_NOHIDESEL   |
                ES_AUTOVSCROLL);
    if(!settings::instance().m_wrap_text)
        style|= WS_HSCROLL | ES_AUTOHSCROLL;
    DWORD style_ex(0);

    // Load text
    
    NN_UPTO_T(i, m_text.size())
    {
        // Create
        m_text[i].Create(m_hWnd,
                         NULL,
                         _T(""),
                         style,
                         style_ex,
                         IDC_RETOP + i);

        // Set text
        text::text_type& t = text::instance().get_text();
        if(t[i].size() != 0)
        {
            m_text[i].SetTextEx(reinterpret_cast<LPCTSTR>(&t[i][0]),
                                ST_DEFAULT,
                                unicode_cp);

            // Clear text
            t[i].clear();
        }
    }

    // Set focus to prevent selection
    m_text[0].SetFocus();

    // Set notification
    set_lang_notification(true);

    // Update layout
    update_layout();
}

void profile_page::open_save(bool open, bool top)
{open;top;
    MessageBox(_T("Not implemented yet"), _T("Transliterator"), MB_OK);
    //DWORD flags = OFN_EXPLORER | OFN_LONGNAMES | OFN_ENABLESIZING |
    //              (!open ?
    //               OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT :
    //               OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);

    //CFileDialog fd(open,
    //               _T("*.*"),
    //               NULL,
    //               flags,
    //               _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"),
    //               m_hWnd);
    //if(fd.DoModal() != IDOK)
    //    return;
    //
    //if(open)
    //{
    //    CAtlFile file;
    //    file.Create(fd.m_ofn.lpstrFile,
    //                GENERIC_READ,
    //                FILE_SHARE_READ,
    //                OPEN_EXISTING,
    //                FILE_ATTRIBUTE_NORMAL);
    //    
    //    ULONGLONG size;
    //    file.GetSize(size);
    //}
    //else
    //{
    //}
}

void profile_page::update_layout()
{
    // Resize edit boxes
	NN_UPTO_T(i, m_text.size())
    {
        // Get rect
        CRect rect;
        
        ::GetWindowRect(GetDlgItem(IDC_GRPTOP + i), &rect);
        ScreenToClient(&rect);

        // Calculate new rect
        rect -= s_delta_rect;

        // Move
        m_text[i].MoveWindow(&rect);
    }
}

void profile_page::update_translation()
{
    translate(::GetFocus() == m_text[language::top] ?
              direction::top_to_bottom :
              direction::bottom_to_top);
}

void profile_page::update_lang()
{
    static const lang_tstring separator(_T(" - "));

    NN_UPTO_T(i, m_text.size())
    {
        // Prepare string
        lang_tstring count_string;
        convert(profiles::instance().get_profile().m_lang_name[i], count_string);

        // Add separator
        count_string += separator;

        // Add length
        TCHAR length[digits_number<int>::value + 1];
        _itot(m_text[i].GetWindowTextLength(), length, 10);
        count_string += length;

        SetDlgItemText(IDC_GRPTOP + i, count_string.c_str());
    }
}

void profile_page::translate(direction::type dir)
{
    // disable_lang_notify
    struct disable_lang_notify
    {
        disable_lang_notify(profile_page& t) : m_t(t)
        {
            m_t.set_lang_notification(false);
        }
        
        ~disable_lang_notify() 
        {
            m_t.set_lang_notification(true);
        }

    private:
        profile_page& m_t;
    } dln(*this);

    // Controls
    CRichEditCtrl from_ctrl = m_text[dir == direction::top_to_bottom ? 0 : 1];
    CRichEditCtrl to_ctrl = m_text[dir == direction::top_to_bottom ? 1 : 0];

    // Get text
    typedef vector<wchar_t> text_vector;
    text_vector text_in(
        static_cast<size_t>(from_ctrl.GetWindowTextLength()) + 1);
    text_vector text_out(translation::size(text_in.size(),
                                           dir,
                                           profiles::instance().get_profile()));

    from_ctrl.GetTextEx(reinterpret_cast<LPTSTR>(&text_in[0]),
                        text_in.size() * sizeof(text_vector::value_type),
                        GT_DEFAULT,
                        unicode_cp);

    // Translate
    translation::translate(&text_in[0],
                           &text_out[0],
                           dir,
                           profiles::instance().get_profile());

    // Set text
    to_ctrl.SetTextEx(reinterpret_cast<LPCTSTR>(&text_out[0]),
                      ST_DEFAULT,
                      unicode_cp);
}

void profile_page::set_lang_notification(bool notify)
{
    NN_FOREACH(text_type::iterator, it, m_text)
        it->SetEventMask(notify ? ENM_CHANGE | ENM_MOUSEEVENTS : 0);
}

void profile_page::save_text()
{
    // Save text
    NN_UPTO_T(i, language::size)
    {
        text::text_type& t = text::instance().get_text();

        // Resize
        size_t length = static_cast<size_t>(m_text[i].GetTextLength() + 1);
        t[i].resize(length);
        
        // Get text
        m_text[i].GetTextEx(reinterpret_cast<LPTSTR>(&t[i][0]),
                            length * sizeof(lang_char),
                            GT_DEFAULT,
                            unicode_cp);
    }
}

LRESULT profile_page::on_init_dialog(HWND /*wnd_focus*/, LPARAM /*lparam*/)
{
    // Init controls
    init_controls();

    // Not handled
    SetMsgHandled(FALSE);

    return 0;
}

LRESULT profile_page::on_destroy()
{
    // Save text
    if(settings::instance().m_save_text != settings::save_text_no)
        save_text();

    return 0;
}

LRESULT profile_page::on_drop_files(HDROP drop)
{
    struct drag_finish
    {
        drag_finish(HDROP drop) : m_drop(drop) {}
        ~drag_finish() { ::DragFinish(m_drop); }
    private:
        HDROP m_drop;
    } df(drop);

    

    return 0;
}

LRESULT profile_page::on_en_change_lang(WORD /*notify_code*/, WORD id, HWND /*wnd_control*/)
{
    bool top(id == IDC_RETOP);

    // Direction
    translate(top ?
              direction::top_to_bottom :
              direction::bottom_to_top);

    // Scroll    
    CRichEditCtrl from(m_text[top ? language::top : language::bottom]);
    CRichEditCtrl to(m_text[top ? language::bottom : language::top]);

    if(settings::instance().m_scroll_text)
        to.LineScroll(from.GetFirstVisibleLine());

    // Update
    update_lang();

    return 0;
}

LRESULT profile_page::on_en_msg_filter_lang(LPNMHDR notify)
{
    MSGFILTER *msg_filter = reinterpret_cast<MSGFILTER *>(notify);
    if(msg_filter->msg == WM_RBUTTONDOWN)
    {
        //::SetFocus(msg_filter->nmhdr.hwndFrom);

        //OnIdle();

        //CPoint pt;
        //::GetCursorPos(&pt);

        //CMenu menu = WTL::AtlLoadMenu(IDR_EDIT);
        //::TrackPopupMenu(menu.GetSubMenu(0),
        //                 TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
        //                 pt.x,
        //                 pt.y,
        //                 0,
        //                 m_hWnd,
        //                 NULL);
    }

    return 0;
}