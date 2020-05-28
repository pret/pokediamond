//==============================================================================
/**
 *
 *@file		assert.h
 *@brief	�A�T�[�g
 *@author	taya
 *@data		2005.08.08
 *
 */
//==============================================================================
#ifndef _ASSERT_H_
#define _ASSERT_H_

// Debug ROM �ł����Ă��A�T�[�g�𖳌��ɂ��������͂��̃t���O���I���ɂ���
#define GF_ASSERT_FORCE_DISABLE


#ifndef GF_ASSERT_FORCE_DISABLE	// �A�T�[�g�L����

	#ifdef PM_DEBUG		// ���� Debug ROM �ł���

		extern void GF_AssertInit( void );
		extern void GF_AssertMain( void );


		extern void GF_AssertProc(const char* filename, unsigned int line_no, const char* exp);
		extern void GF_AssertMsgProc( const char* filename, unsigned int lineno, const char* fmt, ... );
		extern void GF_ASSERT_Printf( const char* fmt, ... );
		#define GF_ASSERT(exp) (exp)? ((void)0) : GF_AssertProc(__FILE__, __LINE__, #exp);
		#define GF_ASSERT_MSG(exp, ...) (exp)? ((void)0) : GF_AssertMsgProc(__FILE__, __LINE__, __VA_ARGS__ );
		#define GF_ASSERT_RETURN(exp, ret) (exp)? ((void)0) : GF_AssertProc(__FILE__, __LINE__, #exp);


		// �A�T�[�g�}�N����L���ɂ��܂�����
		#define GF_ASSERT_ENABLED
	#endif
#endif


// GF_ASSERT_ENABLED��define����Ă��Ȃ���΁A�A�T�[�g�@�\�𖳌��ɂ���
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

		// �A�T�[�g�@�\�������ȏꍇ�������̃`�F�b�N�͍s���A�ʐM���Ȃ狭���I�ɃG���[��ʂɔ�΂�
		extern void GF_AssertFailedWarningCall( void );
		#define GF_ASSERT(exp) (exp)? ((void)0) : GF_AssertFailedWarningCall();
		#define GF_ASSERT_MSG(exp, ...) (exp)? ((void)0) : GF_AssertFailedWarningCall();
		#define GF_ASSERT_RETURN(exp, ret) (exp)? ((void)0) : GF_AssertFailedWarningCall();

	#endif

#endif


#endif
