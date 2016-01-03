#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov2722raw.h"
#include "camera_info_ov2722raw.h"
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
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }
    },
    ISPPca:{
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
        65609,    // i4R_AVG
        13100,    // i4R_STD
        99910,    // i4B_AVG
        26559,    // i4B_STD
        {  // i4P00[9]
            4955000, -1715000, -680000, -897500, 3797500, -340000, -137500, -1835000, 4532500
        },
        {  // i4P10[9]
            545704, -818772, 273068, -140139, 109879, 30260, -193710, 621564, -427854
        },
        {  // i4P01[9]
            335798, -463783, 127984, -174389, 42835, 131555, -154308, -11571, 165879
        },
        {  // i4P20[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P11[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {  // i4P02[9]
            0, 0, 0, 0, 0, 0, 0, 0, 0
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
            1152,    // u4MinGain, 1024 base = 1x
            15872,    // u4MaxGain, 16x
            159,    // u4MiniISOGain, ISOxx  
            64,    // u4GainStepUnit, 1x/8 
            39620,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            39620,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            39620,    // u4CapExpUnit 
            30,    // u4CapMaxFrameRate
            1024,    // u4Cap2PreRatio, 1024 base = 1x
            24,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            2,    // u4HistHighThres
            40,    // u4HistLowThres
            2,    // u4MostBrightRatio
            1,    // u4MostDarkRatio
            160,    // u4CentralHighBound
            20,    // u4CentralLowBound
            {240, 230, 220, 210, 200},    // u4OverExpThres[AE_CCT_STRENGTH_NUM] 
            {86, 108, 128, 148, 170},    // u4HistStretchThres[AE_CCT_STRENGTH_NUM] 
            {18, 22, 26, 30, 34}    // u4BlackLightThres[AE_CCT_STRENGTH_NUM] 
        },
        // rCCTConfig
        {
            TRUE,    // bEnableBlackLight
            TRUE,    // bEnableHistStretch
            FALSE,    // bEnableAntiOverExposure
            TRUE,    // bEnableTimeLPF
            FALSE,    // bEnableCaptureThres
            FALSE,    // bEnableVideoThres
            FALSE,    // bEnableStrobeThres
            47,    // u4AETarget
            47,    // u4StrobeAETarget
            50,    // u4InitIndex
            4,    // u4BackLightWeight
            32,    // u4HistStretchWeight
            4,    // u4AntiOverExpWeight
            2,    // u4BlackLightStrengthIndex
            2,    // u4HistStretchStrengthIndex
            2,    // u4AntiOverExpStrengthIndex
            2,    // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8},    // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM] 
            90,    // u4InDoorEV = 9.0, 10 base 
            -10,    // i4BVOffset delta BV = value/10 
            4,    // u4PreviewFlareOffset
            4,    // u4CaptureFlareOffset
            5,    // u4CaptureFlareThres
            4,    // u4VideoFlareOffset
            5,    // u4VideoFlareThres
            2,    // u4StrobeFlareOffset
            2,    // u4StrobeFlareThres
            8,    // u4PrvMaxFlareThres
            0,    // u4PrvMinFlareThres
            8,    // u4VideoMaxFlareThres
            0,    // u4VideoMinFlareThres
            18,    // u4FlatnessThres    // 10 base for flatness condition.
            75    // u4FlatnessStrength
        }
    },
    // AWB NVRAM
    {
        // AWB calibration data
        {
            // rUnitGain (unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rGoldenGain (golden sample gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rTuningUnitGain (Tuning sample unit gain: 1.0 = 512)
            {
                0,    // i4R
                0,    // i4G
                0    // i4B
            },
            // rD65Gain (D65 WB gain: 1.0 = 512)
            {
                758,    // i4R
                512,    // i4G
                576    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                101,    // i4X
                -188    // i4Y
            },
            // Horizon
            {
                -294,    // i4X
                -165    // i4Y
            },
            // A
            {
                -275,    // i4X
                -242    // i4Y
            },
            // TL84
            {
                -152,    // i4X
                -276    // i4Y
            },
            // CWF
            {
                -91,    // i4X
                -359    // i4Y
            },
            // DNP
            {
                -18,    // i4X
                -232    // i4Y
            },
            // D65
            {
                101,    // i4X
                -188    // i4Y
            },
            // DF
            {
                85,    // i4X
                -316    // i4Y
            }
        },
        // Rotated XY coordinate of AWB light source
        {
            // Strobe
            {
                84,    // i4X
                -196    // i4Y
            },
            // Horizon
            {
                -307,    // i4X
                -139    // i4Y
            },
            // A
            {
                -295,    // i4X
                -217    // i4Y
            },
            // TL84
            {
                -175,    // i4X
                -262    // i4Y
            },
            // CWF
            {
                -121,    // i4X
                -350    // i4Y
            },
            // DNP
            {
                -38,    // i4X
                -230    // i4Y
            },
            // D65
            {
                84,    // i4X
                -196    // i4Y
            },
            // DF
            {
                58,    // i4X
                -322    // i4Y
            }
        },
        // AWB gain of AWB light source
        {
            // Strobe 
            {
                758,    // i4R
                512,    // i4G
                576    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                609,    // i4G
                1135    // i4B
            },
            // A 
            {
                512,    // i4R
                535,    // i4G
                1077    // i4B
            },
            // TL84 
            {
                605,    // i4R
                512,    // i4G
                915    // i4B
            },
            // CWF 
            {
                735,    // i4R
                512,    // i4G
                942    // i4B
            },
            // DNP 
            {
                684,    // i4R
                512,    // i4G
                718    // i4B
            },
            // D65 
            {
                758,    // i4R
                512,    // i4G
                576    // i4B
            },
            // DF 
            {
                881,    // i4R
                512,    // i4G
                700    // i4B
            }
        },
        // Rotation matrix parameter
        {
            5,    // i4RotationAngle
            255,    // i4Cos
            22    // i4Sin
        },
        // Daylight locus parameter
        {
            -146,    // i4SlopeNumerator
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
            -225,    // i4RightBound
            -875,    // i4LeftBound
            -114,    // i4UpperBound
            -242    // i4LowerBound
            },
            // Warm fluorescent
            {
            -225,    // i4RightBound
            -875,    // i4LeftBound
            -242,    // i4UpperBound
            -362    // i4LowerBound
            },
            // Fluorescent
            {
            -88,    // i4RightBound
            -225,    // i4LeftBound
            -115,    // i4UpperBound
            -306    // i4LowerBound
            },
            // CWF
            {
            -88,    // i4RightBound
            -225,    // i4LeftBound
            -306,    // i4UpperBound
            -400    // i4LowerBound
            },
            // Daylight
            {
            109,    // i4RightBound
            -88,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Shade
            {
            469,    // i4RightBound
            109,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
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
            469,    // i4RightBound
            -875,    // i4LeftBound
            -89,    // i4UpperBound
            -400    // i4LowerBound
            },
            // Daylight
            {
            134,    // i4RightBound
            -88,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Cloudy daylight
            {
            234,    // i4RightBound
            59,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Shade
            {
            334,    // i4RightBound
            59,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Twilight
            {
            -88,    // i4RightBound
            -248,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Fluorescent
            {
            134,    // i4RightBound
            -275,    // i4LeftBound
            -146,    // i4UpperBound
            -400    // i4LowerBound
            },
            // Warm fluorescent
            {
            -195,    // i4RightBound
            -395,    // i4LeftBound
            -146,    // i4UpperBound
            -400    // i4LowerBound
            },
            // Incandescent
            {
            -195,    // i4RightBound
            -395,    // i4LeftBound
            -116,    // i4UpperBound
            -276    // i4LowerBound
            },
            // Gray World
            {
            5000,    // i4RightBound
            -5000,    // i4LeftBound
            5000,    // i4UpperBound
            -5000    // i4LowerBound
            }
        },
        // PWB default gain	
        {
            // Daylight
            {
            702,    // i4R
            512,    // i4G
            630    // i4B
            },
            // Cloudy daylight
            {
            817,    // i4R
            512,    // i4G
            526    // i4B
            },
            // Shade
            {
            869,    // i4R
            512,    // i4G
            489    // i4B
            },
            // Twilight
            {
            555,    // i4R
            512,    // i4G
            834    // i4B
            },
            // Fluorescent
            {
            700,    // i4R
            512,    // i4G
            795    // i4B
            },
            // Warm fluorescent
            {
            531,    // i4R
            512,    // i4G
            1105    // i4B
            },
            // Incandescent
            {
            474,    // i4R
            512,    // i4G
            1004    // i4B
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
            50,    // i4SliderValue
            4228    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            50,    // i4SliderValue
            4228    // i4OffsetThr
            },
            // Shade
            {
            50,    // i4SliderValue
            842    // i4OffsetThr
            },
            // Daylight WB gain
            {
            651,    // i4R
            512,    // i4G
            689    // i4B
            },
            // Preference gain: strobe
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: tungsten
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: warm fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: CWF
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: shade
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            },
            // Preference gain: daylight fluorescent
            {
            512,    // i4R
            512,    // i4G
            512    // i4B
            }
        },
        {// CCT estimation
            {// CCT
                2300,    // i4CCT[0]
                2850,    // i4CCT[1]
                4100,    // i4CCT[2]
                5100,    // i4CCT[3]
                6500    // i4CCT[4]
            },
            {// Rotated X coordinate
                -391,    // i4RotatedXCoordinate[0]
                -379,    // i4RotatedXCoordinate[1]
                -259,    // i4RotatedXCoordinate[2]
                -122,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
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
}}; // NSFeature


