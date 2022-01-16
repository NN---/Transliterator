#ifndef TRANSLITERATOR_SETTINGS_SAVER_H
#define TRANSLITERATOR_SETTINGS_SAVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "types.hpp"
#include "language.hpp"

class settings_saver
{
public:
    settings_saver();

    static settings_saver& instance();

    // Load values
    bool load();

    // Save values
    void save();

private:
    void load_settings();
    void load_text();
    void load_profiles();

    void save_settings();
    void save_text();

    // HKEY_CURRENT_USER
    static const HKEY s_root_key;

    // s_root_key\Software\NN
    CRegKey m_root_key;

    // m_root_key\Transliterator\{Version}
    CRegKey m_program_key;

    // Strings
    static const lang_tstring s_root_key_path;
    static const lang_tstring s_program_key_path;
    static const lang_tstring s_run_path;

    // Values
    static const lang_tstring s_settings_value;
    static const array<lang_tstring, language::size> s_text_value;
    static const lang_tstring s_run_value;

    // More
    static const lang_tstring s_load_hidden;
};

#endif // TRANSLITERATOR_SETTINGS_SAVER_H
