/*******************************************************************************************/


/******************************************************************************************/

/* SENSOR FULL SIZE */
#ifndef __SENSOR_H
#define __SENSOR_H   

typedef enum group_enum {
    PRE_GAIN=0,
    CMMCLK_CURRENT,
    FRAME_RATE_LIMITATION,
    REGISTER_EDITOR,
    GROUP_TOTAL_NUMS
} FACTORY_GROUP_ENUM;


#define ENGINEER_START_ADDR 10
#define FACTORY_START_ADDR 0

typedef enum engineer_index
{
    CMMCLK_CURRENT_INDEX=ENGINEER_START_ADDR,
    ENGINEER_END
} FACTORY_ENGINEER_INDEX;

typedef enum register_index
{
	SENSOR_BASEGAIN=FACTORY_START_ADDR,
	PRE_GAIN_R_INDEX,
	PRE_GAIN_Gr_INDEX,
	PRE_GAIN_Gb_INDEX,
	PRE_GAIN_B_INDEX,
	FACTORY_END_ADDR
} FACTORY_REGISTER_INDEX;

typedef struct
{
    SENSOR_REG_STRUCT	Reg[ENGINEER_END];
    SENSOR_REG_STRUCT	CCT[FACTORY_END_ADDR];
} SENSOR_DATA_STRUCT, *PSENSOR_DATA_STRUCT;

typedef enum {
    SENSOR_MODE_INIT = 0,
    SENSOR_MODE_PREVIEW,
    SENSOR_MODE_VIDEO,
    SENSOR_MODE_CAPTURE,
} AR0833_SENSOR_MODE;


typedef struct
{
	kal_uint32 DummyPixels;
	kal_uint32 DummyLines;
	
	kal_uint32 pvShutter;
	kal_uint32 pvGain;
	
	kal_uint32 pvPclk;  // x10 480 for 48MHZ
	kal_uint32 videoPclk;
	kal_uint32 capPclk; // x10
	
	kal_uint32 shutter;
	kal_uint32 maxExposureLines;

	kal_uint16 sensorGlobalGain;//sensor gain read from 0x350a 0x350b;
	kal_uint16 ispBaseGain;//64
	kal_uint16 realGain;//ispBaseGain as 1x

	kal_int16 imgMirror;

	AR0833_SENSOR_MODE sensorMode;

	kal_bool AR0833AutoFlickerMode;
	kal_bool AR0833VideoMode;
	
}AR0833_PARA_STRUCT,*PAR0833_PARA_STRUCT;


    #define CURRENT_MAIN_SENSOR                AR0833_MICRON
   //if define RAW10, MIPI_INTERFACE must be defined
   //if MIPI_INTERFACE is marked, RAW10 must be marked too
    #define MIPI_INTERFACE

   #define AR0833_IMAGE_SENSOR_FULL_HACTIVE    3264
   #define AR0833_IMAGE_SENSOR_FULL_VACTIVE    2448
   #define AR0833_IMAGE_SENSOR_PV_HACTIVE      1616
   #define AR0833_IMAGE_SENSOR_PV_VACTIVE      1212
   #define AR0833_IMAGE_SENSOR_VIDEO_HACTIVE   3264
   #define AR0833_IMAGE_SENSOR_VIDEO_VACTIVE   1836


   #define AR0833_IMAGE_SENSOR_FULL_WIDTH				(AR0833_IMAGE_SENSOR_FULL_HACTIVE -64)	
   #define AR0833_IMAGE_SENSOR_FULL_HEIGHT 				(AR0833_IMAGE_SENSOR_FULL_VACTIVE -44)

	/* SENSOR PV SIZE */

   #define AR0833_IMAGE_SENSOR_PV_WIDTH        (AR0833_IMAGE_SENSOR_PV_HACTIVE - 16)
   #define AR0833_IMAGE_SENSOR_PV_HEIGHT       (AR0833_IMAGE_SENSOR_PV_VACTIVE - 12)

   #define AR0833_IMAGE_SENSOR_VIDEO_WIDTH     (AR0833_IMAGE_SENSOR_VIDEO_HACTIVE - 64)
   #define AR0833_IMAGE_SENSOR_VIDEO_HEIGHT    (AR0833_IMAGE_SENSOR_VIDEO_VACTIVE - 48)


	/* SENSOR SCALER FACTOR */
	#define AR0833_PV_SCALER_FACTOR					    	3
	#define AR0833_FULL_SCALER_FACTOR					    1
	                                        	
	/* SENSOR START/EDE POSITION */         	
	#define AR0833_FULL_X_START						    		(5)
	#define AR0833_FULL_Y_START						    		(3)
	#define AR0833_PV_X_START						    		(3)
	#define AR0833_PV_Y_START						    		(3)	
	#define AR0833_VIDEO_X_START								(3)
	#define AR0833_VIDEO_Y_START								(3)

	#define AR0833_MAX_ANALOG_GAIN					(16)
	#define AR0833_MIN_ANALOG_GAIN					(1)
	#define AR0833_ANALOG_GAIN_1X						(0x0020)

	//#define AR0833_MAX_DIGITAL_GAIN					(8)
	//#define AR0833_MIN_DIGITAL_GAIN					(1)
	//#define AR0833_DIGITAL_GAIN_1X					(0x0100)

	/* SENSOR PIXEL/LINE NUMBERS IN ONE PERIOD */
    #define	AR0833_IMAGE_SENSOR_FULL_HBLANKING  524
    #define AR0833_IMAGE_SENSOR_FULL_VBLANKING  128


    #define	AR0833_IMAGE_SENSOR_PV_HBLANKING    2174
    #define AR0833_IMAGE_SENSOR_PV_VBLANKING    1363
	
    #define	AR0833_IMAGE_SENSOR_VIDEO_HBLANKING    1758
    #define AR0833_IMAGE_SENSOR_VIDEO_VBLANKING    113


	#define AR0833_FULL_PERIOD_PIXEL_NUMS	    (AR0833_IMAGE_SENSOR_FULL_HACTIVE + AR0833_IMAGE_SENSOR_FULL_HBLANKING)  //2592+1200= 3792
    #define AR0833_FULL_PERIOD_LINE_NUMS	    (AR0833_IMAGE_SENSOR_FULL_VACTIVE + AR0833_IMAGE_SENSOR_FULL_VBLANKING)  //1944+150 = 2094
    #define AR0833_PV_PERIOD_PIXEL_NUMS	        (AR0833_IMAGE_SENSOR_PV_HACTIVE + AR0833_IMAGE_SENSOR_PV_HBLANKING)     //1296 +1855 =3151
    #define AR0833_PV_PERIOD_LINE_NUMS	        (AR0833_IMAGE_SENSOR_PV_VACTIVE + AR0833_IMAGE_SENSOR_PV_VBLANKING)    //972 + 128 =1100
    #define AR0833_VIDEO_PERIOD_PIXEL_NUMS 		(AR0833_IMAGE_SENSOR_VIDEO_HACTIVE + AR0833_IMAGE_SENSOR_VIDEO_HBLANKING) 	//1296 +1855 =3151
    #define AR0833_VIDEO_PERIOD_LINE_NUMS		(AR0833_IMAGE_SENSOR_VIDEO_VACTIVE + AR0833_IMAGE_SENSOR_VIDEO_VBLANKING)    //972 + 128 =1100 


	/* DUMMY NEEDS TO BE INSERTED */
	/* SETUP TIME NEED TO BE INSERTED */
	#define AR0833_IMAGE_SENSOR_PV_INSERTED_PIXELS			2
	#define AR0833_IMAGE_SENSOR_PV_INSERTED_LINES			2

	#define AR0833_IMAGE_SENSOR_FULL_INSERTED_PIXELS		4
	#define AR0833_IMAGE_SENSOR_FULL_INSERTED_LINES		    4

#define AR0833MIPI_WRITE_ID 	(0x6C)
#define AR0833MIPI_READ_ID	(0x6D)

// SENSOR CHIP VERSION

#define AR0833MIPI_SENSOR_ID            AR0833_SENSOR_ID

#define AR0833MIPI_PAGE_SETTING_REG    (0xFF)

struct AR0833_SENSOR_STRUCT
{
    kal_uint8 i2c_write_id;
    kal_uint8 i2c_read_id;
    kal_uint16 pvPclk;
    kal_uint16 capPclk;
	kal_uint16 videoPclk;
};


//s_add for porting
//s_add for porting
//s_add for porting

//export functions
UINT32 AR0833MIPIOpen(void);
UINT32 AR0833MIPIGetResolution(MSDK_SENSOR_RESOLUTION_INFO_STRUCT *pSensorResolution);
UINT32 AR0833MIPIGetInfo(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_INFO_STRUCT *pSensorInfo, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 AR0833MIPIControl(MSDK_SCENARIO_ID_ENUM ScenarioId, MSDK_SENSOR_EXPOSURE_WINDOW_STRUCT *pImageWindow, MSDK_SENSOR_CONFIG_STRUCT *pSensorConfigData);
UINT32 AR0833MIPIFeatureControl(MSDK_SENSOR_FEATURE_ENUM FeatureId, UINT8 *pFeaturePara,UINT32 *pFeatureParaLen);
UINT32 AR0833MIPIClose(void);

//#define Sleep(ms) mdelay(ms)
//#define RETAILMSG(x,...)
//#define TEXT

//e_add for porting
//e_add for porting
//e_add for porting

#endif /* __SENSOR_H */

