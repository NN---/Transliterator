#ifndef TRANSLITERATOR_OPTIONS_GENERAL_PAGE_H
#define TRANSLITERATOR_OPTIONS_GENERAL_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"
#include "settings.hpp"

class options_general_page : public page_impl<options_general_page>
{
public:
    enum { IDD = IDD_OPTIONS_GENERAL };

    // DDX map
    BEGIN_DDX_MAP(options_general_page)
        DDX_COMBO_SEL(IDC_CMBLANGUAGE, settings::instance().m_language)
        DDX_COMBO_SEL(IDC_CMBSTARTUP, settings::instance().m_startup)
        DDX_COMBO_SEL(IDC_CMBSAVETEXT, settings::instance().m_save_text)
    END_DDX_MAP()
};

#endif // TRANSLITERATOR_OPTIONS_GENERAL_PAGE_H
