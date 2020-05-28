//============================================================================================
/**
 * @file	field_camera.h
 * @bfief	フィールドカメラ
 * @author	GAME FREAK inc.
 */
//============================================================================================

extern void FieldCameraInit(const VecFx32 *inTarget,
							FIELDSYS_WORK * repw,
							const int AreaCamera,
							const BOOL inDelayFlg);

extern void FieldCameraEnd(FIELDSYS_WORK * repw);
