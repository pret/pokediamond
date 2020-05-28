//============================================================================================
/**
 * @file	pm_str.c
 * @brief	������֘A����
 * @author	Hiroyuki Nakamura
 * @date	2004.11.02
 *
 *	�|�P�����`�f�a����ڐA
 *
 */
//============================================================================================
#define PM_STR_H_GLOBAL

#include "common.h"
//#include "fntsys.h"

#include "system/pm_str.h"


//============================================================================================
//	�V���{����`
//============================================================================================
#define	TEMP_BUF_MAX	( 16 )
#define	MSG_EXP_BUF_MAX	( 64 )


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================


//============================================================================================
//	�O���[�o���ϐ�
//============================================================================================
static const STRCODE* TmpBufAdrs[TEMP_BUF_MAX] = {};
STRCODE	MsgExpandBuffer[MSG_EXP_BUF_MAX] = {};

static const STRCODE n_ch[] = {n0_,n1_,n2_,n3_,n4_,n5_,n6_,n7_,n8_,n9_,A__,B__,C__,D__,E__,F__};

static const int n_max[] = 
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


//============================================================================================
//	�����񑀍�
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ������R�s�[
 *
 * @param	to_str		�R�s�[��o�b�t�@
 * @param	from_str	������f�[�^
 *
 * @return	�o�b�t�@�ɃR�s�[�����f�[�^�Ō��EOM_�ւ̃|�C���^
 *
 *	�f�[�^���Ȃ�(������f�[�^�擪��EOM_������)�ꍇ�A
 *	EOM_���o�b�t�@�擪�ɏ������݁A�����ւ̃|�C���^��Ԃ�
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcpy( STRCODE* to_str, const STRCODE* from_str )
{
	while( *from_str != EOM_ ){
		*to_str = *from_str;
		to_str++;
		from_str++;
	}
	*to_str = EOM_;
	return to_str;
}

//--------------------------------------------------------------------------------------------
/**
 * ������R�s�[�i�������w��j
 *
 * @param	to_str		�R�s�[��o�b�t�@
 * @param	from_str	������f�[�^
 * @param	len			�R�s�[���镶����
 *
 * @return	�u�R�s�[��o�b�t�@ + �R�s�[���镶�����v�ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strncpy( STRCODE* to_str, const STRCODE* from_str, u32 len )
{
	u32	i;

	for( i=0; i<len; i++ ){
		to_str[i] = from_str[i];
	}
	return &to_str[len];
}

//--------------------------------------------------------------------------------------------
/**
 * ������A��
 *
 * @param	to_str		�A�������f�[�^�iram��ɂ��邱�ƁI�I�j
 * @param	from_str	�A������f�[�^
 *
 * @return	�A����̃o�b�t�@��̃f�[�^����EOM_�ւ̃|�C���^
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcat( STRCODE* to_str, const STRCODE* from_str )
{
	while( *to_str != EOM_ ){
		to_str++;
	}
	return PM_strcpy( to_str, from_str );
}

//--------------------------------------------------------------------------------------------
/**
 * ������A���i�������w��j
 *
 * @param	to_str		�A�������f�[�^�iram��ɂ��邱�ƁI�I�j
 * @param	from_str	�A������f�[�^
 * @param	len			�A�����镶����
 *
 * @return	�A����̃o�b�t�@��̃f�[�^���ւ̃|�C���^��Ԃ�
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strncat( STRCODE* to_str, const STRCODE* from_str, u32 len )
{
	while( *to_str != EOM_ ){
		to_str++;
	}
	return PM_strncpy( to_str, from_str, len );
}

//--------------------------------------------------------------------------------------------
/**
 * �����񒷎擾
 *
 * @param	str		�Ώە�����ւ̃|�C���^
 *
 * @return	�Ώە�����̒����iEOM_�܂ł̕������j��Ԃ�
 */
//--------------------------------------------------------------------------------------------
u32 PM_strlen( const STRCODE* str )
{
	u32 len = 0;

	while( str[len] != EOM_ ){
		len++;
	}
	return len;
}

//--------------------------------------------------------------------------------------------
/**
 * �������r
 *
 * @param	s		�Ώە�����ւ̃|�C���^
 * @param	t		�Ώە�����ւ̃|�C���^
 *
 * @retval	"0 = ��v"
 * @retval	"1 = �s��v"
 *
 * @li	�b�W���֐��ƈႢ�����̔�r�͂��Ă��Ȃ�
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strcmp( const STRCODE* s, const STRCODE* t )
{
	while( *s == *t ){
		if( *s == EOM_ ){ return 0; }
		s++;
		t++;
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * �������r�i�������w��j
 *
 * @param	s		�Ώە�����ւ̃|�C���^
 * @param	t		�Ώە�����ւ̃|�C���^
 * @param	n		��r���镶����
 *
 * @retval	"0 = ��v"
 * @retval	"1 = �s��v"
 *
 * @li	�b�W���֐��ƈႢ�����̔�r�͂��Ă��Ȃ�
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strncmp( const STRCODE* s, const STRCODE* t, u32 n )
{
	while( *s == *t ){
		if( n == 0 ){ return 0; }
		if( *s == EOM_ && *t == EOM_ ){ return 0; }
		n--;
		s++;
		t++;
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**	
 * ��������̓`�F�b�N
 *
 * @param	str		�Ώە�����ւ̃|�C���^
 * @param	n		�`�F�b�N���镶����
 *
 * 
 * @retval	"1 = ���͂���"
 * @retval	"0 = ���͂Ȃ�"
 *
 * @li	�w�肳�ꂽ�o�b�t�@�ɋ󔒂�EOM�ȊO�̃R�[�h���܂܂�Ă��邩�`�F�b�N
 */
//--------------------------------------------------------------------------------------------
BOOL PM_strnchk( STRCODE* str, u32 n )
{
	u32	i;

	for( i=0; i<n; i++ ){
		if( (str[i] != spc_) && (str[i] != EOM_) ){
			return 1;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ������o�b�t�@���w�蕶���R�[�h�ŃN���A
 *
 * @param	str		������o�b�t�@
 * @param	code	�����R�[�h
 * @param	len		�N���A���镶����
 *
 * @return	EOM_ �A�h���X
*/
//--------------------------------------------------------------------------------------------
STRCODE* PM_strclear( STRCODE* str, STRCODE code, u32 len )
{
	u32 i;

	for( i=0; i<len; i++ ){
		str[i] = code;
	}
//	str[i] = EOM_;	//������+1�̏ꏊ�ɏ������݂ɍs���̂ŃR�����g�A�E�g
					//05.11.18 by iwasawa

	return &str[i];
}

//--------------------------------------------------------------------------------------------
/**
 * ������o�b�t�@��EOM_�R�[�h�ŃN���A
 *
 * @param	str		������o�b�t�@
 * @param	len		�N���A���镶����
 *
 * @return	�N���A�I�[��EOM_ �A�h���X
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strclearEOM_( STRCODE* str, u32 len )
{
	return PM_strclear( str, EOM_, len );
}

//--------------------------------------------------------------------------------------------
/**
 * ������R�s�[��A�w�蕶�����ɖ����Ȃ��������A�w�蕶���R�[�h�ŃN���A
 *
 * @param	to		�R�s�[�敶����o�b�t�@
 * @param	from	�R�s�[��������
 * @param	code	�N���A�����R�[�h
 * @param	len		�S�̂̕�����
 *
 * @return	EOM_ �A�h���X
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_strcpy_clear( STRCODE* to, const STRCODE* from, STRCODE code, u32 len )
{
	while( *from != EOM_ ){
		if( len == 0 ){ break; }
		*to = *from;
		to++;
		from++;
		len--;
	}
	if( len != 0 ){
		while( len-- ){
			*to = code;
			to++;
		}
	}
	*to = EOM_;

	return to;
}


//============================================================================================
//	���l��������
//============================================================================================
#define NUM_STR(n)	( n>=10 ? hate_ : n_ch[n] )		///<10�i�\�������擾
#define HEX_STR(n)	( n>=16 ? hate_ : n_ch[n] )		///<16�i�\�������擾

//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ��i�P�O�i�j
 *
 * @param	buf		������W�J�ꏊ
 * @param	num		���l
 * @param	type	�ϊ�����
 * @param	keta	����
 *
 * @return	���l�̌��ɏ�������EOM_�ւ̃|�C���^
 *
 * @li	type = NUM_MODE_LEFT	���l
 * @li	type = NUM_MODE_SPACE	�E�l�A����Ȃ������͋�
 * @li	type = NUM_MODE_ZERO	�E�l�A����Ȃ������͐����̃[��
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_NumMsgSet( STRCODE* buf, s32 num, u32 type, u32 keta )
{
	u32	i;
	u32 num_f;
	u32	num_i;

	for( i=n_max[keta-1]; i>0; i/=10 ){
		num_i = (u16)( num / i );
		num_f = (u32)( num - ( i * num_i ) );
		if( type == NUM_MODE_ZERO ){
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ��i�P�O�i�A�}�C�i�X�͂Ȃ��j
 *
 * @param	buf		������W�J�ꏊ
 * @param	num		���l
 * @param	type	�ϊ�����
 * @param	keta	����
 *
 * @return	���l�̌��ɏ�������EOM_�ւ̃|�C���^
 *
 * @li	type = NUM_MODE_LEFT	���l
 * @li	type = NUM_MODE_SPACE	�E�l�A����Ȃ������͋�
 * @li	type = NUM_MODE_ZERO	�E�l�A����Ȃ������͐����̃[��
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_NumMsgSetUnsigned( STRCODE* buf, u32 num, u32 type, u32 keta )
{
	u32	i;
	u32 num_f;
	u16	num_i;

	for( i=n_max[keta-1]; i>0; i/=10 ){
		num_i = (u16)( num / i );
		num_f = (u32)( num - ( i * num_i ) );
		if( type == NUM_MODE_ZERO ){
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (u16)NUM_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ��i�P�U�i�j
 *
 * @param	buf		������W�J�ꏊ
 * @param	num		���l
 * @param	type	�ϊ�����
 * @param	keta	����
 *
 * @return	���l�̌��ɏ�������EOM_�ւ̃|�C���^
 *
 * @li	type = NUM_MODE_LEFT	���l
 * @li	type = NUM_MODE_SPACE	�E�l�A����Ȃ������͋�
 * @li	type = NUM_MODE_ZERO	�E�l�A����Ȃ������͐����̃[��
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_HexNumMsgSet( STRCODE* buf, s32 num, u32 type, u32 keta )
{
	u32	i,max;
	u32	num_i,num_f;

	max = 1;
	for( i=1; i<keta; i++ ){
		max *= 16;
	}

	for( i=max; i>0; i/=16 ){
		num_i = num / i;
		num_f = num % i;
		if( type == NUM_MODE_ZERO ){
			*buf = (STRCODE)HEX_STR( num_i );
			buf++;
		}else if( num_i != 0 || i==1 ){
			type = NUM_MODE_ZERO;
			*buf = (STRCODE)HEX_STR( num_i );
			buf++;
		}else if( type == NUM_MODE_SPACE ){
			*buf = spc_;
			buf++;
		}
		num = num_f;
	}
	*buf = EOM_;

	return buf;
}


//============================================================================================
//	���b�Z�[�W�W�J���[�`��
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���b�Z�[�W�W�J�����iS_MSG_���݁j
 *
 * @param	buf		�W�J��
 * @param	data	�����b�Z�[�W
 *
 * @return	EOM_�̃A�h���X
 */
//--------------------------------------------------------------------------------------------
STRCODE* PM_MsgExpand( STRCODE* buf, const STRCODE* data )
{
	STRCODE	c;

	while(1){
		c = *data;
		data++;
		switch( c ){
		case EOM_:
			*buf = EOM_;
			return buf;
/*
		case I_MSG_:
			buf = PM_MsgExpand( buf, GetIndirectString( *data ) );
			data++;
			break;
*/
		case S_MSG_:
			buf = PM_MsgExpand( buf, TmpBufAdrs[*data] );
			data++;
			break;
/*
		case CTRL_:
			*(buf++) = c;
			c = *data; data++;
			*(buf++) = c;
			switch ( c ) {
			// �p�����[�^�Ȃ�
			case C_FNML_:
			case C_TRGWAIT_:
			case C_CLR_:
			case C_LANG_JP:
			case C_LANG_DEF:
			case C_MUSPAUSE_:
			case C_MUSCONTINUE_:
				break;
			// �p�����[�^3��
			case C_ACOL_:
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				break;
			// �p�����[�^2��
			case C_MUSPLAY_:
				*(buf++) = *(data++);
				*(buf++) = *(data++);
				break;
			// �ʏ�̓p�����[�^1��
			default:
				*(buf++) = *(data++);
				break;
			}
			break;
*/
		default:
			*buf = c;
			buf++;
		}
	}
	return NULL;
}


//============================================================================================
//	S_MSG_����
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * S_MSG_����������
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MsgExp_Init(void)
{
	MI_CpuFill32( (void *)TmpBufAdrs, NULL, TEMP_BUF_MAX * 4 );
}

//--------------------------------------------------------------------------------------------
/**
 * S_MSG_�ݒ菈��
 *
 * @param	id		ID
 * @param	str		�Z�b�g���镶����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void MsgExp_AdrsSet( u32 id, const STRCODE* str )
{
	if( id >= TEMP_BUF_MAX ){
#ifdef	OSP_ERR_MSGEXP_ADRS_SET		// S_MSG_�̐ݒ莸�s
		OS_Printf( "Error : MsgExp_AdrsSet(...) / id >= TEMP_BUF_MAX\n" );
#endif	// OSP_ERR_MSGEXP_ADRS_SET
		return;
	}
	TmpBufAdrs[id] = str;
}











//============================================================================================
//	str�֘A�̏���
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ���l�𕶎���ɕϊ� ( str )
 *
 * @param	str		������i�[�ꏊ
 * @param	num		�ϊ����鐔�l
 * @param	keta	��
 *
 * @return	none
 *
 * @li	�t�@�C�����̍쐬�ȂǂɎg�p����֐��B
 * @li	keta = 0  : ���l��
 * @li	keta != 0 : 0�Ŗ��߂�
 */
//--------------------------------------------------------------------------------------------
void StrNumSet( char * str, u32 num, u32 keta )
{
	char zero[10];
	u32	num_i;
	u32	i;

	if( keta == 0 ){
		sprintf( str, "%d", num );
	}else{
		memset( zero, '\0', 10 );
		for( i=n_max[keta-1]; i>0; i/=10 ){
			num_i = num / i;
			sprintf( zero, "%d", num_i );
			strcat( str, zero );
			num = num - ( i * num_i );
		}
	}
}











