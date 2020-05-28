//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		range_data.c
 *	@brief		���z�f�[�^�擾�֐�
 *	@author		tomoya takahashi 
 *	@data		2006.02.11
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "system/arc_util.h"
#include "system/arc_tool.dat"

#include "gflib/clact.h"

#include "include/poketool/monsno.h"
#include "src/application/zukanlist/zkn_data/zukan_enc_diamond.naix"
#include "include/application/zukanlist/zkn_version.h"

#define __ZKN_RANGE_DATA_H_GLOBAL
#include "include/application/zukanlist/zkn_range_data.h"

//-----------------------------------------------------------------------------
/**
 *					�R�[�f�B���O�K��
 *		���֐���
 *				�P�����ڂ͑啶������ȍ~�͏������ɂ���
 *		���ϐ���
 *				�E�ϐ�����
 *						const�ɂ� c_ ��t����
 *						static�ɂ� s_ ��t����
 *						�|�C���^�ɂ� p_ ��t����
 *						�S�č��킳��� csp_ �ƂȂ�
 *				�E�O���[�o���ϐ�
 *						�P�����ڂ͑啶��
 *				�E�֐����ϐ�
 *						�������Ɓh�Q�h�Ɛ������g�p���� �֐��̈���������Ɠ���
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	�|�P�������z�f�[�^�e�^�C�v�J�n�i���o�[
//=====================================
#define ZKN_RANGEDATA_DAN_MORNING_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_morning_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_NOON_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_noon_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_NIGHT_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_night_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_MORNING_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_morning_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_NOON_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_noon_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_NIGHT_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_night_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_SPECIAL_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_special_mons_000_mrang)
#define ZKN_RANGEDATA_DAN_SPECIAL_COMP_ARC_S	(NARC_zukan_enc_diamond_zkn_dan_range_special_comp_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_SPECIAL_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_special_mons_000_mrang)
#define ZKN_RANGEDATA_FLD_SPECIAL_COMP_ARC_S	(NARC_zukan_enc_diamond_zkn_fld_range_special_comp_mons_000_mrang)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
static int ZknRangeDataZoneLinkIdGet( int zone_id, int arc_dataidx, int heap );



//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[���z�f�[�^�擾
 *
 *	@param	p_inbuff		�f�[�^�i�[��
 *	@param	mons_no			�����X�^�[�i���o�[
 *	@param	type			���z�^�C�v
 *	@param	heap			�g�p�q�[�v
 */
//-----------------------------------------------------------------------------
void ZKN_RANGEDATA_GetMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff, int mons_no, int type, int heap )
{
	int arc_start;
	u32 data_size;
	
	switch( type ){
	// �_���W�������z�f�[�^
	case ZKN_RANGEDATA_TYPE_DAN_MORNING:
		arc_start = ZKN_RANGEDATA_DAN_MORNING_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_NOON:
		arc_start = ZKN_RANGEDATA_DAN_NOON_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_NIGHT:
		arc_start = ZKN_RANGEDATA_DAN_NIGHT_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_SPECIAL:
		arc_start = ZKN_RANGEDATA_DAN_SPECIAL_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_DAN_SPECIAL_COMP:
		arc_start = ZKN_RANGEDATA_DAN_SPECIAL_COMP_ARC_S;
		break;
	
	// �t�B�[���h���z�f�[�^
	case ZKN_RANGEDATA_TYPE_FLD_MORNING:
		arc_start = ZKN_RANGEDATA_FLD_MORNING_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_NOON:
		arc_start = ZKN_RANGEDATA_FLD_NOON_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_NIGHT:
		arc_start = ZKN_RANGEDATA_FLD_NIGHT_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_SPECIAL:
		arc_start = ZKN_RANGEDATA_FLD_SPECIAL_ARC_S;
		break;
	case ZKN_RANGEDATA_TYPE_FLD_SPECIAL_COMP:
		arc_start = ZKN_RANGEDATA_FLD_SPECIAL_COMP_ARC_S;
		break;
	}
	
	// �A�[�J�C�u����ǂݍ���
	p_inbuff->p_rangeid = (int *)ArcUtil_LoadEx( ZKN_ARC_DAT, arc_start + mons_no, FALSE, heap, ALLOC_TOP, &data_size );
	
	// �f�[�^�T�C�Y����z��v�f�����󂯎��
	p_inbuff->num = data_size / sizeof(int);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[�i���o�[���z�f�[�^�j��
 *
 *	@param	p_inbuff 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGEDATA_DeleteMonsNoRange( ZKN_RANGE_DATA_MONS* p_inbuff )
{
	GF_ASSERT( p_inbuff );
	GF_ASSERT( p_inbuff->p_rangeid );
	
	sys_FreeMemoryEz( p_inbuff->p_rangeid );
	p_inbuff->p_rangeid = NULL;
	p_inbuff->num = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�]�[��ID�ɑΉ�����_���W�������zID���擾
 *
 *	@param	zone_id	�]�[��ID
 *	@param	heap	�q�[�v
 *
 *	@retval	ZKN_DAN_ID_NONE		�Ή�����ID�Ȃ�
 *	@retval	���̑�				�Ή�����ID
 */
//-----------------------------------------------------------------------------
int ZKN_RANGEDATA_GetZoneIDLinkDanRangeID( int zone_id, int heap )
{
	return ZknRangeDataZoneLinkIdGet( zone_id, NARC_zukan_enc_diamond_zkn_dan_id_rzidlink, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�]�[��ID�ɑΉ�����t�B�[���h���zID���擾
 *
 *	@param	zone_id	�]�[��ID
 *	@param	heap	�q�[�v
 *
 *	@retval	ZKN_FLD_ID_NONE		�Ή�����ID�Ȃ�
 *	@retval	���̑�				�Ή�����ID
 */
//-----------------------------------------------------------------------------
int ZKN_RANGEDATA_GetZoneIDLinkFldRangeID( int zone_id, int heap )
{
	return ZknRangeDataZoneLinkIdGet( zone_id, NARC_zukan_enc_diamond_zkn_fld_id_rzidlink, heap );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�_���W�����O���b�h���W�f�[�^�擾
 *
 *	@param	heap		�q�[�v
 *	@param	p_num		�f�[�^�z��v�f���i�[��	int�̕ϐ�	(NULL�L��)
 *			���̒l��ZKN_DAN_ID_MAX�Ɠ���
 *
 *	@return	�z��	�j���͊e��
 */
//-----------------------------------------------------------------------------
ZKN_RANGE_DATA_DAN_GRID* ZKN_RANGEDATA_GetDanGridOamData( int heap, int* p_num )
{
	ZKN_RANGE_DATA_DAN_GRID* p_buff;
	u32 data_size;

	
	// �A�[�J�C�u����ǂݍ���
	p_buff = (ZKN_RANGE_DATA_DAN_GRID*)ArcUtil_LoadEx( ZKN_ARC_DAT, NARC_zukan_enc_diamond_zkn_dan_griddata_dangri, FALSE, heap, ALLOC_TOP, &data_size );


	// �f�[�^�T�C�Y����z��p�����擾
	if( p_num ){
		*p_num = data_size / sizeof(ZKN_RANGE_DATA_DAN_GRID);
	}

	return p_buff;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�t�B�[���h�O���b�h���n�`�f�[�^�擾
 *
 *	@param	heap		�q�[�v
 *	@param	p_num		�f�[�^�z��v�f���i�[��	int �̕ϐ��@�iNULL�L���j
 *			���̒l��ZKN_FLD_ID_MAX�Ɠ���
 *	
 *	@return	�z��@�j���͊e��
 */
//-----------------------------------------------------------------------------
ZKN_RANGE_DATA_FLD_GRID* ZKN_RANGEDATA_GetFldGridAraaData( int heap, int* p_num )
{
	ZKN_RANGE_DATA_FLD_GRID* p_buff;
	u32 data_size;

	
	// �A�[�J�C�u����ǂݍ���
	p_buff = (ZKN_RANGE_DATA_FLD_GRID*)ArcUtil_LoadEx( ZKN_ARC_DAT, NARC_zukan_enc_diamond_zkn_fld_griddata_fldgri, FALSE, heap, ALLOC_TOP, &data_size );


	// �f�[�^�T�C�Y����z��p�����擾
	if( p_num ){
		*p_num = data_size / sizeof(ZKN_RANGE_DATA_FLD_GRID);
	}

	return p_buff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�t�B�[���h���z�}�f�[�^����������
 *
 *	@param	p_buff			�������ݐ�o�b�t�@
 *	@param	buff_x			�o�b�t�@���T�C�Y
 *	@parm	buff_y			�o�b�t�@���T�C�Y
 *	@param	cp_write_data	�������݃f�[�^	(�ϐ��̃|�C���^)
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGE_DATA_FldGridDataWrite( u8* p_buff, u8 buff_x, u8 buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data )
{
	int i,j;	// ���[�v

	GF_ASSERT( (cp_write_data->gridy + cp_write_data->sizey) < buff_y );
	GF_ASSERT( (cp_write_data->gridx + cp_write_data->sizex) < buff_x );

	for( i=cp_write_data->gridy; i<cp_write_data->gridy + cp_write_data->sizey; i++ ){

		for( j=cp_write_data->gridx; j<cp_write_data->gridx + cp_write_data->sizex; j++ ){

			p_buff[ (i*buff_x) + j ] |= cp_write_data->arry[ ((i-cp_write_data->gridy) * cp_write_data->sizex) + (j-cp_write_data->gridx)  ];
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�����X�^�[���z�f�[�^�̃t�B�[���h���z�}�b�v���쐬
 *
 *	@param	p_buff				�i�[��
 *	@param	buff_x				�i�[��o�b�t�@���T�C�Y
 *	@param	buff_y				�i�[��o�b�t�@���T�C�Y
 *	@param	cp_write_data		�t�B�[���h�n�`�f�[�^�i�z��j
 *	@param	cp_mons_range		�����X�^�[���z�f�[�^
 *	@param	cp_cut_rangeid		�r�����镪�zID�@�z��
 *	@param	cut_tbl_num			�r������ID�z��
 *
 *	@return	���ۂ̃f�[�^��	�r���z��Ŕr�������\�������邽��
 */
//-----------------------------------------------------------------------------
u32 ZKN_RANGE_DATA_FldGridDataWriteMonsRangeData( u8* p_buff, int buff_x, int buff_y, const ZKN_RANGE_DATA_FLD_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, const u8* cp_cut_randeid, u32 cut_tbl_num )
{
	int i;	// ���[�v�p
	int j;
	u32 count = 0;

	for( i=0; i<cp_mons_range->num - 1; i++ ){	// �����X�^�[���z�Ō�̓_�~�[

		GF_ASSERT( cp_mons_range->p_rangeid[i] );	// 0�͂�������

		// ���O�`�F�b�N
		for( j = 0; j < cut_tbl_num; j++ ){
			if( cp_mons_range->p_rangeid[i] == cp_cut_randeid[j] ){
				break;
			}
		}

		// �r���ȊO�Ȃ珑��
		if( j >= cut_tbl_num ){
			ZKN_RANGE_DATA_FldGridDataWrite( p_buff, buff_x, buff_y,
					&cp_write_data[ cp_mons_range->p_rangeid[i] ] );
			count ++;
		}
	}

	return count;
}


//----------------------------------------------------------------------------
/**
 *	@brief	�_���W�������W��OAM�A�N�^�[�ɐݒ�
 *
 *	@param	p_act			�A�N�^�[
 *	@param	ofs_x			�������ލ��W�l
 *	@param	ofs_y			�������ލ��W�l
 *	@param	gridsizex		�O���b�h���T�C�Y
 *	@param	gridsizey		�O���b�h���T�C�Y
 *	@param	cp_write_data	�_���W�������
 *	@param	norm_seq		�ʏ�A�j���V�[�P���X
 *	@param	sp_seq			����A�j���V�[�P���X
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_RANGE_DATA_DanGridDataSet( CLACT_WORK_PTR p_act, int ofsx, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, int norm_seq, int sp_seq )
{
	VecFx32 mat;

	mat.x = (cp_write_data->gridx * gridsizex) + ofsx;
	mat.y = (cp_write_data->gridy * gridsizey) + ofsy;
	mat.x <<= FX32_SHIFT;
	mat.y <<= FX32_SHIFT;
	
	CLACT_SetMatrix( p_act, &mat );


	// ����OAM�ݒ�
	if( cp_write_data->oam_flg ){
		CLACT_AnmChg( p_act, sp_seq );
	}else{
		CLACT_AnmChg( p_act, norm_seq );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�_���W�������WOAM�ݒ�֐�
 *
 *	@param	pp_act				�A�N�^�[�z��
 *	@param	use_start			�g�p�J�n
 *	@param	act_max				�A�N�^�[�z��v�f��
 *	@param	ofs_x				�������ލ��W�l
 *	@param	ofs_y				�������ލ��W�l
 *	@param	gridsizex			�P�O���b�hX�T�C�Y
 *	@param	gridsizey			�P�O���b�hY�T�C�Y
 *	@param	cp_write_data		�_���W�����O���b�h�f�[�^�z��
 *	@param	cp_mons_range		�����X�^�[���z�f�[�^
 *	@param	norm_seq		�ʏ�A�j���V�[�P���X
 *	@param	sp_seq				����OAM�̏ꍇ�̃A�j���V�[�P���X
 *	@param	cp_cut_rangeid		�r�����镪�zID�@�z��
 *	@param	cut_tbl_num			�r������ID�z��
 *	@param	p_count				���ۂ̃f�[�^��	�r���z��Ŕr�������\�������邽�� �i�[��
 *
 *	@return	�g�p�A�N�^�[��
 */
//-----------------------------------------------------------------------------
int ZKN_RANGE_DATA_DanGridDataSetMonsRangeData( CLACT_WORK_PTR* pp_act, int use_start, int act_max, int ofs_x, int ofsy, int gridsizex, int gridsizey, const ZKN_RANGE_DATA_DAN_GRID* cp_write_data, const ZKN_RANGE_DATA_MONS* cp_mons_range, int norm_seq, int sp_seq, const u8* cp_cut_randeid, u32 cut_tbl_num, u32* p_count )
{
	int i, j;
	int act_count = use_start;
	int count = 0;

	for( i=0; i<cp_mons_range->num - 1; i++ ){	// �����X�^�[���z�Ō�̓_�~�[

		GF_ASSERT( cp_mons_range->p_rangeid[i] );
		GF_ASSERT( act_count < act_max );

		// ���O�`�F�b�N
		for( j = 0; j < cut_tbl_num; j++ ){
			if( cp_mons_range->p_rangeid[i] == cp_cut_randeid[j] ){
				break;
			}
		}

		// �r���ȊO�Ȃ珑��
		if( j >= cut_tbl_num ){
		
			ZKN_RANGE_DATA_DanGridDataSet( pp_act[act_count], ofs_x, ofsy, gridsizex, gridsizey, &cp_write_data[ cp_mons_range->p_rangeid[i] ], norm_seq, sp_seq );
			act_count++;
			count ++;
		}

	}

	*p_count = count;

	return act_count;
}

//-----------------------------------------------------------------------------
/**
 *
 *		[�v���C�x�[�g�֐�]
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	�]�[��ID�ɑΉ�����ID��Ԃ�
 *
 *	@param	zone_id		�]�[��ID
 *	@param	arc_dataidx	�A�[�J�C�u�f�[�^IND	�i�_���W����Link�f�[�^OR�t�B�[���hLINK�f�[�^�j
 *	@param	heap		�q�[�v
 *
 *	@return	�Ή�����ID
 */
//-----------------------------------------------------------------------------
static int ZknRangeDataZoneLinkIdGet( int zone_id, int arc_dataidx, int heap )
{
	int* p_buff;
	u32 data_size;
	int num;
	int i;
	int ret;
	
	GF_ASSERT( (arc_dataidx == NARC_zukan_enc_diamond_zkn_dan_id_rzidlink)||
			(arc_dataidx == NARC_zukan_enc_diamond_zkn_fld_id_rzidlink) );
	
	// �A�[�J�C�u����ǂݍ���
	p_buff = (int *)ArcUtil_LoadEx( ZKN_ARC_DAT, arc_dataidx, FALSE, heap, ALLOC_BOTTOM, &data_size );
	
	// �f�[�^�T�C�Y����z��v�f�����󂯎��
	num = data_size / sizeof(int);

	// ������Ȃ��Ƃ���0��Ԃ��Ƃ��ꂼ��̕��zID��NONE�萔�ɂȂ�
	ret = 0;
	// ���[�v	�ꏏ�̃i���o�[���������炻�̔z��̗v�f�������zID
	for( i=0; i<num; i++ ){
		if( p_buff[i] == zone_id ){

			ret = i;
			break;
		}
	}

	sys_FreeMemoryEz( p_buff );
	return ret;
}
