
#include "../../../headers/goldenFileNames.h"

void tagging_sequence(bool do_pp = 0,
		      bool do_C2 = 0,
		      bool do_C1 = 1,
		      bool do_mu5 = 0,
		      bool do_mu7 = 0,
		      bool do_mu12 = 1){

  const int N_axis_edges = 6;
  double new_axis[N_axis_edges] = {80,90,100,120,150,200};

  

  TLine *li = new TLine();
  li->SetLineStyle(7);

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.06);


  TString input_PYTHIA, input_PYTHIA_EnergyShift, input_PYTHIA_prime, input_PYTHIA_inclJets, input_PYTHIA_inclJets_ResolutionSmear;
  TString input_pp_SingleMuon;
  TString input_pp_MinBias;
  TString input_PYTHIAHYDJET, input_PYTHIAHYDJET_inclJets, input_PYTHIAHYDJET_inclJets_ResolutionSmear;
  TString input_PbPb_SingleMuon;
  TString input_PbPb_MinBias;
  TString input_PbPb_DiJet;

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

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu12_newJetBins;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu12_newJetBins;
    input_pp_MinBias   = goldenFile_pp_MinBias_mu12_newJetBins;
    input_PbPb_MinBias = goldenFile_PbPb_MinBias_mu12_newJetBins;
    input_PbPb_DiJet = goldenFile_PbPb_HardProbes_mu12_newJetBins;
    input_PYTHIA = goldenFile_PYTHIA_mu12_pThat15_newJetBins;
    input_PYTHIA_prime = goldenFile_PYTHIA_mu12_response_pThat15;
    input_PYTHIA_EnergyShift = goldenFile_PYTHIA_mu12_response_pThat15_EnergyShift;
    input_PYTHIA_inclJets = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets.root";
    input_PYTHIA_inclJets_ResolutionSmear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_doJERCorrection.root";
    input_PYTHIAHYDJET = goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins;
    input_PYTHIAHYDJET_inclJets = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response.root";
    input_PYTHIAHYDJET_inclJets_ResolutionSmear = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PH_DiJet_pTjet-5_pThat-15_response_doJERCorrection.root";

  }
  else{};
  

  TFile *f_py , *f_pyp, *f_mb, *f_sm, *f_pyE, *f_pyi, *f_pyr, *f_phi, *f_phr, *f_dj;

  if(do_pp){
    f_py = TFile::Open(input_PYTHIA);
    f_pyp = TFile::Open(input_PYTHIA_prime);
    f_pyE = TFile::Open(input_PYTHIA_EnergyShift);
    f_pyi = TFile::Open(input_PYTHIA_inclJets);
    f_pyr = TFile::Open(input_PYTHIA_inclJets_ResolutionSmear);
    f_phi = TFile::Open(input_PYTHIAHYDJET_inclJets);
    f_phr = TFile::Open(input_PYTHIAHYDJET_inclJets_ResolutionSmear);
    f_mb = TFile::Open(input_pp_MinBias);
    f_sm = TFile::Open(input_pp_SingleMuon);
  }
  else if(do_C1 || do_C2){
    f_py = TFile::Open(input_PYTHIAHYDJET);
    f_pyp = TFile::Open(input_PYTHIA_prime);
    f_pyE = TFile::Open(input_PYTHIA_EnergyShift);
    f_pyi = TFile::Open(input_PYTHIA_inclJets);
    f_phi = TFile::Open(input_PYTHIAHYDJET_inclJets);
    f_phr = TFile::Open(input_PYTHIAHYDJET_inclJets_ResolutionSmear);
    f_pyr = TFile::Open(input_PYTHIA_inclJets_ResolutionSmear);
    f_mb = TFile::Open(input_PbPb_MinBias);
    f_sm = TFile::Open(input_PbPb_SingleMuon);
    f_dj = TFile::Open(input_PbPb_DiJet);
  }
  else{};

  
  // MC histograms
  TH2D *H_inclGen, *H_inclReco, *H_inclMuTag, *H_genMuTag, *H_matchedRecoMuTag, *H_trig, *H_trigp, *H_shift, *H_i, *H_r;  // 2D histograms
  TH1D *h_inclGen, *h_inclReco, *h_inclMuTag, *h_genMuTag, *h_matchedRecoMuTag, *h_trig, *h_trigp, *h_shift, *h_i, *h_r;  // all flavors
  TH1D *b_inclGen, *b_inclReco, *b_inclMuTag, *b_genMuTag, *b_matchedRecoMuTag, *b_trig, *b_trigp, *b_shift;  // b jets
  TH1D *bb_inclGen, *bb_inclReco, *bb_inclMuTag, *bb_genMuTag, *bb_matchedRecoMuTag, *bb_trig, *bb_trigp, *bb_shift;  // b-bar jets
  TH1D *bGS_inclGen, *bGS_inclReco, *bGS_inclMuTag, *bGS_genMuTag, *bGS_matchedRecoMuTag, *bGS_trig, *bGS_trigp, *bGS_shift;  // b-GS jets

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
  f_pyp->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_trigp);
  f_pyE->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_shift);
  if(do_pp){
    f_pyi->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_i);
    f_pyr->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_r);
  }
  else{
    // f_phi->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",centrality_identifier.c_str()),H_i);
    // f_phr->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",centrality_identifier.c_str()),H_r);
    f_pyi->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_i);
    f_pyr->GetObject(Form("h_matchedRecoJetPt_genJetPt_bJets%s",""),H_r);
  }

  //f_pyp->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor%s",""),H_trigp);
  //f_pyE->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor%s",""),H_shift);

  // data histograms
  TH1D *d_inclReco, *d_inclMuTag, *dd_inclMuTag, *d_trig;


  f_dj->GetObject(Form("h_inclRecoJetPt%s",centrality_identifier.c_str()),d_inclReco);
  f_dj->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag%s",centrality_identifier.c_str()),d_inclMuTag);
  
  f_sm->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag%s",centrality_identifier.c_str()),dd_inclMuTag);
  f_sm->GetObject(Form("h_inclRecoJetPt_inclRecoMuonTag_triggerOn%s",centrality_identifier.c_str()),d_trig);

  
  h_inclGen = H_inclGen->ProjectionX("h_inclGen");
  h_inclReco = H_inclReco->ProjectionX("h_inclReco");
  h_inclMuTag = H_inclMuTag->ProjectionX("h_inclMuTag");
  h_genMuTag = H_genMuTag->ProjectionX("h_genMuTag");
  h_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("h_matchedRecoMuTag");
  h_trig = H_trig->ProjectionX("h_trig");
  h_trigp = H_trigp->ProjectionX("h_trigp");
  h_shift = H_shift->ProjectionX("h_shift");
  h_i = H_i->ProjectionX("h_i");
  h_r = H_r->ProjectionX("h_r");


  // NEW REBINNING SCHEME
  h_inclGen = (TH1D*) h_inclGen->Rebin(N_axis_edges-1,"h_inclGen",new_axis);
  h_inclReco = (TH1D*) h_inclReco->Rebin(N_axis_edges-1,"h_inclReco",new_axis);
  h_inclMuTag = (TH1D*) h_inclMuTag->Rebin(N_axis_edges-1,"h_inclMuTag",new_axis);
  h_genMuTag = (TH1D*) h_genMuTag->Rebin(N_axis_edges-1,"h_genMuTag",new_axis);
  h_matchedRecoMuTag = (TH1D*) h_matchedRecoMuTag->Rebin(N_axis_edges-1,"h_matchedRecoMuTag",new_axis);
  h_trig = (TH1D*) h_trig->Rebin(N_axis_edges-1,"h_trig",new_axis);
  h_shift = (TH1D*) h_shift->Rebin(N_axis_edges-1,"h_shift",new_axis);
  h_i = (TH1D*) h_i->Rebin(N_axis_edges-1,"h_i",new_axis);
  h_r = (TH1D*) h_r->Rebin(N_axis_edges-1,"h_r",new_axis);
  d_inclReco = (TH1D*) d_inclReco->Rebin(N_axis_edges-1,"d_inclReco",new_axis);
  d_inclMuTag = (TH1D*) d_inclMuTag->Rebin(N_axis_edges-1,"d_inclMuTag",new_axis);
  dd_inclMuTag = (TH1D*) dd_inclMuTag->Rebin(N_axis_edges-1,"dd_inclMuTag",new_axis);
  d_trig = (TH1D*) d_trig->Rebin(N_axis_edges-1,"d_trig",new_axis);
  

  b_inclGen = H_inclGen->ProjectionX("b_inclGen",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_inclReco = H_inclReco->ProjectionX("b_inclReco",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_inclMuTag = H_inclMuTag->ProjectionX("b_inclMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_genMuTag = H_genMuTag->ProjectionX("b_genMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("b_matchedRecoMuTag",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_trig = H_trig->ProjectionX("b_trig",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  //b_trigp = H_trigp->ProjectionX("b_trigp",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  //b_shift = H_shift->ProjectionX("b_shift",H_inclGen->ProjectionY()->FindBin(5.01),H_inclGen->ProjectionY()->FindBin(5.99));
  b_trigp = H_trigp->ProjectionX("b_trigp");
  b_shift = H_shift->ProjectionX("b_shift");

  bb_inclGen = H_inclGen->ProjectionX("bb_inclGen",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_inclReco = H_inclReco->ProjectionX("bb_inclReco",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_inclMuTag = H_inclMuTag->ProjectionX("bb_inclMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_genMuTag = H_genMuTag->ProjectionX("bb_genMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("bb_matchedRecoMuTag",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_trig = H_trig->ProjectionX("bb_trig",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  // bb_trigp = H_trigp->ProjectionX("bb_trigp",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  // bb_shift = H_shift->ProjectionX("bb_shift",H_inclGen->ProjectionY()->FindBin(-4.99),H_inclGen->ProjectionY()->FindBin(-4.01));
  bb_trigp = H_trigp->ProjectionX("bb_trigp");
  bb_shift = H_shift->ProjectionX("bb_shift");

  bGS_inclGen = H_inclGen->ProjectionX("bGS_inclGen",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_inclReco = H_inclReco->ProjectionX("bGS_inclReco",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_inclMuTag = H_inclMuTag->ProjectionX("bGS_inclMuTag",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_genMuTag = H_genMuTag->ProjectionX("bGS_genMuTag",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_matchedRecoMuTag = H_matchedRecoMuTag->ProjectionX("bGS_matchedRecoMuTag",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_trig = H_trig->ProjectionX("bGS_trig",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  // bGS_trigp = H_trigp->ProjectionX("bGS_trigp",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  // bGS_shift = H_shift->ProjectionX("bGS_shift",H_inclGen->ProjectionY()->FindBin(17.01),H_inclGen->ProjectionY()->FindBin(17.99));
  bGS_trigp = H_trigp->ProjectionX("bGS_trigp");
  bGS_shift = H_shift->ProjectionX("bGS_shift");

  b_inclGen->Add(bb_inclGen);
  b_inclReco->Add(bb_inclReco);
  b_inclMuTag->Add(bb_inclMuTag);
  b_genMuTag->Add(bb_genMuTag);
  b_matchedRecoMuTag->Add(bb_matchedRecoMuTag);
  b_trig->Add(bb_trig);
  //b_trigp->Add(bb_trigp);
  //b_shift->Add(bb_shift);

  b_inclGen->Add(bGS_inclGen);
  b_inclReco->Add(bGS_inclReco);
  b_inclMuTag->Add(bGS_inclMuTag);
  b_genMuTag->Add(bGS_genMuTag);
  b_matchedRecoMuTag->Add(bGS_matchedRecoMuTag);
  b_trig->Add(bGS_trig);
  //b_trigp->Add(bGS_trigp);
  //b_shift->Add(bGS_shift);

  // NEW REBINNING SCHEME
  b_inclGen = (TH1D*) b_inclGen->Rebin(N_axis_edges-1,"b_inclGen",new_axis);
  b_inclReco = (TH1D*) b_inclReco->Rebin(N_axis_edges-1,"b_inclReco",new_axis);
  b_inclMuTag = (TH1D*) b_inclMuTag->Rebin(N_axis_edges-1,"b_inclMuTag",new_axis);
  b_genMuTag = (TH1D*) b_genMuTag->Rebin(N_axis_edges-1,"b_genMuTag",new_axis);
  b_matchedRecoMuTag = (TH1D*) b_matchedRecoMuTag->Rebin(N_axis_edges-1,"b_matchedRecoMuTag",new_axis);
  b_trig = (TH1D*) b_trig->Rebin(N_axis_edges-1,"b_trig",new_axis);
  b_trigp = (TH1D*) b_trigp->Rebin(N_axis_edges-1,"b_trigp",new_axis);
  b_shift = (TH1D*) b_shift->Rebin(N_axis_edges-1,"b_shift",new_axis);




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

  
  

  // MC-driven corrections
  TH1D *r1, *r2, *r3, *r4, *r5, *r6, *r7;
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
  r6 = (TH1D*) b_trig->Clone("r6"); // bJet JES correction
  r6->Divide(b_shift,b_trigp,1,1,"B");
  r7 = (TH1D*) h_i->Clone("r7"); // b-to-incl JER correction
  r7->Divide(h_i,h_r,1,1,"B");

  // Data-driven corrections
  TH1D *rr1, *rr2, *rr3;
  rr1 = (TH1D*) d_inclMuTag->Clone("rr1");
  rr1->Divide(d_inclMuTag,d_inclReco,1,1,"B");
  rr2 = (TH1D*) d_trig->Clone("rr2");
  rr2->Divide(d_trig,dd_inclMuTag,1,1,"B");

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
  //la->DrawLatexNDC(0.25,0.12,"HLT_HIL3Mu7_NHitQ10");
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
  //la->DrawLatexNDC(0.25,0.28,"#hat{#font[52]{p}}_{T} > 30 GeV");
  if(do_mu7) la->DrawLatexNDC(0.25,0.2,"9 < #font[52]{p}_{T}^{#mu} < 14 GeV");
  if(do_mu12) la->DrawLatexNDC(0.25,0.2,"#font[52]{p}_{T}^{#mu} > 14 GeV");
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
  r2->GetYaxis()->SetRangeUser(0.0,4.0);
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



   // matching factor calculation
   TH1D *mf; // mf = matching factor
   TH1D *mf_1, *mf_2, *mf_3, *mf_4; // mf_i = i-th sub-factor


   // MC-driven
   mf = (TH1D*) r2->Clone("mf");
   mf_1 = (TH1D*) mf->Clone("mf_1"); // first sub-factor
   mf->Multiply(mf,r3,1,1,"B"); // muon reconstruction eff in MC
   mf_2 = (TH1D*) mf->Clone("mf_2"); // sub-factor
   mf->Multiply(mf,r4,1,1,"B"); // enhancement from GEANT muons
   mf_3 = (TH1D*) mf->Clone("mf_3"); // sub-factor
   //mf->Multiply(rr2); // trigger eff in DATA
   //mf->Scale(3.0); // account for prescale
   mf->Multiply(mf,r5,1,1,"B"); // trigger eff in MC
   mf_4 = (TH1D*) mf->Clone("mf_4"); // sub-factor
   mf->Multiply(mf,r6,1,1,"B"); // bJet JES correction
   mf->Multiply(mf,r7,1,1,"B"); // mu-tagged bJet JER correction

   // Data-driven
   // mf = (TH1D*) rr1->Clone("mf"); 
   // mf->Multiply(rr2); // trigger eff in DATA      
   // mf->Multiply(mf,r6,1,1,"B"); // bJet JES correction
   // mf->Multiply(mf,r7,1,1,"B"); // mu-tagged bJet JER correction


   TCanvas *c_factor = new TCanvas("c_factor", "c_factor", 700,700);
   c_factor->cd();
   TPad *p_mf = new TPad("p_mf","p_mf",0,0,1,1);
   p_mf->SetLeftMargin(0.2);
   p_mf->SetBottomMargin(0.2);
   p_mf->Draw();
   p_mf->cd();
   mf->GetYaxis()->SetLabelSize(0.04);
   mf->GetXaxis()->SetLabelSize(0.04);
   mf->GetXaxis()->SetTitleSize(0.05);
   mf->GetYaxis()->SetTitleSize(0.05);
   mf->GetYaxis()->SetTitle("Jet selection factor, #alpha");
   mf->GetYaxis()->SetRangeUser(0,0.01);
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
   r1->Write();
   r2->Write();
   r3->Write();
   r4->Write();
   r5->Write();
   r6->Write();
   r7->Write();
   wf_mf->Close();

   

   int nbins = mf->GetNbinsX();
   // for(int ibin = 0; ibin < nbins; ibin++){
   //   mf->SetBinError(ibin,0.);
   // }

   // make b-amplifier plot
   TH1D *b_trig_clone = (TH1D*) b_trig->Clone("b_trig_clone");
   b_trig->Divide(mf);
   TH1D *r_corr = (TH1D*) b_trig->Clone("r_corr");
   //r_corr->Divide(b_trig,b_inclReco,1,1,"B");
   r_corr->Divide(b_inclReco);



   // make sub-amplifiers for closure checks
   // b_genMuTag->Divide(mf_1);
   // TH1D *r_corr_1 = (TH1D*) b_genMuTag->Clone("r_corr_1");
   // r_corr_1->Divide(b_genMuTag,b_inclReco,1,1,"B");

   // b_matchedRecoMuTag->Divide(mf_2);
   // TH1D *r_corr_2 = (TH1D*) b_matchedRecoMuTag->Clone("r_corr_2");
   // r_corr_2->Divide(b_matchedRecoMuTag,b_genMuTag,1,1,"B");

   // b_inclMuTag->Divide(mf_3);
   // TH1D *r_corr_3 = (TH1D*) b_inclMuTag->Clone("r_corr_3");
   // r_corr_3->Divide(b_inclMuTag,b_matchedRecoMuTag,1,1,"B");

   // b_trig_clone->Divide(mf_4);
   // TH1D *r_corr_4 = (TH1D*) b_trig_clone->Clone("r_corr_4");
   // r_corr_4->Divide(b_trig_clone,b_inclMuTag,1,1,"B");

   // TH1D *cursed_histo = (TH1D*) r_corr_1->Clone("cursed_histo");
   // cursed_histo->Divide(r_corr_1,r_corr_2,1,1,"B");

   
   // make closure plot
   // h_trig->Divide(mf);
   // TH1D *r_corr = (TH1D*) h_trig->Clone("r_corr");
   // r_corr->Divide(h_trig,h_inclReco,1,1,"B");
   

   TCanvas* c_frac = new TCanvas("c_frac", "c_frac", 700,700);
   c_frac->cd();
   r_corr->SetTitle("");
   r_corr->GetYaxis()->SetTitle("Corrected(b) / truth(b)");
   //r_corr->GetYaxis()->SetTitle("Corrected(all) / truth(all)");
   r_corr->GetXaxis()->SetTitle("Jet #font[52]{p}_{T} [GeV]");
   r_corr->SetStats(0);
   r_corr->GetYaxis()->SetRangeUser(0,20);
   r_corr->GetYaxis()->SetTitle("#font[52]{b}-amplification factor, #beta");
   r_corr->Draw();
   //r_corr_1->Draw();
   //r_corr_2->Draw();
   //r_corr_3->Draw();
   //r_corr_4->Draw();

   c_frac->SaveAs("./corr.png");

   // b-amplifier file
   TString ba_file_save_string = "";
   // sub-amp files
   TString ba_sub_1_file_save_string = "";
   TString ba_sub_2_file_save_string = "";
   TString ba_sub_3_file_save_string = "";
   TString ba_sub_4_file_save_string = "";
   
   if(do_pp){
     if(do_mu5){
       ba_file_save_string = "./b_amplifiers/ba_pp_mu5.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_pp_mu5.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_pp_mu5.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_pp_mu5.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_pp_mu5.root";
     }
     else if(do_mu7){
       ba_file_save_string = "./b_amplifiers/ba_pp_mu7.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_pp_mu7.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_pp_mu7.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_pp_mu7.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_pp_mu7.root";
     }
     else if(do_mu12){
       ba_file_save_string = "./b_amplifiers/ba_pp_mu12_bJetNeutrinoEnergyShift.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_pp_mu12.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_pp_mu12.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_pp_mu12.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_pp_mu12.root";
     }
     else{}
   }
   else if(do_C2){
     if(do_mu5){
       ba_file_save_string = "./b_amplifiers/ba_C2_mu5.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C2_mu5.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C2_mu5.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C2_mu5.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C2_mu5.root";
     }
     else if(do_mu7){
       ba_file_save_string = "./b_amplifiers/ba_C2_mu7.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C2_mu7.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C2_mu7.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C2_mu7.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C2_mu7.root";
     }
     else if(do_mu12){
       ba_file_save_string = "./b_amplifiers/ba_C2_mu12_bJetNeutrinoEnergyShift.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C2_mu12.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C2_mu12.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C2_mu12.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C2_mu12.root";
     }
     else{}
   }
   else if(do_C1){
     if(do_mu5){
       ba_file_save_string = "./b_amplifiers/ba_C1_mu5.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C1_mu5.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C1_mu5.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C1_mu5.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C1_mu5.root";
     }
     else if(do_mu7){
       ba_file_save_string = "./b_amplifiers/ba_C1_mu7.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C1_mu7.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C1_mu7.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C1_mu7.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C1_mu7.root";
     }
     else if(do_mu12){
       ba_file_save_string = "./b_amplifiers/ba_C1_mu12_bJetNeutrinoEnergyShift.root";
       ba_sub_1_file_save_string = "./b_amplifiers/sub_amps/ba_sub_1_C1_mu12.root";
       ba_sub_2_file_save_string = "./b_amplifiers/sub_amps/ba_sub_2_C1_mu12.root";
       ba_sub_3_file_save_string = "./b_amplifiers/sub_amps/ba_sub_3_C1_mu12.root";
       ba_sub_4_file_save_string = "./b_amplifiers/sub_amps/ba_sub_4_C1_mu12.root";
     }
     else{}
   }
   else{};

   auto wf_ba = TFile::Open(ba_file_save_string,"recreate");
   r_corr->Write();
   wf_ba->Close();

   // auto wf_ba_sub_1 = TFile::Open(ba_sub_1_file_save_string,"recreate");
   // r_corr_1->Write();
   // wf_ba_sub_1->Close();

   // auto wf_ba_sub_2 = TFile::Open(ba_sub_2_file_save_string,"recreate");
   // r_corr_2->Write();
   // wf_ba_sub_2->Close();

   // auto wf_ba_sub_3 = TFile::Open(ba_sub_3_file_save_string,"recreate");
   // r_corr_3->Write();
   // wf_ba_sub_3->Close();

   // auto wf_ba_sub_4 = TFile::Open(ba_sub_4_file_save_string,"recreate");
   // r_corr_4->Write();
   // wf_ba_sub_4->Close();



}

