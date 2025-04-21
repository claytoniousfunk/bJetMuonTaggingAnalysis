// includes
#include "../../headers/goldenFileNames.h"

// definitions
TFile *file1, *file2;
TH2D *M;
TH1D *m, *d;
double I_m, E_m; // integral value and error in MC
double I_d, E_d; // integral value and error in data

void bin_calculator(double A = 60., double B = 80.){

  file1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat30);
  file2 = TFile::Open(goldenFile_PbPb_SingleMuon_mu12);

  file1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",M);
  m = (TH1D*) M->ProjectionX("m");

  file2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",d);
 
  I_m = 0.0;
  E_m = 0.0;
  
  I_m = m->IntegralAndError(m->GetXaxis()->FindBin(A),m->GetXaxis()->FindBin(B),E_m);

  cout << "Integral (MC) = " << I_m << " +/- " << E_m << endl;
  cout << "Int. / Error (MC) = " << E_m/I_m << endl;

  I_d = 0.0;
  E_d = 0.0;

  I_d = d->IntegralAndError(d->GetXaxis()->FindBin(A),d->GetXaxis()->FindBin(B),E_d);
  
  cout << "Integral (data) = " << I_d << " +/- " << E_d << endl;
  cout << "Error / Int. (data) = " << E_d/I_d << endl;

  cout << "Minimize parameter = " << I_d / (E_m / I_m)  << endl;


}
