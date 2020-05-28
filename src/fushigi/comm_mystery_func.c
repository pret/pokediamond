#include "common.h"
#include "system/main.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/arc_util.h"
#include "system/bmp_list.h"
#include "system/msgdata_util.h"

#include "comm_mystery_func.h"


//--------------------------------------------------------------------------------------------
/**
 * VRAM������
 *
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CommMysteryFunc_VramBankSet(void)
{
  GF_BGL_DISPVRAM vramSetTable = {
    GX_VRAM_BG_128_C,				// ���C��2D�G���W����BG
    GX_VRAM_BGEXTPLTT_NONE,			// ���C��2D�G���W����BG�g���p���b�g
    GX_VRAM_SUB_BG_32_H,			/* �T�u2D�G���W����BG */
    GX_VRAM_SUB_BGEXTPLTT_NONE,		/* �T�u2D�G���W����BG�g���p���b�g */
    GX_VRAM_OBJ_64_E,				// ���C��2D�G���W����OBJ
    GX_VRAM_OBJEXTPLTT_NONE,		// ���C��2D�G���W����OBJ�g���p���b�g
    GX_VRAM_SUB_OBJ_16_I,			// �T�u2D�G���W����OBJ
    GX_VRAM_SUB_OBJEXTPLTT_NONE,	// �T�u2D�G���W����OBJ�g���p���b�g
    GX_VRAM_TEX_0_B,				// �e�N�X�`���C���[�W�X���b�g
    GX_VRAM_TEXPLTT_01_FG			// �e�N�X�`���p���b�g�X���b�g
  };
  GF_Disp_SetBank( &vramSetTable );
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	BG������
 * @param	none
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void CommMysteryFunc_BgInit( GF_BGL_INI * ini )
{
  {	/* BG SYSTEM */
    GF_BGL_SYS_HEADER BGsys_data = {
      GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
    };
    GF_BGL_InitBG( &BGsys_data );
  }

  {	/* MAIN DISP BG0 */
    GF_BGL_BGCNT_HEADER MBg0_Data = {
      0, 0, 0x0800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_01, 1, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME0_M, &MBg0_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME0_M );
  }

  {	/* MAIN DISP BG1 */
    GF_BGL_BGCNT_HEADER MBg1_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xe800, GX_BG_CHARBASE_0x08000,
      GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME1_M, &MBg1_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME1_M );
  }

  {	/* MAIN DISP BG2 */
    GF_BGL_BGCNT_HEADER MBg2_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x00000,
      GX_BG_EXTPLTT_23, 0, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME2_M, &MBg2_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME2_M );
  }

  {	/* MAIN DISP BG3 */
    GF_BGL_BGCNT_HEADER MBg3_Data = {
      0, 0, 0x800, 0,
      GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
      GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x0c000,
      GX_BG_EXTPLTT_23, 3, 0, 0, FALSE
    };
    GF_BGL_BGControlSet( ini, GF_BGL_FRAME3_M, &MBg3_Data, GF_BGL_MODE_TEXT );
    GF_BGL_ScrClear( ini, GF_BGL_FRAME3_M );
  }
}


//------------------------------------------------------------------
/**
 * @brief	��������̂����炦�邩�`�F�b�N
 * @param	NONE
 * @return	NONE
 */
//------------------------------------------------------------------
int CommMysteryFunc_CheckGetGift(SAVEDATA *sv, GIFT_COMM_PACK *gcp)
{
  u32 version;
  FUSHIGI_DATA *fdata = SaveData_GetFushigiData(sv);

#if 0
  // �f�o�b�O�p�̋����G���[�����R�[�h
  return COMMMYSTERYFUNC_ERROR_GROUNDCHILD;
#endif
#ifdef DEBUG_ONLY_FOR_mituhara
  OS_TPrintf("�E�����r�[�R���̃o�[�W������ %08X �ł�\n", gcp->beacon.version);
  OS_TPrintf("��x�����󂯎��Ȃ��t���O: %d\n", gcp->beacon.only_one_flag);
  OS_TPrintf("�J�[�h�t����������̃t���O: %d\n", gcp->beacon.have_card);
  OS_TPrintf("���z�z�t���O: %d\n", gcp->beacon.groundchild_flag);
#endif

  
  version = gcp->beacon.version;
  
  // �f�o�b�O�p�̂ӂ����Ȃ�������̏�������
  if(version == 0xFFFFFFFF && gcp->beacon.event_id == 0xFFFF){
    FUSHIGIDATA_Init(fdata);
    SaveData_SaveParts(sv, SVBLK_ID_NORMAL);
    OS_ResetSystem(0); 
  }
  
  // �Ώۃo�[�W�������O�Ȃ�ΑS�Ẵo�[�W�����Ŏ󂯎���
  if(version == 0)
    version = ~0;

  // �Ώۃo�[�W�����Ɋ܂܂�Ă��邩�`�F�b�N
  if((version & (1 << PM_VERSION)) == FALSE)
    return COMMMYSTERYFUNC_ERROR_VERSION;

  // ��x�����󂯎��Ȃ���������̂́A
  if(gcp->beacon.only_one_flag == TRUE &&
     // ���łɎ󂯎���Ă��邩���ׂ�
     FUSHIGIDATA_IsEventRecvFlag(fdata, gcp->beacon.event_id) == TRUE)
    return COMMMYSTERYFUNC_ERROR_HAVE;

  // �J�[�h�t����������̂�
  if(gcp->beacon.have_card == TRUE &&
     // �J�[�h��񂪃Z�[�u�ł��邩�`�F�b�N
    FUSHIGIDATA_CheckCardDataSpace(fdata) == FALSE)
    return COMMMYSTERYFUNC_ERROR_FULLCARD;

  // ����ɔz�B����񂪊܂܂�Ă��邨������̂�
  // �z�B���̃X���b�g���`�F�b�N����
  if(FUSHIGIDATA_CheckDeliDataSpace(fdata) == FALSE)
    return COMMMYSTERYFUNC_ERROR_FULLGIFT;

  // ���z�z�̃`�F�b�N
  if(gcp->beacon.groundchild_flag == 1)
    return COMMMYSTERYFUNC_ERROR_GROUNDCHILD;

  return COMMMYSTERYFUNC_ERROR_NONE;
}


/*  */
