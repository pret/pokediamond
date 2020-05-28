#include "map_tool.h"
#include "worldmap.h"
#include "div_map.h"
#include "fieldsys.h"
#include "field_gimmick.h"

#include "fielddata/mapattr/map_attr.h"

#include "debug_saito.h"

#define HIT_ATTR_MASK	(0x1)
#define LSB_MASK		(0xff)

#define MOVE_HEIGHT_DEF	(20*FX32_ONE)	//20���j�b�g (1.5�O���b�h��24���j�b�g���ƁA�덷���o���Ƃ��ɑΉ�������̂ŁA�؂�l�߂܂���)
//static BOOL GetGroundMapHeight(FIELDSYS_WORK *fsys, VecFx32 *ioPos);
//static BOOL GetUnderMapHeight(FIELDSYS_WORK *fsys, VecFx32 *ioPos);
static const fx32 GetGroundMapHeight(	const FIELDSYS_WORK *fsys,
										const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
										u8 *outCode);
static const fx32 GetUnderMapHeight(	const FIELDSYS_WORK *fsys,
										const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
										u8 *outCode);
static BOOL GetGroundAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ, u16 *outAttr);
static BOOL GetUnderAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ, u16 *outAttr);
static int CheckHeightMove(	const FIELDSYS_WORK *fsys,
							const VecFx32 *inVec,
							const int inGridX,
							const int inGridZ,
							u8 *outCode);

//typedef BOOL (*GET_HEIGHT_FUNC)(FIELDSYS_WORK *fsys, VecFx32 *ioPos);
typedef const fx32 (*GET_HEIGHT_FUNC)(	const FIELDSYS_WORK *fsys,
										const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
										u8 *outCode);
typedef BOOL (*GET_ATTR_FUNC)(const FIELDSYS_WORK *fsys, const int inX, const int inZ, u16 *outAttr);

typedef struct MAP_TOOL_LIST_tag
{
	GET_HEIGHT_FUNC	GetHeightFunc;
	GET_ATTR_FUNC	GetAttributeFunc;
}MAP_TOOL_LIST;

static const MAP_TOOL_LIST GroundMapToolList =
{
	GetGroundMapHeight,
	GetGroundAttribute
};

static const MAP_TOOL_LIST UnderMapToolList =
{
	GetUnderMapHeight,
	GetUnderAttribute
};

//==============================================================================
/**
 * 2�̒l�̍�����Ԃ�(���l)
 *
 * @param   inVal1	�l1��
 * @param	inVal2	�l2��
 *
 * @retval  fx32	�����l
 */
//==============================================================================
static fx32 GetSubVal(const fx32 inVal1, const fx32 inVal2)
{
	fx32 val;
	if (inVal1 >=inVal2){
		val = inVal1 - inVal2;
	}else{
		val = inVal2 - inVal1;
	}

	return val;
}

//==============================================================================
/**
 * �����擾
 *
 * @param   fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inPos	���W
 *
 * @retval  MAP_RESOURCE_PTR	�m�ۂ���MAPRESOURCE�̃|�C���^
 */
//==============================================================================
static const fx32 GetGroundMapHeight(	const FIELDSYS_WORK *fsys,
										const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
										u8 *outCode)
{
	BOOL ex_rc,normal_rc;
	u8 code;
	u32	grid_x,grid_z;
	u32 block_x,block_z;
	u32 block_index;
	u32 local_index;

	u32 grid_no;
	u8 pos_in_block;
	
	VecFx32 target;

	fx32 x_ofs,z_ofs;
	u8 index;

	fx32 height;

	ex_rc = FALSE;
	normal_rc = FALSE;
	
	height = 0;
	target.x =inX;
	target.z =inZ;
	target.y =0;
	
	{
		int map_w;
		int map_grid_w;
		
		DMC_CONST_PTR map_data_ptr = (DMC_CONST_PTR)fsys->map_cont_dat;
		map_w = GetWorldMapMatrixW(fsys->World);
		map_grid_w = map_w*BLOCK_GRID_W;
		
		//���݃u���b�N���v�Z
		grid_x = inX/(16*FX32_ONE);
		grid_z = inZ/(16*FX32_ONE);

		//�g�������f�[�^�𒲂ׂ�
		ex_rc = EXH_HitCheckExHeight(grid_x, grid_z, fsys->ExHeightList, &index);

		block_x = grid_x / BLOCK_GRID_W;
		block_z = grid_z / BLOCK_GRID_H;
		block_index = block_x+block_z*map_w;
	
		//���@���W�Ƀu���b�N�I�t�Z�b�g�������Z
		x_ofs = ((block_x*BLOCK_GRID_W)+(BLOCK_GRID_W/2))*16*FX32_ONE;
		z_ofs = ((block_z*BLOCK_GRID_H)+(BLOCK_GRID_H/2))*16*FX32_ONE;
		target.x = inX - x_ofs;
		target.z = inZ - z_ofs;
	
		grid_no = grid_x+grid_z*map_grid_w;
		pos_in_block = CalcPositionInBlockFromGridNo(grid_no,map_grid_w);
		local_index = CalcLocalIdxFromBlockIdx(block_index,pos_in_block,map_data_ptr);
		if (local_index>3){
			normal_rc = FALSE;
		}else{
			//�����擾
			{
				MHI_CONST_PTR  height_info = GetDivMapHeightInfo(map_data_ptr,local_index);
				///OS_Printf_saitou("local_idx=%d\n",local_index);
				normal_rc = GetHeightForBlock(inNowHeight, target.x, target.z, height_info, &target.y);
			}
		}
	}

	if (ex_rc){
		fx32 ex_height;
		//�g�������f�[�^�擾
		ex_height = EXH_GetExHeight(index, fsys->ExHeightList);
		if (normal_rc){
			OS_Printf_saitou("local_print ex_nor=%x,%x\n",ex_height,target.y);
			//�ǂ�����̗p���邩���`�F�b�N
			//�����ق��𒲂ׂ�
			if (ex_height<=target.y){
				//�ʏ�̕��������ꍇ�͂�����̗p
///				rc = TRUE;
///				ioPos->y = target.y;
				code = HEIGHT_NORMAL;
				height = target.y;
			}else{
				fx32 sub1,sub2;
				OS_Printf_saitou("local_print ex,target,now=%x,%x,%x\n",ex_height,target.y,height);
				//�g���̕��������ꍇ�͎w�荂���ɋ߂��ق����̗p
				sub1 = GetSubVal(target.y, inNowHeight);	//�ʏ퍂���ƌ��ݒl�̍�
				sub2 = GetSubVal(ex_height, inNowHeight);	//�g�������ƌ��ݒl�̍�
				OS_Printf_saitou("local_print ����%x,%x\n",sub1,sub2);
				if (sub1 <= sub2){
					//�ʏ퍂�����̗p
///					ioPos->y = target.y;
					height = target.y;
					code = HEIGHT_NORMAL;
				}else{
					//�g���������̗p
				OS_Printf_saitou("local_print �g���������̗p\n");
///					ioPos->y = ex_height;
					height = ex_height;
					code = HEIGHT_EXPAND;
				}
///				rc = TRUE;
			}
		}else{
			//�g�������f�[�^�݂̂Ƀq�b�g
///			rc = TRUE;
///			ioPos->y = ex_height;
			code = HEIGHT_EXPAND;
			height = ex_height;
		}
	}else{
		if (normal_rc){
///			rc = TRUE;
///			ioPos->y = target.y;
			code = HEIGHT_NORMAL;
			height = target.y;
		}else{
///			rc = FALSE;
			code = HEIGHT_FAIL;
		}
	}
	
///	return rc;
	if (outCode != NULL){
		*outCode = code;
	}
	return height;
}

static const fx32 GetUnderMapHeight(	const FIELDSYS_WORK *fsys,
										const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
										u8 *outCode)
{
	BOOL rc;
	int grid_x,grid_z;
	fx32 height;
	u8 code;
	
	//�O���b�h�ɕϊ�
	grid_x = inX / (16*FX32_ONE);
	grid_z = inZ / (16*FX32_ONE);

	rc = CheckFourBlockIO(	fsys->map_cont_dat,
							grid_x,
							grid_z,
							NULL);
	if (rc){
		code = HEIGHT_NORMAL;
	}else{
		code = HEIGHT_FAIL;
	}

	if (outCode != NULL){
		*outCode = code;
	}
	
	//�����͂O���Z�b�g
	height = 0;
	return height;
}

static BOOL GetGroundAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ, u16 *outAttr)
{
	BOOL rc;
	u32 block_x,block_z;
	u32 block_index;
	u8 local_index;

	u32 grid_no;
	u8 pos_in_block;

	{
		BOOL rc;
		DMC_CONST_PTR map_data_ptr = fsys->map_cont_dat;
		rc = CheckFourBlockIO(	map_data_ptr,
								inX,
								inZ,
								&local_index);
		if (rc == FALSE){
			(*outAttr) = MATTR_NO_ATTR;
			return FALSE;
		}
/**		
		int map_w;
		int map_grid_w;
		DMC_CONST_PTR map_data_ptr = fsys->map_cont_dat;
		map_w = GetWorldMapAreaW(fsys->world);
		map_grid_w = map_w*BLOCK_GRID_W;
		block_x = inX / BLOCK_GRID_W;
		block_z = inZ / BLOCK_GRID_H;

		block_index = block_x+block_z*map_w;
	
		grid_no = inX+inZ*map_grid_w;
		pos_in_block = CalcPositionInBlockFromGridNo(grid_no,map_grid_w);
		local_index = CalcLocalIdxFromBlockIdx(block_index,pos_in_block,map_data_ptr);
		if (local_index>3){
			return FALSE;
		}
*/
		{
			u32 local_grid_index;	//0�`1023
			u16 const *attribute;
			local_grid_index = (inZ % BLOCK_GRID_H)*BLOCK_GRID_W+(inX % BLOCK_GRID_W);
			
			//OS_Printf_saitou("local_grid_index = %d\n",local_grid_index);
			//�A�g���r���[�g�擾
			attribute = GetDivMapAttribute(map_data_ptr, local_index);
			*outAttr = attribute[local_grid_index];
			return TRUE;
		}
	}
}

static BOOL GetUnderAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ, u16 *outAttr)
{
	BOOL rc;
	u32 block_x,block_z;
	u32 block_index;
	u32 local_index;

	u32 grid_no;
	u8 pos_in_block;

	//u8 under_index;

	{
		int map_w;
		int map_grid_w;
		DMC_CONST_PTR map_data_ptr = fsys->map_cont_dat;
		map_w = GetWorldMapMatrixW(fsys->World);
		map_grid_w = map_w*BLOCK_GRID_W;
		block_x = inX / BLOCK_GRID_W;
		block_z = inZ / BLOCK_GRID_H;

		block_index = block_x+block_z*map_w;
	
		//grid_no = inX+inZ*map_grid_w;

		//fsys�ɂԂ牺����n���}�b�s���O�f�[�^�i30��30�j�ɃO���b�h�i���o�[�𓊂��āB�O�`�P�X�̑Ή��C���f�b�N�X�����炤
		//under_index = fsys->under_map[grid_no];
		{
			u32 local_grid_index;	//0�`1023
			u16 const *block_attr;
			local_grid_index = (inZ % BLOCK_GRID_H)*BLOCK_GRID_W+(inX % BLOCK_GRID_W);
			///OS_Printf_saitou("local_=%d",local_grid_index);
			///block_attr = (u16 const *)&(fsys->GroundAttr[BLOCK_ATTR_SIZE*under_index]);
			block_attr = SPATTR_GetSpBlockAttribute(block_index, fsys->SpMatData);
			*outAttr = block_attr[local_grid_index];
			return TRUE;
		}
	}
}


void SetUpMapToolList(MTL_CONST_PTR *outMapToolList, MAP_TOOL_MODE inMapMode)
{
	if (inMapMode == MAP_TOOL_MODE_GROUND){
		*outMapToolList = &GroundMapToolList;
	}else if (inMapMode == MAP_TOOL_MODE_UNDER){
		*outMapToolList = &UnderMapToolList;
	}else{
		GF_ASSERT( 0 && "Mapmode unknown " );
	}
}

//==============================================================================
/**
 * �����茟�o
 *
 * @param   fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inX	�O���b�hX���W
 * @param	inZ	�O���b�hZ���W
 *
 * @retval  BOOL	TRUE:�i���s��	FALSE:�i����
 */
//==============================================================================
BOOL GetHitAttr(const FIELDSYS_WORK *fsys, const int inX, const int inZ)
{
	BOOL rc;
	u16 attribute;
	rc = fsys->map_tool_list->GetAttributeFunc(fsys, inX, inZ, &attribute);
	
	if(rc){
		u8 atr;
		
		atr = (u8)(attribute>>15);
		atr &= HIT_ATTR_MASK;
///		OS_Printf_saitou("idx,x,y,atr = %d,%d,%d\n",inX,inZ,atr);
		if (atr == 1){
			return TRUE;
		}
	}
	
	return FALSE;
}

//==============================================================================
/**
 * �A�g���r���[�g�擾(2�o�C�g)
 *
 * @param	*fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inX		X�O���b�h���W
 * @param	inZ		Z�O���b�h���W
 *
 * @return	attrbute	�A�g���r���[�g�@���s�̏ꍇ��0��Ԃ�
 */
//==============================================================================
u16 GetAttribute(const FIELDSYS_WORK *fsys, const int inX, const int inZ)
{
	BOOL rc;
	u16 attribute;
	rc = fsys->map_tool_list->GetAttributeFunc(fsys, inX, inZ, &attribute);
	
	if(rc){
		return attribute;
	}
	//�擾���s
	return 0;
}

//==============================================================================
/**
 * �A�g���r���[�g�擾(����1�o�C�g)
 *
 * @param	*fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inX		X�O���b�h���W
 * @param	inZ		Z�O���b�h���W
 *
 * @return	attrbute	�A�g���r���[�g�@���s�̏ꍇ��0��Ԃ�
 */
//==============================================================================
MATR GetAttributeLSB(const FIELDSYS_WORK *fsys, const int inX, const int inZ)
{
	BOOL rc;
	u16 attribute;

	rc = fsys->map_tool_list->GetAttributeFunc(fsys, inX, inZ, &attribute);
	
	if(rc){
		u8 atr;
		atr = attribute;
		atr &= LSB_MASK;
		return atr;
	}
	//�擾���s
	return MATTR_NO_ATTR;
}

//==============================================================================
/**
 * �A�g���r���[�g�擾(���1�o�C�g)
 *
 * @param	*fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inX		X�O���b�h���W
 * @param	inZ		Z�O���b�h���W
 *
 * @return	attrbute	�A�g���r���[�g�@���s�̏ꍇ��0��Ԃ�
 */
//==============================================================================
u8 GetAttributeHSB(const FIELDSYS_WORK *fsys, const int inX, const int inZ)
{
	BOOL rc;
	u16 attribute;
	rc = fsys->map_tool_list->GetAttributeFunc(fsys, inX, inZ, &attribute);
	
	if(rc){
		u8 atr;
		atr = (u8)(attribute>>15);
		atr &= LSB_MASK;
		return atr;
	}
	//�擾���s
	return 0;
}



//==============================================================================
/**
 * �����擾
 *
 * @param	*ioHeroPoint	���@���W
 *
 * @return	none
 */
//==============================================================================
const fx32 GetHeightPack(	const FIELDSYS_WORK *fsys,
							const fx32 inNowHeight, const fx32 inX, const fx32 inZ,
							HEIGHT_TYPE *outCode)
{
	BOOL rc;
	fx32 height;
	height = fsys->map_tool_list->GetHeightFunc(fsys, inNowHeight, inX, inZ, outCode);
	//OS_Printf_saitou("GetHeight=%x:%x,%x\n",height,inX,inZ);	
	return height;
}
#if 0
//==============================================================================
/**
 * �����擾
 *
 * @param	*ioHeroPoint	���@���W
 *
 * @return	none
 */
//==============================================================================
BOOL GetHeightPack_old(	FIELDSYS_WORK *fsys, VecFx32 *ioVec)
{
	BOOL rc;
	HEIGHT_TYPE code;
	ioVec->y = fsys->map_tool_list->GetHeightFunc(fsys, ioVec->y, ioVec->x, ioVec->z, &code);
	if (code != HEIGHT_FAIL){
		return TRUE;
	}else{
		return FALSE;
	}
}
#endif
#if 0
//==============================================================================
/**
 * �����擾
 *
 * @param	*ioHeroPoint	���@���W
 *
 * @return	none
 */
//==============================================================================
const fx32 GetHeightPackEx(	FIELDSYS_WORK *fsys,
									const fx32 inNowY, const fx32 inX, const fx32 inZ,
									u8 *outCode)
{
	u8 code;
	fx32 return_height;
	fx32 height;
	
	height = fsys->map_tool_list->GetHeightFunc(fsys, inNowY, inX, inZ, outCode);
	
	{
		fx32 ex_height;
		BOOL ex_rc;
		u8 index;
		u32	grid_x,grid_z;
		//���݃u���b�N���v�Z
		grid_x = inX/(16*FX32_ONE);
		grid_z = inZ/(16*FX32_ONE);
		
		//�g�������f�[�^�𒲂ׂ�
		ex_rc = EXH_HitCheckExHeight(grid_x, grid_z, fsys->ExHeightList, &index);

		if (ex_rc){
			//�g�������f�[�^�擾
			ex_height = EXH_GetExHeight(index, fsys->ExHeightList);
			OS_Printf_saitou("local_print ex_nor=%x,%x\n",ex_height,height);
			//�ǂ�����̗p���邩���`�F�b�N
			//�����ق��𒲂ׂ�
			if (ex_height<=height){
				//�ʏ�̕��������ꍇ�͂�����̗p
				code = HEIGHT_NORMAL;
				return_height = height;
			}else{
				fx32 sub1,sub2;
				OS_Printf_saitou("local_print ex,target,now=%x,%x,%x\n",ex_height,height,inNowY);
				//�g���̕��������ꍇ�͎w�荂���ɋ߂��ق����̗p
				sub1 = GetSubVal(height, inNowY);	//�ʏ퍂���ƌ��ݒl�̍�
				sub2 = GetSubVal(ex_height, inNowY);	//�g�������ƌ��ݒl�̍�
				OS_Printf_saitou("local_print ����%x,%x\n",sub1,sub2);
				if (sub1 <= sub2){
					//�ʏ퍂�����̗p
					return_height = height;
					code = HEIGHT_NORMAL;
				}else{
					//�g���������̗p
				OS_Printf_saitou("local_print �g���������̗p\n");
					return_height = ex_height;
					code = HEIGHT_EXPAND;
				}
			}
		}else{
			//�g�������f�[�^�݂̂Ƀq�b�g
			code = HEIGHT_EXPAND;
			return_height = ex_height;
		}
	}
	
	if (outCode != NULL){
		*outCode = code;
	}
	return return_height;
}
#endif
//==============================================================================
/**
 * ���݂̍����Ǝw��̍�������i���ł��邩�𒲂ׂ�
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^	
 * @param	inVec		���ݍ��W
 * @param	inGridX		�w��O���b�h���WX
 * @param	inGridZ		�w��O���b�h���WZ
 * @param	outCode		�ǂ̍����f�[�^�Ƀq�b�g�������̃`�F�b�N�p�i�ʏ�A�g���A�����Ȃ��j
 *
 * @return	1:����	-1:�Ⴂ		0:����
 */
//==============================================================================
static int CheckHeightMove(	const FIELDSYS_WORK *fsys,
							const VecFx32 *inVec, const int inGridX, const int inGridZ,
							HEIGHT_TYPE *outCode)
{
	int rc;
	fx32 y_high,y_low;
	
	fx32 x,z;
	fx32 height;
	
	//�w��O���b�h�̍������擾
	//�O���b�h��FX32�^�ɂ���(�O���b�h�̒��S���W)
	x = inGridX * 16 * FX32_ONE+(8*FX32_ONE);
	z = inGridZ * 16 * FX32_ONE+(8*FX32_ONE);
	height = 0;

	height = GetHeightPack(fsys, inVec->y, x, z, outCode);
#if 0
	{
		VecFx32 vec;
		OS_Printf_saitou("check_height=%x,%x\n",height,inVec->y);
		Player_VecPosGet( fsys->player, &vec );
		OS_Printf_saitou("player=%x,%x,%x\n",vec.x,vec.y,vec.z);
		OS_Printf_saitou("target=%x,%x,%x\n",x,height,z);
	}
#endif
	//���݂̍����Ɣ�r
	if(height < inVec->y){		//�w��O���b�h�̂ق����Ⴂ
		y_high = inVec->y;
		y_low = height;
		rc = HIT_RES_TOO_LOW;
	}else if(height > inVec->y){	//�w��O���b�h�̂ق�������
		y_high = height;
		y_low = inVec->y;
		rc = HIT_RES_TOO_HEIGH;
	}else{							//����
		rc = HIT_RES_EQUAL;
		return rc;
	}

	//�i���Ƃ݂Ȃ���邩�𔻒�
	if (y_high-y_low >= MOVE_HEIGHT_DEF){
		GF_ASSERT(rc!=0 && "�߂�l���s��");
		//�K��l�ȊO�Ȃ̂ŁA�i���Ƃ݂Ȃ�
	}else{
		rc = HIT_RES_EQUAL;			//�K��l�ȓ��Ȃ̂ŁA�i���Ƃ݂͂Ȃ��Ȃ�
	}
	
	return rc;
}

//==============================================================================
/**
 * ���������������q�b�g����
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^	
 * @param	inVec		���ݍ��W
 * @param	inGridX		�w��O���b�h���WX
 * @param	inGridZ		�w��O���b�h���WZ
 * @param	outFlg		���茋�ʂ��i�[����o�b�t�@
 *
 * @return	BOOL	TRUE:�i���s�@FALSE:�i����
 */
//==============================================================================
BOOL MPTL_CheckHitWall(	const FIELDSYS_WORK *fsys,
						const VecFx32 *inVec,
						const int inGridX,
						const int inGridZ,
						s8 *outFlg)
{	
	int check;
	HEIGHT_TYPE code;
	check = CheckHeightMove(fsys, inVec, inGridX, inGridZ, &code);
	if (outFlg != NULL){
		*outFlg = check;
	}
		
	if (check == HIT_RES_EQUAL){
		BOOL hit;
		//�i���\�Ȃ�΁A�A�g���r���[�g�ɂ��q�b�g������s��
		hit = GetHitAttr(fsys, inGridX, inGridZ);
		if ((!hit)&&(code==HEIGHT_EXPAND)){
			//�A�g���r���[�g�q�b�g�ł��i���\�A���A�g�������f�[�^���擾�����ꍇ
			//���Ȃ����Ȃ��`�F�b�N���s��
			MATR attr = GetAttributeLSB( fsys, inGridX, inGridZ );
			if (MATR_IsWaterNoIn(attr)){	//�g�������ŁA���Ȃ����Ȃ��A�g���r���[�g�̂Ƃ�
				return TRUE;//�i���s��
			}
		}
		return hit;
	}else{
		return TRUE;		//������A���B�i���s��
	}
}

//==============================================================================
/**
 * ���������������q�b�g����@�O�������蔻����s��
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^	
 * @param	inVec		���ݍ��W
 * @param	inGridX		�w��O���b�h���WX
 * @param	inGridZ		�w��O���b�h���WZ
 * @param	outFlg		���茋�ʂ��i�[����o�b�t�@
 *
 * @return	BOOL	TRUE:�i���s�@FALSE:�i����
 */
//==============================================================================
BOOL MPTL_CheckHitWallEx(	FIELDSYS_WORK *fsys,
							const VecFx32 *inVec,
							const int inGridX,
							const int inGridZ,
							s8 *outFlg)
{	
	int check;
	HEIGHT_TYPE code;
	check = CheckHeightMove(fsys, inVec, inGridX, inGridZ, &code);
	if (outFlg != NULL){
		*outFlg = check;
	}
		
	//�i���\�Ȃ�΁A�A�g���r���[�g�ɂ��q�b�g������s��
	if (check == HIT_RES_EQUAL){
		BOOL hit;
		BOOL ex_rc;
		//�n�߂ɊO�������蔻����s��
		ex_rc = FLDGMK_FieldGimmickHitCheck(fsys, inGridX, inGridZ,
											inVec->y, &hit);
		//�O�������蔻����s��Ȃ������Ƃ��̂ݒʏ픻��Ɉڍs����
		if (!ex_rc){	
			hit = GetHitAttr(fsys, inGridX, inGridZ);
			if ((!hit)&&(code==HEIGHT_EXPAND)){
				//�A�g���r���[�g�q�b�g�ł��i���\�A���A�g�������f�[�^���擾�����ꍇ
				//���Ȃ����Ȃ��`�F�b�N���s��
				MATR attr = GetAttributeLSB( fsys, inGridX, inGridZ );
				if (MATR_IsWaterNoIn(attr)){	//�g�������ŁA���Ȃ����Ȃ��A�g���r���[�g�̂Ƃ�
					return TRUE;//�i���s��
				}
			}
			return hit;
		}else{
			return hit;
		}
	}else{
		return TRUE;		//������A���B�i���s��
	}
}


//==============================================================================
/**
 * �w��O���b�h���W�̏�U�O���b�h���̋�`�̍���A�E�����W���Z�o����
 *
 * @param	inGridX		�w��O���b�hX���W
 * @param	inGridZ		�w��O���b�hZ���W
 * @param	inDir		����
 * @param	outX1		��`X���W�i���j
 * @param	outZ1		��`Z���W�i���j
 * @param	outX2		��`X���W�i�E�j
 * @param	outZ2		��`Z���W�i��O�j
 *
 * @return	none
 */
//==============================================================================
void MPTL_GetTargetRect(const int inGridX, const int inGridZ,
						const int inDir, TARGET_RECT *outRect )
{
	int grid_x1,grid_z1,grid_x2,grid_z2;
///	switch(inDir){
///	case 0:					//�����
		//�Ώۍ���O���b�h
		grid_x1 = inGridX-1;
		grid_z1 = inGridZ-2;
		//�ΏۉE���O���b�h
		grid_x2 = inGridX+1;
		grid_z2 = inGridZ;
///		break;
///	default:
///		break;
///	}

	if (grid_x1<0 || grid_z1<0 || grid_x2<0 || grid_z2<0){
		GF_ASSERT(0&&"ERROR:�O���b�h�l���}�C�i�X");
	}
	//�O���b�h��fx32�^�ɕύX
	outRect->X1 = grid_x1*16*FX32_ONE;
	outRect->Z1 = grid_z1*16*FX32_ONE;
	outRect->X2 = (grid_x2+1)*16*FX32_ONE;
	outRect->Z2 = (grid_z2+1)*16*FX32_ONE;
}

//==============================================================================
/**
 * �w��O���b�h���W����_�Ƃ��āA��`���쐬
 *
 * @param	inGridX		�w��O���b�hX���W
 * @param	inGridZ		�w��O���b�hZ���W
 * @param	inX			��_����̃I�t�Z�b�g�@��`X���W�i���J�n�j
 * @param	inZ			��_����̃I�t�Z�b�g�@��`Z���W�i���J�n�j
 * @param	inW			��`����
 * @param	inH			��`�c��
 * @param	outX1		��`X���W�i���j
 * @param	outZ1		��`Z���W�i���j
 * @param	outX2		��`X���W�i�E�j
 * @param	outZ2		��`Z���W�i��O�j
 *
 * @return	none
 */
//==============================================================================
void MPTL_MakeTargetRect(	const int inGridX,const int inGridZ, 
							const int inOfsX, const inOfsZ,
							const u32 inW, const u32 inH,
							TARGET_RECT *outRect )
{
	int grid_x1,grid_z1,grid_x2,grid_z2;
	//�Ώۍ���O���b�h
	grid_x1 = inGridX+inOfsX;
	grid_z1 = inGridZ+inOfsZ;
	//�ΏۉE���O���b�h
	grid_x2 = grid_x1+inW;
	grid_z2 = grid_z1+inH;

	if (grid_x1<0 || grid_z1<0 || grid_x2<0 || grid_z2<0){
		GF_ASSERT(0&&"ERROR:�O���b�h�l���}�C�i�X");
	}
	//�O���b�h��fx32�^�ɕύX
	outRect->X1 = grid_x1*16*FX32_ONE;
	outRect->Z1 = grid_z1*16*FX32_ONE;
	outRect->X2 = grid_x2*16*FX32_ONE;
	outRect->Z2 = grid_z2*16*FX32_ONE;
}

//==============================================================================
/**
 * �w��n�a�i�f�[�^�̍��W�ƁA�����`���r
 *
 * @param	inObjPtr	3D�I�u�W�F�N�g�f�[�^
 * @param	inX1		��`X���W�i���j
 * @param	inZ1		��`Z���W�i���j
 * @param	inX2		��`X���W�i�E�j
 * @param	inZ2		��`Z���W�i��O�j
 * @param	inTrans		�I�t�Z�b�g
 *
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL MPTL_Check3DObjIO(	const M3DO_CONST_PTR inObjPtr,
						const TARGET_RECT *inRect,
						const VecFx32 *inTrans)
{
	VecFx32 vec;
	
	vec = M3DO_GetGlobalVec(inObjPtr);
	vec.x += inTrans->x;
	vec.z += inTrans->z;
	if ( (inRect->X1<=vec.x) && (vec.x<=inRect->X2) &&
			(inRect->Z1<=vec.z) && (vec.z<=inRect->Z2) ){
		return TRUE;
	}
	return FALSE;
}

//==============================================================================
/**
 * �w���`���Ɏw��OBJ�����邩�𔻒�
 *
 * @param fsys				�t�B�[���h�V�X�e���|�C���^
 * @param inTargetObjID		OBJID
 * @param inRect			������`
 * @param outObjData		�q�b�g����OBJ�iNULL�j	
 *
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL MPTL_CheckMap3DObjInRect(	const FIELDSYS_WORK *fsys,
								const int inTargetObjID,
								const TARGET_RECT *inRect,
								M3DO_PTR *outObjData)
{
	u8 idx;
	M3DOL_PTR obj_data_list;

	for(idx=0;idx<4;idx++){
	
	//���[�J���C���f�b�N�X���擾
//	idx = GetNowLocalIndex(fsys->map_cont_dat);
		//�n�a�i���X�g���擾
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		//��`������
		{
			u8 i;
			VecFx32 trans;
			int block_idx;
			int map_w;
			BOOL rc;
			//block_idx = GetNowBlockIndex(fsys->map_cont_dat);
			block_idx = GetBlockIndexFromLocalIndex(fsys->map_cont_dat, idx);
			map_w = GetWorldMapMatrixW(fsys->World);
		
			MPTL_CalcMapOffset(block_idx, map_w, &trans);
			for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
				M3DO_PTR ptr;
				ptr = M3DO_GetMap3DObjData(obj_data_list, i);
				rc = MPTL_Check3DObjIO(	ptr,
										inRect,
										&trans);
				if (rc){
					int id;
					id = M3DO_GetObjID(ptr);
					if (id == inTargetObjID){
						if (outObjData != NULL)
						{
							*outObjData = ptr;
						}
						return TRUE;
					}
				}
			}//end for
		}
	}//end for
	return FALSE;
}

//==============================================================================
/**
 * �w���`���ɕ����w��OBJ�����邩�𔻒�
 *
 * @param fsys				�t�B�[���h�V�X�e���|�C���^
 * @param inTargetObjIDList	OBJID���X�g
 * @param inListNum			���X�g�v�f��
 * @param inRect			������`
 * @param outObjData		�q�b�g����OBJ	(NULL�j
 * @param outObjID			�q�b�g����OBJ�̊i�[�ꏊ�iNULL�j
 * 
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL MPTL_CheckPluralMap3DObjInRect(	const FIELDSYS_WORK *fsys,
										const int* inTargetObjIDList,
										const u8 inListNum,
										const TARGET_RECT *inRect,
										M3DO_PTR *outObjData,
										int *outObjID)
{
	u8 idx;
	M3DOL_PTR obj_data_list;

	for(idx=0;idx<4;idx++){
	
///	//���[�J���C���f�b�N�X���擾
///	idx = GetNowLocalIndex(fsys->map_cont_dat);
		//�n�a�i���X�g���擾
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		//��`������
		{
			u8 i;
			VecFx32 trans;
			int block_idx;
			int map_w;
			BOOL rc;
			//block_idx = GetNowBlockIndex(fsys->map_cont_dat);
			block_idx = GetBlockIndexFromLocalIndex(fsys->map_cont_dat, idx);
			map_w = GetWorldMapMatrixW(fsys->World);
		
			MPTL_CalcMapOffset(block_idx, map_w, &trans);
			for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
				M3DO_PTR ptr;
				ptr = M3DO_GetMap3DObjData(obj_data_list, i);
				rc = MPTL_Check3DObjIO(	ptr,
										inRect,
										&trans);
				if (rc){
					u8 j;
					int id;
					id = M3DO_GetObjID(ptr);
					for(j=0;j<inListNum;j++){
						if (id == inTargetObjIDList[j]){
							if (outObjData != NULL){
								(*outObjData) = ptr;
							}
							if (outObjID != NULL){
								*outObjID = id;
							}
							return TRUE;
						}
					}
				}
			}//end for
		}
	}//end for
	return FALSE;
}

//==============================================================================
/**
 * �w��OBJ�����邩�𔻒�
 * 
 * @param fsys				�t�B�[���h�V�X�e���|�C���^
 * @param inTargetObjID		OBJID
 * @param outObjData		��Ԏn�߂Ƀq�b�g����OBJ�iNULL�j
 * @param outBlockIdx		��Ԏn�߂Ƀq�b�g����OBJ�̂���u���b�N�C���f�b�N�X�iNULL�j
 * 
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL MPTL_CheckMap3DObj(const FIELDSYS_WORK *fsys,
						const int inTargetObjID,
						M3DO_PTR *outObjData,
						int *outBlockIdx)
{
	u8 idx;
	M3DOL_PTR obj_data_list;

	for(idx=0;idx<4;idx++){
		//�n�a�i���X�g���擾
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		{
			u8 i;
			for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
				M3DO_PTR ptr;
				ptr = M3DO_GetMap3DObjData(obj_data_list, i);
				{
					u8 j;
					int id;
					id = M3DO_GetObjID(ptr);
					if (id == inTargetObjID){
						if (outObjData != NULL){
							(*outObjData) = ptr;
						}
						if (outBlockIdx != NULL){
							(*outBlockIdx) = 
								GetBlockIndexFromLocalIndex(fsys->map_cont_dat, idx);
						}
						return TRUE;
					}
				}
			}//end for
		}
	}//end for
	return FALSE;
}

//==============================================================================
/**
 * �����w��OBJ�����邩�𔻒�
 *
 * @param fsys				�t�B�[���h�V�X�e���|�C���^
 * @param inTargetObjIDList	OBJID���X�g
 * @param inListNum			���X�g�v�f��
 * @param outObjData		�q�b�g����OBJ	(NULL�j
 * @param outObjID			�q�b�g����OBJ�̊i�[�ꏊ�iNULL�j
 * 
 * @return	BOOL	TRUE:HIT�@FALSE:NO HIT
 */
//==============================================================================
BOOL MPTL_CheckPluralMap3DObj(	const FIELDSYS_WORK *fsys,
								const int* inTargetObjIDList,
								const u8 inListNum,
								M3DO_PTR *outObjData,
								int *outObjID)
{
	u8 idx;
	M3DOL_PTR obj_data_list;

	for(idx=0;idx<4;idx++){
		//�n�a�i���X�g���擾
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		{
			u8 i;
			for(i=0;i<MAP_READ_OBJ_3D_MAX;i++){
				M3DO_PTR ptr;
				ptr = M3DO_GetMap3DObjData(obj_data_list, i);
				{
					u8 j;
					int id;
					id = M3DO_GetObjID(ptr);
					for(j=0;j<inListNum;j++){
						if (id == inTargetObjIDList[j]){
							if (outObjData != NULL){
								(*outObjData) = ptr;
							}
							if (outObjID != NULL){
								*outObjID = id;
							}
							return TRUE;
						}
					}
				}
			}//end for
		}
	}//end for
	return FALSE;
}

//==============================================================================
/**
 * �u���b�N�C���f�b�N�X����n�`�I�t�Z�b�g���v�Z
 *
 * @param   inBlockIndex	�u���b�N�C���f�b�N�X
 * @param   inMapW			�}�b�v��
 * @param   outTrans		�擾���W
 *
 * @return	none
 */
//==============================================================================
void MPTL_CalcMapOffset(const int inBlockIndex,
						const int inMapW,
						VecFx32 *outTrans)
{
	u16 x_ofs;
	u16 z_ofs;
	outTrans->x = (BLOCK_GRID_W/2)*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z = (BLOCK_GRID_H/2)*ONE_GRID_SIZE*FX32_ONE;	
	x_ofs = inBlockIndex % inMapW;
	z_ofs = inBlockIndex / inMapW;
	outTrans->x += x_ofs*BLOCK_GRID_W*ONE_GRID_SIZE*FX32_ONE;
	outTrans->z += z_ofs*BLOCK_GRID_H*ONE_GRID_SIZE*FX32_ONE;
}
