//============================================================================================
/**
 * @file	app_tool.c
 * @brief	�c�[���֘A
 * @author	Hiroyuki Nakamura
 * @date	05.09.28
 *
 *	�K���ɒǉ����ĉ�����
 */
//============================================================================================
#include "common.h"

#include "system/clact_util.h"
#include "system/render_oam.h"
#include "system/brightness.h"
#include "system/wipe.h"

#define	APP_TOOL_H_GLOBAL
#include "application/app_tool.h"


//============================================================================================
//	�萔��`
//============================================================================================
#define	BRIGHT_SYNC			( COMM_BRIGHTNESS_SYNC )	// �P�x�ύXSync��
#define	BRIGHT_IN_END		( 0 )						// �P�x�ύX�I���l�i�Á����j
#define	BRIGHT_IN_START		( -16 )						// �P�x�ύX�J�n�l�i�Á����j
#define	BRIGHT_OUT_END		( -16 )						// �P�x�ύX�I���l�i�����Áj
#define	BRIGHT_OUT_START	( 0 )						// �P�x�ύX�J�n�l�i�����Áj


//==============================================================================
//	�f�[�^
//==============================================================================
///OAM�^�C�v�̃f�[�^�T�C�Y�e�[�u��
ALIGN4 static const u16 OamTypeSizeTbl[] = {
	OBJSIZE_8x8,		//OAMTYPE_8x8	
	OBJSIZE_16x16,		//OAMTYPE_16x16
	OBJSIZE_32x32,		//OAMTYPE_32x32
	OBJSIZE_64x64,		//OAMTYPE_64x64
	OBJSIZE_16x8,		//OAMTYPE_16x8
	OBJSIZE_32x8,		//OAMTYPE_32x8
	OBJSIZE_32x16,		//OAMTYPE_32x16
	OBJSIZE_64x32,		//OAMTYPE_64x32
	OBJSIZE_8x16,		//OAMTYPE_8x16
	OBJSIZE_8x32,		//OAMTYPE_8x32
	OBJSIZE_16x32,		//OAMTYPE_16x32
	OBJSIZE_32x64,		//OAMTYPE_32x64
};



//--------------------------------------------------------------
/**
 * @brief   OAM�^�C�v����OAM�̃f�[�^�T�C�Y���擾����
 * @param   oam_type		OAM�^�C�v
 * @retval  �f�[�^�T�C�Y(Byte�P��)
 */
//--------------------------------------------------------------
int APP_OamTypeToSize(int oam_type)
{
	oam_type -= OAMTYPE_8x8;	//OAMTYPE_8x8��0�Ŏn�܂��Ă��Ȃ��ꍇ���l���Ĉꉞ
	return OamTypeSizeTbl[oam_type];
}


//--------------------------------------------------------------
/**
 * @brief   �������������߂܂�
 *
 * @param   x		X�̋���
 * @param   y		Y�̋���
 *
 * @retval  int		��������
 *
 * ���W(0,0)���n�_�Ƃ��āA(x,y)�܂ł̒����������v�Z���܂�
 */
//--------------------------------------------------------------
u32 APP_StraightDistance(u32 x, u32 y)
{
	u32 temp;
	
	temp = (x * x) + (y * y);
	temp = SVC_Sqrt(temp << 4);
	return (temp >> 2);
}



//--------------------------------------------------------------------------------------------
/**
 * ���ݒl�̃Q�[�W�h�b�g�����擾
 *
 * @param	prm_now		���ݒl
 * @param	prm_max		�ő�l
 * @param	dot_max		�ő�h�b�g��
 *
 * @return	�h�b�g��
 */
//--------------------------------------------------------------------------------------------
u8 GetNumDotto( u32 prm_now, u32 prm_max, u8 dot_max )
{
	u8 put_dot;
	
	put_dot = prm_now * dot_max / prm_max;
	if( put_dot == 0 && prm_now > 0 ){	// �ޯČv�Z�ł�0�ł����ۂ̒l��1�ȏ�Ȃ�1�ޯĂɂ���
		put_dot = 1;
	}
	return put_dot;
}

//--------------------------------------------------------------
/**
 * @brief   �\���h�b�g�ƍő�h�b�g����HP�Q�[�W�̐F���擾����
 *
 * @param   put_dot		�\���h�b�g��
 * @param   max_dot		�ő�h�b�g��
 *
 * @retval  �Q�[�W�J���[
 */
//--------------------------------------------------------------
u8 GetGaugeDottoColor(u32 put_dot, u32 max_dot)
{
	put_dot <<= 8;		//����Z�g�p�ׁ̈A�������x���܂Ō����悤�ɌŒ菬����
	max_dot <<= 8;
	
	if( put_dot > (max_dot/2) ){
		return HP_DOTTO_GREEN;		// ��
	}else if( put_dot > (max_dot/5) ){
		return HP_DOTTO_YELLOW;		// ��
	}else if( put_dot > 0 ){
		return HP_DOTTO_RED;		// ��
	}
	return HP_DOTTO_NULL;			// HP=0
}

//--------------------------------------------------------------------------------------------
/**
 * HP�Q�[�W�̃J���[���擾
 *
 * @param	hp			���݂�HP
 * @param	mhp			�ő�HP
 * @param	max_dot		�ő�h�b�g��
 *
 * @return	�Q�[�W�J���[
 */
//--------------------------------------------------------------------------------------------
u8 GetHPGaugeDottoColor( u16 hp, u16 mhp, u32 max_dot )
{
	u32 put_dot;
	
	if( hp == mhp ){ return HP_DOTTO_MAX; }
	
	put_dot = GetNumDotto( hp, mhp, max_dot );

	return GetGaugeDottoColor(put_dot, max_dot);
}



//--------------------------------------------------------------------------------------------
/**
 * �P�x�ύX���N�G�X�g
 *
 * @param	req		���N�G�X�gID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void APP_BrightnessReq( u8 req )
{
	if( req == APP_BRIGHT_IN ){
		ChangeBrightnessRequest(
			BRIGHT_SYNC, BRIGHT_IN_END, BRIGHT_IN_START, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );


	}else{
		ChangeBrightnessRequest(
			BRIGHT_SYNC, BRIGHT_OUT_END, BRIGHT_OUT_START, PLANEMASK_ALL, MASK_DOUBLE_DISPLAY );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ���C�v�V�X�e���ɂ��t�F�[�h���N�G�X�g
 *
 * @param	req			���N�G�X�gID
 * @param	heap		�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void APP_WipeStart( u8 req, u32 heap )
{
	if( req == APP_WIPE_IN ){
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, heap );
	}else{
		WIPE_SYS_Start(
			WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, heap );
	}
}


//--------------------------------------------------------------------------------------------
/**
 * ���ύX
 *
 * @param	num		��
 * @param	max		�ő�l
 *
 * @retval	"APP_NUMSEL_NONE = �}�O"
 * @retval	"APP_NUMSEL_UP = �{"
 * @retval	"APP_NUMSEL_DOWN = �|"
 */
//--------------------------------------------------------------------------------------------
u8 NumSelectCheck( s16 * num, u16 max )
{
	s16	tmp;

	tmp = *num;

	if( sys.repeat & PAD_KEY_UP ){
		*num += 1;
		if( *num > max ){ *num = 1; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_UP;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		*num -= 1;
		if( *num <= 0 ){ *num = max; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_DOWN;
	}
	if( sys.repeat & PAD_KEY_LEFT ){
		*num -= 10;
		if( *num <= 0 ){ *num = 1; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_DOWN;
	}
	if( sys.repeat & PAD_KEY_RIGHT ){
		*num += 10;
		if( *num > max ){ *num = max; }
		if( *num == tmp ){ return APP_NUMSEL_NONE; }
		return APP_NUMSEL_UP;
	}

	return APP_NUMSEL_NONE;
}


///06.03.11 add iwasawa
///////////////////////////////////////////////////////////////////////

/**
 *	@brief	�A�[�J�C�u�n���h���E�t�@�C��idx���������ɁA
 *			�w��t���[���̃f�[�^��VRAM�֓]������
 *
 *	@param	bgl		�����ς݂�BGL�f�[�^
 *	@param	heapID	�e���|�����쐬�Ɏg���q�[�v�n���h��
 *	@param	handel	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h��
 *	@param	arcID	�A�[�J�C�u�t�@�C��ID
 *	@param	dataID	�A�[�J�C�u���f�[�^ID
 *	@param	frame	�f�[�^�]��GF_BGL_FRAME_***�w��
 *	@param	mode	0:�L����,1:�X�N���[��,2:�p���b�g
 *	@param	size	�]���T�C�Y�w��(0���w�肵���ꍇ�A�t�@�C���T�C�Y��)
 *	@param	ofs		�]���I�t�Z�b�g�w��
 */
void APP_ArcFileVramLoad(GF_BGL_INI* bgl,int heapID,
		ARCHANDLE* handle,int arcID,int fileID,int frame,int mode,u16 trans_siz,u16 ofs)
{
	u32	size;
	void* pSrc;
	NNSG2dCharacterData* pChar;
	NNSG2dScreenData* pScrn;	
	NNSG2dPaletteData*	pPal;
	
	size = ArchiveDataSizeGet(arcID,fileID);
	pSrc = sys_AllocMemoryLo(heapID,size);
	ArchiveDataLoadByHandle(handle,fileID,(void*)pSrc);

	switch(mode){
	case 0:	//�L�����N�^
		NNS_G2dGetUnpackedCharacterData(pSrc,&pChar); 
		if(trans_siz == 0){
			trans_siz = pChar->szByte;
		}
		OS_Printf("GF_BGL_CharSet size = %08x\n",trans_siz);
		GF_BGL_LoadCharacter(bgl,frame,
				pChar->pRawData,trans_siz,ofs);
		break;
	case 1:
		NNS_G2dGetUnpackedScreenData(pSrc,&pScrn);
		if(trans_siz == 0){
			trans_siz = pScrn->szByte;
		}

		if(GF_BGL_ScreenAdrsGet( bgl,frame) != NULL){
			GF_BGL_ScreenBufSet( bgl, frame, pScrn->rawData, trans_siz );
		}
		OS_Printf("GF_BGL_ScrnSet size = %08x\n",trans_siz);
		GF_BGL_LoadScreen( bgl, frame, pScrn->rawData, trans_siz, ofs );
		break;
	case 2:
		NNS_G2dGetUnpackedPaletteData(pSrc,&pPal);
		if(trans_siz == 0){
			trans_siz = pPal->szByte;
		}
		OS_Printf("GF_BGL_PalSet size = %08x\n",trans_siz);
		GF_BGL_PaletteSet(frame,pPal->pRawData,trans_siz,ofs);
	}
	sys_FreeMemoryEz(pSrc);
}

/**
 *	@brief	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h����n����
 *			�A�[�J�C�u���̃X�N���[���f�[�^��Unpack���Ď擾����
 *
 *	@param	handel	�I�[�v���ς݂̃A�[�J�C�u�t�@�C���n���h��
 *	@param	arcID	�A�[�J�C�u�t�@�C��ID
 *	@param	dataID	�A�[�J�C�u���f�[�^ID
 *	@param	heapID	�������m�ۂ���q�[�v�n���h��
 *
 *	@return void*	�m�ۂ����f�[�^�̈�̐擪�|�C���^
 *	
 *	��Unpack���邾���Ȃ̂ŁA����͎����ł�邱�ƁI
 */
void* APP_ArcScrFileUnpack(ARCHANDLE* handle,
	int arcID,int fileID,NNSG2dScreenData** pDat,int heapID)
{
	int size;
	void* pBuf;
	
	size = ArchiveDataSizeGet(arcID,fileID);
	pBuf = sys_AllocMemory(heapID,size);
	ArchiveDataLoadByHandle(handle,fileID,pBuf);
	NNS_G2dGetUnpackedScreenData(pBuf,pDat);

	return pBuf;
}

