/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include "camera_custom_types.h"
#include "string.h"
#ifdef WIN32
#else
#include "camera_custom_nvram.h"
#endif
#include "flash_feature.h"
#include "flash_param.h"
#include "flash_tuning_custom.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int getDefaultStrobeNVRam(int sensorType, void* data, int* ret_size)
{
	//static NVRAM_CAMERA_STROBE_STRUCT strobeNVRam;
	NVRAM_CAMERA_STROBE_STRUCT* p;
	p = (NVRAM_CAMERA_STROBE_STRUCT*)data;
	static short engTab[]=
    {
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,
        100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,

    };

	//version
	p->u4Version = NVRAM_CAMERA_STROBE_FILE_VERSION;
	//eng tab
	memcpy(p->engTab.yTab, engTab, 256*sizeof(short));
	p->engTab.exp =20000;
	p->engTab.afe_gain = 1024;
	p->engTab.isp_gain = 1024;
	p->engTab.distance = 300; //mm
	//tuning para
	p->tuningPara[0].yTar = 230;  //285;  //188--->250
	p->tuningPara[0].antiIsoLevel = 5;  //-5---->5
	p->tuningPara[0].antiExpLevel = -5;
	p->tuningPara[0].antiStrobeLevel = -8; //-10; //fyx
	p->tuningPara[0].antiUnderLevel = 0;
	p->tuningPara[0].antiOverLevel = 0;
	p->tuningPara[0].foregroundLevel = 0;
	p->tuningPara[0].isRefAfDistance = 0;
	p->tuningPara[0].accuracyLevel = 2;  //-10--->0

	p->tuningPara[1].yTar = 230; //285;  //188--->250
	p->tuningPara[1].antiIsoLevel = 5;  //-5---->5
	p->tuningPara[1].antiExpLevel = -5;
	p->tuningPara[1].antiStrobeLevel = -8; //-10; //fyx
	p->tuningPara[1].antiUnderLevel = 0;
	p->tuningPara[1].antiOverLevel = 0;
	p->tuningPara[1].foregroundLevel = 0;
	p->tuningPara[1].isRefAfDistance = 0;
	p->tuningPara[1].accuracyLevel =2;  //-10--->0

	p->tuningPara[2].yTar = 230; //285;  //188--->250
	p->tuningPara[2].antiIsoLevel = 5;  //-5---->5
	p->tuningPara[2].antiExpLevel = -5;
	p->tuningPara[2].antiStrobeLevel = -8; //-10; //fyx
	p->tuningPara[2].antiUnderLevel = 0;
	p->tuningPara[2].antiOverLevel = 0;
	p->tuningPara[2].foregroundLevel = 0;
	p->tuningPara[2].isRefAfDistance = 0;
	p->tuningPara[2].accuracyLevel = 2;  //-10--->0

	p->tuningPara[3].yTar = 230; //285;  //188--->250
	p->tuningPara[3].antiIsoLevel = 5;  //-5---->5
	p->tuningPara[3].antiExpLevel = -5;
	p->tuningPara[3].antiStrobeLevel = -8; //-10; //fyx
	p->tuningPara[3].antiUnderLevel = 0;
	p->tuningPara[3].antiOverLevel = 0;
	p->tuningPara[3].foregroundLevel = 0;
	p->tuningPara[3].isRefAfDistance = 0;
	p->tuningPara[3].accuracyLevel = 2;  //-10--->0
	//is eng level used (or by firmware)
	p->isTorchEngUpdate =0;
	p->isNormaEnglUpdate =0;
	p->isLowBatEngUpdate =0;
	p->isBurstEngUpdate =0;
	//eng level
	memset(&p->engLevel, 0, sizeof(FLASH_ENG_LEVEL));

	*ret_size = sizeof(NVRAM_CAMERA_STROBE_STRUCT);
	return 0;
}
