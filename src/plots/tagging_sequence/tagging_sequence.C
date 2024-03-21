
#include "../../../headers/goldenFileNames.h"

void tagging_sequence(bool do_pp = 1,
		      bool do_C2 = 0,
		      bool do_C1 = 0,
		      bool do_mu5 = 0,
		      bool do_mu7 = 1,
		      bool do_mu12 = 0){

  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.06);


  TString input_PYTHIA;
  TString input_pp_SingleMuon;
  TString input_pp_MinBias;
  TString input_PYTHIAHYDJET;
  TString input_PbPb_SingleMuon;
  TString input_PbPb_MinBias;

  if(do_mu5){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu5;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu5;
    input_pp_MinBias   = goldenFile_pp_MinBias_mu5;
    input_PbPb_MinBias = goldenFile_PbPb_MinBias_mu5;
    input_PYTHIA = goldenFile_PYTHIA_mu5_pThat30;
    input_PYTHIAHYDJET = goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat30;

  }
  else if(do_mu7){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu7;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu7;
    input_pp_MinBias   = goldenFile_pp_MinBias_mu7;
    input_PbPb_MinBias = goldenFile_PbPb_MinBias_mu7;
    input_PYTHIA = goldenFile_PYTHIA_mu7_pThat30;
    input_PYTHIAHYDJET = goldenFile_PYTHIAHYDJET_DiJet_mu7_pThat30;

  }
  else if(do_mu12){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu12;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu12;
    input_pp_MinBias   = goldenFile_pp_MinBias_mu12;
    input_PbPb_MinBias = goldenFile_PbPb_MinBias_mu12;
    input_PYTHIA = goldenFile_PYTHIA_mu12_pThat30;
    input_PYTHIAHYDJET = goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat30;

  }
  else{};
  

  TFile *f_py , *f_mb, *f_sm;

  if(do_pp){
    f_py = TFile::Open(input_PYTHIA);
    f_mb = TFile::Open(input_pp_MinBias);
    f_sm = TFile::Open(input_pp_SingleMuon);
  }
  else if(do_C1 || do_C2){
    f_py = TFile::Open(input_PYTHIAHYDJET);
    f_mb = TFile::Open(input_PbPb_MinBias);
    f_sm = TFile::Open(input_PbPb_SingleMuon);
  }
  else{};

  
  // MC histograms
  TH2D *H_inclGen, *H_inclReco, *H_inclMuTag, *H_genMuTag, *H_matchedRecoMuTag, *H_trig;  // 2D histograms
  TH1D *h_inclGen, *h_inclReco, *h_inclMuTag, *h_genMuTag, *h_matchedRecoMuTag, *h_trig;  // all flavors
  TH1D *b_inclGen, *b_inclReco, *b_inclMuTag, *b_genMuTag, *b_matchedRecoMuTag, *b_trig;  // b jets
  TH1D *bb_inclGen, *bb_inclReco, *bb_inclMuTag, *bb_genMuTag, *bb_matchedRecoMuTag, *bb_trig;  // b-bar jets


  string centrality_identifier = "";
  if(do_C1) centrality_identifier = "_C1";
  else if(do_C2) centrality_identifier = "_C2";
  else{};
  
  
  f_py->GetObject(Form("h_inclGenJetPt_flavor%s",centrality_identifier.c_str()),H_inclGen);
  f_py->GetObject(Form("h_inclRecoJetPt_flavor%s",centrality_identifier.c_str()),H_inclReco);
  f_py->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_flavor%s",centrality_identifier.c_str()),H_inclMuTag);
  f_py->GetObject(Form("h_inclRecoJetPt_inclGenMuonTag_flavor%s",centrality_identifier.c_str()),H_genMuTag);
  f_py->GetObject(Form("h_inclRecoJetPt_matchedRecoMuonTag_flavor%s",centrality_identifier.c_str()),H_matchedRecoMuTag);
  f_py->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor%s",centrality_identifier.c_str()),H_trig);

  // data histograms
  TH1D *d_inclReco, *d_inclMuTag, *d_trig;


  f_sm->GetObject(Form("h_inclRecoJetPt%s",centrality_identifier.c_str()),d_inclReco);
  f_sm->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag%s",centrality_identifier.c_str()),d_inclMuTag);
  f_sm->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn%s",centrality_identifier.c_str()),d_trig);

  
  h_inclGen = H_inclGen->ProjectionX();
  h_inclReco = H_inclReco->ProjectionX();
  h_inclMuTag = H_inclMuTag->ProjectionX();
  h_genMuTag = H_genMuTag->ProjectionX();
  h_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX();
  h_trig = H_trig->ProjectionX();

  b_inclGen = H_inclGen->ProjectionX("b_inclGen",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_inclReco = H_inclReco->ProjectionX("b_inclReco",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_inclMuTag = H_inclMuTag->ProjectionX("b_inclMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_genMuTag = H_genMuTag->ProjectionX("b_genMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("b_matchedRecoMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_trig = H_trig->ProjectionX("b_trig",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));

  bb_inclGen = H_inclGen->ProjectionX("bb_inclGen",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_inclReco = H_inclReco->ProjectionX("bb_inclReco",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_inclMuTag = H_inclMuTag->ProjectionX("bb_inclMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_genMuTag = H_genMuTag->ProjectionX("bb_genMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("bb_matchedRecoMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_trig = H_trig->ProjectionX("bb_trig",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));

  b_inclGen->Add(bb_inclGen);
  b_inclReco->Add(bb_inclReco);
  b_inclMuTag->Add(bb_inclMuTag);
  b_genMuTag->Add(bb_genMuTag);
  b_matchedRecoMuTag->Add(bb_matchedRecoMuTag);
  b_trig->Add(bb_trig);




  // treat h = b
  // h_inclGen = (TH1D*) b_inclGen->Clone("h_inclGen");
  // h_inclReco = (TH1D*) b_inclReco->Clone("h_inclReco");
  // h_inclMuTag = (TH1D*) b_inclMuTag->Clone("h_inclMuTag");
  // h_genMuTag = (TH1D*) b_genMuTag->Clone("h_genMuTag");
  // h_matchedRecoMuTag = (TH1D*) b_matchedRecoMuTag->Clone("h_matchedRecoMuTag");
  // h_trig = (TH1D*) b_trig->Clone("h_trig");


  TH1D *rb_trig = (TH1D*) b_trig->Clone("rb_trig");
  rb_trig->Divide(b_trig,h_trig,1,1,"B");

  TH1D *rb_inclReco = (TH1D*) b_inclReco->Clone("rb_inclReco");
  rb_inclReco->Divide(b_inclReco,h_inclReco,1,1,"B");
  
  
  // style
  //---- colors
  
  h_inclGen->SetMarkerColor(kBlack);
  h_inclReco->SetMarkerColor(kBlack);
  h_inclMuTag->SetMarkerColor(kBlue-4);
  h_genMuTag->SetMarkerColor(kRed-4);
  h_matchedRecoMuTag->SetMarkerColor(kGreen+2);
  h_trig->SetMarkerColor(kMagenta);
  d_inclReco->SetMarkerColor(kBlack);
  d_inclMuTag->SetMarkerColor(kBlue-4);
  d_trig->SetMarkerColor(kMagenta);
  
  h_inclGen->SetLineColor(kBlack);
  h_inclReco->SetLineColor(kBlack);
  h_inclMuTag->SetLineColor(kBlue-4);
  h_genMuTag->SetLineColor(kRed-4);
  h_matchedRecoMuTag->SetLineColor(kGreen+2);
  h_trig->SetLineColor(kMagenta);
  d_inclReco->SetLineColor(kBlack);
  d_inclMuTag->SetLineColor(kBlue-4);
  d_trig->SetLineColor(kMagenta);
  

  h_inclGen->SetLineWidth(2);
  h_inclReco->SetLineWidth(2);
  h_inclMuTag->SetLineWidth(2);
  h_genMuTag->SetLineWidth(2);
  h_matchedRecoMuTag->SetLineWidth(2);
  h_trig->SetLineWidth(2);
  d_inclReco->SetLineWidth(2);
  d_inclMuTag->SetLineWidth(2);
  d_trig->SetLineWidth(2);

  
  TH1D *r1, *r2, *r3, *r4, *r5;
  r1 = (TH1D*) h_inclReco->Clone("r1");
  r1->Divide(h_inclReco,h_inclGen,1,1,"B");
  r2 = (TH1D*) h_genMuTag->Clone("r2");
  r2->Divide(h_genMuTag,h_inclReco,1,1,"B");
  r3 = (TH1D*) h_matchedRecoMuTag->Clone("r3");
  r3->Divide(h_matchedRecoMuTag,h_genMuTag,1,1,"B");
  r4 = (TH1D*) h_inclMuTag->Clone("r4");
  r4->Divide(h_inclMuTag,h_matchedRecoMuTag,1,1,"B");
  r5 = (TH1D*) h_trig->Clone("r5");
  r5->Divide(h_trig,h_inclMuTag,1,1,"B");

  TH1D *rr1, *rr2, *rr3;
  rr1 = (TH1D*) d_inclMuTag->Clone("rr1");
  rr1->Divide(d_inclMuTag,d_inclReco,1,1,"B");
  rr2 = (TH1D*) d_trig->Clone("rr2");
  rr2->Divide(d_trig,d_inclMuTag,1,1,"B");

  TCanvas *c_dSpectra = new TCanvas("c_dSpectra","c_dSpectra",700,700);
  c_dSpectra->cd();
  TPad *p_dSpectra_1 = new TPad("p_dSpectra_1", "p_dSpectra_1", 0,0.4,1,1);
  TPad *p_dSpectra_2 = new TPad("p_dSpectra_2", "p_dSpectra_2", 0,0.0,1,0.4);
  p_dSpectra_1->SetLeftMargin(0.2);
  p_dSpectra_1->SetBottomMargin(0.0);
  p_dSpectra_1->SetTopMargin(0.1);
  p_dSpectra_2->SetLeftMargin(0.2);
  p_dSpectra_2->SetBottomMargin(0.2);
  p_dSpectra_2->SetTopMargin(0.0);
  p_dSpectra_1->SetLogy();
  p_dSpectra_1->Draw();
  p_dSpectra_2->Draw();
  p_dSpectra_1->cd();
  d_inclReco->SetStats(0);
  d_inclReco->SetTitle("");
  d_inclReco->GetYaxis()->SetTitle("Entries");
  //d_inclReco->GetYaxis()->SetRangeUser(1,1e04);
  d_inclReco->GetYaxis()->SetRangeUser(1,1e08);
  d_inclReco->Draw();
  d_inclMuTag->Draw("same");
  TLegend *leg2 = new TLegend(0.6,0.4,0.85,0.85);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.040);
  leg2->AddEntry(d_inclReco,"incl. reco");
  leg2->AddEntry(d_inclMuTag,"#mu^{inclReco} tagged");
  leg2->Draw();
  la->SetTextFont(62);
  la->SetTextSize(0.06);
  //la->DrawLatexNDC(0.2,0.92,"pp MinBias #sqrt{s_{NN}} = 5.02 TeV");
  la->DrawLatexNDC(0.2,0.92,"PbPb SingleMuon #sqrt{s_{NN}} = 5.02 TeV");
  la->SetTextFont(42);
  la->SetTextSize(0.042);
  la->DrawLatexNDC(0.25,0.2,"#font[52]{p}_{T}^{#mu} > 7 GeV");
  p_dSpectra_2->cd();
  rr1->SetStats(0);
  rr1->SetTitle("");
  rr1->GetYaxis()->SetTitleSize(0.06);
  rr1->GetXaxis()->SetTitleSize(0.06);
  rr1->GetYaxis()->SetLabelSize(0.05);
  rr1->GetXaxis()->SetLabelSize(0.05);
  rr1->GetYaxis()->SetTitle("Ratio  ");
  rr1->GetXaxis()->SetTitle("#font[52]{p}^{recoJet}_{T} [GeV]");
  rr1->GetYaxis()->SetRangeUser(0,0.02);
  rr1->Draw();
  c_dSpectra->SaveAs("./data_inclMuTag.png");
  p_dSpectra_1->cd();
  d_trig->Draw("same");
  // la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu5_NHitQ10");
  la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu7_NHitQ10");
  //la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu12");
  leg2->AddEntry(d_trig,"#mu-triggered");
  p_dSpectra_2->cd();
  rr1->GetYaxis()->SetRangeUser(0,2);
  rr2->Draw("same");
  li->DrawLine(0,1,500,1);
  c_dSpectra->SaveAs("./data_trig.png");
  

  TCanvas *c_spectra = new TCanvas("c_spectra", "c_spectra", 700,700);
  c_spectra->cd();
  TPad *p_spectra_1 = new TPad("p_spectra_1", "p_spectra_1", 0,0.4,1,1);
  TPad *p_spectra_2 = new TPad("p_spectra_2", "p_spectra_2", 0,0.0,1,0.4);
  p_spectra_1->SetLeftMargin(0.2);
  p_spectra_1->SetBottomMargin(0.0);
  p_spectra_1->SetTopMargin(0.1);
  p_spectra_2->SetLeftMargin(0.2);
  p_spectra_2->SetBottomMargin(0.2);
  p_spectra_2->SetTopMargin(0.0);
  p_spectra_1->SetLogy();
  p_spectra_1->Draw();
  p_spectra_2->Draw();
  p_spectra_1->cd();
  h_inclReco->SetStats(0);
  h_inclReco->SetTitle("");
  h_inclReco->GetYaxis()->SetTitle("Weighted Entries");
  h_inclReco->GetYaxis()->SetRangeUser(1e-04,3e04);
  h_inclReco->Draw();
  h_genMuTag->Draw("same");
  TLegend *leg1 = new TLegend(0.6,0.4,0.85,0.85);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.040);
  leg1->AddEntry(h_inclReco,"incl. reco");
  leg1->AddEntry(h_genMuTag,"#mu^{gen} tagged");
  leg1->Draw();
  la->SetTextFont(62);
  la->SetTextSize(0.06);
  if(do_pp) la->DrawLatexNDC(0.2,0.92,"PYTHIA 5.02 TeV");
  else if(do_C1) la->DrawLatexNDC(0.2,0.92,"PYTHIA+HYDJET 0-30% 5.02 TeV");
  else if(do_C2) la->DrawLatexNDC(0.2,0.92,"PYTHIA+HYDJET 30-90% 5.02 TeV");
  else{};
  la->SetTextFont(42);
  la->SetTextSize(0.042);
  la->DrawLatexNDC(0.25,0.28,"#hat{#font[52]{p}}_{T} > 30 GeV");
  la->DrawLatexNDC(0.25,0.2,"#font[52]{p}_{T}^{#mu} > 7 GeV");
  p_spectra_2->cd();
  r2->SetStats(0);
  r2->SetTitle("");
  r2->GetYaxis()->SetTitleSize(0.06);
  r2->GetXaxis()->SetTitleSize(0.06);
  r2->GetYaxis()->SetLabelSize(0.05);
  r2->GetXaxis()->SetLabelSize(0.05);
  r2->GetYaxis()->SetTitle("Ratio  ");
  r2->GetXaxis()->SetTitle("#font[52]{p}^{recoJet}_{T} [GeV]");
  r2->GetYaxis()->SetRangeUser(0.0,0.02);
  r2->Draw();
  c_spectra->SaveAs("./genMuTag.png");
  p_spectra_1->cd();
  h_matchedRecoMuTag->Draw("same");
  leg1->AddEntry(h_matchedRecoMuTag,"#mu^{matchedReco} tagged");
  leg1->Draw();
  p_spectra_2->cd();
  r2->GetYaxis()->SetRangeUser(0.0,2.0);
  li->DrawLine(0,1,500,1);
  r3->Draw("same");
  c_spectra->SaveAs("./matchedRecoMuTag.png");
  p_spectra_1->cd();
  h_inclMuTag->Draw("same");
  leg1->AddEntry(h_inclMuTag,"#mu^{inclReco} tagged");
  leg1->Draw();
  p_spectra_2->cd();
  r2->GetYaxis()->SetRangeUser(0.0,2.0);
  r4->Draw("same");
  c_spectra->SaveAs("./inclMuTag.png");
  p_spectra_1->cd();
  h_trig->Draw("same");
  leg1->AddEntry(h_trig,"#mu-triggered");
  leg1->Draw();
  if(do_mu5) la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu5_NHitQ10");
  else if(do_mu7) la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu7_NHitQ10");
  else if(do_mu12) la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu12");
  else{};
  p_spectra_2->cd();
  r5->Draw("same");
  c_spectra->SaveAs("./trig.png");


   TCanvas *c_factor = new TCanvas("c_factor", "c_factor", 700,700);
   c_factor->cd();
   TPad *p_mf = new TPad("p_mf","p_mf",0,0,1,1);
   p_mf->SetLeftMargin(0.2);
   p_mf->SetBottomMargin(0.2);
   p_mf->Draw();
   p_mf->cd();
   TH1D *mf; // mf = matching factor
   mf = (TH1D*) r2->Clone("mf");
   mf->Multiply(r3);
   mf->Multiply(r4);
   //mf->Multiply(rr2);
   //mf->Scale(3.0);
   mf->Multiply(r5);
   mf->GetYaxis()->SetLabelSize(0.04);
   mf->GetXaxis()->SetLabelSize(0.04);
   mf->GetXaxis()->SetTitleSize(0.05);
   mf->GetYaxis()->SetTitleSize(0.05);
   mf->GetYaxis()->SetTitle("Matching factor");
   mf->Draw();
   TString mf_png_save_string = "";
   if(do_pp){
     if(do_mu5) mf_png_save_string = "./matchingFactor_pp_mu5.png";
     else if(do_mu7) mf_png_save_string = "./matchingFactor_pp_mu7.png";
     else if(do_mu12) mf_png_save_string = "./matchingFactor_pp_mu12.png";
     else{}
   }
   else if(do_C2){
     if(do_mu5) mf_png_save_string = "./matchingFactor_C2_mu5.png";
     else if(do_mu7) mf_png_save_string = "./matchingFactor_C2_mu7.png";
     else if(do_mu12) mf_png_save_string = "./matchingFactor_C2_mu12.png";
     else{}
   }
   else if(do_C1){
     if(do_mu5) mf_png_save_string = "./matchingFactor_C1_mu5.png";
     else if(do_mu7) mf_png_save_string = "./matchingFactor_C1_mu7.png";
     else if(do_mu12) mf_png_save_string = "./matchingFactor_C1_mu12.png";
     else{}
   }
   else{};
   c_factor->SaveAs(mf_png_save_string);

   TString mf_file_save_string = "";
   if(do_pp){
     if(do_mu5) mf_file_save_string = "./matchingFactors/matchingFactor_pp_mu5.root";
     else if(do_mu7) mf_file_save_string = "./matchingFactors/matchingFactor_pp_mu7.root";
     else if(do_mu12) mf_file_save_string = "./matchingFactors/matchingFactor_pp_mu12.root";
     else{}
   }
   else if(do_C2){
     if(do_mu5) mf_file_save_string = "./matchingFactors/matchingFactor_C2_mu5.root";
     else if(do_mu7) mf_file_save_string = "./matchingFactors/matchingFactor_C2_mu7.root";
     else if(do_mu12) mf_file_save_string = "./matchingFactors/matchingFactor_C2_mu12.root";
     else{}
   }
   else if(do_C1){
     if(do_mu5) mf_file_save_string = "./matchingFactors/matchingFactor_C1_mu5.root";
     else if(do_mu7) mf_file_save_string = "./matchingFactors/matchingFactor_C1_mu7.root";
     else if(do_mu12) mf_file_save_string = "./matchingFactors/matchingFactor_C1_mu12.root";
     else{}
   }
   else{};

   
   auto wf_mf = TFile::Open(mf_file_save_string,"recreate");
   mf->Write();
   wf_mf->Close();

   int nbins = mf->GetNbinsX();
   for(int ibin = 0; ibin < nbins; ibin++){
     mf->SetBinError(ibin,0.);
   }
   b_trig->Divide(mf);
   TH1D *r_corr = (TH1D*) b_trig->Clone("r_corr");
   r_corr->Divide(b_trig,b_inclReco,1,1,"B");


   TCanvas* c_frac = new TCanvas("c_frac", "c_frac", 700,700);
   c_frac->cd();
   r_corr->SetTitle("");
   r_corr->GetYaxis()->SetTitle("Corrected(b) / truth(b)");
   r_corr->GetXaxis()->SetTitle("Jet #font[52]{p}_{T} [GeV]");
   r_corr->SetStats(0);
   r_corr->GetYaxis()->SetRangeUser(0,30);
   r_corr->SetTitle("#font[52]{b} amplifier");
   r_corr->Draw();
   c_frac->SaveAs("./corr.png");

   // b-amplifier file
   TString ba_file_save_string = "";
   if(do_pp){
     if(do_mu5) ba_file_save_string = "./b_amplifiers/ba_pp_mu5.root";
     else if(do_mu7) ba_file_save_string = "./b_amplifiers/ba_pp_mu7.root";
     else if(do_mu12) ba_file_save_string = "./b_amplifiers/ba_pp_mu12.root";
     else{}
   }
   else if(do_C2){
     if(do_mu5) ba_file_save_string = "./b_amplifiers/ba_C2_mu5.root";
     else if(do_mu7) ba_file_save_string = "./b_amplifiers/ba_C2_mu7.root";
     else if(do_mu12) ba_file_save_string = "./b_amplifiers/ba_C2_mu12.root";
     else{}
   }
   else if(do_C1){
     if(do_mu5) ba_file_save_string = "./b_amplifiers/ba_C1_mu5.root";
     else if(do_mu7) ba_file_save_string = "./b_amplifiers/ba_C1_mu7.root";
     else if(do_mu12) ba_file_save_string = "./b_amplifiers/ba_C1_mu12.root";
     else{}
   }
   else{};
   auto wf_ba = TFile::Open(ba_file_save_string,"recreate");
   r_corr->Write();
   wf_ba->Close();
  
}

