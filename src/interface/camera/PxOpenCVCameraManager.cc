#include "PxOpenCVCameraManager.h"
#include "PxOpenCVCamera.h"
#include <iostream>

using namespace std;

PxOpenCVCameraManager::PxOpenCVCameraManager(bool _isDepth) : isDepth(false)
{
	if(_isDepth)
	{
		isDepth = true;
		fprintf(stderr, "# RGB-D mode enabled.\n");
	}
}

PxOpenCVCameraManager::~PxOpenCVCameraManager()
{

}

PxCameraPtr
PxOpenCVCameraManager::generateCamera(uint64_t captureIndex)
{
	cv::VideoCapture *cap = getCamera(captureIndex);

	if(isDepth)
	{
		cap->open(CV_CAP_OPENNI);

		if(cap->isOpened())
		{
			// Print some avalible device settings.
			cout << "\nDepth generator output mode:" << endl <<
			        "FRAME_WIDTH      " << cap->get( CV_CAP_PROP_FRAME_WIDTH ) << endl <<
			        "FRAME_HEIGHT     " << cap->get( CV_CAP_PROP_FRAME_HEIGHT ) << endl <<
			        "FRAME_MAX_DEPTH  " << cap->get( CV_CAP_PROP_OPENNI_FRAME_MAX_DEPTH ) << " mm" << endl <<
			        "FPS              " << cap->get( CV_CAP_PROP_FPS ) << endl <<
			        "REGISTRATION     " << cap->get( CV_CAP_PROP_OPENNI_REGISTRATION ) << endl;

			if( cap->get( CV_CAP_OPENNI_IMAGE_GENERATOR_PRESENT ) )
			{
			    cout <<
			        "\nImage generator output mode:" << endl <<
			        "FRAME_WIDTH   " << cap->get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FRAME_WIDTH ) << endl <<
		        	"FRAME_HEIGHT  " << cap->get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FRAME_HEIGHT ) << endl <<
			        "FPS           " << cap->get( CV_CAP_OPENNI_IMAGE_GENERATOR+CV_CAP_PROP_FPS ) << endl;
			}
			else
			{
			    cout << "\nDevice doesn't contain image generator." << endl;
			}
			
			return PxCameraPtr(new PxOpenCVCamera(cap));
		}
		else
		{
			fprintf(stderr, "# ERROR: No OpenCV depth camera found.\n");
			return PxCameraPtr();
		}
	}
	else
	{
		if(cap->isOpened())
		{
			return PxCameraPtr(new PxOpenCVCamera(cap));
		}
		else
		{
			fprintf(stderr, "# ERROR: No OpenCV camera found.\n");
			return PxCameraPtr();
		}
	}
}

PxStereoCameraPtr
PxOpenCVCameraManager::generateStereoCamera(uint64_t serialNum1, uint64_t serialNum2)
{
	fprintf(stderr, "# ERROR: OpenCV camera does not support stereo.\n");
	return PxStereoCameraPtr();
}

int
PxOpenCVCameraManager::getCameraCount(void) const
{
	return 1;
}

cv::VideoCapture*
PxOpenCVCameraManager::getCamera(uint64_t captureIndex)
{
	cv::VideoCapture* cap = new cv::VideoCapture(captureIndex);
	return cap;
}
