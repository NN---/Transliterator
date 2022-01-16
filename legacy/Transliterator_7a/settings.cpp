#include "stdafx.hpp"
#include "settings.hpp"

settings& settings::instance()
{
    static settings s;
    return s;
}

void settings::reset()
{
    // Transliterator dialog placement
    static const WINDOWPLACEMENT default_placement =
    {
        sizeof(placement),
        0,
        SW_SHOWNORMAL
    };
    m_window_placement = default_placement;

    // Profile details
    m_profile_details = false;

    // Current profile
    m_profile = 0;

    // Language
    m_language = language_english;

    // StartUp
    // TODO m_startup = startup_hidden;
    m_startup = startup_no;

    // Save Text
    m_save_text = save_text_save;

    // Task Bar
    m_task_bar = true;

    // Tray
    m_tray = true;

    // Placement
    m_placement = placement_normal;

    // Wrap Text
    m_wrap_text = false;

    // Scroll Text
    m_scroll_text = true;

    // Switch Controls
    m_switch_controls = false;
}
