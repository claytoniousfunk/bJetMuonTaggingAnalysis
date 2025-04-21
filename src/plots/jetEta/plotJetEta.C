


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"




void plotJetEta(bool isPP = 1, bool isC2 = 0, bool isC1 = 0, bool isSingleMuon = 1, bool isMinBias = 0, bool isMu7 = 0, bool isMu12 = 1){

  

  TFile *f1, *f2, *f3;


  if(isPP){

    if(isSingleMuon){
      if(isMu7){
	f1 = TFile::Open(goldenFile_pp_SingleMuon_mu7);
      }
      else if(isMu12){
	f1 = TFile::Open(goldenFile_pp_SingleMuon_mu12_newJetBins);
      }
      else{};
    }
    else if(isMinBias){
      
    }
    else{};

    //f2 = TFile::Open(goldenFile_PYTHIA_mu12_pThat15_JERsmear);
    if(isMu7){
      f2 = TFile::Open(goldenFile_PYTHIA_mu7_pThat30);
    }
    else if(isMu12){
      f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/obsidian/PYTHIA_DiJet_withGS_mu12_tight_pTmu-14_pThat-45_removeHYDJETjet_jetTrkMaxFilter_vzReweight_jetPtReweight_newJetBins.root");
    }
    else{};
     
  }

  if(isC2 || isC1){

    if(isSingleMuon){
      if(isMu7){
	f1 = TFile::Open(goldenFile_PbPb_SingleMuon_mu7);
	f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu7_pThat30);
      }
      else if(isMu12){
	//f1 = TFile::Open(goldenFile_PbPb_SingleMuon_mu12_newJetBins);
	//f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins);

	f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/obsidian/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_newJetBins_fineCentBins.root");
	f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/obsidian/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-45_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_jetPtReweight_newJetBins_fineCentBins.root");

      }
      else{};
    }
    else if(isMinBias){
      
    }
    else{};

     
     
  }

   

   
  TH2D *H1, *H2;
  TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;
  TH1D *h2_add2;


  if(isPP){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn",h1);
      f2->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetEta",h1);
      f2->GetObject("h_inclRecoJetEta_flavor",H2);
    }
    else{};
  }

  if(isC2){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_C1",h1);
      f2->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetEta_C2",h1);
      f2->GetObject("h_inclRecoJetEta_flavor_C2",H2);
    }
    else{};
  }

  if(isC1){
    if(isSingleMuon){
      f1->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_C1",h1);
      //f2->GetObject("h_inclGenJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H1);
      //f2->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H2);
      f2->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H2);
    }
    else if(isMinBias){
      f1->GetObject("h_inclRecoJetEta_C1",h1);
      //f2->GetObject("h_inclGenJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H1);
      f2->GetObject("h_inclRecoJetEta_inclRecoMuonTag_triggerOn_flavor_C1",H2);
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

  //h1 = (TH1D*) H1->ProjectionX("h1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(0-smallShift));
  //h1_add = (TH1D*) H1->ProjectionX("h1_add",binFinder->FindBin(ghostSkipInt+smallShift),binFinder->FindBin(22-smallShift));

  //h1->Add(h1_add);
   
  h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(17-smallShift));
  h2_add = (TH1D*) H2->ProjectionX("h2_add",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  h2_add2 = (TH1D*) H2->ProjectionX("h2_add2",binFinder->FindBin(18+smallShift),binFinder->FindBin(22-smallShift));

  h2_add->Scale(1.2);

  h2->Add(h2_add);
  h2->Add(h2_add2);
   
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
  h1r->GetYaxis()->SetLabelSize(0.057);
  h1r->GetYaxis()->SetTitleSize(0.068);


  TH1D *r1, *r2;

  r1 = (TH1D*) h1r->Clone("r1");
  r1->Divide(h1r,h2r,1,1,"");
  r1->GetXaxis()->SetTitle("#it{#eta}^{jet}");
  r1->GetYaxis()->SetTitleOffset(0.66);
  r1->GetYaxis()->SetTitle("DATA / MC   ");
  //r1->GetYaxis()->SetTitle("PbPb / pp    ");
  //r1->GetYaxis()->SetTitle("unsmeared / smeared "); 
  r1->GetXaxis()->SetLabelSize(0.11);
  r1->GetYaxis()->SetLabelSize(0.11);
  //r1->GetYaxis()->SetTitleSize(0.09);          
  r1->GetYaxis()->SetTitleSize(0.12);
  r1->GetXaxis()->SetTitleSize(0.12);
  r1->GetYaxis()->SetNdivisions(606);
  r1->SetTitle("");
  r1->SetStats(0);


  TLegend *leg = new TLegend(0.55,0.68,0.78,0.88);
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

  if(isC2 || isC1){
    if(isSingleMuon){
      leg->AddEntry(h1r,"PbPb SingleMuon","p");
      //leg->AddEntry(h1r,"PYTHIA+HYDJET Gen","p");
      leg->AddEntry(h2r,"PYTHIA+HYDJET Reco","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"PbPb MinBias","p");
      //leg->AddEntry(h1r,"HYDJET Gen","p");
      leg->AddEntry(h2r,"HYDJET Reco","p");
    }
    else{};
     
  }

  h1r->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
  h1r->GetYaxis()->SetRangeUser(0.13,0.72);
  h1r->Draw();
  h2r->Draw("same");

   
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.06);
  la->DrawLatexNDC(0.22,0.92,"CMS");
  la->SetTextFont(42);
  la->SetTextSize(0.045);
  if(isMinBias){
    la->DrawLatexNDC(0.32,0.92,"#sqrt{#font[52]{s}_{NN}} = 5.02 TeV, inclusive jets");
  }
  else if(isSingleMuon){
    la->DrawLatexNDC(0.32,0.92,"#sqrt{#font[52]{s}_{NN}} = 5.02 TeV, muon-tagged jets");
  }

  la->SetTextSize(0.044);
   
  if(isC2 || isC1){
    la->DrawLatexNDC(0.58,0.6,"akCs4PF jets, #it{p}_{T}^{jet} > 80 GeV");
  }
  else if(isPP){
    la->DrawLatexNDC(0.58,0.6,"ak4PF jets, #it{p}_{T}^{jet} > 80 GeV");
  }

   

  if(isSingleMuon){

    //la->DrawLatexNDC(0.58,0.5,"#font[52]{p}_{T}^{#mu} > 7 GeV, |#eta^{#mu}| < 2.0");
    if(isMu7) la->DrawLatexNDC(0.58,0.5,"9 < #font[52]{p}_{T}^{#it{#mu}} (GeV) < 14, |#eta^{#it{#mu}}| < 2.0");
    if(isMu12) la->DrawLatexNDC(0.58,0.5,"#font[52]{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}}| < 2.0");
  }

  la->SetTextSize(0.05);
  if(isC2){
    //la->DrawLatexNDC(0.35,0.8,"Cent. 30-90%");
    //la->DrawLatexNDC(0.35,0.8,"Cent. 50-90%");
    //la->DrawLatexNDC(0.35,0.8,"Cent. 30-50%");
    //la->DrawLatexNDC(0.35,0.8,"Cent. 10-30%");
    la->DrawLatexNDC(0.35,0.8,"Cent. 0-10%");
  }
  else if(isC1){
    la->DrawLatexNDC(0.35,0.8,"Cent. 0-30%");
  }
   


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
      if(isMu7){
	c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/pp/jetPt_SingleMuon_pp_mu7.pdf");
      }
      else if(isMu12){
	c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/pp/jetPt_SingleMuon_pp_mu12.pdf");
      }
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt");
    }
  }

  if(isC2){
    if(isSingleMuon){
      if(isMu7){
	c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/C2/jetPt_SingleMuon_C2_mu7.pdf");
      }
      else if(isMu12){
	c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/C2/jetPt_SingleMuon_C2_mu12.pdf");
      }
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt");
    }
  }

  if(isC1){
    if(isSingleMuon){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/C1/jetPt_SingleMuon_C1_mu7.pdf");
    }
    if(isMinBias){
      c1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/jetPt/SingleMuon/C1/jetPt_SingleMuon_C1_mu12.pdf");
    }
  }


}
