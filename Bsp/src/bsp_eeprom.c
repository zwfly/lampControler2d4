/*
 * bsp_eeprom.c
 *
 *  Created on: 2017Äê9ÔÂ8ÈÕ
 *      Author: fly
 */
#include "bsp.h"

static UINT8 looptmp = 0, u8_addrl_r;
static UINT8 code *cd_longaddr;
static UINT8 xdata *xd_tmp;

void EEPROM_InitHard(void) {

}

/*****************************************************************************************************************
 write_DATAFLASH_BYTE :
 user can copy all this subroutine into project, then call this function in main.
 ******************************************************************************************************************/
void write_DATAFLASH_BYTE(UINT16 u16_addr, UINT8 u8_data) {

//Check page start address
	u8_addrl_r = u16_addr;
	if (u8_addrl_r < 0x80) {
		u8_addrl_r = 0;
	} else {
		u8_addrl_r = 0x80;
	}
//Save APROM data to XRAM
	xd_tmp = 0x80;
	cd_longaddr = (u16_addr & 0xff00) + u8_addrl_r;
	while (xd_tmp != 0x100) {
		*xd_tmp = *cd_longaddr;
		looptmp++;
		xd_tmp++;
		cd_longaddr++;
	}
// Modify customer data in XRAM
	u8_addrl_r = u16_addr;
	if (u8_addrl_r < 0x80) {
		xd_tmp = u8_addrl_r + 0x80;
	} else {
		xd_tmp = u8_addrl_r + 0;
	}
	*xd_tmp = u8_data;
//Erase APROM DATAFLASH page
	IAPAL = u16_addr;
	IAPAH = u16_addr >> 8;
	IAPFD = 0xFF;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x22;
	set_IAPGO
	;
//Save changed RAM data to APROM DATAFLASH
	u8_addrl_r = u16_addr;
	if (u8_addrl_r < 0x80) {
		u8_addrl_r = 0;
	} else {
		u8_addrl_r = 0x80;
	}
	xd_tmp = 0x80;
	IAPAL = u8_addrl_r;
	IAPAH = u16_addr >> 8;
	set_IAPEN
	;
	set_APUEN
	;
	IAPCN = 0x21;
	while (xd_tmp != 0xFF) {
		IAPFD = *xd_tmp;
		set_IAPGO
		;
		IAPAL++;
		xd_tmp++;
	}
	clr_APUEN
	;
	clr_IAPEN
	;
}

//-------------------------------------------------------------------------
UINT8 read_APROM_BYTE(UINT16 code *u16_addr){
	UINT8 rdata;
	rdata = *u16_addr>>8;
	return rdata;
}

/******************************************************************************************************************/
