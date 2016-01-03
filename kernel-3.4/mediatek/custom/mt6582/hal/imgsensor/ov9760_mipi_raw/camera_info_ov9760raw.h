#ifndef _CAMERA_INFO_OV9760RAW_H
#define _CAMERA_INFO_OV9760RAW_H

/*******************************************************************************
*   Configuration
********************************************************************************/
#define SENSOR_ID                           OV9760MIPI_SENSOR_ID
#define SENSOR_DRVNAME                      SENSOR_DRVNAME_OV9760_MIPI_RAW
#define INCLUDE_FILENAME_ISP_REGS_PARAM     "camera_isp_regs_ov9760raw.h"
#define INCLUDE_FILENAME_ISP_PCA_PARAM      "camera_isp_pca_ov9760raw.h"
#define INCLUDE_FILENAME_ISP_LSC_PARAM      "camera_isp_lsc_ov9760raw.h"
/*******************************************************************************
*
********************************************************************************/

#if defined(ISP_SUPPORT)

#define OV8830RAW_CAMERA_AUTO_DSC CAM_AUTO_DSC
#define OV8830RAW_CAMERA_PORTRAIT CAM_PORTRAIT
#define OV8830RAW_CAMERA_LANDSCAPE CAM_LANDSCAPE
#define OV8830RAW_CAMERA_SPORT CAM_SPORT
#define OV8830RAW_CAMERA_FLOWER CAM_FLOWER
#define OV8830RAW_CAMERA_NIGHTSCENE CAM_NIGHTSCENE
#define OV8830RAW_CAMERA_DOCUMENT CAM_DOCUMENT
#define OV8830RAW_CAMERA_ISO_ANTI_HAND_SHAKE CAM_ISO_ANTI_HAND_SHAKE
#define OV8830RAW_CAMERA_ISO100 CAM_ISO100
#define OV8830RAW_CAMERA_ISO200 CAM_ISO200
#define OV8830RAW_CAMERA_ISO400 CAM_ISO400
#define OV8830RAW_CAMERA_ISO800 CAM_ISO800
#define OV8830RAW_CAMERA_ISO1600 CAM_ISO1600
#define OV8830RAW_CAMERA_VIDEO_AUTO CAM_VIDEO_AUTO
#define OV8830RAW_CAMERA_VIDEO_NIGHT CAM_VIDEO_NIGHT
#define OV8830RAW_CAMERA_NO_OF_SCENE_MODE CAM_NO_OF_SCENE_MODE

#endif
#endif
