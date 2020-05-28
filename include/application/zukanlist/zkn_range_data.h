//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_range_data.h
 *	@brief		���z�f�[�^�擾�֐�
 *	@author		tomoya takahashi	
 *	@data		2006.02.11
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_RANGE_DATA_H__
#define __ZKN_RANGE_DATA_H__

#include "src/application/zukanlist/zkn_data/zkn_rangeid.h"

#undef GLOBAL
#ifdef	__ZKN_RANGE_DATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
#define ZKN_RANGEDATA_FLD_GRID_ARRY_SIZE	( 32 )

//-------------------------------------
//	���z�f�[�^�^�C�v	
//=====================================
enum{
	// �_���W�������z�f�[�^
	ZKN_RANGEDATA_TYPE_DAN_MORNING = 0,
	ZKN_RANGEDATA_TYPE_DAN_NOON,
	ZKN_RANGEDATA_TYPE_DAN_NIGHT,
	ZKN_RANGEDATA_TYPE_DAN_SPECIAL,
	ZKN_RANGEDATA_TYPE_DAN_SPECIAL_COMP,
	
	// �t�B�[���h���z�f�[�^
	ZKN_RANGEDATA_TYPE_FLD_MORNING,
	ZKN_RANGEDATA_TYPE_FLD_NOON,
	ZKN_RANGEDATA_TYPE_FLD_NIGHT,
	ZKN_RANGEDATA_TYPE_FLD_SPECIAL,
	ZKN_RANGEDATA_TYPE_FLD_SPECIAL_COMP,
};

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�|�P�����i���o�[���z�f�[�^�f�[�^
//	(�ŏI�v�f��NONE)
//=====================================
typedef struct {
	int * p_rangeid;	// ���zID�̓������z��
	int num;			// �z��v�f��
} ZKN_RANGE_DATA_MONS;

//-------------------------------------
//	�_���W�����O���b�h���W�@OAM�̎�ރf�[�^
//=====================================
typedef struct {
	u8 gridx;
	u8 gridy;
	u8 oam_flg;
	u8 dummy;
} ZKN_RANGE_DATA_DAN_GRID;

//-------------------------------------
//	�t�B�[���h�n�`�f�[�^
//=====================================
typedef struct {
	u8 gridx;
	u8 gridy;
	u8 sizex;
	u8 sizey;
	u8 arry[ZKN_RANGEDATA_FLD_GRID_ARRY_SIZE];
} ZKN_RANGE_DATA_FLD_GRID;

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL void ZKN_RANGEDATA_GetMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff, int mons_no, int type, int heap );
GLOBAL void ZKN_RANGEDATA_DeleteMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff );

GLOBAL int ZKN_RANGEDATA_GetZoneIDLinkDanRangeID( int zone_id, int heap );
GLOBAL int ZKN_RANGEDATA_GetZoneIDLinkFldRangeID( int zone_id, int heap );

GLOBAL ZKN_RANGE_DATA_DAN_GRID* ZKN_RANGEDATA_GetDanGridOamData( int heap, int* p_num );
GLOBAL ZKN_RANGE_DATA_FLD_GRID* ZKN_RANGEDATA_GetFldGridAraaData( int heap, int* p_num );

GLOBAL void ZKN_RANGE_DATA_FldGridDataWrite( u8* p_buff, u8 buff_x, u8 buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data );

GLOBAL u32 ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( u8* p_buff, int buff_x, int buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, const u8* cp_cut_randeid, u32 cut_tbl_num );


GLOBAL void ZKN_RANGE_DATA_DanGridDataSet( CLACT_WORK_PTR p_act, int ofsx, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, int norm_seq, int sp_seq );
GLOBAL int ZKN_RANGE_DATA_DanGridDataSetMonsRangeData( CLACT_WORK_PTR* pp_act, int use_start, int act_max, int ofs_x, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, int norm_seq, int sp_seq, const u8* cp_cut_randeid, u32 cut_tbl_num, u32* p_count );


#undef	GLOBAL
#endif		// __ZKN_RANGE_DATA_H__

