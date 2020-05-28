/*---------------------------------------------------------------------------*
  Project:  
  File:     calc2d.c
 *---------------------------------------------------------------------------*/
#include <nnsys.h>
#define	__CALC2D_H_GLOBAL
#include "calc2d.h"

//---------------------------------------------------------------------------------------------------------
/**
 *  �O�ς��g�p���Ďw����W���w��x�N�g���̍��E�ǂ���ɂ��邩�𔻒�
 *  @param  *inS_Vec        �x�N�g���n�_
 *  @param  *inE_Vec        �x�N�g���I�_
 *  @param  *inT_Vec        �w����W
 *
 *  @retval int         1:�\�i�x�N�g������܂ށj�@0:��
*/
//---------------------------------------------------------------------------------------------------------
int BG2D_VectorSideS32( const Vec2DS32 *inS_Vec, const Vec2DS32 *inE_Vec, const Vec2DS32 *inT_Vec )
{
    s32 n;
    
    //�O�ς����߂�iVEC_CrossProduct���g�p�j
    n = ( inT_Vec->x * (inS_Vec->y - inE_Vec->y))+(inS_Vec->x * (inE_Vec->y - inT_Vec->y))+(inE_Vec->x * (inT_Vec->y - inS_Vec->y));
    if      ( n >= 0 ){
		return  1; // �\(��)
	}
    else  return 0; // ��(�E)
}

//---------------------------------------------------------------------------------------------------------
/**
 * �������m�̌�������
 *  @param  *inS_Vec1        �x�N�g���n�_
 *  @param  *inE_Vec1        �x�N�g���I�_
 *  @param  *inS_Vec2        �x�N�g���n�_
 *  @param  *inE_Vec2        �x�N�g���I�_
 *
 *  @retval BOOL
*/
//---------------------------------------------------------------------------------------------------------
BOOL BG2D_CheckSegmentToSegmentS32( const Vec2DS32 *inS_Vec1, const Vec2DS32 *inE_Vec1, const Vec2DS32 *inS_Vec2, const Vec2DS32 *inE_Vec2 )
{

	if ( ((BG2D_VectorSideS32(inS_Vec1,inE_Vec1,inS_Vec2) ^ BG2D_VectorSideS32(inS_Vec1,inE_Vec1,inE_Vec2)) == 1) &&
		 ((BG2D_VectorSideS32(inS_Vec2,inE_Vec2,inS_Vec1) ^ BG2D_VectorSideS32(inS_Vec2,inE_Vec2,inE_Vec1)) == 1)	){
		return TRUE;
	}
	else  return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�x�N�g���f�[�^���쐬����
 *
 *@param	u16 x1�F�n�_���W
 *@param	u16 y1�F�n�_���W
 *@param	u16 x2�F�I�_���W
 *@param	u16 y2�F�I�_���W
 *
 *@return	TP_VECTOR_DATA�^�F�x�N�g���̌X����X=�O�̎��̍���
 *
 */
//-----------------------------------------------------------------------------
TP_VECTOR_DATA MakeVector( u16 x1, u16 y1, u16 x2, u16 y2 )
{
	s16 height;		// �_�̋�������
	s16 width;		// �_�̋�����
	TP_VECTOR_DATA	vect;	// �x�N�g���f�[�^
	
	//
	// �J�n���W�ƏI�_���W����X���Ƃ����O�̎���Y�̒l�����߂�
	//
	height = y2 - y1;
	width = x2 - x1;
	if( width != 0 ){	// �O�����
		vect.x = FX_Div( height << FX32_SHIFT, width << FX32_SHIFT );		// �X��
	}else{
		vect.x = 255 << FX32_SHIFT;		// ����Ȃ�Y���ɋ߂��X���l������
	}
	vect.c = (y1 << FX32_SHIFT) - FX_Mul(vect.x, x1 << FX32_SHIFT);	// X=0�̎��̒l�Z�b�g

	return vect;		// �x�N�g����Ԃ�
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�x�N�g���̌�_�����߂�
 *
 *@param	Vec2DS32* vector1_s�F�x�N�g���P�̊J�n�_
 *@param	Vec2DS32* vector1_e�F�x�N�g���P�̏I���_
 *@param	Vec2DS32* vector2_s�F�x�N�g���Q�̊J�n�_
 *@param	Vec2DS32* vector2_e�F�x�N�g���Q�̏I���_
 *@param	Vec2DS32* cross�F��_���W
 *
 *@return	u32�^�F�O�F��_�Ȃ�		�P�F��_����
 *
 */
//-----------------------------------------------------------------------------
u32 CheckCrossMatrix( Vec2DS32* vector1_s, Vec2DS32* vector1_e, Vec2DS32* vector2_s, Vec2DS32* vector2_e, Vec2DS32* cross )
{
	fx32 cross_x;					// �����_�^�̌�_
	fx32 cross_y;					// �����_�^�̌�_
	fx32 half_x;					// �l�̌ܓ��p
	fx32 half_y;					// �l�̌ܓ��p	
	TP_VECTOR_DATA vector_data_1;	// ��_�v�Z�p�x�N�g���f�[�^�P
	TP_VECTOR_DATA vector_data_2;	// ��_�v�Z�p�x�N�g���f�[�^�Q
	Vec2DS32 vect1_max;				// �x�N�g���P�̍ő� �͈͓��������p
	Vec2DS32 vect1_min;				// �x�N�g���P�̍ŏ� �͈͓��������p
	Vec2DS32 vect2_max;				// �x�N�g���Q�̍ő� �͈͓��������p
	Vec2DS32 vect2_min;				// �x�N�g���Q�̍ŏ� �͈͓��������p
	


	//
	// ��_������
	//
	// ��_���Z�b�g
 	if( cross != NULL ){
		cross->x = 0xffff;
		cross->y = 0xffff;
	}


	// �x�N�g���͈͓��Ɍ�_������̂��`�F�b�N
	if( BG2D_CheckSegmentToSegmentS32( vector1_s, vector1_e,
							vector2_s, vector2_e ) == FALSE ){
		// ��_�͂���܂���
		return 0;
	}
	

	// ��_�����߂邽�߂̃x�N�g���f�[�^���쐬
	vector_data_1 = MakeVector( vector1_s->x, vector1_s->y, vector1_e->x, vector1_e->y );
	vector_data_2 = MakeVector( vector2_s->x, vector2_s->y, vector2_e->x, vector2_e->y );

	
	//
	// ��_�����߂�
	// �x�N�g���̂QD�̐��̕���������
	// ���߂�
	// ��_�����邩�`�F�b�N	= ���s���`�F�b�N
	if( vector_data_1.x == vector_data_2.x ){
		return 0;
	}

	// ���s�łȂ��Ƃ�
	// X���W				
	cross_x = FX_Div( (vector_data_2.c - vector_data_1.c), vector_data_1.x - vector_data_2.x );
	
	// Y���W
	cross_y = FX_Mul(vector_data_2.x, cross_x) + vector_data_2.c;
	

	// X���W���l�̌ܓ�����s32�̍��W�ɂ���
	if( FX_Modf( cross_x, &half_x ) >= FX32_HALF ){
		half_x += FX32_ONE;
	}
	cross->x = half_x >> FX32_SHIFT;

	// Y���W���l�̌ܓ�����s32�̍��W�ɂ���
	if( FX_Modf( cross_y, &half_y ) >= FX32_HALF ){
		half_y += FX32_ONE;
	}
	cross->y = half_y >> FX32_SHIFT;

	//
	// �x�N�g���͈͓̔��ɂ��邩�`�F�b�N
	// 
	// �ő�ŏ��l���Z�b�g
	// �x�N�g���P
	if( vector1_s->x >= vector1_e->x ){
		vect1_max.x = vector1_s->x;
		vect1_min.x = vector1_e->x;
	}else{
		vect1_max.x = vector1_e->x;
		vect1_min.x = vector1_s->x;
	}
	if( vector1_s->y >= vector1_e->y ){
		vect1_max.y = vector1_s->y;
		vect1_min.y = vector1_e->y;
	}else{
		vect1_max.y = vector1_e->y;
		vect1_min.y = vector1_s->y;
	}
	// �x�N�g���Q
	if( vector2_s->x >= vector2_e->x ){
		vect2_max.x = vector2_s->x;
		vect2_min.x = vector2_e->x;
	}else{
		vect2_max.x = vector2_e->x;
		vect2_min.x = vector2_s->x;
	}
	if( vector2_s->y >= vector2_e->y ){
		vect2_max.y = vector2_s->y;
		vect2_min.y = vector2_e->y;
	}else{
		vect2_max.y = vector2_e->y;
		vect2_min.y = vector2_s->y;
	}
	
	//
	// �͈͓����`�F�b�N
	//
	if( (((vect1_max.x >= cross->x) && (vect1_min.x <= cross->x)) &&
		((vect1_max.y >= cross->y) && (vect1_min.y <= cross->y))) &&
		(((vect2_max.x >= cross->x) && (vect2_min.x <= cross->x)) &&
		((vect2_max.y >= cross->y) && (vect2_min.y <= cross->y))) ){

#if 0
	OS_Printf( "��_  x[%d] y[%d]\n", cross->x, cross->y );
	OS_Printf( "vect1 x[%d] y[%d] - x[%d] y[%d]\n", vect1_max.x, vect1_max.y, vect1_min.x, vect1_min.y );
	OS_Printf( "vect2 x[%d] y[%d] - x[%d] y[%d]\n", vect2_max.x, vect2_max.y, vect2_min.x, vect2_min.y );
	OS_Printf( "vect1 s_x[%d] s_y[%d] e_x[%d] e_y[%d]\n", vector1_s->x, vector1_s->y, vector1_e->x, vector1_e->y );
	OS_Printf( "vect2 s_x[%d] s_y[%d] e_x[%d] e_y[%d]\n", vector2_s->x, vector2_s->y, vector2_e->x, vector2_e->y );
	OS_Printf( "vect1 a[%d] c[%d]\n", vector_data_1.x >> FX32_SHIFT, vector_data_1.c >> FX32_SHIFT );
	OS_Printf( "vect2 a[%d] c[%d]\n\n", vector_data_2.x >> FX32_SHIFT, vector_data_2.c >> FX32_SHIFT );
#endif
		
		return 1;		// ��_������
	}
	
	return 0;		// ��_�͂��邪�A�͈͓��ł͂Ȃ�
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�G�̏�񂩂���O���������
 *
 *@param	Vec2DS32* pData�F�s�N�`���[�f�[�^
 *@param	u32 Size�F�f�[�^�T�C�Y
 *@param	u16 x�F���肷��X���W
 *@param	u16 y�F���肷��Y���W
 *
 *@return	u32�^�F�O�F�O�@�P�F��
 *
 */
//-----------------------------------------------------------------------------
u32 CheckInOut( Vec2DS32* pData, u32 Size, u16 x, u16 y )
{
	int				i;					// ���[�v�p	
	u32				check_num;			// ���_��
	Vec2DS32		main_s;				// �����p�x�N�g���n�_���W
	Vec2DS32		main_e;				// �����p�x�N�g���I�_���W
	u8				next_way;			// ���̃f�[�^�̕���
	u8				now_way;			// ���̕���
	u8				skip_flag;			// ����_�������Ă��X�L�b�v����t���O
	u32				skip_data_num;		// �X�L�b�v�`�F�b�N����f�[�^�̗v�f��
	s32				skip_work;			// �X�L�b�v�`�F�b�N�̍�Ɨp
	

	//
	// �n�_�ƏI�_���쐬
	//
	main_s.x = x;					// �`�F�b�N���钸�_���W����
	main_s.y = y;					// �`�F�b�N���钸�_���W����
	main_e.x = x;					// �`�F�b�N���钸�_���W�̐^���̓_����
	main_e.y = CALC_IN_OUT_CECK_Y;	// �`�F�b�N���钸�_���W�̐^���̓_����

	// �ϐ�������
	skip_flag = 0;			// �X�L�b�v���Ȃ��悤�ɏ�����

	
	//
	// �s�N�`���f�[�^���̑S�x�N�g�����������A��_�̂���x�N�g���̐�
	// �𐔂���
	// �����̎��F�O
	// �P���̎��F��
	//
	check_num = 0;		// ���_���J�E���g������
	for( i = 0; i < Size - 1; i++ ){

		// �X�L�b�v���`�F�b�N
		if( skip_flag == 1 ){
			
			skip_flag = 0;		// �X�L�b�v����
			
		}else{
			// ���̓_���`�F�b�N����x�N�g���̉E�ɂ��邩���ɂ��邩�`�F�b�N 
			// �O�̎��͐�΂ɒʂ�悤�ɂ���
			skip_work = pData[ i ].x - main_s.x;
			if( skip_work == 0 ){	
				// ���_�Ɠ���
				now_way = 2;
			}else{
				if( skip_work < 0 ){
					// ��
					now_way = 0;
				}else{
					// �E
					now_way = 1;
				}
			}
			
			// ���̕������`�F�b�N
			skip_work = pData[ i + 1 ].x - main_s.x;
			if( skip_work == 0 ){
				// ���_�Ɠ���
				next_way = 2;
			}else{
				if( skip_work < 0 ){
					// ��
					next_way = 0;
				}else{
					// �E
					next_way = 1;
				}
			}

			// �����`�F�b�N
			if( (now_way != next_way) ||
				((now_way == 2) || (next_way == 2)) ){
			
				// ��_������̂�����
				if( BG2D_CheckSegmentToSegmentS32( &main_s, &main_e,
							&pData[ i ], &pData[ i + 1 ] ) == TRUE ){
					// �X�L�b�v�`�F�b�N�̗v�f�����Z�b�g
					skip_data_num = i + 2;

					// �o�b�t�@���I�[�o�[������P�̒��_����̈ʒu�ɂ���
					// �Ȃ��Ȃ�ŏI�̒��_�ƂO�̒��_�͈ꏏ�ɂȂ�悤�ɍ���Ă��邽�߂ł�
					if( skip_data_num >= Size ){
						skip_data_num = (skip_data_num % Size) + 1;
					}
					
					// �����Q���̒��_��main_s-_e�ō쐬�����x�N�g����Y���łQ��������Ă���Ƃ��́A
					// ���_�͂P�ɂȂ�̂Ŏ��ŁA��_������Ƃ��̓X�L�b�v����
					if( (BG2D_VectorSideS32( &main_s, &main_e, &pData[ i ] ) ^
						BG2D_VectorSideS32( &main_s, &main_e, &pData[ skip_data_num ] )) == 1 ){
						// ����_����������X�L�b�v����
						skip_flag = 1;
					}

					// �`�F�b�N
					check_num++;
				}				
			}
		}
	}


	//
	// ���_�����P���Ȃ�P��Ԃ�
	//
	return check_num % 2;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�x�N�g���̍��p�x�����߂�
 *
 *@param	u16 x1�F�n�_���W
 *@param	u16 y1�F�n�_���W
 *@param	u16 x2�F�I�_���W
 *@param	u16 y2�F�I�_���W
 *@param	u16 x3�F�n�_�Q���W
 *@param	u16 y3�F�n�_�Q���W
 *@param	u16 x4�F�I�_�Q���W
 *@param	u16 y4�F�I�_�Q���W
 *
 *@return	u16�^�F�x�N�g���P�ƂQ�̍�鋷���ق��̊p�x
 *
 */
//-----------------------------------------------------------------------------
u16 GetVectorAngle( u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u16 x4, u16 y4 )
{
	u16 rota1, rota2;		// ��]�p
	s16	vec_x, vec_y;		// �x�N�g��
	
	//
	// 1-2�@1-3�̃x�N�g�����쐬���A�Q�����Ԃ̊p�x��Ԃ� 
	//
	// 1-2�̊p�x���v�Z
	vec_x = x2 - x1;
	vec_y = y2 - y1;

	// �p�x�����߂�
	rota1 = FX_Atan2Idx( vec_y << FX32_SHIFT, vec_x << FX32_SHIFT );

	// 1-3�̊p�x���v�Z
	vec_x = x3 - x4;
	vec_y = y3 - y4;

	// �p�x�����߂�
	rota2 = FX_Atan2Idx( vec_y << FX32_SHIFT, vec_x << FX32_SHIFT );
	
	
	// �Ԃ̊p�x�ɂ���
	if( rota1 > rota2 ){
		rota1 -= rota2;
	}else{
		rota2 -= rota1;
		rota1 = rota2;
	}

	// �Ԃ̊p�x��180��葽���Ƃ��͔��Α��̏������p�x�̕��̒l�ɂ���
	if( rota1 > (180 * 182) ){
		rota1 = (360*182) - rota1;
	}


	return rota1;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�x�N�g���̒��������߂�
 *
 *@param	s32 x1, s32 y1�F���_�P
 *@param	s32 x2, s32 y2�F���_�Q
 *
 *
 *@return	u32�^�F����
 *
 */
//-----------------------------------------------------------------------------
u32 GetVectorDistance( s32 x1, s32 y1, s32 x2, s32 y2 )
{
	s32 dist_x, dist_y;			// �e�����̒���
	u32	dist;					// �x�N�g���̒���
	
	
	//
	// �x�N�g���̒��������߂�
	//
	dist_x = x1 - x2;
	dist_y = y1 - y2;

	// ���������߂�
	dist = FX_Sqrt( ((dist_x * dist_x) + (dist_y * dist_y)) << FX32_SHIFT ) >> FX32_SHIFT;

	return dist;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	���_�̃o�b�t�@���󂯎�蒆�S�̍��W�����߂�
 *
 *@param	Vec2DS32* pBuff�F�o�b�t�@
 *@param	u32 Size�F�T�C�Y
 *
 *
 *@return	Vec2DS32�^�F���S�̍��W
 *
 */
//-----------------------------------------------------------------------------
Vec2DS32 GetCenterMatrix( Vec2DS32* pBuff, u32 Size )
{
	Vec2DS32 max;		// �ő�l
	Vec2DS32 min;		// �ŏ��l
	Vec2DS32 ret;		// �߂�l�p
	int	i;				// ���[�v�p
	

	
	// ������
	min = pBuff[ 0 ];
	max = pBuff[ 0 ];
	
	//
	//���ĂƉ��̍ő�A�ŏ��l���擾 
	//
	for( i = 0; i < Size; i++ ){
		//
		// X��Y�̍ő�ŏ��`�F�b�N
		//
		if( min.x > pBuff[ i ].x ){
			min.x = pBuff[ i ].x;
		}else{
			if( max.x < pBuff[ i ].x ){
				max.x = pBuff[ i ].x;
			}
		}

		if( min.y > pBuff[ i ].y ){
			min.y = pBuff[ i ].y;
		}else{
			if( max.y < pBuff[ i ].y ){
				max.y = pBuff[ i ].y;
			}
		}
	}


	//
	// ���S���W�����߂�
	//
	ret.x = ((max.x - min.x) / 2) + min.x;
	ret.y = ((max.y - min.y) / 2) + min.y;
	

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�s��ɉ�]�s���������
 *
 *@param	MtxFx33* p_matrix�F�s��
 *@param	u16 rota_num�F��]�p
 *
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void SetRotaMatrix2D( MtxFx33* p_matrix, u16 rota_num )
{
	MtxFx33 work;
	//
	// ��]�s���������
	//
	MTX_RotZ33( &work, FX_SinIdx(rota_num), FX_CosIdx(rota_num) );

	// �������킹��
	MTX_Concat33( &work, p_matrix, p_matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�s��Ɋg�k�s���������
 *			�g�p�O��MTX_Identity33�i�j�ŒP�ʍs��ɂ��Ă����Ă�������
 *
 *@param	MtxFx33* p_matrix�F�s��
 *@param	fx32 x�F���g�k�l
 *@param	fx32 y�F���Ċg�k�l
 *
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void SetScaleMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y )
{
	MtxFx33 work;

	//
	// ��]�s���������
	//
	MTX_Scale33( &work, x, y, FX32_ONE );

	// �������킹��
	MTX_Concat33( &work, p_matrix, p_matrix );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�s��ɍ��W�������āA��]�A�g�k��̍��W�����߂�
 *			�g�p�O��MTX_Identity33�i�j�ŒP�ʍs��ɂ��Ă����Ă�������
 *
 *@param	MtxFx33* p_matrix�F�s��
 *@param	fx32 x�F�����W
 *@param	fx32 y�F���č��W
 *@param	fx32* p_get_x�F�ϊ���̍��W�i�[�p
 *@param	fx32* p_get_y�F�ϊ���̍��W�i�[�p
 *
 *
 *@return	�Ȃ�
 *
 */
//-----------------------------------------------------------------------------
void GetMatrix2D( MtxFx33* p_matrix, fx32 x, fx32 y, fx32* p_get_x, fx32* p_get_y )
{
	// �v�Z����
	*p_get_x = FX_Mul( p_matrix->_00, x ) + FX_Mul( p_matrix->_01, y );
	*p_get_y = FX_Mul( p_matrix->_10, x ) + FX_Mul( p_matrix->_11, y );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	�߂��_�����߂�
 *
 *@param	Vec2DS32* pBuff�F�o�b�t�@
 *@param	u32 Size�F�T�C�Y
 *@param	Vec2DS32 mat�F�߂��_��T�����W
 *
 *
 *@return	u32 �^�F�߂����W�̓Y����
 *
 */
//-----------------------------------------------------------------------------
u32 GetNearMatrix( Vec2DS32* pBuff, u32 Size, Vec2DS32 mat )
{
	u32		  ret;				// �߂�l�p
	u32		  dist;				// �ŒZ�����i�[�p
	int		  i;				// ���[�v�p
	u32		  dist_work;		// �ŒZ�����p
		

	//
	// �o�b�t�@�O�̒l�ŏ�����
	// 
	ret = 0;
	dist = GetVectorDistance( pBuff[0].x, pBuff[0].y, mat.x, mat.y );
	
	//
	// ��ԋ߂��_�̃|�C���^��Ԃ�
	//
	for( i = 0; i < Size; i++ ){
		// ���������߂�
		dist_work = GetVectorDistance( pBuff[i].x, pBuff[i].y, mat.x, mat.y );

		// �ŒZ���`�F�b�N
		if( dist > dist_work  ){
			dist = dist_work;
			ret = i;
		}
	}

	return ret;
}
