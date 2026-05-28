
#include "plotJetTrkMaxPtRel_proj.h"

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

  h0->SetMarkerStyle(20);
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

void stylize_raw(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  h5->Scale(1./h5->Integral());

  h0->SetLineColor(kBlue-4);
  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kBlue-4);
  h4->SetLineColor(kBlue-4);
  h5->SetLineColor(kBlue-4);

  h0->SetMarkerColor(kBlue-4);
  h1->SetMarkerColor(kBlue-4);
  h2->SetMarkerColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h4->SetMarkerColor(kBlue-4);
  h5->SetMarkerColor(kBlue-4);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h0->SetMarkerStyle(24);
  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(24);
  h3->SetMarkerStyle(24);
  h4->SetMarkerStyle(24);
  h5->SetMarkerStyle(24);

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


void stylize_weighted(TH1D *h0, TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h0->Scale(1./h0->Integral());
  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  h5->Scale(1./h5->Integral());

  h0->SetLineColor(kRed-4);
  h1->SetLineColor(kRed-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kRed-4);
  h5->SetLineColor(kRed-4);

  h0->SetMarkerColor(kRed-4);
  h1->SetMarkerColor(kRed-4);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kRed-4);
  h4->SetMarkerColor(kRed-4);
  h5->SetMarkerColor(kRed-4);

  h0->SetLineWidth(2);
  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h0->SetMarkerStyle(24);
  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(24);
  h3->SetMarkerStyle(24);
  h4->SetMarkerStyle(24);
  h5->SetMarkerStyle(24);

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
  if(j == 1) result = "80 < #it{p}_{T}^{jet} (GeV) < 100, |#it{#eta}^{jet}| < 1.6";
  else if(j == 2) result = "100 < #it{p}_{T}^{jet} (GeV) < 120, |#it{#eta}^{jet}| < 1.6";
  else if(j == 3) result = "120 < #it{p}_{T}^{jet} (GeV) < 150, |#it{#eta}^{jet}| < 1.6";
  else if(j == 4) result = "150 < #it{p}_{T}^{jet} (GeV) < 200, |#it{#eta}^{jet}| < 1.6";
  else if(j == 5) result = "200 < #it{p}_{T}^{jet} (GeV) < 300, |#it{#eta}^{jet}| < 1.6";
  else if(j == 6) result = "300 < #it{p}_{T}^{jet} (GeV) < 500, |#it{#eta}^{jet}| < 1.6";
  else result = "j out of bounds!";
  return result;
}
void set_pTrel_range(TH1D *h1){

  double lowerLimit = 0.0;
  double upperLimit = 0.3;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void plotJetTrkMaxPtRel_proj(int j = 1,
			     double jetPt_low = 80,
			     double jetPt_high = 100){

  CMSString = "#font[62]{CMS}  #font[52]{Preliminary}";
  energyString = "#sqrt{#it{s}} = 5.02 TeV";
  jetPtString = getJetPtString(j);
  hadronPtString = "#it{p}_{T}^{h} > 14 GeV, |#it{#eta}^{h}| < 2.0";

  li = new TLine();
  la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);

  file_pp_mc_raw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-19.root");
  //file_pp_mc_raw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_jetAxisSmear_muPhi-0.000_sigmaPhi-0.005_muEta-0.000_sigmaEta-0.005_2025-8-19.root");
  file_pp_mc_weighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_dRReweight_2025-7-22_jet60.root");

  file_PbPb_mc_raw = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-1.root");
  file_PbPb_mc_weighted = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_pThat-20_trkpT-14_hiBinShift-10_dRReweight_ultraFineCentBins_2025-07-21.root");

  file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/latest/jetTrkMax/pp_jetTrkMax_trkPt-14_jet60_2025-07-22.root");
  file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/latest/jetTrkMax/PbPb_DiJet_onlyJets_withTrackMaxInfo_partial_jetTrkMax_trkPt-14_jet60_ultraFineCentBins_2025-08-04.root");

  if(!file_pp_mc_raw || !file_pp_mc_weighted || !file_PbPb_mc_raw || !file_PbPb_mc_weighted){
    std::cout << "error finding file! exiting\n";
    return;
  }

  file_pp_mc_raw->GetObject("h_jetTrkMaxPtRel_recoJetPt_T0",H_pTrel_pp_mc_raw);
  file_pp_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_mc_weighted);

  TH1D *binFinder = H_pTrel_pp_mc_raw->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  h_pTrel_pp_mc_raw = (TH1D*) H_pTrel_pp_mc_raw->ProjectionX("h_pTrel_pp_mc_raw",binFinder->FindBin(jetPt_low+smallShift),binFinder->FindBin(jetPt_high-smallShift));

  file_PbPb_mc_raw->GetObject(Form("h_jetTrkMaxPtRel_C5J%i",j),h_pTrel_C5_mc_raw);
  file_PbPb_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_C5J%i",j),h_pTrel_C5_mc_weighted);

  file_PbPb_mc_raw->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_pTrel_C4_mc_raw);
  file_PbPb_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_pTrel_C4_mc_weighted);

  file_PbPb_mc_raw->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_pTrel_C3_mc_raw);
  file_PbPb_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_pTrel_C3_mc_weighted);

  file_PbPb_mc_raw->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_pTrel_C2_mc_raw);
  file_PbPb_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_pTrel_C2_mc_weighted);

  file_PbPb_mc_raw->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_pTrel_C1_mc_raw);
  file_PbPb_mc_weighted->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_pTrel_C1_mc_weighted);

  file_pp_data->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C5J%i",j),h_pTrel_C5_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_pTrel_C4_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_pTrel_C3_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_pTrel_C2_data);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_pTrel_C1_data);

  // merge the peripheral
  h_pTrel_C4_data->Add(h_pTrel_C5_data);
  h_pTrel_C4_mc_raw->Add(h_pTrel_C5_mc_raw);
  h_pTrel_C4_mc_weighted->Add(h_pTrel_C5_mc_weighted);
  
  
  set_pTrel_range(h_pTrel_pp_mc_raw);
  set_pTrel_range(h_pTrel_C5_mc_raw);
  set_pTrel_range(h_pTrel_C4_mc_raw);
  set_pTrel_range(h_pTrel_C3_mc_raw);
  set_pTrel_range(h_pTrel_C2_mc_raw);
  set_pTrel_range(h_pTrel_C1_mc_raw);

  set_pTrel_range(h_pTrel_pp_mc_weighted);
  set_pTrel_range(h_pTrel_C5_mc_weighted);
  set_pTrel_range(h_pTrel_C4_mc_weighted);
  set_pTrel_range(h_pTrel_C3_mc_weighted);
  set_pTrel_range(h_pTrel_C2_mc_weighted);
  set_pTrel_range(h_pTrel_C1_mc_weighted);

  set_pTrel_range(h_pTrel_pp_data);
  set_pTrel_range(h_pTrel_C5_data);
  set_pTrel_range(h_pTrel_C4_data);
  set_pTrel_range(h_pTrel_C3_data);
  set_pTrel_range(h_pTrel_C2_data);
  set_pTrel_range(h_pTrel_C1_data);


  h_pTrel_pp_mc_raw = (TH1D*) h_pTrel_pp_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_pp_mc_raw",pTrel_axis);
  h_pTrel_C5_mc_raw = (TH1D*) h_pTrel_C5_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_C5_mc_raw",pTrel_axis);
  h_pTrel_C4_mc_raw = (TH1D*) h_pTrel_C4_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_C4_mc_raw",pTrel_axis);
  h_pTrel_C3_mc_raw = (TH1D*) h_pTrel_C3_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_C3_mc_raw",pTrel_axis);
  h_pTrel_C2_mc_raw = (TH1D*) h_pTrel_C2_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_C2_mc_raw",pTrel_axis);
  h_pTrel_C1_mc_raw = (TH1D*) h_pTrel_C1_mc_raw->Rebin(Nedge_pTrel-1,"h_pTrel_C1_mc_raw",pTrel_axis);
  
  h_pTrel_pp_mc_weighted = (TH1D*) h_pTrel_pp_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_pp_mc_weighted",pTrel_axis);
  h_pTrel_C5_mc_weighted = (TH1D*) h_pTrel_C5_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_C5_mc_weighted",pTrel_axis);
  h_pTrel_C4_mc_weighted = (TH1D*) h_pTrel_C4_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_C4_mc_weighted",pTrel_axis);
  h_pTrel_C3_mc_weighted = (TH1D*) h_pTrel_C3_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_C3_mc_weighted",pTrel_axis);
  h_pTrel_C2_mc_weighted = (TH1D*) h_pTrel_C2_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_C2_mc_weighted",pTrel_axis);
  h_pTrel_C1_mc_weighted = (TH1D*) h_pTrel_C1_mc_weighted->Rebin(Nedge_pTrel-1,"h_pTrel_C1_mc_weighted",pTrel_axis);

  h_pTrel_pp_data = (TH1D*) h_pTrel_pp_data->Rebin(Nedge_pTrel-1,"h_pTrel_pp_data",pTrel_axis);
  h_pTrel_C5_data = (TH1D*) h_pTrel_C5_data->Rebin(Nedge_pTrel-1,"h_pTrel_C5_data",pTrel_axis);
  h_pTrel_C4_data = (TH1D*) h_pTrel_C4_data->Rebin(Nedge_pTrel-1,"h_pTrel_C4_data",pTrel_axis);
  h_pTrel_C3_data = (TH1D*) h_pTrel_C3_data->Rebin(Nedge_pTrel-1,"h_pTrel_C3_data",pTrel_axis);
  h_pTrel_C2_data = (TH1D*) h_pTrel_C2_data->Rebin(Nedge_pTrel-1,"h_pTrel_C2_data",pTrel_axis);
  h_pTrel_C1_data = (TH1D*) h_pTrel_C1_data->Rebin(Nedge_pTrel-1,"h_pTrel_C1_data",pTrel_axis);

  divideByBinwidth(h_pTrel_pp_mc_raw);
  divideByBinwidth(h_pTrel_C5_mc_raw);
  divideByBinwidth(h_pTrel_C4_mc_raw);
  divideByBinwidth(h_pTrel_C3_mc_raw);
  divideByBinwidth(h_pTrel_C2_mc_raw);
  divideByBinwidth(h_pTrel_C1_mc_raw);

  divideByBinwidth(h_pTrel_pp_mc_weighted);
  divideByBinwidth(h_pTrel_C5_mc_weighted);
  divideByBinwidth(h_pTrel_C4_mc_weighted);
  divideByBinwidth(h_pTrel_C3_mc_weighted);
  divideByBinwidth(h_pTrel_C2_mc_weighted);
  divideByBinwidth(h_pTrel_C1_mc_weighted);

  divideByBinwidth(h_pTrel_pp_data);
  divideByBinwidth(h_pTrel_C5_data);
  divideByBinwidth(h_pTrel_C4_data);
  divideByBinwidth(h_pTrel_C3_data);
  divideByBinwidth(h_pTrel_C2_data);
  divideByBinwidth(h_pTrel_C1_data);

  
  stylize_raw(h_pTrel_pp_mc_raw,h_pTrel_C5_mc_raw,h_pTrel_C4_mc_raw,h_pTrel_C3_mc_raw,h_pTrel_C2_mc_raw,h_pTrel_C1_mc_raw);
  stylize_weighted(h_pTrel_pp_mc_weighted,h_pTrel_C5_mc_weighted,h_pTrel_C4_mc_weighted,h_pTrel_C3_mc_weighted,h_pTrel_C2_mc_weighted,h_pTrel_C1_mc_weighted);
  stylize_data(h_pTrel_pp_data,h_pTrel_C5_data,h_pTrel_C4_data,h_pTrel_C3_data,h_pTrel_C2_data,h_pTrel_C1_data);

  

  r_pp = (TH1D*) h_pTrel_pp_data->Clone("r_pp");
  r_C5 = (TH1D*) h_pTrel_C5_data->Clone("r_C5");
  r_C4 = (TH1D*) h_pTrel_C4_data->Clone("r_C4");
  r_C3 = (TH1D*) h_pTrel_C3_data->Clone("r_C3");
  r_C2 = (TH1D*) h_pTrel_C2_data->Clone("r_C2");
  r_C1 = (TH1D*) h_pTrel_C1_data->Clone("r_C1");

  r_pp->Divide(h_pTrel_pp_data,h_pTrel_pp_mc_raw,1,1,"");
  r_C5->Divide(h_pTrel_C5_data,h_pTrel_C5_mc_raw,1,1,"");
  r_C4->Divide(h_pTrel_C4_data,h_pTrel_C4_mc_raw,1,1,"");
  r_C3->Divide(h_pTrel_C3_data,h_pTrel_C3_mc_raw,1,1,"");
  r_C2->Divide(h_pTrel_C2_data,h_pTrel_C2_mc_raw,1,1,"");
  r_C1->Divide(h_pTrel_C1_data,h_pTrel_C1_mc_raw,1,1,"");

  leg_pp = new TLegend(0.55,0.3,0.84,0.6);
  leg_pp->SetFillStyle(0);
  leg_pp->SetBorderSize(0);
  leg_pp->SetTextSize(0.04);
  leg_pp->AddEntry(h_pTrel_pp_mc_raw,"PYTHIA raw","p");
  //leg_pp->AddEntry(h_pTrel_pp_mc_weighted,"PYTHIA w/ #DeltaR reweight","p");
  leg_pp->AddEntry(h_pTrel_pp_data,"pp","p");

  leg_C5 = new TLegend(0.55,0.3,0.84,0.6);
  leg_C5->SetFillStyle(0);
  leg_C5->SetBorderSize(0);
  leg_C5->SetTextSize(0.04);
  leg_C5->AddEntry(h_pTrel_C5_mc_raw,"P+H 70-80% raw","p");
  leg_C5->AddEntry(h_pTrel_C5_mc_weighted,"P+H 70-80% w/ #DeltaR reweight","p");

  leg_C4 = new TLegend(0.55,0.3,0.84,0.6);
  leg_C4->SetFillStyle(0);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.04);
  leg_C4->AddEntry(h_pTrel_C4_mc_raw,"P+H 50-80% raw","p");
  leg_C4->AddEntry(h_pTrel_C4_data,"PbPb 50-80%","p");
  //leg_C4->AddEntry(h_pTrel_C4_mc_weighted,"P+H 50-80% w/ #DeltaR reweight","p");

  leg_C3 = new TLegend(0.55,0.3,0.84,0.6);
  leg_C3->SetFillStyle(0);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.04);
  leg_C3->AddEntry(h_pTrel_C3_mc_raw,"P+H 30-50% raw","p");
  //leg_C3->AddEntry(h_pTrel_C3_mc_weighted,"P+H 30-50% w/ #DeltaR reweight","p");
  leg_C3->AddEntry(h_pTrel_C3_data,"PbPb 30-50%","p");

  leg_C2 = new TLegend(0.55,0.3,0.84,0.6);
  leg_C2->SetFillStyle(0);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.04);
  leg_C2->AddEntry(h_pTrel_C2_mc_raw,"P+H 10-30% raw","p");
  //leg_C2->AddEntry(h_pTrel_C2_mc_weighted,"P+H 10-30% w/ #DeltaR reweight","p");
  leg_C2->AddEntry(h_pTrel_C2_data,"PbPb 10-30%","p");

  leg_C1 = new TLegend(0.55,0.3,0.84,0.6);
  leg_C1->SetFillStyle(0);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.04);
  leg_C1->AddEntry(h_pTrel_C1_mc_raw,"P+H 0-10% raw","p");
  //leg_C1->AddEntry(h_pTrel_C1_mc_weighted,"P+H 0-10% w/ #DeltaR reweight","p");
  leg_C1->AddEntry(h_pTrel_C1_data,"PbPb 0-10%","p");

   

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
  h_pTrel_pp_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  h_pTrel_pp_mc_raw->Draw();
  //h_pTrel_pp_mc_weighted->Draw("same");
  h_pTrel_pp_data->Draw("same");
  leg_pp->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_pp_2->cd();
  r_pp->GetYaxis()->SetTitle("Data / MC  ");
  r_pp->GetYaxis()->SetTitleSize(subTitleSize);
  r_pp->GetYaxis()->SetLabelSize(subLabelSize);
  r_pp->GetYaxis()->SetRangeUser(0.4,1.6);
  r_pp->GetYaxis()->SetTitleOffset(0.55);
  r_pp->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_pp->GetXaxis()->SetTitleSize(subTitleSize);
  r_pp->GetXaxis()->SetLabelSize(subLabelSize);
  r_pp->Draw();
  TF1 *fitFxn_pp = new TF1("fitFxn_pp","pol1");
  //r_pp->Fit(fitFxn_pp);
  double p0_pp = 0.;
  double p1_pp = 0.;
  p0_pp = fitFxn_pp->GetParameter(0);
  p1_pp = fitFxn_pp->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_pp,p1_pp));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_pp->SaveAs(Form("./figures/jetTrkMaxPtRel/pp_J%i.pdf",j));

  // TCanvas *canv_C5 = new TCanvas("canv_C5","C5",700,700);
  // canv_C5->cd();
  // TPad *pad_C5_1 = new TPad("pad_C5_1","pad_C5_1",0,0.4,1,1);
  // TPad *pad_C5_2 = new TPad("pad_C5_2","pad_C5_2",0,0,1,0.4);
  // pad_C5_1->SetLeftMargin(0.1);
  // pad_C5_2->SetLeftMargin(0.1);
  // pad_C5_1->SetRightMargin(0.1);
  // pad_C5_2->SetRightMargin(0.1);
  // pad_C5_1->SetBottomMargin(0);
  // pad_C5_2->SetTopMargin(0);
  // pad_C5_2->SetBottomMargin(0.2);
  // pad_C5_1->Draw();
  // pad_C5_2->Draw();
  // pad_C5_1->cd();
  // h_pTrel_C5_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  // h_pTrel_C5_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  // h_pTrel_C5_mc_raw->GetYaxis()->SetTitleOffset(0.9);
  // h_pTrel_C5_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  // h_pTrel_C5_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  // h_pTrel_C5_mc_raw->Draw();
  // h_pTrel_C5_mc_weighted->Draw("same");
  // h_pTrel_C5_data->Draw("same");
  // leg_C5->Draw();
  // la->DrawLatexNDC(0.12,0.92,CMSString);
  // la->DrawLatexNDC(0.74,0.92,energyString);
  // la->DrawLatexNDC(0.4,0.8,jetPtString);
  // la->DrawLatexNDC(0.4,0.7,hadronPtString);
  // pad_C5_2->cd();
  // r_C5->GetYaxis()->SetTitle("Data / MC  ");
  // r_C5->GetYaxis()->SetTitleSize(subTitleSize);
  // r_C5->GetYaxis()->SetLabelSize(subLabelSize);
  // r_C5->GetYaxis()->SetRangeUser(0.4,1.6);
  // r_C5->GetYaxis()->SetTitleOffset(0.55);
  // r_C5->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  // r_C5->GetXaxis()->SetTitleSize(subTitleSize);
  // r_C5->GetXaxis()->SetLabelSize(subLabelSize);
  // r_C5->Draw();
  // TF1 *fitFxn_C5 = new TF1("fitFxn_C5","pol1");
  // r_C5->Fit(fitFxn_C5);
  // double p0_C5 = 0.;
  // double p1_C5 = 0.;
  // p0_C5 = fitFxn_C5->GetParameter(0);
  // p1_C5 = fitFxn_C5->GetParameter(1);
  // la->SetTextSize(0.07);
  // la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C5,p1_C5));
  // la->SetTextSize(0.04);
  // li->SetLineStyle(7);
  // li->DrawLine(0,1,5,1);
  // //canv_C5->SaveAs(Form("./figures/pTrelReweightEffect/C5_J%i.pdf",j));

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
  h_pTrel_C4_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  h_pTrel_C4_mc_raw->Draw();
  //h_pTrel_C4_mc_weighted->Draw("same");
  h_pTrel_C4_data->Draw("same");
  leg_C4->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C4_2->cd();
  r_C4->GetYaxis()->SetTitle("Data / MC  ");
  r_C4->GetYaxis()->SetTitleSize(subTitleSize);
  r_C4->GetYaxis()->SetLabelSize(subLabelSize);
  r_C4->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C4->GetYaxis()->SetTitleOffset(0.55);
  r_C4->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_C4->GetXaxis()->SetTitleSize(subTitleSize);
  r_C4->GetXaxis()->SetLabelSize(subLabelSize);
  r_C4->Draw();
  TF1 *fitFxn_C4 = new TF1("fitFxn_C4","pol1");
  //r_C4->Fit(fitFxn_C4);
  double p0_C4 = 0.;
  double p1_C4 = 0.;
  p0_C4 = fitFxn_C4->GetParameter(0);
  p1_C4 = fitFxn_C4->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C4,p1_C4));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C4->SaveAs(Form("./figures/jetTrkMaxPtRel/C4_J%i.pdf",j));

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
  h_pTrel_C3_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  h_pTrel_C3_mc_raw->Draw();
  //h_pTrel_C3_mc_weighted->Draw("same");
  h_pTrel_C3_data->Draw("same");
  leg_C3->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C3_2->cd();
  r_C3->GetYaxis()->SetTitle("Data / MC  ");
  r_C3->GetYaxis()->SetTitleSize(subTitleSize);
  r_C3->GetYaxis()->SetLabelSize(subLabelSize);
  r_C3->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C3->GetYaxis()->SetTitleOffset(0.55);
  r_C3->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_C3->GetXaxis()->SetTitleSize(subTitleSize);
  r_C3->GetXaxis()->SetLabelSize(subLabelSize);
  r_C3->Draw();
  TF1 *fitFxn_C3 = new TF1("fitFxn_C3","pol1");
  //r_C3->Fit(fitFxn_C3);
  double p0_C3 = 0.;
  double p1_C3 = 0.;
  p0_C3 = fitFxn_C3->GetParameter(0);
  p1_C3 = fitFxn_C3->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C3,p1_C3));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C3->SaveAs(Form("./figures/jetTrkMaxPtRel/C3_J%i.pdf",j));   

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
  h_pTrel_C2_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  h_pTrel_C2_mc_raw->Draw();
  //h_pTrel_C2_mc_weighted->Draw("same");
  h_pTrel_C2_data->Draw("same");
  leg_C2->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C2_2->cd();
  r_C2->GetYaxis()->SetTitle("Data / MC  ");
  r_C2->GetYaxis()->SetTitleSize(subTitleSize);
  r_C2->GetYaxis()->SetLabelSize(subLabelSize);
  r_C2->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C2->GetYaxis()->SetTitleOffset(0.55);
  r_C2->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_C2->GetXaxis()->SetTitleSize(subTitleSize);
  r_C2->GetXaxis()->SetLabelSize(subLabelSize);
  r_C2->Draw();
  TF1 *fitFxn_C2 = new TF1("fitFxn_C2","pol1");
  //r_C2->Fit(fitFxn_C2);
  double p0_C2 = 0.;
  double p1_C2 = 0.;
  p0_C2 = fitFxn_C2->GetParameter(0);
  p1_C2 = fitFxn_C2->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C2,p1_C2));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C2->SaveAs(Form("./figures/jetTrkMaxPtRel/C2_J%i.pdf",j));   

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
  h_pTrel_C1_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  h_pTrel_C1_mc_raw->Draw();
  //h_pTrel_C1_mc_weighted->Draw("same");
  h_pTrel_C1_data->Draw("same");
  leg_C1->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.4,0.8,jetPtString);
  la->DrawLatexNDC(0.4,0.7,hadronPtString);
  pad_C1_2->cd();
  r_C1->GetYaxis()->SetTitle("Data / MC  ");
  r_C1->GetYaxis()->SetTitleSize(subTitleSize);
  r_C1->GetYaxis()->SetLabelSize(subLabelSize);
  r_C1->GetYaxis()->SetRangeUser(0.4,1.6);
  r_C1->GetYaxis()->SetTitleOffset(0.55);
  r_C1->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  r_C1->GetXaxis()->SetTitleSize(subTitleSize);
  r_C1->GetXaxis()->SetLabelSize(subLabelSize);
  r_C1->Draw();
  TF1 *fitFxn_C1 = new TF1("fitFxn_C1","pol1");
  //r_C1->Fit(fitFxn_C1);
  double p0_C1 = 0.;
  double p1_C1 = 0.;
  p0_C1 = fitFxn_C1->GetParameter(0);
  p1_C1 = fitFxn_C1->GetParameter(1);
  la->SetTextSize(0.07);
  //la->DrawLatexNDC(0.5,0.6,Form("fit: y = %3.3f + %3.3f x",p0_C1,p1_C1));
  la->SetTextSize(0.04);
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  canv_C1->SaveAs(Form("./figures/jetTrkMaxPtRel/C1_J%i.pdf",j));   


  R_C5 = (TH1D*) r_C5->Clone("R_C5");
  R_C4 = (TH1D*) r_C4->Clone("R_C4");
  R_C3 = (TH1D*) r_C3->Clone("R_C3");
  R_C2 = (TH1D*) r_C2->Clone("R_C2");
  R_C1 = (TH1D*) r_C1->Clone("R_C1");

  R_C5->Divide(r_C5,r_pp,1,1,"");
  R_C4->Divide(r_C4,r_pp,1,1,"");
  R_C3->Divide(r_C3,r_pp,1,1,"");
  R_C2->Divide(r_C2,r_pp,1,1,"");
  R_C1->Divide(r_C1,r_pp,1,1,"");

   
  // TCanvas *canv_R = new TCanvas("canv_R","R",700,700);
  // canv_R->cd();
  // TPad *pad_R_1 = new TPad("pad_R_1","pad_R_1",0,0.4,1,1);
  // TPad *pad_R_2 = new TPad("pad_R_2","pad_R_2",0,0,1,0.4);
  // pad_R_1->SetLeftMargin(0.1);
  // pad_R_2->SetLeftMargin(0.1);
  // pad_R_1->SetRightMargin(0.1);
  // pad_R_2->SetRightMargin(0.1);
  // pad_R_1->SetBottomMargin(0);
  // pad_R_2->SetTopMargin(0);
  // pad_R_2->SetBottomMargin(0.2);
  // pad_R_1->Draw();
  // pad_R_2->Draw();
  // pad_R_1->cd();
  // h_pTrel_R_mc_raw->GetYaxis()->SetTitleSize(0.6*subTitleSize);
  // h_pTrel_R_mc_raw->GetYaxis()->SetLabelSize(0.6*subLabelSize);
  // h_pTrel_R_mc_raw->GetYaxis()->SetTitleOffset(0.9);
  // h_pTrel_R_mc_raw->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  // h_pTrel_R_mc_raw->GetYaxis()->SetRangeUser(0,0.25);
  // h_pTrel_R_mc_raw->Draw();
  // h_pTrel_R_mc_weighted->Draw("same");
  // leg_R->Draw();
  // la->DrawLatexNDC(0.12,0.92,CMSString);
  // la->DrawLatexNDC(0.74,0.92,energyString);
  // la->DrawLatexNDC(0.4,0.8,jetPtString);
  // la->DrawLatexNDC(0.4,0.7,hadronPtString);
  // pad_R_2->cd();
  // r_R->GetYaxis()->SetTitle("Data / MC  ");
  // r_R->GetYaxis()->SetTitleSize(subTitleSize);
  // r_R->GetYaxis()->SetLabelSize(subLabelSize);
  // r_R->GetYaxis()->SetRangeUser(0.4,1.6);
  // r_R->GetYaxis()->SetTitleOffset(0.55);
  // r_R->GetXaxis()->SetTitle("leading-hadron #it{p}_{T}^{rel} [GeV]");
  // r_R->GetXaxis()->SetTitleSize(subTitleSize);
  // r_R->GetXaxis()->SetLabelSize(subLabelSize);
  // r_R->Draw();
  // li->SetLineStyle(7);
  // li->DrawLine(0,1,5,1);
  // canv_R->SaveAs(Form("./figures/pTrelReweightEffect/R_J%i.pdf",j));   
   
     
   
}
