//==============================================================================
/**
 * @file	con_tool.c
 * @brief	�R���e�X�g�S�̂Ŏg�p����ėp�I�ȃc�[��
 * @author	matsuda
 * @date	2005.11.22(��)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "con_tool.h"
#include "actin.h"

#include "field/fieldobj_code.h"

#include "battle\chr_def.h"
#include "system/gra_tool.h"
#include "poketool/monsno.h"

#include "msgdata/msg_cmsg_acting.h"
#include "msgdata/msg_cmsg_judge.h"
#include "msgdata/msg_cmsg_breeder.h"
#include "msgdata/msg_cmsg_wazaexplain.h"
#include "msgdata/msg_cmsg_wazakouka.h"
#include "msgdata/msg.naix"

#include "battle/trtype_def.h"

#include "system/arc_util.h"
#include "src/contest/data/contest_data.naix"

#include "system/pmfprint.h"


//==============================================================================
//	�萔��`
//==============================================================================
///BP�̃n�[�g�|�C���g�擾�ׂ̈�if����r�f�[�^��
#define HEART_NUM_BP_IF_MAX		(8)
///�N���b�v�̃n�[�g�|�C���g�擾�ׂ̈�if����r�f�[�^��
#define HEART_NUM_CLIP_IF_MAX		(3)


//==============================================================================
//	�f�[�^
//==============================================================================
#include "ap_waza.dat"

///�Z���ʃf�[�^�̐�
#define APPEAL_WAZA_DATA_MAX	(NELEMS(AppealWazaData))


//--------------------------------------------------------------
/**
 * @brief   �������T�[�o�[���`�F�b�N����
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�������T�[�o�[
 */
//--------------------------------------------------------------
int ConTool_ServerMineCheck(CONTEST_SYSTEM *consys)
{
	if(consys->sio_flag == FALSE 
			|| (consys->sio_flag == TRUE 
			&& consys->c_game.server_no == consys->c_game.my_breeder_no)){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM�t���O�������Ă��邩�擾
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  TRUE:�ʐM�t���O�������Ă���B
 * @retval  FALSE:�ʐM�t���O�������Ă��Ȃ��B
 */
//--------------------------------------------------------------
int ConTool_ContestSioFlagCheck(CONTEST_SYSTEM *consys)
{
	return consys->sio_flag;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�ɎQ������CPU�u���[�_�[�̃f�[�^���Z�b�g
 *
 * @param   heap_id		�e���|�����Ŏg�p����q�[�v��ID
 * @param   entry_num	�Q��������CPU�̐�
 * @param   type		�Q������R���e�X�g�̎��
 * @param   rank		�R���e�X�g�̃����N
 * @param   mode		�R���e�X�g���[�h(CONMODE_???)
 * @param   hof_flag	�a������t���O(TRUE:�a�����肵�Ă���)
 * @param   zenkoku_zukan_flag	�S���}�ӓ���t���O(TRUE:���肵�Ă���)
 */
//--------------------------------------------------------------
void ConTool_CpuBreederEntry(CONTEST_SYSTEM *consys, int heap_id, int entry_num, int type, int rank, int mode, int hof_flag, int zenkoku_zukan_flag)
{
	int i, t;
	u8 *putbrd;
	u8 count = 0;
	u16 no;
	int hof = FALSE;
	int cpu_data_num;
	int tutorial, practice;
	BREEDER_DATA *brd_tbl;
	int special_count, set_no;
	BREEDER_DATA special_brd;
	
	practice = FALSE;
	tutorial = FALSE;
	switch(mode){
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_ACTIN_PRACTICE:
		practice = TRUE;
		break;
	case CONMODE_VISUAL_TUTORIAL:
	case CONMODE_DANCE_TUTORIAL:
	case CONMODE_ACTIN_TUTORIAL:
		tutorial = TRUE;
		break;
	}
	
	brd_tbl = ArcUtil_Load(ARC_CONTEST_DATA, NARC_contest_data_breeder_bin, 
		FALSE, heap_id, ALLOC_BOTTOM);
	cpu_data_num = ArchiveDataSizeGet(ARC_CONTEST_DATA, NARC_contest_data_breeder_bin) 
		/ sizeof(BREEDER_DATA);
	putbrd = sys_AllocMemoryLo(heap_id, cpu_data_num + 1);
	
	if(hof_flag == TRUE && zenkoku_zukan_flag == TRUE){
		hof = TRUE;
	}
	OS_TPrintf("hof_flag = %d, zenkoku_zukan_flag = %d, hof = %d\n", hof_flag, zenkoku_zukan_flag, hof);
	
	for(i = 0; i < cpu_data_num; i++){
		
		if(rank != brd_tbl[i].rank)
			continue;
		//�o��o����^�C�~���O���`�F�b�N
		if(hof == TRUE){
			if(brd_tbl[i].appear == PALACE_BEFORE){
				continue;
			}
		}
		else{
			if(brd_tbl[i].appear == PALACE_AFTER || brd_tbl[i].appear == HOF_SPECIAL){
				continue;
			}
		}
		
		//���K�E�`���[�g���A���t���O�œo��o����^�C�~���O���`�F�b�N
		if(practice == TRUE){
			//���K
			if(brd_tbl[i].part_practice == 0){
				continue;
			}
		}
		else if(tutorial == TRUE){
			//�`���[�g���A��
			if(brd_tbl[i].part_tutorial == 0){
				continue;
			}
		}
		else{
			//�ʏ�
			if(brd_tbl[i].part_practice == 1 || brd_tbl[i].part_tutorial == 1){
				continue;	//���K���`���[�g���A���ɎQ���o����̂̓X���[
			}
		}
		
		if((type == CONTYPE_STYLE && brd_tbl[i].part_style)
				|| (type == CONTYPE_BEAUTIFUL && brd_tbl[i].part_beautiful)
				|| (type == CONTYPE_CUTE && brd_tbl[i].part_cute)
				|| (type == CONTYPE_CLEVER && brd_tbl[i].part_clever)
				|| (type == CONTYPE_STRONG && brd_tbl[i].part_strong)){
			OS_TPrintf("%d�ԃu���[�_�[OK\n", i);
			putbrd[count++] = i;
		}
	}
	putbrd[count] = 0xff;	//�ԕ�
	
	if(tutorial == FALSE){
		GF_ASSERT(count >= entry_num);
		
		//putbrd�̒���1�l�ł�HOF_SPECIAL�����邩�`�F�b�N
		special_count = 0;
		for(i = 0; i < count; i++){
			if(brd_tbl[putbrd[i]].appear == HOF_SPECIAL){
				special_count++;
			}
		}
		if(special_count > 0){
			set_no = contest_rand(consys) % special_count;
			for(i = 0; i < count; i++){
				if(brd_tbl[putbrd[i]].appear == HOF_SPECIAL){
					if(set_no == 0){
						special_brd = brd_tbl[putbrd[i]];
						break;
					}
					else{
						set_no--;
					}
				}
			}
		}
		
		//�ʏ�u���[�_�[�Z�b�g
		for(i = BREEDER_MAX - entry_num; i < BREEDER_MAX; i++){
			no = contest_rand(consys) % count;
			if(brd_tbl[putbrd[no]].appear == HOF_SPECIAL){
				i--;
				continue;
			}
			consys->c_game.bd[i] = brd_tbl[putbrd[no]];
			for(t = no; putbrd[t] != 0xff; t++)
				putbrd[t] = putbrd[t+1];
			count--;
		}
		
		//�X�y�V�����u���[�_�[������ꍇ�̓����_���ň�ӏ��㏑��
		OS_TPrintf("�X�y�V�����u���[�_�[�l����%d\n", special_count);
		if(special_count > 0){
			no = BREEDER_MAX - entry_num;
			no += contest_rand(consys) % entry_num;
			consys->c_game.bd[no] = special_brd;
			OS_TPrintf("�X�y�V�����u���[�_�[%d�ԂɃZ�b�g\n", no);
		}
	}
	else{	//�`���[�g���A���̏ꍇ�̓����_���Ȃ�(�擪���珇�Ɏ����A�GA�A�GB�A�GC�ƂȂ�)
		GF_ASSERT(count >= BREEDER_MAX);
		for(i = 0; i < BREEDER_MAX; i++){
			consys->c_game.bd[i] = brd_tbl[putbrd[i]];
		}
	}
	
	sys_FreeMemoryEz(putbrd);
	sys_FreeMemoryEz(brd_tbl);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�ɎQ������CPU�u���[�_�[�̃C���[�W�N���b�v�f�[�^���Z�b�g
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   heap_id		�e���|�����Ŏg�p����q�[�v��ID
 *
 * ConTool_CpuBreederEntry��CPU�̃u���[�_�[�f�[�^���擾���Ă��炱�̊֐����g�p���Ă�������
 */
//--------------------------------------------------------------
void ConTool_CpuBreederImcSet(CONTEST_SYSTEM *consys, int heap_id)
{
	int breeder, no;
	CON_IMC_DATA *cid_tbl;
	CON_IMC_DATA *clip;
	int start_breeder;
	int data_no;
	
	cid_tbl = ArcUtil_Load(ARC_CONTEST_DATA, NARC_contest_data_con_clip_bin, 
		FALSE, heap_id, ALLOC_BOTTOM);
	
	switch(consys->c_game.mode){
	case CONMODE_VISUAL_TUTORIAL:
	case CONMODE_DANCE_TUTORIAL:
	case CONMODE_ACTIN_TUTORIAL:
		start_breeder = 0;
		break;
	default:
		start_breeder = consys->c_game.player_num;
		break;
	}
	
	for(breeder = start_breeder; breeder < BREEDER_MAX; breeder++){
		switch(consys->c_game.theme){
		case CON_IMAGE_THEME_FLOWERY:
			data_no = consys->c_game.bd[breeder].clip_no_flowery;
			break;
		case CON_IMAGE_THEME_SIMPLE:
			data_no = consys->c_game.bd[breeder].clip_no_simple;
			break;
		case CON_IMAGE_THEME_ARTIFICIAL:
			data_no = consys->c_game.bd[breeder].clip_no_artificial;
			break;
		case CON_IMAGE_THEME_NATURAL:
			data_no = consys->c_game.bd[breeder].clip_no_natural;
			break;
		case CON_IMAGE_THEME_COLORFUL:
			data_no = consys->c_game.bd[breeder].clip_no_colorful;
			break;
		case CON_IMAGE_THEME_LIVELY:
			data_no = consys->c_game.bd[breeder].clip_no_lively;
			break;
		case CON_IMAGE_THEME_REFRESH:
			data_no = consys->c_game.bd[breeder].clip_no_refresh;
			break;
		case CON_IMAGE_THEME_LIMIT:
			data_no = consys->c_game.bd[breeder].clip_no_limit;
			break;
		case CON_IMAGE_THEME_SOFTLY:
			data_no = consys->c_game.bd[breeder].clip_no_softly;
			break;
		case CON_IMAGE_THEME_GORGEOUS:
			data_no = consys->c_game.bd[breeder].clip_no_gorgeous;
			break;
		case CON_IMAGE_THEME_ELEGANT:
			data_no = consys->c_game.bd[breeder].clip_no_elegant;
			break;
		case CON_IMAGE_THEME_SHOWY:
			data_no = consys->c_game.bd[breeder].clip_no_showy;
			break;
		default:
			GF_ASSERT(0 && "���݂��Ȃ��e�[�}");
			data_no = 0;
			break;
		}
		clip = &cid_tbl[data_no];
		
		ImcSaveData_ClaenContestData(consys->c_game.imc_data[breeder]);
		
		ImcSaveData_SetContestPokeData_Easy(consys->c_game.imc_data[breeder], 
			consys->c_game.pp[breeder], clip->mons_pri);
		
		OS_TPrintf("clip_acce = %d\n", clip->acce_data_num);
		for(no = 0; no < clip->acce_data_num; no++){
			ImcSaveData_SetContestAcceData_Easy(consys->c_game.imc_data[breeder], no, 
				clip->acce[no].no, clip->acce[no].x, clip->acce[no].y, clip->acce[no].pri);
		}
		
		ImcSaveData_SetContestBgId(consys->c_game.imc_data[breeder], clip->bg);
		ImcSaveData_SetContestRank(consys->c_game.imc_data[breeder], consys->c_game.rank);
	}
	
	sys_FreeMemoryEz(cid_tbl);
}

//--------------------------------------------------------------
/**
 * @brief   ���K�_���X�p�̃C���[�W�N���b�v�f�[�^�Z�b�g
 *
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ConTool_PracticeDanceImcSet(CONTEST_SYSTEM *consys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		ImcSaveData_ClaenContestData(consys->c_game.imc_data[i]);
		
		ImcSaveData_SetContestPokeData_Easy(consys->c_game.imc_data[i], 
			consys->c_game.pp[i], -1);
		
//		for(no = 0; no < clip->acce_data_num; no++){
//			ImcSaveData_SetContestAcceData_Easy(consys->c_game.imc_data[breeder], no, 
//				clip->acce[no].no, clip->acce[no].x, clip->acce[no].y, clip->acce[no].pri);
//		}
		
		ImcSaveData_SetContestBgId(consys->c_game.imc_data[i], 0);
		ImcSaveData_SetContestRank(consys->c_game.imc_data[i], consys->c_game.rank);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�f�[�^������POKEMON_PARAM���쐬����
 *
 * @param   bd		�u���[�_�[�f�[�^
 * @param   pp		�|�P�p�������
 * @param   heap_id	�q�[�vID
 * 
 * @retval  pp		�쐬����POKEMON_PARAM�ւ̃|�C���^
 */
//--------------------------------------------------------------
void ConTool_BreederPokeParaCreate(const BREEDER_DATA *bd, POKEMON_PARAM *pp, int heap_id)
{
	int i;
	u16 waza_no;
	u32 sex_rnd;
	
	//PokeParaSetSexChr(pp, bd->monsno, 10, POW_RND, bd->sex, CHR_GANBARIYA, 0);
	sex_rnd = PokeParaSexChrRndGet(bd->monsno, bd->sex, CHR_GANBARIYA);
	PokeParaSet(pp, bd->monsno, 10, POW_RND, RND_SET, sex_rnd, ID_NO_RARE, 0x0f0f0f0f);
	//�莝���Z�Z�b�g
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		waza_no = bd->waza[i];
		PokeParaPut(pp, ID_PARA_waza1 + i, &waza_no);
	}

	//�j�b�N�l�[���Ɛe��
	{
		STRBUF *nickname_src, *oyaname_src;
		MSGDATA_MANAGER *man;
		
		man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, 
			NARC_msg_cmsg_breeder_dat, heap_id);
		nickname_src = MSGMAN_AllocString(man, bd->nickname_id);
		oyaname_src = MSGMAN_AllocString(man, bd->name_id);
		
		PokeParaPut(pp, ID_PARA_nickname_buf, nickname_src);
		PokeParaPut(pp, ID_PARA_oyaname_buf, oyaname_src);
		
		STRBUF_Delete(nickname_src);
		STRBUF_Delete(oyaname_src);
		MSGMAN_Delete(man);
	}
	
	//�e�R���f�B�V����(�������悳�A������)�Ƃ��Â�
	{
		u8 style, beautiful, cute, clever, strong, fur;
		
		style = bd->style;
		beautiful = bd->beautiful;
		cute = bd->cute;
		clever = bd->clever;
		strong = bd->strong;
		fur = bd->fur;
		PokeParaPut(pp, ID_PARA_style, &style);
		PokeParaPut(pp, ID_PARA_beautiful, &beautiful);
		PokeParaPut(pp, ID_PARA_cute, &cute);
		PokeParaPut(pp, ID_PARA_clever, &clever);
		PokeParaPut(pp, ID_PARA_strong, &strong);
		PokeParaPut(pp, ID_PARA_fur, &fur);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�p�̃|�P�����\�t�g�E�F�A�X�v���C�g�����֐�
 *
 * @param   ssm_p		�\�t�g�E�F�A�X�v���C�g�}�l�[�W���ւ̃|�C���^
 * @param   poly_id		�|���S��ID
 * @param   pp			POKEMON_PARAM�ւ̃|�C���^
 * @param   dir			�|�P�����̌���(PARA_FRONT or PARA_BACK)
 * @param   ep			OAM�ւ̓W�J�p�o�b�t�@�ւ̃|�C���^(�g�p���Ȃ��ꍇ��NULL)
 * @param   heap_id		�q�[�vID(�ꎞ�g�p)
 * @param   x			�\�����WX
 * @param   y			�\�����WY
 * @param   z			�\�����WZ
 *
 * @retval  �\�t�g�E�F�A�X�v���C�g�̃|�C���^
 *
 * �S����Ŏg����悤�ɔėp�I�ɗp�ӂ��Ă������ł��B
 * ep�͋Z�G�t�F�N�g���o���Ȃ��̂ł����NULL�w��ő��v�ł��B
 */
//--------------------------------------------------------------
SOFT_SPRITE * ConTool_BreederPokemonAdd(SOFT_SPRITE_MANAGER *ssm_p, int poly_id, 
	POKEMON_PARAM *pp, int dir, EXCHR_PARAM *ep, int heap_id, int x, int y, int z)
{
	SOFT_SPRITE_ARC ssa;
	SOFT_SPRITE	*ss;
	int height, sex, monsno;
	
	PokeGraArcDataGetPP(&ssa, pp, dir);
//	sex = PokeSexGet(pp);
//	monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
//	height = PokeHeightGet(monsno, sex, dir);
	height = PokeParaHeightGet(pp,dir);

	if(ep != NULL){
		GF_ASSERT(ep->exchr_buffer != NULL);
		ChangesInto_BattlePokeData(ssa.arc_no, ssa.index_chr, heap_id, ep->exchr_buffer);
		ep->pal_index = ssa.index_pal;
		ep->arcID = ssa.arc_no;
	}
	ss = SoftSpriteAdd(ssm_p, &ssa, x, y + height, z, poly_id, NULL, NULL);
	return ss;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g��R������R���̃f�[�^���Z�b�g
 *
 * @param   heap_id		�e���|�����Ŏg�p����q�[�v��ID
 * @param   sp_no		�����R������No
 * @param   type		�R���e�X�g�̎��
 * @param   rank		�R���e�X�g�̃����N
 */
//--------------------------------------------------------------
void ConTool_JudgeEntry(CONTEST_SYSTEM *consys, int heap_id, int sp_no, int type, int rank)
{
	int i, t;
	u8 count = 0, sp_count = 0;
	u16 no;
	int judge_data_num;
	JUDGE_DATA *judge_tbl;
	u8 *putjudge, *sp_putjudge;
	
	judge_tbl = ArcUtil_Load(ARC_CONTEST_DATA, NARC_contest_data_judge_bin, 
		FALSE, heap_id, ALLOC_BOTTOM);
	judge_data_num = ArchiveDataSizeGet(ARC_CONTEST_DATA, NARC_contest_data_judge_bin) 
		/ sizeof(JUDGE_DATA);
	putjudge = sys_AllocMemoryLo(heap_id, judge_data_num + 1);
	sp_putjudge = sys_AllocMemoryLo(heap_id, judge_data_num + 1);

	for(i = 0; i < judge_data_num; i++){
		if(rank != judge_tbl[i].rank)
			continue;
		
		if(type == CONTYPE_STYLE && judge_tbl[i].condition_style){
			if(judge_tbl[i].condition_style > 1){
				sp_putjudge[sp_count++] = i;
			}
			else{
				putjudge[count++] = i;
			}
		}
		else if(type == CONTYPE_BEAUTIFUL && judge_tbl[i].condition_beautiful){
			if(judge_tbl[i].condition_beautiful > 1){
				sp_putjudge[sp_count++] = i;
			}
			else{
				putjudge[count++] = i;
			}
		}
		else if(type == CONTYPE_CUTE && judge_tbl[i].condition_cute){
			if(judge_tbl[i].condition_cute > 1){
				sp_putjudge[sp_count++] = i;
			}
			else{
				putjudge[count++] = i;
			}
		}
		else if(type == CONTYPE_CLEVER && judge_tbl[i].condition_clever){
			if(judge_tbl[i].condition_clever > 1){
				sp_putjudge[sp_count++] = i;
			}
			else{
				putjudge[count++] = i;
			}
		}
		else if(type == CONTYPE_STRONG && judge_tbl[i].condition_strong){
			if(judge_tbl[i].condition_strong > 1){
				sp_putjudge[sp_count++] = i;
			}
			else{
				putjudge[count++] = i;
			}
		}
	}
	putjudge[count] = 0xff;	//�ԕ�
	sp_putjudge[sp_count] = 0xff;	//�ԕ�
	
	//�m�[�}���R��
	GF_ASSERT(count >= NORMAL_JUDGE_MAX);
	for(i = 0; i < NORMAL_JUDGE_MAX; i++){
	#if 0	//�����_���ł͂Ȃ��A�����珇�ԌŒ�ŏo���悤�ɕύX 2006.06.07(��)
		no = contest_rand(consys) % count;
		consys->c_game.jd[i] = judge_tbl[putjudge[no]];
		for(t = no; putjudge[t] != 0xff; t++)
			putjudge[t] = putjudge[t+1];
		count--;
	#else
		consys->c_game.jd[i] = judge_tbl[putjudge[i]];
	#endif
	}
	
	//�����R��
	GF_ASSERT(sp_count >= GUEST_JUDGE_MAX);
	no = contest_rand(consys) % sp_count;
	consys->c_game.jd[NORMAL_JUDGE_MAX] = judge_tbl[sp_putjudge[no]];
	
	//�����R���̈ʒu�����肵�A�R���f�[�^����ёւ���
	{
		JUDGE_DATA swap_jd;
		
		consys->c_game.special_judge_no = sp_no;
		swap_jd = consys->c_game.jd[sp_no];
		consys->c_game.jd[sp_no] = consys->c_game.jd[NORMAL_JUDGE_MAX];
		consys->c_game.jd[NORMAL_JUDGE_MAX] = swap_jd;
		OS_TPrintf("sp_no = %d\n", sp_no);
	}
	
	sys_FreeMemoryEz(sp_putjudge);
	sys_FreeMemoryEz(putjudge);
	sys_FreeMemoryEz(judge_tbl);
}

//--------------------------------------------------------------
/**
 * @brief   AP�l���擾����
 * @param   appeal_no		�A�s�[���Z�ԍ�
 * @retval  AP�l(�W�Q�l�̏ꍇ�̓}�C�i�X)
 */
//--------------------------------------------------------------
s8 ConTool_GetAPWaza_App(int appeal_no)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	return AppealWazaData[appeal_no].ap_point;
}

//--------------------------------------------------------------
/**
 * @brief   �Z�������b�Z�[�W��ID���擾����
 *
 * @param   appeal_no		�A�s�[���Z�ԍ�
 * @param   u_id			�������b�Z�[�W��i�̃��b�Z�[�WID�����
 * @param   d_id			�������b�Z�[�W���i�̃��b�Z�[�WID�����
 */
//--------------------------------------------------------------
void ConTool_GetAPSetumeiMsgID(int appeal_no, u32 *u_id, u32 *d_id)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	*u_id = AppealWazaData[appeal_no].setumei_u_id;
	*d_id = AppealWazaData[appeal_no].setumei_d_id;
}

//--------------------------------------------------------------
/**
 * @brief   �|�P�������X�g�p�̋Z�������b�Z�[�W��ID���擾����
 *
 * @param   appeal_no		�A�s�[���Z�ԍ�
 *
 * @retval  �������b�Z�[�W��ID
 */
//--------------------------------------------------------------
u32 ConTool_GetListAPSetumeiMsgID(int appeal_no)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	return CMSG_EXPLAIN_LIST_1 + (appeal_no - 1);
}

//--------------------------------------------------------------
/**
 * @brief   �Z���ʃ��b�Z�[�W��ID�ƃ^�O�R�[�h���擾����
 *
 * @param   appeal_no		�A�s�[���Z�ԍ�
 * @param   msg_type		�擾���郁�b�Z�[�W�^�C�v(KOUKA_MSGID_???)
 * @param   msg_id			���b�Z�[�WID�����
 * @param   msg_tag			���b�Z�[�W�^�O�����
 */
//--------------------------------------------------------------
void ConTool_GetKoukaMsgID(int appeal_no, int msg_type, u32 *msg_id, u32 *msg_tag)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	switch(msg_type){
	case KOUKA_MSGID_A:
	default:
		*msg_id = AppealWazaData[appeal_no].kouka_msgid_a;
		*msg_tag = AppealWazaData[appeal_no].kouka_msgtag_a;
		break;
	case KOUKA_MSGID_B:
		*msg_id = AppealWazaData[appeal_no].kouka_msgid_b;
		*msg_tag = AppealWazaData[appeal_no].kouka_msgtag_b;
		break;
	case KOUKA_MSGID_C:
		*msg_id = AppealWazaData[appeal_no].kouka_msgid_c;
		*msg_tag = AppealWazaData[appeal_no].kouka_msgtag_c;
		break;
	case KOUKA_MSGID_D:
		*msg_id = AppealWazaData[appeal_no].kouka_msgid_d;
		*msg_tag = AppealWazaData[appeal_no].kouka_msgtag_d;
		break;
	case KOUKA_MSGID_SP:
		*msg_id = AppealWazaData[appeal_no].sp_msgid;
		*msg_tag = AppealWazaData[appeal_no].sp_msgtag;
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�����N����A���̃����N�̃��b�Z�[�WID���擾����
 * @param   con_rank		�R���e�X�g�����N(CONRANK_???)
 * @param   mode			�R���e�X�g���[�h(CONMODE_???)
 * @param   sio_flag		TRUE:�ʐM�ΐ�
 * @retval  ���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 ConTool_GetRankMsgID(int con_rank, int mode, int sio_flag)
{
	u32 str_id;
	
	if(sio_flag == TRUE){
		return CAMSG_CONRANK_link;
	}
	
	switch(mode){
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_ACTIN_PRACTICE:
		return CAMSG_CONRANK_practice;
	}
	
	switch(con_rank){
	case CONRANK_NORMAL:
		str_id = CAMSG_CONRANK_NORMAL;
		break;
	case CONRANK_SUPER:
		str_id = CAMSG_CONRANK_SUPER;
		break;
	case CONRANK_HYPER:
		str_id = CAMSG_CONRANK_HYPER;
		break;
	case CONRANK_MASTER:
	default:
		str_id = CAMSG_CONRANK_MASTER;
		break;
	}
	return str_id;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�����N����A���̃����N�̃��b�Z�[�WID���擾����(���C���[�W�N���b�v��ʗp�I)
 * @param   con_rank		�R���e�X�g�����N(CONRANK_???)
 * @retval  ���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 ConTool_IMCGetRankMsgID(int con_rank)
{
	u32 str_id;
	
	switch(con_rank){
	case CONRANK_NORMAL:
		str_id = CAMSG_CONRANK_NORMAL;
		break;
	case CONRANK_SUPER:
		str_id = CAMSG_CONRANK_SUPER;
		break;
	case CONRANK_HYPER:
		str_id = CAMSG_CONRANK_HYPER;
		break;
	case CONRANK_MASTER:
		str_id = CAMSG_CONRANK_MASTER;
		break;
	case CONRANK_IMC_SIO:
	default:
		str_id = CAMSG_CONRANK_link;
		break;
	}
	return str_id;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v����A���̃^�C�v�̃��b�Z�[�WID���擾����(���C���[�W�N���b�v��ʗp�I)
 * @param   con_type			CONTYPE_???
 * @retval  ���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 ConTool_IMCGetTypeMsgID(int con_type)
{
	return ConTool_GetTypeMsgID(con_type, CONMODE_GRAND);
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�^�C�v����A���̃^�C�v�̃��b�Z�[�WID���擾����
 * @param   con_rank		�R���e�X�g�^�C�v(CONTYPE_???)
 * @param   con_mode		�R���e�X�g���[�h(CONMODE_???)
 * @retval  ���b�Z�[�WID
 */
//--------------------------------------------------------------
u32 ConTool_GetTypeMsgID(int con_type, int con_mode)
{
	u32 str_id;
	
	if(con_mode == CONMODE_DANCE_PRACTICE){
		return CAMSG_CONRANK_contest;
	}
	
	switch(con_type){
	case CONTYPE_STYLE:
		str_id = CAMSG_CONTYPE_STYLE;
		break;
	case CONTYPE_BEAUTIFUL:
		str_id = CAMSG_CONTYPE_BEAUTIFUL;
		break;
	case CONTYPE_CUTE:
		str_id = CAMSG_CONTYPE_CUTE;
		break;
	case CONTYPE_CLEVER:
		str_id = CAMSG_CONTYPE_CLEVER;
		break;
	case CONTYPE_STRONG:
	default:
		str_id = CAMSG_CONTYPE_STRONG;
		break;
	}
	return str_id;
}

//--------------------------------------------------------------
/**
 * @brief   �u���[�_�[�ԍ�����G���g���[�ԍ����擾����
 * @param   breeder_no		�u���[�_�[�ԍ�
 * @retval  �G���g���[�ԍ�
 *
 * �u���[�_�[�ԍ��ƃG���g���[�ԍ��͈Ⴂ�܂��B
 * �u���[�_�[�ԍ��͒ʐMID�Ɠ����ɂ��Ă��������s���������̂Ńv���C���[����0�n�܂�ł��B
 * �������Q�[���̃C�x���g�i�s��ł́A�v���C���[�̃G���g���[�͈�ԍŌ�Ȃ̂ŁA3�n�܂�ł��B
 * 
 * (�u���[�_�[�ԍ� == �ʐMID) != �G���g���[�ԍ�
 */
//--------------------------------------------------------------
int ConTool_EntryNoGet(int breeder_no)
{
	return BREEDER_MAX - breeder_no - 1;
}

//--------------------------------------------------------------
/**
 * @brief   �G���g���[�ԍ�����u���[�_�[�ԍ����擾����
 * @param   breeder_no		�G���g���[�ԍ�
 * @retval  �u���[�_�[�ԍ�
 *
 * �u���[�_�[�ԍ��ƃG���g���[�ԍ��͈Ⴂ�܂��B
 * �u���[�_�[�ԍ��͒ʐMID�Ɠ����ɂ��Ă��������s���������̂Ńv���C���[����0�n�܂�ł��B
 * �������Q�[���̃C�x���g�i�s��ł́A�v���C���[�̃G���g���[�͈�ԍŌ�Ȃ̂ŁA3�n�܂�ł��B
 * 
 * (�u���[�_�[�ԍ� == �ʐMID) != �G���g���[�ԍ�
 */
//--------------------------------------------------------------
int ConTool_BreederNoGet(int entry_no)
{
	return BREEDER_MAX - entry_no - 1;
}

//--------------------------------------------------------------
/**
 * @brief   ���K���[�h���m�F
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:���K�B�@FALSE:���K�ł͂Ȃ�
 */
//--------------------------------------------------------------
BOOL ConTool_PracticeModeCheck(CONTEST_SYSTEM *consys)
{
	switch(consys->c_game.mode){
	case CONMODE_VISUAL_PRACTICE:
	case CONMODE_DANCE_PRACTICE:
	case CONMODE_ACTIN_PRACTICE:
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �`���[�g���A�����[�h���m�F
 * @param   consys		�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @retval  TRUE:�`���[�g���A���B�@FALSE:�`���[�g���A���ł͂Ȃ�
 */
//--------------------------------------------------------------
BOOL ConTool_TutorialModeCheck(CONTEST_SYSTEM *consys)
{
	switch(consys->c_game.mode){
	case CONMODE_VISUAL_TUTORIAL:
	case CONMODE_DANCE_TUTORIAL:
	case CONMODE_ACTIN_TUTORIAL:
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   BP����\������n�[�g�̐����擾����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 *
 * @retval  �n�[�g�̐�
 */
//--------------------------------------------------------------
int ConTool_HeartNumGet_BP(CONTEST_SYSTEM *consys, int breeder_no)
{
	int num, point, i;
	const u16 *num_data;
	const u16 HeartNumBPData[][HEART_NUM_BP_IF_MAX] = {
		{10, 20, 30, 40, 50, 60, 70, 80},			//NORMAL
		{90, 110, 130, 150, 170, 190, 210, 230},		//SUPER
		{170, 200, 230, 260, 290, 320, 350, 380},	//HYPER
		{320, 360, 400, 440, 480, 520, 560, 600},	//MASTER
		{100, 200, 300, 400, 450, 500, 550, 600},	//SIO
	};
	
	num = 0;
	point = consys->c_game.score[breeder_no].bp;
	
	if(consys->sio_flag == TRUE){
		num_data = HeartNumBPData[CONRANK_MASTER + 1];
	}
	else{
		num_data = HeartNumBPData[consys->c_game.rank];
	}
	
	for(i = 0; i < HEART_NUM_BP_IF_MAX; i++){
		if(point < num_data[i]){
			return num;
		}
		num++;
	}
	return num;
}

//--------------------------------------------------------------
/**
 * @brief   �N���b�v�|�C���g����\������n�[�g�̐����擾����
 *
 * @param   consys			�R���e�X�g�V�X�e�����[�N�ւ̃|�C���^
 * @param   breeder_no		�u���[�_�[�ԍ�
 *
 * @retval  �n�[�g�̐�
 */
//--------------------------------------------------------------
int ConTool_HeartNumGet_Clip(CONTEST_SYSTEM *consys, int breeder_no)
{
	int num, point, i;
	const u8 *num_data;
	const u8 HeartNumClipData[][HEART_NUM_CLIP_IF_MAX] = {
		{3, 5, 8},			//NORMAL
		{5, 10, 15},		//SUPER
		{7, 15, 23},		//HYPER
		{10, 20, 30},		//MASTER
		{10, 20, 30},		//SIO
	};
	
	num = 0;
	point = consys->c_game.score[breeder_no].clip;
	
	if(point == 0){
		return 0;
	}

	if(consys->sio_flag == TRUE){
		num_data = HeartNumClipData[CONRANK_MASTER + 1];
	}
	else{
		num_data = HeartNumClipData[consys->c_game.rank];
	}
	
	num = 1;
	for(i = 0; i < HEART_NUM_CLIP_IF_MAX; i++){
		if(point <= num_data[i]){
			return num;
		}
		num++;
	}
	return num;
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F���b�Z�[�W����ݒ�
 *
 * @param   sio_flag		TRUE:�ʐM�AFALSE:��ʐM
 */
//--------------------------------------------------------------
void ConTool_MsgPrintFlagSet(int sio_flag)
{
	if(sio_flag == FALSE){
		MsgPrintSkipFlagSet(MSG_SKIP_ON);
		MsgPrintAutoFlagSet(MSG_AUTO_SKIP_ON);
		MsgPrintTouchPanelFlagSet(MSG_TP_ON);
	}
	else{
		MsgPrintAutoFlagSet(MSG_AUTO_ON);
		
		MsgPrintSkipFlagSet(MSG_SKIP_OFF);
		MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �R���e�X�g�F���b�Z�[�W����ݒ�����Z�b�g����
 */
//--------------------------------------------------------------
void ConTool_MsgPrintFlagReset(void)
{
	MsgPrintSkipFlagSet(MSG_SKIP_OFF);
	MsgPrintAutoFlagSet(MSG_AUTO_OFF);
	MsgPrintTouchPanelFlagSet(MSG_TP_OFF);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�����Ă���R���e�X�g�̃����N�ƃ^�C�v����A�D���������ɖႦ�郊�{����ID���擾����
 *
 * @param   rank		�R���e�X�g�����N
 * @param   type		�R���e�X�g�^�C�v
 *
 * @retval  ���{��ID(PokeParaGet,Set�Ŏg�����)
 */
//--------------------------------------------------------------
u32 ConTool_RibbonIDGet(int rank, int type)
{
	u32 ribbon;

	switch(type){
	case CONTYPE_STYLE:
		ribbon = ID_PARA_trial_stylemedal_normal + rank;
		break;
	case CONTYPE_BEAUTIFUL:
		ribbon = ID_PARA_trial_beautifulmedal_normal + rank;
		break;
	case CONTYPE_CUTE:
		ribbon = ID_PARA_trial_cutemedal_normal + rank;
		break;
	case CONTYPE_CLEVER:
		ribbon = ID_PARA_trial_clevermedal_normal + rank;
		break;
	case CONTYPE_STRONG:
		ribbon = ID_PARA_trial_strongmedal_normal + rank;
		break;
	default:
		GF_ASSERT(0);
		return ID_PARA_trial_stylemedal_normal;
	}

	return ribbon;
}

//--------------------------------------------------------------
/**
 * @brief   �e�[�}�������_���Ŏ擾����
 *
 * @param   rank		�R���e�X�g�����N
 * @param   sio_flag	TRUE:�ʐM�ΐ�
 *
 * @retval  �e�[�}
 */
//--------------------------------------------------------------
u32 ConTool_ThemeRandomSelect(int rank, int sio_flag)
{
	u8 theme[CON_IMAGE_THEME_MAX];
	int count = 0;
	u32 ret_theme;
	
	if(rank == CONRANK_MASTER || sio_flag == TRUE){
		return gf_rand() % CON_IMAGE_THEME_MAX;
	}
	
	MI_CpuClear8(theme, CON_IMAGE_THEME_MAX);
	
	theme[count++] = CON_IMAGE_THEME_ARTIFICIAL;
	theme[count++] = CON_IMAGE_THEME_NATURAL;
	theme[count++] = CON_IMAGE_THEME_COLORFUL;

	if(rank >= CONRANK_SUPER){
		theme[count++] = CON_IMAGE_THEME_FLOWERY;
		theme[count++] = CON_IMAGE_THEME_SIMPLE;
		theme[count++] = CON_IMAGE_THEME_LIVELY;
	}
	
	if(rank >= CONRANK_HYPER){
		theme[count++] = CON_IMAGE_THEME_REFRESH;
		theme[count++] = CON_IMAGE_THEME_LIMIT;
		theme[count++] = CON_IMAGE_THEME_SOFTLY;
	}
	
	return theme[gf_rand() % count];
}

