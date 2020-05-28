//============================================================================================
/**
 * @file	field_3d_anime.h
 * @brief   フィールド3Dアニメーション関連処理
 * @author	nozomu saito
 * @date	2006.02.13
 */
//============================================================================================
#ifndef _FIELD_3D_ANIME_H_
#define _FIELD_3D_ANIME_H_

#include "field_common.h"


#define FLD_3D_ANIME_MAX	(16)		//フィールドで同時に動くアニメの数

#define LOOP_INFINIT		(-1)
/**
enum{
	FLD_3D_ANIME_NON = 0,		//アニメなし
	FLD_3D_ANIME_STATION,		//常駐アニメ
	FLD_3D_ANIME_NO_STATION,	//非常駐アニメ
	FLD_3D_ANIME_STATION_SUB,	//条件発動常駐アニメ
};
*/
#define F3DA_CONDITIONAL			(1)
#define F3DA_NO_CONDITIONAL			(0)

#define F3DA_ADD_CONDITIONAL	(0x01)	//条件あり追加
#define F3DA_SET_CONDITIONAL	(0x02)	//条件ありセット

//常駐アニメ（ADD、SETに条件はなし）
#define FLD_3D_ANIME_STATION	(0)
//条件つきアニメ（ADD、SETに条件あり）
#define FLD_3D_ANIME_ALL_COND	(F3DA_ADD_CONDITIONAL|F3DA_SET_CONDITIONAL)
//SET時のみ条件があるアニメ(ADDは条件無し)
#define FLD_3D_ANIME_SET_COND	(F3DA_SET_CONDITIONAL)

typedef struct FLD_3D_ANIME_MANAGER_tag*	FLD_3D_ANM_MNG_PTR;
typedef struct FLD_3D_ANIME_DATA_tag*	FLD_3D_ANM_DAT_PTR;
typedef struct FLD_3D_ANIME_DATA_tag const *	FLD_3D_ANM_DAT_CONST_PTR;
///typedef struct ANIME_3D_WORK_tag*	ANIME_3D_WORK_PTR;

typedef struct ANIME_CONT_MNG_tag*	ANIME_CONT_MNG_PTR;
typedef struct ANIME_CONT_tag*	ANIME_CONT_PTR;

extern int F3DA_GetFld3DAnimeCode(	const int inFld3DObjCode,
									const int inAnimeNo/*, const struct list*/);

extern FLD_3D_ANM_MNG_PTR F3DA_Field3DAnimeInit(void);
extern FLD_3D_ANM_DAT_PTR	F3DA_AddField3DAnime(	const int inObjCode,
													const int inAnimeNo,
													const int inLoopCount,
													const int inCode,
													const BOOL inReverse,
													const BOOL inStopFlg,
													const BOOL inConditional,
													NNSG3dResMdl *objectmodel,
													NNSG3dResTex	*pTex,
													FLD_3D_ANM_MNG_PTR field_3d_anime_ptr	);
extern void F3DA_AddField3DAnimeEasy(	const int inObjCode,
										NNSG3dResMdl *objectmodel,
										NNSG3dResTex	*pTex,
										FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern BOOL F3DA_SetFld3DAnime(	const int inObjID,
								const int inAnimeNo,
								const BOOL inConditional,
								NNSG3dRenderObj *objectdata,
								FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern BOOL F3DA_SetFld3DAnimeEasy(	const int inObjID,
									NNSG3dRenderObj *objectdata,
									FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void RereaseFld3DAnimeAll(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void RereaseFld3DAnimeByIdx(const u8 inIdx, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void F3DA_RemoveFld3DAnime(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
									NNSG3dRenderObj *inRenderObj,
									const int inObjCode,
									const int inAnimeNo	);
extern void F3DA_RereaseFld3DAnime(	FLD_3D_ANM_DAT_PTR outAnimePtr,
									FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void FreeFld3DAnimeManager(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByIdx(const int inIndex,
											FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void F3DA_Main(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);

extern FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtrByCode(const int inCode,
													FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern FLD_3D_ANM_DAT_PTR F3DA_GetFld3DAnmPtr(	const int inObjID, const int inAnimeNo,
												FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void F3DA_SetStopFlgByIdx(const u8 inIdx, const BOOL inFlg, FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern void F3DA_SetStopFlg(FLD_3D_ANM_DAT_PTR inAnimePtr, const BOOL inFlg);
extern void F3DA_MoveAnime(FLD_3D_ANM_DAT_PTR inAnimePtr);
extern BOOL F3DA_IsLastFrame(FLD_3D_ANM_DAT_PTR	inAnimeData);
extern BOOL F3DA_IsAnimeEnd(const FLD_3D_ANM_DAT_PTR inAnimeData);
extern u16 F3DA_GetAnimeArcObjNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr);
extern const u8 F3DA_GetAnimeNum(FLD_3D_ANM_MNG_PTR field_3d_anime_ptr, const int inObjCode);
extern void F3DA_SetAnimeReverse(FLD_3D_ANM_DAT_PTR	outAnimeData);
extern void F3DA_SetAnimeReverseDirect(FLD_3D_ANM_DAT_PTR	outAnimeData, const BOOL inReverse);
extern void F3DA_SetAnimeLoopMax(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inLoopMax);
extern void F3DA_SetControlCode(FLD_3D_ANM_DAT_PTR	outAnimeData, const int inControlCode);
extern void F3DA_SetStartFrame(FLD_3D_ANM_DAT_PTR	outAnimeData);
extern void F3DA_SetLastFrame(FLD_3D_ANM_DAT_PTR	outAnimeData);
extern void F3DA_ChangeFrame(FLD_3D_ANM_DAT_PTR	outAnimeData);
extern ANIME_CONT_MNG_PTR F3DASub_InitField3DAnimeCont(void);
extern void F3DASub_FreeAnimeContManager(ANIME_CONT_MNG_PTR *outAnimeContMng);

extern void F3DASub_SetUpAnimation(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
									const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID,
									const int inObjID,
									NNSG3dRenderObj *inRenderObj,
									NNSG3dResMdl 	*inObjectModel,
									NNSG3dResTex *inTex,
									const int inAnimeNum,
									const u8 inLoop,
									const BOOL inReverse);
extern void F3DASub_EntryRenderObj(	const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID,
									const u8 inEntryIndex,
									NNSG3dRenderObj *inRenderObj);

extern void F3DASub_StartAnimation(	const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID,
									const int inAnimeNo);

extern void F3DASub_StartAnimeSnd(	const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID,
									const int inAnimeNo,
									const int inSound);
extern void F3DASub_BindAnimation( const ANIME_CONT_MNG_PTR inAnimeContMng,
									const int inEntryID,
									const int inAnimeNo);
extern void F3DASub_SetStopFlg( const ANIME_CONT_MNG_PTR inAnimeContMng,
								const int inEntryID,
								const int inAnimeNo,
								const BOOL inFlg);
extern void F3DASub_RereaseAnimation(	FLD_3D_ANM_MNG_PTR field_3d_anime_ptr,
										ANIME_CONT_MNG_PTR inAnimeContMng,
										const int inEntryID	);

extern FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
													const int inEntryID,
													const int inAnimeNo	);
extern FLD_3D_ANM_DAT_PTR F3DASub_GetFld3DBindAnmPtr(	const ANIME_CONT_MNG_PTR inAnimeContMng,
														const int inEntryID	);
extern const BOOL F3DASub_WaitAnimation(const ANIME_CONT_MNG_PTR inAnimeContMng,
										const int inEntryID);
extern const int F3DASub_GetObjIDFromEntryID(	const ANIME_CONT_MNG_PTR inAnimeContMng,
												const int inEntryID);
#endif //_FIELD_3D_ANIME_H_


