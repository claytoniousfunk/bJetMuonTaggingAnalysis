

double lowPTFitFxn(double *x, double *par){
  double fitval = par[0] + (par[1] - par[0])*exp(-par[2]*x[0]);  
  return fitval;
}



void normalize(TH1D *h){
  h->Scale(1./h->Integral());
  return;
}


void spectraCompare(){

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  TF1 *PTFitFxn = new TF1("PTFitFxn",lowPTFitFxn,80,500,3);
  
  TFile *f_data, *f_mc;

  f_data = TFile::Open("./rootFiles/CorrectedBJetSpectra/Data/histograms_CorrectedBJetSpectra.root");
  f_mc = TFile::Open("./rootFiles/CorrectedBJetSpectra/MC/histograms_CorrectedBJetSpectra.root");

  TH1D *jetPt_pp_mc, *jetPt_C4_mc, *jetPt_C3_mc, *jetPt_C2_mc, *jetPt_C1_mc;
  TH1D *jetPt_pp_data, *jetPt_C4_data, *jetPt_C3_data, *jetPt_C2_data, *jetPt_C1_data;

  f_mc->GetObject("h_bJetPt_corr_pp",jetPt_pp_mc);
  f_mc->GetObject("h_bJetPt_corr_C4",jetPt_C4_mc);
  f_mc->GetObject("h_bJetPt_corr_C3",jetPt_C3_mc);
  f_mc->GetObject("h_bJetPt_corr_C2",jetPt_C2_mc);
  f_mc->GetObject("h_bJetPt_corr_C1",jetPt_C1_mc);

  f_data->GetObject("h_bJetPt_corr_pp",jetPt_pp_data);
  f_data->GetObject("h_bJetPt_corr_C4",jetPt_C4_data);
  f_data->GetObject("h_bJetPt_corr_C3",jetPt_C3_data);
  f_data->GetObject("h_bJetPt_corr_C2",jetPt_C2_data);
  f_data->GetObject("h_bJetPt_corr_C1",jetPt_C1_data);

     
  normalize(jetPt_pp_mc);
  normalize(jetPt_C4_mc);
  normalize(jetPt_C3_mc);
  normalize(jetPt_C2_mc);
  normalize(jetPt_C1_mc);

  jetPt_pp_data->Draw();

  normalize(jetPt_pp_data);
  normalize(jetPt_C4_data);
  normalize(jetPt_C3_data);
  normalize(jetPt_C2_data);
  normalize(jetPt_C1_data);

  TH1D *r_pp, *r_C4, *r_C3, *r_C2, *r_C1;

  r_pp = (TH1D*) jetPt_pp_data->Clone("r_pp");
  r_pp->Divide(jetPt_pp_data,jetPt_pp_mc,1,1,"");

  r_C4 = (TH1D*) jetPt_C4_data->Clone("r_C4");
  r_C4->Divide(jetPt_C4_data,jetPt_C4_mc,1,1,"");

  r_C3 = (TH1D*) jetPt_C3_data->Clone("r_C3");
  r_C3->Divide(jetPt_C3_data,jetPt_C3_mc,1,1,"");

  r_C2 = (TH1D*) jetPt_C2_data->Clone("r_C2");
  r_C2->Divide(jetPt_C2_data,jetPt_C2_mc,1,1,"");

  r_C1 = (TH1D*) jetPt_C1_data->Clone("r_C1");
  r_C1->Divide(jetPt_C1_data,jetPt_C1_mc,1,1,"");

  TLegend *leg = new TLegend(0.6,0.6,0.88,0.88);
  leg->SetTextSize(0.03);
  leg->SetBorderSize(0);
  //leg->AddEntry(r_pp,"pp","p");
  leg->AddEntry(r_C4,"PbPb 50-80%","p");
  //leg->AddEntry(r_C3,"PbPb 30-50%","p");
  //leg->AddEntry(r_C2,"PbPb 10-30%","p");
  //leg->AddEntry(r_C1,"PbPb 0-10%","p");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  r_C4->SetStats(0);
  r_C4->SetTitle("");
  r_C4->GetYaxis()->SetTitleSize(0.06);
  r_C4->GetYaxis()->SetLabelSize(0.048);
  r_C4->GetXaxis()->SetTitleSize(0.06);
  r_C4->GetXaxis()->SetLabelSize(0.048);
  r_C4->SetTitle("Ratio of #it{b}-jet Spectra Shape");
  r_C4->GetYaxis()->SetTitle("Data / MC");
  r_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_C4->GetYaxis()->SetRangeUser(0,2);
  r_C4->GetXaxis()->SetRangeUser(80,300);
  r_C4->Draw();
  //r_C4->Draw("same");
  //r_C3->Draw("same");
  //r_C2->Draw("same");
  //r_C1->Draw("same");
  // r_C1->Draw("same");
  leg->Draw();  
  li->DrawLine(80,1,300,1);
  
  //r_C1->Fit("PTFitFxn","R","R",80,500);
  //r_C2->Fit("PTFitFxn","R","R",80,300);
  
  //r_C3->Fit("PTFitFxn","R","R",80,300);
  r_C4->Fit("PTFitFxn","R","R",80,300);

  
}
