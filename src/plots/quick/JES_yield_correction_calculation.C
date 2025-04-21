

TFile *f1, *f2, *f3, *f4;
TH2D *H1, *H2, *H3, *H4;
TH1D *h1, *h2, *h3, *h4, *r1, *r2, *rr;
TCanvas *c1;
TPad *p1;

void setup_canvas(TCanvas *canvas, TString canvas_name, TPad *pad, TString pad_name){
  canvas = new TCanvas(canvas_name,canvas_name,700,700);
  canvas->cd();
  pad = new TPad(pad_name,pad_name,0,0,1,1);
  //pad->SetLogy();
  pad->Draw();
  pad->cd();
  return;
}

int main(){

  // f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_JERsmear.root");
  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets.root");

  //f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets.root");
  //f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_doBJetNeutrinoEnergyShift.root");
  //f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_muTaggedJets_doNeutrinoEnergyAddition.root");

  // f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets.root");
  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_doBJetNeutrinoEnergyShift.root");
  // f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_doNeutrinoEnergyAddition.root");

  // f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_pTcut-30.root");
  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_doBJetNeutrinoEnergyShift_pTcut-30.root");
  // f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-30_muTaggedJets_doNeutrinoEnergyAddition_pTcut-30.root");

  // f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets.root");
  // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_JERsmear.root");
  // f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/PYTHIA_mu12_response_pThat-15_inclJets_doJERCorrection.root");
  //f4 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/official/");
  
  f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H1);
  f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H2);
  f3->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H3);
  //f4->GetObject("h_matchedRecoJetPt_genJetPt_bJets",H4);

  // f1->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H1);
  // f2->GetObject("h_matchedRecoJetPt_genJetPt_allJets",H2);

  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");
  h3 = (TH1D*) H3->ProjectionX("h3");

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kRed-4);



  r1 = (TH1D*) h2->Clone("r1");
  r1->Divide(h2,h1,1,1,"B");
  r2 = (TH1D*) h3->Clone("r2");
  r2->Divide(h3,h1,1,1,"B");
  rr = (TH1D*) r1->Clone("rr");
  rr->Divide(r1,r2,1,1,"B");

  // draw tings
  setup_canvas(c1,"c1",p1,"p1");

  
  //h1->Draw();
  //h2->Draw("same");
  //r1->GetYaxis()->SetRangeUser(0,2.5);
  //r1->Draw();
  r2->Draw();

  // r2->GetYaxis()->SetRangeUser(0,2.5);
  // r2->Draw();
  
  //rr->Draw();
  


}

int JES_yield_correction_calculation(){
  main();
  return 0;
}
