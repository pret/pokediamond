#ifndef __COMMON_H__
#define __COMMON_H__

//=========================================================================
/**
 * @file	common.h
 * @brief	���ʒ�`�t�@�C��
 * @author	GAME FREAK inc.
 *
 */
//=========================================================================

#include "gflib/system.h"					//�O���[�o���ϐ���`
#include "gflib/standard.h"
#include "gflib/tcb.h"					//Task Control Block
#include "gflib/mmap_get.h"
// �������d�v�����ȃt�@�C��������
// �������A���t�@�x�b�g���@������
#include "gflib/bg_system.h"				//�a�f�R���g���[���V�X�e��
#include "gflib/blact.h"
#include "gflib/calc2d.h"
#include "gflib/calc3d.h"
#include "gflib/calctool.h"
#include "gflib/camera.h"					//��{�J�����V�X�e��
#include "gflib/clact.h"
#include "gflib/char_manager.h"
#include "gflib/display.h"				//�\����ʐݒ�
#include "gflib/bounding_box.h"
#include "gflib/fntequ_agb_jp.h"
#include "gflib/fntsys.h"
#include "gflib/msg_print.h"
#include "gflib/pltt_manager.h"
#include "gflib/point_sel.h"
#include "gflib/simple_3dgraphics.h"		//��{�R�c�O���t�B�b�N�V�X�e��
#include "gflib/str_tool.h"
#include "gflib/touchpanel_system.h"
#include "gflib/vram_transfer_anm.h"
#include "gflib/vram_transfer_manager.h"
#include "gflib/sleep.h"
#include "gflib/res_manager.h"
#include "gflib/texanm_sys.h"
#include "gflib/gf_gx.h"
#include "gflib/g3d_system.h"

#include "src_os_print.h"			// OS_Printf()�̗L��/������`


#include "gflib\assert.h"
#include "gflib\sdkdef.h"




#define	GLOBAL_MSGLEN	( 2 )		///<������f�[�^�␳��`


//#define	PAD_BUTTON_DECIDE	( PAD_BUTTON_A|PAD_BUTTON_X )	// ����{�^����`
//#define	PAD_BUTTON_CANCEL	( PAD_BUTTON_B|PAD_BUTTON_Y )	// �L�����Z���{�^����`
#define	PAD_BUTTON_DECIDE	( PAD_BUTTON_A )	// ����{�^����`
#define	PAD_BUTTON_CANCEL	( PAD_BUTTON_B )	// �L�����Z���{�^����`



#endif //__COMMON_H__
