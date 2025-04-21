


void pthatCut(){

  TFile *file = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/fineCentBins/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_removeHYDJETjet_jetTrkMaxFilter_vzReweight_hiBinReweight_weightCut0p005_fineCentBins_projectableTemplates.root");

  const int N_val = 8;
  double pthatCutValues[N_val] = {15,20,25,30,35,40,45,50};

  TH2D *H;
  file->GetObject("h_recoJetPt_pthat_C4",H);

  TH1D *h[N_val];
  TH1D *r[N_val-1];

  for(int i = 0; i < N_val; i++){
    
    h[i] = (TH1D*) H->ProjectionX(Form("h_%i",i),H->GetYaxis()->FindBin(pthatCutValues[i]),H->GetYaxis()->FindBin(500.0));

    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);

    if(i > 0){

      r[i-1] = (TH1D*) h[i]->Clone(Form("r_%i",i));
      r[i-1]->Divide(h[i],h[0],1,1,"B");		     
      
    }

  }
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad1 = new TPad("pad1","pad1",0,0.5,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.5);

  pad1->SetLeftMargin(0.15);
  pad2->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0);
  pad2->SetBottomMargin(0.15);
  pad2->SetTopMargin(0);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  h[0]->SetStats(0);
  h[0]->SetTitle("");
  h[0]->GetYaxis()->SetTitle("");
  for(int i = 0; i < N_val; i++){
    if(i==0) h[i]->Draw();
    else h[i]->Draw("same");
  }
 
  pad2->cd();
  for(int i = 0; i < N_val-1; i++){
    if(i==0) r[i]->Draw();
    else r[i]->Draw("same");
  }
   TLegend *leg = new TLegend(0.6,0.3,0.88,0.5);
  leg->SetBorderSize(0);
  for(int i = 0; i < N_val-1;i++){
    leg->AddEntry(r[i],Form("#hat{#it{p}}_{T} > %3.0f",pthatCutValues[i+1]));
  }
  leg->Draw();


}
