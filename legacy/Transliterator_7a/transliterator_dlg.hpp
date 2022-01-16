#ifndef TRANSLITERATOR_TRANSLITERATOR_DLG_H
#define TRANSLITERATOR_TRANSLITERATOR_DLG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"
#include "i_dialog_impl_allocator.hpp"

class transliterator_dlg : public CDialogImpl<transliterator_dlg>,
                           public CIdleHandler,
                           public CUpdateUI<transliterator_dlg>,
                           public dialog_icon<transliterator_dlg>,
                           public dialog_lang<transliterator_dlg>,
                           public message_filter_dlg_accel<transliterator_dlg>
{
public:
    enum { IDD = IDR_TRANSLITERATOR };

    // Constructor
    transliterator_dlg();

    // Overrides
    virtual BOOL OnIdle();

    void dialog_lang_language_changed();

    POINT GetButtonPos(int index)
	{
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		rcWnd.OffsetRect(-rcWnd.TopLeft());

		rcWnd.DeflateRect(2, 2);

		//locate the top right base point
		CPoint	pt(rcWnd.right, rcWnd.top);
		pt.x -= 20;
		pt.y += 2;
		switch (index)
		{
		case 0://autohide pin
			pt.x -= 16*3;
			break;
		}

		return pt;
	}

    // UpdateUI map
    BEGIN_UPDATE_UI_MAP(transliterator_dlg)
        // File
        // Edit
        UPDATE_ELEMENT(ID_EDIT_UNDO, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_REDO, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_CUT, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_COPY, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_PASTE, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_CLEAR, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_CLEAR_ALL, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_EDIT_SELECT_ALL, UPDUI_MENUPOPUP)
        // Profile
        UPDATE_ELEMENT(ID_PROFILE_FIRST, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 1, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 2, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 3, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 4, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 5, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 6, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 7, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 8, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 9, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 10, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 11, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 12, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 13, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 14, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 15, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 16, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 17, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_FIRST + 18, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_PROFILE_LAST, UPDUI_MENUPOPUP)
        // Options
        UPDATE_ELEMENT(ID_OPTIONS_GENERAL, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_OPTIONS_VIEW, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_OPTIONS_HOTKEYS, UPDUI_MENUPOPUP)
        // Tools
        UPDATE_ELEMENT(ID_TOOLS_FILES_TRANSLATION, UPDUI_MENUPOPUP)
        // Help
        UPDATE_ELEMENT(ID_HELP_USAGE, UPDUI_MENUPOPUP)
        UPDATE_ELEMENT(ID_HELP_ABOUT, UPDUI_MENUPOPUP)
    END_UPDATE_UI_MAP()

    // Message map
    BEGIN_MSG_MAP(transliterator_dlg)
        NN_MSGFILTER()
        NN_IDLE()

        // Window Message
        MSG_WM_CLOSE(on_close)
        MSG_WM_GETMINMAXINFO(on_get_min_max_info)
        MSG_WM_HOTKEY(on_hot_key)
        MSG_WM_INITDIALOG(on_init_dialog)
        MSG_WM_SIZE(on_size)
        MSG_WM_SYSCOMMAND(on_sys_command)
        MSG_WM_QUERYENDSESSION(on_query_end_session)
                
        // Command
#pragma warning(push)
#pragma warning(disable:4244) // 'argument' : conversion from 'int' to 'WORD', possible loss of data
        COMMAND_ID_HANDLER_EX(ID_FILE_OPEN_TOP, on_file_open_save)
        COMMAND_ID_HANDLER_EX(ID_FILE_OPEN_BOTTOM, on_file_open_save)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE_TOP, on_file_open_save)
        COMMAND_ID_HANDLER_EX(ID_FILE_SAVE_BOTTOM, on_file_open_save)
        COMMAND_ID_HANDLER_EX(ID_APP_EXIT, on_app_exit)
        COMMAND_RANGE_HANDLER_EX(ID_EDIT_CLEAR, ID_EDIT_REDO, on_edit_commands)      
        COMMAND_RANGE_HANDLER_EX(ID_PROFILE_FIRST, ID_PROFILE_LAST, on_profile)
        COMMAND_RANGE_HANDLER_EX(ID_OPTIONS_GENERAL, ID_OPTIONS_HOTKEYS, on_options)
        COMMAND_ID_HANDLER_EX(ID_TOOLS_FILES_TRANSLATION, on_tools_files_translation)
        COMMAND_ID_HANDLER_EX(ID_HELP_USAGE, on_help_usage)
        COMMAND_ID_HANDLER_EX(ID_HELP_ABOUT, on_help_about)
#pragma warning(pop)

        // Chain Message Map base
        CHAIN_MSG_MAP(CUpdateUI<transliterator_dlg>)
    END_MSG_MAP()

private:
    // Functions
    // Init size
    void init_size();

    // Caption
    void update_caption();

    // Parts
    void init_pages();

    // Layout
    void update_layout();

    // Profile
    void init_profile();

    // Accelerator
    void init_accelerator();
    
    // Close
    void close();

    // Set page
    void set_page(size_t page);

    // Message functions
    LRESULT on_close(void);
    LRESULT on_get_min_max_info(LPMINMAXINFO min_max_info);
    LRESULT on_hot_key(int id, UINT flags, UINT vk);
    LRESULT on_init_dialog(HWND wnd_focus, LPARAM lparam);
    LRESULT on_size(UINT state, CSize size);
    LRESULT on_sys_command(UINT cmd, CPoint pt);
    LRESULT on_query_end_session(UINT reserved, UINT logoff_option);

    LRESULT on_file_open_save(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_app_exit(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_edit_commands(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_profile(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_options(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_tools_files_translation(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_help_usage(WORD notify_code, WORD id, HWND wnd_control);
    LRESULT on_help_about(WORD notify_code, WORD id, HWND wnd_control);

    // Variables
    // Menu position
    enum
    {
        file_menu_position,
        edit_menu_position,
        profile_menu_position,
        options_menu_position,
        help_menu_position
    };
    
    // Max items for accelerators
    static const size_t profile_menu_count = 10;
    
    // Layout
    
    // Size
    CPoint m_min_size;
    static const LONG s_right_size;

    // Pages rect
    CRect m_pages_rect;
    
    // Pages
    enum
    {
        page_profile,
        page_options_general,
        page_options_view,
        page_options_hotkeys,
        page_files_translation,
        page_usage,
        page_about
    };

    size_t m_page;
    
    typedef ptr_vector<i_dialog_impl<CWindow, i_page_impl>,
                       i_dialog_impl_clone_allocator
    > pages_type;

    pages_type m_pages;   
};

#endif // TRANSLITERATOR_TRANSLITERATOR_DLG_H
