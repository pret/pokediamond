//============================================================================================
/**
 * @file	boxv_cursor.c
 * @brief	ボックス操作画面　描画下請け（ポケモンアイコン関連）
 * @author	taya
 * @date	2005.09.20
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "poketool\pokeicon.h"
#include  "poketool\boxdata.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"





//------------------------------------------------------------------
/**
 * 初期化
 *
 * @param   wk		
 * @param   vwk		
 * @param   vpara		
 * @param   actsys		
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
BOOL BoxAppView_IconSysInit(BOX_ICON_SYS* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys )
{
	NNSG2dImagePaletteProxy proxy;
	NNSG2dPaletteData* palData;
	void* tmpbuf;

	NNS_G2dInitImagePaletteProxy( &proxy );
	ArcUtil_PalSysLoad(ARC_POKEICON, PokeIconPalArcIndexGet(), NNS_G2D_VRAM_TYPE_2DMAIN, OBJPAL_ICON*0x20, 
			HEAPID_BOX_VIEW, &proxy);

	tmpbuf = ArcUtil_PalDataGet(ARC_POKEICON, PokeIconPalArcIndexGet(), &palData, HEAPID_BOX_VIEW);
	if(tmpbuf)
	{
		BOOL  cmpFlag;
		NNSG2dPaletteCompressInfo*  cmpData;

		NNS_G2dInitImagePaletteProxy( &proxy );

		cmpFlag = NNS_G2dGetUnpackedPaletteCompressInfo( tmpbuf, &cmpData );
		BoxAppView_PalFade( palData->pRawData, palData->pRawData, palData->szByte / sizeof(u16), 0x057f, 8 );
		if( cmpFlag )
		{
			NNS_G2dLoadPaletteEx( palData, cmpData, OBJPAL_AREASELECT_ICON*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );
		}
		else
		{
			NNS_G2dLoadPalette( palData, OBJPAL_AREASELECT_ICON*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );
		}
		sys_FreeMemoryEz(tmpbuf);
	}


//	wk->cellBuf = ArcUtil_LoadEx(ARC_BOX_GRA, NARC_box_icon_lz_ncer, TRUE, HEAPID_BOX_VIEW, ALLOC_TOP, &(wk->cellBankSize));
	wk->cellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_icon_lz_ncer, TRUE, &(wk->cellBank), HEAPID_BOX_VIEW);
	wk->anmBuf = ArcUtil_AnimBankDataGet(ARC_BOX_GRA, NARC_box_icon_lz_nanr, TRUE, &(wk->anmBank), HEAPID_BOX_VIEW);

	wk->item_cellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_itemicon_lz_ncer, TRUE, &(wk->item_cellBank), HEAPID_BOX_VIEW);
	wk->item_anmBuf = ArcUtil_AnimBankDataGet(ARC_BOX_GRA, NARC_box_itemicon_lz_nanr, TRUE, &(wk->item_anmBank), HEAPID_BOX_VIEW);


	wk->arcHandle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_BOX_VIEW );

	if( wk->cellBuf == NULL || wk->anmBuf == NULL || wk->arcHandle == NULL)
	{
		return FALSE;
	}


	wk->actSys = actsys;
	wk->vpara = vpara;
	wk->vwk = vwk;

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 終了
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconSysQuit( BOX_ICON_SYS* wk )
{
	if( wk->cellBuf != NULL ){
		sys_FreeMemoryEz( wk->cellBuf );
		wk->cellBuf = NULL;
	}
	if( wk->anmBuf != NULL ){
		sys_FreeMemoryEz( wk->anmBuf );
		wk->anmBuf = NULL;
	}
	if( wk->item_cellBuf != NULL )
	{
		sys_FreeMemoryEz( wk->item_cellBuf );
		wk->item_cellBuf = NULL;
	}
	if( wk->item_anmBuf != NULL )
	{
		sys_FreeMemoryEz( wk->item_anmBuf );
		wk->item_anmBuf = NULL;
	}
	if( wk->arcHandle != NULL )
	{
		ArchiveDataHandleClose( wk->arcHandle );
	}
}





//------------------------------------------------------------------
/**
 * アイコンワーク初期化処理
 *
 * @param   wk		
 * @param   num		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconWorkInit( BOX_ICON_SYS* iconSys, BOX_ICON_WORK* wk, u32 num )
{
	while(num--)
	{
		wk->act = NULL;
		NNS_G2dInitImageProxy( &(wk->imgProxy) );

		wk++;
	}
}
//------------------------------------------------------------------
/**
 * アイコンワーク終了処理
 *
 * @param   wk		
 * @param   num		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconWorkQuit( BOX_ICON_SYS* iconSys, BOX_ICON_WORK* wk, u32 num )
{
	while(num--)
	{
		if( wk->act != NULL )
		{
			CLACT_Delete( wk->act );
			wk->act = NULL;
		}
		wk++;
	}
}

//------------------------------------------------------------------
/**
 * アイコンワークのコピー
 *
 * @param   src		
 * @param   dst		
 * @param   num		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconWorkCopy( const BOX_ICON_WORK* src, BOX_ICON_WORK* dst, u32 num )
{
	MI_CpuCopy32( src, dst, sizeof(BOX_ICON_WORK)*num );
}

//------------------------------------------------------------------
/**
 * アイコンアクター追加（PPP指定）
 *
 * @param   wk			ワークポインタ
 * @param   ppp			POKEMON
 * @param   x			
 * @param   y			
 * @param   bgpri		
 * @param   actpri		
 * @param   charno		
 * @param   icon		アイコン作成先バッファ
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconAdd( BOX_ICON_SYS* wk, POKEMON_PASO_PARAM* ppp, s32 x, s32 y, u32 bgpri, u32 actpri, u32 charno, BOX_ICON_WORK* icon )
{
	NNSG2dCharacterData* charData;
	CLACT_HEADER  header;
	u16 monsno;
	u8  tamagoFlag;
	u8  form;
	u8  fastmodeFlag;


	fastmodeFlag = PokePasoParaFastModeOn(ppp);

	BoxAppView_SetActHeader( &header, NULL, BoxAppView_GetObjPlttProxy( wk->vwk ),
			wk->cellBank, wk->anmBank, bgpri );

	monsno = PokePasoParaGet( ppp, ID_PARA_monsno, NULL );
	tamagoFlag = PokePasoParaGet( ppp, ID_PARA_tamago_flag, NULL );
	form = PokePasoParaGet( ppp, ID_PARA_form_no, NULL );
	icon->imgArcIdx = PokeIconCgxArcIndexGet( (POKEMON_PASO_PARAM*)ppp );
	icon->imgPalNo = PokeIconPalNumGet( monsno, form, tamagoFlag );
	icon->itemNo = PokePasoParaGet( ppp, ID_PARA_item, NULL );
	icon->markingBit = PokePasoParaGet( ppp, ID_PARA_mark, NULL );

	NNS_G2dInitImageProxy( &(icon->imgProxy) );
	ArchiveDataLoadOfsByHandle( wk->arcHandle, icon->imgArcIdx, 0, BOXICON_CHARBUF_SIZE, wk->charbuf );
	NNS_G2dGetUnpackedCharacterData( wk->charbuf, &charData );
	charData->mapingType = GX_GetOBJVRamModeChar();
	charData->szByte = BOXICON_CHAR_SIZE*0x20;
	NNS_G2dLoadImage1DMapping( charData, charno*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(icon->imgProxy) );

	header.pImageProxy = &(icon->imgProxy);

	icon->act = BoxAppView_AddActor( wk->actSys, &header, x, y, actpri, NNS_G2D_VRAM_TYPE_2DMAIN );
	GF_ASSERT( icon->act != NULL );

	CLACT_PaletteNoChg( icon->act, OBJPAL_ICON + icon->imgPalNo );
	BoxAppView_IconLimitModeSet( wk, icon, BoxAppVPara_GetLimitModeBitFlag(wk->vpara) );

	PokePasoParaFastModeOff(ppp, fastmodeFlag);
}

//------------------------------------------------------------------
/**
 * アイコンアクター追加（キャラデータ指定）
 *
 * @param   wk			
 * @param   monsno		
 * @param   arcIdx		
 * @param   charBuf		
 * @param   x			
 * @param   y			
 * @param   bgpri		
 * @param   actpri		
 * @param   charno		
 * @param   icon		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconAddCharSet( BOX_ICON_SYS* wk, POKEMON_PASO_PARAM* ppp, u32 monsno, u32 arcIdx, u8* charBuf, s32 x, s32 y, u32 bgpri, u32 actpri, u32 charno, BOX_ICON_WORK* icon )
{
	NNSG2dCharacterData* charData;
	CLACT_HEADER  header;
	BOOL fastmodeFlag;
	u8 tamago_flag, form;

	fastmodeFlag = PokePasoParaFastModeOn(ppp);

	tamago_flag = PokePasoParaGet(ppp, ID_PARA_tamago_flag, NULL);
	form = PokePasoParaGet(ppp, ID_PARA_form_no, NULL);

	BoxAppView_SetActHeader( &header, NULL, BoxAppView_GetObjPlttProxy( wk->vwk ),
			wk->cellBank, wk->anmBank, bgpri );

	icon->imgArcIdx = arcIdx;
	icon->imgPalNo = PokeIconPalNumGet( monsno, form, tamago_flag );
	icon->itemNo = PokePasoParaGet( ppp, ID_PARA_item, NULL );
	icon->markingBit = PokePasoParaGet( ppp, ID_PARA_mark, NULL );


	NNS_G2dInitImageProxy( &(icon->imgProxy) );
	NNS_G2dGetUnpackedCharacterData( charBuf, &charData );
	charData->mapingType = GX_GetOBJVRamModeChar();
	charData->szByte = BOXICON_CHAR_SIZE*0x20;
	NNS_G2dLoadImage1DMapping( charData, charno*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(icon->imgProxy) );

	header.pImageProxy = &(icon->imgProxy);

	icon->act = BoxAppView_AddActor( wk->actSys, &header, x, y, actpri, NNS_G2D_VRAM_TYPE_2DMAIN );
	GF_ASSERT( icon->act != NULL );

	CLACT_PaletteNoChg( icon->act, OBJPAL_ICON + icon->imgPalNo );
	BoxAppView_IconLimitModeSet( wk, icon, BoxAppVPara_GetLimitModeBitFlag(wk->vpara) );

	PokePasoParaFastModeOff(ppp, fastmodeFlag);
}



//------------------------------------------------------------------
/**
 * 絞り込みモードのビットフラグに応じてアクター表示状態を変化させる
 *
 * @param   iconwk		
 * @param   limitBit		
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconLimitModeSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 limitBit )
{
//	#define DBG_PRINT

	if( limitBit != 0 )
	{
		int i;

		if( (limitBit & LIMITMODE_BIT_ITEM) )
		{
			if( icon->itemNo == 0 )
			{
				CLACT_ObjModeSet( icon->act, GX_OAM_MODE_XLU );
				return;
			}
		}

		#ifdef DBG_PRINT
		OS_TPrintf("markingBit = 0x%04x  ", icon->markingBit);
		#endif

		for(i=0; i<POKEPARA_MARKING_ELEMS_MAX; i++)
		{
			if(	(limitBit & (LIMITMODE_BIT_MARK1<<i))
			&&	((icon->markingBit & (1<<i)) == 0)
			){
				#ifdef DBG_PRINT
				OS_TPrintf("mode xlu!\n");
				#endif
				CLACT_ObjModeSet( icon->act, GX_OAM_MODE_XLU );
				return;
			}
		}
		#ifdef DBG_PRINT
		OS_TPrintf("mode normal!\n");
		#endif
	}

	CLACT_ObjModeSet( icon->act, GX_OAM_MODE_NORMAL );

#ifdef DBG_PRINT
#undef DBG_PRINT
#endif
}

//------------------------------------------------------------------
/**
 * アイコン内部ステータスのマーキング用ビットフラグをセット
 *
 * @param   wk			アイコンシステムワークポインタ
 * @param   icon		アイコンワーク
 * @param   markBit		マーキング用ビット
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconMarkBitSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 markBit )
{
	icon->markingBit = markBit;
}
//------------------------------------------------------------------
/**
 * アイコン内部ステータスのアイテムナンバーをセット
 *
 * @param   wk			アイコンシステムワークポインタ
 * @param   icon		アイコンワーク
 * @param   markBit		アイテムナンバー
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconItemNumberSet( BOX_ICON_SYS* wk, BOX_ICON_WORK* icon, u32 itemNo )
{
	icon->itemNo = itemNo;
}


//------------------------------------------------------------------
/**
 * アイコンのキャラデータをアーカイブから読み込み
 *
 * @param   wk			ワークポインタ
 * @param   buf			読み込み先バッファ
 * @param   datIdx		アーカイブ内のﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 * @param   size		読み込みｻｲｽﾞ
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconCharDataLoad( BOX_ICON_SYS* wk, void* buf, u32 datIdx, u32 size )
{
	ArchiveDataLoadOfsByHandle( wk->arcHandle, datIdx, 0, size, buf );
}

//------------------------------------------------------------------
/**
 * アイコンのキャラデータを別位置にセットし直す
 *
 * @param   sys		
 * @param   icon		
 * @param   charpos		転送位置（キャライメージ領域先頭からのキャラ単位オフセット）
 *
 */
//------------------------------------------------------------------
void BoxAppView_Icon_ResetImageBank( BOX_ICON_SYS* sys, BOX_ICON_WORK* icon, u32 charpos )
{
	if(icon->act != NULL)
	{
		NNSG2dCharacterData* charData;

		NNS_G2dInitImageProxy( &(icon->imgProxy) );

		ArchiveDataLoadOfsByHandle( sys->arcHandle, icon->imgArcIdx, 0, BOXICON_CHARBUF_SIZE, sys->charbuf );
		NNS_G2dGetUnpackedCharacterData( sys->charbuf, &charData );
		charData->mapingType = GX_GetOBJVRamModeChar();
		charData->szByte = BOXICON_CHAR_SIZE*0x20;

		NNS_G2dLoadImage1DMapping( charData, charpos*0x20, NNS_G2D_VRAM_TYPE_2DMAIN, &(icon->imgProxy) );

		CLACT_ImageProxySet( icon->act, &(icon->imgProxy) );
	}
}


//------------------------------------------------------------------
/**
 * アイコンアニメスタート
 *
 * @param   iconsys		アイコンシステムワークポインタ
 * @param   icon		アイコンワークポインタ
 * @param   anm			アニメナンバ
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconAnmStart( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon, u32 anm )
{
	if( anm == ICON_ANM_RELEASE || anm == ICON_ANM_COMEBACK )
	{
		CLACT_SetAffineParam( icon->act, CLACT_AFFINE_NORMAL );
	}
	else
	{
		CLACT_SetAffineParam( icon->act, CLACT_AFFINE_NONE );
	}

	CLACT_AnmChg( icon->act, anm );

}
//------------------------------------------------------------------
/**
 * アイコンアニメスタート
 *
 * @param   iconsys		アイコンシステムワークポインタ
 * @param   icon		アイコンワークポインタ
 *
 */
//------------------------------------------------------------------
BOOL BoxAppView_IconAnmWait( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon )
{
	return CLACT_AnmActiveCheck( icon->act ) == FALSE;
}



//------------------------------------------------------------------
/**
 * 範囲選択対象用のパレットと通常パレットの切り替え
 *
 * @param   iconsys			アイコンシステムワークポインタ
 * @param   icon			アイコンワークポインタ
 * @param   areaSelFlag		TRUEなら範囲選択用にする／FALSEで通常にする
 *
 */
//------------------------------------------------------------------
void BoxAppView_IconAreaSelectPalSet( BOX_ICON_SYS* iconsys, BOX_ICON_WORK* icon, BOOL areaSelFlag )
{
	u32 palno = ((areaSelFlag)? OBJPAL_AREASELECT_ICON : OBJPAL_ICON) + icon->imgPalNo;
	CLACT_PaletteNoChg( icon->act, palno );
}


NNSG2dCellDataBank* BoxAppView_IconSys_GetCellBank( BOX_ICON_SYS* sys )
{
	return sys->cellBank;
}

NNSG2dAnimBankData* BoxAppView_IconSys_GetAnimBank( BOX_ICON_SYS* sys )
{
	return sys->anmBank;
}
