// Filename: DiffJetAnaTreeQa.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Thu Jun 11 13:08:16 2020 (-0400)
// URL: jlab.org/~latif

#include "RootInclude.h"
#include "StRootInclude.h"
#include <vector>
#include <iostream>
#include "TGraph.h"

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetNum(TString inFileName, TString outName, TString det)
{
    TChain *ch = new TChain("T");
    
    TFile *file = new TFile(inFileName);   
    TFile *outFile = new TFile(outName, "recreate");

    TH1I *TrigFlag;
    TH1D *nJetsRun;
    TH1I *runId;
    TH1D *nTrigFMSJP0;
    TH1D *nTrigFMSJP1;
    TH1D *nTrigFMSJP2;
    TH1D *nTrigsmbs1;
    TH1D *nTrigsmbs2;
    TH1D *nTrigsmbs3;
    TH1D *nTriglgbs1;
    TH1D *nTriglgbs2;
    TH1D *nTriglgbs3;

    TH1D *nTrigEHT0;
    TH1D *nTrigJP1;
    TH1D *nTrigJP2;
    TH1D *nTrigE0J1L2E;
    TH1D *nTrigJ2J2JH;
    TH1D *nTrigBHT1VPDMB30;
    TH1D *nTrigBHT0BBCMB;
    TH1D *nTrigBHT1BBCMB;
    TH1D *nTrigBHT2BBCMB;

    TH1D *nJetsTrigFMSJP0;
    TH1D *nJetsTrigFMSJP1;
    TH1D *nJetsTrigFMSJP2;
    TH1D *nJetsTrigsmbs1;
    TH1D *nJetsTrigsmbs2;
    TH1D *nJetsTrigsmbs3;
    TH1D *nJetsTriglgbs1;
    TH1D *nJetsTriglgbs2;
    TH1D *nJetsTriglgbs3;

    TH1D *nJetsTrigEHT0;
    TH1D *nJetsTrigJP1;
    TH1D *nJetsTrigJP2;
    TH1D *nJetsTrigE0J1L2E;
    TH1D *nJetsTrigJ2J2JH;
    TH1D *nJetsTrigBHT1VPDMB30;
    TH1D *nJetsTrigBHT0BBCMB;
    TH1D *nJetsTrigBHT1BBCMB;
    TH1D *nJetsTrigBHT2BBCMB;

    TrigFlag = (TH1I*) file->Get("h1TrigFlag");
    nJetsRun = (TH1D*) file->Get("h1NJetsByRun");
    runId = (TH1I*) file->Get("h1runId");
    nTrigFMSJP0 = (TH1D*) file->Get("h1nFMSJP0");
    nTrigFMSJP1 = (TH1D*) file->Get("h1nFMSJP1");
    nTrigFMSJP2 = (TH1D*) file->Get("h1nFMSJP2");
    nTrigsmbs1 = (TH1D*) file->Get("h1nsmbs1");
    nTrigsmbs2 = (TH1D*) file->Get("h1nsmbs2");
    nTrigsmbs3 = (TH1D*) file->Get("h1nsmbs3");
    nTriglgbs1 = (TH1D*) file->Get("h1nlgbs1");
    nTriglgbs2 = (TH1D*) file->Get("h1nlgbs2");
    nTriglgbs3 = (TH1D*) file->Get("h1nlgbs3");

    nTrigEHT0 = (TH1D*) file->Get("h1nEHT0");
    nTrigJP1 = (TH1D*) file->Get("h1nJP1");
    nTrigJP2 = (TH1D*) file->Get("h1nJP2");
    nTrigE0J1L2E = (TH1D*) file->Get("h1nE0J1L2E");
    nTrigJ2J2JH = (TH1D*) file->Get("h1nJ2J2JH");
    nTrigBHT1VPDMB30 = (TH1D*) file->Get("h1nBHT1VPDMB30");
    nTrigBHT0BBCMB = (TH1D*) file->Get("h1nBHT0BBCMB");
    nTrigBHT1BBCMB = (TH1D*) file->Get("h1nBHT1BBCMB");
    nTrigBHT2BBCMB = (TH1D*) file->Get("h1nBHT2BBCMB");

    nJetsTrigFMSJP0 = (TH1D*) file->Get("h1nJets_FMSJP0");
    nJetsTrigFMSJP1 = (TH1D*) file->Get("h1nJets_FMSJP1");
    nJetsTrigFMSJP2 = (TH1D*) file->Get("h1nJets_FMSJP2");
    nJetsTrigsmbs1 = (TH1D*) file->Get("h1nJets_smbs1");
    nJetsTrigsmbs2 = (TH1D*) file->Get("h1nJets_smbs2");
    nJetsTrigsmbs3 = (TH1D*) file->Get("h1nJets_smbs3");
    nJetsTriglgbs1 = (TH1D*) file->Get("h1nJets_lgbs1");
    nJetsTriglgbs2 = (TH1D*) file->Get("h1nJets_lgbs2");
    nJetsTriglgbs3 = (TH1D*) file->Get("h1nJets_lgbs3");

    nJetsTrigEHT0 = (TH1D*) file->Get("h1nJets_EHT0");
    nJetsTrigJP1 = (TH1D*) file->Get("h1nJets_JP1");
    nJetsTrigJP2 = (TH1D*) file->Get("h1nJets_JP2");
    nJetsTrigE0J1L2E = (TH1D*) file->Get("h1nJets_E0J1L2E");
    nJetsTrigJ2J2JH = (TH1D*) file->Get("h1nJets_J2J2JH");
    nJetsTrigBHT1VPDMB30 = (TH1D*) file->Get("h1nJets_BHT1VPDMB30");
    nJetsTrigBHT0BBCMB = (TH1D*) file->Get("h1nJets_BHT0BBCMB");
    nJetsTrigBHT1BBCMB = (TH1D*) file->Get("h1nJets_BHT1BBCMB");
    nJetsTrigBHT2BBCMB = (TH1D*) file->Get("h1nJets_BHT2BBCMB");

	vector <Double_t> runlist;
	vector <Double_t> FMSJP0list;
	vector <Double_t> FMSJP1list;
	vector <Double_t> FMSJP2list;
	vector <Double_t> smbs1list;
        vector <Double_t> smbs2list;
        vector <Double_t> smbs3list;
	vector <Double_t> lgbs1list;
        vector <Double_t> lgbs2list;
        vector <Double_t> lgbs3list;

	vector <Double_t> EHT0list;
        vector <Double_t> JP1list;
        vector <Double_t> JP2list;
        vector <Double_t> E0J1L2Elist;
        vector <Double_t> J2J2JHlist;
        vector <Double_t> BHT1VPDMB30list;
        vector <Double_t> BHT0BBCMBlist;
        vector <Double_t> BHT1BBCMBlist;
        vector <Double_t> BHT2BBCMBlist;

	TString triggerNames_fms[9] = {"FMS-JP0", "FMS-JP1", "FMS-JP2", "FMS-sm-bs1", "FMS-sm-bs2", "FMS-sm-bs3", "FMS-lg-bs1", "FMS-lg-bs2", "FMS-lg-bs3"};
	TString triggerNames_eemc[9] = {"EHT0","JP1","JP2","EHT0*EJP1*L2Egamma","JP2*J2JetHigh","BHT1*VPDMB30","BHT0*BBCMB","BHT1*BBCMB","BHT2*BBCMB"};
	
	Double_t IDtrig[9] = {1,2,3,4,5,6,7,8,9};
	Double_t trigDist[9];

	if (det == "fms")
	{
		trigDist[0] = TrigFlag->GetBinContent(1);
		trigDist[1] = TrigFlag->GetBinContent(2);
		trigDist[2] = TrigFlag->GetBinContent(3);
		trigDist[3] = TrigFlag->GetBinContent(4);
		trigDist[4] = TrigFlag->GetBinContent(5);
		trigDist[5] = TrigFlag->GetBinContent(6);
		trigDist[6] = TrigFlag->GetBinContent(7);
		trigDist[7] = TrigFlag->GetBinContent(8);
		trigDist[8] = TrigFlag->GetBinContent(9);
	}

	if (det == "eemc")
        {
                trigDist[0] = TrigFlag->GetBinContent(1);
                trigDist[1] = TrigFlag->GetBinContent(2) ;
                trigDist[2] = TrigFlag->GetBinContent(3) ;
                trigDist[3] = TrigFlag->GetBinContent(4);
                trigDist[4] = TrigFlag->GetBinContent(5) ;
                trigDist[5] = TrigFlag->GetBinContent(6);
                trigDist[6] = TrigFlag->GetBinContent(7);
                trigDist[7] = TrigFlag->GetBinContent(8);
                trigDist[8] = TrigFlag->GetBinContent(9);
        }

	Double_t nJets, nTrig, nJetsAve;
	Double_t currentRun;

	for (Int_t i=1;i<2800;++i)
	{

		currentRun = i + 6400;
		if ((runId->GetBinContent(i) > 0)&&(det == "fms"))
		{
			runlist.push_back(currentRun);
			nJets = nJetsTrigFMSJP0->GetBinContent(i);
			nTrig = nTrigFMSJP0->GetBinContent(i);
			if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
			FMSJP0list.push_back(nJetsAve);
			nJets = nJetsTrigFMSJP1->GetBinContent(i);
			nTrig = nTrigFMSJP1->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        FMSJP1list.push_back(nJetsAve);
			nJets = nJetsTrigFMSJP2->GetBinContent(i);
			nTrig = nTrigFMSJP2->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        FMSJP2list.push_back(nJetsAve);

			nJets = nJetsTrigsmbs1->GetBinContent(i);
                        nTrig = nTrigsmbs1->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        smbs1list.push_back(nJetsAve);
			nJets = nJetsTrigsmbs2->GetBinContent(i);
                        nTrig = nTrigsmbs2->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        smbs2list.push_back(nJetsAve);
			nJets = nJetsTrigsmbs3->GetBinContent(i);
                        nTrig = nTrigsmbs3->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        smbs3list.push_back(nJetsAve);

			nJets = nJetsTriglgbs1->GetBinContent(i);
                        nTrig = nTriglgbs1->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        lgbs1list.push_back(nJetsAve);
			nJets = nJetsTriglgbs2->GetBinContent(i);
                        nTrig = nTriglgbs2->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        lgbs2list.push_back(nJetsAve);
                        nJets = nJetsTriglgbs3->GetBinContent(i);
                        nTrig = nTriglgbs3->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        lgbs3list.push_back(nJetsAve);
		}

		if ((runId->GetBinContent(i) > 0)&&(det == "eemc"))
		{
			runlist.push_back(currentRun);
			nJets = nJetsTrigEHT0->GetBinContent(i);
			nTrig = nTrigEHT0->GetBinContent(i);
			if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
			EHT0list.push_back(nJetsAve);
			nJets = nJetsTrigJP1->GetBinContent(i);
			nTrig = nTrigJP1->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        JP1list.push_back(nJetsAve);
			nJets = nJetsTrigJP2->GetBinContent(i);
			nTrig = nTrigJP2->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        JP2list.push_back(nJetsAve);

			nJets = nJetsTrigE0J1L2E->GetBinContent(i);
                        nTrig = nTrigE0J1L2E->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        E0J1L2Elist.push_back(nJetsAve);
			nJets = nJetsTrigJ2J2JH->GetBinContent(i);
                        nTrig = nTrigJ2J2JH->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        J2J2JHlist.push_back(nJetsAve);
			nJets = nJetsTrigBHT1VPDMB30->GetBinContent(i);
                        nTrig = nTrigBHT1VPDMB30->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        BHT1VPDMB30list.push_back(nJetsAve);

			nJets = nJetsTrigBHT0BBCMB->GetBinContent(i);
                        nTrig = nTrigBHT0BBCMB->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        BHT0BBCMBlist.push_back(nJetsAve);
			nJets = nJetsTrigBHT1BBCMB->GetBinContent(i);
                        nTrig = nTrigBHT1BBCMB->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        BHT1BBCMBlist.push_back(nJetsAve);
                        nJets = nJetsTrigBHT2BBCMB->GetBinContent(i);
                        nTrig = nTrigBHT2BBCMB->GetBinContent(i);
                        if (nTrig > 0) nJetsAve = nJets / nTrig; else nJetsAve = -1;
                        BHT2BBCMBlist.push_back(nJetsAve);
		}
	}

	if (det == "fms")
        {	
	TGraph* trigger_distribution_FMS = new TGraph(9,IDtrig,trigDist);
	TGraph* gr_FMSJP0 = new TGraph(runlist.size(),(&runlist[0]),(&FMSJP0list[0]));
	TGraph* gr_FMSJP1 = new TGraph(runlist.size(),(&runlist[0]),(&FMSJP1list[0]));
	TGraph* gr_FMSJP2 = new TGraph(runlist.size(),(&runlist[0]),(&FMSJP2list[0]));
	TGraph* gr_smbs1 = new TGraph(runlist.size(),(&runlist[0]),(&smbs1list[0]));
        TGraph* gr_smbs2 = new TGraph(runlist.size(),(&runlist[0]),(&smbs2list[0]));
        TGraph* gr_smbs3 = new TGraph(runlist.size(),(&runlist[0]),(&smbs3list[0]));
	TGraph* gr_lgbs1 = new TGraph(runlist.size(),(&runlist[0]),(&lgbs1list[0]));
        TGraph* gr_lgbs2 = new TGraph(runlist.size(),(&runlist[0]),(&lgbs2list[0]));
        TGraph* gr_lgbs3 = new TGraph(runlist.size(),(&runlist[0]),(&lgbs3list[0]));

	trigger_distribution_FMS->SetName("trigDist");
	gr_FMSJP0->SetName("FMSJP0");
	gr_FMSJP1->SetName("FMSJP1");
	gr_FMSJP2->SetName("FMSJP2");
	gr_smbs1->SetName("smbs1");
        gr_smbs2->SetName("smbs2");
        gr_smbs3->SetName("smbs3");
	gr_lgbs1->SetName("lgbs1");
        gr_lgbs2->SetName("lgbs2");
        gr_lgbs3->SetName("lgbs3");	

		trigger_distribution_FMS->SetTitle("FMS trigger distribution");

		TAxis *ax = trigger_distribution_FMS->GetHistogram()->GetXaxis();
   		Double_t x1 = ax->GetBinLowEdge(1); 
   		Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
		trigger_distribution_FMS->GetHistogram()->GetXaxis()->Set(9,x1,x2);

		for (Int_t i=0;i<9;++i) {trigger_distribution_FMS->GetHistogram()->GetXaxis()->SetBinLabel(i+1,triggerNames_fms[i]);}
		gr_FMSJP0->SetTitle("Average jets for FMS-JP0 trigger for run");
		gr_FMSJP0->GetXaxis()->SetTitle("run number [DDRR]");
		gr_FMSJP1->SetTitle("Average jets for FMS-JP1 trigger for run");
        	gr_FMSJP1->GetXaxis()->SetTitle("run number [DDRR]");
		gr_FMSJP2->SetTitle("Average jets for FMS-JP2 trigger for run");
        	gr_FMSJP2->GetXaxis()->SetTitle("run number [DDRR]");
		gr_smbs1->SetTitle("Average jets for FMS-sm-bs1 trigger for run");
        	gr_smbs1->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_smbs2->SetTitle("Average jets for FMS-sm-bs2 trigger for run");
        	gr_smbs2->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_smbs3->SetTitle("Average jets for FMS-sm-bs3 trigger for run");
        	gr_smbs3->GetXaxis()->SetTitle("run number [DDRR]");
		gr_lgbs1->SetTitle("Average jets for FMS-lg-bs1 trigger for run");
        	gr_lgbs1->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_lgbs2->SetTitle("Average jets for FMS-lg-bs2 trigger for run");
        	gr_lgbs2->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_lgbs3->SetTitle("Average jets for FMS-lg-bs3 trigger for run");
        	gr_lgbs3->GetXaxis()->SetTitle("run number [DDRR]");

		trigger_distribution_FMS->SetFillColor(40);

		trigger_distribution_FMS->Write();
		gr_FMSJP0->Write();
		gr_FMSJP1->Write();
		gr_FMSJP2->Write();
		gr_smbs1->Write();
        	gr_smbs2->Write();
        	gr_smbs3->Write();
		gr_lgbs1->Write();
        	gr_lgbs2->Write();
        	gr_lgbs3->Write();
	}

	if (det == "eemc")
        {	
	TGraph* trigger_distribution_EEMC = new TGraph(9,IDtrig,trigDist);
	TGraph* gr_EHT0 = new TGraph(runlist.size(),(&runlist[0]),(&EHT0list[0]));
	TGraph* gr_JP1 = new TGraph(runlist.size(),(&runlist[0]),(&JP1list[0]));
	TGraph* gr_JP2 = new TGraph(runlist.size(),(&runlist[0]),(&JP2list[0]));
	TGraph* gr_E0J1L2E = new TGraph(runlist.size(),(&runlist[0]),(&E0J1L2Elist[0]));
        TGraph* gr_J2J2JH = new TGraph(runlist.size(),(&runlist[0]),(&J2J2JHlist[0]));
        TGraph* gr_BHT1VPDMB30 = new TGraph(runlist.size(),(&runlist[0]),(&BHT1VPDMB30list[0]));
	TGraph* gr_BHT0BBCMB = new TGraph(runlist.size(),(&runlist[0]),(&BHT0BBCMBlist[0]));
        TGraph* gr_BHT1BBCMB = new TGraph(runlist.size(),(&runlist[0]),(&BHT1BBCMBlist[0]));
        TGraph* gr_BHT2BBCMB = new TGraph(runlist.size(),(&runlist[0]),(&BHT2BBCMBlist[0]));

	trigger_distribution_EEMC->SetName("trigDist");
	gr_EHT0->SetName("EHT0");
	gr_JP1->SetName("JP1");
	gr_JP2->SetName("JP2");
	gr_E0J1L2E->SetName("E0J1L2E");
        gr_J2J2JH->SetName("J2J2JH");
        gr_BHT1VPDMB30->SetName("BHT1VPDMB30");
	gr_BHT0BBCMB->SetName("BHT0BBCMB");
        gr_BHT1BBCMB->SetName("BHT1BBCMB");
        gr_BHT2BBCMB->SetName("BHT2BBCMB");	

		trigger_distribution_EEMC->SetTitle("EEMC trigger distribution");

		TAxis *ax = trigger_distribution_EEMC->GetHistogram()->GetXaxis();
   		Double_t x1 = ax->GetBinLowEdge(1); 
   		Double_t x2 = ax->GetBinUpEdge(ax->GetNbins());
		trigger_distribution_EEMC->GetHistogram()->GetXaxis()->Set(9,x1,x2);

		for (Int_t i=0;i<9;++i) {trigger_distribution_EEMC->GetHistogram()->GetXaxis()->SetBinLabel(i+1,triggerNames_eemc[i]);}
		gr_EHT0->SetTitle("Average jets for EHT0 trigger for run");
		gr_EHT0->GetXaxis()->SetTitle("run number [DDRR]");
		gr_JP1->SetTitle("Average jets for JP1 trigger for run");
        	gr_JP1->GetXaxis()->SetTitle("run number [DDRR]");
		gr_JP2->SetTitle("Average jets for JP2 trigger for run");
        	gr_JP2->GetXaxis()->SetTitle("run number [DDRR]");
		gr_E0J1L2E->SetTitle("Average jets for EHTo*EJP1*L2Egamma trigger for run");
        	gr_E0J1L2E->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_J2J2JH->SetTitle("Average jets for JP2*J2JetHigh trigger for run");
        	gr_J2J2JH->GetXaxis()->SetTitle("run number [DDRR]");
        	gr_BHT1VPDMB30->SetTitle("Average jets for BHT1*VPDMB30 trigger for run");
        	gr_BHT1VPDMB30->GetXaxis()->SetTitle("run nR]");
		gr_BHT0BBCMB->SetTitle("Average jets for BHT0*BBCMB trigger for run");
        	gr_BHT0BBCMB->GetXaxis()->SetTitle("run nR]");
        	gr_BHT1BBCMB->SetTitle("Average jets for BHT1*BBCMB trigger for run");
        	gr_BHT1BBCMB->GetXaxis()->SetTitle("run nR]");
        	gr_BHT2BBCMB->SetTitle("Average jets for BHT2*BBCMB trigger for run");
        	gr_BHT2BBCMB->GetXaxis()->SetTitle("run number [DDRR]");

		trigger_distribution_EEMC->SetFillColor(40);

		trigger_distribution_EEMC->Write();
		gr_EHT0->Write();
        	gr_JP1->Write();
        	gr_JP2->Write();
        	gr_E0J1L2E->Write();
        	gr_J2J2JH->Write();
        	gr_BHT1VPDMB30->Write();
        	gr_BHT0BBCMB->Write();
        	gr_BHT1BBCMB->Write();
        	gr_BHT2BBCMB->Write();

	}


    outFile->Write();
    outFile->Close();
    delete ch;
}
