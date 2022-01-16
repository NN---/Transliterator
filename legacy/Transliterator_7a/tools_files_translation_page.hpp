#ifndef TRANSLITERATOR_FILES_TRANSLATION_PAGE_H
#define TRANSLITERATOR_FILES_TRANSLATION_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"

class tools_files_translation_page : public page_impl<tools_files_translation_page>
{
public:
    enum { IDD = IDD_TOOLS_FILES_TRANSLATION };

    // Message map
    BEGIN_MSG_MAP(tools_files_translation_page)
        MSG_WM_INITDIALOG(on_init_dialog)

        CHAIN_MSG_MAP(page_impl<tools_files_translation_page>)
    END_MSG_MAP()

private:
    LRESULT on_init_dialog(HWND wnd_focus, LPARAM lparam);
};

#endif // TRANSLITERATOR_FILES_TRANSLATION_PAGE_H
