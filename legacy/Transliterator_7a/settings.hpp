#ifndef TRANSLITERATOR_SETTINGS_H
#define TRANSLITERATOR_SETTINGS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "profile.hpp"
#include "language.hpp"

struct settings
{
    static settings& instance();

    void reset();

    // Window Placement
    WINDOWPLACEMENT m_window_placement;

    // Profile details
    bool m_profile_details;

    // Current profile
    size_t m_profile;

    // Languages
    enum languages
    {
        language_english,
        language_russian,
        language_translit,
        language_count
    };
    int m_language;

    // Start Up
    enum startup
    {
        startup_no,
        startup_shown,
        startup_hidden
    };
    int m_startup;

    // Save Text
    enum save_text
    {
        save_text_no,
        save_text_save
    };
    int m_save_text;

    // Task Bar
    BOOL m_task_bar;

    // Tray
    BOOL m_tray;

    // Placement
    enum placement
    {
        placement_normal,
        placement_top,
        placement_bottom,
    };
    int m_placement;

    // Wrap Text
    BOOL m_wrap_text;

    // Scroll Text
    BOOL m_scroll_text;

    // Switch Controls
    BOOL m_switch_controls;
};

#endif // TRANSLITERATOR_SETTINGS_H
