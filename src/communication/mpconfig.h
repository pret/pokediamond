#ifndef ___MPCONFIG_H___
#define ___MPCONFIG_H___
/**
 * @version "$Id: mpconfig.h,v 1.1 2006/05/02 03:09:56 mitsuhara Exp $"
 *
 * @file mpconfig.h
 * @brief MP無線通信ライブラリ コンフィグレーション定義
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif

/* MP通信で使用するDMA番号 */  
#define		MP_DMA_NO			(2)	// GX等のDMA番号と重ならないよう注意

/* 使用ポート */ 
#define		MP_DEFAULT_PORT			(4)	// ポート番号( 4～7 )

/* ポートプライオリティ */
#define		MP_DEFAULT_PORT_PRIO		(2)	// ポートの優先度( 0～3 )

/* ビーコン間隔 */
#define		MP_DEFAULT_BEACON_PERIOD	(200)
  
/* MP通信用GGID */  
#define		MP_GGID				(0x00000178)

/* 最大接続子機数 */  
#define		MP_CONNECT_CHILD_MAX		(9)

/* 親機送信データサイズ */  
#define		MP_PARENT_DATA_SIZE		(64)  

/* 子機送信データサイズ */
#define		MP_CHILD_DATA_SIZE		(64)  

  
#define		MP_SEND_DATA_SIZE		(64)  
  
/* 子機の最大検索親機数 */
#define		MP_SIZE_RECEIVE_MP_PARENT_LIST	(8)

/* 親機の最大接続子機数 */
#define		MP_SIZE_RECEIVE_MP_CHILD_LIST	MP_SIZE_RECEIVE_MP_PARENT_LIST

  
/*  */
#define		MP_NUM_RECEIVE_MP_RETRY		(28)


/* 電波使用率計測時の計測時間（ms） */
#define		MP_MEASURE_TIME			(30)

/* 電波使用率計測動作モード */
#define		MP_MEASURE_MODE			(3)	/* キャリアセンスとED値の論理和 */
  
/* 電波使用率計測時の電波強度下限 */  
#define		MP_MEASURE_ED_THRESHOLD		(17)

  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___MPCONFIG_H___
