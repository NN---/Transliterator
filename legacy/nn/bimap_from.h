#include <map>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include <nn/tripple.hpp>

namespace nn
{
    
// Exceptions
class duplicate_value : public std::logic_error
{
public:
    duplicate_value() : std::logic_error("")
    {
    }
};

class duplicate_value_left_to_right : public duplicate_value
{
};

class duplicate_value_right_to_left : public duplicate_value
{
};

class invalid_direction : public std::logic_error
{
public:
    invalid_direction() : std::logic_error("")
    {
    }
};

// Direction
struct bimap_direction
{
    typedef int type;

    enum
    {
        none_to_none = 0,
        left_to_right = 1,
        right_to_left = 2,
        all_to_all = left_to_right | right_to_left
    };

    static type invert(type direction)
    {
        switch(direction)
        {
            case none_to_none:    return all_to_all;    break;
            case left_to_right:   return right_to_left; break;
            case right_to_left:   return left_to_right; break;
            case all_to_all:      return none_to_none;  break;
            default:              return none_to_none;  break;
        }
    }
};

// Bimap Iterator
template<typename BaseIterator, bimap_direction::type DefaultDirection>
class bimap_iterator : public BaseIterator
{
public:
    // Typedef
    typedef typename BaseIterator::iterator_category    iterator_category;
    typedef typename BaseIterator::difference_type      difference_type;

    // Convert from std::pair<const, const*> to
    // std::pair<const, const* const>
    typedef std::pair<
        typename BaseIterator::value_type::first_type,
        const typename BaseIterator::value_type::second_type
    > value_type;

    typedef value_type* pointer;
    typedef value_type& reference;

    // Constructor
    bimap_iterator()
    {
    }

    bimap_iterator(const bimap_iterator& right) :
        BaseIterator(right)
    {
    }

    template<typename BaseIterator2>
    bimap_iterator(const bimap_iterator<BaseIterator2, DefaultDirection>& right) :
        BaseIterator(right)
    {
    }   

    template<typename BaseIterator2>
    explicit bimap_iterator(BaseIterator2 iterator) :
        BaseIterator(iterator)
    {
    }

    reference operator*() const
    {
        return reference(BaseIterator::operator*());
    }

    pointer operator->() const
    {
        // Safe conversion from const* to const* const
        // We use C-style convertion because reinterpret_cast do not work.
        return (pointer)(BaseIterator::operator->());
    }


    bimap_iterator& operator++()
    {
        BaseIterator::operator++();
        return *this;
    }

    bimap_iterator operator++(int)
    {
        bimap_iterator temp = *this;
        ++*this;
        return temp;
    }

    bimap_iterator& operator--()
    {
        BaseIterator::operator--();
        return *this;
    }

    bimap_iterator operator--(int)
    {
        bimap_iterator temp = *this;
        --*this;
        return temp;
    }
};

// BiMap Left-Right members
template<typename BiMap, typename Map, bimap_direction::type DefaultDirection>
class bimap_lr
{
public:
    // Typedef
    typedef Map                                         map_type;

    typedef typename map_type::key_type                 key_type;
    typedef typename map_type::mapped_type              mapped_type;

    typedef typename map_type::key_compare              key_compare;
    typedef typename map_type::value_compare            value_compare;
    typedef typename map_type::value_type               value_type;

    typedef typename map_type::allocator_type           allocator_type;
    typedef typename map_type::size_type                size_type;
    typedef typename map_type::difference_type          difference_type;

    typedef typename map_type::reference                reference;
    typedef typename map_type::const_reference          const_reference;
    typedef typename map_type::pointer                  pointer;
    typedef typename map_type::const_pointer            const_pointer;

    typedef bimap_iterator<
        typename map_type::iterator,
        DefaultDirection
    > iterator;

    typedef bimap_iterator<
        typename map_type::const_iterator,
        DefaultDirection
    > const_iterator;

    typedef bimap_iterator<
        typename map_type::reverse_iterator,
        DefaultDirection
    > reverse_iterator;

    typedef bimap_iterator<
        typename map_type::const_reverse_iterator,
        DefaultDirection
    > const_reverse_iterator;

    bimap_lr(map_type& map) : m_map(map)
    {
    }

    bimap_lr(const bimap_lr& right) : m_map(right.m_map)
    {
    }

    bimap_lr& operator=(const bimap_lr& right)
    {
        m_map = right.m_map;
        return *this;
    }

    allocator_type get_allocator() const
    {
        return m_map.get_allocator();
    }

    iterator begin()
    {
        return iterator(m_map.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(m_map.begin());
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(m_map.rbegin());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(m_map.rbegin());
    }

    iterator end()
    {
        return iterator(m_map.end());
    }

    const_iterator end() const
    {
        return const_iterator(m_map.end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(m_map.rend());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(m_map.rend());
    }

    bool empty() const
    {
        return m_map.empty();
    }

    size_type size() const
    {
        return m_map.size();
    }

    // key_comp
    key_compare key_comp() const
    {
        return m_map.key_comp();
    }

    // value_comp
    value_compare value_comp() const
    {
        return m_map.value_comp();
    }

    // Map operations
    // find
    iterator find(const key_type& key)
    {
        return iterator(m_map.find(key));
    }

    const_iterator find(const key_type& key) const
    {
        return m_map.find(key);
    }

    // count
    size_type count(const key_type& key) const
    {
        return m_map.count(key);
    }

    // lower_bound
    iterator lower_bound(const key_type& key)
    {
        m_map.lower_bound(key);
    }

    const_iterator lower_bound(const key_type& key) const
    {
        m_map.lower_bound(key);
    }

    // upper_bound
    iterator upper_bound(const key_type& key)
    {
        m_map.upper_bound(key);
    }

    const_iterator upper_bound(const key_type& key) const
    {
        m_map.upper_bound(key);
    }

    std::pair<iterator, iterator> equal_range(const key_type& key)
    {
        return m_map.equal_range(key);
    }
    
    std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
    {
        return m_map.equal_range(key);
    }

    // Special overloading for map class
    friend BiMap;

private:
    typedef typename map_type::iterator                  map_iterator;
    typedef typename map_type::const_iterator            map_const_iterator;
    typedef typename map_type::reverse_iterator          map_reverse_iterator;
    typedef typename map_type::const_reverse_iterator    map_const_reverse_iterator;

    map_iterator map_begin()
    {
        return m_map.begin();
    }

    map_const_iterator map_begin() const
    {
        return m_map.begin();
    }

    map_reverse_iterator map_rbegin()
    {
        return m_map.rbegin();
    }

    map_const_reverse_iterator map_rbegin() const
    {
        return m_map.rbegin();
    }

    map_iterator map_end()
    {
        return m_map.end();
    }

    map_const_iterator map_end() const
    {
        return m_map.end();
    }

    map_reverse_iterator map_rend()
    {
        return m_map.rend();
    }

    map_const_reverse_iterator map_rend() const
    {
        return m_map.rend();
    }

private:
    map_type& m_map;
};

// Bidirectional multimap, from
template<typename Left,
         typename Right,
         typename CompareLeft = std::less<Left>,
         typename CompareRight = std::less<Right>,
         typename AllocatorLeft = std::allocator<std::pair<const Left, const Right*> >,
         typename AllocatorRight = std::allocator<std::pair<const Right, const Left*> >
        >
class bimap_from
{
public:
    // Typedef
    typedef bimap_from<
        Left,
        Right,
        CompareLeft,
        CompareRight,
        AllocatorLeft,
        AllocatorRight
    > this_type;

    // Map
    typedef std::map<
        Left,
        const Right*,
        CompareLeft,
        AllocatorLeft
    > map_left_type;

    typedef std::map<
        Right,
        const Left*,
        CompareRight,
        AllocatorRight
    > map_right_type;

    // Left to Right
    typedef bimap_lr<
        this_type,
        map_left_type,
        bimap_direction::left_to_right
    > left_type;

    // Right to Left
    typedef bimap_lr<
        this_type,
        map_right_type,
        bimap_direction::right_to_left
    > right_type;

    // Size
    typedef std::size_t size_type;
    
    // Value
    typedef tripple<Left, Right, bimap_direction::type> value_type;
    
    // Iterator pair
    typedef std::pair<
        typename left_type::iterator,
        typename right_type::iterator
    > pair_iterator;

    typedef std::pair<
        typename left_type::const_iterator,
        typename right_type::const_iterator
    > pair_const_iterator;

    typedef nn::tripple<
        typename left_type::map_iterator,
        typename right_type::map_iterator,
        bimap_direction::type
    > map_iterator_type;
    
    // Constructor
    bimap_from() : left(m_map_left), right(m_map_right)
    {
    }

    template<typename ForwardIterator>
    bimap_from(ForwardIterator first, ForwardIterator last) :
        left(m_map_left),
        right(m_map_right)
    {
        insert(first, last);
    }
    
    bimap_from(const this_type& r) :
        m_map_left(r.m_map_left),
        m_map_right(r.m_map_right),
        m_count_to(r.m_count_to),
        left(r.left),
        right(r.right)
    {
    }

    // Destructor
    ~bimap_from()
    {
        clear();
    }

    // Assignment
    this_type& operator=(const this_type& r)
    {
        m_map_left = r.m_map_left;
        m_map_right = r.m_map_right;

        m_count_to = r.m_count_to;

        left = r.left;
        right = r.right;

        return *this;
    }
 
    // Capacity
    bool empty() const
    {
        return m_map_left.empty() && m_map_right.empty();
    }

    size_type size() const
    {
        return static_cast<size_type>(std::max(left.size(), right.size()));
    }

    // Modifiers
    // insert
    pair_const_iterator insert(const value_type& v)
    {
        typedef typename left_type::map_iterator left_type_iterator;
        typedef typename right_type::map_iterator right_type_iterator;

        // No erase
        if(v.third == bimap_direction::none_to_none)
            throw invalid_direction();
        
        // Insert left
        std::pair<left_type_iterator, bool> insert_pair_left =
            m_map_left.insert(typename left_type::value_type(v.first, NULL));
            
        // Check for duplicates
        if(v.third & bimap_direction::left_to_right &&
           !insert_pair_left.second &&
           insert_pair_left.first->second != NULL)
            throw duplicate_value_left_to_right();

        // Insert right
        std::pair<right_type_iterator, bool> insert_pair_right =
            m_map_right.insert(typename right_type::value_type(v.second, NULL));

        // Check for duplicates
        if(v.third & bimap_direction::right_to_left &&
           !insert_pair_right.second &&
           insert_pair_right.first->second != NULL)
        {
            // Remove value from left if was created
            if(insert_pair_left.second)
                m_map_left.erase(insert_pair_left.first);

            throw duplicate_value_right_to_left();
        }

        left_type_iterator& it_left = insert_pair_left.first;
        right_type_iterator& it_right = insert_pair_right.first;

        // Exchange references
        if(v.third & bimap_direction::left_to_right)
        {
            it_left->second = &it_right->first;

            // Increase reference count
            ++m_count_to[&it_right->first];
        }
        if(v.third & bimap_direction::right_to_left)
        {
            it_right->second = &it_left->first;

            // Increase reference count
            ++m_count_to[&it_left->first];
        }

        return pair_const_iterator(left_type::const_iterator(),
                                   right_type::const_iterator());
    }
    
    template<typename ForwardIterator>
    void insert(ForwardIterator first, ForwardIterator last)
    {
        for(; first != last; ++first)
            insert(*first);
    }

    // erase
    void erase(const map_iterator_type& v)
    {
        // No insert
        if(v.third == bimap_direction::all_to_all)
            throw invalid_direction();

        // Erase type
        bimap_direction::type erase_direction = bimap_direction::none_to_none;

        // Check for direction and reference
        if(!(v.third & bimap_direction::left_to_right) &&
            v.first->second == &v.second->first)
            erase_direction |= bimap_direction::left_to_right;

        if(!(v.third & bimap_direction::right_to_left) &&
            v.second->second == &v.first->first)
            erase_direction |= bimap_direction::right_to_left;

        if(erase_direction == bimap_direction::none_to_none)
            return;

        // Erase
        if(erase_direction & bimap_direction::left_to_right)
        {
            // Decrease reference count
            if(--m_count_to[v.second->second] == 0)
            {
                m_count_to.erase(v.second->second);

                // Erase item
                m_map_right.erase(*v.first->second);
            }

            v.second->second = NULL;
        }
        if(erase_direction & bimap_direction::right_to_left)
        {
            // Decrease reference count
            if(--m_count_to[v.first->second] == 0)
            {
                m_count_to.erase(v.first->second);

                // Erase item
                m_map_left.erase(*v.second->second);
            }

            v.first->second = NULL;
        }
    }

    void erase(const value_type& v)
    {
        // No insert
        erase(map_iterator_type(m_map_left.find(v.first),
                                m_map_right.find(v.second),
                                v.third));
    }
  
    template<typename ForwardIterator>
    void erase(ForwardIterator first, ForwardIterator last)
    {
        for(; first != last; ++first)
            erase(static_cast<const value_type&>(*first));
    }

    // clear
    void clear()
    {
        // Clear all values
        m_map_left.clear();
        m_map_right.clear();
    }
    
    // swap
    void swap(const this_type& right)
    {
        m_map_left.swap(right.m_map_left);
        m_map_right.swap(right.m_map_right);

        m_count_to.swap(right.m_count_to);

        std::swap(left, right.left);
        std::swap(right, right.right);
    }

public:
    // Left operations
    left_type left;
    // Right operations
    right_type right;

private:
    // Left -> Right
    map_left_type m_map_left;
    // Right -> Left
    map_right_type m_map_right;

    // Reference counting map
    std::map<const void*, unsigned> m_count_to;
};

// Operations
// Copied from <map>
template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator==(bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return left.left.size() == right.left.size() &&
           std::equal(left.left.begin(), left.left.end(), right.left.begin()) &&
           left.right.size() == right.right.size() &&
           std::equal(left.right.begin(), left.end_y(), right.right.begin());
}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator!=(bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return !(left == right);
}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator< (bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return std::lexicographical_compare(left.left.begin(),
                                        left.end_x(),
                                        right.left.begin(),
                                        right.end_x()) &&
           std::lexicographical_compare(left.right.begin(),
                                        left.end_y(),
                                        right.right.begin(),
                                        right.end_y());

}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator> (bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return right < left;
}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator<=(bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return !(right < left);
}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
bool operator>=(bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
                bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    return !(left < right);
}

template<typename Left,
         typename Right,
         typename CompareLeft,
         typename CompareRight,
         typename AllocatorLeft,
         typename AllocatorRight>
void swap(nn::bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& left,
          nn::bimap_from<Left, Right, CompareLeft, CompareRight, AllocatorLeft, AllocatorRight>& right)
{
    left.swap(right);
}

} // namespace nn