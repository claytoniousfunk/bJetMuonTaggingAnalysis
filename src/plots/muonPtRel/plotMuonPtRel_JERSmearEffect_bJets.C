


#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"

void plotMuonPtRel_JERSmearEffect_bJets(bool isPP = 1,
					bool isC4 = 0,
					bool isC3 = 0,
					bool isC2 = 0,
					bool isC1 = 0,
					double jetPt_low = 80.,
					double jetPt_high = 100.,
					double mc_delta = 0){

  

   TFile *f1, *f2, *f3;

   
   if(isPP){
    
     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIA/latest/PYTHIA_DiJet_pThat-20_mu12_pTmu-14_tight_vzReweight_jetPtReweight_jetTrkMaxFilter_removeHYDJETjet0p45_2025-7-8.root");

     
   }

   else{

     f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_DiJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
     f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_MuJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
     f3 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/latest/PYTHIAHYDJET_BJet_pThat-20_mu12_pTmu-14_tight_hiBinReweight_hiBinShift-10_jetTrkMaxFilter_removeHYDJETjet0p45_2025-11-4.root");
    
   }

   


   
   TH2D *H1, *H2;
   TH2D *H1_add, *H1_add2, *H2_add, *H2_add2;
   TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;


   if(isPP){
    
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_T1",H1);
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_T0",H2);
	 
   }

   else if(isC4){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T1",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T1",H1_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T1",H1_add2);
     
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H2);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H2_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C4T0",H2_add2);

     H1->Add(H1_add);
     H1->Add(H1_add2);

     H2->Add(H2_add);
     H2->Add(H2_add2);

   }

   else if(isC3){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T1",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T1",H1_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T1",H1_add2);
     
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H2);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H2_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C3T0",H2_add2);

     H1->Add(H1_add);
     H1->Add(H1_add2);

     H2->Add(H2_add);
     H2->Add(H2_add2);
   }

   else if(isC2){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T1",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T1",H1_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T1",H1_add2);
     
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H2);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H2_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C2T0",H2_add2);

     H1->Add(H1_add);
     H1->Add(H1_add2);

     H2->Add(H2_add);
     H2->Add(H2_add2);

   }

   else if(isC1){

     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T1",H1);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T1",H1_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T1",H1_add2);
     
     f1->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2);
     f2->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2_add);
     f3->GetObject("h_muptrel_recoJetPt_inclRecoMuonTag_triggerOn_bJets_C1T0",H2_add2);

     H1->Add(H1_add);
     H1->Add(H1_add2);

     H2->Add(H2_add);
     H2->Add(H2_add2);

   }


   
   

   TH1D *binFinder = H2->ProjectionY();
   TAxis *yaxis = binFinder->GetXaxis();
   double smallShift = 0.01;


     
   h1 = (TH1D*) H1->ProjectionX("h1",binFinder->FindBin(jetPt_low+smallShift),binFinder->FindBin(jetPt_high-smallShift));
   h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(jetPt_low+smallShift-mc_delta),binFinder->FindBin(jetPt_high-smallShift-mc_delta));

   
   

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


   // const int M = 19;
   // double muRelPtAxis[M] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.2,1.4,1.7,2.1,2.5,3.0,3.8,5.0}; // M = 20;

   const int M = 11;
   double muRelPtAxis[M] = {0.0,0.2,0.4,0.6,0.8,1.0,1.4,2.0,3.0,3.8,5.0}; // M = 20;

   
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
   h1r->GetYaxis()->SetTitle("1/#font[52]{N}^{#mu}_{tot} d#font[52]{N}^{#mu}/d#font[52]{p}_{T}^{rel} [GeV^{-1}]");
   //h1r->GetYaxis()->SetTitle("1/#font[52]{N}^{jet}_{#font[52]{p}_{T}^{jet} > 60 GeV} d#font[52]{N}^{jet}/d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
   h1r->SetStats(0);
   h1r->GetYaxis()->SetLabelSize(0.057);
   h1r->GetYaxis()->SetTitleSize(0.068);


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

   la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,Form("%3.0f < #font[52]{p}_{T}^{jet} (GeV) < %3.0f",jetPt_low,jetPt_high));
   la->DrawLatexNDC(la_x_pos,la_y_pos-0.2,"#it{p}_{T}^{#it{#mu}} > 14 GeV, |#it{#eta}^{#it{#mu}} < 2.0");

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
   canvas_save_string.Append("./figures/JERSmearEffect/bJets/");
   if(isPP) canvas_save_string.Append("pp/");
   else if(isC4) canvas_save_string.Append("C4/");
   else if(isC3) canvas_save_string.Append("C3/");
   else if(isC2) canvas_save_string.Append("C2/");
   else if(isC1) canvas_save_string.Append("C1/");
   else{};
   canvas_save_string.Append(Form("jetPt-%3.0fto%3.0f.pdf",jetPt_low,jetPt_high));

   c1->SaveAs(canvas_save_string.Data());
   

   /*
   */




}
