

#ifdef __CINT__

#pragma link C++ function EjJetQaPlots;                 // EM Jet QA Plots (original jet trees)

#pragma link C++ function EjMakeSimpleAnalysisTree;     // Generate final skimmed tree for A_N calculation. The branches hold simple ordinary array
#pragma link C++ function EjSimpleAnalysisTreeQa;       // Analysis Tree QA Plots
#pragma link C++ function EjCreateSimpleBinnedHist;     // Create binned histograms in pt, E, phi, #photons, spin to be used to extract yield

#pragma link C++ function EjMakeAnalysisTree;           // Generate skimmed analysis tree for A_N calculation from big jet trees (without the Maker chain)
#pragma link C++ function EjRunEmJetTreeMaker;          // Run Em Jet Tree maker. Skimmed analysis Nano jet tree from big jet tree (inside the maker). This is the integrated version of the EjMakerAnalysisTree
#pragma link C++ function EjReadAnalysisTree;           // Example of how to read analysis tree
#pragma link C++ function EjAnalysisTreeQa;             // Analysis Tree QA
#pragma link C++ function EjCreateBinnedHist;           // Create binned histograms in pt, E, phi, #photons, spin to be used to extract yield

#pragma link C++ function EjCalculateAN;                // Calculate A_N from binned histograms

#endif
