#!/usr/bin/perl
##use strict;
##use warnings;

my $folder=$ENV{'PWD'};
chomp($folder);

my $number_input = 200;

for ($i=0;$i<$number_input;$i++)
{

	if ($i % 20 ==0)
	{
		$file_id = $i / 20;
		$outputFile=$folder."/SimFmsJet_P$file_id".".C";
		$outputFilename="SimFmsJet_P$file_id";
		print $outputFile;
		open(Output,"+>$outputFile") or die ("can not open $outputFile");
		print Output "void $outputFilename".'()'."\n";

		print Output '{'."\n";
		print Output ".L starSim\/RunFmsJetMakerSim.C;\n";		
	}

	chomp($inputlist[$i]);
	my $fill = $inputlist[$i];
	#my $inputFilePrint = $folder."/condorjobResults/DiffJetNanoDstfms_0124fill/NanoDiffJetTree_fill$fill.root";
	my $inputMuDstFilePrint = "../SimTest/pythia8_$i.MuDst.root";
	my $inputPythiaFilePrint = "../SimTest/pythia8_$i.starsim.pythia.root";
	
	my $outputFilePrint = $folder."/SimulationResult/SimJet_$i"."_0514.root";

	print Output 'RunFmsJetMakerSim(-1,"'."$inputMuDstFilePrint".'","'."$inputPythiaFilePrint".'","'."$outputFilePrint".'");'."\n";

	if ($i % 20 ==19)
	{
		print Output '}';
		close(Output);
	}

};

close(Output);

