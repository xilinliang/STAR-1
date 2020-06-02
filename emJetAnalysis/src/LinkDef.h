

#ifdef __CINT__

//#pragma link C++ class TStJetParticle;                         // EM Jet Particle Container Class
//#pragma link C++ class TStJetTower;                            // EM Jet Tower Container Class
//#pragma link C++ class TStJetCandidate;                        // EM Jet Candidate Container Class
#pragma link C++ function EjQaPlots;                           // EM Jet QA Plots
#pragma link C++ function EjMakeAnalysisTree;                  // Generate final skimmed tree for A_N calculation
#pragma link C++ function EjAnalysisTreeQa;                    // Analysis Tree QA Plots
#pragma link C++ function EjCreateBinnedHist;                  // Create binned histograms in pt, E, phi, #photons, spin to be used to extract yield
#pragma link C++ function EjCalculateAN;                       // Calculate A_N from binned histograms

#endif