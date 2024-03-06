

#include "../../headers/goldenFileNames.h"

TFile *f1, *f2;
TH2D *H1, *H2;
TH1D *h1, *h2;
TH1D *a1, *a2;

TH1D *r;

void pthatFilterEffect(){


  f1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_newPthatFilter);
  f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_noPthatFilter);
  
  f1->GetObject("h_inclRecoJetPt_flavor_C0",H1);
  f2->GetObject("h_inclRecoJetPt_flavor_C0",H2);

  h1 = (TH1D*) H1->ProjectionX();
  h2 = (TH1D*) H2->ProjectionX();

  //h1->Draw();
  //h2->Draw("same");

  r = (TH1D*) h1->Clone("r");
  r->Divide(h1,h2,1,1,"B");

  r->Draw();
 
  
}
