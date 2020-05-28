package tool;

use Encode;

#======================================================
# 重複しないなら配列にデータを追加
# input : 0:追加したいデータ
#         1:配列リファレンス
#
# return : データのインデックス値
#======================================================
sub store_unique_data {
	my ($val, $ary_ref) = @_;
	my $i;

	for($i = 0; $i < @$ary_ref; $i++)
	{
		if( $val eq $$ary_ref[$i] )
		{
			last;
		}
	}

	if($i == @$ary_ref)
	{
		push @$ary_ref, $val;
	}

	return $i;
}
#======================================================
# 重複の無い配列から該当データのインデックス値を返す
# input : 0:データ
#         1:配列リファレンス
#
# return : データインデックス値（見つからなければ-1）
#======================================================
sub get_unique_idx {
	my ($val, $ary_ref) = @_;
	my $i;

	for($i = 0; $i < @$ary_ref; $i++)
	{
		if( $val eq $$ary_ref[$i] )
		{
			return $i;
		}
	}
	return -1;
}
#===============================================================
# ファイル名の拡張子部分を変換
# input 0: ファイル名
#       1: 返還後の拡張子
#       2: （無くても良い）ファイル名（拡張子除く）末尾に付け足す文字
# return : 拡張子部分を変換したファイル名
#===============================================================
sub change_ext {
	my ($file,$ext,$fooder) = @_;
	my $i;
	my $p;

	unless($ext =~ /^\./)
	{
		$ext = "." . $ext;
	}

	$p = length($file);
	$i = index($file, '.');
	while($i >= 0)
	{
		$p = $i;
		$i = index($txt, '.', $i+1);
	}

	$file = substr($file, 0, $p);
	if($fooder ne "")
	{
		$file .= "_$fooder";
	}

	$file .= $ext;

	return $file;

}
#===============================================================
# ファイルパスからファイル名部分のみを取り出す
# input 0: ファイルパス
# return : ファイル名
#===============================================================
sub get_filename_from_path {
	my $path = shift;

	my $i;

	$i = index($path, '\\');
	if($i < 0){ $i = index($path, '/'); }
	while($i >=0)
	{
		$path = substr($path, $i+1, length($path) - $i);
		$i = index($path, '\\');
		if($i < 0){ $i = index($path, '/'); }
	}

	return $path;

}
#======================================================
# 文字列のutf8フラグを落とし、sjisコンバートする（ヘッダ出力用）
# input : 0:文字列
# return 変換後の文字列
#======================================================
sub enc_sjis {
	my $txt = shift;

	if(utf8::is_utf8($txt))
	{
		utf8::encode($txt);
	}
	
	Encode::from_to($txt, 'utf8', 'shiftjis');
	return $txt;
}

#======================================================
# 文字列のutf8フラグを落とし、utf16コンバートする（ヘッダ出力用）
# input : 0:文字列
# return 変換後の文字列
#======================================================
sub enc_u16 {
	my $txt = shift;

	if(utf8::is_utf8($txt))
	{
		utf8::encode($txt);
	}
	
	Encode::from_to($txt, 'utf8', 'utf16-le');
	return $txt;
}


return 1;
