


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"
#include "../../../headers/functions/divideByBinwidth.h"

void plotJetTrkMaxPtRel_jetPtDependence_MC(bool isPP = 1,
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
    
     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-21.root");
     f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/jetTrkMax/PYTHIA_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-21.root");

     
     
   }

   else{

     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-1.root");
     f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/jetTrkMax/PYTHIAHYDJET_DiJet_jetTrkMax_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-8-1.root");
    
   }

   
   

   
   TH2D *H1, *H2;
   //TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;
   TH1D *h1[N_edges-1], *h2[N_edges-1];
   TH1D *r[N_edges-2];


   if(isPP){
    
     f1->GetObject("h_jetTrkMaxPtRel_recoJetPt_T0",H1);
     canvSaveSuffix = "pp";
 
   }

   else if(isC4){

     f1->GetObject("h_jetTrkMaxPtRel_recoJetPt_C4T0",H1);
     canvSaveSuffix = "C4";

   }

   else if(isC3){

     f1->GetObject("h_jetTrkMaxPtRel_recoJetPt_C3T0",H1);
     canvSaveSuffix = "C3";

   }

   else if(isC2){

     f1->GetObject("h_jetTrkMaxPtRel_recoJetPt_C2T0",H1);
     canvSaveSuffix = "C2";

   }

   else if(isC1){

     f1->GetObject("h_jetTrkMaxPtRel_recoJetPt_C1T0",H1);
     canvSaveSuffix = "C1";

   }

   TH1D *binFinder = H1->ProjectionY();
   TAxis *yaxis = binFinder->GetXaxis();
   double smallShift = 0.01;

   TLegend *leg = new TLegend(0.5,0.5,0.88,0.88);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);

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
   h1[0]->GetYaxis()->SetTitle("1/#font[52]{N}^{#it{h}}_{tot} d#font[52]{N}^{#it{h}}/d#font[52]{p}_{T}^{rel} [GeV^{-1}]");
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

   

   c1->SaveAs(Form("../../../figures/jetTrkMaxPtRel/jetPtDependence_MC/canv_%s.pdf",canvSaveSuffix.Data()));
   
   


   /*
     
    
   
   

   // normalize
   double N1, N2, N3;

   


   // const int M = 19;
   // double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0}; // M = 20;

   

   
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
   

   


   TH1D *r1, *r2;

   r1 = (TH1D*) h1r->Clone("r1");
   r1->Divide(h1r,h2r,1,1,"");
   r1->GetXaxis()->SetTitle("Muon #font[52]{p}_{T}^{rel} [GeV]");
   r1->GetYaxis()->SetTitleOffset(0.66);
   r1->GetYaxis()->SetTitle("Smeared / Nominal ");
   r1->GetXaxis()->SetLabelSize(0.09);
   r1->GetYaxis()->SetLabelSize(0.09);
   r1->GetYaxis()->SetTitleSize(0.10);
   r1->GetXaxis()->SetTitleSize(0.10);
   r1->GetYaxis()->SetNdivisions(606);
   r1->SetTitle("");
   r1->SetStats(0);


   TLegend *leg = new TLegend(0.55,0.68,0.78,0.88);
   leg->SetBorderSize(0);
   leg->SetTextSize(0.05);


   if(isPP){     
     leg->AddEntry(h1r,"PYTHIA JER smeared","p");
     leg->AddEntry(h2r,"PYTHIA nominal","p");
   }

   else{

       leg->AddEntry(h1r,"P+H JER smeared","p");
       leg->AddEntry(h2r,"P+H nominal","p");
     
   }

   h1r->GetXaxis()->SetRangeUser(muRelPtAxis[0]+smallShift,muRelPtAxis[M-1]-smallShift);
   h1r->GetYaxis()->SetRangeUser(0,0.98);
   
   h1r->Draw();
   h2r->Draw("same");

   
   leg->Draw();

   TLatex *la = new TLatex();
   la->SetTextFont(62);
   la->SetTextSize(0.06);
   la->DrawLatexNDC(0.22,0.92,"CMS");
   la->SetTextFont(42);
   la->SetTextSize(0.045);
   
   la->DrawLatexNDC(0.32,0.92,"#sqrt{#font[52]{s}_{NN}} = 5.02 TeV, in-jet muons");
   

   la->SetTextSize(0.044);

   double la_x_pos = 0.58;
   double la_y_pos = 0.58;
   
   
   if(isPP){
     la->DrawLatexNDC(la_x_pos,la_y_pos,"ak4PF jets, |#it{#eta}^{jet}| < 1.6");
   }
   else{
     la->DrawLatexNDC(la_x_pos,la_y_pos,"akCs4PF jets, |#it{#eta}^{jet}| < 1.6");
   }

   la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,Form("%3.0f < #font[52]{p}_{T}^{jet} < %3.0f GeV",jetPt_low,jetPt_high));
   

   // if(isSingleMuon){
   //   la->DrawLatexNDC(la_x_pos,la_y_pos-0.2,"|#it{#eta}^{#mu}| < 2.0");
   // }

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
   


   p2->cd();
   double ratio_low = 0.4;
   double ratio_high = 1.6;
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


   TString canvas_save_string = "";
   canvas_save_string.Append("./figures/JERSmearEffect/");
   if(isPP) canvas_save_string.Append("pp/");
   else if(isC4) canvas_save_string.Append("C4/");
   else if(isC3) canvas_save_string.Append("C3/");
   else if(isC2) canvas_save_string.Append("C2/");
   else if(isC1) canvas_save_string.Append("C1/");
   else{};
   canvas_save_string.Append(Form("jetPt-%3.0fto%3.0f.pdf",jetPt_low,jetPt_high));

   c1->SaveAs(canvas_save_string.Data());
   


   */




}
