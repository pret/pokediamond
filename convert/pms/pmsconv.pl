#!/usr/bin/perl

#===============================================================================
# 簡易会話用データコンバータ
#
# 簡易会話の単語として扱う各種gmmを参照し、
# カテゴリ別・インデックス別の単語ID配列データ等を作成する。
# 作成されたデータはＣプログラムから参照される。
#
# GameFreak taya
#
#===============================================================================

use utf8;
use encode;
use XML::Parser;
use FindBin;

use open OUT => ":encoding(shiftjis)";
binmode(STDERR,":encoding(shiftjis)");
binmode(STDOUT,":encoding(shiftjis)");

require 'gmmparse.pl';


#===============================================================
# 
#===============================================================
my $DUP_SYMBOL = "PMS_WORDID_DUP";
my $DUP_VALUE = "0xfffe";

my $END_SYMBOL = "PMS_WORDID_END";
my $END_VALUE = "0xffff";


my $PWDLIST_FILENAME = "pwdlist.dat";

#===============================================================
# 参照gmm（※ローカライズ作業でここを変更してはいけない）
#===============================================================

use constant SRC_MONSNAME	=> 0;
use constant SRC_WAZANAME	=> 1;
use constant SRC_POKETYPE	=> 2;
use constant SRC_TOKUSEI	=> 3;
use constant SRC_GROUP06	=> 4;
use constant SRC_GROUP07	=> 5;
use constant SRC_GROUP08	=> 6;
use constant SRC_GROUP09	=> 7;
use constant SRC_GROUP10	=> 8;
use constant SRC_GROUP11	=> 9;
use constant SRC_GROUP12	=> 10;


my @TargetGmm = (
	[ '../message/src/monsname.gmm',		'ポケモン名',		  1, -1, -1,  2,	-1, -1, -1,		'POKEMON' ],
	[ '../message/src/wazaname.gmm',		'わざ名',			  1, -1, -1, -1,	449, 464, 465,	'SKILL'   ],
	[ '../message/src/typename.gmm',		'ポケモンタイプ名',	 -1,  9,  9, -1,	-1, -1, -1,		'TYPE'    ],
	[ '../message/src/tokusei.gmm',			'とくせい名',		  1, -1, -1, -1,	121, 123, -1,	'TOKUSEI' ],
	[ '../message/src/pms/pms_word06.gmm',	'トレーナー',		 -1, -1, -1, -1,	-1, -1, -1,		'TRAINER' ],
	[ '../message/src/pms/pms_word07.gmm',	'ひと',				 -1, -1, -1, -1,	-1, -1, -1,		'HITO'    ],
	[ '../message/src/pms/pms_word08.gmm',	'あいさつ',			 -1, -1, -1, -1,	-1, -1, -1,		'AISATSU' ],
	[ '../message/src/pms/pms_word09.gmm',	'せいかつ',			 -1, -1, -1, -1,	-1, -1, -1,		'SEIKATSU'],
	[ '../message/src/pms/pms_word10.gmm',	'きもち',			 -1, -1, -1, -1,	-1, -1, -1,		'KIMOTI'  ],
	[ '../message/src/pms/pms_word11.gmm',	'なんかいことば',	 -1, -1, -1, -1,	-1, -1, -1,		'NANKAI'  ],
	[ '../message/src/pms/pms_word12.gmm',	'ユニオン',			 -1, -1, -1, -1,	-1, -1, -1,		'UNION'   ],

);

use constant TGM_FILEPATH		=> 0;
use constant TGM_COMMENT		=> 1;
use constant TGM_START_SKIP		=> 2;	# 最初のn件をスキップする（-1ならスキップしない）
use constant TGM_MID_SKIP_BEGIN	=> 3;	# 中間n件目からスキップする（-1ならスキップしない）
use constant TGM_MID_SKIP_END	=> 4;	# 中間n件目までスキップする（TGM_MID_SKIP_BEGINとセットで使う）
use constant TGM_END_SKIP		=> 5;	# 最後のn件をスキップする（-1ならスキップしない）
use constant TGM_FORCE_SKIP1	=> 6;	# ナンバー指定スキップ１（-1ならスキップしない）
use constant TGM_FORCE_SKIP2	=> 7;	# ナンバー指定スキップ２（-1ならスキップしない）
use constant TGM_FORCE_SKIP3	=> 8;	# ナンバー指定スキップ３（-1ならスキップしない）
use constant TGM_SRC_ID			=> 9;



#===============================================================
# カテゴリパラメータ（※ローカライズ作業でここを変更してはいけない）
#===============================================================
use constant  CATEGORY_CONV_NORMAL	=> 0;
use constant  CATEGORY_CONV_DIV		=> 1;
use constant  CATEGORY_CONV_MIX		=> 2;
use constant  CATEGORY_CONV_MONSNO	=> 3;

my @CategoryParam = (
	[ 'ポケモン',		'01',	0,	CATEGORY_CONV_DIV,		SRC_MONSNAME,    0, 241  ],
	[ 'ポケモン２',		'02',	0,	CATEGORY_CONV_DIV,		SRC_MONSNAME,  242,  -1  ],
	[ 'わざ',			'03',	0,	CATEGORY_CONV_DIV,		SRC_WAZANAME,    0, 286  ],
	[ 'わざ２',			'04',	0,	CATEGORY_CONV_DIV,		SRC_WAZANAME,  287,  -1  ],
	[ 'ステータス',		'05',	1,	CATEGORY_CONV_MIX,		SRC_TOKUSEI, SRC_POKETYPE  ],
	[ 'トレーナー',		'06',	1,	CATEGORY_CONV_NORMAL,	SRC_GROUP06  ],
	[ 'ひと',			'07',	1,	CATEGORY_CONV_NORMAL,	SRC_GROUP07  ],
	[ 'あいさつ',		'08',	0,	CATEGORY_CONV_NORMAL,	SRC_GROUP08  ],
	[ 'せいかつ',		'09',	1,	CATEGORY_CONV_NORMAL,	SRC_GROUP09  ],
	[ 'きもち',			'10',	1,	CATEGORY_CONV_NORMAL,	SRC_GROUP10  ],
	[ 'なんかいことば',	'11',	0,	CATEGORY_CONV_NORMAL,	SRC_GROUP11  ],
	[ 'ユニオン',		'12',	0,	CATEGORY_CONV_NORMAL,	SRC_GROUP12  ],
);

use constant CPELEM_TITLE			=>  0;
use constant CPELEM_NUMBER			=>  1;
use constant CPELEM_PWD_GROUP		=>  2;
use constant CPELEM_CONVERT_TYPE	=>  3;
use constant CPELEM_CONVERT_ARG0	=>  4;
use constant CPELEM_CONVERT_ARG1	=>  5;
use constant CPELEM_CONVERT_ARG2	=>  6;


#===============================================================
# イニシャル順パラメータ（同じ配列内にある文字を同一項とみなす）
#===============================================================
my @InitialTable = (
	[ 'あ', 'ぁ', 'ア', 'ァ' ],
	[ 'い','ぃ','イ','ィ' ],
	[ 'う','ぅ','ウ','ゥ' ],
	[ 'え','ぇ','エ','ェ' ],
	[ 'お','ぉ','オ','ォ' ],
	[ 'か','が','カ','ガ' ],
	[ 'き','ぎ','キ','ギ' ],
	[ 'く','ぐ','ク','グ' ],
	[ 'け','げ','ケ','ゲ' ],
	[ 'こ','ご','コ','ゴ' ],
	[ 'さ','ざ','サ','ザ' ],
	[ 'し','じ','シ','ジ' ],
	[ 'す','ず','ス','ズ' ],
	[ 'せ','ぜ','セ','ゼ' ],
	[ 'そ','ぞ','ソ','ゾ' ],
	[ 'た','だ','タ','ダ' ],
	[ 'ち','ぢ','チ','ヂ' ],
	[ 'つ','づ','ツ','ヅ' ],
	[ 'て','で','テ','デ' ],
	[ 'と','ど','ト','ド' ],
	[ 'な','ナ' ],
	[ 'に','ニ' ],
	[ 'ぬ','ヌ' ],
	[ 'ね','ネ' ],
	[ 'の','ノ' ],
	[ 'は','ハ','ば','バ','ぱ','パ' ],
	[ 'ひ','ヒ','び','ビ','ぴ','ピ' ],
	[ 'ふ','フ','ぶ','ブ','ぷ','プ' ],
	[ 'へ','ヘ','べ','ベ','ぺ','ペ' ],
	[ 'ほ','ホ','ぼ','ボ','ぽ','ポ' ],
	[ 'ま','マ' ],
	[ 'み','ミ' ],
	[ 'む','ム' ],
	[ 'め','メ' ],
	[ 'も','モ' ],
	[ 'や','ゃ','ヤ','ャ' ],
	[ 'ゆ','ゅ','ユ','ュ' ],
	[ 'よ','ょ','ヨ','ョ' ],
	[ 'ら','ラ' ],
	[ 'り','リ' ],
	[ 'る','ル' ],
	[ 'れ','レ' ],
	[ 'ろ','ロ' ],
	[ 'わ','ワ','を','ヲ','ん','ン' ],

#	ローカライズ時はこちらのテーブルを有効にする（かなは無効にする）
#	[ 'a','A','ａ','Ａ' ],
#	[ 'b','B','ｂ','Ｂ' ],
#	[ 'c','C','ｃ','Ｃ' ],
#	[ 'd','D','ｄ','Ｄ' ],
#	[ 'e','E','ｅ','Ｅ' ],
#	[ 'f','F','ｆ','Ｆ' ],
#	[ 'g','G','ｇ','Ｇ' ],
#	[ 'h','H','ｈ','Ｈ' ],
#	[ 'i','I','ｉ','Ｉ' ],
#	[ 'j','J','ｊ','Ｊ' ],
#	[ 'k','K','ｋ','Ｋ' ],
#	[ 'l','L','ｌ','Ｌ' ],
#	[ 'm','M','ｍ','Ｍ' ],
#	[ 'n','N','ｎ','Ｎ' ],
#	[ 'o','O','ｏ','Ｏ' ],
#	[ 'p','P','ｐ','Ｐ' ],
#	[ 'q','Q','ｑ','Ｑ' ],
#	[ 'r','R','ｒ','Ｒ' ],
#	[ 's','S','ｓ','Ｓ' ],
#	[ 't','T','ｔ','Ｔ' ],
#	[ 'u','U','ｕ','Ｕ' ],
#	[ 'v','V','ｖ','Ｖ' ],
#	[ 'w','W','ｗ','Ｗ' ],
#	[ 'x','X','ｘ','Ｘ' ],
#	[ 'y','Y','ｙ','Ｙ' ],
#	[ 'z','Z','ｚ','Ｚ' ],

);

# ↑このテーブルから、イニシャルごとのインデックスを作っておくためのハッシュ（高速化のため）
my %InitialIdxTable = ();

# ↑このテーブルに属さない文字のＩＤ
use constant INITIAL_ID_OTHER => -1;

#===============================================================
# 音引き記号（ー）を直前の文字の音に合わせて変換するためのテーブル
#（日本語のみ）
#===============================================================
my @OnbikiTbl = (
	[ 'アァカサタナハマヤャラワ',	'ア' ],
	[ 'イィキシチニヒミリ',			'イ' ],
	[ 'ウゥクスツヌフムユュル',		'ウ' ],
	[ 'エェケセテネヘメレ',			'エ' ],
	[ 'オォコソトノホモヨョロ',		'オ' ],
);

#===============================================================
# このスクリプトの動作モード
#===============================================================
use constant  MODE_ERROR => 0;
use constant  MODE_WORD => 1;
use constant  MODE_INPUT => 2;
use constant  MODE_LIST => 3;


#===============================================================
# global
#===============================================================
my @SrcElems = ();
my @SrcString = ();
my $TotalElems  = 0;
my @DupWordIndex = ();


#===============================================================
# 
#===============================================================
&main();
exit(0);

sub main {

	my $mode = check_mode(@ARGV);

	if( $mode == MODE_ERROR )
	{
		&usage();
		return 1;
	}


	if( $mode == MODE_LIST )
	{
		&output_list($ARGV[0]);
	}
	else
	{

		&Setup_InitialIdxTable();

		foreach my $ref (@TargetGmm)
		{
			my $filepath = $FindBin::Bin . '/' . $$ref[TGM_FILEPATH];

			my @tmp = GmmParse::ToArray( $filepath, '日本語' );

			my $elems = @tmp;
			push @SrcElems, $elems;
			$TotalElems += $elems;
			@SrcString = (@SrcString, @tmp);
		}

		output_input_data($ARGV[0]);
		output_word_data($ARGV[1]);
	}
}

sub check_mode {
	my @arg = @_;

	if( @arg == 1 )
	{
		return MODE_LIST;
	}
	elsif( @arg == 2 )
	{
		return MODE_WORD;
	}

	return MODE_ERROR;
}

sub usage {
	my ($pack,$filename,$line) = caller;
	print ">perl $filename <outputfile> <outputfile>\n";
	print "<outputfile>\n";
	print "   1つの時：makefileが参照するリストファイル\n";
	print "   2つの時：１つめが入力画面用データテーブル、２つめが簡易会話システム用データテーブル\n";
}
#===============================================================
# 高速化のため、イニシャルごとのインデックス値テーブルを作っておく
# あ・ぁ・ア・ァ=>1, い・ぃ・イ・ィ=>2, ... みたいなやつ。
#===============================================================
sub Setup_InitialIdxTable {
	my $idx = 0;

	foreach my $ref (@InitialTable)
	{
		foreach my $letter (@$ref)
		{
			$InitialIdxTable{$letter} = $idx;
		}
		$idx++;
	}
}

#===============================================================
# 
#===============================================================
sub output_word_data {
	my $filename = shift;

	if( open(FILE, ">$filename") )
	{
		my $i;
		my $tmp;

		print FILE &GetCommonCommentStr();

		print FILE "#ifdef __PMS_WORD_RES__\t// 単一のファイルからのみincludeを許可する\n\n";


	# ファイル種類を指定するための定数値
		print FILE &ToLongComment( "各gmmファイル指定のための定数" );
		print FILE "enum {\n";
		for($i=0; $i<@SrcElems; $i++)
		{
			printf FILE "\tPMSW_SRC_%s,\n", ${$TargetGmm[$i]}[TGM_SRC_ID];
		}
		print FILE "};\n\n";


	# ファイル毎の要素数
		print FILE &ToLongComment( "各gmmファイル毎の要素数" );
		print FILE "static const u16 PMS_SrcElems[] = {\n";
		$tmp = 0;
		for($i=0; $i<@SrcElems; $i++)
		{
			printf FILE "\t%4d,\t//%s\t%d ... %d\n", $SrcElems[$i], ${$TargetGmm[$i]}[TGM_COMMENT], $tmp, ($tmp+$SrcElems[$i]-1);
			$tmp += $SrcElems[$i];
		}
		print FILE "};\n\n";


	# ファイルのアーカイブIDテーブル
		print FILE &ToLongComment( "各gmmファイルのアーカイブ内ファイルID" );
		print FILE "static const u16 PMS_SrcFileID[] = {\n";
		foreach $tmp (@TargetGmm)
		{
			print FILE "\t";
			print FILE &MakeFileIDString($$tmp[TGM_FILEPATH]);
			print FILE ",\n";
		}
		print FILE "};\n\n";

	# 重複単語テーブル
		print FILE &ToLongComment( "重複単語テーブル" );
		$tmp = @DupWordIndex;
		my @idx;
		my @nums = ();
		for($i=0; $i<@DupWordIndex; $i++)
		{
			@idx = split( /,/, $DupWordIndex[$i] );
			$tmp = @idx;
			push @nums, $tmp;
			print FILE "static const PMS_WORD ";
			print FILE &MakeDupWordAryName($i);
			print FILE "\[\] = {\n";
			print FILE "\t";
			foreach $tmp (@idx)
			{
				printf FILE "%3d,", $tmp;
			}
			print FILE "\n};\n\n";
		}
		print FILE "static const struct {\n";
		print FILE "    const PMS_WORD* data;\n";
		print FILE "    int   count;\n";
		print FILE "}DupWordTable[] = {\n";
		for($i=0; $i<@DupWordIndex; $i++)
		{
			print FILE "\t{ ";
			print FILE &MakeDupWordAryName($i);
			print FILE ", $nums[$i] },\n";
		}
		print FILE "};\n\n";


	# 
		$tmp = @TargetGmm;
		print FILE &ToLongComment( "関連定数" );
		print FILE "#define  PMS_SRCFILE_MAX  ($tmp)\n\n";

		print FILE "#undef __PMS_WORD_RES__\n";
		print FILE "#endif\n\n";

		close(FILE);
		print "->$filename\n";
	}
	else
	{
		print "$filename を出力できません\n";
		return 0;
	}

	return 1;

}

#===============================================================
# 
#===============================================================
sub output_input_data {
	my $filename = shift;

	unless( open( PWD_LIST, ">$PWDLIST_FILENAME")  )
	{
		print "$PWDLIST_FILENAME を作成できません\n";
		return 0;
	}

	if( open(FILE, ">$filename") )
	{
		my $i;
		my $tmp;
		my $cnt;

		print FILE &GetCommonCommentStr();

		print FILE "#ifdef __PMS_INPUT_RES__\n\n";

		print FILE "#define $END_SYMBOL\t($END_VALUE)\n";
		print FILE "#define $DUP_SYMBOL\t($DUP_VALUE)\n\n";

		print FILE "#define PMS_WORDNUM_MAX\t($TotalElems)\t// 総単語数\n\n";


		# カテゴリごとの単語IDテーブル
		print FILE &ToLongComment( "カテゴリごとの単語IDテーブル" );
		foreach $tmp (@CategoryParam) {
			my @datStrID = CreateCategoryIdxTable($tmp);
			my @datStr;
			GetSortTable(\@datStr, \@datStrID);
			print FILE "// $$tmp[0]\n";
			print FILE "static const u16 PMS_CategoryTable_$$tmp[1]\[\] = {\n";

			# パスワード壁紙対象グループは別ファイルにリストをはき出す
			if( $$tmp[CPELEM_PWD_GROUP] )
			{
				for($i=0; $i<@datStrID; $i++)
				{
					print FILE "\t$datStrID[$i]\t//$datStr[$i]\n";
					print PWD_LIST "$datStr[$i]\n";
				}
			}
			else
			{
				for($i=0; $i<@datStrID; $i++)
				{
					print FILE "\t$datStrID[$i]\t//$datStr[$i]\n";
				}
			}

			print FILE "\t$END_SYMBOL\n";
			print FILE "};\n\n";

			$cnt = @datStrID;
			print FILE "#define  PMS_Category_$$tmp[1]_MaxNum\t($cnt)\n\n";
		}
		close( PWD_LIST );
		print "->$PWDLIST_FILENAME\n";

		# 文字順単語IDテーブル
		$tmp = 0;
		print FILE &ToLongComment( "文字順単語IDテーブル" );
		my $ini_max = @InitialTable;
		for($i=0; $i <= $ini_max; $i++)
		{
			my @datStrID = CreateInitialIdxTable($i);
			if( @datStrID > 0 )
			{
				my @datStr;
				GetSortTable(\@datStr, \@datStrID);
				print FILE "// ${$InitialTable[$i]}[0]\n";
				print FILE "static const u16 PMS_InitialTable_$tmp\[\] = {\n";
				for(my $p = 0; $p < @datStrID; $p++)
				{
					print FILE "\t$datStrID[$p]\t//$datStr[$p]\n";
				}
				print FILE "\t$END_SYMBOL\n";
				print FILE "};\n\n";
				$tmp++;
			}
		}

		print FILE "// 文字順テーブルの先頭アドレスをテーブル化しておく\n";
		print FILE "static const u16* const PMS_InitialTable[] = {\n";
		for($i=0; $i<$tmp; $i++)
		{
			print FILE "\tPMS_InitialTable_$i,\n";
		}
		print FILE "};\n\n";


		print FILE "#undef __PMS_INPUT_RES__\n";
		print FILE "#endif  // __PMS_INPUT_RES__\n";

		print "->$filename\n";
		close(FILE);
	}
	else
	{
		print "$filename を出力できません\n";
		return 0;
	}

	return 1;

}


#===============================================================
# カテゴリに含まれる全単語を、IDテーブル化して返す
#===============================================================
sub CreateCategoryIdxTable {
	my $category = shift;
	my @ary = ();

	if( $$category[CPELEM_CONVERT_TYPE] == CATEGORY_CONV_NORMAL )
	{
		@ary = CreateSrcIdxArray( $$category[CPELEM_CONVERT_ARG0] );
	}
	elsif( $$category[CPELEM_CONVERT_TYPE] == CATEGORY_CONV_MIX )
	{
		@ary = CreateSrcIdxArray( $$category[CPELEM_CONVERT_ARG0] );
		@ary = (@ary, CreateSrcIdxArray( $$category[CPELEM_CONVERT_ARG1] ));
	}
	elsif( $$category[CPELEM_CONVERT_TYPE] == CATEGORY_CONV_DIV )
	{
		my @str;
		my @strID;

		@strID = CreateSrcIdxArray( $$category[CPELEM_CONVERT_ARG0] );
		@strID = &GetSortTable( \@str, \@strID );

		my $s = $$category[CPELEM_CONVERT_ARG1];
		my $e = $$category[CPELEM_CONVERT_ARG2];
		if( $e == -1 )
		{
			 $e += @strID;
		}

		for( ; $s <= $e; $s++)
		{
			push @ary , $strID[$s];
		}

	}

	return @ary;
}
#===============================================================
# 同一イニシャルの単語を、IDテーブル化して返す
#===============================================================
sub CreateInitialIdxTable {
	my $ini = shift;
	my $letter;
	my @allStr;
	my @ary = ();

	@allStrID = CreateAllStrIdTable();

	if($ini >= @InitialTable)
	{
		$ini = INITIAL_ID_OTHER;
	}

	foreach $str_id (@allStrID )
	{
		$letter = substr( $SrcString[$str_id], 0, 1 );
		if( &GetInitialID($letter) == $ini )
		{
			push @ary, $str_id;
		}
	}

	my $num = @ary;
	return @ary;
}
#===============================================================
# １文字を受け取り、イニシャルＩＤを返す
#===============================================================
sub GetInitialID {
	my $letter = shift;

	if( exists( $InitialIdxTable{$letter} ) )
	{
		return $InitialIdxTable{$letter};
	}

	return INITIAL_ID_OTHER;
}

#===============================================================
# 使用する全ての単語IDをテーブルにして返す
# ※ 0～@#SrcString をそのまま使うと、
#	 ポケモン名等の先頭ダミー文字列が含まれてしまうため、ここで吸収している
#===============================================================
sub CreateAllStrIdTable {
	my $i;
	my @ary = ();

	for( $i = 0; $i<@TargetGmm; $i++ )
	{
		@ary = (@ary, CreateSrcIdxArray( $i ));
	}

	return @ary;
}


#===============================================================
# gmm １本文を、単語IDテーブル化して返す
# input : gmm ID
#===============================================================
sub CreateSrcIdxArray {
	my $src_no = shift;

	my $p = 0;

	for(my $i=0; $i<$src_no; $i++)
	{
		$p += $SrcElems[$i];
	}

	my $end = $p + $SrcElems[$src_no];

	my @ary = ();

	my $start_skip = ${$TargetGmm[$src_no]}[TGM_START_SKIP];
	my $end_skip = ${$TargetGmm[$src_no]}[TGM_END_SKIP];
	my $mid_skip_begin = ${$TargetGmm[$src_no]}[TGM_MID_SKIP_BEGIN];

	# ポケモン名などは先頭にダミー要素が入っているので、ここでカットしとく
	if( $start_skip != -1 )
	{
		$p += $start_skip;
	}
	if( $end_skip != -1 )
	{
		$end -= $end_skip
	}

	my $skip1 = ${$TargetGmm[$src_no]}[TGM_FORCE_SKIP1];
	my $skip2 = ${$TargetGmm[$src_no]}[TGM_FORCE_SKIP2];
	my $skip3 = ${$TargetGmm[$src_no]}[TGM_FORCE_SKIP3];

	if( $skip1 != -1 ){ $skip1 += ($p-1); }
	if( $skip2 != -1 ){ $skip2 += ($p-1); }
	if( $skip3 != -1 ){ $skip3 += ($p-1); }

	if( $mid_skip_begin != -1 )
	{
		my $mid_skip_end = ${$TargetGmm[$src_no]}[TGM_MID_SKIP_END];
		my $i = -1;
		if( $start_skip != -1 )
		{
			$i += $start_skip;
		}

		for( ; $p < $end; $p++)
		{
			$i++;
			if( ($i >= $mid_skip_begin)
			&&	($i <= $mid_skip_end)
			){
				next;
			}

			if( $p==$skip1 || $p==$skip2 || $p==$skip3 )
			{
				next;
			}

			push @ary, $p;
		}
	}
	else
	{
		for( ; $p < $end; $p++)
		{
			if( $p==$skip1 || $p==$skip2 || $p==$skip3 )
			{
				next;
			}
			push @ary, $p;
		}
	}
	return @ary;
}

#===============================================================
# 
#===============================================================
sub GetSortTable {
	my $strRef = shift;
	my $strIdRef = shift;
	my @idAry = @$strIdRef;

	my @strAry = ();
	my @sortAry = ();
	my %Idx;
	my $id;
	my $i;
	my $src_str;
	my $str;

	for($i=0; $i < @idAry; $i++)
	{
		$id = $idAry[$i];
		$src_str = $SrcString[$id];
		$str = $SrcString[$id];

		# 日本語では、平仮名・片仮名を同一視。海外版では大文字・小文字を同一視。
		$str =~ tr/０-９/0-9/;
		$str =~ tr/A-Z/Ａ-Ｚ/;
		$str =~ tr/a-z/Ａ-Ｚ/;
		$str =~ tr/ぁ-ん/ァ-ン/;
		$str =~ tr/ガ,ギ,グ,ゲ,ゴ/カ,キ,ク,ケ,コ/;
		$str =~ tr/ザ,ジ,ズ,ゼ,ゾ/サ,シ,ス,セ,ソ/;
		$str =~ tr/ダ,ヂ,ヅ,デ,ド/タ,チ,ツ,テ,ト/;
		$str =~ tr/バ,ビ,ブ,ベ,ボ/ハ,ヒ,フ,ヘ,ホ/;
		$str =~ tr/パ,ピ,プ,ペ,ポ/ハ,ヒ,フ,ヘ,ホ/;
		$str =~ tr/ッ/ツ/;
		if( $str =~ /ー/ )
		{
			$str = &conv_onbiki( $str );
		}

#		$str =~ tr/a-z/A-Z/;

#		print "$str\n";

		$sortAry[$i] = [ $str, $src_str, $id ];


		if( exists ($Idx{$src_str}) )
		{
			$Idx{$src_str} .= sprintf( "%4d,", $id );
		}
		else
		{
			$Idx{$src_str} = sprintf( "%4d,", $id );
		}
	}

	@sortAry = sort sort_func @sortAry;

	my @tmp;
	my $dup;
	@idAry = ();
	for($i=0; $i<@sortAry; $i++)
	{
		$src_str = ${$sortAry[$i]}[1];
		if( $Idx{$src_str} ne "" )
		{
			@tmp = split(/,/, $Idx{$src_str});
			$dup = @tmp;
			if( $dup > 1 )
			{
				push @idAry, "$DUP_SYMBOL,$dup," . $Idx{$src_str};
				# 重複ナンバーリストをグローバルに
				push @DupWordIndex, $Idx{$src_str};
			}
			else
			{
				push @idAry, $Idx{$src_str};
			}
			$Idx{$src_str} = "";
			push @$strRef, $src_str;
		}
	}

	@$strIdRef = @idAry;
	return @idAry;
}
sub sort_func {

	my $ret = $$a[0] cmp $$b[0];

	if( $ret == 0 )
	{
		$ret = $$a[1] cmp $$b[1];
	}


	return $ret;#$a <=> $b;
}







#===============================================================
# 音引き記号を前の音に合わせて変更
#===============================================================
sub conv_onbiki {
	my $str = shift;
	my $t, $i,$max, $ref;

	my @list = split( /ー/, $str );

#	print "$str -> ";

	$max = @list - 1;
	if( $str =~ /ー$/ )
	{
		$max++;
	}
	for($i=0; $i<$max; $i++)
	{
		$t = substr($list[$i], length($list[$i])-1, 1);

		foreach my $ref(@OnbikiTbl)
		{
			if( index( $$ref[0], $t ) >= 0 )
			{
				$list[$i] .= $$ref[1];
				last;
			}
		}
	}

	$str = "";
	foreach $t (@list)
	{
		$str .= $t;
	}

#	print "$str\n";

	return $str;

}

#===============================================================
# 
#===============================================================
sub ToLongComment {
	my $str = shift;
	my $line = "//----------------------------------------------------------------\n";
	my $ret = $line;
	$ret .= "/**\n";
	$ret .= " * $str\n";
	$ret .= "*/\n";
	$ret .= $line;
	$ret .= "\n";

	return $ret;
}

#===============================================================
# 
#===============================================================
sub GetCommonCommentStr {
	my @str = (
		"// このファイルはコンバータで自動生成されています\n",
		"// 手作業での編集は行わないようにお願いします\n",
		"// Game Freak   taya\n\n\n",
		);

	my $ret = "";

	foreach my $tmp (@str)
	{
		$ret .= $tmp;
	}

	return $ret;
}

#===============================================================
# 
#===============================================================
sub MakeFileIDString {
	my $path = shift;

	my @tmp = split(/\//, $path);

	my $fn = $tmp[$#tmp];

	$fn =~ s/\.gmm//;
	$fn = "NARC_msg_" . $fn . "_dat";

	return $fn;
}

#===============================================================
# 
#===============================================================
sub MakeDupWordAryName {
	my $num = shift;
	return sprintf("DupWord_%02d", $num);
}

#===============================================================
# 
#===============================================================
sub output_list {
	my $file = shift;

	if( open(FILE, ">$file") )
	{
		print FILE "SOURCE = \\\n";

		foreach my $ref (@TargetGmm)
		{
			print FILE "\t$$ref[TGM_FILEPATH]  \\\n";
		}

		close(FILE);

		print "->$file\n";
	}
	else
	{
		print "$file が出力できない\n";
	}
}

