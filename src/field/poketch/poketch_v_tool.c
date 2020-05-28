//============================================================================================
/**
 * @file	poketch_v_tool.c
 * @bfief	�|�P�b�`�@�`��R�}���h�֘A�̋��ʏ���
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"
#include "field\poketch.h"

#include "poketch_prv.h"
#include "poketch_view.h"


//===========================================================
// �`��R�}���h���[�N�i�O���ɍ\���͔���J�j
//===========================================================
struct _POKETCH_CMD_WORK {
	u32       cmd;		// �R�}���h�i���o�[��ۑ��i���������s�j
	u32       seq;		// �R�}���h�����̃V�[�P���X�Ƃ��Ďg��
	void      *vwk;		// �`�惂�W���[�����[�N�ւ̃|�C���^
	void      *wk;		// �Ǝ����[�N�ւ̃|�C���^
	const void *vpara;	// �`��p�����[�^�\���̂ւ̃|�C���^
	TCB_PTR   tcb;
};
//===========================================================
// �萔
//===========================================================
#define STORE_MAGIC_NUMBER	(0x12345678)

//==============================================================
// Prototype
//==============================================================
static BOOL StoreCmd(POKETCH_CMD_STORE *store, u32 cmd);
static void DeleteCmd(POKETCH_CMD_STORE *store, u32 cmd);


//------------------------------------------------------------------
/**
 * �ғ����R�}���h�̕ۑ��e�[�u����������
 *
 * @param   store		�ۑ��e�[�u���A�h���X
 * @param   max			�ۑ��e�[�u���v�f���i�w�b�_�������j
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_CmdStoreInit(POKETCH_CMD_STORE *store, u32 max)
{
	u32 i;

	store[CMD_STOREWK_MAX] = max;
	store[CMD_STOREWK_MAGICNUMBER] = STORE_MAGIC_NUMBER;


	for(i = 0; i < max; i++)
	{
		store[ CMD_STORE_HEADER_SIZE + i ] = CMD_NULL;
	}
}
//------------------------------------------------------------------
/**
 * �ғ����R�}���h���e�[�u���ɕۑ�
 *
 * @param   store		�ۑ��e�[�u���A�h���X
 * @param   cmd			�R�}���h�i���o�[
 *
 */
//------------------------------------------------------------------
static BOOL StoreCmd(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	GF_ASSERT( store[CMD_STOREWK_MAGICNUMBER] == STORE_MAGIC_NUMBER );

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == CMD_NULL)
		{
			store[ CMD_STORE_HEADER_SIZE + i] = cmd;
			return TRUE;
		}
	}
	OS_TPrintf("�R�}���h�����ς���\n");
	return FALSE;
}
//------------------------------------------------------------------
/**
 * �ғ����R�}���h�폜
 *
 * @param   store		
 * @param   cmd			
 *
 */
//------------------------------------------------------------------
static void DeleteCmd(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	GF_ASSERT( store[CMD_STOREWK_MAGICNUMBER] == STORE_MAGIC_NUMBER );

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == cmd)
		{
			store[ CMD_STORE_HEADER_SIZE + i] = CMD_NULL;
			return;
		}
	}

	GF_ASSERT(0);

}
//------------------------------------------------------------------
/**
 * �`��R�}���h�̏I���҂��i�P�Ɓj
 *
 * @param   store		�ғ����R�}���h��ۑ����Ă���e�[�u��
 * @param   cmd			�R�}���h�i���o�[
 *
 * @retval  BOOL		TRUE�ŏI���^FALSE�Ōp����
 */
//------------------------------------------------------------------
BOOL PoketchViewTool_WaitCommand(POKETCH_CMD_STORE *store, u32 cmd)
{
	u32 i;

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] == cmd)
		{
			return FALSE;
		}
	}

	return TRUE;
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�̏I���҂��i�S���j
 *
 * @param   store		�ғ����R�}���h��ۑ����Ă���e�[�u��
 *
 * @retval  BOOL		TRUE�ŏI���^FALSE�Ōp����
 */
//------------------------------------------------------------------
BOOL PoketchViewTool_WaitCommandAll(POKETCH_CMD_STORE *store)
{
	u32 i;

	for(i = 0; i < store[CMD_STOREWK_MAX]; i++)
	{
		if(store[CMD_STORE_HEADER_SIZE + i] != CMD_NULL)
		{
			return FALSE;
		}
	}
	return TRUE;
}


//------------------------------------------------------------------
/**
 * �`��R�}���h�̃Z�b�g
 *
 * @param   cmd_tbl		�R�}���h�e�[�u���z��
 * @param   cmd			�R�}���h�i���o�[
 * @param   view_wk		�`�惂�W���[���̃��[�N�A�h���X
 * @param   store		�ғ����̕`��R�}���h�i���o�[��ۑ����Ƃ��z��
 * @param   taskpri		�R�}���h�����s����^�X�N�v���C�I���e�B
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetCommand(const POKETCH_VIEW_CMD *cmd_tbl, u32 cmd, void *view_wk,
		const void *vpara, POKETCH_CMD_STORE *store, u32 taskpri, u32 heapID)
{
	u32 i;

	for(i = 0; cmd_tbl[i].cmd != CMD_NULL; i++)
	{
		if(cmd_tbl[i].cmd == cmd)
		{
			POKETCH_CMD_WORK *cwk;
			u32 work_size;

			work_size = sizeof(POKETCH_CMD_WORK) + cmd_tbl[i].work_size;
			cwk = sys_AllocMemory( heapID, work_size );

			if(cwk != NULL)
			{
				// �R�}���h�Ǝ����[�N�́A�K�v�Ȃ狤�ʃ��[�N�̌�ɑ����Ċm�ۂ��Ă���
				if( cmd_tbl[i].work_size != 0)
				{
					cwk->wk = ((u8*)cwk) + sizeof(POKETCH_CMD_WORK);
				}
				else
				{
					cwk->wk = NULL;
				}

				if( StoreCmd( store, cmd ) )
				{
					cwk->vwk = view_wk;
					cwk->seq = 0;
					cwk->cmd = cmd;
					cwk->vpara = vpara;

					cwk->tcb = TCB_Add( cmd_tbl[i].func, cwk, taskpri);
					if( cwk->tcb )
					{
						cmd_tbl[i].func( cwk->tcb, cwk );
					}
				}
				else
				{
					sys_FreeMemoryEz( cwk );
				}
				return;
			}
			else
			{
				GF_ASSERT(0);
				break;
			}
		}
	}

	GF_ASSERT(0);
}
//------------------------------------------------------------------
/**
 * �`��R�}���h�폜
 *
 * @param   store			�ғ����R�}���h�ۑ��e�[�u��
 * @param   cmd_work		�R�}���h���[�N
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_DelCommand(POKETCH_CMD_STORE *store, POKETCH_CMD_WORK *cwk)
{
	DeleteCmd(store, cwk->cmd);
	TCB_Delete(cwk->tcb);
	sys_FreeMemoryEz( cwk );
}


//------------------------------------------------------------------
/**
 * �R�}���h���[�N����`�惂�W���[�����[�N�A�h���X��Ԃ�
 *
 * @param   cwk			�R�}���h���[�N
 *
 * @retval  void*		�`�惂�W���[�����[�N�A�h���X
 */
//------------------------------------------------------------------
void* PoketchViewTool_GetViewWork(POKETCH_CMD_WORK *cwk)
{
	return cwk->vwk;
}

//------------------------------------------------------------------
/**
 * �R�}���h���[�N����`��p�����[�^�A�h���X��Ԃ�
 *
 * @param   cwk				�R�}���h���[�N
 *
 * @retval  const void*		�`��p�����[�^�A�h���X
 */
//------------------------------------------------------------------
const void* PoketchViewTool_GetViewParam(POKETCH_CMD_WORK *cwk)
{
	return cwk->vpara;
}

//------------------------------------------------------------------
/**
 * �R�}���h���[�N����R�}���h�Ǝ����[�N�A�h���X��Ԃ�
 *
 * @param   cwk			�R�}���h���[�N
 *
 * @retval  void*		�R�}���h�Ǝ����[�N�A�h���X
 */
//------------------------------------------------------------------
void* PoketchViewTool_GetCmdWork(POKETCH_CMD_WORK *cwk)
{
	return cwk->wk;
}

//------------------------------------------------------------------
/**
 * �R�}���h���[�N����V�[�P���X�i���o�[��Ԃ�
 *
 * @param   cwk		�R�}���h���[�N
 *
 * @retval  u32		�V�[�P���X�i���o�[
 */
//------------------------------------------------------------------
u32 PoketchViewTool_GetSeq(POKETCH_CMD_WORK *cwk)
{
	return cwk->seq;
}

//------------------------------------------------------------------
/**
 * �R�}���h���[�N�̃V�[�P���X�i���o�[��i�߂�
 *
 * @param   cwk		�R�}���h���[�N
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_FwdSeq(POKETCH_CMD_WORK *cwk)
{
	cwk->seq++;
}

//------------------------------------------------------------------
/**
 * �R�}���h���[�N�̃V�[�P���X�i���o�[���Z�b�g
 *
 * @param   cwk		�R�}���h���[�N
 * @param   seq		�V�[�P���X�i���o�[
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetSeq(POKETCH_CMD_WORK* cwk, u32 seq )
{
	cwk->seq = seq;
}


//------------------------------------------------------------------
/**
 * �R���R�ȏ�̃E�B���h�E��X�N���[���f�[�^���o�b�t�@�ɍ쐬
 *
 * @param   buf		
 * @param   charno		
 * @param   width		
 * @param   height		
 * @param   chardata_width		
 * @param   palno		
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_MakeWindowScrn( u16 *buf, u32 charno, u32 width, u32 height, u32 chardata_width, u32 palno )
{
	u32 i, j, max;

	palno <<= 12;

	buf[0] = palno | charno;
	for(i = 1; i < (width - 1); i++){
		buf[ i ] = palno | (charno + 1);
	}
	buf[ i ] = palno | (charno + 2);

	buf += width;
	charno += chardata_width;
	for(j = 1; j < (height - 1); j++)
	{
		buf[ 0 ] = palno | charno;
		for(i = 1; i < (width-1); i++)
		{
			buf[ i ] = palno | (charno + 1);
		}
		buf[ i ] = palno | (charno + 2);
		buf += width;
	}

	charno += chardata_width;
	buf[0] = palno | charno;
	for(i = 1; i < (width - 1); i++){
		buf[ i ] = palno | (charno + 1);
	}
	buf[ i ] = palno | (charno + 2);


}

//------------------------------------------------------------------
/**
 * �Q�~�Q�̃u���b�N��X�N���[���f�[�^���ޯ̧�ɍ쐬
 *
 * @param   buf			�ޯ̧�擪���ڽ
 * @param   scr_x		�����o���J�nX���W�i��גP�ʁj
 * @param   scr_y		�����o���J�nY���W�i��גP�ʁj
 * @param   scr_w		�ޯ̧�̉����ށi�L�����P�ʁj
 * @param   charno		�u���b�N��L�����f�[�^�̐擪�i���o�[
 * @param   chardata_width		�L�����f�[�^���T�C�Y
 * @param   palno		�p���b�g�i���o�[
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_MakeBlockScrn( u16 *buf, u32 scr_x, u32 scr_y, u32 scr_w, u32 charno, u32 chardata_width, u32 palno )
{
	palno <<= 12;

	buf += (( scr_w * scr_y ) + scr_x );

	buf[0] = palno | charno;
	buf[1] = palno | (charno + 1);
	buf[scr_w] = palno | (charno + chardata_width);
	buf[scr_w+1] = palno | (charno + chardata_width + 1);
}

//------------------------------------------------------------------
/**
 * �J���[�f�[�^���|�P�b�`�S�F�J���[�ɕϊ�
 *
 * @param   col		�J���[�f�[�^�A�h���X
 * @param   max		�ϊ��J���[��
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_TransformColorData( u16* col, u32 max )
{
	u16*  palDat;

	palDat = sys_AllocMemory(POKETCH_APP_VIEW_HEAPID, 0x20);
	if(palDat)
	{
		static const u8 palpos[] = {
			POKETCH_DEFAULTCOLOR_L4_POS,POKETCH_DEFAULTCOLOR_L3_POS,
			POKETCH_DEFAULTCOLOR_L2_POS,POKETCH_DEFAULTCOLOR_L1_POS
		};

		u32 i, r, g, b, l;

		PoketchView_GetColorPalette( palDat );

		for(i=0; i<max; i++)
		{
			r = (col[i] & GX_RGB_R_MASK) >> GX_RGB_R_SHIFT;
			g = (col[i] & GX_RGB_G_MASK) >> GX_RGB_G_SHIFT;
			b = (col[i] & GX_RGB_B_MASK) >> GX_RGB_B_SHIFT;

			l = ((r*299)+(g*587)+(b*114))/1000;	// �P�x�v�Z�Bl = 0~31 �ȃn�Y�B
			l >>= 3;	// l = 0~3 �͈̔͂ɗ��Ƃ�
			if(l>3){	// �O�̂���
				l = 3;
			}

			col[i] = palDat[palpos[l]];
		}
		sys_FreeMemoryEz(palDat);
	}
}
//------------------------------------------------------------------
/**
 * �P�F�J���[�f�[�^������Ďw��ʒu�ɓ]��
 *
 * @param   colno	�F�ԍ��i0~3�j
 * @param   palno	�]���ʒu(0~15�j
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_TransSingleColorData( u32 colno, u32 palno )
{
	u16*  palDat;

	palDat = sys_AllocMemory(POKETCH_APP_VIEW_HEAPID, 0x20);
	if(palDat)
	{
		u16*  tmp_pal = sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, 0x20 );

		PoketchView_GetColorPalette( palDat );

		if(tmp_pal)
		{
			int i;

			for(i=0; i<16; i++)
			{
				tmp_pal[i] = palDat[ colno ];
			}

			DC_FlushRange( tmp_pal, 0x20 );
			GXS_LoadOBJPltt( tmp_pal, palno*0x20, 0x20 );
			sys_FreeMemoryEz(tmp_pal);
		}
		sys_FreeMemoryEz(palDat);
	}
}
//------------------------------------------------------------------
/**
 * �|�P�����A�C�R���̃J���[�f�[�^���|�P�b�`�S�F�J���[�����ē]��
 *
 * @param   palno		�]����p���b�g�i���o
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetupPokeIconPalette( u32 palno )
{
	void* palBuf;
	NNSG2dPaletteData* palData;

	palBuf = ArcUtil_PalDataGet(ARC_POKEICON, PokeIconPalArcIndexGet(),  &palData, HEAPID_POKETCH_APP);
	if(palBuf)
	{
		PoketchViewTool_TransformColorData( palData->pRawData, 4*0x10 );
		DC_FlushRange( palData->pRawData, 4*0x20 );
		GXS_LoadOBJPltt( palData->pRawData, palno*0x20, 4*0x20 );
		sys_FreeMemoryEz(palBuf);
	}

}

//------------------------------------------------------------------
/**
 * �|�P�����A�C�R����CGX�f�[�^��]��
 *
 * @param   charno		�]����L�����i���o
 * @param   datIdx		�]������A�C�R���f�[�^ID�̔z��
 * @param   max			���̕��]�����邩�idatIdx�z��v�f���j
 * @param   anmFlag		�A�j�������邩
 *
 */
//------------------------------------------------------------------
void PoketchViewTool_SetupPokeIconCgx( u32 charno, const u32* datIdx, u32 max, BOOL anmFlag )
{
	enum {
		CGX_HEADER_SIZE = 0x80,
		CGX_BYTESIZE_NO_ANM = 16*0x20,
		CGX_BYTESIZE_ANM    = CGX_BYTESIZE_NO_ANM*2,
		CGX_BUFSIZE_NO_ANM  = CGX_BYTESIZE_NO_ANM  + CGX_HEADER_SIZE,
		CGX_BUFSIZE_ANM     = CGX_BYTESIZE_ANM + CGX_HEADER_SIZE,
	};

	static const u16 transSize[2] = { CGX_BYTESIZE_NO_ANM, CGX_BYTESIZE_ANM };
	static const u16 bufSize[2]   = { CGX_BUFSIZE_NO_ANM,  CGX_BUFSIZE_ANM  };

	u8 *readbuf;

	readbuf = sys_AllocMemory( HEAPID_POKETCH_APP, bufSize[anmFlag] );

	if( readbuf )
	{
		ARCHANDLE* arcHandle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_POKETCH_APP );

		if(arcHandle)
		{
			NNSG2dCharacterData* charData;
			u32 i;

			for(i=0; i<max; i++)
			{
				ArchiveDataLoadOfsByHandle( arcHandle, datIdx[i], 0, bufSize[anmFlag], readbuf );
				NNS_G2dGetUnpackedCharacterData( readbuf, &charData );
				DC_FlushRange( charData->pRawData, transSize[anmFlag] );
				GXS_LoadOBJ( charData->pRawData, (charno*0x20)+(transSize[anmFlag]*i), transSize[anmFlag] );
			}
			ArchiveDataHandleClose(arcHandle);
		}
		sys_FreeMemoryEz(readbuf);
	}

}



//------------------------------------------------------------------
/**
 * �T�uBG1�e�X�g�p�X�N���[���f�[�^�쐬�i���i�łɂ͓���Ȃ��j
 *
 * @param   app_no		�A�v���i���o�[
 *
 */
//------------------------------------------------------------------
void PoketchView_TestScreenMake( GF_BGL_INI* bgl, u32  app_no, u32 bg_frame )
{
	extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);

	#define SET_SCR(scrn, n)	{ 							\
									u32  base = (((n) / 4) * 16) + (((n) & 3) * 2);	\
									(scrn)[0] = base;								\
									(scrn)[1] = base + 1;							\
									(scrn)[2] = base + 8;							\
									(scrn)[3] = base + 9;							\
								}

	enum {
		WRITE_XPOS = 9,
		WRITE_YPOS = 11,
	};
	
	u16  scrn[4];
	u32  no;

	SET_SCR(scrn, 1);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+0, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, 2);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+2, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, 3);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+4, WRITE_YPOS, 2, 2 );

	no = app_no / 10;
	app_no -= (no * 10);
	no += 4;
	app_no += 4;

	SET_SCR(scrn, no);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+6, WRITE_YPOS, 2, 2 );

	SET_SCR(scrn, app_no);
	GF_BGL_ScrWrite(  bgl, bg_frame, scrn, WRITE_XPOS+8, WRITE_YPOS, 2, 2 );


	#undef SET_SCR
}

