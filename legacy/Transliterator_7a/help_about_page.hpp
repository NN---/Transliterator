#ifndef TRANSLITERATOR_ABOUT_PAGE_H
#define TRANSLITERATOR_ABOUT_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"

class help_about_page : public page_impl<help_about_page>
{
public:
    enum { IDD = IDD_HELP_ABOUT };

    // Message map
    BEGIN_MSG_MAP(help_about_page)
        CHAIN_MSG_MAP(page_impl<help_about_page>)
    END_MSG_MAP()
};

#endif // TRANSLITERATOR_ABOUT_PAGE_H
