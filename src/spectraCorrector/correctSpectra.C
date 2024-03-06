#include "spectraCorrector.h"

void correctSpectra(){

  cout << endl;
  cout << "[correctSpectra] ##########  CORRECTING INPUT SPECTRA  ##############" << endl;
  cout << endl;

   cout << "[correctSpectra]...correcting pp..." << endl;
   spectraCorrector(1, 0, 0, 0);
   cout << "[correctSpectra]...done!" << endl;

  // cout << "[correctSpectra]...correcting PbPb 30-90%..." << endl;
  // spectraCorrector(0, 1, 0, 0);
  // cout << "[correctSpectra]...done!" << endl;

  // cout << "[correctSpectra]...correcting PbPb 0-30%..." << endl;
  // spectraCorrector(0, 0, 1, 0);
  // cout << "[correctSpectra]...done!" << endl;
  
}
