#ifndef TRANSLITERATOR_OPTIONS_HOTKEYS_PAGE_H
#define TRANSLITERATOR_OPTIONS_HOTKEYS_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"

class options_hotkeys_page : public page_impl<options_hotkeys_page>
{
public:
    enum { IDD = IDD_OPTIONS_HOTKEYS };

    BEGIN_DDX_MAP(options_hotkeys_page)
    END_DDX_MAP()
};

#endif // TRANSLITERATOR_OPTIONS_HOTKEYS_PAGE_H
