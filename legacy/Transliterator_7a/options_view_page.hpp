#ifndef TRANSLITERATOR_OPTIONS_VIEW_PAGE_H
#define TRANSLITERATOR_OPTIONS_VIEW_PAGE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "page_impl.hpp"
#include "settings.hpp"

class options_view_page : public page_impl<options_view_page>
{
public:
    enum { IDD = IDD_OPTIONS_VIEW };

    BEGIN_DDX_MAP(options_view_page)
        DDX_CHECK(IDC_CHKTASKBAR, settings::instance().m_task_bar)
        DDX_CHECK(IDC_CHKTRAY, settings::instance().m_tray)
        DDX_COMBO_SEL(IDC_CMBPLACEMENT, settings::instance().m_placement)
        DDX_CHECK(IDC_CHKWRAPTEXT, settings::instance().m_wrap_text)
        DDX_CHECK(IDC_CHKSCROLLTEXT, settings::instance().m_scroll_text)
        DDX_CHECK(IDC_CHKSWITCHCONTROLS, settings::instance().m_switch_controls)
    END_DDX_MAP()
};

#endif // TRANSLITERATOR_OPTIONS_VIEW_PAGE_H
