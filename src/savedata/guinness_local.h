/**
 *	@brief	�M�l�X�z�[���@�Z�[�u�f�[�^�^
 */

#include "savedata/guinness.h"
///�M�l�X�f�[�^�^
struct _GUINNESS_DATA{
	u32	groupID;
	u32	record;
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];
};

///�M�l�X�f�[�^�u���b�N�^
struct _GUINNESS_BLOCK{
	struct _GUINNESS_DATA	dat[GNS_DATA_NUM];
};

///�M�l�X���R�[�h�f�[�^�^(���R�[�h�������Ɏg�p)
struct _GUINNESS_RECORD{
	struct	_GUINNESS_DATA	dat[GNS_RECORD_NUM];
};

///�M�l�X�z�[���f�[�^�^
struct _GUINNESS{
	struct _GUINNESS_BLOCK	block[GNS_BLOCK_NUM];
};
