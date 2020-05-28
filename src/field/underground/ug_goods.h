//=============================================================================
/**
 * @file	ug_goods.h
 * @brief	地下のGOODS情報を管理するクラス
 * @author	k.ohno
 * @date    2006.02.14
 */
//=============================================================================

#ifndef __UG_GOODS_H__
#define __UG_GOODS_H__

#define UG_GOODS_NONE (0)

/*
// GOODSタイプ
enum GoodsType_e {
    UG_GOODS_NONE = 0,
    UG_GOODS_PC1,  //地下用パソコン＆ハタ1	基礎。レベル1
    UG_GOODS_PC2,  //地下用パソコン＆ハタ2	基礎。レベル2
    UG_GOODS_PC3,  //地下用パソコン＆ハタ3	基礎。レベル3
    UG_GOODS_PC4,  //地下用パソコン＆ハタ4	基礎。レベル4
    UG_GOODS_OBJECT01,   //ポケセンテーブル	グッズ
    UG_GOODS_OBJECT02,   //きいろクッション	グッズ
    UG_GOODS_OBJECT03,   //あおクッション	グッズ
    UG_GOODS_OBJECT04,   //かいふくマシン	グッズ
    UG_GOODS_OBJECT05,   //ポケセングッズ	グッズ
    UG_GOODS_OBJECT06,   //ショップだな	グッズ
    UG_GOODS_OBJECT07,   //しょうひんだな	グッズ
    UG_GOODS_OBJECT08,   //デパートグッズ	グッズ
    UG_GOODS_OBJECT09,   //デパートグッズ	グッズ
    UG_GOODS_OBJECT10,   //テレビ	グッズ
    UG_GOODS_OBJECT11,   //ピンククッション	グッズ
    UG_GOODS_OBJECT12,   //うえき	グッズ
    UG_GOODS_OBJECT13,   //れいぞうこ	グッズ
    UG_GOODS_OBJECT14,   //シンク	グッズ
    UG_GOODS_OBJECT15,   //ゲームき	グッズ
    UG_GOODS_OBJECT16,   //きのタンス	グッズ
    UG_GOODS_OBJECT17,   //ふかふかベッド	グッズ
    UG_GOODS_OBJECT18,   //おおきいほんだな	グッズ
    UG_GOODS_OBJECT19,   //ちいさいほんだな	グッズ
    UG_GOODS_OBJECT20,   //ごみばこ	グッズ
    UG_GOODS_OBJECT21,   //ダンボール	グッズ
    UG_GOODS_OBJECT22,   //おおきなテーブル	グッズ
    UG_GOODS_OBJECT23,   //博物館グッズ	グッズ
    UG_GOODS_OBJECT24,   //博物館グッズ	グッズ
    UG_GOODS_OBJECT25,   //図書館グッズ	グッズ
    UG_GOODS_OBJECT26,   //図書館グッズ	グッズ
    UG_GOODS_OBJECT27,   //TV局グッズ	グッズ
    UG_GOODS_OBJECT28,   //TV局グッズ	グッズ
    UG_GOODS_OBJECT29,   //アジトグッズ	グッズ
    UG_GOODS_OBJECT30,   //アジトグッズ	グッズ
    UG_GOODS_OBJECT31,   //ちきゅうぎ	グッズ
    UG_GOODS_OBJECT32,   //けんきゅうマシン	グッズ
    UG_GOODS_OBJECT33,   //じっけんマシン	グッズ
    UG_GOODS_OBJECT34,   //けんきゅうだな	グッズ
    UG_GOODS_OBJECT35,   //ジムのせきぞう	グッズ
    UG_GOODS_OBJECT36,   //ジムのつぼ	グッズ
    UG_GOODS_OBJECT37,   //ジムのスイッチ	グッズ
    UG_GOODS_OBJECT38,   //ジムのこおり	グッズ
    UG_GOODS_OBJECT39,   //でんどうのあかし	グッズ
    UG_GOODS_OBJECT40,   //ずかんのあかし	グッズ
    UG_GOODS_OBJECT41,   //たいせんひょう	グッズ
    UG_GOODS_OBJECT42,   //つうしんひょう	グッズ
    UG_GOODS_OBJECT43,   //ちいさないし	グッズ
    UG_GOODS_OBJECT44,   //おおきないし	グッズ
    UG_GOODS_OBJECT45,   //あかいテント	グッズ
    UG_GOODS_OBJECT46,   //あおいテント	グッズ
    UG_GOODS_OBJECT47,   //とうめいテント	グッズ
    UG_GOODS_OBJECT48,   //めいろブロック１	グッズ
    UG_GOODS_OBJECT49,   //めいろブロック２	グッズ
    UG_GOODS_OBJECT50,   //めいろブロック３	グッズ
    UG_GOODS_OBJECT51,   //めいろブロック４	グッズ
    UG_GOODS_OBJECT52,   //めいろブロック５	グッズ
    UG_GOODS_OBJECT53,   //たてながブロック	グッズ
    UG_GOODS_OBJECT54,   //たてかべブロック	グッズ
    UG_GOODS_OBJECT55,   //よこかべブロック	グッズ
    UG_GOODS_TRAP01,     //ワープそうち	罠グッズ
    UG_GOODS_TRAP02,     //テレポートそうち	罠グッズ
    UG_GOODS_TRAP03,     //あなそうち	罠グッズ
    UG_GOODS_TRAP04,     //おおあなそうち	罠グッズ
    UG_GOODS_TRAP05,     //はんてんそうち	罠グッズ
    UG_GOODS_TRAP06,     //こんらんそうち	罠グッズ
    UG_GOODS_TRAP07,     //はしりそうち	罠グッズ
    UG_GOODS_TRAP08,     //きえるそうち	罠グッズ
    UG_GOODS_TRAP09,     //おそいそうち	罠グッズ
    UG_GOODS_TRAP10,     //けむりそうち	罠グッズ
    UG_GOODS_TRAP11,     //えんまくそうち	罠グッズ
    UG_GOODS_TRAP12,     //いわそうち	罠グッズ
    UG_GOODS_TRAP13,     //らくせきそうち	罠グッズ
    UG_GOODS_TRAP14,     //あわそうち	罠グッズ
    UG_GOODS_TRAP15,     //バブルそうち	罠グッズ
    UG_GOODS_TRAP16,     //しびれそうち	罠グッズ
    UG_GOODS_TRAP17,     //でんじはそうち	罠グッズ
    UG_GOODS_TRAP18,     //けいほうそうち	罠グッズ
    UG_GOODS_TRAP19,     //サイレンそうち	罠グッズ
    UG_GOODS_TRAP20,     //このはそうち	罠グッズ
    UG_GOODS_TRAP21,     //はなびらそうち	罠グッズ
    UG_GOODS_TRAP22,     //ひのこそうち	罠グッズ
    UG_GOODS_TRAP23,     //ほのおそうち	罠グッズ
    UG_GOODS_TRAP24,     //レーダーそうち	罠グッズ
    UG_GOODS_TROPHY01,   //かわいいカップ	トロフィー
    UG_GOODS_TROPHY02,   //かっこいいカップ	トロフィー
    UG_GOODS_TROPHY03,   //うつくしいカップ	トロフィー
    UG_GOODS_TROPHY04,   //たくましいカップ	トロフィー
    UG_GOODS_TROPHY05,   //かしこいカップ	トロフィー
    UG_GOODS_TROPHY06,   //あおいすいしょう	トロフィー
    UG_GOODS_TROPHY07,   //ピンクすいしょう	トロフィー
    UG_GOODS_TROPHY08,   //あかいすいしょう	トロフィー
    UG_GOODS_TROPHY09,   //きいろすいしょう	トロフィー
    UG_GOODS_TROPHY10,   //きれいなほうせき	トロフィー
    UG_GOODS_TROPHY11,   //かがやくほうせき	トロフィー
    UG_GOODS_TROPHY12,   //しんぴのほうせき	トロフィー
    UG_GOODS_TROPHY13,   //きらめくほうせき	トロフィー
    UG_GOODS_TROPHY14,   //ブロンズトロフィー	トロフィー
    UG_GOODS_TROPHY15,   //シルバートロフィー	トロフィー
    UG_GOODS_TROPHY16,   //ゴールドトロフィー	トロフィー
    UG_GOODS_TROPHY17,   //プラチナトロフィー	トロフィー
    UG_GOODS_TROPHY18,   //ボールのオブジェ	トロフィー
    UG_GOODS_TROPHY19,   //まんまるオブジェ	トロフィー
    UG_GOODS_TROPHY20,   //かくばりオブジェ	トロフィー
    UG_GOODS_DOLL01,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL02,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL03,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL04,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL05,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL06,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL07,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL08,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL09,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL10,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL11,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL12,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL13,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL14,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL15,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL16,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL17,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL18,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL19,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL20,     //ポケモンドール	ぬいぐるみ
    UG_GOODS_DOLL21,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL22,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL23,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL24,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL25,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL26,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL27,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL28,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL29,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_DOLL30,     //ポケモンドール	おおきなぬいぐるみ
    UG_GOODS_POSTER01,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER02,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER03,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER04,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER05,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER06,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER07,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER08,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER09,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER10,   //ポケモンポスター	ポスター
    UG_GOODS_POSTER11,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER12,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER13,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER14,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER15,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER16,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER17,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER18,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER19,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER20,   //ポケモンポスター	おおきなポスター
    UG_GOODS_POSTER21,   //ポケモンポスター	おおきなポスター
    UG_GOODSTYPE_MAX,
};
*/

#endif // __UG_GOODS_H__




