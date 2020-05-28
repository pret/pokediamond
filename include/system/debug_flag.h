//============================================================================================
/**
 * @file	debug_flag.h
 * @brief	�f�o�b�O�p�\���̒�`
 * @author	Hiroyuki Nakamura
 * @date	2006.05.16
 */
//============================================================================================
#ifdef	PM_DEBUG

#ifndef DEBUG_FLAG_H
#define DEBUG_FLAG_H


typedef struct {
	BOOL	debug_mode;		//�f�o�b�O���[�h���ǂ���
	BOOL	encount_flag;	// �G���J�E���g����@0=ON, 1=OFF
	int		postman_status;	// �ӂ����z�B������
	int		tv_program_id;	///< �e���r�ԑgID
}DEBUG_FLAG_DATA;

extern DEBUG_FLAG_DATA	DebugFlagData;		// �{�̂�"system/main.c"�ɂ���܂�


#endif	// DEBUG_FLAG_H
#endif	// PM_DEBUG
