//===========================================================================
/**
 * @file	safari_scope_obj.c
 * @brief	�T�t�@���]�����n�a�i
 * @author	Nozomu Saito
 * @date	2006.04.24
 * 
 */
//===========================================================================
#include "common.h"
#include "safari_scope_obj.h"
#include "system/clact_util.h"
#include "system/arc_util.h"
#include "system/gra_tool.h"
#include "poketool/poke_tool.h"

#include "field_cutin.naix"

#define SS_ACT_MAX	(1)
#define SS_RESOURCE_NUM	(4)

#define SS_CHR_ID_POKE	(0)
#define SS_PAL_ID_POKE	(1)
#define SS_CEL_ID_POKE	(2)
#define SS_ANM_ID_POKE	(3)

#define SS_CHAR_CONT_NUM				(1)
#define SS_CHAR_VRAMTRANS_MAIN_SIZE	(2048)
#define SS_CHAR_VRAMTRANS_SUB_SIZE		(0)
#define SS_PLTT_CONT_NUM				(1)

typedef struct SAFARI_SCOPE_OBJ_tag
{
	CLACT_U_RES_MANAGER_PTR ResMan[SS_RESOURCE_NUM];
	CLACT_U_RES_OBJ_PTR 	ResObjTbl[SS_RESOURCE_NUM];
	void *PokeChar;
	void *PokePal;
	SOFT_SPRITE_ARC SpriteArc;
	CLACT_SET_PTR 	ClactSet;
	CLACT_U_EASYRENDER_DATA	RendData;
	CLACT_WORK_PTR			ClActWork;
	BOOL DrawValid;
	BOOL DelFlg;
}SAFARI_SCOPE_OBJ;

static void SetActor( SSO_PTR ptr );
static void DrawTCB( TCB_PTR tcb, void *work );
static void SetPokeGra( CLACT_U_RES_MANAGER_PTR man_obj_ptr,
						CLACT_U_RES_MANAGER_PTR man_pal_ptr,
						void *chr_buf, void *pal_buf );

typedef enum{
	RES_POKE_CHR = 0,
	RES_POKE_PAL,
	RES_POKE_CEL,
	RES_POKE_ANM,
};

//���\�[�X�}�l�[�W���[�o�^���e�[�u��
static const u8 ResEntryNumTbl[] = {
	1,			//�L�������\�[�X
	1,			//�p���b�g���\�[�X
	1,			//�Z�����\�[�X
	1,			//�Z���A�j�����\�[�X
};

//--------------------------------------------------------------------------------------------
/**
 * �������m��
 *
 * @return	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 */
//--------------------------------------------------------------------------------------------
SSO_PTR SSO_AllocMemory(const int inHeapID)
{
	SSO_PTR ptr;
	ptr = sys_AllocMemoryLo(inHeapID, sizeof(SAFARI_SCOPE_OBJ));
	return ptr;
}

//--------------------------------------------------------------------------------------------
/**
 * ���������
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSO_FreeMemory(SSO_PTR ptr)
{
	sys_FreeMemoryEz(ptr);
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�b�g�A�b�v
 *
 * @param	ptr			�]�����p�n�a�i�f�[�^�|�C���^
 * @param	inMonsNo	�����X�^�[�i���o�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSO_SetupSafariScopeCLACT(SSO_PTR ptr, const int inMonsNo)
{
	int i;
	ARCHANDLE *handle;

	ptr->DrawValid = FALSE;

	//�|�P�����X�v���C�g�A�[�J�C�u���擾
	{
		int poke_sex;
		u8 sex;
		sex = PokePersonalParaGet( inMonsNo, ID_PER_sex );
		switch(sex){
		case	MONS_MALE:
			poke_sex = PARA_MALE;
			break;
		case	MONS_FEMALE:
			poke_sex = PARA_FEMALE;
			break;
		case	MONS_UNKNOWN:
			poke_sex = PARA_UNK;
			break;
		default:
			if (gf_rand()%2){
				poke_sex = PARA_MALE;
			}else{
				poke_sex = PARA_FEMALE;
			}
		}
		
		//�Ō�̈����́AFormNo�ƌ������ł� by soga 2006.05.01
		PokeGraArcDataGet( &ptr->SpriteArc, inMonsNo, poke_sex, PARA_FRONT, PARA_NORMAL, NULL, NULL );
	}
	// �Z���A�N�^�[������
	ptr->ClactSet = CLACT_U_SetEasyInit( SS_ACT_MAX, &ptr->RendData, HEAPID_FIELD );
	
	//�J�b�g�C���̃A�[�J�C�u���g�p����
	handle = ArchiveDataHandleOpen(ARC_FIELD_CUTIN_GRA, HEAPID_FIELD);
	//���\�[�X�}�l�[�W���[������
	for(i=0;i<SS_RESOURCE_NUM;i++){
		ptr->ResMan[i] = CLACT_U_ResManagerInit(ResEntryNumTbl[i], i, HEAPID_FIELD);
	}

	{
		ptr->ResObjTbl[RES_POKE_CHR] = CLACT_U_ResManagerResAddArcChar_ArcHandle(
				ptr->ResMan[RES_POKE_CHR], handle,
				NARC_field_cutin_poke_oam_NCGR, FALSE, SS_CHR_ID_POKE,
				NNS_G2D_VRAM_TYPE_2DMAIN, HEAPID_FIELD );
		ptr->ResObjTbl[RES_POKE_PAL] = CLACT_U_ResManagerResAddArcPltt_ArcHandle(
				ptr->ResMan[RES_POKE_PAL], handle,
				NARC_field_cutin_dp_boy01_NCLR, FALSE, SS_PAL_ID_POKE,
				NNS_G2D_VRAM_TYPE_2DMAIN, CLACT_U_PLTT_RES, HEAPID_FIELD );
		ptr->ResObjTbl[RES_POKE_CEL] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				ptr->ResMan[RES_POKE_CEL], handle,
				NARC_field_cutin_poke_oam_NCER, FALSE, SS_CEL_ID_POKE,
				CLACT_U_CELL_RES, HEAPID_FIELD );
		ptr->ResObjTbl[RES_POKE_ANM] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
				ptr->ResMan[RES_POKE_ANM], handle,
				NARC_field_cutin_hidenlight_NANR, FALSE, SS_ANM_ID_POKE,
				CLACT_U_CELLANM_RES, HEAPID_FIELD );
	}
	ptr->PokeChar = ChangesInto_BattlePokeData_Alloc(ptr->SpriteArc.arc_no, ptr->SpriteArc.index_chr, HEAPID_FIELD);
	ptr->PokePal = ChangesInto_BattlePokePalData_Alloc( ptr->SpriteArc.arc_no, ptr->SpriteArc.index_pal, HEAPID_FIELD);

	SetPokeGra( ptr->ResMan[RES_POKE_CHR], ptr->ResMan[RES_POKE_PAL], ptr->PokeChar, ptr->PokePal );
	
	ArchiveDataHandleClose(handle);

	SetActor( ptr );

}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�`��J�n
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSO_DrawStartCellAct(SSO_PTR ptr)
{
	ptr->DrawValid = TRUE;
	ptr->DelFlg = FALSE;
	TCB_Add( DrawTCB, ptr, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�`��I��
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSO_DrawEndCellAct(SSO_PTR ptr)
{
	ptr->DrawValid = FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[�I���҂�
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 *
 * @return	BOOL
 */
//--------------------------------------------------------------------------------------------
BOOL SSO_WaitDrawCellTask(SSO_PTR ptr)
{
	return (ptr->DelFlg);
}

//--------------------------------------------------------------------------------------------
/**
 * 2D�Z���I�u�W�F�N�g���
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void SSO_RereaseSSCellObject(SSO_PTR ptr)
{
	u8 i;
	// �Z���A�N�^�[���\�[�X���

	// �L�����]���}�l�[�W���[�j��
	CLACT_U_CharManagerDelete(ptr->ResObjTbl[CLACT_U_CHAR_RES]);

	// �p���b�g�]���}�l�[�W���[�j��
	CLACT_U_PlttManagerDelete(ptr->ResObjTbl[CLACT_U_PLTT_RES]);

	// �L�����E�p���b�g�E�Z���E�Z���A�j���̃��\�[�X�}�l�[�W���[�j��
	for(i=0;i<SS_RESOURCE_NUM;i++){
		CLACT_U_ResManagerDelete(ptr->ResMan[i]);
	}
	// �Z���A�N�^�[�Z�b�g�j��
	CLACT_DestSet(ptr->ClactSet);

	sys_FreeMemoryEz( ptr->PokeChar );
	sys_FreeMemoryEz( ptr->PokePal );

}

//--------------------------------------------------------------------------------------------
/**
 * �`��^�X�N
 *
 * @param	tcb		�^�X�N�|�C���^
 * @param	work	���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void DrawTCB( TCB_PTR tcb, void *work )
{
	SAFARI_SCOPE_OBJ *ptr = work;
	if (ptr->DrawValid){
		CLACT_Draw( ptr->ClactSet );
	}else{
		ptr->DelFlg = TRUE;
		TCB_Delete( tcb );
	}
}

//--------------------------------------------------------------
/**
 * ���\�[�X�}�l�[�W���|�P�����L����VRAM�]��
 * @param	�n�a�i���\�[�X�}�l�[�W��
 * @param	�p���b�g���\�[�X�}�l�[�W��
 * @param	�L�����o�b�t�@
 * @param	�p���b�g�o�b�t�@
 * 
 * @return	none
 */
//--------------------------------------------------------------
static void SetPokeGra( CLACT_U_RES_MANAGER_PTR man_obj_ptr,
						CLACT_U_RES_MANAGER_PTR man_pal_ptr,
						void *chr_buf, void *pal_buf )
{
	int transSize;
	u32 image_vram,palette_vram;
	CLACT_U_RES_OBJ_PTR res_obj_ptr;
	CLACT_U_RES_OBJ_PTR res_pal_ptr;
	NNSG2dImageProxy *image_proxy;
	const NNSG2dImagePaletteProxy *palette_proxy;
	
	res_obj_ptr = CLACT_U_ResManagerGetIDResObjPtr( man_obj_ptr, SS_CHR_ID_POKE );
	res_pal_ptr = CLACT_U_ResManagerGetIDResObjPtr( man_pal_ptr, SS_PAL_ID_POKE );

	//�u�q�`�l�]��
	CLACT_U_CharManagerSetAreaCont( res_obj_ptr );
	CLACT_U_PlttManagerSetCleanArea( res_pal_ptr );
	
	image_proxy = CLACT_U_CharManagerGetProxy( res_obj_ptr );
	palette_proxy = CLACT_U_PlttManagerGetProxy( res_pal_ptr, image_proxy );
	
	image_vram = NNS_G2dGetImageLocation( image_proxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	palette_vram = NNS_G2dGetImagePaletteLocation( palette_proxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	
	transSize = (32*10)*10;	//32byte x10 y10
	DC_FlushRange(chr_buf,transSize);
	GX_LoadOBJ( chr_buf, image_vram, transSize );

	transSize = 32;	//32byte
	DC_FlushRange( pal_buf, transSize );
	GX_LoadOBJPltt( pal_buf, palette_vram, transSize );	//32byte 1Palette
	
}

//--------------------------------------------------------------------------------------------
/**
 * �Z���A�N�^�[���Z�b�g
 *
 * @param	ptr		�]�����p�n�a�i�f�[�^�|�C���^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void SetActor( SSO_PTR ptr )
{
	int i;
	CLACT_HEADER			cl_act_header;
	
	// �Z���A�N�^�[�w�b�_�쐬	
	CLACT_U_MakeHeader(	&cl_act_header,
						SS_CHR_ID_POKE, SS_PAL_ID_POKE,
						SS_CEL_ID_POKE, SS_ANM_ID_POKE,
						CLACT_U_HEADER_DATA_NONE,
						CLACT_U_HEADER_DATA_NONE,
						0, 0,
						ptr->ResMan[CLACT_U_CHAR_RES],
						ptr->ResMan[CLACT_U_PLTT_RES],
						ptr->ResMan[CLACT_U_CELL_RES],
						ptr->ResMan[CLACT_U_CELLANM_RES],
						NULL,NULL);

	{
		//�o�^���i�[
		CLACT_ADD add;

		add.ClActSet	= ptr->ClactSet;
		add.ClActHeader	= &cl_act_header;

		add.mat.x		= 0;//FX32_CONST(32) ;
		add.mat.y		= 0;//FX32_CONST(96) ;		//��ʂ͏㉺�A�����Ă���
		add.mat.z		= 0;
		add.sca.x		= FX32_ONE;
		add.sca.y		= FX32_ONE;
		add.sca.z		= FX32_ONE;
		add.rot			= 0;
		add.pri			= 0;
		add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
		add.heap		= HEAPID_FIELD;

		//�Z���A�N�^�[�\���J�n

		add.mat.x = FX32_ONE * (256/2);
		add.mat.y = FX32_ONE * (192/2);
		ptr->ClActWork = CLACT_Add(&add);
		CLACT_SetAnmFlag(ptr->ClActWork,0);
		CLACT_AnmChg( ptr->ClActWork, 0 );
	}	
}
