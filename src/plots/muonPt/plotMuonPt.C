

#include "/home/clayton/Analysis/code/bJet_analysis/golden_filenames.h"
#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"

void plotMuonPt(bool isPP = 0,
		bool isC2 = 1,
		bool isC1 = 0,
		bool isSingleMuon = 1,
		bool isMinBias = 0,
		bool isJ1 = 1,
		bool isJ2 = 0,
		bool isJ3 = 0,
		bool isJ4 = 0,
		bool isJ5 = 0,
		bool isJ6 = 0){

  

   TFile *f1, *f2, *f3;

   
   if(isPP){

     if(isSingleMuon){
       f1 = TFile::Open(goldenFile_pp_SingleMuon_mu12_newJetBins);
     }
     else if(isMinBias){
       //f1 = TFile::Open(goldenFile_pp_MinBias);
     }
     else{};

     f2 = TFile::Open(goldenFile_PYTHIA_mu12_pThat45_newJetBins);
     
   }

   if(isC2 || isC1){

     if(isSingleMuon){
       f1 = TFile::Open(goldenFile_PbPb_SingleMuon_mu12_newJetBins);
       f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins);
       // f1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/final/PbPb_SingleMuon_scan_mu12_tight_pTmu-14_hiHFcut_fineCentBins_projectableTemplates.root");
       // f2 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/final/allTemplates/PYTHIAHYDJET_DiJet_withGS_scan_mu12_tight_pTmu-14_pThat-15_hiHFcut_jetTrkMaxFilter_vzReweight_hiBinReweight_fineCentBins_projectableTemplates_allTemplates.root");
     }
     else if(isMinBias){
       //f1 = TFile::Open(goldenFile_PbPb_MinBias);
       f2 = TFile::Open(HYDJET_RAW_filename);
     }
     else{};

     
     
   }

   
   

   
   TH2D *H1, *H2;
   TH1D *h1, *h1_add, *h2, *h2_add, *h3, *h3_add;


   if(isPP){
     if(isSingleMuon || isMinBias){
       if(isJ1){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J1",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J1",H2);
       }
       else if(isJ2){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J2",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J2",H2);
       }
       else if(isJ3){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J3",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J3",H2);
       }
       else if(isJ4){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J4",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J4",H2);
       }
       else if(isJ5){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J5",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J5",H2);
       }
       else if(isJ6){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_J6",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_J6",H2);
       }
       else{};
     }
     else{};
   }

   if(isC2){
     if(isSingleMuon || isMinBias){
       if(isJ1){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J1",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J1",H2);
       }
       else if(isJ2){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J2",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J2",H2);
       }
       else if(isJ3){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J3",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J3",H2);
       }
       else if(isJ4){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J4",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J4",H2);
       }
       else if(isJ5){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J5",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J5",H2);
       }
       else if(isJ6){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C2J6",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C2J6",H2);
       }
       else{};
     }
     else{};
   }

   if(isC1){
     if(isSingleMuon || isMinBias){
       if(isJ1){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C1J1",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C1J1",H2);
       }
       else if(isJ2){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C1J2",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C1J2",H2);
       }
       else if(isJ3){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C1J3",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C1J3",H2);
       }
       else if(isJ4){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C1J4",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C1J4",H2);
       }
       else if(isJ5){
	 f1->GetObject("h_mupt_inclRecoMuonTag_triggerOn_C1J5",h1);
	 f2->GetObject("h_mupt_inclRecoMuonTag_triggerOn_flavor_C1J5",H2);
       }
       else{};
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

   H2->Draw();

  
   
   h2 = (TH1D*) H2->ProjectionX("h2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(0-smallShift));
   h2_add = (TH1D*) H2->ProjectionX("h2_add",binFinder->FindBin(ghostSkipInt+smallShift),binFinder->FindBin(22-smallShift));

   h2->Add(h2_add);
   
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
   const int M = 14;
   double muRelPtAxis[M] = {14,15,16,17,18,20,22,25,30,35,40,50,70,100};

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
   h1r->GetYaxis()->SetTitle("1/#font[52]{N}^{#mu}_{tot} d#font[52]{N}^{#mu}/d#font[52]{p}_{T}^{#mu} [GeV^{-1}]");
   //h1r->GetYaxis()->SetTitle("1/#font[52]{N}^{jet}_{#font[52]{p}_{T}^{jet} > 60 GeV} d#font[52]{N}^{jet}/d#font[52]{p}_{T}^{jet} [GeV^{-1}]");
   h1r->SetStats(0);
   h1r->GetYaxis()->SetLabelSize(0.057);
   h1r->GetYaxis()->SetTitleSize(0.068);


   TH1D *r1, *r2;

   r1 = (TH1D*) h1r->Clone("r1");
   r1->Divide(h1r,h2r,1,1,"");
   r1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{#mu} [GeV]");
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
       leg->AddEntry(h2r,"PYTHIA+HYDJET","p");
     }
     else if(isMinBias){
       leg->AddEntry(h1r,"PbPb MinBias","p");
       leg->AddEntry(h2r,"HYDJET","p");
     }
     else{};
     
   }

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
   
   la->DrawLatexNDC(0.32,0.92,"#sqrt{#font[52]{s}_{NN}} = 5.02 TeV, in-jet muons");
   

   la->SetTextSize(0.044);

   double la_x_pos = 0.24;
   double la_y_pos = 0.28;
   
   if(isC2 || isC1){
     la->DrawLatexNDC(la_x_pos,la_y_pos,"akCs4PF jets, |#it{#eta}^{jet}| < 1.6");
   }
   else if(isPP){
     la->DrawLatexNDC(la_x_pos,la_y_pos,"ak4PF jets, |#it{#eta}^{jet}| < 1.6");
   }

   if(isJ1){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"80 < #font[52]{p}_{T}^{jet} < 100 GeV");
   }
   else if(isJ2){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"100 < #font[52]{p}_{T}^{jet} < 120 GeV");
   }
   else if(isJ3){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"120 < #font[52]{p}_{T}^{jet} < 150 GeV");
   }
   else if(isJ4){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"150 < #font[52]{p}_{T}^{jet} < 200 GeV");
   }
   else if(isJ5){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"200 < #font[52]{p}_{T}^{jet} < 300 GeV");
   }
   else if(isJ6){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.1,"300 < #font[52]{p}_{T}^{jet} < 500 GeV");
   }
   else{};
   

   if(isSingleMuon){
     la->DrawLatexNDC(la_x_pos,la_y_pos-0.2,"|#it{#eta}^{#mu}| < 2.0");
   }

   la->SetTextSize(0.05);
   if(isC2){
     //la->DrawLatexNDC(0.35,0.8,"Cent. 0-90%");
     //la->DrawLatexNDC(0.35,0.8,"Cent. 50-90%");
     //la->DrawLatexNDC(0.35,0.8,"Cent. 30-50%");
     //la->DrawLatexNDC(0.35,0.8,"Cent. 10-30%");
     //la->DrawLatexNDC(0.35,0.8,"Cent. 0-10%");
     la->DrawLatexNDC(0.35,0.8,"Cent. 30-90%");
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
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/pp/muonPt_jetPt_60_80_pp_SingleMuon.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/pp/muonPt_jetPt_80_120_pp_SingleMuon.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/pp/muonPt_jetPt_120_200_pp_SingleMuon.pdf");
       }
     }
     if(isMinBias){
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/pp/muonPt_jetPt_60_80_pp_MinBias.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/pp/muonPt_jetPt_80_120_pp_MinBias.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/pp/muonPt_jetPt_120_200_pp_MinBias.pdf");
       }
     }
     if(isMinBias){
       
     }
   }

   if(isC2){
     if(isSingleMuon){
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_30_90/muonPt_jetPt_60_80_PbPb_30_90_SingleMuon.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_30_90/muonPt_jetPt_80_120_PbPb_30_90_SingleMuon.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_30_90/muonPt_jetPt_120_200_PbPb_30_90_SingleMuon.pdf");
       }
     }
     if(isMinBias){
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_30_90/muonPt_jetPt_60_80_PbPb_30_90_MinBias.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_30_90/muonPt_jetPt_80_120_PbPb_30_90_MinBias.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_30_90/muonPt_jetPt_120_200_PbPb_30_90_MinBias.pdf");
       }
     }
   }

   if(isC1){
     if(isSingleMuon){
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_0_30/muonPt_jetPt_60_80_PbPb_0_30_SingleMuon.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_0_30/muonPt_jetPt_80_120_PbPb_0_30_SingleMuon.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/SingleMuon/PbPb_0_30/muonPt_jetPt_120_200_PbPb_0_30_SingleMuon.pdf");
       }
     }
     if(isMinBias){
       if(isJ2){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_0_30/muonPt_jetPt_60_80_PbPb_0_30_MinBias.pdf");
       }
       if(isJ3){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_0_30/muonPt_jetPt_80_120_PbPb_0_30_MinBias.pdf");
       }
       if(isJ4){
	 c1->SaveAs("/home/clayton/Analysis/code/bJet_analysis/muonPt/MinBias/PbPb_0_30/muonPt_jetPt_120_200_PbPb_0_30_MinBias.pdf");
       }
     }
   }


   //c1->SaveAs("/home/clayton/Documents/nuclear/GroupMeeting/figures/01-05-23/clayton_C1.pdf");





}
