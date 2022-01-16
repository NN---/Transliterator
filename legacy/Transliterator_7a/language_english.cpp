#include "stdafx.hpp"
#include "resource.hpp"
#include "language.hpp"

const array<
    language::id_text_type,
    language::text_size
> language::english_text =
{
    id_text_type(IDOK,                        _T("OK")),
    id_text_type(IDCANCEL,                    _T("Cancel")),
    id_text_type(IDR_TRANSLITERATOR,          _T("Transliterator")),
    id_text_type(IDD_OPTIONS_GENERAL,         _T("Options - General")),
    id_text_type(IDD_OPTIONS_VIEW,            _T("Options - View")),
    id_text_type(IDD_OPTIONS_HOTKEYS,         _T("Options - Hot Keys")),
    id_text_type(IDD_TOOLS_FILES_TRANSLATION, _T("Tools - Files Translation")),
    id_text_type(IDD_HELP_USAGE,              _T("Help - Usage")),
    id_text_type(IDD_HELP_ABOUT,              _T("Help - About")),
    id_text_type(IDC_CMBSAVETEXT,             _T("Don't save\nSave")),
    id_text_type(IDC_GRPSAVETEXT,             _T("Save Text")),
    id_text_type(IDC_GRPLANGUAGE,             _T("Language")),
    id_text_type(IDC_CMBLANGUAGE,             _T("English")),
    id_text_type(IDC_CMBSTARTUP,              _T("Don't load\nLoad shown\nLoad hidden")),
    id_text_type(IDC_GRPSTARTUP,              _T("StartUp")),
    id_text_type(IDC_BTNAPPLY,                _T("Apply")),
    id_text_type(IDC_BTNRESTORE,              _T("Restore")),
    id_text_type(IDC_GRPCONTROLS,             _T("Controls")),
    id_text_type(IDC_GRPPLACEMENT,            _T("Placement")),
    id_text_type(IDC_CHKTASKBAR,              _T("Task Bar")),
    id_text_type(IDC_CHKTRAY,                 _T("Tray")),
    id_text_type(IDC_CMBPLACEMENT,            _T("Normal\nOn Top\nOn Bottom")),
    id_text_type(IDC_CHKWRAPTEXT,             _T("Wrap Text")),
    id_text_type(IDC_CHKSCROLLTEXT,           _T("Scroll Text")),
    id_text_type(IDC_CHKSWITCHCONTROLS,       _T("Switch Controls")),
    id_text_type(ID_FILE_EXIT,                _T("Exit")),
    id_text_type(ID_FILE_OPEN_TOP,            _T("Open to top...")),
    id_text_type(ID_FILE_OPEN_BOTTOM,         _T("Open to bottom...")),
    id_text_type(ID_FILE_SAVE_TOP,            _T("Save top...")),
    id_text_type(ID_FILE_SAVE_BOTTOM,         _T("Save bottom...")),
    id_text_type(ID_APP_EXIT,                 _T("Exit\tAlt+F4")),
    id_text_type(ID_EDIT_UNDO,                _T("Undo\tCtrl+Z")),
    id_text_type(ID_EDIT_REDO,                _T("Redo\tCtrl+Y")),
    id_text_type(ID_EDIT_CUT,                 _T("Cut\tCtrl+X")),
    id_text_type(ID_EDIT_COPY,                _T("Copy\tCtrl+C")),
    id_text_type(ID_EDIT_PASTE,               _T("Paste\tCtrl+V")),
    id_text_type(ID_EDIT_CLEAR,               _T("Clear\tDel")),
    id_text_type(ID_EDIT_CLEAR_ALL,           _T("Clear All")),
    id_text_type(ID_EDIT_SELECT_ALL,          _T("Select All\tCtrl+A")),
    id_text_type(ID_OPTIONS_GENERAL,          _T("General")),
    id_text_type(ID_OPTIONS_VIEW,             _T("View")),
    id_text_type(ID_OPTIONS_HOTKEYS,          _T("Hot Keys")),
    id_text_type(ID_TOOLS_FILES_TRANSLATION,  _T("Files Translation")),
    id_text_type(ID_HELP_USAGE,               _T("Usage")),    
    id_text_type(ID_HELP_ABOUT,               _T("About")),    
};

const array<
    language::id_text_type,
    language::other_size
> language::english_other =
{
    id_text_type(IDR_TRANSLITERATOR, _T("File\n")
                                     _T("Edit\n")
                                     _T("Profile\n")
                                     _T("Options\n")
                                     _T("Tools\n")
                                     _T("Help\n"))
};
