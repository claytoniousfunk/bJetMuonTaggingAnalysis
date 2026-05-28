

void bPurityRatio(){

  TFile *file_nom = TFile::Open("../../../rootFiles/bPurityResults/latest/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");
  TFile *file_bGS = TFile::Open("../../../rootFiles/bPurityResults/latest/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root");

  TH1D *h_nom, *h_bGS;

  file_nom->GetObject("bFracResults_pp",h_nom);
  file_bGS->GetObject("bFracResults_pp",h_bGS);

  TH1D *r = (TH1D*) h_nom->Clone("r");

  r->Divide(h_bGS,h_nom,1,1,"B");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  r->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r->GetYaxis()->SetTitle("gluon-splitting-enhanced / nominal ");
  r->GetYaxis()->SetRangeUser(0.95,1);
  r->SetTitle("");
  r->SetStats(0);
  r->Draw();
  

}
