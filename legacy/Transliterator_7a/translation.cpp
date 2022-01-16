#include "stdafx.hpp"
#include "translation.hpp"

namespace translation
{

namespace
{

struct compare_length
{
    template<typename T>
    bool operator()(const T& left, const T& right)
    {
        return left.first.length() < right.first.length();
    }
};

template<typename T>
size_t max_length(const T& c)
{
    return max_element(c.begin(),
                       c.end(),
                       compare_length())->first.length();
}

size_t max_length_translation(const profile& p, direction::type dir)
{                                                       
    return dir == direction::top_to_bottom ?
           max_length(p.m_translation.left) :
           max_length(p.m_translation.right);
}

template<typename Map>
bool translation_impl_(const lang_char*& in,
                       lang_char*& out,
                       const Map& m,
                       size_t max_length)
{
    NN_DOWNFROM_T(length, max_length)
    {
        NN_FOREACH(Map::const_iterator, it, m)
        {
            // Compare
            if(it->first.length() == length &&
                lang_string_traits::compare(in, it->first.c_str(), length) == 0)
            {
                copy(it->second->c_str(),
                     &it->second->c_str()[it->second->length() + 1],
                     out);
                advance(out, it->second->length());
                advance(in, length);

                return true;
            }
        }
    }

    return false;
}

bool translation_impl(const lang_char*& in,
                      lang_char*& out,
                      direction::type dir,
                      const profile& p,
                      size_t max_length)
{
    if(*in == 0)
        return true;

    if(dir == direction::top_to_bottom)
        return translation_impl_(in, out, p.m_translation.left, max_length);
    else
        return translation_impl_(in, out, p.m_translation.right, max_length);
}

} // anonymous namespace

void translate(const lang_char* in,
               lang_char* out,
               direction::type dir,
               const profile& p)
{
    if(*in != 0)
    {
        const size_t max_translation_length = max_length_translation(p, dir);

        while(*in != 0)
        {
            if(translation_impl(in, out, dir, p, max_translation_length))
                continue;

            if(*in != 0)
                *out++ = *in++;
        }
    }

    // Set end
    *out = 0;
}

size_t size(size_t in_size, direction::type dir, const profile& p)
{
    return in_size * (1 + max_length_translation(p, dir));
}

} // namespace translation
