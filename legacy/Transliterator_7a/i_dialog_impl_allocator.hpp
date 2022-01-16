#ifndef TRANSLITERATOR_I_DIALOG_IMPL_ALLOCATOR_H
#define TRANSLITERATOR_I_DIALOG_IMPL_ALLOCATOR_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

// Same as boost::heap_clone_allocator except from deallocate_clone
struct i_dialog_impl_clone_allocator : boost::heap_clone_allocator
{
    template<typename TBase, typename ImplBase>
    static void deallocate_clone(const i_dialog_impl<TBase, ImplBase>* r)
    {
        r->delete_this();
    }
};

#endif // TRANSLITERATOR_I_DIALOG_IMPL_ALLOCATOR_H
