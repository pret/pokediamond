#===============================================================================
# gmmデータ解析スクリプト
# メインのスクリプトでrequireして使うだけ
# 
# GameFreak taya
#
#===============================================================================
package GmmParse;

use XML::Parser;


#=======================================================
# const
#=======================================================
use constant SEQ_INIT					=> 0;	# シーケンス：メッセージ読み込み処理外
use constant SEQ_WAIT_LANGUAGE_TAG		=> 1;
use constant SEQ_STORE_STRING			=> 2;


#=======================================================
# global
#=======================================================
my $Seq = SEQ_INIT;
my $TargetLang = "";
my $TargetID = "";
my $TargetStr = "";
my %TargetHash = ();
my $TargetAry = ();



#=======================================================
# 解析実行、ハッシュを返す
#
# input 0 : 解析対象のファイルパス
#       1 : 対象言語コード ... '日本語' など
#
# return  hash ... IDがkey, 文字列がvalueとしてセットされている
#=======================================================
sub ToHash {
	my ($file, $lang) = @_;

	%TargetHash = ();
	parse($file, $lang);

	return %TargetHash;
}

#=======================================================
# 解析実行、配列を返す
#
# input 0 : 解析対象のファイルパス
#       1 : 対象言語コード ... '日本語' など
#
# return  配列 ... ファイルの先頭から順に出現した文字列がセットされている
#=======================================================
sub ToArray {
	my ($file, $lang) = @_;

	@TargetAry = ();
	parse($file, $lang);

	return @TargetAry;

}

#=======================================================
# 解析実行共通処理
#=======================================================
sub parse {
	my ($file, $lang) = @_;
	my $parser = new XML::Parser;


	$parser->setHandlers(	Start => \&StartHandler,
							End => \&EndHandler,
							Char => \&CharHandler
						);

	$TargetLang = $lang;
	$Seq = SEQ_INIT;


	if( open(FILE, $file) )
	{
		my @stat = stat(FILE);
		my $xmlDat;
		read(FILE, $xmlDat, $stat[7]);
		close( FILE );

		eval {$parser->parse($xmlDat)};
	}
}




#=======================================================
# 解析用ハンドラ
#=======================================================

sub StartHandler {
	my $expat = shift;
	my $tag = shift;
	my %elems = ();

	for(my $i = 0; $i < @_; $i += 2)
	{
		$elems{$_[$i]} = $_[$i+1];
	}


	if($Seq == SEQ_INIT)
	{
		if($tag eq 'row')
		{
			if($elems{erase} eq "")
			{
				$Seq = SEQ_WAIT_LANGUAGE_TAG;
				$TargetID = $elems{id};
			}
		}
	}
	elsif($Seq == SEQ_WAIT_LANGUAGE_TAG)
	{
		if($tag eq 'language')
		{
			if($elems{'name'} eq $TargetLang)
			{
				$Seq = SEQ_STORE_STRING;
				$TargetStr = "";
			}
		}
	}
}

sub CharHandler {
	my $expat = shift;
	my $text = shift;

	if($Seq == SEQ_STORE_STRING)
	{
		$TargetStr .= $text;
	}
}

sub EndHandler {
	my $expat = shift;
	my $tag = shift;


	if( $Seq == SEQ_STORE_STRING )
	{
		if($tag eq 'language')
		{
			$TargetHash{$TargetID} = $TargetStr;
			push @TargetAry, $TargetStr;
			$Seq = SEQ_INIT;
		}
	}
}

return 1;
