//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nutmix_comm_pack.c
 *	@brief		通信PACKAGEシステム
 *	@author		tomoya takahashi
 *	@data		2006.05.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"


#define __NUTMIX_COMM_PACK_H_GLOBAL
#include "nutmix_comm_pack.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define NUTMIX_COMM_PACK_DATABUFF_SIZE	( 38 )	// byte

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ダミーコールバックワーク
//=====================================
typedef struct {
	BOOL init;
	int command;
	u8 data[ NUTMIX_COMM_PACK_DATABUFF_SIZE ];
	int size;
} NUTMIX_COMMPACK_DUMMY_WORK;


//-------------------------------------
//	ダミーコールバックシステム
//=====================================
typedef struct {
	NUTMIX_COMMPACK_DUMMY_WORK	work[NUTMIX_COMM_PACK_DUMMY_WORK_NUM];	// ワーク
	const CommPacketTbl* pCommPacketLocal;	// コマンドテーブル
	int					 commtbl_num;		// コマンドテーブル数
	void*				 pCallBackWork;		// コールバックワーク
	TCB_PTR				 tcb;				// タスクワーク
} NUTMIX_COMMPACK_DUMMY_SYS;


//-------------------------------------
//	外部保持　システムワーク
//	comm_flgからpWorkの使用用途が変わる
//=====================================
typedef struct _NUTMIX_COMMPACK_WORK{
	int comm_flg;	// 通信パックフラグ
	void* pWork;	// ワーク
} ;




//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static NUTMIX_COMMPACK_DUMMY_SYS* NutMix_CommPack_DummySys_Init( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int heapID );
static void NutMix_CommPack_DummySys_Main( TCB_PTR tcb, void* p_work );
static void NutMix_CommPack_DummySys_Delete( NUTMIX_COMMPACK_DUMMY_SYS* p_sys );
static BOOL NutMix_CommPack_DummySys_SendData( NUTMIX_COMMPACK_DUMMY_SYS* p_sys, int command, const void* data, int size );




//----------------------------------------------------------------------------
/**
 *	@brief	コマンドテーブル設定　パック関数
 *
 *	@param	pCommPacketLocal		コマンドテーブル
 *	@param	listNum					リスト数
 *	@param	pWork					コールバックワーク
 *	@param	comm_flg				通信パックフラグ
 *	@param	heapID					ヒープID
 *
 *	@retval	コマンドパックシステムワーク
 */
//-----------------------------------------------------------------------------
NUTMIX_COMMPACK_WORK* NMIX_CommPack_CommandInitialize( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int comm_flg, int heapID )
{
	NUTMIX_COMMPACK_WORK* p_sys;

	// メモリ確保
	p_sys = sys_AllocMemory( heapID, sizeof(NUTMIX_COMMPACK_WORK) );
	p_sys->comm_flg = comm_flg;
	p_sys->pWork = NULL;
	
	if( comm_flg == NUTMIX_COMM_PACK_COMM ){
	    CommCommandInitialize( pCommPacketLocal, listNum, pWork );
		OS_Printf( "通信ﾓｰﾄﾞセットアップ\n" );
	}else{
		p_sys->pWork = NutMix_CommPack_DummySys_Init( pCommPacketLocal, listNum, pWork, heapID );
		OS_Printf( "一人ﾓｰﾄﾞセットアップ\n" );
	}

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コマンド転送　パック関数
 *
 *	@param	command				コマンド
 *	@param	data				データ
 *	@param	size				サイズ
 *	@param	p_sys				コマンドパックシステム
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗
 */
//-----------------------------------------------------------------------------
BOOL NMIX_CommPack_CommSendData( int command, const void* data, int size, NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommSendData( command, data, size );
	}else{
		return NutMix_CommPack_DummySys_SendData( p_sys->pWork, command, data, size );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	コマンドテーブル操作	パックシステム破棄
 *
 *	@param	p_sys	システム
 */
//-----------------------------------------------------------------------------
void NMIX_CommPack_CommDelete( NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_ONE ){
		NutMix_CommPack_DummySys_Delete( p_sys->pWork );
	}
	sys_FreeMemoryEz( p_sys );
}


//----------------------------------------------------------------------------
/**
 *	@brief	自分の接続IDを取得
 *
 *	@param	p_sys	システム
 *
 *	@return	接続ID
 */
//-----------------------------------------------------------------------------
int NMIX_CommPack_CommGetCurrentID( NUTMIX_COMMPACK_WORK* p_sys )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommGetCurrentID();
	}else{
		return NUTMIX_COMM_PACK_DUMMY_NETID;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	通信可能状態なのかどうかを返す ただしコマンドによるネゴシエーションがまだの状態
 *
 *	@param	p_sys	システム
 *	@param	netID	接続ID
 *
 *	@retval	TRUE	接続している
 *	@retval	FALSE	接続していない
 */
//-----------------------------------------------------------------------------
BOOL NMIX_CommPack_CommIsConnect( NUTMIX_COMMPACK_WORK* p_sys, u16 netID )
{
	if( p_sys->comm_flg == NUTMIX_COMM_PACK_COMM ){
	    return CommIsConnect( netID );
	}else{
		if( netID == NUTMIX_COMM_PACK_DUMMY_NETID ){
			return TRUE;
		}else{
			return FALSE;
		}
	}
}



//-----------------------------------------------------------------------------
/**
 * 
 *		プライベート関数
 * 
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーコールバックシステム
 *	
 *	@param	pCommPacketLocal	コマンドテーブル
 *	@param	listNum				テーブル数
 *	@param	pWork				ワーク
 *	@param	heapID				ヒープID
 *
 *	@return	作成したシステムワーク
 */
//-----------------------------------------------------------------------------
static NUTMIX_COMMPACK_DUMMY_SYS* NutMix_CommPack_DummySys_Init( const CommPacketTbl* pCommPacketLocal,int listNum,void* pWork, int heapID )
{
	NUTMIX_COMMPACK_DUMMY_SYS* p_sys;

	// メモリ確保
	p_sys = sys_AllocMemory( heapID, sizeof(NUTMIX_COMMPACK_DUMMY_SYS) );
	memset( p_sys, 0, sizeof(NUTMIX_COMMPACK_DUMMY_SYS) );

	p_sys->pCommPacketLocal	= pCommPacketLocal;
	p_sys->commtbl_num		= listNum;
	p_sys->pCallBackWork	= pWork;

	p_sys->tcb = VWaitTCB_Add( NutMix_CommPack_DummySys_Main, p_sys, NUTMIX_COMM_PACK_DUMMY_TCB_PRI );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン　動さ
 */
//-----------------------------------------------------------------------------
static void NutMix_CommPack_DummySys_Main( TCB_PTR tcb, void* p_work )
{
	NUTMIX_COMMPACK_DUMMY_SYS* p_sys = p_work;
	int i;

	// コールバック処理
	for( i=0; i<NUTMIX_COMM_PACK_DUMMY_WORK_NUM; i++ ){

		// データがあるかチェック
		if( p_sys->work[i].init == TRUE ){
			p_sys->pCommPacketLocal[ p_sys->work[i].command ].callbackFunc( 
					NUTMIX_COMM_PACK_DUMMY_NETID, p_sys->work[i].size, 
					p_sys->work[i].data, p_sys->pCallBackWork );
			// ワーククリア
			memset( &p_sys->work[i], 0, sizeof(NUTMIX_COMMPACK_DUMMY_WORK) );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダミーコールバックシステム破棄
 *
 *	@param	p_sys	システムワーク 
 */
//-----------------------------------------------------------------------------
static void NutMix_CommPack_DummySys_Delete( NUTMIX_COMMPACK_DUMMY_SYS* p_sys )
{
	TCB_Delete( p_sys->tcb );
	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コマンド登録
 *
 *	@param	p_sys		システム
 *	@param	command		コマンド
 *	@param	data		データ
 *	@param	size		サイズ
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗
 */
//-----------------------------------------------------------------------------
static BOOL NutMix_CommPack_DummySys_SendData( NUTMIX_COMMPACK_DUMMY_SYS* p_sys, int command, const void* data, int size )
{
	int i;
	int check_size;
	NUTMIX_COMMPACK_DUMMY_WORK* p_work;

	// 空いているワーク取得
	p_work = NULL;
	for( i=0; i<NUTMIX_COMM_PACK_DUMMY_WORK_NUM; i++ ){
		if( p_sys->work[i].init == FALSE ){
			p_work = &p_sys->work[i];
			break;
		}
	}
	// 登録数オーバー
	GF_ASSERT( p_work );


	// コマンドの共通部分数文引く
	command -= CS_COMMAND_MAX;

	// 登録するコマンドのサイズとデータサイズが等しいかチェック
	check_size = p_sys->pCommPacketLocal[ command ].getSizeFunc();
	GF_ASSERT( check_size == size );

	// ダミーバッファサイズより小さいかチェック
	GF_ASSERT( size < NUTMIX_COMM_PACK_DATABUFF_SIZE );

	// データ設定
	p_work->command = command;
	if( size > 0 ){	// サイズがあったらコピー
		memcpy( p_work->data, data, size );
	}
	p_work->size	= size;
	p_work->init	= TRUE;
	return TRUE;
}
