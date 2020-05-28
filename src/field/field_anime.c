//=============================================================================
/**
 * @file	field_anime.c
 * @bfief	�t�B�[���h�A�j�������i��ɓ]���A�j��)
 * @author	mori GAME FREAK inc.
 *
 *
 */
//=============================================================================

#include "common.h"
#include "calctool.h"
#include "str_tool.h"
#include "system/lib_pack.h"
#include "field_anime.h"



//==============================================================================
// ��`
//==============================================================================
#define FIELD_ANIME_MAX			( 11 )	// �n�`�p�]���A�j���̓���������

#define FIELD_VRAM_ANIME_MAX	( 11 )	//�t�B�[���hVRAM�A�j����

typedef struct{						// �A�j���p�f�[�^�iROM����ǂݍ��݂܂�)
	char name[32];					// �e�N�X�`���t�@�C����
	u16	 AnmTbl[10][2];				// �A�j���p�e�[�u��[0]:�p�^�[���ԍ�  [1]:wait
}FIELD_ANIME;

struct _FIELD_ANIME_WORK{
	u8  			*texadr;		// ���ɓ]������Ă���e�N�X�`���A�h���X
	int 			texsize;		// �]������e�N�X�`���T�C�Y
	NNSG3dResTex 	*animetex;		// �]������e�N�X�`�����\�[�X�̃|�C���^
	void			*texfile;		// �e�N�X�`���t�@�C���̎���
	FIELD_ANIME		*animetbl;		// �A�j���[�V������`�e�[�u���̃|�C���^
	u16				point,wait;		// ���݂̕\���|�C���^,�E�F�C�g
}FIELD_ANIME_WORK;

static const char *FieldVRAMAnime[FIELD_VRAM_ANIME_MAX] = {
	"sea",
	"rhana",
	"asasea",
	"hamabe",
	"asahamabe",
	"t3_fl_b.1",
	"t3_fl_p.1",
	"t3_fl_r.1",
	"t3_fl_y.1",
	"dun_sea",
	"lakep.1",	
};

//==============================================================================
// ���[�N
//==============================================================================

//FIELD_ANIME_WORK	FieldAnimeWork[FIELD_ANIME_MAX];


//==============================================================================
// �֐�
//==============================================================================

//==============================================================================
/**
 * ������
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
FIELD_ANIME_PTR InitFieldAnime(void)
{
	int i;
	FIELD_ANIME_PTR faw=NULL;
	
	faw = sys_AllocMemory(HEAPID_FIELD,sizeof(FIELD_ANIME_WORK)*FIELD_ANIME_MAX);
	
	if(faw!=NULL){
		for(i=0;i<FIELD_ANIME_MAX;i++){
			faw[i].point = 0;
			faw[i].wait  = 0;
			faw[i].texadr  = NULL;
			faw[i].animetex  = NULL;
			faw[i].animetbl  = NULL;
			faw[i].texfile = NULL;
		}
	}
	return faw;
}


//114 892
// 34%


//------------------------------------------------------------------
/**
 * �t�B�[���h�]���A�j���o�^
 *
 * @param   tex			����VRAM�ɓ]���ς݂̃e�N�X�`���Ǘ��|�C���^
 * @param   Tindex		��̃e�N�X�`���̎w��index
 * @param   AnimeNo		�]�����s�������e�N�X�`���A�j���ԍ��i���ꂪ�t�@�C�����ɂȂ�)
 *
 * @retval  int 		�o�^�ł�����0-10 �ł��Ȃ�������-1
 */
//------------------------------------------------------------------
int FieldAnimeSets(FIELD_ANIME_PTR faw, NNSG3dResTex *tex)
{
	int i,result=0;
	for (i=0;i<FIELD_VRAM_ANIME_MAX;i++){
		if(FieldAnimeSet(faw, tex, FieldVRAMAnime[i], i)>=0){
			result++;
		}
	}
	return result;
}


//------------------------------------------------------------------
/**
 * �t�B�[���h�]���A�j���o�^
 *
 * @param   tex			����VRAM�ɓ]���ς݂̃e�N�X�`���Ǘ��|�C���^
 * @param   Tindex		��̃e�N�X�`���̎w��index
 * @param   AnimeNo		�]�����s�������e�N�X�`���A�j���ԍ��i���ꂪ�t�@�C�����ɂȂ�)
 *
 * @retval  int 		�o�^�ł�����0-10 �ł��Ȃ�������-1
 */
//------------------------------------------------------------------
int 	FieldAnimeSet(FIELD_ANIME_PTR faw, NNSG3dResTex *tex, const char *name, int AnimeNo)
{
	int  no,i;
	char filename[40];
	
	if(faw==NULL){								//�m�ۂ���ĂȂ��̂ɌĂ΂�Ă邩������Ȃ��̂�
		return -1;
	}

	for(no=0;no<FIELD_ANIME_MAX;no++){				//�g�p���Ă��Ȃ����[�N������
		if(faw[no].texfile==NULL){
			break;
		}
	}
	if(no==FIELD_ANIME_MAX || tex==NULL){			//�o�^MAX �������͒n�`�e�N�X�`����NULL��������o�^���~
		return -1;
	}


	faw[no].texadr   = GetTexStartVRAMAdrByName(tex,name);	//�]���ςݒn�`�e�N�X�`������]���ΏۂƂȂ�ꏊ���擾����
	if (faw[no].texadr == NULL){
		return -1;			//�e�N�X�`�����Ȃ�������o�^���~
	}

	faw[no].texsize  = GetTexByteSizeByName(tex,name);
	
	sprintf(filename,"data/fld_anime%d.bin",AnimeNo);				
	faw[no].animetbl = sys_LoadFile(HEAPID_FIELD,filename);
	
	OS_Printf("field_anime animetbl=%08x\n",faw[no].animetbl);
//	OS_Printf("texname=%s\n",FieldAnimeWork[no].animetbl->name);
//	for(i=0;i<10;i++){
//		if(FieldAnimeWork[no].animetbl->AnmTbl[i][0]!=0xffff){
//			OS_Printf("anime[i] = %d, wait = %d\n",FieldAnimeWork[no].animetbl->AnmTbl[i][0],FieldAnimeWork[no].animetbl->AnmTbl[i][1]);
//		}else{
//			break;
//		}
//	}
	
	//�]���A�j���e�N�X�`���ǂݍ���
	faw[no].texfile   = sys_LoadGraphFile(faw[no].animetbl->name,HEAPID_FIELD);
	faw[no].animetex  = NNS_G3dGetTex((NNSG3dResFileHeader*) faw[no].texfile );

	return no;
}



//==============================================================================
/**
 * �t�B�[���h�p�e�N�X�`���]���A�j���풓�֐�
 *
 * @param   none		
 *
 * @retval  none		
 */
//==============================================================================
void FieldAnimeMain(FIELD_ANIME_PTR faw)
{
	int i;
	
	if(faw==NULL){								//�m�ۂ���ĂȂ��̂ɌĂ΂�Ă邩������Ȃ��̂�
		return;
	}
	
	for(i=0;i<FIELD_ANIME_MAX;i++){				//�g�p���Ă��Ȃ����[�N������
		if(faw[i].texfile==NULL){
			continue;							//�����Z�b�g����Ă��Ȃ��ꍇ�̓X���[
		}

		//>>add
		if (faw[i].animetbl == NULL){
			continue;
		}
		//<<
		
		if(faw[i].animetbl->AnmTbl[faw[i].point][1] <= faw[i].wait){	//�A�j���X�V�^�C�~���O�̎�
			faw[i].wait = 0;						//�E�F�C�g�N���A
			faw[i].point++;						//�|�C���g�{�{
			if(faw[i].animetbl->AnmTbl[faw[i].point][0]==0xffff){					//�A�j����`���[�܂ł��Ă���ꍇ�̓��[�v
				faw[i].point = 0;
			}
			AddVramTransferManager(
					NNS_GFD_DST_3D_TEX_VRAM,		//�]���Z�b�g
					(u32)faw[i].texadr,
					GetTexStartAdr(faw[i].animetex,faw[i].animetbl->AnmTbl[faw[i].point][0]),
					faw[i].texsize);	
//			OS_Printf("i=%d, point=%d pat=%04x\n",i,faw[i].point,faw[i].animetbl->AnmTbl[faw[i].point][0]);
		}else{
			faw[i].wait++;			//�E�F�C�g�X�V
		}
	}
}



//==============================================================================
/**
 * �ʂɃe�N�X�`���]���A�j�������
 *
 * @param   no		faw[]�̓Y��
 *
 * @retval  none	
 */
//==============================================================================
void FieldAnimeRelease(FIELD_ANIME_PTR faw, int no )
{
	// �e�N�X�`���t�@�C���̉���̓L���b�V���ɐς܂�Ă���̂ōs��Ȃ�
	

	if(faw==NULL){								//�m�ۂ���ĂȂ��̂ɌĂ΂�Ă邩������Ȃ��̂�
		return;
	}

	// �A�j���[�V������`�e�[�u���̉��
	if(faw[no].animetbl!=NULL){
//		NNS_FndCheckExpHeap((void*)faw[no].animetbl,NNS_FND_HEAP_ERROR_PRINT);
		sys_FreeMemoryEz(faw[no].animetbl);
		faw[no].animetbl = NULL;
	}
	faw[no].point = 0;	//�A�j���p���[�N�̏�����
	faw[no].wait  = 0;
}

//==============================================================================
/**
 * �e�N�X�`���A�j���]���V�X�e���I��
 *
 * @param   none
 *
 * @retval  none
 */
//==============================================================================
void FieldAnimeAllRelease(FIELD_ANIME_PTR faw)
{
	int i;
	
	if(faw==NULL){								//�m�ۂ���ĂȂ��̂ɌĂ΂�Ă邩������Ȃ��̂�
		return;
	}	
	
	for(i=0;i<FIELD_ANIME_MAX;i++){
		FieldAnimeRelease( faw, i );
	}
}

//==============================================================================
/**
 * �t�B�[���h�]���A�j���V�X�e�����
 *
 * @param   faw		
 *
 * @retval  none		
 */
//==============================================================================
void ReleaseFieldAnime(FIELD_ANIME_PTR faw)
{
	if(faw!=NULL){
		sys_FreeMemoryEz(faw);
		faw = NULL;
	}
}
