#include <utils/Log.h>
#include <fcntl.h>
#include <math.h>

#include "camera_custom_nvram.h"
#include "camera_custom_sensor.h"
#include "image_sensor.h"
#include "kd_imgsensor_define.h"
#include "camera_AE_PLineTable_ov13850mipiraw.h"
#include "camera_info_ov13850mipiraw.h"
#include "camera_custom_AEPlinetable.h"
#include "camera_custom_tsf_tbl.h"
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
        75170,    // i4R_AVG
        13190,    // i4R_STD
        79140,    // i4B_AVG
        26270,    // i4B_STD
        {  // i4P00[9]
            4448648, -1494813, -393843, -604477, 3414513, -250036, 85095, -1385454, 3860283
        },
        {  // i4P10[9]
            933698, -628943, -304758, -247520, -22220, 269740, -73861, 196166, -122555
        },
        {  // i4P01[9]
            814367, -494023, -320352, -358410, -180556, 538966, -57406, -190454, 247689
        },
        {  // i4P20[9]
            394007, -491950, 98031, -21525, 59812, -38287, 140879, -521951, 381045
        },
        {  // i4P11[9]
            -35750, -344806, 380738, 121574, 59500, -181074, 143388, -309535, 166309
        },
        {  // i4P02[9]
            -315751, 65233, 250618, 151463, 0, 0, 0, 0, 0
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
            1144,    // u4MinGain, 1024 base = 1x
            7680,    // u4MaxGain, 16x
            51,    // u4MiniISOGain, ISOxx  
            32,    // u4GainStepUnit, 1x/8 
            13,    // u4PreExpUnit 
            30,    // u4PreMaxFrameRate
            13,    // u4VideoExpUnit  
            30,    // u4VideoMaxFrameRate 
            1024,    // u4Video2PreRatio, 1024 base = 1x 
            13,    // u4CapExpUnit 
            24,    // u4CapMaxFrameRate
            1024,    // u4Cap2PreRatio, 1024 base = 1x
            22,    // u4LensFno, Fno = 2.8
            350    // u4FocusLength_100x
        },
        // rHistConfig
        {
            4,    // u4HistHighThres
            40,    // u4HistLowThres
            2,    // u4MostBrightRatio
            1,    // u4MostDarkRatio
            160,    // u4CentralHighBound
            20,    // u4CentralLowBound
            {240, 230, 220, 210, 200},    // u4OverExpThres[AE_CCT_STRENGTH_NUM] 
            {82, 108, 128, 148, 170},    // u4HistStretchThres[AE_CCT_STRENGTH_NUM] 
            {18, 22, 26, 30, 34}    // u4BlackLightThres[AE_CCT_STRENGTH_NUM] 
        },
        // rCCTConfig
        {
            TRUE,    // bEnableBlackLight
            TRUE,    // bEnableHistStretch
            FALSE,    // bEnableAntiOverExposure
            TRUE,    // bEnableTimeLPF
            TRUE,    // bEnableCaptureThres
            TRUE,    // bEnableVideoThres
            TRUE,    // bEnableStrobeThres
            47,    // u4AETarget
            47,    // u4StrobeAETarget
            50,    // u4InitIndex
            4,    // u4BackLightWeight
            32,    // u4HistStretchWeight
            4,    // u4AntiOverExpWeight
            2,    // u4BlackLightStrengthIndex
            0,    // u4HistStretchStrengthIndex
            2,    // u4AntiOverExpStrengthIndex
            2,    // u4TimeLPFStrengthIndex
            {1, 3, 5, 7, 8},    // u4LPFConvergeTable[AE_CCT_STRENGTH_NUM] 
            90,    // u4InDoorEV = 9.0, 10 base 
            -4,    // i4BVOffset delta BV = value/10 
            64,    // u4PreviewFlareOffset
            64,    // u4CaptureFlareOffset
            4,    // u4CaptureFlareThres
            64,    // u4VideoFlareOffset
            4,    // u4VideoFlareThres
            32,    // u4StrobeFlareOffset
            2,    // u4StrobeFlareThres
            160,    // u4PrvMaxFlareThres
            0,    // u4PrvMinFlareThres
            160,    // u4VideoMaxFlareThres
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
                871,    // i4R
                512,    // i4G
                624    // i4B
            }
        },
        // Original XY coordinate of AWB light source
        {
           // Strobe
            {
                123,    // i4X
                -269    // i4Y
            },
            // Horizon
            {
                -312,    // i4X
                -272    // i4Y
            },
            // A
            {
                -231,    // i4X
                -297    // i4Y
            },
            // TL84
            {
                -130,    // i4X
                -276    // i4Y
            },
            // CWF
            {
                -88,    // i4X
                -341    // i4Y
            },
            // DNP
            {
                -9,    // i4X
                -316    // i4Y
            },
            // D65
            {
                123,    // i4X
                -269    // i4Y
            },
            // DF
            {
                73,    // i4X
                -328    // i4Y
            }
        },
        // Rotated XY coordinate of AWB light source
        {
            // Strobe
            {
                114,    // i4X
                -273    // i4Y
            },
            // Horizon
            {
                -322,    // i4X
                -261    // i4Y
            },
            // A
            {
                -241,    // i4X
                -289    // i4Y
            },
            // TL84
            {
                -140,    // i4X
                -271    // i4Y
            },
            // CWF
            {
                -100,    // i4X
                -338    // i4Y
            },
            // DNP
            {
                -20,    // i4X
                -316    // i4Y
            },
            // D65
            {
                114,    // i4X
                -273    // i4Y
            },
            // DF
            {
                61,    // i4X
                -331    // i4Y
            }
        },
        // AWB gain of AWB light source
        {
            // Strobe 
            {
                871,    // i4R
                512,    // i4G
                624    // i4B
            },
            // Horizon 
            {
                512,    // i4R
                540,    // i4G
                1193    // i4B
            },
            // A 
            {
                560,    // i4R
                512,    // i4G
                1047    // i4B
            },
            // TL84 
            {
                624,    // i4R
                512,    // i4G
                887    // i4B
            },
            // CWF 
            {
                721,    // i4R
                512,    // i4G
                915    // i4B
            },
            // DNP 
            {
                776,    // i4R
                512,    // i4G
                795    // i4B
            },
            // D65 
            {
                871,    // i4R
                512,    // i4G
                624    // i4B
            },
            // DF 
            {
                881,    // i4R
                512,    // i4G
                723    // i4B
            }
        },
        // Rotation matrix parameter
        {
            2,    // i4RotationAngle
            256,    // i4Cos
            9    // i4Sin
        },
        // Daylight locus parameter
        {
            -137,    // i4SlopeNumerator
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
            -190,    // i4RightBound
            -840,    // i4LeftBound
            -225,    // i4UpperBound
            -325    // i4LowerBound
            },
            // Warm fluorescent
            {
            -190,    // i4RightBound
            -840,    // i4LeftBound
            -325,    // i4UpperBound
            -445    // i4LowerBound
            },
            // Fluorescent
            {
            -70,    // i4RightBound
            -190,    // i4LeftBound
            -206,    // i4UpperBound
            -304    // i4LowerBound
            },
            // CWF
            {
            -70,    // i4RightBound
            -190,    // i4LeftBound
            -304,    // i4UpperBound
            -388    // i4LowerBound
            },
            // Daylight
            {
            139,    // i4RightBound
            -70,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Shade
            {
            499,    // i4RightBound
            139,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Daylight Fluorescent
            {
            139,    // i4RightBound
            -70,    // i4LeftBound
            -353,    // i4UpperBound
            -420    // i4LowerBound
            }
        },
        // PWB light area
        {
            // Reference area
            {
            499,    // i4RightBound
            -840,    // i4LeftBound
            0,    // i4UpperBound
            -445    // i4LowerBound
            },
            // Daylight
            {
            164,    // i4RightBound
            -70,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Cloudy daylight
            {
            264,    // i4RightBound
            89,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Shade
            {
            364,    // i4RightBound
            89,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Twilight
            {
            -70,    // i4RightBound
            -230,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
            },
            // Fluorescent
            {
            164,    // i4RightBound
            -240,    // i4LeftBound
            -221,    // i4UpperBound
            -388    // i4LowerBound
            },
            // Warm fluorescent
            {
            -141,    // i4RightBound
            -341,    // i4LeftBound
            -221,    // i4UpperBound
            -388    // i4LowerBound
            },
            // Incandescent
            {
            -141,    // i4RightBound
            -341,    // i4LeftBound
            -193,    // i4UpperBound
            -353    // i4LowerBound
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
            798,    // i4R
            512,    // i4G
            685    // i4B
            },
            // Cloudy daylight
            {
            945,    // i4R
            512,    // i4G
            571    // i4B
            },
            // Shade
            {
            1008,    // i4R
            512,    // i4G
            532    // i4B
            },
            // Twilight
            {
            617,    // i4R
            512,    // i4G
            902    // i4B
            },
            // Fluorescent
            {
            746,    // i4R
            512,    // i4G
            803    // i4B
            },
            // Warm fluorescent
            {
            573,    // i4R
            512,    // i4G
            1067    // i4B
            },
            // Incandescent
            {
            548,    // i4R
            512,    // i4G
            1024    // i4B
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
            5302    // i4OffsetThr
            },
            // Warm fluorescent	
            {
            0,    // i4SliderValue
            5144    // i4OffsetThr
            },
            // Shade
            {
            0,    // i4SliderValue
            1341    // i4OffsetThr
            },
            // Daylight WB gain
            {
            731,    // i4R
            512,    // i4G
            752    // i4B
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
                -436,    // i4RotatedXCoordinate[0]
                -355,    // i4RotatedXCoordinate[1]
                -254,    // i4RotatedXCoordinate[2]
                -134,    // i4RotatedXCoordinate[3]
                0    // i4RotatedXCoordinate[4]
            }
        }
    },
    {0}
};

#include INCLUDE_FILENAME_ISP_LSC_PARAM
//};  //  namespace

const CAMERA_TSF_TBL_STRUCT CAMERA_TSF_DEFAULT_VALUE =
{
    #include INCLUDE_FILENAME_TSF_PARA
    #include INCLUDE_FILENAME_TSF_DATA
};


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
                                             sizeof(AE_PLINETABLE_T),
                                             0,
                                             sizeof(CAMERA_TSF_TBL_STRUCT)};

    if (CameraDataType > CAMERA_DATA_TSF_TABLE || NULL == pDataBuf || (size < dataSize[CameraDataType]))
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
        case CAMERA_DATA_TSF_TABLE:
            memcpy(pDataBuf,&CAMERA_TSF_DEFAULT_VALUE,sizeof(CAMERA_TSF_TBL_STRUCT));
            break;
        default:
            break;
    }
    return 0;
}}; // NSFeature


