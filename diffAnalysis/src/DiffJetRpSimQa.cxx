// Filename: DiffJetRpSimQa.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Thu Jun 11 13:08:16 2020 (-0400)
// URL: jlab.org/~latif

#include "StRootInclude.h"
#include "RootInclude.h"
#include "BrightStInclude.h"
#include <iostream>
#include "StMuDSTMaker/COMMON/StMuRpsCollection.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrack.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrackPoint.h"
#include "MCOutput/MCOutput.h"

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetRpSimQa(TString inFileName, TString outName)
{
    TChain *tree = new TChain("MCOutput");
    tree->Add(inFileName);

    //TFile* mFile=TFile(inFileName);
    //TTree *tree = (TTree*) mFile->Get("MCOutput");
    
    StMuRpsTrack *rpsTrack =0;    
    //StMuRpsCollection *mRpsColl = 0;

    //TClonesArray *rpsArr = new TClonesArray("StMuRpsCollection");
    MCOutput *rpsArr=0;

    //TBranch *br = tree->GetBranch("mRpsCollection");
    //tree->SetBranchAddress("mRpsCollection",&rpsArr);
    tree->SetBranchAddress("MCOutput",&rpsArr);

    
    
    TFile *outFile = new TFile(outName, "recreate");
    TH1D *h1_nRpTracks = new TH1D("h1_nRpTracks", "Number of RP tracks", 10, 0, 10);     
    TH1D *h1_wRpPt = new TH1D("h1_trkPtWest", "All West RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);
    TH1D *h1_eRpPt = new TH1D("h1_trkPtEast", "All East RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);    
    TH1D *h1_wRpP = new TH1D("h1_trkPWest", "All West RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_eRpP = new TH1D("h1_trkPEast", "All East RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_RpNPlanes = new TH1D("h1_RpNPlanes","Number of RP planes;N Planes",9,0,9);
    TH1D *h1_ThetaX = new TH1D("h1_ThetaX" , "All RP track #theta_{X} ; #theta_{X} [mrad]", 60,-15,15);
    TH1D *h1_ThetaY = new TH1D("h1_ThetaY" , "All RP track #theta_{Y} ; #theta_{Y} [mrad]", 60,-15,15);
    TH2D *h2_ThetaXY = new TH2D("h2_ThetaXY" , "All RP track #theta_{Y} vs #theta_{X} ; #theta_{X} [mrad] ; #theta_{Y} [mrad]" , 60,-15,15 , 60,-15,15);

    TH1D *h1_onlyEastRpPt = new TH1D("h1_onlyEasttrkPtEast", "only East RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);    
    TH1D *h1_onlyEastRpP = new TH1D("h1_onlyEasttrkPEast", "only East RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_onlyEastRpNPlanes = new TH1D("h1_onlyEastRpNPlanes","only East Number of RP planes;N Planes",9,0,9);
    TH1D *h1_onlyEastThetaX = new TH1D("h1_onlyEastThetaX" , "only East RP track #theta_{X} ; #theta_{X} [mrad]", 60,-15,15);
    TH1D *h1_onlyEastThetaY = new TH1D("h1_onlyEastThetaY" , "only East RP track #theta_{Y} ; #theta_{Y} [mrad]", 60,-15,15);
    TH2D *h2_onlyEastThetaXY = new TH2D("h2_onlyEastThetaXY" , "only East RP track #theta_{Y} vs #theta_{X} ; #theta_{X} [mrad] ; #theta_{Y} [mrad]" , 60,-15,15 , 60,-15,15);
    TH1D *h1_onlyEastEta = new TH1D("h1_onlyEastEta" , "only East RP track #eta ; #eta", 100,-10,10);
    TH1D *h1_onlyEastPhi = new TH1D("h1_onlyEastPhi" , "only East RP track #phi ; #phi [rad]", 100,-3.14,3.14);

    TH1D *h1_onlyWestRpPt = new TH1D("h1_onlyWesttrkPtEast", "only West RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 10);    
    TH1D *h1_onlyWestRpP = new TH1D("h1_onlyWesttrkPEast", "only West RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_onlyWestRpNPlanes = new TH1D("h1_onlyWestRpNPlanes","only West Number of RP planes;N Planes",9,0,9);
    TH1D *h1_onlyWestThetaX = new TH1D("h1_onlyWestThetaX" , "only West RP track #theta_{X} ; #theta_{X} [mrad]", 60,-15,15);
    TH1D *h1_onlyWestThetaY = new TH1D("h1_onlyWestThetaY" , "only West RP track #theta_{Y} ; #theta_{Y} [mrad]", 60,-15,15);
    TH2D *h2_onlyWestThetaXY = new TH2D("h2_onlyWestThetaXY" , "only West RP track #theta_{Y} vs #theta_{X} ; #theta_{X} [mrad] ; #theta_{Y} [mrad]" , 60,-15,15 , 60,-15,15);
    TH1D *h1_onlyWestEta = new TH1D("h1_onlyWestEta" , "only West RP track #eta ; #eta", 100,-10,10);
    TH1D *h1_onlyWestPhi = new TH1D("h1_onlyWestPhi" , "only West RP track #phi ; #phi [rad]", 100,-3.14,3.14);
   

 
    //cout << "Total Entries to be processed: "<< br->GetEntries() <<endl;
    cout << "Total Entries to be processed: "<< tree->GetEntries() <<endl;

    for(Int_t evt = 0; evt < tree->GetEntries(); ++evt)
    {
	//tree->GetEntry(evt);

	if(evt % 1000 == 0)
	    cout << "Events Processed: "<< evt <<endl;


		//rp tracks
		tree->GetEntry(evt);
		//mRpsColl = rpsArr->getRpsCollection();
		//rpsArr->getRpsCollection(mRpsColl);
	    	//Int_t nRpsTracks = mRpsColl->numberOfTracks();
	    	Int_t nRpsTracks = rpsArr->getRpsCollection().numberOfTracks();

	    	//Int_t nRpsTracks = rpsArr->numberOfTracks();
		
		//cout<<"nRpsTracks"<<nRpsTracks<<endl;
		h1_nRpTracks->Fill(nRpsTracks);
		for (Int_t rpTrk=0; rpTrk<nRpsTracks;++rpTrk)
		{
	
			//rpsTrack = (StMuRpsTrack*)mRpsColl->track(rpTrk);
			rpsTrack = (StMuRpsTrack*)rpsArr->getRpsCollection().track(rpTrk);

			h1_RpNPlanes->Fill(rpsTrack->planesUsed());	
			if (rpsTrack->planesUsed()<7) continue;
	
			if(rpsTrack->branch() == 2 || rpsTrack->branch() == 3) //West RP :: 2 West Up RP, 3: East Down RP
            		{
                	h1_wRpP->Fill(rpsTrack->p());
                	h1_wRpPt->Fill(rpsTrack->pt());
			

			}

			if(rpsTrack->branch() == 0 || rpsTrack->branch() == 1) //East RP :: O East Up RP, 1: East Down RP
                        {
			h1_eRpP->Fill(rpsTrack->p());
			h1_eRpPt->Fill(rpsTrack->pt());

			}
	
			h1_ThetaX->Fill(1000*rpsTrack->theta(0));
			h1_ThetaY->Fill(1000*rpsTrack->theta(1));
			h2_ThetaXY->Fill(1000*rpsTrack->theta(0),1000*rpsTrack->theta(1));


		}

		if (nRpsTracks == 1)
		{

			
			rpsTrack = (StMuRpsTrack*)rpsArr->getRpsCollection().track(0);
			if(rpsTrack->branch() == 2 || rpsTrack->branch() == 3) //West RP :: 2 West Up RP, 3: East Down RP
            		{
			h1_onlyWestRpNPlanes->Fill(rpsTrack->planesUsed());	
			if (rpsTrack->planesUsed()<7) continue;
			h1_onlyWestThetaX->Fill(1000*rpsTrack->theta(0));
			h1_onlyWestThetaY->Fill(1000*rpsTrack->theta(1));
			h2_onlyWestThetaXY->Fill(1000*rpsTrack->theta(0),1000*rpsTrack->theta(1));
			if (rpsTrack->theta(0) < -0.002 || rpsTrack->theta(0) > 0.002) continue;
			if (fabs(rpsTrack->theta(1)) <  0.0015 || fabs(rpsTrack->theta(1)) > 0.0045) continue;
			h1_onlyWestEta->Fill(rpsTrack->eta());
			h1_onlyWestPhi->Fill(rpsTrack->phi());
                	h1_onlyWestRpP->Fill(rpsTrack->p());
                	h1_onlyWestRpPt->Fill(rpsTrack->pt());
			

			}

			if(rpsTrack->branch() == 0 || rpsTrack->branch() == 1) //East RP :: O East Up RP, 1: East Down RP
                        {
			h1_onlyEastRpNPlanes->Fill(rpsTrack->planesUsed());	
			if (rpsTrack->planesUsed()<7) continue;
			h1_onlyEastThetaX->Fill(1000*rpsTrack->theta(0));
			h1_onlyEastThetaY->Fill(1000*rpsTrack->theta(1));
			h2_onlyEastThetaXY->Fill(1000*rpsTrack->theta(0),1000*rpsTrack->theta(1));
			if (rpsTrack->theta(0) < -0.002 || rpsTrack->theta(0) > 0.002) continue;
			if (fabs(rpsTrack->theta(1)) <  0.0015 || fabs(rpsTrack->theta(1)) > 0.0045) continue;
			h1_onlyEastEta->Fill(rpsTrack->eta());
			h1_onlyEastPhi->Fill(rpsTrack->phi());
			h1_onlyEastRpP->Fill(rpsTrack->p());
			h1_onlyEastRpPt->Fill(rpsTrack->pt());

			}

		}


    }



    outFile->Write();
    outFile->Close();
    //delete ch;
}
