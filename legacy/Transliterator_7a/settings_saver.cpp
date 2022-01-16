#include "stdafx.hpp"
#include "settings_saver.hpp"
#include "settings.hpp"
#include "profiles.hpp"
#include "text.hpp"

// Key
const HKEY settings_saver::s_root_key(HKEY_CURRENT_USER);

const lang_tstring settings_saver::s_root_key_path(_T("Software\\NN"));
const lang_tstring settings_saver::s_program_key_path(_T("Transliterator\\7.0"));
const lang_tstring settings_saver::s_run_path(
    _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));

// Value
const lang_tstring settings_saver::s_settings_value(_T("Settings"));
const array<lang_tstring, language::size> settings_saver::s_text_value =
{
    lang_tstring(_T("Top")),
    lang_tstring(_T("Bottom")),
};
const lang_tstring settings_saver::s_run_value(_T("Transliterator"));

// More
const lang_tstring settings_saver::s_load_hidden(_T(" -h"));

settings_saver::settings_saver()
{
    // Initialize key
    m_root_key.Create(s_root_key, s_root_key_path.c_str());
}

settings_saver& settings_saver::instance()
{
    static settings_saver s;
    return s;
}

bool settings_saver::load()
{
    // Initialize key
    m_program_key.Open(m_root_key, s_program_key_path.c_str());
 
    load_settings();

    // Default language
    default_language::set(language::s_languages[settings::instance().m_language]);

    load_text();
    load_profiles();
    
    return true;
}

void settings_saver::load_settings()
{
    settings& rsettings = settings::instance();

    // Load settings
    if(m_program_key != NULL)
    {
        ULONG settings_size = sizeof(settings);
        LONG res = m_program_key.QueryBinaryValue(s_settings_value.c_str(),
                                                  &rsettings,
                                                  &settings_size);

        // Check result
        if(res == ERROR_SUCCESS && settings_size == sizeof(settings))
            return;
    }

    // Reset
    rsettings.reset();
}

void settings_saver::load_text()
{
    // Load text
    if(m_program_key == NULL ||
       settings::instance().m_save_text == settings::save_text_no)
       return;

    text& rtext = text::instance();
    text::text_type& t = rtext.get_text();

    NN_UPTO_T(i, t.size())
    {
        ULONG text_size = 0;
        // Query size
        if(m_program_key.QueryBinaryValue(s_text_value[i].c_str(),
                                          NULL,
                                          &text_size) != ERROR_SUCCESS)
            continue;

        // Resize
        t[i].resize(text_size / sizeof(lang_char) + 1);

        // Query value
        if(m_program_key.QueryBinaryValue(s_text_value[i].c_str(),
                                          &t[i][0],
                                          &text_size) != ERROR_SUCCESS)
            continue;

        // Set '\0' at the end
        t[i][t[i].size() - 1] = 0;
    }
}

void settings_saver::load_profiles()
{
    // Default profiles.
    profiles::instance().reset();

    // TODO: Load additional profiles
}

void settings_saver::save()
{
    // Prepare registry keys.
    // Delete all values
    m_root_key.RecurseDeleteKey(s_program_key_path.c_str());

    // Create new key
    m_program_key.Create(m_root_key, s_program_key_path.c_str());
    if(m_program_key == NULL)
    {
        //show_error()
        MessageBox(NULL, "Cannot save settings", "Transliterator", MB_OK);
        return;
    }

    save_settings();
    save_text();
}

void settings_saver::save_settings()
{
    settings& rsettings = settings::instance();

    // Set settings
    m_program_key.SetBinaryValue(s_settings_value.c_str(),
                                 &rsettings,
                                 sizeof(settings));

    // Run
    CRegKey run_key;
    run_key.Create(s_root_key, s_run_path.c_str());
    if(run_key == NULL)
        return;
    
    if(rsettings.m_startup == settings::startup_no)
        // Delete if we don't want to load
        run_key.DeleteValue(s_run_value.c_str());
    else
    {
        // Get module path
        array<lang_tchar, MAX_PATH> module_path;
        GetModuleFileName(module_instance(), &module_path[0], module_path.size());

        // Prepare string
        lang_tstring run_value(&module_path[0]);
        if(rsettings.m_startup == settings::startup_hidden)
            run_value += s_load_hidden;

        // Set value
        run_key.SetStringValue(s_run_value.c_str(), run_value.c_str());
    }
}

void settings_saver::save_text()
{
    if(settings::instance().m_save_text == settings::save_text_no)
        return;

    text& rtext = text::instance();
    text::text_type& t = rtext.get_text();

    NN_UPTO_T(i, t.size())
        if(t[i].size() != 0)
            m_program_key.SetBinaryValue(s_text_value[i].c_str(),
                                         &t[i][0],
                                         t[i].size() * sizeof(lang_char));
}
