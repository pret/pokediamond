#ifndef	__EVBTYPE_H__
#define	__EVBTYPE_H__

//BG話かけデータ構造体
typedef struct{
	unsigned short	id;			//スクリプトID
	unsigned short	type;			//イベントタイプ
	unsigned short	gx;			//グリッド座標X
	unsigned short	gz;			//グリッド座標Z
	unsigned short	height;		//高さ
	unsigned short	dir;			//話しかけ方向タイプ	←今回追加
}BG_TALK_DATA;

#define SCRID_NULL 0

#endif	/* __EVBTYPE_H__ */
