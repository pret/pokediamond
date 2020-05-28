//============================================================================================
/**
 * @file	scr_sound.c
 * @bfief	スクリプトコマンド：サウンド関連
 * @author	Satoshi Nohara
 * @date	06.06.26
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "savedata/perapvoice.h"
#include "system/snd_tool.h"
#include "system/snd_perap.h"
#include "fld_bgm.h"


//============================================================================================
//
//	プロロトタイプ宣言
//
//============================================================================================
static BOOL EvWaitBgmFade( VM_MACHINE * core );
static BOOL EvWaitSe(VM_MACHINE * core);
static BOOL EvWaitVoicePlay(VM_MACHINE * core);
static BOOL EvWaitMe( VM_MACHINE * core );

BOOL EvCmdBgmPlay(VM_MACHINE * core );
BOOL EvCmdBgmStop(VM_MACHINE * core );
BOOL EvCmdBgmNowMapPlay(VM_MACHINE * core );
BOOL EvCmdBgmSpecialSet(VM_MACHINE * core );
BOOL EvCmdBgmFadeOut( VM_MACHINE * core );
BOOL EvWaitBgmFade( VM_MACHINE * core );
BOOL EvCmdBgmFadeIn( VM_MACHINE * core );
BOOL EvCmdBgmPlayerPause( VM_MACHINE * core );
BOOL EvCmdPlayerFieldDemoBgmPlay( VM_MACHINE * core );
BOOL EvCmdCtrlBgmFlagSet( VM_MACHINE * core );
BOOL EvCmdSePlay( VM_MACHINE * core );
BOOL EvCmdSeStop( VM_MACHINE * core );
BOOL EvCmdSeWait(VM_MACHINE * core);
BOOL EvCmdVoicePlay( VM_MACHINE * core );
BOOL EvCmdVoicePlayWait( VM_MACHINE * core );
BOOL EvCmdMePlay(VM_MACHINE * core );
BOOL EvCmdMeWait(VM_MACHINE * core );
BOOL EvCmdPerapDataCheck( VM_MACHINE * core );
BOOL EvCmdPerapRecStart( VM_MACHINE * core );
BOOL EvCmdPerapRecStop( VM_MACHINE * core );
BOOL EvCmdPerapSave( VM_MACHINE * core );
BOOL EvCmdSndClimaxDataLoad( VM_MACHINE * core );
BOOL EvCmdSndInitialVolSet( VM_MACHINE * core );
BOOL EvCmdBgmPlayCheck(VM_MACHINE * core );


//============================================================================================
//
//	コマンド
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * BGM終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlayCheck( VM_MACHINE * core )
{
	u16 music	= VMGetU16(core);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = Snd_BgmPlayCheck( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGM変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlay( VM_MACHINE * core )
{
	u16 music = VMGetU16(core);
	Snd_BgmPlay( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGM停止
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmStop( VM_MACHINE * core )
{
	u16 music = VMGetU16(core);	//"未使用"
	//Snd_BgmStop( music, 0 );
	Snd_BgmStop( Snd_NowBgmNoGet(), 0 );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在のマップのBGMを再生
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmNowMapPlay( VM_MACHINE * core )
{
	int zone_id = core->fsys->location->zone_id;
	//u16 music	= Snd_PcBgmNoGet( core->fsys, Snd_FieldBgmNoGet(core->fsys,zone_id) );
	u16 music	= Snd_FieldBgmNoGetNonBasicBank( core->fsys,zone_id );
	Snd_BgmPlay( music );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * マップ内限定のBGM指定がセットされる
 * 自転車BGMの制御などに使用
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmSpecialSet( VM_MACHINE * core )
{
	Snd_FieldBgmSetSpecial( core->fsys, VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGMフェードアウト待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmFadeOut( VM_MACHINE * core )
{
	u16 vol		= VMGetU16(core);
	u16 frame	= VMGetU16(core);
	Snd_BgmFadeOut( vol, frame );
	VM_SetWait( core, EvWaitBgmFade );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitBgmFade( VM_MACHINE * core )
{
	if( Snd_FadeCheck() == 0 ){
		return TRUE;
	}
	return FALSE;
};

//--------------------------------------------------------------------------------------------
/**
 * BGMフェードイン待ち(フェードアウトしたものが再開する)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmFadeIn( VM_MACHINE * core )
{
	u16 frame = VMGetU16(core);
	Snd_BgmFadeIn( BGM_VOL_MAX, frame, BGM_FADEIN_START_VOL_MIN );
	VM_SetWait( core, EvWaitBgmFade );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * シーケンスを一時停止または再開
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdBgmPlayerPause( VM_MACHINE * core )
{
	u8 player = VMGetU8(core);
	BOOL flag = VMGetU8(core);

	Snd_PlayerPause( player, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 演出BGM再生(ライバル、サポート、つれてけ)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPlayerFieldDemoBgmPlay( VM_MACHINE * core )
{
	Snd_PlayerFieldDemoBgmPlay( SND_SCENE_FIELD, VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドBGMを固定にするフラグセット(セーブしない)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdCtrlBgmFlagSet( VM_MACHINE * core )
{
	Snd_CtrlBgmFlagSet( VMGetU8(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ＳＥを鳴らす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSePlay( VM_MACHINE * core )
{
	Snd_SePlay( VMGetWorkValue(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ＳＥを止める
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeStop( VM_MACHINE * core )
{
	Snd_SeStopBySeqNo( VMGetWorkValue(core), 0 );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SE終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 *
 * @li		雨などのループ音で、無限ループになってしまうので、SEナンバー指定して、それをチェック！
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSeWait(VM_MACHINE * core)
{
	//仮想マシンの汎用レジスタにBGMナンバーを格納
	core->reg[0] = VMGetWorkValue(core);

	VM_SetWait( core, EvWaitSe );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitSe(VM_MACHINE * core)
{
	//if( Snd_SePlayCheckAll() == 0 ){
	if( Snd_SePlayCheck(core->reg[0]) == 0 ){
		return TRUE;
	}

	return FALSE;
};


//--------------------------------------------------------------------------------------------
/**
 * 鳴き声を鳴らす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdVoicePlay( VM_MACHINE * core )
{
	u16 no, ptn;
	no	= VMGetWorkValue(core);
	ptn = VMGetWorkValue(core);

	//ぺラップ再生テスト
	//no = MONSNO_PERAPPU;

	//パターンを指定できる関数に置き換える予定
	Snd_PMVoicePlay( no );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * 鳴き声終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdVoicePlayWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitVoicePlay );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitVoicePlay(VM_MACHINE * core)
{
	if( Snd_PMVoicePlayCheck() == 0 ){
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ME再生
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMePlay(VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	Snd_MePlay( VMGetU16(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ME終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdMeWait(VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitMe );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitMe( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	//終了待ちのみ
	//if( Snd_MePlayCheck() == 0 ){
	
	//終了待ち＋ウェイトワーク待ち
	if( Snd_MePlayCheckBgmPlay() == 0 ){ 
		return TRUE;
	}

	return FALSE;
};

//--------------------------------------------------------------------------------------------
/**
 * ペラップデータがあるかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapDataCheck( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	if( Snd_PerapVoiceCheck(SaveData_GetPerapVoice(core->fsys->savedata)) == TRUE ){
		*ret_wk = TRUE;
		return 0;
	}

	*ret_wk = FALSE;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ペラップ録音開始
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapRecStart( VM_MACHINE * core )
{
	u16* ret_wk			= VMGetWork( core );

	if( Snd_PerapVoiceRecStart() == MIC_RESULT_SUCCESS ){
		*ret_wk = TRUE;	//成功
		return 0;
	}

	*ret_wk = FALSE;	//失敗
	return 0;

}

//--------------------------------------------------------------------------------------------
/**
 * ペラップ録音停止
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapRecStop( VM_MACHINE * core )
{
	Snd_PerapVoiceRecStop();
	return 1;

}

//--------------------------------------------------------------------------------------------
/**
 * ペラップ録音したデータをセーブ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdPerapSave( VM_MACHINE * core )
{
	Snd_PerapVoiceDataSave( SaveData_GetPerapVoice(core->fsys->savedata) );
	return 1;

}

//--------------------------------------------------------------------------------------------
/**
 * クライマックス演出サウンドデータ追加ロード
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSndClimaxDataLoad( VM_MACHINE * core )
{
	Snd_DataSetByScene( SND_SCENE_SUB_CLIMAX, 0, 0 );	//サウンドデータロード(BGM引継ぎ)
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 初期ボリュームセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdSndInitialVolSet( VM_MACHINE * core )
{
	u16 no	= VMGetWorkValue(core);
	u16 vol = VMGetWorkValue(core);

	Snd_PlayerSetInitialVolumeBySeqNo( no, vol );
	return 0;
}


