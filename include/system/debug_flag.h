//============================================================================================
/**
 * @file	debug_flag.h
 * @brief	デバッグ用構造体定義
 * @author	Hiroyuki Nakamura
 * @date	2006.05.16
 */
//============================================================================================
#ifdef	PM_DEBUG

#ifndef DEBUG_FLAG_H
#define DEBUG_FLAG_H


typedef struct {
	BOOL	debug_mode;		//デバッグモードかどうか
	BOOL	encount_flag;	// エンカウント制御　0=ON, 1=OFF
	int		postman_status;	// ふしぎ配達員制御
	int		tv_program_id;	///< テレビ番組ID
}DEBUG_FLAG_DATA;

extern DEBUG_FLAG_DATA	DebugFlagData;		// 本体は"system/main.c"にあります


#endif	// DEBUG_FLAG_H
#endif	// PM_DEBUG
