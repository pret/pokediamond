//============================================================================================
/**
 * @file	palanm.c
 * @brief	�p���b�g�t�F�[�h����
 * @author	Hiroyuki Nakamura
 * @date	2004.11.24
 */
//============================================================================================
#define	PALANM_H_GLOBAL

#include "common.h"
#include "tcb.h"

#include "system/palanm.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	DEF_FADE_VAL	( 2 )			// ��{���x
// �v�Z
#define FADE_CHANGE( before, after, evy )					\
			( before + ( ( after - before ) * evy >> 4 ) )

///�t�F�[�h�v�Z���s�����[�J���^�X�N��TCB�v���C�I���e�B
///	���K��TCB�̍Ō�Ɏ��s�����悤�Ƀv���C�I���e�B�����ɂ��Ă���
#define TCBPRI_CALC_FADETASK		(0xffffffff - 1)

#define	NORMAL_COLOR_NUM	( 16 )		// �ʏ�p���b�g�̃J���[��
#define	EXTRA_COLOR_NUM		( 256 )		// �g���p���b�g�̃J���[��


//==============================================================================
//	�\���̒�`
//==============================================================================
/// �p���b�g�t�F�[�h�f�[�^
typedef struct _PALETTE_FADE_DATA{
	FADE_REQ_EX2	dat[ ALL_PALETTE_SIZE ];

	u16	req_flg:2;		// 0=���o�^, 1=���쒆, 2=�ꎞ��~
	u16	req_bit:14;		// ���N�G�X�g�r�b�g�i�J���[�v�Z�p�j
	u16	trans_bit:14;	// �g�����X�r�b�g�i�J���[�]���p�j
	u16	tcb_flg:1;		// TCB�o�^�t���O�@0=���o�^, 1=�o�^��
	u16	auto_trans:1;			// �g�����X�r�b�g�Ɋ֌W�Ȃ��A���t���[���S�p���b�g��]��
	
	u8 force_stop;		//TRUE:�p���b�g�t�F�[�h�����I��
	
	u8 dummy[3];
}PALETTE_FADE_DATA;

/// �J���[�p���b�g�\����
typedef struct {
    u16 Red:5;              // ��
    u16 Green:5;            // ��
    u16 Blue:5;             // ��
    u16 Dummy_15:1;
} PLTT_DATA;

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static u8 ReqBitCheck( u16 flg, u16 req );
static void TransBitSet( PALETTE_FADE_PTR pfd, u16 id );
static void FadeBitCheck( FADEREQ req, FADE_REQ_EX2 * wk, u16 * fade_bit );
static void FadeReqSet(
				FADE_REQ_PARAM * wk, u16 fade_bit,
				s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb );
static void PaletteFadeTask( TCB_PTR tcb, void * work );
static void NormalPaletteFade(PALETTE_FADE_PTR pfd);
static void ExtraPaletteFade(PALETTE_FADE_PTR pfd);
static void PaletteFade( PALETTE_FADE_PTR pfd, u16 id, u16 siz );
static void PaletteFadeMain( PALETTE_FADE_PTR pfd, u16 id, u16 siz );
static void FadeWorkSet( u16 * def, u16 * trans, FADE_REQ_PARAM * wk, u32 siz );
static void FadeParamCheck(PALETTE_FADE_PTR pfd, u8 id, FADE_REQ_PARAM * wk );



//--------------------------------------------------------------
/**
 * @brief   �p���b�g�t�F�[�h�V�X�e�����[�N�쐬
 *
 * @param   heap_id		�q�[�vID
 *
 * @retval  �쐬�����p���b�g�t�F�[�h�V�X�e�����[�N�̃|�C���^
 *
 * �V�X�e�����g��Ȃ��Ȃ�����PaletteFadeFree�ŉ���������s���Ă�������
 */
//--------------------------------------------------------------
PALETTE_FADE_PTR PaletteFadeInit(int heap_id)
{
	PALETTE_FADE_PTR pfd;
	
	pfd = sys_AllocMemory(heap_id, sizeof(PALETTE_FADE_DATA));
	MI_CpuClear8(pfd, sizeof(PALETTE_FADE_DATA));
	return pfd;
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�t�F�[�h�V�X�e�����
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void PaletteFadeFree(PALETTE_FADE_PTR pfd)
{
	sys_FreeMemoryEz(pfd);
}

//--------------------------------------------------------------------------------------------
/**
 * ���N�G�X�g�f�[�^�Z�b�g
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	req			���N�G�X�g�f�[�^�ԍ�
 * @param	def_wk		�����f�[�^
 * @param	trans_wk	�]���p�f�[�^
 * @param	siz			�T�C�Y�i�o�C�g�P�ʁj
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAdrSet(PALETTE_FADE_PTR pfd, FADEREQ req, void * def_wk, void * trans_wk, u32 siz )
{
	pfd->dat[req].def_wk   = (u16 *)def_wk;
	pfd->dat[req].trans_wk = (u16 *)trans_wk;
	pfd->dat[req].siz      = siz;
}

//--------------------------------------------------------------------------------------------
/**
 * ���N�G�X�g�f�[�^��malloc���ăZ�b�g
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	req		���N�G�X�g�f�[�^�ԍ�
 * @param	siz		�f�[�^�T�C�Y�i�o�C�g�P�ʁj
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAllocSet(PALETTE_FADE_PTR pfd, FADEREQ req, u32 siz, u32 heap )
{
	void * def_wk;
	void * trans_wk;

	def_wk   = sys_AllocMemory( heap, siz );
	trans_wk = sys_AllocMemory( heap, siz );

#ifdef	OSP_ERR_PALANMWK_GET	// �p���b�g�t�F�[�h�̃��[�N�擾���s
	if( def_wk == NULL ){
		OS_Printf( "ERROR : PaletteFadeWorkAlloc ( %d ) - def_wk\n", req );
	}
	if( trans_wk == NULL ){
		OS_Printf( "ERROR : PaletteFadeWorkAlloc ( %d ) - trans_wk\n", req );
	}
#endif	// OSP_ERR_PALANMWK_GET

	PaletteFadeWorkAdrSet(pfd, req, def_wk, trans_wk, siz );
}

//--------------------------------------------------------------------------------------------
/**
 * ���N�G�X�g�f�[�^�J��
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	req		���N�G�X�g�f�[�^�ԍ�
 *
 * @return	none
 *
 * @li	PaletteFadeWorkAllocSet()�Ŏ擾�����ꍇ�Ɏg�p
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeWorkAllocFree(PALETTE_FADE_PTR pfd, FADEREQ req)
{
	sys_FreeMemoryEz(pfd->dat[req].def_wk );
	sys_FreeMemoryEz(pfd->dat[req].trans_wk );
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̏����f�[�^���Z�b�g
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	dat		�p���b�g�f�[�^
 * @param	req		���N�G�X�g�f�[�^�ԍ�
 * @param	pos		�J�n�ʒu
 * @param	siz		�f�[�^�T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteWorkSet(PALETTE_FADE_PTR pfd, const void * dat, FADEREQ req, u16 pos, u16 siz )
{
#ifdef	OSP_ERR_PALANM_SIZ_OVER		// �T�C�Y�I�[�o�[
	if( (pos*2+siz) > pfd->dat[req].siz ){
		OS_Printf( "ERROR : PaletteWorkSet - SizeOver ( %d )\n", req );
	}
#endif	// OSP_ERR_PALANM_SIZ_OVER
	MI_CpuCopy16( dat, (void *)&pfd->dat[req].def_wk[pos], (u32)siz );
	MI_CpuCopy16( dat, (void *)&pfd->dat[req].trans_wk[pos], (u32)siz );
}

//--------------------------------------------------------------
/**
 * @brief   �A�[�J�C�u����Ă���p���b�g�f�[�^�����[�h���ă��[�N�ɓW�J���܂�(�g����)
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heap			�f�[�^�ǂݍ��݃e���|�����Ƃ��Ďg���q�[�vID
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   trans_size		�]���T�C�Y(�o�C�g�P�ʁ@��2�o�C�g�A���C�����g����Ă��邱��)
 * @param   pos				�p���b�g�]���J�n�ʒu(�J���[�P��)
 * @param   read_pos		���[�h�����p���b�g�̓ǂݍ��݊J�n�ʒu(�J���[�P��)
 */
//--------------------------------------------------------------
void PaletteWorkSetEx_Arc(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
	FADEREQ req, u32 trans_size, u16 pos, u16 read_pos)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	GF_ASSERT(pos * sizeof(pos) + trans_size <= pfd->dat[req].siz);
	PaletteWorkSet(pfd, &(((u16*)(pal_data->pRawData))[read_pos]), req, pos, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------
/**
 * @brief   �A�[�J�C�u����Ă���p���b�g�f�[�^�����[�h���ă��[�N�ɓW�J���܂�
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heap			�f�[�^�ǂݍ��݃e���|�����Ƃ��Ďg���q�[�vID
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   trans_size		�]���T�C�Y(�o�C�g�P�ʁ@��2�o�C�g�A���C�����g����Ă��邱��)
 * @param   pos				�p���b�g�]���J�n�ʒu(�J���[�P��)
 */
//--------------------------------------------------------------
void PaletteWorkSet_Arc(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
	FADEREQ req, u32 trans_size, u16 pos)
{
	PaletteWorkSetEx_Arc(pfd, fileIdx, dataIdx, heap, req, trans_size, pos, 0);
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�gVRAM���烏�[�N�փf�[�^�R�s�[�����܂�
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   pos				�p���b�g�]���J�n�ʒu(�J���[�P��)
 * @param   trans_size		�]���T�C�Y(�o�C�g�P�ʁ@��2�o�C�g�A���C�����g����Ă��邱��)
 *
 * �g���p���b�g�ɂ͖��Ή��ł�
 */
//--------------------------------------------------------------
void PaletteWorkSet_VramCopy(PALETTE_FADE_PTR pfd, FADEREQ req, u16 pos, u32 trans_size)
{
	u16 *pltt_vram;
	
	GF_ASSERT(pos * sizeof(pos) + trans_size <= pfd->dat[req].siz);

	switch(req){
	case FADE_MAIN_BG:
		pltt_vram = (u16 *)GF_MMAP_MainBgPlttAddr();
		break;
	case FADE_SUB_BG:
		pltt_vram = (u16 *)GF_MMAP_SubBgPlttAddr();
		break;
	case FADE_MAIN_OBJ:
		pltt_vram = (u16 *)GF_MMAP_MainObjPlttAddr();
		break;
	case FADE_SUB_OBJ:
		pltt_vram = (u16 *)GF_MMAP_SubObjPlttAddr();
		break;
	default:
		GF_ASSERT(0 && "���Ή��̃��N�G�X�g�ł�");
		return;
	}
	
	PaletteWorkSet(pfd, &pltt_vram[pos], req, pos, trans_size);
}

//--------------------------------------------------------------
/**
 * @brief   �g���p���b�gVRAM���烏�[�N�փf�[�^�R�s�[�����܂�
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   trans_size		�]���T�C�Y(�o�C�g�P�ʁ@��2�o�C�g�A���C�����g����Ă��邱��)
 * @param   pos				�p���b�g�]���J�n�ʒu(�J���[�P��)
 *
 * ���C���p���b�g��PaletteWorkSet_VramCopy���g�p���Ă�������
 */
//--------------------------------------------------------------
void PaletteWorkSet_VramCopyEx(PALETTE_FADE_PTR pfd, FADEREQ req, u32 trans_size, u16 pos)
{
	GF_ASSERT(0 && "���ݖ��쐬�ł�");
}

//--------------------------------------------------------------
/**
 * @brief   �A�[�J�C�u����Ă���p���b�g�f�[�^���w�肵�����[�N�Ƀ��[�h���܂�(�g����)
 *
 * @param   fileIdx			�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   dataIdx			�A�[�J�C�u�f�[�^�C���f�b�N�X
 * @param   heap			�f�[�^�ǂݍ��݃e���|�����Ƃ��Ďg���q�[�vID
 * @param   trans_size		�]���T�C�Y(�o�C�g�P�ʁ@��2�o�C�g�A���C�����g����Ă��邱��)
 * @param   read_pos		���[�h�����p���b�g�̓ǂݍ��݊J�n�ʒu(�J���[�P��)
 * @param   dest			���[�h�����p���b�g�̓W�J��ւ̃|�C���^
 */
//--------------------------------------------------------------
void PaletteWorkSetEx_ArcWork(u32 fileIdx, u32 dataIdx, u32 heap, u32 trans_size, 
	u16 read_pos, void *dest)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	MI_CpuCopy16(&(((u16*)(pal_data->pRawData))[read_pos]), dest, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���[�N�ԃR�s�[
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	src_req			�R�s�[�����N�G�X�g�f�[�^�ԍ�
 * @param	src_pos			�R�s�[���J�n�ʒu(�J���[�P��)
 * @param	dest_req		�R�s�[�惊�N�G�X�g�f�[�^�ԍ�
 * @param	dest_pos		�R�s�[��J�n�ʒu(�J���[�P��)
 * @param	siz				�R�s�[����f�[�^�T�C�Y(�o�C�g�P��)
 *
 * �R�s�[���͌��f�[�^����ǂݎ��A�R�s�[��͌��f�[�^�A�]����A�̗����ɃR�s�[���s���܂�
 */
//--------------------------------------------------------------------------------------------
void PaletteWorkCopy(PALETTE_FADE_PTR pfd, FADEREQ src_req, u16 src_pos, 
	FADEREQ dest_req, u16 dest_pos, u16 siz )
{
	MI_CpuCopy16((void *)&pfd->dat[src_req].def_wk[src_pos], 
		(void *)&pfd->dat[dest_req].def_wk[dest_pos], siz);
	MI_CpuCopy16((void *)&pfd->dat[src_req].def_wk[src_pos], 
		(void *)&pfd->dat[dest_req].trans_wk[dest_pos], siz);
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���[�N�ɃZ�b�g����Ă���p���b�g�f�[�^���擾
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	tpye	�擾����p���b�g�̎��
 *
 * @return	�Z�b�g����Ă���p���b�g�f�[�^
 */
//--------------------------------------------------------------------------------------------
u16 * PaletteWorkDefaultWorkGet( PALETTE_FADE_PTR pfd, FADEREQ type )
{
	return pfd->dat[type].def_wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g���[�N�ɃZ�b�g����Ă���]���p�p���b�g�f�[�^���擾
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	tpye	�擾����p���b�g�̎��
 *
 * @return	�Z�b�g����Ă���p���b�g�f�[�^
 */
//--------------------------------------------------------------------------------------------
u16 * PaletteWorkTransWorkGet( PALETTE_FADE_PTR pfd, FADEREQ type )
{
	return pfd->dat[type].trans_wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�t�F�[�h���N�G�X�g�i�㏑���s�j
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	req_bit		�p���b�g�̎�ށi�r�b�g�w��j
 * @param	fade_bit	�p���b�g�w��i�r�b�g�w��jbit0 = pal0
 * @param	wait		�v�Z�҂����ԁi�}�C�i�X����j
 * @param	start_evy	�����Z�x
 * @param	end_evy		�ŏI�Z�x
 * @param	next_rgb	�ύX��̐F
 *
 * @retval	"0 = ����"
 * @retval	"1 = �G���["
 *
 * @li	�Z�x�F0 �` 16 ( 0(���̐F) �` 2,3..(���ԐF) �` 16(�w�肵���F) )
 */
//--------------------------------------------------------------------------------------------
u8 PaletteFadeReq(PALETTE_FADE_PTR pfd, u16 req_bit, u16 fade_bit, s8 wait, 
	u8 start_evy, u8 end_evy, u16 next_rgb )
{
	u16	cpy_bit;
	u8	tmp;
	u8	i;

	cpy_bit = fade_bit;
	tmp = 0;
	for( i=0; i<ALL_PALETTE_SIZE; i++ ){
		if( ReqBitCheck( req_bit, i ) == TRUE &&
			ReqBitCheck( pfd->req_bit, i ) == FALSE ){

			FadeBitCheck( i, &pfd->dat[i], &fade_bit );
			FadeReqSet( &pfd->dat[i].prm, fade_bit, wait, start_evy, end_evy, next_rgb );

			TransBitSet( pfd, i );
			if( i >= FADE_MAIN_BG_EX0 ){
				PaletteFadeMain( pfd, i, EXTRA_COLOR_NUM );
			}else{
				PaletteFadeMain( pfd, i, NORMAL_COLOR_NUM );
			}

			fade_bit = cpy_bit;
			tmp = 1;
		}
	}

	if( tmp == 1 ){
		pfd->req_bit |= req_bit;
		if( pfd->tcb_flg == 0 ){
			pfd->tcb_flg = 1;
			pfd->req_flg = 1;
			pfd->force_stop = FALSE;
			TCB_Add( PaletteFadeTask, pfd, TCBPRI_CALC_FADETASK );
		}
	}

	return tmp;
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�t�F�[�h���N�G�X�g�i�㏑���j
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	req_bit		�p���b�g�̎�ށi�r�b�g�w��j
 * @param	fade_bit	�p���b�g�w��i�r�b�g�w��jbit0 = pal0
 * @param	wait		�v�Z�҂����ԁi�}�C�i�X����j
 * @param	start_evy	�����Z�x
 * @param	end_evy		�ŏI�Z�x
 * @param	next_rgb	�ύX��̐F
 *
 * @retval	"0 = ����"
 * @retval	"1 = �G���["
 *
 * @li	�Z�x�F0 �` 16 ( 0(���̐F) �` 2,3..(���ԐF) �` 16(�w�肵���F) )
 */
//--------------------------------------------------------------------------------------------
u8 PaletteFadeReqWrite(PALETTE_FADE_PTR pfd, u16 req_bit, u16 fade_bit, s8 wait, 
	u8 start_evy, u8 end_evy, u16 next_rgb )
{
	u16	cpy_bit;
	u8	tmp;
	u8	i;

	cpy_bit = fade_bit;
	tmp = 0;
	for( i=0; i<ALL_PALETTE_SIZE; i++ ){
		if( ReqBitCheck( req_bit, i ) == TRUE ){
			FadeBitCheck( i, &pfd->dat[i], &fade_bit );
			FadeReqSet( &pfd->dat[i].prm, fade_bit, wait, start_evy, end_evy, next_rgb );

			TransBitSet( pfd, i );
			if( i >= FADE_MAIN_BG_EX0 ){
				PaletteFadeMain( pfd, i, EXTRA_COLOR_NUM );
			}else{
				PaletteFadeMain( pfd, i, NORMAL_COLOR_NUM );
			}

			fade_bit = cpy_bit;
			tmp = 1;
		}
	}

	if( tmp == 1 ){
//		pfd->req_bit |= req_bit;
		pfd->req_bit = req_bit;
		if( pfd->tcb_flg == 0 ){
			pfd->tcb_flg = 1;
			pfd->req_flg = 1;
			pfd->force_stop = FALSE;
			TCB_Add( PaletteFadeTask, pfd, TCBPRI_CALC_FADETASK );
		}
	}

	return tmp;
}

//--------------------------------------------------------------------------------------------
/**
 * ���N�G�X�g�̏�Ԃ𒲂ׂ�
 *
 * @param	flg		
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static u8 ReqBitCheck( u16 flg, u16 req )
{
	if( ( flg & ( 1 << req ) ) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �]���t���O�Z�b�g
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	id		�p���b�gID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TransBitSet( PALETTE_FADE_PTR pfd, u16 id )
{
	if( ReqBitCheck( pfd->trans_bit, id ) == TRUE ){
		return;
	}
	pfd->trans_bit |= ( 1 << id );
}

//--------------------------------------------------------------------------------------------
/**
 * �t�F�[�h�r�b�g�`�F�b�N
 *
 * @param	req			���N�G�X�g�f�[�^�ԍ�
 * @param	wk			���N�G�X�g�f�[�^
 * @param	fade_bit	�p���b�g�w��i�r�b�g�w��jbit0 = pal0
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeBitCheck( FADEREQ req, FADE_REQ_EX2 * wk, u16 * fade_bit )
{
	u16	siz_bit;
	u8	i, j;

	if( req < NORMAL_PALETTE_SIZE ){
		j = wk->siz / 32;
	}else{
		j = wk->siz / 512;
	}

	siz_bit = 0;
	for( i=0; i<j; i++ ){
		siz_bit += ( 1 << i );
	}

	*fade_bit &= siz_bit;
}


//--------------------------------------------------------------------------------------------
/**
 * �p�����[�^�Z�b�g
 *
 * @param	wk			�f�[�^
 * @param	fade_bit	�p���b�g�w��i�r�b�g�w��jbit0 = pal0
 * @param	wait		�v�Z�҂����ԁi�}�C�i�X����j
 * @param	start_evy	�����Z�x
 * @param	end_evy		�ŏI�Z�x
 * @param	next_rgb	�ύX��̐F
 *
 * @return	none
 *
 * @li	�Z�x�F0 �` 16 ( 0(���̐F) �` 2,3..(���ԐF) �` 16(�w�肵���F) )
 */
//--------------------------------------------------------------------------------------------
static void FadeReqSet(
				FADE_REQ_PARAM * wk, u16 fade_bit,
				s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb )
{
	// wait��ϲŽ�̎���value��傫������̪��ނ𑁂�����
	if( wait < 0 ){
		wk->fade_value = DEF_FADE_VAL + abs( wait );
		wk->wait = 0;
	}else{
		wk->fade_value = DEF_FADE_VAL;
		wk->wait = wait;
	}

	wk->fade_bit = fade_bit;
	wk->now_evy  = start_evy;
	wk->end_evy  = end_evy;
	wk->next_rgb = next_rgb;
	wk->wait_cnt = wk->wait;
	
	if( start_evy < end_evy ){
		wk->direction = 0;
	}else{
		wk->direction = 1;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�t�F�[�h���C���^�X�N
 *
 * @param	tcb		TCB�̃|�C���^
 * @param	work	TCB���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFadeTask( TCB_PTR tcb, void * work )
{
	PALETTE_FADE_PTR pfd = work;
	
	if(pfd->force_stop == TRUE){
		pfd->force_stop = FALSE;
		pfd->trans_bit = 0;
		pfd->req_bit = 0;
		pfd->tcb_flg = 0;
		TCB_Delete( tcb );
		return;
	}
	
	if( pfd->req_flg != 1 ){ return; }

	pfd->trans_bit = pfd->req_bit;

	NormalPaletteFade(pfd);
	ExtraPaletteFade(pfd);

	if( pfd->req_bit == 0 ){
		pfd->tcb_flg = 0;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�t�F�[�h������~����
 *
 * @param	tcb		TCB�̃|�C���^
 * @param	work	TCB���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeForceStop(PALETTE_FADE_PTR pfd)
{
	if(pfd->req_bit == 0){
		return;
	}
	
	pfd->force_stop = TRUE;
}

//--------------------------------------------------------------------------------------------
/**
 * �ʏ�p���b�g�̃t�F�[�h�v�Z
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void NormalPaletteFade(PALETTE_FADE_PTR pfd)
{
	u8	i, j;

	for( i=0; i<NORMAL_PALETTE_SIZE; i++ ){
/*
		if( ReqBitCheck( pfd->req_bit, i ) == FALSE ){
			continue;
		}

		if( pfd->dat[i].prm.wait_cnt < pfd->dat[i].prm.wait ){
			pfd->dat[i].prm.wait_cnt++;
			continue;
		}else{
			pfd->dat[i].prm.wait_cnt = 0;
		}

		for( j=0; j<16; j++ ){
			if( ReqBitCheck( pfd->dat[i].prm.fade_bit, j ) == FALSE ){
				continue;
			}
			FadeWorkSet(
				&pfd->dat[i].def_wk[j<<4],
				&pfd->dat[i].trans_wk[j<<4],
				&pfd->dat[i].prm, 16 );
		}

		FadeParamCheck(pfd, i, &pfd->dat[i].prm );
*/
		PaletteFade( pfd, i, NORMAL_COLOR_NUM );

	}
}

//--------------------------------------------------------------------------------------------
/**
 * �g���p���b�g�̃t�F�[�h�v�Z
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void ExtraPaletteFade(PALETTE_FADE_PTR pfd)
{
	u8	i, j;

	for( i=NORMAL_PALETTE_SIZE; i<ALL_PALETTE_SIZE; i++ ){
/*
		if( ReqBitCheck( pfd->req_bit, i ) == FALSE ){
			continue;
		}

		if( pfd->dat[i].prm.wait_cnt < pfd->dat[i].prm.wait ){
			pfd->dat[i].prm.wait_cnt++;
			continue;
		}else{
			pfd->dat[i].prm.wait_cnt = 0;
		}

		for( j=0; j<16; j++ ){
			if( ReqBitCheck( pfd->dat[i].prm.fade_bit, j ) == FALSE ){
				continue;
			}
			FadeWorkSet(
				&pfd->dat[i].def_wk[j<<8],
				&pfd->dat[i].trans_wk[j<<8],
				&pfd->dat[i].prm, 256 );
		}

		FadeParamCheck(pfd, i, &pfd->dat[i].prm );
*/
		PaletteFade( pfd, i, EXTRA_COLOR_NUM );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃t�F�[�h�v�Z
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	id		�p���b�gID
 * @param	siz		�J���[�� ( �ʏ� = 16, �g�� = 256 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFade( PALETTE_FADE_PTR pfd, u16 id, u16 siz )
{
	if( ReqBitCheck( pfd->req_bit, id ) == FALSE ){
		return;
	}

	if( pfd->dat[id].prm.wait_cnt < pfd->dat[id].prm.wait ){
		pfd->dat[id].prm.wait_cnt++;
		return;
	}else{
		pfd->dat[id].prm.wait_cnt = 0;
	}

	PaletteFadeMain( pfd, id, siz );
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�̃t�F�[�h�v�Z���C��
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	id		�p���b�gID
 * @param	siz		�J���[�� ( �ʏ� = 16, �g�� = 256 )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PaletteFadeMain( PALETTE_FADE_PTR pfd, u16 id, u16 siz )
{
	u32	i;

	for( i=0; i<16; i++ ){
		if( ReqBitCheck( pfd->dat[id].prm.fade_bit, i ) == FALSE ){
			continue;
		}
		FadeWorkSet(
			&pfd->dat[id].def_wk[i*siz],
			&pfd->dat[id].trans_wk[i*siz],
			&pfd->dat[id].prm, siz );
	}
	FadeParamCheck( pfd, id, &pfd->dat[id].prm );
}


//--------------------------------------------------------------------------------------------
/**
 * �J���[�v�Z
 *
 * @param	def		���p���b�g�f�[�^
 * @param	trans	�v�Z��̃p���b�g�f�[�^
 * @param	wk		�t�F�[�h�p�����[�^
 * @param	siz		�v�Z�T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeWorkSet( u16 * def, u16 * trans, FADE_REQ_PARAM * wk, u32 siz )
{
	u32	i;
	u8	red, green, blue;

	for( i=0; i<siz; i++ ){
		red   =
			FADE_CHANGE( (def[i]&0x1f), (wk->next_rgb&0x1f), wk->now_evy );
		green =
			FADE_CHANGE( ((def[i]>>5)&0x1f), ((wk->next_rgb>>5)&0x1f), wk->now_evy );
		blue  =
			FADE_CHANGE( ((def[i]>>10)&0x1f), ((wk->next_rgb>>10)&0x1f), wk->now_evy );

		trans[i] = ( blue << 10 ) | ( green << 5 ) | red;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �t�F�[�h�̐i�s�󋵂��Ď�
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param	id		�t�F�[�h�f�[�^�ԍ�
 * @param	wk		�t�F�[�h�p�����[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void FadeParamCheck(PALETTE_FADE_PTR pfd, u8 id, FADE_REQ_PARAM * wk )
{
	s16	tmp;

	if( wk->now_evy == wk->end_evy ){
		if( ( pfd->req_bit & ( 1 << id ) ) != 0 ){
			pfd->req_bit ^= ( 1 << id );
		}
	}else if( wk->direction == 0 ){
		tmp = wk->now_evy;
		tmp += wk->fade_value;
		if( tmp > wk->end_evy ){
			tmp = wk->end_evy;
		}
		wk->now_evy = tmp;
	}else{
		tmp = wk->now_evy;
		tmp -= wk->fade_value;
		if( tmp < wk->end_evy ){
			tmp = wk->end_evy;
		}
		wk->now_evy = tmp;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �p���b�g�]��
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 *
 * @return	none
 *
 * @li	VBlank���ŌĂԂ���
 */
//--------------------------------------------------------------------------------------------
void PaletteFadeTrans(PALETTE_FADE_PTR pfd)
{
	if( pfd->auto_trans == FALSE && pfd->req_flg != 1 ){ return; }

	{
		int	i;

		for( i=0; i<ALL_PALETTE_SIZE; i++ ){
			if(pfd->auto_trans == FALSE){
				if(pfd->dat[i].trans_wk == NULL || ReqBitCheck( pfd->trans_bit, i ) == FALSE){
					continue;
				}
			}

			DC_FlushRange( (void*)pfd->dat[i].trans_wk, pfd->dat[i].siz );
			switch( i ){
			case FADE_MAIN_BG:
				GX_LoadBGPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_SUB_BG:
				GXS_LoadBGPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_MAIN_OBJ:
				GX_LoadOBJPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_SUB_OBJ:
				GXS_LoadOBJPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				break;
			case FADE_MAIN_BG_EX0:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT0_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX1:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT1_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX2:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT2_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_BG_EX3:
				GX_BeginLoadBGExtPltt();
				GX_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT3_ADRS, pfd->dat[i].siz );
				GX_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX0:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT0_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX1:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT1_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX2:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT2_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_SUB_BG_EX3:
				GXS_BeginLoadBGExtPltt();
				GXS_LoadBGExtPltt(
					(const void *)pfd->dat[i].trans_wk,
					EX_PAL_SLOT3_ADRS, pfd->dat[i].siz );
				GXS_EndLoadBGExtPltt();
				break;
			case FADE_MAIN_OBJ_EX:
				GX_BeginLoadOBJExtPltt();
				GX_LoadOBJExtPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				GX_EndLoadOBJExtPltt();
				break;
			case FADE_SUB_OBJ_EX:
				GXS_BeginLoadOBJExtPltt();
				GXS_LoadOBJExtPltt(
					(const void *)pfd->dat[i].trans_wk, 0, pfd->dat[i].siz );
				GXS_EndLoadOBJExtPltt();
			}
		}
	}

	pfd->trans_bit = pfd->req_bit;
	if( pfd->trans_bit == 0 ){
		pfd->req_flg = 0;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �I���`�F�b�N
 *
 * @param   pfd		�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval	"0 = �I��"
 * @retval	"0 != ������"
 */
//--------------------------------------------------------------------------------------------
u16 PaletteFadeCheck(PALETTE_FADE_PTR pfd)
{
	return pfd->req_bit;
}

//--------------------------------------------------------------
/**
 * @brief   �����]���t���O���Z�b�g����
 *
 * @param   pfd			�p���b�g�t�F�[�h�V�X�e�����[�N�ւ̃|�C���^
 * @param   on_off		TRUE:�����]��ON�B�@FALSE:�����]��OFF
 */
//--------------------------------------------------------------
void PaletteTrans_AutoSet(PALETTE_FADE_PTR pfd, int on_off)
{
	pfd->auto_trans = on_off;
}


void PaletteTransSwitch(PALETTE_FADE_PTR pfd, u8 flag)
{
	pfd->req_flg = flag & 0x01;
	pfd->req_bit = 0xFFFFFFFF;
}



//--------------------------------------------------------------------------------------------
/**
 * �w��p���b�g�S�̂��N���A
 *
 * @param	bit		�N���A����p���b�g
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PaletteAreaClear( u16 bit, u32 heap )
{
	void * buf;

	buf = (u8 *)sys_AllocMemory( heap, FADE_PAL_ALL_SIZE );
	memset( buf, 0, FADE_PAL_ALL_SIZE );
	DC_FlushRange( (void*)buf, FADE_PAL_ALL_SIZE );

	if( bit & PF_BIT_MAIN_BG ){
		GX_LoadBGPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_SUB_BG ){
		GXS_LoadBGPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_MAIN_OBJ ){
		GX_LoadOBJPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}
	if( bit & PF_BIT_SUB_OBJ ){
		GXS_LoadOBJPltt( (const void *)buf, 0, FADE_PAL_ALL_SIZE );
	}

	sys_FreeMemory( heap, buf );

	buf = (u8 *)sys_AllocMemory( heap, FADE_EXPAL_ALL_SIZE );
	memset( buf, 0, FADE_EXPAL_ALL_SIZE );
	DC_FlushRange( (void*)buf, FADE_EXPAL_ALL_SIZE );

	if( bit & PF_BIT_MAIN_BG_EX0 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT0_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX1 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT1_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX2 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT2_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_MAIN_BG_EX3 ){
		GX_BeginLoadBGExtPltt();
		GX_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT3_ADRS, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX0 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT0_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX1 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT1_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX2 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT2_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}
	if( bit & PF_BIT_SUB_BG_EX3 ){
		GXS_BeginLoadBGExtPltt();
		GXS_LoadBGExtPltt( (const void *)buf, EX_PAL_SLOT3_ADRS, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadBGExtPltt();
	}

	if( bit & PF_BIT_MAIN_OBJ_EX ){
		GX_BeginLoadOBJExtPltt();
		GX_LoadOBJExtPltt( (const void *)buf, 0, FADE_EXPAL_ALL_SIZE );
		GX_EndLoadOBJExtPltt();
	}

	if( bit & PF_BIT_SUB_OBJ_EX ){
		GXS_BeginLoadOBJExtPltt();
		GXS_LoadOBJExtPltt( (const void *)buf, 0, FADE_EXPAL_ALL_SIZE );
		GXS_EndLoadOBJExtPltt();
	}

	sys_FreeMemory( heap, buf );
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g���[�N���w��R�[�h�ŃN���A����
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   select			�o�b�t�@�w��
 * @param   clear_code		�N���A�R�[�h
 * @param   start			�J�n�ʒu(�J���[�ʒu)
 * @param   end				�I���ʒu(�J���[�ʒu�@���I���ʒu�̃J���[�͏��������܂���B)
 *
 * start=0, end=16 �Ƃ���ƃp���b�g1�{�܂�܂�N���A�ΏۂɂȂ�܂��B
 * start=0, end=15 �Ƃ���ƁA�p���b�g�̍Ō�̃J���[�͑ΏۂɊ܂܂�܂���B
 */
//--------------------------------------------------------------
void PaletteWork_Clear(PALETTE_FADE_PTR pfd, FADEREQ req, FADEBUF select, 
	u16 clear_code, u16 start, u16 end)
{
	GF_ASSERT(end * sizeof(u16) <= pfd->dat[req].siz);

	if(select == FADEBUF_SRC || select == FADEBUF_ALL){
		MI_CpuFill16(&pfd->dat[req].def_wk[start], clear_code, (end - start) * 2);
	}
	if(select == FADEBUF_TRANS || select == FADEBUF_ALL){
		MI_CpuFill16(&pfd->dat[req].trans_wk[start], clear_code, (end - start) * 2);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �w��ʒu�̃J���[�f�[�^���p���b�g���[�N����擾����
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   select			�o�b�t�@�w��
 * @param   color_pos		�擾����J���[�̈ʒu
 *
 * @retval  �J���[�f�[�^
 */
//--------------------------------------------------------------
u16 PaletteWork_ColorGet(PALETTE_FADE_PTR pfd, FADEREQ req, FADEBUF select, u16 color_pos)
{
	if(select == FADEBUF_SRC){
		return pfd->dat[req].def_wk[color_pos];
	}
	if(select == FADEBUF_TRANS){
		return pfd->dat[req].trans_wk[color_pos];
	}

	GF_ASSERT(0 && "�o�b�t�@�w�肪�Ԉ���Ă��܂�\n");
	return 0;
}




//==============================================================================
//	�ʃc�[��
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �\�t�g�t�F�[�h�C���A�A�E�g
 *
 * @param   src			���p���b�g�f�[�^�ւ̃|�C���^
 * @param   dest		�ύX�f�[�^�����
 * @param   col_num		�ύX����J���[��
 * @param   evy			�W��(0�`16) (�ύX�̓x�����A0(���̐F)�`2,3..(���ԐF)�`16(�w�肵���F)
 * @param   next_rgb	�ύX��̐F���w��
 */
//--------------------------------------------------------------
void SoftFade(const u16 *src, u16 *dest, u16 col_num, u8 evy, u16 next_rgb)
{
	u16 i;
	int red, green, blue;
	int next_red, next_green, next_blue;
	
	next_red = ((PLTT_DATA*)&next_rgb)->Red;
	next_green = ((PLTT_DATA*)&next_rgb)->Green;
	next_blue = ((PLTT_DATA*)&next_rgb)->Blue;
	
	for(i = 0; i < col_num; i++){
		red = ((PLTT_DATA*)&src[i])->Red;
		green = ((PLTT_DATA*)&src[i])->Green;
		blue = ((PLTT_DATA*)&src[i])->Blue;
	
		dest[i] = 
			FADE_CHANGE(red, next_red, evy) |
			(FADE_CHANGE(green, next_green, evy) << 5) |
			(FADE_CHANGE(blue, next_blue, evy) << 10);
	}
}

//--------------------------------------------------------------
/**
 * @brief   PFD�������Ƃ����J���[�����Z
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   start_pos		�\�t�g�t�F�[�h�J�n�ʒu(�J���[�P��)
 * @param   col_num			start_pos���牽�̃J���[�������Z�ΏۂƂ��邩(�J���[�P��)
 * @param   evy				EVY�l
 * @param   next_rgb		�ύX��̐F
 */
//--------------------------------------------------------------
void SoftFadePfd(PALETTE_FADE_PTR pfd, FADEREQ req, u16 start_pos, u16 col_num, 
	u8 evy, u16 next_rgb)
{
	GF_ASSERT(pfd->dat[req].def_wk != NULL && pfd->dat[req].trans_wk != NULL);
	
	SoftFade(&pfd->dat[req].def_wk[start_pos], &pfd->dat[req].trans_wk[start_pos], 
		col_num, evy, next_rgb);
}

//--------------------------------------------------------------
/**
 * @brief   �J���[�����Z(�r�b�g�w��F�p���b�g�P��)
 *
 * @param   src				���p���b�g�f�[�^�ւ̃|�C���^
 * @param   dest			�ύX�f�[�^�����
 * @param   fade_bit		�����Z�Ώۂ̃r�b�g
 * @param   evy				EVY�l
 * @param   next_rgb		�ύX��̐F
 */
//--------------------------------------------------------------
void ColorConceChange(const u16 *src, u16 *dest, u16 fade_bit, u8 evy, u16 next_rgb)
{
	int offset = 0;
	
	while(fade_bit){
		if(fade_bit & 1){
			SoftFade(&src[offset], &dest[offset], 16, evy, next_rgb);
		}
		fade_bit >>= 1;
		offset += 16;
	}
}

//--------------------------------------------------------------
/**
 * @brief   PFD�������Ƃ����J���[�����Z(�r�b�g�w��F�p���b�g�P��)
 *
 * @param   pfd				�p���b�g�t�F�[�h�V�X�e���ւ̃|�C���^
 * @param   req				���N�G�X�g�f�[�^�ԍ�
 * @param   fade_bit		�����Z�Ώۂ̃r�b�g
 * @param   evy				EVY�l
 * @param   next_rgb		�ύX��̐F
 */
//--------------------------------------------------------------
void ColorConceChangePfd(PALETTE_FADE_PTR pfd, FADEREQ req, u16 fade_bit, u8 evy, u16 next_rgb)
{
	int offset = 0;
	
	GF_ASSERT(pfd->dat[req].def_wk != NULL && pfd->dat[req].trans_wk != NULL);
	
	while(fade_bit){
		if(fade_bit & 1){
			SoftFadePfd(pfd, req, offset, 16, evy, next_rgb);
		}
		fade_bit >>= 1;
		offset += 16;
	}
}

// =============================================================================
//
//
//	���J���[����֐��S  add goto
//
//
// =============================================================================
#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)
#define COL_FIL(c, p)	((u16)((p)*(c))>>8)

//--------------------------------------------------------------
/**
 * @brief	�O���[�X�P�[����
 *
 * @param	pal				�ύX�Ώۃp���b�g�f�[�^
 * @param	pal_size		�ύX�T�C�Y(���F�ύX���邩)
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PaletteGrayScale(u16* pal, int pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�O���[�X�P�[������ARGB�̔䗦��������
 *
 * @param	pal	
 * @param	pal_size	
 * @param	rp	
 * @param	gp	
 * @param	bp	
 *
 * @retval	none
 *
 *		 r = g = b = 256 �ŃO���[�X�P�[���֐��Ɠ�������
 *
 */
//--------------------------------------------------------------
void PaletteColorChange(u16* pal, int pal_size, int rp, int gp, int bp)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);
		
		r = COL_FIL(c, rp);
		g = COL_FIL(c, gp);
		b = COL_FIL(c, bp);

		if (r > 31){ r = 31; }
		if (g > 31){ g = 31; }
		if (b > 31){ b = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}	
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃p���b�g��ϊ����ē]��
 *
 * @param	pfd			
 * @param	fileIdx	
 * @param	dataIdx	
 * @param	heap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PokeColorChange(PALETTE_FADE_PTR pfd, u32 fileIdx, u32 dataIdx, u32 heap, 
					 FADEREQ req, u32 trans_size, u16 pos, int r, int g, int b)
{
	NNSG2dPaletteData *pal_data;
	void *arc_data;
	
	arc_data = ArcUtil_PalDataGet(fileIdx, dataIdx, &pal_data, heap);
	GF_ASSERT(arc_data != NULL);
	
	if(trans_size == 0){
		trans_size = pal_data->szByte;
	}
	
	//PaletteGrayScale(pal_data->pRawData, 16);
	PaletteColorChange(pal_data->pRawData, 16, r,g,b);

	PaletteWorkSet(pfd, pal_data->pRawData, req, pos, trans_size);
	
	sys_FreeMemoryEz(arc_data);
}




































//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
//============================================================================================
#if 0

//=========================================================================
/**
 *	@file	palanm.c
 *	@brief	�p���b�g�A�j���E�t�F�[�h�A�E�g�A�C��
 *	@author	2004 Game Freak Inc.
 *	@date	04.03.08
 */
//=========================================================================

#include "common.h"
#include "palanm.h"
#include "softfade.h"
#include "ef_tool.h"
#include "decord.h"
#include "task.h"

//----------------------------------------------------------
//	�v���g�^�C�v�錾	�֐����ް�
//----------------------------------------------------------
u8 AddPalAnm(const PalAnmData *pAnmDat, u16 pal_no);
u8 PaletteAnime(void);
static void PaletteAnimeEndCheck(PalAnmWorkData *paw);
void DelPalAnm(u16 id_no);
void PalAnmInitWork(u8 pal_anm_no);
void PaletteAnimeInit(void);
void PalAnmPause(u16 id_no);
void PalAnmMove(u16 id_no);
u8 PalAnmGetWorkNumber(u16 id_no);
void PaletteFadeTrans( void );
void PlttCopy(void);
void PaletteAnimeBeforeAfter(u8 trans_type, u32 *PalAnmBit);
static void PaletteAnimeSub(PalAnmWorkData *paw, u32*);
u8 ColorAddSub(void);
static void FadeCheck(PalAnmWorkData *paw, u32 *PalAnmBit);
void FadeWorkInit(void);
u8 LightColorAddSub(void);
static u8 HardColorCalc(void);
static void HardColorRegisterSet(void);
static u8 FadeEndWaitCheck(void);
void LightFadeReqAdj(u8 fade_type, u8 fade_value);
static void LightFadeCommon(u8 fade_type);

//----------------------------------------------------------
//	�O���[�o���ϐ�
//----------------------------------------------------------
u16 PaletteWork[0x200] = {};			//�ؼ��ف@�@BG&OBJ��گ��ޯ�����
u16 PaletteWorkTrans[0x200] = {};		//�]���p
PalAnmWorkData PalAnmWork[PAL_ANM_MAX] = {};	//�p���b�g�A�j���pܰ�
PlttFadeData FadeData = {};				//̪��ޱ�āA�ݗp�\����
u32 PalAnmFadeBit = 0;	//��گı�ҁA̪��޲݁A��Ă�������گ� �e�ޯĂ���گ�No�ɑΉ�

//�f�o�b�O 2002.09.12 TETSU
u16 PaletteWorkTmp[0x200] = {};			//�W�J�e���|�������[�N
//�f�o�b�O
//
//----------------------------------------------------------
//	�f�[�^
//----------------------------------------------------------
const PalAnmData DmmyPalAnmDat = 
{
	65535,			//id_no
	0, //*PalData		�]������װ��گı��ڽ
	PA_BEFORE,      //type			BEFORE:�װ�����Z�Ώہ@�@AFTER:�װ�����Z��Ώ�
	PA_BG0+PA_COL0, //pal_no		0�`511
	0,              //TransValue	col_no���� �����܂ł���گĂ�ΏۂƂ��邩
	0,              //TransWaitDef	������گı�҂Ɉڂ�܂ł̳���
	0,              //TransValueLoopDef	����]�����J��Ԃ���
	PA_END,         //PalAnmSeq		��ҏI����̏���
	0,             //LoopWaitDef
};




//=========================================================================
//	�p���b�g���[�N�Ɉ��k���ꂽ�p���b�g�f�[�^���Z�b�g
// ����:*SrcAdrs = ���k����Ă����ް����ڽ
// 		pal_no = �W�J����ꏊ  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...��
//		size = �޲Ļ���
//=========================================================================
void DecordPaletteWork(void *SrcAdrs, u16 pal_no, u16 size)
{
#if 0
	DecordWram(SrcAdrs, &PaletteWork[pal_no]);
	CpuCopy(&PaletteWork[pal_no], &PaletteWorkTrans[pal_no], size, 16);
#else
	DecordWram(SrcAdrs, &PaletteWorkTmp[0x0000]);
	CpuCopy(&PaletteWorkTmp[0x0000], &PaletteWork[pal_no], size, 16);
	CpuCopy(&PaletteWorkTmp[0x0000], &PaletteWorkTrans[pal_no], size, 16);
#endif
}
//=========================================================================
//	�p���b�g���[�N�ɔ񈳏k�̃p���b�g�f�[�^���Z�b�g
// ����:*SrcAdrs = ���k����Ă����ް����ڽ
// 		pal_no = �W�J����ꏊ  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...��
//		size = �޲Ļ���
//=========================================================================
void PaletteWorkSet(const u16 *pal_data, u16 pal_no, u16 size)
{
	CpuCopy(pal_data, &PaletteWork[pal_no], size, 16);
	CpuCopy(pal_data, &PaletteWorkTrans[pal_no],size, 16);
}

//=========================================================================
//	�p���b�g���[�N���w��f�[�^�ŃN���A����
// ����: clear_data = ���̃f�[�^�ŗ̈�𖄂߂܂��B
//		pal_no = �ر�����ꏊ  PA_BG0+PA_COL5  PA_OBJ3+PA_COL0 ...��
//		size = �޲Ļ���
//=========================================================================
void PaletteWorkClear(u16 clear_data, u16 pal_no, u16 size)
{
	CpuClear(clear_data, &PaletteWork[pal_no], size, 16);
	CpuClear(clear_data, &PaletteWorkTrans[pal_no], size, 16);
}

/*----------------------------------------------------------*/
/*	V�u�����N���̏���										*/
/*	(V�u�����N���ɏ�ɃR�[�����Ă��������j					*/
/*----------------------------------------------------------*/
void PaletteFadeTrans( void )
{
	if(FadeData.trans_stop == 1)
		return;
	
	DIV_DMACOPY(3, PaletteWorkTrans, PLTT, PLTT_SIZE, 16);
	PalAnmFadeBit = 0;
	if(FadeData.type == 2 && FadeData.fade_sw)
		HardColorRegisterSet();
}
=======
>>>>>>> 1.6

<<<<<<< palanm.c
//=========================================================================
//	�p���b�g�A�j��		  ��Ҳ�ٰ�ߓ��ŌĂ�ł�������
// �߂�l: 0=̪���ظ��Ă��������ĂȂ��A����ظ��Ă��I������
//         1=̪��ގ��s��
//         2=̪���ظ��Ă͂������Ă��邪���Ē��Ȃ̂�(̪��ނ�)�����͂��Ȃ�����
//      0xff=�O���ظ����ް����܂��]������Ă��Ȃ�
//=========================================================================
u8 PaletteAnime(void)
{
	u8 temp;
	u32 PalAnmBit = 0;
	
	if(PalAnmFadeBit != 0)
		return 0xff;
	
	if(FadeData.type == 0)
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = ColorAddSub();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	else if(FadeData.type == 1)
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = LightColorAddSub();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	else
	{
//		PaletteAnimeBeforeAfter(PA_BEFORE, &PalAnmBit);
		temp = HardColorCalc();
//		PaletteAnimeBeforeAfter(PA_AFTER, &PalAnmBit);
	}
	
	PalAnmFadeBit = PalAnmBit | FadeData.fade_bit;
	return temp;
}
//----------------------------------------------------------
//	��گı��ܰ�&̪���ظ��ėpܰ��S������
//----------------------------------------------------------
void PaletteAnimeInit(void)
=======
void PaletteTransSwitch(u8 flag)
>>>>>>> 1.6
{
<<<<<<< palanm.c
	u8 i;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		PalAnmInitWork(i);
	}
	FadeWorkInit();
}
//----------------------------------------------------------
//	PLTT_VRAM���ް���S��PaletteWork�ɺ�߰
//----------------------------------------------------------
void PlttCopy(void)
{
	u16 i;
	u16 *dest;
	
	dest = (u16 *)PLTT;
	
	for(i = 0; i < 0x200; i++)
	{
		PaletteWork[i] = dest[i];
		PaletteWorkTrans[i] = dest[i];
	}
=======
	FadeData.req_flg = flag & 0x01;
	FadeData.req_bit = 0xFFFFFFFF;
>>>>>>> 1.6
}

<<<<<<< palanm.c
//----------------------------------------------------------
//	�p���b�g�����Z���N�G�X�g  ��ظ��Ă��d�Ȃ����ꍇ�͐揟���ł�
//
// fade_bit : �p���b�g���w��i�e�r�b�g���p���b�g�ԍ��ɑΉ�
//			  �r�b�g0 = BG��0�p���b�g�A Bit16 = OBJ��0�p���b�g)
// wait : �l��傫������Ƃ������̪��ޱ�āA�݂��܂��B
//		  �l������������Ƒ���̪��ޱ�āA�݂��܂��B
// start_evy : �ŏ��̐F�̔Z�x���w�肵�܂�(0�`16)
// 			   0(���̐F)�`2,3..(���ԐF)�`16(�w�肵���F)
// end_evy : ̪��ތv�Z��̍ŏI�I�ȐF�̔Z�x���w�肵�܂��B�����̒l�́��Ɠ����ł�
// next_rgb : �ύX��̐F���w��
//
// �߂�l: 1=����I��  0=�װ
//----------------------------------------------------------
u8 PaletteFadeReq(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb)
{
	u8 temp;
	
	if(FadeData.fade_sw == 1)
		return 0;
	
	FadeData.fade_value = 2;
	if(wait < 0){	//wait��ϲŽ�̎���value��傫������̪��ނ𑁂�����
		FadeData.fade_value += abs(wait);
		wait = 0;
	}
	
	FadeData.fade_bit = fade_bit;
	FadeData.wait = wait;			//�����ظ��Ă������u�ԂɎ��s
	FadeData.wait_def = wait;
	FadeData.now_evy = start_evy;
	FadeData.end_evy = end_evy;
	FadeData.next_rgb = next_rgb;
	FadeData.fade_sw = 1;
	FadeData.type = 0;
	if(start_evy < end_evy)
		FadeData.direction = 0;
	else
		FadeData.direction = 1;
	
	PaletteAnime();		//add 2001.06.26(��) ظ��Ă��Ă����ɔ��f������悤�ύX
	
	temp = FadeData.trans_stop;
	FadeData.trans_stop = 0;

	//PaletteFadeTrans();	//add 2001.06.26(��)
	CpuCopy(PaletteWorkTrans, PLTT, PLTT_SIZE, 32);
	PalAnmFadeBit = 0;
	if(FadeData.type == 2 && FadeData.fade_sw)
		HardColorRegisterSet();
	
	FadeData.trans_stop = temp;
	
	return 1;
}

u8 PaletteFadeReq2(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 next_rgb)
{
	u8 temp;
	
	PlttCopy();
	temp = PaletteFadeReq(fade_bit, wait, start_evy, end_evy, next_rgb);
	return temp;
}

//=========================================================================
//	�p���b�g�A�j�� ���C��
//=========================================================================
void PaletteAnimeBeforeAfter(u8 trans_type, u32 *PalAnmBit)
{
	u8 i;
	PalAnmWorkData *paw;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		paw = &PalAnmWork[i];

		if(paw->pal_sw == 0 || paw->PalAnmDat->type != trans_type)
			continue;
		
		if(paw->TransValueLoop == paw->PalAnmDat->TransValueLoopDef)
		{
			PaletteAnimeEndCheck(paw);
			if(paw->pal_sw == 0)	//����EndCheck��Del���ꂽ���̂���
				continue;
		}

		if(paw->TransWait == 0)
		{
			PaletteAnimeSub(paw, PalAnmBit);
		}
		else
		{
			paw->TransWait--;
		}
		
		FadeCheck(paw, PalAnmBit);
	}
}

//----------------------------------------------------------
//	�p���b�g�A�j�� ���Ă���������ܰ��֓]��
//----------------------------------------------------------
static void PaletteAnimeSub(PalAnmWorkData *paw, u32 *PalAnmBit)
{
	u8 trans_value = 0;
	u16 now_pal;
	
	now_pal = paw->TransValueLoop * paw->PalAnmDat->TransValue;
	
	if(paw->PalAnmDat->type == PA_BEFORE)
	{
		while(trans_value < paw->PalAnmDat->TransValue)
		{
			PaletteWork[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			PaletteWorkTrans[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			trans_value++;
			paw->pal_no++;
			now_pal++;
		}
	}
	else	//PA_AFTER
	{
		while(trans_value < paw->PalAnmDat->TransValue)
		{
			PaletteWorkTrans[paw->pal_no]
						= paw->PalAnmDat->PalData[now_pal];
			trans_value++;
			paw->pal_no++;
			now_pal++;
		}
	}
	
	paw->pal_no = paw->pal_no_def;
	paw->TransWait = paw->PalAnmDat->TransWaitDef;
	
	//if(paw->TransValueLoop < paw->PalAnmDat->TransValueLoopDef)
		paw->TransValueLoop++;
	//else
	if(paw->TransValueLoop >= paw->PalAnmDat->TransValueLoopDef)
	{
		if(paw->LoopWait)
			paw->LoopWait--;
		paw->TransValueLoop = 0;
	}
	
	*PalAnmBit |= GET_PALNO_BIT(paw->pal_no_def);
//	BIT_SET(*PalAnmBit, paw->pal_no_def >> 4);	//�ύX������گĂ��ޯĂ��
}

//----------------------------------------------------------
//	̪��ނ���گı�҂������ɓ����Ƃ��̉����Z�␳
//----------------------------------------------------------
static void FadeCheck(PalAnmWorkData *paw, u32 *PalAnmBit)
{
	u8 i;
	u16 now_pal;
	
	if(FadeData.fade_sw == 0 
		|| ((GET_PALNO_BIT(paw->pal_no_def) & FadeData.fade_bit) == 0))
	{
		return;
	}
	
	if(paw->PalAnmDat->type == PA_BEFORE)
	{
		if(FadeData.wait == FadeData.wait_def)
			return;		//̪��ނŏ���Ɍ��F�����̂�OK
		
		//̪��ނ����ĂŎ��s����Ȃ��̂ł����ł��
		SoftFade(paw->pal_no_def, paw->PalAnmDat->TransValue,
				FadeData.now_evy, FadeData.next_rgb);
	}
	else	//PA_AFTER
	{
		if(FadeData.wait > 0)
			return;		//̪��ނ����s����Ȃ��̂Ō��F����Ȃ�
		
		if(paw->TransWait == paw->PalAnmDat->TransWaitDef)
			return;		//�ް����]�����ꂽ�̂�OK
		
		//̪��ނŌ��F����Ă��܂��Ă���̂œ]�����Ȃ���
		now_pal = paw->TransValueLoop * paw->PalAnmDat->TransValue;
		for(i = 0; i < paw->PalAnmDat->TransValue; i++)
		{
			PaletteWorkTrans[paw->pal_no_def+i] = paw->PalAnmDat->PalData[now_pal+i];
			//now_pal++;
		}
	}
}

//----------------------------------------------------------
//	�S�Ă�ٰ�ߏ������I�������̏���
//----------------------------------------------------------
static void PaletteAnimeEndCheck(PalAnmWorkData *paw)
{
	if(paw->LoopWait == 0)
	{
		switch(paw->PalAnmDat->PalAnmSeq)
		{
			case PA_LOOP:
				paw->TransValueLoop = 0;
				paw->TransWait = paw->PalAnmDat->TransWaitDef;
				paw->LoopWait = paw->PalAnmDat->LoopWaitDef;
				paw->pal_no = paw->pal_no_def;
				break;
			case PA_OUFUKU:
			case PA_END:
				DelPalAnm(paw->PalAnmDat->id_no);
				break;
			default:
		}
	}
	else
	{
		paw->LoopWait--;
	}
}
//----------------------------------------------------------
//	�w�肵��ID�̃p���b�g�A�j�����폜
//----------------------------------------------------------
void DelPalAnm(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	PalAnmInitWork(i);
}
//----------------------------------------------------------
//	�p���b�g�A�j���P��������
//----------------------------------------------------------
void PalAnmInitWork(u8 pal_anm_no)
{
	PalAnmWork[pal_anm_no].PalAnmDat = (PalAnmData *)&DmmyPalAnmDat;
	PalAnmWork[pal_anm_no].pal_sw = 0;
	PalAnmWork[pal_anm_no].pal_no_def = 0;
	PalAnmWork[pal_anm_no].pal_no = 0;
	PalAnmWork[pal_anm_no].TransValueLoop = 0;
	PalAnmWork[pal_anm_no].pause = 0;
	PalAnmWork[pal_anm_no].TransWait = 0;
	PalAnmWork[pal_anm_no].LoopWait = 0;
}
//----------------------------------------------------------
//	̪���ظ���ܰ�������
//----------------------------------------------------------
void FadeWorkInit(void)
{
	FadeData.fade_bit = 0;
	FadeData.wait_def = 0;
	FadeData.wait = 0;
	FadeData.now_evy = 0;
	FadeData.end_evy = 0;
	FadeData.next_rgb = 0;
	FadeData.fade_sw = 0;
	FadeData.direction = 0;
	FadeData.trans_stop = 0;
	FadeData.reset_flg = 0;
	FadeData.hard_end = 0;
	FadeData.fade_end = 0;
	FadeData.end_wait = 0;
	FadeData.bg_obj = 0;
	FadeData.fade_value = 2;
}
//----------------------------------------------------------
//	�w�肵��ID�̃p���b�g�A�j�����~�߂�
// �o�^����Ă���PalAnmWork�̔z��ԍ����������Ă���Ȃ璼�ڂ���������������
//----------------------------------------------------------
void PalAnmPause(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	PalAnmWork[i].pause = 1;
}
//----------------------------------------------------------
//	�w�肵��ID��Pause�Ŏ~�߂Ă�����گı�҂𓮂���
// �o�^����Ă���PalAnmWork�̔z��ԍ����������Ă���Ȃ璼�ڂ���������������
//----------------------------------------------------------
void PalAnmMove(u16 id_no)
{
	u8 i;
	
	if((i = PalAnmGetWorkNumber(id_no)) == PAL_ANM_MAX)
		return;		//error
	
	PalAnmWork[i].pause = 0;
}
//----------------------------------------------------------
//	ID����PalAnmWork�̔z��ԍ����o��
//----------------------------------------------------------
u8 PalAnmGetWorkNumber(u16 id_no)
{
	u8 i;
	
	for(i = 0; i < PAL_ANM_MAX; i++)
	{
		if(PalAnmWork[i].PalAnmDat->id_no == id_no)
			return i;
	}
	return PAL_ANM_MAX;	//error
}


//----------------------------------------------------------
//	�\�t�g�t�F�[�h�C���A�A�E�g(��گı��ٰ�ݗp)
// �߂�l: 0=̪���ظ��Ă��������ĂȂ��A����ظ��Ă��I������
//         1=̪��ގ��s��
//         2=̪���ظ��Ă͂������Ă��邪���Ē��Ȃ̂ŏ����͂��Ȃ�����
//----------------------------------------------------------
#include "softfade.h"
u8 ColorAddSub(void)
{
	u16 offset2;
	u16 next_rgb;
	u32 fade_bit;
	s8  evy;
	
	if(FadeData.fade_sw == 0)
		return 0;
	if(FadeEndWaitCheck())
		return FadeData.fade_sw;
	
	if(FadeData.bg_obj == 0){
		if(FadeData.wait < FadeData.wait_def)
		{
			FadeData.wait++;
			return 2;
		}
		else
			FadeData.wait = 0;
	}

	offset2 = 0;
	next_rgb = FadeData.next_rgb;

	if(FadeData.bg_obj == 0)
		fade_bit = FadeData.fade_bit & 0xffff;
	else{
		fade_bit = FadeData.fade_bit >> 16;
		offset2 = 16*16;
	}
	while(fade_bit)
	{
		if(fade_bit & 1)
			SoftFade(offset2, 16, FadeData.now_evy, FadeData.next_rgb);
		fade_bit >>= 1;
		offset2 += 16;
	}
	FadeData.bg_obj ^= 1;
	if(FadeData.bg_obj)
		return FadeData.fade_sw;

	if(FadeData.now_evy == FadeData.end_evy)
	{
		FadeData.fade_bit = 0;
		//FadeData.fade_sw = 0;
		FadeData.fade_end = 1;
	}
	else if(FadeData.direction == 0)
	{
		evy = FadeData.now_evy;	//31�𒴂���Ƶ��ް�۰���N�����̂�
		evy += FadeData.fade_value;
		if(evy > FadeData.end_evy)
			evy = FadeData.end_evy;
		FadeData.now_evy = evy;
	}
	else
	{
		evy = FadeData.now_evy;	//ϲŽ����邽��
		evy -= FadeData.fade_value;
		if(evy < FadeData.end_evy)
			evy = FadeData.end_evy;
		FadeData.now_evy = evy;
	}
	return FadeData.fade_sw;
}







//=========================================================================
//	�J���[���]						2001.06.26(��)
// ����:�@bit = �J���[���]����Ώ���گ�   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorReversal(u32 bit)
{
	u16 i = 0;
	u8 j;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++)
				PaletteWorkTrans[i + j] ^= 0xffff;
		}
		bit >>= 1;
		i += 16;
	}
}

//=========================================================================
//	�J���[���Z						2001.06.29
// ����:�@bit = �J���[���Z����Ώ���گ�   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorRandomPlus(u32 bit,s8 red,s8 green, s8 blue)
{
	u16 i = 0;
	u8 j;
	PlttData *p;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++){
				p = (PlttData*)&(PaletteWorkTrans[i + j]);
				p->Red+=red;
				p->Green+=green;
				p->Blue+=blue;
			}
		}
		bit >>= 1;
		i += 16;
	}
}

//=========================================================================
//	�J���[���Z�̌�n��					2001.06.29
// ����:�@bit = �߂��Ώ���گ�   0bit:BGPalette0   16bit:ObjPalette0
//=========================================================================
void ColorRandomPlusEnd(u32 bit)
{
	u16 i = 0;
	u8 j;
	
	while(bit)
	{
		if(bit & 1)
		{
			for(j = 0; j < 16; j++)
				PaletteWorkTrans[i + j] = PaletteWork[i+j];
		}
		bit >>= 1;
		i += 16;
	}
}


//=========================================================================
//	���Ɣ��݂̂ɗp�r�����ڂ��������t�F�[�h�֐�
// fade_type = �ǂ�̪��ނ��s����
//			   W_to_N:����ɰ��  N_to_W:ɰ�ف���  B_to_N:����ɰ��  N_to_B:ɰ�ف���
//=========================================================================
void LightFadeReq(u8 fade_type)
{
	FadeData.fade_value = 2;
	LightFadeCommon(fade_type);
}

//----------------------------------------------------------
//	LightFadeReq, LightFadeReqSync���ʏ���
//----------------------------------------------------------
static void LightFadeCommon(u8 fade_type)
{
	FadeData.now_evy = 31;
	FadeData.wait_def = fade_type;
	FadeData.fade_sw = 1;
	FadeData.type = 1;
	
	if(fade_type == B_to_N)
		CpuArrayClear(0, PaletteWorkTrans, 16)
	if(fade_type == W_to_N)
		CpuArrayClear(0x7fff, PaletteWorkTrans, 16);
	PaletteAnime();		//ظ��Ă��Ă����ɔ��f������悤�ύX
}

//----------------------------------------------------------
//	�\�t�g�t�F�[�h�C���A�A�E�g(��گı��ٰ�ݗp)
// �߂�l: 0=̪���ظ��Ă��������ĂȂ��A����ظ��Ă��I������
//         1=̪��ގ��s��
//----------------------------------------------------------

u8 LightColorAddSub(void)
{
	u16 i;
	u16 start_pal, end_pal;
	s8 red,green,blue,t_red,t_green,t_blue;
	
	if(FadeData.fade_sw == 0)
		return 0;
	if(FadeEndWaitCheck())
		return FadeData.fade_sw;

	if(FadeData.bg_obj){
		start_pal = 0x100;
		end_pal = 0x200;
	}else{
		start_pal = 0;
		end_pal = 0x100;
	}

	switch(FadeData.wait_def)
	{
		case W_to_N:
			for(i = start_pal; i < end_pal; i++)
			{
				red = ((PlttData*)&PaletteWork[i])->Red;
				green = ((PlttData*)&PaletteWork[i])->Green;
				blue = ((PlttData*)&PaletteWork[i])->Blue;
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red-2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green-2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue-2;
				if(t_red < red)
					t_red = red;
				if(t_green < green)
					t_green = green;
				if(t_blue < blue)
					t_blue = blue;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case N_to_W:
			for(i = start_pal; i < end_pal; i++)
			{
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red+2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green+2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue+2;
				if(t_red > 31)
					t_red = 31;
				if(t_green > 31)
					t_green = 31;
				if(t_blue > 31)
					t_blue = 31;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case B_to_N:
			for(i = start_pal; i < end_pal; i++)
			{
				red = ((PlttData*)&PaletteWork[i])->Red;
				green = ((PlttData*)&PaletteWork[i])->Green;
				blue = ((PlttData*)&PaletteWork[i])->Blue;
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red+2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green+2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue+2;
				if(t_red > red)
					t_red = red;
				if(t_green > green)
					t_green = green;
				if(t_blue > blue)
					t_blue = blue;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
		case N_to_B:
			for(i = start_pal; i < end_pal; i++)
			{
				t_red = ((PlttData*)&PaletteWorkTrans[i])->Red-2;
				t_green = ((PlttData*)&PaletteWorkTrans[i])->Green-2;
				t_blue = ((PlttData*)&PaletteWorkTrans[i])->Blue-2;
				if(t_red < 0)
					t_red = 0;
				if(t_green < 0)
					t_green = 0;
				if(t_blue < 0)
					t_blue = 0;
				PaletteWorkTrans[i] = t_red | (t_green<<5) | (t_blue<<10);
			}
			break;
	}
	
	FadeData.bg_obj ^= 1;
	if(FadeData.bg_obj)
		return FadeData.fade_sw;

	if(FadeData.now_evy - FadeData.fade_value < 0)
		FadeData.now_evy = 0;
	else
		FadeData.now_evy -= FadeData.fade_value;
	if(FadeData.now_evy == 0)
	{
		switch(FadeData.wait_def)
		{	//�����؂�̂Ẳe���Ŋ��S�ɂ��̐F�ɂ͂Ȃ�Ȃ��̂�
			case W_to_N:
			case B_to_N:
				CpuArrayCopy(PaletteWork, PaletteWorkTrans, 32);
				break;
			case N_to_W:
				CpuArrayClear(0xffffffff, PaletteWorkTrans, 32);
				break;
			case N_to_B:
				CpuArrayClear(0, PaletteWorkTrans, 32);
				break;
		}
		FadeData.type = 0;
		//FadeData.fade_sw = 0;
		FadeData.fade_end = 1;
	}

	return FadeData.fade_sw;
}








//----------------------------------------------------------
//	�n�[�h�ɂ��p���b�g�����Z���N�G�X�g
//
// fade_bit : �����Z�̑Ώۂɂ���BG,OBJ���w��(BLDCNTڼ޽��̑�1�Ώ��߸�قɐݒ肷���ޯ�)
//				6,7bit:���x�ύX���߁A�޳��ޯ�(10:UP	 11:DOWN)
//				5bit:BD(�ޯ���׳���), 4bit:OBJ, 3:BG3, 2:BG2, 1:BG1, 0:BG0
//
// wait : �l��傫������Ƃ������̪��ޱ�āA�݂��܂� (MAX:63)
// start_evy : �ŏ��̐F�̔Z�x���w�肵�܂�(0�`16)
// 			   0(���̐F)�`2,3..(���ԐF)�`16(���A�������͔�)
// end_evy : �ŏI�I�ȐF�̔Z�x���w�肵�܂��B�����̒l�́��Ɠ����ł�
// reset_flg : ̪��ޏI������ڼ޽���̏����������邩(0:���Ȃ�  1:����)
//----------------------------------------------------------
void HardFadeReq(u8 fade_bit, u8 wait, u8 start_evy, u8 end_evy, u8 reset_flg)
{
	FadeData.fade_bit = fade_bit;
	FadeData.wait = wait;			//�����ظ��Ă������u�ԂɎ��s
	FadeData.wait_def = wait;
	FadeData.now_evy = start_evy;
	FadeData.end_evy = end_evy;
	FadeData.fade_sw = 1;
	FadeData.type = 2;				//RegisterFade
	FadeData.reset_flg = reset_flg;
	FadeData.hard_end = 0;
	if(start_evy < end_evy)
		FadeData.direction = 0;
	else
		FadeData.direction = 1;
}

//----------------------------------------------------------
//	���W�X�^�[�t�F�[�h�C���A�A�E�g(��گı��ٰ�ݗp)
// �߂�l: 0=̪���ظ��Ă��������ĂȂ��A����ظ��Ă��I������
//         1=̪��ގ��s��
//         2=̪���ظ��Ă͂������Ă��邪���Ē��Ȃ̂ŏ����͂��Ȃ�����
//----------------------------------------------------------
static u8 HardColorCalc(void)
{
	s8  evy;
	
	if(FadeData.fade_sw == 0)
		return 0;

	if(FadeData.wait < FadeData.wait_def)
	{
		FadeData.wait++;
		return 2;
	}
	else
		FadeData.wait = 0;

	if(FadeData.direction == 0){
		FadeData.now_evy++;
		if(FadeData.now_evy > FadeData.end_evy){
			FadeData.hard_end++;
			FadeData.now_evy--;
		}
	}
	else
	{
		evy = FadeData.now_evy;	//ϲŽ����邽��
		FadeData.now_evy--;
		evy--;
		if(evy < FadeData.end_evy){
			FadeData.hard_end++;
			FadeData.now_evy++;
		}
	}
	
	if(FadeData.hard_end){
		//FadeData.fade_sw = 0;		HardColorRegisterSet�֐��̒��ŗ��Ƃ��̂�
		//FadeData.fade_bit = 0;
		if(FadeData.reset_flg){
			FadeData.fade_bit = 0;
			FadeData.now_evy = 0;
		}
		FadeData.reset_flg = 0;
	}
	return FadeData.fade_sw;
}

static void HardColorRegisterSet(void)
{
	RegisterSet(OFFSET_REG_BLDCNT , FadeData.fade_bit);
	RegisterSet(OFFSET_REG_BLDY , FadeData.now_evy);
	if(FadeData.hard_end){
		FadeData.hard_end = 0;
		FadeData.type = 0;
		FadeData.fade_bit = 0;
		FadeData.now_evy = 0;
		FadeData.fade_sw = 0;
	}
}





//=========================================================================
//	̪��ޏI����A���Sync���Ă�����
//	�߂�l: 0=�܂�̪��ޏI�����ĂȂ�		1=���Ē�
//=========================================================================
static u8 FadeEndWaitCheck(void)
{
	if(FadeData.fade_end){
		if(FadeData.end_wait == FADE_END_WAIT){
			FadeData.fade_sw = 0;
			FadeData.fade_end = 0;
			FadeData.end_wait = 0;
		}else
			FadeData.end_wait++;
		return 1;
	}
	return 0;
}




//=========================================================================
//	�w��r�b�g�̃J���[�p���b�g���Ă΂ꂽ�u�ԂɎw��F�A�w��Z�x�ɕύX����
//
// fade_bit : �p���b�g���w��i�e�r�b�g���p���b�g�ԍ��ɑΉ�
//			  �r�b�g0 = BG��0�p���b�g�A Bit16 = OBJ��0�p���b�g)
// start_evy : �ύX��̐F�̔Z�x���w�肵�܂�(0�`16)
// 			   0(���̐F)�`2,3..(���ԐF)�`16(�w�肵���F)
// next_rgb : �ύX��̐F���w��
//=========================================================================
void ColorConceChange(u32 fade_bit, u8 evy, u16 next_rgb)
{
	u16 offset = 0;
	
	while(fade_bit){
		if(fade_bit & 1)
			SoftFade(offset, 16, evy, next_rgb);
		fade_bit >>= 1;
		offset += 16;
	}
}



//=========================================================================
//	�w��r�b�g�̃J���[�p���b�g���Ă΂ꂽ�u�ԂɎw��F�A�w��Z�x�ɕύX����
// ���w�肳��Ă��Ȃ��ޯĂ���گĂ͌��̐F�ɖ߂�܂��B
// fade_bit : �p���b�g���w��i�e�r�b�g���p���b�g�ԍ��ɑΉ�
//			  �r�b�g0 = BG��0�p���b�g�A Bit16 = OBJ��0�p���b�g)
// start_evy : �ύX��̐F�̔Z�x���w�肵�܂�(0�`16)
// 			   0(���̐F)�`2,3..(���ԐF)�`16(�w�肵���F)
// next_rgb : �ύX��̐F���w��
//=========================================================================
void ColorConceChange2(u32 fade_bit, u8 evy, u16 next_rgb)
{
	DIV_DMACOPY(3, PaletteWork, PaletteWorkTrans, 0x400, 32);
	ColorConceChange(fade_bit, evy, next_rgb);
}

//===============================================
// �P�x�v�Z�}�N��
//===============================================
#define RGBtoY(r,g,b)	(((r)*76 + (g)*151 + (b)*29) >> 8)

//--------------------------------------------------------------------------
/**
 * �O���[�X�P�[��
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void PalGrayScale(u16 *pal, u16 pal_size)
{
	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}
//--------------------------------------------------------------------------
/**
 * 2bit�J���[��
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void Pal2BitFilter(u16 *pal, u16 pal_size)
{
	static const u8  col_tbl[32] = {
		 0, 0, 0, 0, 0, 5, 5, 5, 5, 5,
		11,11,11,11,11,16,16,16,16,16,
		21,21,21,21,21,27,27,27,27,27,
		31,31,
	};

	int i, r, g, b;
	u32 c;

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		c = RGBtoY(r,g,b);

		if(c > 31){
			c = 31;
		}
		c = col_tbl[c];
		*pal = (u16)((c<<10)|(c<<5)|c);
		pal++;
	}
}
//--------------------------------------------------------------------------
/**
 * �Z�s�A�J���[
 *
 * @param   pal		
 * @param   pal_size		
 *
 * @retval  none		
 */
//--------------------------------------------------------------------------
void PalSepiaFilter(u16 *pal, u16 pal_size)
{
	int i, r, g, b, y;

#define R_FIL(x)	( ((u16)((x)*307)>>8) )
#define G_FIL(x)	( ((u16)((x)*256)>>8) )
#define B_FIL(x)	( ((u16)((x)*240)>>8) )

	for(i = 0; i < pal_size; i++){
		r = ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		y = RGBtoY(r,g,b);

		r = R_FIL(y);
		g = G_FIL(y);
		b = B_FIL(y);

		if(r > 31){ r = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}


#undef R_FIL
#undef G_FIL
#undef B_FIL
}

// -------------------------------------------------------------------------
/**
 * �J���[�ύX
 *
 * @param	pal			�ύX����p���b�g�̃A�h���X
 * @param	pal_size	���F�ύX���邩�H
 * @paran	rp			��
 * @paran	gp			��
 * @paran	bp			��
 *
 * @return	none
 */
// -------------------------------------------------------------------------
void PalColorFilter(u16 *pal, u16 pal_size, u16 rp, u16 gp, u16 bp)
{
	int i, r, g, b, y;

#define C_FIL(y,c)	((u16)((y)*(c))>>8)

	for(i = 0; i < pal_size; i++){
		r =  ((*pal) & 0x1f);
		g = (((*pal) >> 5) & 0x1f);
		b = (((*pal) >> 10) & 0x1f);

		y = RGBtoY(r,g,b);

		r = C_FIL(y,rp);
		g = C_FIL(y,gp);
		b = C_FIL(y,bp);

		if (r > 31){ r = 31; }
		if (g > 31){ g = 31; }
		if (b > 31){ b = 31; }

		*pal = (u16)((b<<10)|(g<<5)|r);
		pal++;
	}

#undef C_FIL

}

/*====================================================================================*/
/*                                                                                    */
/*  �p���b�g�t�F�[�h���s����                                                          */
/*                                                                                    */
/*====================================================================================*/

static void ParallelFadeTask(u8 id);

enum {
	PFWORK_EVY,
	PFWORK_EVY_END,
	PFWORK_EVY_ADD,
	PFWORK_WAIT,
	PFWORK_COUNT,
	PFWORK_FADEBIT,
	PFWORK_FADEBIT_2ND,
	PFWORK_RGB,
	PFWORK_ID,
};

//------------------------------------------------------------------------------
/**
 * �قȂ�p���b�g�ɕ��s���ĕʁX�̃t�F�[�h��������i�^�X�N�Z�b�g�j
 *
 * @param   fade_bit		�Ώۃp���b�g�r�b�g
 * @param   wait			�E�F�C�g
 * @param   start_evy		�J�nevy
 * @param   end_evy			�I��evy
 * @param   rgb				�t�F�[�h�J���[
 * @param   pri				�^�X�N�v���C�I���e�B
 * @param   id				���ʂh�c�i�Ăяo�������Ǘ��B�^�X�N���ƂɈႤID��n���j
 *
 * @retval  u8			�o�^�����^�X�N�̂h�c
 *
 * fade_bit �` rgb �܂ł̃p�����[�^�́APaletteFadeReq �Ɠ��l�B
 *
 */
//------------------------------------------------------------------------------
void ParallelFadeSet(u32 fade_bit, s8 wait, u8 start_evy, u8 end_evy, u16 rgb, u8 pri, u8 id)
{
	u8 no = AddTask(ParallelFadeTask, pri);

	TaskTable[no].work[PFWORK_EVY] = start_evy;
	TaskTable[no].work[PFWORK_EVY_END] = end_evy;

	if(wait >= 0){
		TaskTable[no].work[PFWORK_WAIT] = wait;
		TaskTable[no].work[PFWORK_EVY_ADD] = 1;
	}else{
		TaskTable[no].work[PFWORK_WAIT] = 0;
		TaskTable[no].work[PFWORK_EVY_ADD] =  -(wait) + 1;
	}

	if(end_evy < start_evy){
		TaskTable[no].work[PFWORK_EVY_ADD] *= -1;
	}

	TaskStoreAdrs(no, PFWORK_FADEBIT, (void*)fade_bit);
	TaskTable[no].work[PFWORK_RGB] = (s16)rgb;
	TaskTable[no].work[PFWORK_ID] = id;

	TaskTable[no].TaskAdrs(no);
}

//------------------------------------------------------------------------------
/**
 * ���s�t�F�[�h�I���҂�
 *
 * @param   id			���ʂh�c�iParallelFadeSet �̈����Ɠ������́j
 *
 * @retval  BOOL		TRUE:�p�����^FALSE:�I��
 */
//------------------------------------------------------------------------------
BOOL ParallelFadeWait(u8 id)
{
	int i;
	for(i = 0; i < TASK_MAX; i++){
		if(	(TaskTable[i].occ == 1)
		&&	(TaskTable[i].TaskAdrs == ParallelFadeTask)
		&&	(TaskTable[i].work[PFWORK_ID] == id)
		){
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------------------
/**
 * ���s�^�X�N�t�F�[�h�S�I��
 *
 * @param   none		
 *
 * @retval  none		
 */
//------------------------------------------------------------------------------
void ParallelFadeStopAll(void)
{
	u8 no = CheckTaskNo(ParallelFadeTask);
	while(no != NOT_EXIST_TASK_ID){
		DelTask(no);
		no = CheckTaskNo(ParallelFadeTask);
	}
}
/**=====================================================================
 *
 * ���s�t�F�[�h���s�^�X�N
 *
 * @param   id		
 *
 * @retval  none		
 *
 *====================================================================*/
static void ParallelFadeTask(u8 id)
{
	s16 *wk;
	u32 fade_bit;

	wk = TaskTable[id].work;
	fade_bit = (u32)TaskTakeAdrs(id, PFWORK_FADEBIT);

	wk[PFWORK_COUNT]++;
	if( wk[PFWORK_COUNT] > wk[PFWORK_WAIT] ){
		wk[PFWORK_COUNT] = 0;

		ColorConceChange(fade_bit, wk[PFWORK_EVY], (u16)(wk[PFWORK_RGB]));
		if(wk[PFWORK_EVY] == wk[PFWORK_EVY_END]){
			DelTask(id);
			return;
		}

		wk[PFWORK_EVY] += wk[PFWORK_EVY_ADD];

		if(wk[PFWORK_EVY_ADD] >= 0){
			if(wk[PFWORK_EVY] >= wk[PFWORK_EVY_END]){
				wk[PFWORK_EVY] = wk[PFWORK_EVY_END];
			}
		}else{
			if(wk[PFWORK_EVY] <= wk[PFWORK_EVY_END]){
				wk[PFWORK_EVY] = wk[PFWORK_EVY_END];
			}
		}

	}

}



#endif
