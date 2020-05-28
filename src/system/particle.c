//==============================================================================
/**
 * @file	particle.c
 * @brief	パーティクル制御ツール
 * @author	matsuda
 * @date	2005.07.04(月)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "spl.h"
#include "wazaeffect/we_err.h"
#include "system/arc_tool.h"

#ifdef PM_DEBUG

	PTC_PTR gDebugPTC = NULL;
	
#endif

//==============================================================================
//	定数定義
//==============================================================================
//SPL_Init
enum{
	EMIT_MAX = 20,			///<1つのリソースで同時に出せる最大エミッタ数
	PARTICLE_MAX = 200,		///<最大パーティクル数
	FIX_POLYGON_ID = 5,		///<固定ポリゴンID
	MIN_POLYGON_ID = 6,		///<最小ポリゴンID
	MAX_POLYGON_ID = 63,	///<最大ポリゴンID
};

///エミッタが生成されていないフラグ
#define NON_EMIT		(0xffff)

///リンクドテクスチャVRAMマネージャで最大管理出来る数
#define LNK_TEX_KEY_MAX		(16)

///リンクドパレットVRAMマネージャで最大管理出来る数
//共用体の相方NNSGfdFrmPlttVramStateと同サイズにするなら2個なんだけど、
//それだとあまりにも数が少ないのでとりあえず8個
#define LNK_PLTT_KEY_MAX	(16)

//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   エミッタパラメータ構造体
 */
//--------------------------------------------------------------
typedef struct{
	SPLEmitter *emit_ptr;			///<エミッタへのポインタ
	u16 res_no;						///<リソース番号
}EMIT_PARAM;

//--------------------------------------------------------------
/**
 * @brief	パーティクルシステム構造体
 */
//--------------------------------------------------------------
typedef struct _PARTICLE_SYSTEM{
	SPLManager *spl_manager;		///<SPLマネージャへのポインタ
//	EMIT_PARAM emitter[EMIT_MAX];	///<エミッタパラメータ
	void *res_ptcl;					///<パーティクルリソースへのポインタ
	SPLEmitter *temp_emit;			///<最後に生成したエミッタのポインタを保持する
	
	void *heap_start;				///<SPLライブラリで使用するワークの先頭アドレス
	void *heap;						///<ヒープの現在の空き領域の先頭アドレスを指す
	void *heap_end;					///<ヒープで使用出来る終了地点のアドレス
	
	pTexCallback user_tex_func;		///<テクスチャVRAMアドレスを返すためのコールバック関数
	pTexCallback user_pltt_func;	///<テクスチャパレットアドレスを返すためのコールバック関数
	
	GF_CAMERA_PTR camera;			///<カメラ
	VecFx32 vec;
	u16 persp_way;					///<投射影の角度
	
	VecFx32 eye;		//カメラの位置ベクトル
	VecFx32 v_up;		//カメラの上方向のベクトルへのポインタ
	VecFx32 at;			//カメラの焦点へのベクトル
	
	union{
		NNSGfdFrmTexVramState tex_frm_state;	///<フレームテクスチャの現在のメモリ確保状態
		NNSGfdTexKey tex_key[LNK_TEX_KEY_MAX];	///<リンクドテクスチャのテクスチャキー
	};
	union{
		NNSGfdFrmPlttVramState pltt_frm_state;		///<フレームパレットの現在のメモリ確保状態
		NNSGfdPlttKey pltt_key[LNK_PLTT_KEY_MAX];	///<リンクドパレットのパレットキー
	};
	
	u8 vram_free;					///<Vramの自動解放モード(PTC_AUTO???_???)
	u8 seq;							///<シーケンス番号
	u8 global_no;					///<使用するグローバル変数番号
	u8 camera_type;					///<カメラの射影方式(GF_CAMERA_PERSPECTIV等)
}PARTICLE_SYSTEM;


//==============================================================================
//	グローバル変数
//==============================================================================
//--------------------------------------------------------------
/**
 * 現在生成されていパーティクルシステムのポインタが入る。
 * SPLライブラリで使用するLocalAlloc関数内で、パーティクルシステムで確保しているヒープ領域の
 * 取得する必要がある。しかしLocalAllocはSPLライブラリで関数の型が決められているため、
 * ヒープ領域のポインタを渡すことが出来ないので、このグローバル変数経由で渡す。
 */
//--------------------------------------------------------------
static void *ParticleSystemPtr[PARTICLE_GLOBAL_MAX];

//--------------------------------------------------------------
/**
 * エミッタ作成時のコールバック関数中で、任意のデータを参照出来るよう、
 * 一時的にここに渡したいデータのポインタを入れる。
 * (自滅エミッタの場合、EmitCreateでNULLポインタが返ってくるので、エミッタ動作を変える場合、
 *  コールバック関数内で変更してあげる必要があるため)
 */
//--------------------------------------------------------------
static void *ParticleTempPtr;

//--------------------------------------------------------------
/**
 * テクスチャロード時のコールバック関数内で、リンクドマネージャーの場合、キー情報を
 * PTCに記憶する必要があるので、ここに一時的にPTCのアドレスをセットしておく
 */
//--------------------------------------------------------------
static PTC_PTR TexLoadTempPtc;


//==============================================================================
//	データ定義
//==============================================================================
///デフォルトのカメラの位置ベクトル
static const VecFx32 DefaultEye = {
//	0, -0x2500, 0x3500
//	0x2500, 0, 0x2200
//	-0x2000, -0x2000, -0x2000
//	-0x300, -0x100, 0x2100
//	0, 0, 0x2100
	0, 0, 0x4000
//	0, 15*0x1000, 0
//	128*0x1000, 128*0x1000, 0x4000
};
///デフォルトのカメラの上方向のベクトル
static const VecFx32 DefaultUp = {
	0, FX32_ONE, 0
};
///デフォルトのカメラの焦点へのベクトル
static const VecFx32 DefaultAt = {
	0, 0, 0
};

//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void *Particle_LocalAlloc_0(u32 size);
static void *Particle_LocalAlloc_1(u32 size);
static void *Particle_LocalAlloc_2(u32 size);
static void *Particle_LocalAlloc_3(u32 size);
static void *Particle_LocalAlloc_4(u32 size);
static void *Particle_LocalAlloc_5(u32 size);
static void *Particle_LocalAlloc_6(u32 size);
static void *Particle_LocalAlloc_7(u32 size);
static void *Particle_LocalAlloc_8(u32 size);
static void *Particle_LocalAlloc_9(u32 size);
static void *Particle_LocalAlloc_10(u32 size);
static void *Particle_LocalAlloc_11(u32 size);
static void *Particle_LocalAlloc_12(u32 size);
static void *Particle_LocalAlloc_13(u32 size);
static void *Particle_LocalAlloc_14(u32 size);
static void *Particle_LocalAlloc_15(u32 size);
static inline void *Particle_LocalAlloc(PARTICLE_SYSTEM *psys, u32 size);
static void Particle_TexLoad(PTC_PTR psys);
static void VWait_TexLoad(TCB_PTR tcb, void *work);

void Particle_SystemExit(PTC_PTR psys);
void Particle_EmitterDeleteAll(PTC_PTR psys);
void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once);

//==============================================================================
//	
//==============================================================================
///パーティクルシステム内で使用する領域確保関数のポインタテーブル
static const SPLAlloc LocalAllocFunc[] = {
	Particle_LocalAlloc_0,
	Particle_LocalAlloc_1,
	Particle_LocalAlloc_2,
	Particle_LocalAlloc_3,
	Particle_LocalAlloc_4,
	Particle_LocalAlloc_5,
	Particle_LocalAlloc_6,
	Particle_LocalAlloc_7,
	Particle_LocalAlloc_8,
	Particle_LocalAlloc_9,
	Particle_LocalAlloc_10,
	Particle_LocalAlloc_11,
	Particle_LocalAlloc_12,
	Particle_LocalAlloc_13,
	Particle_LocalAlloc_14,
	Particle_LocalAlloc_15,
};



#if 0	//------- パーティクル使用例 ---- 2005.07.15(金)

void BattleParticle_TestInit(void)
{
	PARTICLE_SYSTEM *psys;
	
	psys = Particle_SystemCreate(sAllocTex, sAllocTexPalette);
//	psys = Particle_SystemCreate(NULL, sAllocTexPalette);
	TCB_Add(BattleParticle_Main, psys, 20);
}

static void BattleParticle_Main(TCB_PTR tcb, void *work)
{
	PARTICLE_SYSTEM *psys = work;
	void *resource;
	
	switch(psys->seq){
	case 0:
		resource = Particle_ResourceLoad("wazaeffect/effectdata/output5.spa");
		Particle_ResourceSet(psys, resource);
		psys->seq++;
		break;
	case 1:
		Particle_Draw(psys);	//パーティクル描画
		Particle_Calc(psys);	//パーティクル計算
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   テクスチャVRAMアドレスを返すためのコールバック関数
 *
 * @param   size		テクスチャサイズ
 * @param   is4x4comp	4x4圧縮テクスチャであるかどうかのフラグ(TRUE=圧縮テクスチャ)
 *
 * @retval  読み込みを開始するVRAMのアドレス
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
#if 0
	NNSGfdTexKey key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	return NNS_GfdGetTexKeyAddr(key);
#else
	u32 address;
	
	NNSGfdTexKey key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("Vramアドレス＝%#x\n", address);
	return address;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	テクスチャパレットVRAMアドレスを返すためのコールバック関数
 *
 * @param	size		テクスチャサイズ
 * @param	is4pltt		4色パレットであるかどうかのフラグ
 *
 * @retval	読み込みを開始するVRAMのアドレス
 *
 * direct形式のテクスチャの場合、SPL_LoadTexPlttByCallbackFunctionは
 * コールバック関数を呼び出しません。
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
#if 0
	NNSGfdPlttKey key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "パレットエラー");
	}
	return NNS_GfdGetPlttKeyAddr(key);
#else
	return 0x20*4;
#endif
}

#endif	//------------- パーティクル使用例 ---------------------------




//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムで使用するワークの初期化
 *
 * Particle_SystemCreateよりも先にこれを実行する必要があります。
 */
//--------------------------------------------------------------
void Particle_SystemWorkInit(void)
{
	int i;
	
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		ParticleSystemPtr[i] = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムを作成する
 *
 * @param   tex_func		テクスチャロード時、使用するVramアドレスを返す関数へのポインタ
 * @param   pltt_func		テクスチャロード時、使用するパレットVramアドレスを返す関数へのポインタ
 * @param   work			SPLライブラリで使用するために割り当てるワークのポインタ
 * @param   work_size		渡したワークのサイズ(PARTICLE_LIB_HEAP_SIZEと同等OR以上のサイズが必要)
 * @param   personal_camera		パーティクル独自のカメラ設定を持つ場合はTRUE。
 * @param   heap_id			パーティクルシステム作成に使用するヒープID
 *
 * @retval  パーティクルシステムワークへのポインタ(生成出来なかった場合はNULL)
 *
 * tex_func, pltt_func にNULL指定した場合はNitroSystemのVram、Plttマネージャに依存します。
 *
 * workで渡したワークはSPLライブラリで使用します。
 * Allocして手に入れたワーク領域のポインタを渡した場合、Particle_SystemExit後、外側で
 * 解放処理を行ってください。(パーティクルシステム側でワークの解放処理はしません)
 *
 * global_no：パーティクルシステム内でSPLライブラリとのやり取りでグローバル変数を使用します。
 * その為のグローバル変数が配列で既に用意されています。その何番目のグローバル変数を使用して、
 * パーティクルシステムを動かすか、という指定です。
 * 用意されているグローバル変数には限りがあります。(2005.07.26(火)現在は3つ(0～2))
 */
//--------------------------------------------------------------
PTC_PTR Particle_SystemCreate(pTexCallback tex_func, pTexCallback pltt_func, void *work, int work_size, int personal_camera, int heap_id)
{
	PARTICLE_SYSTEM *psys;
	int global_no;
	
	//グローバル変数の空きをサーチ
	for(global_no = 0; global_no < PARTICLE_GLOBAL_MAX; global_no++){
		if(ParticleSystemPtr[global_no] == NULL){
			break;
		}
	}
	if(global_no >= PARTICLE_GLOBAL_MAX){
		return NULL;
	}
	
	//パーティクルシステムのメモリ確保
	psys = sys_AllocMemory(heap_id, sizeof(PARTICLE_SYSTEM));
	if(psys == NULL){
		GF_ASSERT(0 && "メモリ確保失敗\n");
	}
	memset(psys, 0, sizeof(PARTICLE_SYSTEM));

	//パラメータ初期設定
	psys->user_tex_func = tex_func;
	psys->user_pltt_func = pltt_func;

	psys->eye = DefaultEye;
	psys->v_up = DefaultUp;
	psys->at = DefaultAt;

	//メモリ設定
	SDK_ASSERT(global_no < PARTICLE_GLOBAL_MAX);
	memset(work, 0, work_size);
	psys->heap_start = work;
	psys->heap = work;
	psys->heap_end = (void*)((u32)work + work_size);
	psys->global_no = global_no;
	ParticleSystemPtr[global_no] = psys;
	
	//カメラ設定
	if(personal_camera == TRUE){
		psys->camera = GFC_AllocCamera(heap_id);
		{
			VEC_Set(&psys->vec, 0, 0, 0);
			psys->persp_way = 8192;//0x06c1;
		#if 0
			GFC_InitCameraTDA(&psys->vec,
						0x1000,					//距離
						&psys->angle,
						psys->persp_way,		//投射影の角度
						GF_CAMERA_PERSPECTIV,
						psys->camera
						);
		#elif 0
			GFC_InitCameraCDA(&psys->vec,
						0x1000,					//距離
						&psys->angle,
						psys->persp_way,		//投射影の角度
						GF_CAMERA_PERSPECTIV,
						psys->camera
						);
		#else
			GFC_InitCameraTC(&DefaultAt, &DefaultEye,
						psys->persp_way,		//投射影の角度
						GF_CAMERA_PERSPECTIV,
						FALSE,
						psys->camera
						);
		#endif
			psys->camera_type = GF_CAMERA_PERSPECTIV;
			GFC_AttachCamera(psys->camera);
		}
	}

	// パーティクルマネージャを初期化
	psys->spl_manager = SPL_Init(LocalAllocFunc[global_no], EMIT_MAX, PARTICLE_MAX, 
		FIX_POLYGON_ID, MIN_POLYGON_ID, MAX_POLYGON_ID);
	
	Particle_SetVup(psys, &DefaultUp);
	
	return psys;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム終了処理
 *
 * @param   パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
void Particle_SystemExit(PTC_PTR psys)
{
	int i;
	
	SDK_ASSERT(psys != NULL);
	SDK_ASSERT(psys->spl_manager != NULL);

	//エミッタ全削除
	Particle_EmitterDeleteAll(psys);
	
	//テクスチャVram自動解放
	if(psys->vram_free & PTC_AUTOTEX_FRM){
		NNS_GfdSetFrmTexVramState(&psys->tex_frm_state);
	}
	else if(psys->vram_free & PTC_AUTOTEX_LNK){
		//2005.07.25(月)　現在未実装 だけど削除自体の処理は作れるので、削除だけは作成
		int i;
		for(i = 0; i < LNK_TEX_KEY_MAX; i++){
			if(psys->tex_key[i] != NNS_GFD_ALLOC_ERROR_TEXKEY){
				NNS_GfdFreeLnkTexVram(psys->tex_key[i]);
				psys->tex_key[i] = NNS_GFD_ALLOC_ERROR_TEXKEY;
			}
		}
	}
	//パレットVram自動解放パラメータ初期化
	if(psys->vram_free & PTC_AUTOPLTT_FRM){
		NNS_GfdSetFrmPlttVramState(&psys->pltt_frm_state);
	}
	else if(psys->vram_free & PTC_AUTOPLTT_LNK){
		//2005.07.25(月)　現在未実装 だけど削除自体の処理は作れるので、削除だけは作成
		int i;
		for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
			if(psys->pltt_key[i] != NNS_GFD_ALLOC_ERROR_PLTTKEY){
				NNS_GfdFreeLnkPlttVram(psys->pltt_key[i]);
				psys->pltt_key[i] = NNS_GFD_ALLOC_ERROR_PLTTKEY;
			}
		}
	}
	psys->vram_free = PTC_AUTOTEX_NULL | PTC_AUTOPLTT_NULL;
	psys->temp_emit = NULL;

	//リソースファイルを読み込んでいるメモリを解放
	if(psys->res_ptcl != NULL){
		sys_FreeMemoryEz(psys->res_ptcl);
		psys->res_ptcl = NULL;
	}
	
	//パーティクルシステムのワーク解放
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] == psys){
			ParticleSystemPtr[i] = NULL;
			break;
		}
	}
	SDK_ASSERT(i < PARTICLE_GLOBAL_MAX); //ParticleSystemPtrに引っかからないということは不正な値
	
	//カメラ解放
	if(psys->camera != NULL){
		GFC_FreeCamera(psys->camera);
	}

	sys_FreeMemoryEz(psys);
}

//--------------------------------------------------------------
/**
 * @brief   生成されているパーティクルシステム全てを終了させる
 */
//--------------------------------------------------------------
void Particle_SystemExitAll(void)
{
	int i;
	
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_SystemExit(ParticleSystemPtr[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 *
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static inline void *Particle_LocalAlloc(PARTICLE_SYSTEM *psys, u32 size)
{
	void *work;
	u32 heap_adrs, rem;
	
	work = psys->heap;
	
	heap_adrs = (u32)psys->heap + size;
	rem = heap_adrs % 4;
	if(rem > 0){
		heap_adrs += 4 - rem;	//4バイト補正
	}
	psys->heap = (void*)heap_adrs;

	if(psys->heap >= psys->heap_end){
		GF_ASSERT(0 && "パーティクルシステムでメモリオーバーが発生しました！\n");
	}
	return work;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_0(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_0];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_1(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_1];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_2(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_2];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_3(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_3];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_4(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_4];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_5(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_5];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_6(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_6];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_7(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_7];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_8(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_8];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_9(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_9];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_10(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_10];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_11(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_11];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_12(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_12];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_13(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_13];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_14(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_14];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステム内で使用するAlloc関数
 * @param   size		確保するメモリサイズ
 *
 * SPL_Initで関数ポインタとして渡しているので、この関数の形を変えてはいけない。
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_15(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_15];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルのリソースファイルを読み込む
 *
 * @param   heap_id		ヒープID
 * @param   path		読み込むリソースファイル(*.spa)へのポインタ
 *
 * @retval  読み込んだリソースファイルのポインタ
 *
 * Particle_ResourceSet関数とセットで使用する事が前提です。
 * 読み込んだリソースファイルはParticle_SystemExitでFreeMemoryされます。
 */
//--------------------------------------------------------------
void * Particle_ResourceLoad(int heap_id, const char *path)
{
	return sys_LoadFile(heap_id, path);
}

//--------------------------------------------------------------
/**
 * @brief   Arcされているパーティクルのリソースファイルを読み込む
 *
 * @param   file_kind	読み込むアーカイブファイルの種類インデックスナンバー（arc_tool.hに記述)
 * @param   index		読み込むデータのアーカイブファイル上のインデックスナンバー
 * @param   heap_id		ヒープID
 *
 * @retval  読み込んだリソースファイルのポインタ
 *
 * Particle_ResourceSet関数とセットで使用する事が前提です。
 * 読み込んだリソースファイルはParticle_SystemExitでFreeMemoryされます。
 */
//--------------------------------------------------------------
void * Particle_ArcResourceLoad(int file_kind, int index, int heap_id)
{
	return ArchiveDataLoadMalloc(file_kind, index, heap_id);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルのリソースファイルをパーティクルシステムにセットし初期化を行う
 *
 * @param   psys			パーティクルシステムワークへのポインタ
 * @param   resource		Particle_(Arc)ResourceLoadで読み込んだリソースファイルのポインタ
 * @param   vram_free		Vramの自動解放(ビット指定：PTC_AUTOTEX_??? | PTC_AUTOPLTT_???)
 * @param   tex_at_once		TRUE:テクスチャ即転送、FALSE:Vブランク中に転送
 *
 * vram_free補足:モードを有効にすることで、Particle_SystemExit時にテクスチャで占有したVram状態を
 * LoadFile実行前の状態に戻します。
 * 但しParticle_SystemCreate時に、テクスチャのコールバック関数を設定しなかった場合はSPLライブラリの
 * 動作に依存することになります。(多分自動で解放してくれるんじゃないでしょうか…)
 */
//--------------------------------------------------------------
void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once)
{
	GF_ASSERT(psys->spl_manager != NULL);
	GF_ASSERT(psys->res_ptcl == NULL);
	
	psys->vram_free = vram_free;
	//テクスチャVram自動解放パラメータ初期化
	if(vram_free & PTC_AUTOTEX_FRM){
		NNS_GfdGetFrmTexVramState(&psys->tex_frm_state);
	}
	else if(vram_free & PTC_AUTOTEX_LNK){
		//2005.07.25(月)　現在未実装(関数コメントにも状態が書いてあります)
		//とりあえず初期化だけしておく
		int i;
		for(i = 0; i < LNK_TEX_KEY_MAX; i++){
			psys->tex_key[i] = NNS_GFD_ALLOC_ERROR_TEXKEY;
		}
	}
	//パレットVram自動解放パラメータ初期化
	if(vram_free & PTC_AUTOPLTT_FRM){
		NNS_GfdGetFrmPlttVramState(&psys->pltt_frm_state);
	}
	else if(vram_free & PTC_AUTOPLTT_LNK){
		//2005.07.25(月)　現在未実装(関数コメントにも状態が書いてあります)
		//とりあえず初期化だけしておく
		int i;
		for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
			psys->pltt_key[i] = NNS_GFD_ALLOC_ERROR_PLTTKEY;
		}
	}
	
	//パーティクルリソースを関連付ける
	psys->res_ptcl = resource;
	
	//テクスチャロード
	if(tex_at_once == TRUE){
		Particle_TexLoad(psys);
	}
	else{
		VWaitTCB_Add(VWait_TexLoad, psys, 5);
	}
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルのテクスチャーロード
 * @param   psys		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Particle_TexLoad(PTC_PTR psys)
{
	//マネージャに対してパーティクルリソースを読み込む
	SPL_Load(psys->spl_manager, psys->res_ptcl);

	// テクスチャを読み込み
	TexLoadTempPtc = psys;
	if(psys->user_tex_func == NULL){
		//NitroSystemのVRAMマネージャに依存する
		(void)SPL_LoadTexByVRAMManager(psys->spl_manager);
	}
	else{
		// コールバック関数を用いてテクスチャ読み込みを自前でおこなう場合
		SPL_LoadTexByCallbackFunction(psys->spl_manager, psys->user_tex_func);
	}
	if(psys->user_pltt_func == NULL){
		(void)SPL_LoadTexPlttByVRAMManager(psys->spl_manager);
	}
	else{
		SPL_LoadTexPlttByCallbackFunction(psys->spl_manager, psys->user_pltt_func);
	}
	TexLoadTempPtc = NULL;

	{
		u32 tex_size;
		tex_size = SPL_GetTexSizeOnResource(psys->res_ptcl);
	#ifdef OSP_PARTICLE_ON
		OS_Printf("テクスチャサイズ＝%#x\n", tex_size);
	#endif
	}
}

//--------------------------------------------------------------
/**
 * @brief   Vブランクタスク：パーティクルのテクスチャーロード
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_TexLoad(TCB_PTR tcb, void *work)
{
	PTC_PTR psys = work;
	
	Particle_TexLoad(psys);
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   リンクドリストのテクスチャキーを記憶する
 *
 * @param   psys		パーティクルシステムワークへのポインタ
 * @param   tex_key		テクスチャキー
 *
 * ※テクスチャロード時のコールバック関数内でのみ呼ぶ事が許されます
 */
//--------------------------------------------------------------
void Particle_LnkTexKeySet(NNSGfdTexKey tex_key)
{
	int i;
	PTC_PTR psys;
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(TexLoadTempPtc != NULL);
	
	psys = TexLoadTempPtc;
	
	for(i = 0; i < LNK_TEX_KEY_MAX; i++){
		if(psys->tex_key[i] == NNS_GFD_ALLOC_ERROR_TEXKEY){
			psys->tex_key[i] = tex_key;
			return;
		}
	}
	GF_ASSERT(0 && "パーティクルテクスチャ管理数を超えています!\n");
}

//--------------------------------------------------------------
/**
 * @brief   パレットリンクドリストのテクスチャキーを記憶する
 *
 * @param   psys		パーティクルシステムワークへのポインタ
 * @param   tex_key		テクスチャキー
 *
 * ※テクスチャロード時のコールバック関数内でのみ呼ぶ事が許されます
 */
//--------------------------------------------------------------
void Particle_PlttLnkTexKeySet(NNSGfdPlttKey pltt_key)
{
	int i;
	PTC_PTR psys;
	
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	GF_ASSERT(TexLoadTempPtc != NULL);
	
	psys = TexLoadTempPtc;
	
	for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
		if(psys->pltt_key[i] == NNS_GFD_ALLOC_ERROR_PLTTKEY){
			psys->pltt_key[i] = pltt_key;
			return;
		}
	}
	GF_ASSERT(0 && "パーティクルパレットテクスチャ管理数を超えています!\n");
}

#ifdef PM_DEBUG		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   キー入力によってカメラの位置を移動する(デバッグ機能)
 * @param   psys		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void DebugCameraMove(PTC_PTR psys)
{
	const fx32 a = FX32_ONE / 0x10;
	int flag = 0;
	
	if((sys.trg & PAD_BUTTON_START) && (sys.cont & PAD_BUTTON_R) && (sys.cont & PAD_BUTTON_L)){
		WeDebugWork.eye = DefaultEye;
		WeDebugWork.up = DefaultUp;
		WeDebugWork.at = DefaultAt;
		OS_Printf("DebugCamera:標準設定に戻しました\n");
		return;
	}
	
	if(sys.cont & PAD_BUTTON_R){
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.up.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.up.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.up.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.up.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.up.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.up.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("v_up: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.up.x, WeDebugWork.up.y, WeDebugWork.up.z);
		}
	}
	else if(sys.cont & PAD_BUTTON_L){
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.at.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.at.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.at.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.at.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.at.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.at.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("at: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.at.x, WeDebugWork.at.y, WeDebugWork.at.z);
		}
	}
	else{
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.eye.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.eye.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.eye.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.eye.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.eye.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.eye.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("eye: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.eye.x, WeDebugWork.eye.y, WeDebugWork.eye.z);
		}
	}
}
#endif		//+++++++++++++++++++++++++ PM_DEBUG ++++++++++++++++++++++++++++++++++++++

//--------------------------------------------------------------
/**
 * @brief	描画
 */
//--------------------------------------------------------------
void Particle_Draw(PTC_PTR psys)
{
	const MtxFx43 *camera_ptr;

#ifdef PM_DEBUG
	if((sys.cont & PAD_BUTTON_SELECT) && (sys.trg & PAD_BUTTON_START)){
		WeDebugWork.debug_flag ^= WE_DEBUG_BIT_CAMERA;
		if(WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA){
			WeDebugWork.eye = DefaultEye;
			WeDebugWork.up = DefaultUp;
			WeDebugWork.at = DefaultAt;
		}
		OS_Printf("デバッグカメラ移動 = %d\n", WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA);
	}
	if(WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA){
		DebugCameraMove(psys);
		psys->eye = WeDebugWork.eye;
		psys->v_up = WeDebugWork.up;
		psys->at = WeDebugWork.at;
	}
#endif

	if(psys->camera != NULL){
		GFC_SetCameraView(psys->camera_type, psys->camera);
		GFC_AttachCamera(psys->camera);
		GFC_CameraLookAt();
	}
	
	//グローバルステートを適用
	NNS_G3dGlbFlush();

	// パーティクル描画
	camera_ptr = NNS_G3dGlbGetCameraMtx();
	SPL_Draw(psys->spl_manager, camera_ptr);

	if(psys->camera != NULL){
		GFC_PurgeCamera();
	}

	//再びグローバルステートを適用。サンプルのSimpleがこうやってるんで真似。
	NNS_G3dGlbFlush();
}

//--------------------------------------------------------------
/**
 * @brief	計算
 */
//--------------------------------------------------------------
void Particle_Calc(PTC_PTR psys)
{
	SPL_Calc(psys->spl_manager);
}

//--------------------------------------------------------------
/**
 * @brief   実際に動作しているパーティクルマネージャの数を取得する
 * @retval  実行されているマネージャ数
 */
//--------------------------------------------------------------
int Particle_GetActionNum(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   生成されているパーティクルシステム全ての描画を行う
 * @retval  描画が行われた回数
 */
//--------------------------------------------------------------
int Particle_DrawAll(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_Draw(ParticleSystemPtr[i]);
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   生成されているパーティクルシステム全ての計算を行う
 * @retval  計算が行われた回数
 */
//--------------------------------------------------------------
int Particle_CalcAll(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_Calc(ParticleSystemPtr[i]);
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタを生成
 *
 * @param   psys			パーティクルシステムワークへのポインタ
 * @param   res_no			リソース番号
 * @param   init_pos		位置(リソースに設定されたエミッタオフセット位置に加算します)
 *
 * @retval  生成されたエミッタへのポインタ。自滅エミッタの場合はNULLが返ります
 */
//--------------------------------------------------------------
EMIT_PTR Particle_CreateEmitter(PTC_PTR psys, int res_no, const VecFx32 *init_pos)
{
	EMIT_PTR emit;
	
	emit = SPL_Create(psys->spl_manager, res_no, init_pos);
	psys->temp_emit = emit;
#if 0
	if(emit != NULL){
		SPL_Terminate(emit);
	}
#endif
	return emit;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタを生成(生成した時にcallbackに登録した関数が実行されます)
 *
 * @param   psys			パーティクルシステムワークへのポインタ
 * @param   res_no			リソース番号
 * @param   callback		エミッタ生成時に呼び出されるコールバック関数へのポインタ
 * @param   temp_ptr		コールバック関数の中でParticle_GetTempPtr関数を使う事で、
 *                          ここで渡したポインタを取得する事が出来ます。
 *                          Particle_GetTempPtr関数が使えるのはコールバック関数内のみです。
 *
 * @retval  生成されたエミッタへのポインタ。自滅エミッタの場合はNULLが返ります
 *
 * 自滅エミッタをSPL_Createで作成した場合、NULLがかえってくるのでエミッタの設定をプログラムから
 * 変更することはできません。この関数をもちいてSPLEmitter*を引数とするコールバックを登録する
 * ことで、自滅前の自滅エミッタへのポインタを引数としてコールバック関数が呼び出されます。
 * このコールバック関数中でエミッタの設定を変更することが可能です。 
 */
//--------------------------------------------------------------
EMIT_PTR Particle_CreateEmitterCallback(PTC_PTR psys, int res_no, pEmitFunc callback, void *temp_ptr)
{
	EMIT_PTR emit;
	
	ParticleTempPtr = temp_ptr;
	emit = SPL_CreateWithInitialize(psys->spl_manager, res_no, callback);
	ParticleTempPtr = NULL;
	psys->temp_emit = emit;

	return emit;
}

//--------------------------------------------------------------
/**
 * @brief   アクティブなエミッタの数を取得します
 *
 * @param   psys		パーティクルシステムワークへのポインタ
 *
 * @retval  アクティブなエミッタ数
 */
//--------------------------------------------------------------
s32 Particle_GetEmitterNum(PTC_PTR psys)
{
	return SPL_GetEmitterNum(psys->spl_manager);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムワークが管理しているパーティクルを全て削除
 * @param   psys		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
void Particle_EmitterDeleteAll(PTC_PTR psys)
{
	SPL_DeleteAll(psys->spl_manager);	//パーティクル全削除
}

//--------------------------------------------------------------
/**
 * @brief	emitter1個削除
 *
 * @param	psys	
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void Particle_EmitterDelete(PTC_PTR psys, EMIT_PTR emit)
{
	SPL_Delete(psys->spl_manager, emit);	//パーティクル全削除
}


//--------------------------------------------------------------
/**
 * @brief   最後に生成したエミッタのポインタを取得する
 *
 * @param   psys		パーティクルシステムワークへのポインタ
 *
 * @retval  最後に生成したエミッタのポインタ
 */
//--------------------------------------------------------------
EMIT_PTR Particle_TempEmitterPtrGet(PTC_PTR psys)
{
	return psys->temp_emit;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムワークに設定されているヒープ領域の先頭アドレスを取得
 *
 * @param   psys		パーティクルシステムワークへのポインタ
 *
 * @retval  ヒープの先頭アドレス(Particle_SystemCreateで渡したアドレスが返ります)
 */
//--------------------------------------------------------------
void * Particle_HeapPtrGet(PTC_PTR psys)
{
	return psys->heap_start;
}

//--------------------------------------------------------------
/**
 * @brief   カメラの位置ベクトルを取得
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @param   eye		値代入先
 */
//--------------------------------------------------------------
void Particle_GetEye(PTC_PTR psys, VecFx32 *eye)
{
	*eye = psys->eye;
}

//--------------------------------------------------------------
/**
 * @brief   カメラの位置ベクトルをセット
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @param   eye		値代入先
 *
 * GFLibのカメラを使用している場合はこれは機能しません
 */
//--------------------------------------------------------------
void Particle_SetEye(PTC_PTR psys, const VecFx32 *eye)
{
	psys->eye = *eye;
}

//--------------------------------------------------------------
/**
 * @brief   カメラの上方向ベクトルを取得
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @param   v_up		値代入先
 */
//--------------------------------------------------------------
void Particle_GetVup(PTC_PTR psys, VecFx32 *v_up)
{
	*v_up = psys->v_up;
}

//--------------------------------------------------------------
/**
 * @brief   カメラの上方向ベクトルをセット
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @param   v_up		値代入先
 */
//--------------------------------------------------------------
void Particle_SetVup(PTC_PTR psys, const VecFx32 *v_up)
{
	psys->v_up = *v_up;
	GFC_SetCamUp(v_up, psys->camera);
}

//--------------------------------------------------------------
/**
 * @brief   テンポラリワークにセットされているポインタを取得する
 * @retval  テンポラリワークにセットされているポインタ
 *
 * エミッタ作成時のコールバック関数内でのみ使用可能です。
 */
//--------------------------------------------------------------
void * Particle_GetTempPtr(void)
{
	SDK_ASSERT(ParticleTempPtr != NULL);
	return ParticleTempPtr;
}

//--------------------------------------------------------------
/**
 * @brief   デフォルトカメラ位置ベクトルを取得
 * @param   eye		値代入先
 */
//--------------------------------------------------------------
void Particle_GetDefaultEye(VecFx32 *eye)
{
	*eye = DefaultEye;
}

//--------------------------------------------------------------
/**
 * @brief   デフォルトカメラの上方向ベクトルを取得
 * @param   eye		値代入先
 */
//--------------------------------------------------------------
void Particle_GetDefaultUp(VecFx32 *v_up)
{
	*v_up = DefaultUp;
}

//--------------------------------------------------------------
/**
 * @brief   デフォルトカメラの焦点へのベクトルを取得
 * @param   eye		値代入先
 */
//--------------------------------------------------------------
void Particle_GetDefaultAt(VecFx32 *at)
{
	*at = DefaultAt;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムが持っているカメラのポインタを取得します
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @retval  GFカメラへのポインタ(独自のカメラを使用していない場合はNULL)
 */
//--------------------------------------------------------------
GF_CAMERA_PTR Particle_GetCameraPtr(PTC_PTR ptc)
{
	return ptc->camera;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムのカメラ射影方式をセットする
 * @param   ptc				パーティクルシステムワークへのポインタ
 * @param   camera_type		GF_CAMERA_PERSPECTIV or GF_CAMERA_ORTHO
 */
//--------------------------------------------------------------
void Particle_CameraTypeSet(PTC_PTR ptc, int camera_type)
{
	ptc->camera_type = camera_type;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムのカメラ射影方式を取得する
 * @param   ptc		パーティクルシステムワークへのポインタ
 * @retval  GF_CAMERA_PERSPECTIV or GF_CAMERA_ORTHO
 */
//--------------------------------------------------------------
u8 Particle_CameraTypeGet(PTC_PTR ptc)
{
	return ptc->camera_type;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの速度を取得します
 *
 * @param   emit	エミッタへのポインタ
 * @param   vel		値代入先
 */
//--------------------------------------------------------------
void SplSub_GetEmitterVelocity(EMIT_PTR emit, VecFx32 *vel)
{
	*vel = emit->emtr_vel;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの速度をセットします
 *
 * @param   emit	エミッタへのポインタ
 * @param   vel		セットする値
 */
//--------------------------------------------------------------
void SplSub_SetEmitterVelocity(EMIT_PTR emit, const VecFx32 *vel)
{
	SPL_SetEmitterVelocity(emit, vel);
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの向きを取得
 * @param   emit		エミッタへのポインタ
 * @param   vec			値代入先
 */
//--------------------------------------------------------------
void SplSub_GetEmitterAxis(EMIT_PTR emit, VecFx16 *vec)
{
	*vec = emit->axis;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの大きさを取得
 * @param   emit		エミッタへのポインタ
 * @retval  大きさ
 */
//--------------------------------------------------------------
fx32 SplSub_GetEmitterRadius(EMIT_PTR emit)
{
	return emit->radius;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの全方向初速を取得
 * @param   emit		エミッタへのポインタ
 * @retval  全方向初速
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterInitVelocityPos(EMIT_PTR emit)
{
	return emit->init_vel_mag_pos;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの軸方向初速を取得
 * @param   emit		エミッタへのポインタ
 * @retval  軸方向初速
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterInitVelocityAxis(EMIT_PTR emit)
{
	return emit->init_vel_mag_axis;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの基本スケールを取得
 * @param   emit		エミッタへのポインタ
 * @retval  基本スケール
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterBaseScale(EMIT_PTR emit)
{
	return emit->base_scl;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの生成間隔を取得
 * @param   emit		エミッタへのポインタ
 * @retval  生成間隔
 */
//--------------------------------------------------------------
u16 SplSub_GetEmitterEmissionInterval(EMIT_PTR emit)
{
	return emit->etc.gen_intvl;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの基本αを取得
 * @param   emit		エミッタへのポインタ
 * @retval  基本α
 */
//--------------------------------------------------------------
u16 SplSub_GetEmitterBaseAlpha(EMIT_PTR emit)
{
	return emit->etc.base_alp;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタのグローバル色を取得
 * @param   emit		エミッタへのポインタ
 * @retval  グローバル色
 */
//--------------------------------------------------------------
GXRgb SplSub_GetEmitterGlobalColor(EMIT_PTR emit)
{
	return emit->clr;
}

//--------------------------------------------------------------
/**
 * @brief   指定したエミッタの放出レートを設定します
 *
 * @param   emit		エミッタへのポインタ
 * @param   gen_num		設定放出レート
 *
 * SPL_SetEmitterGenerationRatio関数がないようなので代わり
 */
//--------------------------------------------------------------
void SplSub_SetEmitterGenerationRatio(EMIT_PTR emit, fx32 gen_num)
{
	emit->p_res->p_base->gen_num = gen_num;
}

//--------------------------------------------------------------
/**
 * @brief   放出レートを取得します
 * @param   emit		エミッタへのポインタ
 * @retval  放出レート
 */
//--------------------------------------------------------------
fx32 SplSub_GetEmitterGenerationRatio(EMIT_PTR emit)
{
	return emit->p_res->p_base->gen_num;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタの現在位置を取得する
 *
 * @param   p_emtr		エミッタへのポインタ
 * @param   p_pos		取得座標代入先
 */
//--------------------------------------------------------------
void SplSub_GetEmitterPosition(EMIT_PTR emit, VecFx32 * p_pos)
{
	*p_pos = emit->emtr_pos;
}

//--------------------------------------------------------------
/**
 * @brief   エミッタのデフォルト位置を取得する
 *
 * @param   emit		エミッタへのポインタ
 * @param   p_pos		取得座標代入先
 */
//--------------------------------------------------------------
void SplSub_GetEmitterBasePosition(EMIT_PTR emit, VecFx32 * p_pos)
{
	*p_pos = emit->p_res->p_base->pos;
}


// ----------------------------------------------------------------------------
//
//
//
//
//
//	□ Field 操作系の独自関数郡
//		パーティクルライブラリ側でprivateで扱われる変数を
//		外から扱っているので不具合があるかもしれない
//
//
//
//
// ----------------------------------------------------------------------------
#if 0

typedef struct SPLGravity{				// 重力フィールド
    VecFx16 mag;
    u16 reserved0;
} SPLGravity;

typedef struct SPLRandom{				// ランダムフィールド
    VecFx16 mag;
    u16 intvl;
} SPLRandom;

typedef struct SPLMagnet{				// マグネットフィールド
    VecFx32 pos;
    fx16    mag;
    u16     reserved0;
} SPLMagnet;

typedef struct SPLSpin{					// スピンフィールド
    u16 radian;
    u16 axis_type;
} SPLSpin;

typedef struct SPLSimpleCollisionField{	// シンプルコリジョンフィールド
    fx32 y ; // イベントが起こるy平面の値
    fx16 coeff_bounce ;
    
    struct {
        u16 eventtype:2 ;
        u16 global:1 ;
        u16 reserved:13 ;
    } etc ;
} SPLSimpleCollisionField ;

typedef struct SPLConvergence{			// 位置に加算フィールド（マグネットの亜種）
    VecFx32 pos  ; // 吸い寄せられる場所
    fx16    ratio; // 吸い寄せられる強さ
    u16     reserved0;
} SPLConvergence ;

void spl_calc_gravity(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_random(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_magnet(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_spin(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_scfield(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_convergence(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );

#endif

enum {
	SPL_FLD_TYPE_GRAVITY = 0,		///< 重力
	SPL_FLD_TYPE_RANDOM,			///< ランダム
	SPL_FLD_TYPE_MAGNET,			///< マグネット
	SPL_FLD_TYPE_SPIN,				///< スピン
	SPL_FLD_TYPE_SIMPLE_COLL,		///< シンプルコリジョン
	SPL_FLD_TYPE_CONVERGENCE,		///< コンバージェンス
};


//--------------------------------------------------------------
/**
 * @brief	SPL_FieldObject のポインタ取得
 *
 * @param	emit					エミッター
 * @param	field_type				取得フィールドのタイプ
 *
 * @retval	static const void*		ポインタ
 *
 */
//--------------------------------------------------------------
static const void* SPLFieldObj_PointerSearch(EMIT_PTR emit, int field_type)
{
	int i;
	int num;
	SPLField* p_field;
	
	num = emit->p_res->fld_num;
	
	if (num == 0){
		return NULL;
	}
	
	for (i = 0; i < num; i++){
		
		p_field = &emit->p_res->fld_ary[i];
		
		if (p_field == NULL){ continue; }
		
		switch(field_type){
		case SPL_FLD_TYPE_GRAVITY:
			if (p_field->p_exec == spl_calc_gravity){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_RANDOM:
			if (p_field->p_exec == spl_calc_random){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_MAGNET:
			if (p_field->p_exec == spl_calc_magnet){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_SPIN:
			if (p_field->p_exec == spl_calc_spin){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_SIMPLE_COLL:
			if (p_field->p_exec == spl_calc_scfield){
				return p_field->p_obj;
			}
			break;
		case SPL_FLD_TYPE_CONVERGENCE:
			if (p_field->p_exec == spl_calc_convergence){
				return p_field->p_obj;
			}
			continue;
		default:
			return NULL;
		}		
	}
	
	return NULL;
}

// -----------------------------------------
//
//	重力
//
//--------------------------------------------------------------
///< 重力の座標操作
void SplSub_SetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag)
{
	SPLGravity* p_obj;
	
	p_obj = (SPLGravity*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_GRAVITY);
	
	if (p_obj == NULL){ return; }
	
	p_obj->mag = *mag;
}

void SplSub_GetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag)
{
	SPLGravity* p_obj;
	
	p_obj = (SPLGravity*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_GRAVITY);
	
	if (p_obj == NULL){
		VecFx16 err_p = { 0,0,0 };
		*mag = err_p;
		return;
	}
			
	*mag = p_obj->mag;
}


// -----------------------------------------
//
//	ランダム
//
// -----------------------------------------
///< 使う必要があるか不明なのでとりあえず未実装
void SplSub_SetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag)
{
}
void SplSub_GetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag)
{
}
void SplSub_SetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag)
{
}
void SplSub_GetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag)
{
}

// -----------------------------------------
//
// マグネット
//
// -----------------------------------------
///< マグネットの座標操作
void SplSub_SetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){ return; }
			
	p_obj->pos = *p_pos;
}

void SplSub_GetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){
		VecFx32 err_p = { 0,0,0 };
		*p_pos = err_p;
		return;
	}
	
	*p_pos = p_obj->pos;
}

///< マグネットのマグ操作
void SplSub_SetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){ return; }
			
	p_obj->mag = *mag;
}

void SplSub_GetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){
		*mag = 0;
		return;
	}

	*mag = p_obj->mag;
}


// -----------------------------------------
//
//	スピン
//
// -----------------------------------------
///< スピンの角度操作
void SplSub_SetSPLField_SpinRad(EMIT_PTR emit, u16* rad)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){ return; }
	
	p_obj->radian = *rad;
}

void SplSub_GetSPLField_SpinRad(EMIT_PTR emit, u16* rad)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){
		*rad = 0;
		return;
	}
	
	*rad = p_obj->radian;
}

///< スピンの方向タイプ操作
void SplSub_SetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){ return; }
	
	p_obj->axis_type = *axis_type;
}

void SplSub_GetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){
		*axis_type = 0;
		return;
	}
	
	*axis_type = p_obj->axis_type;
}

// -----------------------------------------
//
//	シンプルコリジョン
//
// -----------------------------------------
///< 操作する必要があるか不明なので、とりあえず未実装
void SplSub_SetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y)
{
}
void SplSub_GetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y)
{
}
void SplSub_SetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce)
{
}
void SplSub_GetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce)
{
}
void SplSub_SetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type)
{
}
void SplSub_GetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type)
{
}
void SplSub_SetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global)
{
}
void SplSub_GetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global)
{
}

// -----------------------------------------
//
//	コンバージェンス
//
// -----------------------------------------
///< コンバージェンスの座標操作
void SplSub_SetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){ return; }
	
	p_obj->pos = *p_pos;
}

void SplSub_GetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){
		VecFx32 err_p = { 0,0,0 };
		*p_pos = err_p;
		return;
	}
	
	*p_pos = p_obj->pos;
}

///< コンバージェンスの強さ操作
void SplSub_SetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){ return; }
	
	p_obj->ratio = *ratio;
}

void SplSub_GetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){
		*ratio = 0;
		return;
	}
	
	*ratio = p_obj->ratio;
}
