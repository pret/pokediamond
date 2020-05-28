#!/usr/bin/perl

call &main();
exit(0);

sub main {
	my $root_dir = $ARGV[0];
	if( $root_dir eq "" )
	{
		$root_dir = 'src';
	}
	else
	{
		# ルート指定があった場合、\ を / にしておく
		$root_dir =~ s/\\/\//g;
	}


	system ("find $root_dir|grep gmm\$ > tmp.dat\n");
	if( open( FILE, "<tmp.dat") )
	{
		my @files = <FILE>;
		close(FILE);
		system "rm tmp.dat";
		my $cmd;

		foreach my $filename (@files)
		{
			$filename =~ s/\r\n//g;

			print "$filename ";

			$cmd = "MessageEditor -nw -ot -s $filename -i template.gmt $filename\n";
			system $cmd;

			$cmd = "MessageEditor -nw -cf Q:/msgdata/font/ -s $filename $filename\n";
			system $cmd;

			print " ...done\n";
		}
	}

	
}
#>MessageEditor -nw -ot -s A.gmm -i B.gmt A.gmm
#>MessageEditor -nw -cf c:\usr\ -s A.gmm A.gmm

