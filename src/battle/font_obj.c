//==============================================================================
/**
 * @file	font_obj.c
 * @brief	�t�H���g��OBJ�ŕ\������
 * @author	matsuda
 * @date	2005.10.17(��)
 *
 * �����̃V�X�e���̓A�N�^�[��clact_tool.c���g�p���Ă��鎖���O��ł�
 */
//==============================================================================
#include "common.h"
#include "font_obj.h"
#include "system/arc_tool.h"
#include "system\arc_util.h"
#include "graphic\batt_obj_def.h"
#include "application/app_tool.h"



//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ���쐬���܂�
 *
 * @param   fcd		�t�H���gOBJ�쐬�f�[�^�ւ̃|�C���^
 *
 * ���̊֐��𒼐ڌĂ΂��ɁA�C�����C���֐�FontOBJ_CreateInline���g�p����悤�ɂ��Ă�������
 *
 * �����̃V�X�e���̓A�N�^�[��clact_tool.c���g�p���Ă��鎖���O��ł�
 */
//--------------------------------------------------------------
void FontOBJ_Create(const FONTOBJ_CREATE_DATA *fcd)
{
	s32 arc_charid, arc_palid, arc_cellid, arc_anmid;
	u32 font_len, type_dot;
	s32 oam_count, use_count;
	int i, heap_size, one_oam_size;
	u8 slide_list[FONTOBJ_ACTOR_MAX];
	
	GF_ASSERT(fcd->max_oam <= FONTOBJ_ACTOR_MAX);
	
	MI_CpuClearFast(fcd->fa, sizeof(FONTOBJ_ACTWORK));
	
	type_dot = 8;
	switch(fcd->oam_size){
	case FONTOBJ_OAMSIZE_32x16:
		type_dot = 32;
		one_oam_size = OBJSIZE_32x16;
		heap_size = OBJSIZE_32x16;
		arc_charid = SPACE_32K_32X16_NCGR_BIN;
		arc_palid = SPACE_COLOR_NCLR;
		arc_cellid = SPACE_32K_32X16_NCER_BIN;
		arc_anmid = SPACE_32K_32X16_NANR_BIN;
		for(i = 0; i < FONTOBJ_ACTOR_MAX; i++){
			slide_list[i] = OAMTYPE_32x16;
		}
		break;
	default:
		GF_ASSERT(0 && "����OBJ�F�p�ӂ���Ă��Ȃ��`��ł�\n");
		return;
	}
	
	//������̃h�b�g������A�g�p����OAM�̌����Z�o����
	font_len = FontProc_GetPrintStrWidth(fcd->font, fcd->str, fcd->margin);
	oam_count = FX_DivS32(font_len, type_dot);
	if(FX_ModS32(font_len, type_dot) != 0){
		oam_count++;
	}
	if(oam_count > fcd->max_oam){
		OS_TPrintf("oam_count = %d\n", oam_count);
		GF_ASSERT(0 && "����OBJ�F������̒������g�p�o����OAM���𒴂��Ă��܂�\n");
		return;
	}
	if(fcd->oam_fix == TRUE){
		oam_count = fcd->max_oam;
	}
	
	//�g�pOAM�����̃��\�[�X��o�^
	for(i = 0; i < oam_count; i++){
		CATS_LoadResourceCharArc(fcd->csp, fcd->crp, ARC_BATT_OBJ, arc_charid, 1, 
			fcd->d_area, fcd->start_charid + i);
		CATS_LoadResourceCellArc(fcd->csp, fcd->crp, ARC_BATT_OBJ, arc_cellid, 1, 
			fcd->start_cellid + i);
		CATS_LoadResourceCellAnmArc(fcd->csp, fcd->crp, ARC_BATT_OBJ, arc_anmid, 1, 
			fcd->start_anmid + i);
	}
	//�p���b�g�o�^(2�d�o�^�͒��Ń`�F�b�N����Ă���̂ŌĂ�ő��v)
	CATS_LoadResourcePlttArc(fcd->csp, fcd->crp, ARC_BATT_OBJ, arc_palid, 0, 1, 
		fcd->d_area, fcd->start_palid);
	
	//�A�N�^�[����
	{
		TCATS_OBJECT_ADD_PARAM_S ObjParam;
		
		MI_CpuClearFast(&ObjParam, sizeof(TCATS_OBJECT_ADD_PARAM_S));
		ObjParam.pri = fcd->soft_pri;
		ObjParam.bg_pri = fcd->bg_pri;
		ObjParam.d_area = fcd->d_area;
		ObjParam.pal = fcd->pal_offset;
		for(i = 0; i < oam_count; i++){
			ObjParam.id[CLACT_U_CHAR_RES] = fcd->start_charid + i;
			ObjParam.id[CLACT_U_PLTT_RES] = fcd->start_palid;
			ObjParam.id[CLACT_U_CELL_RES] = fcd->start_cellid + i;
			ObjParam.id[CLACT_U_CELLANM_RES] = fcd->start_anmid + i;
			ObjParam.id[CLACT_U_MULTI_RES] = CLACT_U_HEADER_DATA_NONE;
			ObjParam.id[CLACT_U_MULTIANM_RES] = CLACT_U_HEADER_DATA_NONE;
			fcd->fa->cap[i] = CATS_ObjectAdd_S(fcd->csp, fcd->crp, &ObjParam);
		}
	}
	
	//���b�Z�[�W���쐬���Ċm�ۂ���Vram�̈�֓]��
	{
		u8 *buf, *temp_buf;
		NNSG2dImageProxy * image;
		GF_BGL_BMPWIN bmpwin;
		void *obj_vram;
		heap_size *= oam_count;
		
		//�o�b�t�@��BMP�f�[�^�W�J
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(fcd->bgl, &bmpwin, oam_count * type_dot / 8, 16 / 8, 0, 0);
//		buf = GF_MSG_PrintCGXOnly(&bmpwin, fcd->str, fcd->font, fcd->print_color, fcd->margin);
		GF_STR_PrintExpand(&bmpwin, fcd->font, fcd->str, 0, 0, MSG_NO_PUT, fcd->print_color, fcd->margin, 0, NULL);
		buf = bmpwin.chrbuf;
		
		//�`�����ꂽ�����o�b�t�@��1�����ɍ��킹��悤�ɃX���C�h
		temp_buf = sys_AllocMemory(fcd->heap_id, heap_size);
		APP_MsgOamSlideBuf(buf, temp_buf, slide_list, oam_count);
		
		//�]��
		if(fcd->d_area == NNS_G2D_VRAM_TYPE_2DMAIN){
			obj_vram = G2_GetOBJCharPtr();
		}
		else{
			obj_vram = G2S_GetOBJCharPtr();
		}
		for(i = 0; i < oam_count; i++){
			image = CLACT_ImageProxyGet(fcd->fa->cap[i]->act);
			MI_CpuCopy16(&temp_buf[one_oam_size * i], 
				(void*)((u32)obj_vram 
				+ image->vramLocation.baseAddrOfVram[fcd->d_area]),
				one_oam_size);
		}
		
		//BMP�f�[�^���
		GF_BGL_BmpWinDel(&bmpwin);
		sys_FreeMemoryEz(temp_buf);
	}
	
	//�������쐬
	fcd->fa->start_charid = fcd->start_charid;
	fcd->fa->start_cellid = fcd->start_cellid;
	fcd->fa->start_anmid = fcd->start_anmid;
	fcd->fa->start_palid = fcd->start_palid;
	fcd->fa->use_oam = oam_count;
	fcd->fa->type_dot = type_dot;
	fcd->fa->font_len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ���쐬���܂�
 *
 * @param   crp					
 * @param   fa					�t�H���gOBJ�p�A�N�^�[���[�N�ւ̃|�C���^
 * @param   not_pal_free		TRUE=�p���b�g�̍폜�͍s��Ȃ��@FALSE=�p���b�g�̍폜���s���B
 *
 * not_pal_free�̓p���b�g�𑼂�OBJ�Ƌ��p���Ă���\�����l���ėp�ӂ��Ă��܂�
 */
//--------------------------------------------------------------
void FontOBJ_Delete(CATS_RES_PTR crp, FONTOBJ_ACTWORK *fa, int not_pal_free)
{
	int i;
	
	//���\�[�X���
	for(i = 0; i < fa->use_oam; i++){
		CATS_FreeResourceChar(crp, fa->start_charid + i);
		CATS_FreeResourceCell(crp, fa->start_cellid + i);
		CATS_FreeResourceCellAnm(crp, fa->start_anmid + i);
	}
	if(not_pal_free == FALSE){
		CATS_FreeResourcePltt(crp, fa->start_palid);
	}
	
	//�A�N�^�[�폜
	for(i = 0; i < fa->use_oam; i++){
		CATS_ActorPointerDelete_S(fa->cap[i]);
	}
	
	MI_CpuClearFast(fa, sizeof(FONTOBJ_ACTWORK));
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ��\���E��\���ݒ�
 *
 * @param   fa			�t�H���gOBJ�p�A�N�^�[���[�N�ւ̃|�C���^
 * @param	enable		CATS_ENABLE_TRUE	= �\��
 *						CATS_ENABLE_FALSE	= ��\��
 */
//--------------------------------------------------------------
void FontOBJ_Enable(FONTOBJ_ACTWORK *fa, int enable)
{
	int i;
	
	for(i = 0; i < fa->use_oam; i++){
		CATS_ObjectEnable(fa->cap[i]->act, enable);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ�̍��W���Z�b�g���܂�(X���[���W�w��)
 *
 * @param   fa		�t�H���gOBJ���[�N�ւ̃|�C���^
 * @param   set_type	X���W�Z�b�g���@(FONTOBJ_POS_???)
 * @param   x		�Z�b�g����X���W
 * @param   y		�Z�b�g����Y���W
 *
 * FONTOBJ_POS_LEFT = 	x�𕶎���̍��[�Ƃ��Ĕz�u���܂�
 * FONTOBJ_POS_CENTER =	x�𕶎���̐^�񒆂Ƃ��Ĕz�u���܂�
 * FONTOBJ_POS_RIGHT =	x�𕶎���̉E�[�Ƃ��Ĕz�u���܂�
 */
//--------------------------------------------------------------
void FontOBJ_PosSet(FONTOBJ_ACTWORK *fa, int set_type, s16 x, s16 y)
{
	s16 start_x;
	int i;

	switch(set_type){
	case FONTOBJ_POS_LEFT:
		fa->x = x;
		fa->y = y;
		start_x = x + fa->type_dot / 2;
		break;
	case FONTOBJ_POS_CENTER:
		start_x = x + (fa->type_dot / 2) - (fa->font_len / 2);
		fa->x = start_x;
		fa->y = y;
		break;
	case FONTOBJ_POS_RIGHT:
		start_x = x + (fa->type_dot / 2) - fa->font_len;
		fa->x = start_x;
		fa->y = y;
		break;
	default:
		GF_ASSERT(0 && "��`����Ă��Ȃ��|�W�V�����^�C�v�ł�\n");
		return;
	}

	for(i = 0; i < fa->use_oam; i++){
		CATS_ObjectPosSet(fa->cap[i]->act, start_x, y);
		start_x += fa->type_dot;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �t�H���gOBJ�̍��W���擾���܂�
 *
 * @param   fa		�t�H���gOBJ���[�N�ւ̃|�C���^
 * @param   get_type		X���W�擾���@(FONTOBJ_POS_???)
 * @param   x		�擾����X���W�����
 * @param   y		�擾����Y���W�����
 *
 * FONTOBJ_POS_LEFT = 	������̍��[���W�����o���܂�
 * FONTOBJ_POS_CENTER =	������̐^�񒆍��W�����o���܂�
 * FONTOBJ_POS_RIGHT =	������̉E�[���W�����o���܂�
 */
//--------------------------------------------------------------
void FontOBJ_PosGet(FONTOBJ_ACTWORK *fa, int get_type, s16 *x, s16 *y)
{
	switch(get_type){
	case FONTOBJ_POS_LEFT:
		*x = fa->x;
		*y = fa->y;
		break;
	case FONTOBJ_POS_CENTER:
		*x = fa->x + fa->font_len / 2 - fa->type_dot / 2;
		*y = fa->y;
		break;
	case FONTOBJ_POS_RIGHT:
		*x = fa->x + fa->font_len - fa->type_dot / 2;
		*y = fa->y;
		break;
	default:
		GF_ASSERT(0 && "��`����Ă��Ȃ��|�W�V�����^�C�v�ł�\n");
		return;
	}
}


