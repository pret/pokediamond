#===============================================================================
# メッセージコンバータ用 メッセージリソース管理パッケージ
# メインのスクリプトでrequireして使う
# 
# GameFreak taya
#
#===============================================================================
package resource;

require 'tool.pl';

#===================================================
# Params
#===================================================
my $DataExt = ".dat";

#===================================================
# Globals
#===================================================
my @GroupName = ();
my @MsgCount = ();
my @MsgLen = ();
my @MsgBody = ();
my $LetterOrder = "";

my $LatestColorChangeParam = 0;

#===================================================
# Consts
#===================================================
use constant TAG_CODE		=> 0xfffe;	# タグ開始コード
use constant EOM_CODE		=> 0xffff;	# EOMコード

use constant STR_HEADER_SIZE	=> 0x0008;	# 文字列に付くヘッダのｻｲｽﾞ

#===================================================
# グループごとの初期化
# input 0 : 文字配置順（配置順に文字が並んだutf16-le文字列）
#===================================================
sub init {
	$LetterOrder = shift;
	@GroupIdx = ();
	@MsgCount = ();
	@MsgLen = ();
	@MsgBody = ();
}
#===============================================================
# メッセージ追加
# return  1で正常終了，0で解析できないエラー
#===============================================================
sub add_msg {
	my $txt = shift;
	my $group = shift;
	my $lang_code = shift;
	my $data = "";
	my $len = "";


	my $idx = &tool::store_unique_data( $group, \@GroupName );

	my $i = 0;
	my $str = $txt;
	my $pos_o = index($txt, '[');
	my $pos_c;
	my $tag;
	my $err;

	$LatestColorChangeParam = 0;

	&encode_init();

	while($pos_o >= 0)
	{
		$pos_c = index($txt, ']', $pos_o+1);
		if($pos_c < 0){
			return 0;
		}
		$str = substr($txt, $i, ($pos_o - $i));
		$tag = substr($txt, $pos_o, ($pos_c-$pos_o+1));

		$data .= &encode_game_strcode($str, \$err);
		if( $err )
		{
			return 0;
		}
		
		$tag = &tag_bin($tag);
		if($tag eq "")
		{
			return 0;
		}
		$data .= $tag;

		$i = $pos_c + 1;
		$pos_o = index($txt, '[', $i);
		if($pos_o < 0)
		{
			if($i < length($txt)){
				$str = substr($txt, $i, length($txt) - $i);
			}else{
				$str = "";
			}
			last;
		}
	}

	if($str ne "")
	{
		$data .= &encode_game_strcode($str, \$err);
		if( $err )
		{
			return 0;
		}
	}

	# デフォルトカラーに戻されていない単語
	if( $LatestColorChangeParam != 0 )
	{
		$data .= &tag_bin('[FF:00:色:0]');
	}

	$data .= pack('S', EOM_CODE);

	# １文字２バイト固定なので
	$len = length($data) / 2;


	if( $lang_code eq 'LANG_JAPAN' )
	{
		# 日本語は文字数が短いため、ローカライズ時を考慮して
		# 文字列長を倍にしておく
		my $i;
		for($i=0; $i<$len; $i++)
		{
			$data .= pack('S', EOM_CODE);
		}
		$len *= 2;
	}


	# カンマ区切りでグローバルに保存しておく
	$len .= ",";

	$MsgLen[$idx] .= $len;
	$MsgBody[$idx] .= $data;
	$MsgCount[$idx]++;

	return 1;
}
#===============================================================
# データ出力（外部インターフェイス）
# input 0: 処理中のファイル名（拡張子を変更したものを出力）
#       1  出力先ディレクトリパス
# return  異常終了時はdie
#===============================================================
sub output {

	my $filename = shift;
	my $dir = shift;

	if(@GroupName == 0)
	{
		return 1;
	}


	if(@GroupName == 1)
	{
		$filename = &tool::change_ext($filename, $DataExt);
		$filename = &tool::get_filename_from_path($filename);
		$filename = $dir . $filename;

		&output_main($filename, 0);
	}
	else
	{
		my @sort = sort (@GroupName);
		my $idx;
		my $fn;

		for(my $i = 0; $i < @sort; $i++)
		{
			$idx = &tool::get_unique_idx($sort[$i], \@GroupName);

			$fn = &tool::change_ext($filename, $DataExt, $i);
			$fn = &tool::get_filename_from_path($fn);
			$fn = $dir . $fn;

			&output_main($fn, $idx);
		}

	}
}

#===============================================================
# データ出力（内部メイン）
# input 0: 出力ファイルパス
#       1  対象データインデックス
# return  異常終了時はdie
#===============================================================
sub output_main {
	my $file = shift;
	my $idx = shift;

	if(open (RES, ">$file") )
	{
		my $dat;
		my @len;
		my $val;
		my $rand_seed;
		my $ofs_sum;
		my $i;

		binmode(RES);

	# 先頭２バイトにメッセージ件数
		$dat = pack('S', $MsgCount[$idx]);
		syswrite (RES, $dat, 4);

	# 次の２バイトに暗号用乱数
		$rand_seed = calc_crc($file);
		$dat = pack('S', $rand_seed);
		syswrite (RES, $dat, 2);
#		print &tool::enc_sjis("RndSeed = $rand_seed\n");

	# 次にオフセットテーブル（１件４バイト）
		@len = split(/,/, $MsgLen[$idx]);
		$ofs_sum = 0;
		for($i = 0; $i < $MsgCount[$idx]; $i++)
		{
			# データファイル先頭からのオフセット
			$val = 4 + ($MsgCount[$idx]  * STR_HEADER_SIZE) + $ofs_sum;
			$dat =  pack('I', $val);
			$dat .= pack('I', $len[$i]);
			syswrite (RES, $dat, STR_HEADER_SIZE);

			$ofs_sum += $len[$i] * 2;
		}

	# 最後にメッセージデータ
		syswrite (RES, $MsgBody[$idx], length($MsgBody[$idx]));

		close(RES);

		system("msgenc $file\n");
		print &tool::enc_sjis("-> $file\n");

	}
	else
	{
		die "$file が作成できません";
	}
}

# ファイル名文字列からCRC計算
sub calc_crc {
	my  $filename = shift;
	my  ($crc, $p, $d, $len, $count);

	$len = length( $filename );
	$p = 0;
	$crc = 0;
	while( $len-- )
	{
		$d = ord(substr($filename, $p++, 1));
		$count = 8;
		while( $count-- )
		{
			$crc ^= 0x8003 if ($crc <<= 1) & 0x10000;
			$crc ^= 1 if ($d<<=1) & 0x100;
		}
	}
	return $crc & 0xffff;
}


#---------------------------------------------------------------------------------------
# これ以下は外部からの呼び出しを想定していない
#---------------------------------------------------------------------------------------
my $EncodeSkipCR_Flag = 0;

sub encode_init {	# source local
	$EncodeSkipCR_Flag = 0;
}
#===============================================================
# ゲームで扱う文字コードに変換
# input 0:	ファイルから読んだままの文字（utf8）
# return  	ゲーム内文字コード
#===============================================================
sub encode_game_strcode {	# source local
	my $str = shift;
	my $err_flag = shift;
	my $i;
	my $letterCnt;
	my $ret = "";
	my $letter;
	my $idx;
	my $t;


	$str = &tool::enc_u16($str);
	$letterCnt = length($str) / 2;
	for($i = 0; $i < $letterCnt; $i++)
	{
		$letter = substr($str, $i*2, 2);
		$idx = index($LetterOrder, $letter);
		$t = $letter;
		Encode::from_to($t, 'utf16-le', 'utf8');

		if($t eq "\n")
		{
			if( $EncodeSkipCR_Flag == 0 )
			{
				$ret .= pack('S', 0xe000);
			}
			else
			{
				$EncodeSkipCR_Flag = 0;
			}
		}
		elsif($t eq "▼")
		{
			$ret .= pack('S', 0x25bc);
			$EncodeSkipCR_Flag = 1;		# 次の改行は無視する
		}
		elsif($t eq "▽")
		{
			$ret .= pack('S', 0x25BD);
			$EncodeSkipCR_Flag = 1;		# 次の改行は無視する
		}
		elsif($idx >= 0){
			$idx /= 2;
			$idx++;
			$ret .= pack('S', $idx);
		}
		else
		{
			$$err_flag = 1;
			return "";
		}
	}
	$$err_flag = 0;
	return $ret;

# utf16-le そのまま使うならこれだけでよい
#	return &tool::enc_u16($str);
}

#===============================================================
# タグ文字列をバイナリ化
# input 0: タグ文字列
# return バイナリパックされたタグデータ
#===============================================================
sub tag_bin {
	my $tag_str = shift;

	my @elems = split(/[\[\]:]/, $tag_str);

	my $tag_val;
	my $tag_type;
	my $tag_param;

	shift @elems;	# 最初に空要素が入ってしまうので

	if (@elems < 3 )
	{
		return "";
	}


	# 最初は開始コード（2byte）
	$tag_val = pack('S', TAG_CODE);

	# 次にタグ種類コード（2byte）
	$tag_type = hex($elems[0]) * 256 + hex($elems[1]);
	$tag_val .= pack('S', $tag_type);

	# 次にパラメータ数（2byte）
	my $elem_max = @elems - 3;
	$tag_val .= pack('S', $elem_max);

	# パラメータ１つあたり2byte
	if($elem_max > 0)
	{
		for(my $i = 0; $i < $elem_max; $i++)
		{
			$tag_param = int($elems[3+$i]);
			if( $tag_type == 0xff00 )
			{
				$LatestColorChangeParam = $tag_param;
			}
			$tag_val .= pack('S', $tag_param);
		}
	}

	return $tag_val;
}


return 1;

