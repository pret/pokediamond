//============================================================================================
/**
 * @file	poketch_act.c
 * @bfief	�|�P�b�`�p�A�N�^�[�Ǘ�
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"

#include "system\arc_util.h"
#include "poketch_act.h"


/*
typedef struct NNSG2dSVec2
{
    s16     x;        
    s16     y;
    
}NNSG2dSVec2;

typedef struct NNSG2dFVec2
{
    fx32     x;        
    fx32     y;
    
}NNSG2dFVec2;
*/

/*===================================================*/
/* �萔                                              */
/*===================================================*/
enum {
	ACT_DEFAULT_WORKSIZE = 18,
	ACT_DEFWORK_MAGICNUM_SIZE = 2,
	ACT_DEFWORK_MAGICNUM = 0x3594,
};


struct _PACT {
	const NNSG2dCellDataBank*  cellbank;
	const NNSG2dAnimBankData*  anmbank;

	NNSG2dCellAnimation        cellanm;

	struct _PACT* next;
	struct _PACT* prev;

	NNSG2dFVec2   pos;
	MtxFx22*      affine;
	MtxFx22       affine_body;

	union {
		struct {
			u16 oampri;
			u16 bgpri;
		};
		u32 pri;
	};

	u16           pal_offset;
	u8            vanish;
	u8            affine_flag;

	u16           char_offset;
	u8            h_flip;
	u8            v_flip;

	u16           rotate;
	u8            mosaic;

};

struct _PACTSYS {
	NNSG2dOamManagerInstance*    oamm;


	PACT**         act_stack;
	PACT*          act_top;
	PACT*          act;
	u16            act_max;
	u16            act_stack_p;

	GXOamAttr*     oam;

	u32    heap_type;
};

//==============================================================
// Prototype
//==============================================================
static void ActAllInit( PACT** stack, PACT* acts, u32 numact );
static void ActClear( PACT* act );
static PACT* ActPop( PACTSYS* actsys );
static void ActPush( PACTSYS* actsys, PACT* act );
static void ActChain( PACTSYS* actsys, PACT *act );
static void ActUnchain( PACTSYS* actsys, PACT* act );




//------------------------------------------------------------------
/**
 * �V�X�e��������
 *
 * @param   oamm		�V�X�e�����g��OAM�Ȱ�ެ
 * @param   heap		���[�N�̈�m�ۂɎg���ėǂ��q�[�v���
 *
 * @retval  PACTSYS*	�V�X�e�����[�N�|�C���^
 */
//------------------------------------------------------------------
PACTSYS* PACT_SysCreate( NNSG2dOamManagerInstance* oamm, u32 heap)
{
	PACTSYS* actsys;
	BOOL  succeed = FALSE;

	do {
		actsys = sys_AllocMemory( heap, sizeof(PACTSYS) );
		if( actsys == NULL ){ break; }

		actsys->oam = NULL;
		actsys->act = NULL;
		actsys->act_stack = NULL;

		actsys->oamm = oamm;
		actsys->heap_type = heap;


		actsys->act_max = NNS_G2dGetOamManagerOamCapacity( oamm );

		actsys->oam = sys_AllocMemory( heap, sizeof(GXOamAttr) * actsys->act_max );
		if(actsys->oam == NULL){ break; }

		actsys->act = sys_AllocMemory( heap, sizeof(PACT) * actsys->act_max );
		if( actsys->act == NULL ){ break; }

		actsys->act_stack = sys_AllocMemory( heap, sizeof(PACT*) * actsys->act_max );
		if( actsys->act_stack == NULL ){ break; }

		ActAllInit( actsys->act_stack, actsys->act, actsys->act_max );
		actsys->act_stack_p = 0;
		actsys->act_top = NULL;


		succeed = TRUE;

	}while(0);

	if( succeed == FALSE )
	{
		OS_Printf("poketch actsys initialize failed\n");
		if(actsys != NULL)
		{
			if( actsys->oam != NULL ){
				sys_FreeMemory( heap, actsys->oam );
			}
			if( actsys->act != NULL ){
				sys_FreeMemory( heap, actsys->act );
			}
			if( actsys->act_stack != NULL ){
				sys_FreeMemory( heap, actsys->act_stack );
			}

			sys_FreeMemory( heap, actsys );

		}
		return NULL;
	}

	return actsys;
}

//------------------------------------------------------------------
/**
 * �V�X�e���폜
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void PACT_SysDelete( PACTSYS* actsys )
{
	if( actsys )
	{
		if( actsys->oam ){ sys_FreeMemoryEz( actsys->oam ); }
		if( actsys->act) {sys_FreeMemoryEz( actsys->act ); }
		if( actsys->act_stack ){ sys_FreeMemoryEz( actsys->act_stack ); }
		sys_FreeMemoryEz( actsys );
	}
}
//------------------------------------------------------------------
/**
 * �`��i���C�����[�v�̍Ō�Ɂj
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void PACT_SysMain( PACTSYS* actsys )
{
	if( actsys->act_stack_p )
	{
		PACT*       p = actsys->act_top;
		GXOamAttr*  oam_p = actsys->oam;
		s32         oam_max = actsys->act_max;
		u32   use;

		while( p != NULL )
		{
			NNS_G2dTickCellAnimation( &p->cellanm, FX32_ONE*2 );

			if( p->vanish == 0 )
			{
				const NNSG2dSRTControl*  pSRT = &(p->cellanm.srtCtrl);
				NNSG2dFVec2  pos;

				// ���s�ړ�
				pos.x = p->pos.x + (fx32)(pSRT->srtData.trans.x << FX32_SHIFT);
				pos.y = p->pos.y + (fx32)(pSRT->srtData.trans.y << FX32_SHIFT);

				// ��]�E�g�k�Ȃ�
				if( p->affine_flag == FALSE )
				{
					use = NNS_G2dMakeCellToOams (
						oam_p, oam_max,
						NNS_G2dGetCellAnimationCurrentCell( &p->cellanm ),
						NULL,
						&(pos),
						0,
						FALSE
					);

				}
				// ��]�E�g�k����
				else
				{
					u16 affineIndex;

					// ��]
					MTX_Identity22( p->affine );
					if( pSRT->srtData.SRT_EnableFlag & NNS_G2D_AFFINEENABLE_ROTATE )
					{
						u16 rotate = pSRT->srtData.rotZ + p->rotate;
						MTX_Rot22( p->affine, FX_SinIdx(rotate), FX_CosIdx(rotate) );
					}
					else if( p->rotate )
					{
						MTX_Rot22( p->affine, FX_SinIdx(p->rotate), FX_CosIdx(p->rotate) );
					}

					// �g�k
					if( pSRT->srtData.SRT_EnableFlag & NNS_G2D_AFFINEENABLE_SCALE )
					{
						MTX_ScaleApply22( p->affine, p->affine, FX_Inv(pSRT->srtData.scale.x), FX_Inv(pSRT->srtData.scale.y) );
					}

					affineIndex = NNS_G2dEntryOamManagerAffine( actsys->oamm, p->affine );

					use = NNS_G2dMakeCellToOams (
						oam_p, oam_max,
						NNS_G2dGetCellAnimationCurrentCell( &p->cellanm ),
						p->affine,
						&(pos),
						affineIndex,
						TRUE
					);

				}

				oam_max -= use;
				while(use--)
				{
					oam_p->priority = p->bgpri;
					oam_p->cParam += p->pal_offset;
					oam_p->charNo += p->char_offset;
					oam_p->flipH ^= p->h_flip;
					oam_p->flipV ^= p->v_flip;
					oam_p->mosaic ^= p->mosaic;
					oam_p++;
				}

			}

			p = p->next;
		}

		if( oam_p > actsys->oam )
		{
			NNS_G2dEntryOamManagerOam( actsys->oamm, actsys->oam, oam_p - actsys->oam );
		}
	}
}

//------------------------------------------------------------------
/**
 * �A�N�^�[�ǉ�
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 * @param   param		�A�N�^�[�쐬�p�����[�^
 *
 * @retval  PACT*		�A�N�^�[�|�C���^
 */
//------------------------------------------------------------------
PACT*  PACT_Add( PACTSYS* actsys, const PACT_ADD_PARAM* param,  const PACT_CLANM_PACK* pack )
{
	PACT* act = ActPop( actsys );
	if( act != NULL )
	{
		// �����N���X�g�ɒǉ�
		act->bgpri = param->bgpri;
		act->oampri = param->oampri;
		ActChain( actsys, act );

		// �Z���o���N�A�A�j���o���N������
		act->cellbank = pack->cellbank;
		act->anmbank = pack->anmbank;

		// �A�j����Ԃ�������
		NNS_G2dInitCellAnimation(
			&(act->cellanm),
			NNS_G2dGetAnimSequenceByIdx( act->anmbank, param->anmseq ),
			act->cellbank
		);

		act->pos = param->pos;
		act->pal_offset = 0;
		act->char_offset = 0;
		act->h_flip = ((param->flip & PACT_FLIP_H) != 0);
		act->v_flip = ((param->flip & PACT_FLIP_V) != 0);;
		act->mosaic = FALSE;
		act->rotate = 0;


		act->affine = &(act->affine_body);
		act->affine_flag = param->affine_flag;
		act->vanish = 0;


	}
	return act;
}


//------------------------------------------------------------------
/**
 * �A�N�^�[�폜
 *
 * @param   actsys		
 * @param   act		
 *
 */
//------------------------------------------------------------------
void PACT_Del( PACTSYS* actsys, PACT* act )
{
	// �����N���X�g����O��
	ActUnchain( actsys, act );
	ActPush( actsys, act );
}

//------------------------------------------------------------------
/**
 * �A�N�^�[����F�A�j���V�[�P���X�ύX
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   anmseq		�A�j���V�[�P���X�i���o�[
 *
 */
//------------------------------------------------------------------
void PACT_ChangeAnmSeq( PACT* act, u32 anmseq )
{
//	const NNSG2dAnimSequenceData* anmSeqDat = NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq );
//	NNSG2dAnimController*  anmCtrl = NNS_G2dGetCellAnimationAnimCtrl( &(act->cellanm) );

	NNS_G2dInitCellAnimation(
		&(act->cellanm),
		NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq ),
		act->cellbank
	);
/*
	if( anmSeqDat != NNS_G2dGetAnimCtrlCurrentAnimSequence( anmCtrl ) )
	{
		NNS_G2dSetCellAnimationSequence(
			&(act->cellanm),
			NNS_G2dGetAnimSequenceByIdx( act->anmbank, anmseq )
		);

		NNS_G2dResetAnimCtrlState( anmCtrl );

		NNS_G2dStartAnimCtrl( anmCtrl );
	}
*/
}
//------------------------------------------------------------------
/**
 * �A�N�^�[����F�A�j���Đ����I�����Ă��邩�`�F�b�N
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   anmseq		�A�j���V�[�P���X�i���o�[
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL PACT_CheckAnmEnd( PACT* act )
{
	NNSG2dAnimController*  anmCtrl = NNS_G2dGetCellAnimationAnimCtrl( &(act->cellanm) );
	return NNS_G2dIsAnimCtrlActive( anmCtrl ) == FALSE;
}

//------------------------------------------------------------------
/**
 * �A�N�^�[����F������ʒu����w�蕪�����ړ�
 *
 * @param   act		�A�N�^�[�|�C���^
 * @param   x		�ړ���X
 * @param   y		�ړ���Y
 *
 */
//------------------------------------------------------------------
void PACT_MovePos( PACT* act, fx32 x, fx32 y )
{
	act->pos.x += x;
	act->pos.y += y;
}

//------------------------------------------------------------------
/**
 * �A�N�^�[����F�w��ʒu�ֈړ�
 *
 * @param   act		�A�N�^�[�|�C���^
 * @param   x		�ʒu�w��w
 * @param   y		�ʒu�w��x
 *
 */
//------------------------------------------------------------------
void PACT_SetPos( PACT* act, fx32 x, fx32 y )
{
	act->pos.x = x;
	act->pos.y = y;
}

//------------------------------------------------------------------
/**
 * �A�N�^�[����F���݈ʒu���擾
 *
 * @param   act		�A�N�^�[�|�C���^
 * @param   x		�w���W�󂯎��ϐ��|�C���^
 * @param   y		�x���W�󂯎��ϐ��|�C���^
 *
 */
//------------------------------------------------------------------
void PACT_GetPos( const PACT* act, fx32* x, fx32* y )
{
	*x = act->pos.x;
	*y = act->pos.y;
}

//------------------------------------------------------------------
/**
 * �\���I�t�t���O���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   vanish		�\���I�t�t���O
 *
 */
//------------------------------------------------------------------
void PACT_SetVanish( PACT* act, BOOL vanish )
{
	act->vanish = vanish;
}

//------------------------------------------------------------------
/**
 * BG�v���C�I���e�B���Z�b�g
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 * @param   bgpri		
 *
 */
//------------------------------------------------------------------
void PACT_SetBGPri( PACTSYS* actsys, PACT* act, u32 bgpri )
{
	act->bgpri = bgpri;
}


//------------------------------------------------------------------
/**
 * OAM�v���C�I���e�B���Z�b�g
 *
 * @param   actsys		
 * @param   oampri		
 *
 */
//------------------------------------------------------------------
void PACT_SetOamPri( PACTSYS* actsys, PACT* act, u32 oampri )
{
	ActUnchain( actsys, act );
	act->oampri = oampri;
	ActChain( actsys, act );
}


//------------------------------------------------------------------
/**
 * �p���b�g�I�t�Z�b�g�l���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   offset		�I�t�Z�b�g�l
 *
 */
//------------------------------------------------------------------
void PACT_SetPalOffset( PACT* act, u32 offset )
{
	act->pal_offset = offset;
}
//------------------------------------------------------------------
/**
 * �L�����I�t�Z�b�g�l���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   offset		�I�t�Z�b�g�l
 *
 */
//------------------------------------------------------------------
void PACT_SetCharOffset( PACT* act, u32 offset )
{
	act->char_offset = offset;
}
//------------------------------------------------------------------
/**
 * ���]�t���O���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   flip		���]�t���O
 *
 */
//------------------------------------------------------------------
void PACT_SetFlip( PACT* act, PACT_FLIP flip )
{
	act->h_flip = ((flip & PACT_FLIP_H) != 0);
	act->v_flip = ((flip & PACT_FLIP_V) != 0);
}
//------------------------------------------------------------------
/**
 * ���U�C�N�t���O���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   flag		���U�C�N�t���O
 *
 */
//------------------------------------------------------------------
void PACT_SetMosaic( PACT* act, BOOL flag )
{
	act->mosaic = flag;
}

//------------------------------------------------------------------
/**
 * ��]�p�x���Z�b�g
 *
 * @param   act			�A�N�^�[�|�C���^
 * @param   rotate		��]�p�x�i0�`65535�j
 *
 */
//------------------------------------------------------------------
void PACT_SetRotate( PACT* act, u16 rotate )
{
	act->rotate = rotate;
}



//------------------------------------------------------------------
/**
 * �Z���E�A�j���f�[�^���\���̂ɓǂݍ���
 *
 * @param   pack		�Z���E�A�j���f�[�^�ǂݍ��ݐ�\����
 * @param	arcFileIdx	�A�[�J�C�u�t�@�C���C���f�b�N�X
 * @param   cellfile	�A�[�J�C�u���̃Z���f�[�^�C���f�b�N�X
 * @param   anmfile		�A�[�J�C�u���̃A�j���f�[�^�C���f�b�N�X
 * @param   heap		�ǂݍ��݃o�b�t�@���m�ۂ���˰��ID
 *
 * @retval  BOOL		TRUE�Ő���
 *
 */
//------------------------------------------------------------------
BOOL  PACT_TOOL_LoadCellDatas( PACT_CLANM_PACK* pack, u32 arcFileIdx, u32 cellDataIdx, u32 anmDataIdx, HEAPID heap )
{
	pack->heap = heap;
	pack->cellfile = ArcUtil_UnCompress( arcFileIdx, cellDataIdx, heap );
	pack->anmfile  = ArcUtil_UnCompress( arcFileIdx, anmDataIdx, heap );

	if( pack->cellfile != NULL && pack->anmfile != NULL )
	{
		if( !NNS_G2dGetUnpackedCellBank( pack->cellfile, &(pack->cellbank) ) )
		{
			return FALSE;
		}
		if( !NNS_G2dGetUnpackedMCAnimBank( pack->anmfile, &(pack->anmbank) ) )
		{
			return FALSE;
		}
	}

	return TRUE;

}

//------------------------------------------------------------------
/**
 * �ǂݍ��񂾃Z���E�A�j���f�[�^�����
 *
 * @param   pack	�Z���E�A�j���f�[�^�ǂݍ��ݐ�\����
 *
 */
//------------------------------------------------------------------
void PACT_TOOL_UnloadCellDatas( PACT_CLANM_PACK* pack )
{
	if( pack->cellfile != NULL )
	{
		sys_FreeMemory( pack->heap, pack->cellfile );
		pack->cellfile = NULL;
	}
	if( pack->anmfile != NULL )
	{
		sys_FreeMemory( pack->heap, pack->anmfile );
		pack->anmfile = NULL;
	}
}







//------------------------------------------------------------------
/**
 * �A�N�^�[�Ǘ��f�[�^�S������
 *
 * @param   numact		
 *
 */
//------------------------------------------------------------------
static void ActAllInit( PACT** stack, PACT* acts, u32 numact )
{
	while(numact--)
	{
		*stack = acts;
		ActClear( acts );
		acts++;
		stack++;
	}
}
//------------------------------------------------------------------
/**
 * �A�N�^�[�f�[�^���g�p��ԂɃN���A
 *
 * @param   act		�A�N�^�[�̃f�[�^�N���A
 *
 */
//------------------------------------------------------------------
static void ActClear( PACT* act )
{
	act->next = NULL;
	act->prev = NULL;
}
//------------------------------------------------------------------
/**
 * �A�N�^�[�|�C���^�̃X�^�b�N����|�b�v
 *
 * @param   actsys		�V�X�e�����W���[��
 *
 * @retval  PACT*		�A�N�^�[�|�C���^
 */
//------------------------------------------------------------------
static PACT* ActPop( PACTSYS* actsys )
{
	if( actsys->act_stack_p < actsys->act_max )
	{
		return actsys->act_stack[ actsys->act_stack_p++ ];
	}
	return NULL;
}
//------------------------------------------------------------------
/**
 * �A�N�^�[�|�C���^�̃X�^�b�N�փv�b�V��
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 * @param   act			�A�N�^�[�|�C���^
 *
 */
//------------------------------------------------------------------
static void ActPush( PACTSYS* actsys, PACT* act )
{
	if( actsys->act_stack_p == 0 )
	{
		SDK_ASSERT( 0 );
		return;
	}

	ActClear( act );
	actsys->act_stack_p--;
	actsys->act_stack[ actsys->act_stack_p ] = act;
}

//------------------------------------------------------------------
/**
 * �A�N�^�[���X�g�ɐV�����A�N�^�[���q��
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 * @param   act			�A�N�^�|�C���^�i�v���C�I���e�B�Z�b�g����Ă��邱�Ɓj
 *
 */
//------------------------------------------------------------------
static void ActChain( PACTSYS* actsys, PACT *act )
{
	if( actsys->act_top == NULL )
	{
		actsys->act_top = act;
		act->next = NULL;
		act->prev = NULL;
	}
	else
	{
		PACT* p = actsys->act_top;

		while( 1 )
		{
			// �l���Ⴂ=�v���C�I���e�B����
			if( act->pri < p->pri )
			{
				if( p == actsys->act_top )
				{
					actsys->act_top = act;
				}
				act->prev = p->prev;
				if( act->prev )
				{
					act->prev->next = act;
				}
				act->next = p;
				p->prev = act;
				break;
			}

			if( p->next == NULL )
			{
				p->next = act;
				act->prev = p;
				act->next = NULL;
				break;
			}
			else
			{
				p = p->next;
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * �A�N�^�[���X�g����A�N�^�[���͂���
 *
 * @param   actsys		�V�X�e�����[�N�|�C���^
 * @param   act		
 *
 */
//------------------------------------------------------------------
static void ActUnchain( PACTSYS* actsys, PACT* act )
{
	if( act->prev != NULL)
	{
		if( act->next != NULL )		// �O�ƌ�ɃA�N�^�[������
		{
			act->prev->next = act->next;
			act->next->prev = act->prev;
		}
		else						// ��͂Ȃ����O�ɂ���i�Ō�j
		{
			act->prev->next = NULL;
		}
	}
	else
	{
		if( act->next != NULL )		// �O�͂Ȃ�����ɂ͂���i�擪�j
		{
			act->next->prev = NULL;
			actsys->act_top = act->next;
		}
		else						// �O������Ȃ��i�P�́j
		{
			actsys->act_top = NULL;
		}
	}
}
