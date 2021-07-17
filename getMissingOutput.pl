#!/usr/bin/perl
##use strict;
##use warnings;

my $folder=$ENV{'PWD'};
chomp($folder);
$inputFile=$folder.'/File9830rootresult.in';
$outputFile=$folder.'/File9830badlist.csh';
open(Input,"<$inputFile") or die ("can not open $inputFile");
open(Output,"+>$outputFile") or die ("can not open $outputFile");
print Output "#!/usr/bin/csh \n";
print Output 'star-submit -r ';

@inputlist=<Input>;
$number_input = @inputlist;
my $totaljobs =108;

for ($i=0;$i<$totaljobs;$i++) {$checkfile[$i]=0;}

for ($i=0;$i<$number_input;$i++)
{

	chomp($inputlist[$i]);
	my $outputname = $inputlist[$i];
	my $outputname = substr($outputname,0,-5);
	my $outputid = substr($outputname,70,4);
	print "$outputid ";
	$checkfile[$outputid] = 1;

};

for ($i=0;$i<$totaljobs;$i++)
{
	if ($checkfile[$i] eq 0) {print Output "$i,";};
}

print Output " 9830F97271BB0260159B90432DA23278.session.xml \n";
system("chmod 744 $outputFile")==0 or die "can not chmod";

close(Input);
close(Output);

