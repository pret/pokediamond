//============================================================================================
/**
 * @file	strbuf.c
 * @brief	�ėp������o�b�t�@�^�I�u�W�F�N�g
 * @author	taya
 * @date	2005.11.02
 */
//============================================================================================
#include <stdlib.h>
#include <string.h>
#include "gflib/assert.h"
#include "gflib/msg_print.h"
#include "gflib/strcode.h"
#include "gflib/fntsys.h"
#include "gflib/heapsys.h"

#include "gflib/strbuf_family.h"


//--------------------------------------------------------------
/**
 * �萔                                                      
 */
//--------------------------------------------------------------
#define STRBUF_MAGIC_NUMBER		(0xb6f8d2ec)
#define STRBUF_MAX_SIZE			(1024)

//--------------------------------------------------------------
/**
 * ������o�b�t�@�I�u�W�F�N�g�^��`
 */
//--------------------------------------------------------------
struct _STRBUF {
	u16  size;			///< �z��T�C�Y
	u16  strlen;		///< �����񒷁iEOM���܂܂Ȃ��j
	u32  magicNumber;	///< ����ɏ������ς݂ł��邱�Ƃ��`�F�b�N���邽�߂̃i���o�[

	STRCODE  buffer[1];	///< �z��{��
};

/** �w�b�_�T�C�Y */
#define STRBUF_HEADER_SIZE	(sizeof(STRBUF) - sizeof(STRCODE))

//--------------------------------------------------------------
/**
 * ��Ԉُ�`�F�b�N�}�N��
 */
//--------------------------------------------------------------
#define  STRBUF_CHECK_STATE(pbuf)	{\
	GF_ASSERT((pbuf)!=NULL)	\
	GF_ASSERT((pbuf)->magicNumber == STRBUF_MAGIC_NUMBER);	\
}



//==============================================================================================
//==============================================================================================

//------------------------------------------------------------------
/**
 * ������o�b�t�@�I�u�W�F�N�g�쐬
 *
 * @param   size		�i�[�ł��镶�����iEOM���܂ށj
 * @param   heapID		�쐬��q�[�vID
 *
 * @retval  STRBUF*		�I�u�W�F�N�g�ւ̃|�C���^
 */
//------------------------------------------------------------------
STRBUF* STRBUF_Create( u32 size, u32 heapID )
{
	STRBUF* strbuf;

	strbuf = sys_AllocMemory( heapID, STRBUF_HEADER_SIZE + sizeof(STRCODE)*size );

	if( strbuf )
	{
		strbuf->magicNumber = STRBUF_MAGIC_NUMBER;
		strbuf->size = size;
		strbuf->strlen = 0;
		strbuf->buffer[0] = EOM_;
	}

	return strbuf;
}
//------------------------------------------------------------------
/**
 * ������o�b�t�@�I�u�W�F�N�g�폜
 *
 * @param   strbuf		�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void STRBUF_Delete( STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	// Free ����ɓ����A�h���X�ŌĂяo������MagicNumber�����̂܂܎c���Ă��肷��̂�
	strbuf->magicNumber = STRBUF_MAGIC_NUMBER+1;

	sys_FreeMemoryEz( strbuf );
}
//------------------------------------------------------------------
/**
 * ���e���N���A���ċ󕶎���ɂ���
 * �iCreate ����̓N���A����Ă���̂ŌĂԕK�v�͖����j
 *
 * @param   strbuf		�I�u�W�F�N�g�ւ̃|�C���^
 *
 */
//------------------------------------------------------------------
void STRBUF_Clear( STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	strbuf->strlen = 0;
	strbuf->buffer[0] = EOM_;
}

//------------------------------------------------------------------
/**
 * �o�b�t�@�Ԃ̕�����R�s�[
 *
 * @param   dst		�R�s�[��o�b�t�@�I�u�W�F�N�g
 * @param   src		�R�s�[���o�b�t�@�I�u�W�F�N�g
 *
 */
//------------------------------------------------------------------
void STRBUF_Copy( STRBUF* dst, const STRBUF* src )
{
	STRBUF_CHECK_STATE( dst );
	STRBUF_CHECK_STATE( src );

	if( dst->size > src->strlen )
	{
		memcpy( dst->buffer, src->buffer, (src->strlen+1)*sizeof(STRCODE) );
		dst->strlen = src->strlen;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow : dstsize=%d,  srclen=%d", dst->size, src->strlen);
}

//------------------------------------------------------------------
/**
 * �������e�̃o�b�t�@�𕡐�����
 *
 * @param   strbuf		�������̃o�b�t�@�I�u�W�F�N�g
 *
 * @retval  STRBUF*		�������ꂽ�o�b�t�@�I�u�W�F�N�g
 */
//------------------------------------------------------------------
STRBUF* STRBUF_CreateBufferCopy( const STRBUF* origin, u32 heapID )
{
	STRBUF* copy;

	STRBUF_CHECK_STATE( origin );

	copy = STRBUF_Create( origin->strlen+1, heapID );
	if( copy )
	{
		STRBUF_Copy( copy, origin );
	}

	return copy;
}

//------------------------------------------------------------------
/**
 * �o�b�t�@�ɐ������Z�b�g
 *
 * @param   dst			[out] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   number		���l
 * @param   keta		�ő包��
 * @param   dispType	�\���^�C�v
 * @param   codeType	�����R�[�h�^�C�v
 *
 */
//------------------------------------------------------------------
void STRBUF_SetNumber( STRBUF* dst, int number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	static const u32 n_max[] = 
	{
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};
	int minus;
    static const STRCODE sc_zen[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_};
    static const STRCODE sc_han[] = {h_n0_,h_n1_,h_n2_,h_n3_,h_n4_,h_n5_,h_n6_,h_n7_,h_n8_,h_n9_};


	STRBUF_CHECK_STATE( dst );

	minus = (number < 0);

	if( dst->size > (keta+minus) )
	{
		u32  num_f, num_i, i;
		const STRCODE* sctbl = (codeType==NUMBER_CODETYPE_ZENKAKU)? sc_zen : sc_han;

		STRBUF_Clear(dst);

		if(minus)
		{
			number *= -1;
			dst->buffer[dst->strlen++] = (codeType==NUMBER_CODETYPE_ZENKAKU)? bou_ : h_bou_;
		}


		for(i=n_max[keta-1]; i>0; i/=10)
		{
			num_i = (u16)( number / i );
			num_f = (u32)( number - ( i * num_i ) );

			if( dispType == NUMBER_DISPTYPE_ZERO )
			{
				dst->buffer[dst->strlen++] = (num_i<10)? sctbl[num_i] : hate_;
			}
			else if( num_i != 0 || i==1 )
			{
				dispType = NUMBER_DISPTYPE_ZERO;
				dst->buffer[dst->strlen++] = (num_i<10)? sctbl[num_i] : hate_;
			}
			else if( dispType == NUMBER_DISPTYPE_SPACE )
			{
				dst->buffer[dst->strlen++] = (codeType==NUMBER_CODETYPE_ZENKAKU)? spc_ : h_spc_;
			}

			number = num_f;
		}

		dst->buffer[dst->strlen] = EOM_;
		return;
	}

//	GF_ASSERT_MSG(0, "STRBUF overflow!");
	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, keta=%d", dst->size, keta);
}

//------------------------------------------------------------------
/**
 * ���������𐔎��ɕϊ�����  18�����Ή�  ���̊֐��͕����R�[�h�ɍ��E�����
 *
 * @param   src			�ϊ������������������Ă���o�b�t�@
 * @param   pbFlag      �ϊ��ł������ǂ���
 * @return  ���������ꍇ�ϊ�����
 *
 */
//------------------------------------------------------------------
u64 STRBUF_GetNumber( const STRBUF* src, BOOL* pbFlag  )
{
    u64 num = 0,add = 0, digit = 1;
    int i;
    STRCODE code;
    STRCODE zenNum = n0_;
    STRCODE hanNum = h_n0_;

    if(src->strlen > 18){
        return FALSE;  // �ϊ����s
    }
    for(i = (src->strlen - 1); i >= 0; i--){
        code = src->buffer[i];
        num = code - zenNum;
        if(num >= 10){  // �S�p�̂O�`�X�łȂ�
            num = code - hanNum;
            if(num >= 10){  // ���p�̂O�`�X�łȂ�
                *pbFlag = FALSE;
                return add;  // �ϊ����s
            }
        }
        num = num * digit;
        add += num;
        digit *= 10;  // ���A�b�v
    }
    *pbFlag = TRUE;
    return add;  // �ϊ�����
}

//------------------------------------------------------------------
/**
 * ��������r����
 *
 * @param   str1		������P
 * @param   str2		������Q
 *
 * @retval  int			"0 = ��v"
 * @retval  int			"1 = �s��v"
 */
//------------------------------------------------------------------
int STRBUF_Compare( const STRBUF* str1, const STRBUF* str2 )
{
	STRBUF_CHECK_STATE( str1 );
	STRBUF_CHECK_STATE( str2 );

	{
		int i;


		for(i=0; str1->buffer[i] == str2->buffer[i]; i++)
		{
			if( str1->buffer[i] == EOM_ )
			{
				return 0;
			}
		}

		return 1;
	}
}

//------------------------------------------------------------------
/**
 * �i�[����Ă��镶������Ԃ�
 *
 * @param   strbuf		������o�b�t�@�I�u�W�F�N�g
 *
 * @retval  u32		������
 */
//------------------------------------------------------------------
u32 STRBUF_GetLen( const STRBUF* str )
{
	STRBUF_CHECK_STATE( str );

	return str->strlen;
}


//------------------------------------------------------------------
/**
 * �i�[����Ă��镶���񂪉��s���邩�𒲂ׂ�
 *
 * @param   strbuf		������o�b�t�@�I�u�W�F�N�g
 *
 * @retval  u32		������̍s��
 */
//------------------------------------------------------------------
u32 STRBUF_GetLines( const STRBUF* str )
{
	STRBUF_CHECK_STATE( str );

	{
		int i;
		u32 cnt;

		for(i=0, cnt=1; i<str->strlen; i++)
		{
			if( str->buffer[i] == CR_ )
			{
				cnt++;
			}
		}
		return cnt;
	}
}

//------------------------------------------------------------------
/**
 * ������́A�w��s�݂̂�ʃo�b�t�@�փR�s�[����
 *
 * @param   dst		�R�s�[��o�b�t�@
 * @param   src		�R�s�[���o�b�t�@
 * @param   line	�s�ԍ��i0 origin�j
 *
 */
//------------------------------------------------------------------
void STRBUF_CopyLine( STRBUF* dst, const STRBUF* src, u32 line )
{
	STRBUF_CHECK_STATE( src );
	STRBUF_CHECK_STATE( dst );

	{
		int i = 0;

		if( line )
		{
			for(i=0; i<src->strlen; i++)
			{
				if( src->buffer[i] == CR_ )
				{
					if( --line == 0 )
					{
						i++;
						break;
					}
				}
			}
		}

		STRBUF_Clear( dst );
		for( ; i<src->strlen; i++)
		{
			if( src->buffer[i] == CR_ )
			{
				break;
			}
			STRBUF_AddChar( dst, src->buffer[i] );
		}
	}
}


//==============================================================================================
// ���̕����z�����舵���֐��Q
// �����𗘗p�ł��郂�W���[���͏o���������肷��
//==============================================================================================

//------------------------------------------------------------------
/**
 * ���̕�����iEOM�I�[�j���o�b�t�@�I�u�W�F�N�g�ɃZ�b�g����
 *
 * @param   strbuf		[out] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   sz			[in]  EOM �ŏI��镶���z��
 *
 */
//------------------------------------------------------------------
void STRBUF_SetStringCode( STRBUF* strbuf, const STRCODE* sz )
{
	STRBUF_CHECK_STATE(strbuf);

	strbuf->strlen = 0;
	while( *sz != EOM_ )
	{
		if( strbuf->strlen >= (strbuf->size-1) )
		{
			GF_ASSERT_MSG( 0, "STRBUF overflow: busize=%d", strbuf->size);
			break;
		}
		strbuf->buffer[ strbuf->strlen++ ] = *sz++;
	}

	strbuf->buffer[strbuf->strlen] = EOM_;
}
//------------------------------------------------------------------
/**
 * ���̕�����i�����w��j���o�b�t�@�I�u�W�F�N�g�ɃZ�b�g����
 *
 * @param   strbuf		[out] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   str			[in]  �����z��̐擪�|�C���^
 * @param   len			[in]  �Z�b�g���镶�����iEOM���܂ށj
 *
 */
//------------------------------------------------------------------
void STRBUF_SetStringCodeOrderLength( STRBUF* strbuf, const STRCODE* str, u32 len )
{
	STRBUF_CHECK_STATE(strbuf);

	if( len <= strbuf->size )
	{
		u32 i;

		memcpy( strbuf->buffer, str, len*sizeof(STRCODE) );

		for(i=0; i<len; i++)
		{
			if(strbuf->buffer[i] == EOM_)
			{
				break;
			}
		}
		strbuf->strlen = i;

		// EOM�t������Ȃ������񂾂�����t���Ă���
		if( i==len )
		{
			strbuf->buffer[len-1] = EOM_;
		}
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, strlen=%d", strbuf->size, len);
}

//------------------------------------------------------------------
/**
 * �o�b�t�@���琶�̕����z����R�s�[����
 *
 * @param   strbuf		[in]  �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   ary			[out] �R�s�[��z��
 * @param   arysize		[in]  �R�s�[��z��̗v�f��
 *
 */
//------------------------------------------------------------------
void STRBUF_GetStringCode( const STRBUF* strbuf, STRCODE* ary, u32 arysize )
{
	STRBUF_CHECK_STATE(strbuf);

	if( (strbuf->strlen+1) <= arysize )
	{
		memcpy( ary, strbuf->buffer, (strbuf->strlen+1)*sizeof(STRCODE) );
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: strlen=%d, arysize=%d", strbuf->strlen, arysize);
}
//------------------------------------------------------------------
/**
 * �o�b�t�@�I�u�W�F�N�g������镶���z��̃A�h���X��Ԃ�
 * �����̊֐����Ăяo���ӏ��͒�����B���Ԃ񕶎��o�͌n�̂݁B
 *
 * @param   strbuf				[in] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 *
 * @retval  const STRCODE*		�����z��̃A�h���X
 */
//------------------------------------------------------------------
const STRCODE* STRBUF_GetStringCodePointer( const STRBUF* strbuf )
{
	STRBUF_CHECK_STATE(strbuf);

	return strbuf->buffer;
}


//==============================================================================================
// ������̘A��������s���֐��B�y�y �����g�p�֎~ �z�z
// �g���ėǂ��̂̓��[�J���C�Y���l�����������񏈗����W���[���̂݁B
//==============================================================================================

//------------------------------------------------------------------
/**
 * ������A��
 *
 * @param   dst		�A�������o�b�t�@�I�u�W�F�N�g
 * @param   src		�A�����镶��������o�b�t�@�I�u�W�F�N�g
 *
 */
//------------------------------------------------------------------
void STRBUF_AddStr( STRBUF* dst, const STRBUF* src )
{
	STRBUF_CHECK_STATE(dst);
	STRBUF_CHECK_STATE(src);

	if( (dst->strlen + src->strlen + 1) <= dst->size )
	{
		memcpy( &(dst->buffer[dst->strlen]), src->buffer, (src->strlen+1)*sizeof(STRCODE) );
		dst->strlen += src->strlen;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, src_len=%d, dst_len=%d", dst->size, src->strlen, dst->strlen);
}

//------------------------------------------------------------------
/**
 * �P�����A��
 *
 * @param   dst			�A�������o�b�t�@�I�u�W�F�N�g
 * @param   code		�A�����镶���R�[�h
 *
 */
//------------------------------------------------------------------
void STRBUF_AddChar( STRBUF* dst, STRCODE code )
{
	STRBUF_CHECK_STATE( dst );

	if( (dst->strlen + 1) < dst->size )
	{
		dst->buffer[dst->strlen++] = code;
		dst->buffer[dst->strlen] = EOM_;
		return;
	}

	GF_ASSERT_MSG(0, "STRBUF overflow: busize=%d", dst->size);
}

//==============================================================================================
// �f�o�b�O�p
//==============================================================================================
#ifdef PM_DEBUG

//------------------------------------------------------------------
/**
 * �w�肳�ꂽ�|�C���^��STRBUF�Ƃ��ėL���Ȃ��̂ł��邩�`�F�b�N
 *
 * @param   ptr		�|�C���^
 *
 * @retval  BOOL	TRUE�ŗL���ł���
 */
//------------------------------------------------------------------
BOOL STRBUF_CheckValid(const void* ptr)
{
	return ( (ptr!=NULL) && (((const STRBUF*)ptr)->magicNumber == STRBUF_MAGIC_NUMBER) );
}

//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ��i�P�U�i�j�f�o�b�O��p
 *
 * @param   dst			[out] �o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^
 * @param   number		���l
 * @param   keta		�ő包��
 * @param   dispType	�\���^�C�v
 * @param   codeType	�����R�[�h�^�C�v
 *
 * @return	none
 *
 * @li	type = NUMBER_DISPTYPE_LEFT		���l
 * @li	type = NUMBER_DISPTYPE_SPACE	�E�l�A����Ȃ������͋�
 * @li	type = NUMBER_DISPTYPE_ZERO		�E�l�A����Ȃ������͐����̃[��
 */
//--------------------------------------------------------------------------------------------
void STRBUF_SetHexNumber(	STRBUF* dst, int num, u32 keta,
							NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType )
{
	u32	i,max;
	u32	num_i,num_f;

	u32 temp;
	
	static const STRCODE sc_zen[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_,
												A__,B__,C__,D__,E__,F__};
	static const STRCODE sc_han[] = {h_n0_,h_n1_,h_n2_,h_n3_,h_n4_,h_n5_,h_n6_,h_n7_,h_n8_,h_n9_,
												h_A__,h_B__,h_C__,h_D__,h_E__,h_F__};

	temp = num;
	if( dst->size > (keta) ){						
		const STRCODE* sctbl = (codeType==NUMBER_CODETYPE_ZENKAKU)? sc_zen : sc_han;

		STRBUF_Clear(dst);

		max = 1;
		for( i=1; i<keta; i++ ){
			max *= 16;
		}

		for( i=max; i>0; i/=16 ){
			num_i = temp / i;
			num_f = temp % i;
			if( dispType == NUMBER_DISPTYPE_ZERO ){
				dst->buffer[dst->strlen++] = ( num_i<16 )? sctbl[num_i] : hate_;
			}else if( num_i != 0 || i==1 ){
				dispType = NUMBER_DISPTYPE_ZERO;
				dst->buffer[dst->strlen++] = ( num_i<16 )? sctbl[num_i] : hate_;
			}else if( dispType == NUMBER_DISPTYPE_SPACE ){
				dst->buffer[dst->strlen++] = spc_;
			}
			temp = num_f;
		}
		dst->buffer[dst->strlen] = EOM_;

		return;
	}
	GF_ASSERT_MSG(0, "STRBUF overflow: bufsize=%d, keta=%d", dst->size, keta);
}

#endif
