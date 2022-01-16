#ifndef __NN_Wnd_String__
#define __NN_Wnd_String__

// код должен работать в С и в С++
#ifdef __cplusplus
#define NN_INLINE inline
#else
#define NN_INLINE
#endif // __cplusplus

NN_INLINE HINSTANCE NNGetModuleInstance()
{
#if defined(_AFX)
    return AfxGetInstanceHandle();
#elif defined(_ATL)
    #if _ATL_VER>=0x700
        return ATL::_AtlBaseModule.GetModuleInstance();
    #else
        return _Module.GetModuleInstance();
    #endif // _ATL_VER
#elif defined(_WINDOWS)
    return ::GetModuleHandle(NULL);
#else
    return NULL;
#endif
}

NN_INLINE HINSTANCE NNGetResourceInstance()
{
#if defined(_AFX)
    return AfxGetResourceInstance();
#elif defined(_ATL)
    #if _ATL_VER>=0x700
        return ATL::_AtlBaseModule.GetResourceInstance();
    #else
        return _Module.GetResourceInstance();
    #endif // _ATL_VER
#elif defined(_WINDOWS)
    return ::GetModuleHandle(NULL);
#else
    return NULL;
#endif
}

// Use Shell functions
#ifdef NN_USE_SHL_FOR_STRING
#define NN_USE_SHL_FOR_STRINGA
#define NN_USE_SHL_FOR_STRINGW
#endif // NN_USE_SHL_FOR_STRING

// Use Windows functions
#ifdef NN_USE_WIN_FOR_STRING
#define NN_USE_WIN_FOR_STRINGA
#define NN_USE_WIN_FOR_STRINGW
#endif // NN_USE_WIN_FOR_STRING

#if defined(NN_USE_SHL_FOR_STRINGA) && defined(NN_USE_WIN_FOR_STRINGA)
#error You cannot define NN_USE_SHL_FOR_STRINGA and NN_USE_WIN_FOR_STRINGA
#endif // NN_USE_SHL_FOR_STRINGA && NN_USE_WIN_FOR_STRINGA

#if defined(NN_USE_SHL_FOR_STRINGW) && defined(NN_USE_WIN_FOR_STRINGW)
#error You cannot define NN_USE_SHL_FOR_STRINGW and NN_USE_WIN_FOR_STRINGW
#endif // NN_USE_SHL_FOR_STRINGW && NN_USE_WIN_FOR_STRINGW

// Default Windows function
#if !defined(NN_USE_SHL_FOR_STRINGA) && !defined(NN_USE_WIN_FOR_STRINGA)
#define NN_USE_WIN_FOR_STRINGA
#endif // !NN_USE_SHL_FOR_STRINGA && !NN_USE_WIN_FOR_STRINGA

// Default Windows function
#if !defined(NN_USE_SHL_FOR_STRINGW) && !defined(NN_USE_WIN_FOR_STRINGW)
#define NN_USE_WIN_FOR_STRINGW
#endif // !NN_USE_SHL_FOR_STRINGW && !NN_USE_WIN_FOR_STRINGW

#include <string>

namespace NN
{

// wnd_char_traits_base - char,wchar_t
template<typename T>
struct wnd_char_traits_base : public std::char_traits<T>
{
private:
    static int cmp(const char_type& _Left, const char_type& _Right);
public:
    static bool eq(const char_type& _Left, const char_type& _Right)
    { return cmp(_Left,_Right)==0; }

    static bool lt(const char_type& _Left, const char_type& _Right)
    { return cmp(_Left,_Right)<0; }

    static int compare(const char_type* _First1, const char_type* _First2,
        std::size_t _Count)
    {
        for(; 0 < _Count; --_Count, ++_First1, ++_First2)
        {
            int icmp = cmp(*_First1,*_First2);
            if(icmp)
                return icmp;
        }
        return (0);
    }
};

template<>
inline int wnd_char_traits_base<char>::cmp(
    const typename wnd_char_traits_base<char>::char_type& _Left,
    const typename wnd_char_traits_base<char>::char_type& _Right)
{
    const wnd_char_traits_base<char>::char_type left[2]={_Left};
    const wnd_char_traits_base<char>::char_type right[2]={_Right};

#ifdef NN_USE_WIN_FOR_STRINGA
    return ::lstrcmpA(left,right);
#else
    return ::StrCmpA(left,right);
#endif // NN_USE_WIN_FOR_STRINGA
}

template<>
inline int wnd_char_traits_base<wchar_t>::cmp(
    const typename wnd_char_traits_base<wchar_t>::char_type& _Left,
    const typename wnd_char_traits_base<wchar_t>::char_type& _Right)
{
    const wnd_char_traits_base<wchar_t>::char_type left[2]={_Left};
    const wnd_char_traits_base<wchar_t>::char_type right[2]={_Right};

#ifdef NN_USE_WIN_FOR_STRINGW
    return ::lstrcmpW(left,right);
#else
    return ::StrCmpW(left,right);
#endif // NN_USE_WIN_FOR_STRINGW
}

// wnd_char_traits
template<typename T>
struct wnd_char_traits : public std::char_traits<T>
{};

template<>
struct wnd_char_traits<char> : public wnd_char_traits_base<char>
{};

template<>
struct wnd_char_traits<wchar_t> : public wnd_char_traits_base<wchar_t>
{};

typedef std::basic_string<
        char,
        wnd_char_traits<char>,
        std::allocator<char>
    >wnd_string;

typedef std::basic_string<
        wchar_t,
        wnd_char_traits<wchar_t>,
        std::allocator<wchar_t>
    >wnd_wstring;

#ifndef NN_NO_WNDSTRING_COMPARE

// wnd_string - std::string
inline bool operator==(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())==0; }

inline bool operator!=(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())!=0; }

inline bool operator>(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())>0; }

inline bool operator>=(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())>=0; }

inline bool operator<(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())<0; }

inline bool operator<=(const wnd_string& left,
                const std::string& right)
{ return left.compare(right.c_str())<=0; }

// std::string - wnd_string
inline bool operator==(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())==0; }

inline bool operator!=(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())!=0; }

inline bool operator>(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())>0; }

inline bool operator>=(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())>=0; }

inline bool operator<(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())<0; }

inline bool operator<=(const std::string& left,
                const wnd_string& right)
{ return right.compare(left.c_str())<=0; }

// wnd_wstring - std::wstring
inline bool operator==(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())==0; }

inline bool operator!=(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())!=0; }

inline bool operator>(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())>0; }

inline bool operator>=(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())>=0; }

inline bool operator<(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())<0; }

inline bool operator<=(const wnd_wstring& left,
                const std::wstring& right)
{ return left.compare(right.c_str())<=0; }

// std::wstring - wnd_wstring
inline bool operator==(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())==0; }

inline bool operator!=(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())!=0; }

inline bool operator>(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())>0; }

inline bool operator>=(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())>=0; }

inline bool operator<(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())<0; }

inline bool operator<=(const std::wstring& left,
                const wnd_wstring& right)
{ return right.compare(left.c_str())<=0; }

#endif // NN_NO_WNDSTRING_COMPARE

}

#ifndef NN_NO_WNDLOADSTRING

#include <vector>
#include <nn/instance.h> // функции поста выше

namespace NN
{

// WndLoadString_Traits
template<typename T>
struct WndLoadString_Traits;

template<>
struct WndLoadString_Traits<CHAR>
{
    static int LS(HINSTANCE hInstance,UINT uID,CHAR* lpBuffer,int nBufferMax)
    { return ::LoadStringA(hInstance,uID,lpBuffer,nBufferMax); }
};

template<>
struct WndLoadString_Traits<WCHAR>
{
    static int LS(HINSTANCE hInstance,UINT uID,WCHAR* lpBuffer,int nBufferMax)
    { return ::LoadStringW(hInstance,uID,lpBuffer,nBufferMax); }
};

// WndLoadString
template<typename TChar,typename TString>
inline int WndLoadStringT(HINSTANCE hInstance,UINT uID,TString& str)
{
    if(!hInstance)
        hInstance = NNGetResourceInstance();
    
    size_t buf_size = 256;
    std::vector<TChar> buf(buf_size);
    if(buf.empty())
        return 0;
    
    int len;

    while((len=WndLoadString_Traits<TChar>::LS(
        hInstance,uID,&buf[0],buf_size)) == 
            (int)(buf_size-1))
    {
        buf_size*=2;
        buf.resize(buf_size);
        if(!buf.empty())
            return 0;
    }

    str.assign(&buf[0]);
    return len;
}

template<typename TString>
inline int WndLoadStringA(HINSTANCE hInstance,UINT uID,TString& str)
{ return WndLoadStringT<CHAR,TString>(hInstance,uID,str); }

template<typename TString>
inline int WndLoadStringW(HINSTANCE hInstance,UINT uID,TString& str)
{ return WndLoadStringT<WCHAR,TString>(hInstance,uID,str); }

template<typename TString>
inline int WndLoadString(HINSTANCE hInstance,UINT uID,TString& str)
{
#ifdef UNICODE
    return WndLoadStringW<TString>(hInstance,uID,str);
#else
    return WndLoadStringA<TString>(hInstance,uID,str);
#endif // UNICODE
}

template<typename TString>
inline int WndLoadStringA(UINT uID,TString& str)
{ return WndLoadStringA<TString>(NULL,uID,str); }

template<typename TString>
inline int WndLoadStringW(UINT uID,TString& str)
{ return WndLoadStringW<TString>(NULL,uID,str); }

template<typename TString>
inline int WndLoadString(UINT uID,TString& str)
{
#ifdef UNICODE
    return WndLoadStringW<TString>(ID,str);
#else
    return WndLoadStringA<TString>(uID,str);
#endif // UNICODE
}

}

#endif // NN_NO_WNDLOADSTRING

// wnd_char_traits_impl
template<typename Char, typename Cmp>
struct wnd_char_traits_impl : public std::char_traits<Char>
{
    static bool eq(const char_type& left, const char_type& right)
    {
        return Cmp::cmp(left,right) == 0;
    }

    static bool lt(const char_type& left, const char_type& right)
    {
        return Cmp::cmp(left,right) < 0;
    }

    static int compare(const char_type* first1,
                       const char_type* first2,
                       std::size_t count)
    {
        for(; count > 0; --count, ++first1, ++first2)
        {
            int ret = Cmp::cmp(*first1,*first2);

            if(ret != 0)
                return ret;
        }
        return 0;
    }
};

// wnd_cmp
template<typename Char, bool Windows>
struct wnd_cmp;

template<>
struct wnd_cmp<char, true>
{
    static int cmp(char left, char right)
    {
        char left_cmp[2] = {left, 0};
        char right_cmp[2] = {right, 0};
        
        return ::lstrcmpA(left_cmp, right_cmp);
    }
};

template<>
struct wnd_cmp<wchar_t, true>
{
    static int cmp(wchar_t left, wchar_t right)
    {
        wchar_t left_cmp[2] = {left, 0};
        wchar_t right_cmp[2] = {right, 0};
        
        return ::lstrcmpW(left_cmp, right_cmp);
    }
};

template<>
struct wnd_cmp<char, false>
{
    static int cmp(char left, char right)
    {
        char left_cmp[2] = {left, 0};
        char right_cmp[2] = {right, 0};
        
        return ::StrCmpA(left_cmp, right_cmp);
    }
};

template<>
struct wnd_cmp<wchar_t, false>
{
    static int cmp(wchar_t left, wchar_t right)
    {
        wchar_t left_cmp[2] = {left, 0};
        wchar_t right_cmp[2] = {right, 0};
        
        return ::StrCmpW(left_cmp, right_cmp);
    }
};

// wnd_char_traits_windows
template<typename T>
struct wnd_char_traits_windows :
    public std::char_traits<T>
{
};

template<>
struct wnd_char_traits_windows<char> :
    public wnd_char_traits_impl<char, wnd_cmp<char, true> >
{
};

template<>
struct wnd_char_traits_windows<wchar_t> :
    public wnd_char_traits_impl<wchar_t, wnd_cmp<wchar_t, true> >
{
};

// wnd_char_traits_shell
template<typename T>
struct wnd_char_traits_shell :
    public std::char_traits<T>
{
};

template<>
struct wnd_char_traits_shell<char> :
    public wnd_char_traits_impl<char, wnd_cmp<char, false> >
{
};

template<>
struct wnd_char_traits_shell<wchar_t> :
    public wnd_char_traits_impl<wchar_t, wnd_cmp<wchar_t, false> >
{
};

// Typedef
// String Windows
typedef std::basic_string<
    char,
    wnd_char_traits_windows<char>,
    std::allocator<char>
> wnd_string_windows;

typedef std::basic_string<
    wchar_t,
    wnd_char_traits_windows<wchar_t>,
    std::allocator<wchar_t>
> wnd_wstring_windows;

typedef std::basic_string<
    TCHAR,
    wnd_char_traits_windows<TCHAR>,
    std::allocator<TCHAR>
> wnd_tstring_windows;

// String Shell
typedef std::basic_string<
    char,
    wnd_char_traits_shell<char>,
    std::allocator<char>
> wnd_string_shell;

typedef std::basic_string<
    wchar_t,
    wnd_char_traits_shell<wchar_t>,
    std::allocator<wchar_t>
> wnd_wstring_shell;

typedef std::basic_string<
    TCHAR,
    wnd_char_traits_shell<TCHAR>,
    std::allocator<TCHAR>
> wnd_tstring_shell;

// Define macros for generating code
#define WND_STR_OPERATOR(op, left_type, right_type) \
    inline bool operator##op(const left_type& left, const right_type& right) \
    { \
        return left.compare(right.c_str()) op 0; \
    }

#define WND_STR_COMPARE_IMPL(left_type, right_type) \
    WND_STR_OPERATOR(==, left_type, right_type) \
    WND_STR_OPERATOR(!=, left_type, right_type) \
    WND_STR_OPERATOR(<,  left_type, right_type) \
    WND_STR_OPERATOR(>,  left_type, right_type) \
    WND_STR_OPERATOR(<=, left_type, right_type) \
    WND_STR_OPERATOR(>=, left_type, right_type)

#define WND_STR_COMPARE(left_type, right_type) \
    WND_STR_COMPARE_IMPL(left_type, right_type) \
    WND_STR_COMPARE_IMPL(right_type, left_type)

// Define compare
WND_STR_COMPARE(wnd_string_windows, wnd_string_shell)
WND_STR_COMPARE(wnd_wstring_windows, wnd_wstring_shell)
WND_STR_COMPARE(wnd_string_windows, std::string)
WND_STR_COMPARE(wnd_wstring_windows, std::wstring)
WND_STR_COMPARE(wnd_string_shell, std::string)
WND_STR_COMPARE(wnd_wstring_shell, std::wstring)

// Undefine macros
#undef WND_STR_OPERATOR
#undef WND_STR_COMPARE_IMPL

#endif // __NN_Wnd_String__