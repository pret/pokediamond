//============================================================================================
/**
 * @file	safari_enc.c
 * @brief	�T�t�@���G���J�E���g�֘A
 * @author	saitou
 *
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "fielddata/maptable/zone_id.h"
#include "arc/encdata_ex.naix"

#include "encount_define.h"

#include "safari_enc.h"

#define SAFARI_BIT_SHIFT	(5)

static u8 GetSafariArea( const int inZoneID );

//-----------------------------------------------------------------------------
/**
 * �T�t�@���G���J�E���g�e�[�u�������ւ�
 *
 * @param	inRandomSeed		�����_���̎�
 * @param	inBookGet			�S���}�ӓ���t���O
 * @param	inZoneID			�]�[���h�c
 * @param	*outSafEncMonsNo1	�G���J�E���g�|�P����1�̖�
 * @param	*outSafEncMonsNo2	�G���J�E���g�|�P����2�̖�
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void SafariEnc_SetSafariEnc(	const int inRandomSeed, const BOOL inBookGet,
								const int inZoneID,
								int *outSafEncMonsNo1, int *outSafEncMonsNo2)
{
	int *tbl;
	int arc_idx;
	u8 tblno;
	u8 area = GetSafariArea( inZoneID );
	
	//�S���}�ӊ������ǂ����ŁA�e�[�u����ς���
	if(inBookGet){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//�T�t�@���G���J�E���g�e�[�u���擾
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//�����_���̎�����ɃT�t�@���G���J�E���g�e�[�u������|�P�����I�o
	
	/* ---�I�o���@--- */
	/*�T�t�@�������_���̎��5�r�b�g�����ʃr�b�g����6��������B���2�r�b�g�͎g��Ȃ�*/
	/*�T�t�@���G���A�ԍ��i0�`5�j����A�g���r�b�g�Q������*/
	/*0�Ȃ�A����5�r�b�g�B1�Ȃ玟��5�r�b�g�E�E�E*/
	/*�w��5�r�b�g�Ō��肳��鐔���i0�`31�j���T�t�@������e�[�u���Ŏw�肳���C���f�b�N�X�ƂȂ�*/
	/*���̃C���f�b�N�X�Ō��肷��|�P�����i���o�[������g�ɓ���*/
	/*����g2�ɂ͓����|�P�����i���o�[������*/
	
	tblno = ( (inRandomSeed >> (SAFARI_BIT_SHIFT*area)) & 0x1f );

	tblno %= SAFARI_TBL_MAX;//<<�O�̂��߃e�[�u���ő吔�̗]����̗p�l�Ƃ���

	(*outSafEncMonsNo1) = tbl[tblno];
	(*outSafEncMonsNo2) = tbl[tblno];

	sys_FreeMemoryEz(tbl);
}

//-----------------------------------------------------------------------------
/**
 * �]�[���h�c����T�t�@���G���A�ԍ��i0�`5�j��Ԃ�
 * 0�F����	�E�E�E�@5�F�E��
 *
 * @param	inZoneID		�]�[���h�c
 *
 * @return	u8				�T�t�@���G���A�ԍ�(0�`5)
 */
//-----------------------------------------------------------------------------
static u8 GetSafariArea( const int inZoneID )
{
	u8 area = 0;

	switch(inZoneID){
	case ZONE_ID_D06R0201:
		area = 0;
		break;
	case ZONE_ID_D06R0202:
		area = 1;
		break;
	case ZONE_ID_D06R0203:
		area = 2;
		break;
	case ZONE_ID_D06R0204:
		area = 3;
		break;
	case ZONE_ID_D06R0205:
		area = 4;
		break;
	case ZONE_ID_D06R0206:
		area = 5;
		break;
	default:
		GF_ASSERT(0&&"�T�t�@���]�[���ł͂Ȃ�");
	}
	
	return area;
}


#ifdef PM_DEBUG
//�T�t�@���e�[�u���Z�o
void SafariEnc_DebugGetSafariTbl(	const int inRandomSeed, const BOOL inBookGet,
									const u8 inArea,
									int *outSaf, int *outSafEncMonsNo)
{
	int *tbl;
	int arc_idx;
	u8 tblno;
	u8 area = inArea;
	
	//�S���}�ӊ������ǂ����ŁA�e�[�u����ς���
	if(inBookGet){
		arc_idx = NARC_encdata_ex_safari_af_bin;
	}else{
		arc_idx = NARC_encdata_ex_safari_bef_bin;
	}
	//�T�t�@���G���J�E���g�e�[�u���擾
	tbl = ArchiveDataLoadMallocLo(ARC_ENCDATA_EX, arc_idx, HEAPID_FIELD);
	//�����_���̎�����ɃT�t�@���G���J�E���g�e�[�u������|�P�����I�o
	
	/* ---�I�o���@--- */
	/*�T�t�@�������_���̎��5�r�b�g�����ʃr�b�g����6��������B���2�r�b�g�͎g��Ȃ�*/
	/*�T�t�@���G���A�ԍ��i0�`5�j����A�g���r�b�g�Q������*/
	/*0�Ȃ�A����5�r�b�g�B1�Ȃ玟��5�r�b�g�E�E�E*/
	/*�w��5�r�b�g�Ō��肳��鐔���i0�`31�j���T�t�@������e�[�u���Ŏw�肳���C���f�b�N�X�ƂȂ�*/
	/*���̃C���f�b�N�X�Ō��肷��|�P�����i���o�[������g�ɓ���*/
	/*����g2�ɂ͓����|�P�����i���o�[������*/
	
	tblno = ( (inRandomSeed >> (SAFARI_BIT_SHIFT*area)) & 0x1f );

	tblno %= SAFARI_TBL_MAX;//<<�O�̂��߃e�[�u���ő吔�̗]����̗p�l�Ƃ���

	(*outSaf) = tblno;
	(*outSafEncMonsNo) = tbl[tblno];

	sys_FreeMemoryEz(tbl);
}

#endif
