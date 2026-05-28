


#include "../../headers/AnalysisSetupV2p4.h"

TH1D* divideHistograms(TH1D* h_num, TH1D* h_den, const char* name) {
    TH1D* h_ratio = (TH1D*)h_num->Clone(name);
    h_ratio->Reset();

    for (int i = 1; i <= h_num->GetNbinsX(); i++) {
        double num = h_num->GetBinContent(i);
        double den = h_den->GetBinContent(i);
        if (den == 0) {
            h_ratio->SetBinContent(i, -1.0);
            h_ratio->SetBinError(i, 0.0);
        } else {
            h_ratio->SetBinContent(i, num / den);
            double err = (num / den) * std::sqrt(
                (num > 0 ? std::pow(h_num->GetBinError(i) / num, 2) : 0) +
                std::pow(h_den->GetBinError(i) / den, 2)
            );
            h_ratio->SetBinError(i, err);
        }
    }
    return h_ratio;
}
void fakeJetTriggerStudy(){

  TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  TFile *file_HYDJET_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/latest/HYDJET_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-12_ultraFineCentBins.root");
  TFile *file_PYTHIAHYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");
  TFile *file_PYTHIAHYDJET_jet60 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-unweighted_Jet60HLT_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-13_ultraFineCentBins.root");


  // vz histograms (event counts)
  TH1D *h_vz_PYTHIAHYDJET[NCentralityIndices-1];
  TH1D *h_vz_PYTHIAHYDJET_jet60[NCentralityIndices-1];

  // jet histograms
  TH2D *H_HYDJET[NCentralityIndices-1];
  TH2D *H_HYDJET_jet60[NCentralityIndices-1];
  TH2D *H_PYTHIAHYDJET[NCentralityIndices-1];
  TH2D *H_PYTHIAHYDJET_jet60[NCentralityIndices-1];

  TH1D *h_HYDJET_xJets[NCentralityIndices-1];
  TH1D *h_HYDJET_xJets_jet60[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_allJets[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_matchedJets[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_xJets[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_allJets_jet60[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_matchedJets_jet60[NCentralityIndices-1];
  TH1D *h_PYTHIAHYDJET_xJets_jet60[NCentralityIndices-1];

  TH1D *r_PYTHIAHYDJET[NCentralityIndices-1];
  TH1D *r_PYTHIAHYDJET_jet60[NCentralityIndices-1];

  const int N_edge = 6;
  double newAxis[N_edge] = {80,90,100,120,150,200};

  for(int i = 0; i < NCentralityIndices-1; i++){

    /// retreive vz
    file_PYTHIAHYDJET->GetObject(Form("h_vz_C%i",i+1),h_vz_PYTHIAHYDJET[i]);
    file_PYTHIAHYDJET_jet60->GetObject(Form("h_vz_jet60_C%i",i+1),h_vz_PYTHIAHYDJET_jet60[i]);

    /// retreive jets
    file_HYDJET->GetObject(Form("h_inclRecoJetPt_flavor_C%i",i+1),H_HYDJET[i]);
    file_HYDJET_jet60->GetObject(Form("h_inclRecoJetPt_flavor_C%i",i+1),H_HYDJET_jet60[i]);
    file_PYTHIAHYDJET->GetObject(Form("h_inclRecoJetPt_flavor_C%i",i+1),H_PYTHIAHYDJET[i]);
    file_PYTHIAHYDJET_jet60->GetObject(Form("h_inclRecoJetPt_flavor_C%i",i+1),H_PYTHIAHYDJET_jet60[i]);

    h_HYDJET_xJets[i] = (TH1D*) H_HYDJET[i]->ProjectionX(Form("h_HYDJET_xJets_C%i",i+1));
    h_HYDJET_xJets_jet60[i] = (TH1D*) H_HYDJET_jet60[i]->ProjectionX(Form("h_HYDJET_xJets_jet60_C%i",i+1));

    h_PYTHIAHYDJET_allJets[i] = (TH1D*) H_PYTHIAHYDJET[i]->ProjectionX(Form("h_PYTHIAHYDJET_allJets_C%i",i+1),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(-5.),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(22.));
    h_PYTHIAHYDJET_matchedJets[i] = (TH1D*) H_PYTHIAHYDJET[i]->ProjectionX(Form("h_PYTHIAHYDJET_matchedJets_C%i",i+1),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(-5.),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(-1.));
    h_PYTHIAHYDJET_matchedJets[i]->Add(H_PYTHIAHYDJET[i]->ProjectionX(Form("h_PYTHIAHYDJET_matchedJets_add_C%i",i+1),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(1.),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(22.)));
    h_PYTHIAHYDJET_xJets[i] = (TH1D*) H_PYTHIAHYDJET[i]->ProjectionX(Form("h_PYTHIAHYDJET_xJets_C%i",i+1),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(0.),H_PYTHIAHYDJET[i]->GetYaxis()->FindBin(0.));

    h_PYTHIAHYDJET_allJets_jet60[i] = (TH1D*) H_PYTHIAHYDJET_jet60[i]->ProjectionX(Form("h_PYTHIAHYDJET_allJets_jet60_C%i",i+1),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(-5.),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(22.));
    h_PYTHIAHYDJET_matchedJets_jet60[i] = (TH1D*) H_PYTHIAHYDJET_jet60[i]->ProjectionX(Form("h_PYTHIAHYDJET_matchedJets_jet60_C%i",i+1),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(-5.),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(-1.));
    h_PYTHIAHYDJET_matchedJets_jet60[i]->Add(H_PYTHIAHYDJET_jet60[i]->ProjectionX(Form("h_PYTHIAHYDJET_matchedJets_jet60_add_C%i",i+1),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(1.),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(22.)));
    h_PYTHIAHYDJET_xJets_jet60[i] = (TH1D*) H_PYTHIAHYDJET_jet60[i]->ProjectionX(Form("h_PYTHIAHYDJET_xJets_jet60_C%i",i+1),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(0.),H_PYTHIAHYDJET_jet60[i]->GetYaxis()->FindBin(0.));


    // rebin
    h_PYTHIAHYDJET_allJets[i] = (TH1D*) h_PYTHIAHYDJET_allJets[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_allJets_C%i",i+1),newAxis);
    h_PYTHIAHYDJET_allJets_jet60[i] = (TH1D*) h_PYTHIAHYDJET_allJets_jet60[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_allJets_jet60_C%i",i+1),newAxis);
    h_PYTHIAHYDJET_matchedJets[i] = (TH1D*) h_PYTHIAHYDJET_matchedJets[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_matchedJets_C%i",i+1),newAxis);
    h_PYTHIAHYDJET_matchedJets_jet60[i] = (TH1D*) h_PYTHIAHYDJET_matchedJets_jet60[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_matchedJets_jet60_C%i",i+1),newAxis);
    h_PYTHIAHYDJET_xJets[i] = (TH1D*) h_PYTHIAHYDJET_xJets[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_xJets_C%i",i+1),newAxis);
    h_PYTHIAHYDJET_xJets_jet60[i] = (TH1D*) h_PYTHIAHYDJET_xJets_jet60[i]->Rebin(N_edge-1,Form("h_PYTHIAHYDJET_xJets_jet60_C%i",i+1),newAxis);
    

    r_PYTHIAHYDJET[i] = (TH1D*) h_PYTHIAHYDJET_allJets[i]->Clone(Form("r_PYTHIAHYDJET_C%i",i+1));
    //r_PYTHIAHYDJET[i]->Divide(h_PYTHIAHYDJET_allJets[i],h_PYTHIAHYDJET_matchedJets[i],1,1,"B");
    r_PYTHIAHYDJET[i]->Add(h_PYTHIAHYDJET_matchedJets[i],-1);
    r_PYTHIAHYDJET[i]->Scale(1./h_vz_PYTHIAHYDJET[i]->Integral());
    

    r_PYTHIAHYDJET_jet60[i] = (TH1D*) h_PYTHIAHYDJET_allJets_jet60[i]->Clone(Form("r_PYTHIAHYDJET_jet60_C%i",i+1));
    //r_PYTHIAHYDJET_jet60[i]->Divide(h_PYTHIAHYDJET_allJets_jet60[i],h_PYTHIAHYDJET_matchedJets_jet60[i],1,1,"B");
    r_PYTHIAHYDJET_jet60[i]->Add(h_PYTHIAHYDJET_matchedJets_jet60[i],-1);
    r_PYTHIAHYDJET_jet60[i]->Scale(1./h_vz_PYTHIAHYDJET_jet60[i]->Integral());

    std::cout << "Cent Bin " << i+1  << ": N_evt(jet60) / N_evt(all) = " << h_vz_PYTHIAHYDJET_jet60[i]->Integral() << " / " << h_vz_PYTHIAHYDJET[i]->Integral() << " = " << h_vz_PYTHIAHYDJET_jet60[i]->Integral() / h_vz_PYTHIAHYDJET[i]->Integral() << "\n";

  }

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  // 16-color palette: Wong (8) + Tol Muted (8)
  int colors[16] = {
    TColor::GetColor("#000000"),
    TColor::GetColor("#E69F00"),
    TColor::GetColor("#56B4E9"),
    TColor::GetColor("#009E73"),
    TColor::GetColor("#F0E442"),
    TColor::GetColor("#0072B2"),
    TColor::GetColor("#D55E00"),
    TColor::GetColor("#CC79A7"),
    TColor::GetColor("#332288"),
    TColor::GetColor("#117733"),
    TColor::GetColor("#44AA99"),
    TColor::GetColor("#88CCEE"),
    TColor::GetColor("#DDCC77"),
    TColor::GetColor("#CC6677"),
    TColor::GetColor("#AA4499"),
    TColor::GetColor("#882255"),
  };

  int nCent = NCentralityIndices - 1;
  auto centLabel = [](int i){ return Form("%i-%i%%", i*5, (i+1)*5); };

  // --- Compute fake rate ratios ---
  TH1D *r_ratio[NCentralityIndices-1];
  for(int i = 0; i < nCent; i++){
    r_ratio[i] = (TH1D*) r_PYTHIAHYDJET_jet60[i]->Clone(Form("r_ratio_C%i", i+1));
    r_ratio[i]->Divide(r_PYTHIAHYDJET_jet60[i],r_PYTHIAHYDJET[i],1,1,"B");
  }

  // --- Compute spectra ratios (unbiased / jet60) ---
  TH1D *r_spectra[NCentralityIndices-1];
  for(int i = 0; i < nCent; i++){
    r_spectra[i] = (TH1D*) h_PYTHIAHYDJET_allJets_jet60[i]->Clone(Form("r_spectra_C%i", i+1));
    r_spectra[i]->Divide(h_PYTHIAHYDJET_allJets_jet60[i],h_PYTHIAHYDJET_allJets[i],1,1,"B");
  }

  // --- Range helper ---
  auto getRange = [&](std::initializer_list<TH1D**> sets, double &yMin, double &yMax){
    double gMin = 1e9, gMax = -1e9;
    for(TH1D **ratios : sets){
      for(int i = 0; i < nCent; i++){
	for(int b = 1; b <= ratios[i]->GetNbinsX(); b++){
	  double val = ratios[i]->GetBinContent(b);
	  double err = ratios[i]->GetBinError(b);
	  if(val == 0) continue;
	  gMin = std::min(gMin, val - err);
	  gMax = std::max(gMax, val + err);
	}
      }
    }
    double margin = 0.05 * (gMax - gMin);
    yMin = gMin - margin;
    yMax = gMax + margin;
  };

  double yMin_main, yMax_main, yMin_ratio, yMax_ratio;
  getRange({r_PYTHIAHYDJET, r_PYTHIAHYDJET_jet60}, yMin_main,  yMax_main);
  getRange({r_ratio},                              yMin_ratio, yMax_ratio);

  // --- Draw overlay canvases (square) ---
  auto drawRatios = [&](TH1D **ratios, const char *canvasName, const char *ytitle, double yMin, double yMax){
    TCanvas *c = new TCanvas(canvasName, canvasName, 800, 800);
    TLegend *leg = new TLegend(0.65, 0.12, 0.92, 0.92);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetNColumns(2);

    for(int i = 0; i < nCent; i++){
      ratios[i]->SetLineColor(colors[i]);
      ratios[i]->SetLineWidth(2);
      ratios[i]->SetMarkerColor(colors[i]);
      ratios[i]->SetMarkerStyle(20 + i);
      ratios[i]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
      ratios[i]->GetYaxis()->SetTitle(ytitle);
      ratios[i]->GetYaxis()->SetRangeUser(yMin, yMax);
      ratios[i]->SetTitle("");
      //ratios[i]->Draw(i == 0 ? "EP" : "EP SAME");
      ratios[i]->Draw(i == 0 ? "HIST" : "HIST SAME");
      leg->AddEntry(ratios[i], centLabel(i), "lep");
    }
    leg->Draw();
    c->SaveAs(Form("../../figures/fakeJetTriggerStudy/%s.pdf", canvasName));
  };

  drawRatios(r_PYTHIAHYDJET,       "c_ratio",                   "#frac{N^{fakeJet}_{unbiased}}{N^{evt}_{unbiased}}",         yMin_main,  yMax_main);
  drawRatios(r_PYTHIAHYDJET_jet60, "c_ratio_jet60",             "#frac{N^{fakeJet}_{jet60}}{N^{evt}_{jet60}}", yMin_main,  yMax_main);
  // drawRatios(r_PYTHIAHYDJET,       "c_ratio",                   "N^{allJets}_{unbiased} / N^{matchedJets}_{unbiased}",         yMin_main,  yMax_main);
  // drawRatios(r_PYTHIAHYDJET_jet60, "c_ratio_jet60",             "N^{allJets}_{jet60} / N^{matchedJets}_{jet60}", yMin_main,  yMax_main);
  drawRatios(r_ratio,              "c_ratio_unbiased_over_jet60", "Jet60 / Unbiased",    yMin_ratio, yMax_ratio);

  // --- Per-centrality spectra canvas (top: spectra, bottom: ratio) ---

  // Find global spectra range
  double specMin = 1e9, specMax = -1e9;
  for(int i = 0; i < nCent; i++){
    for(TH1D *h : {h_PYTHIAHYDJET_allJets[i], h_PYTHIAHYDJET_allJets_jet60[i]}){
      for(int b = 1; b <= h->GetNbinsX(); b++){
	double val = h->GetBinContent(b);
	double err = h->GetBinError(b);
	if(val == 0) continue;
	specMin = std::min(specMin, val - err);
	specMax = std::max(specMax, val + err);
      }
    }
  }
  double specMargin = 0.05 * (specMax - specMin);
  specMin -= specMargin;
  specMax += specMargin;

  double ratSpecMin = 0, ratSpecMax = 3;
  // double ratSpecMin = 1e9, ratSpecMax = -1e9;
  // for(int i = 0; i < nCent; i++){
  //   for(int b = 1; b <= r_spectra[i]->GetNbinsX(); b++){
  //     double val = r_spectra[i]->GetBinContent(b);
  //     double err = r_spectra[i]->GetBinError(b);
  //     if(val == 0) continue;
  //     ratSpecMin = std::min(ratSpecMin, val - err);
  //     ratSpecMax = std::max(ratSpecMax, val + err);
  //   }
  // }
  // double ratSpecMargin = 0.05 * (ratSpecMax - ratSpecMin);
  // ratSpecMin -= ratSpecMargin;
  // ratSpecMax += ratSpecMargin;

  for(int i = 0; i < nCent; i++){
    TCanvas *c = new TCanvas(Form("c_spectra_C%i", i+1), Form("Spectra %s", centLabel(i)), 800, 800);

    // Top pad: spectra
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1);
    pad1->SetBottomMargin(0.02);
    pad1->SetLeftMargin(0.15);
    pad1->Draw();
    pad1->cd();

    h_PYTHIAHYDJET_allJets[i]->SetLineColor(kBlack);
    h_PYTHIAHYDJET_allJets[i]->SetMarkerColor(kBlack);
    h_PYTHIAHYDJET_allJets[i]->SetMarkerStyle(20);
    h_PYTHIAHYDJET_allJets[i]->GetYaxis()->SetTitle("Counts");
    h_PYTHIAHYDJET_allJets[i]->GetYaxis()->SetRangeUser(specMin, specMax);
    h_PYTHIAHYDJET_allJets[i]->GetXaxis()->SetLabelSize(0);
    h_PYTHIAHYDJET_allJets[i]->SetTitle("");
    h_PYTHIAHYDJET_allJets[i]->Draw("EP");

    h_PYTHIAHYDJET_allJets_jet60[i]->SetLineColor(TColor::GetColor("#0072B2"));
    h_PYTHIAHYDJET_allJets_jet60[i]->SetMarkerColor(TColor::GetColor("#0072B2"));
    h_PYTHIAHYDJET_allJets_jet60[i]->SetMarkerStyle(21);
    h_PYTHIAHYDJET_allJets_jet60[i]->Draw("EP SAME");

    TLegend *leg = new TLegend(0.55, 0.65, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(h_PYTHIAHYDJET_allJets[i],       "Unbiased", "lep");
    leg->AddEntry(h_PYTHIAHYDJET_allJets_jet60[i], "Jet60",    "lep");
    leg->SetHeader(centLabel(i), "C");
    leg->Draw();

    // Bottom pad: ratio
    c->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0, 1, 0.35);
    pad2->SetTopMargin(0.02);
    pad2->SetBottomMargin(0.25);
    pad2->SetLeftMargin(0.15);
    pad2->Draw();
    pad2->cd();

    r_spectra[i]->SetLineColor(kBlack);
    r_spectra[i]->SetMarkerColor(kBlack);
    r_spectra[i]->SetMarkerStyle(20);
    r_spectra[i]->GetXaxis()->SetTitle("Jet p_{T} (GeV)");
    r_spectra[i]->GetYaxis()->SetTitle("Jet60 / Unbiased");
    //r_spectra[i]->GetYaxis()->SetRangeUser(ratSpecMin, ratSpecMax);
    //r_spectra[i]->GetYaxis()->SetRangeUser(0.0, 3.0);
    r_spectra[i]->GetXaxis()->SetTitleSize(0.09);
    r_spectra[i]->GetXaxis()->SetLabelSize(0.08);
    r_spectra[i]->GetYaxis()->SetTitleSize(0.08);
    r_spectra[i]->GetYaxis()->SetLabelSize(0.07);
    r_spectra[i]->GetYaxis()->SetTitleOffset(0.8);
    r_spectra[i]->SetTitle("");
    r_spectra[i]->Draw("EP");

    c->SaveAs(Form("../../figures/fakeJetTriggerStudy/c_spectra_C%i.pdf", i+1));
  }

}
