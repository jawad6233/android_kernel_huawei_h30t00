/*  MoReUse 2002-09-13 Continuus Version 2                                      */
/*                                                                              */
/* Changes: made ansi compliant                                                 */
/*--------------------------------------------------------------------------    */
 /* (C) Copyright 2002 Koninklijke Philips Electronics N.V., All Rights Reserved*/
 /*                                                                             */
 /* This source code and any compilation or derivative thereof is the sole      */
 /* property of Philips Corporation and is provided pursuant to a Software      */
 /* License Agreement.  This code is the proprietary information of             */
 /* Philips Corporation and is confidential in nature.  Its use and             */
 /* dissemination by any party other than Philips Corporation is strictly       */
 /* limited by the confidential information provisions of the Agreement         */
 /* referenced above.                                                           */
 /*-------------------------------------------------------------------------    */
 /* FILENAME:     tmFlags.h                                                     */
 /*                                                                             */
 /* DESCRIPTION:  Platform dependent build flags (typically generated by the    */
 /*               SDE build process if it doesn't already exist).               */
 /*                                                                             */
 /* DOCUMENT REF: DVP Build Process Specification                               */
 /*                                                                             */
 /* NOTES:        This file defines the TMFL_xxx build flags configuration.     */
 /*               It does not include specific component diversity flags that   */
 /*               are defined in the component makefiles (e.g., TMFL_SCOPE      */
 /*               defined in BSL board files)                                   */
 /*                                                                             */
 /*               This file is based on SDE Version 1.2 generated output.       */
 /*-------------------------------------------------------------------------    */
 /*                                                                             */
 #ifndef TM_FLAGS_H
 #define TM_FLAGS_H

/* Configurable build flags                                                     */
/* NOTE: The following flags are configurable (typically generated by SDE       */
/*          based on _TMXXX build environment variables).  See individual flags */
/*         for comments about the settings and consistency requirements.        */

/* TMFL_BUILD_VERSION: <Major>.<Minor>.<BuildNumber> as decimal digits. This    */
/*   number is product/release dependent and not standardized as of now.        */
/*#define TMFL_BUILD_VERSION            00.01.00*/

/* RIDE tool does not support . in define value */
/* TMFL_BUILD_VERSION is not used to specify neither TDA9975_SW version not TDA9983_SW version */ 
#define TMFL_BUILD_VERSION            00

/* TMFL_CPU: CPU type/model numbers: (TMFL_CPU_TYPE_XXX | TMFL_CPU_MODEL_XXX).  */
/*   Example: (TMFL_CPU_TYPE_X86 | TMFL_CPU_MODEL_I486) or (TMFL_CPU_I486) for  */
/*   an x86 i486 CPU.                                                           */
 #define TMFL_CPU                      (TMFL_CPU_TYPE_X86 | TMFL_CPU_MODEL_I486)

/* TMFL_ENDIAN: CPU endianness: <TMFL_ENDIAN_BIG | TMFL_ENDIAN_LITTLE>          */
 #define TMFL_ENDIAN                   (TMFL_ENDIAN_LITTLE)

/* TMFL_OS: Operating system type/version where the version number should be    */
/*   included if defined: (TMFL_OS_<TTT>[VVV]).  Example: TMFL_OS_PSOS250       */
/*   indicates that the target OS is pSOS Version 2.50.                         */ 
 #define TMFL_OS                       (TMFL_OS_NULLOS)

/* TMFL_CPU_IS_XXX: These are boolean flags that reflects the CPU type and      */
/*   must be consistent with the TMFL_CPU setting (i.e., if TMFL_CPU =          */
/*   TMFL_CPU_I486, then TMFL_CPU_IS_X86 = 1) and all other TMFL_CPU_IS_XXX     */
/*	 flags are 0.                                                               */
 #define TMFL_CPU_IS_X86               1
 #define TMFL_CPU_IS_MIPS              0
 #define TMFL_CPU_IS_HP                0
 #define TMFL_CPU_IS_TM                0
 #define TMFL_CPU_IS_ARM               0
 #define TMFL_CPU_IS_REAL              0

/* TMFL_OS_IS_XXX: These are boolean flags that reflects the OS type and        */
/*   must be consistent with the TMFL_OS setting (i.e., if TMFL_OS =            */
/*   TMFL_OS_PSOS250, then TMFL_OS_IS_PSOS = 1) and all other TMFL_OS_IS_XXX    */
/*   flags are 0.                                                               */
 #define TMFL_OS_IS_BTM                0
 #define TMFL_OS_IS_CE                 0
 #define TMFL_OS_IS_NT                 0
 #define TMFL_OS_IS_PSOS               0
 #define TMFL_OS_IS_NULLOS             1
 #define TMFL_OS_IS_ECOS               0
 #define TMFL_OS_IS_VXWORKS            0
 #define TMFL_OS_IS_MTOS               0


/* Non-configurable constants                                                   */
/* NOTE: These values do not change and should not be modified !                */
 #define TMFL_CPU_TYPE_MASK            0xffff0000
 #define TMFL_CPU_TYPE_X86             0x00010000
 #define TMFL_CPU_TYPE_MIPS            0x00020000
 #define TMFL_CPU_TYPE_TM              0x00030000
 #define TMFL_CPU_TYPE_HP              0x00040000
 #define TMFL_CPU_TYPE_ARM             0x00050000
 #define TMFL_CPU_TYPE_REAL            0x00060000
 #define TMFL_CPU_MODEL_MASK           0x0000ffff
 #define TMFL_CPU_MODEL_I486           0x00000001
 #define TMFL_CPU_MODEL_R3940          0x00000002
 #define TMFL_CPU_MODEL_R4300          0x00000003
 #define TMFL_CPU_MODEL_TM1100         0x00000004
 #define TMFL_CPU_MODEL_TM1300         0x00000005
 #define TMFL_CPU_MODEL_TM32           0x00000006
 #define TMFL_CPU_MODEL_HP             0x00000007
 #define TMFL_CPU_MODEL_R4640          0x00000008
 #define TMFL_CPU_MODEL_ARM7           0x00000009
 #define TMFL_CPU_MODEL_ARM920T        0x0000000a
 #define TMFL_CPU_MODEL_ARM940T        0x0000000b
 #define TMFL_CPU_MODEL_ARM10          0x0000000c
 #define TMFL_CPU_MODEL_STRONGARM      0x0000000d
 #define TMFL_CPU_MODEL_RD24120        0x0000000e
 #define TMFL_CPU_MODEL_ARM926EJS      0x0000000f
 #define TMFL_CPU_MODEL_ARM946         0x00000010
 #define TMFL_CPU_MODEL_R1910          0x00000011
 #define TMFL_CPU_MODEL_R4450          0x00000012
 #define TMFL_CPU_MODEL_TM3260         0x00000013
 #define TMFL_ENDIAN_BIG               1
 #define TMFL_ENDIAN_LITTLE            0
 #define TMFL_OS_MASK                  0xff000000
 #define TMFL_OS_VERSION_MASK          0x00ffffff
 #define TMFL_OS_BTM                   0x00000000
 #define TMFL_OS_CE                    0x01000000
 #define TMFL_OS_CE212                 0x01020102
 #define TMFL_OS_CE300                 0x01030000
 #define TMFL_OS_NT                    0x02000000
 #define TMFL_OS_NT4                   0x02040000
 #define TMFL_OS_PSOS                  0x03000000
 #define TMFL_OS_PSOS250               0x03020500
 #define TMFL_OS_PSOS200               0x03020000
 #define TMFL_OS_NULLOS                0x04000000
 #define TMFL_OS_ECOS                  0x05000000
 #define TMFL_OS_VXWORKS               0x06000000
 #define TMFL_OS_MTOS                  0x07000000
 #define TMFL_SCOPE_SP                 0
 #define TMFL_SCOPE_MP                 1
 #define TMFL_REL_ASSERT               0x00000002
 #define TMFL_REL_DEBUG                0x00000001
 #define TMFL_REL_RETAIL               0x00000000
 #define TMFL_CPU_I486                 0x00010001
 #define TMFL_CPU_R3940                0x00020002
 #define TMFL_CPU_R4300                0x00020003
 #define TMFL_CPU_TM1100               0x00030004
 #define TMFL_CPU_TM1300               0x00030005
 #define TMFL_CPU_TM32                 0x00030006
 #define TMFL_CPU_HP                   0x00040007
 #define TMFL_CPU_R4640                0x00020008
 #define TMFL_CPU_ARM7                 0x00050009
 #define TMFL_CPU_ARM920T              0x0005000a
 #define TMFL_CPU_ARM940T              0x0005000b
 #define TMFL_CPU_ARM10                0x0005000c
 #define TMFL_CPU_STRONGARM            0x0005000d
 #define TMFL_CPU_RD24120              0x0006000e
 #define TMFL_CPU_ARM926EJS            0x0005000f
 #define TMFL_CPU_ARM946               0x00050010
 #define TMFL_CPU_R1910                0x00020011
 #define TMFL_CPU_R4450                0x00020012
 #define TMFL_CPU_TM3260               0x00030013
 #define TMFL_MODE_KERNEL              1
 #define TMFL_MODE_USER                0

/******************************************************************************/
/*	Components features defines                                               */
/******************************************************************************/
#ifdef TMFL_TDA19988
#	ifndef TMFL_TDA19989
#		define TMFL_TDA19989
#	endif /* TMFL_TDA19989 */
#	define TMFL_RGB_DDR_12BITS
#	define TMFL_HDCP_OPTIMIZED_POWER
#endif /* TMFL_TDA19988 */

#ifdef TMFL_TDA19989
#	ifndef TMFL_TDA9989
#		define TMFL_TDA9989
#		define SUPPORT_3D_FP
#	endif /* TMFL_TDA9989 */
#endif /* TMFL_TDA19989 */
/******************************************************************************/
/* Preprocessor checks for invalid settings (if file is manually modified)    */
/******************************************************************************/
/*                                                                            */

/* Check if TMFL_CPU flag changed from its default setting.                   */
#if     (TMFL_CPU == (TMFL_CPU_TYPE_MASK | TMFL_CPU_MODEL_MASK))
#error  ERROR: TMFL_CPU must be set (TMFL_CPU_TYPE_XXX | TMFL_CPU_MODEL_XXX) !
#endif

/* Check if TMFL_ENDIAN flag setting is valid.                                */
#if     ((TMFL_ENDIAN != TMFL_ENDIAN_BIG) && (TMFL_ENDIAN != TMFL_ENDIAN_LITTLE))
#error  ERROR: TMFL_ENDIAN must be set to a valid TMFL_ENDIAN_XXX value !
#endif

/* Check if TMFL_OS flag changed from its default setting.                    */
#if     (TMFL_OS == (TMFL_OS_MASK | TMFL_OS_VERSION_MASK))
#error  ERROR: TMFL_OS must be set to a valid value (TMFL_OS_<TYPE>[<VERSION>]) !
#endif

/* The TMFL_CPU_IS_XXX is a Boolean; one and only one flag can be true (=1).  */
#if     ((TMFL_CPU_IS_X86 + TMFL_CPU_IS_MIPS + TMFL_CPU_IS_TM + TMFL_CPU_IS_HP + TMFL_CPU_IS_ARM + TMFL_CPU_IS_REAL) != 1)
#error  ERROR: One or more TMFL_CPU_IS_XXX values are incorrect or missing !
#endif

/* TMFL_CPU and TMFL_CPU_IS_XXX must be consistent                            */
#if     (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_X86)  && (TMFL_CPU_IS_X86 != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_X86 settings !
#elif   (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_MIPS) && (TMFL_CPU_IS_MIPS != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_MIPS settings !
#elif   (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_TM)   && (TMFL_CPU_IS_TM != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_TM settings !
#elif   (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_HP)   && (TMFL_CPU_IS_HP != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_HP settings !
#elif   (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_ARM)  && (TMFL_CPU_IS_ARM != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_ARM settings !
#elif   (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_REAL) && (TMFL_CPU_IS_REAL != 1))
#error  ERROR: Inconsistent TMFL_CPU and TMFL_CPU_IS_REAL settings !
#endif /* (((TMFL_CPU & TMFL_CPU_TYPE_MASK) == TMFL_CPU_TYPE_X86) && ...      */

/* The TMFL_OS_IS_XXX is a Boolean; one and only one flag can be true (=1).   */
#if     ((TMFL_OS_IS_BTM + TMFL_OS_IS_CE + TMFL_OS_IS_NT + TMFL_OS_IS_PSOS + TMFL_OS_IS_NULLOS + TMFL_OS_IS_ECOS + TMFL_OS_IS_VXWORKS + TMFL_OS_IS_MTOS) != 1)
#error  ERROR: One or more TMFL_OS_IS_XXX values are incorrect or missing !
#endif

#if     (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_BTM)     && (TMFL_OS_IS_BTM != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_BTM settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_CE)      && (TMFL_OS_IS_CE != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_CE settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_NT)      && (TMFL_OS_IS_NT != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_NT settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_PSOS)    && (TMFL_OS_IS_PSOS != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_PSOS settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_NULLOS)  && (TMFL_OS_IS_NULLOS != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_NULLOS settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_ECOS)    && (TMFL_OS_IS_ECOS != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_ECOS settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_VXWORKS) && (TMFL_OS_IS_VXWORKS != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_VXWORKS settings !
#elif   (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_MTOS)    &&  (TMFL_OS_IS_MTOS != 1))
#error  ERROR: Inconsistent TMFL_OS and TMFL_OS_IS_MTOS settings !
#endif /* (((TMFL_OS & TMFL_OS_MASK) == TMFL_OS_XX) && (TMFL_OS_IS_XX != 1))  */

#endif   /* TM_FLAGS_H                                        */
