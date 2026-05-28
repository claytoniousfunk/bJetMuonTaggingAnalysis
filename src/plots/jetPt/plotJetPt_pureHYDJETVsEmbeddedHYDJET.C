

#include "../../../headers/functions/divideByBinwidth.h"


string getCentString(int centralityIndex){

  string result = "";
  
  if(centralityIndex == 0) result = "0-80%";
  else result = Form("%i-%i%%",5*(centralityIndex-1),5*(centralityIndex));
  
  return result;

}


void plotJetPt_pureHYDJETVsEmbeddedHYDJET(int centralityIndex = 1){

  TFile *file_HYDJET = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/HYDJET/canonical/HYDJET_pThat-unweighted_mu12_pTmu-15to999_tight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_WDecayFilter_2026-5-27_ultraFineCentBins.root");
  TFile *file_PYTHIAHYDJET_pThatWeighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-15_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27_ultraFineCentBins.root");
  TFile *file_PYTHIAHYDJET_pThatUnweighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/canonical/PYTHIAHYDJET_DiJet_pThat-unweighted_mu12_pTmu-15to999_tight_vzReweight_hiBinReweightToHardProbesJet80_hiBinShift-10_jetTrkMaxFilter_doPThatCorrelationFilterTight_WDecayFilter_2026-5-27_ultraFineCentBins.root");

  TH2D *H_HYDJET, *H_PYTHIAHYDJET_pThatWeighted, *H_PYTHIAHYDJET_pThatUnweighted;
  TH1D *h_HYDJET_xJets, *h_PYTHIAHYDJET_pThatWeighted_xJets, *h_PYTHIAHYDJET_pThatUnweighted_xJets;
  TH1D *h_hiBin_HYDJET, *h_hiBin_PYTHIAHYDJET_pThatWeighted, *h_hiBin_PYTHIAHYDJET_pThatUnweighted;

  file_HYDJET->GetObject(Form("h_inclRecoJetPt_flavor_C%i",centralityIndex),H_HYDJET);
  file_PYTHIAHYDJET_pThatWeighted->GetObject(Form("h_inclRecoJetPt_flavor_C%i",centralityIndex),H_PYTHIAHYDJET_pThatWeighted);
  file_PYTHIAHYDJET_pThatUnweighted->GetObject(Form("h_inclRecoJetPt_flavor_C%i",centralityIndex),H_PYTHIAHYDJET_pThatUnweighted);

  file_HYDJET->GetObject("h_hiBin",h_hiBin_HYDJET);
  file_PYTHIAHYDJET_pThatWeighted->GetObject("h_hiBin",h_hiBin_PYTHIAHYDJET_pThatWeighted);
  file_PYTHIAHYDJET_pThatUnweighted->GetObject("h_hiBin",h_hiBin_PYTHIAHYDJET_pThatUnweighted);

  h_hiBin_HYDJET->Scale(1./h_hiBin_HYDJET->Integral());
  h_hiBin_PYTHIAHYDJET_pThatWeighted->Scale(1./h_hiBin_PYTHIAHYDJET_pThatWeighted->Integral());
  h_hiBin_PYTHIAHYDJET_pThatUnweighted->Scale(1./h_hiBin_PYTHIAHYDJET_pThatUnweighted->Integral());

  h_hiBin_HYDJET->SetLineColor(kBlack);
  h_hiBin_PYTHIAHYDJET_pThatWeighted->SetLineColor(kBlue-4);
  h_hiBin_PYTHIAHYDJET_pThatUnweighted->SetLineColor(kRed-4);
  
  h_HYDJET_xJets = (TH1D*) H_HYDJET->ProjectionX("h_HYDJET_xJets",H_HYDJET->GetYaxis()->FindBin(0.),H_HYDJET->GetYaxis()->FindBin(0.));

  h_PYTHIAHYDJET_pThatWeighted_xJets = (TH1D*) H_PYTHIAHYDJET_pThatWeighted->ProjectionX("h_PYTHIAHYDJET_pThatWeighted_xJets",H_PYTHIAHYDJET_pThatWeighted->GetYaxis()->FindBin(18.),H_PYTHIAHYDJET_pThatWeighted->GetYaxis()->FindBin(18.));
  h_PYTHIAHYDJET_pThatWeighted_xJets->Add(H_PYTHIAHYDJET_pThatWeighted->ProjectionX("h_PYTHIAHYDJET_pThatWeighted_xJets_add",H_PYTHIAHYDJET_pThatWeighted->GetYaxis()->FindBin(0.),H_PYTHIAHYDJET_pThatWeighted->GetYaxis()->FindBin(0.)));
  
  h_PYTHIAHYDJET_pThatUnweighted_xJets = (TH1D*) H_PYTHIAHYDJET_pThatUnweighted->ProjectionX("h_PYTHIAHYDJET_pThatUnweighted_xJets",H_PYTHIAHYDJET_pThatUnweighted->GetYaxis()->FindBin(18.),H_PYTHIAHYDJET_pThatUnweighted->GetYaxis()->FindBin(18.));
  h_PYTHIAHYDJET_pThatUnweighted_xJets->Add(H_PYTHIAHYDJET_pThatUnweighted->ProjectionX("h_PYTHIAHYDJET_pThatUnweighted_xJets_add",H_PYTHIAHYDJET_pThatUnweighted->GetYaxis()->FindBin(0.),H_PYTHIAHYDJET_pThatUnweighted->GetYaxis()->FindBin(0.)));
  

  h_HYDJET_xJets->Scale(1./h_HYDJET_xJets->Integral());
  h_PYTHIAHYDJET_pThatWeighted_xJets->Scale(1./h_PYTHIAHYDJET_pThatWeighted_xJets->Integral());
  h_PYTHIAHYDJET_pThatUnweighted_xJets->Scale(1./h_PYTHIAHYDJET_pThatUnweighted_xJets->Integral());

  h_HYDJET_xJets->SetLineColor(kBlack);
  h_PYTHIAHYDJET_pThatWeighted_xJets->SetLineColor(kBlue-4);
  h_PYTHIAHYDJET_pThatUnweighted_xJets->SetLineColor(kRed-4);

  h_HYDJET_xJets->SetLineWidth(2);
  h_PYTHIAHYDJET_pThatWeighted_xJets->SetLineWidth(2);
  h_PYTHIAHYDJET_pThatUnweighted_xJets->SetLineWidth(2);

  divideByBinwidth(h_HYDJET_xJets);
  divideByBinwidth(h_PYTHIAHYDJET_pThatWeighted_xJets);
  divideByBinwidth(h_PYTHIAHYDJET_pThatUnweighted_xJets);

  h_HYDJET_xJets->SetTitle("");
  h_PYTHIAHYDJET_pThatWeighted_xJets->SetTitle("");
  h_PYTHIAHYDJET_pThatUnweighted_xJets->SetTitle("");

  h_HYDJET_xJets->SetStats(0);
  h_PYTHIAHYDJET_pThatWeighted_xJets->SetStats(0);
  h_PYTHIAHYDJET_pThatUnweighted_xJets->SetStats(0);

  
  TH1D *r_PYTHIAHYDJET_pThatWeighted = (TH1D*) h_PYTHIAHYDJET_pThatWeighted_xJets->Clone("r_PYTHIAHYDJET_pThatWeighted");
  r_PYTHIAHYDJET_pThatWeighted->Divide(h_HYDJET_xJets);
  TH1D *r_PYTHIAHYDJET_pThatUnweighted = (TH1D*) h_PYTHIAHYDJET_pThatUnweighted_xJets->Clone("r_PYTHIAHYDJET_pThatUnweighted");
  r_PYTHIAHYDJET_pThatUnweighted->Divide(h_HYDJET_xJets);

  TH1D *r_hiBin_PYTHIAHYDJET_pThatWeighted = (TH1D*) h_hiBin_PYTHIAHYDJET_pThatWeighted->Clone("r_hiBin_PYTHIAHYDJET_pThatWeighted");
  r_hiBin_PYTHIAHYDJET_pThatWeighted->Divide(h_hiBin_HYDJET);
  TH1D *r_hiBin_PYTHIAHYDJET_pThatUnweighted = (TH1D*) h_hiBin_PYTHIAHYDJET_pThatUnweighted->Clone("r_hiBin_PYTHIAHYDJET_pThatUnweighted");
  r_hiBin_PYTHIAHYDJET_pThatUnweighted->Divide(h_hiBin_HYDJET);

  string centString = getCentString(centralityIndex);

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.045);

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  TCanvas *canv_hiBin = new TCanvas("canv_hiBin","canv_hiBin",700,700);
  canv_hiBin->cd();
  TPad *pad_hiBin_upper = new TPad("pad_hiBin_upper","pad_hiBin_upper",0,0.4,1,1);
  TPad *pad_hiBin_lower = new TPad("pad_hiBin_lower","pad_hiBin_lower",0,0,1,0.4);
  pad_hiBin_upper->SetLeftMargin(0.15);
  pad_hiBin_lower->SetLeftMargin(0.15);
  pad_hiBin_upper->SetBottomMargin(0.0);
  pad_hiBin_lower->SetBottomMargin(0.2);
  pad_hiBin_upper->SetTopMargin(0.1);
  pad_hiBin_lower->SetTopMargin(0.0);
  pad_hiBin_upper->Draw();
  pad_hiBin_lower->Draw();
  pad_hiBin_upper->cd();

  h_hiBin_HYDJET->GetYaxis()->SetTitleSize(0.07);
  h_hiBin_HYDJET->GetYaxis()->SetLabelSize(0.06);
  h_hiBin_HYDJET->GetYaxis()->SetTitleOffset(0.9);
  h_hiBin_HYDJET->GetYaxis()->SetTitle("1/#it{N}^{evt}_{tot} d#it{N}^{evt}/d(hiBin)");
  h_hiBin_HYDJET->SetTitle("");
  h_hiBin_HYDJET->SetStats(0);
  h_hiBin_HYDJET->Draw("hist");
  h_hiBin_PYTHIAHYDJET_pThatWeighted->Draw("hist same");
  h_hiBin_PYTHIAHYDJET_pThatUnweighted->Draw("hist same");

  TLegend *leg_hiBin = new TLegend(0.35,0.65,0.85,0.85);
  leg_hiBin->SetBorderSize(0);
  leg_hiBin->SetFillStyle(0);
  leg_hiBin->SetTextSize(0.05);
  leg_hiBin->AddEntry(h_hiBin_HYDJET,"HYDJET");
  leg_hiBin->AddEntry(h_hiBin_PYTHIAHYDJET_pThatUnweighted,"PYTHIA+HYDJET (#hat{#it{p}}_{T}-unweighted)");
  leg_hiBin->AddEntry(h_hiBin_PYTHIAHYDJET_pThatWeighted,"PYTHIA+HYDJET (#hat{#it{p}}_{T}-weighted)");
  leg_hiBin->Draw();

  pad_hiBin_lower->cd();

  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetTitleSize(0.085);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetLabelSize(0.075);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetTitle("P+H / HYDJET");
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetRangeUser(0,2);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetTitleSize(0.085);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetLabelSize(0.075);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetTitle("hiBin");
  r_hiBin_PYTHIAHYDJET_pThatWeighted->SetTitle("");
  r_hiBin_PYTHIAHYDJET_pThatWeighted->SetStats(0);
  r_hiBin_PYTHIAHYDJET_pThatWeighted->Draw("hist");
  r_hiBin_PYTHIAHYDJET_pThatUnweighted->Draw("hist same");
  
  li->DrawLine(0,1,500,1);

  canv_hiBin->SaveAs("../../../figures/jetPt/pureHYDJETVsEmbeddedHYDJET/hiBin_pureHYDJETVsEmbeddedHYDJET.pdf");


  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad_upper = new TPad("pad_upper","pad_upper",0,0.4,1,1);
  TPad *pad_lower = new TPad("pad_lower","pad_lower",0,0,1,0.4);
  pad_upper->SetLeftMargin(0.15);
  pad_lower->SetLeftMargin(0.15);
  pad_upper->SetBottomMargin(0.0);
  pad_lower->SetBottomMargin(0.2);
  pad_upper->SetTopMargin(0.1);
  pad_lower->SetTopMargin(0.0);
  pad_upper->SetLogy();
  pad_upper->Draw();
  pad_lower->Draw();
  pad_upper->cd();

  h_HYDJET_xJets->GetYaxis()->SetTitleSize(0.07);
  h_HYDJET_xJets->GetYaxis()->SetLabelSize(0.06);
  h_HYDJET_xJets->GetYaxis()->SetTitleOffset(0.9);
  h_HYDJET_xJets->GetYaxis()->SetTitle("1/#it{N}^{xJet}_{tot} d#it{N}^{xJet}/d#it{p}_{T} [GeV^{-1}]");
  
  h_HYDJET_xJets->Draw("hist");
  h_PYTHIAHYDJET_pThatWeighted_xJets->Draw("hist same");
  h_PYTHIAHYDJET_pThatUnweighted_xJets->Draw("hist same");

  TLegend *leg = new TLegend(0.35,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->AddEntry(h_HYDJET_xJets,"x-jets, HYDJET");
  leg->AddEntry(h_PYTHIAHYDJET_pThatUnweighted_xJets,"x-jets, PYTHIA+HYDJET (#hat{#it{p}}_{T}-unweighted)");
  leg->AddEntry(h_PYTHIAHYDJET_pThatWeighted_xJets,"x-jets, PYTHIA+HYDJET (#hat{#it{p}}_{T}-weighted)");
  leg->Draw();

  
  
  la->DrawLatexNDC(0.22,0.92,Form("PbPb %s",centString.c_str()));

  pad_lower->cd();
  r_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetTitleSize(0.085);
  r_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetLabelSize(0.075);
  r_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetTitle("P+H / HYDJET");
  r_PYTHIAHYDJET_pThatWeighted->GetYaxis()->SetRangeUser(0,2);
  r_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetTitleSize(0.085);
  r_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetLabelSize(0.075);
  r_PYTHIAHYDJET_pThatWeighted->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_PYTHIAHYDJET_pThatWeighted->Draw("hist");
  r_PYTHIAHYDJET_pThatUnweighted->Draw("hist same");
  li->DrawLine(0,1,500,1);

  canv->SaveAs(Form("../../../figures/jetPt/pureHYDJETVsEmbeddedHYDJET/jetPt_pureHYDJETVsEmbeddedHYDJET_C%i.pdf",centralityIndex));
  



}
