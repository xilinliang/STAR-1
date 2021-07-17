#!/usr/bin/perl
##use strict;
##use warnings;

my $folder=$ENV{'PWD'};
chomp($folder);
$inputFile=$folder.'/FmsFillList.in';
open(Input,"<$inputFile") or die ("can not open $inputFile");

@inputlist=<Input>;
$number_input = @inputlist;
my $totaljobs = 54;


for ($i=0;$i<$number_input;$i++)
{

	if ($i % 6 ==0)
	{
		$file_id = $i / 6;
		$outputFile=$folder."/FmsHotChQa_P$file_id".".C";
		$outputFilename="FmsHotChQa_P$file_id";
		print $outputFile;
		open(Output,"+>$outputFile") or die ("can not open $outputFile");
		print Output "void $outputFilename".'()'."\n";
		
		print Output '{'."\n";
	}

	chomp($inputlist[$i]);
	my $fill = $inputlist[$i];
	my $inputFilePrint = $folder."/condorjobResults/DiffJetNanoDstfms_0124fill/NanoDiffJetTree_fill$fill.root";
	my $outputFilePrint = $folder."/root_result/FmsQaByFill/FmsQaFill$fill"."_0124a.root";

	print Output 'AnFmsCellStatus('."$fill".');'."\n";

	if ($i % 6 ==5)
	{
		print Output '}';
		close(Output);
	}

};

close(Input);
close(Output);

