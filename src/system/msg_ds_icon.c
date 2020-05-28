//============================================================================================
/**
 * @file	msg_ds_icon.c
 * @brief	��ʒ��ڃA�C�R������
 * @author	Hiroyuki Nakamura
 * @date	2006.02.22
 */
//============================================================================================
#include "common.h"
#include "system/palanm.h"
#include "system/lib_pack.h"

#define	MSG_DS_ICON_H_GLOBAL
#include "system/msg_ds_icon.h"


//============================================================================================
//	�萔��`
//============================================================================================
typedef void (*dsiFunc)(void*,u16*);	// �֐��|�C���^�^

// �A�C�R�����䃏�[�N
typedef struct {
	TCB_PTR tcb;			// TCB
	dsiFunc func;			// �p���b�g�]���֐��|�C���^
	PALETTE_FADE_PTR pfd;	// �p���b�g�t�F�[�h���[�N
	u16	def_pal[16];		// �����p���b�g
	u16	tmp_pal[16];		// �]���p���b�g
	u8	disp;				// �����������
	u8	pal;				// �p���b�g�ԍ�
	u8	seq;				// �V�[�P���X
	u8	cnt;				// �J�E���^
}DSI_WORK;

// �����V�[�P���X
enum {
	SEQ_START = 0,	// �J�n
	SEQ_DRAW,		// �]��
	SEQ_STOP,		// ��~
	SEQ_FREE,		// ���
};

#define	BACK_COL_POS	( 15 )		// �w�i�J���[�̈ʒu
#define	CHG_PLTT_POS	( 0x7800 )	// ���������J���[�ʒu( ���ʂ���0,1,2,...15 )
#define	CHG_COUNT_MAX	( 32 )		// �J�E���g�ő�
#define	NO_PUT_COUNT	( 24 )		// ��\���J�E���g


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void PaletteCangeTask( TCB_PTR tcb, void * work );
static u8 PalettePut( DSI_WORK * wk );
static void DsiFuncVram_M( void * work, u16 * pal );
static void DsiFuncVram_S( void * work, u16 * pal );
static void DsiFuncWork_M( void * work, u16 * pal );
static void DsiFuncWork_S( void * work, u16 * pal );


//--------------------------------------------------------------------------------------------
/**
 * �A�C�R���_�Ń^�X�N�Z�b�g
 *
 * @param	pfd		�p���b�g�t�F�[�h�f�[�^( NULL�̏ꍇ�AVRAM�ɒ��ڏ������� )
 * @param	disp	�]�����
 * @param	pal		�p���b�g�ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	�^�X�N���[�N
 */
//--------------------------------------------------------------------------------------------
void * MSG_DsIconFlashAdd( PALETTE_FADE_PTR pfd, u16 disp, u16 pal, u32 heap )
{
	DSI_WORK * wk;
	TCB_PTR	tcb;
	u16 * pltt;

	tcb = PMDS_taskAdd( PaletteCangeTask, sizeof(DSI_WORK), 0, heap );
	wk  = (DSI_WORK *)TCB_GetWork( tcb );

	if( pfd != NULL ){
		if( disp == MSG_DSI_MAINDISP ){
			pltt = PaletteWorkDefaultWorkGet( pfd, FADE_MAIN_BG );
			wk->func = DsiFuncWork_M;
		}else{
			pltt = PaletteWorkDefaultWorkGet( pfd, FADE_SUB_BG );
			wk->func = DsiFuncWork_S;
		}
	}else{
		if( disp == MSG_DSI_MAINDISP ){
			pltt = (u16 *)GF_MMAP_MainBgPlttAddr();
			wk->func = DsiFuncVram_M;
		}else{
			pltt = (u16 *)GF_MMAP_SubBgPlttAddr();
			wk->func = DsiFuncVram_S;
		}
	}
	MI_CpuCopy16( &pltt[pal*16], wk->def_pal, 0x20 );
	MI_CpuCopy16( &pltt[pal*16], wk->tmp_pal, 0x20 );
	wk->tcb  = tcb;
	wk->pfd  = pfd;
	wk->disp = disp;
	wk->pal  = pal;
	wk->seq  = SEQ_DRAW;
	wk->cnt  = 0;

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �^�X�N�̃V�[�P���X���O���R���g���[��
 *
 * @param	work	�^�X�N���[�N
 * @param	req		���N�G�X�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MSG_DsIconFlashReq( void * work, u8 req )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	switch( req ){
	case MSG_DSI_REQ_START:
		wk->seq = SEQ_START;
		break;
	case MSG_DSI_REQ_STOP:
		wk->seq = SEQ_STOP;
		break;
	case MSG_DSI_REQ_FREE:
		wk->seq = SEQ_FREE;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �^�X�N���O������폜
 *
 * @param	work	�^�X�N���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MSG_DsIconFlashDelete( void * work )
{
	DSI_WORK * wk = (DSI_WORK *)work;
	PMDS_taskDel( wk->tcb );
}

//--------------------------------------------------------------------------------------------
/**
 * ���C���^�X�N
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteCangeTask( TCB_PTR tcb, void * work )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	switch( wk->seq ){
	case SEQ_START:
		wk->cnt = 0;
		wk->seq = SEQ_DRAW;
		break;

	case SEQ_DRAW:
		if( PalettePut( wk ) == TRUE ){
			wk->func( wk, wk->tmp_pal );
		}
		wk->cnt++;
		if( wk->cnt == CHG_COUNT_MAX ){
			wk->cnt = 0;
		}
		break;

	case SEQ_STOP:
		break;

	case SEQ_FREE:
		wk->func( wk, wk->def_pal );
		PMDS_taskDel( tcb );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���[�N��������
 *
 * @param	wk		���[�N
 *
 * @retval	"TRUE = �ύX����"
 * @retval	"FALSE = �ύX���ĂȂ�"
 */
//--------------------------------------------------------------------------------------------
static u8 PalettePut( DSI_WORK * wk )
{
	u32	i;

	if( wk->cnt == 0 ){
		for( i=0; i<16; i++ ){
			if( ( CHG_PLTT_POS & (1<<i) ) == 0 ){
				continue;
			}
			wk->tmp_pal[i] = wk->def_pal[i];
		}
		return TRUE;
	}else if( wk->cnt == NO_PUT_COUNT ){
		for( i=0; i<16; i++ ){
			if( ( CHG_PLTT_POS & (1<<i) ) == 0 ){
				continue;
			}
			wk->tmp_pal[i] = wk->def_pal[BACK_COL_POS];
		}
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�]��
 *
 * @param	work	���[�N
 * @aram	pal		�]���p���b�g�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DsiFuncVram_M( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	GF_BGL_PaletteSet( GF_BGL_FRAME0_M, pal, 0x20, wk->pal*0x20 );
}

static void DsiFuncVram_S( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	GF_BGL_PaletteSet( GF_BGL_FRAME0_S, pal, 0x20, wk->pal*0x20 );
}

static void DsiFuncWork_M( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	PaletteWorkSet( wk->pfd, pal, FADE_MAIN_BG, wk->pal*16, 0x20 );
}

static void DsiFuncWork_S( void * work, u16 * pal )
{
	DSI_WORK * wk = (DSI_WORK *)work;

	PaletteWorkSet( wk->pfd, pal, FADE_SUB_BG, wk->pal*16, 0x20 );
}
