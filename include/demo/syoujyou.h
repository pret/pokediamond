FS_EXTERN_OVERLAY(syoujyou);

extern PROC_RESULT Syoujyou_Init( PROC * proc, int * seq );
extern PROC_RESULT Syoujyou_Main( PROC * proc, int * seq );
extern PROC_RESULT Syoujyou_Exit( PROC * proc, int * seq );

// �^�C�v
enum {
	SYOUJYOU_TYPE_SINOU = 0,
	SYOUJYOU_TYPE_ZENKOKU,
};

//----------------------------------
//�^�錾
//----------------------------------
///�����\����
typedef struct SYOUJYOU_INI_tag
{
	SAVEDATA*	savedata;
	int			type; 

}SYOUJYOU_INI;

