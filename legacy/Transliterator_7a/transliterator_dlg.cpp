#include "stdafx.hpp"
#include "resource.hpp"
#include "settings.hpp"
#include "profiles.hpp"
#include "settings_saver.hpp"
#include "profile_page.hpp"
#include "options_general_page.hpp"
#include "options_view_page.hpp"
#include "options_hotkeys_page.hpp"
#include "tools_files_translation_page.hpp"
#include "help_usage_page.hpp"
#include "help_about_page.hpp"
#include "transliterator_dlg.hpp"

const LONG transliterator_dlg::s_right_size = 110;

transliterator_dlg::transliterator_dlg() : m_page(0)
{
}

BOOL transliterator_dlg::OnIdle()
{
    if(m_page == page_profile)
    {
        CRichEditCtrl re = ::GetFocus();
        if(re.IsWindow() == TRUE)
        {
            // Selection
            BOOL selection = re.GetSelectionType() != SEL_EMPTY ? TRUE : FALSE;
            
            // Text        
            BOOL text = re.GetTextLength() != 0 ? TRUE : FALSE;

            UIEnable(ID_EDIT_UNDO, re.CanUndo());
            UIEnable(ID_EDIT_REDO, re.CanRedo());
            UIEnable(ID_EDIT_CUT, selection);
            UIEnable(ID_EDIT_COPY, selection);
            UIEnable(ID_EDIT_PASTE, re.CanPaste());
            UIEnable(ID_EDIT_SELECT_ALL, text);
            UIEnable(ID_EDIT_CLEAR, selection);
            UIEnable(ID_EDIT_CLEAR_ALL, text);
        }
    }
    else // Other window
    {
		NN_UPTO_TL(i, (ID_EDIT_CLEAR)(ID_EDIT_REDO + 1))
            UIEnable(i, FALSE);
    }

    // Pages
    // Clear all
	NN_UPTO_TL(i, (ID_PROFILE_FIRST)(ID_HELP_ABOUT + 1))
        UISetCheck(i, FALSE);
    // Check active
    if(m_page == page_profile)
        UISetCheck(ID_PROFILE_FIRST + settings::instance().m_profile,
                   TRUE);
    else
        // -1, because profile is 0
        UISetCheck(ID_OPTIONS_GENERAL + m_page - 1, TRUE);

    return FALSE;
}

void transliterator_dlg::dialog_lang_language_changed()
{
    // Update pages
    NN_FOREACH(pages_type::iterator, it, m_pages)
        it->update_language_i();

    // Update caption
    update_caption();
}

void transliterator_dlg::init_size()
{
    // Minimum size
    CRect rect;
    GetWindowRect(&rect);
        
    m_min_size = rect.Size();
}

void transliterator_dlg::update_caption()
{
    static const lang_tstring separator(_T(" - "));

    // Load caption
    lang_tstring caption;
    load_string_ex(_AtlBaseModule.GetResourceInstance(),
                   IDR_TRANSLITERATOR,
                   caption,
                   nn::default_language::get());

    // Set text
    caption += separator;
    caption += m_pages[m_page].caption();
    SetWindowText(caption.c_str());
}

void transliterator_dlg::init_pages()
{
    // Create parts
    m_pages.push_back(new profile_page());
    m_pages.push_back(new options_general_page());
    m_pages.push_back(new options_view_page());
    m_pages.push_back(new options_hotkeys_page());
    m_pages.push_back(new tools_files_translation_page());
    m_pages.push_back(new help_usage_page());
    m_pages.push_back(new help_about_page());

    NN_FOREACH(pages_type::iterator, it, m_pages)
        it->create(m_hWnd);
}

void transliterator_dlg::update_layout()
{
    // Resize parts
    CRect rect;
    GetClientRect(&rect);

    NN_FOREACH(pages_type::iterator, it, m_pages)
        it->get_base().MoveWindow(&rect);
}

void transliterator_dlg::init_profile()
{
    static const tstring ctrl(_T("\tCtrl+"));

    CMenuHandle profile_menu(
        CMenuHandle(GetMenu()).GetSubMenu(profile_menu_position));

    // Remove dummy item
    profile_menu.DeleteMenu(0, MF_BYPOSITION);

    NN_UPTO_T(i, profiles::instance().get_profiles_count())
    {
        // Add menu item
        profile_menu.AppendMenu(MF_BYCOMMAND, ID_PROFILE_FIRST + i);

        // Prepare string
        tstring menu_string;
        convert(profiles::instance().get_profile(i).m_profile_name, menu_string);

        if(i < profile_menu_count)
        {
            menu_string += ctrl;
            menu_string += (i == 9 ? _T('0') : _T('1') + static_cast<TCHAR>(i));
        }

        // Update translations
        NN_FOREACH(translations::lang_to_translation::iterator,
                    it,
                    translations::text())
            it->second[static_cast<size_t>(ID_PROFILE_FIRST + i)] = menu_string;
    }
}

void transliterator_dlg::init_accelerator()
{
    // Set Accelerators
    set_accelerator(AtlLoadAccelerators(IDR_TRANSLITERATOR));
}

void transliterator_dlg::close()
{
    // Destroy parts
    // Update parts settings
    NN_FOREACH(pages_type::iterator, it, m_pages)
        it->destroy_window();

    // Save settings
    settings_saver::instance().save();

    // Destroy window
    DestroyWindow();
    ::PostQuitMessage(0);
}

void transliterator_dlg::set_page(size_t page)
{
    if(m_page == page)
        return;
    
    // Hide
    m_pages[m_page].get_base().ShowWindow(SW_HIDE);

    // Show
    m_page = page;
    m_pages[m_page].get_base().ShowWindow(SW_SHOW);

    // Update caption
    update_caption();
}

// Message
LRESULT transliterator_dlg::on_close(void)
{
    close();
    return 0;
}

LRESULT transliterator_dlg::on_get_min_max_info(LPMINMAXINFO min_max_info)
{
    min_max_info->ptMinTrackSize = m_min_size;

    return 0;
}

LRESULT transliterator_dlg::on_hot_key(int /*id*/, UINT /*flags*/, UINT /*vk*/)
{

    return 0;
}

LRESULT transliterator_dlg::on_init_dialog(HWND /*wnd_focus*/, LPARAM /*lparam*/)
{
    // Load menu
    SetMenu(AtlLoadMenu(IDR_TRANSLITERATOR));

    // Minimum size
    init_size();

    // Icon
    dialog_icon_init(IDR_TRANSLITERATOR);

    // Pages
    init_pages();

    // Profile
    init_profile();

    // Accelerator
    init_accelerator();

    // Language
    dialog_lang_init();

    // Show profile part
    // Set other page so set_page will show the needed page
    m_page = page_options_general;
    set_page(page_profile);

    // UpdateUI
    UIAddChildWindowContainer(m_hWnd);

    return 0;
}


LRESULT transliterator_dlg::on_size(UINT /*state*/, CSize /*size*/)
{
    update_layout();

    return 0;
}

LRESULT transliterator_dlg::on_sys_command(UINT cmd, CPoint /*pt*/)
{
    SetMsgHandled(FALSE);

    if(cmd == SC_CLOSE)
        close();

    return 0;
}

LRESULT transliterator_dlg::on_query_end_session(UINT /*reserved*/, UINT /*logoff_option*/)
{

    return TRUE;
}

LRESULT transliterator_dlg::on_file_open_save(WORD /*notify_code*/, WORD id, HWND /*wnd_control*/)
{
    // Refer to page_profile
    m_pages[page_profile].open_save(id == ID_FILE_OPEN_TOP ||
                                    id == ID_FILE_OPEN_BOTTOM,
                                    id == ID_FILE_OPEN_TOP ||
                                    id == ID_FILE_SAVE_TOP);

    return 0;
}

LRESULT transliterator_dlg::on_app_exit(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
{
    close();
    return 0;
}

LRESULT transliterator_dlg::on_edit_commands(WORD /*notify_code*/, WORD id, HWND /*wnd_control*/)
{
    if(m_page != page_profile)
        return 0;
    
    CRichEditCtrl re = ::GetFocus();

    switch(id)
    {
        case ID_EDIT_UNDO: re.Undo(); break;
        case ID_EDIT_REDO: re.Redo(); break;
        case ID_EDIT_CUT: re.Cut(); break;
        case ID_EDIT_COPY: re.Copy(); break;
        case ID_EDIT_PASTE: re.Paste(); break;
        case ID_EDIT_SELECT_ALL: re.SetSelAll(); break;
        case ID_EDIT_CLEAR_ALL: re.SetSel(0, -1);
        case ID_EDIT_CLEAR: re.Clear(); break;
    }

    return 0;
}

LRESULT transliterator_dlg::on_profile(WORD /*notify_code*/, WORD id, HWND /*wnd_control*/)
{  
    WORD nprofile = id - ID_PROFILE_FIRST;
    
    if(m_page != page_profile ||
      (nprofile < profiles::instance().get_profiles_count()) && // Check for accelerator
      (nprofile != settings::instance().m_profile))
    {
        // Change page
        set_page(page_profile);
        settings::instance().m_profile = nprofile;

        // Update profile
        NN_FOREACH(pages_type::iterator, it, m_pages)
            it->profile_changed();

        // Profile has changed update caption
        update_caption();
    }

    return 0;
}

LRESULT transliterator_dlg::on_options(WORD /*notify_code*/, WORD id, HWND /*wnd_control*/)
{
    set_page(id - ID_OPTIONS_GENERAL + page_options_general);

    return 0;
}

LRESULT transliterator_dlg::on_tools_files_translation(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
{
    set_page(page_files_translation);

    return 0;
}

LRESULT transliterator_dlg::on_help_usage(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
{
    set_page(page_usage);

    return 0;
}

LRESULT transliterator_dlg::on_help_about(WORD /*notify_code*/, WORD /*id*/, HWND /*wnd_control*/)
{
    set_page(page_about);

    return 0;
}
