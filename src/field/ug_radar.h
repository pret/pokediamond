//===========================================================================
/**
 *
 *@file		ug_radar.h
 *@brief	�Y�z���[�_�[�����i�T�u��ʁj�w�b�_�t�@�C��
 *@author	Akito Mori
 *@data		2005.09.23
 *
 */
//===========================================================================
#ifndef _UG_RADAR_DEF_H_
#define _UG_RADAR_DEF_H_


typedef struct UG_RADAR_WORK	UG_RADAR_WORK;


extern UG_RADAR_WORK *UnderGround_RadarInit( FIELDSYS_WORK *fsys );
extern void UnderGround_RadarEnd(UG_RADAR_WORK *urw);

#endif