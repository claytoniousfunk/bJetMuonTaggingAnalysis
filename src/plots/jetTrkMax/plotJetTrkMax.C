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

void stylize_data(TH1D *h1, TH1D *h2, TH1D *h3){

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlue-4);
  h3->SetMarkerColor(kRed-4);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);

  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(21);
  h3->SetMarkerStyle(33);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");


  double yTitleOffset = 0.3;
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);

}


void stylize_data(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  h5->Scale(1./h5->Integral());

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kGreen+2);
  h5->SetLineColor(kMagenta-9);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlue-4);
  h3->SetMarkerColor(kRed-4);
  h4->SetMarkerColor(kGreen+2);
  h5->SetMarkerColor(kMagenta-9);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h1->SetMarkerStyle(20);
  h2->SetMarkerStyle(21);
  h3->SetMarkerStyle(33);
  h4->SetMarkerStyle(34);
  h5->SetMarkerStyle(47);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  h5->SetStats(0);
  
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");
  h5->SetTitle("");


  double yTitleOffset = 0.3;
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);
  h4->GetYaxis()->SetTitleOffset(yTitleOffset);
  h5->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);
  h4->GetYaxis()->SetNdivisions(yNDivisions);
  h5->GetYaxis()->SetNdivisions(yNDivisions);

}

void stylize_mc(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());
  h3->Scale(1./h3->Integral());
  h4->Scale(1./h4->Integral());
  h5->Scale(1./h5->Integral());

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kBlue-4);
  h3->SetLineColor(kRed-4);
  h4->SetLineColor(kGreen+2);
  h5->SetLineColor(kMagenta-9);

  h1->SetMarkerColor(kBlack);
  h2->SetMarkerColor(kBlue-4);
  h3->SetMarkerColor(kRed-4);
  h4->SetMarkerColor(kGreen+2);
  h5->SetMarkerColor(kMagenta-9);

  double alpha = 0.6;
  h1->SetFillColorAlpha(kGray,alpha);
  h2->SetFillColorAlpha(kBlue-4,alpha);
  h3->SetFillColorAlpha(kRed-4,alpha);
  h4->SetFillColorAlpha(kGreen+2,alpha);
  h5->SetFillColorAlpha(kMagenta,alpha);

  h1->SetLineWidth(2);
  h2->SetLineWidth(2);
  h3->SetLineWidth(2);
  h4->SetLineWidth(2);
  h5->SetLineWidth(2);

  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(25);
  h3->SetMarkerStyle(27);
  h4->SetMarkerStyle(28);
  h5->SetMarkerStyle(46);

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);
  h4->SetStats(0);
  h5->SetStats(0);
  
  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");
  h4->SetTitle("");
  h5->SetTitle("");

  double yTitleOffset = 0.3;
  h1->GetYaxis()->SetTitleOffset(yTitleOffset);
  h2->GetYaxis()->SetTitleOffset(yTitleOffset);
  h3->GetYaxis()->SetTitleOffset(yTitleOffset);
  h4->GetYaxis()->SetTitleOffset(yTitleOffset);
  h5->GetYaxis()->SetTitleOffset(yTitleOffset);

  int yNDivisions = 404;
  h1->GetYaxis()->SetNdivisions(yNDivisions);
  h2->GetYaxis()->SetNdivisions(yNDivisions);
  h3->GetYaxis()->SetNdivisions(yNDivisions);
  h4->GetYaxis()->SetNdivisions(yNDivisions);
  h5->GetYaxis()->SetNdivisions(yNDivisions);

}

void set_dR_range(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  double lowerLimit = 0.0;
  double upperLimit = 0.3;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h2->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h3->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h4->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h5->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void set_pTrel_range(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  double lowerLimit = 0.0;
  double upperLimit = 5;
  
  h1->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h2->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h3->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h4->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);
  h5->GetXaxis()->SetRangeUser(lowerLimit,upperLimit);

}

void normalize_jetPt(TH1D *h1, TH1D *h2, TH1D *h3, TH1D *h4, TH1D *h5){

  h1->Scale(1./h1->Integral(h1->GetXaxis()->FindBin(200.),h1->GetXaxis()->FindBin(500.)));
  h2->Scale(1./h2->Integral(h2->GetXaxis()->FindBin(200.),h2->GetXaxis()->FindBin(500.)));
  h3->Scale(1./h3->Integral(h3->GetXaxis()->FindBin(200.),h3->GetXaxis()->FindBin(500.)));
  h4->Scale(1./h4->Integral(h4->GetXaxis()->FindBin(200.),h4->GetXaxis()->FindBin(500.)));
  h5->Scale(1./h5->Integral(h5->GetXaxis()->FindBin(200.),h5->GetXaxis()->FindBin(500.)));
	    
  
}


void plotJetTrkMax(int j = 3){

  TString CMSString = "#font[62]{CMS}  #font[52]{Preliminary}";
  TString energyString = "#sqrt{#it{s}} = 5.02 TeV";

  TString jetPtString = "";

  if(j == 1) jetPtString = "80 < #it{p}_{T}^{jet} (GeV) < 100, |#it{#eta}^{jet}| < 1.6";
  else if(j == 2) jetPtString = "100 < #it{p}_{T}^{jet} (GeV) < 120, |#it{#eta}^{jet}| < 1.6";
  else if(j == 3) jetPtString = "120 < #it{p}_{T}^{jet} (GeV) < 150, |#it{#eta}^{jet}| < 1.6";
  else if(j == 4) jetPtString = "150 < #it{p}_{T}^{jet} (GeV) < 200, |#it{#eta}^{jet}| < 1.6";
  else{};

  TString hadronPtString = "#it{p}_{T}^{h} > 5 GeV, |#it{#eta}^{h}| < 2.0";

  TLine *li = new TLine();
  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.045);

  TFile *file_pp_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/obsidian/jetTrkMax/PYTHIA_DiJet_jetTrkMax_jet60_pThat-15.root");
  //TFile *file_pp_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/obsidian/jetTrkMax/PYTHIA_DiJet_jetTrkMax_jet60_hadronPtRelReweightJ1.root");
  TFile *file_pp_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/pp/obsidian/jetTrkMax/pp_jetTrkMax_jet60.root");

  TFile *file_PbPb_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/obsidian/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_fineCentBins_jet80_pThat-15.root");
  //TFile *file_PbPb_mc = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/obsidian/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_fineCentBins_hadronPtRelReweightJ1.root");
  TFile *file_PbPb_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/obsidian/jetTrkMax/PbPb_DiJet_onlyJets_withTrackMaxInfo_partial_jetTrkMax_fineCentBins_jet80.root");

  // jetPt
  TH1D *h_jetPt_C4_mc, *h_jetPt_C4_data;
  TH1D *h_jetPt_C3_mc, *h_jetPt_C3_data;
  TH1D *h_jetPt_C2_mc, *h_jetPt_C2_data;
  TH1D *h_jetPt_C1_mc, *h_jetPt_C1_data;
  TH1D *h_jetPt_pp_mc, *h_jetPt_pp_data;
  // dr
  TH1D *h_dR_C4_mc, *h_dR_C4_data;
  TH1D *h_dR_C3_mc, *h_dR_C3_data;
  TH1D *h_dR_C2_mc, *h_dR_C2_data;
  TH1D *h_dR_C1_mc, *h_dR_C1_data;
  TH1D *h_dR_pp_mc, *h_dR_pp_data; 
  // pTrel
  TH1D *h_pTrel_C4_mc, *h_pTrel_C4_data;
  TH1D *h_pTrel_C3_mc, *h_pTrel_C3_data;
  TH1D *h_pTrel_C2_mc, *h_pTrel_C2_data;
  TH1D *h_pTrel_C1_mc, *h_pTrel_C1_data;
  TH1D *h_pTrel_pp_mc, *h_pTrel_pp_data; 


  // retrieve jetPt
  file_PbPb_mc->GetObject("h_jetPt_C4",h_jetPt_C4_mc);
  file_PbPb_data->GetObject("h_jetPt_C4",h_jetPt_C4_data);

  file_PbPb_mc->GetObject("h_jetPt_C3",h_jetPt_C3_mc);
  file_PbPb_data->GetObject("h_jetPt_C3",h_jetPt_C3_data);

  file_PbPb_mc->GetObject("h_jetPt_C2",h_jetPt_C2_mc);
  file_PbPb_data->GetObject("h_jetPt_C2",h_jetPt_C2_data);

  file_PbPb_mc->GetObject("h_jetPt_C1",h_jetPt_C1_mc);
  file_PbPb_data->GetObject("h_jetPt_C1",h_jetPt_C1_data);

  file_pp_mc->GetObject("h_jetPt",h_jetPt_pp_mc);
  file_pp_data->GetObject("h_jetPt",h_jetPt_pp_data);
  
  
  // retrieve dR
  file_PbPb_mc->GetObject(Form("h_jetTrkMaxDR_C4J%i",j),h_dR_C4_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxDR_C4J%i",j),h_dR_C4_data);
  // file_PbPb_mc->GetObject(Form("h_jetTrkMaxDR_C0J%i",j),h_dR_C4_mc);
  // file_PbPb_data->GetObject(Form("h_jetTrkMaxDR_C0J%i",j),h_dR_C4_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxDR_C3J%i",j),h_dR_C3_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxDR_C3J%i",j),h_dR_C3_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxDR_C2J%i",j),h_dR_C2_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxDR_C2J%i",j),h_dR_C2_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxDR_C1J%i",j),h_dR_C1_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxDR_C1J%i",j),h_dR_C1_data);

  file_pp_mc->GetObject(Form("h_jetTrkMaxDR_J%i",j),h_dR_pp_mc);
  file_pp_data->GetObject(Form("h_jetTrkMaxDR_J%i",j),h_dR_pp_data);

  // retrieve pTrel
  file_PbPb_mc->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_pTrel_C4_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C4J%i",j),h_pTrel_C4_data);
  // file_PbPb_mc->GetObject(Form("h_jetTrkMaxPtRel_C0J%i",j),h_pTrel_C4_mc);
  // file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C0J%i",j),h_pTrel_C4_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_pTrel_C3_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C3J%i",j),h_pTrel_C3_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_pTrel_C2_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C2J%i",j),h_pTrel_C2_data);

  file_PbPb_mc->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_pTrel_C1_mc);
  file_PbPb_data->GetObject(Form("h_jetTrkMaxPtRel_C1J%i",j),h_pTrel_C1_data);

  file_pp_mc->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_mc);
  file_pp_data->GetObject(Form("h_jetTrkMaxPtRel_J%i",j),h_pTrel_pp_data);

  



  stylize_data(h_jetPt_pp_data,h_jetPt_C4_data,h_jetPt_C3_data,h_jetPt_C2_data, h_jetPt_C1_data);
  normalize_jetPt(h_jetPt_pp_data,h_jetPt_C4_data,h_jetPt_C3_data,h_jetPt_C2_data, h_jetPt_C1_data);

  stylize_data(h_dR_pp_data,h_dR_C4_data,h_dR_C3_data,h_dR_C2_data,h_dR_C1_data);
  set_dR_range(h_dR_pp_data,h_dR_C4_data,h_dR_C3_data,h_dR_C2_data,h_dR_C1_data);
  
  stylize_data(h_pTrel_pp_data,h_pTrel_C4_data,h_pTrel_C3_data,h_pTrel_C2_data,h_pTrel_C1_data);
  set_pTrel_range(h_pTrel_pp_data,h_pTrel_C4_data,h_pTrel_C3_data,h_pTrel_C2_data,h_pTrel_C1_data);

  stylize_mc(h_jetPt_pp_mc,h_jetPt_C4_mc,h_jetPt_C3_mc,h_jetPt_C2_mc, h_jetPt_C1_mc);
  normalize_jetPt(h_jetPt_pp_mc,h_jetPt_C4_mc,h_jetPt_C3_mc,h_jetPt_C2_mc, h_jetPt_C1_mc);
  
  stylize_mc(h_dR_pp_mc,h_dR_C4_mc,h_dR_C3_mc,h_dR_C2_mc,h_dR_C1_mc);
  set_dR_range(h_dR_pp_mc,h_dR_C4_mc,h_dR_C3_mc,h_dR_C2_mc,h_dR_C1_mc);
  
  stylize_mc(h_pTrel_pp_mc,h_pTrel_C4_mc,h_pTrel_C3_mc,h_pTrel_C2_mc,h_pTrel_C1_mc);
  set_pTrel_range(h_pTrel_pp_mc,h_pTrel_C4_mc,h_pTrel_C3_mc,h_pTrel_C2_mc,h_pTrel_C1_mc);


  // const int Nedge_dR = 23;
  // double dR_axis[Nedge_dR] = {0,0.005,0.01,0.015,0.02,0.025,0.03,0.035,0.04,0.045,0.05,0.06,0.07,0.08,0.09,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};

  const int Nedge_dR = 18;
  double dR_axis[Nedge_dR] = {0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};

  // const int Nedge_dR = 13;
  // double dR_axis[Nedge_dR] = {0,0.02,0.04,0.06,0.08,0.1,0.12,0.14,0.16,0.18,0.2,0.24,0.3};




  
  h_dR_pp_data = (TH1D*) h_dR_pp_data->Rebin(Nedge_dR-1,"h_dR_pp_data",dR_axis);
  h_dR_C4_data = (TH1D*) h_dR_C4_data->Rebin(Nedge_dR-1,"h_dR_C4_data",dR_axis);
  h_dR_C3_data = (TH1D*) h_dR_C3_data->Rebin(Nedge_dR-1,"h_dR_C3_data",dR_axis);
  h_dR_C2_data = (TH1D*) h_dR_C2_data->Rebin(Nedge_dR-1,"h_dR_C2_data",dR_axis);
  h_dR_C1_data = (TH1D*) h_dR_C1_data->Rebin(Nedge_dR-1,"h_dR_C1_data",dR_axis);

  divideByBinwidth(h_dR_pp_data);
  divideByBinwidth(h_dR_C4_data);
  divideByBinwidth(h_dR_C3_data);
  divideByBinwidth(h_dR_C2_data);
  divideByBinwidth(h_dR_C1_data);

  
  h_dR_pp_mc = (TH1D*) h_dR_pp_mc->Rebin(Nedge_dR-1,"h_dR_pp_mc",dR_axis);
  h_dR_C4_mc = (TH1D*) h_dR_C4_mc->Rebin(Nedge_dR-1,"h_dR_C4_mc",dR_axis);
  h_dR_C3_mc = (TH1D*) h_dR_C3_mc->Rebin(Nedge_dR-1,"h_dR_C3_mc",dR_axis);
  h_dR_C2_mc = (TH1D*) h_dR_C2_mc->Rebin(Nedge_dR-1,"h_dR_C2_mc",dR_axis);
  h_dR_C1_mc = (TH1D*) h_dR_C1_mc->Rebin(Nedge_dR-1,"h_dR_C1_mc",dR_axis);

  divideByBinwidth(h_dR_pp_mc);
  divideByBinwidth(h_dR_C4_mc);
  divideByBinwidth(h_dR_C3_mc);
  divideByBinwidth(h_dR_C2_mc);
  divideByBinwidth(h_dR_C1_mc);


  const int Nedge_pTrel = 21;
  double pTrel_axis[Nedge_pTrel] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.2,1.4,1.6,1.8,2,2.4,2.8,3.2,4,5};

  h_pTrel_pp_data = (TH1D*) h_pTrel_pp_data->Rebin(Nedge_pTrel-1,"h_pTrel_pp_data",pTrel_axis);
  h_pTrel_C4_data = (TH1D*) h_pTrel_C4_data->Rebin(Nedge_pTrel-1,"h_pTrel_C4_data",pTrel_axis);
  h_pTrel_C3_data = (TH1D*) h_pTrel_C3_data->Rebin(Nedge_pTrel-1,"h_pTrel_C3_data",pTrel_axis);
  h_pTrel_C2_data = (TH1D*) h_pTrel_C2_data->Rebin(Nedge_pTrel-1,"h_pTrel_C2_data",pTrel_axis);
  h_pTrel_C1_data = (TH1D*) h_pTrel_C1_data->Rebin(Nedge_pTrel-1,"h_pTrel_C1_data",pTrel_axis);

  divideByBinwidth(h_pTrel_pp_data);
  divideByBinwidth(h_pTrel_C4_data);
  divideByBinwidth(h_pTrel_C3_data);
  divideByBinwidth(h_pTrel_C2_data);
  divideByBinwidth(h_pTrel_C1_data);

  
  h_pTrel_pp_mc = (TH1D*) h_pTrel_pp_mc->Rebin(Nedge_pTrel-1,"h_pTrel_pp_mc",pTrel_axis);
  h_pTrel_C4_mc = (TH1D*) h_pTrel_C4_mc->Rebin(Nedge_pTrel-1,"h_pTrel_C4_mc",pTrel_axis);
  h_pTrel_C3_mc = (TH1D*) h_pTrel_C3_mc->Rebin(Nedge_pTrel-1,"h_pTrel_C3_mc",pTrel_axis);
  h_pTrel_C2_mc = (TH1D*) h_pTrel_C2_mc->Rebin(Nedge_pTrel-1,"h_pTrel_C2_mc",pTrel_axis);
  h_pTrel_C1_mc = (TH1D*) h_pTrel_C1_mc->Rebin(Nedge_pTrel-1,"h_pTrel_C1_mc",pTrel_axis);

  divideByBinwidth(h_pTrel_pp_mc);
  divideByBinwidth(h_pTrel_C4_mc);
  divideByBinwidth(h_pTrel_C3_mc);
  divideByBinwidth(h_pTrel_C2_mc);
  divideByBinwidth(h_pTrel_C1_mc);
  

  

  //  define PbPb / pp ratios
  // in data...

  TH1D *r_jetPt_C4_data = (TH1D*) h_jetPt_C4_data->Clone("r_jetPt_C4_data");
  TH1D *r_jetPt_C3_data = (TH1D*) h_jetPt_C3_data->Clone("r_jetPt_C3_data");
  TH1D *r_jetPt_C2_data = (TH1D*) h_jetPt_C2_data->Clone("r_jetPt_C2_data");
  TH1D *r_jetPt_C1_data = (TH1D*) h_jetPt_C1_data->Clone("r_jetPt_C1_data");

  r_jetPt_C4_data->Divide(h_jetPt_C4_data,h_jetPt_pp_data,1,1,"");
  r_jetPt_C3_data->Divide(h_jetPt_C3_data,h_jetPt_pp_data,1,1,"");
  r_jetPt_C2_data->Divide(h_jetPt_C2_data,h_jetPt_pp_data,1,1,"");
  r_jetPt_C1_data->Divide(h_jetPt_C1_data,h_jetPt_pp_data,1,1,"");

  TH1D *r_dR_C4_data = (TH1D*) h_dR_C4_data->Clone("r_dR_C4_data");
  TH1D *r_dR_C3_data = (TH1D*) h_dR_C3_data->Clone("r_dR_C3_data");
  TH1D *r_dR_C2_data = (TH1D*) h_dR_C2_data->Clone("r_dR_C2_data");
  TH1D *r_dR_C1_data = (TH1D*) h_dR_C1_data->Clone("r_dR_C1_data");

  r_dR_C4_data->Divide(h_dR_C4_data,h_dR_pp_data,1,1,"");
  r_dR_C3_data->Divide(h_dR_C3_data,h_dR_pp_data,1,1,"");
  r_dR_C2_data->Divide(h_dR_C2_data,h_dR_pp_data,1,1,"");
  r_dR_C1_data->Divide(h_dR_C1_data,h_dR_pp_data,1,1,"");

  
  TH1D *r_pTrel_C4_data = (TH1D*) h_pTrel_C4_data->Clone("r_pTrel_C4_data");
  TH1D *r_pTrel_C3_data = (TH1D*) h_pTrel_C3_data->Clone("r_pTrel_C3_data");
  TH1D *r_pTrel_C2_data = (TH1D*) h_pTrel_C2_data->Clone("r_pTrel_C2_data");
  TH1D *r_pTrel_C1_data = (TH1D*) h_pTrel_C1_data->Clone("r_pTrel_C1_data");

  r_pTrel_C4_data->Divide(h_pTrel_C4_data,h_pTrel_pp_data,1,1,"");
  r_pTrel_C3_data->Divide(h_pTrel_C3_data,h_pTrel_pp_data,1,1,"");
  r_pTrel_C2_data->Divide(h_pTrel_C2_data,h_pTrel_pp_data,1,1,"");
  r_pTrel_C1_data->Divide(h_pTrel_C1_data,h_pTrel_pp_data,1,1,"");



  // now in mc...
  
  TH1D *r_jetPt_C4_mc = (TH1D*) h_jetPt_C4_mc->Clone("r_jetPt_C4_mc");
  TH1D *r_jetPt_C3_mc = (TH1D*) h_jetPt_C3_mc->Clone("r_jetPt_C3_mc");
  TH1D *r_jetPt_C2_mc = (TH1D*) h_jetPt_C2_mc->Clone("r_jetPt_C2_mc");
  TH1D *r_jetPt_C1_mc = (TH1D*) h_jetPt_C1_mc->Clone("r_jetPt_C1_mc");

  r_jetPt_C4_mc->Divide(h_jetPt_C4_mc,h_jetPt_pp_mc,1,1,"");
  r_jetPt_C3_mc->Divide(h_jetPt_C3_mc,h_jetPt_pp_mc,1,1,"");
  r_jetPt_C2_mc->Divide(h_jetPt_C2_mc,h_jetPt_pp_mc,1,1,"");
  r_jetPt_C1_mc->Divide(h_jetPt_C1_mc,h_jetPt_pp_mc,1,1,"");

  TH1D *r_dR_C4_mc = (TH1D*) h_dR_C4_mc->Clone("r_dR_C4_mc");
  TH1D *r_dR_C3_mc = (TH1D*) h_dR_C3_mc->Clone("r_dR_C3_mc");
  TH1D *r_dR_C2_mc = (TH1D*) h_dR_C2_mc->Clone("r_dR_C2_mc");
  TH1D *r_dR_C1_mc = (TH1D*) h_dR_C1_mc->Clone("r_dR_C1_mc");

  r_dR_C4_mc->Divide(h_dR_C4_mc,h_dR_pp_mc,1,1,"");
  r_dR_C3_mc->Divide(h_dR_C3_mc,h_dR_pp_mc,1,1,"");
  r_dR_C2_mc->Divide(h_dR_C2_mc,h_dR_pp_mc,1,1,"");
  r_dR_C1_mc->Divide(h_dR_C1_mc,h_dR_pp_mc,1,1,"");

  
  TH1D *r_pTrel_C4_mc = (TH1D*) h_pTrel_C4_mc->Clone("r_pTrel_C4_mc");
  TH1D *r_pTrel_C3_mc = (TH1D*) h_pTrel_C3_mc->Clone("r_pTrel_C3_mc");
  TH1D *r_pTrel_C2_mc = (TH1D*) h_pTrel_C2_mc->Clone("r_pTrel_C2_mc");
  TH1D *r_pTrel_C1_mc = (TH1D*) h_pTrel_C1_mc->Clone("r_pTrel_C1_mc");

  r_pTrel_C4_mc->Divide(h_pTrel_C4_mc,h_pTrel_pp_mc,1,1,"");
  r_pTrel_C3_mc->Divide(h_pTrel_C3_mc,h_pTrel_pp_mc,1,1,"");
  r_pTrel_C2_mc->Divide(h_pTrel_C2_mc,h_pTrel_pp_mc,1,1,"");
  r_pTrel_C1_mc->Divide(h_pTrel_C1_mc,h_pTrel_pp_mc,1,1,"");


  // define double ratios
  TH1D *R_jetPt_C4 = (TH1D*) r_jetPt_C4_data->Clone("R_jetPt_C4");
  TH1D *R_jetPt_C3 = (TH1D*) r_jetPt_C3_data->Clone("R_jetPt_C3");
  TH1D *R_jetPt_C2 = (TH1D*) r_jetPt_C2_data->Clone("R_jetPt_C2");
  TH1D *R_jetPt_C1 = (TH1D*) r_jetPt_C1_data->Clone("R_jetPt_C1");

  R_jetPt_C4->Divide(r_jetPt_C4_data,r_jetPt_C4_mc,1,1,"");
  R_jetPt_C3->Divide(r_jetPt_C3_data,r_jetPt_C3_mc,1,1,"");
  R_jetPt_C2->Divide(r_jetPt_C2_data,r_jetPt_C2_mc,1,1,"");
  R_jetPt_C1->Divide(r_jetPt_C1_data,r_jetPt_C1_mc,1,1,"");
 
  TH1D *R_dR_C4 = (TH1D*) r_dR_C4_data->Clone("R_dR_C4");
  TH1D *R_dR_C3 = (TH1D*) r_dR_C3_data->Clone("R_dR_C3");
  TH1D *R_dR_C2 = (TH1D*) r_dR_C2_data->Clone("R_dR_C2");
  TH1D *R_dR_C1 = (TH1D*) r_dR_C1_data->Clone("R_dR_C1");

  R_dR_C4->Divide(r_dR_C4_data,r_dR_C4_mc,1,1,"");
  R_dR_C3->Divide(r_dR_C3_data,r_dR_C3_mc,1,1,"");
  R_dR_C2->Divide(r_dR_C2_data,r_dR_C2_mc,1,1,"");
  R_dR_C1->Divide(r_dR_C1_data,r_dR_C1_mc,1,1,"");
 
  TH1D *R_pTrel_C4 = (TH1D*) r_pTrel_C4_data->Clone("R_pTrel_C4");
  TH1D *R_pTrel_C3 = (TH1D*) r_pTrel_C3_data->Clone("R_pTrel_C3");
  TH1D *R_pTrel_C2 = (TH1D*) r_pTrel_C2_data->Clone("R_pTrel_C2");
  TH1D *R_pTrel_C1 = (TH1D*) r_pTrel_C1_data->Clone("R_pTrel_C1");

  R_pTrel_C4->Divide(r_pTrel_C4_data,r_pTrel_C4_mc,1,1,"");
  R_pTrel_C3->Divide(r_pTrel_C3_data,r_pTrel_C3_mc,1,1,"");
  R_pTrel_C2->Divide(r_pTrel_C2_data,r_pTrel_C2_mc,1,1,"");
  R_pTrel_C1->Divide(r_pTrel_C1_data,r_pTrel_C1_mc,1,1,"");

  // now just data / mc ratio
  TH1D *rm_jetPt_pp = (TH1D*) h_jetPt_pp_data->Clone("rm_jetPt_pp");
  TH1D *rm_jetPt_C4 = (TH1D*) h_jetPt_C4_data->Clone("rm_jetPt_C4");
  TH1D *rm_jetPt_C3 = (TH1D*) h_jetPt_C3_data->Clone("rm_jetPt_C3");
  TH1D *rm_jetPt_C2 = (TH1D*) h_jetPt_C2_data->Clone("rm_jetPt_C2");
  TH1D *rm_jetPt_C1 = (TH1D*) h_jetPt_C1_data->Clone("rm_jetPt_C1");

  TH1D *rm_dR_pp = (TH1D*) h_dR_pp_data->Clone("rm_dR_pp");
  TH1D *rm_dR_C4 = (TH1D*) h_dR_C4_data->Clone("rm_dR_C4");
  TH1D *rm_dR_C3 = (TH1D*) h_dR_C3_data->Clone("rm_dR_C3");
  TH1D *rm_dR_C2 = (TH1D*) h_dR_C2_data->Clone("rm_dR_C2");
  TH1D *rm_dR_C1 = (TH1D*) h_dR_C1_data->Clone("rm_dR_C1");
  
  TH1D *rm_pTrel_pp = (TH1D*) h_pTrel_pp_data->Clone("rm_pTrel_pp");
  TH1D *rm_pTrel_C4 = (TH1D*) h_pTrel_C4_data->Clone("rm_pTrel_C4");
  TH1D *rm_pTrel_C3 = (TH1D*) h_pTrel_C3_data->Clone("rm_pTrel_C3");
  TH1D *rm_pTrel_C2 = (TH1D*) h_pTrel_C2_data->Clone("rm_pTrel_C2");
  TH1D *rm_pTrel_C1 = (TH1D*) h_pTrel_C1_data->Clone("rm_pTrel_C1");

  rm_jetPt_pp->Divide(h_jetPt_pp_data,h_jetPt_pp_mc,1,1,"");
  rm_jetPt_C4->Divide(h_jetPt_C4_data,h_jetPt_C4_mc,1,1,"");
  rm_jetPt_C3->Divide(h_jetPt_C3_data,h_jetPt_C3_mc,1,1,"");
  rm_jetPt_C2->Divide(h_jetPt_C2_data,h_jetPt_C2_mc,1,1,"");
  rm_jetPt_C1->Divide(h_jetPt_C1_data,h_jetPt_C1_mc,1,1,"");

  rm_dR_pp->Divide(h_dR_pp_data,h_dR_pp_mc,1,1,"");
  rm_dR_C4->Divide(h_dR_C4_data,h_dR_C4_mc,1,1,"");
  rm_dR_C3->Divide(h_dR_C3_data,h_dR_C3_mc,1,1,"");
  rm_dR_C2->Divide(h_dR_C2_data,h_dR_C2_mc,1,1,"");
  rm_dR_C1->Divide(h_dR_C1_data,h_dR_C1_mc,1,1,"");

  rm_pTrel_pp->Divide(h_pTrel_pp_data,h_pTrel_pp_mc,1,1,"");
  rm_pTrel_C4->Divide(h_pTrel_C4_data,h_pTrel_C4_mc,1,1,"");
  rm_pTrel_C3->Divide(h_pTrel_C3_data,h_pTrel_C3_mc,1,1,"");
  rm_pTrel_C2->Divide(h_pTrel_C2_data,h_pTrel_C2_mc,1,1,"");
  rm_pTrel_C1->Divide(h_pTrel_C1_data,h_pTrel_C1_mc,1,1,"");










  
  TLegend *leg_data = new TLegend(0.4,0.3,0.6,0.6);
  leg_data->SetFillStyle(0);
  leg_data->SetBorderSize(0);
  leg_data->SetTextSize(0.04);
  leg_data->AddEntry(h_jetPt_pp_data,"pp","p");
  leg_data->AddEntry(h_jetPt_C4_data,"PbPb 50-90%","p");
  leg_data->AddEntry(h_jetPt_C3_data,"PbPb 30-50%","p");
  leg_data->AddEntry(h_jetPt_C2_data,"PbPb 10-30%","p");
  leg_data->AddEntry(h_jetPt_C1_data,"PbPb 0-10%","p");

  TLegend *leg_mc = new TLegend(0.6,0.3,0.89,0.6);
  leg_mc->SetFillStyle(0);
  leg_mc->SetBorderSize(0);
  leg_mc->SetTextSize(0.04);
  leg_mc->AddEntry(h_jetPt_pp_mc,"PYTHIA","p");
  leg_mc->AddEntry(h_jetPt_C4_mc,"PYTHIA+HYDJET 50-90%","p");
  leg_mc->AddEntry(h_jetPt_C3_mc,"PYTHIA+HYDJET 30-50%","p");
  leg_mc->AddEntry(h_jetPt_C2_mc,"PYTHIA+HYDJET 10-30%","p");
  leg_mc->AddEntry(h_jetPt_C1_mc,"PYTHIA+HYDJET 0-10%","p");
 

  double subTitleSize = 0.14;
  double subLabelSize = 0.11;

  // Draw
  TCanvas *canv_jetPt = new TCanvas("canv_jetPt","jetPt",700,900);
  canv_jetPt->cd();
  TPad *pad_jetPt_1 = new TPad("pad_jetPt_1","pad_jetPt_1",0,0.6,1,1);
  TPad *pad_jetPt_2 = new TPad("pad_jetPt_2","pad_jetPt_2",0,0.45,1,0.6);
  TPad *pad_jetPt_3 = new TPad("pad_jetPt_3","pad_jetPt_3",0,0.3,1,0.45);
  TPad *pad_jetPt_4 = new TPad("pad_jetPt_4","pad_jetPt_4",0,0.15,1,0.3);
  TPad *pad_jetPt_5 = new TPad("pad_jetPt_5","pad_jetPt_5",0,0.0,1,0.15);
  pad_jetPt_1->SetLeftMargin(0.1);
  pad_jetPt_2->SetLeftMargin(0.1);
  pad_jetPt_3->SetLeftMargin(0.1);
  pad_jetPt_4->SetLeftMargin(0.1);
  pad_jetPt_5->SetLeftMargin(0.1);
  pad_jetPt_1->SetRightMargin(0.1);
  pad_jetPt_2->SetRightMargin(0.1);
  pad_jetPt_3->SetRightMargin(0.1);
  pad_jetPt_4->SetRightMargin(0.1);
  pad_jetPt_5->SetRightMargin(0.1);
  pad_jetPt_1->SetBottomMargin(0);
  pad_jetPt_2->SetTopMargin(0);
  pad_jetPt_2->SetBottomMargin(0);
  pad_jetPt_3->SetTopMargin(0);
  pad_jetPt_3->SetBottomMargin(0);
  pad_jetPt_4->SetTopMargin(0);
  pad_jetPt_4->SetBottomMargin(0.0);
  pad_jetPt_5->SetTopMargin(0);
  pad_jetPt_5->SetBottomMargin(0.32);
  pad_jetPt_1->Draw();
  pad_jetPt_2->Draw();
  pad_jetPt_3->Draw();
  pad_jetPt_4->Draw();
  pad_jetPt_5->Draw();
  pad_jetPt_1->cd();
  h_jetPt_pp_data->GetYaxis()->SetTitleSize(0.4*subTitleSize);
  h_jetPt_pp_data->GetYaxis()->SetLabelSize(0.4*subLabelSize);
  h_jetPt_pp_data->GetYaxis()->SetTitleOffset(0.7);
  h_jetPt_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T} [GeV^{-1}]");
  h_jetPt_pp_data->Draw();
  h_jetPt_pp_mc->Draw("same");
  h_jetPt_C4_data->Draw("same");
  h_jetPt_C4_mc->Draw("same");
  h_jetPt_C3_data->Draw("same");
  h_jetPt_C3_mc->Draw("same");
  h_jetPt_C2_data->Draw("same");
  h_jetPt_C2_mc->Draw("same");
  h_jetPt_C1_data->Draw("same");
  h_jetPt_C1_mc->Draw("same");
  leg_data->Draw();
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.5,0.8,jetPtString);
  la->DrawLatexNDC(0.5,0.7,hadronPtString);
  pad_jetPt_2->cd();
  rm_jetPt_pp->GetYaxis()->SetTitle("Data / MC");
  rm_jetPt_pp->GetYaxis()->SetTitleSize(subTitleSize);
  rm_jetPt_pp->GetYaxis()->SetLabelSize(subLabelSize);
  rm_jetPt_pp->GetYaxis()->SetRangeUser(0.3,1.7);
  rm_jetPt_pp->Draw();
  rm_jetPt_C4->Draw("same");
  rm_jetPt_C3->Draw("same");
  rm_jetPt_C2->Draw("same");
  rm_jetPt_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(20,1,500,1);
  pad_jetPt_3->cd();
  r_jetPt_C4_data->GetYaxis()->SetTitle("PbPb /pp");
  r_jetPt_C4_data->GetYaxis()->SetTitleSize(subTitleSize);
  r_jetPt_C4_data->GetYaxis()->SetLabelSize(subLabelSize);
  r_jetPt_C4_data->GetYaxis()->SetRangeUser(0.3,1.7);
  r_jetPt_C4_data->Draw();
  r_jetPt_C3_data->Draw("same");
  r_jetPt_C2_data->Draw("same");
  r_jetPt_C1_data->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(20,1,500,1);
  pad_jetPt_4->cd();
  r_jetPt_C4_mc->GetYaxis()->SetTitle("P+H / P");
  r_jetPt_C4_mc->GetYaxis()->SetTitleSize(subTitleSize);
  r_jetPt_C4_mc->GetYaxis()->SetLabelSize(subLabelSize);
  r_jetPt_C4_mc->GetYaxis()->SetRangeUser(0.3,1.7);
  r_jetPt_C4_mc->Draw();
  r_jetPt_C3_mc->Draw("same");
  r_jetPt_C2_mc->Draw("same");
  r_jetPt_C1_mc->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(20,1,500,1);
  pad_jetPt_5->cd();
  R_jetPt_C4->GetYaxis()->SetTitleSize(subTitleSize);
  R_jetPt_C4->GetYaxis()->SetLabelSize(subLabelSize);
  R_jetPt_C4->GetXaxis()->SetTitleSize(subTitleSize);
  R_jetPt_C4->GetXaxis()->SetLabelSize(subLabelSize);
  R_jetPt_C4->GetYaxis()->SetTitle("R(data) / R(MC)");
  R_jetPt_C4->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  R_jetPt_C4->GetYaxis()->SetRangeUser(0.3,1.7);
  R_jetPt_C4->Draw();
  R_jetPt_C3->Draw("same");
  R_jetPt_C2->Draw("same");
  R_jetPt_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(20,1,500,1);

  TCanvas *canv_dR = new TCanvas("canv_dR","dR",700,900);
  canv_dR->cd();
  TPad *pad_dR_1 = new TPad("pad_dR_1","pad_dR_1",0,0.6,1,1);
  TPad *pad_dR_2 = new TPad("pad_dR_2","pad_dR_2",0,0.45,1,0.6);
  TPad *pad_dR_3 = new TPad("pad_dR_3","pad_dR_3",0,0.3,1,0.45);
  TPad *pad_dR_4 = new TPad("pad_dR_4","pad_dR_4",0,0.15,1,0.3);
  TPad *pad_dR_5 = new TPad("pad_dR_5","pad_dR_5",0,0.0,1,0.15);
  pad_dR_1->SetLeftMargin(0.1);
  pad_dR_2->SetLeftMargin(0.1);
  pad_dR_3->SetLeftMargin(0.1);
  pad_dR_4->SetLeftMargin(0.1);
  pad_dR_5->SetLeftMargin(0.1);
  pad_dR_1->SetRightMargin(0.1);
  pad_dR_2->SetRightMargin(0.1);
  pad_dR_3->SetRightMargin(0.1);
  pad_dR_4->SetRightMargin(0.1);
  pad_dR_5->SetRightMargin(0.1);
  pad_dR_1->SetBottomMargin(0);
  pad_dR_2->SetTopMargin(0);
  pad_dR_2->SetBottomMargin(0);
  pad_dR_3->SetTopMargin(0);
  pad_dR_3->SetBottomMargin(0);
  pad_dR_4->SetTopMargin(0);
  pad_dR_4->SetBottomMargin(0.0);
  pad_dR_5->SetTopMargin(0);
  pad_dR_5->SetBottomMargin(0.32);
  pad_dR_1->Draw();
  pad_dR_2->Draw();
  pad_dR_3->Draw();
  pad_dR_4->Draw();
  pad_dR_5->Draw();
  pad_dR_1->cd();
  h_dR_pp_data->GetYaxis()->SetTitleSize(0.4*subTitleSize);
  h_dR_pp_data->GetYaxis()->SetLabelSize(0.4*subLabelSize);
  h_dR_pp_data->GetYaxis()->SetTitleOffset(0.7);
  h_dR_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d(#Delta #it{r})");
  h_dR_pp_data->Draw();
  h_dR_pp_mc->Draw("same");
  h_dR_C4_data->Draw("same");
  h_dR_C4_mc->Draw("same");
  h_dR_C3_data->Draw("same");
  h_dR_C3_mc->Draw("same");
  h_dR_C2_data->Draw("same");
  h_dR_C2_mc->Draw("same");
  h_dR_C1_data->Draw("same");
  h_dR_C1_mc->Draw("same");
  leg_data->Draw();
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.5,0.8,jetPtString);
  la->DrawLatexNDC(0.5,0.7,hadronPtString);
  pad_dR_2->cd();
  rm_dR_pp->GetYaxis()->SetTitle("Data / MC");
  rm_dR_pp->GetYaxis()->SetTitleSize(subTitleSize);
  rm_dR_pp->GetYaxis()->SetLabelSize(subLabelSize);
  rm_dR_pp->GetYaxis()->SetRangeUser(0.62,1.38);
  rm_dR_pp->Draw();
  rm_dR_pp->Fit("pol1");
  rm_dR_C4->Draw("same");
  //rm_dR_C4->Fit("pol4");
  rm_dR_C3->Draw("same");
  rm_dR_C2->Draw("same");
  rm_dR_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  pad_dR_3->cd();
  r_dR_C4_data->GetYaxis()->SetTitle("PbPb /pp");
  r_dR_C4_data->GetYaxis()->SetTitleSize(subTitleSize);
  r_dR_C4_data->GetYaxis()->SetLabelSize(subLabelSize);
  r_dR_C4_data->GetYaxis()->SetRangeUser(0.3,1.7);
  r_dR_C4_data->Draw();
  r_dR_C3_data->Draw("same");
  r_dR_C2_data->Draw("same");
  r_dR_C1_data->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  pad_dR_4->cd();
  r_dR_C4_mc->GetYaxis()->SetTitle("P+H / P");
  r_dR_C4_mc->GetYaxis()->SetTitleSize(subTitleSize);
  r_dR_C4_mc->GetYaxis()->SetLabelSize(subLabelSize);
  r_dR_C4_mc->GetYaxis()->SetRangeUser(0.3,1.7);
  r_dR_C4_mc->Draw();
  r_dR_C3_mc->Draw("same");
  r_dR_C2_mc->Draw("same");
  r_dR_C1_mc->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);
  pad_dR_5->cd();
  R_dR_C4->GetYaxis()->SetTitleSize(subTitleSize);
  R_dR_C4->GetYaxis()->SetLabelSize(subLabelSize);
  R_dR_C4->GetXaxis()->SetTitleSize(subTitleSize);
  R_dR_C4->GetXaxis()->SetLabelSize(subLabelSize);
  R_dR_C4->GetYaxis()->SetTitle("R(data) / R(MC)");
  R_dR_C4->GetXaxis()->SetTitle("#Delta #it{r}(leading-hadron,jet)");
  R_dR_C4->GetYaxis()->SetRangeUser(0.3,1.7);
  R_dR_C4->Draw();
  R_dR_C3->Draw("same");
  R_dR_C2->Draw("same");
  R_dR_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,0.3,1);


  TCanvas *canv_pTrel = new TCanvas("canv_pTrel","pTrel",700,900);
  canv_pTrel->cd();
  TPad *pad_pTrel_1 = new TPad("pad_pTrel_1","pad_pTrel_1",0,0.6,1,1);
  TPad *pad_pTrel_2 = new TPad("pad_pTrel_2","pad_pTrel_2",0,0.45,1,0.6);
  TPad *pad_pTrel_3 = new TPad("pad_pTrel_3","pad_pTrel_3",0,0.3,1,0.45);
  TPad *pad_pTrel_4 = new TPad("pad_pTrel_4","pad_pTrel_4",0,0.15,1,0.3);
  TPad *pad_pTrel_5 = new TPad("pad_pTrel_5","pad_pTrel_5",0,0.0,1,0.15);
  pad_pTrel_1->SetLeftMargin(0.1);
  pad_pTrel_2->SetLeftMargin(0.1);
  pad_pTrel_3->SetLeftMargin(0.1);
  pad_pTrel_4->SetLeftMargin(0.1);
  pad_pTrel_5->SetLeftMargin(0.1);
  pad_pTrel_1->SetRightMargin(0.1);
  pad_pTrel_2->SetRightMargin(0.1);
  pad_pTrel_3->SetRightMargin(0.1);
  pad_pTrel_4->SetRightMargin(0.1);
  pad_pTrel_5->SetRightMargin(0.1);
  pad_pTrel_1->SetBottomMargin(0);
  pad_pTrel_2->SetTopMargin(0);
  pad_pTrel_2->SetBottomMargin(0);
  pad_pTrel_3->SetTopMargin(0);
  pad_pTrel_3->SetBottomMargin(0);
  pad_pTrel_4->SetTopMargin(0);
  pad_pTrel_4->SetBottomMargin(0.0);
  pad_pTrel_5->SetTopMargin(0);
  pad_pTrel_5->SetBottomMargin(0.32);
  pad_pTrel_1->Draw();
  pad_pTrel_2->Draw();
  pad_pTrel_3->Draw();
  pad_pTrel_4->Draw();
  pad_pTrel_5->Draw();
  pad_pTrel_1->cd();
  h_pTrel_pp_data->GetYaxis()->SetTitleSize(0.4*subTitleSize);
  h_pTrel_pp_data->GetYaxis()->SetLabelSize(0.4*subLabelSize);
  h_pTrel_pp_data->GetYaxis()->SetTitleOffset(0.7);
  h_pTrel_pp_data->GetYaxis()->SetTitle("1/#it{N} d#it{N}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h_pTrel_pp_data->Draw();
  h_pTrel_pp_mc->Draw("same");
  h_pTrel_C4_data->Draw("same");
  h_pTrel_C4_mc->Draw("same");
  h_pTrel_C3_data->Draw("same");
  h_pTrel_C3_mc->Draw("same");
  h_pTrel_C2_data->Draw("same");
  h_pTrel_C2_mc->Draw("same");
  h_pTrel_C1_data->Draw("same");
  h_pTrel_C1_mc->Draw("same");
  leg_data->Draw();
  leg_mc->Draw();
  la->DrawLatexNDC(0.12,0.92,CMSString);
  la->DrawLatexNDC(0.74,0.92,energyString);
  la->DrawLatexNDC(0.5,0.8,jetPtString);
  la->DrawLatexNDC(0.5,0.7,hadronPtString);
  pad_pTrel_2->cd();
  rm_pTrel_pp->GetYaxis()->SetTitle("Data / MC");
  rm_pTrel_pp->GetYaxis()->SetTitleSize(subTitleSize);
  rm_pTrel_pp->GetYaxis()->SetLabelSize(subLabelSize);
  rm_pTrel_pp->GetYaxis()->SetRangeUser(0.62,1.38);
  rm_pTrel_pp->Draw();
  rm_pTrel_C4->Draw("same");
  //rm_pTrel_C4->Fit("pol3");
  rm_pTrel_C3->Draw("same");
  rm_pTrel_C2->Draw("same");
  rm_pTrel_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  pad_pTrel_3->cd();
  r_pTrel_C4_data->GetYaxis()->SetTitle("PbPb /pp");
  r_pTrel_C4_data->GetYaxis()->SetTitleSize(subTitleSize);
  r_pTrel_C4_data->GetYaxis()->SetLabelSize(subLabelSize);
  r_pTrel_C4_data->GetYaxis()->SetRangeUser(0.3,1.7);
  r_pTrel_C4_data->Draw();
  r_pTrel_C3_data->Draw("same");
  r_pTrel_C2_data->Draw("same");
  r_pTrel_C1_data->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  pad_pTrel_4->cd();
  r_pTrel_C4_mc->GetYaxis()->SetTitle("P+H / P");
  r_pTrel_C4_mc->GetYaxis()->SetTitleSize(subTitleSize);
  r_pTrel_C4_mc->GetYaxis()->SetLabelSize(subLabelSize);
  r_pTrel_C4_mc->GetYaxis()->SetRangeUser(0.3,1.7);
  r_pTrel_C4_mc->Draw();
  r_pTrel_C3_mc->Draw("same");
  r_pTrel_C2_mc->Draw("same");
  r_pTrel_C1_mc->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);
  pad_pTrel_5->cd();
  R_pTrel_C4->GetYaxis()->SetTitleSize(subTitleSize);
  R_pTrel_C4->GetYaxis()->SetLabelSize(subLabelSize);
  R_pTrel_C4->GetXaxis()->SetTitleSize(subTitleSize);
  R_pTrel_C4->GetXaxis()->SetLabelSize(subLabelSize);
  R_pTrel_C4->GetYaxis()->SetTitle("R(data) / R(MC)");
  R_pTrel_C4->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  R_pTrel_C4->GetYaxis()->SetRangeUser(0.3,1.7);
  R_pTrel_C4->Draw();
  R_pTrel_C3->Draw("same");
  R_pTrel_C2->Draw("same");
  R_pTrel_C1->Draw("same");
  li->SetLineStyle(7);
  li->DrawLine(0,1,5,1);

  // save canvas
  canv_jetPt->SaveAs("./figures/jetPt.pdf");
  canv_dR->SaveAs(Form("./figures/dR_J%i.pdf",j));
  canv_pTrel->SaveAs(Form("./figures/pTrel_J%i.pdf",j));

  //R_pTrel_C2->Fit("pol1");

  TFile *file_PY_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_newJetBins.root");
  TFile *file_PY_C2smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC2_newJetBins.root");
  TFile *file_PY_C1smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/platinum/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_jetPtReweight_vzReweight_muPtRelReweightC1_newJetBins.root");

  TH2D *Z1, *Z2, *Z3;
  TH1D *z1, *z2, *z3;

  file_PY_nom->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",Z1);
  file_PY_C2smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",Z2);
  file_PY_C1smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_J1",Z3);

  z1 = (TH1D*) Z1->ProjectionX("z1");
  z2 = (TH1D*) Z2->ProjectionX("z2");
  z3 = (TH1D*) Z3->ProjectionX("z3");

  stylize_data(z1,z2,z3);

  h_pTrel_pp_mc->Scale(1./h_pTrel_pp_mc->Integral());
  h_pTrel_C4_mc->Scale(1./h_pTrel_C4_mc->Integral());
  h_pTrel_C3_mc->Scale(1./h_pTrel_C3_mc->Integral());
  h_pTrel_C2_mc->Scale(1./h_pTrel_C2_mc->Integral());
  h_pTrel_C1_mc->Scale(1./h_pTrel_C1_mc->Integral());
  z1->Scale(1./z1->Integral());
  z2->Scale(1./z2->Integral());
  z3->Scale(1./z3->Integral());

  TH1D *rz2 = (TH1D*) z2->Clone("rz2");
  TH1D *rz3 = (TH1D*) z3->Clone("rz3");

  rz2->Divide(z2,z1,1,1,"");
  rz3->Divide(z3,z1,1,1,"");

  TLegend *leg_s = new TLegend(0.5,0.5,0.8,0.7);
  leg_s->SetBorderSize(0);
  leg_s->SetTextSize(0.045);
  leg_s->AddEntry(z1,"muon #it{p}_{T}^{rel} (pp)","p");
  leg_s->AddEntry(z2,"muon #it{p}_{T}^{rel} (pp -> 30-90%)","p");
  leg_s->AddEntry(z3,"muon #it{p}_{T}^{rel} (pp -> 0-30%)","p");
  leg_s->AddEntry(h_pTrel_pp_mc,"hadron #it{p}_{T}^{rel} (pp)","p");
  leg_s->AddEntry(h_pTrel_C4_mc,"hadron #it{p}_{T}^{rel} (PH 50-90%)","p");
  leg_s->AddEntry(h_pTrel_C3_mc,"hadron #it{p}_{T}^{rel} (PH 30-50%)","p");
  leg_s->AddEntry(h_pTrel_C2_mc,"hadron #it{p}_{T}^{rel} (PH 10-30%)","p");
  leg_s->AddEntry(h_pTrel_C1_mc,"hadron #it{p}_{T}^{rel} (PH 0-10%)","p");
  
  TCanvas *cz = new TCanvas("cz","cz",700,700);
  cz->cd();
  TPad *pz1 = new TPad("pz1","pz1",0,0.5,1,1);
  TPad *pz2 = new TPad("pz2","pz2",0,0,1,0.5);
  pz1->Draw();
  pz2->Draw();
  pz1->cd();
  h_pTrel_pp_mc->Draw();
  z1->Draw("same");
  z2->Draw("same");
  z3->Draw("same");
  h_pTrel_C4_mc->Draw("same");
  h_pTrel_C3_mc->Draw("same");
  h_pTrel_C2_mc->Draw("same");
  h_pTrel_C1_mc->Draw("same");
  leg_s->Draw();
  pz2->cd();
  r_pTrel_C4_mc->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r_pTrel_C4_mc->GetXaxis()->SetTitle("#it{p}_{T}^{rel} [GeV]");
  r_pTrel_C4_mc->Draw();
  r_pTrel_C3_mc->Draw("same");
  r_pTrel_C2_mc->Draw("same");
  r_pTrel_C1_mc->Draw("same");
  rz2->Draw("same");
  rz3->Draw("same");

}
