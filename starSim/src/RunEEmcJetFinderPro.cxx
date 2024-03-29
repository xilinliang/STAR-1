#include <iostream>
#include "TString.h"
#include "StRootIncludeFmsJet.h"

#include "StIOMaker/StIOMaker.h"
#include "StMcEventMaker/StMcEventMaker.h"
#include "StJetMaker/mcparticles/StjMCParticleCutEta.h"
#include "StSpinPool/StFmsTriggerMaker/StFmsTriggerMaker.h"
#include "StJetMaker/StJetMaker2015.h"
#include "StJetMaker/towers/StjTowerEnergyCutFMS.h"

#include "RunEEmcJetFinderPro.h"

using namespace std;

void RunEEmcJetFinderPro(TString inMuDstFile, TString outJetName, Int_t nEvents)
{
    TString orgName = inMuDstFile;
    TString pythiaFile = orgName.ReplaceAll("MuDst", "pythia");
    TString geantFile = orgName.ReplaceAll("pythia", "geant");

    TString ueFileName = (TString)"ue_" + outJetName;
    TString skimFileName = (TString)"skim_" + outJetName;

    cout<<"Input MuDst file is: "<< inMuDstFile <<endl;
    cout<<"Input pythia file is: "<< pythiaFile <<endl;
    cout<<"Input geant file is: "<< geantFile <<endl;
    
    cout<<" Out JetTree file is: "<< outJetName <<endl;
    cout<<" Out SkimTree file is: "<< skimFileName <<endl;
    cout<<" Out UE file is: "<< ueFileName <<endl;
     
    StChain *chain = new StChain;
    StMuDstMaker* muDstMaker = new StMuDstMaker(0,0,"", inMuDstFile,"",1000);

    StMuDbReader* muDstDb = StMuDbReader::instance();

    St_db_Maker* starDb = new St_db_Maker("StarDb","MySQL:StarDb");
    starDb->SetDateTime(20150321,121503);
    StFmsDbMaker* fmsdb = new StFmsDbMaker("fmsDb");
    fmsdb->SetAttr("fmsGainCorr","fmsGainCorr-BNL-C");
    StEEmcDbMaker* eemcDb = new StEEmcDbMaker;
    StSpinDbMaker* spinDb = new StSpinDbMaker;

    StEmcADCtoEMaker* adc = new StEmcADCtoEMaker;
    adc->saveAllStEvent(true);
     
    StFmsHitMaker* fmshitMk = new StFmsHitMaker();
    // fmshitMk->SetTimeDepCorr(0);
    // fmshitMk->SetTowerRej(1);
    //   fmshitMk->SetReadMuDst(1); ///mmm working
    fmshitMk->SetReadMuDst(1); ///mmm 

    StFmsPointMaker *fmspt =  new StFmsPointMaker("StFmsPointMaker");
    //fmspt->setMergeSmallToLarge(1); //                                                                                  
    //   fmspt->SetReadMuDst(0);  // mmm working
    fmspt->SetReadMuDst(1);  // mmm working


    //------------------- You Need Geant file to get vertex and other info used in the particles branches in jet trees ----------   
    //GEANT reader
    // cout <<"!!!!!!!!!!!!!!! WARNING: GEANT file reader is Disabled. FIX IT !!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
    StIOMaker* ioMaker = new StIOMaker;
    ioMaker->SetFile(geantFile);
    ioMaker->SetIOMode("r");
    ioMaker->SetBranch("*",0,"0");             // Deactivate all branches  
    ioMaker->SetBranch("geantBranch",0,"r");   // Activate geant branch    
    
    StMcEventMaker* mcEventMaker = new StMcEventMaker;
    mcEventMaker->doPrintEventInfo  = false;
    mcEventMaker->doPrintMemoryInfo = false;
   
    // StFmsFastSimulatorMaker* fmsfastsimu = new StFmsFastSimulatorMaker; 

    //-------------------------- FMS Trigger Simulator ----------------------------
    StTriggerSimuMaker* simuTrig = new StTriggerSimuMaker;
    simuTrig->setMC(1); // Must be before individual detectors, to be passed    
    //simuTrig->useOnlineDB();
    //simuTrig->InitRun(11098017);
    simuTrig->InitRun(16080020);
    simuTrig->useOfflineDB();

    // FMS trigger simulator     
    StFmsTriggerMaker* fmstrig = new StFmsTriggerMaker;
    fmstrig->useMuDst();
    fmstrig->forceRunNumber(16080020);
    //  fmstrig->InitRun(11098017);    
    fmstrig->useQTSim();  // was there
    //fmstrig->useDsmData(); //Does not work

    // This is how you can overwrite the trigger threshold (if does not read properly frm db for example)
    // fmstrig->overwriteThr("FMS-sm-bs1", 5.0);
    // fmstrig->overwriteThr("FMS-sm-bs2", 10.0);
    // fmstrig->overwriteThr("FMS-sm-bs3", 15.0);

    // fmstrig->overwriteThr("FMS-lg-bs1", 20.0);
    // fmstrig->overwriteThr("FMS-lg-bs2", 25.0);
    // fmstrig->overwriteThr("FMS-lg-bs3", 30.0);
    
    // fmstrig->overwriteThr("FMS-JP0", 53.0);
    // fmstrig->overwriteThr("FMS-JP1", 79.0);
    // fmstrig->overwriteThr("FMS-JP2", 105.0);

    /////------------------------ Pythia Maker is needed to fill particles branch (in the Jet tree) to create jet out of pythia particles without detector effects ----------------
    //Seems geant file also have same particle info and can be used instead. 
    //for pjet
    St_pythia_Maker* pythia = new St_pythia_Maker;
    pythia->SetFile(pythiaFile);
    // Pythia4pMaker
    StPythiaFourPMaker* pythia4pMaker = new StPythiaFourPMaker;

    
    //StJetSkimEventMaker* skimEventMaker = new StJetSkimEventMaker("StJetSkimEventMaker", muDstMaker, skimFileName);   //Giving problem with SL20a. Try to incorporate EEMC sim part to fix it                                               
    StJetMaker2015* jetmaker = new StJetMaker2015;
    jetmaker->setJetFile(outJetName);
    jetmaker->setJetFileUe(ueFileName);
    jetmaker->setMCmode(true);

    StAnaPars* anapars12 = new StAnaPars;
    anapars12->useTpc  = true;
    anapars12->useBemc = false;
    anapars12->useEemc = true;
    anapars12->useFms  = false;
    anapars12->useEmJetMode = true;
    //anapars12->useFmsHit = true; //CKim
        
    anapars12->addTpcCut(new StjTrackCutFlag(0));
    anapars12->addTpcCut(new StjTrackCutNHits(12));
    anapars12->addTpcCut(new StjTrackCutPossibleHitRatio(0.51));
    anapars12->addTpcCut(new StjTrackCutDca(3));
    anapars12->addTpcCut(new StjTrackCutPt(0.2,200));
    anapars12->addTpcCut(new StjTrackCutEta(-2.5,2.5));
    anapars12->addTpcCut(new StjTrackCutLastPoint(125));

    //BEMC cuts
    anapars12->addBemcCut(new StjTowerEnergyCutBemcStatus(1));
    anapars12->addBemcCut(new StjTowerEnergyCutAdc(4,3)); //ADC-ped>4 AND ADC-ped>3*RMS
    anapars12->addBemcCut(new StjTowerEnergyCutEt(0.2));

    //EEMC cuts
    anapars12->addEemcCut(new StjTowerEnergyCutBemcStatus(1));
    anapars12->addEemcCut(new StjTowerEnergyCutAdc(4,3)); //ADC-ped>4 AND ADC-ped>3*RMS
    anapars12->addEemcCut(new StjTowerEnergyCutEt(0.2));

    //FMS cuts, CKim
    //anapars12->addFmsCut(new StjTowerEnergyCutFMS(0.2, 200)); //min, max //Latif: changed to 0.2, it was set to 3 by Chong
    anapars12->addFmsCut(new StjTowerEnergyCutFMS(2.0, 200)); //min, max //Latif: Photon energy cut allows to reject low energy photons / hadronic contribitions and match a lot better with data
    //* 3 GeV cut was determined by RUN15 calibration condition: Zgg < 0.7 + pairE > 20 GeV

    //Jet cuts
    anapars12->addJetCut(new StProtoJetCutPt(0.01,200));
    //anapars12->addJetCut(new StProtoJetCutEta(-1,5)); //CKim, extend to FMS acceptance
    anapars12->addJetCut(new StProtoJetCutEta(1,5)); //CKim, extend to FMS acceptance

    //-------------- Add MC particle and it's jet branch here -------------
    //StAnaPars* anaparsPart = new StAnaPars;
    //anaparsPart->useMonteCarlo = true; //<-------- This should not be use simultaneously with detertors enabled. //Latif. If not set, particles branch will not be filled. Note: By default the pythia tree is not synchronized if you used filter. Need to reproduce separate pythia tree that has only triggered events. Use that pythia tree to populate particle branch and jet from pythia particles. Check if used geant file whether that would still have synchronization issue. Seems geant file also have pythia particle info can can be used instead of pythia root file.
    
    // MC cuts  
    // anaparsPart->addMcCut(new StjMCParticleCutStatus(1)); // final state particles
    // anaparsPart->addJetCut(new StProtoJetCutPt(0.001,200));
    // anaparsPart->addMcCut(new StjMCParticleCutEta(2.4,4.3)); // final state particles 
    
    //Set anti-kt R=0.7 parameters
    StFastJetPars* AntiKtR070Pars = new StFastJetPars;
    AntiKtR070Pars->setJetAlgorithm(StFastJetPars::antikt_algorithm);
    AntiKtR070Pars->setRparam(0.7);
    AntiKtR070Pars->setRecombinationScheme(StFastJetPars::E_scheme);
    AntiKtR070Pars->setStrategy(StFastJetPars::Best);
    AntiKtR070Pars->setPtMin(2);

    jetmaker->addBranch("AntiKtR070NHits12",anapars12,AntiKtR070Pars);
    //Add MC particle branch here
    
    chain->Init();
    if(nEvents == -1)
	chain->EventLoop();
    else
	chain->EventLoop(nEvents);   
    chain->Finish();
  
    cout<<"SUCCESS!!"<<endl;
    delete chain;
  
}

void RunEEmcJetFinderPro(Int_t cycle, Int_t nEntries)
{
    TString inMuDstFile = Form("EEmcSim_Run15_%i_evt%i.MuDst.root", cycle, nEntries);
    TString outJetFile = Form("EEmcJet_Run15_%i_evt%i.root", cycle, nEntries);
    if(gSystem->AccessPathName(inMuDstFile))
    {
	cout << "No MuDSt Created" <<endl;
	return;
    }
    RunEEmcJetFinderPro(inMuDstFile, outJetFile);
    //cout << "Deleting geant file ...." <<endl;
    //gROOT->ProcessLine(".! rm *.geant.root");
}
