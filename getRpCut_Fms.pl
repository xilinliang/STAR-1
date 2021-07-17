#!/usr/bin/perl
##use strict;
##use warnings;

my $current_folder=$ENV{'PWD'};
chomp($current_folder);
my $folder='/star/data01/pwg/liangxl/BrightSTAR_EMjet';
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
		$outputFile=$current_folder."/FmsRpCut_P$file_id".".C";
		$outputFilename="FmsRpCut_P$file_id";
		print $outputFile;
		open(Output,"+>$outputFile") or die ("can not open $outputFile");
		print Output "void $outputFilename".'()'."\n";
		
		print Output '{'."\n";
	}

	chomp($inputlist[$i]);
	my $fill = $inputlist[$i];
	#my $inputFilePrint = $folder."/condorjobResults/DiffJetNanoDstfms_0124fill/NanoDiffJetTree_fill$fill.root";
	my $inputFilePrint = $folder."/condorjobResults/NanoDiffJetTree_fill$fill.root";
	my $outputFilePrint = $folder."/root_result/FmsRpCut/DiffJetRpCut$fill"."_0707a.root";

	print Output 'DiffJetRpTreeCut("'."$inputFilePrint".'","'."$outputFilePrint".'","fms");'."\n";

	if ($i % 6 ==5)
	{
		print Output '}';
		close(Output);
	}

};

close(Input);
close(Output);

