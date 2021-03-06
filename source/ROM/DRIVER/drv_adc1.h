#ifndef _DRV_ADC1_H_
#define _DRV_ADC1_H_
/*
 * AIROHA Bluetooth Device Firmware
 * COPYRIGHT (C) 2014 AIROHA TECHNOLOGY CORP. CO., LTD. ALL RIGHTS RESERVED
 *
 * drv_adc1.h is the file defines the driver of ADC1 access.
 *
 * Programmer : ChiaHoHu@airoha.com.tw, Ext.3369
 */
#include "config.h"
#include "cpu.h"



////////////////////////////////////////////////////////////////////////////////
// Type Definitions ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Global Variables ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
// Function Prototypes /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
 * DRV_ADC1_Init
 *
 * Initialize the ADC1 hardware parameters
 *
 * @Author : ChiaHoHu <ChiaHoHu@airoha.com.tw>
 *
 */
EXTERN VOID DRV_ADC1_Init(U8 ch);

/**
 * DRV_ADC1_SetGainSel
 *
 * Set ADC1 Gain select
 *
 * @Author : ChiaHoHu <ChiaHoHu@airoha.com.tw>
 *
 */
EXTERN VOID DRV_ADC1_SetGainSel(U8 gain);

/**
 * DRV_ADC1_ChannelRead
 *
 * Read ADC1 Channel value.
 *
 * @Author : ChiaHoHu <ChiaHoHu@airoha.com.tw>
 *
 */
EXTERN U16 DRV_ADC1_ChannelRead(U8 ch);



#endif /* _DRV_ADC1_H_ */

