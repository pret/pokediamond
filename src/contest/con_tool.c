//==============================================================================
/**
 * @file	con_tool.c
 * @brief	コンテスト全体で使用する汎用的なツール
 * @author	matsuda
 * @date	2005.11.22(火)
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
//	定数定義
//==============================================================================
///BPのハートポイント取得の為のif分比較データ個数
#define HEART_NUM_BP_IF_MAX		(8)
///クリップのハートポイント取得の為のif分比較データ個数
#define HEART_NUM_CLIP_IF_MAX		(3)


//==============================================================================
//	データ
//==============================================================================
#include "ap_waza.dat"

///技効果データの数
#define APPEAL_WAZA_DATA_MAX	(NELEMS(AppealWazaData))


//--------------------------------------------------------------
/**
 * @brief   自分がサーバーかチェックする
 *
 * @param   consys		コンテストシステムワークへのポインタ
 *
 * @retval  TRUE:自分がサーバー
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
 * @brief   通信フラグが立っているか取得
 *
 * @param   consys		コンテストシステムワークへのポインタ
 *
 * @retval  TRUE:通信フラグが立っている。
 * @retval  FALSE:通信フラグが立っていない。
 */
//--------------------------------------------------------------
int ConTool_ContestSioFlagCheck(CONTEST_SYSTEM *consys)
{
	return consys->sio_flag;
}

//--------------------------------------------------------------
/**
 * @brief   コンテストに参加するCPUブリーダーのデータをセット
 *
 * @param   heap_id		テンポラリで使用するヒープのID
 * @param   entry_num	参加させるCPUの数
 * @param   type		参加するコンテストの種類
 * @param   rank		コンテストのランク
 * @param   mode		コンテストモード(CONMODE_???)
 * @param   hof_flag	殿堂入りフラグ(TRUE:殿堂入りしている)
 * @param   zenkoku_zukan_flag	全国図鑑入手フラグ(TRUE:入手している)
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
		//登場出来るタイミングかチェック
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
		
		//練習・チュートリアルフラグで登場出来るタイミングかチェック
		if(practice == TRUE){
			//練習
			if(brd_tbl[i].part_practice == 0){
				continue;
			}
		}
		else if(tutorial == TRUE){
			//チュートリアル
			if(brd_tbl[i].part_tutorial == 0){
				continue;
			}
		}
		else{
			//通常
			if(brd_tbl[i].part_practice == 1 || brd_tbl[i].part_tutorial == 1){
				continue;	//練習かチュートリアルに参加出来るのはスルー
			}
		}
		
		if((type == CONTYPE_STYLE && brd_tbl[i].part_style)
				|| (type == CONTYPE_BEAUTIFUL && brd_tbl[i].part_beautiful)
				|| (type == CONTYPE_CUTE && brd_tbl[i].part_cute)
				|| (type == CONTYPE_CLEVER && brd_tbl[i].part_clever)
				|| (type == CONTYPE_STRONG && brd_tbl[i].part_strong)){
			OS_TPrintf("%d番ブリーダーOK\n", i);
			putbrd[count++] = i;
		}
	}
	putbrd[count] = 0xff;	//番兵
	
	if(tutorial == FALSE){
		GF_ASSERT(count >= entry_num);
		
		//putbrdの中に1人でもHOF_SPECIALがいるかチェック
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
		
		//通常ブリーダーセット
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
		
		//スペシャルブリーダーがいる場合はランダムで一箇所上書き
		OS_TPrintf("スペシャルブリーダー人数＝%d\n", special_count);
		if(special_count > 0){
			no = BREEDER_MAX - entry_num;
			no += contest_rand(consys) % entry_num;
			consys->c_game.bd[no] = special_brd;
			OS_TPrintf("スペシャルブリーダー%d番にセット\n", no);
		}
	}
	else{	//チュートリアルの場合はランダムなし(先頭から順に自分、敵A、敵B、敵Cとなる)
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
 * @brief   コンテストに参加するCPUブリーダーのイメージクリップデータをセット
 *
 * @param   consys		コンテストシステムワークへのポインタ
 * @param   heap_id		テンポラリで使用するヒープのID
 *
 * ConTool_CpuBreederEntryでCPUのブリーダーデータを取得してからこの関数を使用してください
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
			GF_ASSERT(0 && "存在しないテーマ");
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
 * @brief   練習ダンス用のイメージクリップデータセット
 *
 * @param   consys		コンテストシステムワークへのポインタ
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
 * @brief   ブリーダーデータを元にPOKEMON_PARAMを作成する
 *
 * @param   bd		ブリーダーデータ
 * @param   pp		ポケパラ代入先
 * @param   heap_id	ヒープID
 * 
 * @retval  pp		作成したPOKEMON_PARAMへのポインタ
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
	//手持ち技セット
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		waza_no = bd->waza[i];
		PokeParaPut(pp, ID_PARA_waza1 + i, &waza_no);
	}

	//ニックネームと親名
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
	
	//各コンディション(かっこよさ、可愛さ等)とけづや
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
 * @brief   コンテスト用のポケモンソフトウェアスプライト生成関数
 *
 * @param   ssm_p		ソフトウェアスプライトマネージャへのポインタ
 * @param   poly_id		ポリゴンID
 * @param   pp			POKEMON_PARAMへのポインタ
 * @param   dir			ポケモンの向き(PARA_FRONT or PARA_BACK)
 * @param   ep			OAMへの展開用バッファへのポインタ(使用しない場合はNULL)
 * @param   heap_id		ヒープID(一時使用)
 * @param   x			表示座標X
 * @param   y			表示座標Y
 * @param   z			表示座標Z
 *
 * @retval  ソフトウェアスプライトのポインタ
 *
 * 全部門で使えるように汎用的に用意しているつもりです。
 * epは技エフェクトを出さないのであればNULL指定で大丈夫です。
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
 * @brief   コンテストを審査する審判のデータをセット
 *
 * @param   heap_id		テンポラリで使用するヒープのID
 * @param   sp_no		凄い審査員のNo
 * @param   type		コンテストの種類
 * @param   rank		コンテストのランク
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
	putjudge[count] = 0xff;	//番兵
	sp_putjudge[sp_count] = 0xff;	//番兵
	
	//ノーマル審判
	GF_ASSERT(count >= NORMAL_JUDGE_MAX);
	for(i = 0; i < NORMAL_JUDGE_MAX; i++){
	#if 0	//ランダムではなく、頭から順番固定で出すように変更 2006.06.07(水)
		no = contest_rand(consys) % count;
		consys->c_game.jd[i] = judge_tbl[putjudge[no]];
		for(t = no; putjudge[t] != 0xff; t++)
			putjudge[t] = putjudge[t+1];
		count--;
	#else
		consys->c_game.jd[i] = judge_tbl[putjudge[i]];
	#endif
	}
	
	//凄い審判
	GF_ASSERT(sp_count >= GUEST_JUDGE_MAX);
	no = contest_rand(consys) % sp_count;
	consys->c_game.jd[NORMAL_JUDGE_MAX] = judge_tbl[sp_putjudge[no]];
	
	//凄い審判の位置を決定し、審判データを並び替える
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
 * @brief   AP値を取得する
 * @param   appeal_no		アピール技番号
 * @retval  AP値(妨害値の場合はマイナス)
 */
//--------------------------------------------------------------
s8 ConTool_GetAPWaza_App(int appeal_no)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	return AppealWazaData[appeal_no].ap_point;
}

//--------------------------------------------------------------
/**
 * @brief   技説明メッセージのIDを取得する
 *
 * @param   appeal_no		アピール技番号
 * @param   u_id			説明メッセージ上段のメッセージID代入先
 * @param   d_id			説明メッセージ下段のメッセージID代入先
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
 * @brief   ポケモンリスト用の技説明メッセージのIDを取得する
 *
 * @param   appeal_no		アピール技番号
 *
 * @retval  説明メッセージのID
 */
//--------------------------------------------------------------
u32 ConTool_GetListAPSetumeiMsgID(int appeal_no)
{
	GF_ASSERT(appeal_no < APPEAL_WAZA_DATA_MAX);
	return CMSG_EXPLAIN_LIST_1 + (appeal_no - 1);
}

//--------------------------------------------------------------
/**
 * @brief   技効果メッセージのIDとタグコードを取得する
 *
 * @param   appeal_no		アピール技番号
 * @param   msg_type		取得するメッセージタイプ(KOUKA_MSGID_???)
 * @param   msg_id			メッセージID代入先
 * @param   msg_tag			メッセージタグ代入先
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
 * @brief   コンテストランクから、そのランクのメッセージIDを取得する
 * @param   con_rank		コンテストランク(CONRANK_???)
 * @param   mode			コンテストモード(CONMODE_???)
 * @param   sio_flag		TRUE:通信対戦
 * @retval  メッセージID
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
 * @brief   コンテストランクから、そのランクのメッセージIDを取得する(※イメージクリップ画面用！)
 * @param   con_rank		コンテストランク(CONRANK_???)
 * @retval  メッセージID
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
 * @brief   コンテストタイプから、そのタイプのメッセージIDを取得する(※イメージクリップ画面用！)
 * @param   con_type			CONTYPE_???
 * @retval  メッセージID
 */
//--------------------------------------------------------------
u32 ConTool_IMCGetTypeMsgID(int con_type)
{
	return ConTool_GetTypeMsgID(con_type, CONMODE_GRAND);
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプから、そのタイプのメッセージIDを取得する
 * @param   con_rank		コンテストタイプ(CONTYPE_???)
 * @param   con_mode		コンテストモード(CONMODE_???)
 * @retval  メッセージID
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
 * @brief   ブリーダー番号からエントリー番号を取得する
 * @param   breeder_no		ブリーダー番号
 * @retval  エントリー番号
 *
 * ブリーダー番号とエントリー番号は違います。
 * ブリーダー番号は通信IDと同じにしていた方が都合がいいのでプレイヤー側は0始まりです。
 * しかしゲームのイベント進行上では、プレイヤーのエントリーは一番最後なので、3始まりです。
 * 
 * (ブリーダー番号 == 通信ID) != エントリー番号
 */
//--------------------------------------------------------------
int ConTool_EntryNoGet(int breeder_no)
{
	return BREEDER_MAX - breeder_no - 1;
}

//--------------------------------------------------------------
/**
 * @brief   エントリー番号からブリーダー番号を取得する
 * @param   breeder_no		エントリー番号
 * @retval  ブリーダー番号
 *
 * ブリーダー番号とエントリー番号は違います。
 * ブリーダー番号は通信IDと同じにしていた方が都合がいいのでプレイヤー側は0始まりです。
 * しかしゲームのイベント進行上では、プレイヤーのエントリーは一番最後なので、3始まりです。
 * 
 * (ブリーダー番号 == 通信ID) != エントリー番号
 */
//--------------------------------------------------------------
int ConTool_BreederNoGet(int entry_no)
{
	return BREEDER_MAX - entry_no - 1;
}

//--------------------------------------------------------------
/**
 * @brief   練習モードか確認
 * @param   consys		コンテストシステムワークへのポインタ
 * @retval  TRUE:練習。　FALSE:練習ではない
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
 * @brief   チュートリアルモードか確認
 * @param   consys		コンテストシステムワークへのポインタ
 * @retval  TRUE:チュートリアル。　FALSE:チュートリアルではない
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
 * @brief   BPから表示するハートの数を取得する
 *
 * @param   consys			コンテストシステムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 *
 * @retval  ハートの数
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
 * @brief   クリップポイントから表示するハートの数を取得する
 *
 * @param   consys			コンテストシステムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 *
 * @retval  ハートの数
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
 * @brief   コンテスト：メッセージ送り設定
 *
 * @param   sio_flag		TRUE:通信、FALSE:非通信
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
 * @brief   コンテスト：メッセージ送り設定をリセットする
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
 * @brief   参加しているコンテストのランクとタイプから、優勝した時に貰えるリボンのIDを取得する
 *
 * @param   rank		コンテストランク
 * @param   type		コンテストタイプ
 *
 * @retval  リボンID(PokeParaGet,Setで使うやつ)
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
 * @brief   テーマをランダムで取得する
 *
 * @param   rank		コンテストランク
 * @param   sio_flag	TRUE:通信対戦
 *
 * @retval  テーマ
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

