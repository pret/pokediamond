//==============================================================================
/**
 * @file	we_sys.h
 * @brief	技エフェクト用システム
 * @author	goto
 * @date	2005.06.22(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef	_WE_SYS_H_
#define _WE_SYS_H_

#include "wazaeffect/we_mana.h"
#include "system/particle.h"
#include "include/battle/bc_common.h"

// =============================================================================
//
//
//	■検索用
//	
//		[ _WE-SYS_ ]		WE-SYS
//		[ _EXPLANATION_ ]	WE-SYSの説明
//		[ _COMMAND_ ]		コマンド
//
//
// =============================================================================

// -----------------------------------------
//
//	□自動追尾用
//
// -----------------------------------------
typedef struct _TAMO_SYS * AMO_SYS_PTR;		///< 自動追尾用構造体
typedef struct _TAMB_SYS * AMB_SYS_PTR;


// -----------------------------------------
//
//	デバッグ
//
// -----------------------------------------
//#define WE_SYS_CMD_OS_PRINT				///< 有効 = コマンド名がPrint
//#define WE_SYS_INF_OS_PRINT				///< 有効 = 情報をPrint

// -----------------------------------------
//
//	技エフェクト用関数ポインタ型
//
// -----------------------------------------
typedef void (*pWeFunc)(WE_SYS_PTR we_sys);


// -----------------------------------------
//
//	技エフェクト用 セルアクターサポート関数
//
// -----------------------------------------
typedef void (*pWeClactFunc)(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap);


// -----------------------------------------
//
//	旧技エフェクト用 アクター登録関数
//
// -----------------------------------------
typedef void (*pWeOldActFunc)(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CLACT_WORK_PTR act);


// -----------------------------------------
//
//	アドレスパラメータ型
//
// -----------------------------------------
typedef int	TAP;

extern void DefaultBlendSet(void);

// =========================================
//
//
//	■DEFINE
//
//
// =========================================

#define WE_JUMP_MAX			(3)				///< ジャンプ命令を入れ子にした際の最大数
#define WE_LOOP_MAX			(3)				///< ループ命令を入れ子にした際の最大数
#define WE_GENE_WK_MAX		(8 + 2)			///< 汎用ワーク /// 060515 致し方なく拡張
#define WE_SE_WK_MAX		(7)				///< SE用のワーク数
#define WE_SE_END_TIMER		(90)			///< 3秒間待つ
#define WE_CRP_MAX			(4)				///< CRPの最大数
#define WE_CAP_MAX			(10)			///< CAPの保存数
#define WE_POKE_CAP_MAX		(4 + 1)			///< ポケモンをOAMにドロップできる数 5番目は使用禁止

#define WE_HAIKEI_ARC		(ARC_BATT_BG)	///< 背景のアーカイブされてるID

#define PARTICLE_EMIT_MAX	(20)			///< パーティクルのエミッターの数

#define PARTICLE_VBLANK_LOAD
#define PARTICLE_VBLANK_LOAD_WAIT	(2)

// =========================================
//
//
//	■ENUM
//
//
// =========================================
// -----------------------------------------
//
//	■サウンドコントロール
//
// -----------------------------------------
enum ESE_SYS_MODE {

	ENUM_SEC_NON 		= 0,				///< 動作なし
	ENUM_SEC_PAN_FLOW,						///< パン-位置関係考慮
	ENUM_SEC_PAN_FLOW_FIX,					///< パン-PT無効
	ENUM_SEC_PAN_FLOW_AF,					///< パン-攻撃側考慮
	
	ENUM_SEC_REPEAT,						///< リピート
	
	ENUM_SEC_WAIT_PLAY,						///< wait時間待ってから再生

};

// -----------------------------------------
//
//	■TCB登録モード
//
// -----------------------------------------
enum ETCB_MODE {

	ENUM_WETCB_NONE		= 0,				///< 特になし
	ENUM_WETCB_EFFECT,						///< エフェクト用
	ENUM_WETCB_SOUND,						///< サウンド用

};

// -----------------------------------------
//
//	■その他の定義
//
// -----------------------------------------
enum EWES_DEFINE {
	
	///< αブレンド対象プレーン
	ENUM_WES_BLD_PLANE_1 = GX_BLEND_PLANEMASK_BG0,
	ENUM_WES_BLD_PLANE_2 = GX_BLEND_PLANEMASK_BG1,
	
};

// =========================================
//
//
//	■外部参照：WE-SYSサポート
//
//
// =========================================

// -----------------------------------------
//
// WE-SYS専用 エフェクト用TCB_Add
//
// -----------------------------------------
extern TCB_PTR WEEffect_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
extern TCB_PTR WEEffect_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work);


// -----------------------------------------
//
// WE-SYS専用 サウンド用TCB_Add
//
// -----------------------------------------
extern TCB_PTR WESound_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
extern TCB_PTR WESound_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work);


// -----------------------------------------
//
// WE-SYS専用 エフェクト用TCB_Delete
//
// -----------------------------------------
extern void WEEffect_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb);


// -----------------------------------------
//
// WE-SYS専用 サウンド用TCB_Delete
//
// -----------------------------------------
extern void WESound_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb);


// =========================================
//
//
//	■外部参照：コマンド [ _COMMAND_ ]
//
//
// =========================================
// -----------------------------------------
//
// コマンドの取得
//
// -----------------------------------------
extern pWeFunc WazaEffectCommandGet(u32 id);


// -----------------------------------------
//
// コンテストなのかチェックする
//
// -----------------------------------------
extern int WeSysModeGet(BTL_SYS_PTR blt_sys);


// -----------------------------------------
//
//	パンの状態を取得する
//
// -----------------------------------------
extern s8 WeSysSePanGet(WE_SYS_PTR we_sys, s8 pan);


// -----------------------------------------
//
//	パンの状態を取得する　攻撃用
//
// -----------------------------------------
extern s8 WeSysSePanAttackGet(WE_SYS_PTR we_sys, s8 pan);


// -----------------------------------------
//
//	開始～終点により、パンの加算値を決める
//
// -----------------------------------------
extern s8 WeSysSePanAddGet(s8 s_pan, s8 e_pan,  s8 a_pan);


// -----------------------------------------
//
//	WE-SYSのメンバアクセス関数 基本的にGetのみ
//
// -----------------------------------------
extern int				WeSysHeapAreaGet(WE_SYS_PTR we_sys);
extern u16				WeSysATNoGet(WE_SYS_PTR we_sys);
extern u16				WeSysDFNoGet(WE_SYS_PTR we_sys);
extern PTC_PTR			WeSysPTCPointerGet(WE_SYS_PTR we_sys);
extern PTC_PTR			WeSysPTCPointerNoGet(WE_SYS_PTR we_sys, int no);
extern EMIT_PTR			WeSysEMITPointerGet(WE_SYS_PTR we_sys, int no);
extern GF_BGL_INI*		WeSysBGLPointerGet(WE_SYS_PTR we_sys);
extern s32				WeSysGPWorkGet(WE_SYS_PTR we_sys, int no);
extern BOOL				WeSysExDataGet(WE_SYS_PTR we_sys, int data[], int num);
extern TCATS_OBJECT_ADD_PARAM_S WeSysCoapGet(WE_SYS_PTR we_sys);

extern CATS_ACT_PTR		WeSysOamCapGet(WE_SYS_PTR we_sys, int no);
extern CATS_ACT_PTR		WeSysPokeCapGet(WE_SYS_PTR we_sys, int no);
extern CATS_RES_PTR		WeSysPokeCrpGet(WE_SYS_PTR we_sys);
extern CATS_RES_PTR		WeSysCrpGet(WE_SYS_PTR we_sys);
extern CATS_SYS_PTR		WeSysCspGet(WE_SYS_PTR we_sys);

extern int				WeSysClientTypeGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysSexGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysMonsNoGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysFormNoGet(WE_SYS_PTR we_sys, int no);
extern int				WeSysPersonalRndGet(WE_SYS_PTR we_sys, int no);
extern SOFT_SPRITE*		WeSysSoftSpritePointerGet(WE_SYS_PTR we_sys, int no);
extern void				WeSysAutoMoveStop(WE_SYS_PTR we_sys, int stop_tr);
extern PALETTE_FADE_PTR WeSysPFDGet(WE_SYS_PTR we_sys);
extern int				WeSysPalIDGet(WE_SYS_PTR we_sys, int client_no);
extern int				WeSysArcIDGet(WE_SYS_PTR we_sys, int client_no);
extern int				WeSysPokeOfsGet(WE_SYS_PTR we_sys, int client_no);

extern int				WeSysHaikeiDataIDGet(int id, int no);
extern void				WeSysBaseBGSet(WE_SYS_PTR wsp, int frm);				///< 基本背景を設定する
extern void				WeSysBaseBGReset(WE_SYS_PTR wsp, int frm);				///< 基本背景を設定する

extern BOOL				IsWeSysBattleMode2vs2(WE_SYS_PTR we_sys);
extern void				WeSys_BattleBGDraw(WE_SYS_PTR wsp, int frame);
extern void				WeSys_BattlePaletteTrans(WE_SYS_PTR wsp);

// 戦闘の定義取得関数 (コンテストチェック込み)
#define	WES_BF_WINDOW		(0)
#define	WES_BF_EFFECT		(1)
#define	WES_BF_BACKGROUND	(2)
#define	WES_BF_3DFRAME		(3)

extern int				BT_3DPriorityGet(WE_SYS_PTR we_sys);
extern int				BT_BGL_FrameGet(WE_SYS_PTR we_sys, int type);
extern int				BT_BGL_BGNoGet(WE_SYS_PTR we_sys, int type);
extern int				BT_BGPriorityGet(WE_SYS_PTR we_sys, int type);

///< 戦闘データからエフェクトの影響を及ぼすもの
enum {
	WE_PARA_DAMAGE = 0,		///< ダメージ
	WE_PARA_POW,			///< 威力
	WE_PARA_NATUKI,			///< なつき
	WE_PARA_WEATHER,		///< 天候
	WE_PARA_TURN,			///< ターン数 waza_eff_cnt
	WE_PARA_GROUND_ID,		///< 地形データ
};

extern int WazaEffParaGet(WE_SYS_PTR we_sys, int para_id);


extern void WeSys_PokeChangeParamMake(WE_SYS_PTR we_sys, WAZA_POKE_CHANGE_PARAM* para, int type);
extern void	HenshinChrSet(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);
extern void	HenshinChrPop(WAZA_POKE_CHANGE_PARAM *wpcp, int heap_id);

extern BOOL ContestFlipCheck(WE_SYS_PTR we_sys, int flag);	///< flag == WEDEF_DROP_M1 E1 M2 E2

extern BOOL BT_WazaKoukaCheck(WE_SYS_PTR we_sys, int client_no);

/// サブ

extern void	BT_HaikeiSubSystemStop(WE_SYS_PTR we_sys);
extern void	BT_HaikeiSubSystemFrameChange(WE_SYS_PTR we_sys);
extern int	BT_HaikeiFadeBit(WE_SYS_PTR we_sys);

/// カメラ
extern int	WeSysCameraTypeGet(int no, WE_SYS_PTR we_sys);

/// 主にデバッグで使う
extern void WE_SYS_CameraModeSet(WE_SYS_PTR we_sys, int mode);

// =============================================================================
//
//
//	■OAM落とし　戦闘システム特化
//
//
// =============================================================================
#define OAM_DROP_ALL	(0xFF)
typedef struct {

	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	PALETTE_FADE_PTR	pfd;
	
} OAM_DROP_PARAM;

typedef struct {
	
	int heap;
	int client_no;
	
	OAM_DROP_PARAM	sys;
	
	int				res_id[ CLIENT_MAX ];
	CATS_ACT_PTR	cap[ CLIENT_MAX ];			///< CAP
	EXCHR_PARAM*	excp[ CLIENT_MAX ];			///< キャラバッファ
	u8 			 	client_type[ CLIENT_MAX ];	///< クライアントType
	SOFT_SPRITE*	ss[ CLIENT_MAX ];			///< ソフトスプライト
	
} OAM_DROP_SYS;

extern OAM_DROP_SYS* OAM_Drop_Init(BATTLE_WORK* bw, int heap, int client_no);
extern OAM_DROP_SYS* OAM_DropAll_Init(BATTLE_WORK* bw, int heap);
extern void			 OAM_Drop_End(OAM_DROP_SYS* ods, int client_no);
extern void			 OAM_DropAll_End(OAM_DROP_SYS* ods);
extern CATS_ACT_PTR	 OAM_Drop_CapGet(OAM_DROP_SYS* ods, int client_no);
extern int 			 OAM_Drop_ClientTypeGet(OAM_DROP_SYS* ods);

// =============================================================================
//
//
//	■WE-SYS 説明 [ _EXPLANATION_ ]
//
//
// =============================================================================
/* ----- explanation -----

	■WE-SYSでのタスク登録
	
	01.はじめに
		タスクを登録するコマンドの廃止、関数呼び出しを使って内部でTCB_Add
		TCBはワークを引数としているので、
		コマンド側でワークを用意するのはどーかと思って。
	
	02.利用方法
		エフェクト、サウンドに関しては独自のTCB_Addを利用すること
		関数呼び出しの仲で、サウンド、エフェクトに関するTCBを作成する場合は
		専用関数で登録・開放を行います。
		それ以外のタスクに関しては、規定はありませんが
		関数呼び出しで使用される関数の型は決まっています
		
		・typedef void (*pWeFunc)(WE_SYS_PTR we_sys);
	
	03.注意点
		WE_SYS_PTRのワークは、登録したTCB側では開放しない事！
		ただの関数呼び出しでも上記の型の関数を指定してください。(TCB_Addするだけでも)
	
	■使い方
	例)
	
	追加するTCBのワーク		--	typedef struct { 
									WE_SYS_PTR ws;		///< 必須
									int attack;
									int	count;
								} TSAMPLE_WORK;
									
	追加したいTCB			--	void SampleTCB(TCB_PTR, void* work);
	コマンドで呼び出す関数	--	void SampleTCBCall(WE_SYS_PTR we_sys);
	
	// ------------------------------------------------------------
	//
	//	呼び出し用	(コマンドの引数にする関数です)
	//
	// ------------------------------------------------------------
	void SampleTCBCallSampleTCBCall(WE_SYS_PTR we_sys){
		
		SAMPLE_WORK* wk;
		
		wk = sys_AllocMemory(･･･);
		
		///< ココから用途によって変わります
		
		///< 01.技用のTCB登録
		wk->ws = we_sys;								///< ココでポインタ渡してください
		WEEffect_TCB_Add(wk->ws, SampleTCB, wk, 0x1000);

		///< 02.サウンド用のTCB登録
		wk->ws = we_sys;								///< ココでポインタ渡してください
		WESound_TCB_Add(wk->ws, SampleTCB, wk, 0x1000);

		///< 03.ただのTCB登録
		TCB_Add(SampleTCB, wk, 0x1000);					///< 普通に使ってください
	}
	
	// ------------------------------------------------------------
	//
	//	動作TCB
	//
	// ------------------------------------------------------------	
	void SampleTCB(TCB_PTR tcb, void* work){
		
		TSAMPLE_WORK* wk = (TSAMPLE_WORK*)work;
		
		///< 削除方法が登録方法によって異なります
		
		///< 01.技用のTCB破棄
		WEEffect_TCB_Delete(wk->ws, tcb);
		
		///< 02.サウンド用のTCB破棄
		WESound_TCB_Delete(wk->ws, tcb);
		
		///< 03.ただのTCB破棄
		TCB_Delete(tcb);
		
		///< WE_SYS_PTR の開放は行わないこと
		sys_FreeMemory(wk);
	}

----- explanation -----	*/

#endif


