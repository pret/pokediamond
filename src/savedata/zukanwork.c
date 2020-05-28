//============================================================================================
/**
 * @file	zukanwork.c
 * @brief	�}�ӏ�ԃA�N�Z�X�p�\�[�X
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.15
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"
#include "poketool/poke_tool.h"

#include "savedata/zukanwork.h"

#include "poketool/monsno.h"
#include "include/application/zukanlist/zkn_world_text_data.h"
#include "src/application/zukanlist/zkn_worldtext.h"

//============================================================================================
//============================================================================================
enum {
	POKEZUKAN_ARRAY_LEN = 16,	///<�|�P�����}�Ӄt���O�z��̂�������16 * 32 = 512�܂ő��v

	POKEZUKAN_UNKNOWN_NUM = UNK_END,///<�A���m�[����

	MAGIC_NUMBER = 0xbeefcafe,

	POKEZUKAN_DEOKISISU_MSK = 0xf,	// bit�}�X�N
};

//----------------------------------------------------------
/**
 * @brief	������ԃf�[�^�^��`
 */
//----------------------------------------------------------
struct _ZUKAN_WORK {
	u32 zukan_magic;						///<�}�W�b�N�i���o�[
	u32 get_flag[POKEZUKAN_ARRAY_LEN];		///<�߂܂����t���O�p���[�N
	u32 see_flag[POKEZUKAN_ARRAY_LEN];		///<�������t���O�p���[�N
	u32 sex_flag[2][POKEZUKAN_ARRAY_LEN];	///<�I�X���X�t���O�p���[�N
	u32 PachiRandom;						///<�p�b�`�[���p�������ێ����[�N
	u8 SiiusiTurn;							///<�V�[�E�V�p���������ێ����[�N		2bit�K�v	1bit*2���
	u8 SiidorugoTurn;						///<�V�[�h���S�p���������ێ����[�N	2bit�K�v	1bit*2���
	u8 MinomuttiTurn;						///<�~�m���b�`�p���������ێ����[�N	6bit�K�v	2bit*3���
	u8 MinomesuTurn;						///<�~�m���X�p���������ێ����[�N		6bit�K�v	2bit*3���
	u8 UnknownTurn[ POKEZUKAN_UNKNOWN_NUM ];///<�A���m�[�����������ԍ�
	u8 GraphicVersionUp;					///<�O���t�B�b�N�o�[�W�����p�@�\�g���t���O
	u8 TextVersionUp[ ZKN_WORLD_TEXT_POKE_NUM ];	///<����o�[�W�����A�b�v�}�X�N
	u8 TextVersionUpMasterFlag;				///<����o�[�W�����A�b�vMaster�t���O
	u8 zukan_get;							///<������擾�t���O
	u8 zenkoku_flag;						///<�S���}�ӕێ��t���O
};

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������f�[�^�p���[�N�̃T�C�Y�擾
 * @return	int		ZUKAN_WORK�̃T�C�Y
 */
//----------------------------------------------------------
int ZukanWork_GetWorkSize(void)
{
	return sizeof(ZUKAN_WORK);
}
//----------------------------------------------------------
/**
 * @brief	������f�[�^�p���[�N�̐�������
 * @param	heapID		�g�p����q�[�v�̎w��
 * @return	ZUKAN_WORK	��������ZUKAN_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
ZUKAN_WORK * ZukanWork_AllocWork(u32 heapID)
{
	ZUKAN_WORK * zw;
	zw = sys_AllocMemory(heapID, sizeof(ZUKAN_WORK));
	ZukanWork_Init(zw);
	return zw;
}

//----------------------------------------------------------
/**
 * @brief	������f�[�^�p���[�N�̃R�s�[
 * @param	from	�R�s�[��ZUKAN_WORK�ւ̃|�C���^
 * @param	to		�R�s�[��ZUKAN_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
void ZukanWork_Copy(const ZUKAN_WORK * from, ZUKAN_WORK * to)
{
	MI_CpuCopy8(from, to, sizeof(ZUKAN_WORK));
}

//============================================================================================
//
//				�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�����񃏁[�N�̐������`�F�b�N
 */
//----------------------------------------------------------
static inline void zukan_incorrect(const ZUKAN_WORK * zw)
{
	GF_ASSERT(zw->zukan_magic == MAGIC_NUMBER);
}
//----------------------------------------------------------
/**
 * @brief	�|�P�����i���o�[�͈̔̓`�F�b�N
 */
//----------------------------------------------------------
static inline BOOL monsno_incorrect(u16 monsno)
{
	if (monsno == 0 || monsno > MONSNO_END) {
		GF_ASSERT_MSG(0, "�|�P�����i���o�[�ُ�F%d\n", monsno);
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	�ėp�r�b�g�`�F�b�N
 */
//----------------------------------------------------------
static inline BOOL check_bit(const u8 * array, u16 flag_id)
{
	flag_id --;
	return 0 != (array[flag_id >> 3] & (1 << (flag_id & 7)));
}
//----------------------------------------------------------
/**
 * @brief	�ėp�r�b�g�Z�b�g
 */
//----------------------------------------------------------
static inline void set_bit(u8 * array, u16 flag_id)
{
	flag_id --;
	array[flag_id >> 3] |= 1 << (flag_id & 7);
}
//----------------------------------------------------------
/**
 * @brief	�ėp1�r�b�g�f�[�^�Z�b�g
 * ���̃r�b�g���N���[���ɂ��Ă���ݒ肵�܂�
 */
//----------------------------------------------------------
static inline void setnum_bit(u8 * array, u8 num, u16 flag_id)
{
	GF_ASSERT( num < 2 );
	flag_id --;

	array[flag_id >> 3] &= ~(1 << (flag_id & 7));
	array[flag_id >> 3] |= num << (flag_id & 7);
}

#if 0
static inline void reset_bit(u8 * array, u16 flag_id)
{
	array[flag_id >> 3] &= (1 << (flag_id & 7)) ^ 0xff;
}
#endif
//----------------------------------------------------------
/**
 * @brief	�ėp�r�b�g���J�E���g����
 */
//----------------------------------------------------------
static inline u16 count_bit(const u32 * array, u32 array_max)
{
	int count, idx;
	u32 item;
	count = 0;
	for (idx = 0; idx < array_max; idx ++) {
		for (item = array[idx]; item != 0; item >>= 1) {
			if (item & 1) {
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------
/**
 * @brief	�ėp2�r�b�g�`�F�b�N
 * ��1bit�ł�1�`x���w�肷��悤�ɂȂ��Ă�����
 * 2bit�ł�0�`x���w�肷��悤�ɂ���
 */
//----------------------------------------------------------
static inline u32 check_bit2(const u8 * array, u16 flag_id)
{
	return (array[flag_id >> 2] >> ((flag_id & 3)*2)) & 0x3;
}
//----------------------------------------------------------
/**
 * @brief	�ėp2�r�b�g�f�[�^�Z�b�g
 * ���̃r�b�g���N���[���ɂ��Ă���ݒ肵�܂�
 */
//----------------------------------------------------------
static inline void setnum_bit2(u8 * array, u8 num, u16 flag_id)
{
	GF_ASSERT( num < 4 );

	array[flag_id >> 2] &= ~(0x3 << ((flag_id & 3)*2) );
	array[flag_id >> 2] |= num << ((flag_id & 3)*2);
}


//----------------------------------------------------------
/**
 * @brief	�݂��r�b�g�ݒ�
 */
//----------------------------------------------------------
static inline void set_see_bit(ZUKAN_WORK * zw, u16 flag_id)
{
	set_bit((u8*)zw->see_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	���܂����r�b�g�ݒ�
 */
//----------------------------------------------------------
static inline void set_get_bit(ZUKAN_WORK * zw, u16 flag_id)
{
	set_bit((u8*)zw->get_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	���ʃr�b�g�ݒ�	���ۂɐݒ�
 * �ŏ��̐��ʐݒ��2�v�f�ڂ̔z��ɂ������l��ݒ肷��
 * ����ɂ��2�v�f�ڂ������l�̎��͈Ⴄ���ʂ̃|�P�������݂Ă��Ȃ�
 * �Ƃ������ƂɂȂ�
 */
//----------------------------------------------------------
static inline void set_sex_bit_first_second(ZUKAN_WORK * zw, u8 num, u8 no, u16 flag_id)
{
	if( no == ZUKAN_WORK_SEX_FIRST ){
		setnum_bit((u8*)zw->sex_flag[ZUKAN_WORK_SEX_SECOND], num, flag_id);
	}
	setnum_bit((u8*)zw->sex_flag[no], num, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	���ʃr�b�g�ݒ�
 */
//----------------------------------------------------------
static inline void set_sex_bit(ZUKAN_WORK * zw, u8 num, u8 no, u16 monsno)
{
	GF_ASSERT_MSG( num <= 2, "num = %d", num );	// �j�@���@�s���ȊO�����܂���
	if( num == PARA_UNK ){		// UNKNOW��
		num = PARA_MALE;		// �j�ɂ���
	}
	set_sex_bit_first_second(zw, num, no, monsno);
}
//----------------------------------------------------------
/**
 * @brief	�݂��r�b�gONOFF�`�F�b�N
 */
//----------------------------------------------------------
static inline BOOL check_see_bit(const ZUKAN_WORK * zw, u16 flag_id)
{
	return check_bit((const u8*)zw->see_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	���܂����r�b�gONOFF�`�F�b�N
 */
//----------------------------------------------------------
static inline BOOL check_get_bit(const ZUKAN_WORK * zw, u16 flag_id)
{
	return check_bit((const u8*)zw->get_flag, flag_id);
}
//----------------------------------------------------------
/**
 * @brief	���ʃr�b�gONOFF�`�F�b�N
 */
//----------------------------------------------------------
static inline u8 check_sex_bit(const ZUKAN_WORK * zw, u16 flag_id, u8 first_second)
{
	return check_bit((const u8*)zw->sex_flag[first_second], flag_id);
}

//----------------------------------------------------------
/**
 * @brief	�ő̗�����ݒ�
 */
//----------------------------------------------------------
static inline void SetZukanRandom(ZUKAN_WORK * zw, u16 monsno, u32 rand)
{
	if (monsno == MONSNO_PATTIIRU) {
		zw->PachiRandom = rand;
	}
}

//----------------------------------------------------------
/**
 * @brief	�A���m�[���̌��ݐݒ萔���擾
 */
//----------------------------------------------------------
static inline int get_zukan_unknown_turn_num( const ZUKAN_WORK * zw )
{
	int i;
	for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
		if( zw->UnknownTurn[i] == 0xff ){
			break;
		}
	}
	return i;
}
//----------------------------------------------------------
/**
 * @brief	�A���m�[���t�H�[���ݒ�ς݂��`�F�b�N
 */
//----------------------------------------------------------
static inline BOOL check_zukan_unknown_turn_set( const ZUKAN_WORK * zw, u8 form )
{
	int i;
	for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
		if( zw->UnknownTurn[i] == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	�A���m�[�����������f�[�^�̍Ō�Ɍ`��ID��ݒ�
 */
//----------------------------------------------------------
static inline void SetZukanUnknownTurn( ZUKAN_WORK * zw, int form)
{
	int set_idx;

	// �ݒ�ς݂��`�F�b�N
	if( check_zukan_unknown_turn_set( zw, form ) ){
		return;
	}

	set_idx = get_zukan_unknown_turn_num( zw );
	if( set_idx < POKEZUKAN_UNKNOWN_NUM ){
		zw->UnknownTurn[ set_idx ] = form;
	}
}

//----------------------------------------------------------
/**
 * @brief	�V�[�E�V�@�V�[�h���S�̌��ݐݒ萔���擾
 */
//----------------------------------------------------------
static int get_zukan_siiusi_turn_num( const ZUKAN_WORK * zw, u32 monsno )
{
	u32 first_form;
	u32 second_form;
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	
	// ���Ă����Ȃ��Ƃ���0
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return 0;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}
	first_form = check_bit( arry, 1 );	
	second_form = check_bit( arry, 2 );	

	if( first_form == second_form ){	// �ŏ��ƂQ�߂��ꏏ�Ȃ�P�񂾂�
		return 1;
	}
	return 2;
}
//----------------------------------------------------------
/**
 * @brief	�~�m���b�`�@�~�m���X�@�t�H�[���ݒ�ς݂��`�F�b�N
 * @param	form	0 or 1
 * *���� 0or1����ō쐬���Ă��܂��B
 */
//----------------------------------------------------------
static BOOL check_zukan_siiusi_turn_set( const ZUKAN_WORK * zw, u32 monsno, u8 form )
{
	u32 get_form;
	u32 i;
	u32 roop_num;
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	
	// ���Ă����Ȃ��Ƃ��͐ݒ肳��Ă���킯���Ȃ�
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return FALSE;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}

	// �ݒ萔���`�F�b�N
	// �P�񂵂����Ă��Ȃ��Ƃ��͂Q�ڂ̃r�b�g�́A
	// �_�~�[�f�[�^�Ȃ̂ŁA�����������Ȃ�
	roop_num = get_zukan_siiusi_turn_num( zw, monsno );
	for( i=0; i<roop_num; i++ ){
		get_form = check_bit( arry, i+1 );	
		if( get_form == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	�V�[�E�V�@�V�[�h���S���������f�[�^�̍Ō�Ɍ`��ID��ݒ�
 * *���� 0or1����ō쐬���Ă��܂��B
 */
//----------------------------------------------------------
static void SetZukanSiiusiTurn( ZUKAN_WORK * zw, u32 monsno, int form)
{
	int set_idx;
	u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );

	// �ݒ�ς݂��`�F�b�N
	if( check_zukan_siiusi_turn_set( zw, monsno, form ) ){
		return;
	}

	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}

	set_idx = get_zukan_siiusi_turn_num( zw, monsno );
	if( set_idx < 2 ){	// 0�����Ȃ�ŏ��ɐݒ�@1�Ȃ�2�߂ɐݒ� 2�Ȃ�ݒ肵�Ȃ�
		setnum_bit( arry, form, set_idx+1 );
		if( set_idx == 0 ){
			setnum_bit( arry, form, set_idx+2 );	// ���������G�ŕۑ�����
		}
	}
}

//----------------------------------------------------------
/**
 * @brief	�~�m���b�`�@�~�m���X�̌��ݐݒ萔���擾
 * ���`��0�`2����
 */
//----------------------------------------------------------
static int get_zukan_minomutti_turn_num( const ZUKAN_WORK * zw, u32 monsno )
{
	u32 get_form;
	int i;
	const u8* arry;

	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	// ���Ă����Ȃ��Ƃ���0
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return 0;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	for( i=0; i<3; i++ ){
		get_form = check_bit2( arry, i );
		if( get_form == 3 ){
			break;
		}
	}
	return i;
}
//----------------------------------------------------------
/**
 * @brief	�~�m���b�`�@�~�m���X�@�t�H�[���ݒ�ς݂��`�F�b�N
 * @param	form	0 or 1 or 2
 * ���`��0�`2����
 */
//----------------------------------------------------------
static BOOL check_zukan_minomutti_turn_set( const ZUKAN_WORK * zw, u32 monsno, u8 form )
{
	u32 get_form;
	int i;
	const u8* arry;

	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	// ���Ă����Ȃ��Ƃ���FALSE
	if( ZukanWork_GetPokeSeeFlag( zw, monsno ) == FALSE ){	
		return FALSE;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	for( i=0; i<3; i++ ){
		get_form = check_bit2( arry, i );
		if( get_form == form ){
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	�~�m���b�`�@�~�m���X���������f�[�^�̍Ō�Ɍ`��ID��ݒ�
 * ���`��0�`2����
 */
//----------------------------------------------------------
static void SetZukanMinomuttiTurn( ZUKAN_WORK * zw, u32 monsno, int form)
{
	int set_idx;
	u8* arry;
	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );

	// �ݒ�ς݂��`�F�b�N
	if( check_zukan_minomutti_turn_set( zw, monsno, form ) ){
		return;
	}

	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}

	set_idx = get_zukan_minomutti_turn_num( zw, monsno );
	if( set_idx < 3 ){
		setnum_bit2( arry, form, set_idx );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����ݒ�
 *
 *	@param	p_arry	�i�[�̈�
 *	@param	no	�f�I�L�V�X�t�H����
 *	@param	num	���������Ԑݒ�
 */
//-----------------------------------------------------------------------------
static inline void setDeokisisuFormNoCore( u32* p_arry, u8 no, u8 num )
{
	u32 shift = (24 + (num * 4));
	u32 msk = ~(POKEZUKAN_DEOKISISU_MSK << shift);
	p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] &= msk;
	p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] |= (no << shift);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����ݒ�
 *
 *	@param	zw	�}�Ӄ��[�N
 *	@param	no	�f�I�L�V�X�t�H����
 *	@param	num	���������Ԑݒ�
 */
//-----------------------------------------------------------------------------
static void setDEOKISISUFormNo( ZUKAN_WORK * zw, u8 no, u8 num )
{
	GF_ASSERT( num < ZUKAN_WORK_DEOKISISU_FORM_NUM );
	GF_ASSERT( no <= POKEZUKAN_DEOKISISU_INIT );
	// �f�I�L�V�X�i���o�[��ݒ�
	// �߂܂����t���O�̌��15bit�󂢂Ă���̂�
	// ���4bit���Ƀf�[�^��o�^���Ă���
	if( num < ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM ){
		setDeokisisuFormNoCore( zw->get_flag, no, num );
	}else{
		setDeokisisuFormNoCore( zw->see_flag, no, num-ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����擾
 *
 *	@param	p_arry	�i�[�̈�
 *	@param	num	���������Ԑݒ�
 *
 *	@retval	�t�H�����i���o�[
 */
//-----------------------------------------------------------------------------
static inline u32 getDeokisisuFormNoCore( const u32* p_arry, u8 num )
{
	u32 shift = (24 + (num * 4));
	u32 ret = (p_arry[ POKEZUKAN_ARRAY_LEN - 1 ] >> shift) & POKEZUKAN_DEOKISISU_MSK;
	return ret;
}
//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����擾
 *
 *	@param	zw	�}�Ӄ��[�N
 *	@retval	�f�I�L�V�X�t�H����
 */
//-----------------------------------------------------------------------------
static inline u32 getDEOKISISUFormNo( const ZUKAN_WORK * zw, u8 num )
{
	u32 form;
	// �f�I�L�V�X�i���o�[��ݒ�
	// �߂܂����t���O�̌��15bit�󂢂Ă���̂�
	// ���4bit�Ƀf�[�^��o�^���Ă���
	if( num < ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM ){
		form = getDeokisisuFormNoCore( zw->get_flag, num );
	}else{
		form = getDeokisisuFormNoCore( zw->see_flag, num - ZUKAN_WORK_DEOKISISU_FORM_SAVEDATA_CUTNUM );
	}
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	���܂łɌ����f�I�L�V�X�̐���Ԃ�
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	���܂łɌ����f�I�L�V�X�̐���Ԃ�
 */
//-----------------------------------------------------------------------------
static u32 nowGetDeokisisuFormNum( const ZUKAN_WORK * zw )
{
	int i;

	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		if( getDEOKISISUFormNo( zw, i ) == POKEZUKAN_DEOKISISU_INIT  ){
			break;
		}
	}
	return i;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�ȑO�ɂ��̌`��̃f�I�L�V�X�����Ă��邩�`�F�b�N
 *
 *	@param	zw	�}�Ӄ��[�N
 *	@param	formno �`��
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	���Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
static BOOL checkSeeDeokisisuFormNo( const ZUKAN_WORK * zw, u32 formno )
{
	int i;
	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		if( getDEOKISISUFormNo( zw, i ) == formno  ){
			return TRUE;
		}
	}
	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	�t�H�[���i���o�[�ݒ�@�p�b�N
 */
//-----------------------------------------------------------------------------
static void SetDeokisisuFormNo( ZUKAN_WORK * zw, u16 monsno, POKEMON_PARAM* pp  )
{
	u8 form = PokeParaGet( pp, ID_PARA_form_no, NULL );
	u32 setno;

	if( monsno == MONSNO_DEOKISISU ){
		// �܂����Ă��Ȃ����`�F�b�N
		if( checkSeeDeokisisuFormNo( zw, form ) == FALSE ){
			setno = nowGetDeokisisuFormNum( zw );	// �ݒ�ʒu
			setDEOKISISUFormNo( zw, form, setno );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����i���o�[�o�b�t�@������
 *
 *	@param	zw	�}�Ӄ��[�N
 */
//-----------------------------------------------------------------------------
static void InitDeokisisuFormNo( ZUKAN_WORK * zw )
{
	int i;
	for( i=0; i<ZUKAN_WORK_DEOKISISU_FORM_NUM; i++ ){
		setDEOKISISUFormNo( zw, 0xf, i );	// 0xf�ŏ���������
	}
}





//----------------------------------------------------------
/**
 * @brief	�����ȃ|�P�����̌��������f�[�^�̕ۑ�
 */
//----------------------------------------------------------
static void SetZukanSpecialTurn(ZUKAN_WORK * zw, u16 monsno, POKEMON_PARAM* pp)
{
	int form;
	
	// �A���m�[���@�E�~�E�V�@�~�m���V�̏��Ԃ̐ݒ�
	if( monsno == MONSNO_ANNOON ){
		form = PokeParaUnknownFormGet( pp );
		SetZukanUnknownTurn( zw, form );
	}else if( monsno == MONSNO_MINOMUTTI ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanMinomuttiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_MINOMESU ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanMinomuttiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_SIIUSI ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanSiiusiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_SIIDORUGO ){
		form = PokeParaGet( pp, ID_PARA_form_no, NULL );
		SetZukanSiiusiTurn( zw, monsno, form );
	}else if( monsno == MONSNO_DEOKISISU ){
		SetDeokisisuFormNo( zw, monsno, pp );	// �f�I�L�V�X�̃t�H������ۑ�
	}
}

//----------------------------------------------------------
/**
 * @brief	�e�L�X�g�o�[�W�����z��C���f�b�N�X�������X�^�[�i���o�[����擾
 */
//----------------------------------------------------------
static inline int get_zukan_textversion_idx(u16 monsno)
{
	return ZKN_WT_GetMonsNo_TEXTVERPokeNum( monsno );
}
//----------------------------------------------------------
/**
 * @brief	�e�L�X�g�o�[�W�����t���O�ݒ�
 */
//----------------------------------------------------------
static void SetZukanTextVersionUp(ZUKAN_WORK * zw, u16 monsno, u32 lang)
{
	int idx;
	int zkn_world_text_code;
	
	
	idx = get_zukan_textversion_idx( monsno );
	zkn_world_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( lang );

	// ���̃|�P�����ɊO����f�[�^�͂Ȃ�
	if(idx == ZKN_WORLD_TEXT_POKE_NUM){ return; }

	// ���̍��̊O����f�[�^�͂Ȃ�
	if(zkn_world_text_code == ZKN_WORLD_TEXT_NUM){ return; }

	zw->TextVersionUp[ idx ] |= 1 << zkn_world_text_code;
}
//----------------------------------------------------------
/**
 * @brief	�ʏ�̃|�P�������ʎ擾
 */
//----------------------------------------------------------
static u32 get_normal_poke_sex( const ZUKAN_WORK * zw, u16 monsno, int first_second )
{
	u32 sex_first, sex_second;
	u32 ret_sex;

	// ��΂ɕs���ȃ|�P������first�͕s����second�̓G���[��Ԃ�
	if( PokePersonalParaGet(monsno,ID_PER_sex) == MONS_UNKNOWN ){
		if( first_second == ZUKAN_WORK_SEX_FIRST ){
			return PARA_UNK;
		}else{
			return ZUKAN_WORK_GET_SEX_ERR;
		}
	}
	
	// ���Ɍ������ʂ��ݒ肳��Ă���̂��`�F�b�N���邽�߂�
	// �ǂ����̏ꍇ�ł��ŏ��Ɍ������ʂ��擾
	sex_first = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );

	// ���Ɍ������ʂ��擾����Ȃ玟�Ɍ������ʂ��擾
	if( first_second == ZUKAN_WORK_SEX_SECOND ){
		sex_second = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_SECOND );

		// �ŏ��Ɍ������ʂƈꏏ==�܂����Ă��Ȃ�
		if( sex_second == sex_first ){
			ret_sex = ZUKAN_WORK_GET_SEX_ERR;
		}else{
			ret_sex = sex_second;
		}
	}else{
		ret_sex = sex_first;
	}

	return ret_sex;
}

//----------------------------------------------------------
/**
 * @brief	�A���m�[�����������Ԏ擾
 */
//----------------------------------------------------------
static inline int get_unknown_see_form( const ZUKAN_WORK * zw, int idx )
{
	return zw->UnknownTurn[ idx ];
}

//----------------------------------------------------------
/**
 * @brief	�V�[�E�V�@�V�[�h���S���������Ԏ擾
 *���� 0or1����ō쐬���Ă��܂��B
 */
//----------------------------------------------------------
static inline int get_siiusi_see_form( const ZUKAN_WORK * zw, u32 monsno, int idx )
{
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) );
	GF_ASSERT( idx < 2 );
	
	if( monsno == MONSNO_SIIUSI ){
		arry = &zw->SiiusiTurn;
	}else{
		arry = &zw->SiidorugoTurn;
	}
	return check_bit( arry, idx+1 );
}

//----------------------------------------------------------
/**
 * @brief	�~�m���b�`�@�~�m���X���������Ԏ擾
 *���� 0�`2����ō쐬���Ă��܂��B
 */
//----------------------------------------------------------
static inline int get_minomutti_see_form( const ZUKAN_WORK * zw, u32 monsno, int idx )
{
	const u8* arry;
	GF_ASSERT( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) );
	GF_ASSERT( idx < 3 );
	
	if( monsno == MONSNO_MINOMUTTI ){
		arry = &zw->MinomuttiTurn;
	}else{
		arry = &zw->MinomesuTurn;
	}
	return check_bit2( arry, idx );
}


//----------------------------------------------------------------------------
/**
 *	@brief	�[���R�N�}�ӊ����ɕK�v�ȃ|�P�������`�F�b�N
 */
//-----------------------------------------------------------------------------
static BOOL check_ZenkokuCompMonsno( u16 monsno )
{
	int i;
	BOOL cut_check;
	static const u16 cut_check_monsno[ ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM ] = {
		MONSNO_MYUU,
		MONSNO_RUGIA,
		MONSNO_HOUOU,
		MONSNO_SEREBHI,
		MONSNO_ZIRAATI,
		MONSNO_DEOKISISU,
		MONSNO_ERUFI,
		MONSNO_MANAFI,
		MONSNO_DAAKU,
		MONSNO_EURISU,
		MONSNO_AUSU,
	};

	// �`�F�b�N���O�|�P�����`�F�b�N
	cut_check = TRUE;
	for( i=0; i<ZUKAN_WORK_ZENKOKU_COMP_NOPOKE_NUM; i++ ){
		if( cut_check_monsno[ i ] == monsno ){
			cut_check = FALSE;
		}
	}
	return cut_check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V���I�E�}�ӊ����ɕK�v�ȃ|�P�������`�F�b�N
 */
//-----------------------------------------------------------------------------
static BOOL check_ShinouCompMonsno( u16 monsno )
{
	int i;
	BOOL cut_check;
	static const u16 cut_check_monsno[ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM] = {
		MONSNO_MANAFI,
	};

	// �`�F�b�N���O�|�P�����`�F�b�N
	cut_check = TRUE;
	for( i=0; i<ZUKAN_WORK_SHINOU_COMP_NOPOKE_NUM; i++ ){
		if( cut_check_monsno[ i ] == monsno ){
			cut_check = FALSE;
		}
	}
	return cut_check;
}

//============================================================================================
//
//			�������񑀍�p�̊O�����J�֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		�����񃏁[�N�̏�����
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void ZukanWork_Init(ZUKAN_WORK * zw)
{
	memset(zw, 0, sizeof(ZUKAN_WORK));
	zw->zukan_magic = MAGIC_NUMBER;
	zw->zenkoku_flag = FALSE;

	// �߂܂������ԃt���O�Ƀ_�~�[�f�[�^�ݒ�
	memset( zw->UnknownTurn, 0xff, sizeof(u8) *  POKEZUKAN_UNKNOWN_NUM );
	zw->SiiusiTurn = 0xff;		
	zw->SiidorugoTurn = 0xff;	
	zw->MinomuttiTurn = 0xff;	
	zw->MinomesuTurn = 0xff;	

	// �f�I�L�V�X�t�H�����^�C�v�ۑ��̈�̏�����
	InitDeokisisuFormNo( zw );
}

//----------------------------------------------------------
/**
 * @brief	�|�P���������܂������̎擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @return	u16		�߂܂�����
 */
//----------------------------------------------------------
u16 ZukanWork_GetPokeGetCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;

	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			count ++;
		}
	}
	return count;

	// �����ł����A�f�I�L�V�X�t���O��get_flag�̌��ɓ��ꂽ�̂ŁA�g�p�ł��܂���
//	return count_bit(zw->get_flag, POKEZUKAN_ARRAY_LEN);

}

//----------------------------------------------------------
/**
 * @brief	�|�P���������������̎擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @return	u16		��������
 */
//----------------------------------------------------------
u16 ZukanWork_GetPokeSeeCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;

	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			count ++;
		}
	}
	return count;

	// �����ł����A�f�I�L�V�X�t���O��get_flag�̌��ɓ��ꂽ�̂ŁA�g�p�ł��܂���
//	return count_bit(zw->see_flag, POKEZUKAN_ARRAY_LEN);
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̐}��Ӱ�ނ̃|�P������߂܂������擾
 *	@param	zw		�}�Ӄ��[�N�ւ̃|�C���^
 *	@return	�߂܂�����
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZukanPokeGetCount(const ZUKAN_WORK * zw)
{
	if( ZukanWork_GetZenkokuZukanFlag( zw ) ){
		return ZukanWork_GetPokeGetCount( zw );
	}
	return ZukanWork_GetShinouPokeGetCount( zw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	���݂̐}��Ӱ�ނ̃|�P�������������擾
 *	@param	zw		�}�Ӄ��[�N�ւ̃|�C���^
 *	@return ������
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZukanPokeSeeCount(const ZUKAN_WORK * zw)
{
	if( ZukanWork_GetZenkokuZukanFlag( zw ) ){
		return ZukanWork_GetPokeSeeCount( zw );
	}
	return ZukanWork_GetShinouPokeSeeCount( zw );
}

//----------------------------------------------------------
/**
 * �y�V���I�E�z
 * @brief	�|�P���������܂������̎擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @return	u16		�߂܂�����
 */
//----------------------------------------------------------
u16 ZukanWork_GetShinouPokeGetCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;
	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			// �ݵ��޶݂ɂ��邩�`�F�b�N
			if( PokeZenkokuNo2ShinouNo( i ) != 0 ){
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------
/**
 * �y�V���I�E�z
 * @brief	�|�P���������������̎擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @return	u16		��������
 */
//----------------------------------------------------------
u16 ZukanWork_GetShinouPokeSeeCount(const ZUKAN_WORK * zw)
{
	int i;
	int count;
	zukan_incorrect(zw);
	count= 0;
	for( i=1; i<=MONSNO_END; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			// �ݵ��޶݂ɂ��邩�`�F�b�N
			if( PokeZenkokuNo2ShinouNo( i ) != 0 ){
				count ++;
			}
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�S���}�ӂ������������`�F�b�N����
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	������
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_CheckZenkokuComp(const ZUKAN_WORK * zw)
{
	u16 num;

	// �[���R�N�}�ӊ����ɕK�v�ȃ|�P���������C�߂܂�����
	num = ZukanWork_GetZenkokuGetCompCount( zw );

	if( num >= ZUKAN_WORK_ZENKOKU_COMP_NUM ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V���I�E�}�ӂ������������`�F�b�N����
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@retval	TRUE	����
 *	@retval	FALSE	������
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_CheckShinouComp(const ZUKAN_WORK * zw)
{
	u16 num;

	// �V���I�E�}�ӊ����ɕK�v�ȃ|�P���������C��������
	num = ZukanWork_GetShinouSeeCompCount( zw );

	if( num >= ZUKAN_WORK_SHINOU_COMP_NUM ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�[���R�N�}�Ӂ@�����ɕK�v�ȃ|�P������߂܂�����
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@return	�����ɕK�v�ȃ|�P������߂܂�����
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetZenkokuGetCompCount(const ZUKAN_WORK * zw)
{
	int i;
	u16 num;
	// �G���t�B�@�}�i�t�B�@�_�[�N�@�G���E�X�@�A�E�X
	// �ȊO��߂܂��Ă�����OK
	num = 0;
	for( i=1; i<=ZUKAN_WORK_ZENKOKU_MONSMAX; i++ ){
		if( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE ){
			if( check_ZenkokuCompMonsno( i ) == TRUE ){
				num ++;
			}
		}
	}
	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V���I�E�}�Ӂ@�����ɕK�v�ȃ|�P��������������
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@return	�����ɕK�v�ȃ|�P��������������
 */
//-----------------------------------------------------------------------------
u16 ZukanWork_GetShinouSeeCompCount(const ZUKAN_WORK * zw)
{
	int i;
	u16 num;
	u32 monsno;

	// �G���t�B�@�}�i�t�B�@�_�[�N�@�G���E�X�@�A�E�X
	// �ȊO��߂܂��Ă�����OK
	num = 0;
	for( i=1; i<=ZUKAN_WORK_ZENKOKU_MONSMAX; i++ ){
		if( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE ){
			monsno = PokeZenkokuNo2ShinouNo( i );
			if( monsno != 0 ){
				if( check_ShinouCompMonsno( i ) == TRUE ){
					num ++;
				}
			}
		}
	}
	return num;
}

//----------------------------------------------------------
/**
 * @brief	�|�P������߂܂������ǂ����̃t���O�擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @param	monsno	�|�P�����i���o�[
 * @return	BOOL	�t���O����
 */
//----------------------------------------------------------
BOOL ZukanWork_GetPokeGetFlag(const ZUKAN_WORK * zw, u16 monsno)
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return FALSE;
	}
	if (check_get_bit(zw, monsno) && check_see_bit(zw, monsno)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//----------------------------------------------------------
/**
 * @brief	�|�P���������������ǂ����̃t���O�擾
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @param	monsno	�|�P�����i���o�[
 * @return	BOOL	�t���O����
 */
//----------------------------------------------------------
BOOL ZukanWork_GetPokeSeeFlag(const ZUKAN_WORK * zw, u16 monsno)
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return FALSE;
	}
	return check_see_bit(zw, monsno);
}

//----------------------------------------------------------------------------
/**
 *	@brief	����|�P�����̌������擾
 *
 *	@param	zw			�}�Ӄ��[�N�ւ̃|�C���^
 *	@param	random_poke	�擾����|�P����������
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeRandomFlag(const ZUKAN_WORK * zw, u8 random_poke)
{
	u32 random;
	
	zukan_incorrect(zw);

	switch( random_poke ){
	case ZUKAN_WORK_RANDOM_PACHI:		// �p�b�`�[��������
		random = zw->PachiRandom;
		break;
		
	default:
		GF_ASSERT_MSG( 0, "random_poke = %d\n", random_poke );
		break;
	}

	return random;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�|�P������\������Ƃ��̐��ʎ擾
 *
 *	@param	zw				�����񃏁[�N�ւ̃|�C���^
 *	@param	monsno			�|�P�����i���o�[
 *	@param	first_second	�ŏ��Ɍ������ʂ����Ɍ������ʂ�
 *
 *	@retval	PARA_MALE		�I�X
 *	@retval	PARA_FEMALE		���X
 *	@retval	PARA_UNK		�s��	
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�������ʂ��܂�����
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSexFlag(const ZUKAN_WORK * zw, u16 monsno, int first_second )
{
	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	// ���ĂȂ��Ƃ��̓G���[�R�[�h��Ԃ�
	if( !check_see_bit(zw, monsno) ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}

	// �m�[�}���|�P����
	return get_normal_poke_sex( zw, monsno, first_second );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���m�[�����������ݒ�
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@param	count	�A���m�[������	(0�`27)
 *	
 *	@retval	�A���m�[���t�H�[���i���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeAnoonForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	// ���̐��̃A���m�[���t�H���������Ă��邩�`�F�b�N
	if( get_zukan_unknown_turn_num( zw ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}

	// �t�H��������Ԃ�
	return get_unknown_see_form( zw, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�A���m�[����������
 *
 *	@param	zw		�}�Ӄ��[�N
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeAnoonSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_unknown_turn_num( zw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�E�V�t�H�����擾
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@param	count	���������Ԑ�	
 *
 *	@retval	���̏��ԂɌ������t�H����
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiiusiForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// ���̐��̃V�[�E�V�t�H���������Ă��邩�`�F�b�N
	if( get_zukan_siiusi_turn_num( zw, MONSNO_SIIUSI ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_siiusi_see_form( zw, MONSNO_SIIUSI, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�E�V�̃t�H������������
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	�t�H������������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiiusiSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_siiusi_turn_num( zw, MONSNO_SIIUSI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�h���S�t�H�����i���o�[�擾
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@param	count	���������Ԑ�	
 *
 *	@retval	���̏��ԂɌ������t�H�����i���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiidorugoForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	
	// ���̐��̃V�[�h���S�t�H���������Ă��邩�`�F�b�N
	if( get_zukan_siiusi_turn_num( zw, MONSNO_SIIDORUGO ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_siiusi_see_form( zw, MONSNO_SIIDORUGO, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�V�[�h���S�̃t�H������������
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	�t�H������������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeSiidorugoSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_siiusi_turn_num( zw, MONSNO_SIIDORUGO );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���b�`�t�H�����i���o�[�擾
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@param	count	���������Ԑ�	
 *
 *	@retval	���̏��ԂɌ������t�H�����i���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomuttiForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// ���̐��̃~�m���b�`�t�H���������Ă��邩�`�F�b�N
	if( get_zukan_minomutti_turn_num( zw, MONSNO_MINOMUTTI ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_minomutti_see_form( zw, MONSNO_MINOMUTTI, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���b�`�̃t�H������������
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	�t�H������������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomuttiSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_minomutti_turn_num( zw, MONSNO_MINOMUTTI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���X�n�`�t�H�����i���o�[�擾
 *
 *	@param	zw		�}�Ӄ��[�N
 *	@param	count	���������Ԑ�	
 *
 *	@retval	���̏��ԂɌ������t�H�����i���o�[
 *	@retval	ZUKAN_WORK_GET_SEX_ERR	�����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomesuForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);

	// ���̐��̃~�m���X�t�H���������Ă��邩�`�F�b�N
	if( get_zukan_minomutti_turn_num( zw, MONSNO_MINOMESU ) <= count ){
		return ZUKAN_WORK_GET_SEX_ERR;
	}
	return get_minomutti_see_form( zw, MONSNO_MINOMESU, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�~�m���X�̃t�H������������
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	�t�H������������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeMinomesuSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return get_zukan_minomutti_turn_num( zw, MONSNO_MINOMESU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�t�H�����@���擾����
 *
 *	@param	zw	�}�Ӄ��[�N
 *	@param	count�J�E���g
 *
 *	@return	�f�I�L�V�X�t�H�����i���o�[
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeDeokisisuForm(const ZUKAN_WORK * zw, int count)
{
	zukan_incorrect(zw);
	return getDEOKISISUFormNo( zw, count );
}

//----------------------------------------------------------------------------
/**	
 *	@brief	�f�I�L�V�X�t�H�����@���������擾
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	������
 */
//-----------------------------------------------------------------------------
u32 ZukanWork_GetPokeDeokisisuFormSeeNum(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return nowGetDeokisisuFormNum( zw );
}


//----------------------------------------------------------
/**
 * @brief	������f�[�^�Z�b�g�i�������j
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @param	pp		�������|�P������POKEMON_PARAM�ւ̃|�C���^
 */
//----------------------------------------------------------
void ZukanWork_SetPokeSee(ZUKAN_WORK * zw, POKEMON_PARAM * pp)
{
	u16 monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	u32 rand = PokeParaGet(pp, ID_PARA_personal_rnd, NULL);
	u32 sex = PokeSexGet(pp);
	u32 first_sex;	// �ŏ��Ɍ�������

	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return;
	}
	if (!check_see_bit(zw, monsno)) {
		SetZukanRandom(zw, monsno, rand);			// �ő̗���
		set_sex_bit( zw, sex, ZUKAN_WORK_SEX_FIRST, monsno );			// �ŏ��Ɍ�������
	}else{
		// �ŏ��Ɍ������ʂƈႤ�Ƃ��Z�J���h�ɓo�^����
		first_sex = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );
		if( first_sex != sex ){
			set_sex_bit( zw, sex, ZUKAN_WORK_SEX_SECOND, monsno );			// ���Ɍ�������
		}
	}
	SetZukanSpecialTurn(zw, monsno, pp);		// ����|�P�����̌��������Ԑݒ�
	set_see_bit(zw, monsno);
}

//----------------------------------------------------------
/**
 * @brief	������f�[�^�Z�b�g�i�߂܂����j
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @param	pp		�߂܂����|�P������POKEMON_PARAM�ւ̃|�C���^
 */
//----------------------------------------------------------
void ZukanWork_SetPokeGet(ZUKAN_WORK * zw, POKEMON_PARAM * pp)
{
	u16 monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	u32 lang = PokeParaGet(pp, ID_PARA_country_code, NULL);
	u32 rand = PokeParaGet(pp, ID_PARA_personal_rnd, NULL);
	u32 sex = PokeSexGet(pp);
	u32 first_sex;	// �ŏ��Ɍ�������

	zukan_incorrect(zw);
	if (monsno_incorrect(monsno)) {
		return;
	}
	if (!check_see_bit(zw, monsno)) {
		SetZukanRandom(zw, monsno, rand);			// �ő̗���
		set_sex_bit( zw, sex, ZUKAN_WORK_SEX_FIRST, monsno );			// �\������
	}else{
		// �ŏ��Ɍ������ʂƈႤ�Ƃ��Z�J���h�ɓo�^����
		first_sex = check_sex_bit( zw, monsno, ZUKAN_WORK_SEX_FIRST );
		if( first_sex != sex ){
			set_sex_bit( zw, sex, ZUKAN_WORK_SEX_SECOND, monsno );			// �\������
		}
	}
	SetZukanSpecialTurn(zw, monsno, pp);		// ����|�P�����̌��������Ԑݒ�
	SetZukanTextVersionUp(zw, monsno, lang);	// ���R�[�h
	set_get_bit(zw, monsno);
	set_see_bit(zw, monsno);
}

//----------------------------------------------------------
/**
 * @brief	�S�������񃂁[�h���Z�b�g
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void ZukanWork_SetZenkokuZukanFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->zenkoku_flag = TRUE;
}

//----------------------------------------------------------
/**
 * @brief	�S�������񃂁[�h���ǂ����H�̖₢���킹
 * @param	zw		�����񃏁[�N�ւ̃|�C���^
 * @retval	TRUE	�S�������񃂁[�h�I�[�v��
 * @retval	FALSE	�V���I�E�����񃂁[�h
 */
//----------------------------------------------------------
BOOL ZukanWork_GetZenkokuZukanFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->zenkoku_flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����p�@�\�g���t���O�擾
 *
 *	@param	zw		�����񃏁[�N�ւ̃|�C���^
 *
 *	@retval	TRUE	�o�[�W�����A�b�v����
 *	@retval	FALSE	�o�[�W�����A�b�v������
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetGraphicVersionUpFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->GraphicVersionUp;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�O���t�B�b�N�o�[�W�����p�@�\�g���t���O�ݒ�
 *
 *	@param	zw		�}�Ӄ��[�N�ւ̃|�C���^
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetGraphicVersionUpFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->GraphicVersionUp = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�Ӄe�L�X�g�o�[�W�����`�F�b�N
 *
 *	@param	zw
 *	@param	monsno
 *	@param	country_code		���R�[�h
 *
 *	@retval	TRUE	���̍��̃o�[�W������\�����Ă悢
 *	@retval	FALSE	���̍��̃o�[�W������\�����Ă͂����Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetTextVersionUpFlag(const ZUKAN_WORK * zw, u16 monsno, u32 country_code)
{
	int idx;


	GF_ASSERT( country_code < 8 );		// ���R�[�h�ő吔
	
	zukan_incorrect(zw);
	// �e�L�X�g�o�[�W�����̂���|�P�������`�F�b�N
	idx = get_zukan_textversion_idx(monsno);
	if( idx == ZKN_WORLD_TEXT_POKE_NUM ){ return FALSE; }

	// �O����e�L�X�g�p�i���o�[�ɕϊ�
	country_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country_code );

	// ���̌���̃t���O�������Ă��邩�`�F�b�N
	return (zw->TextVersionUp[idx] & (1<<country_code));
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӊO����o�[�W�����@Master�t���O
 *
 *	@param	zw	�}�Ӄ��[�N
 *	���̃t���O�������Ă��Ȃ��ƁA�O����}�ӂ̓I�[�v������Ȃ�
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetTextVersionUpMasterFlag( ZUKAN_WORK * zw )
{
	zw->TextVersionUpMasterFlag = TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӊO����o�[�W�����@Master�t���O�擾
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@retval	TRUE	�o�[�W�����A�b�v�ς�
 *	@retval	FALSE	�o�[�W�����A�b�v����ĂȂ�
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetTextVersionUpMasterFlag(const ZUKAN_WORK * zw)
{
	return zw->TextVersionUpMasterFlag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӕێ��t���O�擾
 *
 *	@param	zw	�}�Ӄ��[�N�ւ̃|�C���^
 *
 *	@retval	TRUE	�ێ�
 *	@retval	FALSE	�ێ����Ă��Ȃ�
 */
//-----------------------------------------------------------------------------
BOOL ZukanWork_GetZukanGetFlag(const ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	return zw->zukan_get;
}

//----------------------------------------------------------------------------
/**
 *	@brief	�}�ӕێ��t���O�ݒ�
 *
 *	@param	zw	�}�Ӄ��[�N
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZukanWork_SetZukanGetFlag(ZUKAN_WORK * zw)
{
	zukan_incorrect(zw);
	zw->zukan_get = TRUE;
}

//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	������ԃf�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	ZUKAN_WORK	�����񃏁[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
ZUKAN_WORK * SaveData_GetZukanWork(SAVEDATA * sv)
{
	ZUKAN_WORK * zs;
	zs = SaveData_Get(sv, GMDATA_ID_ZUKANWORK);
	return zs;
}

//============================================================================================
//============================================================================================
// �A���m�[���@�E�~�E�V�@�~�m���V�@�̌��������Ԃ����Ă�
static void set_debag_special_poke_see_no( ZUKAN_WORK * zw, int monsno )
{
	int i;
	
	// �A���m�[���@�E�~�E�V�@�~�m���V�̏��Ԃ̐ݒ�
	if( monsno == MONSNO_ANNOON ){
		for( i=0; i<POKEZUKAN_UNKNOWN_NUM; i++ ){
			SetZukanUnknownTurn( zw, i );
		}
	}else if( (monsno == MONSNO_MINOMUTTI) || (monsno == MONSNO_MINOMESU) ){
		for( i=ZUKAN_WORK_MINOMUSHI_FORM_NUM - 1; i>=0; i-- ){
			SetZukanMinomuttiTurn( zw, monsno, i );
		}
	}else if( (monsno == MONSNO_SIIUSI) || (monsno == MONSNO_SIIDORUGO) ){
		for( i=ZUKAN_WORK_UMIUSHI_FORM_NUM - 1; i>=0; i-- ){
			SetZukanSiiusiTurn( zw, monsno, i );
		}
	}else if( (monsno == MONSNO_DEOKISISU) ){
		for( i=ZUKAN_WORK_DEOKISISU_FORM_NUM - 1; i>=0; i-- ){
			setDEOKISISUFormNo( zw, i, ZUKAN_WORK_DEOKISISU_FORM_NUM-(i+1) );
		}
	}
	
}

// ���ʐݒ�
static void set_debug_poke_sex( ZUKAN_WORK * zw, int monsno )
{
	int sex = PokePersonalParaGet( monsno, ID_PER_sex );
	
	if( sex == MONS_MALE ){
		// ���ʐݒ�
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}
	if( sex == MONS_FEMALE ){
		// ���ʐݒ�
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}
	if( sex == MONS_UNKNOWN ){
		// ���ʐݒ�
		set_sex_bit( zw, PARA_UNK, ZUKAN_WORK_SEX_FIRST, monsno );
		return;
	}

	// ���ʐݒ�
	if( monsno % 2 ){
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_FIRST, monsno );
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_SECOND, monsno );
	}else{
		set_sex_bit( zw, PARA_FEMALE, ZUKAN_WORK_SEX_FIRST, monsno );
		set_sex_bit( zw, PARA_MALE, ZUKAN_WORK_SEX_SECOND, monsno );
	}
}

//----------------------------------------------------------
/**
 * @brief	�f�o�b�O�p�F������f�[�^����
 * @param	zw			�����񃏁[�N�ւ̃|�C���^
 * @param	option
 */
//----------------------------------------------------------
extern void Debug_ZukanWork_Make(ZUKAN_WORK * zw, int start, int end, BOOL see_flg)
{
	int i;
	zukan_incorrect(zw);

	GF_ASSERT( start > 0 );
	GF_ASSERT( end <= MONSNO_END );
	
	for (i = start; i <= end; i++) {
		if( see_flg == TRUE ){
			set_see_bit(zw, i);
		}else{
		
			set_get_bit(zw, i);
			set_see_bit(zw, i);

			// �O���}�Ӑݒ�
			SetZukanTextVersionUp(zw, i, LANG_JAPAN);
			SetZukanTextVersionUp(zw, i, LANG_ENGLISH);
			SetZukanTextVersionUp(zw, i, LANG_FRANCE);
			SetZukanTextVersionUp(zw, i, LANG_ITALY);
			SetZukanTextVersionUp(zw, i, LANG_GERMANY);
			SetZukanTextVersionUp(zw, i, LANG_SPAIN);
		}

		// �������ݒ�
		SetZukanRandom( zw, i, 0 );

		// ���ꌩ�������Ԑݒ�
		set_debag_special_poke_see_no( zw, i );

		// ����	
		set_debug_poke_sex( zw, i );
	}

	// �O���t�B�b�N�o�[�W�����A�b�v
	ZukanWork_SetGraphicVersionUpFlag(zw);
	ZukanWork_SetTextVersionUpMasterFlag(zw);
}

//----------------------------------------------------------------------------
/**
 *	@brief	�f�I�L�V�X�o�b�N�A�b�v
 *
 *	@param	zw	�}�Ӄ��[�N
 */
//-----------------------------------------------------------------------------
void Debug_ZukanWork_DeokisisuBuckUp( ZUKAN_WORK * zw )
{
	// �f�I�L�V�X�t�H����ID�o�b�t�@������
	InitDeokisisuFormNo( zw );
		
	// �f�I�L�V�X�ێ����Ă��邩�`�F�b�N
	if( ZukanWork_GetPokeSeeFlag( zw, MONSNO_DEOKISISU ) == TRUE ){
		// �t�H�����i���o�[�O�ŃZ�[�u
		setDEOKISISUFormNo( zw, 0, 0 );
	}
}


// �O���Q�ƃC���f�b�N�X����鎞�̂ݗL��(�Q�[�����͖���)
#ifdef CREATE_INDEX
void *Index_Get_Zukan_Offset(ZUKAN_WORK *zw){ return &zw->zukan_get; }
void *Index_Get_Zenkoku_Zukan_Offset(ZUKAN_WORK *zw){ return &zw->zenkoku_flag; }
void *Index_Get_Get_Flag_Offset(ZUKAN_WORK *zw){ return &zw->get_flag; }
void *Index_Get_See_Flag_Offset(ZUKAN_WORK *zw){ return &zw->see_flag; }
void *Index_Get_Sex_Flag_Offset(ZUKAN_WORK *zw){ return &zw->sex_flag; }
#endif




//------------------------------------------------------------------
/**
 * �S�|�P�����́A�߂܂������t�H�����i���o�[��Ԃ�
 *
 * @param   zw			
 * @param   monsno		
 * @param   count		
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 ZukanWork_GetPokeForm( const ZUKAN_WORK* zw, int monsno, int count )
{
	OS_TPrintf("monsno:%d\n", monsno);
	switch( monsno ){
	case MONSNO_ANNOON:
		OS_TPrintf("  Annoon\n");
		if( count < ZukanWork_GetPokeAnoonSeeNum(zw) )
		{
			OS_TPrintf("   CheckForm\n");
			return ZukanWork_GetPokeAnoonForm( zw, count );
		}
		break;

	case MONSNO_SIIUSI:
		if( count < ZukanWork_GetPokeSiiusiSeeNum(zw) )
		{
			return ZukanWork_GetPokeSiiusiForm( zw, count );
		}
		break;

	case MONSNO_SIIDORUGO:
		if( count < ZukanWork_GetPokeSiidorugoSeeNum(zw) )
		{
			return ZukanWork_GetPokeSiidorugoForm( zw, count );
		}
		break;

	case MONSNO_MINOMUTTI:
		if( count < ZukanWork_GetPokeMinomuttiSeeNum(zw) )
		{
			return ZukanWork_GetPokeMinomuttiForm( zw, count );
		}
		break;

	case MONSNO_MINOMESU:
		if( count < ZukanWork_GetPokeMinomesuSeeNum(zw) )
		{
			return ZukanWork_GetPokeMinomesuForm( zw, count );
		}
		break;

	case MONSNO_DEOKISISU:
		if( count < ZukanWork_GetPokeDeokisisuFormSeeNum(zw) )
		{
			return ZukanWork_GetPokeDeokisisuForm( zw, count );
		}
		break;

	}

	return 0;

}
