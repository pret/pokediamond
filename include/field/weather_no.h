//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weatheru_no.h
 *@brief	���V�C	�i���o�[
 *@author	tomoya takahashi
 *@data		2006.06.08
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#ifndef __WEATHER_NO_H__
#define	__WEATHER_NO_H__

//-------------------------------------
//	�V�C�f�[�^��	(no)
//
//	���@�V��i���o�[��
//=====================================
enum{
	WEATHER_SYS_SUNNY,			// ����
	WEATHER_SYS_CLOUDINESS,		// �܂�		BG	
	WEATHER_SYS_RAIN,			// �J		OAM	FOG
	WEATHER_SYS_STRAIN,			// ��J		OAM FOG 
	WEATHER_SYS_SPARK,			// ��J		OAM FOG BG
	WEATHER_SYS_SNOW,			// ��		OAM FOG
	WEATHER_SYS_SNOWSTORM,		// ����		OAM FOG
	WEATHER_SYS_SNOWSTORM_H,	// �Ґ���	OAM FOG BG
	WEATHER_SYS_FOG,			// ����		FOG	
	WEATHER_SYS_VOLCANO,		// �ΎR�D	OAM FOG BG
	WEATHER_SYS_SANDSTORM,		// BG�g�p����	OAM FOG BG
	WEATHER_SYS_DIAMONDDUST,	// �X�m�[�_�X�g	OAM FOG
	WEATHER_SYS_SPIRIT,			// �C��		OAM
	WEATHER_SYS_MYSTIC,			// �_��		OAM FOG
	WEATHER_SYS_MIST1,			// �������̖�	FOG	BG
	WEATHER_SYS_MIST2,			// �������̖�	FOG	BG
	WEATHER_SYS_FLASH,			// �t���b�V��		BG

	WEATHER_SYS_SPARK_EFF,		// ��		BG
	WEATHER_SYS_FOGS,			// ��		FOG
	WEATHER_SYS_FOGM,		// ����		FOG

// ����Ȃ��Ȃ�	
#if 1
	WEATHER_SYS_RAINBOW,	// ��		BG
	WEATHER_SYS_SNOW_STORM_BG,// BG�g�p����	OAM FOG BG
	WEATHER_SYS_STORM,		// ����		OAM FOG
#endif

	WEATHER_SYS_NUM,// �V�C��
};


#endif // __WEATHER_NO_H__
