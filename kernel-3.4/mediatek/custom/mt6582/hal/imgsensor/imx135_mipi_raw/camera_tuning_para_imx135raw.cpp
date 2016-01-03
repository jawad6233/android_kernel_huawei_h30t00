#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_imx135raw.h"
#include "camera_info_imx135raw.h"
#include "camera_custom_AEPlinetable.h"

const NVRAM_CAMERA_ISP_PARAM_STRUCT CAMERA_ISP_DEFAULT_VALUE =
{{
    //Version
    Version: NVRAM_CAMERA_PARA_FILE_VERSION,

    //SensorId
    SensorId: SENSOR_ID,
    ISPComm:{
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    	}
    },
    ISPPca: {
        #include INCLUDE_FILENAME_ISP_PCA_PARAM
    },
    ISPRegs:{
        #include INCLUDE_FILENAME_ISP_REGS_PARAM
    },
    ISPMfbMixer:{{
        {//00: MFB mixer for ISO 100
            0x00000000, 0x00000000
        },
        {//01: MFB mixer for ISO 200
            0x00000000, 0x00000000
        },
        {//02: MFB mixer for ISO 400
            0x00000000, 0x00000000
        },
        {//03: MFB mixer for ISO 800
            0x00000000, 0x00000000
        },
        {//04: MFB mixer for ISO 1600
            0x00000000, 0x00000000
        },
        {//05: MFB mixer for ISO 2400
            0x00000000, 0x00000000
        },
        {//06: MFB mixer for ISO 3200
            0x00000000, 0x00000000
    }
    }},
    ISPCcmPoly22:{
        75170, // i4R_AVG
        13190, // i4R_STD
        79140, // i4B_AVG
        26270, // i4B_STD
        { // i4P00[9]
            4448648, -1494813, -393843, -604477, 3414513, -250036,  85095, -1385454, 3860283 
        },
        { // i4P10[9]
            933698,  -628943, -304758, -247520,  -22220,  269740, -73861,   196166, -122555
        },
        { // i4P01[9]
            814367,  -494023, -320352, -358410, -180556,  538966, -57406,  -190454,  247689
        },
        { // i4P20[9]
            394007,  -491950,   98031,  -21525,   59812,  -38287, 140879,  -521951,  381045
        },
        { // i4P11[9]
            -35750,  -344806,  380738,  121574,   59500, -181074, 143388,  -309535,  166309
        },
        { // i4P02[9]
            -315751,    65233,  250618,  151463,   34149, -185612,  21808,    -8637,  -12997
        }        
    }
}};

const NVRAM_CAMERA_3A_STRUCT CAMERA_3A_NVRAM_DEFAULT_VALUE =
{
    NVRAM_CAMERA_3A_FILE_VERSION, // u4Version
    SENSOR_ID, // SensorId

    // AE NVRAM
    {
        // rDevicesInfo
        {
            1136,    // u4MinGain, 1024 base = 1x
            10240,    // u4MaxGain, 16x
            85,    // u4MiniISOGain, ISOxx  
            128,    // u4GainStepUnit, 1x/8 
            19769,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            19769,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            21049,    // u4CapExpUnit 
            15,    // u4CapMaxFrameRate
            1024,    // u4Cap2PreRatio, 1024 base = 1x
            22,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
         },
         // rHistConfig
        {
            4, // 2,   // u4HistHighThres
            40,  // u4HistLowThres
            2,   // u4MostBrightRatio
            1,   // u4MostDarkRatio
            160, // u4CentralHighBound
            20,  // u4CentralLowBound
            {240, 230, 220, 210, 200}, // u4OverExpThres[AE_CCT_STRENGTH_NUM]
            {82, 108, 128, 148, 170},  // u4HistStretchThres[AE_CCT_STRENGTH_NUM]
            {18, 22, 26, 30, 34}       // u4BlackLightThres[AE_CCT_STRENGTH_NUM]
        },
        // rCCTConfig
        {
            TRUE,            // bEnableBlackLight
            TRUE,            // bEnableHistStretch
            FALSE,           // bEnableAntiOverExposure
            TRUE,            // bEnableTimeLPF
            TRUE,            // bEnableCaptureThres
            TRUE,            // bEnableVideoThres
            TRUE,            // bEnableStrobeThres
            47,                // u4AETarget
            47,                // u4StrobeAETarget

            50,                // u4InitIndex
            5,                 // u4BackLightWeight
            32,                // u4HistStretchWeight
            4,                 // u4AntiOverExpWeight
            2,                 // u4BlackLightStrengthIndex
            0, // 2,                 // u4HistStretchStrengthIndex
            2,                 // u4AntiOverExpStrengthIndex
            2,                 // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8}, // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM]
            90,                // u4InDoorEV = 9.0, 10 base
            -10,               // i4BVOffset delta BV = -2.3
            64,                 // u4PreviewFlareOffset
            64,                 // u4CaptureFlareOffset
            4,                 // u4CaptureFlareThres
            64,                 // u4VideoFlareOffset
            4,                 // u4VideoFlareThres
            32,                 // u4StrobeFlareOffset
            2,                 // u4StrobeFlareThres
            160,                 // u4PrvMaxFlareThres
            0,                 // u4PrvMinFlareThres
            160,                 // u4VideoMaxFlareThres
            0,                 // u4VideoMinFlareThres            
            18,                // u4FlatnessThres              // 10 base for flatness condition.
            75                 // u4FlatnessStrength
         }
    },

    // AWB NVRAM
{								
	// AWB calibration data							
	{							
		// rCalGain (calibration gain: 1.0 = 512)						
		{						
			0,	// u4R				
			0,	// u4G				
			0	// u4B				
		},						
		// rDefGain (Default calibration gain: 1.0 = 512)						
		{						
			0,	// u4R				
			0,	// u4G				
			0	// u4B				
		},						
		// rDefGain (Default calibration gain: 1.0 = 512)						
		{						
			0,	// u4R				
			0,	// u4G				
			0	// u4B				
		},						
		// rD65Gain (D65 WB gain: 1.0 = 512)						
		{						
                1093,    // i4R
                512,    // i4G
                720    // i4B
		}						
	},							
	// Original XY coordinate of AWB light source							
	{							
		// Strobe						
		{						
                154,    // i4X
                -402    // i4Y
		},						
		// Horizon						
		{						
                -420,    // i4X
                -392    // i4Y
		},						
		// A						
		{						
                -295,    // i4X
                -404    // i4Y
		},						
		// TL84						
		{						
                -89,    // i4X
                -441    // i4Y
		},						
		// CWF						
		{						
                -60,    // i4X
                -473    // i4Y
		},						
		// DNP						
		{						
                24,    // i4X
                -446    // i4Y
		},						
		// D65						
		{						
                154,    // i4X
                -406    // i4Y
		},						
		// DF						
		{						
			0, 	// i4X				
			0	// i4Y				
		}						
	},							
	// Rotated XY coordinate of AWB light source							
	{							
		// Strobe						
		{						
                154,    // i4X
                -402    // i4Y
		},						
		// Horizon						
		{						
                -420,    // i4X
                -392    // i4Y
		},						
		// A						
		{						
                -295,    // i4X
                -404    // i4Y
            },
    		// TL84
    		{
                -89,    // i4X
                -441    // i4Y
            },
            // CWF
            {
                -60,    // i4X
                -473    // i4Y
            },
            // DNP
            {
                24,    // i4X
                -446    // i4Y
            },
            // D65
            {
                154,    // i4X
                -406    // i4Y
            },
		// DF						
		{						
			0,	// i4X				
			0	// i4Y				
		}						
	},							
	// AWB gain of AWB light source							
	{							
		// Strobe						
		{						
                1087,    // i4R
                512,    // i4G
                717    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                532,    // i4G
                1595    // i4B
		},
		// A
		{
                594,    // i4R
                512,    // i4G
                1320    // i4B
            },
            // TL84 
            {
                825,    // i4R
                512,    // i4G
                1050    // i4B
            },
            // CWF 
            {
                896,    // i4R
                512,    // i4G
                1054    // i4B
		},
		// DNP
		{
                966,    // i4R
                512,    // i4G
                907    // i4B
            },
            // D65 
            {
                1093,    // i4R
                512,    // i4G
                720    // i4B
            },
		// DF						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		}						
	},							
    	// Rotation matrix parameter
    	{
            0,    // i4RotationAngle
            256,    // i4Cos
            0    // i4Sin
    	},
        // Daylight locus parameter
        {
            -127,    // i4SlopeNumerator
            128    // i4SlopeDenominator
        },
        // AWB light area
        {
            // Strobe:FIXME
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            },
            // Tungsten
            {
            -139,    // i4RightBound
            -789,    // i4LeftBound
            -348,    // i4UpperBound
            -448    // i4LowerBound
            },
            // Warm fluorescent
            {
            -139,    // i4RightBound
            -789,    // i4LeftBound
            -448,    // i4UpperBound
            -568    // i4LowerBound
            },
            // Fluorescent
            {
            -26,    // i4RightBound
            -139,    // i4LeftBound
            -337,    // i4UpperBound
            -457    // i4LowerBound
            },
            // CWF
            {
            -26,    // i4RightBound
            -139,    // i4LeftBound
            -457,    // i4UpperBound
            -523    // i4LowerBound
            },
            // Daylight
            {
            179,    // i4RightBound
            -26,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Shade
            {
            539,    // i4RightBound
            179,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            0,    // i4RightBound
            0,    // i4LeftBound
            0,    // i4UpperBound
            0    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            539,    // i4RightBound
            -789,    // i4LeftBound
            -301,    // i4UpperBound
            -568    // i4LowerBound
            },
            // Daylight
            {
            204,    // i4RightBound
            -26,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Cloudy daylight
            {
            304,    // i4RightBound
            129,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Shade
            {
            404,    // i4RightBound
            129,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Twilight
            {
            -26,    // i4RightBound
            -186,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
            // Fluorescent
            {
            204,    // i4RightBound
            -189,    // i4LeftBound
            -356,    // i4UpperBound
            -523    // i4LowerBound
            },
            // Warm fluorescent
            {
            -195,    // i4RightBound
            -395,    // i4LeftBound
            -356,    // i4UpperBound
            -523    // i4LowerBound
            },
            // Incandescent
            {
            -195,    // i4RightBound
            -395,    // i4LeftBound
            -326,    // i4UpperBound
            -486    // i4LowerBound
            },
		// Gray World						
		{						
			5000,	// i4RightBound				
			-5000,	// i4LeftBound				
			5000,	// i4UpperBound				
			-5000	// i4LowerBound				
		}						
	},							
	// PWB default gain							
	{							
            // Daylight
            {
            1001,    // i4R
            512,    // i4G
            786    // i4B
            },
            // Cloudy daylight
            {
            1189,    // i4R
            512,    // i4G
            662    // i4B
            },
            // Shade
            {
            1273,    // i4R
            512,    // i4G
            618    // i4B
            },
            // Twilight
            {
            769,    // i4R
            512,    // i4G
            1024    // i4B
            },
            // Fluorescent
            {
            938,    // i4R
            512,    // i4G
            919    // i4B
            },
            // Warm fluorescent
            {
            623,    // i4R
            512,    // i4G
            1384    // i4B
            },
            // Incandescent
            {
            595,    // i4R
            512,    // i4G
            1323    // i4B
            },
            // Gray World
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        // AWB preference color	
        {
            // Tungsten
            {
            0,    // i4SliderValue
            7534    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            4992    // i4OffsetThr
            },
            // Shade
            {
            0,    // i4SliderValue
            1341    // i4OffsetThr
            },
            // Daylight WB gain
            {
            916,    // i4R
            512,    // i4G
            859    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            495,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            508,    // i4R
            512,    // i4G
            512    // i4B
		},						
		// Preference gain: fluorescent						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		},						
		// Preference gain: CWF						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		},						
		// Preference gain: daylight						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		},						
		// Preference gain: shade						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		},						
		// Preference gain: daylight fluorescent						
		{						
			512,	// u4R				
			512,	// u4G				
			512	// u4B				
		}						
	},							
	// CCT estimation							
	{							
		// CCT						
		{						
			2300,	// i4CCT[0]				
			2850,	// i4CCT[1]				
			4100,	// i4CCT[2]				
			5100,	// i4CCT[3]				
			6500 	// i4CCT[4]				
		},						
		// Rotated X coordinate						
    		{
			-574,	// i4RotatedXCoordinate[0]
			-449,	// i4RotatedXCoordinate[1]
                -243,    // i4RotatedXCoordinate[2]
                -130,    // i4RotatedXCoordinate[3]
    			0	// i4RotatedXCoordinate[4]
		}						
	}							


    },
	{0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace


typedef NSFeature::RAWSensorInfo<SENSOR_ID> SensorInfoSingleton_T;


namespace NSFeature {
template <>
UINT32
SensorInfoSingleton_T::
impGetDefaultData(CAMERA_DATA_TYPE_ENUM const CameraDataType, VOID*const pDataBuf, UINT32 const size) const
{
    UINT32 dataSize[CAMERA_DATA_TYPE_NUM] = {sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT),
                                             sizeof(NVRAM_CAMERA_3A_STRUCT),
                                             sizeof(NVRAM_CAMERA_SHADING_STRUCT),
                                             sizeof(NVRAM_LENS_PARA_STRUCT),
                                             sizeof(AE_PLINETABLE_T)};

    if (CameraDataType > CAMERA_DATA_AE_PLINETABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
    {
        return 1;
    }

    switch(CameraDataType)
    {
        case CAMERA_NVRAM_DATA_ISP:
            memcpy(pDataBuf,&CAMERA_ISP_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_ISP_PARAM_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_3A:
            memcpy(pDataBuf,&CAMERA_3A_NVRAM_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_3A_STRUCT));
            break;
        case CAMERA_NVRAM_DATA_SHADING:
            memcpy(pDataBuf,&CAMERA_SHADING_DEFAULT_VALUE,sizeof(NVRAM_CAMERA_SHADING_STRUCT));
            break;
        case CAMERA_DATA_AE_PLINETABLE:
            memcpy(pDataBuf,&g_PlineTableMapping,sizeof(AE_PLINETABLE_T));
            break;
        default:
            break;
    }
    return 0;
}};  //  NSFeature


