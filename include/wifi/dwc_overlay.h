//=============================================================================
/**
 * @file	dwc_overlay.h
 * @brief	WIFIのオーバーレイ切り替え用関数
 * @author	Katsumi Ohno
 * @date    2006.07.12
 */
//=============================================================================

#ifndef __DWC_OVERLAY_H__
#define __DWC_OVERLAY_H__



extern void DwcOverlayStart(void);
extern void DwcOverlayEnd(void);
extern void DwcUtilOverlayStart(void);
extern void DwcUtilOverlayEnd(void);
extern void DwcUtilOverlayCall(SAVEDATA* pSaveData,int HeapID);
extern void DwcTestOverlayStart(SAVEDATA* pSaveData ,int HeapID);
extern void DwcTestOverlayEnd(void);

extern void DpwCommonOverlayStart(void);
extern void DpwCommonOverlayEnd(void);



#endif //__DWC_OVERLAY_H__

