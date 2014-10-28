#pragma warning(disable:4244)
#pragma warning(disable:4711)

#include <streams.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <olectl.h>
#include <dvdmedia.h>
#include "Vcam.h"
#include "GigeCam.h"


extern bool g_flipImage;

int BPPInit = 8;//20;   // 1280*960

 int varX = 80;//80;

 int varY = 60;//60;
//////////////////////////////////////////////////////////////////////////
//  CVCam is the source filter which masquerades as a capture device
//////////////////////////////////////////////////////////////////////////
CUnknown * WINAPI CVCam::CreateInstance(LPUNKNOWN lpunk, HRESULT *phr)
{
    ASSERT(phr);
    CVCam * punk = new CVCam(lpunk, phr);
	return punk->IsCameraAvailable() ? punk : 0;
}

CVCam::CVCam(LPUNKNOWN lpunk, HRESULT *phr) : CSource(NAME(PluginName), lpunk, CLSID_VirtualCam), mCameraAvailable(false)
{
	mCurrentVideoMode = CamModes::VGA_RGB;
    ASSERT(phr);
    CAutoLock cAutoLock(&m_cStateLock);
    // Create the one and only output pin
	m_kinected = m_kinectCam.Nui_Init() ;
	if( !m_kinected ) { MessageBox(0,"Could not connect to first camera !","",0); return; }
	mCameraAvailable = true;
 
	m_pBufferSize = m_kinectCam.getWidth() * m_kinectCam.getHeight() * m_kinectCam.getBpp();
	m_pBuffer = new BYTE[m_pBufferSize];
    m_paStreams = (CSourceStream **) new CVCamStream*[1];
    m_paStreams[0] = new CVCamStream(phr, this, PluginName );
}

CVCam::~CVCam()
{
	m_kinectCam.Nui_UnInit();
	delete m_paStreams[0];
	delete [] m_paStreams;
}

bool CVCam::IsCameraAvailable() {
	return mCameraAvailable;
}

HRESULT CVCam::QueryInterface(REFIID riid, void **ppv)
{
    //Forward request for IAMStreamConfig & IKsPropertySet to the pin
    if(riid == _uuidof(IAMStreamConfig) || riid == _uuidof(IKsPropertySet))
        return m_paStreams[0]->QueryInterface(riid, ppv);
    else
        return CSource::QueryInterface(riid, ppv);
}

//////////////////////////////////////////////////////////////////////////
// CVCamStream is the one and only output pin of CVCam which handles 
// all the stuff.
//////////////////////////////////////////////////////////////////////////
CVCamStream::CVCamStream(HRESULT *phr, CVCam *pParent, LPCWSTR pPinName) : CSourceStream(NAME(PluginName),phr, pParent, pPinName), m_pParent(pParent)
{
    // Set the default media type as 640x480x24@15
    GetMediaType(BPPInit, &m_mt);
}

HRESULT CVCamStream::QueryInterface(REFIID riid, void **ppv)
{   
    // Standard OLE stuff
    if(riid == _uuidof(IAMStreamConfig))
        *ppv = (IAMStreamConfig*)this;
    else if(riid == _uuidof(IKsPropertySet))
        *ppv = (IKsPropertySet*)this;
    else
        return CSourceStream::QueryInterface(riid, ppv);

    AddRef();
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
//  This is the routine where we create the data being output by the Virtual
//  Camera device.
//////////////////////////////////////////////////////////////////////////

HRESULT CVCamStream::FillBuffer(IMediaSample *pms)
{
    REFERENCE_TIME rtNow;   
    REFERENCE_TIME avgFrameTime = ((VIDEOINFOHEADER*)m_mt.pbFormat)->AvgTimePerFrame;

    rtNow = m_rtLastTime;
    m_rtLastTime += avgFrameTime;
    pms->SetTime(&rtNow, &m_rtLastTime);
    pms->SetSyncPoint(TRUE);

    BYTE *pData;
    long lDataLen;
    pms->GetPointer(&pData);
    lDataLen = pms->GetSize();
 
	if (m_pParent->m_kinected) {
		bool newframe = m_pParent->m_kinectCam.Nui_GetCamFrame(m_pParent->m_pBuffer, m_pParent->m_pBufferSize);
		if( newframe ) {
				int srcPos = 0;
				int destPos = 0;
				//convert monochrome to RGB
				for (int y = 0; y < m_pParent->m_kinectCam.getHeight() ; y++) {
					for (int x = 0; x < m_pParent->m_kinectCam.getWidth() ; x++) {
						 if (destPos < lDataLen-3) {

							bool flip = true;
						 	if (flip)
						 		srcPos = (x * m_pParent->m_kinectCam.getBpp()) + (((m_pParent->m_kinectCam.getHeight()-1 )-y) * m_pParent->m_kinectCam.getWidth()  * m_pParent->m_kinectCam.getBpp());
						 	else
								srcPos = (((m_pParent->m_kinectCam.getWidth() -1) - x) * m_pParent->m_kinectCam.getBpp()) + (((m_pParent->m_kinectCam.getHeight()-1 )-y) * m_pParent->m_kinectCam.getWidth()  * m_pParent->m_kinectCam.getBpp());

							pData[destPos++] = m_pParent->m_pBuffer[srcPos];
							pData[destPos++] = m_pParent->m_pBuffer[srcPos+1];
							pData[destPos++] = m_pParent->m_pBuffer[srcPos+2];	 
						 }
					}
				}
				return NOERROR;
		
		}else{ return S_OK; } 
  
	}
	else
	{
		for (int i = 0; i < lDataLen; ++i)
			pData[i] = rand();
	}
 
    return NOERROR;

 
} // FillBuffer


//
// Notify
// Ignore quality management messages sent from the downstream filter
STDMETHODIMP CVCamStream::Notify(IBaseFilter * pSender, Quality q)
{
    return E_NOTIMPL;
} // Notify

//////////////////////////////////////////////////////////////////////////
// This is called when the output format has been negotiated
//////////////////////////////////////////////////////////////////////////
HRESULT CVCamStream::SetMediaType(const CMediaType *pmt)
{

	//CSourceStream::SetMediaType(pmt);
	//IFilterGraph *pGraph = m_pParent->GetGraph();
	//pGraph->Reconnect(this);

	/*
	HRESULT hr;
	if (direction == PINDIR_OUTPUT) 
	{
		// Before we set the output type, we might need to reconnect 
		// the input pin with a new type.
		if (m_pInput && m_pInput->IsConnected()) 
		{
			// Check if the current input type is compatible.
			hr = CheckTransform(
				&m_pInput->CurrentMediaType(),
				&m_pOutput->CurrentMediaType());
			if (SUCCEEDED(hr))
			{
				return S_OK;
			}
			// Otherwise, we need to reconnect the input pin.
			// Note: The CheckMediaType method has already called 
			// QueryAccept on the upstream filter. 
			hr = m_pGraph->Reconnect(m_pInput);
			return hr;
		}
	}*/
	//return S_OK;


     DECLARE_PTR(VIDEOINFOHEADER, pvi, pmt->Format());
	  HRESULT hr = CSourceStream::SetMediaType(pmt);
	 //IFilterGraph *pGraph = m_pParent->GetGraph();
	 // pGraph->Reconnect(this);

	 
   
    return hr;
}

// See Directshow help topic for IAMStreamConfig for details on this method
HRESULT CVCamStream::GetMediaType(int iPosition, CMediaType *pmt)
{
   if(iPosition < 0) return E_INVALIDARG;
   if(iPosition > BPPInit) return VFW_S_NO_MORE_ITEMS;

    if(iPosition == 0)  {
        *pmt = m_mt;
        return S_OK;
    }
 
    DECLARE_PTR(VIDEOINFOHEADER, pvi, pmt->AllocFormatBuffer(sizeof(VIDEOINFOHEADER)));
    ZeroMemory(pvi, sizeof(VIDEOINFOHEADER));

    pvi->bmiHeader.biCompression = BI_RGB;
    pvi->bmiHeader.biBitCount    = 24;
    pvi->bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth       = m_pParent->m_kinectCam.getWidth();//640;//80 * iPosition;
    pvi->bmiHeader.biHeight      = m_pParent->m_kinectCam.getHeight();//480;//60 * iPosition;
    pvi->bmiHeader.biPlanes      = 1;
    pvi->bmiHeader.biSizeImage   = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;

    pvi->AvgTimePerFrame = 1000000; // (1/120) * 10,000,000   ;//1000000; // Average time per frame (100ns units)

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    pmt->SetType(&MEDIATYPE_Video);
    pmt->SetFormatType(&FORMAT_VideoInfo);
    pmt->SetTemporalCompression(FALSE);

    // Work out the GUID for the subtype from the header info.
    const GUID SubTypeGUID = GetBitmapSubtype(&pvi->bmiHeader);
    pmt->SetSubtype(&SubTypeGUID);
    pmt->SetSampleSize(pvi->bmiHeader.biSizeImage);
    
    return NOERROR;
 

} // GetMediaType

// This method is called to see if a given output format is supported
HRESULT CVCamStream::CheckMediaType(const CMediaType *pMediaType)
{
    //VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *)(pMediaType->Format());
    if(*pMediaType != m_mt) 
        return E_INVALIDARG;
    return S_OK;
} // CheckMediaType

// This method is called after the pins are connected to allocate buffers to stream data
HRESULT CVCamStream::DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pProperties)
{
    CAutoLock cAutoLock(m_pFilter->pStateLock());
    HRESULT hr = NOERROR;

    VIDEOINFOHEADER *pvi = (VIDEOINFOHEADER *) m_mt.Format();
    pProperties->cBuffers = 1;
    pProperties->cbBuffer = pvi->bmiHeader.biSizeImage;

    ALLOCATOR_PROPERTIES Actual;
    hr = pAlloc->SetProperties(pProperties,&Actual);

	if(FAILED(hr)){ MessageBox(0,"if(FAILED(hr))","",0);  return hr; }
	if(Actual.cbBuffer < pProperties->cbBuffer){  MessageBox(0,"Actual.cbBuffer < pProperties->cbBuffer failed","",0); return E_FAIL; }

    return NOERROR;
} // DecideBufferSize

// Called when graph is run
HRESULT CVCamStream::OnThreadCreate()
{
    m_rtLastTime = 0;
    return NOERROR;
} // OnThreadCreate


//////////////////////////////////////////////////////////////////////////
//  IAMStreamConfig
//////////////////////////////////////////////////////////////////////////

HRESULT STDMETHODCALLTYPE CVCamStream::SetFormat(AM_MEDIA_TYPE *pmt)
{

	 
 
	VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)pmt->pbFormat;
	// pVih contains the detailed format information.
	LONG lWidth = pVih->bmiHeader.biWidth;
	LONG lHeight = pVih->bmiHeader.biHeight;
 
	// calculate framerate
	long nTenMillion    = 10000000;
	long lAvgFrameDuration  = 0;

	if( pmt->formattype == FORMAT_VideoInfo || pmt->formattype == FORMAT_MPEGVideo )    
		lAvgFrameDuration = (LONG) ((VIDEOINFOHEADER *)(pmt->pbFormat))->AvgTimePerFrame;

	else if( pmt->formattype == FORMAT_VideoInfo2 || pmt->formattype == FORMAT_MPEG2_VIDEO )    
		lAvgFrameDuration = (LONG) ((VIDEOINFOHEADER2 *)(pmt->pbFormat))->AvgTimePerFrame;

	long plFramesPerSecond = ( lAvgFrameDuration != 0 ) ? ((long)( nTenMillion / lAvgFrameDuration )) : 0;

	int DstFps = plFramesPerSecond;

  

	pVih->AvgTimePerFrame =   (REFERENCE_TIME)(10000000/DstFps); 

 
	m_pParent->m_kinectCam.SetMode( lWidth , lHeight , DstFps );// ZCL_STDMODE::ZCL_UXGA_MONO, ZCL_FPS::ZCL_Fps_60 );
	m_pParent->m_kinectCam.ResetConfiguration();

	m_pParent->m_pBufferSize = m_pParent->m_kinectCam.getWidth() * m_pParent->m_kinectCam.getHeight() * m_pParent->m_kinectCam.getBpp();
	delete m_pParent->m_pBuffer;
	m_pParent->m_pBuffer = 0;
	m_pParent->m_pBuffer = new BYTE[m_pParent->m_pBufferSize];
 

	std::ostringstream stringStream;
	stringStream << "Width: " << lWidth << " Height: " << lHeight << " Framerate : " << plFramesPerSecond ;
	std::string copyOfStr = "SetFormat : " + stringStream.str() ;
	MessageBox(0, copyOfStr.c_str() ,"",0);
 
    m_mt = *pmt;
    IPin* pin; 
    ConnectedTo(&pin);
    if(pin)
    {
        IFilterGraph *pGraph = m_pParent->GetGraph();
        pGraph->Reconnect(this);
    }
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CVCamStream::GetFormat(AM_MEDIA_TYPE **ppmt)
{
    *ppmt = CreateMediaType(&m_mt);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CVCamStream::GetNumberOfCapabilities(int *piCount, int *piSize)
{
    *piCount = BPPInit;
    *piSize = sizeof(VIDEO_STREAM_CONFIG_CAPS);
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CVCamStream::GetStreamCaps(int iIndex, AM_MEDIA_TYPE **pmt, BYTE *pSCC)
{
    *pmt = CreateMediaType(&m_mt);
    DECLARE_PTR(VIDEOINFOHEADER, pvi, (*pmt)->pbFormat);

//    if (iIndex == 0) iIndex = 4;
    if (iIndex == 0) iIndex = BPPInit;
	
	pvi->bmiHeader.biCompression = BI_RGB;
    pvi->bmiHeader.biBitCount    = 24;
    pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_pParent->m_kinectCam.getWidth();//80 * iIndex;
    pvi->bmiHeader.biHeight     = m_pParent->m_kinectCam.getHeight();//60 * iIndex;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;

    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle

    (*pmt)->majortype = MEDIATYPE_Video;
    (*pmt)->subtype = MEDIASUBTYPE_RGB24;
    (*pmt)->formattype = FORMAT_VideoInfo;
    (*pmt)->bTemporalCompression = FALSE;
    (*pmt)->bFixedSizeSamples= TRUE;//FALSE;
    (*pmt)->lSampleSize = pvi->bmiHeader.biSizeImage;
    (*pmt)->cbFormat = sizeof(VIDEOINFOHEADER);
    
    DECLARE_PTR(VIDEO_STREAM_CONFIG_CAPS, pvscc, pSCC);
    
    pvscc->guid = FORMAT_VideoInfo;
    pvscc->VideoStandard = AnalogVideo_None;
    pvscc->InputSize.cx = m_pParent->m_kinectCam.getWidth();
    pvscc->InputSize.cy = m_pParent->m_kinectCam.getHeight();
    pvscc->MinCroppingSize.cx = varX;
    pvscc->MinCroppingSize.cy = varY;
    pvscc->MaxCroppingSize.cx = m_pParent->m_kinectCam.getWidth();
    pvscc->MaxCroppingSize.cy = m_pParent->m_kinectCam.getHeight();
    pvscc->CropGranularityX = 0;//varX;
    pvscc->CropGranularityY = 0;//varY;
    pvscc->CropAlignX = 0;
    pvscc->CropAlignY = 0;

    pvscc->MinOutputSize.cx = varX;
    pvscc->MinOutputSize.cy = varY;
    pvscc->MaxOutputSize.cx = m_pParent->m_kinectCam.getWidth();
    pvscc->MaxOutputSize.cy = m_pParent->m_kinectCam.getHeight();
    pvscc->OutputGranularityX = 0;
    pvscc->OutputGranularityY = 0;
    pvscc->StretchTapsX = 0;
    pvscc->StretchTapsY = 0;
    pvscc->ShrinkTapsX = 0;
    pvscc->ShrinkTapsY = 0;

	int MinFps = 10;
	int MaxFps = 120;

    pvscc->MinFrameInterval = (REFERENCE_TIME)(10000000/MinFps); //200000;//200000;   //120 fps (1/50) * 10 000 000
    pvscc->MaxFrameInterval =  (REFERENCE_TIME)(10000000/MaxFps); //50000000;// 50000000; // 0.2 fps
    pvscc->MinBitsPerSecond = (varX * varY * 3 * BPPInit) / 5;
    pvscc->MaxBitsPerSecond = m_pParent->m_kinectCam.getWidth() * m_pParent->m_kinectCam.getHeight() * 3 * BPPInit * MaxFps;

    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// IKsPropertySet
//////////////////////////////////////////////////////////////////////////


HRESULT CVCamStream::Set(REFGUID guidPropSet, DWORD dwID, void *pInstanceData, 
                        DWORD cbInstanceData, void *pPropData, DWORD cbPropData)
{// Set: Cannot set any properties.
    return E_NOTIMPL;
}

// Get: Return the pin category (our only property). 
HRESULT CVCamStream::Get(
    REFGUID guidPropSet,   // Which property set.
    DWORD dwPropID,        // Which property in that set.
    void *pInstanceData,   // Instance data (ignore).
    DWORD cbInstanceData,  // Size of the instance data (ignore).
    void *pPropData,       // Buffer to receive the property data.
    DWORD cbPropData,      // Size of the buffer.
    DWORD *pcbReturned     // Return the size of the property.
)
{
    if (guidPropSet != AMPROPSETID_Pin)             return E_PROP_SET_UNSUPPORTED;
    if (dwPropID != AMPROPERTY_PIN_CATEGORY)        return E_PROP_ID_UNSUPPORTED;
    if (pPropData == NULL && pcbReturned == NULL)   return E_POINTER;
    
    if (pcbReturned) *pcbReturned = sizeof(GUID);
    if (pPropData == NULL)          return S_OK; // Caller just wants to know the size. 
    if (cbPropData < sizeof(GUID))  return E_UNEXPECTED;// The buffer is too small.
        
    *(GUID *)pPropData = PIN_CATEGORY_CAPTURE;
    return S_OK;
}

// QuerySupported: Query whether the pin supports the specified property.
HRESULT CVCamStream::QuerySupported(REFGUID guidPropSet, DWORD dwPropID, DWORD *pTypeSupport)
{
    if (guidPropSet != AMPROPSETID_Pin) return E_PROP_SET_UNSUPPORTED;
    if (dwPropID != AMPROPERTY_PIN_CATEGORY) return E_PROP_ID_UNSUPPORTED;
    // We support getting this property, but not setting it.
    if (pTypeSupport) *pTypeSupport = KSPROPERTY_SUPPORT_GET; 
    return S_OK;
}
