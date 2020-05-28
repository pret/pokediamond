/**
 *	@file	tmap_def.h
 *	@brief	�^�E���}�b�v���W���[���@���L�萔��`�t�@�C��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.01
 */
#ifndef __H_TMAP_DEF_H__
#define __H_TMAP_DEF_H__

///���ʃ}�N����`
#ifdef PM_DEBUG
#define TMAP_HEAP_PRINT(str) {\
 OS_Printf( "\nINFO : townmap.c -> %s\n",(str));	\
 OS_Printf( "TOWNMAP_HEAP_SIZE : 0x%x\n", sys_GetHeapFreeSize( HEAPID_TOWNMAP ) ); \
}
#else	//PM_DEBUG
#define TMAP_HEAP_PRINT
#endif	//PM_DEBUG

//�X�N���[���T�C�Y�擾�}�N��
#define SCWS_GET(p)	((p)->screenWidth/8)
#define SCHS_GET(p)	((p)->screenHeight/8)

#define TMAP_BUFLEN_ZNW	(10*2)
#define TOWNV_TYPE_MAX	(4)
#define TOWN_VIEW_MAX	(TMAP_ARRIVEDATA_MAX)

#define TMAP_BLOCK_OFFSETX	(2)
#define TMAP_BLOCK_OFFSETZ	(2)
#define TMAP_BLOCK_UNIT		(16)
#define TMAP_SBLOCK_UNIT	(16)

#define FORCUS_CHG_SYNC	(8)

//���C�����Dot�I�t�Z�b�g
#define TMAP_MDOT_OFSX	(25)
#define TMAP_MDOT_OFSZ	(-34)
#define TMAP_MDOT_UNIT	(7)

#endif	//__H_TMAP_DEF_H__

