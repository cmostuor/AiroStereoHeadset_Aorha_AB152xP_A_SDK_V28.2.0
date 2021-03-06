#ifndef _MMI_EVENT_OPCODE_H_
	#define _MMI_EVENT_OPCODE_H_
	
#include "bt_config_profile.h"

// ============================
// ======= System Events =======
// ============================

//HCI  - EVT Opcode Range: 0x00 ~ 0x3D
//SAP - Opcode Range: 0xA0 ~ 0xAF
//HFP - Opcode Range: 0xB0 ~ 0xDF
//HFP - Indicator Range: 0xE0 ~ 0xEF
//HFP - Indicator's DATA Range: 0xE0 ~ 0xEF
//HFP - CIEV ind Range: 0xF1 ~ 0xF7
//MMI - Internal Message Range: -0xFA ~ 0xFE 
#define MMI_INTERNAL_OFFSET		0xF9

// ============================
// ======= Media Events =======
// ============================

//KEY-EVT Opcode Range: 0x00 ~ 0x6F

//BAT-EVT Opcode Range: 0x70 ~ 0x77
#define MMI_BAT_EVT_OFFSET		0x7F
//GAP Opcode Range: 0x80 ~ 0xAC
#define MMI_STATUS_EVT_OFFSET	0x91

enum
{	
	//MMI internal use cmd 
	MMI_KEY_EVENT = 0X01 + MMI_INTERNAL_OFFSET,
	MMI_DETACH_CMD_TO_MMI,
	MMI_CHECK_POWERON_TIMER,
	MMI_CHARGING_TO,
	MMI_PWROFF_CMD,
	MMI_RESET_PAIRED_DEVICE_CMD,
	//--------------------------------------------------------
};

enum
{
    MMI_TRSPX_PASSKEY_START,
    MMI_TRSPX_PASSKEY_DIGIT_ENTERED,
    MMI_TRSPX_PASSKEY_DIGIT_ERASED,
    MMI_TRSPX_PASSKEY_CLEARED,
    MMI_TRSPX_PASSKEY_ENTRY_COMPLETED,
};

enum
{
    MMI_TRSPX_DISPLAY_ENTERED_INFO_YES,
    MMI_TRSPX_DISPLAY_ENTERED_INFO_NO,
};

enum
{    	
    // from UART
    MMI_TRSPX_TX_DATA_FROM_LOCAL_REQ = 0x02,     // from UART
    MMI_TRSPX_PASSKEY_ENTRY_RSP = 0x40,
    MMI_TRSPX_DISPLAY_YES_OR_NO_RSP,

    // to UART
//  MMI_TRSPX_SERVICE_CONNECTED = 0x01,
//	MMI_TRSPX_SERVICE_DISCONNECTED = 0x02,
    MMI_TRSPX_RX_DATA_FROM_REMOTE = 0x01, // from air to UART
    MMI_TRSPX_PASSKEY_REQ = 0x60,
    MMI_TRSPX_PAIRING_CMP,
    MMI_TRSPX_DISPLAY_YES_OR_NO_REQ,
    //MMI_TRSPX_TX_DATA_FROM_LOCAL_RESP,    // to UART
};

#ifdef HID_Profile
enum
{
    MMI_HID_OCF_UART_CMD = 0x02,    // from UART
    MMI_HID_OCF_PIN_CODE_CMD = 0x03,

    MMI_HID_OCF_UART_EVT = 0x12,    // to UART
};
#endif


enum
{
	// 0x0X
	KEY_INVALID, //0x00
	KEY_RECONNECT_USER_INIT,	
	KEY_DISCOVERABLE,  
	KEY_NONDISCOVERABLE,
	KEY_CONNECTED_TO_DISCOVERABLE,
	KEY_CONNECTED_TO_CONNECTABLE,   
	KEY_NFC_DISCOVREABLE,  
	KEY_CONFIRMATION_ACCEPT,
	KEY_CONFIRMATION_REJECT,
	KEY_DEBUG_KEY_TOGGLE,
	KEY_VOICEUP,	  				   
	KEY_VOICEDN,
	KEY_CHECK_BATTERY_STATUS,  
	KEY_BUZZER_MUTE_TOGGLE,					  
	KEY_TOGGLE_VOLUME,   	  
	KEY_VOLUME_ORIENTATION_NORMAL, 

	// 0x1X
	KEY_VOLUME_ORIENTATION_INVERT,   
	KEY_TOGGLE_LED,
	KEY_ENABLE_LED,
	KEY_DISABLE_LED,
	KEY_CANCEL_LED_INDICATION,
	KEY_MEDIA_TRIGGER_1,	
	KEY_MEDIA_TRIGGER_2,
	KEY_POWER_ON_THEN_ENTERDISCOVERABLE,
	KEY_POWER_ON,
	KEY_POWER_OFF,	
	KEY_RESET,
	KEY_RESET_PAIRED_DEVICES,
	KEY_MAX_DEVICE_ALLOWED_UP,
	KEY_MAX_DEVICE_ALLOWED_DOWN,  
	KEY_MAX_DEVICE_ALLOWED_TOGGLE,  
	KEY_RECONNECT_AFTER_POWER_ON,
	
	//0x2X
	KEY_VOICE_PROMPT_TOGGLE,
	KEY_VOICE_PROMPT_ENABLE,
	KEY_VOICE_PROMPT_DISABLE,
	KEY_VOICE_PROMPT_LANG_CHANGE,
	KEY_VOICE_PROMPT_LANG_SELECT,
	KEY_VOICE_PROMPT_LANG_CONFIRM,		
	KEY_TEST_VOICE_PROMPT_PLAY,
	KEY_TEST_VOICE_PROMPT_NEXT,
	KEY_BUTTONLOCKON,
	KEY_BUTTONLOCKOFF,
	KEY_BUTTONLOCKTOGGLE,
	KEY_VOICE_COMMAND_ENABLE,
	KEY_MICUP,		
	KEY_MICDN,		 
	KEY_MIC_MUTE_TOGGLE,	 
	KEY_MIC_MUTE_ON,

	//0x3X
	KEY_MIC_MUTE_OFF,
	KEY_AIR_ENTER_AIR_PAIRING,		
	KEY_AIR_EXIT_AIR_PAIRING,
	KEY_AUDIO_TRANSFER,	 
	KEY_SET_VOICE_RECOGNITION,
	KEY_RDIAL,				
	KEY_DIALMEM, 		
	KEY_DIALNUM, 
	KEY_CNLOUTGOING,	 	 
	KEY_REJCALL,
	KEY_REJCALL_SECOND_PHONE,	 				  
	KEY_ONHOLD_CALL,
	KEY_ACPCALL, 
	KEY_ENDCALL,  
	KEY_3WAYRELNUDUB,	 
	KEY_3WAYRELNACP,
	
	//0x4X
	KEY_3WAYRELNACP_X,
	KEY_3WAYHOLDNACP,
	KEY_3WAYHOLDNACP_X,
	KEY_3WAYADD,	 
	KEY_3WAYCALLTRANSFER,
	KEY_HSP_BUTTON_PRESSED,	 
	KEY_DISABLE_NREC,
	KEY_GETCALLNUM,
	KEY_QUERY_CALL_LIST,
	KEY_SEND_DTMF,					
	KEY_ATTACH_LAST_VOICE_TAG_RECORDED,
	KEY_SEND_CLIP,
	KEY_SET_VOICE_RECOGNITION_SECONDARY,
	KEY_RDIAL_SECONDARY,   
	KEY_SET_VOICE_RECOGNITION_CANCEL,
	KEY_SET_VOICE_RECOGNITION_SECONDARY_CANCEL,
	
	//0x5X
	KEY_SIRI_START_OR_CONTINUE,	
	KEY_SIRI_END,
	KEY_SIRI_START_OR_CONTINUE_SECONDARY,
	KEY_SIRI_END_SECONDARY,
	KEY_AVRCP_PLAY,
	KEY_AVRCP_STOP,
	KEY_AVRCP_PAUSE,
	KEY_AVRCP_RECORD,
	KEY_AVRCP_REWIND_PUSH,
	KEY_AVRCP_FAST_FORWARD_PUSH,	
	KEY_AVRCP_EJECT,   
	KEY_AVRCP_FORWARD,
	KEY_AVRCP_BACKWARD,
	KEY_AVRCP_REWIND_RELEASE,
	KEY_AVRCP_FAST_FORWARD_RELEASE,
	KEY_AVRCP_REPEAT_MODE_CHANGE,
	
	//0x6X
	KEY_AVRCP_SHUFFLE_MODE_CHANGE,
	KEY_AVRCP_ACTIVE_TOGGLE,	
	KEY_PEQ_MODE_CHANGE,
	KEY_FM_POWERON,	 
	KEY_FM_POWEROFF,  
	KEY_SEEKUP,
	KEY_SEEKDOWN,
	KEY_TUNEUP,
	KEY_TUNEDN,
	KEY_FM_MUTETOGGLE,
	KEY_ENTER_LINEIN_MODE,
	KEY_EXIT_LINEIN_MODE,
	KEY_LINEIN_MUTE_TOGGLE,
	KEY_ENTER_TESTMODE,
	KEY_SWITCH_TEST_MODE_CHANNEL,  
	KEY_SWITCH_TEST_MODE_POWER,

	//0x7x
	KEY_SWITCH_TEST_MODE_STATE,				  
	KEY_SWITCH_TEST_MODE_TX_PACKET_TYPE,
	KEY_SCO_SWITCH,
	KEY_AIR_ENTER_AIR_SECURE_PAIRING,
	KEY_MULTI_A2DP_PLAY_MODE_TOGGLE,
	KEY_CHECK_STATUS_OF_CONNECTION,
	KEY_WHAT_CAN_I_SAY,
	KEY_LEFT_CHANNEL,
	KEY_RIGHT_CHANNEL,
	KEY_STEREO_CHANNEL,
	KEY_VOICE_COMMAND_CANCEL,
	KEY_VOICE_MAKE_A_CALL,
	KEY_CHECK_STATUS,
	KEY_CHANGE_SOUND_EFFECT,
	KEY_CONTROL_DBB_ON_OFF,
	KEY_TOTAL_NO,  //0x7F=127


	
	UART_CMD_START = 0xA0,
	UART_CMD_RECONNECT_TO_INDEX = UART_CMD_START,
	UART_CMD_READ_BD_ADDR,
	UART_CMD_WRITE_DEVICE_NAME,
	UART_CMD_QUERY_LINK_HISTORY,
	UART_CMD_CONNECTABLE,
	UART_CMD_NONE_CONNECTABLE,
	UART_CMD_DISCONNECT_SPECIFIC_LINK,
	UART_CMD_CHECK_CHARGER_STATUS,
	UART_CMD_STOP_VOICEPROMPT,
	UART_CMD_PLAY_VOICE_PROMPT,
	UART_CMD_QUERY_SERVICE_INDEX,
	UART_CMD_VOLUME_SET,
	UART_CMD_PAIRING_CONFIRM,
	UART_CMD_CHANGE_AUDIO_SEL,
	UART_CMD_SET_AVRCP_VOL,
	UART_CMD_HIGH_QUALITY_AUDIO_CODEC,
	
	//0xBX
	UART_CMD_QUERY_LINKKEY_BY_BDADDR,
	UART_CMD_I2C_READ,
	UART_CMD_I2C_WRITE,
	UART_CMD_GET_REMOTE_NAME,
	UART_CMD_GET_FW_VERSION,
	UART_CMD_DSP_FREQUENCT_SELECT,
	UART_CMD_SET_PROFILE_SUPPORT_STATUS,
	UART_CMD_FIND_MY_ACCESSORY,
	UART_CMD_INQUIRY,
	UART_CMD_CREATE_CONNECTION,
	
	/*  !!! please add new uart command above this warning !!! */
	UART_CMD_END,
};

#define UART_CMD_NUM	(UART_CMD_END - UART_CMD_START)

#define KEY_SECOND_TABLE_START_INDEX 0x0100
#define MEDIA_EVT_SECOND_TABLE_START_INDEX 0x1000

enum
{
	//0x0100
	KEY_SECOND_TABLE_START = KEY_SECOND_TABLE_START_INDEX,
	KEY_CONTROL_MIC_A2DP_MODE,
	KEY_SELFIE,
	KEY_ENABLE_DUT_MODE_COMMAND,
	KEY_MIC_L_ENABLE,
	KEY_MIC_R_ENABLE,
	KEY_MIC_TO_SPK_ENABLE,
	KEY_MIC_TO_SPK_DISABLE,
	KEY_ENABLE_EC_NR,
	KEY_DISABLE_EC_NR,
	KEY_2K_TONE_ENABLE,
	KEY_2K_TONE_DISABLE,
	KEY_SWITCH_STEREO_MONO,
	KEY_SWITCH_SELFIE,
	KEY_AUDIO_TRANSPARENCY,
	KEY_ROLE_CHANGE,
	KEY_SECOND_TABLE_END
};

#define KEY_SECOND_TABLE_NUM (KEY_SECOND_TABLE_END-KEY_SECOND_TABLE_START)

enum
{
	//0x0X
	NO_MEDIA = 0,
	MEDIA_EVT_KEY_RECONNECT_USER_INIT,	
	MEDIA_EVT_KEY_DISCOVERABLE,  
	MEDIA_EVT_KEY_NONDISCOVERABLE,
	MEDIA_EVT_KEY_CONNECTED_TO_DISCOVERABLE,
	MEDIA_EVT_KEY_CONNECTED_TO_CONNECTABLE,
	MEDIA_EVT_KEY_NFC_DISCOVREABLE,  
	MEDIA_EVT_KEY_CONFIRMATION_ACCEPT,
	MEDIA_EVT_KEY_CONFIRMATION_REJECT,
	MEDIA_EVT_KEY_DEBUG_KEY_TOGGLE,
	MEDIA_EVT_KEY_VOICEUP,				   
	MEDIA_EVT_KEY_VOICEDN,
	MEDIA_EVT_KEY_CHECK_BATTERY_STATUS,  
	MEDIA_EVT_KEY_BUZZER_MUTE_TOGGLE, 				  
	MEDIA_EVT_KEY_TOGGLE_VOLUME,		  
	MEDIA_EVT_KEY_VOLUME_ORIENTATION_NORMAL,
	
	//0x1X
	MEDIA_EVT_KEY_VOLUME_ORIENTATION_INVERT,
	MEDIA_EVT_KEY_TOGGLE_LED,
	MEDIA_EVT_KEY_ENABLE_LED,
	MEDIA_EVT_KEY_DISABLE_LED,
	MEDIA_EVT_KEY_CANCEL_LED_INDICATION,
	MEDIA_EVT_KEY_MEDIA_TRIGGER_1,
	MEDIA_EVT_KEY_MEDIA_TRIGGER_2,
	MEDIA_EVT_KEY_POWER_ON_THEN_ENTERDISCOVERABLE,
	MEDIA_EVT_KEY_POWER_ON,
	MEDIA_EVT_KEY_POWER_OFF,	
	MEDIA_EVT_KEY_RESET,
	MEDIA_EVT_KEY_RESET_PAIRED_DEVICES,
	MEDIA_EVT_KEY_MAX_DEVICE_ALLOWED_UP,
	MEDIA_EVT_KEY_MAX_DEVICE_ALLOWED_DOWN,  
	MEDIA_EVT_KEY_MAX_DEVICE_ALLOWED_TOGGLE,	
	MEDIA_EVT_KEY_RECONNECT_AFTER_POWER_ON,
	
	//0x2X
	MEDIA_EVT_KEY_VOICE_PROMPT_TOGGLE,
	MEDIA_EVT_KEY_VOICE_PROMPT_ENABLE,
	MEDIA_EVT_KEY_VOICE_PROMPT_DISABLE,
	MEDIA_EVT_KEY_VOICE_PROMPT_LANG_CHANGE,
	MEDIA_EVT_KEY_VOICE_PROMPT_LANG_SELECT,
	MEDIA_EVT_KEY_VOICE_PROMPT_LANG_CONFIRM,
	MEDIA_EVT_KEY_TEST_VOICE_PROMPT_PLAY,
	MEDIA_EVT_KEY_TEST_VOICE_PROMPT_NEXT,
	MEDIA_EVT_KEY_BUTTONLOCKON,
	MEDIA_EVT_KEY_BUTTONLOCKOFF,
	MEDIA_EVT_KEY_BUTTONLOCKTOGGLE,
	MEDIA_EVT_KEY_VOICE_COMMAND_ENABLE, 
	MEDIA_EVT_KEY_MICUP,
	MEDIA_EVT_KEY_MICDN,
	MEDIA_EVT_KEY_MIC_MUTE_TOGGLE,	 
	MEDIA_EVT_KEY_MIC_MUTE_ON,

	//0x3X
	MEDIA_EVT_KEY_MIC_MUTE_OFF,
	MEDIA_EVT_KEY_KEY_AIR_ENTER_AIR_PAIRING,		
	MEDIA_EVT_KEY_KEY_AIR_EXIT_AIR_PAIRING,
	MEDIA_EVT_KEY_AUDIO_TRANSFER, 
	MEDIA_EVT_KEY_SET_VOICE_RECOGNITION,
	MEDIA_EVT_KEY_RDIAL,			
	MEDIA_EVT_KEY_DIALMEM,
	MEDIA_EVT_KEY_DIALNUM, 
	MEDIA_EVT_KEY_CNLOUTGOING, 	 
	MEDIA_EVT_KEY_REJCALL,
	MEDIA_EVT_KEY_REJCALL_SECOND_PHONE,					  
	MEDIA_EVT_KEY_ONHOLD_CALL,
	MEDIA_EVT_KEY_ACPCALL, 
	MEDIA_EVT_KEY_ENDCALL,  
	MEDIA_EVT_KEY_3WAYRELNUDUB,	 
	MEDIA_EVT_KEY_3WAYRELNACP,
	
	//0x4X
	MEDIA_EVT_KEY_3WAYRELNACP_X,
	MEDIA_EVT_KEY_3WAYHOLDNACP,
	MEDIA_EVT_KEY_3WAYHOLDNACP_X,
	MEDIA_EVT_KEY_3WAYADD,	 
	MEDIA_EVT_KEY_3WAYCALLTRANSFER,
	MEDIA_EVT_KEY_HSP_BUTTON_PRESSED,  
	MEDIA_EVT_KEY_DISABLE_NREC,
	MEDIA_EVT_KEY_GETCALLNUM,
	MEDIA_EVT_KEY_QUERY_CALL_LIST,
	MEDIA_EVT_KEY_SEND_DTMF,					
	MEDIA_EVT_KEY_ATTACH_LAST_VOICE_TAG_RECORDED,
	MEDIA_EVT_KEY_SEND_CLIP,
	MEDIA_EVT_KEY_SET_VOICE_RECOGNITION_SECONDARY,
	MEDIA_EVT_KEY_RDIAL_SECONDARY,   
	MEDIA_EVT_KEY_SET_VOICE_RECOGNITION_CANCEL,
	MEDIA_EVT_KEY_SET_VOICE_RECOGNITION_SECONDARY_CANCEL,
	
	//0x5X
	MEDIA_EVT_KEY_SIRI_START_OR_CONTINUE,
	MEDIA_EVT_KEY_SIRI_END,
	MEDIA_EVT_KEY_SIRI_START_OR_CONTINUE_SECONDARY,
	MEDIA_EVT_KEY_SIRI_END_SECONDARY,
	MEDIA_EVT_KEY_A2DP_PLAY,
	MEDIA_EVT_KEY_A2DP_STOP,
	MEDIA_EVT_KEY_A2DP_PAUSE,
	MEDIA_EVT_KEY_A2DP_RECORD,
	MEDIA_EVT_KEY_A2DP_REWIND_PUSH,
	MEDIA_EVT_KEY_A2DP_FAST_FORWARD_PUSH, 
	MEDIA_EVT_KEY_A2DP_EJECT,   
	MEDIA_EVT_KEY_A2DP_FORWARD,
	MEDIA_EVT_KEY_A2DP_BACKWARD,
	MEDIA_EVT_KEY_A2DP_REWIND_RELEASE,
	MEDIA_EVT_KEY_A2DP_FAST_FORWARD_RELEASE,
	MEDIA_EVT_KEY_AVRCP_REPEAT_MODE_CHANGE,
	
	//0x6X
	MEDIA_EVT_KEY_AVRCP_SHUFFLE_MODE_CHANGE,
	MEDIA_EVT_KEY_AVRCP_ACTIVE_TOGGLE,
	MEDIA_EVT_KEY_PEQ_MODE_CHANGE,
	MEDIA_EVT_KEY_FM_POWERON,  
	MEDIA_EVT_KEY_FM_POWEROFF,  
	MEDIA_EVT_KEY_SEEKUP,
	MEDIA_EVT_KEY_SEEKDOWN,
	MEDIA_EVT_KEY_TUNEUP,
	MEDIA_EVT_KEY_TUNEDN,
	MEDIA_EVT_KEY_FM_MUTETOGGLE,
	MEDIA_EVT_KEY_ENTER_LINEIN_MODE,
	MEDIA_EVT_KEY_EXIT_LINEIN_MODE,
	MEDIA_EVT_KEY_LINEIN_MUTE_TOGGLE,
	MEDIA_EVT_KEY_ENTER_TESTMODE, 
	MEDIA_EVT_KEY_SWITCH_TEST_MODE_CHANNEL, 	
	MEDIA_EVT_KEY_SWITCH_TEST_MODE_POWER,

	//0x7x
	MEDIA_EVT_KEY_SWITCH_TEST_MODE_STATE, 			  
	MEDIA_EVT_KEY_SWITCH_TEST_MODE_TX_PACKET_TYPE,		
	MEDIA_EVT_KEY_SCO_SWITCH,
	MEDIA_EVT_KEY_KEY_KEY_AIR_ENTER_AIR_SECURE_PAIRING,
	MEDIA_EVT_KEY_MULTI_A2DP_PLAY_MODE_TOGGLE,
	MEDIA_EVT_KEY_CHECK_STATUS_OF_CONNECTION,
	MEDIA_EVT_KEY_WHAT_CAN_I_SAY,
	MEDIA_EVT_KEY_LEFT_CHANNEL,
	MEDIA_EVT_KEY_RIGHT_CHANNEL,
	MEDIA_EVT_KEY_STEREO_CHANNEL,
	MEDIA_EVT_KEY_VOICE_COMMAND_CANCEL,
	MEDIA_EVT_KEY_VOICE_MAKE_A_CALL,
	MEDIA_EVT_KEY_CHECK_STATUS,
	MEDIA_EVT_KEY_CHANGE_SOUND_EFFECT,
	MEDIA_EVT_KEY_CONTROL_DBB_ON_OFF,
	//KEY_TOTAL_NO,  //0x7F



	//Battery
	MEDIA_EVT_BAT_LOW = MMI_BAT_EVT_OFFSET, // low battery, 0x7F
	MEDIA_EVT_BAT_FULL, //battery voltage is over full_voltage, i.e., fake charge-complete signal
	MEDIA_EVT_BAT_CHGCPL, //charge complete
	MEDIA_EVT_BAT_RECHG, //recharge 0x80
	MEDIA_EVT_BAT_CHGROUT, //charger pull out
	MEDIA_EVT_BAT_CHGRIN, //charger plug in
	MEDIA_EVT_BAT_CHGTO,	//charge TO
	MEDIA_EVT_BAT_HW_CHGTO,	//hw detects charging TO
	MEDIA_EVT_BATTERY_INTERVAL_0,
	MEDIA_EVT_BATTERY_INTERVAL_1,
	MEDIA_EVT_BATTERY_INTERVAL_2,
	MEDIA_EVT_BATTERY_INTERVAL_3,
	MEDIA_EVT_BAT_LOW_LED,
	MEDIA_EVT_BAT_LOW_RING,
	MEDIA_EVT_BAT_SECURE_TEMP,  
	MEDIA_EVT_BAT_RISKY_TEMP,
	MEDIA_EVT_BAT_OK,			
	MEDIA_EVT_BAT_DISCOUNT_TEMP, //0x90

	//Indication Events
	MEDIA_EVT_SLC_CONNECTED = MMI_STATUS_EVT_OFFSET,	//0x91
	MEDIA_EVT_2_SLC_CONNECTED,
	MEDIA_EVT_3_SLC_CONNECTED,
	MEDIA_EVT_4_SLC_CONNECTED,
	MEDIA_EVT_SLC_DISCONNECTED,
	MEDIA_EVT_PAIRING_SUCCESSFUL,
	MEDIA_EVT_PAIRING_FAIL,
	MEDIA_EVT_LINK_LOSS,
	MEDIA_EVT_END_OF_CALL,
	MEDIA_EVT_POWER_ON,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT1,
	MEDIA_EVT_POWER_OFF,
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT1,
	MEDIA_EVT_POWER_OFF_IN_SHUTDOWN_LOW_BAT,
	MEDIA_EVT_RINGTONE,

	//0xA0
	MEDIA_EVT_RECONNECT_FAILED,  //0xA0
	MEDIA_EVT_MUTE_REMINDER,
	MEDIA_EVT_NETWORK_NOT_PRESENT,
	MEDIA_EVT_NETWORK_PRESENT,
	MEDIA_EVT_OFF_STATE,
	MEDIA_EVT_PINCODE_REQUEST,
	MEDIA_EVT_CONFIRMATION_REQUEST,
	MEDIA_EVT_CALL_CONNECTED,
	MEDIA_EVT_AUDIO_LINK_OPEN,		
	MEDIA_EVT_AUDIO_LINK_CLOSE,
	MEDIA_EVT_CONNECTABLE_TIMEOUT,
	MEDIA_EVT_HFP_ERROR_RECEIVED,
	MEDIA_EVT_RESET_COMPLETE,
	MEDIA_EVT_ENTER_TESTMODE_STATE,
	MEDIA_EVT_REFRESH_ENCRYPTION,
	MEDIA_EVT_FG_LED_DISPLAY_OVER,
	
	//0xB0
	MEDIA_EVT_RESERVED,	
	MEDIA_EVT_ENTER_CTX_TEST_MODE,
	MEDIA_EVT_ENTER_DISCOVERABLE,
	MEDIA_EVT_EXIT_DISCOVERABLE,
	MEDIA_EVT_ENTER_INCOMING,
	MEDIA_EVT_EXIT_INCOMING,
	MEDIA_EVT_PHONE_IS_TOO_FAR_1,
	MEDIA_EVT_PHONE_IS_TOO_FAR_2,  
	MEDIA_EVT_RINGTONE_2,  			
	MEDIA_EVT_VOLUME_REACH_MAX,
	MEDIA_EVT_VOLUME_REACH_MIN,
	MEDIA_EVT_REDIAL_SUCCESSFUL_EVT,
	MEDIA_EVT_A2DP_VOLUME_REACH_MAX,
	MEDIA_EVT_A2DP_VOLUME_REACH_MIN,
	MEDIA_EVT_FM_VOLUME_REACH_MAX,
	MEDIA_EVT_FM_VOLUME_REACH_MIN,
	
	//0xC0
	MEDIA_EVT_FM_NOT_BUSY,
	MEDIA_EVT_LINEIN_VOLUME_REACH_MAX,
	MEDIA_EVT_LINEIN_VOLUME_REACH_MIN,
	MEDIA_EVT_MISSED_CALL_REMINDER1,  
	MEDIA_EVT_MISSED_CALL_REMINDER2,
	MEDIA_EVT_VOICE_PROMPT_LANG_CHANGE,
	MEDIA_EVT_VOICE_PROMPT_LANG_SELECT,
	MEDIA_EVT_VOICE_PROMPT_LANG_CONFIRM,
	MEDIA_EVT_ENTER_LINE_IN_MODE,
	MEDIA_EVT_EXIT_LINE_IN_MODE,
	MEDIA_EVT_A2DP_ENABLE,
	MEDIA_EVT_A2DP_DISABLE,
	MEDIA_EVT_VOICE_DIAL_ENABLE,
	MEDIA_EVT_REDIAL_ENABLE,
	MEDIA_EVT_MUTE_ON,
	MEDIA_EVT_MUTE_OFF,
	
	//0xD0
	MEDIA_EVT_FM_MUTE_ON,
	MEDIA_EVT_FM_MUTE_OFF,
	MEDIA_EVT_FM_ENABLE, 
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT2,
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT3,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT2,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT3,
	MEDIA_EVT_RINGTONE_IN_CALL,
	MEDIA_EVT_RINGTONE2_IN_CALL,
	MEDIA_EVT_TWS_ENTER_PAIRING,
	MEDIA_EVT_TWS_EXIT_PAIRING,
	MEDIA_EVT_TWS_DURING_PAIRING,
	MEDIA_EVT_TWS_LEFT_CHANNEL,
	MEDIA_EVT_TWS_RIGHT_CHANNEL,
	MEDIA_EVT_TWS_RELAY_ONLY,
	MEDIA_EVT_TWS_FOLLOWER,
	
	//0xE0
	MEDIA_EVT_SIRI_STARTING,
	MEDIA_EVT_SIRI_CONTINUE,
	MEDIA_EVT_SIRI_END,
	MEDIA_EVT_VOICE_COMMAND_FAIL,
	MEDIA_EVT_VOICE_COMMAND_MULTILAYER_TRIGGER,
	MEDIA_EVT_RESERVED1,
	MEDIA_EVT_MIC_UPDN,

	//For APP
	MEDIA_EVT_KEY_FIND_MY_ACCESSORY,
	MEDIA_EVT_TWS_DISCONNECTED,

	//reserve for UART cmd to play voice prompt
	MEDIA_EVT_UART_CMD_RESERVE = 0xFF,
};


enum
{
	//0x0100
	MMI_EVT_KEY_SECOND_TABLE_START = KEY_SECOND_TABLE_START_INDEX,
	MMI_EVT_KEY_CONTROL_MIC_A2DP_MODE,
	MMI_EVT_KEY_SELFIE,
	MMI_EVT_KEY_ENABLE_DUT_MODE_COMMAND,
	MMI_EVT_KEY_MIC_L_ENABLE,
	MMI_EVT_KEY_MIC_R_ENABLE,
	MMI_EVT_KEY_MIC_TO_SPK_ENABLE,
	MMI_EVT_KEY_MIC_TO_SPK_DISABLE,
	MMI_EVT_KEY_ENABLE_EC_NR,
	MMI_EVT_KEY_DISABLE_EC_NR,
	MMI_EVT_KEY_2K_TONE_ENABLE,
	MMI_EVT_KEY_2K_TONE_DISABLE,
	MMI_EVT_KEY_SWITCH_STEREO_MONO,
	MMI_EVT_KEY_SWITCH_SELFIE,
	MMI_EVT_KEY_AUDIO_TRANSPARENCY,
	MMI_EVT_KEY_ROLE_CHANGE,
	MMI_EVT_KEY_SECOND_TABLE_END
};

enum
{
	//0x1000
	MEDIA_EVT_SECOND_TABLE_START = MEDIA_EVT_SECOND_TABLE_START_INDEX,
	MEDIA_EVT_KEY_CONTROL_MIC_A2DP_MODE,
	MEDIA_EVT_KEY_SELFIE,
	MEDIA_EVT_KEY_ENABLE_DUT_MODE_COMMAND,
	MEDIA_EVT_KEY_MIC_L_ENABLE,
	MEDIA_EVT_KEY_MIC_R_ENABLE,
	MEDIA_EVT_KEY_MIC_TO_SPK_ENABLE,
	MEDIA_EVT_KEY_MIC_TO_SPK_DISABLE,
	MEDIA_EVT_KEY_ENABLE_EC_NR,
	MEDIA_EVT_KEY_DISABLE_EC_NR,
	MEDIA_EVT_KEY_2K_TONE_ENABLE,
	MEDIA_EVT_KEY_2K_TONE_DISABLE,
	MEDIA_EVT_KEY_SWITCH_STEREO_MONO,
	MEDIA_EVT_KEY_SWITCH_SELFIE,
	MEDIA_EVT_KEY_AUDIO_TRANSPARENCY,
	MEDIA_EVT_KEY_ROLE_CHANGE,
	
	MEDIA_EVT_INCOMING_CALL_ENDED = (MEDIA_EVT_SECOND_TABLE_START_INDEX | 0x80),//0x1080
	MEDIA_EVT_AG_CNLOUTGOING,
	MEDIA_EVT_AG_REJCALL,
	
	MEDIA_EVT_SECOND_TABLE_END
};

enum
{
	SYSTEM_KEY_EVENT,
	AIR_KEY_EVENT,
	HFP_KEY_EVENT,
	AVRCP_KEY_EVENT,
	FM_KEY_EVENT,
	LINE_IN_KEY_EVENT,
	TESTMODE_KEY_EVENT,
	HID_KEY_EVENT,
	KEY_EVENT_GROUP_NO,
	NOT_KEY_EVENT,
};

typedef struct
{
	U8 group;
	U8 index;
}KeyEvtMapType;

typedef struct
{
	U8 group;
	U8 index;
}KeyEvtMapType2;

enum
{
	SYSTEM_KEY_EVENT_KEY_RECONNECT_USER_INIT, //KEY_RECONNECT_USER_INIT	//0x01	
	SYSTEM_KEY_EVENT_KEY_DISCOVERABLE,//KEY_DISCOVERABLE,  
	SYSTEM_KEY_EVENT_KEY_NONDISCOVERABLE, //KEY_NONDISCOVERABLE,
	SYSTEM_KEY_EVENT_KEY_CONNECTED_TO_DISCOVERABLE, //KEY_CONNECTED_TO_DISCOVERABLE,
	SYSTEM_KEY_EVENT_KEY_CONNECTED_TO_CONNECTABLE, //KEY_CONNECTED_TO_CONNECTABLE,   //0x05
	SYSTEM_KEY_EVENT_KEY_NFC_DISCOVREABLE, //KEY_NFC_DISCOVREABLE,  
	SYSTEM_KEY_EVENT_KEY_CONFIRMATION_ACCEPT, //KEY_CONFIRMATION_ACCEPT,
	SYSTEM_KEY_EVENT_KEY_CONFIRMATION_REJECT, //KEY_CONFIRMATION_REJECT,
	SYSTEM_KEY_EVENT_KEY_DEBUG_KEY_TOGGLE, //KEY_DEBUG_KEY_TOGGLE,
	SYSTEM_KEY_EVENT_KEY_VOICEUP, //KEY_VOICEUP,	  //0x0a				   
	SYSTEM_KEY_EVENT_KEY_VOICEDN, //KEY_VOICEDN,
	SYSTEM_KEY_EVENT_KEY_CHECK_BATTERY_STATUS, //KEY_CHECK_BATTERY_STATUS,  
	SYSTEM_KEY_EVENT_KEY_BUZZER_MUTE_TOGGLE, //KEY_BUZZER_MUTE_TOGGLE,					  
	SYSTEM_KEY_EVENT_KEY_TOGGLE_VOLUME, //KEY_TOGGLE_VOLUME,   	  
	SYSTEM_KEY_EVENT_KEY_VOLUME_ORIENTATION_NORMAL, //KEY_VOLUME_ORIENTATION_NORMAL,    //0x0F
	SYSTEM_KEY_EVENT_KEY_VOLUME_ORIENTATION_INVERT, //KEY_VOLUME_ORIENTATION_INVERT,   //0x10
	SYSTEM_KEY_EVENT_KEY_TOGGLE_LED, //KEY_TOGGLE_LED,
	SYSTEM_KEY_EVENT_KEY_ENABLE_LED, //KEY_ENABLE_LED,
	SYSTEM_KEY_EVENT_KEY_DISABLE_LED, //KEY_DISABLE_LED,
	SYSTEM_KEY_EVENT_KEY_CANCEL_LED_INDICATION, //KEY_CANCEL_LED_INDICATION,
	SYSTEM_KEY_EVENT_KEY_MEDIA_TRIGGER_1, //KEY_MEDIA_TRIGGER_1,	//0x15
	SYSTEM_KEY_EVENT_KEY_MEDIA_TRIGGER_2, //KEY_MEDIA_TRIGGER_2,
	SYSTEM_KEY_EVENT_KEY_POWER_ON_THEN_ENTERDISCOVERABLE,//KEY_POWER_ON_THEN_ENTERDISCOVERABLE,
	SYSTEM_KEY_EVENT_KEY_POWER_ON,//KEY_POWER_ON,
	SYSTEM_KEY_EVENT_KEY_POWER_OFF,//KEY_POWER_OFF,	
	SYSTEM_KEY_EVENT_KEY_RESET,//KEY_RESET,		//0x1a
	SYSTEM_KEY_EVENT_KEY_RESET_PAIRED_DEVICES,//KEY_RESET_PAIRED_DEVICES,
	SYSTEM_KEY_EVENT_KEY_MAX_DEVICE_ALLOWED_UP,//KEY_MAX_DEVICE_ALLOWED_UP,
	SYSTEM_KEY_EVENT_KEY_MAX_DEVICE_ALLOWED_DOWN,//KEY_MAX_DEVICE_ALLOWED_DOWN,  
	SYSTEM_KEY_EVENT_KEY_MAX_DEVICE_ALLOWED_TOGGLE,//KEY_MAX_DEVICE_ALLOWED_TOGGLE,  
	SYSTEM_KEY_EVENT_KEY_RECONNECT_AFTER_POWER_ON,//KEY_RECONNECT_AFTER_POWER_ON,		//0x1F
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_TOGGLE,//KEY_VOICE_PROMPT_TOGGLE,		//0x20
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_ENABLE,//KEY_VOICE_PROMPT_ENABLE,
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_DISABLE,//KEY_VOICE_PROMPT_DISABLE,
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_LANG_CHANGE,//KEY_VOICE_PROMPT_LANG_CHANGE,
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_LANG_SELECT,//KEY_VOICE_PROMPT_LANG_SELECT,
	SYSTEM_KEY_EVENT_KEY_VOICE_PROMPT_LANG_CONFIRM,//KEY_VOICE_PROMPT_LANG_CONFIRM,		//0x25
	SYSTEM_KEY_EVENT_KEY_TEST_VOICE_PROMPT_PLAY,//KEY_TEST_VOICE_PROMPT_PLAY,
	SYSTEM_KEY_EVENT_KEY_TEST_VOICE_PROMPT_NEXT,//KEY_TEST_VOICE_PROMPT_NEXT,
	SYSTEM_KEY_EVENT_KEY_BUTTONLOCKON,//KEY_BUTTONLOCKON,
	SYSTEM_KEY_EVENT_KEY_BUTTONLOCKOFF,//KEY_BUTTONLOCKOFF,
	SYSTEM_KEY_EVENT_KEY_BUTTONLOCKTOGGLE,//KEY_BUTTONLOCKTOGGLE,			//0x2a
	SYSTEM_KEY_EVENT_KEY_VOICE_COMMAND_ENABLE,//KEY_VOICE_COMMAND_ENABLE,
	SYSTEM_KEY_EVENT_KEY_MICUP,//KEY_MICUP,		
	SYSTEM_KEY_EVENT_KEY_MICDN,//KEY_MICDN,		 
	SYSTEM_KEY_EVENT_KEY_MIC_MUTE_TOGGLE,//KEY_MIC_MUTE_TOGGLE,	 
	SYSTEM_KEY_EVENT_KEY_MIC_MUTE_ON,//KEY_MIC_MUTE_ON,	 
	SYSTEM_KEY_EVENT_KEY_MIC_MUTE_OFF,//KEY_MIC_MUTE_OFF,					//0x30
	SYSTEM_KEY_EVENT_KEY_SCO_SWITCH, //KEY_SCO_SWITCH,
	SYSTEM_KEY_EVENT_KEY_PEQ_MODE_CHANGE, //KEY_PEQ_MODE_CHANGE
	SYSTEM_KEY_EVENT_KEY_MULTI_A2DP_PLAY_MODE_TOGGLE,//KEY_MULTI_A2DP_PLAY_MODE_TOGGLE
	SYSTEM_KEY_EVENT_KEY_CHECK_STATUS_OF_CONNECTION, //KEY_CHECK_STATUS_OF_CONNECTION
	SYSTEM_KEY_EVENT_KEY_WHAT_CAN_I_SAY,//KEY_WHAT_CAN_I_SAY
	SYSTEM_KEY_EVENT_KEY_VOICE_COMMAND_CANCEL,//KEY_VOICE_COMMAND_CANCEL
	SYSTEM_KEY_EVENT_KEY_VOICE_MAKE_A_CALL,//KEY_VOICE_MAKE_A_CALL
	SYSTEM_KEY_EVENT_KEY_CHECK_STATUS, //KEY_CHECK_STATUS												
	SYSTEM_KEY_EVENT_KEY_CHANGE_SOUND_EFFECT, //KEY_CHANGE_SOUND_EFFECT
	SYSTEM_KEY_EVENT_KEY_CONTROL_DBB_ON_OFF, //KEY_CONTROL_DBB_ON_OFF		//0x3A
	SYSTEM_KEY_CONTROL_MIC_A2DP_MODE, //KEY_CONTROL_MIC_A2DP_MODE
	SYSTEM_KEY_ENABLE_DUT_MODE_COMMAND, //KEY_ENABLE_DUT_MODE_COMMAND
	SYSTEM_KEY_EVENT_KEY_MIC_L_ENABLE, //KEY_MIC_L_ENABLE
	SYSTEM_KEY_EVENT_KEY_MIC_R_ENABLE, //kEY_MIC_R_ENABLE
	SYSTEM_KEY_EVENT_KEY_MIC_TO_SPK_ENABLE, //KEY_MIC_TO_SPK_ENABLE
	SYSTEM_KEY_EVENT_KEY_MIC_TO_SPK_DISABLE, //KEY_MIC_TO_SPK_DISABLE
	SYSTEM_KEY_EVENT_KEY_ENABLE_EC_NR, //KEY_ENABLE_EC_NR
	SYSTEM_KEY_EVENT_KEY_DISABLE_EC_NR, //KEY_DISABLE_EC_NR
	SYSTEM_KEY_EVENT_KEY_2K_TONE_ENABLE, //KEY_2K_TONE_ENABLE
	SYSTEM_KEY_EVENT_KEY_2K_TONE_DISABLE, //KEY_2K_TONE_DISABLE
	SYSTEM_KEY_EVENT_KEY_SWITCH_STEREO_MONO, //KEY_SWITCH_STEREO_MONO
	SYSTEM_KEY_EVENT_KEY_AUDIO_TRANSPARENCY, //KEY_AUDIO_TRANSPARENCY
	SYSTEM_KEY_EVENT_KEY_ROLE_CHANGE, //KEY_ROLE_CHANGE
	SYSTEM_KEY_EVENT_NO,
};

enum
{
	AIR_KEY_EVENT_KEY_AIR_ENTER_AIR_PAIRING,		
	AIR_KEY_EVENT_KEY_AIR_EXIT_AIR_PAIRING,		
	AIR_KEY_EVENT_KEY_AIR_ENTER_AIR_SECURE_PAIRING,
	AIR_KEY_EVENT_NO,
};

enum
{
	HFP_KEY_EVENT_KEY_AUDIO_TRANSFER,	 
	HFP_KEY_EVENT_KEY_SET_VOICE_RECOGNITION,
	HFP_KEY_EVENT_KEY_RDIAL,			//0x35 				
	HFP_KEY_EVENT_KEY_DIALMEM, 		
	HFP_KEY_EVENT_KEY_DIALNUM, 
	HFP_KEY_EVENT_KEY_CNLOUTGOING,	 	 
	HFP_KEY_EVENT_KEY_REJCALL,
	HFP_KEY_EVENT_KEY_REJCALL_SECOND_PHONE,	 				  
	HFP_KEY_EVENT_KEY_ONHOLD_CALL,		//0x3B
	HFP_KEY_EVENT_KEY_ACPCALL, 
	HFP_KEY_EVENT_KEY_ENDCALL,  
	HFP_KEY_EVENT_KEY_3WAYRELNUDUB,	 
	HFP_KEY_EVENT_KEY_3WAYRELNACP,
	HFP_KEY_EVENT_KEY_3WAYRELNACP_X,	//0x40
	HFP_KEY_EVENT_KEY_3WAYHOLDNACP,
	HFP_KEY_EVENT_KEY_3WAYHOLDNACP_X,
	HFP_KEY_EVENT_KEY_3WAYADD,	 
	HFP_KEY_EVENT_KEY_3WAYCALLTRANSFER,
	HFP_KEY_EVENT_KEY_HSP_BUTTON_PRESSED,	 
	HFP_KEY_EVENT_KEY_DISABLE_NREC,		//0x46
	HFP_KEY_EVENT_KEY_GETCALLNUM,
	HFP_KEY_EVENT_KEY_QUERY_CALL_LIST,
	HFP_KEY_EVENT_KEY_SEND_DTMF,					
	HFP_KEY_EVENT_KEY_ATTACH_LAST_VOICE_TAG_RECORDED,
	HFP_KEY_EVENT_KEY_SEND_CLIP,			//0x4B
	HFP_KEY_EVENT_KEY_SET_VOICE_RECOGNITION_SECONDARY,
	HFP_KEY_EVENT_KEY_RDIAL_SECONDARY,   
	HFP_KEY_EVENT_KEY_SET_VOICE_RECOGNITION_CANCEL,
	HFP_KEY_EVENT_KEY_SET_VOICE_RECOGNITION_SECONDARY_CANCEL,
	HFP_KEY_EVENT_KEY_SIRI_START_OR_CONTINUE,		//0x50
	HFP_KEY_EVENT_KEY_SIRI_END,			//0x51
	HFP_KEY_EVENT_KEY_SIRI_START_OR_CONTINUE_SECONDARY,
	HFP_KEY_EVENT_KEY_SIRI_END_SECONDARY,
	HFP_KEY_EVENT_NO,
};

enum
{
	AVRCP_KEY_EVENT_KEY_AVRCP_PLAY,
	AVRCP_KEY_EVENT_KEY_AVRCP_STOP,
	AVRCP_KEY_EVENT_KEY_AVRCP_PAUSE,		//0x56
	AVRCP_KEY_EVENT_KEY_AVRCP_RECORD,
	AVRCP_KEY_EVENT_KEY_AVRCP_REWIND_PUSH,
	AVRCP_KEY_EVENT_KEY_AVRCP_FAST_FORWARD_PUSH,	
	AVRCP_KEY_EVENT_KEY_AVRCP_EJECT,   
	AVRCP_KEY_EVENT_KEY_AVRCP_FORWARD,	//0x5B
	AVRCP_KEY_EVENT_KEY_AVRCP_BACKWARD,
	AVRCP_KEY_EVENT_KEY_AVRCP_REWIND_RELEASE,
	AVRCP_KEY_EVENT_KEY_AVRCP_FAST_FORWARD_RELEASE,
	AVRCP_KEY_EVENT_KEY_AVRCP_REPEAT_MODE_CHANGE,
	AVRCP_KEY_EVENT_KEY_AVRCP_SHUFFLE_MODE_CHANGE,	//0x60
	AVRCP_KEY_EVENT_KEY_AVRCP_ACTIVE_TOGGLE,
	AVRCP_KEY_EVENT_KEY_KEY_LEFT_CHANNEL,
	AVRCP_KEY_EVENT_KEY_KEY_RIGHT_CHANNEL,
	AVRCP_KEY_EVENT_KEY_KEY_STEREO_CHANNEL,
	AVRCP_KEY_EVENT_NO,
};

enum
{
	FM_KEY_EVENT_KEY_FM_POWERON,	 
	FM_KEY_EVENT_KEY_FM_POWEROFF,  
	FM_KEY_EVENT_KEY_SEEKUP,
	FM_KEY_EVENT_KEY_SEEKDOWN,  //0x66
	FM_KEY_EVENT_KEY_TUNEUP,
	FM_KEY_EVENT_KEY_TUNEDN,
	FM_KEY_EVENT_KEY_FM_MUTETOGGLE,
	FM_KEY_EVENT_NO,
};

enum
{
	LINE_IN_KEY_EVENT_KEY_ENTER_LINEIN_MODE,
	LINE_IN_KEY_EVENT_KEY_EXIT_LINEIN_MODE,
	LINE_IN_KEY_EVENT_KEY_LINEIN_MUTE_TOGGLE,
	LINE_IN_KEY_EVENT_NO,
};

enum
{
	TESTMODE_KEY_EVENT_KEY_ENTER_TESTMODE, 
	TESTMODE_KEY_EVENT_KEY_SWITCH_TEST_MODE_CHANNEL,  
	TESTMODE_KEY_EVENT_KEY_SWITCH_TEST_MODE_POWER,	  	   				
	TESTMODE_KEY_EVENT_KEY_SWITCH_TEST_MODE_STATE,				  
	TESTMODE_KEY_EVENT_KEY_SWITCH_TEST_MODE_TX_PACKET_TYPE,
	TESTMODE_KEY_EVENT_NO,
};

enum
{
	HID_KEY_EVENT_KEY_SELFIE,
	HID_KEY_EVENT_SWITCH_SELFIE,
	HID_KEY_EVENT_NO,
};

typedef struct
{
	void (*fKeyEvt)(U8 linkIndex);
}MMI_KEY_EVT;

typedef struct
{
	U16 (*fKeyCheckValid)(U16 keyCode);
}MMI_KEY_CHECK;

#endif
