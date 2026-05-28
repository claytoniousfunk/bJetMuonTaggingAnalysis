


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"

double lowPTFitFxn(double *x, double *par){
  double fitval = 1 + par[0]*exp(-par[1]*x[0]);  
  return fitval;
}



void plotJetPt_fineCentBins(bool isPP = 0,
			    bool isC4 = 1,
			    bool isC3 = 0,
			    bool isC2 = 0,
			    bool isC1 = 0,
			    bool isSingleMuon = 0,
			    bool isMinBias = 1,
			    bool isHardProbes = 0
			    ){

  

  TF1 *fitFxn = new TF1("fitFxn",lowPTFitFxn,80,500,2);
  //fitFxn->SetParameter(0,0.2);
  //fitFxn->SetParameter(1,140);
  //fitFxn->SetParLimits(0,0,1);
  
  TFile *f1, *f2, *f3;


  if(isPP){

    if(isSingleMuon){
      
      f1 = TFile::Open(goldenFile_pp_SingleMuon_mu12_pTmu15);
      
    }
    else if(isMinBias){

      f1 = TFile::Open(goldenFile_pp_MinBias_mu12);
      
    }
    else if(isHardProbes){

      f1 = TFile::Open(goldenFile_pp_HighEGJet_jet80_mu12);

    }
    else{};
    
    f2 = TFile::Open(goldenFile_PYTHIA_pThat30_mu12_pTmu15_vzReweight);
     
  }

  else if(isC1 || isC2 || isC3 || isC4){
    
    if(isSingleMuon){
      	
      f1 = TFile::Open(goldenFile_PbPb_SingleMuon_mu12_pTmu15);
      	
    }
    else if(isMinBias){
    	
      f1 = TFile::Open(goldenFile_PbPb_MinBias_mu12);
	
    }
    else if(isHardProbes){

      f1 = TFile::Open(goldenFile_PbPb_HardProbes_jet80_mu12);
      
    }
    else{};

    f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_pThat30_mu12_pTmu15_hiBinReweight_vzReweight);
     
  }

   

   
  TH2D *H1, *H2;
  TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;
  TH1D *h2_add2;


  if(isPP){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h1);
      f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt",h1);
      f2->GetObject("h_inclRecoJetPt_flavor",H2);
    }
    else{};
  }

  if(isC4){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h1);
      f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C4",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt_C4",h1);
      f2->GetObject("h_inclRecoJetPt_flavor_C4",H2);
    }
    else{};
  }

  if(isC3){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h1);
      f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C3",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt_C3",h1);
      f2->GetObject("h_inclRecoJetPt_flavor_C3",H2);
    }
    else{};
  }

  if(isC2){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h1);
      f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C2",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt_C2",h1);
      f2->GetObject("h_inclRecoJetPt_flavor_C2",H2);
    }
    else{};
  }

  if(isC1){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h1);
      f2->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt_C1",h1);
      f2->GetObject("h_inclRecoJetPt_flavor_C1",H2);
    }
    else{}
  }


  TH1D *binFinder = H2->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  bool skipGhosts = 0;
  double ghostSkipInt = 0.0;

  if(skipGhosts){
    ghostSkipInt = 1.0;
  }

  //H2->Draw();

  h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(0-smallShift));
  h2_add = (TH1D*) H2->ProjectionX("h2_add",binFinder->FindBin(ghostSkipInt+smallShift),binFinder->FindBin(22-smallShift));

  h2->Add(h2_add);
   
  // h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(17-smallShift));
  // h2_add = (TH1D*) H2->ProjectionX("h2_add",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  // h2_add2 = (TH1D*) H2->ProjectionX("h2_add2",binFinder->FindBin(18+smallShift),binFinder->FindBin(22-smallShift));

  //h2_add->Scale(1.2);

  // h2->Add(h2_add);
  // h2->Add(h2_add2);

  //h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(22-smallShift));
   
  // normalize
  double N1, N2, N3;

  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0.35,1,1);
  TPad *p2 = new TPad("p2","p2",0,0,1,0.35);
  p1->SetLogy();
  p1->SetBottomMargin(0.0);
  p1->SetLeftMargin(0.22);
  p2->SetTopMargin(0.0);
  p2->SetBottomMargin(0.33);
  p2->SetLeftMargin(0.22);
  p1->Draw();
  p2->Draw();
  p1->cd();

   
  //const int M = 9;
  //double muRelPtAxis[M] = {50,55,60,70,80,100,120,200,500};

  // ppMinBias vs PYTHIA binning
  //const int M = 9;
  //double muRelPtAxis[M] = {60,70,80,90,100,115,130,150,200};

  // const int M = 21;
  // double muRelPtAxis[M] = {60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,180,200,250,320,400,500};

  const int M = 15;
  double muRelPtAxis[M] = {80,90,100,110,120,130,140,150,160,180,200,250,320,400,500};

  // const int M = 11;
  // double muRelPtAxis[M] = {120,130,140,150,160,180,200,250,320,400,500};

  //const int M = 4;
  //double muRelPtAxis[M] = {60,80,120,200};
   

  // ppSingleMuon vs PYTHIA binning
  //const int M = 41;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,210,220,230,240,250,265,280,300,350,500};

  // PbPbSingleMuon 30-90% vs PYTHIA+HYDJET 30-90% binning
  // const int M = 25;
  // double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,145,155,170,190,230,300,500};

  // PbPbSingleMuon 0-30% vs PYTHIA+HYDJET 0-30% binning
  //const int M = 25;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,145,155,170,190,230,300,500};

  // PbPbMinBias 30-90% vs PYTHIA+HYDJET 30-90% binning
  //const int M = 25;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,145,155,170,190,230,300,500};

  // PbPbMinBias 30-90% vs PYTHIA+HYDJET 30-90% binning
  //const int M = 30;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,145,155,170,190,210,230,250,270,300,330,360,500};


   
  N1 = h1->Integral(h1->FindBin(muRelPtAxis[0]+smallShift),h1->FindBin(muRelPtAxis[M-1]-smallShift));
  N2 = h2->Integral(h2->FindBin(muRelPtAxis[0]+smallShift),h2->FindBin(muRelPtAxis[M-1]-smallShift));

  cout << "muRelPtAxis[0] = " << muRelPtAxis[0] << endl;
  cout << "muRelPtAxis[M-1] = " << muRelPtAxis[M-1] << endl;
   
  cout << "N1 = " << N1 << "   |   N2 = " << N2 << endl;

  h1->Scale(1.0/N1);
  h2->Scale(1.0/N2);
   
  TH1D *h1r, *h2r, *h3r;

  h1r = (TH1D*) h1->Rebin(M-1,"h1r",muRelPtAxis);
  h2r = (TH1D*) h2->Rebin(M-1,"h2r",muRelPtAxis);

  // h1r = (TH1D*) h1->Clone("h1r");
  // h2r = (TH1D*) h2->Clone("h2r");
   

  for(int i = 0; i < h1r->GetSize(); i++){
    double x1 = h1r->GetBinWidth(i);
    double y1 = h1r->GetBinContent(i);
    double z1 = h1r->GetBinError(i);
    double y2 = h2r->GetBinContent(i);
    double z2 = h2r->GetBinError(i);
    
    if(x1!=0){
      h1r->SetBinContent(i,y1/x1);
      h1r->SetBinError(i,z1/x1);
      h2r->SetBinContent(i,y2/x1);
      h2r->SetBinError(i,z2/x1);
    
    }
  }

  h1r->SetMarkerColor(kBlack);
  h2r->SetMarkerColor(kBlack);
   

  h1r->SetLineColor(kBlack);
  h2r->SetLineColor(kBlack);
   

  h1r->SetMarkerStyle(20);
  h2r->SetMarkerStyle(25);
   

  h1r->SetTitle("");
  h1r->GetXaxis()->SetTitle("");
  h1r->GetXaxis()->SetLabelSize(0);
  h1r->GetYaxis()->SetTitleOffset(1.15);
  //h1r->GetYaxis()->SetTitle("1/#font[52]{N}^{jet}_{tot} d#font[52]{N}^{jet}/d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
  h1r->GetYaxis()->SetTitle("1/#it{N}^{jet}_{tot} d#font[52]{N}^{jet}/d#it{p}_{T}^{jet} [GeV^{-1}]");
  h1r->SetStats(0);
  h1r->GetYaxis()->SetLabelSize(0.054);
  h1r->GetYaxis()->SetTitleSize(0.063);


  TH1D *r1, *r2;

  r1 = (TH1D*) h1r->Clone("r1");
  r1->Divide(h1r,h2r,1,1,"");
  r1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{jet} [GeV]");
  r1->GetYaxis()->SetTitleOffset(0.66);
  r1->GetYaxis()->SetTitle("   Data / MC ");
  //r1->GetYaxis()->SetTitle("PbPb / pp    ");
  //r1->GetYaxis()->SetTitle("unsmeared / smeared "); 
  r1->GetXaxis()->SetLabelSize(0.10);
  r1->GetYaxis()->SetLabelSize(0.10);
  //r1->GetYaxis()->SetTitleSize(0.09);          
  r1->GetYaxis()->SetTitleSize(0.11);
  r1->GetXaxis()->SetTitleSize(0.11);
  r1->GetYaxis()->SetNdivisions(606);
  r1->SetTitle("");
  r1->SetStats(0);


  TLegend *leg = new TLegend(0.53,0.68,0.78,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);


  if(isPP){
    if(isSingleMuon){
      leg->AddEntry(h1r,"pp SingleMuon","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"pp MinBias","p");
    }
    else if(isHardProbes){
      leg->AddEntry(h1r,"pp HighEGJet","p");
    }
    else{};
    leg->AddEntry(h2r,"PYTHIA","p");
  }

  else{
    if(isSingleMuon){
      leg->AddEntry(h1r,"PbPb SingleMuon","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"PbPb MinBias","p");
    }
    else if(isHardProbes){
      leg->AddEntry(h1r,"PbPb HardProbes","p");
    }
    else{};
    leg->AddEntry(h2r,"PYTHIA+HYDJET","p");
  }

  h1r->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
  //h1r->GetYaxis()->SetRangeUser(1e-5,0.5e2);
   
  h1r->Draw();
  h2r->Draw("same");

   
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.06);
  la->DrawLatexNDC(0.22,0.92,"CMS");
  la->SetTextFont(42);
  la->SetTextSize(0.045);
  la->DrawLatexNDC(0.32,0.92,"#sqrt{#font[52]{s}_{NN}} = 5.02 TeV");
  la->SetTextSize(0.044);
   
  if(isC4 || isC3 || isC2 || isC1){
    if(isSingleMuon){
      la->DrawLatexNDC(0.51,0.6,"#it{#mu}-tagged akCs4PF jets, |#it{#eta}^{jet}| < 1.6");
      la->DrawLatexNDC(0.58,0.52,"mu12 trigger");
      la->DrawLatexNDC(0.58,0.44,"#font[52]{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
    }
    else la->DrawLatexNDC(0.58,0.6,"akCs4PF jets, |#it{#eta}^{jet}| < 1.6");
    
    
  }
  else if(isPP){
    if(isSingleMuon){
      la->DrawLatexNDC(0.53,0.6,"#it{#mu}-tagged ak4PF jets, |#it{#eta}^{jet}| < 1.6");
      la->DrawLatexNDC(0.58,0.52,"mu12 trigger");
      la->DrawLatexNDC(0.58,0.44,"#font[52]{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
    }
    else la->DrawLatexNDC(0.58,0.6,"ak4PF jets, |#it{#eta}^{jet}| < 1.6");
    
  }

   

  if(isSingleMuon){
    
  }

  la->SetTextSize(0.05);
  if(isC4){
    la->DrawLatexNDC(0.32,0.8,"Cent. 50-80%");
  }
  else if(isC3){
    la->DrawLatexNDC(0.32,0.8,"Cent. 30-50%");
  }
  else if(isC2){
    la->DrawLatexNDC(0.32,0.8,"Cent. 10-30%");
  }
  else if(isC1){
    la->DrawLatexNDC(0.35,0.8,"Cent. 0-10%");
  }
   


  p2->cd();
  double ratio_low = 0.4;
  double ratio_high = 1.6;
  r1->GetYaxis()->SetRangeUser(ratio_low,ratio_high);
  r1->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
  r1->SetMarkerSize(0.8);
  r1->Draw();
  //r1->Fit("fitFxn");

  TLine *line = new TLine(muRelPtAxis[0],1,muRelPtAxis[M-1],1);
  line->SetLineStyle(9);
  line->Draw();

  line->SetLineStyle(2);
  line->DrawLine(muRelPtAxis[0],1.2,muRelPtAxis[M-1],1.2);
  line->DrawLine(muRelPtAxis[0],0.8,muRelPtAxis[M-1],0.8);

  //line->SetLineStyle(2);
  //line->DrawLine(60,ratio_low,60,ratio_high);

  if(isPP){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/pp/jetPt_SingleMuon_pp_mu12.pdf");
    }
    else if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/MinBias/pp/jetPt_MinBias_pp_mu12.pdf");
    }
    else if(isHardProbes){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/HardProbes/pp/jetPt_HardProbes_pp_mu12.pdf");
    }
    else{};
  }

  if(isC4){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C4/jetPt_SingleMuon_C4_mu12.pdf");
    }
    else if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/MinBias/C4/jetPt_MinBias_C4_mu12.pdf");
    }
    else if(isHardProbes){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/HardProbes/C4/jetPt_HardProbes_C4_mu12.pdf");
    }
    else{};
  }

  if(isC3){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C3/jetPt_SingleMuon_C3_mu12.pdf");
    }
    else if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/MinBias/C3/jetPt_MinBias_C3_mu12.pdf");
    }
    else if(isHardProbes){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/HardProbes/C3/jetPt_HardProbes_C3_mu12.pdf");
    }
    else{};
  }
  
  if(isC2){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C2/jetPt_SingleMuon_C2_mu12.pdf");
    }
    else if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/MinBias/C2/jetPt_MinBias_C2_mu12.pdf");
    }
    else if(isHardProbes){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/HardProbes/C2/jetPt_HardProbes_C2_mu12.pdf");
    }
    else{};
  }

  if(isC1){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/SingleMuon/C1/jetPt_SingleMuon_C1_mu12.pdf");
    }
    else if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/MinBias/C1/jetPt_MinBias_C1_mu12.pdf");
    }
    else if(isHardProbes){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetPt/HardProbes/C1/jetPt_HardProbes_C1_mu12.pdf");
    }
    else{};
  }


}
