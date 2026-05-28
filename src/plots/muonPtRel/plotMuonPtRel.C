
#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"

TString makeJetPtString(double jetPtMin,
			double jetPtMax){

  TString result = "";

  if(jetPtMin < 100 && jetPtMax < 100) result = Form("pTjet-%2.0fto%2.0f",jetPtMin,jetPtMax);
  else if(jetPtMin < 100 && jetPtMax >= 100) result = Form("pTjet-%2.0fto%3.0f",jetPtMin,jetPtMax);
  else if(jetPtMin >= 100 && jetPtMax >= 100) result = Form("pTjet-%3.0fto%3.0f",jetPtMin,jetPtMax);
  else{};

  return result;
  
}


void plotMuonPtRel(bool isPP = 0,
		   bool isC4 = 0,
		   bool isC3 = 0,
		   bool isC2 = 1,
		   bool isC1 = 0,
		   bool isSingleMuon = 1,
		   bool isMinBias = 0,
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
    else{};

    f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_pThat30_mu12_pTmu15_hiBinReweight_vzReweight);
     
  }
   

   
  TH2D *H1, *H2;
  TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;


  if(isPP){
    f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn",H1);
    f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_T0",H2);
  }
  else if(isC4){
    f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C4",H1);
    f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C4T0",H2);
  }
  else if(isC3){
    f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C3",H1);
    f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C3T0",H2);
  }
  else if(isC2){
    f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C2",H1);
    f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C2T0",H2);
  }
  else if(isC1){
    f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_C1",H1);
    f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_allJets_C1T0",H2);
  }
  else{};

   
   
   
  TH1D *binFinder = H2->ProjectionY();
  TAxis *yaxis = binFinder->GetXaxis();
  double smallShift = 0.01;

  bool skipGhosts = 0;
  double ghostSkipInt = 0.0;

  if(skipGhosts){
    ghostSkipInt = 1.0;
  }

  //H2->Draw();

  
  h1 = (TH1D*) H1->ProjectionX("h1",binFinder->FindBin(jetPtMin+smallShift),binFinder->FindBin(jetPtMax-smallShift));
  h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(jetPtMin+smallShift),binFinder->FindBin(jetPtMax-smallShift));

   
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

 
  // ppMinBias vs PYTHIA binning
  const int M = 20;
  double muRelPtAxis[M] = {0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.6,1.8,2,2.4,2.8,3.5,5};

   

   
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
  h1r->GetYaxis()->SetTitle("1/#it{N}^{#it{#mu}}_{tot} d#it{N}^{#it{#mu}}/d#it{p}_{T}^{rel} [GeV^{-1}]");
  h1r->SetStats(0);
  h1r->GetYaxis()->SetLabelSize(0.057);
  h1r->GetYaxis()->SetTitleSize(0.068);


  TH1D *r1, *r2;

  r1 = (TH1D*) h1r->Clone("r1");
  r1->Divide(h1r,h2r,1,1,"");
  r1->GetXaxis()->SetTitle("Muon #it{p}_{T}^{rel} [GeV]");
  r1->GetYaxis()->SetTitleOffset(0.66);
  r1->GetYaxis()->SetTitle("  Data / MC ");
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

  if(isC4 || isC3 || isC2 || isC1){
    if(isSingleMuon){
      leg->AddEntry(h1r,"PbPb SingleMuon","p");
      leg->AddEntry(h2r,"PYTHIA+HYDJET","p");
    }
    else if(isMinBias){
      leg->AddEntry(h1r,"PbPb MinBias","p");
      leg->AddEntry(h2r,"HYDJET","p");
    }
    else{};
     
  }

  h1r->GetYaxis()->SetRangeUser(0,1.3);
  h1r->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
   
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

  double la_x_pos = 0.49;
  double la_y_pos = 0.58;
   
  if(isC4 || isC3 || isC2 || isC1){
    la->DrawLatexNDC(la_x_pos,la_y_pos,"#it{#mu}-tagged akCs4PF jets");
  }
  else if(isPP){
    la->DrawLatexNDC(la_x_pos,la_y_pos,"#it{#mu}-tagged ak4PF jets");
  }


  la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,Form("%3.0f < #font[52]{p}_{T}^{jet} (GeV) < %3.0f, |#it{#eta}^{jet}| < 1.6",jetPtMin,jetPtMax));
   

  if(isSingleMuon){
    la->DrawLatexNDC(la_x_pos,la_y_pos-0.2,"#it{p}_{T}^{#it{#mu}} > 15 GeV, |#it{#eta}^{#mu}| < 2.0");
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

  TString jetPtString = makeJetPtString(jetPtMin,jetPtMax);
   

  if(isPP){
    if(isSingleMuon){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/SingleMuon/pp/muonPtRel_SingleMuon_pp_mu12_%s.pdf",jetPtString.Data()));
    }
    if(isMinBias){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/MinBias/pp/muonPtRel_MinBias_pp_mu12_%s.pdf",jetPtString.Data()));
    }
  }

  else if(isC4){
    if(isSingleMuon){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/SingleMuon/C4/muonPtRel_SingleMuon_C4_mu12_%s.pdf",jetPtString.Data()));
    }
    if(isMinBias){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/MinBias/C4/muonPtRel_MinBias_C4_mu12_%s.pdf",jetPtString.Data()));
    }
  }

  else if(isC3){
    if(isSingleMuon){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/SingleMuon/C3/muonPtRel_SingleMuon_C3_mu12_%s.pdf",jetPtString.Data()));
    }
    if(isMinBias){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/MinBias/C3/muonPtRel_MinBias_C3_mu12_%s.pdf",jetPtString.Data()));
    }
  }

  else if(isC2){
    if(isSingleMuon){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/SingleMuon/C2/muonPtRel_SingleMuon_C2_mu12_%s.pdf",jetPtString.Data()));
    }
    if(isMinBias){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/MinBias/C2/muonPtRel_MinBias_C2_mu12_%s.pdf",jetPtString.Data()));
    }
  }

  else if(isC1){
    if(isSingleMuon){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/SingleMuon/C1/muonPtRel_SingleMuon_C1_mu12_%s.pdf",jetPtString.Data()));
    }
    if(isMinBias){
      c1->SaveAs(Form("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/muonPtRel/MinBias/C1/muonPtRel_MinBias_C1_mu12_%s.pdf",jetPtString.Data()));
    }
  }

  else{};

  /*

   */

}
