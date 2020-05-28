#===============================================================================
# メッセージコンバータ用 文字列ID管理パッケージ
# メインのスクリプトでrequireして使うだけ
# 
# GameFreak taya
#
#===============================================================================
package idman;

require 'tool.pl';

my @IdList = ();
my @FileList = ();
my @GroupList = ();

my @Id_File_Idx = ();
my @Id_Group_Idx = ();

my $ErrorMsg = "";

#===============================================================
# 新規IDを追加
# input : 0:ID（文字列）
#         1:グループ名
#         2:処理中ファイル名
#
#===============================================================
sub store {
	my ($id, $group, $filename) = @_;
	my $err_msg;
	my $i;

# 同一IDがあれば死ぬ（別ファイルでも）


	for($i = 0; $i < @IdList; $i++)
	{
		if( $id eq $IdList[$i] )
		{
			my $dup_filename = $FileList[ $Id_File_Idx[$i] ];
			if( $dup_filename eq $filename )
			{
#				die("ID [$id] の重複（$filename）");
				$ErrorMsg .= "ID [$id] Duplicate in ($filename)\n";
			}
			else
			{
				$ErrorMsg .= "ID [$id] Duplicate in ($dup_filename, $filename)\n";
			}

#			die($err_msg);
		}
	}

# ID, ファイル名, グループ名を登録しておく

	push @IdList, $id;

	my $idx = &tool::store_unique_data( $filename, \@FileList );
	push @Id_File_Idx, $idx;

	$idx = &tool::store_unique_data( $group, \@GroupList );
	push @Id_Group_Idx, $idx;

}
#===============================================================
# store 処理でエラーがあった場合、その詳細を出力して die 
#===============================================================
sub check_error {
	if( $ErrorMsg ne "" )
	{
		die($ErrorMsg);
	}
}
#===============================================================
# ヘッダファイル出力
# input : 0:処理中ファイル名（拡張子を .h に変えたものがヘッダファイル名になる）
#         1:出力先ディレクトリパス
#
# return : エラーがあればdie
#===============================================================
sub output_header {
	my ($file, $path) = @_;
	my $output_file;
	my $idx;
	my $cnt;

	$file_idx = &tool::get_unique_idx($file, \@FileList);

	if($file_idx < 0)
	{
		die("予期せぬエラー");
		return;
	}

	$output_file = &tool::change_ext($file, ".h");
	$output_file = &tool::get_filename_from_path($output_file);
	$output_file = "msg_" . $output_file;
	$output_file = $path . $output_file;



	if( open(HEADER_FILE, ">$output_file") )
	{
		my $outputFileName = &tool::get_filename_from_path($output_file);
		print HEADER_FILE &tool::enc_sjis("//==============================================================================\n");
		print HEADER_FILE &tool::enc_sjis("/**\n");
		print HEADER_FILE &tool::enc_sjis(" * \@file		$outputFileName\n");
		print HEADER_FILE &tool::enc_sjis(" * \@brief		メッセージID参照用ヘッダファイル\n");
		print HEADER_FILE &tool::enc_sjis(" *\n");
		print HEADER_FILE &tool::enc_sjis(" * このファイルはコンバータにより自動生成されています\n");
		print HEADER_FILE &tool::enc_sjis(" */\n");
		print HEADER_FILE &tool::enc_sjis("//==============================================================================\n");
		print HEADER_FILE &make_header_tag($output_file);

	# 単一グループしか無い場合の出力
		if( &check_single_group ($file_idx) )
		{
			$cnt = 0;
			for(my $i = 0; $i < @Id_File_Idx; $i++)
			{
				if($Id_File_Idx[$i] == $file_idx)
				{
					my $txt = &tool::enc_sjis("#define\t$IdList[$i]\t\t($cnt)\n");
					print HEADER_FILE "$txt";
					$cnt++;
				}
			}

		}
	# 複数グループが含まれる場合の出力
		else
		{
			my @group_list;
			&get_group($file_idx, \@group_list);

			foreach my $group (@group_list) {

				print HEADER_FILE &tool::enc_sjis( "// $group\n" );

				$cnt = 0;
				for(my $i = 0; $i < @Id_File_Idx; $i++)
				{
					if(	($Id_File_Idx[$i] == $file_idx)
					&&	($group eq $GroupList[ $Id_Group_Idx[$i] ])
					){
						print HEADER_FILE &tool::enc_sjis("#define\t$IdList[$i]\t\t($cnt)\n");
						$cnt++;
					}
				}
				print HEADER_FILE &tool::enc_sjis("\n");
			}
		}


		print HEADER_FILE &tool::enc_sjis("\n#endif\n");

		close(HEADER_FILE);

		print &tool::enc_sjis("-> $output_file\n");
	}
	else
	{
		die("$output_file が作成できません");
	}
}
#===============================================================
# 最新（現在処理中）のID文字列を返す
# return : ID文字列
#===============================================================
sub get_latest_id {
	my $idx = @IdList - 1;
	if($idx < 0)
	{
		return "";
	}
	return $IdList[$idx];
}
#===============================================================
# 最新（現在処理中）のグループ文字列を返す
# return : グループ文字列
#===============================================================
sub get_latest_group {
	my $idx = @Id_Group_Idx - 1;
	if($idx < 0)
	{
		return "";
	}
	$idx = $Id_Group_Idx[$idx];
	if($idx >= @GroupList)
	{
		return "";
	}
	return $GroupList[$idx];
}


#------------------------------------------------------------------------------------------
# 以下のサブルーチンは外部からの呼び出しを想定していない
#------------------------------------------------------------------------------------------

#======================================================
# ヘッダーの多重インクルード防止タグ（ #ifndef ～ ）を作る
# input : 0:ヘッダファイル名
# return : 防止タグ文字列
#======================================================
sub make_header_tag {
	my $header_name = shift;

	my @list = split(/[\/\\]/, $header_name);
	my $c = @list;
	$header_name = $list[$cnt-1];

	$header_name = uc ($header_name);

	my @p = split(/[.\/\\]/, $header_name);
	my $sym = '__';

	foreach (@p) {
		$sym .= $_;
		$sym .= "_";
	}
	$sym .= "_";

	my $ret = "#ifndef $sym\n#define $sym\n\n";

	return $ret;
}
#======================================================
# コンバート対象のファイル名に単一のグループしか含まれていないかチェック
# input : 0:対象ファイルidx
# return : 1で単一グループ、0で複数グループが含まれる
#======================================================
sub check_single_group {
	my $file_idx = shift;
	my $first_group_idx = -1;

	for(my $i = 0; $i < @Id_File_Idx; $i++)
	{
		if($file_idx == $Id_File_Idx[$i])
		{
			if($first_group_idx == -1)
			{
				$first_group_idx = $Id_Group_Idx[$i];
			}
			elsif($first_group_idx != $Id_Group_Idx[$i])
			{
				return 0;
			}
		}
	}

	return 1;
}
#======================================================
# コンバート対象のファイルに含まれるグループイン名のみを配列化
# input : 0:対象ファイルidx
# input   1:グループインデックスを作成する配列のリファレンス
#======================================================
sub get_group {
	my $file_idx = shift;
	my $ary_ref = shift;

	for(my $i = 0; $i < @Id_File_Idx; $i++)
	{
		if($file_idx == $Id_File_Idx[$i])
		{
			&tool::store_unique_data($GroupList[ $Id_Group_Idx[$i] ], $ary_ref);
		}
	}

	@$ary_ref = sort(@$ary_ref);
}



return 1;
