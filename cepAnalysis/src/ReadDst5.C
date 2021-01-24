// Filename: ReadDst.C
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Mon Apr 27 02:00:44 2020 (-0400)
// URL: jlab.org/~latif

void ReadDst5()
{
    gSystem->Load("BrContainers.so");

   
    TChain *ch = new TChain("T");
//    ch->Add("/gpfs/mnt/gpfs01/star/pwg/kabir/dst/R15CepNanoDst/CepNanoDstMaker_16064079.root");
//    ch ->Add("/star/data01/pwg/liangxl/mywork/BrightSTAR/jobResults/condor/root_result/CepNanoDstMaker_nocut0625.root");
//    ch ->Add("/star/data01/pwg/liangxl/mywork/BrightSTAR/jobResults/condor/root_result/CepNanoDstMaker_nocut0701.root");
    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P6.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P4.root");
//  ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P8.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P4.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P5.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P4.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P5.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P4.root");
//    ch->Add("/star/data01/pwg/liangxl/BrightSTAR1/condorjobResults/CepNanoDst0816_root/CepNanoDst0816_P5.root");    

     //Add other files here or can use wildcat in the file name
    
    TFile *file = new TFile("cepDstQA_5.root", "recreate");
    TH1D *h_nVertices = new TH1D("nVertices", "Number of vertices", 20, 0, 20);
    TH1D *h_nPrimaryTracks = new TH1D("nPrimaryTracks", "Number of primary tracks", 20, 0, 20);
    TH1D *h_VtxZ = new TH1D("vtxZ", "vertex z; z [cm]", 100, -200, 200);
    TH1D *h_TrackEta = new TH1D("TrackEta","Track #eta ; #eta",80,-2,2);
    TH1D *h_TrackPt = new TH1D("TrackPt","Track P_{T} ; P_{T}",100,0,20);

    TH1D *h_nTracks = new TH1D("nTracks", "Number of RP tracks", 20, 0, 20);
    TH1D *h_westP = new TH1D("trkPwest", "West RP trk P; RP track P [GeV/c]", 200, 60, 150);
    TH1D *h_westPt = new TH1D("trkPtWest", "West RP trk Pt; RP track P_{T} [GeV/c]", 200, 0, 2);

    TH1D *h_eastP = new TH1D("trkPEast", "East RP trk P; RP track P [GeV/c]", 200, 60, 150);
    TH1D *h_eastPt = new TH1D("trkPtEast", "East RP trk Pt; RP track P_{T} [GeV/c]", 200, 0, 2);
    TH1I *h_NEastRpTrk = new TH1I("h_NEastRpTrk", "number of east Rp track",5,0,5);
    TH1I *h_NWestRpTrk = new TH1I("h_NWestRpTrk", "number of west Rp track",5,0,5);
    TH1I *h_RpNPlanes  = new TH1I("h_RpNPlanes", "number of planes",10,0,10);
    TH1D *h_DeltaThetaX= new TH1D("h_DeltaThetaX","#Delta #theta_{X}; #Delta #theta_{X} [mrad]",100,-10,10 );
    TH1D *h_DeltaThetaY= new TH1D("h_DeltaThetaY","#Delta #theta_{Y}; #Delta #theta_{Y} [mrad]",100,-10,10 );
    TH1D *h_RpTrkPx    = new TH1D("h_RpTrkPx","RP track P_{x} ; P_{x} [GeV]", 100, -.5, .5);
    TH1D *h_RpTrkPy    = new TH1D("h_RpTrkPy","RP track P_{y} ; P_{y} [GeV]", 100, -.5, .5);
    TH2D *h_RpTrkPxPy  = new TH2D("h_RpTrkPxPy", "RP track P_{y} vs P_{x} ; P_{x} [GeV] ; P_{y} [GeV]", 100, -0.5,0.5, 100,-0.5, 0.5);


    TH1D *h_nPions = new TH1D("nPions", "Number of pions", 10, 0, 10);
    TH1D *h_pionPt = new TH1D("pionPt", "Pt of pions", 50, 0, 5);
    TH1I *h_nVtxMatchTOF = new TH1I("h_nVtxMatchTOF","number of primary vertex match TOF",8,0,8);
    TH1D *h_ZVtx   = new TH1D("h_ZVtx","z component of primary vertex;z [cm]",300,-150,150);
    TH1I *h_TrkMatchTof = new TH1I("h_TrkMatchTof", "number of track match TOF",10,0,10);
    TH1I *h_TrkMatchBEMC = new TH1I("h_TrkMatchBEMC", "number of track match BEMC",10,0,10);
    TH1D *h_RminMatchTOF = new TH1D("h_RminMatchTOF", "Match with TOF;R_{min}",100,0,1);
    TH1D *h_RminNotMatchTOF = new TH1D("h_RminNotMatchTOF","Not matvh with TOF;R_{min}",100,0,1);
    TH1I *h_nHitFit = new TH1I("h_nHitFit","number of hit used in TPC reconstruction",50,0,50);
    TH1I *h_nHitDedx = new TH1I("h_nHitDedx","number of hits used in specific energy loss reconstruction",50,0,50);
    TH1D *h_DCAR = new TH1D("h_DCAR","DCA(R);DCA(R) [cm]",500,0,10);
    TH1D *h_DCAz = new TH1D("h_DCAz","DCA(z);DCA(z) [cm]",500,0,10);
    TH1D *h_dDCAz = new TH1D("h_dDCAz","#delta DCA(z);#delta DCA(z) [cm]",500,0,10);
    TH1D *h_DeltaVertexZ = new TH1D("h_DeltaVertexZ", "#Delta Vertex Z: z^{TPC} - z^{RP};#Delta Vertex Z [cm]",75, -75, 75);
    TH1D *h_DPxMissing = new TH1D("h_DPxMissing"," #Delta P_{x} missing;#Delta P_{x} missing [GeV]",100,-2,2);
    TH1D *h_DPyMissing = new TH1D("h_DPyMissing"," #Delta P_{y} missing;#Delta P_{y} missing [GeV]",100,-2,2);
    TH1D *h_Beta = new TH1D("h_Beta","#beta for track",100, -1000,100); 
 
    TH2D *h2_NSigmaPivsNSigmaPr = new TH2D("h2_NSigmaPivsNSigmaPr_Pair","n#sigma^{pair}_{#pi} vs n#sigma^{pair}_{pr} ; n#sigma^{pair}_{pr} ; n#sigma^{pair}_{#pi}", 30,0,30,30,0,30);
    TH2D *h2_NSigmaPivsNSigmaKa = new TH2D("h2_NSigmaPivsNSigmaKa_Pair","n#sigma^{pair}_{#pi} vs n#sigma^{pair}_{Ka} ; n#sigma^{pair}_{Ka} ; n#sigma^{pair}_{#pi}", 30,0,30,30,0,30);
    TH2D *h2_NSigmaKavsNSigmaPr = new TH2D("h2_NSigmaKavsNSigmaPr_Pair","n#sigma^{pair}_{Ka} vs n#sigma^{pair}_{pr} ; n#sigma^{pair}_{pr} ; n#sigma^{pair}_{Ka}", 30,0,30,30,0,30);
    TH2D *h2_m2vsNSigmaPr = new TH2D("h2_m2vsNSigmaPair_Pr","m^{2} vs n#sigma^{pair}_{pr} ; n#sigma^{pair}_{pr} ; m^{2} [GeV^{2}]", 30,0,30,70,-0.2,1.2);
    TH2D *h2_m2vsNSigmaPi = new TH2D("h2_m2vsNSigmaPair_Pi","m^{2} vs n#sigma^{pair}_{#pi} ; n#sigma^{pair}_{#pi} ; m^{2} [GeV^{2}]", 30,0,30,70,-0.2,1.2);
    TH2D *h2_m2vsNSigmaKa = new TH2D("h2_m2vsNSigmaPair_Ka","m^{2} vs n#sigma^{pair}_{Ka} ; n#sigma^{pair}_{Ka} ; m^{2} [GeV^{2}]", 30,0,30,70,-0.2,1.2);
    TH1D *h_m2 = new TH1D("h_m2","m^{2} ; m^{2} [GeV^{2}]" , 70,-0.2, 1.2);
    TH1D *h_pippim = new TH1D("h_pippim","#pi^{+} #pi^{-} ; m_{#pi^{+}#pi^{-}}[GeV]",81,0.3,3);
    TH1D *h_kapkam = new TH1D("h_kapkam","K^{+} K^{-} ; m_{K^{+}K^{-}}[GeV]",60,0,3);
    TH1D *h_ppbar = new TH1D("h_ppbar","pp ; m_{pp}[GeV]",60,0,3);

    TClonesArray *trkArr = new TClonesArray("TStTrackData");  
    TClonesArray *rpsArr = new TClonesArray("TStRpsTrackData");
    TClonesArray *emcArr = new TClonesArray("TStEmcPointData");
    TClonesArray *eArr = new TClonesArray("TStChargedPidData");
    TClonesArray *piArr = new TClonesArray("TStChargedPidData");
    TClonesArray *prArr = new TClonesArray("TStChargedPidData");
    TClonesArray *kaArr = new TClonesArray("TStChargedPidData");
    TClonesArray *ukArr = new TClonesArray("TStChargedPidData");

    TStEventData *event = new TStEventData();
 
    ch->SetBranchAddress("event", &event);
    ch->SetBranchAddress("track", &trkArr);
    ch->SetBranchAddress("rpTrack", &rpsArr);
    ch->SetBranchAddress("emcPoint", &emcArr);
    ch->SetBranchAddress("e", &eArr);   //electrons
    ch->SetBranchAddress("pi", &piArr); // pions
    ch->SetBranchAddress("pr", &prArr); // protons
    ch->SetBranchAddress("ka", &kaArr); // kaons
    ch->SetBranchAddress("uk", &ukArr); // unknown particles

    TStTrackData *Track;
    TStRpsTrackData *rpsTrack;
    TStRpsTrackData *rpsTrackEast;
    TStRpsTrackData *rpsTrackWest;
    Int_t nRpsTracks;   
    TStEmcPointData *emcPhoton;
    TStChargedPidData *chargedPart;
    Int_t nChargedPart;

    
    Int_t nEntries = ch->GetEntries(); //Number of events

    //Loap over all events
    for(Int_t evt = 0; evt < nEntries; ++evt)
    {
	ch->GetEntry(evt); //Load event

	//--------- Read Event Information ------------------
	//Read TPC track info
	h_nVertices->Fill(event->GetNvertices());
	h_VtxZ->Fill(event->GetVz());
	h_nPrimaryTracks->Fill(event->GetNprimaryTracks());
	h_nVtxMatchTOF->Fill(event->GetNBTOFMatchVertices());

	if (event->GetNBTOFMatchVertices() != 1 ) continue;  //cut1

	h_ZVtx->Fill(event->GetVz());
	if (fabs(event->GetVz())>80) continue; //cut2

	//Check TStEventData.h for all available Get() methods

	nTracks = trkArr->GetEntriesFast();
	Int_t TrkMatchTof=0;
	Int_t TrkMatchBEMC=0;
	Int_t TrkMatchTofBemcAccept=0;
	Int_t GoodTPCTrack1=-1;
	Int_t GoodTPCTrack2=-1;
	for(Int_t trk = 0; trk < nTracks; ++trk)
	{
		track = (TStTrackData*) trkArr->At(trk);
		if (track->GetBTofPidTraitsFlag() > 0) 
		{
			++TrkMatchTof;
			h_RminMatchTOF->Fill(track->GetDistR());
		}
		else    h_RminNotMatchTOF->Fill(track->GetDistR());
		if (track->GetDistR() < 0.07) ++TrkMatchBEMC;
//		if (((track->GetBTofPidTraitsFlag() > 0)&&(track->GetDistR() < 0.07))) 
		if (((track->GetBTofPidTraitsFlag() > 0)))
		{
			if (GoodTPCTrack1 == -1) {GoodTPCTrack1 = trk;}
			else GoodTPCTrack2=trk;
			++TrkMatchTofBemcAccept;
		}
// 		if (((track->GetBTofPidTraitsFlag() == 0)&&(track->GetDistR() < 0.07))) TrkMatchTofBemcAccept=-999;

      }

//      if (TrkMatchTof>2) TrkMatchTofBemcAccept=0;
      h_TrkMatchTof->Fill(TrkMatchTof);
      h_TrkMatchBEMC->Fill(TrkMatchBEMC);
//	if (TrkMatchTofBemcAccept != 2) continue; //cut C3.1
	if (TrkMatchTof != 2) continue;

	track1 = (TStTrackData*) trkArr->At(GoodTPCTrack1);
	track2 = (TStTrackData*) trkArr->At(GoodTPCTrack2);
	h_TrackEta->Fill(track1->GetEta());
	h_TrackPt-> Fill(track1->GetPt());	
	h_TrackEta->Fill(track2->GetEta());
        h_TrackPt-> Fill(track2->GetPt());

	if ((track1->GetEta() < 0.2)|| (track2->GetEta()< 0.2)) continue; //cut C3.3
	if ((track1->GetPt() > 0.9)||(track2->GetPt() > 0.9))   continue; //cut C3.3
	if ((track1->GetQ() * track2->GetQ() > 0)) continue; //cut C3.2

	h_nHitFit->Fill(track1->GetNHitsFit());
	h_nHitFit->Fill(track2->GetNHitsFit());
	h_nHitDedx->Fill(track1->GetNHitsDedx());
	h_nHitDedx->Fill(track2->GetNHitsDedx());

	if ((track1->GetNHitsFit() <25) ||(track2->GetNHitsFit() <25)) continue;
	if ((track1->GetNHitsDedx() < 15)||(track2->GetNHitsDedx()<15))continue;//cut C3.4
	
	h_DCAR->Fill(track1->GetDcaD());
	h_DCAR->Fill(track2->GetDcaD());
	h_DCAz->Fill(track1->GetDcaZ());
        h_DCAz->Fill(track2->GetDcaZ());
	h_dDCAz->Fill(fabs(track1->GetDcaZ() - track2->GetDcaZ()));

	if ((track1->GetDcaD() > 1.5) || ((track2->GetDcaD() > 1.5))) continue;//cut C3.5
	if ((track1->GetDcaZ() > 1.5) || ((track2->GetDcaZ() > 1.5))) continue;
//	if (fabs(track1->GetDcaZ() - track2->GetDcaZ())>1.5 ) continue; //cut C3.6

	//----------- Read RP Information --------------------------
	nRpsTracks = rpsArr->GetEntriesFast();
	h_nTracks->Fill(nRpsTracks);
	Int_t WestRpTrk=0;
	Int_t EastRpTrk=0;
	Int_t WestTrkId=-1;
	Int_t EastTrkId=-1;
	for(Int_t trk = 0; trk < nRpsTracks; ++trk)
	{
	    rpsTrack = (TStRpsTrackData*)rpsArr->At(trk);

	    if(rpsTrack->GetBranch() == 2 || rpsTrack->GetBranch() == 3) //East RP :: O East Up RP, 1: East Down RP
	    {		    
		h_westP->Fill(rpsTrack->GetP());		
		h_westPt->Fill(rpsTrack->GetPt());
		++WestRpTrk;
		WestTrkId = trk;
		//Check TStRpsTrackData.h file for all available Get() methods 		
	    }	    
	    if(rpsTrack->GetBranch() == 0 || rpsTrack->GetBranch() == 1) //East RP :: O East Up RP, 1: East Down RP
            {

		h_eastP->Fill(rpsTrack->GetP());
                h_eastPt->Fill(rpsTrack->GetPt());
                ++EastRpTrk;
		EastTrkId = trk;
	    }
	    h_RpNPlanes->Fill(rpsTrack->GetNplanes());

	}
	h_NWestRpTrk->Fill(WestRpTrk);
	h_NEastRpTrk->Fill(EastRpTrk);
	
	if ((WestRpTrk != 1) || (EastRpTrk != 1)) continue;//cut 4.3	

	rpsTrackWest = (TStRpsTrackData*)rpsArr->At(WestTrkId);
	rpsTrackEast = (TStRpsTrackData*)rpsArr->At(EastTrkId);
	if ((rpsTrackWest->GetNplanes() < 6) ||(rpsTrackEast->GetNplanes() < 6)) continue;//cut 4.1

	h_DeltaThetaX->Fill(rpsTrackWest->GetDeltaThetaX());
	h_DeltaThetaY->Fill(rpsTrackWest->GetDeltaThetaY());
	h_DeltaThetaX->Fill(rpsTrackEast->GetDeltaThetaX());
        h_DeltaThetaY->Fill(rpsTrackEast->GetDeltaThetaY());

	if ((rpsTrackWest->GetDeltaThetaX()<-2)||(rpsTrackWest->GetDeltaThetaX()>4)) continue; //cut 4.2
	if ((rpsTrackWest->GetDeltaThetaY()<-2)||(rpsTrackWest->GetDeltaThetaY()>2)) continue;//cut 4.2
	if ((rpsTrackEast->GetDeltaThetaX()<-2)||(rpsTrackEast->GetDeltaThetaX()>4)) continue; //cut 4.2
	if ((rpsTrackEast->GetDeltaThetaY()<-2)||(rpsTrackEast->GetDeltaThetaY()>2)) continue;//cut 4.2

	h_RpTrkPx->Fill(rpsTrackWest->GetPx());
	h_RpTrkPy->Fill(rpsTrackWest->GetPy());
	h_RpTrkPx->Fill(rpsTrackEast->GetPx());
        h_RpTrkPy->Fill(rpsTrackEast->GetPy());
	h_RpTrkPxPy->Fill(rpsTrackEast->GetPx(),rpsTrackEast->GetPy());
	h_RpTrkPxPy->Fill(rpsTrackWest->GetPx(),rpsTrackWest->GetPy());


	if ((fabs(rpsTrackWest->GetPy()) < 0.2)||(fabs(rpsTrackWest->GetPy()) > 0.4) || (fabs(rpsTrackEast->GetPy()) < 0.2)||(fabs(rpsTrackEast->GetPy()) > 0.4)) continue; //Cut 4.4
	if ((rpsTrackWest->GetPx() < -0.2) || (rpsTrackEast->GetPx() < -0.2)) continue;
	if (((rpsTrackWest->GetPx()+0.3)*(rpsTrackWest->GetPx()+0.3) + ((rpsTrackWest->GetPy()*rpsTrackWest->GetPy()))) > 0.25) continue;
	if (((rpsTrackEast->GetPx()+0.3)*(rpsTrackEast->GetPx()+0.3) + ((rpsTrackEast->GetPy()*rpsTrackEast->GetPy()))) > 0.25) continue;

	Double_t RpTrkVertex=(rpsTrackWest->GetTime() - rpsTrackEast->GetTime()) * 299792458 *100 /2;
	Double_t DeltaVertexZ=event->GetVz() - RpTrkVertex;
	h_DeltaVertexZ->Fill(DeltaVertexZ);
//	if (fabs(DeltaVertexZ)>36) continue;  //Cut C5

	Double_t NSigmaPi_1 = track1->GetNSigmaPi();
	Double_t NSigmaPi_2 = track2->GetNSigmaPi();
	Double_t NSigmaPr_1 = track1->GetNSigmaPr();
        Double_t NSigmaPr_2 = track2->GetNSigmaPr();
	Double_t NSigmaKa_1 = track1->GetNSigmaKa();
        Double_t NSigmaKa_2 = track2->GetNSigmaKa();
	Double_t mass2_1 = track1->GetM2();
	Double_t mass2_2 = track2->GetM2();

	Double_t NSigmaPair_Pi = sqrt(NSigmaPi_1 * NSigmaPi_1 + NSigmaPi_2 * NSigmaPi_2);
        Double_t NSigmaPair_Pr = sqrt(NSigmaPr_1 * NSigmaPr_1 + NSigmaPr_2 * NSigmaPr_2);
        Double_t NSigmaPair_Ka = sqrt(NSigmaKa_1 * NSigmaKa_1 + NSigmaKa_2 * NSigmaKa_2);

        h2_NSigmaPivsNSigmaPr->Fill(NSigmaPair_Pr,NSigmaPair_Pi);
        h2_NSigmaPivsNSigmaKa->Fill(NSigmaPair_Ka,NSigmaPair_Pi);
        h2_NSigmaKavsNSigmaPr->Fill(NSigmaPair_Pr,NSigmaPair_Ka);
	if (track1->GetBeta() !=-999 )  h2_m2vsNSigmaPr->Fill(NSigmaPair_Pr,mass2_1);
        if (track2->GetBeta() !=-999 )  h2_m2vsNSigmaPr->Fill(NSigmaPair_Pr,mass2_2);
	if (track1->GetBeta() !=-999 )  h2_m2vsNSigmaPi->Fill(NSigmaPair_Pi,mass2_1);
        if (track2->GetBeta() !=-999 )  h2_m2vsNSigmaPi->Fill(NSigmaPair_Pi,mass2_2);
        if (track1->GetBeta() !=-999 )  h2_m2vsNSigmaKa->Fill(NSigmaPair_Ka,mass2_1);
        if (track2->GetBeta() !=-999 )  h2_m2vsNSigmaKa->Fill(NSigmaPair_Ka,mass2_2);
        h_m2->Fill(mass2_1);
	h_m2->Fill(mass2_2);
	h_Beta->Fill(track1->GetBeta());
        h_Beta->Fill(track2->GetBeta());

	TLorentzVector track1Vec;
        TLorentzVector track2Vec;

        if ((track2->GetBeta() !=-999)&&(track1->GetBeta() !=-999))
        {

                if ((NSigmaPair_Pi >3)&&(NSigmaPair_Ka>3)&&(NSigmaPair_Pr<3)&&(mass2_1 > 0.6)&&(mass2_2 > 0.6))  //Proton
                {
                        track1Vec.SetXYZM(track1->GetPx(),track1->GetPy(),track1->GetPz(),0.88);
                        track2Vec.SetXYZM(track2->GetPx(),track2->GetPy(),track2->GetPz(),0.88);
                        h_ppbar->Fill((track1Vec + track2Vec).M());
                }

		else if ((NSigmaPair_Pi >3)&&(NSigmaPair_Pr>3)&&(NSigmaPair_Ka<3)&&(mass2_1 > 0.15)&&(mass2_2 > 0.15)) //Kaon
                {
                        track1Vec.SetXYZM(track1->GetPx(),track1->GetPy(),track1->GetPz(),0.243);
                        track2Vec.SetXYZM(track2->GetPx(),track2->GetPy(),track2->GetPz(),0.243);
                        h_kapkam->Fill((track1Vec + track2Vec).M());
                }

                else if ((NSigmaPair_Pi < sqrt(12))) //Kion
                {
                        track1Vec.SetXYZM(track1->GetPx(),track1->GetPy(),track1->GetPz(),0.019);
                        track2Vec.SetXYZM(track2->GetPx(),track2->GetPy(),track2->GetPz(),0.019);
                        if ((track1Vec.Pt()>0.2)&&(track2Vec.Pt()>0.2)&&(fabs(track1Vec.Eta())<0.7)&&(fabs(track2Vec.Eta())<0.7)) h_pippim->Fill((track1Vec + track2Vec).M());
                }

        }


	Double_t PX_missing= rpsTrackWest->GetPx() + rpsTrackEast->GetPx() + track1->GetPx() + track2->GetPx();
	Double_t PY_missing= rpsTrackWest->GetPy() + rpsTrackEast->GetPy() + track1->GetPy() + track2->GetPy();
	h_DPxMissing->Fill(PX_missing);
	h_DPyMissing->Fill(PY_missing);


	//------------- Read Charged Particle Information ---------------------------
	//Read pion info
	//Access other charged particles (pr, e, ka) in the same way
	
    }
    
    file->Write();
}
