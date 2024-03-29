
#include "StRootInclude.h"
#include "RootInclude.h"
#include "cppInclude.h"
#include "TStTrigDef.h"

/*
 It is possible to integrate it as part of maker and create the tree from JetMaker buffer. See Zhanwen's FMS jet analysis maker as the example. This way you do not need to keep large jet trees.
*/

//Use file name with wildcard to chain many files
void EjMakeSimpleAnalysisTree(
    TString det, Int_t nentries,
	    TString jetfile,
	    TString skimfile,
	    TString outfile
    )
{
    cout << "nentries = " << nentries << endl;
    cout << "jetfile  = " << jetfile  << endl;
    cout << "skimfile = " << skimfile << endl;
    cout << "outfile = " << outfile << endl;

    if(!(det == "fms" || det == "eemc"))
    {
	cout << "Invalid detector name" <<endl;
	return;
    }
    
    // Load libraries
    // gSystem->Load("StJetEvent");
    // gSystem->Load("StJetSkimEvent");

    TFile *outFile = new TFile(outfile, "recreate");
    TTree *tree = new TTree("T", "Binned Jet Tree");
    
    // Open jet & skim files
    TChain* jetChain = new TChain("jet");
    TChain* skimChain = new TChain("jetSkimTree");

    Int_t nFiles_jet, nFiles_skim;
    nFiles_jet = jetChain->Add(jetfile);
    nFiles_skim = skimChain->Add(skimfile);

    Int_t nEvents = jetChain->GetEntries();
    if(nentries == -1 || nentries > nEvents)
	nentries = nEvents;

    cout << "Number of files added: "<<nFiles_jet <<endl;
    cout << "Total Entries to be processed: "<< nentries <<endl;
    //Check if added files are sorted properly which is crucial for skimChain vs jetChain synchronization
    jetChain->ls();
    skimChain->ls();
    // Set jet buffer
    StJetEvent* jetEvent = 0;
    jetChain->SetBranchAddress("AntiKtR070NHits12",&jetEvent);

    // Set skim buffer
    StJetSkimEvent* skimEvent = 0;
    skimChain->SetBranchAddress("skimEventBranch",&skimEvent);


    TH1D *h1nJets = new TH1D ("h1nJets", "Number of Jets [ -1 < #eta < 4.0 ]; No. of Jets", 15, -1, 14);
    TH1D *h1nJets_eemc = new TH1D ("h1nJets_eemc", "Number of EEMC EM Jets  [ 0.8 < #eta < 4.0 && Rt == 1 ]; No. of Jets", 15, -1, 14);

    Double_t mEEmcZSMD = kEEmcZSMD;
    Double_t mFmsZ = 735.0;
    Double_t fmsEtaMin = 2.0;
    Double_t fmsEtaMax = 4.5;
    Double_t eemcEtaMin = 0.8;
    Double_t eemcEtaMax = 2.5;
    Double_t etaMin;
    Double_t etaMax;
    Double_t zDist;

    if(det == "fms")
    {
	zDist = mFmsZ;
	etaMin = fmsEtaMin;
	etaMax = fmsEtaMax;
    }
    else if(det == "eemc")
    {
	zDist = mEEmcZSMD;
	etaMin = eemcEtaMin;
	etaMax = eemcEtaMax;
    }

    const Int_t kMaxPhotons = 100;
    Int_t runNumber;
    Int_t eventId;
    Int_t spin4Bit;
    Int_t spinB;
    Int_t spinY;
    Int_t trigFlag[9]; // index 0:JP0 1:JP1 2:JP2 3:sm-bs-1 4:sm-bs-2 5:sm-bs-3 6:lg-bs-1 7:lg-bs-2 8:lg-bs-3 
    Int_t nPhotons;
    
    Double_t eta;
    Double_t phi;
    Double_t eng;
    Double_t pt;
    Double_t vtxZ;
    Double_t jetX;
    Double_t jetY;
    Double_t rt;
    Double_t phEng[kMaxPhotons];

    TLorentzVector lv;
    TVector3 v3;
    Double_t theta;
    Int_t nEmJets;

    tree->Branch("run", &runNumber, "run/I");
    tree->Branch("event", &eventId, "event/I");
    tree->Branch("spinB", &spinB, "spinB/I");
    tree->Branch("spinY", &spinY, "spinY/I");
    tree->Branch("nPhotons", &nPhotons, "nPhotons/I");

    tree->Branch("phi", &phi, "phi/D");
    tree->Branch("eta", &eta, "eta/D");
    tree->Branch("eng", &eng, "eng/D");
    tree->Branch("pt", &pt, "pt/D");
    tree->Branch("vtxZ", &vtxZ, "vtxZ/D");
    tree->Branch("jetX", &jetX, "jetX/D");
    tree->Branch("jetY", &jetY, "jetY/D");
    tree->Branch("rt", &rt, "rt/D");
    tree->Branch("phEng", phEng, "phEng[nPhotons]/D");
    tree->Branch("trigFlag", trigFlag, "trigFlag[9]/I");  //index 0:JP0 1:JP1 2:JP2 3:sm-bs-1 4:sm-bs-2 5:sm-bs-3 6:lg-bs-1 7:lg-bs-2 8:lg-bs-3 
    
    skimChain->GetEvent(0);
    
    const Int_t kMaxTriggers = 9;
    Int_t trigIds[kMaxTriggers];
    TString triggerNames_fms[kMaxTriggers] = {"FMS-JP0", "FMS-JP1", "FMS-JP2", "FMS-sm-bs1", "FMS-sm-bs2", "FMS-sm-bs3", "FMS-lg-bs1", "FMS-lg-bs2", "FMS-lg-bs3"};
    TString triggerNames_eemc[kMaxTriggers] = {"EHT0", "JP1", "JP2", "EHT0*EJP1*L2Egamma", "JP2*L2JetHigh", "BHT1*VPDMB-30", "BHT0*BBCMB", "BHT1*BBCMB", "BHT2*BBCMB"};

    if(det == "fms")
    {
	for(Int_t i = 0; i < kMaxTriggers; ++i)
	    trigIds[i] = TStTrigDef::GetTrigId(skimEvent->runId(), triggerNames_fms[i]);
    }
    else if(det == "eemc")
    {
	for(Int_t i = 0; i < kMaxTriggers; ++i)
	    trigIds[i] = TStTrigDef::GetTrigId(skimEvent->runId(), triggerNames_eemc[i]);
    }
        
    StJetSkimTrig* jetTrig[kMaxTriggers]; 
    
    StJetParticle *particle;
    StJetTower *tower;
    Int_t vtxType = -1;
    vtxZ = -999;
    //----- Event loop ----------
    //Loads entries from Jet Tree and Skim Tree simultaneously
    for(unsigned long iEntry = 0; iEntry < nentries; ++iEntry)
    {
	if (jetChain->GetEvent(iEntry) <= 0 || skimChain->GetEvent(iEntry) <= 0)
	    break;

	// Should not be null
	assert(jetEvent && skimEvent);

	// Enforce event synchronization
	assert(jetEvent->runId() == skimEvent->runId() && jetEvent->eventId() == skimEvent->eventId());

	if (iEntry % 1000 == 0) cout << iEntry << endl;

	for(Int_t i = 0; i < kMaxTriggers; ++i)
	    jetTrig[i] = skimEvent->trigger(trigIds[i]);
		
	if(jetEvent->numberOfJets() == 0)
	    continue;
	
	StJetVertex* vertex = jetEvent->vertex(); //same as jetEvent->vertex(0)
	if (!vertex)
	    continue;
	
	// if(vertex->ranking() < 0) continue; //Not applicable for EM jet

	//--------- Event Selection --------
	// if(fabs(vertex->position().z()) > 80.0) //Do it from next level of processing
	//     continue;

	if ((skimEvent->bx7() > 30 && skimEvent->bx7() < 40) || (skimEvent->bx7() > 110 && skimEvent->bx7() < 120))
	    continue;
	
	//------ Reset values --------
	eta = -999.0;
	phi = -999.0;
	spinB = -9;
	spinY = -9;
	pt = -999;
	eng = -999;
	nPhotons = -1;
	jetX = -999;
	jetY = -999;
	vtxZ = -999;
	std::fill_n(trigFlag, 9, 0);
	std::fill_n(phEng, kMaxPhotons, -1);
	
	//vtxZ = vertex->position().z();

	runNumber = jetEvent->runId();
	eventId = jetEvent->eventId();
	spin4Bit = skimEvent->spin4usingBx48(); 
	/*
	  Spin info to be interpreted based on: https://drupal.star.bnl.gov/STAR/blog/oleg/spin-patterns-and-polarization-direction
	 spin = 10:  STAR pol B+ Y+
	      =  9:  STAR pol B+ Y-
	      =  6:  STAR pol B- Y+
              =  5:  STAR pol B- Y-
         (Note: Bunches can also be unpolarized, i.e. other possible values for the 4-spin bits are 1, 2, 4, and 8.)
	*/

	switch(spin4Bit) 
	{
	case 5:
	{
	    spinB = -1;
	    spinY = -1;
	    break;
	}
	case 6:
	{
	    spinB = -1;
	    spinY = +1;
	    break;
	}
	case 9:
	{
	    spinB = +1;
	    spinY = -1;
	    break;
	}
	case 10:
	{
	    spinB = +1;
	    spinY = +1;
	    break;
	}
	default: //either one is unpolarized or undefined
	    spinB = 0;
	    spinY = 0;
	}

	for(Int_t i = 0; i < kMaxTriggers; ++i)
	{
	    if(jetTrig[i])
	    {
		if(jetTrig[i]->didFire() && jetTrig[i]->shouldFire()) //<-------- Check what did/should fire actually is
		    trigFlag[i] = 1;
	    }
	}

	h1nJets->Fill(jetEvent->numberOfJets()); //This number would be greater than num of jets from the index = 0 vertex
	nEmJets = 0;

	//It seems most jet people loop over vertices. Find the justification.
	//I was looping over number of jets initially
	//Seems like directly looping over jets does not allow access to tower and particle information successfully. While if jet is accesses through vertex, the corresponding jet allows access to particle and tower information

	/*
	for(Int_t i = 0; i < jetEvent->numberOfJets(); ++i) 
	{
	    eta = jetEvent->jet(i)->eta();

	    if(eta < etaMin  || eta > etaMax) //Consider FMS or EEMC EM Jets only 
		continue;
	    
	    phi = jetEvent->jet(i)->phi();
	    eng = jetEvent->jet(i)->E();
	    pt = jetEvent->jet(i)->pt();
	    vtxZ = jetEvent->jet(i)->vertex()->position().z();
	    nPhotons = jetEvent->jet(i)->numberOfTowers();
	    rt = jetEvent->jet(i)->rt();
	    
	    theta =  2 * atan( exp(-eta) );
	    jetX = (zDist - vtxZ) * tan(theta) * cos(phi);
	    jetY = (zDist - vtxZ) * tan(theta) * sin(phi);


	    for(Int_t j = 0; j < jetEvent->jet(i)->numberOfTowers(); ++j)
	    {
		tower = jetEvent->jet(i)->tower(j);
				
		if(j >= kMaxPhotons)
		    break;
		phEng[j] = tower->energy(); //This will cause the crash ans tower will be null
	    }


	    if(rt == 1)
		++nEmJets;
	    
	    tree->Fill();
	}
	h1nJets_eemc->Fill(nEmJets);

	*/
	
	for(Int_t i = 0; i < vertex->numberOfJets(); ++i) 
	{
	    eta = vertex->jet(i)->eta();

	    if(eta < etaMin  || eta > etaMax) //Consider FMS or EEMC EM Jets only 
		continue;
	    
	    phi = vertex->jet(i)->phi();
	    eng = vertex->jet(i)->E();
	    pt = vertex->jet(i)->pt();
	    vtxZ = vertex->jet(i)->vertex()->position().z();
	    nPhotons = vertex->jet(i)->numberOfTowers();
	    rt = vertex->jet(i)->rt();
	    
	    theta =  2 * atan( exp(-eta) );
	    jetX = (zDist - vtxZ) * tan(theta) * cos(phi);
	    jetY = (zDist - vtxZ) * tan(theta) * sin(phi);

	    for(Int_t j = 0; j < vertex->jet(i)->numberOfTowers(); ++j)
	    {
		tower = vertex->jet(i)->tower(j);
				
		if(j >= kMaxPhotons)
		    break;
		phEng[j] = tower->energy();
	    }
	    
	    if(rt == 1)
		++nEmJets;
	    
	    tree->Fill();
	}
	h1nJets_eemc->Fill(nEmJets);
		
    } // End event loop

    outFile->Write();
}
