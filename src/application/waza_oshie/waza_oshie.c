//============================================================================================
/**
 * @file	waza_oshie.c
 * @brief	�Z����/�v���o������
 * @author	Hiroyuki Nakamura
 * @date	06.05.09
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "savedata/mystatus.h"
#include "savedata/config.h"
#include "poketool/poke_tool.h"

#define WAZA_OSHIE_H_GLOBAL
#include "application/waza_oshie.h"


#define LV_WAZA_OBOE_MAX	( LEVELUPWAZA_OBOE_MAX/2 )	// ���x���A�b�v�Ŋo����Z�� + �I�[�R�[�h
#define LV_WAZA_OBOE_END	( LEVELUPWAZA_OBOE_END )	// �I�[�R�[�h
#define LV_WAZA_LV_MASK		( LEVELUPWAZA_LEVEL_MASK )	// �o���郌�x������
#define LV_WAZA_WAZA_MASK   ( LEVELUPWAZA_WAZA_MASK )	// �o����Z����
#define LV_WAZA_LV_SHIFT	( LEVELUPWAZA_LEVEL_SHIFT )	// ���x���擾�V�t�g


//--------------------------------------------------------------------------------------------
/**
 * �Z�����f�[�^�̈�擾
 *
 * @param	heap	�q�[�vID
 *
 * @return	�Z�����f�[�^�̈�
 */
//--------------------------------------------------------------------------------------------
WAZAOSHIE_DATA * WazaOshie_DataAlloc( u32 heap )
{
	WAZAOSHIE_DATA * dat = sys_AllocMemory( heap, sizeof(WAZAOSHIE_DATA) );
	memset( dat, 0, sizeof(WAZAOSHIE_DATA) );
	return dat;
}

//--------------------------------------------------------------------------------------------
/**
 * �Z�����f�[�^�̈���
 *
 * @param	heap	�q�[�vID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void WazaOshie_DataFree( WAZAOSHIE_DATA * dat )
{
	sys_FreeMemoryEz( dat );
}

//--------------------------------------------------------------------------------------------
/**
 * �v���o���\�ȋZ���擾
 *
 * @param	pp		�|�P�����f�[�^
 * @param	heap	�q�[�vID
 *
 * @return	�擾�����Z�f�[�^
 *
 *	����͊e����
 */
//--------------------------------------------------------------------------------------------
u16 * RemaindWazaGet( POKEMON_PARAM * pp, u32 heap )
{
	u16 * get;
	u16 * ret;
	u16	waza[4];
	u16	mons;
	u8	lv;
	u8	form;
	u8	h, i, j;

	mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );
	form = (u8)PokeParaGet( pp, ID_PARA_form_no, NULL );
	lv   = (u8)PokeParaGet( pp, ID_PARA_level, NULL );
	for( i=0; i<4; i++ ){
		waza[i] = (u16)PokeParaGet( pp, ID_PARA_waza1+i, NULL );
	}

	get = sys_AllocMemory( heap, LV_WAZA_OBOE_MAX * 2 );
	ret = sys_AllocMemory( heap, LV_WAZA_OBOE_MAX * 2 );

//	PokeWazaOboeDataGet( mons, get );
	PokeFormNoWazaOboeDataGet( mons, form, get );

	j = 0;
	for( i=0; i<LV_WAZA_OBOE_MAX; i++ ){
		// �I�[�R�[�h�`�F�b�N
		if( get[i] == LV_WAZA_OBOE_END ){
			ret[j] = WAZAOSHIE_TBL_MAX;
			break;
		// ���݂̃��x���Ŋo������Z��
		}else if( ((get[i]&LV_WAZA_LV_MASK)>>LV_WAZA_LV_SHIFT) > lv ){
//			ret[j] = WAZAOSHIE_TBL_MAX;
//			break;
			continue;
		}else{
			get[i] &= LV_WAZA_WAZA_MASK;
			// ���łɊo���Ă��邩
			for( h=0; h<4; h++ ){
				if( get[i] == waza[h] ){ break; }
			}
			if( h == 4 ){
				// �e�[�u���ɓ����Z���Ȃ���
				for( h=0; h<j; h++ ){
					if( ret[h] == get[i] ){ break; }
				}
				if( h == j ){
					ret[j] = get[i];
					j++;
				}
			}
		}
	}

	sys_FreeMemoryEz( get );

	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * ��������/�v���o����Z�����邩�`�F�b�N
 *
 * @param	tbl		�Z�e�[�u��
 *
 * @retval	"TRUE = ����"
 * @retval	"FALSE = �Ȃ�"
 */
//--------------------------------------------------------------------------------------------
BOOL WazaOshie_WazaTableChack( u16 * tbl )
{
	if( tbl[0] == WAZAOSHIE_TBL_MAX ){
		return FALSE;
	}
	return TRUE;
}
