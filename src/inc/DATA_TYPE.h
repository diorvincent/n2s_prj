/*
 * DATA_TYPE.h
 * Xi'An ManHui Info. Science LLC
 * Created on: Nov 29, 2023
 * Author: Xue Le
 */

#ifndef DATA_TYPE_DATA_TYPE_H_
#define DATA_TYPE_DATA_TYPE_H_
/* ===========================================  Includes  =========================================== */
#include <stdint.h>


/* ===========================================  Typedef   =========================================== */
typedef uint8_t   U8;
typedef int8_t    S8;
typedef uint16_t  U16;
typedef int16_t   S16;
typedef uint32_t  U32;
typedef int32_t   S32;
typedef float     F32;
typedef double    F64;
typedef U8        flag;
typedef flag      FLAG;

/* ==========================================  Variables  =========================================== */


/* ==========================================    Define   =========================================== */
#define CAL_ADDR __attribute__ ((section(".CalData")))

#define U8_DISP         U8
#define U8_CAL          volatile const U8
#define U8_MIN          (0U)
#define U8_MAX          (255U)

#define S8_DISP         S8
#define S8_CAL          volatile const S8
#define S8_MIN          (-128)
#define S8_MAX          ( 127)

#define U16_DISP        U16
#define U16_CAL         volatile const U16
#define U16_MIN         (0U)
#define U16_MAX         (65535U)

#define S16_DISP        S16
#define S16_CAL         volatile const S16
#define S16_MIN         (-32768)
#define S16_MAX         ( 32767)

#define U32_DISP        U32
#define U32_CAL         volatile const U32
#define U32_MIN         (0U)
#define U32_MAX         (4294967295U)

#define S32_DISP        S32
#define S32_CAL         volatile const S32
#define S32_MIN         (-2147483648)
#define S32_MAX         ( 2147483647)

#define F32_DISP        F32
#define F32_CAL         volatile const F32

#define F64_DISP        F64
#define F64_CAL         volatile const F64
/* =====================================  Functions declaration  ==================================== */

#endif /* DATA_TYPE_DATA_TYPE_H_ */
