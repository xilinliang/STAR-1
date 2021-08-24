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
void DiffJetXFnPhotonsANCalc(TString inFileName, TString outName, TString det)
{
    TChain *ch = new TChain("T");
    
    TFile *file = new TFile(inFileName);   
    TFile *outFile = new TFile(outName, "recreate");

    TH2D *BlueBeamUp;
    TH2D *BlueBeamDown;
    TH2D *BlueBeamUpnPhotons[6];
    TH2D *BlueBeamDownnPhotons[6];
 
    BlueBeamUp = (TH2D*) file->Get("h2_U_xF_vs_phi");
    BlueBeamDown = (TH2D*) file->Get("h2_D_xF_vs_phi");
    for (int k=1; k<6 ; k=k+1)
    {

	BlueBeamUpnPhotons[k] = (TH2D*) file->Get(Form("h2_U_xF_vs_phi_nPhotons_%i",k));
	BlueBeamDownnPhotons[k] = (TH2D*) file->Get(Form("h2_D_xF_vs_phi_nPhotons_%i",k));

    }

    Double_t pi=3.14;
    Double_t polB;

    if (det == "fms")
    {

	int XFbins, nXFusebins, Phibins;
	XFbins = 10;
	nXFusebins = 6;
	Phibins = 16;
	Double_t BlueUpNum[Phibins+1][XFbins+1];
	Double_t BlueDownNum[Phibins+1][XFbins+1];
	Double_t PhiPoint[] = {pi/16.,3*pi/16.,5*pi/16.,7*pi/16.,9*pi/16.,11*pi/16.,13*pi/16.,15*pi/16.};
	Double_t PhiPointErr[] = {0,0,0,0,0,0,0,0};
	Double_t XFpoint[] = {0.05,0.15,0.25,0.35,0.45,0.55};
	Double_t XFpointErr[] = {0,0,0,0,0,0};

	polB=0.57;

	//get number of event within each bin by XF and phi
	for (int i=0; i<Phibins ; i=i+1)
	{

		for (int j=0; j<XFbins; j=j+1)
		{

			BlueUpNum[i][j] = BlueBeamUp->GetBinContent(i+1,j+1);
			cout<<"Blue beam Up x:"<<i<<" y:"<<j<<" n entries:"<<BlueUpNum[i][j]<<endl; 
			BlueDownNum[i][j] = BlueBeamDown->GetBinContent(i+1,j+1);
			cout<<"Blue beam Down x:"<<i<<" y:"<<j<<" n entries:"<<BlueDownNum[i][j]<<endl; 

		}

	}

	Double_t rawAN[Phibins/2];
	Double_t rawANErr[Phibins/2];
	Double_t ANresult[nXFusebins];
	Double_t ANresultErr[nXFusebins];
	Double_t a,b,c,d ,  rawANnomin , rawANdenomin, rawANErrnomin , rawANErrdenomin;

	TGraphErrors *BlueBeamRawAN[nXFusebins];
	TGraphErrors *BlueBeamAN;

	
	TF1 *BlueFit[nXFusebins];

	for (int j=0; j<nXFusebins; j=j+1)
	{


		for(int i=0; i<(Phibins / 2); i=i+1)
		{

			a = BlueUpNum[i+(Phibins/2)][j]; //a: N^{up} (phi)
			b = BlueDownNum[i][j]; //b: N^{down} (phi + pi)
			c = BlueDownNum[i+(Phibins/2)][j]; //c: N^{down} (phi)
			d = BlueUpNum[i][j]; //d: N^{up} (phi + pi)

			rawANnomin = sqrt(a*b) - sqrt(c*d);
			rawANdenomin = sqrt(a*b) + sqrt(c*d);
			rawAN[i] = rawANnomin / rawANdenomin;

			rawANErrnomin = b*c*d + a*c*d + a*b*d + a*b*c;
			rawANErrdenomin = pow(rawANdenomin,4);
			rawANErr[i] = sqrt(rawANErrnomin / rawANErrdenomin);
			//cout<<"XF "<<(0.1*(j))<<" to "<<(0.1*(j+1))<<" phi bin: "<<(0.125*(i))<<"pi to "<<(0.125*(i+1))<<"pi  raw AN="<<rawAN[i]<<"  raw AN uncertainty="<<rawANErr[i]<<endl;

		}
		
		BlueBeamRawAN[j] = new TGraphErrors(Phibins / 2,PhiPoint , rawAN, PhiPointErr,rawANErr);
		BlueBeamRawAN[j]->SetName(Form("BlueBeamRawAN_%i",j));
		BlueBeamRawAN[j]->SetTitle(Form("Blue Beam Raw A_{N} by x_{F} %.1f to %.1f",0.1*j, 0.1*(j+1)));
		//BlueBeamRawAN[j]->Write();

		BlueFit[j] = new TF1(Form("BlueFit_%i",j),"[0]*cos(x) + [1]");
		BlueBeamRawAN[j]->Fit(Form("BlueFit_%i",j));
		ANresult[j] = BlueFit[j]->GetParameter(0) / polB;
		ANresultErr[j] = BlueFit[j]->GetParError(0) / polB;
		BlueBeamRawAN[j]->Write();

	}

	BlueBeamAN = new TGraphErrors(nXFusebins , XFpoint , ANresult , XFpointErr , ANresultErr);
	BlueBeamAN->SetName("BlueBeamAN");
	BlueBeamAN->SetTitle("Blue Beam A_{N}");
	BlueBeamAN->Write();


    }





    outFile->Write();
    outFile->Close();
    delete ch;
}
