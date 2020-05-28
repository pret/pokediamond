//============================================================================================
/**
 * @file	window.c
 * @brief	�E�B���h�E�\��
 * @author	Hiroyuki Nakamura
 * @date	2005.10.13
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/lib_pack.h"
#include "system/winframe.naix"
#include "system/menu_gra.naix"
#include "system/softsprite.h"
#include "system/clact_tool.h"
#include "system/gra_tool.h"
#include "system/pmfprint.h"
#include "poketool/poke_tool.h"
#include "field/field_board.naix"
#include "../field/field_clact.h"
#include "../field/field_cutin.naix"

#define WINDOW_H_GLOBAL
#include "system/window.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	MAKE_CURSOR_CGX_SIZ		( 0x20*4*3 )	// ����J�[�\���T�C�Y

// �ŔE�B���h�E�}�b�v�J�n�A�[�J�C�uID
#define	BOARD_TOWNMAP_START		( NARC_field_board_board_town_dmy_NCGR )	// �X
#define	BOARD_ROADMAP_START		( NARC_field_board_board_road000_NCGR )		// ��

#define	TIMEWAIT_ICON_SIZE	( 0x20 * 4 * 8 )	// �ҋ@�A�C�R���̃T�C�Y
#define	TIMEWAIT_WAIT		( 16 )				// �ҋ@�A�C�R���̃A�j���E�F�C�g

// �ҋ@�A�C�R�����[�N
typedef struct {
	GF_BGL_BMPWIN * win;			// �\������BMP
	u8	cgx[TIMEWAIT_ICON_SIZE];	// �J�[�\���L�����쐬�̈�
	u8	backup[0x20*4];				// �L�����o�b�N�A�b�v�̈�
	u16	cgxpos;						// ��b�E�B���h�E�̓]���ʒu
	u8	cnt;						// �J�E���^
	u8	pat:7;						// �A�j���ԍ�
	u8	seq:2;						// �V�[�P���X
}TIMEWAIT_ICON;

// �|�P�����\���E�B���h�E���[�N
typedef struct {
	FIELD_CLACT fcat;		// �t�B�[���h�Z���A�N�^�[���[�N
	CATS_ACT_PTR	cap;	// �Z���A�N�^�[
	GF_BGL_INI * bgl;		// BGL
	u8	frm;				// �`��t���[��
	u8	px;					// �\��X���W
	u8	py;					// �\��Y���W
	u8	cmd;				// �O���R�}���h
}POKEWIN_WORK;

#define	POKEWIN_CLA_CHR_ID	( 89301 )	// �|�P�����Z���A�N�^�[�̃L�������\�[�XID
#define	POKEWIN_CLA_PAL_ID	( 89301 )	// �|�P�����Z���A�N�^�[�̃p���b�g���\�[�XID
#define	POKEWIN_CLA_CEL_ID	( 89301 )	// �|�P�����Z���A�N�^�[�̃Z�����\�[�XID
#define	POKEWIN_CLA_ANM_ID	( 89301 )	// �|�P�����Z���A�N�^�[�̃Z���A�j�����\�[�XID

#define	POKEWIN_OBJCGX_SIZ		( 32*10*10 )				// �|�P����OBJ��CGX�T�C�Y�i�P�p�^�[���j
#define	POKEWIN_OBJCGX_SIZ_ALL	( POKEWIN_OBJCGX_SIZ*2 )	// �|�P����OBJ��CGX�T�C�Y�i�S�́j


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void CursorCgxMake( GF_BGL_BMPWIN * win, u16 cgxnum );

static void BoardMapCgxSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 type, u16 map, u32 heap );

static void TimeWaitIconPut( TIMEWAIT_ICON * wk, u32 flg );
static void TimeWaitIconMain( TCB_PTR tcb, void * work );

static POKEWIN_WORK * PokeWin_TcbAdd( GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u32 heap );
static void PokeWin_ClactSet( POKEWIN_WORK * wk, u32 heap );
static void PokeWin_LoadRes( POKEWIN_WORK * wk );
static void PokeWin_ClactAdd( POKEWIN_WORK * wk, u8 px, u8 py );
static void PokeWin_PokeGraSetCore( FIELD_CLACT * wk, SOFT_SPRITE_ARC * ssa );
static void PokeWin_PokeGraSetEz( FIELD_CLACT * wk, u16 mons, u8 sex );
static void PokeWin_PokeGraSetPP( FIELD_CLACT * wk, POKEMON_PARAM * pp );
static void PokeWin_Main( TCB_PTR tcb, void * work );
static void PokeWinFrameWrite( POKEWIN_WORK * wk, u8 pal, u16 cgx );
static void PokeWinFrameClear( POKEWIN_WORK * wk );


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
// �|�P�����Z���A�N�^�[�̓o�^�f�[�^
static const TCATS_OBJECT_ADD_PARAM_S PokeWinAct_S =
{
	0, 0, 0,
	0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN,
	{
		POKEWIN_CLA_CHR_ID, POKEWIN_CLA_PAL_ID,
		POKEWIN_CLA_CEL_ID, POKEWIN_CLA_ANM_ID, 0, 0,
	},
	0, 0
};


//============================================================================================
//============================================================================================
//	���j���[�E�B���h�E
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�̃L�������Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	cgx			�L�����]���ʒu
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MenuWinCgxSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 win_num, u32 heap )
{
	if( win_num == MENU_TYPE_SYSTEM ){
		ArcUtil_BgCharSet(
			ARC_WINFRAME, NARC_winframe_system_ncgr, ini, frmnum, cgx, 0, 0, heap );
	}else{
		ArcUtil_BgCharSet(
			ARC_WINFRAME, NARC_winframe_fmenu_ncgr, ini, frmnum, cgx, 0, 0, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	none
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 MenuWinPalArcGet(void)
{
	return ( NARC_winframe_system_nclr );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E�̃O���t�B�b�N���Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[��
 * @param	cgx			�L�����]���ʒu
 * @param	pal			�p���b�g�ԍ�
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MenuWinGraphicSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap )
{
	u32	arc;

	// �L����
	if( win_num == MENU_TYPE_SYSTEM ){
		arc = NARC_winframe_system_ncgr;
	}else{
		arc = NARC_winframe_fmenu_ncgr;
	}
	ArcUtil_BgCharSet( ARC_WINFRAME, arc, ini, frmnum, cgx, 0, 0, heap );

	// �p���b�g
	if( win_num == MENU_TYPE_UG ){
		arc = NARC_winframe_ugmenu_win_nclr;
	}else{
		arc = NARC_winframe_system_nclr;
	}
	if( frmnum < GF_BGL_FRAME0_S ){
		ArcUtil_PalSet( ARC_WINFRAME, arc , PALTYPE_MAIN_BG, pal*0x20, 0x20, heap );
	}else{
		ArcUtil_PalSet( ARC_WINFRAME, arc , PALTYPE_SUB_BG, pal*0x20, 0x20, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	���j���[�E�C���h�E�`�惁�C��
 *
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	px			�w���W
 * @param	py			�x���W
 * @param	sx			�w�T�C�Y
 * @param	sy			�T�C�Y
 * @param	pal			�g�p�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpMenuWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx,   px-1,  py-1, 1,  1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px,    py-1, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px+sx, py-1, 1,  1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+3, px-1,  py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-1,  py+sy, 1,  1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px,    py+sy, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+8, px+sx, py+sy, 1,  1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * ���j���[�E�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	pal			�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpMenuWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	BmpMenuWinWriteMain(
		win->ini, frm,
		GF_BGL_BmpWinGet_PosX( win ),
		GF_BGL_BmpWinGet_PosY( win ),
		GF_BGL_BmpWinGet_SizeX( win ),
		GF_BGL_BmpWinGet_SizeY( win ),
		pal, win_cgx );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOn( win );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	���j���[�E�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpMenuWinClear( GF_BGL_BMPWIN * win, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	GF_BGL_ScrFill(
		win->ini, frm, 0,
		GF_BGL_BmpWinGet_PosX( win ) - 1,
		GF_BGL_BmpWinGet_PosY( win ) - 1,
		GF_BGL_BmpWinGet_SizeX( win ) + 2,
		GF_BGL_BmpWinGet_SizeY( win ) + 2,
		0 );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOff( win );
	}
}


//============================================================================================
//============================================================================================
//	��b�E�B���h�E
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�L�����̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�E�B���h�EID
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 TalkWinCgxArcGet( u32 id )
{
	return ( NARC_winframe_talk_win00_ncgr + id );
}

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�p���b�g�̃A�[�J�C�u�C���f�b�N�X�擾
 *
 * @param	id		�E�B���h�EID
 *
 * @return	�A�[�J�C�u�C���f�b�N�X
 */
//--------------------------------------------------------------------------------------------
u32 TalkWinPalArcGet( u32 id )
{
	return ( NARC_winframe_talk_win00_nclr + id );
}

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	pal			�g�p�p���b�g
 * @param	win_num		�E�B���h�E�ԍ�
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkWinGraphicSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 win_num, u32 heap )
{
	ArcUtil_BgCharSet( ARC_WINFRAME, TalkWinCgxArcGet(win_num), ini, frmnum, cgx, 0, 0, heap );
	if( frmnum < GF_BGL_FRAME0_S ){
		ArcUtil_PalSet(
			ARC_WINFRAME, TalkWinPalArcGet(win_num), PALTYPE_MAIN_BG, pal*0x20, 0x20, heap );
	}else{
		ArcUtil_PalSet(
			ARC_WINFRAME, TalkWinPalArcGet(win_num), PALTYPE_SUB_BG, pal*0x20, 0x20, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�C���h�E�`�惁�C��
 *
 * @param	ini			BGL�f�[�^
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	px			�w���W
 * @param	py			�x���W
 * @param	sx			�w�T�C�Y
 * @param	sy			�T�C�Y
 * @param	pal			�g�p�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpTalkWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx, px-2, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px-1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px, py-1, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+3, px+sx,	py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+4, px+sx+1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx+2, py-1, 1, 1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-2, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px-1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+9, px+sx, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+10, px+sx+1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+11, px+sx+2, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+12, px-2, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+13, px-1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+14, px, py+sy, sx, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+15, px+sx, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+16, px+sx+1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+17, px+sx+2, py+sy, 1, 1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E�X�N���[���f�[�^���ABitmapWindow�Ɋ֘A�t����ꂽ
 * BG�t���[���̃X�N���[���o�b�t�@�ɃZ�b�g����
 *
 * @param   win		
 * @param   charno		
 * @param   palno		
 *
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinScreenSet( GF_BGL_BMPWIN * win, u32 charno, u32 palno )
{
	BmpTalkWinWriteMain(
		win->ini,
		GF_BGL_BmpWinGet_Frame( win ),
		GF_BGL_BmpWinGet_PosX( win ),
		GF_BGL_BmpWinGet_PosY( win ),
		GF_BGL_BmpWinGet_SizeX( win ),
		GF_BGL_BmpWinGet_SizeY( win ),
		palno, charno );
}

//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	pal			�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal )
{
	BmpTalkWinScreenSet( win, win_cgx, pal );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOn( win );
	}

	CursorCgxMake( win, win_cgx );
//	PokeFontTrgCursorCgxSet( win_cgx );
}

//--------------------------------------------------------------------------------------------
/**
 *	��b�E�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpTalkWinClear( GF_BGL_BMPWIN * win, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	GF_BGL_ScrFill(
		win->ini, frm, 0,
		GF_BGL_BmpWinGet_PosX( win ) - 2,
		GF_BGL_BmpWinGet_PosY( win ) - 1,
		GF_BGL_BmpWinGet_SizeX( win ) + 5,
		GF_BGL_BmpWinGet_SizeY( win ) + 2,
		0 );

	if( trans_sw == WINDOW_TRANS_ON ){
//		GF_BGL_LoadScreenReq( win->ini, frm );
		GF_BGL_BmpWinOff( win );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �L�����쐬
 *
 * @param	src			�]������L�����f�[�^
 * @param	src_x		�ǂݍ��݌��ǂݍ��݊J�nX���W
 * @param	src_y		�ǂݍ��݌��ǂݍ��݊J�nY���W
 * @param	src_dx		�]������L������X�T�C�Y
 * @param	src_dy		�]������L������Y�T�C�Y
 * @param	buf			�]����̃L�����f�[�^
 * @param	buf_sx		�]����̃L������X�T�C�Y
 * @param	buf_sy		�]����̃L������Y�T�C�Y
 * @param	win_x		�������ݐ揑�����݊J�nX���W
 * @param	win_y		�������ݐ揑�����݊J�nY���W
 * @param	win_dx		�`��͈�X�T�C�Y
 * @param	win_dy		�`��͈�Y�T�C�Y
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpPrintCharMake(
			void * src, u16 src_x, u16 src_y, u16 src_dx, u16 src_dy,
			void * buf, u16 buf_sx, u16 buf_sy, u16 win_x, u16 win_y, u16 win_dx, u16 win_dy )
{
	BMPPRT_HEADER	src_data;
	BMPPRT_HEADER	dst_data;

	src_data.adrs	= (u8 *)src;
	src_data.size_x = src_dx;
	src_data.size_y = src_dy;

	dst_data.adrs	= (u8 *)buf;
	dst_data.size_x = buf_sx;
	dst_data.size_y = buf_sy;

	GF_BMP_PrintMain( &src_data, &dst_data, src_x, src_y, win_x, win_y, win_dx, win_dy, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * ����J�[�\���Z�b�g
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	cgxnum		�E�B���h�E�ʒu
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CursorCgxMake( GF_BGL_BMPWIN * win, u16 cgxnum )
{
	u32	heap;
	u8 * wincgx;
	u8 * scrcgx;
	u8 * curcgx;
	void * arc;
	u8	frm;
	u8	i;

	heap   = GF_BGL_HeapIDGet( win->ini );
	frm    = GF_BGL_BmpWinGet_Frame( win );
	wincgx = sys_AllocMemory( heap, MAKE_CURSOR_CGX_SIZ );
	scrcgx = GF_BGL_CgxGet( frm );

	{
		NNSG2dCharacterData * dat;
		arc = ArcUtil_CharDataGet( ARC_WINFRAME, NARC_winframe_win_cursol1_ncgr, 0, &dat, heap );
		curcgx = (u8 *)dat->pRawData;
	}

	for( i=0; i<3; i++ ){
		memcpy( &wincgx[i*0x20*4+0x20*0], &scrcgx[(cgxnum+10)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*1], &scrcgx[(cgxnum+11)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*2], &scrcgx[(cgxnum+10)*0x20], 0x20 );
		memcpy( &wincgx[i*0x20*4+0x20*3], &scrcgx[(cgxnum+11)*0x20], 0x20 );
	}

	BmpPrintCharMake( curcgx, 4, 0, 12, 16*3, wincgx, 12, 16*3, 1, 0, 12, 16*3 );

	GF_BGL_LoadCharacter( win->ini, frm, wincgx, MAKE_CURSOR_CGX_SIZ, cgxnum+18 );
	PokeFontTrgCursorCgxSet( cgxnum );

	sys_FreeMemoryEz( arc );
	sys_FreeMemoryEz( wincgx );
}


//--------------------------------------------------------------------------------------------
/**
 * ��b�E�B���h�E�̃J���[�O�̃h�b�g���w��J���[�ɕύX����
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	cal			�ύX�J���[
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void TalkWinGraphicNullSet( GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 col, u8 win_num, u32 heap )
{
	void * arc;
	NNSG2dCharacterData * dat;
	u8 * curcgx;
	u32	i;
	u8	dott, dotu;

	arc = ArcUtil_CharDataGet(
			ARC_WINFRAME, TalkWinCgxArcGet(win_num), 0, &dat, heap );
	curcgx = sys_AllocMemory( heap, 0x20*18 );
	memcpy( curcgx, dat->pRawData, 0x20*18 );

	for( i=0; i<0x20*18; i++ ){
		dott = curcgx[i] >> 4;
		dotu = curcgx[i] & 0x0f;
		if( dott == 0 ){ dott = col; }
		if( dotu == 0 ){ dotu = col; }
		curcgx[i] = (dott<<4)|dotu;
	}

	GF_BGL_LoadCharacter( ini, frmnum, curcgx, 0x20*18, cgx );
	sys_FreeMemoryEz( arc );
	sys_FreeMemoryEz( curcgx );
}


//============================================================================================
//============================================================================================
//	�ŔE�B���h�E
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ŔE�C���h�E�Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���i���o�[(bg_sys)
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	pal			�g�p�p���b�g
 * @param	type		�Ŕ^�C�v
 * @param	map			�}�b�v�ԍ��i�^�E���}�b�v�A�W���j
 * @param	heap		�q�[�vID
 *
 * @return	none
 *
 *	type = *_POST, *_INFO �̏ꍇ�́Amap = 0 �ŗǂ�
 */
//--------------------------------------------------------------------------------------------
void BoardWinGraphicSet(
		GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 pal, u8 type, u16 map, u32 heap )
{
	// �E�B���h�E�L�����]��
	ArcUtil_BgCharSet(
		ARC_FIELD_BOARD, NARC_field_board_kanb_win00_NCGR,
		ini, frmnum, cgx, BOARD_WIN_CGX_SIZ*0x20, 0, heap );

	// �E�B���h�E�p���b�g�]��
	{
		NNSG2dPaletteData * nns;
		void * buf;
		u16 * dat;
		
		buf = ArchiveDataLoadMalloc( ARC_FIELD_BOARD, NARC_field_board_kanb_win00_NCLR, heap );
		NNS_G2dGetUnpackedPaletteData( buf, &nns );
		dat = (u16 *)nns->pRawData;
		GF_BGL_PaletteSet( frmnum, (void *)&dat[type*16], 0x20, pal*0x20 );
		sys_FreeMemory( heap, buf );
	}

	// �n�}�Z�b�g
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
//		BoardMapSet( ini, frmnum, cgx+BOARD_WIN_CGX_SIZ, pal, type, map, heap );
		BoardMapCgxSet( ini, frmnum, cgx+BOARD_WIN_CGX_SIZ, type, map, heap );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �ŔE�C���h�E�}�b�v�f�[�^�Z�b�g
 *
 * @param	ini			BGL�f�[�^
 * @param	frmnum		BG�t���[���i���o�[
 * @param	cgx			�L�����Z�b�g�ʒu
 * @param	type		�Ŕ^�C�v
 * @param	map			�}�b�v�ԍ��i�^�E���}�b�v�A�W���j
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardMapCgxSet(
				GF_BGL_INI * ini, u8 frmnum, u16 cgx, u8 type, u16 map, u32 heap )
{
	if( type == BOARD_TYPE_TOWN ){
		map += BOARD_TOWNMAP_START;
	}else{
		map += BOARD_ROADMAP_START;
	}

	ArcUtil_BgCharSet(
		ARC_FIELD_BOARD, map, ini, frmnum, cgx, BOARD_MAP_CGX_SIZ*0x20, 0, heap );
}

//--------------------------------------------------------------------------------------------
/**
 *	�ŔE�C���h�E�`�惁�C���i���A���Ŕj
 *
 * @param	ini			BGL�f�[�^
 * @param	frm			BG�t���[���i���o�[(bg_sys)
 * @param	px			�w���W
 * @param	py			�x���W
 * @param	sx			�w�T�C�Y
 * @param	sy			�T�C�Y
 * @param	pal			�g�p�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpBoardWinWriteMain(
				GF_BGL_INI * ini, u8 frm, u8 px, u8 py, u8 sx, u8 sy, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( ini, frm, cgx, px-9, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+1, px-8, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+2, px-7, py-1, sx+7, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+3, px+sx,	py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+4, px+sx+1, py-1, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+5, px+sx+2, py-1, 1, 1, pal );

	GF_BGL_ScrFill( ini, frm, cgx+6, px-9, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+7, px-8, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+8, px-1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+9, px+sx, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+10, px+sx+1, py, 1, sy, pal );
	GF_BGL_ScrFill( ini, frm, cgx+11, px+sx+2, py, 1, sy, pal );

	GF_BGL_ScrFill( ini, frm, cgx+12, px-9, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+13, px-8, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+14, px-7, py+sy, sx+7, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+15, px+sx, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+16, px+sx+1, py+sy, 1, 1, pal );
	GF_BGL_ScrFill( ini, frm, cgx+17, px+sx+2, py+sy, 1, 1, pal );
}

//--------------------------------------------------------------------------------------------
/**
 *	�ŔE�C���h�E�}�b�v�`��
 *
 * @param	win		BMP�E�B���h�E�f�[�^
 * @param	cgx		�}�b�v�L�����ʒu
 * @param	pal		�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BmpBoardMapWrite( GF_BGL_BMPWIN * win, u16 cgx, u8 pal )
{
	u16	i, j;
	u16	px, py;
	u8	frm;
	
	frm = GF_BGL_BmpWinGet_Frame( win );
	px  = GF_BGL_BmpWinGet_PosX( win ) - 7;
	py  = GF_BGL_BmpWinGet_PosY( win );

	for( i=0; i<4; i++ ){
		for( j=0; j<6; j++ ){
			GF_BGL_ScrFill( win->ini, frm, cgx+i*6+j, px+j, py+i, 1, 1, pal );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �ŔE�B���h�E��`��
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	trans_sw	�]���X�C�b�`
 * @param	win_cgx		�E�B���h�E�L�����ʒu
 * @param	type		�Ŕ^�C�v
 * @param	pal			�p���b�g
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpBoardWinWrite( GF_BGL_BMPWIN * win, u8 trans_sw, u16 win_cgx, u8 pal, u8 type )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	// ���A��
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		BmpBoardWinWriteMain(
			win->ini, frm,
			GF_BGL_BmpWinGet_PosX( win ),
			GF_BGL_BmpWinGet_PosY( win ),
			GF_BGL_BmpWinGet_SizeX( win ),
			GF_BGL_BmpWinGet_SizeY( win ),
			pal, win_cgx );

		BmpBoardMapWrite( win, win_cgx+BOARD_WIN_CGX_SIZ, pal );
	// ���A���ȊO
	}else{
		// �f�[�^�\������b�E�B���h�E�Ɠ����Ȃ̂ŁA��b�E�B���h�E�`��
		BmpTalkWinWriteMain(
			win->ini, frm,
			GF_BGL_BmpWinGet_PosX( win ),
			GF_BGL_BmpWinGet_PosY( win ),
			GF_BGL_BmpWinGet_SizeX( win ),
			GF_BGL_BmpWinGet_SizeY( win ),
			pal, win_cgx );
	}

	if( trans_sw == WINDOW_TRANS_ON ){
		GF_BGL_BmpWinOn( win );
	}

	CursorCgxMake( win, win_cgx );
}

//--------------------------------------------------------------------------------------------
/**
 *	�ŔE�B���h�E���N���A
 *
 * @param	win			BMP�E�B���h�E�f�[�^
 * @param	type		�Ŕ^�C�v
 * @param	trans_sw	�]���X�C�b�`
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpBoardWinClear( GF_BGL_BMPWIN * win, u8 type, u8 trans_sw )
{
	u8	frm = GF_BGL_BmpWinGet_Frame( win );

	// ���A��
	if( type == BOARD_TYPE_TOWN || type == BOARD_TYPE_ROAD ){
		GF_BGL_ScrFill(
			win->ini, frm, 0,
			GF_BGL_BmpWinGet_PosX( win ) - 9,
			GF_BGL_BmpWinGet_PosY( win ) - 1,
			GF_BGL_BmpWinGet_SizeX( win ) + 11,
			GF_BGL_BmpWinGet_SizeY( win ) + 2,
			0 );
	}else{
		GF_BGL_ScrFill(
			win->ini, frm, 0,
			GF_BGL_BmpWinGet_PosX( win ) - 2,
			GF_BGL_BmpWinGet_PosY( win ) - 1,
			GF_BGL_BmpWinGet_SizeX( win ) + 4,
			GF_BGL_BmpWinGet_SizeY( win ) + 2,
			0 );
	}

	if( trans_sw == WINDOW_TRANS_ON ){
		GF_BGL_BmpWinOff( win );
	}
}


//============================================================================================
//============================================================================================
//	�ҋ@�A�C�R��
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�ǉ�
 *
 * @param	win		��b�E�B���h�E��BMP
 * @param	cgxpos	��b�E�B���h�E�g�L�����iTalkWinGraphicSet�Ȃǁj�̓]���ʒu
 *
 * @return	�ҋ@�A�C�R���̃��[�N
 */
//--------------------------------------------------------------------------------------------
void * TimeWaitIconAdd( GF_BGL_BMPWIN * win, u32 cgxpos )
{
	TIMEWAIT_ICON * wk;
	u32	heap;
	u8 * scrcgx;
	u8 * curcgx;
	u8 * back_win;
	void * arc;
	u8	frm;
	u8	i;

	heap   = GF_BGL_HeapIDGet( win->ini );
	frm    = GF_BGL_BmpWinGet_Frame( win );
	scrcgx = GF_BGL_CgxGet( frm );

//	wk = TCB_GetWork( PMDS_taskAdd(TimeWaitIconMain,sizeof(TIMEWAIT_ICON),0,heap) );
	wk = sys_AllocMemory( heap, sizeof(TIMEWAIT_ICON) );

	// �]���̈�o�b�N�A�b�v
	memcpy( wk->backup, &scrcgx[(cgxpos+18)*0x20], 0x20*4 );
	// �쐬�̈揉����
	back_win = (u8 *)sys_AllocMemory( heap, 0x20*4 );
	memcpy( &back_win[0x20*0], &scrcgx[(cgxpos+10)*0x20], 0x20 );
	memcpy( &back_win[0x20*1], &scrcgx[(cgxpos+11)*0x20], 0x20 );
	memcpy( &back_win[0x20*2], &scrcgx[(cgxpos+10)*0x20], 0x20 );
	memcpy( &back_win[0x20*3], &scrcgx[(cgxpos+11)*0x20], 0x20 );
	for( i=0; i<8; i++ ){
		memcpy( &wk->cgx[0x20*4*i], back_win, 0x20*4 );
	}
	sys_FreeMemoryEz( back_win );

	{
		NNSG2dCharacterData * dat;
		arc = ArcUtil_CharDataGet( ARC_WINFRAME, NARC_winframe_win_cursol2_ncgr, 0, &dat, heap );
		curcgx = (u8 *)dat->pRawData;
	}

	BmpPrintCharMake( curcgx, 0, 0, 16, 16*8, wk->cgx, 16, 16*8, 0, 0, 16, 16*8 );

	sys_FreeMemoryEz( arc );

	wk->win = win;
	wk->cgxpos = (u16)cgxpos;
	wk->cnt = 0;
	wk->pat = 0;
	wk->seq = 0;

	VIntrTCB_Add( TimeWaitIconMain, wk, 0 );
	TimeWaitIconPut( wk, 1 );

	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\��
 *
 * @param	wk		�ҋ@�A�C�R���̃��[�N
 * @param	cgxpos	��b�E�B���h�E�̓]���ʒu
 *
 * @return	none
 *
 * @li	flg = 0 : �ʏ�
 * @li	flg = 1 : �X�N���[�����]��
 * @li	flg = 2 : �I����
 */
//--------------------------------------------------------------------------------------------
static void TimeWaitIconPut( TIMEWAIT_ICON * wk, u32 flg )
{
	u8	frm, px, py, sx;

	frm = GF_BGL_BmpWinGet_Frame( wk->win );
	px  = GF_BGL_BmpWinGet_PosX( wk->win );
	py  = GF_BGL_BmpWinGet_PosY( wk->win );
	sx  = GF_BGL_BmpWinGet_SizeX( wk->win );

	if( flg == 2 ){
		GF_BGL_LoadCharacter( wk->win->ini, frm, wk->backup, 0x20*4, wk->cgxpos+18 );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+10, px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+11, px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+10, px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			wk->win->ini, frm, wk->cgxpos+11, px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( wk->win->ini, frm );
		return;
	}

	GF_BGL_LoadCharacter(
		wk->win->ini, frm, &wk->cgx[0x20*4*wk->pat], 0x20*4, wk->cgxpos+18 );

	if( flg == 0 ){ return; }

	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+18, px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+19, px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+20, px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->win->ini, frm, wk->cgxpos+21, px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );

	GF_BGL_LoadScreenReq( wk->win->ini, frm );
}

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R�����C���^�X�N
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void TimeWaitIconMain( TCB_PTR tcb, void * work )
{
	TIMEWAIT_ICON * wk = work;

	if( wk->seq != 0 ){
        if(wk->seq == 1){
            TimeWaitIconPut( wk, 2 );
        }
		TCB_Delete( tcb );
		return;
	}
	wk->cnt++;

	if( wk->cnt == TIMEWAIT_WAIT ){
		wk->cnt = 0;
		wk->pat = ( wk->pat + 1 ) & 7;
		TimeWaitIconPut( wk, 0 );
	}
}

//------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���^�X�N�̃��[�N��������邽�߂����̃^�X�N
 *�i���荞�ݒ��Ƀ���������������Ȃ����߁j
 *
 * @param   tcb		
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void TimeWaitIconWorkFreeTask( TCB_PTR tcb, void* wk )
{
	sys_FreeMemoryEz( wk );
	TCB_Delete( tcb );
}

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�폜���N�G�X�g
 *
 * @param	work	�ҋ@�A�C�R���̃��[�N
 *
 * @return	none
 *
 *	work���폜����܂�
 */
//--------------------------------------------------------------------------------------------
void TimeWaitIconDel( void * work )
{
	TIMEWAIT_ICON * wk = work;

	VWaitTCB_Add( TimeWaitIconWorkFreeTask, wk, 0 );

	wk->seq = 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �ҋ@�A�C�R���\���^�X�N�폜���N�G�X�g
 *
 * @param	work	�ҋ@�A�C�R���̃��[�N
 *
 * @return	none
 *
 *	work���폜����܂�  SCR�͏��������܂���
 */
//--------------------------------------------------------------------------------------------
void TimeWaitIconTaskDel( void * work )
{
	TIMEWAIT_ICON * wk = work;

	VWaitTCB_Add( TimeWaitIconWorkFreeTask, wk, 0 );

	wk->seq = 2;
}


//============================================================================================
//============================================================================================
//	�|�P�����\���E�B���h�E
//============================================================================================
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E�\���i�ԍ��A���ʎw��j
 *
 * @param	bgl		BGL�f�[�^
 * @param	frm		�\��BG�t���[��
 * @param	px		�\��X���W
 * @param	py		�\��Y���W
 * @param	pal		�E�B���h�E�p���b�g
 * @param	cgx		�E�B���h�E�L����
 * @param	mons	�|�P�����ԍ�
 * @param	sex		�|�P�����̐���
 * @param	heap	�q�[�vID
 *
 * @return	�R�}���h�̃|�C���^
 *
 *	�\�����W�́A�g���܂߂Ȃ��l���w�肷�邱��
 */
//--------------------------------------------------------------------------------------------
u8 * PokeWindowPut(
		GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u8 pal, u16 cgx, u16 mons, u8 sex, int heap )
{
	POKEWIN_WORK * wk = PokeWin_TcbAdd( bgl, frm, px, py, heap );

	PokeWin_ClactSet( wk, heap );
	PokeWin_LoadRes( wk );
	PokeWin_ClactAdd( wk, px, py );
	PokeWin_PokeGraSetEz( &wk->fcat, mons, sex );
	PokeWinFrameWrite( wk, pal, cgx );

	GF_BGL_LoadScreenReq( bgl, frm );

	return &wk->cmd;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E�\���iPOKEMON_PARAM�w��j
 *
 * @param	bgl		BGL�f�[�^
 * @param	frm		�\��BG�t���[��
 * @param	px		�\��X���W
 * @param	py		�\��Y���W
 * @param	pal		�E�B���h�E�p���b�g
 * @param	cgx		�E�B���h�E�L����
 * @param	pp		POKEMON_PARAM
 * @param	heap	�q�[�vID
 *
 * @return	�R�}���h�̃|�C���^
 *
 *	�\�����W�́A�g���܂߂Ȃ��l���w�肷�邱��
 */
//--------------------------------------------------------------------------------------------
u8 * PokeWindowPutPP(
		GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u8 pal, u16 cgx, POKEMON_PARAM * pp, int heap )
{
	POKEWIN_WORK * wk = PokeWin_TcbAdd( bgl, frm, px, py, heap );

	PokeWin_ClactSet( wk, heap );
	PokeWin_LoadRes( wk );
	PokeWin_ClactAdd( wk, px, py );
	PokeWin_PokeGraSetPP( &wk->fcat, pp );
	PokeWinFrameWrite( wk, pal, cgx );

	GF_BGL_LoadScreenReq( bgl, frm );

	return &wk->cmd;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E�Ď��^�X�N
 *
 * @param	tcb
 * @param	work
 *
 * @return	none
 *
 *	�I������ꍇ�́A�O������t���O�𑀍�
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_Main( TCB_PTR tcb, void * work )
{
	POKEWIN_WORK * wk = work;

	switch( wk->cmd ){
	case POKEWIN_CMD_END:
		PokeWinFrameClear( wk );
		CATS_ActorPointerDelete_S( wk->cap );
		FieldCellActDelete_S( &wk->fcat );
		PMDS_taskDel( tcb );
		return;

	case POKEWIN_CMD_ANM:
		wk->cmd = POKEWIN_CMD_MOVE;
		CLACT_AnmChg( wk->cap->act, 1 );
		break;

	case POKEWIN_CMD_MOVE:
		if( CLACT_AnmFrameGet( wk->cap->act ) == 6 ){
			wk->cmd = POKEWIN_CMD_NONE;
		}
	}
	
	CLACT_AnmFrameChg( wk->cap->act, FX32_ONE );
	CLACT_Draw( wk->fcat.cas );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E TCB�ǉ� & ���[�N�쐬
 *
 * @param	bgl		BGL�f�[�^
 * @param	frm		�\��BG�t���[��
 * @param	px		�\��X���W
 * @param	py		�\��Y���W
 * @param	heap	�q�[�vID
 *
 * @return	�|�P�����E�B���h�E�̃��[�N
 */
//--------------------------------------------------------------------------------------------
static POKEWIN_WORK * PokeWin_TcbAdd( GF_BGL_INI * bgl, u8 frm, u8 px, u8 py, u32 heap )
{
	POKEWIN_WORK * wk = TCB_GetWork( PMDS_taskAdd(PokeWin_Main,sizeof(POKEWIN_WORK),0,heap) );
	wk->cmd = POKEWIN_CMD_NONE;
	wk->bgl = bgl;
	wk->frm = frm;
	wk->px  = px;
	wk->py  = py;
	return wk;
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E �Z���A�N�^�[�Z�b�g
 *
 * @param	wk		���[�N
 * @param	heap	�q�[�vID
 *
 * @return	�|�P�����E�B���h�E�̃��[�N
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_ClactSet( POKEWIN_WORK * wk, u32 heap )
{
	TCATS_RESOURCE_NUM_LIST	crnl = { 1, 1, 1, 1, 0, 0 };
	FieldCellActSet_S( &wk->fcat, &crnl, 1, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E ���\�[�X�ǂݍ���
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_LoadRes( POKEWIN_WORK * wk )
{
	// �p���b�g
	FldClact_LoadResPlttArc(
		&wk->fcat, ARC_WINFRAME,
		NARC_winframe_poke_win_nclr, 0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, POKEWIN_CLA_PAL_ID );
	// �Z��
	FldClact_LoadResCellArc(
		&wk->fcat, ARC_WINFRAME, NARC_winframe_poke_win_ncer, 0, POKEWIN_CLA_CEL_ID );
	// �Z���A�j��
	FldClact_LoadResCellAnmArc(
		&wk->fcat, ARC_WINFRAME, NARC_winframe_poke_win_nanr, 0, POKEWIN_CLA_ANM_ID );
	// �L����
	FldClact_LoadResourceCharArc(
		&wk->fcat, ARC_WINFRAME,
		NARC_winframe_poke_win_ncgr, 0, NNS_G2D_VRAM_TYPE_2DMAIN, POKEWIN_CLA_CHR_ID );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����E�B���h�E �Z���A�N�^�[�ǉ�
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_ClactAdd( POKEWIN_WORK * wk, u8 px, u8 py )
{
	TCATS_OBJECT_ADD_PARAM_S	prm = PokeWinAct_S;

	prm.x = ( px + 5 ) * 8;
	prm.y = ( py + 5 ) * 8;
	wk->cap = FieldCellActAdd_S( &wk->fcat, &prm );

	CLACT_Draw( wk->fcat.cas );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����O���t�B�b�N�Z�b�g�i�ԍ��A���ʎw��j
 *
 * @param	wk		�t�B�[���h�Z���A�N�^�[���[�N
 * @param	mons	�|�P�����ԍ�
 * @param	sex		�|�P�����̐���
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetEz( FIELD_CLACT * wk, u16 mons, u8 sex )
{
	void * ssm;
	SOFT_SPRITE_ARC	ssa;

	ssm = SoftSpriteInit( wk->heap );
	PokeGraArcDataGet( &ssa, mons, sex, PARA_FRONT, PARA_NORMAL, NULL, NULL );	//�Ō�̈�����FormNo�ƌ������ł� by soga
	PokeWin_PokeGraSetCore( wk, &ssa );
	SoftSpriteEnd( ssm );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����O���t�B�b�N�Z�b�g�iPOKEMON_PARAM�w��j
 *
 * @param	wk		�t�B�[���h�Z���A�N�^�[���[�N
 * @param	pp		POKEMON_PARAM
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetPP( FIELD_CLACT * wk, POKEMON_PARAM * pp )
{
	void * ssm;
	SOFT_SPRITE_ARC	ssa;

	ssm = SoftSpriteInit( wk->heap );
	PokeGraArcDataGetPP( &ssa, pp, PARA_FRONT );
	PokeWin_PokeGraSetCore( wk, &ssa );
	SoftSpriteEnd( ssm );
}

//--------------------------------------------------------------------------------------------
/**
 * �|�P�����O���t�B�b�N�Z�b�g �R�A
 *
 * @param	wk		�t�B�[���h�Z���A�N�^�[���[�N
 * @param	ssa
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWin_PokeGraSetCore( FIELD_CLACT * wk, SOFT_SPRITE_ARC * ssa )
{
	u8 * buf;
	u32 vram;
	CLACT_U_RES_OBJ_PTR c_res;
	NNSG2dImageProxy * c_pxy;
	CLACT_U_RES_OBJ_PTR p_res;
	const NNSG2dImagePaletteProxy * p_pxy;

	// �L����
	buf = sys_AllocMemory( wk->heap, POKEWIN_OBJCGX_SIZ_ALL );
	{
		CHANGES_INTO_DATA_RECT rc = { 0, 0, 10, 10 };
		ChangesInto_OAM_from_PokeTex_RC( ssa->arc_no, ssa->index_chr, wk->heap, &rc, &buf[0] );
	}
	{
		CHANGES_INTO_DATA_RECT rc = { 10, 0, 10, 10 };
		ChangesInto_OAM_from_PokeTex_RC(
			ssa->arc_no, ssa->index_chr, wk->heap, &rc, &buf[POKEWIN_OBJCGX_SIZ] );
	}

	c_res  = CLACT_U_ResManagerGetIDResObjPtr( wk->resMan[0], POKEWIN_CLA_CHR_ID );
	c_pxy  = CLACT_U_CharManagerGetProxy( c_res );
	vram   = NNS_G2dGetImageLocation( c_pxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( buf, POKEWIN_OBJCGX_SIZ_ALL );
	GX_LoadOBJ( buf, vram, POKEWIN_OBJCGX_SIZ_ALL );
	sys_FreeMemoryEz( buf );

	// �p���b�g
	buf    = ChangesInto_BattlePokePalData_Alloc( ssa->arc_no, ssa->index_pal, wk->heap );
	p_res  = CLACT_U_ResManagerGetIDResObjPtr( wk->resMan[1], POKEWIN_CLA_PAL_ID );
	p_pxy  = CLACT_U_PlttManagerGetProxy( p_res, c_pxy );
	vram   = NNS_G2dGetImagePaletteLocation( p_pxy, NNS_G2D_VRAM_TYPE_2DMAIN );
	DC_FlushRange( buf, 32 );
	GX_LoadOBJPltt( buf, vram, 32 );	//32byte 1Palette
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------------------------------------
/**
 * �E�B���h�E�`��
 *
 * @param	wk		���[�N
 * @param	pal		�g�p�p���b�g
 * @param	cgx		�g�p�L����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWinFrameWrite( POKEWIN_WORK * wk, u8 pal, u16 cgx )
{
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx,   wk->px-1,  wk->py-1, 1,  1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+1, wk->px,    wk->py-1, 10, 1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+2, wk->px+10, wk->py-1, 1,  1, pal );

	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+4, wk->px,    wk->py, 10, 10, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+3, wk->px-1,  wk->py, 1,  10, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+5, wk->px+10, wk->py, 1,  10, pal );

	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+6, wk->px-1,  wk->py+10, 1,  1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+7, wk->px,    wk->py+10, 10, 1, pal );
	GF_BGL_ScrFill( wk->bgl, wk->frm, cgx+8, wk->px+10, wk->py+10, 1,  1, pal );

	GF_BGL_LoadScreenV_Req( wk->bgl, wk->frm );
}

//--------------------------------------------------------------------------------------------
/**
 * �E�B���h�E�N���A
 *
 * @param	wk		���[�N
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void PokeWinFrameClear( POKEWIN_WORK * wk )
{
	GF_BGL_ScrFill( wk->bgl, wk->frm, 0, wk->px-1, wk->py-1, 12, 12, 0 );
	GF_BGL_LoadScreenV_Req( wk->bgl, wk->frm );
}
