
int getCutoffBin(TH1D *h, double cutoffPercentage){
  // h = input histogram
  // cutoffPercentage = keep this fraction of counts, throw away above this fraction (0 < x < 1)

  int result = -1;
  
  if(cutoffPercentage < 0 || cutoffPercentage > 1){
    std::cout << "***** ERROR: please input fraction between 0 and 1\n";
    return -1;
  }


  double S_tot = h->Integral();
  double S_i = 0;
  
  for(int i = 1; i < h->GetSize(); i++){
    S_i = h->Integral(0,i);
    if( (S_i / S_tot) > cutoffPercentage){
      std::cout << "COMPLETE: cutoff bin acquired\n";
      return i;
    }
  }

  std::cout << "COMPLETE: no cutoff bin acquired.  Returning -1\n";
  return -1;
}


string getCanvasName(bool isPP,
		     bool isC4,
		     bool isC3,
		     bool isC2,
		     bool isC1){

  string result = "";

  if(isPP) result = "pThatCorrelation_pp";
  else if(isC4) result = "pThatCorrelation_C4";
  else if(isC3) result = "pThatCorrelation_C3";
  else if(isC2) result = "pThatCorrelation_C2";
  else if(isC1) result = "pThatCorrelation_C1";
  else{};

  return result;

}

double fitFxn_gaus(double *x, double *par){
  double pt = x[0];
  double fitval = par[0]*TMath::Gaus(x[0],par[1],par[2]); // Gaussian
  return fitval;
}

double fitFxn_doubleExp(double *x, double *par){
  double pt = x[0];
  double fitval = par[0] + par[1]*TMath::Exp(-par[2]*x[0])+ par[3]*TMath::Exp(-par[4]*x[0]) ; // constant + double exponential
  return fitval;
}

double fitFxn_tripleExp(double *x, double *par){
  double pt = x[0];
  double fitval = par[0] + par[1]*TMath::Exp(-par[2]*x[0])+ par[3]*TMath::Exp(-par[4]*x[0]) + par[5]*TMath::Exp(-par[6]*x[0]) ; // constant + double exponential
  return fitval;
}


void pThatCorrelation(bool isPP = 0,
		      bool isC4 = 1,
		      bool isC3 = 0,
		      bool isC2 = 0,
		      bool isC1 = 0,
		      double cutoff_input = 0.999990){

  TLatex *la = new TLatex();
  gStyle->SetOptFit(0111);

  TString saveSuffix = "";
  if(isPP) saveSuffix = "pp";
  else if(isC4) saveSuffix = "C4";
  else if(isC3) saveSuffix = "C3";
  else if(isC2) saveSuffix = "C2";
  else if(isC1) saveSuffix = "C1";
  else{};

  TFile *f;

  if(isPP) f = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/response/PYTHIA_DiJet_response_pThat-15_mu12_pTmu-15_tight_jetTrkMaxFilter_2026-3-31.root");
  else     f = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/response/PYTHIAHYDJET_response_DiJet_pThat-15_mu12_pTmu-15_tight_vzReweight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_2026-3-25.root");


  TH2D *H;

  if(isPP) f->GetObject("h_leadingRecoJetPtOverPThat_pThat",H);
  else if(isC4) f->GetObject("h_leadingRecoJetPtOverPThat_pThat_C4",H);
  else if(isC3) f->GetObject("h_leadingRecoJetPtOverPThat_pThat_C3",H);
  else if(isC2) f->GetObject("h_leadingRecoJetPtOverPThat_pThat_C2",H);
  else if(isC1) f->GetObject("h_leadingRecoJetPtOverPThat_pThat_C1",H);
  else{};

  TH1D *hx_test = H->ProjectionY();
  TAxis *xAxis = hx_test->GetXaxis();
  
  // const int Nbins = 18;
  // double pThat_axis[Nbins] = {15,20,25,30,35,40,45,50,60,70,80,90,100,120,150,200,300,500};

  const int Nbins = 15;
  double pThat_axis[Nbins] = {15,20,30,40,50,60,70,80,90,100,120,150,200,300,500};

  // const int Nbins = 32;
  // double pThat_axis[Nbins] = {15,16,17,18,19,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200,220,240,260,280,300,350,400,450,500};

  TH1D *h_fit;

  double x[Nbins-1];
  double left[Nbins-1];
  double err[Nbins-1];
  double cutoff[Nbins-1];
  int firstXBin = 0;
  int lastXBin = 0;

  double mean[Nbins-1];
  double sigma[Nbins-1];

  TH1D *h;
  double mean_i, sigma_i;
  double err_mean_i, err_sigma_i;
  
  int N_fit_params = 3;
  TF1 *fitFxn = new TF1("fitFxn",fitFxn_gaus,0,5,N_fit_params);

  //TF1 *fitFxn_cutoff = new TF1("fitFxn_cutoff",fitFxn_doubleExp,pThat_axis[0],pThat_axis[Nbins-1],5); // double exp
  TF1 *fitFxn_cutoff = new TF1("fitFxn_cutoff",fitFxn_tripleExp,pThat_axis[0],pThat_axis[Nbins-1],7); // triple exp

  TCanvas *canv_fit = new TCanvas("canv_fit","canv_fit",700,700);
  TPad *pad_fit = new TPad("pad_fit","pad_fit",0,0,1,1);
  pad_fit->SetLeftMargin(0.15);
  pad_fit->SetBottomMargin(0.15);
  canv_fit->cd();
  pad_fit->Draw();
  pad_fit->cd();

  for(int i = 0; i < Nbins-1; i++){
    x[i] = (pThat_axis[i+1]+pThat_axis[i])/2; // take bin center
    err[i] = (pThat_axis[i+1] - pThat_axis[i])/2; // calculate bin width / 2
    cout << "i = " << i << ", x[i] = " << x[i] << endl;
    firstXBin = xAxis->FindBin(pThat_axis[i]+0.001);
    lastXBin = xAxis->FindBin(pThat_axis[i+1]-0.001);
    left[i] = pThat_axis[i];
    h = H->ProjectionX("h",firstXBin,lastXBin);
    h->Scale(1./h->Integral());
    double meanParLimLow = 0.4;
    double meanParLimHigh = 1.6;
    double sigmaParMin = 0.0;
    double sigmaParMax = 0.6;
    double initMean = h->GetMean();
    double initSigma = h->GetStdDev();
    double fitLow = 0.7; 
    double fitHigh = 1.3;
    TString fitOptionString = "WL R";
    h->Draw();
    fitFxn->SetParameter(0,0.04);
    fitFxn->SetParameter(1,initMean);
    fitFxn->SetParameter(2,initSigma);
    fitFxn->SetParLimits(0,0,0.1);
    fitFxn->SetParLimits(1,meanParLimLow,meanParLimHigh);
    fitFxn->SetParLimits(2,sigmaParMin,sigmaParMax);
    h->Fit(fitFxn,fitOptionString,"",fitLow,fitHigh);
    mean_i = fitFxn->GetParameter(1);
    err_mean_i = fitFxn->GetParError(1);
    sigma_i = fitFxn->GetParameter(2);
    err_sigma_i = fitFxn->GetParError(2);
    mean[i] = mean_i;
    sigma[i] = sigma_i;
    cutoff[i] = h->GetBinCenter(getCutoffBin(h,cutoff_input));

    la->SetTextFont(42);
    la->SetTextSize(0.04);
    TString system_string = "";
    if(isPP) system_string = "#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}          PYTHIA (5.02 TeV)}";
    else system_string =     "#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}   PYTHIA+HYDJET (5.02 TeV)}";

    h->GetXaxis()->SetTitle("#it{p}_{T}^{leadingRecoJet} / #hat{#it{p}}_{T}");
    h->GetYaxis()->SetTitle("Weighted entries");
    h->SetStats(0);
    h->SetTitle("");
    h->GetXaxis()->SetRangeUser(0,2); 
    h->GetYaxis()->SetRangeUser(0,0.06);
    h->Draw();
    la->DrawLatexNDC(0.22,0.92,system_string);
    la->SetTextSize(0.037);
    la->DrawLatexNDC(0.65,0.6,Form("#it{#mu} = %3.3f",mean_i));
    la->DrawLatexNDC(0.65,0.53,Form("#it{#sigma} = %3.3f",sigma_i));
    la->DrawLatexNDC(0.65,0.46,Form("#it{a}_{#it{G}} = %3.3f",fitFxn->GetParameter(0)));
    la->DrawLatexNDC(0.3,0.85,Form("%3.0f < #hat{#it{p}}_{T} (GeV) < %3.0f",pThat_axis[i],pThat_axis[i+1]));
    fitFxn->SetLineColor(kRed-4);
    fitFxn->Draw("same");
    string canvas_name = getCanvasName(isPP,isC4,isC3,isC2,isC1);
    
    canv_fit->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/pThatCorrelation/%s_%3.0f_%3.0f.pdf",canvas_name.c_str(),pThat_axis[i],pThat_axis[i+1]));
    
  }
  
  
  //////////////////////////////////////////////////

  TGraph *graph_sigma = new TGraph(Nbins-1,x,sigma);
  TGraph *graph_cutoff = new TGraph(Nbins-1,x,cutoff);
  graph_sigma->SetMarkerColor(kBlack);
  graph_sigma->SetMarkerStyle(20);
  graph_cutoff->SetMarkerColor(kBlack);
  graph_cutoff->SetMarkerStyle(24);
  // TH1F *h_cutoff = graph_cutoff->GetHistogram();
  //h_cutoff->Draw("hist");
  graph_cutoff->Fit(fitFxn_cutoff,"WL R","",pThat_axis[0],pThat_axis[Nbins-1]);

  // TF1 *fxn = graph_cutoff->GetFunction("fitFxn_cutoff");

  TMultiGraph *mg = new TMultiGraph();
  //mg->Add(graph_sigma);
  mg->Add(graph_cutoff);
  mg->GetXaxis()->SetTitle("#hat{#it{p}}_{T} [GeV]");
  mg->GetYaxis()->SetTitle(Form("#it{p}_{T}^{jet} / #hat{#it{p}}_{T} (%2.4f %% cutoff)",100.*cutoff_input));
  mg->Draw("AP");
  




}
