//==============================================================================
/**
 * @file	fieldobj_header.h
 * @brief	フィールドオブジェクトヘッダー構造体定義ヘッダー
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FIELD_OBJ_HEADER_FILE
#define FIELD_OBJ_HEADER_FILE

//==============================================================================
//	typedef strcut
//==============================================================================
//--------------------------------------------------------------
//	デバッグ
//--------------------------------------------------------------

//--------------------------------------------------------------
//	FIELD_OBJ 動作、描画関数ワークサイズ (byte size)
//--------------------------------------------------------------
#define FLDOBJ_MOVE_WORK_SIZE		(16)					///<動作関数用ワークサイズ
#define FLDOBJ_MOVE_SUB_WORK_SIZE	(16)					///<動作サブ関数用ワークサイズ
#define FLDOBJ_MOVE_CMD_WORK_SIZE	(16)					///<動作コマンド用ワークサイズ
#define FLDOBJ_DRAW_WORK_SIZE		(32)					///<描画関数用ワークサイズ

//--------------------------------------------------------------
//	型定義
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_H FIELD_OBJ_H;
typedef struct _TAG_FIELD_OBJ_SAVE_DATA * FIELD_OBJ_SAVE_DATA_PTR;

//--------------------------------------------------------------
///	FIELD_OBJ_H構造体
//--------------------------------------------------------------
struct _TAG_FIELD_OBJ_H
{
	unsigned short id;										///<識別ID
	unsigned short obj_code;								///<表示するOBJコード
	unsigned short move_code;								///<動作コード
	unsigned short event_type;								///<イベントタイプ
	unsigned short event_flag;								///<イベントフラグ
	unsigned short event_id;								///<イベントID
	short dir;												///<指定方向
	unsigned short param0;									///<指定パラメタ 0
	unsigned short param1;									///<指定パラメタ 1
	unsigned short param2;									///<指定パラメタ 2
	short move_limit_x;										///<X方向移動制限
	short move_limit_z;										///<Z方向移動制限
	unsigned short gx;										///<グリッドX
	unsigned short gz;										///<グリッドZ
	int gy;													///<Y値 fx32型
};

#define FIELD_OBJ_H_SIZE (sizeof(FIELD_OBJ_H))				///<FIELD_OBJ_Hサイズ

//--------------------------------------------------------------
///	FIELD_OBJ_SAVE_DATA構造体
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SAVE_DATA
{
	u32 status_bit;											///<ステータスビット
	u32 move_bit;											///<動作ビット
	u8 obj_id;												///<OBJ ID
	u8 move_code;											///<動作コード
	s8 move_limit_x;										///<X方向移動制限
	s8 move_limit_z;										///<Z方向移動制限
	s8 dir_head;											///<FIELD_OBJ_H指定方向
	s8 dir_disp;											///<現在向いている方向
	s8 dir_move;											///<現在動いている方向
	u8 dummy;												///<ダミー
	u16 zone_id;											///<ゾーン ID
	u16 obj_code;											///<OBJコード
	u16 event_type;											///<イベントタイプ
	u16 event_flag;											///<イベントフラグ
	u16 event_id;											///<イベントID
	s16 param0;												///<ヘッダ指定パラメタ
	s16 param1;												///<ヘッダ指定パラメタ
	s16 param2;												///<ヘッダ指定パラメタ
	s16 gx_init;											///<初期グリッドX
	s16 gy_init;											///<初期グリッドY
	s16 gz_init;											///<初期グリッドZ
	s16 gx_now;												///<現在グリッドX
	s16 gy_now;												///<現在グリッドY
	s16 gz_now;												///<現在グリッドZ
	fx32 fx32_y;											///<fx32型の高さ値
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<動作関数用ワーク
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<動作サブ関数用ワーク
}FIELD_OBJ_SAVE_DATA;

#define FIELD_OBJ_SAVE_DATA_SIZE (sizeof(FIELD_OBJ_SAVE_DATA))	///<FIELD_OBJ_SAVE_DATA size

//--------------------------------------------------------------
///	FIELD_OBJ_SAVE_DATA構造体 old
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_SAVE_DATA_OLD
{
	u32 status_bit;											///<ステータスビット
	u32 move_bit;											///<動作ビット
	u32 obj_id;												///<OBJ ID
	u32 zone_id;											///<ゾーン ID
	u32 obj_code;											///<OBJコード
	u32 move_code;											///<動作コード
	u32 event_type;											///<イベントタイプ
	u32 event_flag;											///<イベントフラグ
	u32 event_id;											///<イベントID
	int dir_head;											///<FIELD_OBJ_H指定方向
	int dir_disp;											///<現在向いている方向
	int dir_move;											///<現在動いている方向
	int param0;												///<ヘッダ指定パラメタ
	int param1;												///<ヘッダ指定パラメタ
	int param2;												///<ヘッダ指定パラメタ
	int move_limit_x;										///<X方向移動制限
	int move_limit_z;										///<Z方向移動制限
	int gx_init;											///<初期グリッドX
	int gy_init;											///<初期グリッドY
	int gz_init;											///<初期グリッドZ
	int gx_now;												///<現在グリッドX
	int gy_now;												///<現在グリッドY
	int gz_now;												///<現在グリッドZ
	u8 move_proc_work[FLDOBJ_MOVE_WORK_SIZE];				///<動作関数用ワーク
	u8 move_sub_proc_work[FLDOBJ_MOVE_SUB_WORK_SIZE];		///<動作サブ関数用ワーク
}FIELD_OBJ_SAVE_DATA_OLD;

#define FIELD_OBJ_SAVE_DATA_OLD_SIZE (sizeof(FIELD_OBJ_SAVE_DATA_OLD))

#endif //FIELD_OBJ_HEADER_FILE
