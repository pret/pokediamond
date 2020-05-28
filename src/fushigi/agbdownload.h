//===================================================================
/**
 * @file	agbdownload.h
 * @bfief	AGBカセットからのふしぎデータダウンロード
 * @author	Satoshi Mitsuhara
 * @date	06.06.09
 *
 * $Id: agbdownload.h,v 1.1 2006/06/08 17:59:07 mitsuhara Exp $
 */
//===================================================================
#ifndef __AGBDOWNLOAD_H__
#define __AGBDOWNLOAD_H__


// データサイズが置かれているアドレス
#define AGBMISSIONDATASIZE	0x08100000
// ビーコン情報が配置されているアドレス
#define AGBBEACONDATAPTR	0x08100010
// ふしぎデータが配置されているアドレス
#define AGBMISSIONDATAPTR	0x08100100

#define AGB_MAKER_CODE		0x3130		// 任天堂

extern int GetAgbCartridgeDataSize(void);
extern BOOL GetAgbCartridgeBeaconData(void *dist, int size);
extern BOOL ReadAgbCartridgeData(void *dist, int size);


#endif	// __AGBDOWNLOAD_H__
/*  */

