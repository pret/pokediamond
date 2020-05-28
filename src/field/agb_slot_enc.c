//============================================================================================
/**
 * @file	agb_slot_enc.c
 * @brief	ＡＧＢスロットバージョン別エンカウント関連
 * @author	saitou
 *
 */
//============================================================================================

#include "common.h"
#include "encount_dat.h"

#include "agb_slot_enc.h"

//-----------------------------------------------------------------------------
/**
 * AGBスロットエンカウントテーブル差し替え
 *
 * @param	*inEncData			エンカウントデータ
 * @param	inBookGet			全国図鑑入手フラグ
 * @param	*outAgbEncMonsNo1	エンカウントポケモン1体目
 * @param	*outAgbEncMonsNo2	エンカウントポケモン2体目
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void AgbSlotEnc_SetAgbSlotEnc(	const ENCOUNT_DATA *inEncData,
								const BOOL inBookGet,
								int *outAgbEncMonsNo1, int *outAgbEncMonsNo2)
{
	//全国図鑑入手していなければ、何もしない
	if (!inBookGet){
		return;
	}
	
	//AGBスロットのバージョン別にエンカウントデータをセット
	switch(sys.AgbCasetteVersion){		
	case VERSION_SAPPHIRE:
		(*outAgbEncMonsNo1) = inEncData->SapphireEnc[0];
		(*outAgbEncMonsNo2) = inEncData->SapphireEnc[1];
		break;
	case VERSION_RUBY:
		(*outAgbEncMonsNo1) = inEncData->RubyEnc[0];
		(*outAgbEncMonsNo2) = inEncData->RubyEnc[1];
		break;
	case VERSION_EMERALD:
		(*outAgbEncMonsNo1) = inEncData->EmeraldEnc[0];
		(*outAgbEncMonsNo2) = inEncData->EmeraldEnc[1];
		break;
	case VERSION_RED:
		(*outAgbEncMonsNo1) = inEncData->FireEnc[0];
		(*outAgbEncMonsNo2) = inEncData->FireEnc[1];
		break;
	case VERSION_GREEN:
		(*outAgbEncMonsNo1) = inEncData->LeafEnc[0];
		(*outAgbEncMonsNo2) = inEncData->LeafEnc[1];
		break;
	}
}
