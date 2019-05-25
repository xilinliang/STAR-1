#ifndef TFMSMAKER_H     
#define TFMSMAKER_H

#include "StMaker.h"
#include "TString.h"

class TFile;
class StMuDstMaker;
class TH1F;
class StMuEvent;
class StMuTrack;

class TFmsMaker : public StMaker
{
public:

    TFmsMaker(StMuDstMaker* maker);
    ~TFmsMaker() {;}

    void   Clear(Option_t *option="") {StMaker::Clear();}    
    Int_t  Init();                      
    Int_t  Make();                      
    Int_t  Finish();                    

    void SetFileName(TString fileName) {mFileName = fileName;}
    void SetRefMult(int lo, int hi) {mRefMult[0]=lo; mRefMult[1]=hi;}

private:
    bool accept(StMuEvent*);
    bool accept(StMuTrack*);

    StMuDstMaker* mMuDstMaker;

    int       mNEventsPassed;  
    int       mNEventsFailed;  
    int	      mRefMult[2];	
    TString   mFileName;      

    //-------- Define histograms here --------//
    TH1F *hDeltaPhi;
    TH1F *hPhi;
    TH1F *hPt;
    TH1F *hRefMult;
    TH1F *hVz;

    ClassDef(TFmsMaker,1)
};

#endif
