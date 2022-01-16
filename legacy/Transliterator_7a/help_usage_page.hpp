#ifndef TRANSLITERATOR_USAGE_PAGE_H
#define TRANSLITERATOR_USAGE_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"

class help_usage_page : public page_impl<help_usage_page>
{
public:
    enum { IDD = IDD_HELP_USAGE };

    // Message map
    BEGIN_MSG_MAP(using_page)
        CHAIN_MSG_MAP(page_impl<help_usage_page>)
    END_MSG_MAP()
};

#endif // TRANSLITERATOR_USAGE_PAGE_H
