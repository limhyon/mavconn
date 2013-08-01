#include "PxCameraManagerFactory.h"
#include "PxOpenCVCameraManager.h"

PxCameraManagerPtr PxCameraManagerFactory::opencvCameraManager;

PxCameraManagerPtr
PxCameraManagerFactory::generate(const std::string& type)
{
	if (type.compare("opencv") == 0)
	{
		if (opencvCameraManager.get() == 0)
		{
			opencvCameraManager = PxCameraManagerPtr(new PxOpenCVCameraManager(false));
		}
		return opencvCameraManager;
	}
	else if(type.compare("opencv-depth") == 0)
	{
		if (opencvCameraManager.get() == 0)
		{
			//! Enable RGB-D mode
			opencvCameraManager = PxCameraManagerPtr(new PxOpenCVCameraManager(true));
		}
		return opencvCameraManager;
	}
	else
	{
		return PxCameraManagerPtr();
	}
}
