#pragma once

#include "Tracy/Tracy.hpp"


#define HZ_PROFILE 1
#if HZ_PROFILE
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name) ZoneScopedN(name)
#define HZ_PROFILE_FUNCTION() ZoneScoped
#else
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name)
#define HZ_PROFILE_FUNCTION()
#endif
