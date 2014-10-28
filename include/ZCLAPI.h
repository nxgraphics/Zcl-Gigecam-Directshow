// ZCL version 2.10.4 API Header File
// Copyright (C) 2005-2012 TechnoScope Co., Ltd.

#ifndef	_ZCLAPIH_
#define	_ZCLAPIH_

#pragma pack( push, 4 )

#ifdef __cplusplus
extern "C" {
#endif

#define ZCL_LIBRARY_STRUCT_VERSION		210

#undef	Dllport
#ifdef	_ZCLCREATEDLL_
#define	Dllport	__declspec( dllexport )  __cdecl
#define	HCAMERA					pCAMERA_HANDLE
#define	HCTBL					pCTABLE_HANDLE
#else
#define	Dllport	__declspec( dllimport )  __cdecl
#define	HCAMERA					PVOID
#define	HCTBL					PVOID
#endif


typedef enum ZCL_STDMODE
{
	ZCL_QQVGA				= 0,		//   160 x  120 YUV(4:4:4)
	ZCL_QVGA,							//   320 x  240 YUV(4:2:2)
	ZCL_VGA_YUV1,						//   640 x  480 YUV(4:1:1)
	ZCL_VGA_YUV2,						//   640 x  480 YUV(4:2:2)
	ZCL_VGA_RGB,						//   640 x  480 RGB
	ZCL_VGA_MONO,						//   640 x  480 Mono
	ZCL_VGA_MONO16,						//   640 x  480 Mono16
	ZCL_SVGA_YUV,						//   800 x  600 YUV(4:2:2)
	ZCL_SVGA_RGB,						//   800 x  600 RGB
	ZCL_SVGA_MONO,						//   800 x  600 MONO
	ZCL_SVGA_MONO16,					//   800 x  600 MONO16
	ZCL_XGA_YUV,						//	1024 x  768 YUV(4:2:2)
	ZCL_XGA_RGB,						//	1024 x  768 RGB
	ZCL_XGA_MONO,						//	1024 x  768 MONO
	ZCL_XGA_MONO16,						//	1024 x  768 MONO16
	ZCL_SXGA_YUV,						//	1280 x  960 YUV(4:2:2)
	ZCL_SXGA_RGB,						//	1280 x  960 RGB
	ZCL_SXGA_MONO,						//	1280 x  960 MONO
	ZCL_SXGA_MONO16,					//	1280 x  960 MONO16
	ZCL_UXGA_YUV,						//	1600 x 1200 YUV(4:2:2)
	ZCL_UXGA_RGB,						//	1600 x 1200 RGB
	ZCL_UXGA_MONO,						//	1600 x 1200 MONO
	ZCL_UXGA_MONO16						//	1600 x 1200 MONO16
} ZCL_STDMODE;


typedef enum ZCL_FPS
{
	ZCL_Fps_1875			= 0,		//	FrameRate_0 (1.875fps)
	ZCL_Fps_375,						//	FrameRate_1 (3.75fps)
	ZCL_Fps_75,							//	FrameRate_2 (7.5fps)
	ZCL_Fps_15,							//	FrameRate_3 (15fps)
	ZCL_Fps_30,							//	FrameRate_4 (30fps)
	ZCL_Fps_60,							//	FrameRate_5 (60fps)
	ZCL_Fps_120,						//	FrameRate_6 (120fps)
	ZCL_Fps_240							//	FrameRate_7 (240fps)
} ZCL_FPS;


typedef enum ZCL_EXTMODE
{
	ZCL_Mode_0				= 0,		//	Mode_0
	ZCL_Mode_1,							//	Mode_1
	ZCL_Mode_2,							//	Mode_2
	ZCL_Mode_3,							//	Mode_3
	ZCL_Mode_4,							//	Mode_4
	ZCL_Mode_5,							//	Mode_5
	ZCL_Mode_6,							//	Mode_6
	ZCL_Mode_7,							//	Mode_7
	ZCL_Mode_8,							//	Mode_8
	ZCL_Mode_9,							//	Mode_9
	ZCL_Mode_10,						//	Mode_10
	ZCL_Mode_11,						//	Mode_11
	ZCL_Mode_12,						//	Mode_12
	ZCL_Mode_13,						//	Mode_13
	ZCL_Mode_14,						//	Mode_14
	ZCL_Mode_15,						//	Mode_15
	ZCL_Mode_16,						//	Mode_16
	ZCL_Mode_17,						//	Mode_17
	ZCL_Mode_18,						//	Mode_18
	ZCL_Mode_19,						//	Mode_19
	ZCL_Mode_20,						//	Mode_20
	ZCL_Mode_21,						//	Mode_21
	ZCL_Mode_22,						//	Mode_22
	ZCL_Mode_23,						//	Mode_23
	ZCL_Mode_24,						//	Mode_24
	ZCL_Mode_25,						//	Mode_25
	ZCL_Mode_26,						//	Mode_26
	ZCL_Mode_27,						//	Mode_27
	ZCL_Mode_28,						//	Mode_28
	ZCL_Mode_29,						//	Mode_29
	ZCL_Mode_30,						//	Mode_30
	ZCL_Mode_31							//	Mode_31
} ZCL_EXTMODE;


typedef enum ZCL_COLORID
{
	ZCL_MONO				= 0,		//	MONO			8bit No Conv
	ZCL_YUV411,							//	YUV411			8bit
	ZCL_YUV422,							//	YUV422			8bit
	ZCL_YUV444,							//	YUV444			8bit
	ZCL_RGB,							//	RGB				8bit
	ZCL_MONO16,							//	MONO16			16bit
	ZCL_RGB16,							//	RGB16			16bit
	ZCL_SMONO16,						//	Signed MONO16	16bit
	ZCL_SRGB16,							//	Signed RGB16	16bit
	ZCL_RAW,							//	RAW				8bit
	ZCL_RAW16,							//	RAW16			16bit
	ZCL_MONO12,							//	MONO			12bit
	ZCL_RAW12,							//	RAW				12bit

	ZCL_MONO10,							//	MONO			10bit
	ZCL_RAW10,							//	RAW				10bit
	ZCL_BGR,							//	BGR				8bit No Conv
	ZCL_BGR16,							//	BGR				16bit
	ZCL_RGBA,							//	RGBA			8bit
	ZCL_BGRA,							//	BGRA			8bit No Conv
	ZCL_RGB10G,							//	RGB V1			10bit
	ZCL_RGB10P,							//	RGB V2			10bit
	ZCL_RGB12,							//	RGB				12bit
	ZCL_RGB565,							//	RGB				5bit
	ZCL_BGR565,							//	BGR				5bit No Conv
	ZCL_YUV422Y,						//	YUV422			8bit
} ZCL_COLORID;


typedef	enum ZCL_PIXELFORMATID
{
	ZCL_PIX_MONO1P				= 0x01010038,
	ZCL_PIX_MONO4P				= 0x01010039,
	ZCL_PIX_MONO8				= 0x01080001,
	ZCL_PIX_MONO8S				= 0x01080002,
	ZCL_PIX_MONO8_SIGNED		= 0x01080002,
	ZCL_PIX_MONO10				= 0x01100003,
	ZCL_PIX_MONO10_PACKED		= 0x010C0004,
	ZCL_PIX_MONO10G12			= 0x010C003A,
	ZCL_PIX_MONO12				= 0x01100005,
	ZCL_PIX_MONO12_PACKED		= 0x010C0006,
	ZCL_PIX_MONO12G				= 0x010C003B,
	ZCL_PIX_MONO14				= 0x01100025,
	ZCL_PIX_MONO16				= 0x01100007,
	ZCL_PIX_BAYERGR8			= 0x01080008,
	ZCL_PIX_BAYERRG8			= 0x01080009,
	ZCL_PIX_BAYERGB8			= 0x0108000A,
	ZCL_PIX_BAYERBG8			= 0x0108000B,
	ZCL_PIX_BAYERGR10			= 0x0110000C,
	ZCL_PIX_BAYERRG10			= 0x0110000D,
	ZCL_PIX_BAYERGB10			= 0x0110000E,
	ZCL_PIX_BAYERBG10			= 0x0110000F,
	ZCL_PIX_BAYERGR12			= 0x01100010,
 	ZCL_PIX_BAYERRG12			= 0x01100011,
	ZCL_PIX_BAYERGB12			= 0x01100012,
	ZCL_PIX_BAYERBG12			= 0x01100013,
	ZCL_PIX_BAYERGR10_PACKED	= 0x010C0026,
	ZCL_PIX_BAYERGR10G12		= 0x010C003C,
	ZCL_PIX_BAYERRG10_PACKED	= 0x010C0027,
	ZCL_PIX_BAYERRG10G12		= 0x010C003D,
	ZCL_PIX_BAYERGB10_PACKED	= 0x010C0028,
	ZCL_PIX_BAYERGB10G12		= 0x010C003E,
	ZCL_PIX_BAYERBG10_PACKED	= 0x010C0029,
	ZCL_PIX_BAYERBG10G12		= 0x010C003F,
	ZCL_PIX_BAYERGR12_PACKED	= 0x010C002A,
 	ZCL_PIX_BAYERGR12G			= 0x010C0040,
	ZCL_PIX_BAYERRG12_PACKED	= 0x010C002B,
	ZCL_PIX_BAYERRG12G			= 0x010C0041,
	ZCL_PIX_BAYERGB12_PACKED	= 0x010C002C,
	ZCL_PIX_BAYERGB12G			= 0x010C0042,
	ZCL_PIX_BAYERBG12_PACKED	= 0x010C002D,
	ZCL_PIX_BAYERBG12G			= 0x010C0043,
	ZCL_PIX_BAYERGR16_PACKED	= 0x0110002E,
 	ZCL_PIX_BAYERGR16			= 0x0110002E,
	ZCL_PIX_BAYERRG16_PACKED	= 0x0110002F,
	ZCL_PIX_BAYERRG16			= 0x0110002F,
	ZCL_PIX_BAYERGB16_PACKED	= 0x01100030,
	ZCL_PIX_BAYERGB16			= 0x01100030,
	ZCL_PIX_BAYERBG16_PACKED	= 0x01100031,
	ZCL_PIX_BAYERBG16			= 0x01100031,
	ZCL_PIX_RGB8_PACKED			= 0x02180014,
	ZCL_PIX_RGB8				= 0x02180014,
	ZCL_PIX_BGR8_PACKED			= 0x02180015,
	ZCL_PIX_BGR8				= 0x02180015,
	ZCL_PIX_RGBA8				= 0x02180016,
	ZCL_PIX_BGRA8				= 0x02180017,
	ZCL_PIX_RGB10_PACKED		= 0x02300018,
	ZCL_PIX_RGB10				= 0x02300018,
	ZCL_PIX_BGR10_PACKED		= 0x02300019,
	ZCL_PIX_BGR10				= 0x02300019,
	ZCL_PIX_RGB12_PACKED		= 0x0230001A,
	ZCL_PIX_RGB12				= 0x0230001A,
	ZCL_PIX_BGR12_PACKED		= 0x0230001B,
	ZCL_PIX_BGR12				= 0x0230001B,
	ZCL_PIX_RGB16_PACKED		= 0x02300033,
	ZCL_PIX_RGB16				= 0x02300033,
	ZCL_PIX_RGB10V1_PACKED		= 0x0220001C,
	ZCL_PIX_RGB10G32			= 0x02200044,
	ZCL_PIX_RGB10V2_PACKED		= 0x0220001D,
	ZCL_PIX_RGB10P32			= 0x0220001D,
	ZCL_PIX_RGB12V1_PACKED		= 0x02240034,
	ZCL_PIX_RGB12G				= 0x02240045,
	ZCL_PIX_RGB565_PACKED		= 0x02100035,
	ZCL_PIX_RGB565P				= 0x02100035,
	ZCL_PIX_BGR565_PACKED		= 0x02100036,
	ZCL_PIX_BGR565P				= 0x02100036,
	ZCL_PIX_YUV411_PACKED		= 0x020C001E,
	ZCL_PIX_YUV411_8_UYYVYY		= 0x020C001E,
	ZCL_PIX_YUV422_PACKED		= 0x0210001F,
	ZCL_PIX_YUV422_8_UYVY		= 0x0210001F,
	ZCL_PIX_YUV422_YUYV_PACKED	= 0x02100032,
	ZCL_PIX_YUV422_8_YUYV		= 0x02100032,
	ZCL_PIX_YUV444_PACKED		= 0x02180020,
	ZCL_PIX_YUV8_UYV			= 0x02180020,
} ZCL_PIXELFORMATID;


typedef	enum ZCL_GIGESTREAMTYPE
{
	ZCL_GIGEIMAGEDATA				= 1,
	ZCL_GIGERAWDATA,
	ZCL_GIGEFILEDATA,
	ZCL_GIGECHUNKDATA,
	ZCL_GIGEEXTCHUNKDATA,
	ZCL_GIGEVENDORDATA				= 0x8000,
} ZCL_GIGESTREAMTYPE;


typedef	enum ZCL_FEATUREID
{
	ZCL_BRIGHTNESS			= 0,		//	Brightness
	ZCL_AE,								//	Auto Exposure
	ZCL_SHARPNESS,						//	Sharpness
	ZCL_WHITEBALANCE,					//	White Balance
	ZCL_HUE,							//	HUE
	ZCL_SATURATION,						//	Saturation
	ZCL_GAMMA,							//	Gamma
	ZCL_SHUTTER,						//	Shutter
	ZCL_GAIN,							//	Gain
	ZCL_IRIS,							//	Iris
	ZCL_FOCUS,							//	Focus
	ZCL_TEMPERATURE,					//	Temperature
	ZCL_TRIGGER,						//	Trigger
	ZCL_TRIGGER_DELAY,					//	Trigger Delay
	ZCL_WHITE_SHADING,					//	White Shading
	ZCL_FRAMERATE,						//	FrameRate
	ZCL_ZOOM,							//	Zoom
	ZCL_PAN,							//	Pan
	ZCL_TILT,							//	Tilt
	ZCL_OPTICAL_FILTER,					//	Optical Filter
	ZCL_ONE_SHOT,						//	One Shot
	ZCL_MULTI_SHOT,						//	Multi Shot
	ZCL_POWER_ONOFF,					//	Power On Off
	ZCL_MEMORYCHANNEL,					//	Memory Channel
} ZCL_FEATUREID;


typedef enum ZCL_TRIGGERMODE
{
	ZCL_Trigger_Mode0		= 0,		//	Trigger Mode0
	ZCL_Trigger_Mode1,					//	Trigger Mode1
	ZCL_Trigger_Mode2,					//	Trigger Mode2
	ZCL_Trigger_Mode3,					//	Trigger Mode3
	ZCL_Trigger_Mode4,					//	Trigger Mode4
	ZCL_Trigger_Mode5,					//	Trigger Mode5
	ZCL_Trigger_Mode14		= 14,		//	Trigger Mode14
	ZCL_Trigger_Mode15					//	Trigger Mode15
} ZCL_TRIGGERMODE;


typedef enum ZCL_TRIGGERSOURCE
{
	ZCL_Trigger_Source0		= 0,		//	Trigger Source0
	ZCL_Trigger_Source1,				//	Trigger Source1
	ZCL_Trigger_Source2,				//	Trigger Source2
	ZCL_Trigger_Source3,				//	Trigger Source3
	ZCL_Software_Trigger	= 7			//	Software Trigger
} ZCL_TRIGGERSOURCE;


typedef enum ZCL_TRANSMITSPEED
{
	ZCL_S100M				= 0,		//	100M
	ZCL_S200M,							//	200M
	ZCL_S400M,							//	400M
	ZCL_S800M,							//	800M
	ZCL_S1600M,							//	1.6G
	ZCL_S3200M							//	3.2G
} ZCL_TRANSMITSPEED;


typedef enum ZCL_CONVERTMODE
{
	ZCL_C24bit				= 0,		//	24bit
	ZCL_C16bit,							//	16bit
	ZCL_C15bit,							//	15bit
	ZCL_CFilter,						//	Color Filter
	ZCL_C32bit,							//	32bit
	ZCL_CFilterRAW8G,					//	RAW8 + G
	ZCL_CFilterRAW16,					//	RAW16
	ZCL_CFilterRAW16G,					//	RAW16 + G
	ZCL_CFilterRAW12,					//	RAW12
	ZCL_CFilterRAW12G,					//	RAW12 + G
	ZCL_CFilterRAW10,					//	RAW10
	ZCL_CFilterRAW10G,					//	RAW10 + G
	ZCL_CFilter24RAW8,					//	RAW8
	ZCL_CFilter24RAW8G,					//	RAW8 + G
	ZCL_CFilter24RAW16,					//	RAW16
	ZCL_CFilter24RAW16G,				//	RAW16 + G
	ZCL_CFilter24RAW12,					//	RAW12
	ZCL_CFilter24RAW12G,				//	RAW12 + G
	ZCL_CFilter24RAW10,					//	RAW10
	ZCL_CFilter24RAW10G,				//	RAW10 + G
	ZCL_CFilterRAW8 = ZCL_CFilter,		//	RAW8
} ZCL_CONVERTMODE;


typedef enum ZCL_CFILTERMODE
{
	ZCL_FRGGB				= 0,		//	RG/GB
	ZCL_FGBRG,							//	GB/RG
	ZCL_FGRBG,							//	GR/BG
	ZCL_FBGGR							//	BG/GR
} ZCL_CFILTERMODE;


typedef enum ZCL_SHIFTID
{
										//	15 14 13 12 ..... 2 1 0
										//
	ZCL_SFT0				= 0,		//	7-0 bit
	ZCL_SFT1,							//	8-1 bit
	ZCL_SFT2,							//	9-2 bit
	ZCL_SFT3,							//	10-3 bit
	ZCL_SFT4,							//	11-4 bit
	ZCL_SFT5,							//	12-5 bit
	ZCL_SFT6,							//	13-6 bit
	ZCL_SFT7,							//	14-7 bit
	ZCL_SFT8							//	15-8 bit
} ZCL_SHIFTID;


typedef enum ZCL_STOREMODE
{
	ZCL_BMPmode				= 0,		//	BMP file mode
	ZCL_MEMmode,						//	MEMORY mode
	ZCL_BMPmodeLR,						//	BMP file mode (Flip horizontal)
	ZCL_MEMmodeLR,						//	MEMORY mode (Flip horizontal)
} ZCL_STOREMODE;


typedef	enum ZCL_SETREQID
{
	ZCL_FEATURE_OFF			= 0,		//	Feature function stop
	ZCL_ONE_PUSH,						//	Execution of One Push
	ZCL_AUTO,							//	Automatic setting
	ZCL_VALUE,							//	Manual value setting
	ZCL_ABSVALUE,						//	ABS manual value setting
	ZCL_ABSONE_PUSH,					//	ABS Execution of One Push
	ZCL_ABSAUTO							//	ABS Automatic setting
} ZCL_SETREQID;


typedef	enum ZCL_ENDIAN
{
	ZCL_BIGENDIAN			= 0,		//	Big Endian
	ZCL_LITTLEENDIAN					//	Little Endian
} ZCL_ENDIAN;


typedef	enum ZCL_CAMERATYPE
{
	ZCL_CAMERA1394			= 0,
	ZCL_CAMERAGIGE
} ZCL_CAMERATYPE;


//Status Code
typedef enum STATUS_SYSTEMCODE
{
	STATUSZCL_BUSRESET		= 1,		//	Bus reset generation
	STATUSZCL_POWERUP					//	Return from sleep of system
} STATUS_SYSTEMCODE;


typedef	enum STATUS_RTNCODE
{
	STATUSZCL_NO_ERROR = 0,				//	No error
	STATUSZCL_COMPLETE = 0,				//	Success in processing
	STATUSZCL_PARAMETER_ERROR,			//	A parameter is illegal
	STATUSZCL_BUFFER_SHORT,				//	A buffer is short

	STATUSZCL_OPEN_ERROR,				//	Failure in the opening of a camera
	STATUSZCL_OPENED,					//	A camera has been already opened
	STATUSZCL_CANNOT_FOUND,				//	A camera cannot be found
	STATUSZCL_NO_OPEN,					//	A camera is not opened

	STATUSZCL_COMMUNICATE_ERROR,		//	Failure in communication

	STATUSZCL_DATA_INACCURACY,			//	The acquired data is inaccurate
	STATUSZCL_NO_SUPPORT,				//	No function is mounted
	STATUSZCL_VMODE_ERROR,				//	Camera parameter setting error
	STATUSZCL_FEATURE_ERROR,			//	Camera feature control error
	STATUSZCL_VALUE_ERROR,				//	Camera parameter setting error(AbsValue, Value)
	STATUSZCL_SELFCLEAR_ERROR,			//	A self-clear flag is not cleared
	STATUSZCL_IMAGE_ERROR,				//	Image size setting error
	STATUSZCL_RESOURCE_ERROR,			//	Requested. during securing of isochronous resources
	STATUSZCL_NOTRESOURCE_ERROR,		//	Isochronous resources are not secured
	STATUSZCL_ALLOCATE_ERROR,			//	Failure in the securing of isochronous resources
	STATUSZCL_STARTED_ERROR,			//	The start state has been already reached
	STATUSZCL_NOTSTART_ERROR,			//	The start state is not reached
	STATUSZCL_REQUEST_ERROR,			//	Failure in request
	STATUSZCL_REQUEST_TIMEOUT,			//	Time-out in request

	STATUSZCL_SOFTTRIGGER_BUSY,			//	During Softtrigger practice
	STATUSZCL_MULTISLOPE_ERROR,			//	Multi-slope setting error

	STATUSZCL_ABORTEXEC_ERROR,			//	I was working to cancel it, and it was depended

	STATUSZCL_REQUEST_USERCANCEL,		//	user cancel in request
	STATUSZCL_REQUEST_BUSRESETCANCEL,	//	busReset cancel in request

	STATUSZCL_REQUEST_EXEC,				//	Request exective 

	STATUSZCL_STRUCTVERSION_ERROR,		//	The version of the structure body is unjust

	STATUSZCL_FUNCTION_ONLY1394,		//	Functions only for 1394 cameras
	STATUSZCL_FUNCTION_ONLYGIGE,		//	Functions only for GigE cameras
	STATUSZCL_GIGE_NOTMULTICAST,		//	Not MultiCast IPAddr 
	STATUSZCL_GIGE_IPADDR_ERROR,		//	Not MultiCast IPAddr 

	STATUSZCL_UNDEF_ERROR = 99			//	Other error
} STATUS_RTNCODE;


#pragma warning( push )
#pragma warning( disable : 4200 )


//	ZCLCameraInfo
typedef struct ZCL_CAMERAINFO
{
	UINT64				UID;
	BYTE				VendorName[ 256 ];
	BYTE				ModelName[ 256 ];
} ZCL_CAMERAINFO, *pZCL_CAMERAINFO;


//	ZCLGigECameraInfo
typedef struct ZCL_GIGECAMERAINFO
{
	BYTE				MACAddr[ 6 ];
	WORD				Spec_Major;
	WORD				Spec_Minor;
	DWORD				Dev_Mode;
	BYTE				VendorName[ 32 ];
	BYTE				ModelName[ 32 ];
	BYTE				Dev_Ver[ 32 ];
	BYTE				Vendor_Info[ 48 ];
	BYTE				SerialNumber[ 16 ];
	BYTE				UserName[ 16 ];
} ZCL_GIGECAMERAINFO, *pZCL_GIGECAMERAINFO;


//	ZCLGetList
typedef struct ZCL_LIST
{
	DWORD				CameraCount;	//	Number of connected cameras or numbers of Info arrays
	ZCL_CAMERAINFO		Info[ 0 ];
} ZCL_LIST, *pZCL_LIST;


//	ZCLSetCameraMode
//	ZCLNowCameraMode
//	ZCLCheckCameraMode
typedef struct ZCL_CAMERAMODE
{
	BOOL				StdMode_Flag;	//	Standard mode flag
	union U
	{
		//	Standard mode
		struct STD
		{
			ZCL_STDMODE			Mode;
			ZCL_FPS				FrameRate;
		} Std;

		//	Enhancing mode
		struct EXT
		{
			ZCL_EXTMODE			Mode;
			ZCL_COLORID			ColorID;
			ZCL_CFILTERMODE		FilterID;
		} Ext;
	} u;
} ZCL_CAMERAMODE, *pZCL_CAMERAMODE;


//	ZCLGetStreamMode
typedef struct ZCL_GETSTREAMMODE
{
	WORD				MinWidth;
	WORD				MinHeight;
	WORD				MaxWidth;
	WORD				MaxHeight;
	WORD				IncWidth;
	WORD				IncHeight;
	WORD				IncOffsetX;
	WORD				IncOffsetY;
	float				MinFrameRate;
	float				MaxFrameRate;
	BOOL				InqFrameRateAuto;
	WORD				Width;
	WORD				Height;
	WORD				OffsetX;
	WORD				OffsetY;
	ZCL_PIXELFORMATID	PixelFormat;
	BOOL				FrameRateAuto;
	float				FrameRate;
} ZCL_GETSTREAMMODE, *pZCL_GETSTREAMMODE;


//	ZCLSetStreamMode
typedef struct ZCL_SETSTREAMMODE
{
	WORD				Width;
	WORD				Height;
	WORD				OffsetX;
	WORD				OffsetY;
	ZCL_PIXELFORMATID	PixelFormat;
	BOOL				FrameRateAuto;
	float				FrameRate;
} ZCL_SETSTREAMMODE, *pZCL_SETSTREAMMODE;


//	ZCLGetStreamMode
//	ZCLSetStreamMode
typedef struct ZCL_HEARTBEATMODE
{
	BOOL				Exec_Flag;
	DWORD				TimeCount;
} ZCL_HEARTBEATMODE, *pZCL_HEARTBEATMODE;


//	ZCLGetPixelFormat
typedef struct ZCL_PIXELFORMATLIST
{
	DWORD				Count;
	ZCL_PIXELFORMATID	PixelFormat[ 32 ];
} ZCL_PIXELFORMATLIST, *pZCL_PIXELFORMATLIST;


//	ZCLGetExtModeInfo
typedef	struct ZCL_EXTMODEINFO
{
	DWORD				ModeCount;		//	Number of enhancing mode
	struct MODE
	{
		WORD				MaxWidth;
		WORD				MaxHeight;
		WORD				UnitSizeX;
		WORD				UnitSizeY;
		WORD				UnitPosX;
		WORD				UnitPosY;
		WORD				C_MONO:1;
		WORD				C_YUV411:1;
		WORD				C_YUV422:1;
		WORD				C_YUV444:1;
		WORD				C_RGB:1;
		WORD				C_MONO16:1;
		WORD				C_RGB16:1;
		WORD				C_SMONO16:1;
		WORD				C_SRGB16:1;
		WORD				C_RAW:1;
		WORD				C_RAW16:1;
		WORD				C_MONO12:1;
		WORD				C_RAW12:1;
		WORD				C_MONO10:1;
		WORD				C_RAW10:1;
		WORD				C_BGR:1;
		WORD				C_BGR16:1;
		WORD				C_RGBA:1;
		WORD				C_BGRA:1;
		WORD				C_RGB10G:1;
		WORD				C_RGB10P:1;
		WORD				C_RGB12:1;
		WORD				C_RGB565:1;
		WORD				C_BGR565:1;
		WORD				C_YUV422Y:1;
	} Mode[ 32 ];
} ZCL_EXTMODEINFO, *pZCL_EXTMODEINFO;


//	ZCLCheckFeature
typedef	struct ZCL_CHECKFEATURE
{
	DWORD				Version;
	ZCL_FEATUREID		FeatureID;
	BOOL				PresenceFlag;

	union U
	{
		//	Function commonness definition
		struct STD
		{
			BYTE				Abs_Inq:1;
			BYTE				One_Push_Inq:1;
			BYTE				ReadOut_Inq:1;
			BYTE				On_Off_Inq:1;
			BYTE				Auto_Inq:1;
			BYTE				Manual_Inq:1;
			DWORD				Min_Value;
			DWORD				Max_Value;
			float				Abs_Min_Value;
			float				Abs_Max_Value;
		} Std;

		//	Trigger
		struct TRIGGER
		{
			BYTE				Abs_Inq:1;
			BYTE				ReadOut_Inq:1;
			BYTE				On_Off_Inq:1;
			BYTE				Polarity_Inq:1;
			BYTE				Value_Read_Inq:1;
			BYTE				Source0:1;
			BYTE				Source1:1;
			BYTE				Source2:1;
			BYTE				Source3:1;
			BYTE				Software:1;
			BYTE				Mode0:1;
			BYTE				Mode1:1;
			BYTE				Mode2:1;
			BYTE				Mode3:1;
			BYTE				Mode4:1;
			BYTE				Mode5:1;
			BYTE				Mode14:1;
			BYTE				Mode15:1;
			float				Abs_Min_Value;
			float				Abs_Max_Value;
		} Trigger;
		BYTE				Max_MemChannel;
	} u;
} ZCL_CHECKFEATURE, *pZCL_CHECKFEATURE;


//	ZCLGetFeatureValue
typedef	struct ZCL_GETFEATUREVALUE
{
	DWORD				Version;
	ZCL_FEATUREID		FeatureID;

	union U
	{
		//	Function commonness definition
		struct STD
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Auto_M:1;
			DWORD				Value;
			float				Abs_Value;
		} Std;

		//	WhiteBalance
		struct WHITEBALANCE
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Auto_M:1;
			DWORD				UB_Value;
			DWORD				VR_Value;
			float				Abs_Value;
		} WhiteBalance;

		//	Temperature
		struct TEMPERATURE
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Auto_M:1;
			DWORD				Target_Value;
			DWORD				Temp_Value;
			float				Abs_Value;
		} Temperature;

		//	Trigger
		struct TRIGGER
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Rcvd:1;
			BYTE				Polarity:1;
			BYTE				Value:1;
			BYTE				Source;
			BYTE				Mode;
			DWORD				Parameter;
			float				Abs_Value;
		} Trigger;

		//	TriggerDelay
		struct TRIGGERDELAY
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Rcvd:1;
			DWORD				Value;
			float				Abs_Value;
		} TriggerDelay;

		//	WhiteShading
		struct WHITESHADING
		{
			BYTE				Abs:1;
			BYTE				On_Off:1;
			BYTE				Auto_M:1;
			BYTE				R_Value;
			BYTE				G_Value;
			BYTE				B_Value;
			float				Abs_Value;
		} WhiteShading;

		BOOL				Exec_Flag;
		BOOL				PowerOn_Flag;
	} u;
} ZCL_GETFEATUREVALUE, *pZCL_GETFEATUREVALUE;


//	ZCLSetFeatureValue
typedef	struct ZCL_SETFEATUREVALUE
{
	DWORD				Version;
	ZCL_SETREQID		ReqID;
	ZCL_FEATUREID		FeatureID;

	union U
	{
		//	Function commonness definition
		struct STD
		{
			DWORD				Value;
			float				Abs_Value;
		} Std;

		// WhiteBalance
		struct WHITEBALANCE
		{
			DWORD				UB_Value;
			DWORD				VR_Value;
			float				Abs_Value;
		} WhiteBalance;

		//	Trigger
		struct TRIGGER
		{
			BYTE				Polarity:1;
			BYTE				Source;
			BYTE				Mode;
			DWORD				Parameter;
			float				Abs_Value;
		} Trigger;

		//	WhiteShading
		struct WHITESHADING
		{
			BYTE				R_Value;
			BYTE				G_Value;
			BYTE				B_Value;
			float				Abs_Value;
		} WhiteShading;
	} u;
} ZCL_SETFEATUREVALUE, *pZCL_SETFEATUREVALUE;


//	ZCLGetImageInfo
typedef	struct ZCL_GETIMAGEINFO
{
	BOOL				StdMode_Flag;
	struct IMAGE
	{
		WORD				PosX;
		WORD				PosY;
		WORD				Width;
		WORD				Height;
		ZCL_COLORID			ColorID;
		DWORD				DataLength;		//	Effective data length of image data
		DWORD				Buffer;			//	Necessary buffer length for image data
	} Image;

	struct EXT
	{
		WORD				MaxImageX;
		WORD				MaxImageY;
		WORD				UnitSizeX;
		WORD				UnitSizeY;
		WORD				UnitPosX;
		WORD				UnitPosY;
	} Ext;
} ZCL_GETIMAGEINFO, *pZCL_GETIMAGEINFO;


//	ZCLSetImageInfo
typedef	struct ZCL_SETIMAGEINFO
{
	WORD				PosX;
	WORD				PosY;
	WORD				Width;
	WORD				Height;
	BOOL				MaxSize_Flag;
} ZCL_SETIMAGEINFO, *pZCL_SETIMAGEINFO;


typedef	union ZCL_STREAMCONT
{
	struct IMAGE
	{
		DWORD				Pixel_Type;
		DWORD				Width;
		DWORD				Height;
		DWORD				Offset_X;
		DWORD				Offset_Y;
		WORD				Padding_X;
		WORD				Padding_Y;
		DWORD				Size_Y;
	} Image;

	struct RAW
	{
		UINT64				DataSize;
	} Raw;

	struct FILE
	{
		UINT64				DataSize;
		BYTE				FileName[ 512 ];
	} File;

	struct CHUNK
	{
		DWORD				DataSize;
	} Chunk;

	struct EXT_CHUNK
	{
		DWORD					Pixel_Type;
		DWORD					Width;
		DWORD					Height;
		DWORD					Offset_X;
		DWORD					Offset_Y;
		WORD					Padding_X;
		WORD					Padding_Y;
		DWORD					DataSize;
		DWORD					Size_Y;
		DWORD					Chunk_ID;
	} Ext_Chunk;

	struct VENDOR
	{
		BYTE					VendorData[ 512 ];
	} Vendor;
} ZCL_STREAMCONT, *pZCL_STREAMCONT;


//	ZCLStreamComplete
typedef	struct ZCL_STREAMINFO
{
	ULONG				Ver;
	union U
	{
		struct V0
		{
			WORD				Stream_Type;
			WORD				Fream_ID;
			UINT64				TimeStamp;

			ZCL_STREAMCONT		Contents;

		} v0;

		struct V1
		{
			ULONG				Stream_Type;
			UINT64				Fream_ID;
			UINT64				TimeStamp;

			ZCL_STREAMCONT		Contents;
		} v1;
	} u;
} ZCL_STREAMINFO, *pZCL_STREAMINFO;


typedef	struct ZCL_IMAGEDATAINFO
{
	ZCL_CAMERATYPE		CameraType;
	union U
	{
		struct C1394
		{
			ZCL_TRANSMITSPEED	Speed;
			DWORD				CycleTime_S;
			DWORD				CycleCount_S;
			DWORD				CycleTime_E;
			DWORD				CycleCount_E;
		} C1394;

		struct CGIGE
		{
			BYTE				*pPktInfo;
			DWORD				PktInfoLen;
			ZCL_STREAMINFO		StreamInfo;
		} CGigE;
	} u;
} ZCL_IMAGEDATAINFO, *pZCL_IMAGEDATAINFO;


typedef enum ZCL_CFILTERMODE_SONY
{
	ZCL_SONYGBRG			= 0,		//	GB/RG
	ZCL_SONYBGGR,						//	BG/GR
	ZCL_SONYRGGB,						//	RG/GB
	ZCL_SONYGRBG,						//	GR/BG
} ZCL_CFILTERMODE_SONY;


//	ZCLGetRegister
//	ZCLGetExtRegister
//	ZCLSetRegister
//	ZCLSetExtRegister
typedef	struct ZCL_REGISTER
{
	DWORD				Offset;
	DWORD				Size;
	PVOID				Value;
} ZCL_REGISTER, *pZCL_REGISTER;


//	ZCLGigEGetRegister
//	ZCLGigESetRegister
typedef	struct ZCL_GIGEREGISTER
{
	DWORD				Count;
	DWORD				Addr[ 135 ];
	DWORD				Value[ 135 ];
} ZCL_GIGEREGISTER, *pZCL_GIGEREGISTER;


typedef	struct ZCL_COLORVALUE
{
	double				a;
	double				b;
	double				c;
	double				d;
} ZCL_COLORVALUE, *pZCL_COLORVALUE;


typedef	struct ZCL_COLORMODE
{
	ZCL_COLORID			ColorID;
	ZCL_CFILTERMODE		CFilter;
	ZCL_STOREMODE		StoreMode;
	ZCL_ENDIAN			EndianMode;
	BOOL				Parallel_Flag;
} ZCL_COLORMODE, *pZCL_COLORMODE;


//	ZCLOpenGigE
//	ZCLWatchOpenGigE
typedef	struct ZCL_OPENREQUEST
{
	UINT64				UID;
	BYTE				UserName[ 16 ];
} ZCL_OPENREQUEST, *pZCL_OPENREQUEST;


typedef	VOID	(CALLBACK* SYSTEMFUNC)( STATUS_SYSTEMCODE, PVOID );
typedef	VOID	(CALLBACK* IMAGEFUNC)( HCAMERA, BYTE*, DWORD, DWORD, DWORD, ZCL_IMAGEDATAINFO*, PVOID );


//API------------------------------------------------------------------------------------------------------------
VOID			Dllport ZCLSetCallBack( PVOID, SYSTEMFUNC );
VOID			Dllport ZCLSetStructVersion( DWORD );
STATUS_RTNCODE	Dllport	ZCLGetLastError( VOID );
BOOL			Dllport	ZCLGetList( ZCL_LIST * );
BOOL			Dllport	ZCLOpen( UINT64, HCAMERA* );
BOOL			Dllport	ZCLClose( HCAMERA );
BOOL			Dllport	ZCLCameraInfo( HCAMERA, ZCL_CAMERAINFO*, ZCL_TRANSMITSPEED* );
BOOL			Dllport	ZCLCameraBusInfo( HCAMERA, DWORD*, ZCL_CAMERATYPE* );
VOID			Dllport	ZCLAllClose( VOID );
BOOL			Dllport	ZCLCamera( HCAMERA, BOOL* );
BOOL			Dllport	ZCLCameraInit( HCAMERA );
BOOL			Dllport	ZCLCheckCameraMode( HCAMERA, ZCL_CAMERAMODE* );
BOOL			Dllport	ZCLSetCameraMode( HCAMERA, ZCL_CAMERAMODE* );
BOOL			Dllport	ZCLNowCameraMode( HCAMERA, ZCL_CAMERAMODE* );
BOOL			Dllport	ZCLGetExtModeInfo( HCAMERA, ZCL_EXTMODEINFO* );
BOOL			Dllport	ZCLSaveMem( HCAMERA, DWORD );
BOOL			Dllport	ZCLLoadMem( HCAMERA, DWORD );
BOOL			Dllport	ZCLCheckFeature( HCAMERA, ZCL_CHECKFEATURE* );
BOOL			Dllport	ZCLGetFeatureValue( HCAMERA, ZCL_GETFEATUREVALUE* );
BOOL			Dllport	ZCLSetFeatureValue( HCAMERA, ZCL_SETFEATUREVALUE* );
BOOL			Dllport	ZCLGetImageInfo( HCAMERA, ZCL_GETIMAGEINFO* );
BOOL			Dllport	ZCLSetImageInfo( HCAMERA, ZCL_SETIMAGEINFO* );
BOOL			Dllport	ZCLSetImageInfo2( HCAMERA, ZCL_SETIMAGEINFO*, DWORD*, DWORD* );
BOOL			Dllport	ZCLSetPktSize( HCAMERA, DWORD, DWORD* );
BOOL			Dllport	ZCLIsoAlloc( HCAMERA );
BOOL			Dllport	ZCLIsoRelease( HCAMERA );
BOOL			Dllport	ZCLIsoStart( HCAMERA, DWORD );
BOOL			Dllport	ZCLIsoStop( HCAMERA );
BOOL			Dllport	ZCLSoftTrigger( HCAMERA, BOOL );
BOOL			Dllport	ZCLImageReq( HCAMERA, BYTE*, DWORD );
BOOL			Dllport	ZCLImageCompleteWait( HCAMERA, BYTE*, ZCL_TRANSMITSPEED*, DWORD*, DWORD* );
BOOL			Dllport	ZCLImageCompleteWaitTimeOut( HCAMERA, BYTE*, ZCL_TRANSMITSPEED*, DWORD*, DWORD*, DWORD );
BOOL			Dllport	ZCLAbortImageReqAll( HCAMERA );
BOOL			Dllport	ZCLVSyncReq( HCAMERA, PVOID* );
BOOL			Dllport	ZCLVSyncCompleteWait( HCAMERA, PVOID );
BOOL			Dllport	ZCLVSyncCompleteWaitTimeOut( HCAMERA, PVOID, DWORD );
BOOL			Dllport ZCLSetImageCallBack( HCAMERA, PVOID, IMAGEFUNC, DWORD );
BOOL			Dllport	ZCLGetRegister( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLGetExtRegister( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLSetRegister( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLSetExtRegister( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLGetConfigROM( HCAMERA, DWORD* );
BOOL			Dllport	ZCLGetDataDepth( HCAMERA, DWORD* );
BOOL			Dllport	ZCLBroadcastPkt( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLBroadcastPktAll( HCAMERA, ZCL_REGISTER* );
DWORD			Dllport	ZCLGetLibraryRevision( VOID );
BOOL			Dllport	ZCLReset( VOID );
VOID			Dllport	ZCLReDetection( VOID );
BOOL			Dllport	ZCLShutterAbsAuto( HCAMERA );

BOOL			Dllport	ZCLOnePushAWB( HCAMERA );
BOOL			Dllport	ZCLOnePushAWBComplete( HCAMERA, DWORD );

/************************************************/
/*	Watch API									*/
/************************************************/
BOOL			Dllport	ZCLWatchOpen( UINT64, HCAMERA* );
BOOL			Dllport	ZCLWatchOpenGigE( ZCL_OPENREQUEST*, HCAMERA* );
BOOL			Dllport	ZCLWatchClose( HCAMERA );
BOOL			Dllport	ZCLWatchCamera( HCAMERA, BOOL* );
BOOL			Dllport	ZCLWatchAlloc( HCAMERA );
BOOL			Dllport	ZCLWatchRelease( HCAMERA );
BOOL			Dllport	ZCLWatchStart( HCAMERA );
BOOL			Dllport	ZCLWatchStop( HCAMERA );

/************************************************/
/*	GigE Only API								*/
/************************************************/
BOOL			Dllport	ZCLOpenGigE( ZCL_OPENREQUEST*, HCAMERA* );
BOOL			Dllport	ZCLGigECameraInfo( HCAMERA, ZCL_GIGECAMERAINFO*, DWORD* );
BOOL			Dllport	ZCLGetStreamMode( HCAMERA, ZCL_GETSTREAMMODE*, DWORD*, ZCL_HEARTBEATMODE* );
BOOL			Dllport	ZCLSetStreamMode( HCAMERA, ZCL_SETSTREAMMODE*, DWORD*, ZCL_HEARTBEATMODE* );
BOOL			Dllport	ZCLGetPixelFormat( HCAMERA, ZCL_PIXELFORMATLIST* );
BOOL			Dllport	ZCLBandAdjust( HCAMERA, BOOL, DWORD );
BOOL			Dllport	ZCLGigEGetPktSize( HCAMERA, DWORD*, DWORD*, DWORD*, DWORD* );
BOOL			Dllport	ZCLGigESetPktSize( HCAMERA, DWORD );
BOOL			Dllport	ZCLTestStream( HCAMERA, DWORD );
BOOL			Dllport	ZCLStreamAlloc( HCAMERA, BYTE*, BOOL );
BOOL			Dllport	ZCLStreamRelease( HCAMERA );
BOOL			Dllport	ZCLStreamStart( HCAMERA, DWORD );
BOOL			Dllport	ZCLStreamStop( HCAMERA );
BOOL			Dllport	ZCLStreamReq( HCAMERA, BYTE*, DWORD );
BOOL			Dllport	ZCLStreamComplete( HCAMERA, BYTE*, DWORD, ZCL_STREAMINFO*, BYTE**, DWORD* );
BOOL			Dllport	ZCLAbortStreamReqAll( HCAMERA );
BOOL			Dllport	ZCLGigEGetRegister( HCAMERA, ZCL_GIGEREGISTER* );
BOOL			Dllport	ZCLGigESetRegister( HCAMERA, ZCL_GIGEREGISTER* );
BOOL			Dllport	ZCLGigEGetMemory( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLGigESetMemory( HCAMERA, ZCL_REGISTER* );
BOOL			Dllport	ZCLGigEGetLUT( HCAMERA, DWORD, DWORD*, DWORD* );
BOOL			Dllport	ZCLGigESetLUT( HCAMERA, DWORD, DWORD*, DWORD* );

BOOL			Dllport	ZCLCreateConvHandle( HCTBL*, ZCL_CONVERTMODE, ZCL_SHIFTID, ZCL_COLORVALUE* );
VOID			Dllport	ZCLCloseConvHandle( HCTBL );
VOID			Dllport	ZCLCloseAllConvHandle( VOID );
BOOL			Dllport	ZCLColorConvExec( HCTBL, DWORD, DWORD, ZCL_COLORMODE*, BYTE*, BYTE* );
BOOL			Dllport	ZCLColorConvSetBMPINFO( HCTBL, DWORD, DWORD, BITMAPINFO* );
BOOL			Dllport	ZCLCreateMonoBMPINFO( DWORD, DWORD, PBITMAPINFO*, DWORD* );
VOID			Dllport	ZCLDeleteMonoBMPINFO( PBITMAPINFO );
VOID			Dllport	ZCLDeleteAllMonoBMPINFO( VOID );

#ifdef __cplusplus
}
#endif

#pragma warning( pop )
#pragma pack( pop )

#endif
