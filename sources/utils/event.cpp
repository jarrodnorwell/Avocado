#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/utils/event.h"

#else

#include "utils/event.h"

#endif // TARGET_OS_IPHONE

Dexode::EventBus bus;

void toast(const std::string& message) {
	bus.notify(Event::Gui::Toast{ message });
}