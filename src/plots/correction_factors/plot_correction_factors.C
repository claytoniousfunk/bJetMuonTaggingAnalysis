

TFile *f1, *f2, *f3;
TFile *f4, *f5, *f6;
TFile *fi1, *fi2, *fi3;
TFile *fi4, *fi5, *fi6;
TH1D *a1, *a2, *a3, *a4, *a5, *a6;
TH1D *b1, *b2, *b3, *b4, *b5, *b6;
TH1D *c1, *c2, *c3, *c4, *c5, *c6;
TH1D *d1, *d2, *d3, *d4, *d5, *d6;
TH1D *e1;
TH1D *g1, *g2, *g3;
TH1D *h1, *h2, *h3;
TCanvas *c_a, *c_b, *c_c, *c_d, *c_e, *c_g, *c_h, *c_rat;
TPad *p_a, *p_b, *p_c, *p_d, *p_e, *p_g, *p_h, *p_rat;
TPad *pp_a, *pp_b, *pp_c, *pp_d, *pp_e, *pp_g, *pp_h, *pp_rat;
TLegend *leg_a, *leg_b, *leg_rat;


void set_pad(TPad *pad){
  pad->SetLeftMargin(0.18);
  pad->SetBottomMargin(0.15);
  pad->Draw();
}

void set_hist(TH1D *h){
  h->SetStats(0);
  h->SetTitle("");
  double label_size = 0.035;
  double title_size = 0.05;
  h->GetXaxis()->SetLabelSize(label_size);
  h->GetYaxis()->SetLabelSize(label_size);
  h->GetXaxis()->SetTitleSize(title_size);
  h->GetYaxis()->SetTitleSize(title_size);
  

}

void configure_legend(TLegend *legend, TH1D *hist_1, TString title_1, TH1D *hist_2, TString title_2, TH1D *hist_3, TString title_3){
  legend->SetBorderSize(0);
  double legend_text_size = 0.037;
  legend->SetTextSize(legend_text_size);
  legend->AddEntry(hist_1,title_1);
  legend->AddEntry(hist_2,title_2);
  legend->AddEntry(hist_3,title_3);
}

void stylize_hists(TH1D *hist_1, TH1D *hist_2, TH1D *hist_3){

  hist_1->SetTitle("");
  hist_2->SetTitle("");
  hist_3->SetTitle("");

  hist_1->SetStats(0);
  hist_2->SetStats(0);
  hist_3->SetStats(0);
  
  hist_1->SetLineColor(kBlack);
  hist_2->SetLineColor(kRed-4);
  hist_3->SetLineColor(kBlue-4);

  hist_1->SetLineWidth(2);
  hist_2->SetLineWidth(2);
  hist_3->SetLineWidth(2);

  hist_1->SetMarkerColor(kBlack);
  hist_2->SetMarkerColor(kRed-4);
  hist_3->SetMarkerColor(kBlue-4);

}

void stylize_hists(TH1D *hist_1, TH1D *hist_2, TH1D *hist_3, TH1D *hist_4, TH1D *hist_5, TH1D *hist_6){
  hist_1->SetLineColor(kBlack);
  hist_2->SetLineColor(kRed-4);
  hist_3->SetLineColor(kBlue-4);
  hist_4->SetLineColor(kBlack);
  hist_5->SetLineColor(kRed-4);
  hist_6->SetLineColor(kBlue-4);

  hist_1->SetLineWidth(2);
  hist_2->SetLineWidth(2);
  hist_3->SetLineWidth(2);
  hist_4->SetLineWidth(2);
  hist_5->SetLineWidth(2);
  hist_6->SetLineWidth(2);

  hist_1->SetLineStyle(1);
  hist_2->SetLineStyle(1);
  hist_3->SetLineStyle(1);
  hist_4->SetLineStyle(7);
  hist_5->SetLineStyle(7);
  hist_6->SetLineStyle(7);

  hist_1->SetMarkerColor(kBlack);
  hist_2->SetMarkerColor(kRed-4);
  hist_3->SetMarkerColor(kBlue-4);
  hist_4->SetMarkerColor(kBlack);
  hist_5->SetMarkerColor(kRed-4);
  hist_6->SetMarkerColor(kBlue-4);

}

void stylize_hists(TH1D *hist_1){
  hist_1->SetLineColor(kBlack);
  hist_1->SetLineWidth(2);
  hist_1->SetMarkerColor(kBlack);

}


void plot_correction_factors(){

  f1 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_pp_mu12.root");
  f2 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_C2_mu12.root");
  f3 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_C1_mu12.root");
  f4 = TFile::Open("../tagging_sequence/b_amplifiers/ba_pp_mu12_bJetNeutrinoEnergyShift.root");
  f5 = TFile::Open("../tagging_sequence/b_amplifiers/ba_C2_mu12_bJetNeutrinoEnergyShift.root");
  f6 = TFile::Open("../tagging_sequence/b_amplifiers/ba_C1_mu12_bJetNeutrinoEnergyShift.root");

  fi1 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_pp_mu12_bJets.root");
  fi2 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_C2_mu12_bJets.root");
  fi3 = TFile::Open("../tagging_sequence/matchingFactors/matchingFactor_C1_mu12_bJets.root");
  fi4 = TFile::Open("../tagging_sequence/b_amplifiers/ba_pp_mu12_bJetNeutrinoEnergyShift_bJets.root");
  fi5 = TFile::Open("../tagging_sequence/b_amplifiers/ba_C2_mu12_bJetNeutrinoEnergyShift_bJets.root");
  fi6 = TFile::Open("../tagging_sequence/b_amplifiers/ba_C1_mu12_bJetNeutrinoEnergyShift_bJets.root");
  
  f1->GetObject("r2",a1);
  f2->GetObject("r2",a2);
  f3->GetObject("r2",a3);
  fi1->GetObject("r2",a4);
  fi2->GetObject("r2",a5);
  fi3->GetObject("r2",a6);

  f1->GetObject("r3",b1);
  f2->GetObject("r3",b2);
  f3->GetObject("r3",b3);
  fi1->GetObject("r3",b4);
  fi2->GetObject("r3",b5);
  fi3->GetObject("r3",b6);

  f1->GetObject("r4",c1);
  f2->GetObject("r4",c2);
  f3->GetObject("r4",c3);
  fi1->GetObject("r4",c4);
  fi2->GetObject("r4",c5);
  fi3->GetObject("r4",c6);

  f1->GetObject("r5",d1);
  f2->GetObject("r5",d2);
  f3->GetObject("r5",d3);
  fi1->GetObject("r5",d4);
  fi2->GetObject("r5",d5);
  fi3->GetObject("r5",d6);

  f1->GetObject("r6",e1);
  f1->GetObject("r7",h1);


  


  f4->GetObject("r_corr",g1);
  f5->GetObject("r_corr",g2);
  f6->GetObject("r_corr",g3);

  stylize_hists(a1,a2,a3,a4,a5,a6);
  stylize_hists(b1,b2,b3,b4,b5,b6);
  stylize_hists(c1,c2,c3,c4,c5,c6);
  stylize_hists(d1,d2,d3,d4,d5,d6);
  stylize_hists(e1);
  stylize_hists(h1);
  stylize_hists(g1,g2,g3);

  c_a = new TCanvas("c_a","c_a",700,700);
  c_a->cd();
  p_a = new TPad("p_a","p_a",0,0.4,1,1);
  pp_a = new TPad("pp_a","pp_a",0,0,1,0.4);
  p_a->SetBottomMargin(0.18);
  pp_a->SetTopMargin(0);
  pp_a->SetBottomMargin(0.18);
  p_a->Draw();
  pp_a->Draw();
  p_a->cd();
  set_hist(a1);
  a1->GetYaxis()->SetRangeUser(0,0.16);
  a1->GetYaxis()->SetTitle("#it{#lambda}^{gen-#it{#mu}-tag}");
  a1->Draw();
  a2->Draw("same");
  a3->Draw("same");
  a4->Draw("same");
  a5->Draw("same");
  a6->Draw("same");
  leg_a = new TLegend(0.3,0.75,0.5,0.88);
  configure_legend(leg_a,a1,"PYTHIA",a2,"PYTHIA+HYDJET 30-90\%",a3,"PYTHIA+HYDJET 0-30\%");
  leg_a->Draw();
  pp_a->cd();
  TH1D *rat_pp_a = (TH1D*) a4->Clone("rat_pp_a");
  rat_pp_a->Divide(a4,a1,1,1,"");
  TH1D *rat_C2_a = (TH1D*) a5->Clone("rat_C2_a");
  rat_C2_a->Divide(a5,a2,1,1,"");  
  TH1D *rat_C1_a = (TH1D*) a6->Clone("rat_C1_a");
  rat_C1_a->Divide(a6,a3,1,1,"");
  stylize_hists(rat_pp_a,rat_C2_a,rat_C1_a);

  rat_pp_a->GetYaxis()->SetTitle("#it{#beta}^{gen-#it{#mu}-tag}");

   rat_pp_a->Draw();
   rat_C2_a->Draw("same");
   rat_C1_a->Draw("same");

  
  

  c_b = new TCanvas("c_b","c_b",700,700);
  c_b->cd();
  p_b = new TPad("p_b","p_b",0,0,1,1);
  pp_b = new TPad("pp_b","pp_b",0,0,1,0.4);
  p_b->SetBottomMargin(0.18);
  //pp_b->SetTopMargin(0);
  //pp_b->SetBottomMargin(0.18);
  p_b->Draw();
  //pp_b->Draw();
  p_b->cd();
  set_hist(b1);
  b1->GetYaxis()->SetRangeUser(0.74,1.04);
  b1->GetYaxis()->SetTitle("#it{#lambda}^{#it{#mu}-reco}");
  b1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  b1->Draw();
  b2->Draw("same");
  b3->Draw("same");
  //b4->Draw("same");
  //b5->Draw("same");
  //b6->Draw("same");
  leg_a->Draw();
  //pp_b->cd();
  TH1D *rat_pp_b = (TH1D*) b4->Clone("rat_pp_b");
  rat_pp_b->Divide(b4,b1,1,1,"");
  TH1D *rat_C2_b = (TH1D*) b5->Clone("rat_C2_b");
  rat_C2_b->Divide(b5,b2,1,1,"");  
  TH1D *rat_C1_b = (TH1D*) b6->Clone("rat_C1_b");
  rat_C1_b->Divide(b6,b3,1,1,"");
  stylize_hists(rat_pp_b,rat_C2_b,rat_C1_b);

  rat_pp_b->GetYaxis()->SetTitle("#it{#beta}^{gen-#it{#mu}-tag}");

  // rat_pp_b->Draw();
  // rat_C2_b->Draw("same");
  // rat_C1_b->Draw("same");

  c_c = new TCanvas("c_c","c_c",700,700);
  c_c->cd();
  p_c = new TPad("p_c","p_c",0,0,1,1);
  set_pad(p_c);
  p_c->cd();
  set_hist(c1);
  c1->GetYaxis()->SetRangeUser(0.96,2.04);
  c1->GetYaxis()->SetTitle("#it{#lambda}^{in-flight-#it{#mu}}");
  c1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  c1->Draw();
  c2->Draw("same");
  c3->Draw("same");
  //c4->Draw("same");
  //c5->Draw("same");
  //c6->Draw("same");
  TH1D *rat_pp_c = (TH1D*) c4->Clone("rat_pp_c");
  rat_pp_c->Divide(c4,c1,1,1,"");
  //rat_pp_c->Draw();
  TH1D *rat_C2_c = (TH1D*) c5->Clone("rat_C2_c");
  rat_C2_c->Divide(c5,c2,1,1,"");
  //rat_C2_c->Draw("same");
  TH1D *rat_C1_c = (TH1D*) c6->Clone("rat_C1_c");
  rat_C1_c->Divide(c6,c3,1,1,"");
  //rat_C1_c->Draw("same");
  
  leg_a->Draw();

  c_d = new TCanvas("c_d","c_d",700,700);
  c_d->cd();
  p_d = new TPad("p_d","p_d",0,0,1,1);
  set_pad(p_d);
  p_d->cd();
  set_hist(d1);
  d1->GetYaxis()->SetRangeUser(0.71,1.09);
  d1->GetYaxis()->SetTitle("#it{#lambda}^{#it{#mu}-trig}");
  d1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  d1->Draw();
  d2->Draw("same");
  d3->Draw("same");
  //d4->Draw("same");
  //d5->Draw("same");
  //d6->Draw("same");
  TH1D *rat_pp_d = (TH1D*) d4->Clone("rat_pp_d");
  rat_pp_d->Divide(d4,d1,1,1,"");
  //rat_pp_d->Draw();
  TH1D *rat_C2_d = (TH1D*) d5->Clone("rat_C2_d");
  rat_C2_d->Divide(d5,d2,1,1,"");
  //rat_C2_d->Draw("same");
  TH1D *rat_C1_d = (TH1D*) d6->Clone("rat_C1_d");
  rat_C1_d->Divide(d6,d3,1,1,"");
  //rat_C1_d->Draw("same");
  
  leg_b = new TLegend(0.3,0.75,0.5,0.88);
  configure_legend(leg_b,d1,"pp",d2,"PbPb 30-90\%",d3,"PbPb 0-30\%");
  //leg_b->Draw();
  leg_a->Draw();
  
  c_rat = new TCanvas("c_rat","c_rat",700,700);
  c_rat->cd();
  p_rat = new TPad("p_rat","p_rat",0,0,1,1);
  set_pad(p_rat);
  // p_rat->cd();
  // TH1D *beta_pp = (TH1D*) rat_pp_a->Clone("beta_pp");
  // TH1D *beta_C2 = (TH1D*) rat_C2_a->Clone("beta_C2");
  // TH1D *beta_C1 = (TH1D*) rat_C1_a->Clone("beta_C1");
  // stylize_hists(beta_pp,beta_C2,beta_C1);
  // beta_pp->Multiply(rat_pp_b);
  // beta_pp->Multiply(rat_pp_c);
  // beta_pp->Multiply(rat_pp_d);
  // beta_pp->Draw();
  
  // beta_C2->Multiply(rat_C2_b);
  // beta_C2->Multiply(rat_C2_c);
  // beta_C2->Multiply(rat_C2_d);
  // beta_C2->Draw("same");

  // beta_C1->Multiply(rat_C1_b);
  // beta_C1->Multiply(rat_C1_c);
  // beta_C1->Multiply(rat_C1_d);
  // beta_C1->Draw("same");


  
  c_e = new TCanvas("c_e","c_e",700,700);
  c_e->cd();
  p_e = new TPad("p_e","p_e",0,0,1,1);
  set_pad(p_e);
  p_e->cd();
  set_hist(e1);
  e1->GetYaxis()->SetRangeUser(0.69,1.88);
  e1->GetYaxis()->SetTitle("#it{#lambda}^{#it{#nu}-corr}");
  e1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  e1->Draw();

  c_g = new TCanvas("c_g","c_g",700,700);
  c_g->cd();
  p_g = new TPad("p_g","p_g",0,0,1,1);
  set_pad(p_g);
  p_g->cd();
  set_hist(g1);
  //g1->GetYaxis()->SetRangeUser(0.69,1.88);
  g1->GetYaxis()->SetTitle("#it{#beta}(#it{#lambda}_{#it{i}})");
  g1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  g1->Draw();
  g2->Draw("same");
  g3->Draw("same");
  leg_b->Draw();

  c_h = new TCanvas("c_h","c_h",700,700);
  c_h->cd();
  p_h = new TPad("p_h","p_h",0,0,1,1);
  set_pad(p_h);
  p_h->cd();
  set_hist(h1);
  h1->GetYaxis()->SetTitle("#it{#lambda}^{res}");
  h1->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h1->Draw();

  
}
