// Filename: DiffJetRpTreeQa.cxx
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Thu Jun 11 13:08:16 2020 (-0400)
// URL: jlab.org/~latif

#include "RootInclude.h"
#include "StRootInclude.h"
#include "BrJetMaker/TStJetCandidate.h"
#include "BrJetMaker/TStJetEvent.h"
#include "BrJetMaker/TStJetSkimEvent.h"
#include "BrContainers/TStRpsTrackData.h"
#include <iostream>

using namespace std;

//Use wildcat in the file name to combine many files.
void DiffJetXFNphotonsCalc(TString inFileName, TString outName, TString det)
{
    TChain *ch = new TChain("T");
    ch->Add(inFileName);
    
    TStJetEvent *jetEvent = 0;
    TStJetSkimEvent *skimEvent;
    TStJetCandidate *jet;
    TStJetTower *tower;
    TStJetParticle *particle;
    TStRpsTrackData *rpsTrack =0;    

    TClonesArray *rpsArr = new TClonesArray("TStRpsTrackData");

    ch->SetBranchAddress("jetEvents", &jetEvent);
    ch->SetBranchAddress("rpTrack",&rpsArr);

    
    TFile *outFile = new TFile(outName, "recreate");
    TH1D *h1nJets_all = new TH1D("h1nJets_all", "Number of Jets from All [TPC/BEMC + EEMC + FMS]", 10, 0, 10);
    TH1D *h1nJets  = new TH1D("h1nJets ", "Number of  Jets [FMS or EEMC]", 10, 0, 10);
    TH1D *h1spinB = new TH1D("h1spinB", "Blue beam spin; Blue beam spin", 5, -2, 2);
    TH1D *h1spinY = new TH1D("h1spinY", "Yellow beam spin; Yellow beam spin", 5, -2, 2);
    TH1D *h1UnixTime = new TH1D("h1UnixTime", "Event Unix Time; Event Unix Time", 1000000, 1426e6, 1427e6);
    TH1D *h1TrigType = new TH1D("h1TrigType", "Trigger Type; Trigger Type", 10, 0, 10);
    
    TH1D *h1TowerEta = new TH1D("h1TowerEta", "Tower Eta", 100, 1.0, 4.5);
    TH1D *h1TowerPhi = new TH1D("h1TowerPhi", "Tower Phi", 100, -3.2, 3.2);
    TH1D *h1TowerE = new TH1D("h1TowerE", "Tower E", 100, 0, 100);

    TH1D *h1Eta = new TH1D ("h1Eta", "EM Jet Eta; Jet #eta", 100, 1.0, 5.0);
    TH1D *h1Phi = new TH1D ("h1Phi", "EM Jet Phi; Jet #phi [rad]", 100, -3.3, 3.3);
    TH1D *h1E = new TH1D ("h1E", "EM Jet E; Jet E [GeV]", 100, 0.0, 70.0);
    TH1D *h1JetE_s = new TH1D ("h1JetE_s", "EM Jet E [small cells]; Jet E [GeV]", 100, 0.0, 85.0);
    TH1D *h1JetE_l = new TH1D ("h1JetE_l", "EM Jet E [large cells]; Jet E [GeV]", 100, 0.0, 70.0);    
    TH1D *h1Pt = new TH1D ("h1Pt", "Jet Pt (Pt cut); Jet Pt [GeV/c]", 100, 0.0, 50.0);
    TH1D *h1Pt_nocut = new TH1D ("h1Pt_nocut", "Jet Pt (no cut); Jet Pt [GeV/c]", 100, 0.0, 50.0);
    TH1I *h1nPhotons = new TH1I("h1nPhotons", "number of photons in EM jets; Number of Photons", 20, 0, 20);
    TH1D *h1vtxZ = new TH1D("h1vtxZ", "Jet vetrex z; Jet vertex z [cm]", 100, -200, 200);

    TH1I *h1_nRpTracks = new TH1I("h1_nRpTracks", "Number of RP tracks", 20, 0, 20);     
    TH1D *h1_wRpPt = new TH1D("h1_trkPtWest", "West RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 20);
    TH1D *h1_eRpPt = new TH1D("h1_trkPtEast", "East RP trk Pt; RP track P_{T} [GeV/c]", 100, 0, 20);    
    TH1D *h1_wRpP = new TH1D("h1_trkPWest", "West RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1D *h1_eRpP = new TH1D("h1_trkPEast", "East RP trk P; RP track P [GeV/c]", 200, 0, 200);
    TH1I *h1_RpNPlanes = new TH1I("h1_RpNPlanes","Number of RP planes;N Planes",9,0,9);
    TH1I *h1_RpNPlanes_East = new TH1I("h1_RpNPlanes_East","Number of RP planes in East side;N Planes East",9,0,9);
    TH1I *h1_RpNPlanes_West = new TH1I("h1_RpNPlanes_West","Number of RP planes in West side;N Planes West",9,0,9);
    TH2D *h2EvsPt = new TH2D("h2EvsPt", "Eng vs Pt; Pt [GeV/C]; E [GeV]", 100, 0, 20, 100, 0, 100);
    TH2D *h2PtvsE = new TH2D("h2PtvsE", "Pt vs E; E [GeV]; Pt [GeV/c]", 100,  0, 100, 100, 0, 20);
    TH2D *h2nPhVsEng = new TH2D("h2nPhVsEng", "Number of photons vs Eng; E [Gev]; No. of Photons", 100, 0, 100, 20, 0, 20);

    TH2D *h2_U_xF_vs_phi = new TH2D("h2_U_xF_vs_phi","Blue beam spin +1 x_{F} vs #phi ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1);
    TH2D *h2_D_xF_vs_phi = new TH2D("h2_D_xF_vs_phi","Blue beam spin -1 x_{F} vs #phi ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1);
    TH2D *h2_U_nPhotons_vs_phi = new TH2D("h2_U_nPhotons_vs_phi","Blue beam spin +1 n photons vs #phi ; #phi [rad] ; n photons",16,-3.14,3.14,6,0,6);
    TH2D *h2_D_nPhotons_vs_phi = new TH2D("h2_D_nPhotons_vs_phi","Blue beam spin -1 n photons vs #phi ; #phi [rad] ; n photons",16,-3.14,3.14,6,0,6);

    TH2D *h2_U_xF_vs_phi_nPhotons[6];
    h2_U_xF_vs_phi_nPhotons[1] = new TH2D("h2_U_xF_vs_phi_nPhotons_1","Blue beam spin +1 x_{F} vs #phi n photons = 1 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_U_xF_vs_phi_nPhotons[2] = new TH2D("h2_U_xF_vs_phi_nPhotons_2","Blue beam spin +1 x_{F} vs #phi n photons = 2 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_U_xF_vs_phi_nPhotons[3] = new TH2D("h2_U_xF_vs_phi_nPhotons_3","Blue beam spin +1 x_{F} vs #phi n photons = 3 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_U_xF_vs_phi_nPhotons[4] = new TH2D("h2_U_xF_vs_phi_nPhotons_4","Blue beam spin +1 x_{F} vs #phi n photons = 4 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_U_xF_vs_phi_nPhotons[5] = new TH2D("h2_U_xF_vs_phi_nPhotons_5","Blue beam spin +1 x_{F} vs #phi n photons = 5+; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    TH2D *h2_D_xF_vs_phi_nPhotons[6];
    h2_D_xF_vs_phi_nPhotons[1] = new TH2D("h2_D_xF_vs_phi_nPhotons_1","Blue beam spin -1 x_{F} vs #phi n photons = 1 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_D_xF_vs_phi_nPhotons[2] = new TH2D("h2_D_xF_vs_phi_nPhotons_2","Blue beam spin -1 x_{F} vs #phi n photons = 2 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_D_xF_vs_phi_nPhotons[3] = new TH2D("h2_D_xF_vs_phi_nPhotons_3","Blue beam spin -1 x_{F} vs #phi n photons = 3 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_D_xF_vs_phi_nPhotons[4] = new TH2D("h2_D_xF_vs_phi_nPhotons_4","Blue beam spin -1 x_{F} vs #phi n photons = 4 ; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 
    h2_D_xF_vs_phi_nPhotons[5] = new TH2D("h2_D_xF_vs_phi_nPhotons_5","Blue beam spin -1 x_{F} vs #phi n photons = 5+; #phi [rad] ; x_{F}",16,-3.14,3.14,10,0,1); 


    Double_t etaMin;
    Double_t etaMax;
    Double_t detZ; //For FMS
    if(det == "fms")
    {
	etaMin = 2.0;
	etaMax = 4.5;
	detZ = 735.; //For FMS

	h1TrigType->GetXaxis()->SetBinLabel(1,"FMS JP0");
	h1TrigType->GetXaxis()->SetBinLabel(2,"FMS JP1");
	h1TrigType->GetXaxis()->SetBinLabel(3,"FMS JP2");
	h1TrigType->GetXaxis()->SetBinLabel(4,"Small BS1");
	h1TrigType->GetXaxis()->SetBinLabel(5,"Small BS2");
	h1TrigType->GetXaxis()->SetBinLabel(6,"Small BS3");
	h1TrigType->GetXaxis()->SetBinLabel(7,"Large BS1");
	h1TrigType->GetXaxis()->SetBinLabel(8,"Large BS2");
	h1TrigType->GetXaxis()->SetBinLabel(9,"Large BS3");	
    }
    else if(det == "eemc")
    {
	etaMin = 1.0;
	etaMax = 2.0;
	detZ = kEEmcZSMD; //For EEMC

	h1TrigType->GetXaxis()->SetBinLabel(1,"EHT0");
	h1TrigType->GetXaxis()->SetBinLabel(2,"JP1");
	h1TrigType->GetXaxis()->SetBinLabel(3,"JP2");
	h1TrigType->GetXaxis()->SetBinLabel(4,"EHT0*EJP1*L2Egamma");
	h1TrigType->GetXaxis()->SetBinLabel(5,"JP2*L2JetHigh");
	h1TrigType->GetXaxis()->SetBinLabel(6,"BHT1*VPDMB-30");
	h1TrigType->GetXaxis()->SetBinLabel(7,"BHT0*BBCMB");
	h1TrigType->GetXaxis()->SetBinLabel(8,"BHT1*BBCMB");
	h1TrigType->GetXaxis()->SetBinLabel(9,"BHT2*BBCMB");		
    }
    else
    {
	cout << "Invalid detector" <<endl;
	return;
    }
    
    
    Double_t jetX, jetY, eta, phi, theta, vtxZ, eng, pt,nEMjets_cut,xF;
    Int_t nJets = 0;
    
    cout << "Total Entries to be processed: "<< ch->GetEntries() <<endl;

    for(Int_t evt = 0; evt < ch->GetEntries(); ++evt)
    {
	ch->GetEntry(evt);

	if(evt % 1000 == 0)
	    cout << "Events Processed: "<< evt <<endl;
	
	skimEvent = jetEvent->GetEvent();
	
	h1UnixTime->Fill(skimEvent->GetUnixTime());
	h1spinB->Fill(skimEvent->GetSpinB());
	h1spinY->Fill(skimEvent->GetSpinY());
        if(skimEvent->GetTrigFlag(5)) {continue;}
	h1nJets_all->Fill(jetEvent->GetNumberOfJets());
	vtxZ = skimEvent->GetVertexZ();
	if (fabs(vtxZ) > 80) continue;
	
	// for(Int_t t = 0; t < 9; ++t) //Moved to the end of envet loop
	// {
	//     if(skimEvent->GetTrigFlag(t))
	// 	h1TrigType->Fill(t);
	// }

	//Exclude FMS small-bs3 trigger that gives ring of fire issue. But this removes most of high energetic jets.
	if(det == "fms")
	{
	    if(skimEvent->GetTrigFlag(5))
		continue;
	}
	//Alternative way to reduce ring of fire, require: BBCMult > 2 and TofMult > 2
	
	nJets = 0;

	//roman pot cut	
	Int_t nRpsTracks = rpsArr->GetEntriesFast();
	h1_nRpTracks->Fill(nRpsTracks);
	if (nRpsTracks != 1) continue;
	
		rpsTrack = (TStRpsTrackData*)rpsArr->At(0);

		h1_RpNPlanes->Fill(rpsTrack->GetNplanes());	
		if (rpsTrack->GetNplanes()<7) continue;
		if(rpsTrack->GetBranch() == 0 || rpsTrack->GetBranch() == 1) //East RP :: O East Up RP, 1: East Down RP
                {
			continue;
                }
		else 
		{
			if(rpsTrack->GetBranch() == 2 || rpsTrack->GetBranch() == 3) // 2:  West Up RP, 3: West Down RP
                	{
				//continue;
                	}
			else continue;
		}	


	if(nJets > 0)
	{
	    for(Int_t t = 0; t < 9; ++t)
	    {
		if(skimEvent->GetTrigFlag(t))
		    h1TrigType->Fill(t);
	    }
	}
    

	for(Int_t j = 0; j <  jetEvent->GetNumberOfJets(); ++j)
	{
	    jet = jetEvent->GetJet(j);
	   	    
	    eta = jet->GetEta();
	    phi = jet->GetPhi();
	    theta =  2 * atan( exp(-eta) );

	    if(eta < etaMin || eta > etaMax) //Conside only EEMC and FMS coverage
		continue;

	    ++nJets;
	    eng = jet->GetE();
	    pt = jet->GetPt();
	    
 	    xF = eng / 100.;

	    if(j == 0)
		h1vtxZ->Fill(vtxZ);
	   
	    h1Pt_nocut->Fill(pt);

	    //if (eng < 2) continue;
	    //if (pt < 2) continue; 
    	    Int_t nPhotons=jet->GetNumberOfTowers();
	    h1nPhotons->Fill(nPhotons);
	    h1Eta->Fill(eta);
	    h1Phi->Fill(phi);
	    h1Pt->Fill(pt);
	    h1E->Fill(eng);
	 
   
	    h2EvsPt->Fill(pt, eng);
	    h2PtvsE->Fill(eng, pt);
	    h2nPhVsEng->Fill(eng, jet->GetNumberOfTowers());

	    //fill n entries 
	    if (skimEvent->GetSpinB() == 1) 
		{
			h2_U_xF_vs_phi->Fill(phi,xF);
			if (nPhotons ==0) {h2_U_xF_vs_phi->Fill(phi,0);}
			if (nPhotons <=5 && nPhotons > 0) {h2_U_xF_vs_phi->Fill(phi,nPhotons);h2_U_xF_vs_phi_nPhotons[nPhotons]->Fill(phi,xF);}
			if (nPhotons > 5) {h2_U_xF_vs_phi->Fill(phi,5);h2_U_xF_vs_phi_nPhotons[5]->Fill(phi,xF);}
		}

	    if (skimEvent->GetSpinB() == -1) 
		{
			h2_D_xF_vs_phi->Fill(phi,xF);
			if (nPhotons ==0) {h2_D_xF_vs_phi->Fill(phi,0);}
			if (nPhotons <=5 && nPhotons > 0) {h2_D_xF_vs_phi->Fill(phi,nPhotons);h2_D_xF_vs_phi_nPhotons[nPhotons]->Fill(phi,xF);}
			if (nPhotons > 5) {h2_D_xF_vs_phi->Fill(phi,5);h2_D_xF_vs_phi_nPhotons[5]->Fill(phi,xF);}
		}
	   
 
	    for(Int_t k = 0; k < jet->GetNumberOfTowers(); ++k)
	    {
		tower = jet->GetTower(k);
	
		h1TowerEta->Fill(tower->GetEta());
		h1TowerPhi->Fill(tower->GetPhi());
		h1TowerE->Fill(tower->GetEnergy());
	    }
	}

		

	    //Particle Branch is for simulated data only
	    // for(Int_t k = 0; k < jet->GetNumberOfParticles(); ++k)
	    // {
	    // 	particle = jet->GetParticle(k);
	
	    // }	    
	h1nJets->Fill(nJets);


    }

    outFile->Write();
    outFile->Close();
    delete ch;
}
