
#ifndef	__CUSTOM_BALL_H__
#define	__CUSTOM_BALL_H__

#include "system/savedata_def.h"


// �Ƃ肠�����A�Z�[�u�̈�fix�̂��ߕK�v�Ȃ��̂��`��
#define CB_DEF_SEAL_MAX				(8)			///< �\��閇��
#define CB_DEF_CORE_MAX				(12)		///< �J�X�^���{�[���̐�
#define CB_DEF_ITEM_DATA_NUM_MAX	(80)		///< �V�[���̎��
#define CB_DEF_ITEM_DATA_NUM		(80 + 1)	//(80)		///< �V�[���̎��
#define CB_DEF_SEAL_STOCK_MAX		(99)		///< �V�[���ő吔

#define CB_DEF_INDEX_ORIGIN			(1)			///< index �̊J�n (0 = �� �ň����̂� 1 ����)


enum {
	CB_ENUM_SEAL_ID_000 = 0,	///< �������Ă��Ȃ�
	CB_ENUM_SEAL_ID_001,
};
#define CB_DEF_SEAL_NONE	(CB_ENUM_SEAL_ID_000)		///< �V�[���������Ă��Ȃ�


///< custom
typedef struct _CUSTOM_BALL_SEAL		CB_SEAL;		///< �V�[���̃f�[�^
typedef struct _CUSTOM_BALL_CORE		CB_CORE;		///< �J�X�^���{�[���̃f�[�^

///< item
typedef struct _CUSTOM_BALL_ITEM_DATA	CB_ITEM_DATA;	///< �A�C�e���f�[�^

///< save
typedef struct _CUSTOM_BALL_SAVE_DATA	CB_SAVE_DATA;	///< �Z�[�u�f�[�^ custom/core �܂�


// -----------------------------------------
//
//	�� �V�[���̃f�[�^
//
// -----------------------------------------
struct _CUSTOM_BALL_SEAL {
	
	u8	seal_id;		///< �V�[���ԍ�
	u8	x;				///< x ���W
	u8	y;				///< y ���W
	
};


// -----------------------------------------
//
//	�� �J�X�^���{�[���̃f�[�^(�|�P�����̎莝�����ێ�)
//
// -----------------------------------------
struct _CUSTOM_BALL_CORE {

	CB_SEAL	cb_seal[ CB_DEF_SEAL_MAX ];

};

#if 0
///< item
struct _CUSTOM_BALL_ITEM_DATA {
	
	u8	seal[ CB_DEF_ITEM_DATA_NUM ];
	
};


///< save
struct _CUSTOM_BALL_SAVE_DATA {
	
	CB_CORE			cb_core[ CB_DEF_CORE_MAX ];

	CB_ITEM_DATA	cb_item;
	
};
#endif

// =============================================================================
//
//
//	���֐�
//
//
// =============================================================================
extern int				CustomBall_GetWorkSize(void);								///< �Z�[�u�̈�̃T�C�Y���擾
extern CB_SAVE_DATA*	CustomBall_AllocSaveData(u32 heap_id);						///< �Z�[�u�̈���m��
extern void				CustomBall_Init(CB_SAVE_DATA* csd);							///< ����������


///< �A�N�Z�X�֐� --- custom
extern CB_SAVE_DATA*	CB_SaveData_AllDataGet(SAVEDATA* sv);						///< �Z�[�u�f�[�^���擾����

extern CB_CORE*			CB_SaveData_CoreDataGet(CB_SAVE_DATA* save, int no);
extern void				CB_SaveData_CoreDataSet(CB_SAVE_DATA* save, CB_CORE* core, int no);

extern CB_SEAL*			CB_SaveData_SealDataGet(CB_CORE* core, int no);
extern void				CB_SaveData_SealDataSet(CB_CORE* core, CB_SEAL* seal, int no);

extern u8				CB_SaveData_SealIDGet(const CB_SEAL* seal);						///< �w�肳�ꂽ�V�[����ID���擾
extern void				CB_SaveData_SealIDSet(CB_SEAL* seal, u8 id);					///< �w�肳�ꂽ�V�[����ID��ݒ�

extern u8				CB_SaveData_SealPXGet(const CB_SEAL* seal);						///< �w�肳�ꂽ�V�[����X���擾
extern void				CB_SaveData_SealPXSet(CB_SEAL* seal, u8 id);					///< �w�肳�ꂽ�V�[����X��ݒ�

extern u8				CB_SaveData_SealPYGet(const CB_SEAL* seal);						///< �w�肳�ꂽ�V�[����Y���擾
extern void				CB_SaveData_SealPYSet(CB_SEAL* seal, u8 id);					///< �w�肳�ꂽ�V�[����Y��ݒ�


///< �A�N�Z�X�֐� --- item
extern CB_ITEM_DATA*	CB_SaveData_ItemDataGet(CB_SAVE_DATA* save);					///< �A�C�e���f�[�^�S��

extern u8				CB_SaveData_ItemTypeGet(const CB_ITEM_DATA* save, int no);		///< �A�C�e���^�C�v�擾
extern void				CB_SaveData_ItemTypeSet(CB_ITEM_DATA* save, int no, int type);	///< �A�C�e���^�C�v�ݒ�

extern u8				CB_SaveData_ItemNumGet(const CB_ITEM_DATA* save, int no);		///< �A�C�e�����擾
extern u8				CB_SaveData_ItemNumGet_CBO(const CB_ITEM_DATA* item, int no);	///< �A�C�e�����擾
extern void				CB_SaveData_ItemNumSet(CB_ITEM_DATA* save, int no, int stock);	///< �A�C�e�����ݒ�
extern void				CB_SaveData_ItemNumAdd(CB_ITEM_DATA* save, int no, s16 stock);	///< �A�C�e��������

extern BOOL				CB_SaveData_ItemNumAddCheck(CB_SAVE_DATA* save, int no, s16 stock);	///< �A�C�e��������
extern BOOL				CB_SaveData_ItemNumAddCheck_CBO(CB_SAVE_DATA* save, int no, s16 stock);
extern BOOL				CB_SaveData_IsAddIt(CB_SAVE_DATA* save, int no, s16 stock);			///< �A�C�e���������`�F�b�N�̂�


///< �c�[���n
extern void CB_Tool_SaveData_Copy(const CB_SAVE_DATA* from, CB_SAVE_DATA* to);
extern void CB_Tool_CoreData_Copy(const CB_CORE* from, CB_CORE* to);
extern void CB_Tool_SealData_Copy(const CB_SEAL* from, CB_SEAL* to);

extern BOOL CB_Tool_IsSeal(const CB_SAVE_DATA* save, int id);
extern BOOL CB_Tool_IsSealCore(const CB_CORE* cb_core, int id);
extern int CB_Tool_IsSealTotalNum(const CB_SAVE_DATA* save, int id);
extern int CB_Tool_SealCllectionGet(const CB_SAVE_DATA* save);
extern int CB_Tool_SealTotalNumGet(const CB_SAVE_DATA* save, int id);

#ifdef PM_DEBUG

#include "include/poketool/poke_tool.h"

///< �f�o�b�O�֐�
enum {
	DEBUG_CB_MODE_CLEAR,			///< ����
	DEBUG_CB_MODE_ITEM_FULL = 1,	///< �A�C�e���ő�
	DEBUG_CB_MODE_ITEM_RANDOM,		///< �K���ȃV�[����p��
};

extern void Debug_CB_Set(POKEMON_PARAM* pp);
extern void Debug_CB_SaveData_Sample(CB_SAVE_DATA* save, int mode);
extern void Debug_CB_SaveData_Poke_Sample(SAVEDATA * save, int mode);
#endif

#endif

