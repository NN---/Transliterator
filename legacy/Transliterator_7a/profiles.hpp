#ifndef TRANSLITERATOR_PROFILES_H
#define TRANSLITERATOR_PROFILES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // _MSC_VER && (_MSC_VER >= 1200)

#include "profile.hpp"

class profiles
{
public:
    static profiles& instance();

    // Get profile
    const profile& get_profile() const;
    profile& get_profile(size_t n);
    size_t get_profiles_count();

    void reset();

private:
    // Profiles
    static const size_t max_profiles = 20;
    typedef ptr_vector<profile> profiles_type;
    profiles_type m_profiles;

    static void init_profile1(profile& p);
    static void init_profile2(profile& p);
    static void init_profile3(profile& p);
    static void init_profile4(profile& p);
    static void init_profile5(profile& p);
    static void init_profile6(profile& p);
    static void init_profile7(profile& p);
    static void init_profile8(profile& p);

    // Initialize default profiles
    static const size_t default_profiles_count = 8;
};

#endif // TRANSLITERATOR_PROFILES_H
