#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/bmp_list.h"
#include "system/msgdata_util.h"

#include "comm_mystery_func.h"


//--------------------------------------------------------------------------------------------
/**
 * VRAM初期化
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CommMysteryFunc_VramBankSet(void)
{
  GF_BGL_DISPVRAM vramSetTable = {
    GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
    GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
    GX_VRAM_SUB_BG_32_H,			/* サブ2DエンジンのBG */
    GX_VRAM_SUB_BGEXTPLTT_NONE,		/* サブ2DエンジンのBG拡張パレット */
    GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
    GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
    GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
    GX_VRAM_TEX_0_B,				// テクスチャイメージスロット
    GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
  };
  GF_Disp_SetBank( &vramSetTable );
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	BG初期化
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CommMysteryFunc_BgInit( GF_BGL_INI * ini )
{
  {	/* BG SYSTEM */
    GF_BGL_SYS_HEADER BGsys_data = {
      GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
    };
    GF_BGL_InitBG( &BGsys_data );
  }

  {	/* MAIN DISP BG0 */
    GF_BGL_BGCNT_HEADER MBg0_Data = {
      0, 0, 0x0800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &MBg0_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
  }

  {	/* MAIN DISP BG1 */
    GF_BGL_BGCNT_HEADER MBg1_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &MBg1_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
  }

  {	/* MAIN DISP BG2 */
    GF_BGL_BGCNT_HEADER MBg2_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_23, 0, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &MBg2_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
  }

  {	/* MAIN DISP BG3 */
    GF_BGL_BGCNT_HEADER MBg3_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x0c000,
      GX_BG_EXTPLTT_23, 3, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &MBg3_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
  }
}


//------------------------------------------------------------------
/**
 * @brief	おくりものをもらえるかチェック
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
int CommMysteryFunc_CheckGetGift(SAVEDATA *sv, GIFT_COMM_PACK *gcp)
{
  u32 version;
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(sv);

#if 0
  // デバッグ用の強制エラー発生コード
  return COMMMYSTERYFUNC_ERROR_GROUNDCHILD;
#endif
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("拾ったビーコンのバージョンは %08X です\n", gcp->beacon.version);
  OS_TPrintf("一度しか受け取れないフラグ: %d\n", gcp->beacon.only_one_flag);
  OS_TPrintf("カード付きおくりものフラグ: %d\n", gcp->beacon.have_card);
  OS_TPrintf("孫配布フラグ: %d\n", gcp->beacon.groundchild_flag);
#endif

  
  version = gcp->beacon.version;
  
  // デバッグ用のふしぎなおくりもの消去処理
  if(version == 0xFFFFFFFF && gcp->beacon.event_id == 0xFFFF){
    FUSHIGIDATA_Init(fdata);
    SaveData_SaveParts(sv, SVBLK_ID_NORMAL);
    OS_ResetSystem(0); 
  }
  
  // 対象バージョンが０ならば全てのバージョンで受け取れる
  if(version == 0)
    version = ~0;

  // 対象バージョンに含まれているかチェック
  if((version & (1 << PM_VERSION)) == FALSE)
    return COMMMYSTERYFUNC_ERROR_VERSION;

  // 一度しか受け取れないおくりものは、
  if(gcp->beacon.only_one_flag == TRUE &&
     // すでに受け取っているか調べる
     FUSHIGIDATA_IsEventRecvFlag(fdata, gcp->beacon.event_id) == TRUE)
    return COMMMYSTERYFUNC_ERROR_HAVE;

  // カード付きおくりものは
  if(gcp->beacon.have_card == TRUE &&
     // カード情報がセーブできるかチェック
    FUSHIGIDATA_CheckCardDataSpace(fdata) == FALSE)
    return COMMMYSTERYFUNC_ERROR_FULLCARD;

  // さらに配達員情報が含まれているおくりものは
  // 配達員のスロットもチェックする
  if(FUSHIGIDATA_CheckDeliDataSpace(fdata) == FALSE)
    return COMMMYSTERYFUNC_ERROR_FULLGIFT;

  // 孫配布のチェック
  if(gcp->beacon.groundchild_flag == 1)
    return COMMMYSTERYFUNC_ERROR_GROUNDCHILD;

  return COMMMYSTERYFUNC_ERROR_NONE;
}


/*  */
