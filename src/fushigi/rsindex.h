// RS�̓C���f�b�N�X�ɑΉ����Ă��Ȃ��̂�
#define RSINDEX_POKENUM 564
#define RSINDEX_POKEINDEX 568
#define RSINDEX_FLDSIZE 15040
#define RSINDEX_MYDATASIZE 2192
#define RSINDEX_ZUKANBLOCK 24
#define RSINDEX_SEEFLAG2 2360
#define RSINDEX_SEEFLAG3 14988
#define RSINDEX_EXTRAFLAG 12591
#define RSINDEX_SAVESTATEFLAG 9
#define RSINDEX_EVENTFLAG 4640


#define USRFLAG_START		0
#define USRFLAG_MAX			2048				/* �X�N���v�g��`�̃t���O�ő吔 */
#define USRFLAG_AREA_MAX	(USRFLAG_MAX/8)

#define SYSFLAG_START		(USRFLAG_MAX)
#define	SYSFLAG_MAX			192					/* �V�X�e����`�̃t���O�ő吔 */
#define	SYSFLAG_AREA_MAX	(SYSFLAG_MAX/8)

#define TIMEFLAG_START		(USRFLAG_MAX+SYSFLAG_MAX)
#define TIMEFLAG_MAX		64					/* ���Ԍo�߃C�x���g�p�t���O�ő吔*/
#define	TIMEFLAG_AREA_MAX	(TIMEFLAG_MAX/8)

#define FRLG_SYSFLAG_START_OTHERS (SYSFLAG_START+40)
#define FRLG_SYS_ZUKAN_GET (FRLG_SYSFLAG_START_OTHERS+1)	//��������������



typedef struct {
		s8 div_id;
		s8 map_id;
		s8 exit_id;
		s16 x;
		s16 y;
} MapID;

