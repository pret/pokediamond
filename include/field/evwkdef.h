//==============================================================================================
/**
 * @file	evwkdef.c
 * @brief	フラグ、ワーク領域定義
 * @author	Satoshi Nohara
 * @date	2005.11.07
 */
//==============================================================================================
#ifndef __EVWKDEF_H__
#define __EVWKDEF_H__

//----------------------------------------------------------------------------------------------
//
//	フラグ関連定義
//
//----------------------------------------------------------------------------------------------
//script/saveflag.h
#define USRFLAG_START		0
#define USRFLAG_MAX			2400						//スクリプト定義のフラグ最大数
#define USRFLAG_AREA_MAX	(USRFLAG_MAX/8)

//field/sysflag.h
#define SYSFLAG_START		(USRFLAG_MAX)
#define	SYSFLAG_MAX			320							//システム定義のフラグ最大数
#define	SYSFLAG_AREA_MAX	(SYSFLAG_MAX/8)

#define TIMEFLAG_START		(USRFLAG_MAX+SYSFLAG_MAX)
#define TIMEFLAG_MAX		192							//時間経過イベント用フラグ最大数
#define	TIMEFLAG_AREA_MAX	(TIMEFLAG_MAX/8)

//フラグ最大数
#define	EVENT_FLAG_MAX		(USRFLAG_MAX+SYSFLAG_MAX+TIMEFLAG_MAX)
#define	EVENT_FLAG_AREA_MAX	(EVENT_FLAG_MAX/8)

//フラグオフセット
#define	SVFLG_START			0x0000						//セーブフラグスタートナンバー
#define	SCFLG_START			0x4000						//制御フラグスタートナンバー

//トレーナーフラグ
#define TR_FLAG_START		1360						//トレーナーID対応フラグ開始位置
#define TR_FLAG_MAX			(USRFLAG_MAX-TR_FLAG_START)	//トレーナーID対応フラグ最大数

//セーブしないフラグ関連定義
#define	CTRLFLAG_MAX		64							//制御フラグ最大数
#define	CTRLFLAG_AREA_MAX	(CTRLFLAG_MAX/8)

//フラグスタートナンバー
#define FE_FLAG_START		(100)						//イベント進行制御フラグ
#define FV_FLAG_START		(400)						//バニッシュフラグ
#define FH_FLAG_START		(730)						//隠しアイテムフラグ(256個)
#define FB_FLAG_START		(FH_FLAG_START+256)			//フィールド上のアイテムフラグ(256個)

#define LOCAL_FLAG_MAX		(64)						//ローカルフラグ数(8bit*8=64)
#define LOCAL_FLAG_AREA_MAX	(LOCAL_FLAG_MAX/8)

//----------------------------------------------------------------------------------------------
//
//	ワーク関連定義
//
//----------------------------------------------------------------------------------------------
//script/savework.h
#define EVENT_WORK_AREA_MAX	288

#define	SVWK_START			0x4000								//セーブワーク定義スタートナンバー

//ワークオフセット
#define LOCAL_WORK_START	(0+SVWK_START)						//ローカルワーク開始
#define LOCAL_WORK_MAX		(32)								//ローカルワーク数
#define OBJCHR_WORK_START	(LOCAL_WORK_START+LOCAL_WORK_MAX)	//変更可能なOBJキャラ指定ワーク開始
#define OBJCHR_WORK_MAX		(16)								//変更可能なOBJキャラ指定ワーク数
#define OTHERS_WORK_START	(OBJCHR_WORK_START+OBJCHR_WORK_MAX)	//その他のワーク開始
#define OTHERS_WORK_MAX		(64)								//その他のワーク数
#define SYSWORK_MAX			(LOCAL_WORK_MAX+OBJCHR_WORK_MAX+OTHERS_WORK_MAX)	//

#define	SVSCRWK_START		(SVWK_START+SYSWORK_MAX)			//script/savework.h(スクリプト用)
#define	SCWK_START			0x8000						//データ交換・汎用ワーク定義スタートナンバー

#if 0
//----------------------------------------------------------------------------------------------
//
//	エメラルド
//
//----------------------------------------------------------------------------------------------
//フラグ数 = 2400
//ぎりぎりまで使用していた

//トレーナーフラグ数 = 864
//854使用していた

//ワーク数 = 256
//多少余裕ある感じ？だった
#endif


#endif

