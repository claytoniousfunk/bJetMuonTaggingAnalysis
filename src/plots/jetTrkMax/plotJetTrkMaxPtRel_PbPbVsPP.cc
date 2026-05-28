
#include "plotJetTrkMaxPtRel_PbPbVsPP.h"

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


void stylize_data(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  h5->Scale(1./h5->Integral());

  h0->SetLineColor(kBlack);
  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlack);
  h3->SetLineColor(kBlack);
  h4->SetLineColor(kBlack);
  h5->SetLineColor(kBlack);

  h0->SetMarkerColor(kBlack);
  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlack);
  h3->SetMarkerColor(kBlack);
  h4->SetMarkerColor(kBlack);
  h5->SetMarkerColor(kBlack);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h0->SetMarkerStyle(24);
  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(20);
  h3->SetMarkerStyle(20);
  h4->SetMarkerStyle(20);
  h5->SetMarkerStyle(20);

  h0->SetStats(0);
  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  h5->SetStats(0);
  
  h0->SetTitle("");
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");
  h5->SetTitle("");


  double yTitleOffset = 0.3;
  h0->GetYaxis()->SetTitleOffset(yTitleOffset);
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);
  h4->GetYaxis()->SetTitleOffset(yTitleOffset);
  h5->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h0->GetYaxis()->SetNdivisions(yNDivisions);
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);
  h4->GetYaxis()->SetNdivisions(yNDivisions);
  h5->GetYaxis()->SetNdivisions(yNDivisions);

}


TString getJetPtString(int j){
  TString result = "";
  if(j == 1) result = "80 < #it{p}_{T}^{jet} (GeV) < 100";
  else if(j == 2) result = "100 < #it{p}_{T}^{jet} (GeV) < 120";
  else if(j == 3) result = "120 < #it{p}_{T}^{jet} (GeV) < 150";
  else if(j == 4) result = "150 < #it{p}_{T}^{jet} (GeV) < 200";
  else if(j == 5) result = "200 < #it{p}_{T}^{jet} (GeV) < 300";
  else result = "";
  return result;
}
void set_dR_range(TH1D *h1){

  double lowerLimit = 0.0;
  double upperLimit = 5.0;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void plotJetTrkMaxPtRel_PbPbVsPP(int j = 1){

  CMSString = "#font[62]{CMS}  #font[52]{Preliminary}";
  energyString = "#sqrt{#it{s}} = 5.02 TeV";
  jetPtString = getJetPtString(j);
  hadronPtString = "#it{p}_{T}^{h} > 14 GeV, |#it{#eta}^{h}| < 2.0";

  li = new TLine();
  la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);


  file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/jetTrkMax/pp_jetTrkMax_trkPt-14_jet60_2025-07-22.root");
  file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/jetTrkMax/PbPb_DiJet_onlyJets_withTrackMaxInfo_partial_jetTrkMax_trkPt-14_jet60_ultraFineCentBins_2025-08-04.root");

  if(!file_pp_data || !file_PbPb_data){
    std::cout << "error finding file! exiting\n";
    return;
  }

  

  file_pp_data->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_dR_pp_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C5J%i",j),h_dR_C5_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_dR_C4_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_dR_C3_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_dR_C2_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_dR_C1_data);

  h_dR_pp_data = (TH1D*) h_dR_pp_data->Rebin(Nedge_dR-1,"h_dR_pp_data",dR_axis);
  h_dR_C5_data = (TH1D*) h_dR_C5_data->Rebin(Nedge_dR-1,"h_dR_C5_data",dR_axis);
  h_dR_C4_data = (TH1D*) h_dR_C4_data->Rebin(Nedge_dR-1,"h_dR_C4_data",dR_axis);
  h_dR_C3_data = (TH1D*) h_dR_C3_data->Rebin(Nedge_dR-1,"h_dR_C3_data",dR_axis);
  h_dR_C2_data = (TH1D*) h_dR_C2_data->Rebin(Nedge_dR-1,"h_dR_C2_data",dR_axis);
  h_dR_C1_data = (TH1D*) h_dR_C1_data->Rebin(Nedge_dR-1,"h_dR_C1_data",dR_axis);


  divideByBinwidth(h_dR_pp_data);
  divideByBinwidth(h_dR_C5_data);
  divideByBinwidth(h_dR_C4_data);
  divideByBinwidth(h_dR_C3_data);
  divideByBinwidth(h_dR_C2_data);
  divideByBinwidth(h_dR_C1_data);

  stylize_data(h_dR_pp_data,h_dR_C5_data,h_dR_C4_data,h_dR_C3_data,h_dR_C2_data,h_dR_C1_data);

  set_dR_range(h_dR_pp_data);
  set_dR_range(h_dR_C5_data);
  set_dR_range(h_dR_C4_data);
  set_dR_range(h_dR_C3_data);
  set_dR_range(h_dR_C2_data);
  set_dR_range(h_dR_C1_data);

  r_C5 = (TH1D*) h_dR_C5_data->Clone("r_C5");
  r_C4 = (TH1D*) h_dR_C4_data->Clone("r_C4");
  r_C3 = (TH1D*) h_dR_C3_data->Clone("r_C3");
  r_C2 = (TH1D*) h_dR_C2_data->Clone("r_C2");
  r_C1 = (TH1D*) h_dR_C1_data->Clone("r_C1");

  r_C5->Divide(h_dR_C5_data,h_dR_pp_data,1,1,"");
  r_C4->Divide(h_dR_C4_data,h_dR_pp_data,1,1,"");
  r_C3->Divide(h_dR_C3_data,h_dR_pp_data,1,1,"");
  r_C2->Divide(h_dR_C2_data,h_dR_pp_data,1,1,"");
  r_C1->Divide(h_dR_C1_data,h_dR_pp_data,1,1,"");

  leg_C5 = new TLegend(0.5,0.3,0.84,0.6);
  leg_C5->SetFillStyle(0);
  leg_C5->SetBorderSize(0);
  leg_C5->SetTextSize(0.04);
  leg_C5->AddEntry(h_dR_pp_data,"pp","p");
  leg_C5->AddEntry(h_dR_C5_data,"PbPb 70-80%","p");

  leg_C4 = new TLegend(0.5,0.3,0.84,0.6);
  leg_C4->SetFillStyle(0);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.04);
  leg_C4->AddEntry(h_dR_pp_data,"pp","p");
  leg_C4->AddEntry(h_dR_C4_data,"PbPb 50-70%","p");

  leg_C3 = new TLegend(0.5,0.3,0.84,0.6);
  leg_C3->SetFillStyle(0);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.04);
  leg_C3->AddEntry(h_dR_pp_data,"pp","p");
  leg_C3->AddEntry(h_dR_C3_data,"PbPb 30-50%","p");

  leg_C2 = new TLegend(0.5,0.3,0.84,0.6);
  leg_C2->SetFillStyle(0);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.04);
  leg_C2->AddEntry(h_dR_pp_data,"pp","p");
  leg_C2->AddEntry(h_dR_C2_data,"PbPb 10-30%","p");

  leg_C1 = new TLegend(0.5,0.3,0.84,0.6);
  leg_C1->SetFillStyle(0);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.04);
  leg_C1->AddEntry(h_dR_pp_data,"pp","p");
  leg_C1->AddEntry(h_dR_C1_data,"PbPb 0-10%","p");
   

  subTitleSize = 0.08;
  subLabelSize = 0.06;

  
  TCanvas *canv_C5 = new TCanvas("canv_C5","C5",700,700);
  canv_C5->cd();
  TPad *pad_C5_1 = new TPad("pad_C5_1","pad_C5_1",0,0.4,1,1);
  TPad *pad_C5_2 = new TPad("pad_C5_2","pad_C5_2",0,0,1,0.4);
  pad_C5_1->SetLeftMargin(0.1);
  pad_C5_2->SetLeftMargin(0.1);
  pad_C5_1->SetRightMargin(0.1);
  pad_C5_2->SetRightMargin(0.1);
  pad_C5_1->SetBottomMargin(0);
  pad_C5_2->SetTopMargin(0);
  pad_C5_2->SetBottomMargin(0.2);
  pad_C5_1->Draw();
  pad_C5_2->Draw();
  pad_C5_1->cd();
  h_dR_C5_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_C5_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_C5_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_C5_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel}");
  h_dR_C5_data->GetYaxis()->SetRangeUser(0,0.35);
  h_dR_C5_data->Draw();
  h_dR_pp_data->Draw("same");
  leg_C5->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C5_2->cd();
  r_C5->GetYaxis()->SetTitle("PbPb / pp  ");
  r_C5->GetYaxis()->SetTitleSize(subTitleSize);
  r_C5->GetYaxis()->SetLabelSize(subLabelSize);
  r_C5->GetYaxis()->SetRangeUser(0.3,1.7);
  r_C5->GetYaxis()->SetTitleOffset(0.55);
  r_C5->GetXaxis()->SetTitle("#it{p}_{T}^{rel}(leading-hadron,jet)");
  r_C5->GetXaxis()->SetTitleSize(subTitleSize);
  r_C5->GetXaxis()->SetLabelSize(subLabelSize);
  r_C5->Draw();
  TF1 *fitFxn_C5 = new TF1("fitFxn_C5","pol1");
  r_C5->Fit(fitFxn_C5,"0");
  double p0_C5 = 0.;
  double p1_C5 = 0.;
  p0_C5 = fitFxn_C5->GetParameter(0);
  p1_C5 = fitFxn_C5->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C5,p1_C5));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C5->SaveAs(Form("./figures/jetTrkMaxDR_PbPbVsPP/C5_%i.pdf",j));



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
  h_dR_C4_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_C4_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_C4_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_C4_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel}");
  h_dR_C4_data->GetYaxis()->SetRangeUser(0,0.35);
  h_dR_C4_data->Draw();
  h_dR_pp_data->Draw("same");
  leg_C4->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C4_2->cd();
  r_C4->GetYaxis()->SetTitle("PbPb / pp  ");
  r_C4->GetYaxis()->SetTitleSize(subTitleSize);
  r_C4->GetYaxis()->SetLabelSize(subLabelSize);
  r_C4->GetYaxis()->SetRangeUser(0.3,1.7);
  r_C4->GetYaxis()->SetTitleOffset(0.55);
  r_C4->GetXaxis()->SetTitle("#it{p}_{T}^{rel}(leading-hadron,jet)");
  r_C4->GetXaxis()->SetTitleSize(subTitleSize);
  r_C4->GetXaxis()->SetLabelSize(subLabelSize);
  r_C4->Draw();
  TF1 *fitFxn_C4 = new TF1("fitFxn_C4","pol1");
  r_C4->Fit(fitFxn_C4,"0");
  double p0_C4 = 0.;
  double p1_C4 = 0.;
  p0_C4 = fitFxn_C4->GetParameter(0);
  p1_C4 = fitFxn_C4->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C4,p1_C4));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C4->SaveAs(Form("./figures/jetTrkMaxDR_PbPbVsPP/C4_%i.pdf",j));



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
  h_dR_C3_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_C3_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_C3_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_C3_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel}");
  h_dR_C3_data->GetYaxis()->SetRangeUser(0,0.35);
  h_dR_C3_data->Draw();
  h_dR_pp_data->Draw("same");
  leg_C3->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C3_2->cd();
  r_C3->GetYaxis()->SetTitle("PbPb / pp  ");
  r_C3->GetYaxis()->SetTitleSize(subTitleSize);
  r_C3->GetYaxis()->SetLabelSize(subLabelSize);
  r_C3->GetYaxis()->SetRangeUser(0.3,1.7);
  r_C3->GetYaxis()->SetTitleOffset(0.55);
  r_C3->GetXaxis()->SetTitle("#it{p}_{T}^{rel}(leading-hadron,jet)");
  r_C3->GetXaxis()->SetTitleSize(subTitleSize);
  r_C3->GetXaxis()->SetLabelSize(subLabelSize);
  r_C3->Draw();
  TF1 *fitFxn_C3 = new TF1("fitFxn_C3","pol1");
  r_C3->Fit(fitFxn_C3,"0");
  double p0_C3 = 0.;
  double p1_C3 = 0.;
  p0_C3 = fitFxn_C3->GetParameter(0);
  p1_C3 = fitFxn_C3->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C3,p1_C3));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C3->SaveAs(Form("./figures/jetTrkMaxDR_PbPbVsPP/C3_%i.pdf",j));



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
  h_dR_C2_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_C2_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_C2_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_C2_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel}");
  h_dR_C2_data->GetYaxis()->SetRangeUser(0,0.35);
  h_dR_C2_data->Draw();
  h_dR_pp_data->Draw("same");
  leg_C2->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C2_2->cd();
  r_C2->GetYaxis()->SetTitle("PbPb / pp  ");
  r_C2->GetYaxis()->SetTitleSize(subTitleSize);
  r_C2->GetYaxis()->SetLabelSize(subLabelSize);
  r_C2->GetYaxis()->SetRangeUser(0.3,1.7);
  r_C2->GetYaxis()->SetTitleOffset(0.55);
  r_C2->GetXaxis()->SetTitle("#it{p}_{T}^{rel}(leading-hadron,jet)");
  r_C2->GetXaxis()->SetTitleSize(subTitleSize);
  r_C2->GetXaxis()->SetLabelSize(subLabelSize);
  r_C2->Draw();
  TF1 *fitFxn_C2 = new TF1("fitFxn_C2","pol1");
  r_C2->Fit(fitFxn_C2,"0");
  double p0_C2 = 0.;
  double p1_C2 = 0.;
  p0_C2 = fitFxn_C2->GetParameter(0);
  p1_C2 = fitFxn_C2->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C2,p1_C2));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C2->SaveAs(Form("./figures/jetTrkMaxDR_PbPbVsPP/C2_%i.pdf",j));


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
  h_dR_C1_data->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  h_dR_C1_data->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  h_dR_C1_data->GetYaxis()->SetTitleOffset(0.9);
  h_dR_C1_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel}");
  h_dR_C1_data->GetYaxis()->SetRangeUser(0,0.35);
  h_dR_C1_data->Draw();
  h_dR_pp_data->Draw("same");
  leg_C1->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C1_2->cd();
  r_C1->GetYaxis()->SetTitle("PbPb / pp  ");
  r_C1->GetYaxis()->SetTitleSize(subTitleSize);
  r_C1->GetYaxis()->SetLabelSize(subLabelSize);
  r_C1->GetYaxis()->SetRangeUser(0.3,1.7);
  r_C1->GetYaxis()->SetTitleOffset(0.55);
  r_C1->GetXaxis()->SetTitle("#it{p}_{T}^{rel}(leading-hadron,jet)");
  r_C1->GetXaxis()->SetTitleSize(subTitleSize);
  r_C1->GetXaxis()->SetLabelSize(subLabelSize);
  r_C1->Draw();
  TF1 *fitFxn_C1 = new TF1("fitFxn_C1","pol1");
  r_C1->Fit(fitFxn_C1,"0");
  double p0_C1 = 0.;
  double p1_C1 = 0.;
  p0_C1 = fitFxn_C1->GetParameter(0);
  p1_C1 = fitFxn_C1->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C1,p1_C1));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C1->SaveAs(Form("./figures/jetTrkMaxDR_PbPbVsPP/C1_%i.pdf",j));
  
   
}
