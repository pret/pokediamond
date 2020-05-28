#!perl

$basename = $ARGV[0];
$totalname = $ARGV[1];
#$totalname = $basename . ".elf";
$basename =~ s/_total//;

# evb
$str = sprintf("BGTALK_%s_num:", $basename);
&pickupbin($totalname, $str);
$str = sprintf("BGTALK_%s:", $basename);
&pickupbin($totalname, $str);

# evc
$str = sprintf("FObj_%s_num:", $basename);
&pickupbin($totalname, $str);
$str = sprintf("FObj_%s:", $basename);
&pickupbin($totalname, $str);

# evd
$str = sprintf("Connect_%s_num:", $basename);
&pickupbin($totalname, $str);
$str = sprintf("Connect_%s:", $basename);
&pickupbin($totalname, $str);

# evp
$str = sprintf("PosEv_%s_num:", $basename);
&pickupbin($totalname, $str);
$str = sprintf("PosEv_%s:", $basename);
&pickupbin($totalname, $str);


sub pickupbin {
    my $file = $_[0];
    my $label = $_[1];
    my $align, $size, $rodata, $head, $mode;

	#printf("%s: %s\n", $file, $label);
    open(FILE, $file);
    $mode = 0;
    while(<FILE>){
	if($mode == 0){
	    $align = $_ if(/  Section Alignment :/);
	    $size  = $_ if(/  Section Size      :/);
	    $head  = $_ if(/Header:/);
	    $rodata = $_ if(/\(\.rodata\)/);
	    if(/$label/){
		print $rodata, "\n", $head, $align, $size;
		print;
		$mode = 1;
	    }
	} else {
	    if(length($_) <= 2){
		print "\n";
		close(FILE);
		return;
	    }
	    print;
	}

    }
    close(FILE);

    

}


