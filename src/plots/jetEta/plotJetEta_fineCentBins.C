


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"




void plotJetEta_fineCentBins(bool isPP = 1,
			     bool isC4 = 0,
			     bool isC3 = 0,
			     bool isC2 = 0,
			     bool isC1 = 0,
			     bool isSingleMuon = 1,
			     bool isMinBias = 0,
			     bool isHardProbes = 0,
			     double jetPtMin = 80,
			     double jetPtMax = 500){

  

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
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn",H2);
    }
    else if(isMinBias || isHardProbes){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta",H2);
    }
    else{};
  }

  else if(isC4){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C4",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C4",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_C4",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_C4",H2);
    }
    else{};
  }

  else if(isC3){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C3",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C3",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_C3",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_C3",H2);
    }
    else{};
  }

  else if(isC2){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C2",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C2",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_C2",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_C2",H2);
    }
    else{};
  }

  else if(isC1){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C1",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_inclRecoMuonTag_triggerOn_C1",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetPt_inclRecoJetEta_C1",H1);
      f2->GetObject("h_inclRecoJetPt_inclRecoJetEta_C1",H2);
    }
    else{};
  }

  else{};


  TH1D *binFinder = H2->ProjectionX();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  h1 = (TH1D*) H1->ProjectionY("h1",binFinder->FindBin(jetPtMin+smallShift),binFinder->FindBin(jetPtMax-smallShift));
  h2 = (TH1D*) H2->ProjectionY("h2",binFinder->FindBin(jetPtMin+smallShift),binFinder->FindBin(jetPtMax-smallShift));

   
  // normalize
  double N1, N2, N3;

  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  c1->cd();
  TPad *p1 = new TPad("p1","p1",0,0.35,1,1);
  TPad *p2 = new TPad("p2","p2",0,0,1,0.35);
  //p1->SetLogy();
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

  // const int M = 17;
  // double muRelPtAxis[M] = {-1.6,-1.4,-1.2,-1.0,-0.8,-0.6,-0.4,-0.2,0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6};

  const int M = 33;
  double muRelPtAxis[M] = {-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1.0,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6};

  //const int M = 4;
  //double muRelPtAxis[M] = {60,80,120,200};
   

  // ppSingleMuon vs PYTHIA binning
  //const int M = 41;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,140,145,150,155,160,165,170,175,180,185,190,195,200,210,220,230,240,250,265,280,300,350,500};

  // PbPbSingleMuon 30-90% vs PYTHIA+HYDJET 30-90% binning
  //const int M = 25;
  //double muRelPtAxis[M] = {50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125,130,135,145,155,170,190,230,300,500};

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

  //h1r = (TH1D*) h1->Clone("h1r");
  //h2r = (TH1D*) h2->Clone("h2r");
   

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
  h1r->GetYaxis()->SetTitle("1/#it{N}^{jet} d#it{N}^{jet}/d#it{#eta}^{jet}");
  h1r->SetStats(0);
  h1r->GetYaxis()->SetLabelSize(0.052);
  h1r->GetYaxis()->SetTitleSize(0.063);


  TH1D *r1, *r2;

  r1 = (TH1D*) h1r->Clone("r1");
  r1->Divide(h1r,h2r,1,1,"");
  r1->GetXaxis()->SetTitle("#it{#eta}^{jet}");
  r1->GetYaxis()->SetTitleOffset(0.66);
  r1->GetYaxis()->SetTitle("  Data / MC ");
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


  TLegend *leg = new TLegend(0.55,0.72,0.78,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);


  if(isPP){
    if(isSingleMuon){
      leg->AddEntry(h1r,"pp SingleMuon","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"pp MinBias","p");
    }
    else{};
    leg->AddEntry(h2r,"PYTHIA","p");
  }

  if(isC4 || isC3 || isC2 || isC1){
    if(isSingleMuon){
      leg->AddEntry(h1r,"PbPb SingleMuon","p");
      //leg->AddEntry(h1r,"PYTHIA+HYDJET Gen","p");
      leg->AddEntry(h2r,"PYTHIA+HYDJET","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"PbPb MinBias","p");
      //leg->AddEntry(h1r,"HYDJET Gen","p");
      leg->AddEntry(h2r,"HYDJET Reco","p");
    }
    else{};
     
  }

  h1r->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
  h1r->GetYaxis()->SetRangeUser(0.,1.2);
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
    if(isSingleMuon) la->DrawLatexNDC(0.48,0.66,"#it{#mu}-tagged akCs4PF jets, mu12 trigger");
    else la->DrawLatexNDC(0.58,0.66,"akCs4PF jets");

    la->DrawLatexNDC(0.58,0.58,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtMin,jetPtMax));
  }
  else if(isPP){
    if(isSingleMuon) la->DrawLatexNDC(0.48,0.66,"#it{#mu}-tagged ak4PF jets, mu12 trigger");
    else la->DrawLatexNDC(0.58,0.66,"ak4PF jets");

    la->DrawLatexNDC(0.58,0.58,Form("%3.0f < #it{p}_{T}^{jet} (GeV) < %3.0f",jetPtMin,jetPtMax));
  }

   

  if(isSingleMuon){

    //la->DrawLatexNDC(0.58,0.5,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#eta^{#mu}| < 2.0");
    
    la->DrawLatexNDC(0.58,0.5,"#font[52]{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  }

  la->SetTextSize(0.05);
  if(isC4){
    la->DrawLatexNDC(0.35,0.8,"Cent. 50-80%");
  }
  else if(isC3){
    la->DrawLatexNDC(0.35,0.8,"Cent. 30-50%");
  }
  else if(isC2){
    la->DrawLatexNDC(0.35,0.8,"Cent. 10-30%");
  }
  else if(isC1){
    la->DrawLatexNDC(0.35,0.8,"Cent. 0-10%");
  }
  else{};
   


  p2->cd();
  double ratio_low = 0.3;
  double ratio_high = 1.7;
  r1->GetYaxis()->SetRangeUser(ratio_low,ratio_high);
  r1->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
  r1->SetMarkerSize(0.8);
  r1->Draw();

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
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/pp/jetEta_SingleMuon_pp_mu12.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/MinBias/pp/jetEta_MinBias_pp_mu12.pdf");
    }
  }

  else if(isC4){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C4/jetEta_SingleMuon_C4_mu12.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/MinBias/C4/jetEta_MinBias_C4_mu12.pdf");
    }
  }

  else if(isC3){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C3/jetEta_SingleMuon_C3_mu12.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/MinBias/C3/jetEta_MinBias_C3_mu12.pdf");
    }
  }

  else if(isC2){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C2/jetEta_SingleMuon_C2_mu12.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/MinBias/C2/jetEta_MinBias_C2_mu12.pdf");
    }
  }

  else if(isC1){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/SingleMuon/C1/jetEta_SingleMuon_C1_mu12.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/jetEta/MinBias/C1/jetEta_MinBias_C1_mu12.pdf");
    }
  }

  else{};




}
