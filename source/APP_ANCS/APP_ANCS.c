#include "reside_flash.inc"

#define _APP_ANCS_C_

#include "rc.h"
#include "bt_config_profile.h"

#include "..\MMI\MMI_Base.h"

#ifdef LE_SUPPORTED_HOST_FLASH
#ifdef APP_ANCS_C
#include "..\BLE_Service\BLE_ANCS_C_interface.h"
#include "APP_ANCS_interface.h"
#ifdef ANCS_CELL_PHONE_APP
#include "APP_ANCS.h"
#include "..\ATT\ATT_SDK.h"
#include "..\ATT\ATT.h"
#include "..\MMI_LE\link_index_ctl.h"
#include "..\APP\APP_Interface.h"
#endif

#define DBG_UART_ENABLE_APP_ANCS
//#define DBG_CELL_PHONE_APP

#ifdef DBG_CELL_PHONE_APP
PRIVATE void APP_ANCS_NotificationDisable(U8 linkIdx);
PRIVATE void APP_ANCS_GetAppAttr(U8 linkIdx, BLE_ANCS_C_ATTR_LIST_STRU XDATA_PTR attrPtr);
PRIVATE void APP_ANCS_GetAppId(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr);
PRIVATE void APP_ANCS_PerformNotiAction(U8 linkIdx, U8 XDATA_PTR notiUID);
#endif

PRIVATE void APP_ANCS_EvtHandler(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr);

#ifdef ANCS_CELL_PHONE_APP
PUBLIC U8 APP_ANCS_RxCB(U8 CBtype)
{
    U8 serverIdx;
    U16 len;
    
    if(CBtype == CB_AFTER_WRITING)
    {
        serverIdx = ATT_FindServerIndexByAddr((U8 CODE_PTR)&gApp_ANCS_ctl.controlPointRx);
        len = ATT_GetAttributeValueCurrentLen(serverIdx);        

        BLE_ANCS_C_WriteData(0, gApp_ANCS_ctl.controlPointRx, len);
    }
    return 0;
}

PRIVATE void APP_ANCS_SetRsp(ANCS_APP_RSP_STRU XDATA_PTR rspPtr, U8 vocf, U8 result)
{
    if (rspPtr)
    {
        rspPtr->hciXportId = APP_HCI_EVENT_PACKET;
        rspPtr->hciEvtCode = HCI_EVENT_AIROHA_VENDOR;
        rspPtr->hciLen = ANCS_APP_RSP_BASIC_LEN;
        rspPtr->vocf = vocf;
        rspPtr->vogf = HCI_VENDOR_OGF_ANCS_RESP;
        rspPtr->result = result;
    }
}

PRIVATE void APP_ANCS_SendRspData(ANCS_APP_RSP_STRU XDATA_PTR rspPtr, U8 vocf, U8 result)
{
    APP_ANCS_SetRsp(rspPtr, vocf, result);
    APP_sendTxData((U8 XDATA_PTR)rspPtr, OS_OFFSET_OF(ANCS_APP_RSP_STRU, paraPtr));
}

PUBLIC void APP_ANCS_CmdRx(APP_CMD_STRU XDATA_PTR cmdPtr, U16 len)
{
    ANCS_APP_RSP_STRU XDATA_PTR rspPtr;
    
    if (len == (cmdPtr->hciLen + OS_OFFSET_OF(APP_CMD_STRU, vocf)))
    {
        switch (cmdPtr->vocf)
        {
            case ANCS_APP_CMD_SET_VIBRATION:
            {
                if (cmdPtr->hciLen == (ANCS_APP_VOCF_VOGF_LEN + ANCS_APP_CMD_SET_VIBRATION_PARA_LEN))
                {
                    if (rspPtr = (ANCS_APP_RSP_STRU XDATA_PTR)SYS_MemoryGet(OS_OFFSET_OF(ANCS_APP_RSP_STRU, paraPtr)))
                    {
                        #ifdef DBG_UART_ENABLE_APP_ANCS
                        LightDbgPrint("ancsSet %x %x %x %x %x %x", (U8)*(cmdPtr->paraPtr), (U8)*(cmdPtr->paraPtr+1), (U8)*(cmdPtr->paraPtr+2), (U8)*(cmdPtr->paraPtr+3), (U8)*(cmdPtr->paraPtr+4), (U8)*(cmdPtr->paraPtr+5));
                        #endif
                        BLE_ANCS_C_WriteVibrationSetting(cmdPtr->paraPtr);
                        APP_ANCS_SendRspData(rspPtr, cmdPtr->vocf, HCI_VEVT_OCF_RESULT_CODE_SUCCESS); 
                        OSMEM_Put((U8 XDATA_PTR)rspPtr);
                    }
                    return;
                }
            }
            break;

            case ANCS_APP_CMD_GET_VIBRATION:
            {
                if (rspPtr = (ANCS_APP_RSP_STRU XDATA_PTR)SYS_MemoryGet(OS_OFFSET_OF(ANCS_APP_RSP_STRU, paraPtr) + ANCS_APP_CMD_SET_VIBRATION_PARA_LEN))
                {
                    APP_ANCS_SetRsp((ANCS_APP_RSP_STRU XDATA_PTR)rspPtr, cmdPtr->vocf, HCI_VEVT_OCF_RESULT_CODE_SUCCESS);
                    rspPtr->hciLen += ANCS_APP_CMD_SET_VIBRATION_PARA_LEN;
                    OSMEM_memcpy_xdata_code(rspPtr->paraPtr, BLE_ANCS_C_GetVibrationSetting(), ANCS_APP_CMD_SET_VIBRATION_PARA_LEN);
                    APP_sendTxData((U8 XDATA_PTR)rspPtr, OS_OFFSET_OF(ANCS_APP_RSP_STRU, paraPtr) + ANCS_APP_CMD_SET_VIBRATION_PARA_LEN);
                    OSMEM_Put((U8 XDATA_PTR)rspPtr);
                }
                return;
            }
            break;

            default:
            {
                #ifdef DBG_UART_ENABLE_APP_ANCS
                LightDbgPrint("APP_ANCS_CMD: %x", (U8)cmdPtr->vocf);
                #endif
            }
            break;
        }
    }
    if (rspPtr = (ANCS_APP_RSP_STRU XDATA_PTR)SYS_MemoryGet(OS_OFFSET_OF(ANCS_APP_RSP_STRU, paraPtr)))
    {
        APP_ANCS_SendRspData(rspPtr, cmdPtr->vocf, HCI_VEVT_OCF_RESULT_CODE_FAIL);
        OSMEM_Put((U8 XDATA_PTR)rspPtr);
    }
}

PRIVATE void APP_ANCS_TxData(U8 linkIdx, U8 XDATA_PTR dataPtr, U16 len, BOOL isSrcNotif)
{
    ATT_SEND_DATA_STRU XDATA_PTR paraPtr;
    U8 CODE_PTR cccdAddr;
    U16 serviceIdx;

    if (isSrcNotif)
    {
        cccdAddr = gApp_ANCS_ctl.srcNotifTxCCCD;
        serviceIdx = gApp_ANCS_ctl.srcNotifTxIdx;
    }
    else
    {
        cccdAddr = gApp_ANCS_ctl.dataNotifTxCCCD;
        serviceIdx = gApp_ANCS_ctl.dataNotifTxIdx;
    }
    if ((((ATT_GetCCCDByLink(ATT_FindServerIndexByAddr(cccdAddr), 0)) >> 8) & 0x01) == 0)
    {
        #ifdef DBG_UART_ENABLE_APP_ANCS
        LightDbgPrint("APP_ANCS_TxData: CCCD Disable");
        #endif
        #ifdef DBG_CELL_PHONE_APP
        #else
            return;
        #endif
    }

    if (paraPtr = SYS_MemoryGet(sizeof(ATT_SEND_DATA_STRU)))
    {
        paraPtr->dataPtr = dataPtr;
        paraPtr->serverIdx = serviceIdx;
        paraPtr->len = len;
        paraPtr->maxLen = ANCS_MAX_SEND_TX_DATA_LEN;
        paraPtr->connHdl = LIC_LE_GetConnHdl(linkIdx);
        ATT_SendTxData(paraPtr);
        
        OSMEM_Put((U8 XDATA_PTR)paraPtr);
        #ifdef DBG_UART_ENABLE_APP_ANCS
        LightDbgPrint("APP_ANCS_TxData OK");
        #endif
        return;
    }
    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("APP_ANCS_TxData NG");
    #endif
}
#endif

PUBLIC void APP_ANCS_Init(void)
{
    BLE_ANCS_C_Init(0, APP_ANCS_EvtHandler);

    #ifdef ANCS_CELL_PHONE_APP
    gApp_ANCS_ctl.srcNotifTxIdx = ATT_FindServerIndexByAddr((U8 CODE_PTR)&gApp_ANCS_ctl.srcNotifTxIdx);
    gApp_ANCS_ctl.dataNotifTxIdx = ATT_FindServerIndexByAddr((U8 CODE_PTR)&gApp_ANCS_ctl.dataNotifTxIdx);
    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("APP_ANCS_Init %x %x", (U8)gApp_ANCS_ctl.srcNotifTxIdx, (U8)gApp_ANCS_ctl.dataNotifTxIdx);
    #endif
    #endif
}

PRIVATE void APP_ANCS_NotificationSetup(U8 linkIdx)
{
    BLE_ANCS_C_EnableNotifNotificationSource(linkIdx);
    BLE_ANCS_C_EnableNotifDataSource(linkIdx);
}

// test begin
// get notification attributes
#ifdef DBG_CELL_PHONE_APP
PRIVATE void APP_ANCS_NotificationDisable(U8 linkIdx)
{
    BLE_ANCS_C_DisableNotifNotificationSource(linkIdx);
    BLE_ANCS_C_DisableNotifDataSource(linkIdx);
}

PRIVATE void APP_ANCS_GetNotiAttr(U8 linkIdx, U8 XDATA_PTR notiUID)
{
    BLE_ANCS_C_GET_NOTI_ATTR_STRU XDATA_PTR paraPtr;
    BLE_ANCS_C_ATTR_STRU XDATA_PTR attrPtr;
    
    if (paraPtr = (BLE_ANCS_C_GET_NOTI_ATTR_STRU XDATA_PTR)SYS_MemoryGet(1))
    {
        OSMEM_memcpy_xdata_xdata(paraPtr->notiUID, notiUID, ANCS_NOTIF_UID_SIZE);
        paraPtr->numAttr = 1;
        attrPtr = paraPtr->attrList;
        attrPtr->attrId = NOTI_ATTR_ID_APP_ID;
        //attrPtr++;
        //attrPtr->attrId = NOTI_ATTR_ID_POSITIVE_ACTION_LABEL;
        //attrPtr++;
        //attrPtr->attrId = NOTI_ATTR_ID_NEGATIVE_ACTION_LABEL;
        
        BLE_ANCS_C_GetNotifAttributes(linkIdx, paraPtr);
        OSMEM_Put((U8 XDATA_PTR)paraPtr);
    }
}

// get app attributes
PRIVATE void APP_ANCS_GetAppAttr(U8 linkIdx, BLE_ANCS_C_ATTR_LIST_STRU XDATA_PTR attrPtr)
{
    BLE_ANCS_C_GET_APP_ATTR_STRU XDATA_PTR paraPtr;
    
    if (paraPtr = (BLE_ANCS_C_GET_NOTI_ATTR_STRU XDATA_PTR)SYS_MemoryGet(1))
    {
        //OSMEM_memcpy_xdata_xdata(paraPtr->notiUID, notiUID, ANCS_NOTIF_UID_SIZE);
        paraPtr->numAttr = 1;
        paraPtr->appIdLen = ENDIAN_TRANSFORM_U16(attrPtr->len);
        OSMEM_memcpy_xdata_xdata(paraPtr->appId, attrPtr->dataPtr, paraPtr->appIdLen);
        *(paraPtr->appId + paraPtr->appIdLen) = APP_ATTR_ID_DISPLAY_NAME;
        *(U16 XDATA_PTR)(paraPtr->appId + paraPtr->appIdLen + 1) = ENDIAN_TRANSFORM_U16(20); // spec not define but need length
        
        BLE_ANCS_C_GetAppAttributes(linkIdx, paraPtr);
        OSMEM_Put((U8 XDATA_PTR)paraPtr);
    }
}

PRIVATE void APP_ANCS_GetAppId(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr)
{
    U16 len = evtPtr->len;
    U8 XDATA_PTR attrList;
    U16 curTotalLen;

    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("APP_ANCS dataSrc len %x %x", (U8)len, (U8)(len>>8));
    #endif

    if (len < OS_OFFSET_OF(ANCS_DATA_SRC_STRU, attrId))
    {
        return;
    }
    len -= OS_OFFSET_OF(ANCS_DATA_SRC_STRU, attrId);
    attrList = &evtPtr->rsp.dataSrc.attrId;
    while (len)
    {
        curTotalLen = ENDIAN_TRANSFORM_U16(*(U16 XDATA_PTR)(attrList+1)) + sizeof(BLE_ANCS_C_ATTR_STRU);
        #ifdef DBG_UART_ENABLE_APP_ANCS
        LightDbgPrint("len %x %x %x %x %x %x", (U8)(ENDIAN_TRANSFORM_U16(*(U16 XDATA_PTR)(attrList+1))), (U8)((ENDIAN_TRANSFORM_U16(*(U16 XDATA_PTR)(attrList+1)))>>8), (U8)curTotalLen, (U8)(curTotalLen>>8), (U8)len, (U8)(len>>8));
        #endif
        if (len < curTotalLen)
        {
            return ;
        }
        #ifdef DBG_UART_ENABLE_APP_ANCS
        LightDbgPrint("attr", (U8)*attrList, (U8)*(attrList+1), (U8)*(attrList+2));
        LightDbgPrint("attrData %x %x %x %x", (U8)*(attrList+3), (U8)*(attrList+4), (U8)*(attrList+5), (U8)*(attrList+6));
        #endif
        
        if (*attrList == NOTI_ATTR_ID_APP_ID)
        {
            APP_ANCS_GetAppAttr(evtPtr->linkIdx, (BLE_ANCS_C_ATTR_LIST_STRU XDATA_PTR)attrList);
        }
        attrList += curTotalLen;
        len -= curTotalLen;        
    }
}

// perform notification action
PRIVATE void APP_ANCS_PerformNotiAction(U8 linkIdx, U8 XDATA_PTR notiUID)
{
    BLE_ANCS_C_PERFORM_NOTI_ACTION_STRU para;

    OSMEM_memcpy_xdata_xdata(para.notiUID, notiUID, ANCS_NOTIF_UID_SIZE);
    para.actionId = ACTION_ID_NEGATIVE;
    
    BLE_ANCS_C_PerformNotiAction(linkIdx, &para);
}
// test end
#endif  //#ifdef DBG_CELL_PHONE_APP

PRIVATE void APP_ANCS_SrcNotif(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr)
{
    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("srcNotif %x %x %x %x", (U8)evtPtr->rsp.notiSrc.evtId, (U8)evtPtr->rsp.notiSrc.evtFlag, (U8)evtPtr->rsp.notiSrc.ctgyId, (U8)evtPtr->rsp.notiSrc.ctgyCount);
    LightDbgPrint("uid %x %x %x %x", evtPtr->rsp.notiSrc.notiUID[0], evtPtr->rsp.notiSrc.notiUID[1], evtPtr->rsp.notiSrc.notiUID[2], evtPtr->rsp.notiSrc.notiUID[3]);
    #endif
    
    switch (evtPtr->rsp.notiSrc.ctgyId)
    {
        #ifdef DBG_CELL_PHONE_APP
        case CATEGORY_ID_INCOMING_CALL:
        {
            if (evtPtr->rsp.notiSrc.evtId == EVENT_ID_NOTIFICATION_ADDED)
            {
                //APP_ANCS_PerformNotiAction(evtPtr->linkIdx, evtPtr->rsp.notiSrc.notiUID);
        		{
                U8 cmd[] = {0x01, 0x00, 0xFC, 0x08, 0x01, 0x4C, 0xFF,0xFF,0xFF,0xFF,0x00,0x00};
                APP_ANCS_CmdRx((APP_CMD_STRU XDATA_PTR)cmd, sizeof(cmd));
                cmd[3]=2;
                cmd[4]=2;
                APP_ANCS_CmdRx((APP_CMD_STRU XDATA_PTR)cmd, 6);
                }
            }
        }
        break;
        #endif
        
        default:
        {
        	#ifdef DBG_CELL_PHONE_APP
        	if ((evtPtr->rsp.notiSrc.evtId == EVENT_ID_NOTIFICATION_ADDED) && (evtPtr->rsp.notiSrc.ctgyId == CATEGORY_ID_OTHER))
        	{
        	    //APP_ANCS_GetNotiAttr(evtPtr->linkIdx, evtPtr->rsp.notiSrc.notiUID);
        	    U8 writeData[6] = {0};

        	    OSMEM_memcpy_xdata_xdata((U8 XDATA_PTR)&writeData[1], evtPtr->rsp.notiSrc.notiUID, 4);
        	    writeData[5] = 0;
        	    BLE_ANCS_C_WriteData(0, (U8 XDATA_PTR)writeData, 6);
        	    
        	}
        	#endif
        }
        break;
       
    }

    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("Vibrate %x %x %x %x %x %x", (U8)*(BLE_ANCS_C_GetVibrationSetting()), (U8)*(BLE_ANCS_C_GetVibrationSetting()+1), (U8)*(BLE_ANCS_C_GetVibrationSetting()+2), (U8)*(BLE_ANCS_C_GetVibrationSetting()+3), (U8)*(BLE_ANCS_C_GetVibrationSetting()+4), (U8)*(BLE_ANCS_C_GetVibrationSetting()+5));
    #endif
    if (evtPtr->rsp.notiSrc.evtFlag & ANCS_EVENT_FLAG_MASK_PRE_EXISTING)
    {
        return; // avoid vibration
    }
    if (evtPtr->rsp.notiSrc.evtId <= EVENT_ID_NOTIFICATION_REMOVED && evtPtr->rsp.notiSrc.ctgyId <= CATEGORY_ID_ENTERMAINMENT)    
    {
        if ((*(U16 XDATA_PTR)&(BLE_ANCS_C_GetVibrationSetting() + (evtPtr->rsp.notiSrc.evtId * 2))) & ENDIAN_TRANSFORM_U16(BIT_MASK16(evtPtr->rsp.notiSrc.ctgyId)))
        {
            MMI_PushMediaEvent(MEDIA_EVT_FM_MUTE_ON);
            #ifdef DBG_UART_ENABLE_APP_ANCS
            LightDbgPrint("MEDIA_EVT_FM_MUTE_ON %x %x", (U8)ENDIAN_TRANSFORM_U16(BIT_MASK16(evtPtr->rsp.notiSrc.ctgyId)), (U8)BIT_MASK16(evtPtr->rsp.notiSrc.ctgyId));
            #endif
        }
    }
}

PRIVATE void APP_ANCS_DataNotif(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr)
{
    #ifdef DBG_UART_ENABLE_APP_ANCS
    U8 XDATA_PTR printPtr = evtPtr->rsp.dataSrc.attrValue;
    LightDbgPrint("dataNotif %x %x %x %x", (U8)evtPtr->rsp.dataSrc.cmdId, (U8)evtPtr->rsp.dataSrc.attrId, (U8)evtPtr->rsp.dataSrc.attrLen, (U8)(evtPtr->rsp.dataSrc.attrLen>>8));
    LightDbgPrint("dataNotif %x %x %x %x %x %x", printPtr[0], printPtr[1], printPtr[2], printPtr[3], printPtr[4], printPtr[5]);
    #endif

    switch (evtPtr->rsp.dataSrc.cmdId)
    {
        case CMD_ID_GET_NOTIFICATION_ATTRIBUTES:
        {
            #ifdef DBG_CELL_PHONE_APP
            U8 FB_APP_ID[] =
            {
                0x63, 0x6F, 0x6D, 0x2E, 0x66, 0x61, 0x63, 0x65, 0x62, 0x6F, 0x6F, 0x6B, 0x2E, 0x4D, 0x65, 0x73, 0x73, 0x65, 0x6E, 0x67, 0x65, 0x72
            };
            if (evtPtr->rsp.dataSrc.attrId == NOTI_ATTR_ID_APP_ID && !OS_memcmp(evtPtr->rsp.dataSrc.attrValue, (U8 XDATA_PTR)FB_APP_ID, ENDIAN_TRANSFORM_U16(evtPtr->rsp.dataSrc.attrLen)))
            {
                APP_ANCS_GetAppId(evtPtr);
            }            
            #endif
        }
        break;

        case CMD_ID_GET_APP_ATTRIBUTES:
        {
            #ifdef DBG_CELL_PHONE_APP
            //APP_ANCS_NotificationDisable(evtPtr->linkIdx);
            #endif
        }
        break;

        case CMD_ID_PERFORM_NOTIFICATION_ACTION:
        break;
    }
}

PRIVATE void APP_ANCS_EvtHandler(BLE_ANCS_C_EVT_STRU XDATA_PTR evtPtr)
{
    #ifdef DBG_UART_ENABLE_APP_ANCS
    LightDbgPrint("APP_ANCS_EvtHandler %x", (U8)evtPtr->evtId);
    #endif
    
    switch (evtPtr->evtId)
    {
        case ANCS_C_EVT_DISCOVER_COMPLETE:
        {
            APP_ANCS_NotificationSetup(evtPtr->linkIdx);
        }
        break;

        case ANCS_C_EVT_DISCOVER_FAILED:
        {
            #ifdef DBG_UART_ENABLE_APP_ANCS
            LightDbgPrint("ANCS Discover failed! %x", (U8)evtPtr->rsp.errCode);
            #endif
        }
        break;

        case ANCS_C_EVT_SOURCE_NOTIFICATION:
        {
            APP_ANCS_SrcNotif(evtPtr);
            #ifdef ANCS_CELL_PHONE_APP
            APP_ANCS_TxData(evtPtr->linkIdx, (U8 XDATA_PTR)&evtPtr->rsp, evtPtr->len, TRUE);
            #endif
        }
        break;

        case ANCS_C_EVT_DATA_NOTIFICATION:
        {
            APP_ANCS_DataNotif(evtPtr);
            #ifdef ANCS_CELL_PHONE_APP
            APP_ANCS_TxData(evtPtr->linkIdx, (U8 XDATA_PTR)&evtPtr->rsp, evtPtr->len, FALSE);
            #endif
        }
        break;
    }
}
#endif
#endif
