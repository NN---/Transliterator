#ifndef TRANSLITERATOR_PROFILE_PAGE_H
#define TRANSLITERATOR_PROFILE_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"
#include "language.hpp"
#include "direction.hpp"

class profile_page : public page_impl<profile_page>
{
public:
    enum { IDD = IDD_PROFILE };

    // Overrides
    void DlgResize_UpdateLayout(int cxWidth, int cyHeight);

    void dialog_lang_language_changed();

    virtual void profile_changed();

    virtual lang_tstring caption();

    virtual void open_save(bool open, bool top);

    // Resize map
    BEGIN_DLGRESIZE_MAP(profile_page)
        BEGIN_DLGRESIZE_GROUP()
            DLGRESIZE_CONTROL(IDC_GRPTOP, DLSZ_SIZE_X|DLSZ_SIZE_Y)
            DLGRESIZE_CONTROL(IDC_GRPBOTTOM, DLSZ_SIZE_X|DLSZ_SIZE_Y)
        END_DLGRESIZE_GROUP()
    END_DLGRESIZE_MAP()

    // Message map
    BEGIN_MSG_MAP(profile_part)
        MSG_WM_INITDIALOG(on_init_dialog)
        MSG_WM_DESTROY(on_destroy)
        MSG_WM_DROPFILES(on_drop_files)
        
#pragma warning(push)
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'WORD', possible loss of data
        COMMAND_HANDLER_EX(IDC_RETOP, EN_CHANGE, on_en_change_lang)
        COMMAND_HANDLER_EX(IDC_REBOTTOM, EN_CHANGE, on_en_change_lang)
#pragma warning(pop)
        
        NOTIFY_HANDLER_EX(IDC_RETOP, EN_MSGFILTER, on_en_msg_filter_lang)
        NOTIFY_HANDLER_EX(IDC_REBOTTOM, EN_MSGFILTER, on_en_msg_filter_lang)

        CHAIN_MSG_MAP(page_impl<profile_page>)
    END_MSG_MAP()

private:
    // Controls
    void init_controls();

    // Layout
    void update_layout();

    // Language
    void update_lang();

    // Translation
    void update_translation();
    void translate(direction::type dir);

    // Notification
    void set_lang_notification(bool notify);

    // Text
    void save_text();

    // Messages
    LRESULT on_init_dialog(HWND wnd_focus, LPARAM lparam);
    LRESULT on_destroy();
    LRESULT on_drop_files(HDROP drop);

    LRESULT on_en_change_lang(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_en_msg_filter_lang(LPNMHDR notify);

    // Variables
    static const CRect s_delta_rect;

    typedef array<CRichEditCtrl, language::size> text_type;
    text_type m_text;
};

#endif // TRANSLITERATOR_PROFILE_PAGE_H
