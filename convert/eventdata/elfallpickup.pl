#!perl
#
# elfallpickup.pl flist all_data.elf
#

# all_data.elf
$totalname = $ARGV[1];

open(FLIST, $ARGV[0]);
$flist = <FLIST>;
close(FLIST);

open(FILE, $totalname);
foreach $basename (split(/\s+/, $flist)){
#    print $basename, "\n";
    &createbin();
    $outfile = $basename . "_total.bin";
    open(WFILE, "> $outfile");
    print WFILE eval(sprintf("pack(\"C*\", %s);", $data));
    close(WFILE);
}
close(FILE);



#
# 指定ラベルのデータをファイルから抜き出す
#
sub createbin {
    $data = '';
# evb
    &pickupbin(sprintf("BGTALK_%s_num:", $basename));
    &pickupbin(sprintf("BGTALK_%s:", $basename));
# evc
    &pickupbin(sprintf("FObj_%s_num:", $basename));
    &pickupbin(sprintf("FObj_%s:", $basename));
# evd
    &pickupbin(sprintf("Connect_%s_num:", $basename));
    &pickupbin(sprintf("Connect_%s:", $basename));
# evp
    &pickupbin(sprintf("PosEv_%s_num:", $basename));
    &pickupbin(sprintf("PosEv_%s:", $basename));
}


#
# ファイルから指定のラベルデータを抜き出す
# ※データはグローバル変数$dataへ蓄積される
#
sub pickupbin {
    my $label = $_[0];
    my $mode;

    seek(FILE, 0, 0);
    $mode = 0;
    while(<FILE>){
	if($mode == 0){
	    if(/$label/){
		$mode = 1;
	    }
	} else {
	    if(length($_) <= 2){
		return;
	    }
	    s/^0x........: //;
	    s/'.*'//;
	    s/\s+$/ /;
	    s/ (..)/0x$1,/g;
	    $data .= $_;
	}
    }
}


