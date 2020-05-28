//******************************************************************************
/**
 * 
 * @file	fieldobj_code.h
 * @brief	フィールドOBJで使用するシンボル,コード宣言 アセンブラソース読み込みアリ 故にenum禁止
 * @author	kagaya
 * @data	05.07.20
 */
//******************************************************************************
#ifndef FIELD_OBJ_CODE_H_FILE
#define FIELD_OBJ_CODE_H_FILE

//==============================================================================
///	方向
//==============================================================================
#define DIR_NOT			(-1)								///<向きがない場合
#define DIR_UP			(0)									///<上向き
#define DIR_DOWN		(1)									///<下向き
#define DIR_LEFT		(2)									///<左向き
#define DIR_RIGHT		(3)									///<右向き

#define DIR_LEFTUP		(4)									///<左上向き
#define DIR_RIGHTUP		(5)									///<右上向き
#define DIR_LEFTDOWN	(6)									///<左下向き
#define DIR_RIGHTDOWN	(7)									///<右下向き

#define DIR_4_MAX (DIR_LEFTUP)								///<4方向最大

//==============================================================================
//	特殊ID
//==============================================================================
//--------------------------------------------------------------
//	フィールドOBJ 特殊ID
//--------------------------------------------------------------
#define FLDOBJ_ID_PLAYER (0xff)	///<自機専用ID
#define FLDOBJ_ID_PAIR   (0xfe)	///<連れ歩き専用ID

//==============================================================================
//	フィールドOBJ 動作コード
//==============================================================================
//--------------------------------------------------------------
//	フィールドOBJ 動作コード
//--------------------------------------------------------------
#define MV_DMY			0x00		///<動作無し
#define MV_PLAYER		0x01		///<自機専用
#define MV_DIR_RND		0x02		///<ランダムに方向切り替え
#define MV_RND			0x03		///<ランダムに移動
#define MV_RND_V		0x04		///<ランダムに縦移動
#define MV_RND_H		0x05		///<ランダムに横移動
#define MV_RND_UL		0x06		///<ランダムに上左方向切り替え
#define MV_RND_UR		0x07		///<ランダムに上右方向切り替え
#define MV_RND_DL		0x08		///<ランダムに下左方向切り替え
#define MV_RND_DR		0x09		///<ランダムに下右方向切り替え
#define MV_RND_UDL		0x0a		///<ランダムに上下左方向切り替え
#define MV_RND_UDR		0x0b		///<ランダムに上下右方向切り替え
#define MV_RND_ULR		0x0c		///<ランダムに上左右方向切り替え
#define MV_RND_DLR		0x0d		///<ランダムに下左右方向切り替え
#define MV_UP			0x0e		///<上固定
#define MV_DOWN			0x0f		///<下固定
#define MV_LEFT			0x10		///<左固定
#define MV_RIGHT		0x11		///<右固定
#define MV_SPIN_L		0x12		///<左回転
#define MV_SPIN_R		0x13		///<右回転
#define MV_RT2			0x14		///<ルート2
#define MV_RTURLD       0x15        ///<ルート3 上右左下
#define MV_RTRLDU       0x16        ///<ルート3 右左下上
#define MV_RTDURL       0x17        ///<ルート3 下上右左
#define MV_RTLDUR       0x18        ///<ルート3 左下上右
#define MV_RTULRD       0x19        ///<ルート3 上左右下
#define MV_RTLRDU       0x1a        ///<ルート3 左右下上
#define MV_RTDULR       0x1b        ///<ルート3 下上左右
#define MV_RTRDUL       0x1c        ///<ルート3 右下上左
#define MV_RTLUDR       0x1d        ///<ルート3 左上下右
#define MV_RTUDRL       0x1e        ///<ルート3 上下右左
#define MV_RTRLUD       0x1f        ///<ルート3 右左上下
#define MV_RTDRLU       0x20        ///<ルート3 下右左上
#define MV_RTRUDL       0x21        ///<ルート3 右上下左
#define MV_RTUDLR       0x22        ///<ルート3 上下左右
#define MV_RTLRUD       0x23        ///<ルート3 左右上下
#define MV_RTDLRU       0x24        ///<ルート3 下左右上
#define MV_RTUL         0x25        ///<ルート4 上左
#define MV_RTDR         0x26        ///<ルート4 下右
#define MV_RTLD         0x27        ///<ルート4 左下
#define MV_RTRU         0x28        ///<ルート4 右上
#define MV_RTUR         0x29        ///<ルート4 上右
#define MV_RTDL         0x2a        ///<ルート4 下左
#define MV_RTLU         0x2b        ///<ルート4 左上
#define MV_RTRD         0x2c        ///<ルート4 右下
#define MV_RND_UD		0x2d		///<ランダムに上下切り替え
#define MV_RND_LR		0x2e		///<ランダムに左右切り替え
#define MV_SEED			0x2f		///<木の実
#define MV_PAIR			0x30		///<連れ歩き
#define MV_REWAR		0x31		///<再戦
#define MV_TR_PAIR		0x32		///<トレーナー連れ歩き
#define MV_HIDE_SNOW	0x33		///<隠れ蓑　雪
#define MV_HIDE_SAND	0x34		///<隠れ蓑　砂
#define MV_HIDE_GRND	0x35		///<隠れ蓑　土
#define MV_HIDE_KUSA	0x36		///<隠れ蓑　草

#define MV_CODE_MAX		0x37		///<コード最大（プログラム判定専用
#define MV_CODE_NOT		0xff		///<非動作コード(プログラム判定専用

/*　未対応
#define MV_COPYU	///<ものまね上
#define MV_COPYD	///<ものまね下
#define MV_COPYL	///<ものまね右
#define MV_COPYR	///<ものまね左
#define MV_COPYGRASSD	///<ものまね草下
#define MV_COPYGRASSL	///<ものまね草左
#define MV_COPYGRASSR	///<ものまね草右
#define MV_COPYGRASSU	///<ものまね草上
#define MV_HIDE_SKY			///<隠れ蓑　空
#define MV_HIDE_SWIM		///<隠れ蓑　海
#define MV_HIDE_SNOWMAN		///<隠れ蓑　雪だるま
#define MV_SLEEP	///<眠り　ダッシュで起きる
#define MV_DIVE		///<素潜り
*/

/*
 サブ動作で対応するもの
　1:とまってきょろきょろ ok
　　ランダム移動
　　ルート２，３，４　
　2：とまってくるくる ok
　　ランダム移動
　　ルート２，３，４　
	
　3：くるくる移動 ok
　　ランダム移動
　　ルート２，３，４　
　4：逃げる
　　ルート２，３，４　
　5：横泳ぎ
　　ルート２?
 * */

//==============================================================================
//	フィールドOBJ イベントタイプ
//==============================================================================
//--------------------------------------------------------------
//	フィールドOBJ イベントタイプ
//--------------------------------------------------------------
#define EV_TYPE_NORMAL 				0x00	///<通常タイプ
#define EV_TYPE_TRAINER				0x01	///<トレーナータイプ
#define EV_TYPE_TRAINER_EYEALL		0x02	///<トレーナー全方位検知タイプ
#define EV_TYPE_ITEM				0x03	///<アイテムタイプ
#define EV_TYPE_TRAINER_KYORO		0x04	///<トレーナータイプ　きょろきょろ
#define EV_TYPE_TRAINER_SPIN_STOP_L	0x05	///<トレーナータイプ　停止回転　左周り
#define EV_TYPE_TRAINER_SPIN_STOP_R	0x06	///<トレーナータイプ　停止回転　右回り
#define EV_TYPE_TRAINER_SPIN_MOVE_L	0x07	///<トレーナータイプ　移動回転　左周り
#define EV_TYPE_TRAINER_SPIN_MOVE_R	0x08	///<トレーナータイプ　移動回転　右回り
#define EV_TYPE_MSG 				0x09	///<通常タイプ メッセージID指定

/*
#define EV_TYPE_TRAINER_ESCAPE		0x09	///<トレーナータイプ　逃げる
#define EV_TYPE_TRAINER_SWIM_H		0x0a	///<トレーナータイプ　横泳ぎ
#define EV_TYPE_TRAINER_LIGHT			///<トレーナータイプ　ライト
#define EV_TYPE_TRAINER_LIGHT_DASH		///<トレーナータイプ　ライトダッシュ
*/

//==============================================================================
//	フィールドOBJ 描画ステータス
//==============================================================================
//--------------------------------------------------------------
///	フィールドOBJ 描画ステータス
//--------------------------------------------------------------
#define DRAW_STA_STOP		0x00		///<停止
#define DRAW_STA_WALK		0x01		///<移動
#define DRAW_STA_WALK_32F	0x01		///<移動 32フレーム
#define DRAW_STA_WALK_16F	0x02		///<移動 16フレーム
#define DRAW_STA_WALK_8F	0x03		///<移動 8フレーム
#define DRAW_STA_WALK_4F	0x04		///<移動 4フレーム
#define DRAW_STA_WALK_2F	0x05		///<移動 2フレーム
#define DRAW_STA_WALK_6F	0x06		///<移動 6フレーム
#define DRAW_STA_WALK_3F	0x07		///<移動 3フレーム
#define DRAW_STA_WALK_7F	0x08		///<移動 7フレーム

#define DRAW_STA_MAX (DRAW_STA_WALK_7F+1)	///<描画ステータス最大

#define DRAW_STA_PC_BOW		0x09
#define DRAW_STA_PCWOMAN_MAX (DRAW_STA_PC_BOW+1)

//--------------------------------------------------------------
///	フィールドOBJ 自機専用描画ステータス
//--------------------------------------------------------------
#define DRAW_STA_DASH_4F		(DRAW_STA_MAX)					///<移動　ダッシュ 4フレーム
#define DRAW_STA_MAX_HERO		(DRAW_STA_DASH_4F+1)			///<描画ステータス最大　自機

#define DRAW_STA_TAKE_OFF_16F	(DRAW_STA_MAX+1)				///<自機　ジャンプ台
#define DRAW_STA_TAKE_OFF_8F	(DRAW_STA_MAX+2)				///<自機　ジャンプ台
#define DRAW_STA_MAX_CYCLEHERO	(DRAW_STA_TAKE_OFF_8F+1)		///<描画ステータス最大　自機

//--------------------------------------------------------------
///	フィールドOBJ 自機釣り専用描画ステータス
//--------------------------------------------------------------
#define DRAW_STA_FISH_END	0x00
#define DRAW_STA_FISH_START	0x01
#define DRAW_STA_FISH_ON	0x02
#define DRAW_STA_FISH_HIT	0x03

#define DRAW_STA_MAX_FISH	(DRAW_STA_FISH_HIT+1)

//--------------------------------------------------------------
///	フィールドOBJ 自機万歳専用描画ステータス
//--------------------------------------------------------------
#define DRAW_STA_BANZAI 	0x00
#define DRAW_STA_BANZAI_UKE	0x01
#define DRAW_STA_MAX_BANZAI (DRAW_STA_BANZAI_UKE+1)

//==============================================================================
//	フィールドOBJ アニメーションコマンドコード
//==============================================================================
//--------------------------------------------------------------
//	フィールドOBJ アニメーションコマンドコード
//--------------------------------------------------------------
#define AC_DIR_U				0x00		///<上に向く
#define AC_DIR_D				0x01		///<下に向く
#define AC_DIR_L				0x02		///<左に向く
#define AC_DIR_R				0x03		///<右に向く
#define AC_WALK_U_32F			0x04		///<上に移動　32フレーム
#define AC_WALK_D_32F			0x05		///<下に移動　32フレーム
#define AC_WALK_L_32F			0x06		///<左に移動　32フレーム
#define AC_WALK_R_32F			0x07		///<右に移動　32フレーム
#define AC_WALK_U_16F			0x08		///<上に移動　16フレーム
#define AC_WALK_D_16F			0x09		///<下に移動　16フレーム
#define AC_WALK_L_16F			0x0a		///<左に移動　16フレーム
#define AC_WALK_R_16F			0x0b		///<右に移動　16フレーム
#define AC_WALK_U_8F			0x0c		///<上に移動　8フレーム
#define AC_WALK_D_8F			0x0d		///<下に移動　8フレーム
#define AC_WALK_L_8F			0x0e		///<左に移動　8フレーム
#define AC_WALK_R_8F			0x0f		///<右に移動　8フレーム
#define AC_WALK_U_4F			0x10		///<上に移動　4フレーム
#define AC_WALK_D_4F			0x11		///<下に移動　4フレーム
#define AC_WALK_L_4F			0x12		///<左に移動　4フレーム
#define AC_WALK_R_4F			0x13		///<右に移動　4フレーム
#define AC_WALK_U_2F			0x14		///<上に移動　2フレーム
#define AC_WALK_D_2F			0x15		///<下に移動　2フレーム
#define AC_WALK_L_2F			0x16		///<左に移動　2フレーム
#define AC_WALK_R_2F			0x17		///<右に移動　2フレーム
#define AC_STAY_WALK_U_32F		0x18		///<上向きにその場歩き　32フレーム
#define AC_STAY_WALK_D_32F		0x19		///<下向きにその場歩き　32フレーム
#define AC_STAY_WALK_L_32F		0x1a		///<左向きにその場歩き　32フレーム
#define AC_STAY_WALK_R_32F		0x1b		///<右向きにその場歩き　32フレーム
#define AC_STAY_WALK_U_16F		0x1c		///<上向きにその場歩き　16フレーム
#define AC_STAY_WALK_D_16F		0x1d		///<下向きにその場歩き　16フレーム
#define AC_STAY_WALK_L_16F		0x1e		///<左向きにその場歩き　16フレーム
#define AC_STAY_WALK_R_16F		0x1f		///<右向きにその場歩き　16フレーム
#define AC_STAY_WALK_U_8F		0x20		///<上向きにその場歩き　8フレーム
#define AC_STAY_WALK_D_8F		0x21		///<下向きにその場歩き　8フレーム
#define AC_STAY_WALK_L_8F		0x22		///<左向きにその場歩き　8フレーム
#define AC_STAY_WALK_R_8F		0x23		///<右向きにその場歩き　8フレーム
#define AC_STAY_WALK_U_4F		0x24		///<上向きにその場歩き　4フレーム
#define AC_STAY_WALK_D_4F		0x25		///<下向きにその場歩き　4フレーム
#define AC_STAY_WALK_L_4F		0x26		///<左向きにその場歩き　4フレーム
#define AC_STAY_WALK_R_4F		0x27		///<右向きにその場歩き　4フレーム
#define AC_STAY_WALK_U_2F		0x28		///<上向きにその場歩き　2フレーム
#define AC_STAY_WALK_D_2F		0x29		///<下向きにその場歩き　2フレーム
#define AC_STAY_WALK_L_2F		0x2a		///<左向きにその場歩き　2フレーム
#define AC_STAY_WALK_R_2F		0x2b		///<右向きにその場歩き　2フレーム
#define AC_STAY_JUMP_U_16F		0x2c		///<上向きにその場ジャンプ 16フレーム
#define AC_STAY_JUMP_D_16F		0x2d		///<下向きにその場ジャンプ 16フレーム
#define AC_STAY_JUMP_L_16F		0x2e		///<左向きにその場ジャンプ 16フレーム
#define AC_STAY_JUMP_R_16F		0x2f		///<右向きにその場ジャンプ 16フレーム
#define AC_STAY_JUMP_U_8F		0x30		///<上向きにその場ジャンプ 8フレーム
#define AC_STAY_JUMP_D_8F		0x31		///<下向きにその場ジャンプ 8フレーム
#define AC_STAY_JUMP_L_8F		0x32		///<左向きにその場ジャンプ 8フレーム
#define AC_STAY_JUMP_R_8F		0x33		///<右向きにその場ジャンプ 8フレーム
#define AC_JUMP_U_1G_8F			0x34		///<上向きにジャンプ 1グリッド 8フレーム
#define AC_JUMP_D_1G_8F			0x35		///<下向きにジャンプ 1グリッド 8フレーム
#define AC_JUMP_L_1G_8F			0x36		///<左向きにジャンプ 1グリッド 8フレーム
#define AC_JUMP_R_1G_8F			0x37		///<右向きにジャンプ 1グリッド 8フレーム
#define AC_JUMP_U_2G_16F		0x38		///<上向きにジャンプ 2グリッド 16フレーム
#define AC_JUMP_D_2G_16F		0x39		///<下向きにジャンプ 2グリッド 16フレーム
#define AC_JUMP_L_2G_16F		0x3a		///<左向きにジャンプ 2グリッド 16フレーム
#define AC_JUMP_R_2G_16F		0x3b		///<右向きにジャンプ 2グリッド 16フレーム
#define AC_WAIT_1F				0x3c		///<1フレーム待ち
#define AC_WAIT_2F				0x3d		///<2フレーム待ち
#define AC_WAIT_4F				0x3e		///<4フレーム待ち
#define AC_WAIT_8F				0x3f		///<8フレーム待ち
#define AC_WAIT_15F				0x40		///<15フレーム待ち
#define AC_WAIT_16F				0x41		///<16フレーム待ち
#define AC_WAIT_32F				0x42		///<32フレーム待ち
#define AC_WARP_UP				0x43		///<上にワープ
#define AC_WARP_DOWN			0x44		///<下にワープ
#define AC_VANISH_ON			0x45		///<非表示にする
#define AC_VANISH_OFF			0x46		///<表示にする
#define AC_DIR_PAUSE_ON			0x47		///<方向固定する
#define AC_DIR_PAUSE_OFF		0x48		///<方向固定しない
#define AC_ANM_PAUSE_ON			0x49		///<アニメポーズ
#define AC_ANM_PAUSE_OFF		0x4a		///<アニメポーズを解除
#define AC_MARK_GYOE			0x4b		///<!マークを出す
#define AC_WALK_U_6F			0x4c		///<上方向に移動　6フレーム
#define AC_WALK_D_6F			0x4d		///<下方向に移動　6フレーム
#define AC_WALK_L_6F			0x4e		///<左方向に移動　6フレーム
#define AC_WALK_R_6F			0x4f		///<右方向に移動　6フレーム
#define AC_WALK_U_3F			0x50		///<上方向に移動　3フレーム
#define AC_WALK_D_3F			0x51		///<下方向に移動　3フレーム
#define AC_WALK_L_3F			0x52		///<左方向に移動　3フレーム
#define AC_WALK_R_3F			0x53		///<右方向に移動　3フレーム
#define AC_WALK_U_1F			0x54		///<上方向に移動　1フレーム(システム未対応 使用禁止
#define AC_WALK_D_1F			0x55		///<下方向に移動　1フレーム(システム未対応 使用禁止
#define AC_WALK_L_1F			0x56		///<左方向に移動　1フレーム(システム未対応 使用禁止
#define AC_WALK_R_1F			0x57		///<右方向に移動　1フレーム(システム未対応 使用禁止
#define AC_DASH_U_4F			0x58		///<上方向に移動　4フレーム(自機専用
#define AC_DASH_D_4F			0x59		///<下方向に移動　4フレーム(自機専用
#define AC_DASH_L_4F			0x5a		///<左方向に移動　4フレーム(自機専用
#define AC_DASH_R_4F			0x5b		///<右方向に移動　4フレーム(自機専用
#define AC_JUMPHI_L_1G_16F		0x5c	///<左方向に高いジャンプ 1グリッド 16フレーム(自機専用
#define AC_JUMPHI_R_1G_16F		0x5d	///<右方向に高いジャンプ 1グリッド 16フレーム(自機専用
#define AC_JUMPHI_L_3G_32F		0x5e	///<左方向に高いジャンプ 3グリッド 32フレーム(自機専用
#define AC_JUMPHI_R_3G_32F		0x5f	///<右方向に高いジャンプ 3グリッド 32フレーム(自機専用
#define AC_WALK_U_7F			0x60		///<上方向に移動　7フレーム
#define AC_WALK_D_7F			0x61		///<下方向に移動　7フレーム
#define AC_WALK_L_7F			0x62		///<左方向に移動　7フレーム
#define AC_WALK_R_7F			0x63		///<右方向に移動　7フレーム
#define AC_PC_BOW				0x64		///<PCお辞儀(PCWOMAN1専用
#define AC_HIDE_PULLOFF			0x65		///<隠れ蓑脱ぐ(MV_HIDE専用
#define AC_HERO_BANZAI			0x66		///<PC両手差出(自機専用
#define AC_MARK_SAISEN			0x67		///<再戦マーク表示
#define AC_HERO_BANZAI_UKE		0x68		///<PC両手差出受け取り(自機専用

#define ACMD_MAX				0x69		///<アニメーションコマンド最大数

#define ACMD_END				0xfe		///<アニメーションコマンド終了
#define ACMD_NOT				0xff		///<非アニメーションコマンド

//==============================================================================
//	フィールドOBJ 表示コード
//==============================================================================
//--------------------------------------------------------------
//	フィールドOBJ 表示コード
//--------------------------------------------------------------
#define HERO			0x0000		///<主人公
#define BABYBOY1		0x0001		///<男の子
#define BABYGIRL1		0x0002		///<女の子
#define BOY1			0x0003		///<少年
#define BOY2			0x0004		///<活発少年
#define BOY3			0x0005		///<麦わら少年
#define GIRL1			0x0006		///<少女
#define GIRL2			0x0007		///<活発少女
#define GIRL3			0x0008		///<お洒落少女
#define MAN1			0x0009		///<お兄さん
#define MAN2			0x000a		///<ツッパリお兄さん
#define MAN3			0x000b		///<トレーナーお兄さん
#define WOMAN1			0x000c		///<お姉さん
#define WOMAN2			0x000d		///<お洒落お姉さん
#define WOMAN3			0x000e		///<トレーナーお姉さん
#define MIDDLEMAN1		0x000f		///<おじさん
#define MIDDLEWOMAN1	0x0010		///<おばさん
#define OLDMAN1			0x0011		///<和風爺さん
#define OLDWOMAN1		0x0012		///<和風婆さん
#define BIGMAN			0x0013		///<太ったお兄さん
#define MOUNT			0x0014		///<山男
#define CYCLEHERO		0x0015		///<主人公自転車
#define REPORTER		0x0016		///<
#define CAMERAMAN		0x0017		///<
#define SHOPM1			0x0018		///<
#define SHOPW1			0x0019		///<
#define PCWOMAN1		0x001a		///<
#define PCWOMAN2		0x001b		///<
#define PCWOMAN3		0x001c		///<
#define ASSISTANTM		0x001d		///<
#define ASSISTANTW		0x001e		///<
#define BADMAN			0x001f		///<
#define SKIERM			0x0020		///<
#define SKIERW			0x0021		///<
#define POLICEMAN		0x0022		///<
#define IDOL			0x0023		///<
#define GENTLEMAN		0x0024		///<
#define LADY			0x0025		///<
#define CYCLEM			0x0026		///<
#define CYCLEW			0x0027		///<
#define WORKMAN			0x0028		///<
#define FARMER			0x0029		///<
#define COWGIRL			0x002a		///<
#define CLOWN			0x002b		///<
#define ARTIST			0x002c		///<
#define SPORTSMAN		0x002d		///<
#define SWIMMERM		0x002e		///<
#define SWIMMERW		0x002f		///<
#define BEACHGIRL		0x0030		///<
#define BEACHBOY		0x0031		///<
#define EXPLORE			0x0032		///<
#define FIGHTER			0x0033		///<
#define CAMPBOY			0x0034		///<
#define PICNICGIRL		0x0035		///<
#define FISHING			0x0036		///<
#define AMBRELLA		0x0037		///<
#define SEAMAN			0x0038		///<
#define BRINGM			0x0039		///<
#define BRINGW			0x003a		///<
#define WAITER			0x003b		///<
#define WAITRESS		0x003c		///<
#define VETERAN			0x003d		///<
#define GORGGEOUSM		0x003e		///<
#define GORGGEOUSW		0x003f		///<
#define BOY4			0x0040		///<
#define GIRL4			0x0041		///<
#define MAN4			0x0042		///<
#define WOMAN4			0x0043		///<
#define MAN5			0x0044		///<
#define WOMAN5			0x0045		///<
#define MYSTERY			0x0046		///<
#define PIKACHU			0x0047		///<
#define PIPPI			0x0048		///<
#define PURIN			0x0049		///<
#define KODUCK			0x004a		///<
#define PRASLE			0x004b		///<
#define MINUN			0x004c		///<
#define MARIL			0x004d		///<
#define ACHAMO			0x004e		///<
#define ENECO			0x004f		///<
#define GONBE			0x0050		///<
#define BABY			0x0051		///<
#define MIDDLEMAN2		0x0052		///<
#define MIDDLEWOMAN2	0x0053		///<
#define ROCK			0x0054		///<
#define BREAKROCK		0x0055		///<
#define TREE			0x0056		///<
#define MONATERBALL		0x0057		///<
#define SHADOW			0x0058		///<
#define BOUGH			0x0059		///<
#define FALLTREE		0x005a		///<
#define BOARD_A			0x005b		///<看板
#define BOARD_B			0x005c		///<看板
#define BOARD_C			0x005d		///<看板
#define BOARD_D			0x005e		///<看板
#define BOARD_E			0x005f		///<看板
#define BOARD_F			0x0060		///<看板
#define HEROINE			0x0061		///<
#define CYCLEHEROINE	0x0062		///<
#define DOCTOR			0x0063
#define SEED			0x0064
#define WKOBJCODE00		0x0065
#define WKOBJCODE01		0x0066
#define WKOBJCODE02		0x0067
#define WKOBJCODE03		0x0068
#define WKOBJCODE04		0x0069
#define WKOBJCODE05		0x006a
#define WKOBJCODE06		0x006b
#define WKOBJCODE07		0x006c
#define WKOBJCODE08		0x006d
#define WKOBJCODE09		0x006e
#define WKOBJCODE10		0x006f
#define WKOBJCODE11		0x0071
#define WKOBJCODE12		0x0072
#define WKOBJCODE13		0x0073
#define WKOBJCODE14		0x0074
#define WKOBJCODE15		0x0075
#define SNOWBALL		0x0076
#define GINGABOSS		0x0078
#define GKANBU1			0x0079
#define GKANBU2			0x007a
#define GKANBU3			0x007b
#define GINGAM			0x007c
#define GINGAW			0x007d
#define LEADER1			0x007e
#define LEADER2			0x007f
#define LEADER3			0x0080
#define LEADER4			0x0081
#define LEADER5			0x0082
#define LEADER6			0x0083
#define LEADER7			0x0084
#define LEADER8			0x0085
#define BIGFOUR1		0x0086
#define BIGFOUR2		0x0087
#define BIGFOUR3		0x0088
#define BIGFOUR4		0x0089
#define CHAMPION		0x008a
#define PAPA			0x008b
#define MAMA			0x008c
#define SEVEN1			0x008d
#define SEVEN2			0x008e
#define SEVEN3			0x008f
#define SEVEN4			0x0090
#define SEVEN5			0x0091
#define SEVEN6			0x0092
#define SEVEN7			0x0093
#define RIVEL			0x0094
#define BOAT			0x0095
#define TRAIN			0x0096
#define SPPOKE1			0x0097
#define SPPOKE2			0x0098
#define SPPOKE3			0x0099
#define SPPOKE4			0x009a
#define SPPOKE5			0x009b
#define SPPOKE6			0x009c
#define SPPOKE7			0x009d
#define SPPOKE8			0x009e
#define SPPOKE9			0x009f
#define SPPOKE10		0x00a0
#define SPPOKE11		0x00a1
#define OBAKE			0x00a2
#define WOMAN6			0x00a3
#define OLDMAN2			0x00a4
#define OLDWOMAN2		0x00a5
#define OOKIDO			0x00a6
#define MIKAN			0x00a7
#define SUNGLASSES		0x00a8
#define TOWERBOSS		0x00a9
#define SNOWCOVER		0x00aa
#define TREECOVER		0x00ab
#define ROCKCOVER		0x00ac
#define BIRD			0x00ad
#define BAG				0x00ae
#define MAID			0x00af
#define SPHERO			0x00b0
#define SPHEROINE		0x00b1
#define	SWIMHERO		0x00b2
#define SWIMHEROINE		0x00b3
#define WATERHERO		0x00b4
#define WATERHEROINE	0x00b5
#define VENTHOLE		0x00b6
#define BOOK			0x00b7
#define SPPOKE12		0x00b8
#define BALLOON			0x00b9
#define CONTESTHERO		0x00ba
#define CONTESTHEROINE	0x00bb
#define FISHINGHERO		0x00bc
#define FISHINGHEROINE	0x00bd
#define MOSS			0x00be
#define FREEZES			0x00bf
#define POLE			0x00c0
#define DELIVERY		0x00c1
#define DSBOY			0x00c2
#define KOIKING			0x00c3
#define POKEHERO		0x00c4
#define POKEHEROINE		0x00c5
#define SAVEHERO		0x00c6
#define SAVEHEROINE		0x00c7
#define BANZAIHERO		0x00c8
#define BANZAIHEROINE	0x00c9
#define DOOR			0x00ca
#define MONUMENT		0x00cb
#define PATIRITUSU		0x00cc
#define KINOCOCO		0x00cd
#define MIMITUTO		0x00ce
#define KOLUCKY			0x00cf
#define WANRIKY			0x00d0
#define DOOR2			0x00d1

#define OBJCODEMAX		0xffff		///<OBJコード最大

//--------------------------------------------------------------
///	ワーク参照型OBJコード　チェックシンボル
//--------------------------------------------------------------
#define WKOBJCODE_ORG	(WKOBJCODE00)
#define WKOBJCODE_END	(WKOBJCODE15)

//--------------------------------------------------------------
///	木の実専用OBJコード　通常のOBJコードに重ならない様、注意
/// ※マップエディタでの配置は禁止
//--------------------------------------------------------------
#define SEEDCODEORG (0x1000)
#define SEED00				(SEEDCODEORG + 0x00)
#define SEED01A                (SEEDCODEORG + 0x01)
#define SEED01B                (SEEDCODEORG + 0x02)
#define SEED01C                (SEEDCODEORG + 0x03)
#define SEED02A                (SEEDCODEORG + 0x04)
#define SEED02B                (SEEDCODEORG + 0x05)
#define SEED02C                (SEEDCODEORG + 0x06)
#define SEED03A                (SEEDCODEORG + 0x07)
#define SEED03B                (SEEDCODEORG + 0x08)
#define SEED03C                (SEEDCODEORG + 0x09)
#define SEED04A                (SEEDCODEORG + 0x0a)
#define SEED04B                (SEEDCODEORG + 0x0b)
#define SEED04C                (SEEDCODEORG + 0x0c)
#define SEED05A                (SEEDCODEORG + 0x0d)
#define SEED05B                (SEEDCODEORG + 0x0e)
#define SEED05C                (SEEDCODEORG + 0x0f)
#define SEED06A                (SEEDCODEORG + 0x10)
#define SEED06B                (SEEDCODEORG + 0x11)
#define SEED06C                (SEEDCODEORG + 0x12)
#define SEED07A                (SEEDCODEORG + 0x13)
#define SEED07B                (SEEDCODEORG + 0x14)
#define SEED07C                (SEEDCODEORG + 0x15)
#define SEED08A                (SEEDCODEORG + 0x16)
#define SEED08B                (SEEDCODEORG + 0x17)
#define SEED08C                (SEEDCODEORG + 0x18)
#define SEED09A                (SEEDCODEORG + 0x19)
#define SEED09B                (SEEDCODEORG + 0x1a)
#define SEED09C                (SEEDCODEORG + 0x1b)
#define SEED10A                (SEEDCODEORG + 0x1c)
#define SEED10B                (SEEDCODEORG + 0x1d)
#define SEED10C                (SEEDCODEORG + 0x1e)
#define SEED11A                (SEEDCODEORG + 0x1f)
#define SEED11B                (SEEDCODEORG + 0x20)
#define SEED11C                (SEEDCODEORG + 0x21)
#define SEED12A                (SEEDCODEORG + 0x22)
#define SEED12B                (SEEDCODEORG + 0x23)
#define SEED12C                (SEEDCODEORG + 0x24)
#define SEED13A                (SEEDCODEORG + 0x25)
#define SEED13B                (SEEDCODEORG + 0x26)
#define SEED13C                (SEEDCODEORG + 0x27)
#define SEED14A                (SEEDCODEORG + 0x28)
#define SEED14B                (SEEDCODEORG + 0x29)
#define SEED14C                (SEEDCODEORG + 0x2a)
#define SEED15A                (SEEDCODEORG + 0x2b)
#define SEED15B                (SEEDCODEORG + 0x2c)
#define SEED15C                (SEEDCODEORG + 0x2d)
#define SEED16A                (SEEDCODEORG + 0x2e)
#define SEED16B                (SEEDCODEORG + 0x2f)
#define SEED16C                (SEEDCODEORG + 0x30)
#define SEED17A                (SEEDCODEORG + 0x31)
#define SEED17B                (SEEDCODEORG + 0x32)
#define SEED17C                (SEEDCODEORG + 0x33)
#define SEED18A                (SEEDCODEORG + 0x34)
#define SEED18B                (SEEDCODEORG + 0x35)
#define SEED18C                (SEEDCODEORG + 0x36)
#define SEED19A                (SEEDCODEORG + 0x37)
#define SEED19B                (SEEDCODEORG + 0x38)
#define SEED19C                (SEEDCODEORG + 0x39)
#define SEED20A                (SEEDCODEORG + 0x3a)
#define SEED20B                (SEEDCODEORG + 0x3b)
#define SEED20C                (SEEDCODEORG + 0x3c)
#define SEED21A                (SEEDCODEORG + 0x3d)
#define SEED21B                (SEEDCODEORG + 0x3e)
#define SEED21C                (SEEDCODEORG + 0x3f)
#define SEED22A                (SEEDCODEORG + 0x40)
#define SEED22B                (SEEDCODEORG + 0x41)
#define SEED22C                (SEEDCODEORG + 0x42)
#define SEED23A                (SEEDCODEORG + 0x43)
#define SEED23B                (SEEDCODEORG + 0x44)
#define SEED23C                (SEEDCODEORG + 0x45)
#define SEED24A                (SEEDCODEORG + 0x46)
#define SEED24B                (SEEDCODEORG + 0x47)
#define SEED24C                (SEEDCODEORG + 0x48)
#define SEED25A                (SEEDCODEORG + 0x49)
#define SEED25B                (SEEDCODEORG + 0x4a)
#define SEED25C                (SEEDCODEORG + 0x4b)
#define SEED26A                (SEEDCODEORG + 0x4c)
#define SEED26B                (SEEDCODEORG + 0x4d)
#define SEED26C                (SEEDCODEORG + 0x4e)
#define SEED27A                (SEEDCODEORG + 0x4f)
#define SEED27B                (SEEDCODEORG + 0x50)
#define SEED27C                (SEEDCODEORG + 0x51)
#define SEED28A                (SEEDCODEORG + 0x52)
#define SEED28B                (SEEDCODEORG + 0x53)
#define SEED28C                (SEEDCODEORG + 0x54)
#define SEED29A                (SEEDCODEORG + 0x55)
#define SEED29B                (SEEDCODEORG + 0x56)
#define SEED29C                (SEEDCODEORG + 0x57)
#define SEED30A                (SEEDCODEORG + 0x58)
#define SEED30B                (SEEDCODEORG + 0x59)
#define SEED30C                (SEEDCODEORG + 0x5a)
#define SEED31A                (SEEDCODEORG + 0x5b)
#define SEED31B                (SEEDCODEORG + 0x5c)
#define SEED31C                (SEEDCODEORG + 0x5d)
#define SEED32A                (SEEDCODEORG + 0x5e)
#define SEED32B                (SEEDCODEORG + 0x5f)
#define SEED32C                (SEEDCODEORG + 0x60)
#define SEED33A                (SEEDCODEORG + 0x61)
#define SEED33B                (SEEDCODEORG + 0x62)
#define SEED33C                (SEEDCODEORG + 0x63)
#define SEED34A                (SEEDCODEORG + 0x64)
#define SEED34B                (SEEDCODEORG + 0x65)
#define SEED34C                (SEEDCODEORG + 0x66)
#define SEED35A                (SEEDCODEORG + 0x67)
#define SEED35B                (SEEDCODEORG + 0x68)
#define SEED35C                (SEEDCODEORG + 0x69)
#define SEED36A                (SEEDCODEORG + 0x6a)
#define SEED36B                (SEEDCODEORG + 0x6b)
#define SEED36C                (SEEDCODEORG + 0x6c)
#define SEED37A                (SEEDCODEORG + 0x6d)
#define SEED37B                (SEEDCODEORG + 0x6e)
#define SEED37C                (SEEDCODEORG + 0x6f)
#define SEED38A                (SEEDCODEORG + 0x70)
#define SEED38B                (SEEDCODEORG + 0x71)
#define SEED38C                (SEEDCODEORG + 0x72)
#define SEED39A                (SEEDCODEORG + 0x73)
#define SEED39B                (SEEDCODEORG + 0x74)
#define SEED39C                (SEEDCODEORG + 0x75)
#define SEED40A                (SEEDCODEORG + 0x76)
#define SEED40B                (SEEDCODEORG + 0x77)
#define SEED40C                (SEEDCODEORG + 0x78)
#define SEED41A                (SEEDCODEORG + 0x79)
#define SEED41B                (SEEDCODEORG + 0x7a)
#define SEED41C                (SEEDCODEORG + 0x7b)
#define SEED42A                (SEEDCODEORG + 0x7c)
#define SEED42B                (SEEDCODEORG + 0x7d)
#define SEED42C                (SEEDCODEORG + 0x7e)
#define SEED43A                (SEEDCODEORG + 0x7f)
#define SEED43B                (SEEDCODEORG + 0x80)
#define SEED43C                (SEEDCODEORG + 0x81)
#define SEED44A                (SEEDCODEORG + 0x82)
#define SEED44B                (SEEDCODEORG + 0x83)
#define SEED44C                (SEEDCODEORG + 0x84)
#define SEED45A                (SEEDCODEORG + 0x85)
#define SEED45B                (SEEDCODEORG + 0x86)
#define SEED45C                (SEEDCODEORG + 0x87)
#define SEED46A                (SEEDCODEORG + 0x88)
#define SEED46B                (SEEDCODEORG + 0x89)
#define SEED46C                (SEEDCODEORG + 0x8a)
#define SEED47A                (SEEDCODEORG + 0x8b)
#define SEED47B                (SEEDCODEORG + 0x8c)
#define SEED47C                (SEEDCODEORG + 0x8d)
#define SEED48A                (SEEDCODEORG + 0x8e)
#define SEED48B                (SEEDCODEORG + 0x8f)
#define SEED48C                (SEEDCODEORG + 0x90)
#define SEED49A                (SEEDCODEORG + 0x91)
#define SEED49B                (SEEDCODEORG + 0x92)
#define SEED49C                (SEEDCODEORG + 0x93)
#define SEED50A                (SEEDCODEORG + 0x94)
#define SEED50B                (SEEDCODEORG + 0x95)
#define SEED50C                (SEEDCODEORG + 0x96)
#define SEED51A                (SEEDCODEORG + 0x97)
#define SEED51B                (SEEDCODEORG + 0x98)
#define SEED51C                (SEEDCODEORG + 0x99)
#define SEED52A                (SEEDCODEORG + 0x9a)
#define SEED52B                (SEEDCODEORG + 0x9b)
#define SEED52C                (SEEDCODEORG + 0x9c)
#define SEED53A                (SEEDCODEORG + 0x9d)
#define SEED53B                (SEEDCODEORG + 0x9e)
#define SEED53C                (SEEDCODEORG + 0x9f)
#define SEED54A                (SEEDCODEORG + 0xa0)
#define SEED54B                (SEEDCODEORG + 0xa1)
#define SEED54C                (SEEDCODEORG + 0xa2)
#define SEED55A                (SEEDCODEORG + 0xa3)
#define SEED55B                (SEEDCODEORG + 0xa4)
#define SEED55C                (SEEDCODEORG + 0xa5)
#define SEED56A                (SEEDCODEORG + 0xa6)
#define SEED56B                (SEEDCODEORG + 0xa7)
#define SEED56C                (SEEDCODEORG + 0xa8)
#define SEED57A                (SEEDCODEORG + 0xa9)
#define SEED57B                (SEEDCODEORG + 0xaa)
#define SEED57C                (SEEDCODEORG + 0xab)
#define SEED58A                (SEEDCODEORG + 0xac)
#define SEED58B                (SEEDCODEORG + 0xad)
#define SEED58C                (SEEDCODEORG + 0xae)
#define SEED59A                (SEEDCODEORG + 0xaf)
#define SEED59B                (SEEDCODEORG + 0xb0)
#define SEED59C                (SEEDCODEORG + 0xb1)
#define SEED60A                (SEEDCODEORG + 0xb2)
#define SEED60B                (SEEDCODEORG + 0xb3)
#define SEED60C                (SEEDCODEORG + 0xb4)
#define SEED61A                (SEEDCODEORG + 0xb5)
#define SEED61B                (SEEDCODEORG + 0xb6)
#define SEED61C                (SEEDCODEORG + 0xb7)
#define SEED62A                (SEEDCODEORG + 0xb8)
#define SEED62B                (SEEDCODEORG + 0xb9)
#define SEED62C                (SEEDCODEORG + 0xba)
#define SEED63A                (SEEDCODEORG + 0xbb)
#define SEED63B                (SEEDCODEORG + 0xbc)
#define SEED63C                (SEEDCODEORG + 0xbd)
#define SEED64A                (SEEDCODEORG + 0xbe)
#define SEED64B                (SEEDCODEORG + 0xbf)
#define SEED64C                (SEEDCODEORG + 0xc0)

//--------------------------------------------------------------
///	特殊OBJコード
/// ※マップエディタでの配置は禁止
//--------------------------------------------------------------
#define NONDRAW			(0x2000)

//==============================================================================
//	フィールドOBJ モデルID
//==============================================================================
//--------------------------------------------------------------
//	モデルID
//--------------------------------------------------------------
#define BLACT_MDLID_32x32		0x0000		///<32x32
#define BLACT_MDLID_16x16		0x0001		///<16x16
#define BLACT_MDLID_16x16_1		0x0002		///<16x16
#define BLACT_MDLID_SEED_ME		0x0003		///<木の実　芽
#define BLACT_MDLID_SEED		0x0004		///<木の実
#define BLACT_MDLID_64x64		0x0005		///<64x64
#define BLACT_MDLID_FISHINGHERO	0x0006		///<釣り自機
#define BLACT_MDLID_16x32		0x0007		///<16x32
#define BLACT_MDLID_64x32		0x0008		///<64x32

#define BLACT_MDLID_MAX			0xffff		///<モデルID最大

//==============================================================================
//	フィールドOBJ アニメID
//==============================================================================
//--------------------------------------------------------------
//	アニメID
//--------------------------------------------------------------
#define BLACT_ANMID_NORMAL_0	0x0000		///<ノーマルアニメ
#define BLACT_ANMID_HERO_0		0x0001		///<自機用アニメ
#define BLACT_ANMID_SEED		0x0002		///<木の実アニメ
#define BLACT_ANMID_HEROCYCLE_0	0x0003		///<自機自転車アニメ
#define BLACT_ANMID_SPHERO		0x0004
#define BLACT_ANMID_WATERHERO	0x0005
#define BLACT_ANMID_SWIMHERO	0x0006
#define BLACT_ANMID_BIRD		0x0007
#define BLACT_ANMID_SPPOKE		0x0008
#define BLACT_ANMID_CONTESTHERO	0x0009
#define BLACT_ANMID_FISHINGHERO	0x000a
#define BLACT_ANMID_PCWOMAN		0x000b
#define BLACT_ANMID_KOIKING		0x000c
#define BLACT_ANMID_POKEHERO	0x000d
#define BLACT_ANMID_SAVEHERO	0x000e
#define BLACT_ANMID_BANZAIHERO	0x000f
#define BLACT_ANMID_SPPOKE6		0x0010
#define BLACT_ANMID_SPPOKE7		0x0011
#define BLACT_ANMID_SPPOKE9		0x0012
#define BLACT_ANMID_SPPOKE10	0x0013
#define BLACT_ANMID_SPPOKE11	0x0014

#define BLACT_ANMID_MAX			0xffff		///<アニメID最大

#endif //FIELD_OBJ_CODE_H_FILE
