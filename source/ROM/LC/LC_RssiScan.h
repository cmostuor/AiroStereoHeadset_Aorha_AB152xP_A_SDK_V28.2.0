/*
 * AIROHA Bluetooth Device Firmware
 * COPYRIGHT (C) 2014 AIROHA TECHNOLOGY CORP. CO., LTD. ALL RIGHTS RESERVED
 *
 * LC_RssiScan.h is the include file of LC_RssiScan.c defines the header file of channel assessment handler.
 *
 * Programmer : AmosLin@airoha.com.tw, Ext.2851
 *              CharlesSu@airoha.com.tw, Ext.2882
 */
////////////////////////////////////////////////////////////////////////////////
// Constant Definitions ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#ifndef _LC_RSSISCAN_H_
#define _LC_RSSISCAN_H_

////////////////////////////////////////////////////////////////////////////////
// Type Definitions ////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// Extern Function /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#define RSSISCAN_CHANNEL_NUM 40
#define RSSI_MAX_LV 20

EXTERN U8 XDATA RssiScanChannel[RSSISCAN_CHANNEL_NUM];
EXTERN U8 XDATA RssiLv[RSSISCAN_CHANNEL_NUM];

#endif