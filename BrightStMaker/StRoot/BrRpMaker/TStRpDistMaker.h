// Filename: TStRpDistMaker.h
// Description: 
// Author: Latif Kabir < kabir@bnl.gov >
// Created: Sat Jun 22 00:16:27 2019 (-0400)
// URL: jlab.org/~latif

#ifndef TSTRPDISTMAKERM_H    
#define TSTRPDISTMAKERM_H

#include "StMaker.h"
#include "TString.h"
#include "StMuDSTMaker/COMMON/StMuRpsCollection.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrack.h"
#include "StMuDSTMaker/COMMON/StMuRpsTrackPoint.h"

class TFile;
class StMuDstMaker;
class StMuDst;
class TH1F;
class StMuEvent;
class StMuTrack;

class TStRpDistMaker : public StMaker
{
public:

    TStRpDistMaker(StMuDstMaker* maker);
    ~TStRpDistMaker() {;}

    void   Clear(Option_t *option="") {StMaker::Clear();}    
    Int_t  Init();                      
    Int_t  Make();                      
    Int_t  Finish();                    

    void SetFileName(TString fileName) {mFileName = fileName;}

private:
    Bool_t Accept(StMuEvent*);
    Bool_t Accept(StMuTrack*);

    StMuDstMaker* mMuDstMaker;
    StMuDst* mMuDst;
    StMuEvent *mMuEvent;
    StMuRpsCollection *mRpsMuColl;
    
    Int_t mNEventsPassed;  
    Int_t mNEventsFailed;  	
    TString mFileName;
    Int_t mNplots = 13;

    TFile* mFile;
    TH1F *mHist1[13];
    
    ClassDef(TStRpDistMaker,1)
};

#endif
