#include "reside_flash.inc"

#define _MMI_HID_C_

#include "MMI.h"
#ifdef HID_Profile
#include "MMI_HID.h"
#include "MMI_SCN.h"
#include "MMI_SDAP.h"
#include "MMI_Reconnect.h"
#include "MMI_Protocol.h"
#include "..\HID\HID_interface.h"
#include "MMI_State.h"
#include "..\SDAP\SDAP_InterFace.H"

U8 CODE KB_Base_Report[] =
{
	8, 0, 0, 0, 0, 0, 0, 0, 
	10, 0, 0, 0, 
	0xA1, // hid header
	0x01, // report id
};

U8 CODE Phtograph_Base_Report[] =
{
	8, 0, 0, 0, 0, 0, 0, 0, 
	3, 0, 0, 0, 0xA1,
	0x02, 0x00,

};

PRIVATE VOID MMI_Send_Photograph_KeyEvent(U8 linkIndex, U8 Length, U8 ReportID, U8 Data0, U8 Data1, U8 Data2)
{
	U8 XDATA_PTR ptr1;

	ptr1 = OSMEM_Get (OSMEM_ptr1);

    if (ptr1)
    {
        OSMEM_memset_xdata(&ptr1[13], 0, Length);
    	OSMEM_memcpy_xdata_code ( ptr1, Phtograph_Base_Report, sizeof (Phtograph_Base_Report));

    	ptr1[8] = Length;
    	ptr1[13] = ReportID;
    	ptr1[14] = Data0;
    	ptr1[15] = Data1;
    	ptr1[16] = Data2;
    	LightDbgPrint("SelfieKey! %d", gHID_channel_ctl[linkIndex].channelHDLIndex[HID_INTERRUPT_CHANNEL]->channel_state);
    	UpperLayer_SendL2capChannelData(gHID_channel_ctl[linkIndex].channelHDLIndex[HID_INTERRUPT_CHANNEL], (U8 XDATA_PTR)ptr1);
    	//OSMQ_Put (OSMQ_L2CAP_Data_From_Protocol_ptr[interruptChannelIndex], ptr1 );
    	//OSMQ_Put (OSMQ_L2CAP_Data_From_Profile_ptr[gPM_ctl.channel_index[PM_INTERRUPT_CHANNEL]], ptr1 );
	}
}

PRIVATE void MMI_SendShutterKeyCode(U8 linkIndex)
{
    if (SDAP_IsIOS(linkIndex))
    {
        MMI_Send_Photograph_KeyEvent(linkIndex, 4, 0x03, 0xE9, 0x00, 0x00 );//Vol+
        MMI_Send_Photograph_KeyEvent(linkIndex, 4, 0x03, 0x00, 0x00, 0x00 );//Vol+	Release
    }
    else
    {   
        //MMI_Send_Photograph_KeyEvent(linkIndex, 10, 0x01, 0x00, 0x00, 0x28 );//KB Enter
        //MMI_Send_Photograph_KeyEvent(linkIndex, 10, 0x01, 0x00, 0x00, 0x00 );//KB Enter Release
    	MMI_Send_Photograph_KeyEvent(linkIndex, 5, 0x01, 0x01, 0x00, 0x00 );//Joystick
    	MMI_Send_Photograph_KeyEvent(linkIndex, 5, 0x03, 0x00, 0x08, 0x00 );//Vol+
    	MMI_Send_Photograph_KeyEvent(linkIndex, 5, 0x01, 0x00, 0x00, 0x00 );//Joystick Release
    	MMI_Send_Photograph_KeyEvent(linkIndex, 5, 0x03, 0x00, 0x00, 0x00 );//Vol+	Release

    	MMI_Send_Photograph_KeyEvent(linkIndex, 3, 0x02, 0x01, 0x00, 0x00 );//Mouse
    	MMI_Send_Photograph_KeyEvent(linkIndex, 3, 0x02, 0x00, 0x00, 0x00 );//Mouse
    }  
}

PRIVATE void MMI_HID_Reconnect(U8 linkIndex)
{
    if (MMI_ConnectProfile(linkIndex, PROFILE_HID))
	{
	    gMMI_HID_ctl.hidCtl[linkIndex].actionMisc |= MMI_HID_ACTION_SEND_SELFIE_KEY;
	}
}

PRIVATE void MMI_HID_KeySelfie(U8 linkIndex)
{
	LightDbgPrint("Selfie %x %x!!", (U8)linkIndex, (U8)gHID_channel_ctl[linkIndex].channelHDLIndex[HID_INTERRUPT_CHANNEL]->channel_state);
	if (!HID_IsEnable())
	{
	    LightDbgPrint("ignore selfie key");
	    // TESTING...
	    //MMI_HID_SetProfileAvailable(TRUE);
	    return;
	}
	if (gHID_channel_ctl[linkIndex].mmiProfileInfo.state == HID_STATE_CONNECTED)
	{
	    MMI_SendShutterKeyCode(linkIndex);
	}
	else if (gHID_channel_ctl[linkIndex].mmiProfileInfo.state == HID_STATE_IDLE && ((gMMI_ctl.mmiInfo[linkIndex].linkPara.miscMask & MMI_ACTIVE_CONNECT) != MMI_ACTIVE_CONNECT))
	{
	    MMI_HID_Reconnect(linkIndex);
	}
	// TESTING...
	//MMI_HID_SetProfileAvailable(FALSE);
}

PRIVATE void MMI_HID_SwitchSelfie(U8 linkIndex)
{
    UNUSED(linkIndex);
    MMI_HID_SetProfileAvailable(!HID_IsEnable());
}

static MMI_KEY_EVT CODE MMI_HID_KeyEvtHandler[HID_KEY_EVENT_NO] =
{
	{MMI_HID_KeySelfie}, //HID_KEY_EVENT_KEY_SELFIE
	{MMI_HID_SwitchSelfie}, //HID_KEY_EVENT_SWITCH_SELFIE
};

PUBLIC void MMI_HID_CreateConnection(U8 linkIndex)
{
    LightDbgPrint("MMI_HID_CreateConnection %x %x", (U8)gHID_channel_ctl[linkIndex].mmiProfileInfo.state, (U8)MMI_SDAP_IsSupportHID(linkIndex));
	if(gHID_channel_ctl[linkIndex].mmiProfileInfo.state == HID_STATE_IDLE)
	{
		if(MMI_SUPPORT_HID_FEAT && MMI_SDAP_IsSupportHID(linkIndex))
		{
		    HID_ProfileConnectionRequest(linkIndex);
		}
	}
}

PUBLIC BOOL MMI_HID_ReleaseServiceLink(U8 linkIndex)
{
    UNUSED(linkIndex);
    
    return TRUE;
}

PUBLIC void MMI_HID_ConnectedHandle(U8 linkIndex)
{
	gHID_channel_ctl[linkIndex].mmiProfileInfo.state = HID_STATE_CONNECTED;    
    MMI_ConnectableStateChangeWhenConnected();
}

PUBLIC void MMI_HID_EventHandler(U8 linkIndex, U8 eventCode)
{
    switch (eventCode)
    {
        case HID_CONNECTION_COMPLETE_EVENT:                                    
            //cttodo
            MMI_ActivateProfile(linkIndex, &gHID_channel_ctl[linkIndex].mmiProfileInfo);
            if ((gMMI_ctl.mmiInfo[linkIndex].linkPara.miscMask & MMI_ACTIVE_CONNECT) == MMI_ACTIVE_CONNECT)
            {
                //MMI_PrepareActiveProfileConnectionOri(linkIndex);
            }
            else
            {
                MMI_SniffEnable(linkIndex, MMI_SNIFF_ACL_READY_SLC_NOT_YET);
            }

            if (gMMI_HID_ctl.hidCtl[linkIndex].actionMisc & MMI_HID_ACTION_SEND_SELFIE_KEY)
            {
                gMMI_HID_ctl.hidCtl[linkIndex].actionMisc &= ~(MMI_HID_ACTION_SEND_SELFIE_KEY);
                MMI_HID_KeySelfie(linkIndex);
            }
            LightDbgPrint("MMI_HID Connected %x %x", (U8)linkIndex, (U8)gHID_channel_ctl[linkIndex].channelHDLIndex[HID_INTERRUPT_CHANNEL]->channel_state);
            LightDbgPrint("MMI - topState: %x", (U8)MMI_GetTopStateByLink(linkIndex));            
            break;
            
        case HID_DISCONNECTION_COMPLETE_EVENT:
        {
            LightDbgPrint("MMI_HID Disconnected %x %x", (U8)MMI_GetTopStateByLink(linkIndex), gHID_channel_ctl[linkIndex].mmiProfileInfo.state);
            if (gHID_channel_ctl[linkIndex].mmiProfileInfo.state == HID_STATE_IDLE)
            {
                return;
            }                        
            //cttodo
            //MMI_DeMountProfile(linkIndex, &gMMIHID_ProfileNode[linkIndex]);
//            MMI_DEL_HID_LINK(linkIndex);
            gHID_channel_ctl[linkIndex].mmiProfileInfo.state = HID_STATE_IDLE; 
            MMI_PROTOCOL_L2CAPDisconnected(linkIndex, PROFILE_LINK_EVENT_DISC_COMPLETE, FALSE);
            MMI_UnloadProfile(linkIndex, &gHID_channel_ctl[linkIndex].mmiProfileInfo);
            OSMEM_memset_xdata(&gMMI_HID_ctl.hidCtl[linkIndex], 0, sizeof(MmiHidCtlType));
        }
        break;                
    }    
}

PUBLIC void MMI_HID_ProcessUartCmd(U8 linkIndex, U16 len, U8 XDATA_PTR dataPtr, U8 XDATA_PTR msgPtr)
{
    U16 curLen;
    
    if (len < 1)
    {
        OSMEM_Put(msgPtr);
        return;
    }
    
    if (msgPtr)
    {
        curLen = len;
        while(curLen)
        {
            *(msgPtr+HID_DATA_OFFSET+curLen-1) = *(dataPtr+curLen-1);  // copy from back to head since the same memory block, and destination position is shift one byte
            curLen--;
        }
        OSMEM_memcpy_xdata_code(msgPtr, KB_Base_Report, sizeof (KB_Base_Report));
        *(U16 XDATA_PTR)(msgPtr + HID_LENGTH_OFFSET) = ENDIAN_TRANSFORM_U16(len + 2); // hid header + report id

        UpperLayer_SendL2capChannelData(gHID_channel_ctl[linkIndex].channelHDLIndex[HID_INTERRUPT_CHANNEL], msgPtr);
    }    
}

PUBLIC void MMI_HID_ProcessKeyEvent(U8 linkIndex, U8 index)
{
	if(MMI_HID_KeyEvtHandler[index].fKeyEvt)
	{
		MMI_HID_KeyEvtHandler[index].fKeyEvt(linkIndex);
	}
}

PUBLIC void MMI_HID_SetProfileAvailable(BOOL enabled)
{
    LightDbgPrint("SetProfileAvailable %x %x", (U8)HID_IsEnable(), (U8)enabled);
    if (HID_IsEnable() == enabled)
    {        
        return;
    }
        
    if (enabled)
    {        
        HID_SetEnable(TRUE);
        // save data
        gMMI_driver_variation_nvram.misc_para.init.isMiscEnabled |= IS_HID_ENABLED;
    }
    else
    {        
        HID_SetEnable(FALSE);
        // save data
        gMMI_driver_variation_nvram.misc_para.init.isMiscEnabled &= (~IS_HID_ENABLED);
    }
    MMI_SECTOR_SetUpdateFlag(TRUE);
}

#endif
