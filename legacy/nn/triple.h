namespace nn
{

// Like std::pair but takes 3 arguments
template<typename First, typename Second, typename Third>
struct tripple
{
    typedef tripple<First, Second, Third> this_type;

    typedef First first_type;
    typedef Second second_type;
    typedef Third third_type;

    tripple() :
        first(First()),
        second(Second()),
        third(Third())
    {
    }

    tripple(const First& first_val,
           const Second& second_val,
           const Third& third_val) :
        first(first_val),
        second(second_val),
        third(third_val)
    {
    }

    template<typename First2, typename Second2, typename Third2>
    tripple(const tripple<First2, Second2, Third2>& right) :
        first(right.first),
        second(right.second),
        third(right.third)
    {
    }

    void swap(const this_type& right)
    {
        std::swap(first, right.first);
        std::swap(second, right.second);
        std::swap(third, right.third);
    }

    First first;
    Second second;
    Third third;
};

template<typename First, typename Second, typename Third>
bool operator==(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return left.first == right.first &&
           left.second == right.second &&
           left.third == right.third;
}

template<typename First, typename Second, typename Third>
bool operator!=(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return !(left == right);
}

template<typename First, typename Second, typename Third>
bool operator <(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return left.first < right.first &&
           left.second < right.second &&
           left.third < right.third;
}

template<typename First, typename Second, typename Third>
bool operator >(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return right < left;
}

template<typename First, typename Second, typename Third>
bool operator<=(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return !(right < left);
}

template<typename First, typename Second, typename Third>
bool operator>=(const tripple<First, Second, Third>& left,
                const tripple<First, Second, Third>& right)
{
    return !(left < right);
}

template<typename First, typename Second, typename Third>
tripple<First, Second, Third> make_tripple(const First& first,
                                         const Second& second,
                                         const Third& third)
{
    return tripple<First, Second, Third>(first, second, third);
}

template<typename First, typename Second, typename Third>
void swap(const nn::tripple<First, Second, Third>& left,
          const nn::tripple<First, Second, Third>& right)
{
    left.swap(right);
}

} // namespace nn