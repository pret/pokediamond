#include "map_tool.h"
#include "worldmap.h"
#include "div_map.h"
#include "fieldsys.h"
#include "field_gimmick.h"

#include "fielddata/mapattr/map_attr.h"

#include "debug_saito.h"

#define HIT_ATTR_MASK	(0x1)
#define LSB_MASK		(0xff)

#define MOVE_HEIGHT_DEF	(20*FX32_ONE)	//20ユニット (1.5グリッド＝24ユニットだと、誤差が出たときに対応が難しいので、切り詰めました)
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
 * 2つの値の差分を返す(正値)
 *
 * @param   inVal1	値1つ目
 * @param	inVal2	値2つ目
 *
 * @retval  fx32	差分値
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
 * 高さ取得
 *
 * @param   fsys	フィールドシステムポインタ
 * @param	inPos	座標
 *
 * @retval  MAP_RESOURCE_PTR	確保したMAPRESOURCEのポインタ
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
		
		//現在ブロックを計算
		grid_x = inX/(16*FX32_ONE);
		grid_z = inZ/(16*FX32_ONE);

		//拡張高さデータを調べる
		ex_rc = EXH_HitCheckExHeight(grid_x, grid_z, fsys->ExHeightList, &index);

		block_x = grid_x / BLOCK_GRID_W;
		block_z = grid_z / BLOCK_GRID_H;
		block_index = block_x+block_z*map_w;
	
		//自機座標にブロックオフセット分を減算
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
			//高さ取得
			{
				MHI_CONST_PTR  height_info = GetDivMapHeightInfo(map_data_ptr,local_index);
				///OS_Printf_saitou("local_idx=%d\n",local_index);
				normal_rc = GetHeightForBlock(inNowHeight, target.x, target.z, height_info, &target.y);
			}
		}
	}

	if (ex_rc){
		fx32 ex_height;
		//拡張高さデータ取得
		ex_height = EXH_GetExHeight(index, fsys->ExHeightList);
		if (normal_rc){
			OS_Printf_saitou("local_print ex_nor=%x,%x\n",ex_height,target.y);
			//どちらを採用するかをチェック
			//高いほうを調べる
			if (ex_height<=target.y){
				//通常の方が高い場合はそれを採用
///				rc = TRUE;
///				ioPos->y = target.y;
				code = HEIGHT_NORMAL;
				height = target.y;
			}else{
				fx32 sub1,sub2;
				OS_Printf_saitou("local_print ex,target,now=%x,%x,%x\n",ex_height,target.y,height);
				//拡張の方が高い場合は指定高さに近いほうを採用
				sub1 = GetSubVal(target.y, inNowHeight);	//通常高さと現在値の差
				sub2 = GetSubVal(ex_height, inNowHeight);	//拡張高さと現在値の差
				OS_Printf_saitou("local_print 差分%x,%x\n",sub1,sub2);
				if (sub1 <= sub2){
					//通常高さを採用
///					ioPos->y = target.y;
					height = target.y;
					code = HEIGHT_NORMAL;
				}else{
					//拡張高さを採用
				OS_Printf_saitou("local_print 拡張高さを採用\n");
///					ioPos->y = ex_height;
					height = ex_height;
					code = HEIGHT_EXPAND;
				}
///				rc = TRUE;
			}
		}else{
			//拡張高さデータのみにヒット
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
	
	//グリッドに変換
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
	
	//高さは０をセット
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
			u32 local_grid_index;	//0～1023
			u16 const *attribute;
			local_grid_index = (inZ % BLOCK_GRID_H)*BLOCK_GRID_W+(inX % BLOCK_GRID_W);
			
			//OS_Printf_saitou("local_grid_index = %d\n",local_grid_index);
			//アトリビュート取得
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

		//fsysにぶら下がる地下マッピングデータ（30ｘ30）にグリッドナンバーを投げて。０～１９の対応インデックスをもらう
		//under_index = fsys->under_map[grid_no];
		{
			u32 local_grid_index;	//0～1023
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
 * あたり検出
 *
 * @param   fsys	フィールドシステムポインタ
 * @param	inX	グリッドX座標
 * @param	inZ	グリッドZ座標
 *
 * @retval  BOOL	TRUE:進入不可	FALSE:進入可
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
 * アトリビュート取得(2バイト)
 *
 * @param	*fsys	フィールドシステムポインタ
 * @param	inX		Xグリッド座標
 * @param	inZ		Zグリッド座標
 *
 * @return	attrbute	アトリビュート　失敗の場合は0を返す
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
	//取得失敗
	return 0;
}

//==============================================================================
/**
 * アトリビュート取得(下位1バイト)
 *
 * @param	*fsys	フィールドシステムポインタ
 * @param	inX		Xグリッド座標
 * @param	inZ		Zグリッド座標
 *
 * @return	attrbute	アトリビュート　失敗の場合は0を返す
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
	//取得失敗
	return MATTR_NO_ATTR;
}

//==============================================================================
/**
 * アトリビュート取得(上位1バイト)
 *
 * @param	*fsys	フィールドシステムポインタ
 * @param	inX		Xグリッド座標
 * @param	inZ		Zグリッド座標
 *
 * @return	attrbute	アトリビュート　失敗の場合は0を返す
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
	//取得失敗
	return 0;
}



//==============================================================================
/**
 * 高さ取得
 *
 * @param	*ioHeroPoint	自機座標
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
 * 高さ取得
 *
 * @param	*ioHeroPoint	自機座標
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
 * 高さ取得
 *
 * @param	*ioHeroPoint	自機座標
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
		//現在ブロックを計算
		grid_x = inX/(16*FX32_ONE);
		grid_z = inZ/(16*FX32_ONE);
		
		//拡張高さデータを調べる
		ex_rc = EXH_HitCheckExHeight(grid_x, grid_z, fsys->ExHeightList, &index);

		if (ex_rc){
			//拡張高さデータ取得
			ex_height = EXH_GetExHeight(index, fsys->ExHeightList);
			OS_Printf_saitou("local_print ex_nor=%x,%x\n",ex_height,height);
			//どちらを採用するかをチェック
			//高いほうを調べる
			if (ex_height<=height){
				//通常の方が高い場合はそれを採用
				code = HEIGHT_NORMAL;
				return_height = height;
			}else{
				fx32 sub1,sub2;
				OS_Printf_saitou("local_print ex,target,now=%x,%x,%x\n",ex_height,height,inNowY);
				//拡張の方が高い場合は指定高さに近いほうを採用
				sub1 = GetSubVal(height, inNowY);	//通常高さと現在値の差
				sub2 = GetSubVal(ex_height, inNowY);	//拡張高さと現在値の差
				OS_Printf_saitou("local_print 差分%x,%x\n",sub1,sub2);
				if (sub1 <= sub2){
					//通常高さを採用
					return_height = height;
					code = HEIGHT_NORMAL;
				}else{
					//拡張高さを採用
				OS_Printf_saitou("local_print 拡張高さを採用\n");
					return_height = ex_height;
					code = HEIGHT_EXPAND;
				}
			}
		}else{
			//拡張高さデータのみにヒット
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
 * 現在の高さと指定の高さから段差であるかを調べる
 *
 * @param	fsys		フィールドシステムポインタ	
 * @param	inVec		現在座標
 * @param	inGridX		指定グリッド座標X
 * @param	inGridZ		指定グリッド座標Z
 * @param	outCode		どの高さデータにヒットしたかのチェック用（通常、拡張、高さなし）
 *
 * @return	1:高い	-1:低い		0:同じ
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
	
	//指定グリッドの高さを取得
	//グリッドをFX32型にする(グリッドの中心座標)
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
	//現在の高さと比較
	if(height < inVec->y){		//指定グリッドのほうが低い
		y_high = inVec->y;
		y_low = height;
		rc = HIT_RES_TOO_LOW;
	}else if(height > inVec->y){	//指定グリッドのほうが高い
		y_high = height;
		y_low = inVec->y;
		rc = HIT_RES_TOO_HEIGH;
	}else{							//同じ
		rc = HIT_RES_EQUAL;
		return rc;
	}

	//段差とみなされるかを判定
	if (y_high-y_low >= MOVE_HEIGHT_DEF){
		GF_ASSERT(rc!=0 && "戻り値が不正");
		//規定値以外なので、段差とみなす
	}else{
		rc = HIT_RES_EQUAL;			//規定値以内なので、段差とはみなさない
	}
	
	return rc;
}

//==============================================================================
/**
 * 高さを加味したヒット判定
 *
 * @param	fsys		フィールドシステムポインタ	
 * @param	inVec		現在座標
 * @param	inGridX		指定グリッド座標X
 * @param	inGridZ		指定グリッド座標Z
 * @param	outFlg		判定結果を格納するバッファ
 *
 * @return	BOOL	TRUE:進入不可　FALSE:進入可
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
		//進入可能ならば、アトリビュートによるヒット判定を行う
		hit = GetHitAttr(fsys, inGridX, inGridZ);
		if ((!hit)&&(code==HEIGHT_EXPAND)){
			//アトリビュートヒットでも進入可能、かつ、拡張高さデータを取得した場合
			//水なら入れないチェックを行う
			MATR attr = GetAttributeLSB( fsys, inGridX, inGridZ );
			if (MATR_IsWaterNoIn(attr)){	//拡張高さで、水なら入れないアトリビュートのとき
				return TRUE;//進入不可
			}
		}
		return hit;
	}else{
		return TRUE;		//当たりアリ。進入不可
	}
}

//==============================================================================
/**
 * 高さを加味したヒット判定　外部当たり判定も行う
 *
 * @param	fsys		フィールドシステムポインタ	
 * @param	inVec		現在座標
 * @param	inGridX		指定グリッド座標X
 * @param	inGridZ		指定グリッド座標Z
 * @param	outFlg		判定結果を格納するバッファ
 *
 * @return	BOOL	TRUE:進入不可　FALSE:進入可
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
		
	//進入可能ならば、アトリビュートによるヒット判定を行う
	if (check == HIT_RES_EQUAL){
		BOOL hit;
		BOOL ex_rc;
		//始めに外部当たり判定を行う
		ex_rc = FLDGMK_FieldGimmickHitCheck(fsys, inGridX, inGridZ,
											inVec->y, &hit);
		//外部当たり判定を行わなかったときのみ通常判定に移行する
		if (!ex_rc){	
			hit = GetHitAttr(fsys, inGridX, inGridZ);
			if ((!hit)&&(code==HEIGHT_EXPAND)){
				//アトリビュートヒットでも進入可能、かつ、拡張高さデータを取得した場合
				//水なら入れないチェックを行う
				MATR attr = GetAttributeLSB( fsys, inGridX, inGridZ );
				if (MATR_IsWaterNoIn(attr)){	//拡張高さで、水なら入れないアトリビュートのとき
					return TRUE;//進入不可
				}
			}
			return hit;
		}else{
			return hit;
		}
	}else{
		return TRUE;		//当たりアリ。進入不可
	}
}


//==============================================================================
/**
 * 指定グリッド座標の上６グリッド分の矩形の左上、右下座標を算出する
 *
 * @param	inGridX		指定グリッドX座標
 * @param	inGridZ		指定グリッドZ座標
 * @param	inDir		方向
 * @param	outX1		矩形X座標（左）
 * @param	outZ1		矩形Z座標（奥）
 * @param	outX2		矩形X座標（右）
 * @param	outZ2		矩形Z座標（手前）
 *
 * @return	none
 */
//==============================================================================
void MPTL_GetTargetRect(const int inGridX, const int inGridZ,
						const int inDir, TARGET_RECT *outRect )
{
	int grid_x1,grid_z1,grid_x2,grid_z2;
///	switch(inDir){
///	case 0:					//上方向
		//対象左上グリッド
		grid_x1 = inGridX-1;
		grid_z1 = inGridZ-2;
		//対象右下グリッド
		grid_x2 = inGridX+1;
		grid_z2 = inGridZ;
///		break;
///	default:
///		break;
///	}

	if (grid_x1<0 || grid_z1<0 || grid_x2<0 || grid_z2<0){
		GF_ASSERT(0&&"ERROR:グリッド値がマイナス");
	}
	//グリッドをfx32型に変更
	outRect->X1 = grid_x1*16*FX32_ONE;
	outRect->Z1 = grid_z1*16*FX32_ONE;
	outRect->X2 = (grid_x2+1)*16*FX32_ONE;
	outRect->Z2 = (grid_z2+1)*16*FX32_ONE;
}

//==============================================================================
/**
 * 指定グリッド座標を基点として、矩形を作成
 *
 * @param	inGridX		指定グリッドX座標
 * @param	inGridZ		指定グリッドZ座標
 * @param	inX			基点からのオフセット　矩形X座標（左開始）
 * @param	inZ			基点からのオフセット　矩形Z座標（奥開始）
 * @param	inW			矩形横幅
 * @param	inH			矩形縦幅
 * @param	outX1		矩形X座標（左）
 * @param	outZ1		矩形Z座標（奥）
 * @param	outX2		矩形X座標（右）
 * @param	outZ2		矩形Z座標（手前）
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
	//対象左上グリッド
	grid_x1 = inGridX+inOfsX;
	grid_z1 = inGridZ+inOfsZ;
	//対象右下グリッド
	grid_x2 = grid_x1+inW;
	grid_z2 = grid_z1+inH;

	if (grid_x1<0 || grid_z1<0 || grid_x2<0 || grid_z2<0){
		GF_ASSERT(0&&"ERROR:グリッド値がマイナス");
	}
	//グリッドをfx32型に変更
	outRect->X1 = grid_x1*16*FX32_ONE;
	outRect->Z1 = grid_z1*16*FX32_ONE;
	outRect->X2 = grid_x2*16*FX32_ONE;
	outRect->Z2 = grid_z2*16*FX32_ONE;
}

//==============================================================================
/**
 * 指定ＯＢＪデータの座標と、判定矩形を比較
 *
 * @param	inObjPtr	3Dオブジェクトデータ
 * @param	inX1		矩形X座標（左）
 * @param	inZ1		矩形Z座標（奥）
 * @param	inX2		矩形X座標（右）
 * @param	inZ2		矩形Z座標（手前）
 * @param	inTrans		オフセット
 *
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
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
 * 指定矩形内に指定OBJがあるかを判定
 *
 * @param fsys				フィールドシステムポインタ
 * @param inTargetObjID		OBJID
 * @param inRect			検索矩形
 * @param outObjData		ヒットしたOBJ（NULL可）	
 *
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
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
	
	//ローカルインデックスを取得
//	idx = GetNowLocalIndex(fsys->map_cont_dat);
		//ＯＢＪリストを取得
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		//矩形内判定
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
 * 指定矩形内に複数指定OBJがあるかを判定
 *
 * @param fsys				フィールドシステムポインタ
 * @param inTargetObjIDList	OBJIDリスト
 * @param inListNum			リスト要素数
 * @param inRect			検索矩形
 * @param outObjData		ヒットしたOBJ	(NULL可）
 * @param outObjID			ヒットしたOBJの格納場所（NULL可）
 * 
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
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
	
///	//ローカルインデックスを取得
///	idx = GetNowLocalIndex(fsys->map_cont_dat);
		//ＯＢＪリストを取得
		Get3DObjListFromLocalIdx(idx, fsys->map_cont_dat, &obj_data_list);
		//矩形内判定
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
 * 指定OBJがあるかを判定
 * 
 * @param fsys				フィールドシステムポインタ
 * @param inTargetObjID		OBJID
 * @param outObjData		一番始めにヒットしたOBJ（NULL可）
 * @param outBlockIdx		一番始めにヒットしたOBJのあるブロックインデックス（NULL可）
 * 
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
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
		//ＯＢＪリストを取得
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
 * 複数指定OBJがあるかを判定
 *
 * @param fsys				フィールドシステムポインタ
 * @param inTargetObjIDList	OBJIDリスト
 * @param inListNum			リスト要素数
 * @param outObjData		ヒットしたOBJ	(NULL可）
 * @param outObjID			ヒットしたOBJの格納場所（NULL可）
 * 
 * @return	BOOL	TRUE:HIT　FALSE:NO HIT
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
		//ＯＢＪリストを取得
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
 * ブロックインデックスから地形オフセットを計算
 *
 * @param   inBlockIndex	ブロックインデックス
 * @param   inMapW			マップ幅
 * @param   outTrans		取得座標
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
