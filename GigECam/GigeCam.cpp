
#include "stdafx.h"
#include "GigeCam.h"
#include "stdio.h"
#include <shlobj.h>
#include <string>
#include <xmmintrin.h>
#include <math.h>
 

bool g_flipImage = false;
BYTE * MyBuffer;
BYTE * MyBufferCopy;
ZCL_GETIMAGEINFO	NowImageInfo;
ZCL_CAMERAMODE mode;
HCAMERA hCamera = 0;
HANDLE mThread = 0;

bool run = true;
bool HasNewFrame = false;

//CRITICAL_SECTION CriticalSection; 

UINT64 mCameraID = -1;
 
KinectCam::KinectCam() : mBpp(1) {

	//mWidth  = 800;
	//mHeight = 600;
	//mFramerate = ZCL_Fps_60;
	//mVideoMode = ZCL_SVGA_MONO;

	mWidth  = 640;
	mHeight = 480;
	mFramerate = ZCL_Fps_60;
	mVideoMode = ZCL_VGA_MONO;
	MyBuffer = 0;
	MyBufferCopy = 0;

	//if (!InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x00000400) ) 
	//	return;

}

ZCL_STDMODE KinectCam::getMode()
{
	return mode.u.Std.Mode ;
}

long KinectCam::getWidth() {
	return  mWidth;
}

long KinectCam::getHeight(){
	return  mHeight;// NowImageInfo.Image.Height;
}
 
int KinectCam::getBpp(){
return mBpp;
}

void KinectCam::SetMode( long width, long height, unsigned int framerate ) {//ZCL_STDMODE mode, ZCL_FPS framerate ) { // apply and set mode
 
	if( width == 640 && height == 480 ){ mVideoMode = ZCL_VGA_MONO; }
	else if( width == 800 && height == 600 ){ mVideoMode = ZCL_SVGA_MONO; }
	else if( width == 1024 && height == 768 ){ mVideoMode = ZCL_XGA_MONO; }
	else if( width == 1280 && height == 960 ){ mVideoMode = ZCL_SXGA_MONO; }
	else if( width == 1600 && height == 1200 ){ mVideoMode = ZCL_UXGA_MONO; }
	else{  MessageBox( 0,"KinectCam::SetMode :: No mode set !","",0 ); }

	mWidth = width;
	mHeight = height;

	if( framerate < 15 ) {
		mFramerate = ZCL_FPS::ZCL_Fps_15;
		MessageBox( 0,"KinectCam::SetMode :: framerate is minus !","",0 );
	}
	else if( framerate >= 15 && framerate < 30 ) {
		mFramerate = ZCL_FPS::ZCL_Fps_15;
	}
	else if( framerate >= 30 && framerate < 60) {
		mFramerate = ZCL_FPS::ZCL_Fps_30;
	}
	else if( framerate >= 60 && framerate < 120) {
		mFramerate = ZCL_FPS::ZCL_Fps_60;
	}
	else if( framerate >= 120 && framerate < 240) {
		mFramerate = ZCL_FPS::ZCL_Fps_120;
	}
	else if( framerate >= 240) {
		mFramerate = ZCL_FPS::ZCL_Fps_240;
	}
	else{  
		mFramerate = ZCL_FPS::ZCL_Fps_60;
		MessageBox( 0,"KinectCam::SetMode :: No framerate set !","",0 );
	}
 
}

void KinectCam::SetWidth( unsigned int Width ) {
	mWidth = Width;
}

void KinectCam::SetHeight( unsigned int Height ) {
	mHeight = Height;
}

void KinectCam::SetBpp( short bpp ){
	mBpp = bpp;
}

DWORD MyThread(LPVOID func)
{
	KinectCam * ptr = ( KinectCam * ) func;


	if(! ZCLImageReq( hCamera, MyBuffer, NowImageInfo.Image.Buffer ))
	{

		return 0;
	}


	while( run ) {

		 

		//if( hCamera ){

		//CAutoLock cAutoLock(&m_critSec);

		//HasNewFrame = false;

		//EnterCriticalSection(&CriticalSection); 
 

			ZCL_TRANSMITSPEED Speed;
			ULONG time1, time2;
			BOOL flag = ZCLImageCompleteWait( hCamera, MyBuffer, &Speed, &time1, &time2 );

			//memcpy( MyBufferCopy, MyBuffer, ptr->getWidth()*ptr->getHeight()*ptr->getBpp());

			if(ZCLImageReq( hCamera, MyBuffer, NowImageInfo.Image.Buffer )) {

			}

			//LeaveCriticalSection(&CriticalSection);

			if(flag) HasNewFrame = true;
			//HasNewFrame = true;
		//}

			 

		Sleep(0);

	}

	return true;

}

bool KinectCam::ResetConfiguration() {

	run = false;
	if( mThread ){
		WaitForSingleObject( mThread, INFINITE );
		TerminateThread(mThread,0);
		mThread = 0;
	}
	HasNewFrame = false;

	if( hCamera ){
		ZCLIsoStop( hCamera );
		ZCLIsoRelease( hCamera );
		ZCLClose( hCamera );
		//ZCLAllClose(); 
		hCamera = 0;
	}

	if( !ZCLOpen( mCameraID, &hCamera ) ) {  //could not open camera
		MessageBox(0,"ZCLOpen Failed !","",0);
		return false;
	} 
	 
	mode.StdMode_Flag = TRUE;
	mode.u.Std.Mode = mVideoMode;//ZCL_VGA_MONO;//ZCL_VGA_RGB; // 640 x 640 RGB
	mode.u.Std.FrameRate = mFramerate;//ZCL_Fps_60; 
	if( !ZCLSetCameraMode( hCamera, &mode )){ MessageBox(0,"ZCLSetCameraMode Failed !","",0); return false;} //failed setting camera mode
	if( !ZCLGetImageInfo( hCamera, &NowImageInfo ) ){ MessageBox(0,"ZCLGetImageInfo Failed !","",0); return false;} //arrangement for picture buffer

	if( MyBuffer ) { delete MyBuffer; MyBuffer = 0; }
	MyBuffer = new BYTE[ NowImageInfo.Image.Buffer ];

	if( MyBufferCopy ) { delete MyBufferCopy; MyBufferCopy = 0; }
	MyBufferCopy = new BYTE[ mWidth*mHeight*mBpp ];

	//DSTBuffer = new BYTE[ NowImageInfo.Image.Buffer ];
	//int Width  = NowImageInfo.Image.Width;
	//int Height = NowImageInfo.Image.Height;

	if(!ZCLIsoAlloc(hCamera)){ MessageBox(0,"ZCLIsoAlloc Failed !","",0); return false; } // error allocating ISO ressources
	//ZCLSetImageCallBack( hCamera, NULL, ImageFuncOk, 5 );


	if( !ZCLIsoStart( hCamera, 0 ) ){ MessageBox(0," ZCLIsoStart Failed !","",0); return false; } 

	//if(ZCLImageReq( hCamera, MyBuffer, NowImageInfo.Image.Buffer )) {
	//MessageBox(0,"Creating thread !","",0);
	DWORD var;
	run = true;
	mThread = CreateThread( NULL, 0 , (LPTHREAD_START_ROUTINE) MyThread , this, 0 , &var );

	//MessageBox(0,"Creating thread ok !","",0);

	return true;//break;
	 

	 /*

	run = false;
	if( mThread ){
		WaitForSingleObject( mThread, INFINITE );
		TerminateThread(mThread,0);
		mThread = 0;
	}
	HasNewFrame = false;
 
	if( hCamera ){
		ZCLIsoStop( hCamera );
		ZCLIsoRelease( hCamera );
		ZCLClose( hCamera );
		ZCLAllClose(); 
		hCamera = 0;
	}

	

	if( !ZCLOpen( mCameraID, &hCamera ) ) {  //could not open camera
		MessageBox(0," ResetConfiguration : ZCLOpen Failed !","",0); 
	}
 
	ZCL_CAMERAMODE  modelocal;
	modelocal.StdMode_Flag = TRUE;
	modelocal.u.Std.Mode = mVideoMode;//ZCL_VGA_MONO;//ZCL_VGA_RGB; // 640 x 640 RGB
	modelocal.u.Std.FrameRate = mFramerate;//ZCL_Fps_60; 
	if( !ZCLSetCameraMode( hCamera, &modelocal )){ MessageBox(0," ResetConfiguration : ZCLSetCameraMode Failed !","",0); return false;} //failed setting camera mode
 
	ZCL_GETIMAGEINFO	NowImageInfoLocal;
	if( !ZCLGetImageInfo( hCamera, &NowImageInfoLocal ) ){ MessageBox(0,"ZCLGetImageInfo Failed !","",0); return false;} //arrangement for picture buffer


	if( MyBuffer ) delete MyBuffer;
	MyBuffer = 0;
	MyBuffer = new BYTE[ NowImageInfoLocal.Image.Buffer ];

	if(!ZCLIsoAlloc(hCamera)) {
		MessageBox(0," ResetConfiguration : ZCLIsoAlloc Failed !","",0);
		// error allocating ISO ressources
		return false;
	}



	if( !ZCLIsoStart( hCamera, 0 ) ){ MessageBox(0," ResetConfiguration : ZCLIsoStart Failed !","",0); return false; } 

 
	
	run = true;
	DWORD var;
	mThread = CreateThread( NULL, 0 , (LPTHREAD_START_ROUTINE) MyThread , this, 0 , &var );

	//MessageBox(0,"CREATED","",0);
  

	return true;*/
}

 
 

bool KinectCam::Nui_Init( ) 
{
	 
	ZCL_LIST	*pCameraList;
	DWORD		count;
	int			i;
 
	ZCLSetStructVersion( ZCL_LIBRARY_STRUCT_VERSION );
	count = 0;
	if( ZCLGetList( (pZCL_LIST)&count ) )
	{
		pCameraList = (pZCL_LIST)malloc( sizeof(ZCL_LIST) + sizeof(ZCL_CAMERAINFO) * count );
		ZeroMemory( pCameraList, ( sizeof(ZCL_LIST) + sizeof(ZCL_CAMERAINFO) * count ) );
		pCameraList->CameraCount = count;
		if( ZCLGetList( pCameraList ) ) {

			for( i = 0; i < (int)pCameraList->CameraCount; i++ ) { //make camera list

				char sdata[ 512 ];
				char sdata2[ 512 ];
				WCHAR wdata[ 256 ];
				WCHAR wdata2[ 256 ];

				memset( sdata, 0, sizeof( sdata ) );
				memset( sdata2, 0, sizeof( sdata2 ) );
				memset( wdata, 0, sizeof( wdata ) );
				memset( wdata2, 0, sizeof( wdata2 ) );

				sprintf_s( sdata, sizeof( sdata ) , "%s : 0x%08x%08x", pCameraList->Info[ i ].ModelName, (DWORD)( (pCameraList->Info[ i ].UID & 0xffffffff00000000) >> 32 ), (DWORD)(pCameraList->Info[ i ].UID & 0xffffffff ) );
				sprintf_s( sdata2, sizeof( sdata2 ) , "%s", pCameraList->Info[ i ].VendorName );
				
				//code convert(BYTE->WORD)
				for( int idx = 0; idx < 256; idx++ ) {
					wdata[ idx ] = sdata[ idx ];
				}
				for( int idx = 0; idx < 256; idx++ ) {
					wdata2[ idx ] = sdata2[ idx ];
				}


				mCameraID = pCameraList->Info[ i ].UID;

				SetMode( 640, 480, 60 );
				ResetConfiguration(); 

				break;
 
				/* if( !ZCLOpen( pCameraList->Info[ i ].UID, &hCamera ) ) {  //could not open camera
					MessageBox(0,"ZCLOpen Failed !","",0);
					return false;
				} 
				else {

				 


					 
					mode.StdMode_Flag = TRUE;
					mVideoMode = ZCL_VGA_MONO;
					mode.u.Std.Mode = mVideoMode;//ZCL_VGA_MONO;//ZCL_VGA_RGB; // 640 x 640 RGB
					mode.u.Std.FrameRate = mFramerate;//ZCL_Fps_60; 
					if( !ZCLSetCameraMode( hCamera, &mode )){ MessageBox(0,"ZCLSetCameraMode Failed !","",0); return false;} //failed setting camera mode
					if( !ZCLGetImageInfo( hCamera, &NowImageInfo ) ){ MessageBox(0,"ZCLGetImageInfo Failed !","",0); return false;} //arrangement for picture buffer
		
					
					MyBuffer = new BYTE[ NowImageInfo.Image.Buffer ];
					//DSTBuffer = new BYTE[ NowImageInfo.Image.Buffer ];
					//int Width  = NowImageInfo.Image.Width;
					//int Height = NowImageInfo.Image.Height;

					if(!ZCLIsoAlloc(hCamera)){ MessageBox(0,"ZCLIsoAlloc Failed !","",0); return false; } // error allocating ISO ressources
					//ZCLSetImageCallBack( hCamera, NULL, ImageFuncOk, 5 );

					
					if( !ZCLIsoStart( hCamera, 0 ) ){ MessageBox(0," ZCLIsoStart Failed !","",0); return false; } 
  
					//if(ZCLImageReq( hCamera, MyBuffer, NowImageInfo.Image.Buffer )) {
						MessageBox(0,"Creating thread !","",0);
						DWORD var;
						mThread = CreateThread( NULL, 0 , (LPTHREAD_START_ROUTINE) MyThread , this, 0 , &var );

						MessageBox(0,"Creating thread ok !","",0);
						
						return true;//break;
					//}else{
					//	MessageBox(0,"Could not create thread !","",0);
					//	return false;
					//}
					
					 
 
				} */
			}
		}
	}

	return true;
}

void KinectCam::Nui_UnInit()
{
	run = false;
	ZCLIsoStop( hCamera  );
	ZCLSetImageCallBack( hCamera, NULL, NULL, 0 );
	ZCLIsoRelease( hCamera );
	ZCLClose( hCamera );
	ZCLAllClose(); 
}

bool KinectCam::Nui_GetCamFrame( BYTE * frameBuffer, int frameSize )
{

	 
	

	if( HasNewFrame == true ) {


		//for (int i = 0; i < frameSize; ++i)
		//	MyBuffer[i] =  rand();

	 

		// EnterCriticalSection(&CriticalSection); 

		memcpy( frameBuffer, MyBuffer , mWidth*mHeight*mBpp );//640*480*1 );// mWidth*mHeight*mBpp ); 

		//LeaveCriticalSection(&CriticalSection);

		HasNewFrame = false;
		return true;
	}

	 memset( frameBuffer , 128 , frameSize );
	return false;


	/*
		DWORD *ImageBuffer;
		ImageBuffer = &NowImageInfo.Image.Buffer;

		if(ZCLImageReq( hCamera, MyBuffer, *ImageBuffer )) {
			bool OK = true;
				}

		ZCL_TRANSMITSPEED Speed;
		ULONG time1, time2;
		bool flag = ZCLImageCompleteWait( hCamera, MyBuffer, &Speed, &time1, &time2 );
		//if( WaitForSingleObject( gEventList[ EventNo ].EndEvent, 0 ) == WAIT_OBJECT_0 )
		//{
		//	ResetEvent( gEventList[ EventNo ].EndEvent );
		//	break;
		//}

		
		if( flag ) {
			long index = 0;
			for( long i = 0 ; i < getWidth()*getHeight()*4; i = i+4 ) {
				frameBuffer[i] = MyBuffer[index];
				frameBuffer[i+1] = MyBuffer[index];
				frameBuffer[i+2] = MyBuffer[index];
				frameBuffer[i+3] = 255; 
				index++;
			}
		}*/
 
		
}


