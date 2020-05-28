//==============================================================================
/**
 * @file	gra_tool.c
 * @brief	�O���t�B�b�N�c�[��
 * @author	goto
 * @date	2005.11.16
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/bmp_list.h"

#include "system/gra_tool.h"

#include "system/arc_tool.h"

#include "include/battle/battle_common.h"
#include "system/softsprite.h"
#include "include/poketool/monsno.h"

// =============================================================================
//
//
//	���摜�ϊ�
//
//
// =============================================================================
// 1Char��2D��1D�ϊ�
static void CharCopy1_1D_from_2D(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len);

//--------------------------------------------------------------
/**
 * @brief	2D��1D��1�L�����ϊ�
 *
 * @param	src			���f�[�^
 * @param	dst			�W�J��
 * @param	ofs			���f�[�^�̃R�s�[�J�n�ʒu
 * @param	bofs		�W�J��o�b�t�@�̏������݈ʒu
 * @param	cs			�R�s�[�T�C�Y
 * @param	len			2D�f�[�^�̕�
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CharCopy1_1D_from_2D(const u8* src, u8* dst, int* ofs, int* bofs, int cs, int len)
{
	int i;
	u32 dat;
	
	for (i = 0; i < 8; i++){
		memcpy(&dst[ *bofs ], &src[ *ofs ], cs);
		*ofs  += len;
		*bofs += cs;
	}
}


//--------------------------------------------------------------
/**
 * @brief	�f�̃L�����f�[�^���o��
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	ch_data	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void UnpackCharData(int arc_id, int index_no, int heap_id, NNSG2dCharacterData** ch_data)
{
	BOOL  res;
	void* aw = NULL;
	
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< �L�����f�[�^�̎擾
	res = NNS_G2dGetUnpackedCharacterData(aw, &(*ch_data));
	
	GF_ASSERT(ch_data != NULL);
	
	GF_ASSERT(res != FALSE);
	
	sys_FreeMemoryEz(aw);
}

//--------------------------------------------------------------
/**
 * @brief	�n���ꂽ�L�����f�[�^��ϊ�
 *
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	ch_data	
 * @param	buff	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CI_1D_from_2D(int x, int y, int w, int h, NNSG2dCharacterData* ch_data, void* buff)
{
	u8* p_data = NULL;
	u8* p_buff = NULL;
	int size;
	int cs;
	int ofs;
	int bofs;
	int len;

	GF_ASSERT(ch_data->W >= (x + w));		///< �T�C�Y�`�F�b�N
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< ����
	cs     = (sizeof(u8) * 4);				///< �R�s�[�T�C�Y 8dot = 4Byte
	p_data = ch_data->pRawData;				///< �L�����f�[�^
	p_buff = (u8*)buff;						///< �W�J�o�b�t�@
	
	len = (ch_data->W * cs);				///< ����(���摜�̕�)
	ofs = (x * cs) + (y * len);				///< �J�n�ʒu
	bofs = 0;								///< �o�b�t�@�̏������݈ʒu
	
	//�S�̺�߰
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< �J�n�ʒu
				CharCopy1_1D_from_2D(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1�L�����R�s�[
			}
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�������A�Ԃ��Ώۂ��ǂ���
 *
 * @param	monsno	
 *
 * @retval	static BOOL	TRUE = �Ԃ�
 *
 */
//--------------------------------------------------------------
static BOOL IsStrikeMonsNo(int monsno)
{
	int i;
	int data;
	
	const int monsno_tbl[] = {
		MONSNO_PATTIIRU,
		MONSNO_MAX,				///< �����
	};
	
	for (i = 0; i < MONSNO_MAX; i++){
		
		data = monsno_tbl[ i ];
		
		if (data == MONSNO_MAX){ break; }
		
		if (data == monsno){			
			return TRUE;	
		}		
	}	
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	�Ԃ����������ϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	buff	
 * @param	rnd	
 * @param	animeFlag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void Ex_ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	BOOL bStrike;
	NNSG2dCharacterData* ch_data = NULL;
	
	UnpackCharData(arc_id, index_no, heap_id, &ch_data);
	
	SoftSpriteChrMask(ch_data->pRawData);				///< ����
	
	bStrike = IsStrikeMonsNo(monsno);
	
	if (dir == PARA_FRONT && bStrike == TRUE){
		
		SoftSprite_MakeStrike(ch_data->pRawData, rnd, anime);
		
	}
	
	CI_1D_from_2D(x, y, w, h, ch_data, buff);
}

///< �����������擾
static void* Ex_ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, u32 rnd, BOOL anime, int dir, int monsno)
{
	
	void* buff;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	Ex_ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff, rnd, anime, dir, monsno);
		
	return buff;
}

//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	x					�ϊ��Ώۋ�`:x
 * @param	y					�ϊ��Ώۋ�`:y
 * @param	w					�ϊ��Ώۋ�`:w
 * @param	h					�ϊ��Ώۋ�`:h
 * @param	buff				�W�J��o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_1D_from_2D(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	void* aw = NULL;
	u8* p_data = NULL;
	u8* p_buff = NULL;
	NNSG2dCharacterData* ch_data = NULL;

	int size;
	int cs;
	int ofs;
	int bofs;
	int len;
	BOOL res;
	
	///< �f�[�^�̓W�J
	aw = ArchiveDataLoadMalloc(arc_id, index_no, heap_id);
	
	GF_ASSERT(aw != NULL);
	
	///< �L�����f�[�^�̎擾
	res = NNS_G2dGetUnpackedCharacterData(aw, &ch_data);
	
	GF_ASSERT(res != FALSE);

	GF_ASSERT(ch_data->W >= (x + w));		///< �T�C�Y�`�F�b�N
	GF_ASSERT(ch_data->H >= (y + h));
	
	///< ����
	cs     = (sizeof(u8) * 4);				///< �R�s�[�T�C�Y 8dot = 4Byte
	p_data = ch_data->pRawData;				///< �L�����f�[�^
	
	SoftSpriteChrMask(p_data);				///< ����
	
	p_buff = (u8*)buff;						///< �W�J�o�b�t�@
	
	len = (ch_data->W * cs);				///< ����(���摜�̕�)
	ofs = (x * cs) + (y * len);				///< �J�n�ʒu
	bofs = 0;								///< �o�b�t�@�̏������݈ʒu
	
	//�S�̺�߰
	{
		int i;
		int j;

		for (j = y; j < (y + h); j++){
			for (i = x; i < (x + w); i++){
				ofs = (i * cs) + (j * len * CHAR_DOT_Y);			///< �J�n�ʒu
				CharCopy1_1D_from_2D(p_data, p_buff, &ofs, &bofs, cs, len);	///< 1�L�����R�s�[
			}
		}
	}
	
	sys_FreeMemoryEz(aw);
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	rc					��`
 * @param	buff				�o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_1D_from_2D_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, rc->x, rc->y, rc->h, rc->w, buff);
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɓW�J�o�b�t�@��Alloc���ĕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	x					�ϊ��Ώۋ�`:x
 * @param	y					�ϊ��Ώۋ�`:y
 * @param	w					�ϊ��Ώۋ�`:w
 * @param	h					�ϊ��Ώۋ�`:h
 *
 * @retval	void*				�W�J�����o�b�t�@�̃|�C���^
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_1D_from_2D(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;	
}


//--------------------------------------------------------------
/**
 * @brief	2D��1D�ɓW�J�o�b�t�@��Alloc���ĕϊ�����
 *
 * @param	arc_id				�A�[�J�C�u�C���f�b�N�X
 * @param	index_no			�t�@�C���C���f�b�N�X
 * @param	heap_id				�q�[�vID
 * @param	rc					��`
 *
 * @retval	void*				�W�J�����o�b�t�@�̃|�C���^
 *
 */
//--------------------------------------------------------------
void* ChangesInto_1D_from_2D_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	1D��OAM�`��ɕϊ�
 *
 * @param	sx				�ϊ��Ώۃf�[�^�̃T�C�Y X	
 * @param	sy				�ϊ��Ώۃf�[�^�̃T�C�Y Y
 * @param	x				�؂蔲���J�n X
 * @param	y				�؂蔲���J�n Y
 * @param	w				�؂蔲���T�C�Y W
 * @param	h				�؂蔲���T�C�Y H
 * @param	bofs			�I�t�Z�b�g
 * @param	src				���f�[�^
 * @param	dst				�W�J��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_1D(int sx, int sy, int x, int y, int w, int h, int* bofs, const void* src, void* dst)
{
	int i, j;
	u8* p_data;
	u8* p_buff;
	int ofs;
	
	int lx;
	int ly;
	
	p_data = (u8*)src;
	p_buff = (u8*)dst;
	
	lx = x + w;
	ly = y + h;

	for (j = y; j < ly; j++){
		for (i = x; i < lx; i++){
			ofs = (i * CHAR_BYTE) + (j * CHAR_BYTE * sx);
			memcpy(&p_buff[ *bofs ], &p_data[ ofs ], CHAR_BYTE);
			*bofs += CHAR_BYTE;
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	1D��OAM�`��ɕϊ� ��`�ŃT�C�Y�w��
 *
 * @param	sx				�ϊ��Ώۃf�[�^�̃T�C�Y X	
 * @param	sy				�ϊ��Ώۃf�[�^�̃T�C�Y Y
 * @param	rc				��`
 * @param	bofs			�I�t�Z�b�g
 * @param	src				�f�[�^
 * @param	dst				�W�J��
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_1D_RC(int sx, int sy, const CHANGES_INTO_DATA_RECT* rc, int* bofs, const void* src, void* dst)
{
	ChangesInto_OAM_from_1D(sx, sy, rc->x, rc->y, rc->w, rc->h, bofs, src, dst);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 * @param	buff			�W�J��o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	const CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h);		///< 1D����2D�֕ϊ�

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	rc				��`
 * @param	buff			�o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff)
{
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	x
 * @param	y
 * @param	w
 * @param	h
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc(int arc_id, int index_no, int heap_id, int x, int y, int w, int h)
{
	void* buff = NULL;
	
	int size;
	
	size = ((w * h) * CHAR_BYTE);
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, x, y, w, h, buff);
	
	return buff;
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����̃f�[�^��2D��1D��OAM�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�C���f�b�N�X�ԍ�
 * @param	heap_id			�q�[�vID
 * @param	rc				��`
 *
 * @retval	void*			�W�J���ꂽ�o�b�t�@�|�C���^
 *
 */
//--------------------------------------------------------------
void* ChangesInto_OAM_from_PokeTex_Alloc_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc)
{
	return ChangesInto_OAM_from_PokeTex_Alloc(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^��퓬�p�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�f�[�^�C���f�b�N�X
 * @param	heap_id			�q�[�v�̈�
 * @param	buff			�o�b�t�@
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff)
{
	const CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H
	};
	
	ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff);
}


//--------------------------------------------------------------
/**
 * @brief	�|�P�����f�[�^��퓬�p�ɕϊ�
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�f�[�^�C���f�b�N�X
 * @param	heap_id			�q�[�vID
 *
 * @retval	void*			�o�b�t�@
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff);
	
	return buff;	
}

//--------------------------------------------------------------
/**
 * @brief	�f�̃p���b�g�f�[�^�����o��
 *
 * @param	arc_id			�A�[�J�C�uID
 * @param	index_no		�f�[�^�C���f�b�N�X
 * @param	heap_id			�q�[�vID
 *
 * @retval	void*			�o�b�t�@
 *
 */
//--------------------------------------------------------------
void* ChangesInto_BattlePokePalData_Alloc(int arc_id, int index_no, int heap_id)
{
	NNSG2dPaletteData	*pd;
	void*				buf;
	void*				col;
	int					i;
	BOOL				ret;

	//�p���b�g�f�[�^�ǂݍ���
	col=sys_AllocMemory(heap_id,0x20);
	buf=ArchiveDataLoadMalloc(arc_id,index_no,heap_id);
	ret=NNS_G2dGetUnpackedPaletteData(buf,&pd);

	GF_ASSERT(ret==TRUE);

	MI_CpuCopy16(pd->pRawData,col,0x20);

	sys_FreeMemoryEz(buf);

	return col;	
}



//--------------------------------------------------------------
/**
 * @brief	�Ԃ����l�������|�P�����f�[�^�ϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	x	
 * @param	y	
 * @param	w	
 * @param	h	
 * @param	buff	
 * @param	rnd				������
 * @param	anime			�A�j���t���O
 * @param	dir				����
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_OAM_from_PokeTex(int arc_id, int index_no, int heap_id, int x, int y, int w, int h, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	int i;
	int num;
	int ofs;
	void* temp = NULL;
	
	const CHANGES_INTO_DATA_RECT rc[] = {
		{ 0, 0, 8, 8 },
		{ 8, 0, 2, 4 },
		{ 8, 4, 2, 4 },
		{ 0, 8, 4, 2 },
		{ 4, 8, 4, 2 },
		{ 8, 8, 2, 2 },
	};
	
	num = NELEMS(rc);
	ofs = 0;
	
	temp = Ex_ChangesInto_1D_from_2D_Alloc(arc_id, index_no, heap_id, x, y, w, h, rnd, anime, dir, monsno);		///< 1D����2D�֕ϊ�

	for (i = 0; i < num; i++){
		ChangesInto_OAM_from_1D_RC(w, h, &rc[i], &ofs, temp, buff);
	}
	
	sys_FreeMemoryEz(temp);
}

//--------------------------------------------------------------
/**
 * @brief	�Ԃ��l���|�P�����ϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	rc	
 * @param	buff	
 * @param	rnd				������
 * @param	anime			�A�j���t���O
 * @param	dir				����
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_OAM_from_PokeTex_RC(int arc_id, int index_no, int heap_id, const CHANGES_INTO_DATA_RECT* rc, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	Ex_ChangesInto_OAM_from_PokeTex(arc_id, index_no, heap_id, rc->x, rc->y, rc->w, rc->h, buff, rnd, anime, dir, monsno);
}


//--------------------------------------------------------------
/**
 * @brief	�Ԃ����l�������|�P�����ϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	buff	
 * @param	rnd				������
 * @param	anime			�A�j���t���O
 * @param	dir				����
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void  Ex_ChangesInto_BattlePokeData(int arc_id, int index_no, int heap_id, void* buff, u32 rnd, BOOL anime, int dir, int monsno)
{
	const CHANGES_INTO_DATA_RECT rc = {
		POKE_TEX_X,
		POKE_TEX_Y,
		POKE_TEX_W,
		POKE_TEX_H
	};
	
	Ex_ChangesInto_OAM_from_PokeTex_RC(arc_id, index_no, heap_id, &rc, buff, rnd, anime, dir, monsno);
}

//--------------------------------------------------------------
/**
 * @brief	�Ԃ����l�������|�P�����ϊ�
 *
 * @param	arc_id	
 * @param	index_no	
 * @param	heap_id	
 * @param	rnd				������
 * @param	anime			�A�j���t���O
 * @param	dir				����
 *
 * @retval	void*	
 *
 */
//--------------------------------------------------------------
void* Ex_ChangesInto_BattlePokeData_Alloc(int arc_id, int index_no, int heap_id, u32 rnd, BOOL anime, int dir, int monsno)
{
	void* buff = NULL;
	
	int size;
	
	size = POKE_TEX_SIZE;
	
	buff = sys_AllocMemory(heap_id, size);
	
	Ex_ChangesInto_BattlePokeData(arc_id, index_no, heap_id, buff, rnd, anime, dir, monsno);
	
	return buff;		
}

