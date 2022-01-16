#ifndef TRANSLITERATOR_PAGE_IMPL_H
#define TRANSLITERATOR_PAGE_IMPL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "types.hpp"

struct i_dialog_lang
{
    virtual void update_language_i() = 0;
};

struct i_profile_changed
{
    virtual void profile_changed() = 0;
};

struct i_caption
{
    virtual lang_tstring caption() = 0;
};

struct i_open_save
{
    virtual void open_save(bool open, bool top) = 0;
};

struct i_page_impl : i_dialog_lang,
                     i_profile_changed,
                     i_caption,
                     i_open_save
{
};

template<typename T>
class page_impl : public CDialogImpl<T>,
                  public CDialogResize<T>,
                  public CWinDataExchange<T>,
                  public dialog_lang<T>,
                  public dialog_impl<T, CWindow, i_page_impl>

{
public:
    // Override
    virtual void update_language_i()
    {
        static_cast<T*>(this)->update_language();
    }

    virtual void profile_changed()
    {
    }

    virtual lang_tstring caption()
    {
        // Load string with IDD
        lang_tstring caption;
        get_translation_text(static_cast<T*>(this)->IDD,
                            caption, 
                            default_language::get());
        return caption;
    }

    virtual void open_save(bool /*open*/, bool /*top*/)
    {
    }

    void dialog_lang_language_changed()
    {
        load_settings();
    }

    // Initialization
    void page_impl_init()
    {
        // Init resize
        DlgResize_Init(false, false);

        // Init language
        dialog_lang_init();
    }

    // Resize Map
    BEGIN_DLGRESIZE_MAP(page_impl)
    END_DLGRESIZE_MAP()

    // DDX Map
    virtual BEGIN_DDX_MAP(page_impl)
    END_DDX_MAP()

    // Message Map
    BEGIN_MSG_MAP(page_impl)
        MSG_WM_INITDIALOG(on_init_dialog)
        MSG_WM_SHOWWINDOW(on_show_window)

        #pragma warning(push)
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'WORD', possible loss of data
        COMMAND_ID_HANDLER_EX(IDC_BTNAPPLY, on_apply)
        COMMAND_ID_HANDLER_EX(IDC_BTNRESTORE, on_restore)
#pragma warning(pop)

        CHAIN_MSG_MAP(CDialogResize<T>)
    END_MSG_MAP()

private:
    void save_settings()
    {
        DoDataExchange(DDX_SAVE);
    }

    void load_settings()
    {
        DoDataExchange(DDX_LOAD);
    }

    LRESULT on_init_dialog(HWND /*wnd_focus*/, LPARAM /*lparam*/)
    {
        page_impl_init();

        return FALSE;
    }

    LRESULT on_show_window(BOOL show, UINT /*status*/)
    {
        // Load settings
        if(show == TRUE)
            load_settings();

        return 0;
    }

    LRESULT on_apply(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
    {
        save_settings();
        return 0;
    }

    LRESULT on_restore(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
    {
        load_settings();
        return 0;
    }
};

#endif // TRANSLITERATOR_PAGE_IMPL_H
