//============================================================================================
/**
 * @file	palanm.c
 * @brief	パレットフェード処理
 * @author	Hiroyuki Nakamura
 * @date	2004.11.24
 */
//============================================================================================
#define	PALANM_H_GLOBAL

#include "common.h"
#include "tcb.h"

#include "system/palanm.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"


//============================================================================================
//	定数定義
//============================================================================================
#define	DEF_FADE_VAL	( 2 )			// 基本速度
// 計算
#define FADE_CHANGE( before, after, evy )					\
			( before + ( ( after - before ) * evy >> 4 ) )

///フェード計算を行うローカルタスクのTCBプライオリティ
///	※必ずTCBの最後に実行されるようにプライオリティを下にしている
#define TCBPRI_CALC_FADETASK		(0xffffffff - 1)

#define	NORMAL_COLOR_NUM	( 16 )		// 通常パレットのカラー数
#define	EXTRA_COLOR_NUM		( 256 )		// 拡張パレットのカラー数


//==============================================================================
//	構造体定義
//==============================================================================
/// パレットフェードデータ
typedef struct _PALETTE_FADE_DATA{
	FADE_REQ_EX2	dat[ ALL_PALETTE_SIZE ];

	u16	req_flg:2;		// 0=未登録, 1=動作中, 2=一時停止
	u16	req_bit:14;		// リクエストビット（カラー計算用）
	u16	trans_bit:14;	// トランスビット（カラー転送用）
	u16	tcb_flg:1;		// TCB登録フラグ　0=未登録, 1=登録済
	u16	auto_trans:1;			// トランスビットに関係なく、毎フレーム全パレットを転送
	
	u8 force_stop;		//TRUE:パレットフェード強制終了
	
	u8 dummy[3];
}PALETTE_FADE_DATA;

/// カラーパレット構造体
typedef struct {
    u16 Red:5;              // 赤
    u16 Green:5;            // 緑
    u16 Blue:5;             // 青
    u16 Dummy_15:1;
} PLTT_DATA;

//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static u8 ReqBitCheck( u16 flg, u16 req );
static void TransBitSet( PALETTE_FADE_PTR pfd, u16 id );
static void FadeBitCheck( FADEREQ req, FADE_REQ_EX2 * wk, u16 * fade_bit );
static void FadeReqSet(
				FADE_REQ_PARAM * wk, u16 fade_bit,
				s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb );
static void PaletteFadeTask( TCB_PTR tcb, void * work );
static void NormalPaletteFade(PALETTE_FADE_PTR pfd);
static void ExtraPaletteFade(PALETTE_FADE_PTR pfd);
static void PaletteFade( PALETTE_FADE_PTR pfd, u16 id, u16 siz );
static void PaletteFadeMain( PALETTE_FADE_PTR pfd, u16 id, u16 siz );
static void FadeWorkSet( u16 * def, u16 * trans, FADE_REQ_PARAM * wk, u32 siz );
static void FadeParamCheck(PALETTE_FADE_PTR pfd, u8 id, FADE_REQ_PARAM * wk );



//--------------------------------------------------------------
/**
 * @brief   パレットフェードシステムワーク作成
 *
 * @param   heap_id		ヒープID
 *
 * @retval  作成したパレットフェードシステムワークのポインタ
 *
 * システムを使わなくなったらPaletteFadeFreeで解放処理を行ってください
 */
//--------------------------------------------------------------
PALETTE_FADE_PTR PaletteFadeInit(int heap_id)
{
	PALETTE_FADE_PTR pfd;
	
	pfd = sys_AllocMemory(heap_id, sizeof(PALETTE_FADE_DATA));
	MI_CpuClear8(pfd, sizeof(PALETTE_FADE_DATA));
	return pfd;
}

//--------------------------------------------------------------
/**
 * @brief   パレットフェードシステム解放
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 */
//--------------------------------------------------------------
void PaletteFadeFree(PALETTE_FADE_PTR pfd)
{
	sys_FreeMemoryEz(pfd);
}

//--------------------------------------------------------------------------------------------
/**
 * リクエストデータセット
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	req			リクエストデータ番号
 * @param	def_wk		初期データ
 * @param	trans_wk	転送用データ
 * @param	siz			サイズ（バイト単位）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAdrSet(PALETTE_FADE_PTR pfd, FADEREQ req, void * def_wk, void * trans_wk, u32 siz )
{
	pfd->dat[req].def_wk   = (u16 *)def_wk;
	pfd->dat[req].trans_wk = (u16 *)trans_wk;
	pfd->dat[req].siz      = siz;
}

//--------------------------------------------------------------------------------------------
/**
 * リクエストデータをmallocしてセット
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	req		リクエストデータ番号
 * @param	siz		データサイズ（バイト単位）
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAllocSet(PALETTE_FADE_PTR pfd, FADEREQ req, u32 siz, u32 heap )
{
	void * def_wk;
	void * trans_wk;

	def_wk   = sys_AllocMemory( heap, siz );
	trans_wk = sys_AllocMemory( heap, siz );

#ifdef	OSP_ERR_PALANMWK_GET	// パレットフェードのワーク取得失敗
	if( def_wk == NULL ){
		OS_Printf( "ERROR : PaletteFadeWorkAlloc ( %d ) - def_wk\n", req );
	}
	if( trans_wk == NULL ){
		OS_Printf( "ERROR : PaletteFadeWorkAlloc ( %d ) - trans_wk\n", req );
	}
#endif	// OSP_ERR_PALANMWK_GET

	PaletteFadeWorkAdrSet(pfd, req, def_wk, trans_wk, siz );
}

//--------------------------------------------------------------------------------------------
/**
 * リクエストデータ開放
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	req		リクエストデータ番号
 *
 * @return	none
 *
 * @li	PaletteFadeWorkAllocSet()で取得した場合に使用
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAllocFree(PALETTE_FADE_PTR pfd, FADEREQ req)
{
	sys_FreeMemoryEz(pfd->dat[req].def_wk );
	sys_FreeMemoryEz(pfd->dat[req].trans_wk );
}

//--------------------------------------------------------------------------------------------
/**
 * パレットの初期データをセット
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	dat		パレットデータ
 * @param	req		リクエストデータ番号
 * @param	pos		開始位置
 * @param	siz		データサイズ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteWorkSet(PALETTE_FADE_PTR pfd, const void * dat, FADEREQ req, u16 pos, u16 siz )
{
#ifdef	OSP_ERR_PALANM_SIZ_OVER		// サイズオーバー
	if( (pos*2+siz) > pfd->dat[req].siz ){
		OS_Printf( "ERROR : PaletteWorkSet - SizeOver ( %d )\n", req );
	}
#endif	// OSP_ERR_PALANM_SIZ_OVER
	MI_CpuCopy16( dat, (void *)&pfd->dat[req].def_wk[pos], (u32)siz );
	MI_CpuCopy16( dat, (void *)&pfd->dat[req].trans_wk[pos], (u32)siz );
}

//--------------------------------------------------------------
/**
 * @brief   アーカイブされているパレットデータをロードしてワークに展開します(拡張版)
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param   fileIdx			アーカイブファイルインデックス
 * @param   dataIdx			アーカイブデータインデックス
 * @param   heap			データ読み込みテンポラリとして使うヒープID
 * @param   req				リクエストデータ番号
 * @param   trans_size		転送サイズ(バイト単位　※2バイトアライメントされていること)
 * @param   pos				パレット転送開始位置(カラー単位)
 * @param   read_pos		ロードしたパレットの読み込み開始位置(カラー単位)
 */
//--------------------------------------------------------------
void PaletteWorkSetEx_Arc(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
	FADEREQ req, u32 trans_size, u16 pos, u16 read_pos)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	GF_ASSERT(pos * sizeof(pos) + trans_size <= pfd->dat[req].siz);
	PaletteWorkSet(pfd, &(((u16*)(pal_data->pRawData))[read_pos]), req, pos, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   アーカイブされているパレットデータをロードしてワークに展開します
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param   fileIdx			アーカイブファイルインデックス
 * @param   dataIdx			アーカイブデータインデックス
 * @param   heap			データ読み込みテンポラリとして使うヒープID
 * @param   req				リクエストデータ番号
 * @param   trans_size		転送サイズ(バイト単位　※2バイトアライメントされていること)
 * @param   pos				パレット転送開始位置(カラー単位)
 */
//--------------------------------------------------------------
void PaletteWorkSet_Arc(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
	FADEREQ req, u32 trans_size, u16 pos)
{
	PaletteWorkSetEx_Arc(pfd, fileIdx, dataIdx, heap, req, trans_size, pos, 0);
}

//--------------------------------------------------------------
/**
 * @brief   パレットVRAMからワークへデータコピーをします
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param   req				リクエストデータ番号
 * @param   pos				パレット転送開始位置(カラー単位)
 * @param   trans_size		転送サイズ(バイト単位　※2バイトアライメントされていること)
 *
 * 拡張パレットには未対応です
 */
//--------------------------------------------------------------
void PaletteWorkSet_VramCopy(PALETTE_FADE_PTR pfd, FADEREQ req, u16 pos, u32 trans_size)
{
	u16 *pltt_vram;
	
	GF_ASSERT(pos * sizeof(pos) + trans_size <= pfd->dat[req].siz);

	switch(req){
	case FADE_MAIN_BG:
		pltt_vram = (u16 *)GF_MMAP_MainBgPlttAddr();
		break;
	case FADE_SUB_BG:
		pltt_vram = (u16 *)GF_MMAP_SubBgPlttAddr();
		break;
	case FADE_MAIN_OBJ:
		pltt_vram = (u16 *)GF_MMAP_MainObjPlttAddr();
		break;
	case FADE_SUB_OBJ:
		pltt_vram = (u16 *)GF_MMAP_SubObjPlttAddr();
		break;
	default:
		GF_ASSERT(0 && "未対応のリクエストです");
		return;
	}
	
	PaletteWorkSet(pfd, &pltt_vram[pos], req, pos, trans_size);
}

//--------------------------------------------------------------
/**
 * @brief   拡張パレットVRAMからワークへデータコピーをします
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param   req				リクエストデータ番号
 * @param   trans_size		転送サイズ(バイト単位　※2バイトアライメントされていること)
 * @param   pos				パレット転送開始位置(カラー単位)
 *
 * メインパレットはPaletteWorkSet_VramCopyを使用してください
 */
//--------------------------------------------------------------
void PaletteWorkSet_VramCopyEx(PALETTE_FADE_PTR pfd, FADEREQ req, u32 trans_size, u16 pos)
{
	GF_ASSERT(0 && "現在未作成です");
}

//--------------------------------------------------------------
/**
 * @brief   アーカイブされているパレットデータを指定したワークにロードします(拡張版)
 *
 * @param   fileIdx			アーカイブファイルインデックス
 * @param   dataIdx			アーカイブデータインデックス
 * @param   heap			データ読み込みテンポラリとして使うヒープID
 * @param   trans_size		転送サイズ(バイト単位　※2バイトアライメントされていること)
 * @param   read_pos		ロードしたパレットの読み込み開始位置(カラー単位)
 * @param   dest			ロードしたパレットの展開先へのポインタ
 */
//--------------------------------------------------------------
void PaletteWorkSetEx_ArcWork(u32 fileIdx, u32 dataIdx, u32 heap, u32 trans_size, 
	u16 read_pos, void *dest)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	MI_CpuCopy16(&(((u16*)(pal_data->pRawData))[read_pos]), dest, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------------------------------------
/**
 * パレットワーク間コピー
 *
 * @param   pfd				パレットフェードシステムワークへのポインタ
 * @param	src_req			コピー元リクエストデータ番号
 * @param	src_pos			コピー元開始位置(カラー単位)
 * @param	dest_req		コピー先リクエストデータ番号
 * @param	dest_pos		コピー先開始位置(カラー単位)
 * @param	siz				コピーするデータサイズ(バイト単位)
 *
 * コピー元は元データから読み取り、コピー先は元データ、転送先、の両方にコピーを行います
 */
//--------------------------------------------------------------------------------------------
void PaletteWorkCopy(PALETTE_FADE_PTR pfd, FADEREQ src_req, u16 src_pos, 
	FADEREQ dest_req, u16 dest_pos, u16 siz )
{
	MI_CpuCopy16((void *)&pfd->dat[src_req].def_wk[src_pos], 
		(void *)&pfd->dat[dest_req].def_wk[dest_pos], siz);
	MI_CpuCopy16((void *)&pfd->dat[src_req].def_wk[src_pos], 
		(void *)&pfd->dat[dest_req].trans_wk[dest_pos], siz);
}

//--------------------------------------------------------------------------------------------
/**
 * パレットワークにセットされているパレットデータを取得
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	tpye	取得するパレットの種類
 *
 * @return	セットされているパレットデータ
 */
//--------------------------------------------------------------------------------------------
u16 * PaletteWorkDefaultWorkGet( PALETTE_FADE_PTR pfd, FADEREQ type )
{
	return pfd->dat[type].def_wk;
}

//--------------------------------------------------------------------------------------------
/**
 * パレットワークにセットされている転送用パレットデータを取得
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	tpye	取得するパレットの種類
 *
 * @return	セットされているパレットデータ
 */
//--------------------------------------------------------------------------------------------
u16 * PaletteWorkTransWorkGet( PALETTE_FADE_PTR pfd, FADEREQ type )
{
	return pfd->dat[type].trans_wk;
}

//--------------------------------------------------------------------------------------------
/**
 * パレットフェードリクエスト（上書き不可）
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	req_bit		パレットの種類（ビット指定）
 * @param	fade_bit	パレット指定（ビット指定）bit0 = pal0
 * @param	wait		計算待ち時間（マイナスあり）
 * @param	start_evy	初期濃度
 * @param	end_evy		最終濃度
 * @param	next_rgb	変更後の色
 *
 * @retval	"0 = 正常"
 * @retval	"1 = エラー"
 *
 * @li	濃度：0 ～ 16 ( 0(元の色) ～ 2,3..(中間色) ～ 16(指定した色) )
 */
//--------------------------------------------------------------------------------------------
u8 PaletteFadeReq(PALETTE_FADE_PTR pfd, u16 req_bit, u16 fade_bit, s8 wait, 
	u8 start_evy, u8 end_evy, u16 next_rgb )
{
	u16	cpy_bit;
	u8	tmp;
	u8	i;

	cpy_bit = fade_bit;
	tmp = 0;
	for( i=0; i<ALL_PALETTE_SIZE; i++ ){
		if( ReqBitCheck( req_bit, i ) == TRUE &&
			ReqBitCheck( pfd->req_bit, i ) == FALSE ){

			FadeBitCheck( i, &pfd->dat[i], &fade_bit );
			FadeReqSet( &pfd->dat[i].prm, fade_bit, wait, start_evy, end_evy, next_rgb );

			TransBitSet( pfd, i );
			if( i >= FADE_MAIN_BG_EX0 ){
				PaletteFadeMain( pfd, i, EXTRA_COLOR_NUM );
			}else{
				PaletteFadeMain( pfd, i, NORMAL_COLOR_NUM );
			}

			fade_bit = cpy_bit;
			tmp = 1;
		}
	}

	if( tmp == 1 ){
		pfd->req_bit |= req_bit;
		if( pfd->tcb_flg == 0 ){
			pfd->tcb_flg = 1;
			pfd->req_flg = 1;
			pfd->force_stop = FALSE;
			TCB_Add( PaletteFadeTask, pfd, TCBPRI_CALC_FADETASK );
		}
	}

	return tmp;
}

//--------------------------------------------------------------------------------------------
/**
 * パレットフェードリクエスト（上書き可）
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	req_bit		パレットの種類（ビット指定）
 * @param	fade_bit	パレット指定（ビット指定）bit0 = pal0
 * @param	wait		計算待ち時間（マイナスあり）
 * @param	start_evy	初期濃度
 * @param	end_evy		最終濃度
 * @param	next_rgb	変更後の色
 *
 * @retval	"0 = 正常"
 * @retval	"1 = エラー"
 *
 * @li	濃度：0 ～ 16 ( 0(元の色) ～ 2,3..(中間色) ～ 16(指定した色) )
 */
//--------------------------------------------------------------------------------------------
u8 PaletteFadeReqWrite(PALETTE_FADE_PTR pfd, u16 req_bit, u16 fade_bit, s8 wait, 
	u8 start_evy, u8 end_evy, u16 next_rgb )
{
	u16	cpy_bit;
	u8	tmp;
	u8	i;

	cpy_bit = fade_bit;
	tmp = 0;
	for( i=0; i<ALL_PALETTE_SIZE; i++ ){
		if( ReqBitCheck( req_bit, i ) == TRUE ){
			FadeBitCheck( i, &pfd->dat[i], &fade_bit );
			FadeReqSet( &pfd->dat[i].prm, fade_bit, wait, start_evy, end_evy, next_rgb );

			TransBitSet( pfd, i );
			if( i >= FADE_MAIN_BG_EX0 ){
				PaletteFadeMain( pfd, i, EXTRA_COLOR_NUM );
			}else{
				PaletteFadeMain( pfd, i, NORMAL_COLOR_NUM );
			}

			fade_bit = cpy_bit;
			tmp = 1;
		}
	}

	if( tmp == 1 ){
//		pfd->req_bit |= req_bit;
		pfd->req_bit = req_bit;
		if( pfd->tcb_flg == 0 ){
			pfd->tcb_flg = 1;
			pfd->req_flg = 1;
			pfd->force_stop = FALSE;
			TCB_Add( PaletteFadeTask, pfd, TCBPRI_CALC_FADETASK );
		}
	}

	return tmp;
}

//--------------------------------------------------------------------------------------------
/**
 * リクエストの状態を調べる
 *
 * @param	flg		
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u8 ReqBitCheck( u16 flg, u16 req )
{
	if( ( flg & ( 1 << req ) ) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 転送フラグセット
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	id		パレットID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TransBitSet( PALETTE_FADE_PTR pfd, u16 id )
{
	if( ReqBitCheck( pfd->trans_bit, id ) == TRUE ){
		return;
	}
	pfd->trans_bit |= ( 1 << id );
}

//--------------------------------------------------------------------------------------------
/**
 * フェードビットチェック
 *
 * @param	req			リクエストデータ番号
 * @param	wk			リクエストデータ
 * @param	fade_bit	パレット指定（ビット指定）bit0 = pal0
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeBitCheck( FADEREQ req, FADE_REQ_EX2 * wk, u16 * fade_bit )
{
	u16	siz_bit;
	u8	i, j;

	if( req < NORMAL_PALETTE_SIZE ){
		j = wk->siz / 32;
	}else{
		j = wk->siz / 512;
	}

	siz_bit = 0;
	for( i=0; i<j; i++ ){
		siz_bit += ( 1 << i );
	}

	*fade_bit &= siz_bit;
}


//--------------------------------------------------------------------------------------------
/**
 * パラメータセット
 *
 * @param	wk			データ
 * @param	fade_bit	パレット指定（ビット指定）bit0 = pal0
 * @param	wait		計算待ち時間（マイナスあり）
 * @param	start_evy	初期濃度
 * @param	end_evy		最終濃度
 * @param	next_rgb	変更後の色
 *
 * @return	none
 *
 * @li	濃度：0 ～ 16 ( 0(元の色) ～ 2,3..(中間色) ～ 16(指定した色) )
 */
//--------------------------------------------------------------------------------------------
static void FadeReqSet(
				FADE_REQ_PARAM * wk, u16 fade_bit,
				s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb )
{
	// waitがﾏｲﾅｽの時はvalueを大きくしてﾌｪｰﾄﾞを早くする
	if( wait < 0 ){
		wk->fade_value = DEF_FADE_VAL + abs( wait );
		wk->wait = 0;
	}else{
		wk->fade_value = DEF_FADE_VAL;
		wk->wait = wait;
	}

	wk->fade_bit = fade_bit;
	wk->now_evy  = start_evy;
	wk->end_evy  = end_evy;
	wk->next_rgb = next_rgb;
	wk->wait_cnt = wk->wait;
	
	if( start_evy < end_evy ){
		wk->direction = 0;
	}else{
		wk->direction = 1;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレットフェードメインタスク
 *
 * @param	tcb		TCBのポインタ
 * @param	work	TCBワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFadeTask( TCB_PTR tcb, void * work )
{
	PALETTE_FADE_PTR pfd = work;
	
	if(pfd->force_stop == TRUE){
		pfd->force_stop = FALSE;
		pfd->trans_bit = 0;
		pfd->req_bit = 0;
		pfd->tcb_flg = 0;
		TCB_Delete( tcb );
		return;
	}
	
	if( pfd->req_flg != 1 ){ return; }

	pfd->trans_bit = pfd->req_bit;

	NormalPaletteFade(pfd);
	ExtraPaletteFade(pfd);

	if( pfd->req_bit == 0 ){
		pfd->tcb_flg = 0;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレットフェード強制停止命令
 *
 * @param	tcb		TCBのポインタ
 * @param	work	TCBワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeForceStop(PALETTE_FADE_PTR pfd)
{
	if(pfd->req_bit == 0){
		return;
	}
	
	pfd->force_stop = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * 通常パレットのフェード計算
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NormalPaletteFade(PALETTE_FADE_PTR pfd)
{
	u8	i, j;

	for( i=0; i<NORMAL_PALETTE_SIZE; i++ ){
/*
		if( ReqBitCheck( pfd->req_bit, i ) == FALSE ){
			continue;
		}

		if( pfd->dat[i].prm.wait_cnt < pfd->dat[i].prm.wait ){
			pfd->dat[i].prm.wait_cnt++;
			continue;
		}else{
			pfd->dat[i].prm.wait_cnt = 0;
		}

		for( j=0; j<16; j++ ){
			if( ReqBitCheck( pfd->dat[i].prm.fade_bit, j ) == FALSE ){
				continue;
			}
			FadeWorkSet(
				&pfd->dat[i].def_wk[j<<4],
				&pfd->dat[i].trans_wk[j<<4],
				&pfd->dat[i].prm, 16 );
		}

		FadeParamCheck(pfd, i, &pfd->dat[i].prm );
*/
		PaletteFade( pfd, i, NORMAL_COLOR_NUM );

	}
}

//--------------------------------------------------------------------------------------------
/**
 * 拡張パレットのフェード計算
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ExtraPaletteFade(PALETTE_FADE_PTR pfd)
{
	u8	i, j;

	for( i=NORMAL_PALETTE_SIZE; i<ALL_PALETTE_SIZE; i++ ){
/*
		if( ReqBitCheck( pfd->req_bit, i ) == FALSE ){
			continue;
		}

		if( pfd->dat[i].prm.wait_cnt < pfd->dat[i].prm.wait ){
			pfd->dat[i].prm.wait_cnt++;
			continue;
		}else{
			pfd->dat[i].prm.wait_cnt = 0;
		}

		for( j=0; j<16; j++ ){
			if( ReqBitCheck( pfd->dat[i].prm.fade_bit, j ) == FALSE ){
				continue;
			}
			FadeWorkSet(
				&pfd->dat[i].def_wk[j<<8],
				&pfd->dat[i].trans_wk[j<<8],
				&pfd->dat[i].prm, 256 );
		}

		FadeParamCheck(pfd, i, &pfd->dat[i].prm );
*/
		PaletteFade( pfd, i, EXTRA_COLOR_NUM );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレットのフェード計算
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	id		パレットID
 * @param	siz		カラー個数 ( 通常 = 16, 拡張 = 256 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFade( PALETTE_FADE_PTR pfd, u16 id, u16 siz )
{
	if( ReqBitCheck( pfd->req_bit, id ) == FALSE ){
		return;
	}

	if( pfd->dat[id].prm.wait_cnt < pfd->dat[id].prm.wait ){
		pfd->dat[id].prm.wait_cnt++;
		return;
	}else{
		pfd->dat[id].prm.wait_cnt = 0;
	}

	PaletteFadeMain( pfd, id, siz );
}

//--------------------------------------------------------------------------------------------
/**
 * パレットのフェード計算メイン
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	id		パレットID
 * @param	siz		カラー個数 ( 通常 = 16, 拡張 = 256 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFadeMain( PALETTE_FADE_PTR pfd, u16 id, u16 siz )
{
	u32	i;

	for( i=0; i<16; i++ ){
		if( ReqBitCheck( pfd->dat[id].prm.fade_bit, i ) == FALSE ){
			continue;
		}
		FadeWorkSet(
			&pfd->dat[id].def_wk[i*siz],
			&pfd->dat[id].trans_wk[i*siz],
			&pfd->dat[id].prm, siz );
	}
	FadeParamCheck( pfd, id, &pfd->dat[id].prm );
}


//--------------------------------------------------------------------------------------------
/**
 * カラー計算
 *
 * @param	def		元パレットデータ
 * @param	trans	計算後のパレットデータ
 * @param	wk		フェードパラメータ
 * @param	siz		計算サイズ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeWorkSet( u16 * def, u16 * trans, FADE_REQ_PARAM * wk, u32 siz )
{
	u32	i;
	u8	red, green, blue;

	for( i=0; i<siz; i++ ){
		red   =
			FADE_CHANGE( (def[i]&0x1f), (wk->next_rgb&0x1f), wk->now_evy );
		green =
			FADE_CHANGE( ((def[i]>>5)&0x1f), ((wk->next_rgb>>5)&0x1f), wk->now_evy );
		blue  =
			FADE_CHANGE( ((def[i]>>10)&0x1f), ((wk->next_rgb>>10)&0x1f), wk->now_evy );

		trans[i] = ( blue << 10 ) | ( green << 5 ) | red;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * フェードの進行状況を監視
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 * @param	id		フェードデータ番号
 * @param	wk		フェードパラメータ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeParamCheck(PALETTE_FADE_PTR pfd, u8 id, FADE_REQ_PARAM * wk )
{
	s16	tmp;

	if( wk->now_evy == wk->end_evy ){
		if( ( pfd->req_bit & ( 1 << id ) ) != 0 ){
			pfd->req_bit ^= ( 1 << id );
		}
	}else if( wk->direction == 0 ){
		tmp = wk->now_evy;
		tmp += wk->fade_value;
		if( tmp > wk->end_evy ){
			tmp = wk->end_evy;
		}
		wk->now_evy = tmp;
	}else{
		tmp = wk->now_evy;
		tmp -= wk->fade_value;
		if( tmp < wk->end_evy ){
			tmp = wk->end_evy;
		}
		wk->now_evy = tmp;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレット転送
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 *
 * @return	none
 *
 * @li	VBlank内で呼ぶこと
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeTrans(PALETTE_FADE_PTR pfd)
{
	if( pfd->auto_trans == FALSE && pfd->req_flg != 1 ){ return; }

	{
		int	i;

		for( i=0; i<ALL_PALETTE_SIZE; i++ ){
			if(pfd->auto_trans == FALSE){
				if(pfd->dat[i].trans_wk == NULL || ReqBitCheck( pfd->trans_bit, i ) == FALSE){
					continue;
				}
			}

			DC_FlushRange( (void*)pfd->dat[i].trans_wk, pfd->dat[i].siz );
			switch( i ){
			case FADE_MAIN_BG:
				GX_LoadBGPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_SUB_BG:
				GXS_LoadBGPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_MAIN_OBJ:
				GX_LoadOBJPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_SUB_OBJ:
				GXS_LoadOBJPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_MAIN_BG_EX0:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT0_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX1:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT1_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX2:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT2_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX3:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT3_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX0:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT0_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX1:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT1_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX2:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT2_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX3:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT3_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_OBJ_EX:
				GX_BeginLoadOBJExtPltt();
				GX_LoadOBJExtPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				GX_EndLoadOBJExtPltt();
				break;
			case FADE_SUB_OBJ_EX:
				GXS_BeginLoadOBJExtPltt();
				GXS_LoadOBJExtPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				GXS_EndLoadOBJExtPltt();
			}
		}
	}

	pfd->trans_bit = pfd->req_bit;
	if( pfd->trans_bit == 0 ){
		pfd->req_flg = 0;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * 終了チェック
 *
 * @param   pfd		パレットフェードシステムワークへのポインタ
 *
 * @retval	"0 = 終了"
 * @retval	"0 != 処理中"
 */
//--------------------------------------------------------------------------------------------
u16 PaletteFadeCheck(PALETTE_FADE_PTR pfd)
{
	return pfd->req_bit;
}

//--------------------------------------------------------------
/**
 * @brief   自動転送フラグをセットする
 *
 * @param   pfd			パレットフェードシステムワークへのポインタ
 * @param   on_off		TRUE:自動転送ON。　FALSE:自動転送OFF
 */
//--------------------------------------------------------------
void PaletteTrans_AutoSet(PALETTE_FADE_PTR pfd, int on_off)
{
	pfd->auto_trans = on_off;
}


void PaletteTransSwitch(PALETTE_FADE_PTR pfd, u8 flag)
{
	pfd->req_flg = flag & 0x01;
	pfd->req_bit = 0xFFFFFFFF;
}



//--------------------------------------------------------------------------------------------
/**
 * 指定パレット全体をクリア
 *
 * @param	bit		クリアするパレット
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteAreaClear( u16 bit, u32 heap )
{
	void * buf;

	buf = (u8 *)sys_AllocMemory( heap, FADE_PAL_ALL_SIZE );
	memset( buf, 0, FADE_PAL_ALL_SIZE );
	DC_FlushRange( (void*)buf, FADE_PAL_ALL_SIZE );

	if( bit & PF_BIT_MAIN_BG ){
		GX_LoadBGPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_SUB_BG ){
		GXS_LoadBGPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_MAIN_OBJ ){
		GX_LoadOBJPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_SUB_OBJ ){
		GXS_LoadOBJPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}

	sys_FreeMemory( heap, buf );

	buf = (u8 *)sys_AllocMemory( heap, FADE_EXPAL_ALL_SIZE );
	memset( buf, 0, FADE_EXPAL_ALL_SIZE );
	DC_FlushRange( (void*)buf, FADE_EXPAL_ALL_SIZE );

	if( bit & PF_BIT_MAIN_BG_EX0 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT0_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX1 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT1_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX2 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT2_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX3 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT3_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX0 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT0_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX1 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT1_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX2 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT2_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX3 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT3_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}

	if( bit & PF_BIT_MAIN_OBJ_EX ){
		GX_BeginLoadOBJExtPltt();
		GX_LoadOBJExtPltt( (const void *)buf, 0, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadOBJExtPltt();
	}

	if( bit & PF_BIT_SUB_OBJ_EX ){
		GXS_BeginLoadOBJExtPltt();
		GXS_LoadOBJExtPltt( (const void *)buf, 0, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadOBJExtPltt();
	}

	sys_FreeMemory( heap, buf );
}

//--------------------------------------------------------------
/**
 * @brief   パレットワークを指定コードでクリアする
 *
 * @param   pfd				パレットフェードシステムへのポインタ
 * @param   req				リクエストデータ番号
 * @param   select			バッファ指定
 * @param   clear_code		クリアコード
 * @param   start			開始位置(カラー位置)
 * @param   end				終了位置(カラー位置　※終了位置のカラーは書き換えません。)
 *
 * start=0, end=16 とするとパレット1本まるまるクリア対象になります。
 * start=0, end=15 とすると、パレットの最後のカラーは対象に含まれません。
 */
//--------------------------------------------------------------
void PaletteWork_Clear(PALETTE_FADE_PTR pfd, FADEREQ req, FADEBUF select, 
	u16 clear_code, u16 start, u16 end)
{
	GF_ASSERT(end * sizeof(u16) <= pfd->dat[req].siz);

	if(select == FADEBUF_SRC || select == FADEBUF_ALL){
		MI_CpuFill16(&pfd->dat[req].def_wk[start], clear_code, (end - start) * 2);
	}
	if(select == FADEBUF_TRANS || select == FADEBUF_ALL){
		MI_CpuFill16(&pfd->dat[req].trans_wk[start], clear_code, (end - start) * 2);
	}
}

//--------------------------------------------------------------
/**
 * @brief   指定位置のカラーデータをパレットワークから取得する
 *
 * @param   pfd				パレットフェードシステムへのポインタ
 * @param   req				リクエストデータ番号
 * @param   select			バッファ指定
 * @param   color_pos		取得するカラーの位置
 *
 * @retval  カラーデータ
 */
//--------------------------------------------------------------
u16 PaletteWork_ColorGet(PALETTE_FADE_PTR pfd, FADEREQ req, FADEBUF select, u16 color_pos)
{
	if(select == FADEBUF_SRC){
		return pfd->dat[req].def_wk[color_pos];
	}
	if(select == FADEBUF_TRANS){
		return pfd->dat[req].trans_wk[color_pos];
	}

	GF_ASSERT(0 && "バッファ指定が間違っています\n");
	return 0;
}




//==============================================================================
//	個別ツール
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ソフトフェードイン、アウト
 *
 * @param   src			元パレットデータへのポインタ
 * @param   dest		変更データ代入先
 * @param   col_num		変更するカラー数
 * @param   evy			係数(0～16) (変更の度合い、0(元の色)～2,3..(中間色)～16(指定した色)
 * @param   next_rgb	変更後の色を指定
 */
//--------------------------------------------------------------
void SoftFade(const u16 *src, u16 *dest, u16 col_num, u8 evy, u16 next_rgb)
{
	u16 i;
	int red, green, blue;
	int next_red, next_green, next_blue;
	
	next_red = ((PLTT_DATA*)&next_rgb)->Red;
	next_green = ((PLTT_DATA*)&next_rgb)->Green;
	next_blue = ((PLTT_DATA*)&next_rgb)->Blue;
	
	for(i = 0; i < col_num; i++){
		red = ((PLTT_DATA*)&src[i])->Red;
		green = ((PLTT_DATA*)&src[i])->Green;
		blue = ((PLTT_DATA*)&src[i])->Blue;
	
		dest[i] = 
			FADE_CHANGE(red, next_red, evy) |
			(FADE_CHANGE(green, next_green, evy) << 5) |
			(FADE_CHANGE(blue, next_blue, evy) << 10);
	}
}

//--------------------------------------------------------------
/**
 * @brief   PFDを引数としたカラー加減算
 *
 * @param   pfd				パレットフェードシステムへのポインタ
 * @param   req				リクエストデータ番号
 * @param   start_pos		ソフトフェード開始位置(カラー単位)
 * @param   col_num			start_posから何個のカラーを加減算対象とするか(カラー単位)
 * @param   evy				EVY値
 * @param   next_rgb		変更後の色
 */
//--------------------------------------------------------------
void SoftFadePfd(PALETTE_FADE_PTR pfd, FADEREQ req, u16 start_pos, u16 col_num, 
	u8 evy, u16 next_rgb)
{
	GF_ASSERT(pfd->dat[req].def_wk != NULL && pfd->dat[req].trans_wk != NULL);
	
	SoftFade(&pfd->dat[req].def_wk[start_pos], &pfd->dat[req].trans_wk[start_pos], 
		col_num, evy, next_rgb);
}

//--------------------------------------------------------------
/**
 * @brief   カラー加減算(ビット指定：パレット単位)
 *
 * @param   src				元パレットデータへのポインタ
 * @param   dest			変更データ代入先
 * @param   fade_bit		加減算対象のビット
 * @param   evy				EVY値
 * @param   next_rgb		変更後の色
 */
//--------------------------------------------------------------
void ColorConceChange(const u16 *src, u16 *dest, u16 fade_bit, u8 evy, u16 next_rgb)
{
	int offset = 0;
	
	while(fade_bit){
		if(fade_bit & 1){
			SoftFade(&src[offset], &dest[offset], 16, evy, next_rgb);
		}
		fade_bit >>= 1;
		offset += 16;
	}
}

//--------------------------------------------------------------
/**
 * @brief   PFDを引数としたカラー加減算(ビット指定：パレット単位)
 *
 * @param   pfd				パレットフェードシステムへのポインタ
 * @param   req				リクエストデータ番号
 * @param   fade_bit		加減算対象のビット
 * @param   evy				EVY値
 * @param   next_rgb		変更後の色
 */
//--------------------------------------------------------------
void ColorConceChangePfd(PALETTE_FADE_PTR pfd, FADEREQ req, u16 fade_bit, u8 evy, u16 next_rgb)
{
	int offset = 0;
	
	GF_ASSERT(pfd->dat[req].def_wk != NULL && pfd->dat[req].trans_wk != NULL);
	
	while(fade_bit){
		if(fade_bit & 1){
			SoftFadePfd(pfd, req, offset, 16, evy, next_rgb);
		}
		fade_bit >>= 1;
		offset += 16;
	}
}

// =============================================================================
//
//
//	■カラー操作関数郡  add goto
//
//
// =============================================================================
#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)
#define COL_FIL(c, p)	((u16)((p)*(c))>>8)

//--------------------------------------------------------------
/**
 * @brief	グレースケール化
 *
 * @param	pal				変更対象パレットデータ
 * @param	pal_size		変更サイズ(何色変更するか)
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PaletteGrayScale(u16* pal, int pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}


//--------------------------------------------------------------
/**
 * @brief	グレースケールから、RGBの比率をかける
 *
 * @param	pal	
 * @param	pal_size	
 * @param	rp	
 * @param	gp	
 * @param	bp	
 *
 * @retval	none
 *
 *		 r = g = b = 256 でグレースケール関数と同じ動作
 *
 */
//--------------------------------------------------------------
void PaletteColorChange(u16* pal, int pal_size, int rp, int gp, int bp)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);
		
		r = COL_FIL(c, rp);
		g = COL_FIL(c, gp);
		b = COL_FIL(c, bp);

		if (r > 31){ r = 31; }
		if (g > 31){ g = 31; }
		if (b > 31){ b = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}	
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのパレットを変換して転送
 *
 * @param	pfd			
 * @param	fileIdx	
 * @param	dataIdx	
 * @param	heap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PokeColorChange(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
					 FADEREQ req, u32 trans_size, u16 pos, int r, int g, int b)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	//PaletteGrayScale(pal_data->pRawData, 16);
	PaletteColorChange(pal_data->pRawData, 16, r,g,b);

	PaletteWorkSet(pfd, pal_data->pRawData, req, pos, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}




































//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
#if 0

//=========================================================================
/**
 *	@file	palanm.c
 *	@brief	パレットアニメ・フェードアウト、イン
 *	@author	2004 Game Freak Inc.
 *	@date	04.03.08
 */
//=========================================================================

#include "common.h"
#include "palanm.h"
#include "softfade.h"
#include "ef_tool.h"
#include "decord.h"
#include "task.h"

//----------------------------------------------------------
//	プロトタイプ宣言	関数＆ﾃﾞｰﾀ
//----------------------------------------------------------
u8 AddPalAnm(const PalAnmData *pAnmDat, u16 pal_no);
u8 PaletteAnime(void);
static void PaletteAnimeEndCheck(PalAnmWorkData *paw);
void DelPalAnm(u16 id_no);
void PalAnmInitWork(u8 pal_anm_no);
void PaletteAnimeInit(void);
void PalAnmPause(u16 id_no);
void PalAnmMove(u16 id_no);
u8 PalAnmGetWorkNumber(u16 id_no);
void PaletteFadeTrans( void );
void PlttCopy(void);
void PaletteAnimeBeforeAfter(u8 trans_type, u32 *PalAnmBit);
static void PaletteAnimeSub(PalAnmWorkData *paw, u32*);
u8 ColorAddSub(void);
static void FadeCheck(PalAnmWorkData *paw, u32 *PalAnmBit);
void FadeWorkInit(void);
u8 LightColorAddSub(void);
static u8 HardColorCalc(void);
static void HardColorRegisterSet(void);
static u8 FadeEndWaitCheck(void);
void LightFadeReqAdj(u8 fade_type, u8 fade_value);
static void LightFadeCommon(u8 fade_type);

//----------------------------------------------------------
//	グローバル変数
//----------------------------------------------------------
u16 PaletteWork[0x200] = {};			//ｵﾘｼﾞﾅﾙ　　BG&OBJﾊﾟﾚｯﾄﾊﾞｯｸｱｯﾌﾟ
u16 PaletteWorkTrans[0x200] = {};		//転送用
PalAnmWorkData PalAnmWork[PAL_ANM_MAX] = {};	//パレットアニメ用ﾜｰｸ
PlttFadeData FadeData = {};				//ﾌｪｰﾄﾞｱｳﾄ、ｲﾝ用構造体
u32 PalAnmFadeBit = 0;	//ﾊﾟﾚｯﾄｱﾆﾒ、ﾌｪｰﾄﾞｲﾝ、ｱｳﾄさせるﾊﾟﾚｯﾄ 各ﾋﾞｯﾄがﾊﾟﾚｯﾄNoに対応

//デバッグ 2002.09.12 TETSU
u16 PaletteWorkTmp[0x200] = {};			//展開テンポラリワーク
//デバッグ
//
//----------------------------------------------------------
//	データ
//----------------------------------------------------------
const PalAnmData DmmyPalAnmDat = 
{
	65535,			//id_no
	0, //*PalData		転送するｶﾗｰﾊﾟﾚｯﾄｱﾄﾞﾚｽ
	PA_BEFORE,      //type			BEFORE:ｶﾗｰ加減算対象　　AFTER:ｶﾗｰ加減算非対象
	PA_BG0+PA_COL0, //pal_no		0～511
	0,              //TransValue	col_noから いくつまでのﾊﾟﾚｯﾄを対象とするか
	0,              //TransWaitDef	次のﾊﾟﾚｯﾄｱﾆﾒに移るまでのｳｪｲﾄ
	0,              //TransValueLoopDef	何回転送を繰り返すか
	PA_END,         //PalAnmSeq		ｱﾆﾒ終了後の処理
	0,             //LoopWaitDef
};




//=========================================================================
//	パレットワークに圧縮されたパレットデータをセット
// 引数:*SrcAdrs = 圧縮されているﾃﾞｰﾀｱﾄﾞﾚｽ
// 		pal_no = 展開する場所  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...等
//		size = ﾊﾞｲﾄｻｲｽﾞ
//=========================================================================
void DecordPaletteWork(void *SrcAdrs, u16 pal_no, u16 size)
{
#if 0
	DecordWram(SrcAdrs, &PaletteWork[pal_no]);
	CpuCopy(&PaletteWork[pal_no], &PaletteWorkTrans[pal_no], size, 16);
#else
	DecordWram(SrcAdrs, &PaletteWorkTmp[0x0000]);
	CpuCopy(&PaletteWorkTmp[0x0000], &PaletteWork[pal_no], size, 16);
	CpuCopy(&PaletteWorkTmp[0x0000], &PaletteWorkTrans[pal_no], size, 16);
#endif
}
//=========================================================================
//	パレットワークに非圧縮のパレットデータをセット
// 引数:*SrcAdrs = 圧縮されているﾃﾞｰﾀｱﾄﾞﾚｽ
// 		pal_no = 展開する場所  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...等
//		size = ﾊﾞｲﾄｻｲｽﾞ
//=========================================================================
void PaletteWorkSet(const u16 *pal_data, u16 pal_no, u16 size)
{
	CpuCopy(pal_data, &PaletteWork[pal_no], size, 16);
	CpuCopy(pal_data, &PaletteWorkTrans[pal_no],size, 16);
}

//=========================================================================
//	パレットワークを指定データでクリアする
// 引数: clear_data = このデータで領域を埋めます。
//		pal_no = ｸﾘｱｰする場所  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...等
//		size = ﾊﾞｲﾄｻｲｽﾞ
//=========================================================================
void PaletteWorkClear(u16 clear_data, u16 pal_no, u16 size)
{
	CpuClear(clear_data, &PaletteWork[pal_no], size, 16);
	CpuClear(clear_data, &PaletteWorkTrans[pal_no], size, 16);
}

/*----------------------------------------------------------*/
/*	Vブランク中の処理										*/
/*	(Vブランク中に常にコールしてください）					*/
/*----------------------------------------------------------*/
void PaletteFadeTrans( void )
{
	if(FadeData.trans_stop == 1)
		return;
	
	DIV_DMACOPY(3, PaletteWorkTrans, PLTT, PLTT_SIZE, 16);
	PalAnmFadeBit = 0;
	if(FadeData.type == 2 && FadeData.fade_sw)
		HardColorRegisterSet();
}
=======
>>>>>>> 1.6

<<<<<<< palanm.c
//=========================================================================
//	パレットアニメ		  ※ﾒｲﾝﾙｰﾌﾟ内で呼んでください
// 戻り値: 0=ﾌｪｰﾄﾞﾘｸｴｽﾄがかかってない、又はﾘｸｴｽﾄが終了した
//         1=ﾌｪｰﾄﾞ実行中
//         2=ﾌｪｰﾄﾞﾘｸｴｽﾄはかかっているがｳｪｲﾄ中なので(ﾌｪｰﾄﾞの)処理はしなかった
//      0xff=前回のﾘｸｴｽﾄﾃﾞｰﾀがまだ転送されていない
//=========================================================================
u8 PaletteAnime(void)
{
	u8 temp;
	u32 PalAnmBit = 0;
	
	if(PalAnmFadeBit != 0)
		return 0xff;
	
	if(FadeData.type == 0)
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = ColorAddSub();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	else if(FadeData.type == 1)
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = LightColorAddSub();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	else
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = HardColorCalc();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	
	PalAnmFadeBit = PalAnmBit | FadeData.fade_bit;
	return temp;
}
//----------------------------------------------------------
//	ﾊﾟﾚｯﾄｱﾆﾒﾜｰｸ&ﾌｪｰﾄﾞﾘｸｴｽﾄ用ﾜｰｸ全初期化
//----------------------------------------------------------
void PaletteAnimeInit(void)
=======
void PaletteTransSwitch(u8 flag)
>>>>>>> 1.6
{
<<<<<<< palanm.c
	u8 i;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		PalAnmInitWork(i);
	}
	FadeWorkInit();
}
//----------------------------------------------------------
//	PLTT_VRAMのﾃﾞｰﾀを全てPaletteWorkにｺﾋﾟｰ
//----------------------------------------------------------
void PlttCopy(void)
{
	u16 i;
	u16 *dest;
	
	dest = (u16 *)PLTT;
	
	for(i = 0; i < 0x200; i++)
	{
		PaletteWork[i] = dest[i];
		PaletteWorkTrans[i] = dest[i];
	}
=======
	FadeData.req_flg = flag & 0x01;
	FadeData.req_bit = 0xFFFFFFFF;
>>>>>>> 1.6
}

<<<<<<< palanm.c
//----------------------------------------------------------
//	パレット加減算リクエスト  ※ﾘｸｴｽﾄが重なった場合は先勝ちです
//
// fade_bit : パレットを指定（各ビットがパレット番号に対応
//			  ビット0 = BGの0パレット、 Bit16 = OBJの0パレット)
// wait : 値を大きくするとゆっくりﾌｪｰﾄﾞｱｳﾄ、ｲﾝします。
//		  値を小さくすると早くﾌｪｰﾄﾞｱｳﾄ、ｲﾝします。
// start_evy : 最初の色の濃度を指定します(0～16)
// 			   0(元の色)～2,3..(中間色)～16(指定した色)
// end_evy : ﾌｪｰﾄﾞ計算後の最終的な色の濃度を指定します。引数の値は↑と同じです
// next_rgb : 変更後の色を指定
//
// 戻り値: 1=正常終了  0=ｴﾗｰ
//----------------------------------------------------------
u8 PaletteFadeReq(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb)
{
	u8 temp;
	
	if(FadeData.fade_sw == 1)
		return 0;
	
	FadeData.fade_value = 2;
	if(wait < 0){	//waitがﾏｲﾅｽの時はvalueを大きくしてﾌｪｰﾄﾞを早くする
		FadeData.fade_value += abs(wait);
		wait = 0;
	}
	
	FadeData.fade_bit = fade_bit;
	FadeData.wait = wait;			//初回はﾘｸｴｽﾄかけた瞬間に実行
	FadeData.wait_def = wait;
	FadeData.now_evy = start_evy;
	FadeData.end_evy = end_evy;
	FadeData.next_rgb = next_rgb;
	FadeData.fade_sw = 1;
	FadeData.type = 0;
	if(start_evy < end_evy)
		FadeData.direction = 0;
	else
		FadeData.direction = 1;
	
	PaletteAnime();		//add 2001.06.26(火) ﾘｸｴｽﾄしてすぐに反映させるよう変更
	
	temp = FadeData.trans_stop;
	FadeData.trans_stop = 0;

	//PaletteFadeTrans();	//add 2001.06.26(火)
	CpuCopy(PaletteWorkTrans, PLTT, PLTT_SIZE, 32);
	PalAnmFadeBit = 0;
	if(FadeData.type == 2 && FadeData.fade_sw)
		HardColorRegisterSet();
	
	FadeData.trans_stop = temp;
	
	return 1;
}

u8 PaletteFadeReq2(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb)
{
	u8 temp;
	
	PlttCopy();
	temp = PaletteFadeReq(fade_bit, wait, start_evy, end_evy, next_rgb);
	return temp;
}

//=========================================================================
//	パレットアニメ メイン
//=========================================================================
void PaletteAnimeBeforeAfter(u8 trans_type, u32 *PalAnmBit)
{
	u8 i;
	PalAnmWorkData *paw;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		paw = &PalAnmWork[i];

		if(paw->pal_sw == 0 || paw->PalAnmDat->type != trans_type)
			continue;
		
		if(paw->TransValueLoop == paw->PalAnmDat->TransValueLoopDef)
		{
			PaletteAnimeEndCheck(paw);
			if(paw->pal_sw == 0)	//↑のEndCheckでDelされた時のため
				continue;
		}

		if(paw->TransWait == 0)
		{
			PaletteAnimeSub(paw, PalAnmBit);
		}
		else
		{
			paw->TransWait--;
		}
		
		FadeCheck(paw, PalAnmBit);
	}
}

//----------------------------------------------------------
//	パレットアニメ ｳｪｲﾄをﾁｪｯｸしてﾜｰｸへ転送
//----------------------------------------------------------
static void PaletteAnimeSub(PalAnmWorkData *paw, u32 *PalAnmBit)
{
	u8 trans_value = 0;
	u16 now_pal;
	
	now_pal = paw->TransValueLoop * paw->PalAnmDat->TransValue;
	
	if(paw->PalAnmDat->type == PA_BEFORE)
	{
		while(trans_value < paw->PalAnmDat->TransValue)
		{
			PaletteWork[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			PaletteWorkTrans[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			trans_value++;
			paw->pal_no++;
			now_pal++;
		}
	}
	else	//PA_AFTER
	{
		while(trans_value < paw->PalAnmDat->TransValue)
		{
			PaletteWorkTrans[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			trans_value++;
			paw->pal_no++;
			now_pal++;
		}
	}
	
	paw->pal_no = paw->pal_no_def;
	paw->TransWait = paw->PalAnmDat->TransWaitDef;
	
	//if(paw->TransValueLoop < paw->PalAnmDat->TransValueLoopDef)
		paw->TransValueLoop++;
	//else
	if(paw->TransValueLoop >= paw->PalAnmDat->TransValueLoopDef)
	{
		if(paw->LoopWait)
			paw->LoopWait--;
		paw->TransValueLoop = 0;
	}
	
	*PalAnmBit |= GET_PALNO_BIT(paw->pal_no_def);
//	BIT_SET(*PalAnmBit, paw->pal_no_def >> 4);	//変更したﾊﾟﾚｯﾄのﾋﾞｯﾄをｾｯﾄ
}

//----------------------------------------------------------
//	ﾌｪｰﾄﾞとﾊﾟﾚｯﾄｱﾆﾒが同時に動くときの加減算補正
//----------------------------------------------------------
static void FadeCheck(PalAnmWorkData *paw, u32 *PalAnmBit)
{
	u8 i;
	u16 now_pal;
	
	if(FadeData.fade_sw == 0 
		|| ((GET_PALNO_BIT(paw->pal_no_def) & FadeData.fade_bit) == 0))
	{
		return;
	}
	
	if(paw->PalAnmDat->type == PA_BEFORE)
	{
		if(FadeData.wait == FadeData.wait_def)
			return;		//ﾌｪｰﾄﾞで勝手に減色されるのでOK
		
		//ﾌｪｰﾄﾞがｳｪｲﾄで実行されないのでここでやる
		SoftFade(paw->pal_no_def, paw->PalAnmDat->TransValue,
				FadeData.now_evy, FadeData.next_rgb);
	}
	else	//PA_AFTER
	{
		if(FadeData.wait > 0)
			return;		//ﾌｪｰﾄﾞが実行されないので減色されない
		
		if(paw->TransWait == paw->PalAnmDat->TransWaitDef)
			return;		//ﾃﾞｰﾀが転送されたのでOK
		
		//ﾌｪｰﾄﾞで減色されてしまっているので転送しなおす
		now_pal = paw->TransValueLoop * paw->PalAnmDat->TransValue;
		for(i = 0; i < paw->PalAnmDat->TransValue; i++)
		{
			PaletteWorkTrans[paw->pal_no_def+i] = paw->PalAnmDat->PalData[now_pal+i];
			//now_pal++;
		}
	}
}

//----------------------------------------------------------
//	全てのﾙｰﾌﾟ処理が終わった後の処理
//----------------------------------------------------------
static void PaletteAnimeEndCheck(PalAnmWorkData *paw)
{
	if(paw->LoopWait == 0)
	{
		switch(paw->PalAnmDat->PalAnmSeq)
		{
			case PA_LOOP:
				paw->TransValueLoop = 0;
				paw->TransWait = paw->PalAnmDat->TransWaitDef;
				paw->LoopWait = paw->PalAnmDat->LoopWaitDef;
				paw->pal_no = paw->pal_no_def;
				break;
			case PA_OUFUKU:
			case PA_END:
				DelPalAnm(paw->PalAnmDat->id_no);
				break;
			default:
		}
	}
	else
	{
		paw->LoopWait--;
	}
}
//----------------------------------------------------------
//	指定したIDのパレットアニメを削除
//----------------------------------------------------------
void DelPalAnm(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	PalAnmInitWork(i);
}
//----------------------------------------------------------
//	パレットアニメ単発初期化
//----------------------------------------------------------
void PalAnmInitWork(u8 pal_anm_no)
{
	PalAnmWork[pal_anm_no].PalAnmDat = (PalAnmData *)&DmmyPalAnmDat;
	PalAnmWork[pal_anm_no].pal_sw = 0;
	PalAnmWork[pal_anm_no].pal_no_def = 0;
	PalAnmWork[pal_anm_no].pal_no = 0;
	PalAnmWork[pal_anm_no].TransValueLoop = 0;
	PalAnmWork[pal_anm_no].pause = 0;
	PalAnmWork[pal_anm_no].TransWait = 0;
	PalAnmWork[pal_anm_no].LoopWait = 0;
}
//----------------------------------------------------------
//	ﾌｪｰﾄﾞﾘｸｴｽﾄﾜｰｸ初期化
//----------------------------------------------------------
void FadeWorkInit(void)
{
	FadeData.fade_bit = 0;
	FadeData.wait_def = 0;
	FadeData.wait = 0;
	FadeData.now_evy = 0;
	FadeData.end_evy = 0;
	FadeData.next_rgb = 0;
	FadeData.fade_sw = 0;
	FadeData.direction = 0;
	FadeData.trans_stop = 0;
	FadeData.reset_flg = 0;
	FadeData.hard_end = 0;
	FadeData.fade_end = 0;
	FadeData.end_wait = 0;
	FadeData.bg_obj = 0;
	FadeData.fade_value = 2;
}
//----------------------------------------------------------
//	指定したIDのパレットアニメを止める
// 登録されているPalAnmWorkの配列番号が分かっているなら直接いじった方が早い
//----------------------------------------------------------
void PalAnmPause(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	PalAnmWork[i].pause = 1;
}
//----------------------------------------------------------
//	指定したIDのPauseで止めていたﾊﾟﾚｯﾄｱﾆﾒを動かす
// 登録されているPalAnmWorkの配列番号が分かっているなら直接いじった方が早い
//----------------------------------------------------------
void PalAnmMove(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	
	PalAnmWork[i].pause = 0;
}
//----------------------------------------------------------
//	IDからPalAnmWorkの配列番号を出す
//----------------------------------------------------------
u8 PalAnmGetWorkNumber(u16 id_no)
{
	u8 i;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		if(PalAnmWork[i].PalAnmDat->id_no == id_no)
			return i;
	}
	return PAL_ANM_MAX;	//error
}


//----------------------------------------------------------
//	ソフトフェードイン、アウト(ﾊﾟﾚｯﾄｱﾆﾒﾙｰﾁﾝ用)
// 戻り値: 0=ﾌｪｰﾄﾞﾘｸｴｽﾄがかかってない、又はﾘｸｴｽﾄが終了した
//         1=ﾌｪｰﾄﾞ実行中
//         2=ﾌｪｰﾄﾞﾘｸｴｽﾄはかかっているがｳｪｲﾄ中なので処理はしなかった
//----------------------------------------------------------
#include "softfade.h"
u8 ColorAddSub(void)
{
	u16 offset2;
	u16 next_rgb;
	u32 fade_bit;
	s8  evy;
	
	if(FadeData.fade_sw == 0)
		return 0;
	if(FadeEndWaitCheck())
		return FadeData.fade_sw;
	
	if(FadeData.bg_obj == 0){
		if(FadeData.wait < FadeData.wait_def)
		{
			FadeData.wait++;
			return 2;
		}
		else
			FadeData.wait = 0;
	}

	offset2 = 0;
	next_rgb = FadeData.next_rgb;

	if(FadeData.bg_obj == 0)
		fade_bit = FadeData.fade_bit & 0xffff;
	else{
		fade_bit = FadeData.fade_bit >> 16;
		offset2 = 16*16;
	}
	while(fade_bit)
	{
		if(fade_bit & 1)
			SoftFade(offset2, 16, FadeData.now_evy, FadeData.next_rgb);
		fade_bit >>= 1;
		offset2 += 16;
	}
	FadeData.bg_obj ^= 1;
	if(FadeData.bg_obj)
		return FadeData.fade_sw;

	if(FadeData.now_evy == FadeData.end_evy)
	{
		FadeData.fade_bit = 0;
		//FadeData.fade_sw = 0;
		FadeData.fade_end = 1;
	}
	else if(FadeData.direction == 0)
	{
		evy = FadeData.now_evy;	//31を超えるとｵｰﾊﾞｰﾌﾛｰを起こすので
		evy += FadeData.fade_value;
		if(evy > FadeData.end_evy)
			evy = FadeData.end_evy;
		FadeData.now_evy = evy;
	}
	else
	{
		evy = FadeData.now_evy;	//ﾏｲﾅｽを取るため
		evy -= FadeData.fade_value;
		if(evy < FadeData.end_evy)
			evy = FadeData.end_evy;
		FadeData.now_evy = evy;
	}
	return FadeData.fade_sw;
}







//=========================================================================
//	カラー反転						2001.06.26(火)
// 引数:　bit = カラー反転する対象ﾊﾟﾚｯﾄ   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorReversal(u32 bit)
{
	u16 i = 0;
	u8 j;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++)
				PaletteWorkTrans[i + j] ^= 0xffff;
		}
		bit >>= 1;
		i += 16;
	}
}

//=========================================================================
//	カラー加算						2001.06.29
// 引数:　bit = カラー加算する対象ﾊﾟﾚｯﾄ   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorRandomPlus(u32 bit,s8 red,s8 green, s8 blue)
{
	u16 i = 0;
	u8 j;
	PlttData *p;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++){
				p = (PlttData*)&(PaletteWorkTrans[i + j]);
				p->Red+=red;
				p->Green+=green;
				p->Blue+=blue;
			}
		}
		bit >>= 1;
		i += 16;
	}
}

//=========================================================================
//	カラー加算の後始末					2001.06.29
// 引数:　bit = 戻す対象ﾊﾟﾚｯﾄ   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorRandomPlusEnd(u32 bit)
{
	u16 i = 0;
	u8 j;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++)
				PaletteWorkTrans[i + j] = PaletteWork[i+j];
		}
		bit >>= 1;
		i += 16;
	}
}


//=========================================================================
//	黒と白のみに用途をしぼった高速フェード関数
// fade_type = どのﾌｪｰﾄﾞを行うか
//			   W_to_N:白→ﾉｰﾏﾙ  N_to_W:ﾉｰﾏﾙ→白  B_to_N:黒→ﾉｰﾏﾙ  N_to_B:ﾉｰﾏﾙ→黒
//=========================================================================
void LightFadeReq(u8 fade_type)
{
	FadeData.fade_value = 2;
	LightFadeCommon(fade_type);
}

//----------------------------------------------------------
//	LightFadeReq, LightFadeReqSync共通処理
//----------------------------------------------------------
static void LightFadeCommon(u8 fade_type)
{
	FadeData.now_evy = 31;
	FadeData.wait_def = fade_type;
	FadeData.fade_sw = 1;
	FadeData.type = 1;
	
	if(fade_type == B_to_N)
		CpuArrayClear(0, PaletteWorkTrans, 16)
	if(fade_type == W_to_N)
		CpuArrayClear(0x7fff, PaletteWorkTrans, 16);
	PaletteAnime();		//ﾘｸｴｽﾄしてすぐに反映させるよう変更
}

//----------------------------------------------------------
//	ソフトフェードイン、アウト(ﾊﾟﾚｯﾄｱﾆﾒﾙｰﾁﾝ用)
// 戻り値: 0=ﾌｪｰﾄﾞﾘｸｴｽﾄがかかってない、又はﾘｸｴｽﾄが終了した
//         1=ﾌｪｰﾄﾞ実行中
//----------------------------------------------------------

u8 LightColorAddSub(void)
{
	u16 i;
	u16 start_pal, end_pal;
	s8 red,green,blue,t_red,t_green,t_blue;
	
	if(FadeData.fade_sw == 0)
		return 0;
	if(FadeEndWaitCheck())
		return FadeData.fade_sw;

	if(FadeData.bg_obj){
		start_pal = 0x100;
		end_pal = 0x200;
	}else{
		start_pal = 0;
		end_pal = 0x100;
	}

	switch(FadeData.wait_def)
	{
		case W_to_N:
			for(i = start_pal; i < end_pal; i++)
			{
				red = ((PlttData*)&PaletteWork[i])->Red;
				green = ((PlttData*)&PaletteWork[i])->Green;
				blue = ((PlttData*)&PaletteWork[i])->Blue;
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red-2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green-2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue-2;
				if(t_red < red)
					t_red = red;
				if(t_green < green)
					t_green = green;
				if(t_blue < blue)
					t_blue = blue;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case N_to_W:
			for(i = start_pal; i < end_pal; i++)
			{
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red+2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green+2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue+2;
				if(t_red > 31)
					t_red = 31;
				if(t_green > 31)
					t_green = 31;
				if(t_blue > 31)
					t_blue = 31;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case B_to_N:
			for(i = start_pal; i < end_pal; i++)
			{
				red = ((PlttData*)&PaletteWork[i])->Red;
				green = ((PlttData*)&PaletteWork[i])->Green;
				blue = ((PlttData*)&PaletteWork[i])->Blue;
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red+2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green+2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue+2;
				if(t_red > red)
					t_red = red;
				if(t_green > green)
					t_green = green;
				if(t_blue > blue)
					t_blue = blue;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case N_to_B:
			for(i = start_pal; i < end_pal; i++)
			{
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red-2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green-2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue-2;
				if(t_red < 0)
					t_red = 0;
				if(t_green < 0)
					t_green = 0;
				if(t_blue < 0)
					t_blue = 0;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
	}
	
	FadeData.bg_obj ^= 1;
	if(FadeData.bg_obj)
		return FadeData.fade_sw;

	if(FadeData.now_evy - FadeData.fade_value < 0)
		FadeData.now_evy = 0;
	else
		FadeData.now_evy -= FadeData.fade_value;
	if(FadeData.now_evy == 0)
	{
		switch(FadeData.wait_def)
		{	//少数切り捨ての影響で完全にその色にはならないので
			case W_to_N:
			case B_to_N:
				CpuArrayCopy(PaletteWork, PaletteWorkTrans, 32);
				break;
			case N_to_W:
				CpuArrayClear(0xffffffff, PaletteWorkTrans, 32);
				break;
			case N_to_B:
				CpuArrayClear(0, PaletteWorkTrans, 32);
				break;
		}
		FadeData.type = 0;
		//FadeData.fade_sw = 0;
		FadeData.fade_end = 1;
	}

	return FadeData.fade_sw;
}








//----------------------------------------------------------
//	ハードによるパレット加減算リクエスト
//
// fade_bit : 加減算の対象にするBG,OBJを指定(BLDCNTﾚｼﾞｽﾀの第1対象ﾋﾟｸｾﾙに設定するﾋﾞｯﾄ)
//				6,7bit:光度変更ｱｯﾌﾟ、ﾀﾞｳﾝﾋﾞｯﾄ(10:UP	 11:DOWN)
//				5bit:BD(ﾊﾞｯｸｸﾞﾗｳﾝﾄﾞ), 4bit:OBJ, 3:BG3, 2:BG2, 1:BG1, 0:BG0
//
// wait : 値を大きくするとゆっくりﾌｪｰﾄﾞｱｳﾄ、ｲﾝします (MAX:63)
// start_evy : 最初の色の濃度を指定します(0～16)
// 			   0(元の色)～2,3..(中間色)～16(黒、もしくは白)
// end_evy : 最終的な色の濃度を指定します。引数の値は↑と同じです
// reset_flg : ﾌｪｰﾄﾞ終了時にﾚｼﾞｽﾀｰの初期化をするか(0:しない  1:する)
//----------------------------------------------------------
void HardFadeReq(u8 fade_bit, u8 wait, u8 start_evy, u8 end_evy, u8 reset_flg)
{
	FadeData.fade_bit = fade_bit;
	FadeData.wait = wait;			//初回はﾘｸｴｽﾄかけた瞬間に実行
	FadeData.wait_def = wait;
	FadeData.now_evy = start_evy;
	FadeData.end_evy = end_evy;
	FadeData.fade_sw = 1;
	FadeData.type = 2;				//RegisterFade
	FadeData.reset_flg = reset_flg;
	FadeData.hard_end = 0;
	if(start_evy < end_evy)
		FadeData.direction = 0;
	else
		FadeData.direction = 1;
}

//----------------------------------------------------------
//	レジスターフェードイン、アウト(ﾊﾟﾚｯﾄｱﾆﾒﾙｰﾁﾝ用)
// 戻り値: 0=ﾌｪｰﾄﾞﾘｸｴｽﾄがかかってない、又はﾘｸｴｽﾄが終了した
//         1=ﾌｪｰﾄﾞ実行中
//         2=ﾌｪｰﾄﾞﾘｸｴｽﾄはかかっているがｳｪｲﾄ中なので処理はしなかった
//----------------------------------------------------------
static u8 HardColorCalc(void)
{
	s8  evy;
	
	if(FadeData.fade_sw == 0)
		return 0;

	if(FadeData.wait < FadeData.wait_def)
	{
		FadeData.wait++;
		return 2;
	}
	else
		FadeData.wait = 0;

	if(FadeData.direction == 0){
		FadeData.now_evy++;
		if(FadeData.now_evy > FadeData.end_evy){
			FadeData.hard_end++;
			FadeData.now_evy--;
		}
	}
	else
	{
		evy = FadeData.now_evy;	//ﾏｲﾅｽを取るため
		FadeData.now_evy--;
		evy--;
		if(evy < FadeData.end_evy){
			FadeData.hard_end++;
			FadeData.now_evy++;
		}
	}
	
	if(FadeData.hard_end){
		//FadeData.fade_sw = 0;		HardColorRegisterSet関数の中で落とすので
		//FadeData.fade_bit = 0;
		if(FadeData.reset_flg){
			FadeData.fade_bit = 0;
			FadeData.now_evy = 0;
		}
		FadeData.reset_flg = 0;
	}
	return FadeData.fade_sw;
}

static void HardColorRegisterSet(void)
{
	RegisterSet(OFFSET_REG_BLDCNT , FadeData.fade_bit);
	RegisterSet(OFFSET_REG_BLDY , FadeData.now_evy);
	if(FadeData.hard_end){
		FadeData.hard_end = 0;
		FadeData.type = 0;
		FadeData.fade_bit = 0;
		FadeData.now_evy = 0;
		FadeData.fade_sw = 0;
	}
}





//=========================================================================
//	ﾌｪｰﾄﾞ終了後、一定Syncｳｪｲﾄを入れる
//	戻り値: 0=まだﾌｪｰﾄﾞ終了してない		1=ｳｪｲﾄ中
//=========================================================================
static u8 FadeEndWaitCheck(void)
{
	if(FadeData.fade_end){
		if(FadeData.end_wait == FADE_END_WAIT){
			FadeData.fade_sw = 0;
			FadeData.fade_end = 0;
			FadeData.end_wait = 0;
		}else
			FadeData.end_wait++;
		return 1;
	}
	return 0;
}




//=========================================================================
//	指定ビットのカラーパレットを呼ばれた瞬間に指定色、指定濃度に変更する
//
// fade_bit : パレットを指定（各ビットがパレット番号に対応
//			  ビット0 = BGの0パレット、 Bit16 = OBJの0パレット)
// start_evy : 変更後の色の濃度を指定します(0～16)
// 			   0(元の色)～2,3..(中間色)～16(指定した色)
// next_rgb : 変更後の色を指定
//=========================================================================
void ColorConceChange(u32 fade_bit, u8 evy, u16 next_rgb)
{
	u16 offset = 0;
	
	while(fade_bit){
		if(fade_bit & 1)
			SoftFade(offset, 16, evy, next_rgb);
		fade_bit >>= 1;
		offset += 16;
	}
}



//=========================================================================
//	指定ビットのカラーパレットを呼ばれた瞬間に指定色、指定濃度に変更する
// ※指定されていないﾋﾞｯﾄのﾊﾟﾚｯﾄは元の色に戻ります。
// fade_bit : パレットを指定（各ビットがパレット番号に対応
//			  ビット0 = BGの0パレット、 Bit16 = OBJの0パレット)
// start_evy : 変更後の色の濃度を指定します(0～16)
// 			   0(元の色)～2,3..(中間色)～16(指定した色)
// next_rgb : 変更後の色を指定
//=========================================================================
void ColorConceChange2(u32 fade_bit, u8 evy, u16 next_rgb)
{
	DIV_DMACOPY(3, PaletteWork, PaletteWorkTrans, 0x400, 32);
	ColorConceChange(fade_bit, evy, next_rgb);
}

//===============================================
// 輝度計算マクロ
//===============================================
#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)

//--------------------------------------------------------------------------
/**
 * グレースケール
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void PalGrayScale(u16 *pal, u16 pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}
//--------------------------------------------------------------------------
/**
 * 2bitカラー風
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void Pal2BitFilter(u16 *pal, u16 pal_size)
{
	static const u8  col_tbl[32] = {
		 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
		11,11,11,11,11,16,16,16,16,16,
		21,21,21,21,21,27,27,27,27,27,
		31,31,
	};

	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		if(c > 31){
			c = 31;
		}
		c = col_tbl[c];
		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}
//--------------------------------------------------------------------------
/**
 * セピアカラー
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void PalSepiaFilter(u16 *pal, u16 pal_size)
{
	int i, r, g, b, y;

#define R_FIL(x)	( ((u16)((x)*307)>>8) )
#define G_FIL(x)	( ((u16)((x)*256)>>8) )
#define B_FIL(x)	( ((u16)((x)*240)>>8) )

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		y = RGBtoY(r,g,b);

		r = R_FIL(y);
		g = G_FIL(y);
		b = B_FIL(y);

		if(r > 31){ r = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}


#undef R_FIL
#undef G_FIL
#undef B_FIL
}

// -------------------------------------------------------------------------
/**
 * カラー変更
 *
 * @param	pal			変更するパレットのアドレス
 * @param	pal_size	何色変更するか？
 * @paran	rp			赤
 * @paran	gp			緑
 * @paran	bp			青
 *
 * @return	none
 */
// -------------------------------------------------------------------------
void PalColorFilter(u16 *pal, u16 pal_size, u16 rp, u16 gp, u16 bp)
{
	int i, r, g, b, y;

#define C_FIL(y,c)	((u16)((y)*(c))>>8)

	for(i = 0; i < pal_size; i++){
		r =  ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		y = RGBtoY(r,g,b);

		r = C_FIL(y,rp);
		g = C_FIL(y,gp);
		b = C_FIL(y,bp);

		if (r > 31){ r = 31; }
		if (g > 31){ g = 31; }
		if (b > 31){ b = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}

#undef C_FIL

}

/*====================================================================================*/
/*                                                                                    */
/*  パレットフェード並行処理                                                          */
/*                                                                                    */
/*====================================================================================*/

static void ParallelFadeTask(u8 id);

enum {
	PFWORK_EVY,
	PFWORK_EVY_END,
	PFWORK_EVY_ADD,
	PFWORK_WAIT,
	PFWORK_COUNT,
	PFWORK_FADEBIT,
	PFWORK_FADEBIT_2ND,
	PFWORK_RGB,
	PFWORK_ID,
};

//------------------------------------------------------------------------------
/**
 * 異なるパレットに並行して別々のフェードをかける（タスクセット）
 *
 * @param   fade_bit		対象パレットビット
 * @param   wait			ウェイト
 * @param   start_evy		開始evy
 * @param   end_evy			終了evy
 * @param   rgb				フェードカラー
 * @param   pri				タスクプライオリティ
 * @param   id				識別ＩＤ（呼び出し側が管理。タスクごとに違うIDを渡す）
 *
 * @retval  u8			登録したタスクのＩＤ
 *
 * fade_bit ～ rgb までのパラメータは、PaletteFadeReq と同様。
 *
 */
//------------------------------------------------------------------------------
void ParallelFadeSet(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 rgb, u8 pri, u8 id)
{
	u8 no = AddTask(ParallelFadeTask, pri);

	TaskTable[no].work[PFWORK_EVY] = start_evy;
	TaskTable[no].work[PFWORK_EVY_END] = end_evy;

	if(wait >= 0){
		TaskTable[no].work[PFWORK_WAIT] = wait;
		TaskTable[no].work[PFWORK_EVY_ADD] = 1;
	}else{
		TaskTable[no].work[PFWORK_WAIT] = 0;
		TaskTable[no].work[PFWORK_EVY_ADD] =  -(wait) + 1;
	}

	if(end_evy < start_evy){
		TaskTable[no].work[PFWORK_EVY_ADD] *= -1;
	}

	TaskStoreAdrs(no, PFWORK_FADEBIT, (void*)fade_bit);
	TaskTable[no].work[PFWORK_RGB] = (s16)rgb;
	TaskTable[no].work[PFWORK_ID] = id;

	TaskTable[no].TaskAdrs(no);
}

//------------------------------------------------------------------------------
/**
 * 並行フェード終了待ち
 *
 * @param   id			識別ＩＤ（ParallelFadeSet の引数と同じもの）
 *
 * @retval  BOOL		TRUE:継続中／FALSE:終了
 */
//------------------------------------------------------------------------------
BOOL ParallelFadeWait(u8 id)
{
	int i;
	for(i = 0; i < TASK_MAX; i++){
		if(	(TaskTable[i].occ == 1)
		&&	(TaskTable[i].TaskAdrs == ParallelFadeTask)
		&&	(TaskTable[i].work[PFWORK_ID] == id)
		){
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------------
/**
 * 並行タスクフェード全終了
 *
 * @param   none		
 *
 * @retval  none		
 */
//------------------------------------------------------------------------------
void ParallelFadeStopAll(void)
{
	u8 no = CheckTaskNo(ParallelFadeTask);
	while(no != NOT_EXIST_TASK_ID){
		DelTask(no);
		no = CheckTaskNo(ParallelFadeTask);
	}
}
/**=====================================================================
 *
 * 並行フェード実行タスク
 *
 * @param   id		
 *
 * @retval  none		
 *
 *====================================================================*/
static void ParallelFadeTask(u8 id)
{
	s16 *wk;
	u32 fade_bit;

	wk = TaskTable[id].work;
	fade_bit = (u32)TaskTakeAdrs(id, PFWORK_FADEBIT);

	wk[PFWORK_COUNT]++;
	if( wk[PFWORK_COUNT] > wk[PFWORK_WAIT] ){
		wk[PFWORK_COUNT] = 0;

		ColorConceChange(fade_bit, wk[PFWORK_EVY], (u16)(wk[PFWORK_RGB]));
		if(wk[PFWORK_EVY] == wk[PFWORK_EVY_END]){
			DelTask(id);
			return;
		}

		wk[PFWORK_EVY] += wk[PFWORK_EVY_ADD];

		if(wk[PFWORK_EVY_ADD] >= 0){
			if(wk[PFWORK_EVY] >= wk[PFWORK_EVY_END]){
				wk[PFWORK_EVY] = wk[PFWORK_EVY_END];
			}
		}else{
			if(wk[PFWORK_EVY] <= wk[PFWORK_EVY_END]){
				wk[PFWORK_EVY] = wk[PFWORK_EVY_END];
			}
		}

	}

}



#endif
