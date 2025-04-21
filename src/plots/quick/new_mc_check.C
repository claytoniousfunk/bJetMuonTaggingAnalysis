void new_mc_check(){

  TFile *f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins.root");
  TFile *f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/platinum/dripping-tap/PH_DiJet_batch1_scan_mu12_tight_pTmu-14_pThat-15_removeHYDJETjets_leadingXjetDump_vzReweight_hiBinReweight_muomMatchingLogicFix_weightLogicFix_hiHFcut_newJetBins.root");

  TH2D *H1, *H2;

  //f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",H1);
  //f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",H2);

  // f1->GetObject("h_inclRecoJetPhi_flavor_C0",H1);
  // f2->GetObject("h_inclRecoJetPhi_flavor_C0",H2);

  f1->GetObject("h_inclRecoJetPt_flavor_C0",H1);
  f2->GetObject("h_inclRecoJetPt_flavor_C0",H2);

  H2->Draw();

  /*

  TH1D *h1, *h2, *h3;
  TH1D *a1, *a2;
  TH1D *bf;

  double ss = 0.1;

  bf = (TH1D*) H1->ProjectionY();
  
  h1 = (TH1D*) H1->ProjectionX("h1",bf->FindBin(-3.+ss),bf->FindBin(4.-ss));
  h2 = (TH1D*) H2->ProjectionX("h2",bf->FindBin(-3.+ss),bf->FindBin(4.-ss));

  a1 = (TH1D*) H1->ProjectionX("a1",bf->FindBin(21.+ss),bf->FindBin(22.-ss));
  a2 = (TH1D*) H2->ProjectionX("a2",bf->FindBin(21.+ss),bf->FindBin(22.-ss));


  // h1 = (TH1D*) H1->ProjectionX("h1",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  // h2 = (TH1D*) H2->ProjectionX("h2",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));

  // a1 = (TH1D*) H1->ProjectionX("a1",bf->FindBin(5.+ss),bf->FindBin(18.-ss));
  // a2 = (TH1D*) H2->ProjectionX("a2",bf->FindBin(5.+ss),bf->FindBin(18.-ss));


  
  h1->Add(a1);
  h2->Add(a2);


  double light_nom_scale = 1.0; // final correction
  double light_nom_scale_prime = 1.0; // integral entry
  double light_nom_scale_pprime = 1.0; // error entry
  double light_add_scale = 1.0; // final correction
  double light_add_scale_prime = 1.0; // integral entry
  double light_add_scale_pprime = 1.0; // error entry
 
  light_nom_scale_prime = h1->IntegralAndError(h1->FindBin(0.0),h1->FindBin(10.0),light_nom_scale_pprime);
  light_add_scale_prime = h2->IntegralAndError(h2->FindBin(0.0),h2->FindBin(10.0),light_add_scale_pprime);
  light_nom_scale = light_nom_scale_pprime / light_nom_scale_prime;
  light_add_scale = light_add_scale_pprime / light_add_scale_prime;
  //h1->Scale(light_nom_scale / h1->Integral());
  //h2->Scale(light_add_scale / h2->Integral());
  //h1->Add(h2);

  //h1->Draw();



  h3 = (TH1D*) h1->Clone("h3");
  //h3->Add(h2);

  double a = 0.0;
  double b = 5.0;
  int binx1 = h1->FindBin(a);
  int binx2 = h1->FindBin(b);
  double E1 = 0.0;
  double I1 = h1->IntegralAndError(binx1,binx2,E1,"");
  double E2 = 0.0;
  double I2 = h2->IntegralAndError(binx1,binx2,E2,"");

  cout << "I1 = " << I1 << "+/- " << E1 << " (" << E1/I1 << ")"<< endl;
  cout << "I2 = " << I2 << "+/- " << E2 << " (" << E2/I2 << ")"<< endl;
  



  cout << " >>>> R1/R2 = " << (E2/I2) / (E1/I1) << endl;
  cout << "H1(entries) = " << H1->GetEntries() << endl;
  cout << "H2(entries) = " << H2->GetEntries() << endl;
  cout << "ratio = " << (1.*H2->GetEntries())/(1.*H1->GetEntries()) << endl;

  
  // const int N_edge = 20;
  // double new_axis[N_edge] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0,10};

  // const int N_edge = 10;
  // double new_axis[N_edge] = {0.0,0.3,0.6,0.9,1.2,2.1,3.0,3.8,5.0,10};

  const int N_edge = 12;
  double new_axis[N_edge] = {20,30,40,50,60,80,100,120,150,200,300,500};
  

  TH1D *h1R, *h2R, *h3R;

  h1R = (TH1D*) h1->Rebin(N_edge-1,"h1R",new_axis);
  h2R = (TH1D*) h2->Rebin(N_edge-1,"h2R",new_axis);
  h3R = (TH1D*) h3->Rebin(N_edge-1,"h3R",new_axis);

  for(int i = 0; i < h1R->GetSize(); i++){
    double bin_width_i = h1R->GetBinWidth(i);
    double bin_content_i = h1R->GetBinContent(i);
    double bin_error_i = h1R->GetBinError(i);
    if(bin_width_i != 0){
      h1R->SetBinContent(i,bin_content_i/bin_width_i);
      h1R->SetBinError(i,bin_error_i,bin_width_i);
    }
  }

  for(int i = 0; i < h2R->GetSize(); i++){
    double bin_width_i = h2R->GetBinWidth(i);
    double bin_content_i = h2R->GetBinContent(i);
    double bin_error_i = h2R->GetBinError(i);
    if(bin_width_i != 0){
      h2R->SetBinContent(i,bin_content_i/bin_width_i);
      h2R->SetBinError(i,bin_error_i,bin_width_i);
    }
  }

  for(int i = 0; i < h3R->GetSize(); i++){
    double bin_width_i = h3R->GetBinWidth(i);
    double bin_content_i = h3R->GetBinContent(i);
    double bin_error_i = h3R->GetBinError(i);
    if(bin_width_i != 0){
      h3R->SetBinContent(i,bin_content_i/bin_width_i);
      h3R->SetBinError(i,bin_error_i,bin_width_i);
    }
  }
  
  
  h1R->SetLineColor(kRed-4);
  h2R->SetLineColor(kBlue-4);
  h3R->SetLineColor(kGreen+2);

  h1R->SetLineWidth(2);
  h2R->SetLineWidth(2);
  h3R->SetLineWidth(2);
  
  h1R->Scale(1./h1R->Integral());
  h2R->Scale(1./h2R->Integral());

  TH1D *r = (TH1D*) h2R->Clone("r");
  r->Divide(h2R,h1R,1,1,"");

  

  TCanvas *c1 = new TCanvas("c1","c1",700,700);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0.4,1,1);
  TPad *p2 = new TPad("p2","p2",0,0,1,0.4);
  p1->SetLeftMargin(0.2);
  p2->SetLeftMargin(0.2);
  p1->SetBottomMargin(0.0);
  p2->SetBottomMargin(0.2);
  p1->SetTopMargin(0.1);
  p2->SetTopMargin(0.0);
  //p1->SetLogy();
  p1->Draw();
  p2->Draw();
  p1->cd();
  h1R->SetTitle("");
  h1R->SetStats(0);
  h1R->Draw();
  h2R->Draw("same");
  p2->cd();
  r->SetTitle("");
  r->SetStats(0);
  r->Draw();

  TCanvas *c2 = new TCanvas("c2","c2",1000,700);
  c2->Divide(2,1);
  c2->cd(1);
  h2R->Draw();
  c2->cd(2);
  h3R->Draw();

  */
  
}
