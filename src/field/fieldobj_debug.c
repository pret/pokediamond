//==============================================================================
/**
 *
 * @file	fieldobj_debug.c
 * @brief	�t�B�[���hOBJ�@�f�o�b�O
 * @author	kagaya
 * @data	2005.07.11
 *
 */
//==============================================================================
//----
#ifdef PM_DEBUG
//----
#include "common.h"
#include "fieldobj.h"

#include "..\fielddata\maptable\zone_id.h"

//==============================================================================
//	�G�C���A�X�e�X�g
//==============================================================================
#ifdef DEBUG_ALIES

const FIELD_OBJ_H DATA_DebugFldOBJHeaderR202A[2] =
{
	{
		128,		///<����ID
		BOY1,		///<�\������OBJ�R�[�h
		MV_DMY,	///<����R�[�h
		0,			///<�C�x���g�^�C�v
		ZONE_ID_C01,///<�C�x���g�t���O
		SCRID_ALIES,///<�C�x���gID
		DIR_DOWN,	///<�w�����
		0,	///<�w��p�����^ 0
		0,	///<�w��p�����^ 1
		0,	///<�w��p�����^ 2
		1,	///<X�����ړ�����
		1,///<Z�����ړ�����
		171,///<�O���b�hX
		798,///<�O���b�hZ
		0,	///<Y�l
	},
	{
		129,		///<����ID
		BOARD_A,	///<�\������OBJ�R�[�h
		MV_DMY,	///<����R�[�h
		0,			///<�C�x���g�^�C�v
		ZONE_ID_C01,///<�C�x���g�t���O
		SCRID_ALIES,///<�C�x���gID
		DIR_DOWN,	///<�w�����
		0,	///<�w��p�����^ 0
		0,	///<�w��p�����^ 1
		0,	///<�w��p�����^ 2
		1,	///<X�����ړ�����
		1,///<Z�����ړ�����
		170,///<�O���b�hX
		798,///<�O���b�hZ
		0,	///<Y�l
	},
};

const FIELD_OBJ_H DATA_DebugFldOBJHeaderC01[2] =
{
	{
		128,		///<����ID
		BOY1,		///<�\������OBJ�R�[�h
		MV_DMY,	///<����R�[�h
		0,			///<�C�x���g�^�C�v
		0,///<�C�x���g�t���O
		0,///<�C�x���gID
		DIR_DOWN,	///<�w�����
		0,	///<�w��p�����^ 0
		0,	///<�w��p�����^ 1
		0,	///<�w��p�����^ 2
		1,	///<X�����ړ�����
		1,///<Z�����ړ�����
		171,///<�O���b�hX
		798,///<�O���b�hZ
		0,	///<Y�l
	},
	{
		129,		///<����ID
		BOARD_A,		///<�\������OBJ�R�[�h
		MV_DMY,	///<����R�[�h
		0,			///<�C�x���g�^�C�v
		0,///<�C�x���g�t���O
		0,///<�C�x���gID
		DIR_DOWN,	///<�w�����
		0,	///<�w��p�����^ 0
		0,	///<�w��p�����^ 1
		0,	///<�w��p�����^ 2
		1,	///<X�����ړ�����
		1,///<Z�����ړ�����
		170,///<�O���b�hX
		798,///<�O���b�hZ
		0,	///<Y�l
	},
};

//--------------------------------------------------------------
/**
 * �G�C���A�X�e�X�g�@�Â��]�[��OBJ�폜���̃e�X�g
 * @param
 * @retval
 */
//--------------------------------------------------------------
FIELD_OBJ_H * DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeader(
		int new_zone_id, int *head_max, const FIELD_OBJ_H *head )
{
	int max;
	FIELD_OBJ_H *debughead;
	
	max = *head_max;
	
	if( new_zone_id == ZONE_ID_C01 ){
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderC01[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderC01[1];
		max += 2;
		OS_Printf( "�t�B�[���hOBJ �]�[���X�V�폜�����ɂăG�C���A�X�e�X�g�@C01\n" );
	}else if( new_zone_id == ZONE_ID_R202 ){
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderR202A[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderR202A[1];
		max += 2;
		OS_Printf( "�t�B�[���hOBJ �]�[���X�V�폜�����ɂăG�C���A�X�e�X�g�@R202\n" );
	}else{
		debughead = sys_AllocMemoryLo( HEAPID_FIELD, FIELD_OBJ_H_SIZE*(max) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
	}
	
	*head_max = max;
	return( debughead );
}

void DEBUG_FieldOBJ_ZoneUpdateDeleteAliesHeaderDelete( FIELD_OBJ_H *head )
{
	sys_FreeMemory( HEAPID_FIELD, head );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ AddBin()�G�C���A�X�p
 * @param
 * @retval
 */
//--------------------------------------------------------------
FIELD_OBJ_H * DEBUG_FieldOBJ_AddBinHeaderAlies(
		int zone_id, int *head_max, const FIELD_OBJ_H *head )
{
	int max = *head_max;
	FIELD_OBJ_H *debughead;
	
	if( zone_id == ZONE_ID_C01 ){
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderC01[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderC01[1];
		max += 2;
		OS_Printf( "�t�B�[���hOBJ �ꊇ�ǉ������ɂăG�C���A�X�e�X�g�@C01\n" );
	}else if( zone_id == ZONE_ID_R202 ){
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*(max+2) );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
		debughead[max] = DATA_DebugFldOBJHeaderR202A[0];
		debughead[max+1] = DATA_DebugFldOBJHeaderR202A[1];
		max += 2;
		OS_Printf( "�t�B�[���hOBJ �ꊇ�ǉ������ɂăG�C���A�X�e�X�g�@C01\n" );
	}else{
		debughead = sys_AllocMemoryLo( HEAPID_WORLD, FIELD_OBJ_H_SIZE*max );
		memcpy( debughead, head, FIELD_OBJ_H_SIZE*max );
	}

	*head_max = max;
	return( debughead );
}

void DEBUG_FieldOBJ_AddBinHeaderAliesDelete( FIELD_OBJ_H *head )
{
	sys_FreeMemory( HEAPID_WORLD, head );
}
#endif	//DEBUG_ALIES

//----
#endif	//PM_DEBUG
//----
