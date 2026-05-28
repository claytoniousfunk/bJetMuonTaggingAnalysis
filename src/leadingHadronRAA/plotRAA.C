


void plotRAA(){

  TFile *file_pp = TFile::Open("../../rootFiles/leadingHadronRAA/trkHistograms_pp.root");
  TFile *file_PbPb = TFile::Open("../../rootFiles/leadingHadronRAA/trkHistograms_PbPb.root");

  TH1D *vz_pp;
  TH1D *vz_C4;
  TH1D *vz_C3;
  TH1D *vz_C2;
  TH1D *vz_C1;

  TH1D *trkpt_pp;
  TH1D *trkpt_C4;
  TH1D *trkpt_C3;
  TH1D *trkpt_C2;
  TH1D *trkpt_C1;

  file_pp->GetObject("h_vz_pp",vz_pp);
  file_pp->GetObject("h_trkpt_pp",trkpt_pp);

  file_PbPb->GetObject("h_vz_PbPb_C4",vz_C4);
  file_PbPb->GetObject("h_trkpt_PbPb_C4",trkpt_C4);

  file_PbPb->GetObject("h_vz_PbPb_C3",vz_C3);
  file_PbPb->GetObject("h_trkpt_PbPb_C3",trkpt_C3);

  file_PbPb->GetObject("h_vz_PbPb_C2",vz_C2);
  file_PbPb->GetObject("h_trkpt_PbPb_C2",trkpt_C2);

  file_PbPb->GetObject("h_vz_PbPb_C1",vz_C1);
  file_PbPb->GetObject("h_trkpt_PbPb_C1",trkpt_C1);

  /////////////////////////////////////////////////////////////////

  trkpt_pp->Scale(1./vz_pp->Integral());
  trkpt_C4->Scale(1./(0.7452*vz_C4->Integral()));
  trkpt_C3->Scale(1./(3.95*vz_C3->Integral()));
  trkpt_C2->Scale(1./(11.60*vz_C2->Integral()));
  trkpt_C1->Scale(1./(23.05*vz_C1->Integral()));

  ////////////////////////////////////////////////////////////////

  TH1D *RAA_C4;
  TH1D *RAA_C3;
  TH1D *RAA_C2;
  TH1D *RAA_C1;

  RAA_C4 = (TH1D*) trkpt_C4->Clone("RAA_C4");
  RAA_C3 = (TH1D*) trkpt_C3->Clone("RAA_C3");
  RAA_C2 = (TH1D*) trkpt_C2->Clone("RAA_C2");
  RAA_C1 = (TH1D*) trkpt_C1->Clone("RAA_C1");

  RAA_C4->Divide(trkpt_C4,trkpt_pp,1,1,"");
  RAA_C3->Divide(trkpt_C3,trkpt_pp,1,1,"");
  RAA_C2->Divide(trkpt_C2,trkpt_pp,1,1,"");
  RAA_C1->Divide(trkpt_C1,trkpt_pp,1,1,"");

  RAA_C1->GetYaxis()->SetRangeUser(0,1);
  RAA_C1->Draw();
  

  


}
