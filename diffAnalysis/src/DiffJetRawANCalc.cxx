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
void DiffJetRawANCalc(TString inFileName, TString outName, TString det)
{
    TChain *ch = new TChain("T");
    
    TFile *file = new TFile(inFileName);   
    TFile *outFile = new TFile(outName, "recreate");

    TH2D *BlueBeamUp;
    TH2D *BlueBeamDown;
 
    BlueBeamUp = (TH2D*) file->Get("h2_U_xF_vs_phi");
    BlueBeamDown = (TH2D*) file->Get("h2_D_xF_vs_phi");

    Double_t pi=3.14;

    if (det == "fms")
    {

	int XFbins, Phibins;
	XFbins = 10;
	Phibins = 16;
	Double_t BlueUpNum[Phibins+1][XFbins+1];
	Double_t BlueDownNum[Phibins+1][XFbins+1];
	Double_t PhiPoint[] = {0,pi/8.,2*pi/8.,3*pi/8.,4*pi/8.,5*pi/8.,6*pi/8.,7*pi/8.};
	Double_t PhiPointErr[] = {0,0,0,0,0,0,0,0};

	//get number of event within each bin by XF and phi
	for (int i=1; i<=Phibins ; i=i+1)
	{

		for (int j=1; j<=XFbins; j=j+1)
		{

			BlueUpNum[i][j] = BlueBeamUp->GetBinContent(i,j);
			//cout<<"Blue beam Up x:"<<i<<" y:"<<j<<" n entries:"<<BlueUpNum[i][j]<<endl; 
			BlueDownNum[i][j] = BlueBeamDown->GetBinContent(i,j);
			//cout<<"Blue beam Down x:"<<i<<" y:"<<j<<" n entries:"<<BlueDownNum[i][j]<<endl; 

		}

	}

	Double_t rawAN[Phibins/2+1];
	Double_t rawANErr[Phibins/2+1];
	Double_t a,b,c,d ,  rawANnomin , rawANdenomin, rawANErrnomin , rawANErrdenomin;
	TGraphErrors *BlueBeamRawAN[XFbins+1];

	for (int j=1; j<=6; j=j+1)
	{


		for(int i=1; i<=(Phibins / 2); i=i+1)
		{

			a = BlueUpNum[i+(Phibins/2)][j]; //a: N^{up} (phi)
			b = BlueDownNum[i][j]; //b: N^{down} (phi + pi)
			c = BlueDownNum[i+(Phibins/2)][j]; //c: N^{down} (phi)
			d = BlueUpNum[i][j]; //d: N^{up} (phi + pi)

			rawANnomin = sqrt(a*b) - sqrt(c*d);
			rawANdenomin = sqrt(a*b) + sqrt(c*d);
			rawAN[i-1] = rawANnomin / rawANdenomin;

			rawANErrnomin = b*c*d + a*c*d + a*b*d + a*b*c;
			rawANErrdenomin = pow(rawANdenomin,4);
			rawANErr[i-1] = rawANErrnomin / rawANErrdenomin;
			//cout<<"XF "<<(0.1*(j-1))<<" to "<<(0.1*j)<<" phi bin: "<<(0.125*(i-1))<<"pi to "<<(0.125*i)<<"pi  raw AN="<<rawAN<<"  raw AN uncertainty="<<rawANErr<<endl;

		}
		
		BlueBeamRawAN[j] = new TGraphErrors(Phibins / 2,PhiPoint , rawAN, PhiPointErr,rawANErr);
		BlueBeamRawAN[j]->SetName(Form("BlueBeamRawAN_%i",j));
		BlueBeamRawAN[j]->SetTitle(Form("Blue Beam Raw A_{N} by x_{F} %.1f to %.1f",0.1*(j-1), 0.1*j));
		BlueBeamRawAN[j]->Write();


	}


    }





    outFile->Write();
    outFile->Close();
    delete ch;
}
