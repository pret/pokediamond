//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sys.h
 *	@brief		図鑑システム
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_SYS_H__
#define __ZKN_SYS_H__

#include "include/system/procsys.h"
#include "include/application/zukanlist/zkn_sys_static.h"
#include "include/application/zukanlist/zkn_data_work.h"

#undef GLOBAL
#ifdef	__ZKN_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-------------------------------------
//	ペアレントデータワーク
//=====================================
typedef struct {
	const ZUKAN_WORK*	cp_zukansave_data;
	const MYSTATUS*		cp_hero_data;
	int time_zone;		// 図鑑を開いたときの時間帯
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	ZKN_DATA_WORK* p_zkn_work;
} ZKN_PEARENT_DATA;


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック生成
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcInit( PROC* proc, int* seq );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロックメイン
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcMain( PROC* proc, int* seq );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック終了
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL PROC_RESULT ZKN_ProcEnd( PROC* proc, int* seq );





//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	システム初期化データ
//=====================================
typedef struct {
	const ZUKAN_WORK*	cp_zukansave_data;
	const MYSTATUS*		cp_hero_data;
	int time_zone;		// 図鑑を開いたときの時間帯
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	ZKN_DATA_WORK* p_zkn_work;
} ZKN_SYS_INIT_DATA;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_SYS_SetUpDraw( int heap );
GLOBAL void ZKN_SYS_ReleaseDraw( void );
GLOBAL ZKN_SYS_PTR ZKN_SYS_Init( int heap, const ZKN_SYS_INIT_DATA* p_init );
GLOBAL BOOL ZKN_SYS_Main( ZKN_SYS_PTR zkn );
GLOBAL void ZKN_Vblank( ZKN_SYS_PTR zkn );


#undef	GLOBAL
#endif		// __ZKN_SYS_H__

