

double lowPTFitFxn(double *x, double *par){
  double fitval = par[0] + par[1]*exp(-par[2]*x[0]);  
  return fitval;
}



void normalize(TH1D *h){
  h->Scale(1./h->Integral());
  return;
}


void spectraCompare(){

  TF1 *PTFitFxn = new TF1("PTFitFxn",lowPTFitFxn,80,500,3);
  
  TFile *f_data, *f_mc;

  f_data = TFile::Open("./rootFiles/MuTagMuTrigBJetSpectra/Data/histograms_MuTagMuTrigBJetSpectra.root");
  f_mc = TFile::Open("./rootFiles/MuTagMuTrigBJetSpectra/MC/histograms_MuTagMuTrigBJetSpectra.root");

  TH1D *jetPt_pp_mc, *jetPt_C3_mc, *jetPt_C2_mc, *jetPt_C1_mc;
  TH1D *jetPt_pp_data, *jetPt_C3_data, *jetPt_C2_data, *jetPt_C1_data;

  f_mc->GetObject("h_bJetPt_muTag_muTrig_pp",jetPt_pp_mc);
  f_mc->GetObject("h_bJetPt_muTag_muTrig_C3",jetPt_C3_mc);
  f_mc->GetObject("h_bJetPt_muTag_muTrig_C2",jetPt_C2_mc);
  f_mc->GetObject("h_bJetPt_muTag_muTrig_C1",jetPt_C1_mc);

  f_data->GetObject("h_bJetPt_muTag_muTrig_pp",jetPt_pp_data);
  f_data->GetObject("h_bJetPt_muTag_muTrig_C3",jetPt_C3_data);
  f_data->GetObject("h_bJetPt_muTag_muTrig_C2",jetPt_C2_data);
  f_data->GetObject("h_bJetPt_muTag_muTrig_C1",jetPt_C1_data);

  normalize(jetPt_pp_mc);
  normalize(jetPt_C3_mc);
  normalize(jetPt_C2_mc);
  normalize(jetPt_C1_mc);

  normalize(jetPt_pp_data);
  normalize(jetPt_C3_data);
  normalize(jetPt_C2_data);
  normalize(jetPt_C1_data);

  TH1D *r_pp, *r_C3, *r_C2, *r_C1;

  r_pp = (TH1D*) jetPt_pp_data->Clone("r_pp");
  r_pp->Divide(jetPt_pp_data,jetPt_pp_mc,1,1,"");

  r_C3 = (TH1D*) jetPt_C3_data->Clone("r_C3");
  r_C3->Divide(jetPt_C3_data,jetPt_C3_mc,1,1,"");

  r_C2 = (TH1D*) jetPt_C2_data->Clone("r_C2");
  r_C2->Divide(jetPt_C2_data,jetPt_C2_mc,1,1,"");

  r_C1 = (TH1D*) jetPt_C1_data->Clone("r_C1");
  r_C1->Divide(jetPt_C1_data,jetPt_C1_mc,1,1,"");



  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  r_pp->SetStats(0);
  r_pp->SetTitle("");
  r_pp->GetYaxis()->SetTitleSize(0.06);
  r_pp->GetYaxis()->SetLabelSize(0.048);
  r_pp->GetXaxis()->SetTitleSize(0.06);
  r_pp->GetXaxis()->SetLabelSize(0.048);
  r_pp->GetYaxis()->SetTitle("Data / MC");
  r_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_pp->GetYaxis()->SetRangeUser(0,2);
  r_pp->Draw();
  r_C3->Draw("same");
  r_C2->Draw("same");
  r_C1->Draw("same");

  // r_C1->Fit("PTFitFxn");
  // r_C2->Fit("PTFitFxn");
  // r_C3->Fit("PTFitFxn");

}
