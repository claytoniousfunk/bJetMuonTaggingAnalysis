


void plotTriggerDependence(bool doPP = 1,
			   bool doC2 = 0,
			   bool doC1 = 0){

  TFile *f1 = TFile::Open("./rootFiles/output_inclRecoMuonTag.root");
  TFile *f2 = TFile::Open("./rootFiles/output_inclRecoMuonTag_triggerOn.root");

  TH1D *taggingFreq_pp_mc, *taggingFreq_pp_data;
  TH1D *taggingFreq_C2_mc, *taggingFreq_C2_data;
  TH1D *taggingFreq_C1_mc, *taggingFreq_C1_data;
  
  TH1D *taggingFreq_trig_pp_mc, *taggingFreq_trig_pp_data;
  TH1D *taggingFreq_trig_C2_mc, *taggingFreq_trig_C2_data;
  TH1D *taggingFreq_trig_C1_mc, *taggingFreq_trig_C1_data;

  TString systemString = "";
  if(doPP) systemString = "pp";
  else if(doC2) systemString = "PbPb_C2";
  else if(doC1) systemString = "PbPb_C1";
  else {};

  f1->GetObject(Form("taggingFreq_%s_MC",systemString.Data()),taggingFreq_pp_mc);
  f2->GetObject(Form("taggingFreq_%s_MC",systemString.Data()),taggingFreq_trig_pp_mc);

  f1->GetObject(Form("taggingFreq_%s_data",systemString.Data()),taggingFreq_pp_data);
  f2->GetObject(Form("taggingFreq_%s_data",systemString.Data()),taggingFreq_trig_pp_data);

  taggingFreq_pp_mc->SetLineColor(kBlue-4);
  taggingFreq_trig_pp_mc->SetLineColor(kBlue-4);
  taggingFreq_pp_mc->SetLineWidth(2);
  taggingFreq_trig_pp_mc->SetLineWidth(2);
  taggingFreq_trig_pp_mc->SetLineStyle(7);

  taggingFreq_pp_data->SetLineColor(kRed-4);
  taggingFreq_trig_pp_data->SetLineColor(kRed-4);
  taggingFreq_pp_data->SetLineWidth(2);
  taggingFreq_trig_pp_data->SetLineWidth(2);
  taggingFreq_trig_pp_data->SetLineStyle(7);


  TH1D *r_trig_pp_mc = (TH1D*) taggingFreq_trig_pp_mc->Clone("r");
  r_trig_pp_mc->Divide(taggingFreq_trig_pp_mc,taggingFreq_pp_mc,1,1,"B");
  //r_trig_pp_mc->Draw();

  TH1D *r_trig_pp_data = (TH1D*) taggingFreq_trig_pp_data->Clone("r_trig_pp_data");
  r_trig_pp_data->Divide(taggingFreq_trig_pp_data,taggingFreq_pp_data,1,1,"B");
  //r_trig_pp_data->Draw();



  TString legendString_mc = "";
  TString legendString_trig_mc = "";
  TString legendString_data = "";
  TString legendString_trig_data = "";

  if(doPP){
    legendString_mc = "PYTHIA";
    legendString_trig_mc = "PYTHIA + mu12";
    legendString_data = "pp";
    legendString_trig_data = "pp + mu12";
  }
  if(doC2){
    legendString_mc = "PH 30-90%";
    legendString_trig_mc = "PH 30-90% + mu12";
    legendString_data = "PbPb 30-90%";
    legendString_trig_data = "PbPb 30-90% + mu12";
  }
  if(doC1){
    legendString_mc = "PH 0-30%";
    legendString_trig_mc = "PH 0-30% + mu12";
    legendString_data = "PbPb 0-30%";
    legendString_trig_data = "PbPb 0-30% + mu12";
  }
  

  TLegend *leg = new TLegend(0.5,0.7,0.8,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  
  leg->AddEntry(taggingFreq_pp_mc,legendString_mc);
  leg->AddEntry(taggingFreq_trig_pp_mc,legendString_trig_mc);
  leg->AddEntry(taggingFreq_pp_data,legendString_data);
  leg->AddEntry(taggingFreq_trig_pp_data,legendString_trig_data);
  

  TCanvas *c_pp = new TCanvas("c_pp","c_pp",700,700);
  c_pp->cd();
  TPad *pu_pp = new TPad("pu_pp","pd_pp",0,0.4,1,1); // upper pad
  TPad *pl_pp = new TPad("pl_pp","pd_pp",0,0,1,0.4); // lower pad
  pu_pp->SetBottomMargin(0);
  pl_pp->SetTopMargin(0);
  pu_pp->SetLeftMargin(0.15);
  pl_pp->SetLeftMargin(0.15);
  pu_pp->SetTopMargin(0.1);
  pl_pp->SetBottomMargin(0.15);
  pu_pp->Draw();
  pl_pp->Draw();
  pu_pp->cd();
  taggingFreq_pp_data->SetStats(0);
  taggingFreq_pp_data->SetTitle("");
  taggingFreq_pp_data->GetYaxis()->SetTitleSize(0.06);
  taggingFreq_pp_data->GetYaxis()->SetLabelSize(0.045);
  taggingFreq_pp_data->GetYaxis()->SetRangeUser(0,0.01);
  taggingFreq_pp_data->GetYaxis()->SetTitle("Muon-tag fraction");
  r_trig_pp_data->SetStats(0);
  r_trig_pp_data->SetTitle("");
  r_trig_pp_data->GetYaxis()->SetTitleSize(0.08);
  r_trig_pp_data->GetYaxis()->SetLabelSize(0.06);
  r_trig_pp_data->GetYaxis()->SetRangeUser(0.75,1.05);
  r_trig_pp_data->GetYaxis()->SetTitle("Trig / no-trig  ");
  taggingFreq_pp_data->Draw("hist");
  taggingFreq_trig_pp_data->Draw("hist same");
  taggingFreq_pp_mc->Draw("hist same");
  taggingFreq_trig_pp_mc->Draw("hist same");
  leg->Draw();
  pl_pp->cd();
  r_trig_pp_data->Draw("hist");
  r_trig_pp_mc->Draw("hist same");

  c_pp->SaveAs(Form("./figures/muonTagFraction_%s.pdf",systemString.Data()));

}
