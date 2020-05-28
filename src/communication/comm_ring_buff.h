//=============================================================================
/**
 * @file	comm_ring_buff.h
 * @bfief	リングバッファの仕組みを管理する関数
 * @author	katsumi ohno
 * @date	05/09/16
 */
//=============================================================================


#ifndef __COMM_RING_BUFF_H__
#define __COMM_RING_BUFF_H__

// リングバッファ構造体
typedef struct{
    u8* pWork;
    s16 startPos;
    volatile s16 endPos;
    volatile s16 backupEndPos;
//    s16 backupStartPos;
    s16 size;
} RingBuffWork;

// リングバッファの初期化
extern void CommRingInitialize(RingBuffWork* pRing, u8* pDataArea, int size);
// リングにデータを入れる
extern void CommRingPuts(RingBuffWork* pRing, u8* pDataArea, int size,int line);
// リングからデータを得る
extern int CommRingGets(RingBuffWork* pRing, u8* pDataArea, int size);
// リングから1byteデータを得る
extern u8 CommRingGetByte(RingBuffWork* pRing);
// リングにデータがあるか引っ張り出す ポインタは変えない
extern int CommRingChecks(RingBuffWork* pRing, u8* pDataArea, int size);
// リングサイズを得る
extern int CommRingDataSize(RingBuffWork* pRing);
// リングの残りサイズを得る
extern int CommRingDataRestSize(RingBuffWork* pRing);

// スタートのバックアップからスタートを戻す
extern void CommRingStartPop(RingBuffWork* pRing);
// スタートのバックアップへスタートを入れる
extern void CommRingStartPush(RingBuffWork* pRing);
// End場所をすりかえる
extern void CommRingEndChange(RingBuffWork* pRing);

#endif// __COMM_RING_BUFF_H__

