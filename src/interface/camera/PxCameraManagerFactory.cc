#include "PxCameraManagerFactory.h"

#ifdef MVIMPACT_ENABLED
#include "PxBluefoxCameraManager.h"
#endif
#include "PxFireflyCameraManager.h"

PxCameraManagerPtr PxCameraManagerFactory::bluefoxCameraManager;
PxCameraManagerPtr PxCameraManagerFactory::fireflyCameraManager;

PxCameraManagerPtr
PxCameraManagerFactory::generate(const std::string& type)
{
	bool blueFoxSupported = false;
#ifdef MVIMPACT_ENABLED
	blueFoxSupported = true;
#endif

	// return singleton instance of device-specific camera manager
	if (type.compare("bluefox") == 0 && blueFoxSupported)
	{
		if (bluefoxCameraManager.get() == 0)
		{
#ifdef MVIMPACT_ENABLED
			bluefoxCameraManager = PxCameraManagerPtr(new PxBluefoxCameraManager);
#endif
		}
		return bluefoxCameraManager;
	}
	else if (type.compare("firefly") == 0)
	{
		if (fireflyCameraManager.get() == 0)
		{
			fireflyCameraManager = PxCameraManagerPtr(new PxFireflyCameraManager);
		}
		return fireflyCameraManager;
	}
	else
	{
		return PxCameraManagerPtr();
	}
}
