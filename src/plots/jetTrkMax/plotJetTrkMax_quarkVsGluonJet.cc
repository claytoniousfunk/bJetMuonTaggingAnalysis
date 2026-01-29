
#include "plotJetTrkMax_quarkVsGluonJet.h"

TH1D* divideByBinwidth(TH1D* h_in){

  for(int k = 0; k < h_in->GetSize(); k++){

    double value = h_in->GetBinContent(k);
    double error = h_in->GetBinError(k);
    double width = h_in->GetBinWidth(k);

    if(width != 0){

      h_in->SetBinContent(k,value/width);
      h_in->SetBinError(k,error/width);

    }

  }

  return h_in;

}

void stylize_data(TH1D *h1){

  h1->Scale(1./h1->Integral());

  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);

  h1->SetLineWidth(2);
  h1->SetMarkerStyle(20);
  h1->SetStats(0);  
  h1->SetTitle("");

  double yTitleOffset = 0.3;
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h1->GetYaxis()->SetNdivisions(yNDivisions);

}

void stylize_mc(TH1D *h1){

  h1->Scale(1./h1->Integral());

  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);

  double alpha = 0.6;
  h1->SetFillColorAlpha(kGray,alpha);
  h1->SetLineWidth(2);
  h1->SetMarkerStyle(24);
  h1->SetStats(0);  
  h1->SetTitle("");

  double yTitleOffset = 0.3;
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h1->GetYaxis()->SetNdivisions(yNDivisions);

}

void stylize_templates(TH1D *hq, TH1D *hg){

  hq->Scale(1./hq->Integral());
  hg->Scale(1./hg->Integral());

  hq->SetLineColor(kRed-4);
  hg->SetLineColor(kBlue-4);

  double alpha = 0.6;
  hq->SetFillColorAlpha(kRed-4,alpha);
  hg->SetFillColorAlpha(kBlue-4,alpha);

  hq->SetLineWidth(2);
  hg->SetLineWidth(2);

  hq->SetMarkerColor(kRed-4);
  hg->SetMarkerColor(kBlue-4);

  hq->SetMarkerStyle(20);
  hg->SetMarkerStyle(24);

  hq->SetStats(0);
  hg->SetStats(0);

  hq->SetTitle("");
  hg->SetTitle("");

  double yTitleOffset = 0.3;
  hq->GetYaxis()->SetTitleOffset(yTitleOffset);
  hg->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  hq->GetYaxis()->SetNdivisions(yNDivisions);
  hg->GetYaxis()->SetNdivisions(yNDivisions);

}

void set_dR_range(TH1D *h1){

  double lowerLimit = 0.0;
  double upperLimit = 0.3;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void set_pTrel_range(TH1D *h1){

  double lowerLimit = 0.0;
  double upperLimit = 5.0;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void normalize_jetPt(TH1D *h1){

  double jetPtLow = 200.0;
  double jetPtHigh = 500.0;
  h1->Scale(1./h1->Integral(h1->GetXaxis()->FindBin(jetPtLow),h1->GetXaxis()->FindBin(jetPtHigh)));
  
}

TString getJetPtString(int j){
  TString result = "";
  if(j == 1) result = "80 < #it{p}_{T}^{jet} (GeV) < 100, |#it{#eta}^{jet}| < 1.6";
  else if(j == 2) result = "100 < #it{p}_{T}^{jet} (GeV) < 120, |#it{#eta}^{jet}| < 1.6";
  else if(j == 3) result = "120 < #it{p}_{T}^{jet} (GeV) < 150, |#it{#eta}^{jet}| < 1.6";
  else if(j == 4) result = "150 < #it{p}_{T}^{jet} (GeV) < 200, |#it{#eta}^{jet}| < 1.6";
  else if(j == 5) result = "200 < #it{p}_{T}^{jet} (GeV) < 300, |#it{#eta}^{jet}| < 1.6";
  else{std::cout << "ERROR: choose j between 1 and 5\n";};
  return result;
}

double fitFxn_dR(double *x, double *par){
  double dR = x[0];
  int bin = h_fit_qJets->FindBin(dR);
  double qFraction = (par[0])*h_fit_qJets->GetBinContent(bin);
  double gFraction = (1-par[0])*h_fit_gJets->GetBinContent(bin);
  return qFraction + gFraction;
}




void plotJetTrkMax_quarkVsGluonJet(int j = 1){

  CMSString = "#font[62]{CMS}  #font[52]{Preliminary}";
  energyString = "#sqrt{#it{s}} = 5.02 TeV";
  jetPtString = getJetPtString(j);
  hadronPtString = "#it{p}_{T}^{h} > 14 GeV, |#it{#eta}^{h}| < 2.0";

  li = new TLine();
  la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);

  file_pp_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-7-22_jet60.root");
  file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/jetTrkMax/pp_jetTrkMax_trkPt-14_jet60_2025-07-22.root");

  if(!file_pp_mc || !file_pp_data){
    std::cout << "error retrieving file! exiting.\n";
    return;
  }

  // retrieve jetPt
  file_pp_mc->GetObject("h_jetPt",h_jetPt_pp_mc);
  file_pp_data->GetObject("h_jetPt",h_jetPt_pp_data);

  file_pp_mc->GetObject(Form("h_jetTrkMaxDR_J%i",j),h_dR_pp_mc);
  file_pp_mc->GetObject(Form("h_jetTrkMaxDR_qJets_J%i",j),h_dR_pp_qJets_mc);
  file_pp_mc->GetObject(Form("h_jetTrkMaxDR_gJets_J%i",j),h_dR_pp_gJets_mc);  
  file_pp_data->GetObject(Form("h_jetTrkMaxDR_J%i",j),h_dR_pp_data);

  file_pp_mc->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_mc);
  file_pp_data->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_data);

  stylize_data(h_jetPt_pp_data);
  normalize_jetPt(h_jetPt_pp_data);

  stylize_data(h_dR_pp_data);
  set_dR_range(h_dR_pp_data);
  
  stylize_data(h_pTrel_pp_data);
  set_pTrel_range(h_pTrel_pp_data);

  stylize_mc(h_jetPt_pp_mc);
  normalize_jetPt(h_jetPt_pp_mc);
  
  stylize_mc(h_dR_pp_mc);
  set_dR_range(h_dR_pp_mc);
  
  stylize_mc(h_pTrel_pp_mc);
  set_pTrel_range(h_pTrel_pp_mc);

  stylize_templates(h_dR_pp_qJets_mc,h_dR_pp_gJets_mc);
  set_dR_range(h_dR_pp_qJets_mc);
  set_dR_range(h_dR_pp_gJets_mc);
 
  // h_dR_pp_data = (TH1D*) h_dR_pp_data->Rebin(Nedge_dR-1,"h_dR_pp_data",dR_axis);
  // h_dR_pp_mc = (TH1D*) h_dR_pp_mc->Rebin(Nedge_dR-1,"h_dR_pp_mc",dR_axis);
  
  // divideByBinwidth(h_dR_pp_data);
  // divideByBinwidth(h_dR_pp_mc);

  h_pTrel_pp_data = (TH1D*) h_pTrel_pp_data->Rebin(Nedge_pTrel-1,"h_pTrel_pp_data",pTrel_axis);
  h_pTrel_pp_mc = (TH1D*) h_pTrel_pp_mc->Rebin(Nedge_pTrel-1,"h_pTrel_pp_mc",pTrel_axis);  

  divideByBinwidth(h_pTrel_pp_data);
  divideByBinwidth(h_pTrel_pp_mc); 

  r_jetPt_pp = (TH1D*) h_jetPt_pp_data->Clone("r_jetPt_pp"); 
  r_dR_pp = (TH1D*) h_dR_pp_data->Clone("r_dR_pp");
  r_dR_temp = (TH1D*) h_dR_pp_qJets_mc->Clone("r_dR_temp");
  r_pTrel_pp = (TH1D*) h_pTrel_pp_data->Clone("r_pTrel_pp");
 
  r_jetPt_pp->Divide(h_jetPt_pp_data,h_jetPt_pp_mc,1,1,"");  
  r_dR_pp->Divide(h_dR_pp_data,h_dR_pp_mc,1,1,"");
  r_dR_temp->Divide(h_dR_pp_qJets_mc,h_dR_pp_gJets_mc,1,1,"");
  r_pTrel_pp->Divide(h_pTrel_pp_data,h_pTrel_pp_mc,1,1,"");
 
  leg_mc = new TLegend(0.6,0.3,0.89,0.6);
  leg_mc->SetFillStyle(0);
  leg_mc->SetBorderSize(0);
  leg_mc->SetTextSize(0.04);
  leg_mc->AddEntry(h_jetPt_pp_mc,"PYTHIA","p");
  leg_mc->AddEntry(h_jetPt_pp_data,"pp","p");

  leg_temp = new TLegend(0.6,0.3,0.89,0.6);
  leg_temp->SetFillStyle(0);
  leg_temp->SetBorderSize(0);
  leg_temp->SetTextSize(0.04);
  leg_temp->AddEntry(h_dR_pp_qJets_mc,"Quark Jets","p");
  leg_temp->AddEntry(h_dR_pp_gJets_mc,"Gluon Jets","p");



  
  subTitleSize = 0.08;
  subLabelSize = 0.06;

  // Draw
  TCanvas *canv_jetPt = new TCanvas("canv_jetPt","jetPt",700,700);
  canv_jetPt->cd();
  TPad *pad_jetPt_1 = new TPad("pad_jetPt_1","pad_jetPt_1",0,0.4,1,1);
  TPad *pad_jetPt_2 = new TPad("pad_jetPt_2","pad_jetPt_2",0,0,1,0.4);
  pad_jetPt_1->SetLeftMargin(0.1);
  pad_jetPt_2->SetLeftMargin(0.1);
  pad_jetPt_1->SetRightMargin(0.1);
  pad_jetPt_2->SetRightMargin(0.1);
  pad_jetPt_1->SetBottomMargin(0);
  pad_jetPt_2->SetTopMargin(0);
  pad_jetPt_2->SetBottomMargin(0.2);
  pad_jetPt_1->Draw();
  pad_jetPt_2->Draw();
  pad_jetPt_1->cd();
  h_jetPt_pp_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_jetPt_pp_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_jetPt_pp_data->GetYaxis()->SetTitleOffset(0.9);
  h_jetPt_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_pp_data->Draw();
  h_jetPt_pp_mc->Draw("same");
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_jetPt_2->cd();
  r_jetPt_pp->GetYaxis()->SetTitle("Data / MC");
  r_jetPt_pp->GetYaxis()->SetTitleSize(subTitleSize);
  r_jetPt_pp->GetYaxis()->SetLabelSize(subLabelSize);
  r_jetPt_pp->GetYaxis()->SetRangeUser(0.3,1.7);
  r_jetPt_pp->GetYaxis()->SetTitleOffset(0.55);
  r_jetPt_pp->GetXaxis()->SetTitleSize(subTitleSize);
  r_jetPt_pp->GetXaxis()->SetLabelSize(subLabelSize);
  r_jetPt_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  r_jetPt_pp->Draw();
  li->SetLineStyle(7);
  li->DrawLine(20,1,500,1);
  canv_jetPt->SaveAs("./figures/quarkVsGluonJets/jetPt.pdf");


  TCanvas *canv_dR = new TCanvas("canv_dR","dR",700,700);
  canv_dR->cd();
  TPad *pad_dR_1 = new TPad("pad_dR_1","pad_dR_1",0,0.4,1,1);
  TPad *pad_dR_2 = new TPad("pad_dR_2","pad_dR_2",0,0,1,0.4);
  pad_dR_1->SetLeftMargin(0.1);
  pad_dR_2->SetLeftMargin(0.1);
  pad_dR_1->SetRightMargin(0.1);
  pad_dR_2->SetRightMargin(0.1);
  pad_dR_1->SetBottomMargin(0);
  pad_dR_2->SetTopMargin(0);
  pad_dR_2->SetBottomMargin(0.2);
  pad_dR_1->Draw();
  pad_dR_2->Draw();
  pad_dR_1->cd();
  h_dR_pp_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_pp_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_pp_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#DeltaR [GeV^{-1}]");
  h_dR_pp_data->GetYaxis()->SetRangeUser(0,0.1);
  h_dR_pp_data->Draw();
  h_dR_pp_mc->Draw("same");
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_dR_2->cd();
  r_dR_pp->GetYaxis()->SetTitle("Data / MC");
  r_dR_pp->GetYaxis()->SetTitleSize(subTitleSize);
  r_dR_pp->GetYaxis()->SetLabelSize(subLabelSize);
  r_dR_pp->GetYaxis()->SetRangeUser(0.3,1.7);
  r_dR_pp->GetYaxis()->SetTitleOffset(0.55);
  r_dR_pp->GetXaxis()->SetTitle("#DeltaR(leading-hadron,jet)");
  r_dR_pp->GetXaxis()->SetTitleSize(subTitleSize);
  r_dR_pp->GetXaxis()->SetLabelSize(subLabelSize);
  r_dR_pp->Draw();
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  canv_dR->SaveAs(Form("./figures/quarkVsGluonJets/dR_J%i.pdf",j));

  TCanvas *canv_dRtemp = new TCanvas("canv_dRtemp","dRtemp",700,700);
  canv_dRtemp->cd();
  TPad *pad_dRtemp_1 = new TPad("pad_dRtemp_1","pad_dRtemp_1",0,0.4,1,1);
  TPad *pad_dRtemp_2 = new TPad("pad_dRtemp_2","pad_dRtemp_2",0,0,1,0.4);
  pad_dRtemp_1->SetLeftMargin(0.1);
  pad_dRtemp_2->SetLeftMargin(0.1);
  pad_dRtemp_1->SetRightMargin(0.1);
  pad_dRtemp_2->SetRightMargin(0.1);
  pad_dRtemp_1->SetBottomMargin(0);
  pad_dRtemp_2->SetTopMargin(0);
  pad_dRtemp_2->SetBottomMargin(0.2);
  pad_dRtemp_1->Draw();
  pad_dRtemp_2->Draw();
  pad_dRtemp_1->cd();
  h_dR_pp_qJets_mc->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_pp_qJets_mc->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_pp_qJets_mc->GetYaxis()->SetTitleOffset(0.9);
  h_dR_pp_qJets_mc->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#DeltaR [GeV^{-1}]");
  h_dR_pp_qJets_mc->GetYaxis()->SetRangeUser(0,0.1);
  h_dR_pp_qJets_mc->Draw();
  h_dR_pp_gJets_mc->Draw("same");
  leg_temp->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_dRtemp_2->cd();
  r_dR_temp->GetYaxis()->SetTitle("Quark / Gluon");
  r_dR_temp->GetYaxis()->SetTitleSize(subTitleSize);
  r_dR_temp->GetYaxis()->SetLabelSize(subLabelSize);
  r_dR_temp->GetYaxis()->SetRangeUser(0.3,1.7);
  r_dR_temp->GetYaxis()->SetTitleOffset(0.55);
  r_dR_temp->GetXaxis()->SetTitle("#DeltaR(leading-hadron,jet)");
  r_dR_temp->GetXaxis()->SetTitleSize(subTitleSize);
  r_dR_temp->GetXaxis()->SetLabelSize(subLabelSize);
  r_dR_temp->Draw();
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  canv_dRtemp->SaveAs(Form("./figures/quarkVsGluonJets/dRtemp_J%i.pdf",j));


  //h_fit_pp = (TH1D*) h_dR_pp_mc->Clone("h_fit_pp");
  h_fit_pp = (TH1D*) h_dR_pp_data->Clone("h_fit_pp");
  h_fit_qJets = (TH1D*) h_dR_pp_qJets_mc->Clone("h_fit_qJets");
  h_fit_gJets = (TH1D*) h_dR_pp_gJets_mc->Clone("h_fit_gJets");
  
  int numPar = 1;
  TF1 *func = new TF1("func",fitFxn_dR,0,0.3,numPar);
  func->SetParameter(0,0.5);
  func->SetParLimits(0,0,1);

  h_fit_pp->Fit(func,"M R","N",0,0.3);

  double qFractionFromFit = func->GetParameter(0);
  double gFractionFromFit = 1. - qFractionFromFit;

  std::cout << "quark fraction = " << qFractionFromFit << "\n";
  std::cout << "gluon fraction = " << gFractionFromFit << "\n";

  h_fit_pp_draw = (TH1D*) h_fit_pp->Clone("h_fit_pp_draw");
  h_fit_qJets_draw = (TH1D*) h_fit_qJets->Clone("h_fit_qJets_draw");
  h_fit_gJets_draw = (TH1D*) h_fit_gJets->Clone("h_fit_gJets_draw");
  set_dR_range(h_fit_pp_draw);
  set_dR_range(h_fit_qJets_draw);
  set_dR_range(h_fit_gJets_draw);
  
  h_fit_pp_draw->Scale(1. / h_fit_pp_draw->Integral());
  h_fit_qJets_draw->Scale(qFractionFromFit / h_fit_qJets_draw->Integral());
  h_fit_gJets_draw->Scale(gFractionFromFit / h_fit_gJets_draw->Integral());

  h_stack = new THStack("h_stack","");
  h_stack->Add(h_fit_gJets_draw);
  h_stack->Add(h_fit_qJets_draw);
  h_stack_histo_rep = (TH1D*) h_fit_gJets_draw->Clone("h_stack_histo_rep");
  h_stack_histo_rep->Add(h_fit_qJets_draw);
  
  r_fit = (TH1D*) h_fit_pp_draw->Clone("r_fit");
  r_fit->Divide(h_fit_pp_draw,h_stack_histo_rep,1,1,"");
  
  TCanvas *canv_fit = new TCanvas("canv_fit","fit",700,700);
  canv_fit->cd();
  TPad *pad_fit_1 = new TPad("pad_fit_1","pad_fit_1",0,0.4,1,1);
  TPad *pad_fit_2 = new TPad("pad_fit_2","pad_fit_2",0,0,1,0.4);
  pad_fit_1->SetLeftMargin(0.1);
  pad_fit_2->SetLeftMargin(0.1);
  pad_fit_1->SetRightMargin(0.1);
  pad_fit_2->SetRightMargin(0.1);
  pad_fit_1->SetBottomMargin(0);
  pad_fit_2->SetTopMargin(0);
  pad_fit_2->SetBottomMargin(0.2);
  pad_fit_1->Draw();
  pad_fit_2->Draw();
  pad_fit_1->cd();
  h_fit_pp_draw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_fit_pp_draw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_fit_pp_draw->GetYaxis()->SetTitleOffset(0.9);
  h_fit_pp_draw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#DeltaR [GeV^{-1}]");
  h_fit_pp_draw->GetYaxis()->SetRangeUser(0,0.1);
  h_fit_pp_draw->Draw("ep");
  h_stack->Draw("hist same");
  leg_temp->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.5,0.22,Form("quark fraction = %2.2f%%",100.*qFractionFromFit));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.5,0.14,Form("gluon fraction = %2.2f%%",100.*gFractionFromFit));
  la->SetTextColor(kBlack);
  pad_fit_2->cd();
  r_fit->GetYaxis()->SetTitle("Data / Fit  ");
  r_fit->GetYaxis()->SetTitleSize(subTitleSize);
  r_fit->GetYaxis()->SetLabelSize(subLabelSize);
  r_fit->GetYaxis()->SetRangeUser(0.3,1.7);
  r_fit->GetYaxis()->SetTitleOffset(0.55);
  r_fit->GetXaxis()->SetTitle("#DeltaR(leading-hadron,jet)");
  r_fit->GetXaxis()->SetTitleSize(subTitleSize);
  r_fit->GetXaxis()->SetLabelSize(subLabelSize);
  r_fit->Draw();
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  canv_fit->SaveAs(Form("./figures/quarkVsGluonJets/fit_J%i.pdf",j));

  
  

  TCanvas *canv_pTrel = new TCanvas("canv_pTrel","pTrel",700,700);
  canv_pTrel->cd();
  TPad *pad_pTrel_1 = new TPad("pad_pTrel_1","pad_pTrel_1",0,0.4,1,1);
  TPad *pad_pTrel_2 = new TPad("pad_pTrel_2","pad_pTrel_2",0,0,1,0.4);
  pad_pTrel_1->SetLeftMargin(0.1);
  pad_pTrel_2->SetLeftMargin(0.1);
  pad_pTrel_1->SetRightMargin(0.1);
  pad_pTrel_2->SetRightMargin(0.1);
  pad_pTrel_1->SetBottomMargin(0);
  pad_pTrel_2->SetTopMargin(0);
  pad_pTrel_2->SetBottomMargin(0.2);
  pad_pTrel_1->Draw();
  pad_pTrel_2->Draw();
  pad_pTrel_1->cd();
  h_pTrel_pp_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_pTrel_pp_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_pTrel_pp_data->GetYaxis()->SetTitleOffset(0.9);
  h_pTrel_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d(#DeltaR)");
  h_pTrel_pp_data->GetYaxis()->SetRangeUser(0,1.2);
  h_pTrel_pp_data->Draw();
  h_pTrel_pp_mc->Draw("same");
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_pTrel_2->cd();
  r_pTrel_pp->GetYaxis()->SetTitle("Data / MC");
  r_pTrel_pp->GetYaxis()->SetTitleSize(subTitleSize);
  r_pTrel_pp->GetYaxis()->SetLabelSize(subLabelSize);
  r_pTrel_pp->GetYaxis()->SetRangeUser(0.3,1.7);
  r_pTrel_pp->GetYaxis()->SetTitleOffset(0.55);
  r_pTrel_pp->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_pTrel_pp->GetXaxis()->SetTitleSize(subTitleSize);
  r_pTrel_pp->GetXaxis()->SetLabelSize(subLabelSize);
  r_pTrel_pp->Draw();
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_pTrel->SaveAs(Form("./figures/quarkVsGluonJets/pTrel_J%i.pdf",j)); 



  // 







  

  return;

  
}
