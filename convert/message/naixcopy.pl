#!/usr/bin/perl

#----------------------------------------------------------------------------
# 収納ファイル数やファイル並びに変更があったアーカイブのnaixのみcopyする
#----------------------------------------------------------------------------

use File::Copy;

call &main();
exit(0);


sub main {
	if( @ARGV != 2 )
	{
		print "usage perl naixcopy.pl <srcfile> <dstfile>\n";
		return;
	}

	my  $src_file_path = $ARGV[0];
	my  $dst_file_path = $ARGV[1];

	if( open(SRC, "<$src_file_path") )
	{
		my @src = <SRC>;
		close(SRC);
		if( open(DST, "<$dst_file_path") )
		{
			my @dst = <DST>;
			close(DST);

			my $max = @src;

			if($max != @dst)
			{
				copyfile( $src_file_path, $dst_file_path );
				return;
			}

			my $i=0;
			for($i=0; $i<$max; $i++)
			{
				if( $i == 6 ){ next; }
				if( $src[$i] ne $dst[$i] )
				{
					copyfile( $src_file_path, $dst_file_path );
					return;
				}
			}
		}
		else
		{
			copyfile( $src_file_path, $dst_file_path );
			return;
		}
		print "not necessary to copy that's file..\n";
	}
	else
	{
		print "can't open $src_file_path!!\n";
	}
}


sub copyfile {
	my $src = shift;
	my $dst = shift;

#	$src =~ s/\//\\\\/g;
#	$dst =~ s/\//\\\\/g;
#	my $sysarg = "xcopy /Y $src $dst";
#	print "$sysarg\n";
#	system($sysarg);

	copy $src, $dst;
	print "updated $dst";
}
