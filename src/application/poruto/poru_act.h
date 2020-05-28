/**
 *	@brief	ポルトケースアクター系
 */

#ifndef __H_PORU_ACT_H__
#define __H_PORU_ACT_H__

extern void PoruCase_ActorInit(PORU_CASE_WORK *wk);
extern void PoruCase_ActorRelease(PORU_CASE_WORK *wk);
extern void PoruCase_ActorMain(PORU_CASE_WORK *wk);
extern void PoruCase_ActorTrans(PORU_CASE_WORK* wk);

#define NORMAL_ACTMAX	(3)
#define FMARK_ACTMAX	(5)
#define BUTTON_ACTMAX	(6)

typedef enum{
 NACT_CURSOR,
 NACT_UP,
 NACT_DOWN,
};

#define PORUCASE_ACTMAX	( \
 NORMAL_ACTMAX + \
 FMARK_ACTMAX + \
 BUTTON_ACTMAX \
)

#define NACT_CUR_PX	(105)
#define NACT_CUR_PY	(39)
#define NACT_CUR_SY	(16)
#define NACT_UP_PX	(80)
#define NACT_DOWN_PX	(80)
#define NACT_UP_PY	(18)
#define NACT_DOWN_PY	(140)

#define NACT_CUR_PALF	(0)
#define NACT_CUR_PALT	(9)

typedef enum{
 BACT_ST_NULL,
 BACT_ST_01,
 BACT_ST_02,
 BACT_ST_03,
 BACT_ST_INI_PUSH,
 BACT_ST_INI = 0xFFFF,
 BACT_PTN = 3,
};

///アクターコントロール系サブ関数
extern void NAct_CursorChg(PORU_CASE_WORK* wk,BOOL mode);

#endif	//__H_PORU_ACT_H__
