//============================================================================================
/**
 * @file	ug_itemtype.h
 * @brief	地下アイテムタイプ用ヘッダ
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================

#ifndef __UG_ITEMTYPE_H__
#define __UG_ITEMTYPE_H__


// ほれる石の種類

#define STONE_TYPE_NONE    (0)
#define STONE_TYPE_DIAMOND (1)    //  こんごうだま
#define STONE_TYPE_PEARL   (2)      //  ましろだま
#define STONE_TYPE_RED     (3)        //  あかいいし
#define STONE_TYPE_BLUE    (4)       //  あおいいし
#define STONE_TYPE_GREEN   (5)      //  みどりのいし
#define STONE_TYPE_MAX     (6)

// 埋める種類
#define DIG_PARTS_NONE       (STONE_TYPE_NONE)
#define DIG_PARTS_KONGOU_S   (STONE_TYPE_DIAMOND)   //こんごうだま	KASEKI_KONGOU_S
#define DIG_PARTS_SIRATAMA_S (STONE_TYPE_PEARL) //しらたま	KASEKI_SIRATAMA_S
#define DIG_PARTS_RED_S      (STONE_TYPE_RED)        //赤いタマ
#define DIG_PARTS_BLUE_S     (STONE_TYPE_BLUE)       //青いタマ
#define DIG_PARTS_GREEN_S    (STONE_TYPE_GREEN)      //緑のタマ
#define DIG_PARTS_KONGOU_L   (6)  //だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_SIRATAMA_L (7) //だいしらたま	KASEKI_SIRATAMA_L
#define DIG_PARTS_RED_L      (8)//だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_BLUE_L     (9) //だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_GREEN_L    (10)//だいしらたま	KASEKI_SIRATAMA_L
#define DIG_PARTS_TREASURE_MIN   (11)
#define DIG_PARTS_CIRCLE   (DIG_PARTS_TREASURE_MIN)        //まんまる	KASEKI_
#define DIG_PARTS_KEYSTONE   (12)        //かなめ	KASEKI_
#define DIG_PARTS_SUN       (13) //たいようのいし	KASEKI_SUN
#define DIG_PARTS_STAR      (14) //ほしのかけら	KASEKI_STAR
#define DIG_PARTS_MOON      (15) //つきのいし	KASEKI_MOON
#define DIG_PARTS_HARD      (16) //かたいいし	KASEKI_HARD
#define DIG_PARTS_KAMINARI  (17) //かみなりのいし	KASEKI_KAMINARI
#define DIG_PARTS_KAWARAZU  (18) //かわらずのいし	KASEKI_KAWARAZU
#define DIG_PARTS_HONOO     (19) //ほのおのいし	KASEKI_HONOO
#define DIG_PARTS_MIZU      (20) //みずのいし	KASEKI_MIZU
#define DIG_PARTS_REAF      (21) //リーフのいし	KASEKI_REAF
#define DIG_PARTS_GOLD      (22) //きんのたま	KASEKI_GOLD
#define DIG_PARTS_KAI       (23) //かいのカセキ	KASEKI_KAI
#define DIG_PARTS_KOURA     (24) //こうらのカセキ	KASEKI_KOURA
#define DIG_PARTS_TSUME     (25) //ツメのカセキ	KASEKI_TSUME
#define DIG_PARTS_NEKKO     (26) //ねっこのカセキ	KASEKI_NEKKO
#define DIG_PARTS_KOHAKU    (27) //ひみつのコハク	KASEKI_KOHAKU
#define DIG_PARTS_BONE      (28) //ふといほね	KASEKI_BONE
#define DIG_PARTS_GENKI_S   (29)// 元気のかけら
#define DIG_PARTS_GENKI_L   (30)//げんきのかたまり
#define DIG_PARTS_PLA_RED   (31) //あかいかけら
#define DIG_PARTS_PLA_BLUE  (32) //あおいかけら
#define DIG_PARTS_PLA_YELLOW (33)  //きいろいかけら
#define DIG_PARTS_PLA_GREEN (34) //みどりのかけら
#define DIG_PARTS_HEART     (35) //ハートのウロコ
#define DIG_PARTS_SHIELD    (36) //たてのカセキ
#define DIG_PARTS_ZUGAI     (37) //ずがいのカセキ
#define DIG_PARTS_CRAY      (38)  //ひかりのねんど
#define DIG_PARTS_IRONBALL  (39)  //くろいてっきゅう
#define DIG_PARTS_COLD      (40) //つめたいいわ
#define DIG_PARTS_SARA      (41)  //さらさらいわ
#define DIG_PARTS_HEAT      (42)  //あついいわ
#define DIG_PARTS_WET       (43)   //しめったいわ
#define DIG_PARTS_PLATE_FIRE   (44)//ひのたまプレート
#define DIG_PARTS_PLATE_WATER  (45) //しずくプレート
#define DIG_PARTS_PLATE_THUNDER (46)  //いかづちプレート
#define DIG_PARTS_PLATE_GREEN  (47) //みどりのプレート
#define DIG_PARTS_PLATE_ICICLE  (48)  //つららのプレート
#define DIG_PARTS_PLATE_KNUCKLE (49)  //こぶしのプレート
#define DIG_PARTS_PLATE_POISON (50)  //もうどくプレート
#define DIG_PARTS_PLATE_GROUND (51)  //だいちのプレート
#define DIG_PARTS_PLATE_SKY    (52)  //あおぞらプレート
#define DIG_PARTS_PLATE_WONDER      (53)   //ふしぎのプレート
#define DIG_PARTS_PLATE_IRIDESCENCE (54)//たまむしプレート
#define DIG_PARTS_PLATE_ROCK        (55)//がんせきプレート
#define DIG_PARTS_PLATE_GHOST       (56)//もののけプレート
#define DIG_PARTS_PLATE_DRAGON      (57)//りゅうのプレート
#define DIG_PARTS_PLATE_DARK        (58)//こわもてプレート
#define DIG_PARTS_PLATE_IRON        (59)//こうてつプレート
#define DIG_PARTS_TREASURE_MAX     (60)
#define DIG_PARTS_NODIG1    (DIG_PARTS_TREASURE_MAX)     //掘れない岩	kaseki_iwa01	面積が４マス	棒形の真っ黒の石
#define DIG_PARTS_NODIG2   (61)    //掘れない岩	kaseki_iwa02	面積が４マス	四角型の真っ黒の石
#define DIG_PARTS_NODIG3   (62)    //掘れない岩	kaseki_iwa03	面積が４マス	T型の真っ黒の石
#define DIG_PARTS_NODIG4  (63)   //掘れない岩	kaseki_iwa04	面積が４マス	Z型の真っ黒の石
#define DIG_PARTS_NODIG5  (64)   //掘れない岩	kaseki_iwa05	面積が４マス	S型の真っ黒の石
#define DIG_PARTS_NODIG6  (65)   //掘れない岩	kaseki_iwa06	面積が９マス	四角型の真っ黒の石
#define DIG_PARTS_NODIG7  (66)   //掘れない岩	kaseki_iwa07	面積が８マス	棒形の真っ黒の石
#define DIG_PARTS_MAX     (67)
#define DIG_PARTS_TYPE_FOSSIL_MIN (DIG_PARTS_KAI)
#define DIG_PARTS_TYPE_FOSSIL_MAX (DIG_PARTS_BONE+1)


// 罠タイプ
#define UG_TRAPTYPE_NONE    (0)
#define UG_TRAPTYPE_DIR_UP  (1)
#define UG_TRAPTYPE_DIR_RIGHT   (2)
#define UG_TRAPTYPE_DIR_DOWN     (3)
#define UG_TRAPTYPE_DIR_LEFT   (4)
#define UG_TRAPTYPE_BIGDIR_UP    (5)
#define UG_TRAPTYPE_BIGDIR_RIGHT (6)
#define UG_TRAPTYPE_BIGDIR_DOWN   (7)
#define UG_TRAPTYPE_BIGDIR_LEFT   (8)
#define UG_TRAPTYPE_WARP   (9)
#define UG_TRAPTYPE_TELEPORT   (10)
#define UG_TRAPTYPE_HOLE   (11)
#define UG_TRAPTYPE_BIG_HOLE   (12)
#define UG_TRAPTYPE_REVERSE   (13)
#define UG_TRAPTYPE_GIDDY      (14)          // 混   乱
#define UG_TRAPTYPE_RUNNING   (15)
#define UG_TRAPTYPE_INVISIBLE   (16)
#define UG_TRAPTYPE_SLOW   (17)
#define UG_TRAPTYPE_SMOG      (18)    //    画面に霧
#define UG_TRAPTYPE_BIG_SMOG       (19)  // 画面に霧
#define UG_TRAPTYPE_ROCK   (20)
#define UG_TRAPTYPE_ROCKFALL   (21)
#define UG_TRAPTYPE_SUDS   (22)
#define UG_TRAPTYPE_BUBBLE   (23)
#define UG_TRAPTYPE_ALART1   (24)
#define UG_TRAPTYPE_ALART2   (25)
#define UG_TRAPTYPE_ALART3   (26)
#define UG_TRAPTYPE_ALART4   (27)
#define UG_TRAPTYPE_LEAF   (28)
#define UG_TRAPTYPE_DIRTY_BLOSSOMS  (29)
#define UG_TRAPTYPE_FIRE   (30)
#define UG_TRAPTYPE_BLAZE   (31)
#define UG_TRAPTYPE_RADAR   (32)
#define UG_TRAPTYPE_DRILL   (33)
#define UG_TRAPTYPE_MAX   (34)
   


#if 0
// ほれる石の種類
typedef enum{
  STONE_TYPE_NONE,
  STONE_TYPE_DIAMOND,    //  こんごうだま
  STONE_TYPE_PEARL,      //  ましろだま
  STONE_TYPE_RED,        //  あかいいし
  STONE_TYPE_BLUE,       //  あおいいし
  STONE_TYPE_GREEN,      //  みどりのいし
  STONE_TYPE_MAX
} StoneType_e;

// 埋める種類
typedef enum {
  DIG_PARTS_NONE = STONE_TYPE_NONE,
  DIG_PARTS_KONGOU_S = STONE_TYPE_DIAMOND,   //こんごうだま	KASEKI_KONGOU_S
  DIG_PARTS_SIRATAMA_S = STONE_TYPE_PEARL, //しらたま	KASEKI_SIRATAMA_S
  DIG_PARTS_RED_S = STONE_TYPE_RED,        //赤いタマ
  DIG_PARTS_BLUE_S = STONE_TYPE_BLUE,       //青いタマ
  DIG_PARTS_GREEN_S = STONE_TYPE_GREEN,      //緑のタマ
  DIG_PARTS_KONGOU_L,   //だいこんごうだま	KASEKI_KONGOU_L
  DIG_PARTS_SIRATAMA_L, //だいしらたま	KASEKI_SIRATAMA_L
  DIG_PARTS_RED_L,   //だいこんごうだま	KASEKI_KONGOU_L
  DIG_PARTS_BLUE_L,   //だいこんごうだま	KASEKI_KONGOU_L
  DIG_PARTS_GREEN_L, //だいしらたま	KASEKI_SIRATAMA_L
  DIG_PARTS_TREASURE_MIN,
  DIG_PARTS_CIRCLE = DIG_PARTS_TREASURE_MIN,        //まんまる	KASEKI_
  DIG_PARTS_KEYSTONE,        //かなめ	KASEKI_
  DIG_PARTS_SUN,        //たいようのいし	KASEKI_SUN
  DIG_PARTS_STAR,       //ほしのかけら	KASEKI_STAR
  DIG_PARTS_MOON,       //つきのいし	KASEKI_MOON
  DIG_PARTS_HARD,       //かたいいし	KASEKI_HARD
  DIG_PARTS_KAMINARI,   //かみなりのいし	KASEKI_KAMINARI
  DIG_PARTS_KAWARAZU,   //かわらずのいし	KASEKI_KAWARAZU
  DIG_PARTS_HONOO,      //ほのおのいし	KASEKI_HONOO
  DIG_PARTS_MIZU,       //みずのいし	KASEKI_MIZU
  DIG_PARTS_REAF,       //リーフのいし	KASEKI_REAF
  DIG_PARTS_GOLD,       //きんのたま	KASEKI_GOLD
  DIG_PARTS_KAI,        //かいのカセキ	KASEKI_KAI
  DIG_PARTS_KOURA,      //こうらのカセキ	KASEKI_KOURA
  DIG_PARTS_TSUME,      //ツメのカセキ	KASEKI_TSUME
  DIG_PARTS_NEKKO,      //ねっこのカセキ	KASEKI_NEKKO
  DIG_PARTS_KOHAKU,     //ひみつのコハク	KASEKI_KOHAKU
  DIG_PARTS_BONE,       //ふといほね	KASEKI_BONE
  DIG_PARTS_GENKI_S,   // 元気のかけら
  DIG_PARTS_GENKI_L, //げんきのかたまり
  DIG_PARTS_PLA_RED,//あかいかけら
  DIG_PARTS_PLA_BLUE,//あおいかけら
  DIG_PARTS_PLA_YELLOW,//きいろいかけら
  DIG_PARTS_PLA_GREEN,//みどりのかけら
  DIG_PARTS_HEART,//ハートのウロコ
  DIG_PARTS_SHIELD,//たてのカセキ
  DIG_PARTS_ZUGAI,//ずがいのカセキ
  DIG_PARTS_CRAY,//ひかりのねんど
  DIG_PARTS_IRONBALL,//くろいてっきゅう
  DIG_PARTS_COLD,//つめたいいわ
  DIG_PARTS_SARA,//さらさらいわ
  DIG_PARTS_HEAT,//あついいわ
  DIG_PARTS_WET, //しめったいわ
  DIG_PARTS_PLATE_FIRE,//ひのたまプレート
  DIG_PARTS_PLATE_WATER,//しずくプレート
  DIG_PARTS_PLATE_THUNDER,//いかづちプレート
  DIG_PARTS_PLATE_GREEN, //みどりのプレート
  DIG_PARTS_PLATE_ICICLE ,//つららのプレート
  DIG_PARTS_PLATE_KNUCKLE ,//こぶしのプレート
  DIG_PARTS_PLATE_POISON,//もうどくプレート
  DIG_PARTS_PLATE_GROUND,//だいちのプレート
  DIG_PARTS_PLATE_SKY,//あおぞらプレート
  DIG_PARTS_PLATE_WONDER,//ふしぎのプレート
  DIG_PARTS_PLATE_IRIDESCENCE ,//たまむしプレート
  DIG_PARTS_PLATE_ROCK,//がんせきプレート
  DIG_PARTS_PLATE_GHOST,//もののけプレート
  DIG_PARTS_PLATE_DRAGON,//りゅうのプレート
  DIG_PARTS_PLATE_DARK,//こわもてプレート
  DIG_PARTS_PLATE_IRON,//こうてつプレート
  
  DIG_PARTS_TREASURE_MAX,
  DIG_PARTS_NODIG1 = DIG_PARTS_TREASURE_MAX,     //掘れない岩	kaseki_iwa01	面積が４マス	棒形の真っ黒の石
  DIG_PARTS_NODIG2,     //掘れない岩	kaseki_iwa02	面積が４マス	四角型の真っ黒の石
  DIG_PARTS_NODIG3,     //掘れない岩	kaseki_iwa03	面積が４マス	T型の真っ黒の石
  DIG_PARTS_NODIG4,     //掘れない岩	kaseki_iwa04	面積が４マス	Z型の真っ黒の石
  DIG_PARTS_NODIG5,     //掘れない岩	kaseki_iwa05	面積が４マス	S型の真っ黒の石
  DIG_PARTS_NODIG6,     //掘れない岩	kaseki_iwa06	面積が９マス	四角型の真っ黒の石
  DIG_PARTS_NODIG7,     //掘れない岩	kaseki_iwa07	面積が８マス	棒形の真っ黒の石
  DIG_PARTS_MAX,
  DIG_PARTS_TYPE_FOSSIL_MIN = DIG_PARTS_KAI,
  DIG_PARTS_TYPE_FOSSIL_MAX = (DIG_PARTS_BONE+1),
} DigType_e;


// 罠タイプ
enum TrapType_e {
  UG_TRAPTYPE_NONE = 0,
  UG_TRAPTYPE_DIR_UP,
  UG_TRAPTYPE_DIR_RIGHT,
  UG_TRAPTYPE_DIR_DOWN,
  UG_TRAPTYPE_DIR_LEFT,
  UG_TRAPTYPE_BIGDIR_UP,
  UG_TRAPTYPE_BIGDIR_RIGHT,
  UG_TRAPTYPE_BIGDIR_DOWN,
  UG_TRAPTYPE_BIGDIR_LEFT,
  UG_TRAPTYPE_WARP,
  UG_TRAPTYPE_TELEPORT,
  UG_TRAPTYPE_HOLE,
  UG_TRAPTYPE_BIG_HOLE,
  UG_TRAPTYPE_REVERSE,
  UG_TRAPTYPE_GIDDY,  // 混乱
  UG_TRAPTYPE_RUNNING,
  UG_TRAPTYPE_INVISIBLE,
  UG_TRAPTYPE_SLOW,
  UG_TRAPTYPE_SMOG,  // 画面に霧
  UG_TRAPTYPE_BIG_SMOG,  // 画面に霧
  UG_TRAPTYPE_ROCK,
  UG_TRAPTYPE_ROCKFALL,
  UG_TRAPTYPE_SUDS,
  UG_TRAPTYPE_BUBBLE,
  UG_TRAPTYPE_ALART1,
  UG_TRAPTYPE_ALART2,
  UG_TRAPTYPE_ALART3,
  UG_TRAPTYPE_ALART4,
  UG_TRAPTYPE_LEAF,
  UG_TRAPTYPE_DIRTY_BLOSSOMS,
  UG_TRAPTYPE_FIRE,
  UG_TRAPTYPE_BLAZE,
  UG_TRAPTYPE_RADAR,
  UG_TRAPTYPE_DRILL,
  UG_TRAPTYPE_MAX,
};
#endif
/// 宝石の成長MAX値
#define UG_STONE_CARAT_MAX  (99)

#endif //__UG_ITEMTYPE_H__
