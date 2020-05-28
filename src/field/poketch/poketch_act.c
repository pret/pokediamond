//============================================================================================
/**
 * @file	poketch_act.c
 * @bfief	ポケッチ用アクター管理
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"

#include "system\arc_util.h"
#include "poketch_act.h"


/*
typedef struct NNSG2dSVec2
{
    s16     x;        
    s16     y;
    
}NNSG2dSVec2;

typedef struct NNSG2dFVec2
{
    fx32     x;        
    fx32     y;
    
}NNSG2dFVec2;
*/

/*===================================================*/
/* 定数                                              */
/*===================================================*/
enum {
	ACT_DEFAULT_WORKSIZE = 18,
	ACT_DEFWORK_MAGICNUM_SIZE = 2,
	ACT_DEFWORK_MAGICNUM = 0x3594,
};


struct _PACT {
	const NNSG2dCellDataBank*  cellbank;
	const NNSG2dAnimBankData*  anmbank;

	NNSG2dCellAnimation        cellanm;

	struct _PACT* next;
	struct _PACT* prev;

	NNSG2dFVec2   pos;
	MtxFx22*      affine;
	MtxFx22       affine_body;

	union {
		struct {
			u16 oampri;
			u16 bgpri;
		};
		u32 pri;
	};

	u16           pal_offset;
	u8            vanish;
	u8            affine_flag;

	u16           char_offset;
	u8            h_flip;
	u8            v_flip;

	u16           rotate;
	u8            mosaic;

};

struct _PACTSYS {
	NNSG2dOamManagerInstance*    oamm;


	PACT**         act_stack;
	PACT*          act_top;
	PACT*          act;
	u16            act_max;
	u16            act_stack_p;

	GXOamAttr*     oam;

	u32    heap_type;
};

//==============================================================
// Prototype
//==============================================================
static void ActAllInit( PACT** stack, PACT* acts, u32 numact );
static void ActClear( PACT* act );
static PACT* ActPop( PACTSYS* actsys );
static void ActPush( PACTSYS* actsys, PACT* act );
static void ActChain( PACTSYS* actsys, PACT *act );
static void ActUnchain( PACTSYS* actsys, PACT* act );




//------------------------------------------------------------------
/**
 * システム初期化
 *
 * @param   oamm		システムが使うOAMﾏﾈｰｼﾞｬ
 * @param   heap		ワーク領域確保に使って良いヒープ種類
 *
 * @retval  PACTSYS*	システムワークポインタ
 */
//------------------------------------------------------------------
PACTSYS* PACT_SysCreate( NNSG2dOamManagerInstance* oamm, u32 heap)
{
	PACTSYS* actsys;
	BOOL  succeed = FALSE;

	do {
		actsys = sys_AllocMemory( heap, sizeof(PACTSYS) );
		if( actsys == NULL ){ break; }

		actsys->oam = NULL;
		actsys->act = NULL;
		actsys->act_stack = NULL;

		actsys->oamm = oamm;
		actsys->heap_type = heap;


		actsys->act_max = NNS_G2dGetOamManagerOamCapacity( oamm );

		actsys->oam = sys_AllocMemory( heap, sizeof(GXOamAttr) * actsys->act_max );
		if(actsys->oam == NULL){ break; }

		actsys->act = sys_AllocMemory( heap, sizeof(PACT) * actsys->act_max );
		if( actsys->act == NULL ){ break; }

		actsys->act_stack = sys_AllocMemory( heap, sizeof(PACT*) * actsys->act_max );
		if( actsys->act_stack == NULL ){ break; }

		ActAllInit( actsys->act_stack, actsys->act, actsys->act_max );
		actsys->act_stack_p = 0;
		actsys->act_top = NULL;


		succeed = TRUE;

	}while(0);

	if( succeed == FALSE )
	{
		OS_Printf("poketch actsys initialize failed\n");
		if(actsys != NULL)
		{
			if( actsys->oam != NULL ){
				sys_FreeMemory( heap, actsys->oam );
			}
			if( actsys->act != NULL ){
				sys_FreeMemory( heap, actsys->act );
			}
			if( actsys->act_stack != NULL ){
				sys_FreeMemory( heap, actsys->act_stack );
			}

			sys_FreeMemory( heap, actsys );

		}
		return NULL;
	}

	return actsys;
}

//------------------------------------------------------------------
/**
 * システム削除
 *
 * @param   actsys		システムワークポインタ
 *
 */
//------------------------------------------------------------------
void PACT_SysDelete( PACTSYS* actsys )
{
	if( actsys )
	{
		if( actsys->oam ){ sys_FreeMemoryEz( actsys->oam ); }
		if( actsys->act) {sys_FreeMemoryEz( actsys->act ); }
		if( actsys->act_stack ){ sys_FreeMemoryEz( actsys->act_stack ); }
		sys_FreeMemoryEz( actsys );
	}
}
//------------------------------------------------------------------
/**
 * 描画（メインループの最後に）
 *
 * @param   actsys		システムワークポインタ
 *
 */
//------------------------------------------------------------------
void PACT_SysMain( PACTSYS* actsys )
{
	if( actsys->act_stack_p )
	{
		PACT*       p = actsys->act_top;
		GXOamAttr*  oam_p = actsys->oam;
		s32         oam_max = actsys->act_max;
		u32   use;

		while( p != NULL )
		{
			NNS_G2dTickCellAnimation( &p->cellanm, FX32_ONE*2 );

			if( p->vanish == 0 )
			{
				const NNSG2dSRTControl*  pSRT = &(p->cellanm.srtCtrl);
				NNSG2dFVec2  pos;

				// 平行移動
				pos.x = p->pos.x + (fx32)(pSRT->srtData.trans.x << FX32_SHIFT);
				pos.y = p->pos.y + (fx32)(pSRT->srtData.trans.y << FX32_SHIFT);

				// 回転・拡縮なし
				if( p->affine_flag == FALSE )
				{
					use = NNS_G2dMakeCellToOams (
						oam_p, oam_max,
						NNS_G2dGetCellAnimationCurrentCell( &p->cellanm ),
						NULL,
						&(pos),
						0,
						FALSE
					);

				}
				// 回転・拡縮あり
				else
				{
					u16 affineIndex;

					// 回転
					MTX_Identity22( p->affine );
					if( pSRT->srtData.SRT_EnableFlag & NNS_G2D_AFFINEENABLE_ROTATE )
					{
						u16 rotate = pSRT->srtData.rotZ + p->rotate;
						MTX_Rot22( p->affine, FX_SinIdx(rotate), FX_CosIdx(rotate) );
					}
					else if( p->rotate )
					{
						MTX_Rot22( p->affine, FX_SinIdx(p->rotate), FX_CosIdx(p->rotate) );
					}

					// 拡縮
					if( pSRT->srtData.SRT_EnableFlag & NNS_G2D_AFFINEENABLE_SCALE )
					{
						MTX_ScaleApply22( p->affine, p->affine, FX_Inv(pSRT->srtData.scale.x), FX_Inv(pSRT->srtData.scale.y) );
					}

					affineIndex = NNS_G2dEntryOamManagerAffine( actsys->oamm, p->affine );

					use = NNS_G2dMakeCellToOams (
						oam_p, oam_max,
						NNS_G2dGetCellAnimationCurrentCell( &p->cellanm ),
						p->affine,
						&(pos),
						affineIndex,
						TRUE
					);

				}

				oam_max -= use;
				while(use--)
				{
					oam_p->priority = p->bgpri;
					oam_p->cParam += p->pal_offset;
					oam_p->charNo += p->char_offset;
					oam_p->flipH ^= p->h_flip;
					oam_p->flipV ^= p->v_flip;
					oam_p->mosaic ^= p->mosaic;
					oam_p++;
				}

			}

			p = p->next;
		}

		if( oam_p > actsys->oam )
		{
			NNS_G2dEntryOamManagerOam( actsys->oamm, actsys->oam, oam_p - actsys->oam );
		}
	}
}

//------------------------------------------------------------------
/**
 * アクター追加
 *
 * @param   actsys		システムワークポインタ
 * @param   param		アクター作成パラメータ
 *
 * @retval  PACT*		アクターポインタ
 */
//------------------------------------------------------------------
PACT*  PACT_Add( PACTSYS* actsys, const PACT_ADD_PARAM* param,  const PACT_CLANM_PACK* pack )
{
	PACT* act = ActPop( actsys );
	if( act != NULL )
	{
		// リンクリストに追加
		act->bgpri = param->bgpri;
		act->oampri = param->oampri;
		ActChain( actsys, act );

		// セルバンク、アニメバンクを持つ
		act->cellbank = pack->cellbank;
		act->anmbank = pack->anmbank;

		// アニメ状態を初期化
		NNS_G2dInitCellAnimation(
			&(act->cellanm),
			NNS_G2dGetAnimSequenceByIdx( act->anmbank, param->anmseq ),
			act->cellbank
		);

		act->pos = param->pos;
		act->pal_offset = 0;
		act->char_offset = 0;
		act->h_flip = ((param->flip & PACT_FLIP_H) != 0);
		act->v_flip = ((param->flip & PACT_FLIP_V) != 0);;
		act->mosaic = FALSE;
		act->rotate = 0;


		act->affine = &(act->affine_body);
		act->affine_flag = param->affine_flag;
		act->vanish = 0;


	}
	return act;
}


//------------------------------------------------------------------
/**
 * アクター削除
 *
 * @param   actsys		
 * @param   act		
 *
 */
//------------------------------------------------------------------
void PACT_Del( PACTSYS* actsys, PACT* act )
{
	// リンクリストから外す
	ActUnchain( actsys, act );
	ActPush( actsys, act );
}

//------------------------------------------------------------------
/**
 * アクター操作：アニメシーケンス変更
 *
 * @param   act			アクターポインタ
 * @param   anmseq		アニメシーケンスナンバー
 *
 */
//------------------------------------------------------------------
void PACT_ChangeAnmSeq( PACT* act, u32 anmseq )
{
//	const NNSG2dAnimSequenceData* anmSeqDat = NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq );
//	NNSG2dAnimController*  anmCtrl = NNS_G2dGetCellAnimationAnimCtrl( &(act->cellanm) );

	NNS_G2dInitCellAnimation(
		&(act->cellanm),
		NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq ),
		act->cellbank
	);
/*
	if( anmSeqDat != NNS_G2dGetAnimCtrlCurrentAnimSequence( anmCtrl ) )
	{
		NNS_G2dSetCellAnimationSequence(
			&(act->cellanm),
			NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq )
		);

		NNS_G2dResetAnimCtrlState( anmCtrl );

		NNS_G2dStartAnimCtrl( anmCtrl );
	}
*/
}
//------------------------------------------------------------------
/**
 * アクター操作：アニメ再生が終了しているかチェック
 *
 * @param   act			アクターポインタ
 * @param   anmseq		アニメシーケンスナンバー
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL PACT_CheckAnmEnd( PACT* act )
{
	NNSG2dAnimController*  anmCtrl = NNS_G2dGetCellAnimationAnimCtrl( &(act->cellanm) );
	return NNS_G2dIsAnimCtrlActive( anmCtrl ) == FALSE;
}

//------------------------------------------------------------------
/**
 * アクター操作：今いる位置から指定分だけ移動
 *
 * @param   act		アクターポインタ
 * @param   x		移動量X
 * @param   y		移動量Y
 *
 */
//------------------------------------------------------------------
void PACT_MovePos( PACT* act, fx32 x, fx32 y )
{
	act->pos.x += x;
	act->pos.y += y;
}

//------------------------------------------------------------------
/**
 * アクター操作：指定位置へ移動
 *
 * @param   act		アクターポインタ
 * @param   x		位置指定Ｘ
 * @param   y		位置指定Ｙ
 *
 */
//------------------------------------------------------------------
void PACT_SetPos( PACT* act, fx32 x, fx32 y )
{
	act->pos.x = x;
	act->pos.y = y;
}

//------------------------------------------------------------------
/**
 * アクター操作：現在位置を取得
 *
 * @param   act		アクターポインタ
 * @param   x		Ｘ座標受け取り変数ポインタ
 * @param   y		Ｙ座標受け取り変数ポインタ
 *
 */
//------------------------------------------------------------------
void PACT_GetPos( const PACT* act, fx32* x, fx32* y )
{
	*x = act->pos.x;
	*y = act->pos.y;
}

//------------------------------------------------------------------
/**
 * 表示オフフラグをセット
 *
 * @param   act			アクターポインタ
 * @param   vanish		表示オフフラグ
 *
 */
//------------------------------------------------------------------
void PACT_SetVanish( PACT* act, BOOL vanish )
{
	act->vanish = vanish;
}

//------------------------------------------------------------------
/**
 * BGプライオリティをセット
 *
 * @param   actsys		システムワークポインタ
 * @param   bgpri		
 *
 */
//------------------------------------------------------------------
void PACT_SetBGPri( PACTSYS* actsys, PACT* act, u32 bgpri )
{
	act->bgpri = bgpri;
}


//------------------------------------------------------------------
/**
 * OAMプライオリティをセット
 *
 * @param   actsys		
 * @param   oampri		
 *
 */
//------------------------------------------------------------------
void PACT_SetOamPri( PACTSYS* actsys, PACT* act, u32 oampri )
{
	ActUnchain( actsys, act );
	act->oampri = oampri;
	ActChain( actsys, act );
}


//------------------------------------------------------------------
/**
 * パレットオフセット値をセット
 *
 * @param   act			アクターポインタ
 * @param   offset		オフセット値
 *
 */
//------------------------------------------------------------------
void PACT_SetPalOffset( PACT* act, u32 offset )
{
	act->pal_offset = offset;
}
//------------------------------------------------------------------
/**
 * キャラオフセット値をセット
 *
 * @param   act			アクターポインタ
 * @param   offset		オフセット値
 *
 */
//------------------------------------------------------------------
void PACT_SetCharOffset( PACT* act, u32 offset )
{
	act->char_offset = offset;
}
//------------------------------------------------------------------
/**
 * 反転フラグをセット
 *
 * @param   act			アクターポインタ
 * @param   flip		反転フラグ
 *
 */
//------------------------------------------------------------------
void PACT_SetFlip( PACT* act, PACT_FLIP flip )
{
	act->h_flip = ((flip & PACT_FLIP_H) != 0);
	act->v_flip = ((flip & PACT_FLIP_V) != 0);
}
//------------------------------------------------------------------
/**
 * モザイクフラグをセット
 *
 * @param   act			アクターポインタ
 * @param   flag		モザイクフラグ
 *
 */
//------------------------------------------------------------------
void PACT_SetMosaic( PACT* act, BOOL flag )
{
	act->mosaic = flag;
}

//------------------------------------------------------------------
/**
 * 回転角度をセット
 *
 * @param   act			アクターポインタ
 * @param   rotate		回転角度（0～65535）
 *
 */
//------------------------------------------------------------------
void PACT_SetRotate( PACT* act, u16 rotate )
{
	act->rotate = rotate;
}



//------------------------------------------------------------------
/**
 * セル・アニメデータを構造体に読み込み
 *
 * @param   pack		セル・アニメデータ読み込み先構造体
 * @param	arcFileIdx	アーカイブファイルインデックス
 * @param   cellfile	アーカイブ内のセルデータインデックス
 * @param   anmfile		アーカイブ内のアニメデータインデックス
 * @param   heap		読み込みバッファを確保するﾋｰﾌﾟID
 *
 * @retval  BOOL		TRUEで成功
 *
 */
//------------------------------------------------------------------
BOOL  PACT_TOOL_LoadCellDatas( PACT_CLANM_PACK* pack, u32 arcFileIdx, u32 cellDataIdx, u32 anmDataIdx, HEAPID heap )
{
	pack->heap = heap;
	pack->cellfile = ArcUtil_UnCompress( arcFileIdx, cellDataIdx, heap );
	pack->anmfile  = ArcUtil_UnCompress( arcFileIdx, anmDataIdx, heap );

	if( pack->cellfile != NULL && pack->anmfile != NULL )
	{
		if( !NNS_G2dGetUnpackedCellBank( pack->cellfile, &(pack->cellbank) ) )
		{
			return FALSE;
		}
		if( !NNS_G2dGetUnpackedMCAnimBank( pack->anmfile, &(pack->anmbank) ) )
		{
			return FALSE;
		}
	}

	return TRUE;

}

//------------------------------------------------------------------
/**
 * 読み込んだセル・アニメデータを解放
 *
 * @param   pack	セル・アニメデータ読み込み先構造体
 *
 */
//------------------------------------------------------------------
void PACT_TOOL_UnloadCellDatas( PACT_CLANM_PACK* pack )
{
	if( pack->cellfile != NULL )
	{
		sys_FreeMemory( pack->heap, pack->cellfile );
		pack->cellfile = NULL;
	}
	if( pack->anmfile != NULL )
	{
		sys_FreeMemory( pack->heap, pack->anmfile );
		pack->anmfile = NULL;
	}
}







//------------------------------------------------------------------
/**
 * アクター管理データ全初期化
 *
 * @param   numact		
 *
 */
//------------------------------------------------------------------
static void ActAllInit( PACT** stack, PACT* acts, u32 numact )
{
	while(numact--)
	{
		*stack = acts;
		ActClear( acts );
		acts++;
		stack++;
	}
}
//------------------------------------------------------------------
/**
 * アクターデータ未使用状態にクリア
 *
 * @param   act		アクターのデータクリア
 *
 */
//------------------------------------------------------------------
static void ActClear( PACT* act )
{
	act->next = NULL;
	act->prev = NULL;
}
//------------------------------------------------------------------
/**
 * アクターポインタのスタックからポップ
 *
 * @param   actsys		システムモジュール
 *
 * @retval  PACT*		アクターポインタ
 */
//------------------------------------------------------------------
static PACT* ActPop( PACTSYS* actsys )
{
	if( actsys->act_stack_p < actsys->act_max )
	{
		return actsys->act_stack[ actsys->act_stack_p++ ];
	}
	return NULL;
}
//------------------------------------------------------------------
/**
 * アクターポインタのスタックへプッシュ
 *
 * @param   actsys		システムワークポインタ
 * @param   act			アクターポインタ
 *
 */
//------------------------------------------------------------------
static void ActPush( PACTSYS* actsys, PACT* act )
{
	if( actsys->act_stack_p == 0 )
	{
		SDK_ASSERT( 0 );
		return;
	}

	ActClear( act );
	actsys->act_stack_p--;
	actsys->act_stack[ actsys->act_stack_p ] = act;
}

//------------------------------------------------------------------
/**
 * アクターリストに新しいアクターを繋ぐ
 *
 * @param   actsys		システムワークポインタ
 * @param   act			アクタポインタ（プライオリティセットされていること）
 *
 */
//------------------------------------------------------------------
static void ActChain( PACTSYS* actsys, PACT *act )
{
	if( actsys->act_top == NULL )
	{
		actsys->act_top = act;
		act->next = NULL;
		act->prev = NULL;
	}
	else
	{
		PACT* p = actsys->act_top;

		while( 1 )
		{
			// 値が低い=プライオリティ高い
			if( act->pri < p->pri )
			{
				if( p == actsys->act_top )
				{
					actsys->act_top = act;
				}
				act->prev = p->prev;
				if( act->prev )
				{
					act->prev->next = act;
				}
				act->next = p;
				p->prev = act;
				break;
			}

			if( p->next == NULL )
			{
				p->next = act;
				act->prev = p;
				act->next = NULL;
				break;
			}
			else
			{
				p = p->next;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * アクターリストからアクターをはずす
 *
 * @param   actsys		システムワークポインタ
 * @param   act		
 *
 */
//------------------------------------------------------------------
static void ActUnchain( PACTSYS* actsys, PACT* act )
{
	if( act->prev != NULL)
	{
		if( act->next != NULL )		// 前と後にアクターがいる
		{
			act->prev->next = act->next;
			act->next->prev = act->prev;
		}
		else						// 後はないが前にいる（最後）
		{
			act->prev->next = NULL;
		}
	}
	else
	{
		if( act->next != NULL )		// 前はないが後にはいる（先頭）
		{
			act->next->prev = NULL;
			actsys->act_top = act->next;
		}
		else						// 前も後もない（単体）
		{
			actsys->act_top = NULL;
		}
	}
}
