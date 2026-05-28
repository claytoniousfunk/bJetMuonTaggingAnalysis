
#include "plotMuonPtRel_dRReweightEffect.h"

void stylize_raw(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  
  h0->SetLineColor(kBlack);
  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);
  h4->SetLineColor(kMagenta-9);
  
  h0->SetMarkerColor(kBlack);
  h1->SetMarkerColor(kBlue-4);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kGreen+2);
  h4->SetMarkerColor(kMagenta-9);
  
  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  
  h0->SetMarkerStyle(20);
  h1->SetMarkerStyle(21);
  h2->SetMarkerStyle(33);
  h3->SetMarkerStyle(34);
  h4->SetMarkerStyle(47);
  
  h0->SetStats(0);
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
    
  h0->SetTitle("");
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");
  
  double yTitleOffset = 0.3;
  h0->GetYaxis()->SetTitleOffset(yTitleOffset);
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);
  h4->GetYaxis()->SetTitleOffset(yTitleOffset);
  
  int yNDivisions = 404;
  h0->GetYaxis()->SetNdivisions(yNDivisions);
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);
  h4->GetYaxis()->SetNdivisions(yNDivisions);
  
}


void stylize_weighted(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4){

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());

  h0->SetLineColor(kBlack);
  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);
  h4->SetLineColor(kMagenta-9);

  h0->SetMarkerColor(kBlack);
  h1->SetMarkerColor(kBlue-4);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kGreen+2);
  h4->SetMarkerColor(kMagenta-9);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);

  h0->SetMarkerStyle(24);
  h1->SetMarkerStyle(25);
  h2->SetMarkerStyle(27);
  h3->SetMarkerStyle(28);
  h4->SetMarkerStyle(46);

  h0->SetStats(0);
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  
  h0->SetTitle("");
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");

  double yTitleOffset = 0.3;
  h0->GetYaxis()->SetTitleOffset(yTitleOffset);
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);
  h4->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h0->GetYaxis()->SetNdivisions(yNDivisions);
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);
  h4->GetYaxis()->SetNdivisions(yNDivisions);

}


TString getJetPtString(double low, double high){
  TString result = "";
  result = Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",low,high);
  return result;
}

void set_pTrel_range(TH1D *h1){

  double lowerLimit = 0.0;
  double upperLimit = 5.0;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void plotMuonPtRel_dRReweightEffect(double jetPt_low = 80.,
				    double jetPt_high = 100.){

  CMSString = "#font[62]{CMS}  #font[52]{Preliminary}";
  energyString = "#sqrt{#it{s}} = 5.02 TeV";
  jetPtString = getJetPtString(jetPt_low,jetPt_high);
  hadronPtString = "#it{p}_{T}^{h} > 14 GeV, |#it{#eta}^{h}| < 2.0";

  li = new TLine();
  la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);

   file_pp_mc_raw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-7-8.root");
   file_pp_mc_weighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_dRReweight_2025-7-8.root");

   file_PbPb_mc_raw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-6-2.root");
   file_PbPb_mc_weighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_dRReweight_2025-7-18.root");

   if(!file_pp_mc_raw || !file_pp_mc_weighted || !file_PbPb_mc_raw || !file_PbPb_mc_weighted){
     std::cout << "error finding file! exiting\n";
     return;
   }

   file_pp_mc_raw->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_T0",H_pTrel_pp_mc_raw);
   file_pp_mc_weighted->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_T0",H_pTrel_pp_mc_weighted);

   file_PbPb_mc_raw->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H_pTrel_C4_mc_raw);
   file_PbPb_mc_weighted->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H_pTrel_C4_mc_weighted);

   file_PbPb_mc_raw->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H_pTrel_C3_mc_raw);
   file_PbPb_mc_weighted->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H_pTrel_C3_mc_weighted);

   file_PbPb_mc_raw->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H_pTrel_C2_mc_raw);
   file_PbPb_mc_weighted->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H_pTrel_C2_mc_weighted);

   file_PbPb_mc_raw->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_pTrel_C1_mc_raw);
   file_PbPb_mc_weighted->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H_pTrel_C1_mc_weighted);

   // projections
   binFinder = (TH1D*) H_pTrel_pp_mc_raw->ProjectionY("binFinder");
   smallShift = 0.01;
   
   h_pTrel_pp_mc_raw = (TH1D*) H_pTrel_pp_mc_raw->ProjectionX("h_pTrel_pp_mc_raw",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C4_mc_raw = (TH1D*) H_pTrel_C4_mc_raw->ProjectionX("h_pTrel_C4_mc_raw",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C3_mc_raw = (TH1D*) H_pTrel_C3_mc_raw->ProjectionX("h_pTrel_C3_mc_raw",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C2_mc_raw = (TH1D*) H_pTrel_C2_mc_raw->ProjectionX("h_pTrel_C2_mc_raw",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C1_mc_raw = (TH1D*) H_pTrel_C1_mc_raw->ProjectionX("h_pTrel_C1_mc_raw",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));

   h_pTrel_pp_mc_weighted = (TH1D*) H_pTrel_pp_mc_weighted->ProjectionX("h_pTrel_pp_mc_weighted",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C4_mc_weighted = (TH1D*) H_pTrel_C4_mc_weighted->ProjectionX("h_pTrel_C4_mc_weighted",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C3_mc_weighted = (TH1D*) H_pTrel_C3_mc_weighted->ProjectionX("h_pTrel_C3_mc_weighted",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C2_mc_weighted = (TH1D*) H_pTrel_C2_mc_weighted->ProjectionX("h_pTrel_C2_mc_weighted",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   h_pTrel_C1_mc_weighted = (TH1D*) H_pTrel_C1_mc_weighted->ProjectionX("h_pTrel_C1_mc_weighted",binFinder->FindBin(jetPt_low + smallShift),binFinder->FindBin(jetPt_high - smallShift));
   
   
   stylize_raw(h_pTrel_pp_mc_raw,h_pTrel_C4_mc_raw,h_pTrel_C3_mc_raw,h_pTrel_C2_mc_raw,h_pTrel_C1_mc_raw);
   stylize_weighted(h_pTrel_pp_mc_weighted,h_pTrel_C4_mc_weighted,h_pTrel_C3_mc_weighted,h_pTrel_C2_mc_weighted,h_pTrel_C1_mc_weighted);

   set_pTrel_range(h_pTrel_pp_mc_raw);
   set_pTrel_range(h_pTrel_C4_mc_raw);
   set_pTrel_range(h_pTrel_C3_mc_raw);
   set_pTrel_range(h_pTrel_C2_mc_raw);
   set_pTrel_range(h_pTrel_C1_mc_raw);

   set_pTrel_range(h_pTrel_pp_mc_weighted);
   set_pTrel_range(h_pTrel_C4_mc_weighted);
   set_pTrel_range(h_pTrel_C3_mc_weighted);
   set_pTrel_range(h_pTrel_C2_mc_weighted);
   set_pTrel_range(h_pTrel_C1_mc_weighted);

   r_pp = (TH1D*) h_pTrel_pp_mc_weighted->Clone("r_pp");
   r_C4 = (TH1D*) h_pTrel_C4_mc_weighted->Clone("r_C4");
   r_C3 = (TH1D*) h_pTrel_C3_mc_weighted->Clone("r_C3");
   r_C2 = (TH1D*) h_pTrel_C2_mc_weighted->Clone("r_C2");
   r_C1 = (TH1D*) h_pTrel_C1_mc_weighted->Clone("r_C1");

   r_pp->Divide(h_pTrel_pp_mc_weighted,h_pTrel_pp_mc_raw,1,1,"B");
   r_C4->Divide(h_pTrel_C4_mc_weighted,h_pTrel_C4_mc_raw,1,1,"B");
   r_C3->Divide(h_pTrel_C3_mc_weighted,h_pTrel_C3_mc_raw,1,1,"B");
   r_C2->Divide(h_pTrel_C2_mc_weighted,h_pTrel_C2_mc_raw,1,1,"B");
   r_C1->Divide(h_pTrel_C1_mc_weighted,h_pTrel_C1_mc_raw,1,1,"B");

   leg_pp = new TLegend(0.55,0.3,0.84,0.6);
   leg_pp->SetFillStyle(0);
   leg_pp->SetBorderSize(0);
   leg_pp->SetTextSize(0.04);
   leg_pp->AddEntry(h_pTrel_pp_mc_raw,"PYTHIA raw","p");
   leg_pp->AddEntry(h_pTrel_pp_mc_weighted,"PYTHIA w/ #DeltaR reweight","p");

   leg_C4 = new TLegend(0.55,0.3,0.84,0.6);
   leg_C4->SetFillStyle(0);
   leg_C4->SetBorderSize(0);
   leg_C4->SetTextSize(0.04);
   leg_C4->AddEntry(h_pTrel_C4_mc_raw,"P+H 50-80% raw","p");
   leg_C4->AddEntry(h_pTrel_C4_mc_weighted,"P+H 50-80% w/ #DeltaR reweight","p");

   leg_C3 = new TLegend(0.55,0.3,0.84,0.6);
   leg_C3->SetFillStyle(0);
   leg_C3->SetBorderSize(0);
   leg_C3->SetTextSize(0.04);
   leg_C3->AddEntry(h_pTrel_C3_mc_raw,"P+H 30-50% raw","p");
   leg_C3->AddEntry(h_pTrel_C3_mc_weighted,"P+H 30-50% w/ #DeltaR reweight","p");

   leg_C2 = new TLegend(0.55,0.3,0.84,0.6);
   leg_C2->SetFillStyle(0);
   leg_C2->SetBorderSize(0);
   leg_C2->SetTextSize(0.04);
   leg_C2->AddEntry(h_pTrel_C2_mc_raw,"P+H 10-30% raw","p");
   leg_C2->AddEntry(h_pTrel_C2_mc_weighted,"P+H 10-30% w/ #DeltaR reweight","p");

   leg_C1 = new TLegend(0.55,0.3,0.84,0.6);
   leg_C1->SetFillStyle(0);
   leg_C1->SetBorderSize(0);
   leg_C1->SetTextSize(0.04);
   leg_C1->AddEntry(h_pTrel_C1_mc_raw,"P+H 0-10% raw","p");
   leg_C1->AddEntry(h_pTrel_C1_mc_weighted,"P+H 0-10% w/ #DeltaR reweight","p");

   

   subTitleSize = 0.08;
   subLabelSize = 0.06;

   TCanvas *canv_pp = new TCanvas("canv_pp","pp",700,700);
   canv_pp->cd();
   TPad *pad_pp_1 = new TPad("pad_pp_1","pad_pp_1",0,0.4,1,1);
   TPad *pad_pp_2 = new TPad("pad_pp_2","pad_pp_2",0,0,1,0.4);
   pad_pp_1->SetLeftMargin(0.1);
   pad_pp_2->SetLeftMargin(0.1);
   pad_pp_1->SetRightMargin(0.1);
   pad_pp_2->SetRightMargin(0.1);
   pad_pp_1->SetBottomMargin(0);
   pad_pp_2->SetTopMargin(0);
   pad_pp_2->SetBottomMargin(0.2);
   pad_pp_1->Draw();
   pad_pp_2->Draw();
   pad_pp_1->cd();
   h_pTrel_pp_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
   h_pTrel_pp_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
   h_pTrel_pp_mc_raw->GetYaxis()->SetTitleOffset(0.9);
   h_pTrel_pp_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
   h_pTrel_pp_mc_raw->GetYaxis()->SetRangeUser(0,0.15);
   h_pTrel_pp_mc_raw->Draw();
   h_pTrel_pp_mc_weighted->Draw("same");
   leg_pp->Draw();
   la->DrawLatexNDC(0.12,0.92,CMSString);
   la->DrawLatexNDC(0.74,0.92,energyString);
   la->DrawLatexNDC(0.4,0.8,jetPtString);
   la->DrawLatexNDC(0.4,0.7,hadronPtString);
   pad_pp_2->cd();
   r_pp->GetYaxis()->SetTitle("Weighted / Raw  ");
   r_pp->GetYaxis()->SetTitleSize(subTitleSize);
   r_pp->GetYaxis()->SetLabelSize(subLabelSize);
   r_pp->GetYaxis()->SetRangeUser(0.7,1.3);
   r_pp->GetYaxis()->SetTitleOffset(0.55);
   r_pp->GetXaxis()->SetTitle("#it{b}-jet muon #it{p}_{T}^{rel} [GeV]");
   r_pp->GetXaxis()->SetTitleSize(subTitleSize);
   r_pp->GetXaxis()->SetLabelSize(subLabelSize);
   r_pp->Draw();
   li->SetLineStyle(7);
   li->DrawLine(0,1,0.3,1);
   //canv_pp->SaveAs(Form("./figures/dRReweightEffectOnMuons/pp_J%i.pdf",j));

   TCanvas *canv_C4 = new TCanvas("canv_C4","C4",700,700);
   canv_C4->cd();
   TPad *pad_C4_1 = new TPad("pad_C4_1","pad_C4_1",0,0.4,1,1);
   TPad *pad_C4_2 = new TPad("pad_C4_2","pad_C4_2",0,0,1,0.4);
   pad_C4_1->SetLeftMargin(0.1);
   pad_C4_2->SetLeftMargin(0.1);
   pad_C4_1->SetRightMargin(0.1);
   pad_C4_2->SetRightMargin(0.1);
   pad_C4_1->SetBottomMargin(0);
   pad_C4_2->SetTopMargin(0);
   pad_C4_2->SetBottomMargin(0.2);
   pad_C4_1->Draw();
   pad_C4_2->Draw();
   pad_C4_1->cd();
   h_pTrel_C4_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
   h_pTrel_C4_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
   h_pTrel_C4_mc_raw->GetYaxis()->SetTitleOffset(0.9);
   h_pTrel_C4_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
   h_pTrel_C4_mc_raw->GetYaxis()->SetRangeUser(0,0.15);
   h_pTrel_C4_mc_raw->Draw();
   h_pTrel_C4_mc_weighted->Draw("same");
   leg_C4->Draw();
   la->DrawLatexNDC(0.12,0.92,CMSString);
   la->DrawLatexNDC(0.74,0.92,energyString);
   la->DrawLatexNDC(0.4,0.8,jetPtString);
   la->DrawLatexNDC(0.4,0.7,hadronPtString);
   pad_C4_2->cd();
   r_C4->GetYaxis()->SetTitle("Weighted / Raw  ");
   r_C4->GetYaxis()->SetTitleSize(subTitleSize);
   r_C4->GetYaxis()->SetLabelSize(subLabelSize);
   r_C4->GetYaxis()->SetRangeUser(0.7,1.3);
   r_C4->GetYaxis()->SetTitleOffset(0.55);
   r_C4->GetXaxis()->SetTitle("#it{b}-jet muon #it{p}_{T}^{rel} [GeV]");
   r_C4->GetXaxis()->SetTitleSize(subTitleSize);
   r_C4->GetXaxis()->SetLabelSize(subLabelSize);
   r_C4->Draw();
   li->SetLineStyle(7);
   li->DrawLine(0,1,0.3,1);
   //canv_C4->SaveAs(Form("./figures/dRReweightEffectOnMuons/C4_J%i.pdf",j));

   TCanvas *canv_C3 = new TCanvas("canv_C3","C3",700,700);
   canv_C3->cd();
   TPad *pad_C3_1 = new TPad("pad_C3_1","pad_C3_1",0,0.4,1,1);
   TPad *pad_C3_2 = new TPad("pad_C3_2","pad_C3_2",0,0,1,0.4);
   pad_C3_1->SetLeftMargin(0.1);
   pad_C3_2->SetLeftMargin(0.1);
   pad_C3_1->SetRightMargin(0.1);
   pad_C3_2->SetRightMargin(0.1);
   pad_C3_1->SetBottomMargin(0);
   pad_C3_2->SetTopMargin(0);
   pad_C3_2->SetBottomMargin(0.2);
   pad_C3_1->Draw();
   pad_C3_2->Draw();
   pad_C3_1->cd();
   h_pTrel_C3_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
   h_pTrel_C3_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
   h_pTrel_C3_mc_raw->GetYaxis()->SetTitleOffset(0.9);
   h_pTrel_C3_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
   h_pTrel_C3_mc_raw->GetYaxis()->SetRangeUser(0,0.15);
   h_pTrel_C3_mc_raw->Draw();
   h_pTrel_C3_mc_weighted->Draw("same");
   leg_C3->Draw();
   la->DrawLatexNDC(0.12,0.92,CMSString);
   la->DrawLatexNDC(0.74,0.92,energyString);
   la->DrawLatexNDC(0.4,0.8,jetPtString);
   la->DrawLatexNDC(0.4,0.7,hadronPtString);
   pad_C3_2->cd();
   r_C3->GetYaxis()->SetTitle("Weighted / Raw  ");
   r_C3->GetYaxis()->SetTitleSize(subTitleSize);
   r_C3->GetYaxis()->SetLabelSize(subLabelSize);
   r_C3->GetYaxis()->SetRangeUser(0.7,1.3);
   r_C3->GetYaxis()->SetTitleOffset(0.55);
   r_C3->GetXaxis()->SetTitle("#it{b}-jet muon #it{p}_{T}^{rel} [GeV]");
   r_C3->GetXaxis()->SetTitleSize(subTitleSize);
   r_C3->GetXaxis()->SetLabelSize(subLabelSize);
   r_C3->Draw();
   li->SetLineStyle(7);
   li->DrawLine(0,1,0.3,1);
   //canv_C3->SaveAs(Form("./figures/dRReweightEffectOnMuons/C3_J%i.pdf",j));   

   TCanvas *canv_C2 = new TCanvas("canv_C2","C2",700,700);
   canv_C2->cd();
   TPad *pad_C2_1 = new TPad("pad_C2_1","pad_C2_1",0,0.4,1,1);
   TPad *pad_C2_2 = new TPad("pad_C2_2","pad_C2_2",0,0,1,0.4);
   pad_C2_1->SetLeftMargin(0.1);
   pad_C2_2->SetLeftMargin(0.1);
   pad_C2_1->SetRightMargin(0.1);
   pad_C2_2->SetRightMargin(0.1);
   pad_C2_1->SetBottomMargin(0);
   pad_C2_2->SetTopMargin(0);
   pad_C2_2->SetBottomMargin(0.2);
   pad_C2_1->Draw();
   pad_C2_2->Draw();
   pad_C2_1->cd();
   h_pTrel_C2_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
   h_pTrel_C2_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
   h_pTrel_C2_mc_raw->GetYaxis()->SetTitleOffset(0.9);
   h_pTrel_C2_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
   h_pTrel_C2_mc_raw->GetYaxis()->SetRangeUser(0,0.15);
   h_pTrel_C2_mc_raw->Draw();
   h_pTrel_C2_mc_weighted->Draw("same");
   leg_C2->Draw();
   la->DrawLatexNDC(0.12,0.92,CMSString);
   la->DrawLatexNDC(0.74,0.92,energyString);
   la->DrawLatexNDC(0.4,0.8,jetPtString);
   la->DrawLatexNDC(0.4,0.7,hadronPtString);
   pad_C2_2->cd();
   r_C2->GetYaxis()->SetTitle("Weighted / Raw  ");
   r_C2->GetYaxis()->SetTitleSize(subTitleSize);
   r_C2->GetYaxis()->SetLabelSize(subLabelSize);
   r_C2->GetYaxis()->SetRangeUser(0.7,1.3);
   r_C2->GetYaxis()->SetTitleOffset(0.55);
   r_C2->GetXaxis()->SetTitle("#it{b}-jet muon #it{p}_{T}^{rel} [GeV]");
   r_C2->GetXaxis()->SetTitleSize(subTitleSize);
   r_C2->GetXaxis()->SetLabelSize(subLabelSize);
   r_C2->Draw();
   li->SetLineStyle(7);
   li->DrawLine(0,1,0.3,1);
   //canv_C2->SaveAs(Form("./figures/dRReweightEffectOnMuons/C2_J%i.pdf",j));   

   TCanvas *canv_C1 = new TCanvas("canv_C1","C1",700,700);
   canv_C1->cd();
   TPad *pad_C1_1 = new TPad("pad_C1_1","pad_C1_1",0,0.4,1,1);
   TPad *pad_C1_2 = new TPad("pad_C1_2","pad_C1_2",0,0,1,0.4);
   pad_C1_1->SetLeftMargin(0.1);
   pad_C1_2->SetLeftMargin(0.1);
   pad_C1_1->SetRightMargin(0.1);
   pad_C1_2->SetRightMargin(0.1);
   pad_C1_1->SetBottomMargin(0);
   pad_C1_2->SetTopMargin(0);
   pad_C1_2->SetBottomMargin(0.2);
   pad_C1_1->Draw();
   pad_C1_2->Draw();
   pad_C1_1->cd();
   h_pTrel_C1_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
   h_pTrel_C1_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
   h_pTrel_C1_mc_raw->GetYaxis()->SetTitleOffset(0.9);
   h_pTrel_C1_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
   h_pTrel_C1_mc_raw->GetYaxis()->SetRangeUser(0,0.15);
   h_pTrel_C1_mc_raw->Draw();
   h_pTrel_C1_mc_weighted->Draw("same");
   leg_C1->Draw();
   la->DrawLatexNDC(0.12,0.92,CMSString);
   la->DrawLatexNDC(0.74,0.92,energyString);
   la->DrawLatexNDC(0.4,0.8,jetPtString);
   la->DrawLatexNDC(0.4,0.7,hadronPtString);
   pad_C1_2->cd();
   r_C1->GetYaxis()->SetTitle("Weighted / Raw  ");
   r_C1->GetYaxis()->SetTitleSize(subTitleSize);
   r_C1->GetYaxis()->SetLabelSize(subLabelSize);
   r_C1->GetYaxis()->SetRangeUser(0.7,1.3);
   r_C1->GetYaxis()->SetTitleOffset(0.55);
   r_C1->GetXaxis()->SetTitle("#it{b}-jet muon #it{p}_{T}^{rel} [GeV]");
   r_C1->GetXaxis()->SetTitleSize(subTitleSize);
   r_C1->GetXaxis()->SetLabelSize(subLabelSize);
   r_C1->Draw();
   li->SetLineStyle(7);
   li->DrawLine(0,1,0.3,1);
   //canv_C1->SaveAs(Form("./figures/dRReweightEffectOnMuons/C1_J%i.pdf",j));   



   
     
   
}
