?EP?P011_f1_0xFFB116?P011 SEGMENT 'ECODE_PATCH'
PUBLIC P011_f1_0xFFB116_1??
PUBLIC P011_f1_0xFFB116_2??
RSEG ?EP?P011_f1_0xFFB116?P011	;program segment

P011_f1_0xFFB116_1??:
DB		0x14, 0xB1, 0xFF
DB		0
DB		0x94, 0xF2
EJMP	P011_f1_patch

P011_f1_0xFFB116_2??:
DB		0x18, 0xB1, 0xFF
DB		2
EJMP	P011_f1_patch
DB		0x7E, 0x24

P011_f1_patch:
; LC_SAC_SET_CURRENT_LINK(LC_SAC_LINK_SW);
MOV      0xC1,#0x2B
MOV      0xC2,#0x0A
;gLC_ctl.LinkSchedCtl[0].LinkIndex = INVALID_LINK_SCH_CTL_IDX;
;gLC_ctl.LinkSchedCtl[1].LinkIndex = INVALID_LINK_SCH_CTL_IDX;
;gLC_ctl.LastSchedLinkCtlIdx = INVALID_LINK_SCH_CTL_IDX;
;gLC_ctl.CurrSchedLinkCtlIdx = INVALID_LINK_SCH_CTL_IDX;
MOV		 DPTR,#0x86B0
MOV	     A,#0xFF
MOVX	 @DPTR,A
INC      DPTR
MOVX     @DPTR,A
INC		 DPTR
MOVX     @DPTR,A
MOV		 DPTR,#0x86C5
MOVX     @DPTR,A

MOV      WR6,#0xE120
EJMP     0xFFB11A