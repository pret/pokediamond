//==============================================================================
/**
 * @file	wp_tbl.c
 * @brief	技エフェクトパーティクルデータテーブル
 * @author	matsuda
 * @date	2005.07.22(金)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "wazaeffect/wp_tbl.h"
#include "wazaeffect/wp_num.h"
#include "wazaeffect/battle_particle.h"
#include "wazaeffect/wp_callback.h"
#include "wazaeffect/effectdata/we_list.h"
#include "system/arc_tool.h"

#include "wpcb_common.h"

//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void DummyEmitCallback(EMIT_PTR emit);

//==============================================================================
//	定数定義
//==============================================================================
#define DUMMY_CALLBACK		DummyEmitCallback

//==============================================================================
//	技エフェクトパーティクルデータテーブル
//==============================================================================
#if 0	//Arcするようになったので不要 2005.10.05(水)
#include "wazaeffect/effectdata/we_list.dat"
#endif


//--------------------------------------------------------------
/**
 * @brief   エミッタ作成時に呼び出すコールバック関数へのポインタ配列
 *
 * 増減させるたびに、wp_num.hの定義も合わせて増減させる必要があります。(EMTFUNC_???)
 */
//--------------------------------------------------------------
static const pEmitFunc EmitterCallbackFunc[] = {
	DummyEmitCallback,
	EmitCall_CameraReverseAttack,
	EmitCall_CameraReverseDefence,
	EmitCall_AttackPos,
	EmitCall_DefencePos,
	EmitCall_AxisAttack,
	EmitCall_AxisDefence,
	
	EmitCall_AxisAttack_DefaultCNV,
	EmitCall_AxisAttack_CenterCNV,
	EmitCall_AxisAttack_TargetPokemonCNV,
	EmitCall_AxisAttack_PlayerPokemonCNV,
	EmitCall_AxisAttack_PosSetCNV,
	
	EmitCall_AxisAttack_DefaultMAG,
	EmitCall_AxisAttack_CenterMAG,
	EmitCall_AxisAttack_TargetPokemonMAG,
	EmitCall_AxisAttack_PlayerPokemonMAG,
	EmitCall_AxisAttack_PosSetMAG,
	
	ECB_Operator,
	EmitCall_SepPos,
	
	EmitCall_DFsidePos,
	EmitCall_ATsidePos,
	
	EmitCall_ATPosCR,
	
	EmitCall_Debug,
};


#if 0		//======================================
static const WP_DATA WazaParticleDataTbl[] = {
	{
		"wazaeffect/effectdata/test1.spa",
		DUMMY_CALLBACK,
		0,
	},
	{
		"wazaeffect/effectdata/test2.spa",
		DUMMY_CALLBACK,
		0,
	},
	{
		"wazaeffect/effectdata/test3.spa",
		DUMMY_CALLBACK,
		0,
	},
};
#endif




//--------------------------------------------------------------
/**
 * @brief   エミッタ生成時に呼び出すコールバック関数が必要ない時に指定するダミー関数
 *
 * @param   emit		生成したエミッタへのポインタ
 *
 * NULL指定でも大丈夫そうだけど、特にマニュアルに記載されている訳でもないので、
 * 安全を考慮してダミー関数を設定するようにします。
 */
//--------------------------------------------------------------
static void DummyEmitCallback(EMIT_PTR emit)
{
	return;
}


#if 0	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   技エフェクトパーティクルデータテーブルから、指定データ番号のアドレスを取得する
 *
 * @param   data_no		データ番号(wp_num.h:WP_???)
 *
 * @retval  データアドレス
 */
//--------------------------------------------------------------
const WP_DATA * Wp_DataPtrGet(int data_no)
{
	if(data_no >= NELEMS(WazaParticleDataTbl)){
		SDK_ASSERT(0);
		return &WazaParticleDataTbl[0];	//吹っ飛ばないように最初のポインタを一応返す
	}
	
	return &WazaParticleDataTbl[data_no];
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルを生成する
 *
 * @param   data_no		データ番号(wp_num.h:WP_???)
 */
//--------------------------------------------------------------
void Wp_ParticleSet(PTC_PTR ptc, int data_no)
{
	const WP_DATA *wpdata;
	
	wpdata = Wp_DataPtrGet(data_no);
	
	Particle_LoadFile(ptc, wpdata->spa_path);
	Particle_CreateEmitterCallback(ptc, wpdata->res_no, wpdata->emit_func);
}
#endif


//--------------------------------------------------------------
/**
 * @brief   パーティクルシステムを生成し、リソースファイルを読み込む
 *
 * @param   data_no		データ番号(wp_num.h:SPA_???)
 * @param   tex_at_once		TRUE:テクスチャ即転送、FALSE:Vブランク中に転送
 */
//--------------------------------------------------------------
PTC_PTR Wp_Init(int heap_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = BattleParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(ARC_WAZA_PARTICLE, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

#ifdef PM_DEBUG

	gDebugPTC = ptc;

#endif
	
	return ptc;
}

//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	heap_id	
 * @param	arc_id	
 * @param	data_no	
 * @param   tex_at_once		TRUE:テクスチャ即転送、FALSE:Vブランク中に転送
 *
 * @retval	PTC_PTR	
 *
 */
//--------------------------------------------------------------
PTC_PTR Wp_InitEx(int heap_id, int arc_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = BattleParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

#ifdef PM_DEBUG

	gDebugPTC = ptc;

#endif
	
	return ptc;
}

///< カスタム専用
PTC_PTR Wp_InitEx_CB(int heap_id, int arc_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = CB_Particle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);
	
	return ptc;
}


void * Particle_ArcResourceLoad_AH(ARCHANDLE* ah, int index, int heap_id)
{
	return ArchiveDataLoadAllocByHandle(ah,index, heap_id );
}

///< アーカイブのハンドル保持
PTC_PTR Wp_InitEx_CBAH(ARCHANDLE* ah, int heap_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = CB_Particle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad_AH(ah, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

	return ptc;
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルのエミッタを作成する
 *
 * @param   ptc				パーティクルシステムワークへのポインタ
 * @param   resource_no		リソース番号
 * @param   func_num		コールバック関数番号(wp_num.h:EMTFUNC_???)
 * @param   temp_ptr		エミッタ作成時にテンポラリワークに預けるポインタ
 */
//--------------------------------------------------------------
EMIT_PTR Wp_EmitterCreate(PTC_PTR ptc, int resource_no, int func_num, void *temp_ptr)
{
	return Particle_CreateEmitterCallback(ptc, resource_no, EmitterCallbackFunc[func_num], temp_ptr);
}

//--------------------------------------------------------------
/**
 * @brief   パーティクルのエミッタを作成する(コールバック関数を直接ポインタで渡す)
 *
 * @param   ptc				パーティクルシステムワークへのポインタ
 * @param   resource_no		リソース番号
 * @param   func_num		コールバック関数番号(wp_num.h:EMTFUNC_???)
 * @param   temp_ptr		エミッタ作成時にテンポラリワークに預けるポインタ
 */
//--------------------------------------------------------------
EMIT_PTR Wp_EmitterCreateFunc(PTC_PTR ptc, int resource_no, pEmitFunc func, void *temp_ptr)
{
	return Particle_CreateEmitterCallback(ptc, resource_no, func, temp_ptr);
}

//--------------------------------------------------------------
/**
 * @brief   読み込んでいるリソースファイルを解放する
 *
 * @param   ptc		パーティクルシステムワークへのポインタ
 */
//--------------------------------------------------------------
void Wp_Exit(PTC_PTR ptc)
{
	BattleParticle_Exit(ptc);
}

