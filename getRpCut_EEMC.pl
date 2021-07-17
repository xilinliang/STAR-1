#!/usr/bin/perl
##use strict;
##use warnings;

my $folder=$ENV{'PWD'};
chomp($folder);
$inputFile=$folder.'/EemcFillList.in';
open(Input,"<$inputFile") or die ("can not open $inputFile");

@inputlist=<Input>;
$number_input = @inputlist;


for ($i=0;$i<$number_input;$i++)
{

	if ($i % 6 ==0)
	{
		$file_id = $i / 6;
		$outputFile=$folder."/EemcRpCut_P$file_id".".C";
		$outputFilename="EemcRpCut_P$file_id";
		print $outputFile;
		open(Output,"+>$outputFile") or die ("can not open $outputFile");
		print Output "void $outputFilename".'()'."\n";
		
		print Output '{'."\n";
	}

	chomp($inputlist[$i]);
	my $fill = $inputlist[$i];
	#my $inputFilePrint = $folder."/condorjobResults/DiffJetNanoDstfms_0124fill/NanoDiffJetTree_fill$fill.root";
	my $inputFilePrint = $folder."/condorjobResults/NanoDiffJetTree_fill$fill.root";
	my $outputFilePrint = $folder."/root_result/EemcRpCut/DiffJetRpCut$fill"."_0313.root";

	print Output 'DiffJetRpTreeQa("'."$inputFilePrint".'","'."$outputFilePrint".'","eemc");'."\n";

	if ($i % 6 == 5)
	{
		print Output '}';
		close(Output);
	}

};

	if ($number_input % 6 > 0)
        {
                print Output '}';
                close(Output);
        }

close(Input);
close(Output);

