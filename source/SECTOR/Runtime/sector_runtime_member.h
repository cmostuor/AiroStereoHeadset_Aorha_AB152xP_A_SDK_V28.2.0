#if AIRAPP_CALLER_NAME
SECTORS_ENUM_MACRO( SECTOR_APP_CALLERNAME_DATA, &gSector_AppCallerNameData, sizeof(SECTOR_APP_CALLERNAME_DATA_STRU), CRC_NOT_CHK)
#else
SECTORS_ENUM_MACRO( SECTOR_APP_CALLERNAME_DATA, NULL, 0, CRC_NOT_CHK)
#endif
