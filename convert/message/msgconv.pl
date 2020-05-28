#!/usr/bin/perl

#===============================================================================
# メッセージコンバータ
#
# メッセージエディタのデータファイル（gmm）を読み込んで、各国語版の
# メッセージリソースを出力するためのPerlスクリプトです。
#
# Perlのヴァージョンは、XML::Parser モジュールを使用可能なものにする必要があります。
#（当スクリプト自体は ActivePerl v5.8.6 動作環境で作成しました）
# 
# GameFreak taya
#
#===============================================================================


use XML::Parser;
use encode;
use utf8;

use open OUT => ":encoding(shiftjis)";

binmode(STDERR,":encoding(shiftjis)");
binmode(STDOUT,":encoding(shiftjis)");

require 'letter_order.pl';
require 'resource.pl';
require 'idman.pl';

#===================================================
# Params
#===================================================
my %LangParamTbl = (		# 言語コード指定パラメータ

	'LANG_JAPAN',	'日本語',		# スクリプト実行時のパラメータとして'jp'を指定すると、
							# エディタ「日本語」列に書かれたメッセージをコンバート対象とします。
							# 必要に応じてこのテーブルをカスタマイズしてください。
							# エディタ側にも指定言語の列が無ければ正しく動作しないことに注意してください。

	'LANG_ENGLISH',	'英語',
	'LANG_ITALY',	'イタリア語',
	'LANG_FRANCE',	'フランス語',
	'LANG_SPAIN',	'スペイン語',
	'LANG_GERMANY',	'ドイツ語',


);

my $HEADER_OUTPUT_DIR = '../../include/msgdata/';
my $HEADER_EXT = '.h';
my $RESOURCE_OUTPUT_DIR = './data/';
my $RESOURCE_EXT = '.dat';

my $TIMECHECK_DATA_PATH = '../../src/msgdata/msg.narc';	# このファイルと比較して新しいgmmのみをコンバートする

#===================================================
# Constants
#===================================================
use constant SEQ_FREE		=> 0;	# シーケンス：メッセージ読み込み処理外
use constant SEQ_COLUMNS	=> 1;	# シーケンス：'columns'タグ読み込み開始
use constant SEQ_GROUP		=> 2;	# シーケンス：'columns-group'タグ読み込み開始
use constant SEQ_ROW		=> 3;	# シーケンス：'row'タグ読み込み開始
use constant SEQ_LANG_START	=> 4;	# シーケンス：'row-language'タグ読み込み開始
use constant SEQ_LANG		=> 5;	# シーケンス：'row-language'タグ読み込み途中
use constant SEQ_FINISH		=> 6;	# シーケンス：指定言語メッセージの処理終了
use constant SEQ_DEFAULT_LANG_START => 7;
use constant SEQ_DEFAULT_LANG_READING => 8;

use constant LETTER_ORDER_FILE => "pokemon_dp.xlor";	# 文字オーダーファイル

#===================================================
# Globals
#===================================================
my $TargetLang = "";		# 出力対象の言語（日本語なら“日本語”と文字列が入る）
my $TargetLangCode = "";	# 出力対象の言語識別コード（日本語なら“jp”と文字列が入る）
my $ParsingFileName = "";	# 解析中のファイル名
my $DefaultGroupName = "デフォルト";	# デフォルトのグループ名（読み込んだソースによって可変）
my $ReadingText = "";		# 読み込み中のテキスト内容
my $AllMakeFlag = 0;		# ファイルの更新日時チェックをせず、全ファイルをコンバートする

my $DefaultLangText = "";
my $DefaultLang = "日本語";


#===============================================================
# main
# 異常終了時、システムに1を返す。通常時は0を返す
#===============================================================
my $err = &main;
exit($err);

sub main {
	my @files;

	srand(time ^ ($$ + ($$ << 15)));


	if(	$ARGV[0] eq '-a' )
	{
		$AllMakeFlag = 1;
		shift(@ARGV);
	}


	if(	(@ARGV != 2)
	||	($LangParamTbl{$ARGV[1]} eq "")
	){
		&usage;
		return 1;
	}
	$TargetLang = $LangParamTbl{$ARGV[1]};
	$TargetLangCode = $ARGV[1];

	if(	($ARGV[0] =~ /\.gmm$/)
	||	($ARGV[0] =~ /\.xml$/)
	){
		push(@files, $ARGV[0]);
	}
	else
	{
		if(open(FILE,  '<:encoding(shiftjis)', $ARGV[0]) )
		{
			while(<FILE>)
			{
				$_ =~ s/[\r\n]//g;
				push (@files, $_);
			}
			close(file);

			&delete_old_datfile( \@files, $RESOURCE_OUTPUT_DIR );
		}
		else
		{
			print STDERR "エラー：$ARGV[0] が開けません\n";
			return 1;
		}
	}

	my $letterOrder = &letter_order::get(LETTER_ORDER_FILE);
	if($letterOrder eq "")
	{
		print STDERR "エラー：正しい文字オーダーデータを取得できません\n";
		return 1;
	}

	my $parser = new XML::Parser;

	$parser->setHandlers(	Start => \&StartHandler,
							End => \&EndHandler,
							Char => \&CharHandler
						);


	foreach (@files)
	{
		if(&conv($_, \$parser, $letterOrder))
		{
			return 1;
		}
	}

	return 0;
}
#===============================================================
# 日付チェック
# input 1: ファイル１
#       2: ファイル２
# return   ファイル１が存在しないorファイル１の方が古い場合は１
#          それ以外は０
#===============================================================
sub update_time_check {
	my $target = shift;
	my $source = shift;

	if( $AllMakeFlag ){ return 1; }
	unless( -e $target ){ return 1; }
	unless( -e $source ){ return 0; }

	my @filestatus = stat($target);
	my $target_time = $filestatus[9];
	@filestatus = stat($source);
	my $source_time = $filestatus[9];

	if( $target_time < $source_time )
	{
		return 1;
	}

	return 0;
}

#===============================================================
# リスト化されていない古いdatファイルを削除する
# input 1: ソースファイルリストへのリファレンス
#       2: datファイルが存在するディレクトリパス
#===============================================================
sub delete_old_datfile {
	my $src_ref = shift;
	my $dat_path = shift;
	my %src_list;
	my $tmp;

	foreach (@$src_ref) {
		$tmp = $_;
		if( $tmp =~ /\\/ )
		{
			my @tmpary = split(/\\/, $tmp);
			$tmp = $tmpary[@tmpary-1];
		}
		$tmp =~ s/\.gmm$/\.dat/;
		$src_list{$tmp} = 1;
	}

	if( opendir(DIR, $dat_path) )
	{
		my @datlist = readdir(DIR);
		my $datfile;
		foreach $datfile (@datlist) {
			unless( $datfile =~ /\.dat$/ )
			{
				next;
			}
			if( $src_list{$datfile} == 1 )
			{
				next;
			}
			unlink($dat_path.$datfile);
		}
		closedir(DIR);
	}

}

#===============================================================
# usage
#===============================================================
sub usage {
	my ($pack,$filename,$line) = caller;

	print ">perl $filename [-a] <gmm> <lang>\n";
	print "[-a]   ファイル更新日付をチェックせず、全ファイルをコンバートする\n";
	print "<gmm>  メッセージエディタ用データファイル（gmmファイル）\n";
	print "       または、gmmファイル名のリストファイル\n";
	print "<lang> コンバート対象となる言語コード\n";

	my @key = keys(%LangParamTbl);
	my @val = values(%LangParamTbl);

	for(my $i = 0; $i < @key; $i++)
	{
		print "       $key[$i] -> $val[$i]\n";
	}
}
#===============================================================
# コンバートメイン
# input : 0: コンバート対象ファイル名
# 異常終了で1,正常終了で0を返す
#===============================================================
sub conv {
	my $filename = shift;
	my $parser = shift;
	my $letterOrder = shift;
	my $xml;

	if( open(FILE, $filename) )
	{
		my @stat = stat(FILE);
		read(FILE, $xml, $stat[7]);
		close(FILE);
	}
	else
	{
		print STDERR "エラー：$filename が開けません\n";
		return 1;
	}

	$ParsingFileName = $filename;
	&ResetSeq();
	&resource::init($letterOrder);


	eval {$$parser->parse($xml)};
	if($@){
		print STDERR "エラー: $@\n";
		return 1;
	}

	&idman::check_error();

	&idman::output_header($filename, $HEADER_OUTPUT_DIR);
	&resource::output($filename, $RESOURCE_OUTPUT_DIR);

	return 0;

}

#===============================================================
# XML開始タグ読み込み時のハンドラ
#===============================================================
sub StartHandler {
	my $expat = shift;
	my $tag = shift;
	my %elems = ();

	my $seq = &GetSeq;


	for(my $i = 0; $i < @_; $i += 2)
	{
		$elems{$_[$i]} = $_[$i+1];
	}

	if($seq == SEQ_FREE)
	{
		if($tag eq "columns")
		{
			&SetSeq(SEQ_COLUMNS);
		}
		if($tag eq "row")
		{
			if($elems{erase} eq "")
			{
				my $group = $elems{group};
				if($group eq ""){ $group = $DefaultGroupName; }

#				print "-store -> $elems{id}\n";
				idman::store($elems{id}, $group, $ParsingFileName);

				&SetSeq(SEQ_ROW);
			}
		}
	}
	elsif($seq == SEQ_COLUMNS)
	{
		if($tag eq "group")
		{
			if($elems{default} ne "")
			{
				$DefaultGroupName = $elems{default};
			}
			&ResetSeq();
		}
	}
	elsif($seq == SEQ_ROW)
	{
		if($tag eq "language")
		{
			if($elems{name} eq $TargetLang)
			{
				&FwdSeq;
			}
			elsif($elems{name} eq $DefaultLang)
			{
				&SetSeq(SEQ_DEFAULT_LANG_START);
			}
		}
	}


=pod
	map {print $_,"//"}@{$expat->{Context}} , "\n";
	print "++(";
	map {print "$_"," "}@_;
	print ")\n";
=cut
}
#===============================================================
# XML終了タグ読み込み時のハンドラ
#===============================================================
sub EndHandler
{
	my $expat = shift;
	my $tag = shift;

	my $seq = &GetSeq();

	if( $seq == SEQ_DEFAULT_LANG_READING )
	{
		if($tag eq "language")
		{
			&SetSeq( SEQ_ROW );
			return;
		}
	}
	if($seq == SEQ_LANG)
	{
		if($tag eq "language")
		{
			my $group = &idman::get_latest_group();
			my $id = &idman::get_latest_id();

			if($group eq "")
			{
				die("解析出来ない：ID[ $id ] in $ParsingFileName\n");
			}

			if(&resource::add_msg($ReadingText, $group, $TargetLangCode) == 0)
			{
				print "解析出来ない文字：ID[ $id ] in $ParsingFileName\n";
			}

			&FwdSeq();
		}
	}

	if($seq == SEQ_LANG_START)
	{
		if($tag eq "language")
		{
#			my $id = &idman::get_latest_id();
#			die("[ $TargetLang ] のFFFメッセージデータがない：ID[ $id ] in $ParsingFileName\n");
			&SetSeq( SEQ_ROW );
		}
	}

	if($tag eq "row")
	{
		if($seq == SEQ_FINISH)
		{
			&ResetSeq();
		}
		elsif($seq == SEQ_ROW)
		{
			my $group = &idman::get_latest_group();
			my $id = &idman::get_latest_id();

			print "$id in $ParsingFileName have not translated\n";
			&resource::add_msg($DefaultLangText, $group, $TargetLangCode);
#			die("[ $TargetLang ] のメッセージデータがない：ID[ $id ] in $ParsingFileName\n");
			&ResetSeq();
		}
	}

}
#===============================================================
# XMLタグ内文字列読み込み時のハンドラ
#===============================================================
sub CharHandler
{
	my $expat = shift;
	my $text = shift;

	my $seq = &GetSeq();


	if($seq == SEQ_LANG_START)
	{
		$ReadingText = $text;
		&FwdSeq();
	}
	elsif($seq == SEQ_LANG)
	{
		$ReadingText .= $text;
	}
	elsif($seq == SEQ_DEFAULT_LANG_START)
	{
		$DefaultLangText = $text;
		&SetSeq(SEQ_DEFAULT_LANG_READING);
	}
	elsif($seq == SEQ_DEFAULT_LANG_READING)
	{
		$DefaultLangText .= $text;
	}
}


#===============================================================
# シーケンス処理
#===============================================================
my $Sequence = SEQ_FREE;

sub ResetSeq {
	$Sequence = SEQ_FREE;
}

sub GetSeq {
	return $Sequence;
}

sub SetSeq {
	$Sequence = shift;
}

sub FwdSeq {
	$Sequence++;
	if($Sequence > SEQ_FINISH)
	{
		$Sequence = SEQ_FREE;
	}
}



