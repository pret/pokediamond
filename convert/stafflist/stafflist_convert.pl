#!/usr/bin/perl

use encode;
use utf8;

require 'makegmm.pl';





my $STRID_BLANK_VALUE = '0xffff';
my $STRID_BLANK_SYMBOL = 'ENDING_STRID_BLNK';



my $SrcFileName = "";
my $DatFileName = "";
my $GmmFileName = "";

my $ProcResult = main();
exit($ProcResult);






sub main {

	if( @ARGV != 3 )
	{
		print ">perl stafflist_convert.pl [src] [dst_dat] [dst_gmm]\n";
		return 1;
	}

	$SrcFileName = $ARGV[0];
	$DatFileName = $ARGV[1];
	$GmmFileName = $ARGV[2];


	if( open( DAT, ">$DatFileName") == 0)
	{
		print "can't create $DatFileName\n";
		return 1;
	}

	if( make_gmm::init('..\message\template.gmm', 'jp') == 0)
	{
		print "failure initialize \'make_gmm\' module\n";
		return 1;
	}

	if( open( SRC, "<$SrcFileName") == 0)
	{
		print "can't open $SrcFileName\n";
		return 1;
	}

	my @src = <SRC>;
	close(SRC);

	DatFile_PrintHeader();

	my @dat;
	my $id;
	my $cnt=0;
	my $totalHeight=0;
	my $prev_version = "";

	for($i=1; $i<@src; $i++)
	{
		$src[$i] =~ s/[\r\n]//g;
		@dat = split( /\t/, $src[$i] );

		if( @dat != 6 )
		{
			next;
		}

		my ($text, $height, $color, $version, $centering) = @dat;

		if( $text ne "" )
		{
			$id = sprintf("ENDING_STRID_%04d", $cnt++);
			Encode::from_to($text, 'shiftjis', 'utf8');
			utf8::decode($text);
			if( $color != 0 )
			{
				$text = "\[FF:00:色:$color\]" . $text;
			}
			make_gmm::add($id, $text, 216, "1:font_system");

			DatFile_PrintDat( $id, $totalHeight, $centering, $version );
		}

		if($prev_version ne "" || $version eq "")
		{
			$totalHeight += $height;
		}
		$prev_version = $version;
	}


	if( make_gmm::output($GmmFileName) == 0)
	{
		print "can't create $GmmFileName\n";
		return 1;
	}
	print "->$GmmFileName\n";

	DatFile_PrintFooder();
	close(DAT);
	print "->$DatFileName\n";

	return 0;
}

sub DatFile_PrintLine {
	my $txt = shift;

	if(utf8::is_utf8($txt))
	{
		utf8::encode($txt);
	}
	Encode::from_to($txt, 'utf8', 'shiftjis');

	print DAT "$txt";

}

sub GetFileNameOnly {
	my $path = shift;
	my @list = split(/\\/, $path);
	my $cnt = @list;
	return $list[$cnt-1];
}


sub  DatFile_PrintHeader {
	my ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday) = localtime(time);

	$year += 1900;
	$mon += 1;

	my $DateStr = sprintf("%d.%02d.%02d", $year, $mon, $mday);
	my $filename = GetFileNameOnly($DatFileName);

	DatFile_PrintLine("//----------------------------------------------------------------------\n");
	DatFile_PrintLine("/**\n");
	DatFile_PrintLine(" * \@file   $filename\n");
	DatFile_PrintLine(" * \@brief  スタッフリストデータテーブル\n");
	DatFile_PrintLine(" * \@date   $DateStr\n");
	DatFile_PrintLine(" *\n");
	DatFile_PrintLine(" * このファイルはコンバータにより自動生成されたものです\n");
	DatFile_PrintLine(" * GameFreak taya\n");
	DatFile_PrintLine(" */\n");
	DatFile_PrintLine("//----------------------------------------------------------------------\n");
	DatFile_PrintLine("#ifdef __STAFFLIST_DAT__\n\n");

	DatFile_PrintLine("#include \"msgdata\\msg_stafflist.h\"\n\n");

	DatFile_PrintLine("#define $STRID_BLANK_SYMBOL    ($STRID_BLANK_VALUE)\n\n");

	DatFile_PrintLine("static const struct {\n");
	DatFile_PrintLine("\tu16 strID;\n");
	DatFile_PrintLine("\tu16 height;\n");
	DatFile_PrintLine("\tu16 centeringFlag;\n");
	DatFile_PrintLine("}StaffListDataTable[] = {\n");


}

sub DatFile_PrintDat {
	my $strID = shift;
	my $height = shift;
	my $centering = shift;
	my $version = shift;
	my $v_flg = 0;


	$height = sprintf("%d", $height);
	while(length($height)<5){
		$height = ' ' . $height;
	}

	if($centering eq "" )
	{
		$centering = 'FALSE';
	}
	else
	{
		$centering = 'TRUE';
	}

	if($version eq 'DIA')  { DatFile_PrintLine("#if ( PM_VERSION == VERSION_DIAMOND )\n"); $v_flg = 1; }
	if($version eq 'PEARL'){ DatFile_PrintLine("#if ( PM_VERSION == VERSION_PEARL )\n"); $v_flg = 1; }

	DatFile_PrintLine("\t{ $strID, $height, $centering },\n");

	if($v_flg)
	{
		DatFile_PrintLine("#endif\n\n");
	}

}


sub DatFile_PrintFooder {
	DatFile_PrintLine("};\n\n");
	DatFile_PrintLine("#endif\n");
}
