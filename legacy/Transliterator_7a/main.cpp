#include "stdafx.hpp"
#include "resource.hpp"
#include "language.hpp"
#include "settings_saver.hpp"
#include "transliterator_dlg.hpp"

void run()
{
    CMessageLoop the_loop;
    _Module.AddMessageLoop(&the_loop);
    
    transliterator_dlg dlg;
    dlg.Create(GetDesktopWindow());
    dlg.ShowWindow(SW_SHOW);
    
    the_loop.Run();

    _Module.RemoveMessageLoop();
}

int WINAPI _tWinMain(HINSTANCE instance,
                     HINSTANCE /*prev_instance*/,
                     LPTSTR /*cmd_line*/,
                     int /*cmd_show*/)
{
    // Initialize RichEdit
    LoadLibrary(CRichEditCtrl::GetLibraryName());

    // Initialize common controls
    AtlInitCommonControls(0xFF);

    struct coinitialize
    {
        coinitialize() { ::CoInitialize(NULL); }
        ~coinitialize() {:: CoUninitialize(); }
    } coinitialize_;

    struct module_init
    {
        module_init(HINSTANCE instance) { _Module.Init(NULL, instance); }
        ~module_init() { _Module.Term(); }
    } module_init_(instance);

    // Init language translation
    language::init();

    // Load settings
    if(settings_saver::instance().load())
        run();

    return 0;
}
