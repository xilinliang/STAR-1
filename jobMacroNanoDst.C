void jobMacroNanoDst(TString fileList, TString outName)
{
    gROOT->Macro("rootlogon.C");
    AnRunDiffJetTreeMaker(fileList, outName,"fms");
//    RunFmsHotChQaMaker(fileList, outName,-1);
}
