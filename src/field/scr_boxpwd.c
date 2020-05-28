//=============================================================================================
/**
 * @file	scr_boxpwd.c
 * @brief	ボックスパスワード壁紙関連処理
 * @author	taya
 * @date	2006/06/01
 */
//=============================================================================================
#include "common.h"
#include "system\pms_word.h"
#include "savedata\mystatus.h"
#include "application\pms_input_data.h"

#include "scr_boxpwd.h"

enum {
	EX_WALLPAPER_MAX = 8,
};


static void lotate( u8* ary, u8 targetNum, u8 lotNum )
{
	u8 lsb, i;

	while(lotNum--)
	{
		lsb = (ary[0] >> 7) & 1;
		for(i=0; i<(targetNum-1); i++)
		{
			ary[i] <<= 1;
			ary[i] |= ((ary[i+1] >> 7) & 1);
		}
		ary[i] <<= 1;
		ary[i] |= lsb;
	}
}


static int hitcheck( u16 player_id, PMS_WORD w1, PMS_WORD w2, PMS_WORD w3, PMS_WORD w4 )
{
	int maxValue, v, i;
	s16 pwd[4];
	u8  bit[4];

	maxValue = PMSI_DAT_GetBoxPwdMax();

	pwd[0] = PMSI_DAT_WordToBoxPwdID( w1 );
	pwd[1] = PMSI_DAT_WordToBoxPwdID( w2 );
	pwd[2] = PMSI_DAT_WordToBoxPwdID( w3 );
	pwd[3] = PMSI_DAT_WordToBoxPwdID( w4 );

	OS_TPrintf("pwdMax = %d\n", maxValue);
	OS_TPrintf("word1:%4d -> %3d\n", w1, pwd[0]);
	OS_TPrintf("word1:%4d -> %3d\n", w2, pwd[1]);
	OS_TPrintf("word1:%4d -> %3d\n", w3, pwd[2]);
	OS_TPrintf("word1:%4d -> %3d\n", w4, pwd[3]);

	for(i=0; i<4; i++)
	{
		if( pwd[i] < 0 )
		{
			return BOXPWD_RESULT_ERROR;
		}

		if( i > 0 )
		{
			if( pwd[i] >= pwd[i-1] )
			{
				v = pwd[i] - pwd[i-1];
				if( v > 255 )
				{
					return BOXPWD_RESULT_ERROR;
				}
				bit[i] = v;
			}
			else
			{
				v = maxValue - (pwd[i-1] - pwd[i]);
				if( v > 255)
				{
					return BOXPWD_RESULT_ERROR;
				}
				bit[i] = v;
			}
		}
		else
		{
			if( pwd[0] > 255 )
			{
				return BOXPWD_RESULT_ERROR;
			}
			bit[0] = pwd[0];
		}
	}

	lotate( bit, 4, 7 );

	OS_TPrintf("random = %d\n", bit[3]);

	for(i=0; i<3; i++)
	{
		bit[i] ^= ((bit[3] >> 4) | (bit[3] & 0xf0));
	}

	lotate( bit, 3, (bit[3] & 0x0f) );

	if( bit[0] >= EX_WALLPAPER_MAX )
	{
		return BOXPWD_RESULT_ERROR;
	}

	bit[1] ^= bit[0];
	bit[2] ^= bit[0];

	OS_TPrintf("id = %d\n", ((bit[1]<<8) | (bit[2])));

	if( ((bit[1]<<8) | (bit[2])) == player_id )
	{
		return bit[0];
	}

	return BOXPWD_RESULT_ERROR;
}




//------------------------------------------------------------------
/**
 * ボックス隠し壁紙のパスワードチェック
 *
 * @param   mystatus	プレイヤーステータス（ID参照用）
 * @param   word1		入力された単語１
 * @param   word2		入力された単語２
 * @param   word3		入力された単語３
 * @param   word4		入力された単語４
 *
 * @retval  int			パスワードが正しければ、壁紙ID（0～EX_WALLPAPER_MAX-1)
 *						パスワードが間違いなら、BOXPWD_RESULT_ERROR
 */
//------------------------------------------------------------------
int  BOXPWD_HitCheck( const MYSTATUS* mystatus, PMS_WORD word1, PMS_WORD word2, PMS_WORD word3, PMS_WORD word4 )
{
	int wp_num;
	u8 dup1, dup2, dup3, dup4;
	u8 c1, c2, c3, c4;
	u16  player_id;


	dup1 = 1 + PMSW_GetDupWordCount( word1 );
	dup2 = 1 + PMSW_GetDupWordCount( word2 );
	dup3 = 1 + PMSW_GetDupWordCount( word3 );
	dup4 = 1 + PMSW_GetDupWordCount( word4 );

	player_id = MyStatus_GetID_Low(mystatus);

	for(c1=0; c1<dup1; c1++)
	{
		for(c2=0; c2<dup2; c2++)
		{
			for(c3=0; c3<dup3; c3++)
			{
				for(c4=0; c4<dup4; c4++)
				{
					wp_num = hitcheck( 
						player_id,
						PMSW_GetDupWord( word1, c1 ),
						PMSW_GetDupWord( word2, c2 ),
						PMSW_GetDupWord( word3, c3 ),
						PMSW_GetDupWord( word4, c4 )
					);

					if( wp_num != BOXPWD_RESULT_ERROR )
					{
						return wp_num;
					}
				}
			}
		}
	}

	return BOXPWD_RESULT_ERROR;
}
//c01r0203

