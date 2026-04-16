


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"
#include "../../../headers/functions/divideByBinwidth.h"

void plotMuonPtRel_jetPtDependence_MC(bool isPP = 1,
				      bool isC4 = 0,
				      bool isC3 = 0,
				      bool isC2 = 0,
				      bool isC1 = 0){

  


  const int N_edges = 6;
  double jetPt_edges[N_edges] = {80,100,120,150,200,300};

  TLatex *la = new TLatex();
  la->SetTextFont(42);

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
   TFile *f1, *f2, *f3;

   TString canvSaveSuffix = "";
   
   if(isPP){
    
     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-7-8.root");
     f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-7-8.root");

     
     
   }

   else{

     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
     f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
     f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
    
   }

   
   

   
   TH2D *H1, *H2, *H3;
   //TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;
   TH1D *h1[N_edges-1], *h2[N_edges-1];
   TH1D *r[N_edges-2];


   if(isPP){
    
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_T0",H1);
     canvSaveSuffix = "pp";
 
   }

   else if(isC4){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H2);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H3);
     H1->Add(H2);
     H1->Add(H3);
     canvSaveSuffix = "C4";

   }

   else if(isC3){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H2);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H3);
     H1->Add(H2);
     H1->Add(H3);
     canvSaveSuffix = "C3";

   }

   else if(isC2){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H2);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H3);
     H1->Add(H2);
     H1->Add(H3);
     canvSaveSuffix = "C2";

   }

   else if(isC1){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H3);
     H1->Add(H2);
     H1->Add(H3);
     canvSaveSuffix = "C1";

   }

   TH1D *binFinder = H1->ProjectionY();
   TAxis *yaxis = binFinder->GetXaxis();
   double smallShift = 0.01;

   TLegend *leg = new TLegend(0.5,0.5,0.88,0.88);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05
);

   TString jetPtBinStrings[N_edges-1] = {"80 < #it{p}_{T}^{jet} (GeV) < 100",
					 "100 < #it{p}_{T}^{jet} (GeV) < 120",
					 "120 < #it{p}_{T}^{jet} (GeV) < 150",
					 "150 < #it{p}_{T}^{jet} (GeV) < 200",
					 "200 < #it{p}_{T}^{jet} (GeV) < 300"};   

   const int M = 11;
   double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.4,2.0,3.0,3.8,5.0}; // M = 20;

   for(int i = 0; i < N_edges-1; i++){

     std::cout << "projection jet bin " << jetPt_edges[i] << " -- " << jetPt_edges[i+1] << "\n";
     h1[i] = (TH1D*) H1->ProjectionX(Form("h1_%i",i),binFinder->FindBin(jetPt_edges[i]+smallShift),binFinder->FindBin(jetPt_edges[i+1]-smallShift));
     h1[i] = (TH1D*) h1[i]->Rebin(M-1,Form("h1_%i",i),muRelPtAxis);
     h1[i] = divideByBinwidth(h1[i]);
     h1[i]->Scale(1./h1[i]->Integral()); // normalize by area
     h1[i]->SetLineWidth(2);
     leg->AddEntry(h1[i],jetPtBinStrings[i].Data());
     if(i > 0){
       r[i-1] = (TH1D*) h1[i]->Clone(Form("r_%i",i));
       r[i-1]->Divide(h1[i],h1[0],1,1,"B");
     }
     
   }

   h1[0]->SetLineColor(kBlack);
   h1[1]->SetLineColor(kBlue+9);
   h1[2]->SetLineColor(kRed-4);
   h1[3]->SetLineColor(kGreen+2);
   h1[4]->SetLineColor(kBlue-4);

   r[0]->SetLineColor(kBlue+9);
   r[1]->SetLineColor(kRed-4);
   r[2]->SetLineColor(kGreen+2);
   r[3]->SetLineColor(kBlue-4);



   

   
   TCanvas *c1 = new TCanvas("c1","c1",700,700);
   c1->cd();
   TPad *p1 = new TPad("p1","p1",0,0.4,1,1);
   TPad *p2 = new TPad("p2","p2",0,0,1,0.4);
   //p1->SetLogy();
   p1->SetBottomMargin(0.0);
   p1->SetLeftMargin(0.22);
   p2->SetTopMargin(0.0);
   p2->SetBottomMargin(0.33);
   p2->SetLeftMargin(0.22);
   p1->Draw();
   p2->Draw();
   p1->cd();
   h1[0]->SetTitle("");
   h1[0]->GetXaxis()->SetTitle("");
   h1[0]->GetXaxis()->SetLabelSize(0);
   h1[0]->GetYaxis()->SetTitleOffset(1.15);
   h1[0]->GetYaxis()->SetTitle("1/#font[52]{N}^{#mu}_{tot} d#font[52]{N}^{#mu}/d#font[52]{p}_{T}^{rel} [GeV^{-1}]");
   h1[0]->SetStats(0);
   h1[0]->GetYaxis()->SetLabelSize(0.057);
   h1[0]->GetYaxis()->SetTitleSize(0.068);
   h1[0]->Draw();
   h1[1]->Draw("same");
   h1[2]->Draw("same");
   h1[3]->Draw("same");
   leg->Draw();
   p2->cd();
   r[0]->GetXaxis()->SetTitle("");
   r[0]->GetXaxis()->SetLabelSize(0);
   r[0]->GetYaxis()->SetTitleOffset(1.15);
   r[0]->SetTitle("");
   r[0]->GetYaxis()->SetRangeUser(0,5);
   r[0]->GetYaxis()->SetTitle("ratio to 80-100 bin");
   r[0]->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
   r[0]->SetStats(0);
   r[0]->GetYaxis()->SetLabelSize(0.067);
   r[0]->GetYaxis()->SetTitleSize(0.078);
   r[0]->GetXaxis()->SetLabelSize(0.067);
   r[0]->GetXaxis()->SetTitleSize(0.078);
   r[0]->Draw();
   r[1]->Draw("same");
   r[2]->Draw("same");
   r[3]->Draw("same");
   li->DrawLine(0,1,5,1);

   

   c1->SaveAs(Form("../../../figures/muonPtRel/jetPtDependence_MC/canv_%s.pdf",canvSaveSuffix.Data()));
   




}
