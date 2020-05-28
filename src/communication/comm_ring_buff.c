//=============================================================================
/**
 * @file	comm_ring_buff.c
 * @bfief	リングバッファの仕組みを管理する関数
 * @author	katsumi ohno
 * @date	05/09/16
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"
#include "comm_ring_buff.h"



static int _ringPos(RingBuffWork* pRing,int i);

//==============================================================================
/**
 * リングバッファ管理構造体初期化
 * @param   pRing        リングバッファ管理ポインタ
 * @param   pDataArea    リングバッファメモリー
 * @param   size         リングバッファメモリーサイズ
 * @retval  none
 */
//==============================================================================
void CommRingInitialize(RingBuffWork* pRing, u8* pDataArea, int size)
{
    pRing->pWork = pDataArea;
    pRing->size = size;
    pRing->startPos = 0;
    pRing->endPos = 0;
    pRing->backupEndPos = 0;
//    pRing->backupStartPos = 0;
}

//==============================================================================
/**
 * リングバッファに書き込む
 * @param   pRing        リングバッファ管理ポインタ
 * @param   pDataArea    書き込むデータ
 * @param   size         書き込みサイズ
 * @param   bUsed  このリングを使用中らしい
 * @retval  none
 */
//==============================================================================
void CommRingPuts(RingBuffWork* pRing, u8* pDataArea, int size,int line)
{
    int i,j;

    // ここのASSERTに引っかかるということは
    // 処理が遅延しているのに、通信は毎syncくるので
    // ストックするバッファ分まであふれると、ここで止まります。
    // 通信のバッファを増やすか、今の部分の処理を分断するか、対処が必要です。
    // 最終的にはこのエラーがあると通信を切断します。
    if(CommRingDataRestSize(pRing) <= size){
#ifdef DEBUG_ONLY_FOR_ohno
        OHNO_PRINT("%d %d line %d \n",CommRingDataRestSize(pRing),size,line);
        GF_ASSERT_MSG(0,"CommRingOVER %d %d",CommRingDataRestSize(pRing),size);
#endif
        CommSetError();
        return;
    }
    j = 0;
    for(i = pRing->backupEndPos; i < pRing->backupEndPos + size; i++,j++){
        GF_ASSERT(pDataArea);
        pRing->pWork[_ringPos( pRing, i )] = pDataArea[j];
    }
    pRing->backupEndPos = _ringPos( pRing, i );
}

//==============================================================================
/**
 * リングバッファからデータを得る
 * @param   pRing        リングバッファ管理ポインタ
 * @param   pDataArea    読み込みバッファ
 * @param   size         読み込みバッファサイズ
 * @retval  実際に読み込んだデータ
 */
//==============================================================================
int CommRingGets(RingBuffWork* pRing, u8* pDataArea, int size)
{
    int i,j;

    i = CommRingChecks(pRing, pDataArea, size);
    pRing->startPos = _ringPos( pRing, pRing->startPos + i);
//    OHNO_PRINT("++++++ バッファからだした %d %d  %d byte\n", pRing->startPos, pRing->endPos, i);
    return i;
}

//==============================================================================
/**
 * リングバッファから1byteデータを得る
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  1byteのデータ リングにデータがないときは0(不定)
 */
//==============================================================================
u8 CommRingGetByte(RingBuffWork* pRing)
{
    u8 byte;

    CommRingGets(pRing, &byte, 1);
    return byte;
}

//==============================================================================
/**
 * リングバッファのデータ検査  読み込むだけで位置を進めない
 * @param   pRing        リングバッファ管理ポインタ
 * @param   pDataArea    読み込みバッファ
 * @param   size         読み込みバッファサイズ
 * @retval  実際に読み込んだデータ
 */
//==============================================================================
int CommRingChecks(RingBuffWork* pRing, u8* pDataArea, int size)
{
    int i,j;

    j = 0;
    for(i = pRing->startPos; i < pRing->startPos + size; i++,j++){
        if(pRing->endPos == _ringPos( pRing,i )){
            return j;
        }
        pDataArea[j] = pRing->pWork[_ringPos( pRing,i )];
    }
    return j;
}

//==============================================================================
/**
 * リングバッファのデータがいくつ入っているか得る
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  データサイズ
 */
//==============================================================================
int CommRingDataSize(RingBuffWork* pRing)
{
    if(pRing->startPos > pRing->endPos){
        return (pRing->size + pRing->endPos - pRing->startPos);
    }
    return (pRing->endPos - pRing->startPos);
}

//==============================================================================
/**
 * リングバッファのデータがどのくらいあまっているか検査
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  実際に読み込んだデータ
 */
//==============================================================================
int CommRingDataRestSize(RingBuffWork* pRing)
{
    return (pRing->size - CommRingDataSize(pRing));
}

//==============================================================================
/**
 * カウンターをバックアップする
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  nono
 */
//==============================================================================
//void CommRingStartPush(RingBuffWork* pRing)
//{
//    pRing->backupStartPos = pRing->startPos;
//}

//==============================================================================
/**
 * カウンターをバックアップする
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  nono
 */
//==============================================================================
//void CommRingStartPop(RingBuffWork* pRing)
//{
//    pRing->startPos = pRing->backupStartPos;
//}

//==============================================================================
/**
 * ringサイズの場所
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  
 */
//==============================================================================
int _ringPos(RingBuffWork* pRing,int i)
{
    return i % pRing->size;

}

//==============================================================================
/**
 * カウンター場所をすりかえる
 * @param   pRing        リングバッファ管理ポインタ
 * @retval  nono
 */
//==============================================================================
void CommRingEndChange(RingBuffWork* pRing)
{
    pRing->endPos = pRing->backupEndPos;
}

