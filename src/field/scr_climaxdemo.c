//============================================================================================
/**
 * @file	scr_climaxdemo.c
 * @bfief	スクリプトコマンド用:テンガンザン山頂デモ呼び出し
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.01
 *
 */
//============================================================================================
#include "common.h"

#include "fieldsys.h"
#include "fieldmap_func.h"
#include "camera.h"
#include "field_demo.h"

#include "scr_climaxdemo.h"
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

static FLDMAPFUNC_WORK * ClimaxDemoWork;

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
BOOL ClimaxDemoCall(FIELDSYS_WORK * fsys, int demo_id)
{
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	switch (demo_id) {
	case CLIMAX_DEMO_LEGENDPOKE_START:
		ClimaxDemoWork = FLDMAP_DEMO_LegendPokeApp_Start(fsys);
		break;

	case CLIMAX_DEMO_LEGENDPOKE_ENDCHK:
		if (FLDMAP_DEMO_LegendPokeApp_EndCheck(ClimaxDemoWork)) {
			FLDMAP_DEMO_LegendPokeApp_End(ClimaxDemoWork);
			return 1;
		} else {
			return 0;
		}
		break;

	case CLIMAX_DEMO_BLACKRING_START:
		ClimaxDemoWork = FLDMAP_DEMO_BlackRing_Start(fsys);
		break;

	case CLIMAX_DEMO_BLACKRING_END:
		FLDMAP_DEMO_BlackRing_End(ClimaxDemoWork);
		break;

	case CLIMAX_DEMO_GINGA_START:
		ClimaxDemoWork = FLDMAP_DEMO_Ginga_Start(fsys);
		break;

	case CLIMAX_DEMO_GINGA_ENDREQ:
		FLDMAP_DEMO_Ginga_EndReq(ClimaxDemoWork);
		break;

	case CLIMAX_DEMO_GINGA_ENDCHK:
		if (FLDMAP_DEMO_Ginga_GetState(ClimaxDemoWork) == FLDMAP_DEMO_GINGA_SEQ_END) {
			FLDMAP_DEMO_Ginga_End(ClimaxDemoWork);
			return 1;
		} else {
			return 0;
		}
		break;

	case CLIMAX_DEMO_ANTEGG_00:
		ClimaxDemoWork = FLDMAP_DEMO_AntEgg_Start(fsys, FLDMAP_DEMO_ANTEGG_CUT00);
		break;

	case CLIMAX_DEMO_ANTEGG_01:
		ClimaxDemoWork = FLDMAP_DEMO_AntEgg_Start(fsys, FLDMAP_DEMO_ANTEGG_CUT01);
		break;

	case CLIMAX_DEMO_ANTEGG_02:
		ClimaxDemoWork = FLDMAP_DEMO_AntEgg_Start(fsys, FLDMAP_DEMO_ANTEGG_CUT02);
		break;

	default:
		GF_ASSERT(0);
	}
	return 0;
}
