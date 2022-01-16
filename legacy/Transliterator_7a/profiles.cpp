#include "stdafx.hpp"
#include "profiles.hpp"
#include "settings.hpp"

profiles& profiles::instance()
{
    static profiles s;
    return s;
}

const profile& profiles::get_profile() const
{
    return m_profiles[settings::instance().m_profile];
}

profile& profiles::get_profile(size_t n)
{
    return m_profiles[n];
}

size_t profiles::get_profiles_count()
{
    return m_profiles.size();
}

void profiles::reset()
{
    static const array<void (*)(profile&), default_profiles_count> init_profile =
    {
        &init_profile1,
        &init_profile2,
        &init_profile3,
        &init_profile4,
        &init_profile5,
        &init_profile6,
        &init_profile7,
        &init_profile8
    };

    NN_UPTO_T(i, init_profile.size())
    {
        m_profiles.push_back(new profile());
        init_profile[i](m_profiles[i]);
    }
}