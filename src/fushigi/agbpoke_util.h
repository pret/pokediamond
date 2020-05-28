extern void agbpoke_codeConv(u8 *src, u16 *dest, int length);

extern u32 agbpoke_GetTrainerID(void);
extern u8 *agbpoke_GetTrainerName(void);

//=========================================================================
//	
// プレイヤーシステムデータ
//
//=========================================================================
#define AGB_PERSON_NAME_SIZE	7
#define AGB_EOM_SIZE		1

typedef struct PersonalData{
		u8 my_name[AGB_PERSON_NAME_SIZE+AGB_EOM_SIZE];	//	自分の名前
		u8 my_sex;					//	自分の性別
		u8 save_flag;				//	セーブしたかどうかのフラグ
		u8 ID[4];					//	ＩＤナンバー

		u16 playtime_h;				//	プレイ時間（時）
		u8 playtime_m;				//	プレイ時間（分）
		u8 playtime_s;				//	プレイ時間（秒）
		u8 playtime_ms;				//	プレイ時間（1/60秒）

		u8 key_config;				//	オプションのキー設定
		u16 msg_speed:3;			//	ＭＳＧ送りの早さ
		u16 window_type:5;			//	システムウィンドウの種類
		u16 sound_mode:1;			//	ステレオ・モノラル切り替え
		u16 btl_type:1;				//	「かちぬき」「いれかえ」
		u16 btl_eff_sw:1;			//	戦闘エフェクトの有無
		u16 tnavi_zoom:1;			//	トレナビマップモード

  // これ以降は特殊な構造体が必要、または互換性を維持されていない項目なのでカット
}SYS_SAVE_DATA;

/*  */
