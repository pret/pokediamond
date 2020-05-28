#!/usr/bin/perl

&main();
exit(0);

sub main {
	my $DependSrcName = $ARGV[0];
	my $DataDir = $ARGV[1];
	my $DependListName = $ARGV[2];
	my $TargetListName = $ARGV[3];
	my $LangFlag = $ARGV[4];

	if(open(SRC, "<$DependSrcName"))
	{
		my @src = <SRC>;
		my @targets;
		my $i;

		close(SRC);

		for($i=0; $i<@src; $i++)
		{
			$src[$i] =~ s/[\r\n]//g;
			push (@targets, &make_target_path($DataDir, $src[$i]));
		}

		print_targets(\@targets, $TargetListName);
		print_depends(\@src, \@targets, $LangFlag, $DependListName);

	}

}


sub make_target_path {
	my $dir = shift;
	my $file = shift;

	if($file =~ /\//)
	{
		my @tmp = split(/\//, $file);
		$file = $tmp[(@tmp-1)];
	}

	$file =~ s/gmm$/dat/;
	return $dir . '/' . $file;
}


sub print_targets {
	my $ref = shift;
	my $filename = shift;

	if(open(TARGET_FILE, ">$filename"))
	{
		print TARGET_FILE "TARGETS = \\\n";
		foreach (@$ref)
		{
			print TARGET_FILE "\t$_ \\\n";
		}
		close(TARGET_FILE);
	}
}

sub print_depends {
	my $src_ref = shift;
	my $target_ref = shift;
	my $lang = shift;
	my $filename = shift;

	if(open(DEPEND_FILE, ">$filename"))
	{
		my $i;
		for($i=0; $i<@$src_ref; $i++)
		{
			print DEPEND_FILE "$$target_ref[$i]:\t$$src_ref[$i]\n";
			print DEPEND_FILE "\t perl msgconv.pl $$src_ref[$i] $lang\n\n";
		}
		close(DEPEND_FILE);
	}
}
