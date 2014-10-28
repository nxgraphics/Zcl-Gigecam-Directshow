
#ifndef KinectCamClass
#define KinectCamClass

#pragma once
//#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
 
#include "ZCLAPI.h"

#define PluginName L"GigeCamera"


 


enum CamModes {
	VGA_RGB,						//   640 x  480 RGB
	SVGA_RGB,						//   800 x  600 RGB
	XGA_RGB,						//	1024 x  768 RGB
	SXGA_RGB,						//	1280 x  960 RGB
	UXGA_RGB,						//	1600 x 1200 RGB
};

 
//class CVCam;
class __declspec(dllexport) KinectCam
{
public:
	KinectCam();
    bool Nui_Init();
    void Nui_UnInit();
    bool Nui_GetCamFrame(BYTE *frameBuffer, int frameSize);
	ZCL_STDMODE getMode();
	long getWidth();
	long getHeight();
	int getBpp();
	void SetMode( long width, long height, unsigned int framerate );
	void SetWidth( unsigned int Width ) ;
	void SetHeight( unsigned int Height );
	void SetBpp( short bpp );
	bool ResetConfiguration(  );


private:
	HANDLE m_hNextVideoFrameEvent;
    HANDLE m_pVideoStreamHandle;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned int mBpp;
	ZCL_FPS mFramerate;
	ZCL_STDMODE mVideoMode;
};


#endif