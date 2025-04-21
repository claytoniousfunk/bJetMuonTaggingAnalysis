

TFile *file_JES_incl, *file_JES_muTagged, *file_JES_nuCorr, *file_JES_nuAdd, *file_JES_JERCorr;
TFile *file_JER_incl, *file_JER_muTagged, *file_JER_nuCorr, *file_JER_nuAdd, *file_JER_JERCorr;
TCanvas *canv_1;
TPad *pad_1_upper, *pad_1_lower;
TCanvas *canv_2;
TPad *pad_2_upper, *pad_2_lower;
TH1D *h1, *h2, *h3, *h4, *h5;
TH1D *g1, *g2, *g3, *g4, *g5;
TH1D *r2, *r3, *r4;
TH1D *R2, *R3, *R4;

void configureCanvas(TCanvas *canv, TPad *pad1, TPad *pad2){

  canv->cd();
  pad1->SetLeftMargin(0.15);
  pad2->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0.0);
  pad2->SetBottomMargin(0.17);
  pad1->SetTopMargin(0.15);
  pad2->SetTopMargin(0.0);
  pad1->Draw();
  pad2->Draw();
  

}

void stylizeHistograms(TH1D *hist1, TH1D *hist2, TH1D *hist3, TH1D *hist4, TH1D *hist5){

  hist1->SetLineColor(kBlack);
  hist2->SetLineColor(kBlue-4);
  hist3->SetLineColor(kBlue-4);
  hist4->SetLineColor(kBlue-4);
  hist5->SetLineColor(kBlack);

  hist1->SetLineWidth(2);
  hist2->SetLineWidth(2);
  hist3->SetLineWidth(2);
  hist4->SetLineWidth(2);
  hist5->SetLineWidth(2);

  hist1->SetLineStyle(1);
  hist2->SetLineStyle(1);
  hist3->SetLineStyle(2);
  hist4->SetLineStyle(2);
  hist5->SetLineStyle(2);

  hist1->SetStats(0);
  hist2->SetStats(0);
  hist3->SetStats(0);
  hist4->SetStats(0);
  hist5->SetStats(0);

  hist1->SetTitle("");
  hist2->SetTitle("");
  hist3->SetTitle("");
  hist4->SetTitle("");
  hist5->SetTitle("");

  double titleSize = 0.06;
  double labelSize = 0.05;
  hist1->GetYaxis()->SetTitleSize(titleSize);
  hist1->GetXaxis()->SetTitleSize(titleSize);
  hist1->GetYaxis()->SetLabelSize(labelSize);
  hist1->GetXaxis()->SetLabelSize(labelSize);

  hist2->GetYaxis()->SetTitleSize(titleSize);
  hist2->GetXaxis()->SetTitleSize(titleSize);
  hist2->GetYaxis()->SetLabelSize(labelSize);
  hist2->GetXaxis()->SetLabelSize(labelSize);

  hist3->GetYaxis()->SetTitleSize(titleSize);
  hist3->GetXaxis()->SetTitleSize(titleSize);
  hist3->GetYaxis()->SetLabelSize(labelSize);
  hist3->GetXaxis()->SetLabelSize(labelSize);

  hist4->GetYaxis()->SetTitleSize(titleSize);
  hist4->GetXaxis()->SetTitleSize(titleSize);
  hist4->GetYaxis()->SetLabelSize(labelSize);
  hist4->GetXaxis()->SetLabelSize(labelSize);

  hist5->GetYaxis()->SetTitleSize(titleSize);
  hist5->GetXaxis()->SetTitleSize(titleSize);
  hist5->GetYaxis()->SetLabelSize(labelSize);
  hist5->GetXaxis()->SetLabelSize(labelSize);

  
  return;
}

void makeRatio(TH1D *hist1, TH1D *hist2, TH1D *ratio, bool doBinomialDivision){
  ratio = (TH1D*) hist1->Clone("ratio");
  if(doBinomialDivision){
    ratio->Divide(hist1,hist2,1,1,"B");
  }
  else{
    ratio->Divide(hist1,hist2,1,1,"");
  }
  return;
}



void jetEnergyResolution_plots(){

  file_JES_incl = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_incl.root");
  file_JES_muTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_muTagged.root");
  file_JES_nuCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_nuCorr.root");
  file_JES_nuAdd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_nuAdd.root");
  file_JES_JERCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JES/JES_JERCorr.root");

  file_JER_incl = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_incl.root");
  file_JER_muTagged = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_muTagged.root");
  file_JER_nuCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_nuCorr.root");
  file_JER_nuAdd = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_nuAdd.root");
  file_JER_JERCorr = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_JERCorr.root");

  file_JES_incl->GetObject("JES_result_i",h1);
  file_JES_muTagged->GetObject("JES_result_b",h2);
  file_JES_nuCorr->GetObject("JES_result_b",h3);
  file_JES_nuAdd->GetObject("JES_result_b",h4);
  file_JES_JERCorr->GetObject("JES_result_i",h5);

  file_JER_incl->GetObject("JER_result_i",g1);
  file_JER_muTagged->GetObject("JER_result_b",g2);
  file_JER_nuCorr->GetObject("JER_result_b",g3);
  file_JER_nuAdd->GetObject("JER_result_b",g4);
  file_JER_JERCorr->GetObject("JER_result_i",g5);

  canv_1 = new TCanvas("canv_1","canv_1",700,700);
  pad_1_upper = new TPad("pad_1_upper","pad_1_upper",0,0.5,1,1);
  pad_1_lower = new TPad("pad_1_lower","pad_1_lower",0,0.0,1,0.5);

  configureCanvas(canv_1,pad_1_upper,pad_1_lower);

  stylizeHistograms(h1,h2,h3,h4,h5);
  stylizeHistograms(g1,g2,g3,g4,g5);
  
  pad_1_upper->cd();
  h1->GetYaxis()->SetRangeUser(0.8,1.2);
  h1->GetYaxis()->SetTitle("#it{#mu}(#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet})");
  h1->Draw();
  h2->Draw("same");
  //h3->Draw("same");
  h4->Draw("same");
  makeRatio(h2,h1,r2,0);
  makeRatio(h3,h1,r3,0);
  makeRatio(h4,h1,r4,0);
  pad_1_lower->cd();
  g1->GetYaxis()->SetRangeUser(0.0,0.3);
  g1->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  g1->GetYaxis()->SetTitle("#it{#sigma}(#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet})");
  g1->Draw();
  g3->Draw("same");
  g5->Draw("same");
  //g3->Draw("same");
  //g4->Draw("same");
  



  //r2->GetYaxis()->SetRangeUser(0.8,1.2);
  //r2->Draw();
  //r3->Draw("same");
  //r4->Draw("same");

  canv_2 = new TCanvas("canv_2","canv_2",700,700);
  pad_2_upper = new TPad("pad_2_upper","pad_2_upper",0,0.5,1,1);
  pad_2_lower = new TPad("pad_2_lower","pad_2_lower",0,0.0,1,0.5);
  configureCanvas(canv_2,pad_2_upper,pad_2_lower);
  
  pad_2_upper->cd();
  
}
