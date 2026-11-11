#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/disc/track.h"

#else

#include "disc/track.h"

#endif // TARGET_OS_IPHONE

namespace disc
{
} // namespace disc
