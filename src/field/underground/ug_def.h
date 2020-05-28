//=============================================================================
/**
 * @file	ug_def.h
 * @brief	地下とイベントとの橋渡しの定義が書いてある
 * @author	Katsumi Ohno
 * @date    2006.2.28
 */
//=============================================================================

#ifndef _UG_DEF_H_
#define _UG_DEF_H_

#define UG_SHOP_GOODS     (0)     // グッズ親父
#define UG_SHOP_TRAP      (1)     // トラップ親父
#define UG_SHOP_TREASURE  (2)     // たから親父

// ShopMenuFuncAndCheckが返す値 この他の値はわな番号かグッズ番号

#define UG_SHOP_CARAT_SMALL (0xfffb)     // 大きさが小さい場合
#define UG_SHOP_BAG_FULL    (0xfffc)     // バッグがいっぱいの場合
#define UG_SHOP_MISS_SELECT (0xfffd)  // 選択したタマが異なる場合
#define UG_SHOP_NONE        (0xfffe)         // 選択中
#define UG_SHOP_CANCEL      (0xffff)        // キャンセル


// レーダーユニット表示範囲  ここ以外の場所は秘密基地
#define RADAR_SCOPE_XS (32)
#define RADAR_SCOPE_ZS (64)
#define RADAR_SCOPE_XE (479)
#define RADAR_SCOPE_ZE (479)


#endif // _UG_DEF_H_

