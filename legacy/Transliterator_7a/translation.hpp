#ifndef TRANSLITERATOR_TRANSLATION_H
#define TRANSLITERATOR_TRANSLATION_H

#include "profile.hpp"
#include "types.hpp"
#include "direction.hpp"

namespace translation
{

void translate(const lang_char* in,
               lang_char* out,
               direction::type dir,
               const profile& p);

size_t size(size_t in_size, direction::type dir, const profile& p);

} // namespace translation

#endif // TRANSLITERATOR_TRANSLATION_H
