#ifndef __TYPES_H__
#define __TYPES_H__

// Translate
#define LANG_COUNT 6
#define LANGMAP_COUNT 150
typedef NN::StaticArray<char,LANG_COUNT> LangString;
typedef LangString::Traits LangStringTraits;
typedef NN::StaticArray<wchar_t,LANG_COUNT> LangStringW;
typedef LangStringW::Traits LangStringTraitsW;
typedef NN::Tuple<LangString,LangString,Translate::LangTranslate> LangType;
typedef NN::Tuple<LangStringW,LangStringW,Translate::LangTranslate> LangTypeW;
typedef NN::StaticArrayMap<LangType,LANGMAP_COUNT> LangMap;

// Ignore
#define IGNORE_COUNT 30
#define IGNOREMAP_COUNT 50
typedef NN::StaticArray<char,IGNORE_COUNT> IgnoreString;
typedef NN::Tuple<IgnoreString,Translate::LangTranslate> IgnoreType;
typedef NN::StaticArrayMap<IgnoreType,IGNOREMAP_COUNT> IgnoreMap;

#endif // __TYPES_H__