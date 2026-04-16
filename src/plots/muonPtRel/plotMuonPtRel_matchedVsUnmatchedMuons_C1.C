
#include "../../../headers/functions/divideByBinwidth.h"

TString getJetPtString(double jetPtLow, double jetPtHigh){

  TString result = "";

  if(jetPtLow < 100 && jetPtHigh < 100) result = Form("pTjet-%2.0fto%2.0f",jetPtLow,jetPtHigh);
  else if(jetPtLow < 100 && jetPtHigh >= 100) result = Form("pTjet-%2.0fto%3.0f",jetPtLow,jetPtHigh);
  else if(jetPtLow >= 100 && jetPtHigh >= 100) result = Form("pTjet-%3.0fto%3.0f",jetPtLow,jetPtHigh);
  else{};

  return result;


}

void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3){

  double lineWidth = 2.0;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);
  
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlue-4);
  h3->SetMarkerColor(kRed-4);


}



void plotMuonPtRel_matchedVsUnmatchedMuons_C1(double jetPtLow = 80,
					      double jetPtHigh = 500){


  TString jetPtSuffix = getJetPtString(jetPtLow,jetPtHigh);
  
  TFile *f_PH = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-30_mu12_pTmu-15to999_tight_vzReweight_hiBinReweight_hiBinShift-10_leadingXjetDumpFilter_jetTrkMaxFilter_removeHYDJETjet0p35CutOnGen_WDecayFilter_weightCut_2026-2-26.root");

  TH2D *H_incl_allJets, *H_matched_allJets, *H_unmatched_allJets;
  TH2D *H_incl_uJets, *H_matched_uJets, *H_unmatched_uJets;
  TH2D *H_incl_dJets, *H_matched_dJets, *H_unmatched_dJets;
  TH2D *H_incl_sJets, *H_matched_sJets, *H_unmatched_sJets;
  TH2D *H_incl_gJets, *H_matched_gJets, *H_unmatched_gJets;
  TH2D *H_incl_cJets, *H_matched_cJets, *H_unmatched_cJets;
  TH2D *H_incl_bJets, *H_matched_bJets, *H_unmatched_bJets;
  TH2D *H_incl_bGSJets, *H_matched_bGSJets, *H_unmatched_bGSJets;
  TH2D *H_incl_xJets, *H_matched_xJets, *H_unmatched_xJets;

  TH1D *h_incl_allJets, *h_matched_allJets, *h_unmatched_allJets;
  TH1D *h_incl_uJets, *h_matched_uJets, *h_unmatched_uJets;
  TH1D *h_incl_dJets, *h_matched_dJets, *h_unmatched_dJets;
  TH1D *h_incl_sJets, *h_matched_sJets, *h_unmatched_sJets;
  TH1D *h_incl_gJets, *h_matched_gJets, *h_unmatched_gJets;
  TH1D *h_incl_cJets, *h_matched_cJets, *h_unmatched_cJets;
  TH1D *h_incl_bJets, *h_matched_bJets, *h_unmatched_bJets;
  TH1D *h_incl_bGSJets, *h_matched_bGSJets, *h_unmatched_bGSJets;
  TH1D *h_incl_xJets, *h_matched_xJets, *h_unmatched_xJets;

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C0T0",H_incl_allJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_allJets_C0T0",H_matched_allJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_allJets_C0T0",H_unmatched_allJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C0T0",H_incl_bJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_bJets_C0T0",H_matched_bJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_bJets_C0T0",H_unmatched_bJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bGSJets_C0T0",H_incl_bGSJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_bGSJets_C0T0",H_matched_bGSJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_bGSJets_C0T0",H_unmatched_bGSJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_uJets_C0T0",H_incl_uJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_uJets_C0T0",H_matched_uJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_uJets_C0T0",H_unmatched_uJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_dJets_C0T0",H_incl_dJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_dJets_C0T0",H_matched_dJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_dJets_C0T0",H_unmatched_dJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_sJets_C0T0",H_incl_sJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_sJets_C0T0",H_matched_sJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_sJets_C0T0",H_unmatched_sJets);

  f_PH->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_gJets_C0T0",H_incl_gJets);
  f_PH->GetObject("h_muptrel_recoJetPt_matchedRecoMuonTag_triggerOn_gJets_C0T0",H_matched_gJets);
  f_PH->GetObject("h_muptrel_recoJetPt_unmatchedRecoMuonTag_triggerOn_gJets_C0T0",H_unmatched_gJets);


  TH1D *binFinder = (TH1D*) H_incl_allJets->ProjectionY("binFinder");
  double ss = 0.01;
  
  h_incl_allJets = (TH1D*) H_incl_allJets->ProjectionX("h_incl_allJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_allJets = (TH1D*) H_matched_allJets->ProjectionX("h_matched_allJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_allJets = (TH1D*) H_unmatched_allJets->ProjectionX("h_unmatched_allJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_bJets = (TH1D*) H_incl_bJets->ProjectionX("h_incl_bJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_bJets = (TH1D*) H_matched_bJets->ProjectionX("h_matched_bJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_bJets = (TH1D*) H_unmatched_bJets->ProjectionX("h_unmatched_bJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_bGSJets = (TH1D*) H_incl_bGSJets->ProjectionX("h_incl_bGSJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_bGSJets = (TH1D*) H_matched_bGSJets->ProjectionX("h_matched_bGSJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_bGSJets = (TH1D*) H_unmatched_bGSJets->ProjectionX("h_unmatched_bGSJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_uJets = (TH1D*) H_incl_uJets->ProjectionX("h_incl_uJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_uJets = (TH1D*) H_matched_uJets->ProjectionX("h_matched_uJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_uJets = (TH1D*) H_unmatched_uJets->ProjectionX("h_unmatched_uJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_dJets = (TH1D*) H_incl_dJets->ProjectionX("h_incl_dJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_dJets = (TH1D*) H_matched_dJets->ProjectionX("h_matched_dJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_dJets = (TH1D*) H_unmatched_dJets->ProjectionX("h_unmatched_dJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_sJets = (TH1D*) H_incl_sJets->ProjectionX("h_incl_sJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_sJets = (TH1D*) H_matched_sJets->ProjectionX("h_matched_sJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_sJets = (TH1D*) H_unmatched_sJets->ProjectionX("h_unmatched_sJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  h_incl_gJets = (TH1D*) H_incl_gJets->ProjectionX("h_incl_gJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_matched_gJets = (TH1D*) H_matched_gJets->ProjectionX("h_matched_gJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));
  h_unmatched_gJets = (TH1D*) H_unmatched_gJets->ProjectionX("h_unmatched_gJets",binFinder->FindBin(jetPtLow+ss),binFinder->FindBin(jetPtHigh - ss));

  /// merge b and bGS
  h_incl_bJets->Add(h_incl_bGSJets);
  h_matched_bJets->Add(h_matched_bGSJets); 
  h_unmatched_bJets->Add(h_unmatched_bGSJets);

  //// merge udsg
  h_incl_uJets->Add(h_incl_dJets);
  h_incl_uJets->Add(h_incl_sJets);
  h_incl_uJets->Add(h_incl_gJets);
  h_matched_uJets->Add(h_matched_dJets);
  h_matched_uJets->Add(h_matched_sJets);
  h_matched_uJets->Add(h_matched_gJets);
  h_unmatched_uJets->Add(h_unmatched_dJets);
  h_unmatched_uJets->Add(h_unmatched_sJets);
  h_unmatched_uJets->Add(h_unmatched_gJets);
  
  stylizeHistograms(h_incl_allJets,h_matched_allJets,h_unmatched_allJets);
  stylizeHistograms(h_incl_bJets,h_matched_bJets,h_unmatched_bJets);
  stylizeHistograms(h_incl_uJets,h_matched_uJets,h_unmatched_uJets);

  const int Nedge = 8;
  double newAxis[Nedge] = {0,0.3,0.6,1,1.5,2.0,3.0,5.0};
  h_incl_uJets = (TH1D*) h_incl_uJets->Rebin(Nedge-1,"h_incl_uJets",newAxis);
  h_matched_uJets = (TH1D*) h_matched_uJets->Rebin(Nedge-1,"h_matched_uJets",newAxis);
  h_unmatched_uJets = (TH1D*) h_unmatched_uJets->Rebin(Nedge-1,"h_unmatched_uJets",newAxis);

  divideByBinwidth(h_incl_uJets);
  divideByBinwidth(h_matched_uJets);
  divideByBinwidth(h_unmatched_uJets);

  
  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  double titleSize = 0.05;
  double xTitleSize = 0.043;
  double xLabelSize = 0.038;
  double yTitleSize = 0.043;
  double yLabelSize = 0.038;

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.038);

  TLine *li = new TLine();
  li->SetLineStyle(7);

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_allJets = new TCanvas("canv_allJets","canv_allJets",700,700);
  canv_allJets->cd();
  TPad *pad_allJets = new TPad("pad_allJets","pad_allJets",0,0,1,1);
  pad_allJets->SetLeftMargin(leftMargin);
  pad_allJets->SetBottomMargin(bottomMargin);
  pad_allJets->Draw();
  pad_allJets->cd();
  h_incl_allJets->SetStats(0);
  h_incl_allJets->SetTitleSize(titleSize);
  h_incl_allJets->SetTitle("PYTHIA+HYDJET 0-80%, all jets");
  h_incl_allJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_incl_allJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_incl_allJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_incl_allJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_incl_allJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_incl_allJets->GetYaxis()->SetTitle("a.u.");
  h_incl_allJets->Draw();
  h_matched_allJets->Draw("same");
  h_unmatched_allJets->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f, |#it{#eta}^{jet}| < 1.6",jetPtLow,jetPtHigh));
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,Form("Matched muons (%3.1f %%)",100.*h_matched_allJets->Integral()/h_incl_allJets->Integral()));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,Form("Unmatched muons (%3.1f %%)",100.*h_unmatched_allJets->Integral()/h_incl_allJets->Integral()));
  canv_allJets->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRel_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_allJets_%s.pdf",jetPtSuffix.Data()));


  TCanvas *canv_allJetsShape = new TCanvas("canv_allJetsShape","canv_allJetsShape",700,700);
  canv_allJetsShape->cd();
  TPad *pad_allJetsShape = new TPad("pad_allJetsShape","pad_allJetsShape",0,0,1,1);
  pad_allJetsShape->SetLeftMargin(leftMargin);
  pad_allJetsShape->SetBottomMargin(bottomMargin);
  pad_allJetsShape->Draw();
  pad_allJetsShape->cd();
  h_matched_allJets->Scale(1./h_matched_allJets->Integral());
  h_unmatched_allJets->Scale(1./h_unmatched_allJets->Integral());
  h_matched_allJets->SetStats(0);
  h_matched_allJets->SetTitleSize(titleSize);
  h_matched_allJets->SetTitle("PYTHIA+HYDJET 0-80%, all jets");
  h_matched_allJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_matched_allJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_matched_allJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_matched_allJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_matched_allJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_matched_allJets->GetYaxis()->SetTitle("a.u.");
  h_matched_allJets->GetYaxis()->SetRangeUser(0,0.15);
  h_matched_allJets->Draw();
  h_unmatched_allJets->Draw("same");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,"Matched muons");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,"Unmatched muons");
  canv_allJetsShape->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRelShape_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_allJets_%s.pdf",jetPtSuffix.Data()));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_bJets = new TCanvas("canv_bJets","canv_bJets",700,700);
  canv_bJets->cd();
  TPad *pad_bJets = new TPad("pad_bJets","pad_bJets",0,0,1,1);
  pad_bJets->SetLeftMargin(leftMargin);
  pad_bJets->SetBottomMargin(bottomMargin);
  pad_bJets->Draw();
  pad_bJets->cd();
  h_incl_bJets->SetStats(0);
  h_incl_bJets->SetTitleSize(titleSize);
  h_incl_bJets->SetTitle("PYTHIA+HYDJET 0-80%, #it{b}-jets");
  h_incl_bJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_incl_bJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_incl_bJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_incl_bJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_incl_bJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_incl_bJets->GetYaxis()->SetTitle("a.u.");
  h_incl_bJets->Draw();
  h_matched_bJets->Draw("same");
  h_unmatched_bJets->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f, |#it{#eta}^{jet}| < 1.6",jetPtLow,jetPtHigh));
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,Form("Matched muons (%3.1f %%)",100.*h_matched_bJets->Integral()/h_incl_bJets->Integral()));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,Form("Unmatched muons (%3.1f %%)",100.*h_unmatched_bJets->Integral()/h_incl_bJets->Integral()));
  canv_bJets->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRel_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_bJets_%s.pdf",jetPtSuffix.Data()));


  TCanvas *canv_bJetsShape = new TCanvas("canv_bJetsShape","canv_bJetsShape",700,700);
  canv_bJetsShape->cd();
  TPad *pad_bJetsShape = new TPad("pad_bJetsShape","pad_bJetsShape",0,0,1,1);
  pad_bJetsShape->SetLeftMargin(leftMargin);
  pad_bJetsShape->SetBottomMargin(bottomMargin);
  pad_bJetsShape->Draw();
  pad_bJetsShape->cd();
  h_matched_bJets->Scale(1./h_matched_bJets->Integral());
  h_unmatched_bJets->Scale(1./h_unmatched_bJets->Integral());
  h_matched_bJets->SetStats(0);
  h_matched_bJets->SetTitleSize(titleSize);
  h_matched_bJets->SetTitle("PYTHIA+HYDJET 0-80%, #it{b}-jets");
  h_matched_bJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_matched_bJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_matched_bJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_matched_bJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_matched_bJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_matched_bJets->GetYaxis()->SetTitle("a.u.");
  h_matched_bJets->GetYaxis()->SetRangeUser(0,0.15);
  h_matched_bJets->Draw();
  h_unmatched_bJets->Draw("same");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,"Matched muons");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,"Unmatched muons");
  canv_bJetsShape->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRelShape_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_bJets_%s.pdf",jetPtSuffix.Data()));

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TCanvas *canv_uJets = new TCanvas("canv_uJets","canv_uJets",700,700);
  canv_uJets->cd();
  TPad *pad_uJets = new TPad("pad_uJets","pad_uJets",0,0,1,1);
  pad_uJets->SetLeftMargin(leftMargin);
  pad_uJets->SetBottomMargin(bottomMargin);
  pad_uJets->Draw();
  pad_uJets->cd();
  h_incl_uJets->SetStats(0);
  h_incl_uJets->SetTitleSize(titleSize);
  h_incl_uJets->SetTitle("PYTHIA+HYDJET 0-80%, #it{udsg}-jets");
  h_incl_uJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_incl_uJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_incl_uJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_incl_uJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_incl_uJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_incl_uJets->GetYaxis()->SetTitle("a.u.");
  h_incl_uJets->Draw();
  h_matched_uJets->Draw("same");
  h_unmatched_uJets->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.4,0.8,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f, |#it{#eta}^{jet}| < 1.6",jetPtLow,jetPtHigh));
  la->DrawLatexNDC(0.4,0.72,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,Form("Matched muons (%3.1f %%)",100.*h_matched_uJets->Integral()/h_incl_uJets->Integral()));
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,Form("Unmatched muons (%3.1f %%)",100.*h_unmatched_uJets->Integral()/h_incl_uJets->Integral()));
  canv_uJets->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRel_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_udsgJets_%s.pdf",jetPtSuffix.Data()));


  TCanvas *canv_uJetsShape = new TCanvas("canv_uJetsShape","canv_uJetsShape",700,700);
  canv_uJetsShape->cd();
  TPad *pad_uJetsShape = new TPad("pad_uJetsShape","pad_uJetsShape",0,0,1,1);
  pad_uJetsShape->SetLeftMargin(leftMargin);
  pad_uJetsShape->SetBottomMargin(bottomMargin);
  pad_uJetsShape->Draw();
  pad_uJetsShape->cd();
  h_matched_uJets->Scale(1./h_matched_uJets->Integral());
  h_unmatched_uJets->Scale(1./h_unmatched_uJets->Integral());
  h_matched_uJets->SetStats(0);
  h_matched_uJets->SetTitleSize(titleSize);
  h_matched_uJets->SetTitle("PYTHIA+HYDJET 0-80%, #it{udsg}-jets");
  h_matched_uJets->GetXaxis()->SetTitleSize(xTitleSize);
  h_matched_uJets->GetXaxis()->SetLabelSize(xLabelSize);
  h_matched_uJets->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_matched_uJets->GetYaxis()->SetTitleSize(yTitleSize);
  h_matched_uJets->GetYaxis()->SetLabelSize(yLabelSize);
  h_matched_uJets->GetYaxis()->SetTitle("a.u.");
  h_matched_uJets->GetYaxis()->SetRangeUser(0,0.85);
  h_matched_uJets->Draw();
  h_unmatched_uJets->Draw("same");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.64,"Matched muons");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.4,0.56,"Unmatched muons");
  canv_uJetsShape->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRelShape_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_udsgJets_%s.pdf",jetPtSuffix.Data()));


  TH1D *h_uJetsShapeRatio = (TH1D*) h_matched_uJets->Clone("h_uJetsShapeRatio");
  h_uJetsShapeRatio->Divide(h_matched_uJets,h_unmatched_uJets,1,1,"");
  
  TCanvas *canv_uJetsShapeRatio = new TCanvas("canv_uJetsShapeRatio","canv_uJetsShapeRatio",700,700);
  canv_uJetsShapeRatio->cd();
  TPad *pad_uJetsShapeRatio = new TPad("pad_uJetsShapeRatio","pad_uJetsShapeRatio",0,0,1,1);
  pad_uJetsShapeRatio->SetLeftMargin(leftMargin);
  pad_uJetsShapeRatio->SetBottomMargin(bottomMargin);
  pad_uJetsShapeRatio->Draw();
  pad_uJetsShapeRatio->cd();
  h_uJetsShapeRatio->SetStats(0);
  h_uJetsShapeRatio->SetTitleSize(titleSize);
  h_uJetsShapeRatio->SetTitle("PYTHIA+HYDJET 0-80%, #it{udsg}-jets");
  h_uJetsShapeRatio->GetXaxis()->SetTitleSize(xTitleSize);
  h_uJetsShapeRatio->GetXaxis()->SetLabelSize(xLabelSize);
  h_uJetsShapeRatio->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  h_uJetsShapeRatio->GetYaxis()->SetTitleSize(yTitleSize);
  h_uJetsShapeRatio->GetYaxis()->SetLabelSize(yLabelSize);
  h_uJetsShapeRatio->GetYaxis()->SetTitle("Matched / Unmatched");
  h_uJetsShapeRatio->GetYaxis()->SetRangeUser(0,4);
  h_uJetsShapeRatio->Draw();
  li->DrawLine(newAxis[0],1,newAxis[Nedge-1],1);
  canv_uJetsShapeRatio->SaveAs(Form("../../../figures/muonPtRel/matchedVsUnmatchedMuons/muonPtRelShapeRatio_matchedVsUnmatchedMuons_PYTHIAHYDJET_C1_udsgJets_%s.pdf",jetPtSuffix.Data()));


}
