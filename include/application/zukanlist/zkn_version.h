//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_version.h
 *	@brieuf		図鑑 カートリッジバージョン分岐
 *	@author		tomoya takahashi
 *	@data		2006.02.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_VERSION_H__
#define __ZKN_VERSION_H__

#include "include/msgdata/msg.naix"
#include "include/system/arc_tool.dat"

#if ( PM_VERSION == VERSION_DIAMOND )

#define ZKN_TEXT_DAT	( NARC_msg_zkn_comment_00_dat )
#define ZKN_ARC_DAT	( ARC_ZUKAN_ENC_DIAMOND )

#elif( PM_VERSION == VERSION_PEARL )

#define ZKN_TEXT_DAT	( NARC_msg_zkn_comment_01_dat )
#define ZKN_ARC_DAT	( ARC_ZUKAN_ENC_PEARL )

#endif


#endif		// __ZKN_VERSION_H__

