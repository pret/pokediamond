//==============================================================================
/**
 *
 *@file		assert.h
 *@brief	アサート
 *@author	taya
 *@data		2005.08.08
 *
 */
//==============================================================================
#ifndef _ASSERT_H_
#define _ASSERT_H_

// Debug ROM であってもアサートを無効にしたい時はこのフラグをオンにする
#define GF_ASSERT_FORCE_DISABLE


#ifndef GF_ASSERT_FORCE_DISABLE	// アサート有効で

	#ifdef PM_DEBUG		// かつ Debug ROM である

		extern void GF_AssertInit( void );
		extern void GF_AssertMain( void );


		extern void GF_AssertProc(const char* filename, unsigned int line_no, const char* exp);
		extern void GF_AssertMsgProc( const char* filename, unsigned int lineno, const char* fmt, ... );
		extern void GF_ASSERT_Printf( const char* fmt, ... );
		#define GF_ASSERT(exp) (exp)? ((void)0) : GF_AssertProc(__FILE__, __LINE__, #exp);
		#define GF_ASSERT_MSG(exp, ...) (exp)? ((void)0) : GF_AssertMsgProc(__FILE__, __LINE__, __VA_ARGS__ );
		#define GF_ASSERT_RETURN(exp, ret) (exp)? ((void)0) : GF_AssertProc(__FILE__, __LINE__, #exp);


		// アサートマクロを有効にしましたよ
		#define GF_ASSERT_ENABLED
	#endif
#endif


// GF_ASSERT_ENABLEDがdefineされていなければ、アサート機能を無効にする
#ifndef GF_ASSERT_ENABLED

	#define GF_AssertInit()				((void)0);
	#define GF_AssertMain()				((void)0);
	#define GF_ASSERT_Printf( ... )		((void)0);


	#if 0

		#define GF_ASSERT(exp)				((void)0);
		#define GF_ASSERT_MSG(exp, ...)		((void)0);
		#define GF_ASSERT_RETURN(exp, ret) \
	                if(!(exp)){ \
	                  return ret; \
	                }
	#else

		// アサート機能が無効な場合も条件のチェックは行い、通信中なら強制的にエラー画面に飛ばす
		extern void GF_AssertFailedWarningCall( void );
		#define GF_ASSERT(exp) (exp)? ((void)0) : GF_AssertFailedWarningCall();
		#define GF_ASSERT_MSG(exp, ...) (exp)? ((void)0) : GF_AssertFailedWarningCall();
		#define GF_ASSERT_RETURN(exp, ret) (exp)? ((void)0) : GF_AssertFailedWarningCall();

	#endif

#endif


#endif
