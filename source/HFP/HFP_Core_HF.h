
#ifndef _HFP_HANDLER_HF_H_
#define _HFP_HANDLER_HF_H_

enum
{
	HFP_INDICATORS,
	HFP_RESULT_CODE,
	HFP_ERROR_RESULT_CODE,
};

#define HFP_INDICATOR_ARRAY_SIZE			7
#define HFP_INDICATOR_MAX_LENGTH			(10+1)//add one to add a 0x00 at the end of the string;

//HFP AT result code index B (Shall match the result code array)
enum {
	HFP_RESULT_CODE_RING			,		//0
	HFP_RESULT_CODE_PLUS_BRSF		,
	HFP_RESULT_CODE_PLUS_CIND		,
	HFP_RESULT_CODE_PLUS_CHLD		,
	HFP_RESULT_CODE_PLUS_VGM		,
	HFP_RESULT_CODE_PLUS_VGS		,		//5
	HFP_RESULT_CODE_OK				,
	HFP_RESULT_CODE_ERROR			,					
	HFP_RESULT_CODE_CIEV			,					
	HFP_RESULT_CODE_PLUS_BVRA		,				
	HFP_RESULT_CODE_PLUS_COPS		,		//10
	HFP_RESULT_CODE_PLUS_BTRH		,				
	HFP_RESULT_CODE_PLUS_BSIR		,
	HFP_RESULT_CODE_PLUS_CNUM		,
	HFP_RESULT_CODE_PLUS_CME		,
	HFP_RESULT_CODE_PLUS_CLCC		,		//15
	HFP_RESULT_CODE_PLUS_CLIP		,
	HFP_RESULT_CODE_PLUS_CCWA		,
	HFP_RESULT_CODE_PLUS_BINP		,						
	HFP_RESULT_CODE_PLUS_XAPL		,
	HFP_RESULT_CODE_PLUS_BCS		,		//20
	HFP_RESULT_CODE_PLUS_BIND		,
	HFP_RESULT_CODE_PLUS_APLSIRI	,
	HFP_RESULT_CODE_ARRAY_SIZE,

	
	HFP_RESULT_CODE_NO_CARRIER	= HFP_RESULT_CODE_ARRAY_SIZE,		//24
	HFP_RESULT_CODE_BUSY			,
	HFP_RESULT_CODE_NO_ANSWER		,
	HFP_RESULT_CODE_DELAYED			,
	HFP_RESULT_CODE_BLACKLISTED		,
	HFP_ERROR_RESULT_CODE_END,
};

#define HFP_RESULT_CODE_MAX_LENGTH			(8+1)//add one to add a 0x00 at the end of the string;

#define HFP_ERROR_RESULT_CODE_ARRAY_SIZE	(HFP_ERROR_RESULT_CODE_END - HFP_RESULT_CODE_ARRAY_SIZE)
#define HFP_ERROR_RESULT_CODE_MAX_LENGTH	(11+1)//add one to add a 0x00 at the end of the string;

#define MAX_HFP_CIND_INDEX					((OSMEM1_BLKSIZE - sizeof(HFP_at_BIA)) / 2)


//misc Flags
#define HFP_GET_MMI_CMD_NO_UPDATE_RING		0x02


#endif //_HFP_HANDLER_HF_H_
