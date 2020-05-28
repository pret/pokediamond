#!/usr/bin/perl
#===============================================================================
# 文字コードファイル作成
#
# NitroSystem fontcvtr 用文字オーダーファイルを元に、文字コード定義ファイルを作成
# （現状だとPC上で入力できない特殊文字コードの扱いが難しい）
#
# GameFreak taya
#
#===============================================================================

use encode;
use utf8;

use open OUT => ":encoding(shiftjis)";

binmode(STDERR,":encoding(shiftjis)");
binmode(STDOUT,":encoding(shiftjis)");

require 'letter_order.pl';


#===============================================================
# main
# 異常終了時、システムに1を返す。通常時は0を返す
#===============================================================
my $err = &main;
exit($err);

sub main {
	my $input_filename;
	my $output_filename;

	if( @ARGV == 1 )
	{
		$input_filename = $ARGV[0];
		$output_filename = $input_filename;
		$output_filename =~ s/\.+[^\.]+$//g;
		$output_filename .= '_strcode.h';
	}
	elsif(@ARGV == 2 )
	{
		$input_filename = $ARGV[0];
		$output_filename = $ARGV[1];
	}
	else
	{
		&usage();
		return;
	}

	my $letterOrder = &letter_order::get($input_filename);
	if($letterOrder eq "")
	{
		print STDERR "エラー：正しい文字オーダーデータを取得できません\n";
		return 1;
	}

	&letter_order::enumcode_output($output_filename);


	return 0;
}

#===============================================================
# usage
#===============================================================
sub usage {
	my ($pack,$filename,$line) = caller;

	print ">perl $filename <input_xlor> [output]\n";
}
