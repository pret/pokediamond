//============================================================================================
/**
 * @file	sway_grass_enc.c
 * @brief	�h�ꑐ�G���J�E���g
 * @author	saito GAME FREAK inc.
 * @date	2006.02.14
 */
//============================================================================================

#include "sway_grass_enc.h"
#include "field_effect.h"
#include "map_tool.h"

#include "fieldsys.h"	//for savedata

#include "bounding_box.h"

#include "battle/battle_common.h"	//for FIGHT_WIN, FIGHT_POKE_GET

#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "savedata/encount.h"

#include "itemtool/itemsym.h"
#include "encount_define.h"

#include "script.h"		//for GetEvScriptWorkMemberAdrs
#include "fielddata/script/pokesearcher_def.h"
#include "sway_grass_hist.h"

#define ISMIN(rc,a,b) { \
	(a<b)? (rc=TRUE):(rc=FALSE); \
}

#define SEARCH_AROUND		(4)
#define SEARCH_WIDTH_MAX	(9)
#define SEARCH_OFFS			(SEARCH_WIDTH_MAX/2)
#define SERCH_NUM_ROUND1	(32)	//�O���O��
#define SERCH_NUM_ROUND2	(24)	//��
#define SERCH_NUM_ROUND3	(16)	//��
#define SERCH_NUM_ROUND4	(8)		//�O������

#define RARE_POKE_PROP_MAX	(8200)	//����ő�8200
#define RARE_POKE_PROP_MIN	(200)	//����ŏ�200
#define SUB_PROP			(200)	//���������m��

enum {
	SEQ_SWAY_SEARCH,
	SEQ_SWAY_BGM_START,
	SEQ_SWAY_WAIT,
	SEQ_SWAY_NG,
	SEQ_SWAY_END
};

typedef struct SWAY_GRASS_INFO_tag
{
	int GridX;
	int GridZ;
	int EncTblCode;	//�G���J�E���g����e�[�u���R�[�h
	BOOL	SwayGrassFlg;
	BOOL	ChainFlg;	//�A���t���O
	BOOL	IsRare;
	EOA_PTR	GrassAnime;
	VecFx32 GrassPos;
}SWAY_GRASS_INFO;

typedef struct SWAY_GRASS_tag{
	int EncTblCode;			//�G���J�E���g�����e�[�u���R�[�h
	int Chain;				//�A����
	int EncMonsNo;			//�h�ꑐ�G���J�E���g���������X�^�[�i���o�[
	int EncMonsLv;				//�h�ꑐ�G���J�E���g���������X�^�[���x��
	BOOL Valid;		//�h�ꑐ�����ǂ���
	BOOL FirstEnc;			//���h�ꑐ�G���J�E���g��
	BOOL SwayEncReturn;	//��ꑐ�퓬�Ƃ��ĕ��A������
	SWAY_GRASS_INFO GrassInfo[SEARCH_AROUND];
	BOUNDING_BOX	BoundingBox;
	u8 RewritePos;			//�`�F�[�����R�[�h���������ʒu
}SWAY_GRASS;

static BOOL SetSwayGrassInfo(	FIELDSYS_WORK * fsys,
							const fx32 inPlayerHeight,
							const int inX, const int inZ,
							const u8 inSearchX, const u8 inSearchZ,
							SWAY_GRASS_INFO *outInfo	);
static BOOL CheckSwayGrass(	const SWAY_GRASS_PTR inSwayGrass,
							const int inX, const int inZ,
							u8 *outRound);
static void UpdateSwayGrassHist(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR ioSwayGrass);
static u8 GetSwayGrassMinRecordPos(FIELDSYS_WORK * fsys);
static BOOL GetChainFlg(const u8 inRound, const int inBattleResult);
static BOOL SwayGrassSetupEvent(GMEVENT_CONTROL * event);
static BOOL CheckRare(const int inChain);
static void IncChain(int *outChain);

//-----------------------------------------------------------------------------
/**
 * @brief	�������m�ۊ֐�
 * @param	inHeapID	�q�[�vID
 * 
 * @retval	ptr			��ꑐ�\���̂ւ̃|�C���^
 *
 */
//-----------------------------------------------------------------------------
SWAY_GRASS_PTR SwayGrass_AllocSwayGrass(const int inHeapID)
{
	SWAY_GRASS_PTR ptr;
	ptr = sys_AllocMemory(inHeapID, sizeof(SWAY_GRASS) );
	//�o�E���f�B���O�{�b�N�X�쐬(���P�O���b�h���A�������O���b�h���A���s���P�O���b�h��)
	BB_MakeBoundingBox(FX32_ONE*16,FX32_ONE*8,FX32_ONE*16,&ptr->BoundingBox);
	return ptr;
}

//-----------------------------------------------------------------------------
/**
 * @brief	����������֐�	(�Q�[���n�߂Ɋm�ۂ��āA���̂܂܂Ȃ̂ŉ�����Ȃ�����)
 * @param	outSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_FreeSwayGrass(SWAY_GRASS_PTR outSwayGrass)
{
	sys_FreeMemoryEz(outSwayGrass);
}

//-----------------------------------------------------------------------------
/**
 * @brief	������
 * @param	outSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_InitSwayGrass(SWAY_GRASS_PTR outSwayGrass)
{
	u8 i;
	outSwayGrass->Chain = 0;
	outSwayGrass->EncTblCode = SWAY_GRASS_ENC_NORMAL;
	outSwayGrass->EncMonsNo = 0;
	outSwayGrass->EncMonsLv = 0;
	outSwayGrass->Valid = FALSE;
	outSwayGrass->RewritePos = 0;
	outSwayGrass->FirstEnc = TRUE;
	outSwayGrass->SwayEncReturn = FALSE;
	
	MI_CpuClear8(&(outSwayGrass->GrassInfo[0]), sizeof(SWAY_GRASS_INFO)*SEARCH_AROUND);
	for(i=0;i<SEARCH_AROUND;i++){
		outSwayGrass->GrassInfo[i].SwayGrassFlg = FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�h�ꑐ�{��
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inX				�������SX���W
 * @param	inZ				�������SZ���W
 * @param	ioSwayGrass	�h�ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	BOOL		TRUE:�h�ꑐ�L���@FALSE:�h�ꑐ����
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_SearchSwayGrass(	FIELDSYS_WORK * fsys,
								const int inX, const int inZ,
								SWAY_GRASS_PTR ioSwayGrass)
{
	u8 i;				//�O���J�E���^
	u8 size_x,size_z;	//�O���c���T�C�Y
	u8 num;				//����ԍ�
	u8 t_num;			//�v�Z�e���|����
	int x,z;			//���W
///	BOOL chain_flg;		//�A���t���O
	u8 valid_num;		//�h�ꑐ��

	const VecFx32 *player_vec;

	u8	rand_list[SEARCH_AROUND] = {	//�����_���e�[�u���i�e�O�����̃����_���ő�l�j
		SERCH_NUM_ROUND1,	//��ԊO��
		SERCH_NUM_ROUND2,
		SERCH_NUM_ROUND3,
		SERCH_NUM_ROUND4	//��ԓ���
	};

	//���@�����擾
	player_vec = Player_VecPosPtrGet( fsys->player );

	valid_num = 0;
	for(i=0;i<SEARCH_AROUND;i++){
		BOOL rc;
		//�Ώۍ��W�������_���Ō���
		num = gf_p_rand(rand_list[i]);
		//OS_Printf("num%d\n",num);
		//�����ݒ�
		size_x = SEARCH_WIDTH_MAX-(i*2);
		//�c���ݒ�
		size_z = SEARCH_WIDTH_MAX-(i*2);

		//���肵���ԍ��𕝂Ŋ���
		t_num = num/size_x;
		//����0�Ȃ�O����A1�Ȃ牺
		//��A���Ƀq�b�g�����ꍇ�A�]��ł����W������i���͏��Łj
		if (t_num == 0){
			x = i+num%size_x;
			z = i;
		}else if(t_num == 1){
			x = i+num%size_x;
			z = i+size_z-1;
		}else{
			//	//�q�b�g���Ȃ������ꍇ�A���肵���ԍ�-��*2����
			GF_ASSERT( num>=(size_x*2) );
			t_num = num-(size_x*2);
			//���H�����ԍ���2�Ŋ���
			//��+1��z��������i���͍������A�E�����Ȃ̂ŁA���Ŕ��f�j
			z = i+(t_num/2)+1;
			if (t_num%2 == 0){	//�O��������
				x = i;
			}else{				//�O���E����
				x = i+size_x-1;
			}
		}
#if 0		
		//�A�����邩�ǂ���������
		chain_flg = GetChainFlg(i,inBattleResult);
#endif
		//OS_Printf("grass_anime%d,%d\n",x,z);

		//���肵�����W�̏����Z�b�g
		rc = SetSwayGrassInfo(	fsys, player_vec->y, inX, inZ, x, z,
								&ioSwayGrass->GrassInfo[i]);
		if (rc){
			valid_num++;
		}
	}

	if (valid_num == 0){
		SwayGrass_InitSwayGrass(ioSwayGrass);
		//�ȏI��点��
		Snd_FadeOutNextPlayCall(fsys,
								Snd_FieldBgmNoGet(fsys,fsys->location->zone_id),
								BGM_FADE_FIELD_MODE );
	}else{
		ioSwayGrass->Valid = TRUE;
	}

	return ioSwayGrass->Valid;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�A���ݒ�
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inBattleResult	�퓬����	 FIGHT_WIN	FIGHT_POKE_GET
 * @param	ioSwayGrass	�h�ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void	SwayGrass_SetChain(	FIELDSYS_WORK * fsys,
								const int inBattleResult,
								SWAY_GRASS_PTR ioSwayGrass)
{
	u8 i;				//�O���J�E���^
	for(i=0;i<SEARCH_AROUND;i++){
		if ( ioSwayGrass->GrassInfo[i].SwayGrassFlg){
			//�A�����邩�ǂ���������
			ioSwayGrass->GrassInfo[i].ChainFlg = GetChainFlg(i,inBattleResult);//�A���t���O�Z�b�g
			//����G���J�E���g����e�[�u�����Z�b�g
			if (!ioSwayGrass->GrassInfo[i].ChainFlg){
				//�A�����Ȃ��̂Ńe�[�u���̒��I(�m����1/2)
				if(gf_p_rand(100) < 50){	//�m�[�}��
					ioSwayGrass->GrassInfo[i].EncTblCode = SWAY_GRASS_ENC_NORMAL;
				}else{		//�e�[�u���ύX
					ioSwayGrass->GrassInfo[i].EncTblCode = SWAY_GRASS_ENC_SP;
				}
				ioSwayGrass->GrassInfo[i].IsRare = FALSE;
			}else{
				//�A������ꍇ�͑O��̃e�[�u���������p��
				ioSwayGrass->GrassInfo[i].EncTblCode = ioSwayGrass->EncTblCode;
				//���A�|�P�������I
				ioSwayGrass->GrassInfo[i].IsRare = CheckRare(fsys->SwayGrass->Chain);
			}
		}
	}
}


//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�A�j���Z�b�g
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	outSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_SetSwayGrassAnime(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR outSwayGrass)
{
	u8 i;
	for(i=0;i<SEARCH_AROUND;i++){
		if (outSwayGrass->GrassInfo[i].SwayGrassFlg){
			int x = outSwayGrass->GrassInfo[i].GridX;
			int z = outSwayGrass->GrassInfo[i].GridZ;
			//���A�t���O���������Ă��邩�ŃA�j������
			if (outSwayGrass->GrassInfo[i].IsRare){
				//���A�|�P�����G���J�E���g�p�A�j���Z�b�g
				outSwayGrass->GrassInfo[i].GrassAnime =
					FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_KIRAKIRA );
			}else{
				//�Z�b�g����Ă���e�[�u���R�[�h�ŃA�j���𕪊�
				if (outSwayGrass->GrassInfo[i].EncTblCode == SWAY_GRASS_ENC_NORMAL){
					//�ʏ�e�[�u��
					outSwayGrass->GrassInfo[i].GrassAnime =
						FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_SMALL );
				}else{
					//�h�ꑐ��p�e�[�u��
					outSwayGrass->GrassInfo[i].GrassAnime =
						FE_EncGrass_Add( fsys, x, z, FE_GRASS_TYPE_ENCOUNT_BIG );
				}
			}
		}else{
			outSwayGrass->GrassInfo[i].GrassAnime = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�A�j���I���҂�
 * @param	ioSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * 
 * @retval	BOOL	TRUE:�A�j���I��	FALSE:�A�j���p��
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckSwayGrassAnimeEnd(SWAY_GRASS_PTR ioSwayGrass)
{
	u8 count;
	u8 i;
	count = 0;
	for(i=0;i<SEARCH_AROUND;i++){
		if (ioSwayGrass->GrassInfo[i].GrassAnime != NULL){
			
			if (FE_EncGrass_AnimeCheck( ioSwayGrass->GrassInfo[i].GrassAnime )){
				EOA_Delete( ioSwayGrass->GrassInfo[i].GrassAnime );
				ioSwayGrass->GrassInfo[i].GrassAnime = NULL;
				count++;
			}
		}else{
			count++;
		}
	}
	if(count >= SEARCH_AROUND){
		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�`�F�b�N
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	ioSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * @param	outUseEncTable	�g�p����G���J�E���g�e�[�u���R�[�h
 * @param	outMonsDeside	�G���J�E���g����|�P���������肵�Ă��邩������t���O
 * 
 * @retval	BOOL	TRUE:�h�ꑐ�G���J�E���g�����@FALSE:�h�ꑐ�G���J�E���g�s����
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckSpEncount(	const int inX, const int inZ,
								FIELDSYS_WORK * fsys,
								SWAY_GRASS_PTR ioSwayGrass,
								int *outUseEncTable,
								BOOL *outMonsDeside,
								BOOL *outRare)
{
	u8 round;
	BOOL chain_flg;
	int tbl_code;
	
	*outMonsDeside = FALSE;
	*outRare = FALSE;
	//��ꑐ�G���J�E���g���ǂ������`�F�b�N
	if ( !CheckSwayGrass(ioSwayGrass, inX, inZ, &round) ){
		//���񂾍��W���h�ꑐ�ł͂Ȃ�
		return FALSE;//SWAY_GRASS_ENC_NO_ENC;
	}
	
	ioSwayGrass->SwayEncReturn = TRUE;	//�퓬��͂�ꑐ
	
	chain_flg = ioSwayGrass->GrassInfo[round].ChainFlg;
	tbl_code = ioSwayGrass->GrassInfo[round].EncTblCode;
	//���߂ăG���J�E���g�����`�F�b�N	
	if(ioSwayGrass->FirstEnc == FALSE){ //���߂Ăł͂Ȃ�
		if(chain_flg){			//�A�������Ȃ�A�����|�P����
			IncChain(&(ioSwayGrass->Chain));		//�A����+1
			//*outUseEncTable = ioSwayGrass->EncTblCode;//�ۑ����Ƃ����R�[�h
			*outUseEncTable = tbl_code;	//SwayGrass�̃����o���璼�Ɏ�邱�Ƃ��\������ǂ��AInfo������
			*outMonsDeside = TRUE;
			//�h�ꑐ�G���J�E���g�����`�F�b�N�ƍX�V
			UpdateSwayGrassHist(fsys, ioSwayGrass);
			//ioSwayGrass->SwayGrassEnc = TRUE;	//�h�ꑐ�G���J�E���g���t���O�I��
			
			(*outRare) = ioSwayGrass->GrassInfo[round].IsRare;	//���A�t���O�Z�b�g
			
			return TRUE;//SWAY_GRASS_ENC_KEEP_MONSTER;
		}else{		//�Ⴄ�|�P����
			*outUseEncTable = tbl_code;	//�G���J�E���g�e�[�u���R�[�h�Z�b�g
		}
	}else{	//���߂ėh�ꑐ
		*outUseEncTable = tbl_code;
		ioSwayGrass->FirstEnc = FALSE;
		//���������ΏۂƂȂ�h�ꑐ�G���J�E���g�������擾����
		//(3�̗����̒��ň�ԘA���������Ȃ����R�[�h�̏ꏊ���擾����)
		ioSwayGrass->RewritePos = GetSwayGrassMinRecordPos(fsys);
	}
	
	//�ǂ����̃e�[�u����K�p��������ۑ�
	ioSwayGrass->EncTblCode = *outUseEncTable;

	//ioSwayGrass->SwayGrassEnc = TRUE;	//�h�ꑐ�G���J�E���g���t���O�I��
	
	return TRUE;//SWAY_GRASS_ENC_START;
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�G���J�E���g�|�P�������L��(�i���o�[�A���x��)
 * @param	outSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * @param	inMonsNo			�G���J�E���g�����X�^�[�i���o�[
 * @param	inMonsLv			�G���J�E���g�����X�^�[���x��
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_SetEncMonsNoLv(SWAY_GRASS_PTR outSwayGrass, const int inMonsNo, const int inMonsLv)
{
	GF_ASSERT(inMonsNo != 0);
	outSwayGrass->EncMonsNo = inMonsNo;
	outSwayGrass->EncMonsLv = inMonsLv;
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�G���J�E���g�|�P�������擾�i�i���o�[�A���x���j
 * @param	inSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * @param	outMonsNo		�G���J�E���g�����X�^�[�i���o�[�i�[��
 * @param	outMonsLv		�G���J�E���g�����X�^�[���x���i�[��
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_GetEncMonsNoLv(SWAY_GRASS_PTR inSwayGrass,  int *outMonsNo, int *outMonsLv)
{
	(*outMonsNo) = inSwayGrass->EncMonsNo;
	(*outMonsLv) = inSwayGrass->EncMonsLv;

}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�G���J�E���g���A���𒲂ׂ�
 * @param	inSwayGrass		��ꑐ�\���̂ւ̃|�C���^
 * @retval	BOOL		TRUE:�h�ꑐ�G���J�E���g���A		FALSE:�ʏ�G���J�E���g���A				
 *
 */
//-----------------------------------------------------------------------------
const BOOL SwayGrass_IsSwayEncRetern(const SWAY_GRASS_PTR inSwayGrass)
{
	return inSwayGrass->SwayEncReturn;
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ʓ��O�`�F�b�N
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inX				�������SX���W
 * @param	inZ				�������SZ���W
 * @param	inSearchX		����X���W�i���΁j
 * @param	inSearchZ		����Z���W�i���΁j
 * @param	inChainFlg		�A���t���O
 * @param	inEncTblCode	���݂̃G���J�E���g�e�[�u���R�[�h
 * @param	outInfo			��ꑐ���\���̂ւ̃|�C���^
 * 
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_CheckIO(FIELDSYS_WORK * fsys)
{
	BOOL rc;
	SWAY_GRASS_INFO *info;
	
	int i;

	if ((!fsys->SwayGrass->Valid)||(fsys->event!=NULL)){
		return;
	}
	
	//��ʓ��O�`�F�b�N
	for(i=0;i<SEARCH_AROUND;i++){
		info = &(fsys->SwayGrass->GrassInfo[i]);
		rc = BB_CullingCheck3DModelNonResQuick( &(info->GrassPos),
											 &(fsys->SwayGrass->BoundingBox) );
		if ((info->SwayGrassFlg)&&(!rc)){
			//�����ɂ���
			info->SwayGrassFlg = FALSE;
		}
	}
	//�S�����������`�F�b�N
	{
		int count;
		count = 0;
		for(i=0;i<SEARCH_AROUND;i++){
			info = &(fsys->SwayGrass->GrassInfo[i]);
			if (info->SwayGrassFlg == FALSE){
				count++;
			}
		}
		if (count == SEARCH_AROUND){
			///OS_Printf("�h�ꑐ�͖����ɂȂ�܂���\n");
			SwayGrass_InitSwayGrass(fsys->SwayGrass);			
			//�ȏI��点��
			Snd_FadeOutNextPlayCall(fsys,
									Snd_FieldBgmNoGet(fsys,fsys->location->zone_id),
									BGM_FADE_FIELD_MODE );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�L���`�F�b�N
 * @param	inSwayGrass	�h�ꑐ�\���̂ւ̃|�C���^
 *
 * @retval	BOOL	TRUE:�h�ꑐ�L��		FALSE:�h�ꑐ����
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_CheckValid( const SWAY_GRASS_PTR inSwayGrass )
{
	return inSwayGrass->Valid;
}


//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ���Z�b�g
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inPlayerHeight	���@����
 * @param	inX				�������SX���W
 * @param	inZ				�������SZ���W
 * @param	inSearchX		����X���W�i���΁j
 * @param	inSearchZ		����Z���W�i���΁j
 * @param	outInfo			��ꑐ���\���̂ւ̃|�C���^
 * 
 * @retval	BOOL			TRUE:�h�ꑐ�L��		FALSE:�h�ꑐ����
 *
 */
//-----------------------------------------------------------------------------
static BOOL SetSwayGrassInfo(	FIELDSYS_WORK * fsys,
								const fx32 inPlayerHeight,
								const int inX, const int inZ,
								const u8 inSearchX, const u8 inSearchZ,
								SWAY_GRASS_INFO *outInfo	)
{
	int x,z;
	MATR attr;
	x = (inX-SEARCH_OFFS)+inSearchX;
	z = (inZ-SEARCH_OFFS)+inSearchZ;
	//���W�ۑ�
	outInfo->GridX = x;
	outInfo->GridZ = z;
	//�A�g���r���[�g�{��
	attr = GetAttributeLSB(fsys, x, z);
	
	if (  MATR_IsGrass(attr) ){
		HEIGHT_TYPE code;
		//fx32�^�̍��W���擾
		outInfo->GrassPos.x = FX32_ONE*16*x;
		outInfo->GrassPos.z = FX32_ONE*16*z;
		outInfo->GrassPos.y = GetHeightPack(fsys,
											0, outInfo->GrassPos.x, outInfo->GrassPos.z,
											&code);
		//�������擾���āA���@�̍����Ɣ�r����
		if (inPlayerHeight != outInfo->GrassPos.y){
			//����������ł͂Ȃ��̂ŁA�͂˂�
			outInfo->SwayGrassFlg = 0;
			OS_Printf("�������Ⴄ�̂ŁA�h�ꑐ�Ƃ݂Ȃ���\n");
			return FALSE;
		}
		//�]�[���h�c���Ⴄ�ꍇ�́A�͂˂�
		{
			int zone_id;
			int block_x,block_z;
			block_x = x/BLOCK_GRID_W;
			block_z = z/BLOCK_GRID_H;
			zone_id = World_GetZoneIDFromMatrixXZ(fsys->World, block_x, block_z);
			if (fsys->location->zone_id != zone_id){
				outInfo->SwayGrassFlg = 0;
				OS_Printf("�]�[���h�c�Ⴄ�̂ŁA�h�ꑐ�Ƃ݂Ȃ���\n");
				return FALSE;
			}
		}
		

		//���Ȃ��ꑐ�t���O�𗧂Ă�
		outInfo->SwayGrassFlg = 1;
		
		return TRUE;
	}else{
		//���ł͂Ȃ��̂Ńt���O�I�t
		outInfo->SwayGrassFlg = 0;
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�`�F�b�N
 * @param	inSwayGrass	�h�ꑐ�\���̂ւ̃|�C���^
 * @param	inX			X���W
 * @param	inZ			Z���W
 * @param	outRound	�q�b�g��������
 *
 * @retval	BOOL	TRUE:�h�ꑐ�q�b�g		FALSE:�h�ꑐ�q�b�g���ĂȂ�
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckSwayGrass(	const SWAY_GRASS_PTR inSwayGrass,
							const int inX, const int inZ,
							u8 *outRound)
{
	u8 i;
	for(i=0;i<SEARCH_AROUND;i++){
		if (inSwayGrass->GrassInfo[i].SwayGrassFlg){
			if ( (inSwayGrass->GrassInfo[i].GridX == inX) &&
					(inSwayGrass->GrassInfo[i].GridZ == inZ) ){
				*outRound = i;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	��ꑐ�����`�F�b�N�ƍX�V
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^	
 * @param	inSwayGrass	��ꑐ�\���̂ւ̃|�C���^	
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
static void UpdateSwayGrassHist(FIELDSYS_WORK * fsys, SWAY_GRASS_PTR ioSwayGrass)
{
	SWAY_GRASS_HIST * hist;
	int chain;
	int i;
	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );
	chain = hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain;
	if (chain < ioSwayGrass->Chain){//�L�^�����������H
		//�X�V
		hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain = ioSwayGrass->Chain;
		hist->SwayGrassRec[ioSwayGrass->RewritePos].MonsNo = ioSwayGrass->EncMonsNo;
		//�\�[�g
		SwayGrassHist_SortHistData(hist);
		//���������ʒu�̑{��
		if (hist->SwayGrassRec[ioSwayGrass->RewritePos].Chain <= ioSwayGrass->Chain){
			//���������ʒu�����ꂽ�̂ő{��
			for(i=0;i<3;i++){
				if ( hist->SwayGrassRec[(2-i)].Chain == ioSwayGrass->Chain){
					ioSwayGrass->RewritePos = (2-i);
					return;
				}	
			}
			//�����ɂ͂��Ȃ��͂��B���Ă��܂����ꍇ�͏]���̏��������ʒu����������(���������ʒu�ύX���Ȃ�)
			GF_ASSERT(0);
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�h�ꑐ���R�[�h���̏��������ʒu���擾
 *
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^	
 *
 * @retval	u8		���������ʒu
 *
 */
//-----------------------------------------------------------------------------
static u8 GetSwayGrassMinRecordPos(FIELDSYS_WORK *fsys)
{
	SWAY_GRASS_HIST * hist;
	u8 pos;
	BOOL rc;

	hist = EncDataSave_GetSwayGrassHist( EncDataSave_GetSaveDataPtr(fsys->savedata) );

	//�����L���O������Ă��Ȃ��Ƃ��̈ʒu�擾
	for(pos=0;pos<3;pos++){
		if (hist->SwayGrassRec[pos].MonsNo == 0){
			return pos;
		}
	}

	//�����L���O�����܂��Ă���Ƃ��̈ʒu�擾
	ISMIN(rc,hist->SwayGrassRec[0].Chain,hist->SwayGrassRec[1].Chain);
	if (rc){
		pos = 0;
	}else{
		pos = 1;
	}
	ISMIN(rc,hist->SwayGrassRec[pos].Chain,hist->SwayGrassRec[2].Chain);
	if (!rc){
		pos = 2;
	}

	return pos;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�A���t���O�̌���
 *
 * @param	inRound			�O��
 * @param	inBattleResult	�퓬���� FIGHT_WIN	FIGHT_POKE_GET
 * 
 * @retval	BOOL		�A���t���O	TURE:�A������	FALSE:�A�����Ȃ�	
 *
 */
//-----------------------------------------------------------------------------
static BOOL GetChainFlg(const u8 inRound, const int inBattleResult)
{
	//�����|�P�������o�������m���Ō��߂�
	u8 *tbl;
	u8 table1[SEARCH_AROUND] = {88,68,48,28};
	u8 table2[SEARCH_AROUND] = {98,78,58,38};
	//�O��A�ߊl���Đ퓬���I���������Ńe�[�u����ύX
	if (inBattleResult == FIGHT_WIN){
		tbl = table1;
	}else if(inBattleResult == FIGHT_POKE_GET){
		tbl = table2;
	}
	if(gf_p_rand(100)<tbl[inRound]){			//�A������
		return TRUE;
	}else{		//�A�����Ȃ�
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	����h�ꑐ�N��
 *
 * @param	*fsys		�t�B�[���h�V�X�e���|�C���^
 * 
 * @retval	none	
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_Setup(FIELDSYS_WORK * fsys)
{
	int *seq;
	seq = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(int));
	(*seq) = 0;
	//�C�x���g�Z�b�g
	FieldEvent_Set(fsys, SwayGrass_SetupEvent, seq);
}

//-----------------------------------------------------------------------------
/**
 * @brief	����h�ꑐ�Z�b�g�C�x���g
 * 
 * @param	*event		�C�x���g�|�C���^
 * 
 * @retval	BOOL	TRUE:�I��	FALSE:�p��
 *
 */
//-----------------------------------------------------------------------------
BOOL SwayGrass_SetupEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int *seq = FieldEvent_GetSpecialWork(event);
	
	switch (*seq) {
	case SEQ_SWAY_SEARCH:
		{
			u8 *charge;
			//�n�a�i�|�[�Y
			FieldOBJSys_MovePauseAll( fsys->fldobjsys );
			//�|�P�T�[�`���[�g�p�\�`�F�b�N(�[�d�������Ă��邩�H)
			//�Z�[�u�f�[�^�擾
			charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
			if ( (*charge)<POKESEARCHER_CHARGE_MAX ){
				EventCall_Script(event, SCRID_POKE_SEARCHER, NULL, NULL);
				*(u16*)(GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_WK_PARAM0)) = POKESEARCHER_CHARGE_MAX-(*charge);
				(*seq) = SEQ_SWAY_END;
			}else{
				int x,z;
				//�|�P�T�[�`���[�[�d�N���A
				(*charge) = 0;
				//���@�̈ʒu�擾
				x = Player_NowGPosXGet(fsys->player);
				z = Player_NowGPosZGet(fsys->player);
				//���T�[�`
				SwayGrass_SearchSwayGrass(fsys, x, z,fsys->SwayGrass);
				if (fsys->SwayGrass->Valid){
					SwayGrass_SetChain(fsys, FIGHT_WIN, fsys->SwayGrass);	//����e�[�u���͐퓬�����ŌŒ�
					//���A�j���Z�b�g
					SwayGrass_SetSwayGrassAnime(fsys, fsys->SwayGrass);
					(*seq) = SEQ_SWAY_BGM_START;
				}else{
					(*seq) = SEQ_SWAY_NG;
				}
			}
		}
		break;
	case SEQ_SWAY_BGM_START:
		//�ȊJ�n
		//Snd_FadeOutNextPlayCall( fsys, SEQ_KUSAGASA, BGM_FADE_FIELD_MODE );
		Snd_BgmPlay( SEQ_KUSAGASA );											//06.05.18
		(*seq) = SEQ_SWAY_WAIT;
		break;
	case SEQ_SWAY_WAIT:
		//�A�j���I���҂�
		if (SwayGrass_CheckSwayGrassAnimeEnd(fsys->SwayGrass)){
			(*seq) = SEQ_SWAY_END;
		}
		break;
	case SEQ_SWAY_END:
		//�I��
		sys_FreeMemoryEz(seq);
		//OBJ�|�[�Y�N���A
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		return TRUE;
		break;
		
	case SEQ_SWAY_NG:
		// ���b�Z�[�W�\��
		EventCall_Script( event, SCRID_POKE_SEARCHER_NG, NULL, NULL );
		(*seq) = SEQ_SWAY_END;
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	���A�`�F�b�N
 * 
 * @param	inChain		�A����
 * 
 * @retval	BOOL	TRUE:���A	FALSE:�m�[�}��
 *
 */
//-----------------------------------------------------------------------------
#if 0
static BOOL CheckRare(const int inChain)
{
	int prop;
	if (inChain == 0){
		return FALSE;
	}
	
	prop = RARE_POKE_PROP_MAX - (inChain*SUB_PROP);
	if (prop < 0){
		prop = 1;
	}

	if ( gf_rand()%prop == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}
#else
static BOOL CheckRare(const int inChain)
{
	int prop;
	if (inChain == 0){
		return FALSE;
	}
	
	prop = RARE_POKE_PROP_MAX - (inChain*SUB_PROP);
	if (prop < RARE_POKE_PROP_MIN){
		prop = RARE_POKE_PROP_MIN;
	}

	if ( gf_p_rand(prop) == 0 ){
		return TRUE;
	}else{
		return FALSE;
	}
}
#endif

//-----------------------------------------------------------------------------
/**
 * @brief	�A�����X�V�i�n�Y�����������Ǔ����|�P�����ƃG���J�E���g�����Ƃ��p�j
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_UpDateChain(FIELDSYS_WORK * fsys)
{
	IncChain(&(fsys->SwayGrass->Chain));	//�A����+1
	//�h�ꑐ�G���J�E���g�����`�F�b�N�ƍX�V
	UpdateSwayGrassHist(fsys, fsys->SwayGrass);
}

#if 0
//-----------------------------------------------------------------------------
/**
 * @brief	�������������ʒu�X�V
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_ChangeHistRewritePos(FIELDSYS_WORK * fsys)
{
	fsys->SwayGrass->RewritePos = GetSwayGrassMinRecordPos(fsys);
}
#endif

//-----------------------------------------------------------------------------
/**
 * @brief	�`�F�[�����擾
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @retval	int		�`�F�[����
 *
 */
//-----------------------------------------------------------------------------
int SwayGrass_GetChain(FIELDSYS_WORK * fsys)
{
	return fsys->SwayGrass->Chain;
}

//==============================================================================
/**
 * �|�P�T�[�`���[�`���[�W<<���O���|�P�g���ɂȂ����炵���B�܂���킵���B
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 */
//==============================================================================
void SwayGrass_ChargePokeSearcher(FIELDSYS_WORK *fsys)
{
	u8 *charge;
	//�|�P�T�[�`���[�������Ă��邩�`�F�b�N
	if( MyItem_CheckItem( SaveData_GetMyItem(fsys->savedata),
							ITEM_POKETORE,1,HEAPID_FIELD) == TRUE ){
		//�Z�[�u�f�[�^�擾
		charge = EncDataSave_GetPokeSearcherCharge(EncDataSave_GetSaveDataPtr(fsys->savedata));
		if ( (*charge)<POKESEARCHER_CHARGE_MAX ){
			(*charge)++;
		}
	}
}

//==============================================================================
/**
 * �A�����̉��Z
 *
 * @param	outChain		�A�����ւ̃|�C���^
 *
 * @return	none
 */
//==============================================================================
static void IncChain(int *outChain)
{
	(*outChain)++;
	if ( (*outChain) > SWAY_GRASS_CHAIN_MAX ){
		(*outChain) = SWAY_GRASS_CHAIN_MAX;
	}
}

#ifdef PM_DEBUG
//-----------------------------------------------------------------------------
/**
 * @brief	�`�F�[�����ύX
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	n		��
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_DebugIncChain(FIELDSYS_WORK * fsys, int n)
{
	if (fsys->SwayGrass->Chain + n > SWAY_GRASS_CHAIN_MAX){
		fsys->SwayGrass->Chain = SWAY_GRASS_CHAIN_MAX;
	}else{
		fsys->SwayGrass->Chain += n;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�`�F�[�����Z�b�g
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	n		��
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_DebugSetChain(FIELDSYS_WORK * fsys, int n)
{
	if (n > SWAY_GRASS_CHAIN_MAX){
		fsys->SwayGrass->Chain = SWAY_GRASS_CHAIN_MAX;
	}else{
		fsys->SwayGrass->Chain = n;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�����擾
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * @param	inIdx	���\���̃C���f�b�N�X	0�`3
 *
 * @retval	none
 *
 */
//-----------------------------------------------------------------------------
void SwayGrass_GetGrassInfo(FIELDSYS_WORK * fsys, const u8 inIdx,
							int *outX, int *outZ, u8 *outTbl,
							BOOL *outValid, BOOL *outChainFlg, BOOL *outRare)
{
	SWAY_GRASS_INFO *info;
	GF_ASSERT(inIdx<SEARCH_AROUND);

	info = &fsys->SwayGrass->GrassInfo[inIdx];

	(*outX) = info->GridX;
	(*outZ) = info->GridZ;
	(*outTbl) = info->EncTblCode;
	(*outValid) = info->SwayGrassFlg;
	(*outChainFlg) = info->ChainFlg;
	(*outRare) = info->IsRare;


}

#endif
