#!/usr/bin/perl

#===============================================================================
# �{�b�N�X�ǎ��p�X���[�h�o��
#
# �v���C���[ID�Ɨ~�����ǎ��̃i���o�[�������Ƃ��Ď󂯎��A�p�X���[�h���o�͂���
# pmsconv.pl �̏o�͂���p�X���[�h�P�ꃊ�X�g�ipwdlist.dat�j���Q�Ƃ���B
#
# GameFreak taya
#
#===============================================================================


my $LISTFILE_NAME = "pwdlist.dat";


#==============================================================
#==============================================================


exit (&main() );


sub usage {
	my ($pack,$filename,$line) = caller;
	print "===========================================\n";
	print "usage: >perl $filename <id> <wp_num>\n";
	print "===========================================\n";
	print "<id>\n";
	print "    �v���C���[ID\n";
	print "<wp_num>\n";
	print "    �~�����ǎ��̃i���o�[\n";
}


sub main {

	if (@ARGV != 2 )
	{
		&usage();
		return 1;
	}

	my $id = $ARGV[0];
	my $wp_num = $ARGV[1];

	if( ($id =~ /[^0-9]/)
	||	($wp_num =~ /[^0-9]/)
	){
		&usage();
		return 1;
	}
	if( ($id > 65535) || ($wp_num > 255) )
	{
		&usage();
		return 1;
	}

	unless( open( LIST, "<$LISTFILE_NAME") )
	{
		print "$LISTFILE_NAME ���J���܂���\n";
		return 1;
	}

	my $i;

	my @wordList = <LIST>;
	close(LIST);
	my $listMax = @wordList;
	for($i=0; $i<$listMax; $i++)
	{
		$wordList[$i] =~ s/[\r\n]//g;
	}

	my $rand1 = int(rand(16));
	my $rand2 = int(rand(16));
	my $id_lo = $id & 255;
	my $id_hi = ($id >> 8) & 255;


	my @bitAry = ();
	push @bitAry, &num2bit( $wp_num );
	push @bitAry, &num2bit( $wp_num ^ $id_hi );
	push @bitAry, &num2bit( $wp_num ^ $id_lo );
	push @bitAry, &num2bit( ($rand1 << 4) + ($rand2) );

	print "wpnum:$wp_num,  ID_hi:$id_hi, ID_lo:$id_lo, rand1:$rand1, rand2:$rand2 listMax:$listMax\n";

	my $i;
	my $xor_mask = ($rand1<<4) | $rand1;
	&lotate_R( \@bitAry, 3, $rand2 );
	for($i=0; $i<3; $i++)
	{
		$bitAry[$i] = &num2bit( &bit2num($bitAry[$i]) ^ $xor_mask );
	}
	&lotate_R( \@bitAry, 4, 7 );

	my @numAry = ();
	&bitary2numary(\@bitAry, \@numAry);

	if( &verify(\@numAry, $wp_num, $id_hi, $id_lo, $rand1, $rand2) == 0 )
	{
		printf "�A���S���Y���G���[\n";
		return 1;
	}

	#----------------------------------------------
	# �Ō�ɈÍ����o��
	#----------------------------------------------
	my $word_num = 0;
	my $prev_num = 0;
	my $num;
	my $idx;
	for($i=0; $i<4; $i++)
	{
		$num = &bit2num( $bitAry[$i] );
		$prev_num = $word_num;
		$word_num += $num;
		$idx = $word_num;
		if( $idx >= $listMax )
		{
			$idx -= $listMax;
		}
		print "$wordList[$idx]  ( $prev_num + $num = $word_num -> $idx)\n";
		$word_num = $idx;
	}

	return 0;
}

#----------------------------------------------
# ���l��bit������i8bit�j
#----------------------------------------------
sub num2bit {
	my $num = shift;
	my $bit = "";

	for(my $i=0; $i<8; $i++)
	{
		if( $num & (1<<$i) )
		{
			$bit = "1" . $bit;
		}
		else
		{
			$bit = "0" . $bit;
		}
	}
	return $bit;
}
#----------------------------------------------
# bit�����񁨐��l�i8bit�j
#----------------------------------------------
sub bit2num {
	my $bit = shift;
	my $num = 0;
	my @bitstr = split( //, $bit );
	my $p = 1;

	for( my $i=7; $i>=0; $i-- )
	{
		if( $bitstr[$i] eq "1" )
		{
			$num += $p;
		}
		$p *= 2;
	}
	return $num;
}

#----------------------------------------------
# ���l�z��bit�����z��
#----------------------------------------------
sub bitary2numary {
	my $refBitAry = shift;
	my $refNumAry = shift;

	@$refNumAry = ();
	for(my $i=0; $i<4; $i++)
	{
		push @$refNumAry, &bit2num($$refBitAry[$i]);
	}
}
#----------------------------------------------
# bit�����z�񁨐��l�z��
#----------------------------------------------
sub numary2bitary {
	my $refNumAry = shift;
	my $refBitAry = shift;

	@$refBitAry = ();
	for(my $i=0; $i<4; $i++)
	{
		push @$refBitAry, &num2bit($$refNumAry[$i]);
	}
}

#----------------------------------------------
# bit�����z��̉E���[�e�[�g
# input	0: �r�b�g��z��̃��t�@�����X
#		1: �Ώۗv�f��
#		2: ���[�e�[�g��
#----------------------------------------------
sub lotate_R {
	my $refAry = shift;
	my $targetNum = shift;
	my $lotNum = shift;

	my @bitAry = ();
	my $i;
	my $n;
	my $bit;


	for($i=0; $i<$targetNum; $i++)
	{
		push @bitAry, split( //, $$refAry[$i] );
	}

	for($i=0; $i<$lotNum; $i++)
	{
		$n = pop @bitAry;
		unshift @bitAry, $n;
	}

	for($i=0; $i<$targetNum; $i++)
	{
		$bit = "";
		for($n=0; $n<8; $n++)
		{
			$bit .= $bitAry[ $i*8+$n ];
		}
		$$refAry[$i] = $bit;
	}


}
#----------------------------------------------
# bit�����z��̍����[�e�[�g
# input	0: �r�b�g��z��̃��t�@�����X
#		1: �Ώۗv�f��
#		2: ���[�e�[�g��
#----------------------------------------------
sub lotate_L {
	my $refAry = shift;
	my $targetNum = shift;
	my $lotNum = shift;

	my @bitAry = ();
	my $i;
	my $n;
	my $bit;

	for($i=0; $i<$targetNum; $i++)
	{
		push @bitAry, split( //, $$refAry[$i] );
	}

	for($i=0; $i<$lotNum; $i++)
	{
		$n = shift @bitAry;
		push @bitAry, $n;
	}

	for($i=0; $i<$targetNum; $i++)
	{
		$bit = "";
		for($n=0; $n<8; $n++)
		{
			$bit = $bit . $bitAry[ $i*8+$n ];
		}
		$$refAry[$i] = $bit;
	}
}

#---------------------------------------------------------------
# �Í����������̂𕜍����āA�e��p�����[�^�ƈ�v���邩�`�F�b�N
#
# return : 0�ŕs��v�^1�ň�v
#---------------------------------------------------------------
sub verify {
	my ($refNumAry, $wp_num, $id_hi, $id_lo, $rand1, $rand2) = @_;

	my @bitAry = ();
	my @numAry = ();
	my $i;

	&numary2bitary( $refNumAry, \@bitAry );
	&lotate_L( \@bitAry, 4, 7 );
	&bitary2numary( \@bitAry, \@numAry );
	if( (($rand1<<4)|($rand2)) != $numAry[3] )
	{
		print "err 1\n";
		return 0;
	}

	for($i=0; $i<3; $i++)
	{
		$numAry[$i] ^= (($rand1<<4)|$rand1);
	}
	&numary2bitary( \@numAry, \@bitAry );
	&lotate_L( \@bitAry, 3, $rand2 );
	&bitary2numary( \@bitAry, \@numAry );

	if( $wp_num != $numAry[0] )
	{
		print "err 2\n";
		return 0;
	}

	if( ($id_hi ^ $numAry[1]) != $wp_num )
	{
		print "err 3\n";
		return 0;
	}

	if( ($id_lo ^ $numAry[2]) != $wp_num )
	{
		print "err 4\n";
		return 0;
	}

	return 1;
}



sub print_bitary {
	my $refAry = shift;
	my $str = shift;

	print "<<$str>>\n  ";
	for(my $i=0; $i<4; $i++)
	{
		print "$$refAry[$i] ";
	}
	print "\n";

}
