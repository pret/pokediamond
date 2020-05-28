/**
 *	@brief	ポルトリスト BMPメニューコントロール
 */

#ifndef __H_PORUCASE_BMP_H__
#define __H_PORUCASE_BMP_H__

typedef enum{
 MLIST_PUT,
 MLIST_DEL,
 MLIST_EXIT,
 MLIST_MAX
};

/**
 *	@brief	ポルトリストメニュー作成
 */
extern void PoruList_CreatePMenu(PORU_CASE_WORK* wk);
/**
 *	@brief	ポルトリスト　メニューリスト削除
 */
extern void PoruList_DeletePMenu(PORU_CASE_WORK* wk,BOOL trans);

/**
 *	@brief	ポルトボタンプッシュ時処理
 */
extern void PoruBtn_StateSet(PORU_CASE_WORK* wk,u8 idx,u8 state);

/**
 *	@brief	ポルトリストソート
 */
extern void PoruList_SortMenu(PORU_CASE_WORK* wk,u8 mode);

/**
 *	@brief	メニューリスト作成
 */
extern void MenuList_Create(PORU_CASE_WORK* wk);

/**
 *	@brief	メニューリスト削除
 */
extern void MenuList_Delete(PORU_CASE_WORK* wk);

/**
 *	@brief	YesNoウィンドウ描画前メッセージ表示
 */
extern void YesNoList_StartMsgSet(PORU_CASE_WORK* wk);
/**
 *	@brief	ポルトを捨てますメッセージセット
 */
extern void YesNoList_DelMsgSet(PORU_CASE_WORK* wk);

/**
 *	@brief	YesNoウィンドウ初期化
 */
extern void YesNoList_Create(PORU_CASE_WORK* wk);

/**
 *	@brief	初期画面描画メッセージセット
 */
extern void PoruCase_DrawInitialMsg(PORU_CASE_WORK* wk);

#endif	//__H_PORUCASE_BMP_H__
