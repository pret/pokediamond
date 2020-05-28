/**
 *	@file	nmix_stdata.h
 *	@biref	ナッツミキサー　常駐データ構造体定義
 *	@author	Miyuki Iwasawa
 *	@date	06.04.07
 */

#ifndef __H_NMIX_STDATA_H__
#define __H_NMIX_STDATA_H__

#include "system/wordset.h"
#include "system/msgdata.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_porutogame1.h"

// スピード注意コメント
enum{
	NMIX_STMSG_SPEED_KOGERU00,
	NMIX_STMSG_SPEED_HAYAI00,
	NMIX_STMSG_SPEED_KOGERU01,
	NMIX_STMSG_SPEED_HAYAI01,
	NMIX_STMSG_SPEED_KOGERU02,
	NMIX_STMSG_SPEED_NUM
};

// 結果発表コメント
enum{
	NMIX_STMSG_RESULT_COOK_TIME_TI,
	NMIX_STMSG_RESULT_COOK_TIME,
	NMIX_STMSG_RESULT_KOBOSI_NUM_TI,
	NMIX_STMSG_RESULT_KOBOSI_NUM,
	NMIX_STMSG_RESULT_KOGASI_NUM_TI,
	NMIX_STMSG_RESULT_KOGASI_NUM,
	NMIX_STMSG_RESULT_PORUTO_TI,
	NMIX_STMSG_RESULT_PORUTO,
	NMIX_STMSG_RESULT_TEAMWORK_TI,
	NMIX_STMSG_RESULT_TEAMWORK,
	NMIX_STMSG_RESULT_NUM
};


///常駐メッセージデータ
typedef struct _NMIXER_MSG{
	MSGDATA_MANAGER *man;	///<マネージャ
	WORDSET* wset;		///<ワーク
	STRBUF	*tmp;		///<汎用

	STRBUF	*wait;		///<そのままおまちください
	STRBUF	*nuts_in;	///<木の実いれる
	STRBUF	*tr_name;	///<トレーナー名
	
	STRBUF	*casein;	///<ケースにしまう
	STRBUF	*replay;	///<引き続き……
	STRBUF	*exit;		///<中止
	STRBUF	*bag_erabu;	///<バッグからえらんで
	STRBUF	*poruto_ippai;	///<ポルトがいっぱい
	STRBUF	*nuts_none;	///<木の実がありません
	
	STRBUF	*end;		///<おわり
	STRBUF	*result;	///<結果発表 タイトル
	
	STRBUF	*spd[NMIX_STMSG_SPEED_NUM];	///<スピード
	STRBUF	*res[NMIX_STMSG_RESULT_NUM];	///<結果表示
}NMIXER_MSG;

#define WORDSET_NMIXER_BUFLEN	(64)

#endif	//__H_NMIX_STDATA_H__
