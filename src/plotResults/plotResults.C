#include "../../headers/systematicsResults.h"
#include "../../headers/goldenFileNames.h"

TFile *file_results_pp;
TFile *file_results_C2;
TFile *file_results_C1;

TFile *file_PY;
TFile *file_PH;

TH2D *genJetPt_2D_pp, *genJetPt_2D_C2, *genJetPt_2D_C1;
TH1D *genJetPt_allJets_pp, *genJetPt_bJets_pp, *genJetPt_bbarJets_pp;
TH1D *genJetPt_allJets_C2, *genJetPt_bJets_C2, *genJetPt_bbarJets_C2;
TH1D *genJetPt_allJets_C1, *genJetPt_bJets_C1, *genJetPt_bbarJets_C1;

TH1D *bFractionResults_pp;
TH1D *bFractionResults_C2;
TH1D *bFractionResults_C1;

void plotResults(){

  file_PY = TFile::Open(goldenFile_PYTHIA);
  file_PH = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet);

  file_PY->GetObject("h_inclGenJetPt_flavor",genJetPt_2D_pp);
  file_PH->GetObject("h_inclGenJetPt_flavor_C2",genJetPt_2D_C2);
  file_PH->GetObject("h_inclGenJetPt_flavor_C1",genJetPt_2D_C1);

  TH1D *binFinder = genJetPt_2D_pp->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;
  
  genJetPt_allJets_pp = (TH1D*) genJetPt_2D_pp->ProjectionX("genJetPt_allJets_pp",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(22 - smallShift));
  genJetPt_allJets_C2 = (TH1D*) genJetPt_2D_C2->ProjectionX("genJetPt_allJets_C2",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(22 - smallShift));
  genJetPt_allJets_C1 = (TH1D*) genJetPt_2D_C1->ProjectionX("genJetPt_allJets_C1",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(22 - smallShift));

  genJetPt_bJets_pp = (TH1D*) genJetPt_2D_pp->ProjectionX("genJetPt_bJets_pp",binFinder->FindBin(5 + smallShift), binFinder->FindBin(6 - smallShift));
  genJetPt_bJets_C2 = (TH1D*) genJetPt_2D_C2->ProjectionX("genJetPt_bJets_C2",binFinder->FindBin(5 + smallShift), binFinder->FindBin(6 - smallShift));
  genJetPt_bJets_C1 = (TH1D*) genJetPt_2D_C1->ProjectionX("genJetPt_bJets_C1",binFinder->FindBin(5 + smallShift), binFinder->FindBin(6 - smallShift));

  genJetPt_bbarJets_pp = (TH1D*) genJetPt_2D_pp->ProjectionX("genJetPt_bbarJets_pp",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(-4 - smallShift));
  genJetPt_bbarJets_C2 = (TH1D*) genJetPt_2D_C2->ProjectionX("genJetPt_bbarJets_C2",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(-4 - smallShift));
  genJetPt_bbarJets_C1 = (TH1D*) genJetPt_2D_C1->ProjectionX("genJetPt_bbarJets_C1",binFinder->FindBin(-5 + smallShift), binFinder->FindBin(-4 - smallShift));

  genJetPt_bJets_pp->Add(genJetPt_bbarJets_pp);
  genJetPt_bJets_C2->Add(genJetPt_bbarJets_C2);
  genJetPt_bJets_C1->Add(genJetPt_bbarJets_C1);

  TH1D *rg_pp = (TH1D*) genJetPt_bJets_pp->Clone("rg_pp");
  rg_pp->Divide(genJetPt_bJets_pp,genJetPt_allJets_pp,1,1,"B");

  TH1D *rg_C2 = (TH1D*) genJetPt_bJets_C2->Clone("rg_C2");
  rg_C2->Divide(genJetPt_bJets_C2,genJetPt_allJets_C2,1,1,"B");

  TH1D *rg_C1 = (TH1D*) genJetPt_bJets_C1->Clone("rg_C1");
  rg_C1->Divide(genJetPt_bJets_C1,genJetPt_allJets_C1,1,1,"B");

  

  

  rg_pp->SetMarkerSize(0);
  rg_pp->SetFillColorAlpha(kGray+2,0.6);
  rg_C2->SetMarkerSize(0);
  rg_C2->SetFillColorAlpha(kRed-4,0.6);
  rg_C1->SetMarkerSize(0);
  rg_C1->SetFillColorAlpha(kBlue-4,0.6);
  
  file_results_pp = TFile::Open("../../rootFiles/bFractionResults/bFractionResults_pp.root");
  file_results_C2 = TFile::Open("../../rootFiles/bFractionResults/bFractionResults_C2.root");
  file_results_C1 = TFile::Open("../../rootFiles/bFractionResults/bFractionResults_C1.root");
  
  file_results_pp->GetObject("r",bFractionResults_pp);
  file_results_C2->GetObject("r",bFractionResults_C2);
  file_results_C1->GetObject("r",bFractionResults_C1);

  bFractionResults_pp->SetLineColor(kBlack);
  bFractionResults_C2->SetLineColor(kRed-4);
  bFractionResults_C1->SetLineColor(kBlue-4);

  bFractionResults_pp->SetMarkerColor(kBlack);
  bFractionResults_C2->SetMarkerColor(kRed-4);
  bFractionResults_C1->SetMarkerColor(kBlue-4);
  
  bFractionResults_pp->SetLineWidth(2);
  bFractionResults_C2->SetLineWidth(2);
  bFractionResults_C1->SetLineWidth(2);

  double msize = 1.2;

  bFractionResults_pp->SetMarkerSize(msize);
  bFractionResults_C2->SetMarkerSize(msize);
  bFractionResults_C1->SetMarkerSize(msize);

  bFractionResults_pp->SetMarkerStyle(22);
  bFractionResults_C2->SetMarkerStyle(20);
  bFractionResults_C1->SetMarkerStyle(21);





  // calculate systematics and make corresponding histograms

  double sys_err_val_tot_pp_J2 = TMath::Sqrt(sys_cFraction_PYTHIA_J2*sys_cFraction_PYTHIA_J2
					     + sys_lowerBound_pp_J2 * sys_lowerBound_pp_J2
					     + sys_bEnhance_PYTHIA_J2 * sys_bEnhance_PYTHIA_J2
					     + sys_cEnhance_PYTHIA_J2 * sys_cEnhance_PYTHIA_J2
					     + sys_JER_PYTHIA_J2 * sys_JER_PYTHIA_J2); 

  double sys_err_val_tot_pp_J3 = TMath::Sqrt(sys_cFraction_PYTHIA_J3*sys_cFraction_PYTHIA_J3
					     + sys_lowerBound_pp_J3 * sys_lowerBound_pp_J3
					     + sys_bEnhance_PYTHIA_J3 * sys_bEnhance_PYTHIA_J3
					     + sys_cEnhance_PYTHIA_J3 * sys_cEnhance_PYTHIA_J3
					     + sys_JER_PYTHIA_J3 * sys_JER_PYTHIA_J3); 

  double sys_err_val_tot_pp_J4 = TMath::Sqrt(sys_cFraction_PYTHIA_J4*sys_cFraction_PYTHIA_J4
					     + sys_lowerBound_pp_J4 * sys_lowerBound_pp_J4
					     + sys_bEnhance_PYTHIA_J4 * sys_bEnhance_PYTHIA_J4
					     + sys_cEnhance_PYTHIA_J4 * sys_cEnhance_PYTHIA_J4
					     + sys_JER_PYTHIA_J4 * sys_JER_PYTHIA_J4); 

  double sys_err_val_tot_C2_J2 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J2*sys_cFraction_PYTHIAHYDJET_C2_J2 +
					     sys_lowerBound_PbPb_C2_J2*sys_lowerBound_PbPb_C2_J2 +
					     sys_bEnhance_PYTHIAHYDJET_C2_J2*sys_bEnhance_PYTHIAHYDJET_C2_J2 +
					     sys_cEnhance_PYTHIAHYDJET_C2_J2*sys_cEnhance_PYTHIAHYDJET_C2_J2 +
					     sys_JER_PYTHIAHYDJET_C2_J2*sys_JER_PYTHIAHYDJET_C2_J2);
  double sys_err_val_tot_C2_J3 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J3*sys_cFraction_PYTHIAHYDJET_C2_J3 +
					     sys_lowerBound_PbPb_C2_J3*sys_lowerBound_PbPb_C2_J3 +
					     sys_bEnhance_PYTHIAHYDJET_C2_J3*sys_bEnhance_PYTHIAHYDJET_C2_J3 +
					     sys_cEnhance_PYTHIAHYDJET_C2_J3*sys_cEnhance_PYTHIAHYDJET_C2_J3 +
					     sys_JER_PYTHIAHYDJET_C2_J3*sys_JER_PYTHIAHYDJET_C2_J3);
  double sys_err_val_tot_C2_J4 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C2_J4*sys_cFraction_PYTHIAHYDJET_C2_J4 +
					     sys_lowerBound_PbPb_C2_J4*sys_lowerBound_PbPb_C2_J4 +
					     sys_bEnhance_PYTHIAHYDJET_C2_J4*sys_bEnhance_PYTHIAHYDJET_C2_J4 +
					     sys_cEnhance_PYTHIAHYDJET_C2_J4*sys_cEnhance_PYTHIAHYDJET_C2_J4 +
					     sys_JER_PYTHIAHYDJET_C2_J4*sys_JER_PYTHIAHYDJET_C2_J4);

  double sys_err_val_tot_C1_J2 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J2*sys_cFraction_PYTHIAHYDJET_C1_J2 +
					     sys_lowerBound_PbPb_C1_J2*sys_lowerBound_PbPb_C1_J2 +
					     sys_bEnhance_PYTHIAHYDJET_C1_J2*sys_bEnhance_PYTHIAHYDJET_C1_J2 +
					     sys_cEnhance_PYTHIAHYDJET_C1_J2*sys_cEnhance_PYTHIAHYDJET_C1_J2 +
					     sys_JER_PYTHIAHYDJET_C1_J2*sys_JER_PYTHIAHYDJET_C1_J2);
  double sys_err_val_tot_C1_J3 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J3*sys_cFraction_PYTHIAHYDJET_C1_J3 +
					     sys_lowerBound_PbPb_C1_J3*sys_lowerBound_PbPb_C1_J3 +
					     sys_bEnhance_PYTHIAHYDJET_C1_J3*sys_bEnhance_PYTHIAHYDJET_C1_J3 +
					     sys_cEnhance_PYTHIAHYDJET_C1_J3*sys_cEnhance_PYTHIAHYDJET_C1_J3 +
					     sys_JER_PYTHIAHYDJET_C1_J3*sys_JER_PYTHIAHYDJET_C1_J3);
  double sys_err_val_tot_C1_J4 = TMath::Sqrt(sys_cFraction_PYTHIAHYDJET_C1_J4*sys_cFraction_PYTHIAHYDJET_C1_J4 +
					     sys_lowerBound_PbPb_C1_J4*sys_lowerBound_PbPb_C1_J4 +
					     sys_bEnhance_PYTHIAHYDJET_C1_J4*sys_bEnhance_PYTHIAHYDJET_C1_J4 +
					     sys_cEnhance_PYTHIAHYDJET_C1_J4*sys_cEnhance_PYTHIAHYDJET_C1_J4 +
					     sys_JER_PYTHIAHYDJET_C1_J4*sys_JER_PYTHIAHYDJET_C1_J4);

  double sys_err_vals_pp[3] = {sys_err_val_tot_pp_J2, sys_err_val_tot_pp_J3, sys_err_val_tot_pp_J4};
  double sys_err_vals_C2[3] = {sys_err_val_tot_C2_J2, sys_err_val_tot_C2_J3, sys_err_val_tot_C2_J4};
  double sys_err_vals_C1[3] = {sys_err_val_tot_C1_J2, sys_err_val_tot_C1_J3, sys_err_val_tot_C1_J4};

  TH1D *sys_err_pp = (TH1D*) bFractionResults_pp->Clone("sys_err_pp");
  TH1D *sys_err_C2 = (TH1D*) bFractionResults_C2->Clone("sys_err_C2");
  TH1D *sys_err_C1 = (TH1D*) bFractionResults_C1->Clone("sys_err_C1");

  for(int i = 0; i < 4; i++){
    sys_err_pp->SetBinError(i+1,sys_err_vals_pp[i]*bFractionResults_pp->GetBinContent(i+1));
    sys_err_C2->SetBinError(i+1,sys_err_vals_C2[i]*bFractionResults_C2->GetBinContent(i+1));
    sys_err_C1->SetBinError(i+1,sys_err_vals_C1[i]*bFractionResults_C1->GetBinContent(i+1));
  }

  sys_err_C2->SetFillStyle(3354);
  sys_err_C1->SetFillStyle(3345);

  sys_err_pp->SetFillColorAlpha(kGray,0.6);
  sys_err_C2->SetFillColorAlpha(kRed-4,0.6);
  sys_err_C1->SetFillColorAlpha(kBlue-4,0.6);

  sys_err_pp->SetMarkerSize(0);
  sys_err_C2->SetMarkerSize(0);
  sys_err_C1->SetMarkerSize(0);

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0,1,1);
  p1->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.2);
  p1->Draw();
  p1->cd();
  sys_err_pp->SetStats(0);
  sys_err_pp->SetTitle("");
  double tsize = 0.042;
  double lsize = 0.032;
  sys_err_pp->GetYaxis()->SetTitleSize(tsize);
  sys_err_pp->GetYaxis()->SetLabelSize(lsize);
  sys_err_pp->GetXaxis()->SetTitleSize(tsize);
  sys_err_pp->GetXaxis()->SetLabelSize(lsize);
  sys_err_pp->GetYaxis()->SetTitle("inclusive #font[52]{b}-jet fraction");
  sys_err_pp->GetXaxis()->SetTitle("Jet #font[52]{p}_{T} [GeV]");
  sys_err_pp->GetYaxis()->SetRangeUser(0,0.07);
  sys_err_pp->Draw("e2");
  bFractionResults_pp->Draw("same");
  rg_pp->Draw("e3 same");
  rg_C2->Draw("e3 same");
  rg_C1->Draw("e3 same");
  sys_err_C2->Draw("e2 same");
  bFractionResults_C2->Draw("same");
  sys_err_C1->Draw("e2 same");
  bFractionResults_C1->Draw("same");
  


  TLegend *leg1 = new TLegend(0.62,0.75,0.88,0.88);
  leg1->SetBorderSize(0.0);
  leg1->SetTextSize(0.03);
  leg1->AddEntry(bFractionResults_pp,"pp","pl");
  leg1->AddEntry(bFractionResults_C2,"PbPb 30-90%","pl");
  leg1->AddEntry(bFractionResults_C1,"PbPb 0-30%","pl");
  leg1->Draw();

  TLegend *leg3 = new TLegend(0.22,0.75,0.48,0.88);
  leg3->SetBorderSize(0.0);
  leg3->SetTextSize(0.03);
  leg3->AddEntry(rg_pp,"PYTHIA","f");
  leg3->AddEntry(rg_C2,"PYTHIA+HYDJET 30-90%","f");
  leg3->AddEntry(rg_C1,"PYTHIA+HYDJET 0-30%","f");
  leg3->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.22,0.92,"CMS #scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  la->DrawLatexNDC(0.64,0.92,"#sqrt{s} = 5.02 TeV");


  
  TH1D *rr_C2_pp = (TH1D*) bFractionResults_C2->Clone("rr_C2_pp");
  rr_C2_pp->Divide(bFractionResults_C2,bFractionResults_pp,1,1,"");
  TH1D *rr_C1_pp = (TH1D*) bFractionResults_C1->Clone("rr_C1_pp");
  rr_C1_pp->Divide(bFractionResults_C1,bFractionResults_pp,1,1,"");

  TH1D *sys_rr_C2_pp = (TH1D*) sys_err_C2->Clone("sys_rr_C2_pp");
  sys_rr_C2_pp->Divide(sys_err_C2,sys_err_pp,1,1,"");
  TH1D *sys_rr_C1_pp = (TH1D*) sys_err_C1->Clone("sys_rr_C1_pp");
  sys_rr_C1_pp->Divide(sys_err_C1,sys_err_pp,1,1,"");

  TCanvas *c2 = new TCanvas("c2","c2",700,700);
  c2->cd();
  TPad *p2 = new TPad("p2","p2",0,0,1,1);
  p2->SetLeftMargin(0.2);
  p2->SetBottomMargin(0.2);
  p2->Draw();
  p2->cd();
  sys_rr_C2_pp->GetYaxis()->SetTitle("Ratio to pp");
  sys_rr_C2_pp->GetYaxis()->SetRangeUser(0,2);
  sys_rr_C2_pp->Draw("e2");
  rr_C2_pp->Draw("same");
  sys_rr_C1_pp->Draw("same e2");
  rr_C1_pp->Draw("same");

  la->SetTextFont(62);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.22,0.92,"CMS #scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  la->DrawLatexNDC(0.64,0.92,"#sqrt{s} = 5.02 TeV");

  TLegend *leg2 = new TLegend(0.45,0.75,0.75,0.88);
  leg2->SetBorderSize(0.0);
  leg2->SetTextSize(0.036);
  leg2->AddEntry(rr_C2_pp,"PbPb 30-90%","pl");
  leg2->AddEntry(rr_C1_pp,"PbPb 0-30%","pl");
  leg2->Draw();

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(60,1,200,1);

  
  c1->SaveAs("../../figures/results/bFraction.pdf");
  c2->SaveAs("../../figures/results/resultRatio.pdf");


}
