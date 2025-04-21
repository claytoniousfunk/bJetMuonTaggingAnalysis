#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/systematicsResults.h"
#include "../../../headers/goldenFileNames.h"


void fraction_plot(bool do_mu5 = 0,
		   bool do_mu7 = 0,
		   bool do_mu12 = 1){



  const int M = 6;
  double new_axis[M] = {80,90,100,120,150,200};

  


  
  TString input_PYTHIA;
  TString input_pp_SingleMuon;
  TString input_pp_MinBias;
  TString input_PYTHIAHYDJET;
  TString input_PbPb_SingleMuon;
  TString input_PbPb_MinBias;

  if(do_mu5){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu5;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu5;
    input_pp_MinBias      = goldenFile_pp_MinBias_mu5;
    input_PbPb_MinBias    = goldenFile_PbPb_MinBias_mu5;
    input_PYTHIA          = goldenFile_PYTHIA_mu5_pThat30;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat15;

  }
  else if(do_mu7){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu7;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu7;
    input_pp_MinBias      = goldenFile_pp_MinBias_mu7;
    input_PbPb_MinBias    = goldenFile_PbPb_MinBias_mu7;
    input_PYTHIA          = goldenFile_PYTHIA_mu7_pThat30;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu7_pThat30;

  }
  else if(do_mu12){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu12_newJetBins;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu12_newJetBins;
    input_pp_MinBias      = goldenFile_pp_MinBias_mu12_newJetBins;
    input_PbPb_MinBias    = goldenFile_PbPb_MinBias_mu12_newJetBins;
    input_PYTHIA          = goldenFile_PYTHIA_mu12_pThat15_newJetBins;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat15_newJetBins;

  }
  else{};


  
  TFile *x1, *x2, *x3;
  x1 = TFile::Open(input_PYTHIA);
  x2 = TFile::Open(input_PYTHIAHYDJET);

  TH2D *Y1, *Y2, *Y3;
  TH2D *YY1, *YY2, *YY3;
  TH2D *YYY1, *YYY2, *YYY3;
  TH2D *YYYY1, *YYYY2, *YYYY3;
  TH2D *YYYYY1, *YYYYY2, *YYYYY3;
  TH1D *y1, *y2, *y3;
  TH1D *yy1, *yy2, *yy3;
  TH1D *yyy1, *yyy2, *yyy3;
  TH1D *yyyy1, *yyyy2, *yyyy3;
  TH1D *yyyyy1, *yyyyy2, *yyyyy3;
  TH1D *b1, *b2, *b3;
  TH1D *b1_add, *b2_add, *b3_add;
  TH1D *b1_add2, *b2_add2, *b3_add2;

  TH1D *bb1, *bb2, *bb3;
  TH1D *bb1_add, *bb2_add, *bb3_add;
  TH1D *bb1_add2, *bb2_add2, *bb3_add2;

  TH1D *bbb1, *bbb2, *bbb3;
  TH1D *bbb1_add, *bbb2_add, *bbb3_add;
  TH1D *bbb1_add2, *bbb2_add2, *bbb3_add2;

  TH1D *bbbb1, *bbbb2, *bbbb3;
  TH1D *bbbb1_add, *bbbb2_add, *bbbb3_add;
  TH1D *bbbb1_add2, *bbbb2_add2, *bbbb3_add2;

  TH1D *bbbbb1, *bbbbb2, *bbbbb3;
  TH1D *bbbbb1_add, *bbbbb2_add, *bbbbb3_add;
  TH1D *bbbbb1_add2, *bbbbb2_add2, *bbbbb3_add2;

  TH1D *genb, *geni;
  TH1D *genb_add, *genb_add2;
  TH2D *G;

  x1->GetObject("h_inclRecoJetPt_flavor",Y1);
  x1->GetObject("h_inclGenJetPt_flavor",G);
  x1->GetObject("h_inclRecoJetPt_inclGenMuonTag_flavor",YY1);
  x1->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_flavor",YYY1);
  x1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_flavor",YYYY1);
  x1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",YYYYY1);
  
  x2->GetObject("h_inclRecoJetPt_flavor_C2",Y2);
  x2->GetObject("h_inclRecoJetPt_flavor_C1",Y3);

  geni = (TH1D*) G->ProjectionX();
  y1 = (TH1D*) Y1->ProjectionX();
  yy1 = (TH1D*) YY1->ProjectionX();
  yyy1 = (TH1D*) YYY1->ProjectionX();
  yyyy1 = (TH1D*) YYYY1->ProjectionX();
  yyyyy1 = (TH1D*) YYYYY1->ProjectionX();


  y2 = (TH1D*) Y2->ProjectionX();
  y3 = (TH1D*) Y3->ProjectionX();

  TH1D *binFinder = Y1->ProjectionY();
  double smallShift = 0.01;

  genb = (TH1D*) G->ProjectionX("genb",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  genb_add = (TH1D*) G->ProjectionX("genb_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  genb_add2 = (TH1D*) G->ProjectionX("genb_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  genb->Add(genb_add);
  genb->Add(genb_add2);
  
  b1 = (TH1D*) Y1->ProjectionX("b1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b1_add = (TH1D*) Y1->ProjectionX("b1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b1_add2 = (TH1D*) Y1->ProjectionX("b1_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  b1->Add(b1_add);
  b1->Add(b1_add2);

  bb1 = (TH1D*) YY1->ProjectionX("bb1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  bb1_add = (TH1D*) YY1->ProjectionX("bb1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  bb1_add2 = (TH1D*) YY1->ProjectionX("bb1_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  bb1->Add(bb1_add);
  bb1->Add(bb1_add2);

  bbb1 = (TH1D*) YYY1->ProjectionX("bbb1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  bbb1_add = (TH1D*) YYY1->ProjectionX("bbb1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  bbb1_add2 = (TH1D*) YYY1->ProjectionX("bbb1_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  bbb1->Add(bbb1_add);
  bbb1->Add(bbb1_add2);

  bbbb1 = (TH1D*) YYYY1->ProjectionX("bbbb1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  bbbb1_add = (TH1D*) YYYY1->ProjectionX("bbbb1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  bbbb1_add2 = (TH1D*) YYYY1->ProjectionX("bbbb1_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  bbbb1->Add(bbbb1_add);
  bbbb1->Add(bbbb1_add2);

  bbbbb1 = (TH1D*) YYYYY1->ProjectionX("bbbbb1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  bbbbb1_add = (TH1D*) YYYYY1->ProjectionX("bbbbb1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  bbbbb1_add2 = (TH1D*) YYYYY1->ProjectionX("bbbbb1_add2",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  bbbbb1->Add(bbbbb1_add);
  bbbbb1->Add(bbbbb1_add2);



  

  b2 = (TH1D*) Y2->ProjectionX("b2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b2_add = (TH1D*) Y2->ProjectionX("b2_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b2_add2 = (TH1D*) Y2->ProjectionX("b2_add2",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  b2->Add(b2_add);
  b2->Add(b2_add2);

  b3 = (TH1D*) Y3->ProjectionX("b3",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b3_add = (TH1D*) Y3->ProjectionX("b3_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b3_add2 = (TH1D*) Y3->ProjectionX("b3_add2",binFinder->FindBin(17+smallShift),binFinder->FindBin(18-smallShift));
  b3->Add(b3_add);
  b3->Add(b3_add2);

  TH1D *genb_R = (TH1D*) genb->Rebin(M-1,"genb_R",new_axis);
  divideByBinwidth(genb_R); genb_R->Scale(5.0);

  TH1D *geni_R = (TH1D*) geni->Rebin(M-1,"geni_R",new_axis);
  divideByBinwidth(geni_R); geni_R->Scale(5.0);
  
  TH1D *b1_R = (TH1D*) b1->Rebin(M-1,"b1_R",new_axis);
  divideByBinwidth(b1_R); b1_R->Scale(5.0);

  TH1D *b2_R = (TH1D*) b2->Rebin(M-1,"b2_R",new_axis);
  divideByBinwidth(b2_R); b2_R->Scale(5.0);

  TH1D *b3_R = (TH1D*) b3->Rebin(M-1,"b3_R",new_axis);
  divideByBinwidth(b3_R); b3_R->Scale(5.0); 
  
  TH1D *bb1_R = (TH1D*) bb1->Rebin(M-1,"bb1_R",new_axis);
  divideByBinwidth(bb1_R); bb1_R->Scale(5.0); 

  TH1D *bbb1_R = (TH1D*) bbb1->Rebin(M-1,"bbb1_R",new_axis);
  divideByBinwidth(bbb1_R); bbb1_R->Scale(5.0);

  TH1D *bbbb1_R = (TH1D*) bbbb1->Rebin(M-1,"bbbb1_R",new_axis);
  divideByBinwidth(bbbb1_R); bbbb1_R->Scale(5.0);

  TH1D *bbbbb1_R = (TH1D*) bbbbb1->Rebin(M-1,"bbbbb1_R",new_axis);
  divideByBinwidth(bbbbb1_R); bbbbb1_R->Scale(5.0);

  TH1D *y1_R = (TH1D*) y1->Rebin(M-1,"y1_R",new_axis);
  divideByBinwidth(y1_R); y1_R->Scale(5.0);

  TH1D *y2_R = (TH1D*) y2->Rebin(M-1,"y2_R",new_axis);
  divideByBinwidth(y2_R); y2_R->Scale(5.0);

  TH1D *y3_R = (TH1D*) y3->Rebin(M-1,"y3_R",new_axis);
  divideByBinwidth(y3_R); y3_R->Scale(5.0);
  
  TH1D *yy1_R = (TH1D*) yy1->Rebin(M-1,"yy1_R",new_axis);
  divideByBinwidth(yy1_R); yy1_R->Scale(5.0); 

  TH1D *yyy1_R = (TH1D*) yyy1->Rebin(M-1,"yyy1_R",new_axis);
  divideByBinwidth(yyy1_R); yyy1_R->Scale(5.0);

  TH1D *yyyy1_R = (TH1D*) yyyy1->Rebin(M-1,"yyyy1_R",new_axis);
  divideByBinwidth(yyyy1_R); yyyy1_R->Scale(5.0);

  TH1D *yyyyy1_R = (TH1D*) yyyyy1->Rebin(M-1,"yyyyy1_R",new_axis);
  divideByBinwidth(yyyyy1_R); yyyyy1_R->Scale(5.0); 
  

  TH1D *b_truth_gen = (TH1D*) genb->Clone("b_truth_gen");
  b_truth_gen->Divide(genb,geni,1,1,"B");

  TH1D *b_truth_gen_R = (TH1D*) genb_R->Clone("b_truth_gen_R");
  b_truth_gen_R->Divide(genb_R,geni_R,1,1,"B");
  
  TH1D *b_truth_pp = (TH1D*) b1->Clone("b_truth_pp");
  b_truth_pp->Divide(b1,y1,1,1,"B");

  TH1D *b_truth_pp_R = (TH1D*) b1_R->Clone("b_truth_pp_R");
  b_truth_pp_R->Divide(b1_R,y1_R,1,1,"B");

  TH1D *b_truth_pp_inclGenMuTag_R = (TH1D*) bb1_R->Clone("b_truth_pp_inclGenMuTag_R");
  b_truth_pp_inclGenMuTag_R->Divide(bb1_R,yy1_R,1,1,"B");

  TH1D *b_truth_pp_matchedRecoMuTag_R = (TH1D*) bbb1_R->Clone("b_truth_pp_matchedRecoMuTag_R");
  b_truth_pp_matchedRecoMuTag_R->Divide(bbb1_R,yyy1_R,1,1,"B");

  TH1D *b_truth_pp_inclRecoMuTag_R = (TH1D*) bbbb1_R->Clone("b_truth_pp_inclRecoMuTag_R");
  b_truth_pp_inclRecoMuTag_R->Divide(bbbb1_R,yyyy1_R,1,1,"B");

  TH1D *b_truth_pp_inclRecoMuTag_triggerOn_R = (TH1D*) bbbbb1_R->Clone("b_truth_pp_inclRecoMuTag_triggerOn_R");
  b_truth_pp_inclRecoMuTag_triggerOn_R->Divide(bbbbb1_R,yyyyy1_R,1,1,"B");

 
  
  
  
  TH1D *b_truth_C2 = (TH1D*) b2->Clone("b_truth_C2");
  b_truth_C2->Divide(b2,y2,1,1,"B");

  TH1D *b_truth_C2_R = (TH1D*) b2_R->Clone("b_truth_C2_R");
  b_truth_C2_R->Divide(b2_R,y2_R,1,1,"B");

  TH1D *b_truth_C1 = (TH1D*) b3->Clone("b_truth_C1");
  b_truth_C1->Divide(b3,y3,1,1,"B");

  TH1D *b_truth_C1_R = (TH1D*) b3_R->Clone("b_truth_C1_R");
  b_truth_C1_R->Divide(b3_R,y3_R,1,1,"B");

  b_truth_pp->SetLineColor(kBlack);
  b_truth_pp->SetLineStyle(1);
  b_truth_pp->SetMarkerSize(0);
  b_truth_pp->SetLineWidth(2);

  b_truth_gen->SetLineColor(kBlack);
  b_truth_gen->SetLineStyle(2);
  b_truth_gen->SetMarkerSize(0);
  b_truth_gen->SetLineWidth(2);

  b_truth_C2->SetLineColor(kRed-4);
  //  b_truth_C2->SetLineStyle(7);
  b_truth_C2->SetMarkerSize(0);
  b_truth_C2->SetLineWidth(2);

  b_truth_C1->SetLineColor(kBlue-4);
  //  b_truth_C1->SetLineStyle(7);
  b_truth_C1->SetMarkerSize(0);
  b_truth_C1->SetLineWidth(2);

  
  
  TFile *f1, *f2, *f3;
  TFile *F1, *F2, *F3;

  TString b_purity_file_string = "";

  if(do_mu5) b_purity_file_string = "../../../rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-1_mu7-0_mu12-0_mergeB-1_mergeC-1_pTrel-0.0-5.0_cMult-1.0_bMult-1.2-JERsmear-1.root";
  else if(do_mu7) b_purity_file_string = "../../../rootFiles/bPurityResults/golden//bPurityResults_DATA-0_mu5-0_mu7-1_mu12-0_mergeB-0_mergeC-0_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root";
  else if(do_mu12) b_purity_file_string = "../../../rootFiles/bPurityResults/final/bPurityResults_DATA-1_mergeB-1_mergeC-1_pTrel-0.0to5.0_cMult-1.0_bMult-1.0_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root";
  //else if(do_mu12) b_purity_file_string = "../../../rootFiles/bPurityResults/golden/bPurityResults_DATA-0_mu5-0_mu7-0_mu12-1_mergeB-1_mergeC-1_pTrel-0.0to3.0_cMult-1.0_bMult-1.2_JERsmear-0_JEUShiftUp-0_JEUShiftDown-0_bJetEnergyShift-0.root";

  else{};
  

  // b-fraction results
  f1 = TFile::Open(b_purity_file_string);


  TH1D *h1, *h2, *h3;
  TH1D *H1, *H2, *H3;

  f1->GetObject("bFracResults_pp",h1);
  f1->GetObject("bFracResults_C2",h2);
  f1->GetObject("bFracResults_C1",h3);



  TString b_amplifier_pp_file_string = "";
  TString b_amplifier_C2_file_string = "";
  TString b_amplifier_C1_file_string = "";

  TString b_amplifier_sub_1_pp_file_string = "";
  TString b_amplifier_sub_1_C2_file_string = "";
  TString b_amplifier_sub_1_C1_file_string = "";

  TString b_amplifier_sub_2_pp_file_string = "";
  TString b_amplifier_sub_2_C2_file_string = "";
  TString b_amplifier_sub_2_C1_file_string = "";

  TString b_amplifier_sub_3_pp_file_string = "";
  TString b_amplifier_sub_3_C2_file_string = "";
  TString b_amplifier_sub_3_C1_file_string = "";

  TString b_amplifier_sub_4_pp_file_string = "";
  TString b_amplifier_sub_4_C2_file_string = "";
  TString b_amplifier_sub_4_C1_file_string = "";

  if(do_mu5){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu5.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu5.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu5.root";
    b_amplifier_sub_1_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_pp_mu5.root";
    b_amplifier_sub_1_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C2_mu5.root";
    b_amplifier_sub_1_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C1_mu5.root";
    b_amplifier_sub_2_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_pp_mu5.root";
    b_amplifier_sub_2_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C2_mu5.root";
    b_amplifier_sub_2_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C1_mu5.root";
    b_amplifier_sub_3_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_pp_mu5.root";
    b_amplifier_sub_3_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C2_mu5.root";
    b_amplifier_sub_3_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C1_mu5.root";
    b_amplifier_sub_4_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_pp_mu5.root";
    b_amplifier_sub_4_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C2_mu5.root";
    b_amplifier_sub_4_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C1_mu5.root";
  }
  else if(do_mu7){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu7_nom.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu7.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu7.root";
    b_amplifier_sub_1_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_pp_mu7.root";
    b_amplifier_sub_1_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C2_mu7.root";
    b_amplifier_sub_1_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C1_mu7.root";
    b_amplifier_sub_2_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_pp_mu7.root";
    b_amplifier_sub_2_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C2_mu7.root";
    b_amplifier_sub_2_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C1_mu7.root";
    b_amplifier_sub_3_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_pp_mu7.root";
    b_amplifier_sub_3_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C2_mu7.root";
    b_amplifier_sub_3_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C1_mu7.root";
    b_amplifier_sub_4_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_pp_mu7.root";
    b_amplifier_sub_4_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C2_mu7.root";
    b_amplifier_sub_4_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C1_mu7.root";
  }
  else if(do_mu12){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu12_bJetNeutrinoEnergyShift.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu12_bJetNeutrinoEnergyShift.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu12_bJetNeutrinoEnergyShift.root";
    b_amplifier_sub_1_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_pp_mu12.root";
    b_amplifier_sub_1_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C2_mu12.root";
    b_amplifier_sub_1_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_1_C1_mu12.root";
    b_amplifier_sub_2_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_pp_mu12.root";
    b_amplifier_sub_2_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C2_mu12.root";
    b_amplifier_sub_2_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_2_C1_mu12.root";
    b_amplifier_sub_3_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_pp_mu12.root";
    b_amplifier_sub_3_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C2_mu12.root";
    b_amplifier_sub_3_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_3_C1_mu12.root";
    b_amplifier_sub_4_pp_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_pp_mu12.root";
    b_amplifier_sub_4_C2_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C2_mu12.root";
    b_amplifier_sub_4_C1_file_string = "../tagging_sequence/b_amplifiers/sub_amps/ba_sub_4_C1_mu12.root";
  }
  else{};

  // b-amplifier files
  TFile *fb1, *fb2, *fb3;
  fb1 = TFile::Open(b_amplifier_pp_file_string);
  fb2 = TFile::Open(b_amplifier_C2_file_string);
  fb3 = TFile::Open(b_amplifier_C1_file_string);

  TH1D *ba1, *ba2, *ba3;

  fb1->GetObject("r_corr",ba1);
  fb2->GetObject("r_corr",ba2);
  fb3->GetObject("r_corr",ba3);

  // sub-amplifiers
  TFile *fb1_1, *fb1_2, *fb1_3, *fb1_4; // sub-amplifiers for pp
  fb1_1 = TFile::Open(b_amplifier_sub_1_pp_file_string);
  fb1_2 = TFile::Open(b_amplifier_sub_2_pp_file_string);
  fb1_3 = TFile::Open(b_amplifier_sub_3_pp_file_string);
  fb1_4 = TFile::Open(b_amplifier_sub_4_pp_file_string);
  TFile *fb2_1, *fb2_2, *fb2_3, *fb2_4; // sub-amplifiers for C2
  fb2_1 = TFile::Open(b_amplifier_sub_1_C2_file_string);
  fb2_2 = TFile::Open(b_amplifier_sub_2_C2_file_string);
  fb2_3 = TFile::Open(b_amplifier_sub_3_C2_file_string);
  fb2_4 = TFile::Open(b_amplifier_sub_4_C2_file_string);
  TFile *fb3_1, *fb3_2, *fb3_3, *fb3_4; // sub-amplifiers for C1
  fb3_1 = TFile::Open(b_amplifier_sub_1_C1_file_string);
  fb3_2 = TFile::Open(b_amplifier_sub_2_C1_file_string);
  fb3_3 = TFile::Open(b_amplifier_sub_3_C1_file_string);
  fb3_4 = TFile::Open(b_amplifier_sub_4_C1_file_string);

  TH1D *ba1_1, *ba1_2, *ba1_3, *ba1_4;
  TH1D *ba2_1, *ba2_2, *ba2_3, *ba2_4;
  TH1D *ba3_1, *ba3_2, *ba3_3, *ba3_4;

  fb1_1->GetObject("r_corr_1",ba1_1);
  fb1_2->GetObject("r_corr_2",ba1_2);
  fb1_3->GetObject("r_corr_3",ba1_3);
  fb1_4->GetObject("r_corr_4",ba1_4);

  fb2_1->GetObject("r_corr_1",ba2_1);
  fb2_2->GetObject("r_corr_2",ba2_2);
  fb2_3->GetObject("r_corr_3",ba2_3);
  fb2_4->GetObject("r_corr_4",ba2_4);

  fb3_1->GetObject("r_corr_1",ba3_1);
  fb3_2->GetObject("r_corr_2",ba3_2);
  fb3_3->GetObject("r_corr_3",ba3_3);
  fb3_4->GetObject("r_corr_4",ba3_4);
  




  
  


  
  TH1D *ba1_R = (TH1D*) ba1->Rebin(M-1,"ba1_R",new_axis);
  TH1D *ba1_1_R = (TH1D*) ba1_1->Rebin(M-1,"ba1_1_R",new_axis);
  TH1D *ba1_2_R = (TH1D*) ba1_2->Rebin(M-1,"ba1_2_R",new_axis);
  TH1D *ba1_3_R = (TH1D*) ba1_3->Rebin(M-1,"ba1_3_R",new_axis);
  TH1D *ba1_4_R = (TH1D*) ba1_4->Rebin(M-1,"ba1_4_R",new_axis);
  
  TH1D *ba2_R = (TH1D*) ba2->Rebin(M-1,"ba2_R",new_axis);
  TH1D *ba2_1_R = (TH1D*) ba2_1->Rebin(M-1,"ba2_1_R",new_axis);
  TH1D *ba2_2_R = (TH1D*) ba2_2->Rebin(M-1,"ba2_2_R",new_axis);
  TH1D *ba2_3_R = (TH1D*) ba2_3->Rebin(M-1,"ba2_3_R",new_axis);
  TH1D *ba2_4_R = (TH1D*) ba2_4->Rebin(M-1,"ba2_4_R",new_axis);

  TH1D *ba3_R = (TH1D*) ba3->Rebin(M-1,"ba3_R",new_axis);
  TH1D *ba3_1_R = (TH1D*) ba3_1->Rebin(M-1,"ba3_1_R",new_axis);
  TH1D *ba3_2_R = (TH1D*) ba3_2->Rebin(M-1,"ba3_2_R",new_axis);
  TH1D *ba3_3_R = (TH1D*) ba3_3->Rebin(M-1,"ba3_3_R",new_axis);
  TH1D *ba3_4_R = (TH1D*) ba3_4->Rebin(M-1,"ba3_4_R",new_axis);




  // divideByBinwidth(ba1_R);   ba1_R->Scale(5.0);
  // divideByBinwidth(ba1_1_R); ba1_1_R->Scale(5.0);
  // divideByBinwidth(ba1_2_R); ba1_2_R->Scale(5.0);
  // divideByBinwidth(ba1_3_R); ba1_3_R->Scale(5.0);
  // divideByBinwidth(ba1_4_R); ba1_4_R->Scale(5.0);

  // divideByBinwidth(ba2_R);   ba2_R->Scale(5.0);
  // divideByBinwidth(ba2_1_R); ba2_1_R->Scale(5.0);
  // divideByBinwidth(ba2_2_R); ba2_2_R->Scale(5.0);
  // divideByBinwidth(ba2_3_R); ba2_3_R->Scale(5.0);
  // divideByBinwidth(ba2_4_R); ba2_4_R->Scale(5.0);

  // divideByBinwidth(ba3_R);   ba3_R->Scale(5.0);
  // divideByBinwidth(ba3_1_R); ba3_1_R->Scale(5.0);
  // divideByBinwidth(ba3_2_R); ba3_2_R->Scale(5.0);
  // divideByBinwidth(ba3_3_R); ba3_3_R->Scale(5.0);
  // divideByBinwidth(ba3_4_R); ba3_4_R->Scale(5.0);



  

  // make sub-amplification histos from closure test
  TH1D *h1_0 = (TH1D*) h1->Clone("h1_0");
  TH1D *h1_1 = (TH1D*) h1->Clone("h1_1");
  TH1D *h1_2 = (TH1D*) h1->Clone("h1_2");
  TH1D *h1_3 = (TH1D*) h1->Clone("h1_3");
  TH1D *h1_4 = (TH1D*) h1->Clone("h1_4");

  h1_1->Divide(h1,ba1_4_R,1,1,"");
  h1_2->Divide(h1,ba1_3_R,1,1,"");
  h1_3->Divide(h1,ba1_2_R,1,1,"");
  h1_4->Divide(h1,ba1_1_R,1,1,"");

  TH2D *h2_0 = (TH2D*) h2->Clone("h2_0");
  TH2D *h2_1 = (TH2D*) h2->Clone("h2_1");
  TH2D *h2_2 = (TH2D*) h2->Clone("h2_2");
  TH2D *h2_3 = (TH2D*) h2->Clone("h2_3");
  TH2D *h2_4 = (TH2D*) h2->Clone("h2_4");

  h2_1->Divide(h2,ba2_4_R,1,1,"");
  h2_2->Divide(h2,ba2_3_R,1,1,"");
  h2_3->Divide(h2,ba2_2_R,1,1,"");
  h2_4->Divide(h2,ba2_1_R,1,1,"");

  TH3D *h3_0 = (TH3D*) h3->Clone("h3_0");
  TH3D *h3_1 = (TH3D*) h3->Clone("h3_1");
  TH3D *h3_2 = (TH3D*) h3->Clone("h3_2");
  TH3D *h3_3 = (TH3D*) h3->Clone("h3_3");
  TH3D *h3_4 = (TH3D*) h3->Clone("h3_4");

  h3_1->Divide(h3,ba3_4_R,1,1,"");
  h3_2->Divide(h3,ba3_3_R,1,1,"");
  h3_3->Divide(h3,ba3_2_R,1,1,"");
  h3_4->Divide(h3,ba3_1_R,1,1,"");

  
  // h1_1->Draw();


  // set b-amplifier errors to zero
  for(int i = 0; i < ba1_R->GetSize(); i++){
    ba1_R->SetBinError(i,0);
    ba2_R->SetBinError(i,0);
    ba3_R->SetBinError(i,0);
  }


  
  // divide fraction by b-amplifier
  h1->Divide(h1,ba1_R,1,1,"");
  h2->Divide(h2,ba2_R,1,1,"");
  h3->Divide(h3,ba3_R,1,1,"");

  // b_truth_pp_inclRecoMuTag_triggerOn_R->Draw();
  // h1_1->Draw("same");

  // TH1D *v = (TH1D*) b_truth_pp_inclRecoMuTag_triggerOn_R->Clone("v");
  // v->Divide(h1_1,b_truth_pp_inclRecoMuTag_triggerOn_R,1,1,"");

  // v->Draw();
  
  //b_truth_pp_R->Draw();

  // h2->SetLineColor(kRed-4);
  // h3->SetLineColor(kBlue-4);
  // h2->SetTitle("");
  // h2->SetStats(0);
  // h2->Draw();
  // h3->Draw("same");

  // ba2_R->SetLineColor(kRed-4);
  // ba3_R->SetLineColor(kBlue-4);
  // ba2_R->SetTitle("");
  // ba2_R->SetStats(0);
  // ba2_R->Draw();
  // ba3_R->Draw("same");
  
  
  
  
  
  
  double marker_size = 2.5;
  int line_width = 4;
  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);
  //h1->SetLineColor(kMagenta);
  //h1->SetMarkerColor(kMagenta);
  h1->SetMarkerStyle(89);
  h1->SetMarkerSize(marker_size);

  h2->SetLineColor(kRed-4);
  h2->SetMarkerColor(kRed-4);
  h2->SetMarkerStyle(90);
  h2->SetMarkerSize(marker_size);

  h3->SetLineColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h3->SetMarkerStyle(93);
  h3->SetMarkerSize(marker_size);

  h1->SetLineWidth(line_width);
  h2->SetLineWidth(line_width);
  h3->SetLineWidth(line_width);

  TH1D *r1, *r2, *r3;

  r1 = (TH1D*) h1->Clone("r1");
  r2 = (TH1D*) h2->Clone("r2");
  r3 = (TH1D*) h3->Clone("r3");

  // r1->Divide(h1,h1,1,1,"");
  // r2->Divide(h2,h1,1,1,"");
  // r3->Divide(h3,h1,1,1,"");

  
  
  // h1->Draw();
  // h2->Draw("same");
  // h3->Draw("same");

  TH1D *s1 = (TH1D*) r1->Clone("s1");
  TH1D *s2 = (TH1D*) r2->Clone("s2");
  TH1D *s3 = (TH1D*) r3->Clone("s3");

  double sys_input_pp_J1 = 0.0;
  double sys_input_pp_J2 = 0.0;
  double sys_input_pp_J3 = 0.0;
  double sys_input_pp_J4 = 0.0;
  double sys_input_pp_J5 = 0.0;
  double sys_input_pp_J6 = 0.0;

  double sys_input_C2_J1 = 0.0;
  double sys_input_C2_J2 = 0.0;
  double sys_input_C2_J3 = 0.0;
  double sys_input_C2_J4 = 0.0;
  double sys_input_C2_J5 = 0.0;
  double sys_input_C2_J6 = 0.0;

  double sys_input_C1_J1 = 0.0;
  double sys_input_C1_J2 = 0.0;
  double sys_input_C1_J3 = 0.0;
  double sys_input_C1_J4 = 0.0;
  double sys_input_C1_J5 = 0.0;
  double sys_input_C1_J6 = 0.0;

  double sys_input_X_J2 = 0.0;
  double sys_input_X_J3 = 0.0;
  double sys_input_X_J4 = 0.0;

  double sys_input_pp_X_J2 = 0.0;
  double sys_input_pp_X_J3 = 0.0;
  double sys_input_pp_X_J4 = 0.0;

  double sys_input_pp_U_J2 = 0.0;
  double sys_input_pp_U_J3 = 0.0;
  double sys_input_pp_U_J4 = 0.0;

  double sys_input_C2_X_J2 = 0.0;
  double sys_input_C2_X_J3 = 0.0;
  double sys_input_C2_X_J4 = 0.0;

  double sys_input_C2_U_J2 = 0.0;
  double sys_input_C2_U_J3 = 0.0;
  double sys_input_C2_U_J4 = 0.0;

  double sys_input_C1_X_J2 = 0.0;
  double sys_input_C1_X_J3 = 0.0;
  double sys_input_C1_X_J4 = 0.0;

  double sys_input_C1_U_J2 = 0.0;
  double sys_input_C1_U_J3 = 0.0;
  double sys_input_C1_U_J4 = 0.0;


  

  // if(do_mu5){

  //   // pp
  //   sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu5_J2*sys_cFraction_pp_mu5_J2 +
  // 				  sys_lowerBound_pp_mu5_J2*sys_lowerBound_pp_mu5_J2 +
  // 				  sys_bEnhance_pp_mu5_J2*sys_bEnhance_pp_mu5_J2 +
  // 				  sys_cEnhance_pp_mu5_J2*sys_cEnhance_pp_mu5_J2 +
  // 				  sys_JERsmear_pp_mu5_J2*sys_JERsmear_pp_mu5_J2 +
  // 				  sys_bGS_pp_mu5_J2*sys_bGS_pp_mu5_J2 +
  // 				  sys_JEUShiftUp_pp_mu5_J2*sys_JEUShiftUp_pp_mu5_J2 +
  // 				  sys_JEUShiftDown_pp_mu5_J2*sys_JEUShiftDown_pp_mu5_J2);
    
  //   sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu5_J3*sys_cFraction_pp_mu5_J3 +
  // 				  sys_lowerBound_pp_mu5_J3*sys_lowerBound_pp_mu5_J3 +
  // 				  sys_bEnhance_pp_mu5_J3*sys_bEnhance_pp_mu5_J3 +
  // 				  sys_cEnhance_pp_mu5_J3*sys_cEnhance_pp_mu5_J3 +
  // 				  sys_JERsmear_pp_mu5_J3*sys_JERsmear_pp_mu5_J3 +
  // 				  sys_bGS_pp_mu5_J3*sys_bGS_pp_mu5_J3 +
  // 				  sys_JEUShiftUp_pp_mu5_J3*sys_JEUShiftUp_pp_mu5_J3 +
  // 				  sys_JEUShiftDown_pp_mu5_J3*sys_JEUShiftDown_pp_mu5_J3);

  //   sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu5_J4*sys_cFraction_pp_mu5_J4 +
  // 				  sys_lowerBound_pp_mu5_J4*sys_lowerBound_pp_mu5_J4 +
  // 				  sys_bEnhance_pp_mu5_J4*sys_bEnhance_pp_mu5_J4 +
  // 				  sys_cEnhance_pp_mu5_J4*sys_cEnhance_pp_mu5_J4 +
  // 				  sys_JERsmear_pp_mu5_J4*sys_JERsmear_pp_mu5_J4 +
  // 				  sys_bGS_pp_mu5_J4*sys_bGS_pp_mu5_J4 +
  // 				  sys_JEUShiftUp_pp_mu5_J4*sys_JEUShiftUp_pp_mu5_J4 +
  // 				  sys_JEUShiftDown_pp_mu5_J4*sys_JEUShiftDown_pp_mu5_J4);

  //   // C2
  //   sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J2*sys_cFraction_PbPb_mu5_C2_J2 +
  // 				  sys_lowerBound_PbPb_mu5_C2_J2*sys_lowerBound_PbPb_mu5_C2_J2 +
  // 				  sys_bEnhance_PbPb_mu5_C2_J2*sys_bEnhance_PbPb_mu5_C2_J2 +
  // 				  sys_cEnhance_PbPb_mu5_C2_J2*sys_cEnhance_PbPb_mu5_C2_J2 +
  // 				  sys_JERsmear_PbPb_mu5_C2_J2*sys_JERsmear_PbPb_mu5_C2_J2 +
  // 				  sys_bGS_PbPb_mu5_C2_J2*sys_bGS_PbPb_mu5_C2_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C2_J2*sys_JEUShiftUp_PbPb_mu5_C2_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C2_J2*sys_JEUShiftDown_PbPb_mu5_C2_J2);
    
  //   sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J3*sys_cFraction_PbPb_mu5_C2_J3 +
  // 				  sys_lowerBound_PbPb_mu5_C2_J3*sys_lowerBound_PbPb_mu5_C2_J3 +
  // 				  sys_bEnhance_PbPb_mu5_C2_J3*sys_bEnhance_PbPb_mu5_C2_J3 +
  // 				  sys_cEnhance_PbPb_mu5_C2_J3*sys_cEnhance_PbPb_mu5_C2_J3 +
  // 				  sys_JERsmear_PbPb_mu5_C2_J3*sys_JERsmear_PbPb_mu5_C2_J3 +
  // 				  sys_bGS_PbPb_mu5_C2_J3*sys_bGS_PbPb_mu5_C2_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C2_J3*sys_JEUShiftUp_PbPb_mu5_C2_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C2_J3*sys_JEUShiftDown_PbPb_mu5_C2_J3);

  //   sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J4*sys_cFraction_PbPb_mu5_C2_J4 +
  // 				  sys_lowerBound_PbPb_mu5_C2_J4*sys_lowerBound_PbPb_mu5_C2_J4 +
  // 				  sys_bEnhance_PbPb_mu5_C2_J4*sys_bEnhance_PbPb_mu5_C2_J4 +
  // 				  sys_cEnhance_PbPb_mu5_C2_J4*sys_cEnhance_PbPb_mu5_C2_J4 +
  // 				  sys_JERsmear_PbPb_mu5_C2_J4*sys_JERsmear_PbPb_mu5_C2_J4 +
  // 				  sys_bGS_PbPb_mu5_C2_J4*sys_bGS_PbPb_mu5_C2_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C2_J4*sys_JEUShiftUp_PbPb_mu5_C2_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C2_J4*sys_JEUShiftDown_PbPb_mu5_C2_J4);

  //   // C1
  //   sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J2*sys_cFraction_PbPb_mu5_C1_J2 +
  // 				  sys_lowerBound_PbPb_mu5_C1_J2*sys_lowerBound_PbPb_mu5_C1_J2 +
  // 				  sys_bEnhance_PbPb_mu5_C1_J2*sys_bEnhance_PbPb_mu5_C1_J2 +
  // 				  sys_cEnhance_PbPb_mu5_C1_J2*sys_cEnhance_PbPb_mu5_C1_J2 +
  // 				  sys_JERsmear_PbPb_mu5_C1_J2*sys_JERsmear_PbPb_mu5_C1_J2 +
  // 				  sys_bGS_PbPb_mu5_C1_J2*sys_bGS_PbPb_mu5_C1_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C1_J2*sys_JEUShiftUp_PbPb_mu5_C1_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C1_J2*sys_JEUShiftDown_PbPb_mu5_C1_J2);
    
  //   sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J3*sys_cFraction_PbPb_mu5_C1_J3 +
  // 				  sys_lowerBound_PbPb_mu5_C1_J3*sys_lowerBound_PbPb_mu5_C1_J3 +
  // 				  sys_bEnhance_PbPb_mu5_C1_J3*sys_bEnhance_PbPb_mu5_C1_J3 +
  // 				  sys_cEnhance_PbPb_mu5_C1_J3*sys_cEnhance_PbPb_mu5_C1_J3 +
  // 				  sys_JERsmear_PbPb_mu5_C1_J3*sys_JERsmear_PbPb_mu5_C1_J3 +
  // 				  sys_bGS_PbPb_mu5_C1_J3*sys_bGS_PbPb_mu5_C1_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C1_J3*sys_JEUShiftUp_PbPb_mu5_C1_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C1_J3*sys_JEUShiftDown_PbPb_mu5_C1_J3);

  //   sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J4*sys_cFraction_PbPb_mu5_C1_J4 +
  // 				  sys_lowerBound_PbPb_mu5_C1_J4*sys_lowerBound_PbPb_mu5_C1_J4 +
  // 				  sys_bEnhance_PbPb_mu5_C1_J4*sys_bEnhance_PbPb_mu5_C1_J4 +
  // 				  sys_cEnhance_PbPb_mu5_C1_J4*sys_cEnhance_PbPb_mu5_C1_J4 +
  // 				  sys_JERsmear_PbPb_mu5_C1_J4*sys_JERsmear_PbPb_mu5_C1_J4 +
  // 				  sys_bGS_PbPb_mu5_C1_J4*sys_bGS_PbPb_mu5_C1_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu5_C1_J4*sys_JEUShiftUp_PbPb_mu5_C1_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu5_C1_J4*sys_JEUShiftDown_PbPb_mu5_C1_J4);

  //   // periph / central correlated systematic errors
  //   sys_input_X_J2 = TMath::Sqrt((sys_cFraction_PbPb_mu5_C1_J2 - sys_cFraction_PbPb_mu5_C2_J2)*(sys_cFraction_PbPb_mu5_C1_J2 - sys_cFraction_PbPb_mu5_C2_J2) +
  // 				  (sys_lowerBound_PbPb_mu5_C1_J2 - sys_lowerBound_PbPb_mu5_C2_J2)*(sys_lowerBound_PbPb_mu5_C1_J2 - sys_lowerBound_PbPb_mu5_C2_J2) +
  // 				  (sys_bEnhance_PbPb_mu5_C1_J2 - sys_bEnhance_PbPb_mu5_C2_J2)*(sys_bEnhance_PbPb_mu5_C1_J2 - sys_bEnhance_PbPb_mu5_C2_J2) +
  // 				  (sys_cEnhance_PbPb_mu5_C1_J2 - sys_cEnhance_PbPb_mu5_C2_J2)*(sys_cEnhance_PbPb_mu5_C1_J2 - sys_cEnhance_PbPb_mu5_C2_J2) +
  // 				  (sys_JERsmear_PbPb_mu5_C1_J2 - sys_JERsmear_PbPb_mu5_C2_J2)*(sys_JERsmear_PbPb_mu5_C1_J2 - sys_JERsmear_PbPb_mu5_C2_J2) +
  // 				  (sys_bGS_PbPb_mu5_C1_J2 - sys_bGS_PbPb_mu5_C2_J2)*(sys_bGS_PbPb_mu5_C1_J2 - sys_bGS_PbPb_mu5_C2_J2));

  //   sys_input_X_J3 = TMath::Sqrt((sys_cFraction_PbPb_mu5_C1_J3 - sys_cFraction_PbPb_mu5_C2_J3)*(sys_cFraction_PbPb_mu5_C1_J3 - sys_cFraction_PbPb_mu5_C2_J3) +
  // 				  (sys_lowerBound_PbPb_mu5_C1_J3 - sys_lowerBound_PbPb_mu5_C2_J3)*(sys_lowerBound_PbPb_mu5_C1_J3 - sys_lowerBound_PbPb_mu5_C2_J3) +
  // 				  (sys_bEnhance_PbPb_mu5_C1_J3 - sys_bEnhance_PbPb_mu5_C2_J3)*(sys_bEnhance_PbPb_mu5_C1_J3 - sys_bEnhance_PbPb_mu5_C2_J3) +
  // 				  (sys_cEnhance_PbPb_mu5_C1_J3 - sys_cEnhance_PbPb_mu5_C2_J3)*(sys_cEnhance_PbPb_mu5_C1_J3 - sys_cEnhance_PbPb_mu5_C2_J3) +
  // 				  (sys_JERsmear_PbPb_mu5_C1_J3 - sys_JERsmear_PbPb_mu5_C2_J3)*(sys_JERsmear_PbPb_mu5_C1_J3 - sys_JERsmear_PbPb_mu5_C2_J3) +
  // 				  (sys_bGS_PbPb_mu5_C1_J3 - sys_bGS_PbPb_mu5_C2_J3)*(sys_bGS_PbPb_mu5_C1_J3 - sys_bGS_PbPb_mu5_C2_J3));

  //   sys_input_X_J4 = TMath::Sqrt((sys_cFraction_PbPb_mu5_C1_J4 - sys_cFraction_PbPb_mu5_C2_J4)*(sys_cFraction_PbPb_mu5_C1_J4 - sys_cFraction_PbPb_mu5_C2_J4) +
  // 				 (sys_lowerBound_PbPb_mu5_C1_J4 - sys_lowerBound_PbPb_mu5_C2_J4)*(sys_lowerBound_PbPb_mu5_C1_J4 - sys_lowerBound_PbPb_mu5_C2_J4) +
  // 				 (sys_bEnhance_PbPb_mu5_C1_J4 - sys_bEnhance_PbPb_mu5_C2_J4)*(sys_bEnhance_PbPb_mu5_C1_J4 - sys_bEnhance_PbPb_mu5_C2_J4) +
  // 				 (sys_cEnhance_PbPb_mu5_C1_J4 - sys_cEnhance_PbPb_mu5_C2_J4)*(sys_cEnhance_PbPb_mu5_C1_J4 - sys_cEnhance_PbPb_mu5_C2_J4) +
  // 				 (sys_JERsmear_PbPb_mu5_C1_J4 - sys_JERsmear_PbPb_mu5_C2_J4)*(sys_JERsmear_PbPb_mu5_C1_J4 - sys_JERsmear_PbPb_mu5_C2_J4) +
  // 				 (sys_bGS_PbPb_mu5_C1_J4 - sys_bGS_PbPb_mu5_C2_J4)*(sys_bGS_PbPb_mu5_C1_J4 - sys_bGS_PbPb_mu5_C2_J4));
    
  // }


  // else if(do_mu7){

  //   // pp
  //   sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu7_J2*sys_cFraction_pp_mu7_J2 +
  // 				  sys_lowerBound_pp_mu7_J2*sys_lowerBound_pp_mu7_J2 +
  // 				  sys_bEnhance_pp_mu7_J2*sys_bEnhance_pp_mu7_J2 +
  // 				  sys_cEnhance_pp_mu7_J2*sys_cEnhance_pp_mu7_J2 +
  // 				  sys_JERsmear_pp_mu7_J2*sys_JERsmear_pp_mu7_J2 +
  // 				  sys_bGS_pp_mu7_J2*sys_bGS_pp_mu7_J2 +
  // 				  sys_JEUShiftUp_pp_mu7_J2*sys_JEUShiftUp_pp_mu7_J2 +
  // 				  sys_JEUShiftDown_pp_mu7_J2*sys_JEUShiftDown_pp_mu7_J2);
    
  //   sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu7_J3*sys_cFraction_pp_mu7_J3 +
  // 				  sys_lowerBound_pp_mu7_J3*sys_lowerBound_pp_mu7_J3 +
  // 				  sys_bEnhance_pp_mu7_J3*sys_bEnhance_pp_mu7_J3 +
  // 				  sys_cEnhance_pp_mu7_J3*sys_cEnhance_pp_mu7_J3 +
  // 				  sys_JERsmear_pp_mu7_J3*sys_JERsmear_pp_mu7_J3 +
  // 				  sys_bGS_pp_mu7_J3*sys_bGS_pp_mu7_J3 +
  // 				  sys_JEUShiftUp_pp_mu7_J3*sys_JEUShiftUp_pp_mu7_J3 +
  // 				  sys_JEUShiftDown_pp_mu7_J3*sys_JEUShiftDown_pp_mu7_J3);

  //   sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu7_J4*sys_cFraction_pp_mu7_J4 +
  // 				  sys_lowerBound_pp_mu7_J4*sys_lowerBound_pp_mu7_J4 +
  // 				  sys_bEnhance_pp_mu7_J4*sys_bEnhance_pp_mu7_J4 +
  // 				  sys_cEnhance_pp_mu7_J4*sys_cEnhance_pp_mu7_J4 +
  // 				  sys_JERsmear_pp_mu7_J4*sys_JERsmear_pp_mu7_J4 +
  // 				  sys_bGS_pp_mu7_J4*sys_bGS_pp_mu7_J4 +
  // 				  sys_JEUShiftUp_pp_mu7_J4*sys_JEUShiftUp_pp_mu7_J4 +
  // 				  sys_JEUShiftDown_pp_mu7_J4*sys_JEUShiftDown_pp_mu7_J4);

  //   // C2
  //   sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J2*sys_cFraction_PbPb_mu7_C2_J2 +
  // 				  sys_lowerBound_PbPb_mu7_C2_J2*sys_lowerBound_PbPb_mu7_C2_J2 +
  // 				  sys_bEnhance_PbPb_mu7_C2_J2*sys_bEnhance_PbPb_mu7_C2_J2 +
  // 				  sys_cEnhance_PbPb_mu7_C2_J2*sys_cEnhance_PbPb_mu7_C2_J2 +
  // 				  sys_JERsmear_PbPb_mu7_C2_J2*sys_JERsmear_PbPb_mu7_C2_J2 +
  // 				  sys_bGS_PbPb_mu7_C2_J2*sys_bGS_PbPb_mu7_C2_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C2_J2*sys_JEUShiftUp_PbPb_mu7_C2_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C2_J2*sys_JEUShiftDown_PbPb_mu7_C2_J2);
    
  //   sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J3*sys_cFraction_PbPb_mu7_C2_J3 +
  // 				  sys_lowerBound_PbPb_mu7_C2_J3*sys_lowerBound_PbPb_mu7_C2_J3 +
  // 				  sys_bEnhance_PbPb_mu7_C2_J3*sys_bEnhance_PbPb_mu7_C2_J3 +
  // 				  sys_cEnhance_PbPb_mu7_C2_J3*sys_cEnhance_PbPb_mu7_C2_J3 +
  // 				  sys_JERsmear_PbPb_mu7_C2_J3*sys_JERsmear_PbPb_mu7_C2_J3 +
  // 				  sys_bGS_PbPb_mu7_C2_J3*sys_bGS_PbPb_mu7_C2_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C2_J3*sys_JEUShiftUp_PbPb_mu7_C2_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C2_J3*sys_JEUShiftDown_PbPb_mu7_C2_J3);

  //   sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J4*sys_cFraction_PbPb_mu7_C2_J4 +
  // 				  sys_lowerBound_PbPb_mu7_C2_J4*sys_lowerBound_PbPb_mu7_C2_J4 +
  // 				  sys_bEnhance_PbPb_mu7_C2_J4*sys_bEnhance_PbPb_mu7_C2_J4 +
  // 				  sys_cEnhance_PbPb_mu7_C2_J4*sys_cEnhance_PbPb_mu7_C2_J4 +
  // 				  sys_JERsmear_PbPb_mu7_C2_J4*sys_JERsmear_PbPb_mu7_C2_J4 +
  // 				  sys_bGS_PbPb_mu7_C2_J4*sys_bGS_PbPb_mu7_C2_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C2_J4*sys_JEUShiftUp_PbPb_mu7_C2_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C2_J4*sys_JEUShiftDown_PbPb_mu7_C2_J4);

  //   // C1
  //   sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J2*sys_cFraction_PbPb_mu7_C1_J2 +
  // 				  sys_lowerBound_PbPb_mu7_C1_J2*sys_lowerBound_PbPb_mu7_C1_J2 +
  // 				  sys_bEnhance_PbPb_mu7_C1_J2*sys_bEnhance_PbPb_mu7_C1_J2 +
  // 				  sys_cEnhance_PbPb_mu7_C1_J2*sys_cEnhance_PbPb_mu7_C1_J2 +
  // 				  sys_JERsmear_PbPb_mu7_C1_J2*sys_JERsmear_PbPb_mu7_C1_J2 +
  // 				  sys_bGS_PbPb_mu7_C1_J2*sys_bGS_PbPb_mu7_C1_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C1_J2*sys_JEUShiftUp_PbPb_mu7_C1_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C1_J2*sys_JEUShiftDown_PbPb_mu7_C1_J2);
    
  //   sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J3*sys_cFraction_PbPb_mu7_C1_J3 +
  // 				  sys_lowerBound_PbPb_mu7_C1_J3*sys_lowerBound_PbPb_mu7_C1_J3 +
  // 				  sys_bEnhance_PbPb_mu7_C1_J3*sys_bEnhance_PbPb_mu7_C1_J3 +
  // 				  sys_cEnhance_PbPb_mu7_C1_J3*sys_cEnhance_PbPb_mu7_C1_J3 +
  // 				  sys_JERsmear_PbPb_mu7_C1_J3*sys_JERsmear_PbPb_mu7_C1_J3 +
  // 				  sys_bGS_PbPb_mu7_C1_J3*sys_bGS_PbPb_mu7_C1_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C1_J3*sys_JEUShiftUp_PbPb_mu7_C1_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C1_J3*sys_JEUShiftDown_PbPb_mu7_C1_J3);

  //   sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J4*sys_cFraction_PbPb_mu7_C1_J4 +
  // 				  sys_lowerBound_PbPb_mu7_C1_J4*sys_lowerBound_PbPb_mu7_C1_J4 +
  // 				  sys_bEnhance_PbPb_mu7_C1_J4*sys_bEnhance_PbPb_mu7_C1_J4 +
  // 				  sys_cEnhance_PbPb_mu7_C1_J4*sys_cEnhance_PbPb_mu7_C1_J4 +
  // 				  sys_JERsmear_PbPb_mu7_C1_J4*sys_JERsmear_PbPb_mu7_C1_J4 +
  // 				  sys_bGS_PbPb_mu7_C1_J4*sys_bGS_PbPb_mu7_C1_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu7_C1_J4*sys_JEUShiftUp_PbPb_mu7_C1_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu7_C1_J4*sys_JEUShiftDown_PbPb_mu7_C1_J4);


  //   // periph / central correlated systematic errors
  //   sys_input_X_J2 = TMath::Sqrt((sys_cFraction_PbPb_mu7_C1_J2 - sys_cFraction_PbPb_mu7_C2_J2)*(sys_cFraction_PbPb_mu7_C1_J2 - sys_cFraction_PbPb_mu7_C2_J2) +
  // 				  (sys_lowerBound_PbPb_mu7_C1_J2 - sys_lowerBound_PbPb_mu7_C2_J2)*(sys_lowerBound_PbPb_mu7_C1_J2 - sys_lowerBound_PbPb_mu7_C2_J2) +
  // 				  (sys_bEnhance_PbPb_mu7_C1_J2 - sys_bEnhance_PbPb_mu7_C2_J2)*(sys_bEnhance_PbPb_mu7_C1_J2 - sys_bEnhance_PbPb_mu7_C2_J2) +
  // 				  (sys_cEnhance_PbPb_mu7_C1_J2 - sys_cEnhance_PbPb_mu7_C2_J2)*(sys_cEnhance_PbPb_mu7_C1_J2 - sys_cEnhance_PbPb_mu7_C2_J2) +
  // 				  (sys_JERsmear_PbPb_mu7_C1_J2 - sys_JERsmear_PbPb_mu7_C2_J2)*(sys_JERsmear_PbPb_mu7_C1_J2 - sys_JERsmear_PbPb_mu7_C2_J2) +
  // 				  (sys_bGS_PbPb_mu7_C1_J2 - sys_bGS_PbPb_mu7_C2_J2)*(sys_bGS_PbPb_mu7_C1_J2 - sys_bGS_PbPb_mu7_C2_J2));

  //   sys_input_X_J3 = TMath::Sqrt((sys_cFraction_PbPb_mu7_C1_J3 - sys_cFraction_PbPb_mu7_C2_J3)*(sys_cFraction_PbPb_mu7_C1_J3 - sys_cFraction_PbPb_mu7_C2_J3) +
  // 				  (sys_lowerBound_PbPb_mu7_C1_J3 - sys_lowerBound_PbPb_mu7_C2_J3)*(sys_lowerBound_PbPb_mu7_C1_J3 - sys_lowerBound_PbPb_mu7_C2_J3) +
  // 				  (sys_bEnhance_PbPb_mu7_C1_J3 - sys_bEnhance_PbPb_mu7_C2_J3)*(sys_bEnhance_PbPb_mu7_C1_J3 - sys_bEnhance_PbPb_mu7_C2_J3) +
  // 				  (sys_cEnhance_PbPb_mu7_C1_J3 - sys_cEnhance_PbPb_mu7_C2_J3)*(sys_cEnhance_PbPb_mu7_C1_J3 - sys_cEnhance_PbPb_mu7_C2_J3) +
  // 				  (sys_JERsmear_PbPb_mu7_C1_J3 - sys_JERsmear_PbPb_mu7_C2_J3)*(sys_JERsmear_PbPb_mu7_C1_J3 - sys_JERsmear_PbPb_mu7_C2_J3) +
  // 				  (sys_bGS_PbPb_mu7_C1_J3 - sys_bGS_PbPb_mu7_C2_J3)*(sys_bGS_PbPb_mu7_C1_J3 - sys_bGS_PbPb_mu7_C2_J3));

  //   sys_input_X_J4 = TMath::Sqrt((sys_cFraction_PbPb_mu7_C1_J4 - sys_cFraction_PbPb_mu7_C2_J4)*(sys_cFraction_PbPb_mu7_C1_J4 - sys_cFraction_PbPb_mu7_C2_J4) +
  // 				 (sys_lowerBound_PbPb_mu7_C1_J4 - sys_lowerBound_PbPb_mu7_C2_J4)*(sys_lowerBound_PbPb_mu7_C1_J4 - sys_lowerBound_PbPb_mu7_C2_J4) +
  // 				 (sys_bEnhance_PbPb_mu7_C1_J4 - sys_bEnhance_PbPb_mu7_C2_J4)*(sys_bEnhance_PbPb_mu7_C1_J4 - sys_bEnhance_PbPb_mu7_C2_J4) +
  // 				 (sys_cEnhance_PbPb_mu7_C1_J4 - sys_cEnhance_PbPb_mu7_C2_J4)*(sys_cEnhance_PbPb_mu7_C1_J4 - sys_cEnhance_PbPb_mu7_C2_J4) +
  // 				 (sys_JERsmear_PbPb_mu7_C1_J4 - sys_JERsmear_PbPb_mu7_C2_J4)*(sys_JERsmear_PbPb_mu7_C1_J4 - sys_JERsmear_PbPb_mu7_C2_J4) +
  // 				 (sys_bGS_PbPb_mu7_C1_J4 - sys_bGS_PbPb_mu7_C2_J4)*(sys_bGS_PbPb_mu7_C1_J4 - sys_bGS_PbPb_mu7_C2_J4));
    



  // }

  // else if(do_mu12){

  //   // pp
  //   sys_input_pp_J1 = TMath::Sqrt(sys_cFraction_pp_mu12_J1*sys_cFraction_pp_mu12_J1 +
  // 				  sys_lowerBound_pp_mu12_J1*sys_lowerBound_pp_mu12_J1 +
  // 				  sys_bEnhance_pp_mu12_J1*sys_bEnhance_pp_mu12_J1 +
  // 				  sys_cEnhance_pp_mu12_J1*sys_cEnhance_pp_mu12_J1 +
  // 				  sys_JERsmear_pp_mu12_J1*sys_JERsmear_pp_mu12_J1 +
  // 				  sys_bGS_pp_mu12_J1*sys_bGS_pp_mu12_J1 +
  // 				  sys_JEUShiftUp_pp_mu12_J1*sys_JEUShiftUp_pp_mu12_J1 +
  // 				  sys_JEUShiftDown_pp_mu12_J1*sys_JEUShiftDown_pp_mu12_J1+
  // 				  sys_residual_pp_mu12_J1*sys_residual_pp_mu12_J1);

  //   sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu12_J2*sys_cFraction_pp_mu12_J2 +
  // 				  sys_lowerBound_pp_mu12_J2*sys_lowerBound_pp_mu12_J2 +
  // 				  sys_bEnhance_pp_mu12_J2*sys_bEnhance_pp_mu12_J2 +
  // 				  sys_cEnhance_pp_mu12_J2*sys_cEnhance_pp_mu12_J2 +
  // 				  sys_JERsmear_pp_mu12_J2*sys_JERsmear_pp_mu12_J2 +
  // 				  sys_bGS_pp_mu12_J2*sys_bGS_pp_mu12_J2 +
  // 				  sys_JEUShiftUp_pp_mu12_J2*sys_JEUShiftUp_pp_mu12_J2 +
  // 				  sys_JEUShiftDown_pp_mu12_J2*sys_JEUShiftDown_pp_mu12_J2+
  // 				  sys_residual_pp_mu12_J2*sys_residual_pp_mu12_J2);
    
  //   sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu12_J3*sys_cFraction_pp_mu12_J3 +
  // 				  sys_lowerBound_pp_mu12_J3*sys_lowerBound_pp_mu12_J3 +
  // 				  sys_bEnhance_pp_mu12_J3*sys_bEnhance_pp_mu12_J3 +
  // 				  sys_cEnhance_pp_mu12_J3*sys_cEnhance_pp_mu12_J3 +
  // 				  sys_JERsmear_pp_mu12_J3*sys_JERsmear_pp_mu12_J3 +
  // 				  sys_bGS_pp_mu12_J3*sys_bGS_pp_mu12_J3 +
  // 				  sys_JEUShiftUp_pp_mu12_J3*sys_JEUShiftUp_pp_mu12_J3 +
  // 				  sys_JEUShiftDown_pp_mu12_J3*sys_JEUShiftDown_pp_mu12_J3+
  // 				  sys_residual_pp_mu12_J3*sys_residual_pp_mu12_J3);

  //   sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu12_J4*sys_cFraction_pp_mu12_J4 +
  // 				  sys_lowerBound_pp_mu12_J4*sys_lowerBound_pp_mu12_J4 +
  // 				  sys_bEnhance_pp_mu12_J4*sys_bEnhance_pp_mu12_J4 +
  // 				  sys_cEnhance_pp_mu12_J4*sys_cEnhance_pp_mu12_J4 +
  // 				  sys_JERsmear_pp_mu12_J4*sys_JERsmear_pp_mu12_J4 +
  // 				  sys_bGS_pp_mu12_J4*sys_bGS_pp_mu12_J4 +
  // 				  sys_JEUShiftUp_pp_mu12_J4*sys_JEUShiftUp_pp_mu12_J4 +
  // 				  sys_JEUShiftDown_pp_mu12_J4*sys_JEUShiftDown_pp_mu12_J4+
  // 				  sys_residual_pp_mu12_J4*sys_residual_pp_mu12_J4);

  //   sys_input_pp_J5 = TMath::Sqrt(sys_cFraction_pp_mu12_J5*sys_cFraction_pp_mu12_J5 +
  // 				  sys_lowerBound_pp_mu12_J5*sys_lowerBound_pp_mu12_J5 +
  // 				  sys_bEnhance_pp_mu12_J5*sys_bEnhance_pp_mu12_J5 +
  // 				  sys_cEnhance_pp_mu12_J5*sys_cEnhance_pp_mu12_J5 +
  // 				  sys_JERsmear_pp_mu12_J5*sys_JERsmear_pp_mu12_J5 +
  // 				  sys_bGS_pp_mu12_J5*sys_bGS_pp_mu12_J5 +
  // 				  sys_JEUShiftUp_pp_mu12_J5*sys_JEUShiftUp_pp_mu12_J5 +
  // 				  sys_JEUShiftDown_pp_mu12_J5*sys_JEUShiftDown_pp_mu12_J5+
  // 				  sys_residual_pp_mu12_J5*sys_residual_pp_mu12_J5);

  //   sys_input_pp_J6 = TMath::Sqrt(sys_cFraction_pp_mu12_J6*sys_cFraction_pp_mu12_J6 +
  // 				  sys_lowerBound_pp_mu12_J6*sys_lowerBound_pp_mu12_J6 +
  // 				  sys_bEnhance_pp_mu12_J6*sys_bEnhance_pp_mu12_J6 +
  // 				  sys_cEnhance_pp_mu12_J6*sys_cEnhance_pp_mu12_J6 +
  // 				  sys_JERsmear_pp_mu12_J6*sys_JERsmear_pp_mu12_J6 +
  // 				  sys_bGS_pp_mu12_J6*sys_bGS_pp_mu12_J6 +
  // 				  sys_JEUShiftUp_pp_mu12_J6*sys_JEUShiftUp_pp_mu12_J6 +
  // 				  sys_JEUShiftDown_pp_mu12_J6*sys_JEUShiftDown_pp_mu12_J6+
  // 				  sys_residual_pp_mu12_J6*sys_residual_pp_mu12_J6);    

  //   // C2
  //   sys_input_C2_J1 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J1*sys_cFraction_PbPb_mu12_C2_J1 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J1*sys_lowerBound_PbPb_mu12_C2_J1 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J1*sys_bEnhance_PbPb_mu12_C2_J1 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J1*sys_cEnhance_PbPb_mu12_C2_J1 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J1*sys_JERsmear_PbPb_mu12_C2_J1 +
  // 				  sys_bGS_PbPb_mu12_C2_J1*sys_bGS_PbPb_mu12_C2_J1 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J1*sys_JEUShiftUp_PbPb_mu12_C2_J1 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J1*sys_JEUShiftDown_PbPb_mu12_C2_J1+
  // 				  sys_residual_pp_mu12_J1*sys_residual_pp_mu12_J1);

  //   sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J2*sys_cFraction_PbPb_mu12_C2_J2 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J2*sys_lowerBound_PbPb_mu12_C2_J2 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J2*sys_bEnhance_PbPb_mu12_C2_J2 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J2*sys_cEnhance_PbPb_mu12_C2_J2 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J2*sys_JERsmear_PbPb_mu12_C2_J2 +
  // 				  sys_bGS_PbPb_mu12_C2_J2*sys_bGS_PbPb_mu12_C2_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J2*sys_JEUShiftUp_PbPb_mu12_C2_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J2*sys_JEUShiftDown_PbPb_mu12_C2_J2+
  // 				  sys_residual_pp_mu12_J2*sys_residual_pp_mu12_J2);    
    
  //   sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J3*sys_cFraction_PbPb_mu12_C2_J3 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J3*sys_lowerBound_PbPb_mu12_C2_J3 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J3*sys_bEnhance_PbPb_mu12_C2_J3 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J3*sys_cEnhance_PbPb_mu12_C2_J3 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J3*sys_JERsmear_PbPb_mu12_C2_J3 +
  // 				  sys_bGS_PbPb_mu12_C2_J3*sys_bGS_PbPb_mu12_C2_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J3*sys_JEUShiftUp_PbPb_mu12_C2_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J3*sys_JEUShiftDown_PbPb_mu12_C2_J3+
  // 				  sys_residual_pp_mu12_J3*sys_residual_pp_mu12_J3);

  //   sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J4*sys_cFraction_PbPb_mu12_C2_J4 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J4*sys_lowerBound_PbPb_mu12_C2_J4 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J4*sys_bEnhance_PbPb_mu12_C2_J4 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J4*sys_cEnhance_PbPb_mu12_C2_J4 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J4*sys_JERsmear_PbPb_mu12_C2_J4 +
  // 				  sys_bGS_PbPb_mu12_C2_J4*sys_bGS_PbPb_mu12_C2_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J4*sys_JEUShiftUp_PbPb_mu12_C2_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J4*sys_JEUShiftDown_PbPb_mu12_C2_J4+
  // 				  sys_residual_pp_mu12_J4*sys_residual_pp_mu12_J4);

  //   sys_input_C2_J5 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J5*sys_cFraction_PbPb_mu12_C2_J5 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J5*sys_lowerBound_PbPb_mu12_C2_J5 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J5*sys_bEnhance_PbPb_mu12_C2_J5 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J5*sys_cEnhance_PbPb_mu12_C2_J5 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J5*sys_JERsmear_PbPb_mu12_C2_J5 +
  // 				  sys_bGS_PbPb_mu12_C2_J5*sys_bGS_PbPb_mu12_C2_J5 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J5*sys_JEUShiftUp_PbPb_mu12_C2_J5 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J5*sys_JEUShiftDown_PbPb_mu12_C2_J5+
  // 				  sys_residual_pp_mu12_J5*sys_residual_pp_mu12_J5);

  //   sys_input_C2_J6 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J6*sys_cFraction_PbPb_mu12_C2_J6 +
  // 				  sys_lowerBound_PbPb_mu12_C2_J6*sys_lowerBound_PbPb_mu12_C2_J6 +
  // 				  sys_bEnhance_PbPb_mu12_C2_J6*sys_bEnhance_PbPb_mu12_C2_J6 +
  // 				  sys_cEnhance_PbPb_mu12_C2_J6*sys_cEnhance_PbPb_mu12_C2_J6 +
  // 				  sys_JERsmear_PbPb_mu12_C2_J6*sys_JERsmear_PbPb_mu12_C2_J6 +
  // 				  sys_bGS_PbPb_mu12_C2_J6*sys_bGS_PbPb_mu12_C2_J6 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C2_J6*sys_JEUShiftUp_PbPb_mu12_C2_J6 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C2_J6*sys_JEUShiftDown_PbPb_mu12_C2_J6+
  // 				  sys_residual_pp_mu12_J6*sys_residual_pp_mu12_J6);


  //   // C1
  //   sys_input_C1_J1 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J1*sys_cFraction_PbPb_mu12_C1_J1 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J1*sys_lowerBound_PbPb_mu12_C1_J1 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J1*sys_bEnhance_PbPb_mu12_C1_J1 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J1*sys_cEnhance_PbPb_mu12_C1_J1 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J1*sys_JERsmear_PbPb_mu12_C1_J1 +
  // 				  sys_bGS_PbPb_mu12_C1_J1*sys_bGS_PbPb_mu12_C1_J1 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J1*sys_JEUShiftUp_PbPb_mu12_C1_J1 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J1*sys_JEUShiftDown_PbPb_mu12_C1_J1+
  // 				  sys_residual_pp_mu12_J1*sys_residual_pp_mu12_J1);

  //   sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J2*sys_cFraction_PbPb_mu12_C1_J2 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J2*sys_lowerBound_PbPb_mu12_C1_J2 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J2*sys_bEnhance_PbPb_mu12_C1_J2 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J2*sys_cEnhance_PbPb_mu12_C1_J2 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J2*sys_JERsmear_PbPb_mu12_C1_J2 +
  // 				  sys_bGS_PbPb_mu12_C1_J2*sys_bGS_PbPb_mu12_C1_J2 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J2*sys_JEUShiftUp_PbPb_mu12_C1_J2 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J2*sys_JEUShiftDown_PbPb_mu12_C1_J2+
  // 				  sys_residual_pp_mu12_J2*sys_residual_pp_mu12_J2);
    
    
  //   sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J3*sys_cFraction_PbPb_mu12_C1_J3 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J3*sys_lowerBound_PbPb_mu12_C1_J3 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J3*sys_bEnhance_PbPb_mu12_C1_J3 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J3*sys_cEnhance_PbPb_mu12_C1_J3 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J3*sys_JERsmear_PbPb_mu12_C1_J3 +
  // 				  sys_bGS_PbPb_mu12_C1_J3*sys_bGS_PbPb_mu12_C1_J3 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J3*sys_JEUShiftUp_PbPb_mu12_C1_J3 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J3*sys_JEUShiftDown_PbPb_mu12_C1_J3+
  // 				  sys_residual_pp_mu12_J3*sys_residual_pp_mu12_J3);

  //   sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J4*sys_cFraction_PbPb_mu12_C1_J4 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J4*sys_lowerBound_PbPb_mu12_C1_J4 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J4*sys_bEnhance_PbPb_mu12_C1_J4 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J4*sys_cEnhance_PbPb_mu12_C1_J4 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J4*sys_JERsmear_PbPb_mu12_C1_J4 +
  // 				  sys_bGS_PbPb_mu12_C1_J4*sys_bGS_PbPb_mu12_C1_J4 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J4*sys_JEUShiftUp_PbPb_mu12_C1_J4 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J4*sys_JEUShiftDown_PbPb_mu12_C1_J4+
  // 				  sys_residual_pp_mu12_J4*sys_residual_pp_mu12_J4);

  //   sys_input_C1_J5 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J5*sys_cFraction_PbPb_mu12_C1_J5 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J5*sys_lowerBound_PbPb_mu12_C1_J5 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J5*sys_bEnhance_PbPb_mu12_C1_J5 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J5*sys_cEnhance_PbPb_mu12_C1_J5 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J5*sys_JERsmear_PbPb_mu12_C1_J5 +
  // 				  sys_bGS_PbPb_mu12_C1_J5*sys_bGS_PbPb_mu12_C1_J5 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J5*sys_JEUShiftUp_PbPb_mu12_C1_J5 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J5*sys_JEUShiftDown_PbPb_mu12_C1_J5+
  // 				  sys_residual_pp_mu12_J5*sys_residual_pp_mu12_J5);

  //   sys_input_C1_J6 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J6*sys_cFraction_PbPb_mu12_C1_J6 +
  // 				  sys_lowerBound_PbPb_mu12_C1_J6*sys_lowerBound_PbPb_mu12_C1_J6 +
  // 				  sys_bEnhance_PbPb_mu12_C1_J6*sys_bEnhance_PbPb_mu12_C1_J6 +
  // 				  sys_cEnhance_PbPb_mu12_C1_J6*sys_cEnhance_PbPb_mu12_C1_J6 +
  // 				  sys_JERsmear_PbPb_mu12_C1_J6*sys_JERsmear_PbPb_mu12_C1_J6 +
  // 				  sys_bGS_PbPb_mu12_C1_J6*sys_bGS_PbPb_mu12_C1_J6 +
  // 				  sys_JEUShiftUp_PbPb_mu12_C1_J6*sys_JEUShiftUp_PbPb_mu12_C1_J6 +
  // 				  sys_JEUShiftDown_PbPb_mu12_C1_J6*sys_JEUShiftDown_PbPb_mu12_C1_J6+
  // 				  sys_residual_pp_mu12_J6*sys_residual_pp_mu12_J6);    



  //   // correlated errors

  //   sys_input_pp_X_J2 = TMath::Sqrt(sys_cFraction_pp_mu12_J2*sys_cFraction_pp_mu12_J2 +
  // 				    sys_bGS_pp_mu12_J2*sys_bGS_pp_mu12_J2);
  //   sys_input_pp_X_J3 = TMath::Sqrt(sys_cFraction_pp_mu12_J3*sys_cFraction_pp_mu12_J3 +
  // 				    sys_bGS_pp_mu12_J3*sys_bGS_pp_mu12_J3);
  //   sys_input_pp_X_J4 = TMath::Sqrt(sys_cFraction_pp_mu12_J4*sys_cFraction_pp_mu12_J4 +
  // 				    sys_bGS_pp_mu12_J4*sys_bGS_pp_mu12_J4);

    

  //   // periph / central correlated systematic errors
  //   sys_input_X_J2 = TMath::Sqrt((sys_cFraction_PbPb_mu12_C1_J2 - sys_cFraction_PbPb_mu12_C2_J2)*(sys_cFraction_PbPb_mu12_C1_J2 - sys_cFraction_PbPb_mu12_C2_J2) +
  // 				  (sys_lowerBound_PbPb_mu12_C1_J2 - sys_lowerBound_PbPb_mu12_C2_J2)*(sys_lowerBound_PbPb_mu12_C1_J2 - sys_lowerBound_PbPb_mu12_C2_J2) +
  // 				  (sys_bEnhance_PbPb_mu12_C1_J2 - sys_bEnhance_PbPb_mu12_C2_J2)*(sys_bEnhance_PbPb_mu12_C1_J2 - sys_bEnhance_PbPb_mu12_C2_J2) +
  // 				  (sys_cEnhance_PbPb_mu12_C1_J2 - sys_cEnhance_PbPb_mu12_C2_J2)*(sys_cEnhance_PbPb_mu12_C1_J2 - sys_cEnhance_PbPb_mu12_C2_J2) +
  // 				  (sys_JERsmear_PbPb_mu12_C1_J2 - sys_JERsmear_PbPb_mu12_C2_J2)*(sys_JERsmear_PbPb_mu12_C1_J2 - sys_JERsmear_PbPb_mu12_C2_J2) +
  // 				  (sys_bGS_PbPb_mu12_C1_J2 - sys_bGS_PbPb_mu12_C2_J2)*(sys_bGS_PbPb_mu12_C1_J2 - sys_bGS_PbPb_mu12_C2_J2));

  //   sys_input_X_J3 = TMath::Sqrt((sys_cFraction_PbPb_mu12_C1_J3 - sys_cFraction_PbPb_mu12_C2_J3)*(sys_cFraction_PbPb_mu12_C1_J3 - sys_cFraction_PbPb_mu12_C2_J3) +
  // 				  (sys_lowerBound_PbPb_mu12_C1_J3 - sys_lowerBound_PbPb_mu12_C2_J3)*(sys_lowerBound_PbPb_mu12_C1_J3 - sys_lowerBound_PbPb_mu12_C2_J3) +
  // 				  (sys_bEnhance_PbPb_mu12_C1_J3 - sys_bEnhance_PbPb_mu12_C2_J3)*(sys_bEnhance_PbPb_mu12_C1_J3 - sys_bEnhance_PbPb_mu12_C2_J3) +
  // 				  (sys_cEnhance_PbPb_mu12_C1_J3 - sys_cEnhance_PbPb_mu12_C2_J3)*(sys_cEnhance_PbPb_mu12_C1_J3 - sys_cEnhance_PbPb_mu12_C2_J3) +
  // 				  (sys_JERsmear_PbPb_mu12_C1_J3 - sys_JERsmear_PbPb_mu12_C2_J3)*(sys_JERsmear_PbPb_mu12_C1_J3 - sys_JERsmear_PbPb_mu12_C2_J3) +
  // 				  (sys_bGS_PbPb_mu12_C1_J3 - sys_bGS_PbPb_mu12_C2_J3)*(sys_bGS_PbPb_mu12_C1_J3 - sys_bGS_PbPb_mu12_C2_J3));

  //   sys_input_X_J4 = TMath::Sqrt((sys_cFraction_PbPb_mu12_C1_J4 - sys_cFraction_PbPb_mu12_C2_J4)*(sys_cFraction_PbPb_mu12_C1_J4 - sys_cFraction_PbPb_mu12_C2_J4) +
  // 				 (sys_lowerBound_PbPb_mu12_C1_J4 - sys_lowerBound_PbPb_mu12_C2_J4)*(sys_lowerBound_PbPb_mu12_C1_J4 - sys_lowerBound_PbPb_mu12_C2_J4) +
  // 				 (sys_bEnhance_PbPb_mu12_C1_J4 - sys_bEnhance_PbPb_mu12_C2_J4)*(sys_bEnhance_PbPb_mu12_C1_J4 - sys_bEnhance_PbPb_mu12_C2_J4) +
  // 				 (sys_cEnhance_PbPb_mu12_C1_J4 - sys_cEnhance_PbPb_mu12_C2_J4)*(sys_cEnhance_PbPb_mu12_C1_J4 - sys_cEnhance_PbPb_mu12_C2_J4) +
  // 				 (sys_JERsmear_PbPb_mu12_C1_J4 - sys_JERsmear_PbPb_mu12_C2_J4)*(sys_JERsmear_PbPb_mu12_C1_J4 - sys_JERsmear_PbPb_mu12_C2_J4) +
  // 				 (sys_bGS_PbPb_mu12_C1_J4 - sys_bGS_PbPb_mu12_C2_J4)*(sys_bGS_PbPb_mu12_C1_J4 - sys_bGS_PbPb_mu12_C2_J4));
    
  // }
  
    
  

  
  // else{};

  
  s1->SetBinError(1,sys_input_pp_J1*s1->GetBinContent(1));
  s1->SetBinError(2,sys_input_pp_J2*s1->GetBinContent(2));
  s1->SetBinError(3,sys_input_pp_J3*s1->GetBinContent(3));
  s1->SetBinError(4,sys_input_pp_J4*s1->GetBinContent(4));
  s1->SetBinError(5,sys_input_pp_J5*s1->GetBinContent(5));
  s1->SetBinError(6,sys_input_pp_J6*s1->GetBinContent(6));      
  
  s2->SetBinError(1,sys_input_C2_J1*s2->GetBinContent(1));
  s2->SetBinError(2,sys_input_C2_J2*s2->GetBinContent(2));
  s2->SetBinError(3,sys_input_C2_J3*s2->GetBinContent(3));
  s2->SetBinError(4,sys_input_C2_J4*s2->GetBinContent(4));
  s2->SetBinError(5,sys_input_C2_J5*s2->GetBinContent(5));
  s2->SetBinError(6,sys_input_C2_J6*s2->GetBinContent(6));

  s3->SetBinError(1,sys_input_C1_J1*s3->GetBinContent(1));
  s3->SetBinError(2,sys_input_C1_J2*s3->GetBinContent(2));
  s3->SetBinError(3,sys_input_C1_J3*s3->GetBinContent(3));
  s3->SetBinError(4,sys_input_C1_J4*s3->GetBinContent(4));
  s3->SetBinError(5,sys_input_C1_J5*s3->GetBinContent(5));
  s3->SetBinError(6,sys_input_C1_J6*s3->GetBinContent(6));      

  s1->SetFillColorAlpha(kBlack,1.0);
  //s1->SetFillColorAlpha(kMagenta,1.0);
  //s1->SetLineColor(kMagenta);
  s1->SetFillStyle(3345);
  s2->SetFillColorAlpha(kRed-4,0.5);
  s3->SetFillColorAlpha(kBlue-4,0.5);
  
  // dont include last point in PbPb (stats too low)
  // r2->SetBinContent(6,100);
  // r2->SetBinError(6,100);
  // r3->SetBinContent(6,100);
  // r3->SetBinError(6,100);
  // s2->SetBinContent(6,100);
  // s2->SetBinError(6,100);
  // s3->SetBinContent(6,100);
  // s3->SetBinError(6,100);
  


  TCanvas *canv = new TCanvas("canv","canv",600,600);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.2);
  pad->Draw();
  pad->cd();
  //r2->GetYaxis()->SetTitle("#it{f}_{#it{b}}(PbPb) / #it{f}_{#it{b}}(pp)");
  s1->GetYaxis()->SetTitle("inclusive #font[52]{b}-jet fraction");
  s1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{jet} [GeV]");
  s1->GetXaxis()->SetRangeUser(80,300);
  //r2->GetYaxis()->SetRangeUser(0,2);
  s1->GetYaxis()->SetRangeUser(0,0.14);
  //r1->GetYaxis()->SetRangeUser(0.00,0.10);
  //r1->GetYaxis()->SetRangeUser(0.02,0.07);
  s1->SetTitle("");
  s1->SetStats(0);
  s1->Draw("e2");
  s2->Draw("e2 same");
  s3->Draw("e2 same");
  r1->Draw("same");
  //r1->Draw();
  r2->Draw("same");
  r3->Draw("same");


  TString jet_pt_cout[7] = {"null","80 < pT,jet (GeV) < 100","100 < pT,jet (GeV) < 120","120 < pT,jet (GeV) < 150","150 < pT,jet (GeV) < 200", "200 < pT,jet (GeV) < 300", "300 < pT,jet (GeV) < 500"};
  cout << " ~~~~~~ pp ~~~~~~ " << endl;
  for(int i = 0; i < 7; i++){
    cout << jet_pt_cout[i] << " | f_b^incl = " << 100.*r1->GetBinContent(i) << "+/- " << 100.*r1->GetBinError(i) << " (stat.) +/- " << 100.*s1->GetBinError(i) << " (sys.) "   << endl ;
  }
  cout << " ~~~~~~ PbPb 30-90% ~~~~~~ " << endl;
  for(int i = 0; i < 7; i++){
    cout << jet_pt_cout[i] << " | f_b^incl = " << 100.*r2->GetBinContent(i) << "+/- " << 100.*r2->GetBinError(i) << " (stat.) +/- " << 100.*s2->GetBinError(i) << " (sys.) "   << endl ;
  }
  cout << " ~~~~~~ PbPb 0-30% ~~~~~~ " << endl;
  for(int i = 0; i < 7; i++){
    cout << jet_pt_cout[i] << " | f_b^incl = " << 100.*r3->GetBinContent(i) << "+/- " << 100.*r3->GetBinError(i) << " (stat.) +/- " << 100.*s3->GetBinError(i) << " (sys.) "   << endl ;
  }
  


  TLegend *leg = new TLegend(0.62,0.75,0.85,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.028);
  leg->AddEntry(h1,"pp","p");
  leg->AddEntry(h2,"PbPb 30-90%","p");
  leg->AddEntry(h3,"PbPb 0-30%","p");

  // leg->AddEntry(h1,"PYTHIA","p");
  // leg->AddEntry(h2,"PYTHIA+HYDJET 30-90%","p");
  // leg->AddEntry(h3,"PYTHIA+HYDJET 0-30%","p");
  
  //leg->AddEntry(h1,"PYTHIA","p");
  //leg->AddEntry(h1,"PYTHIA w/ energy-corr.","p");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.03);
  la->DrawLatexNDC(0.21,0.92,"#font[62]{CMS }#scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextSize(0.025);
  if(do_mu5) la->DrawLatexNDC(0.42,0.92,"PbPb (323 #mub^{-1}), pp (99 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu7) la->DrawLatexNDC(0.42,0.92,"PbPb (787 #mub^{-1}), pp (274 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu12) la->DrawLatexNDC(0.42,0.92,"PbPb (1689 #mub^{-1}), pp (301 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else{};
  

  //b_truth_pp->Draw("hist same");
  b_truth_gen->Draw("hist same");
  //b_truth_pp->Rebin(5); b_truth_pp->Scale(1./5.);
  //b_truth_C2->Draw("hist same");
  //b_truth_C1->Draw("hist same");

  TLegend *leg2 = new TLegend(0.22,0.75,0.5,0.88);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.028);
  //leg2->AddEntry(b_truth_pp,"PYTHIA Reco","l");
  leg2->AddEntry(b_truth_gen,"PYTHIA","l");
  // leg2->AddEntry(b_truth_C2,"PYTHIA+HYDJET 30-90%","l");
  // leg2->AddEntry(b_truth_C1,"PYTHIA+HYDJET 0-30%","l");
  leg2->Draw();

  
  TString canv_bFrac_save_string = "";

  if(do_mu5){
    canv_bFrac_save_string = "../../../figures/results/bFraction_mu5.pdf";
  }
  else if(do_mu7){
    canv_bFrac_save_string = "../../../figures/results/bFraction_mu7.pdf";
  }
  else if(do_mu12){
    canv_bFrac_save_string = "../../../figures/results/bFraction_mu12.pdf";
  }
  else{};
  
  canv->SaveAs(canv_bFrac_save_string);
  

  // MC closure plot

  TCanvas *canv_cl = new TCanvas("canv_cl","canv_cl",600,600);
  canv_cl->cd();
  TPad *pad_cl = new TPad("pad_cl","pad_cl",0,0,1,1);
  pad_cl->SetLeftMargin(0.2);
  pad_cl->SetBottomMargin(0.2);
  pad_cl->Draw();
  pad_cl->cd();

  TH1D *h_closure_pp = (TH1D*) r1->Clone("h_closure_pp");
  h_closure_pp->Divide(r1,b_truth_gen_R,1,1,"B");
  //h_closure_pp->Divide(r1,b_truth_pp_R,1,1,"B");
  TH1D *h_closure_pp_inclGenMuTag = (TH1D*) h1_3->Clone("h_closure_pp_inclGenMuTag");
  h_closure_pp_inclGenMuTag->Divide(h1_3,b_truth_pp_inclGenMuTag_R,1,1,"B");
  TH1D *h_closure_pp_matchedRecoMuTag = (TH1D*) h1_2->Clone("h_closure_pp_matchedRecoMuTag");
  h_closure_pp_matchedRecoMuTag->Divide(h1_2,b_truth_pp_matchedRecoMuTag_R,1,1,"B");
  TH1D *h_closure_pp_inclRecoMuTag = (TH1D*) h1_1->Clone("h_closure_pp_inclRecoMuTag");
  h_closure_pp_inclRecoMuTag->Divide(h1_1,b_truth_pp_inclRecoMuTag_R,1,1,"B");
  TH1D *h_closure_pp_inclRecoMuTag_triggerOn = (TH1D*) h1_0->Clone("h_closure_pp_inclRecoMuTag_triggerOn");
  h_closure_pp_inclRecoMuTag_triggerOn->Divide(h1_0,b_truth_pp_inclRecoMuTag_triggerOn_R,1,1,"B");


  h_closure_pp->SetLineColor(kBlack);
  h_closure_pp_inclGenMuTag->SetLineColor(kRed-4);
  h_closure_pp_matchedRecoMuTag->SetLineColor(kBlue-4);
  h_closure_pp_inclRecoMuTag->SetLineColor(kGreen+2);
  h_closure_pp_inclRecoMuTag_triggerOn->SetLineColor(kMagenta);

  h_closure_pp_inclGenMuTag->SetLineWidth(3);
  h_closure_pp_matchedRecoMuTag->SetLineWidth(3);
  h_closure_pp_inclRecoMuTag->SetLineWidth(3);
  h_closure_pp_inclRecoMuTag_triggerOn->SetLineWidth(3);

  h_closure_pp_inclGenMuTag->SetLineStyle(2);
  h_closure_pp_matchedRecoMuTag->SetLineStyle(3);
  h_closure_pp_inclRecoMuTag->SetLineStyle(4);
  h_closure_pp_inclRecoMuTag_triggerOn->SetLineStyle(5);

  

  
  //h_closure_pp->SetTitle("Closure in pp");
  //h_closure_pp->SetTitle("Reco-level closure in pp");
  h_closure_pp->SetTitle("Gen-level closure in pp");
  h_closure_pp->GetXaxis()->SetTitle("#it{p}_{T}^{jet} [GeV]");
  h_closure_pp->GetYaxis()->SetTitle("#it{f}_{b}(Corrected MC) / #it{f}_{b}(truth)");
  h_closure_pp->GetYaxis()->SetRangeUser(0.65,1.35);
  //h_closure_pp->GetYaxis()->SetRangeUser(0.35,1.65);
  h_closure_pp->SetStats(0);
  h_closure_pp->SetMarkerSize(0);
  h_closure_pp->Draw();
  // h_closure_pp_inclRecoMuTag_triggerOn->Draw("same");
  // h_closure_pp_inclRecoMuTag->Draw("same");
  // h_closure_pp_matchedRecoMuTag->Draw("same");
  // h_closure_pp_inclGenMuTag->Draw("same");

  for(int i = 0; i < h_closure_pp->GetSize(); i++){
    cout << "|1 - h_closure_pp(" << i << ")| = " << TMath::Abs(1. - h_closure_pp->GetBinContent(i)) << endl;
  }

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(80,1,300,1);

  TLegend *leg_cl = new TLegend(0.25,0.7,0.88,0.88);
  leg_cl->SetBorderSize(0);
  leg_cl->SetTextSize(0.026);
  // leg_cl->AddEntry(h_closure_pp_inclRecoMuTag_triggerOn,"Closure after template fit");
  // leg_cl->AddEntry(h_closure_pp_inclRecoMuTag,"Closure after muon-trigger correction");
  // leg_cl->AddEntry(h_closure_pp_matchedRecoMuTag,"Closure after in-flight-muon correction");
  // leg_cl->AddEntry(h_closure_pp_inclGenMuTag,"Closure after muon-reco correction");
  // leg_cl->AddEntry(h_closure_pp,"Closure after jet-to-muon tag correction (full)");
  
  //leg_cl->Draw();


  // C2 closure
  TCanvas *canv_cl_C2 = new TCanvas("canv_cl_C2","canv_cl_C2",600,600);
  canv_cl_C2->cd();
  TPad *pad_cl_C2 = new TPad("pad_cl_C2","pad_cl_C2",0,0,1,1);
  pad_cl_C2->SetLeftMargin(0.2);
  pad_cl_C2->SetBottomMargin(0.2);
  pad_cl_C2->Draw();
  pad_cl_C2->cd();
  
  TH1D *h_closure_C2 = (TH1D*) r2->Clone("h_closure_C2");
  h_closure_C2->Divide(r2,b_truth_gen_R,1,1,"B");
  // TH2D *h_closure_C2_inclGenMuTag = (TH2D*) h2_3->Clone("h_closure_C2_inclGenMuTag");
  // h_closure_C2_inclGenMuTag->Divide(h2_3,b_truth_C2_inclGenMuTag_R,1,1,"B");
  // TH2D *h_closure_C2_matchedRecoMuTag = (TH2D*) h2_2->Clone("h_closure_C2_matchedRecoMuTag");
  // h_closure_C2_matchedRecoMuTag->Divide(h2_2,b_truth_C2_matchedRecoMuTag_R,1,1,"B");
  // TH2D *h_closure_C2_inclRecoMuTag = (TH2D*) h2_1->Clone("h_closure_C2_inclRecoMuTag");
  // h_closure_C2_inclRecoMuTag->Divide(h2_1,b_truth_C2_inclRecoMuTag_R,1,1,"B");
  // TH2D *h_closure_C2_inclRecoMuTag_triggerOn = (TH2D*) h2_0->Clone("h_closure_C2_inclRecoMuTag_triggerOn");
  // h_closure_C2_inclRecoMuTag_triggerOn->Divide(h2_0,b_truth_C2_inclRecoMuTag_triggerOn_R,1,1,"B");

  // h_closure_C2->SetLineColor(kBlack);
  // h_closure_C2_inclGenMuTag->SetLineColor(kRed-4);
  // h_closure_C2_matchedRecoMuTag->SetLineColor(kBlue-4);
  // h_closure_C2_inclRecoMuTag->SetLineColor(kGreen+2);
  // h_closure_C2_inclRecoMuTag_triggerOn->SetLineColor(kMagenta);

  // h_closure_C2_inclGenMuTag->SetLineWidth(3);
  // h_closure_C2_matchedRecoMuTag->SetLineWidth(3);
  // h_closure_C2_inclRecoMuTag->SetLineWidth(3);
  // h_closure_C2_inclRecoMuTag_triggerOn->SetLineWidth(3);

  // h_closure_C2_inclGenMuTag->SetLineStyle(2);
  // h_closure_C2_matchedRecoMuTag->SetLineStyle(3);
  // h_closure_C2_inclRecoMuTag->SetLineStyle(4);
  // h_closure_C2_inclRecoMuTag_triggerOn->SetLineStyle(5);

  for(int i = 0; i < h_closure_C2->GetSize(); i++){
    cout << "|1 - h_closure_C2(" << i << ")| = " << TMath::Abs(1. - h_closure_C2->GetBinContent(i)) << endl;
  }
  
  h_closure_C2->SetTitle("Closure in PbPb 30-90%");
  h_closure_C2->GetXaxis()->SetTitle("#it{p}_{T}^{jet} [GeV]");
  h_closure_C2->GetYaxis()->SetTitle("#it{f}_{#it{b}}(Corrected MC) / #it{f}_{#it{b}}(truth)");
  h_closure_C2->GetYaxis()->SetRangeUser(0.35,1.65);
  h_closure_C2->SetStats(0);
  h_closure_C2->SetMarkerSize(0);
  h_closure_C2->Draw();
  li->DrawLine(80,1,300,1);

   // C1 closure
  TCanvas *canv_cl_C1 = new TCanvas("canv_cl_C1","canv_cl_C1",600,600);
  canv_cl_C1->cd();
  TPad *pad_cl_C1 = new TPad("pad_cl_C1","pad_cl_C1",0,0,1,1);
  pad_cl_C1->SetLeftMargin(0.2);
  pad_cl_C1->SetBottomMargin(0.2);
  pad_cl_C1->Draw();
  pad_cl_C1->cd();
  
  TH1D *h_closure_C1 = (TH1D*) r3->Clone("h_closure_C1");
  h_closure_C1->Divide(r3,b_truth_gen_R,1,1,"B");
  //h_closure_C1->Divide(r3,b_truth_C1_R,1,1,"B");
  // TH3D *h_closure_C1_inclGenMuTag = (TH3D*) h3_3->Clone("h_closure_C1_inclGenMuTag");
  // h_closure_C1_inclGenMuTag->Divide(h3_3,b_truth_C1_inclGenMuTag_R,1,1,"B");
  // TH3D *h_closure_C1_matchedRecoMuTag = (TH3D*) h3_2->Clone("h_closure_C1_matchedRecoMuTag");
  // h_closure_C1_matchedRecoMuTag->Divide(h3_2,b_truth_C1_matchedRecoMuTag_R,1,1,"B");
  // TH3D *h_closure_C1_inclRecoMuTag = (TH3D*) h3_1->Clone("h_closure_C1_inclRecoMuTag");
  // h_closure_C1_inclRecoMuTag->Divide(h3_1,b_truth_C1_inclRecoMuTag_R,1,1,"B");
  // TH3D *h_closure_C1_inclRecoMuTag_triggerOn = (TH3D*) h3_0->Clone("h_closure_C1_inclRecoMuTag_triggerOn");
  // h_closure_C1_inclRecoMuTag_triggerOn->Divide(h3_0,b_truth_C1_inclRecoMuTag_triggerOn_R,1,1,"B");

  // h_closure_C1->SetLineColor(kBlack);
  // h_closure_C1_inclGenMuTag->SetLineColor(kRed-4);
  // h_closure_C1_matchedRecoMuTag->SetLineColor(kBlue-4);
  // h_closure_C1_inclRecoMuTag->SetLineColor(kGreen+2);
  // h_closure_C1_inclRecoMuTag_triggerOn->SetLineColor(kMagenta);

  // h_closure_C1_inclGenMuTag->SetLineWidth(3);
  // h_closure_C1_matchedRecoMuTag->SetLineWidth(3);
  // h_closure_C1_inclRecoMuTag->SetLineWidth(3);
  // h_closure_C1_inclRecoMuTag_triggerOn->SetLineWidth(3);

  // h_closure_C1_inclGenMuTag->SetLineStyle(2);
  // h_closure_C1_matchedRecoMuTag->SetLineStyle(3);
  // h_closure_C1_inclRecoMuTag->SetLineStyle(4);
  // h_closure_C1_inclRecoMuTag_triggerOn->SetLineStyle(5);

  for(int i = 0; i < h_closure_C1->GetSize(); i++){
    cout << "|1 - h_closure_C1(" << i << ")| = " << TMath::Abs(1. - h_closure_C1->GetBinContent(i)) << endl;
  }

  
  h_closure_C1->SetTitle("Closure in PbPb 0-30%");
  h_closure_C1->GetXaxis()->SetTitle("#it{p}_{T}^{jet} [GeV]");
  h_closure_C1->GetYaxis()->SetTitle("#it{f}_{b}(Corrected MC) / #it{f}_{b}(truth)");
  h_closure_C1->GetYaxis()->SetRangeUser(0.65,1.35);
  h_closure_C1->SetStats(0);
  h_closure_C1->SetMarkerSize(0);
  h_closure_C1->Draw();
  li->DrawLine(80,1,300,1);


  
  // PbPb/pp plot

  TH1D *R1, *R2, *R3;

  R1 = (TH1D*) h1->Clone("R1");
  R2 = (TH1D*) h2->Clone("R2");
  R3 = (TH1D*) h3->Clone("R3");

  R1->Divide(h1,h1,1,1,"");
  R2->Divide(h2,h1,1,1,"");
  R3->Divide(h3,h1,1,1,"");  

  TH1D *S1 = (TH1D*) R1->Clone("S1");
  TH1D *S2 = (TH1D*) R2->Clone("S2");
  TH1D *S3 = (TH1D*) R3->Clone("S3");

  S1->SetBinError(1,sys_input_pp_J1*S1->GetBinContent(1));
  S1->SetBinError(2,sys_input_pp_J2*S1->GetBinContent(2));
  S1->SetBinError(3,sys_input_pp_J3*S1->GetBinContent(3));
  S1->SetBinError(4,sys_input_pp_J3*S1->GetBinContent(4));
  S1->SetBinError(5,sys_input_pp_J3*S1->GetBinContent(5));
  S1->SetBinError(6,sys_input_pp_J3*S1->GetBinContent(6));
  
  
  S2->SetBinError(1,TMath::Sqrt(sys_input_C2_J1*S2->GetBinContent(1)*sys_input_C2_J1*S2->GetBinContent(1) + sys_input_pp_J1*S1->GetBinContent(1)*sys_input_pp_J1*S1->GetBinContent(1)));
  S2->SetBinError(2,TMath::Sqrt(sys_input_C2_J2*S2->GetBinContent(1)*sys_input_C2_J2*S2->GetBinContent(1) + sys_input_pp_J2*S1->GetBinContent(1)*sys_input_pp_J2*S1->GetBinContent(1)));
  S2->SetBinError(3,TMath::Sqrt(sys_input_C2_J3*S2->GetBinContent(1)*sys_input_C2_J3*S2->GetBinContent(1) + sys_input_pp_J3*S1->GetBinContent(1)*sys_input_pp_J3*S1->GetBinContent(1)));
  S2->SetBinError(4,TMath::Sqrt(sys_input_C2_J4*S2->GetBinContent(1)*sys_input_C2_J4*S2->GetBinContent(1) + sys_input_pp_J4*S1->GetBinContent(1)*sys_input_pp_J4*S1->GetBinContent(1)));
  S2->SetBinError(5,TMath::Sqrt(sys_input_C2_J5*S2->GetBinContent(1)*sys_input_C2_J5*S2->GetBinContent(1) + sys_input_pp_J5*S1->GetBinContent(1)*sys_input_pp_J5*S1->GetBinContent(1)));
  //S2->SetBinError(6,TMath::Sqrt(sys_input_C2_J6*S2->GetBinContent(1)*sys_input_C2_J6*S2->GetBinContent(1) + sys_input_pp_J6*S1->GetBinContent(1)*sys_input_pp_J6*S1->GetBinContent(1)));
  S2->SetBinError(6,0.0);
  // put the last point off the map
  // S2->SetBinContent(6,100);
  // R2->SetBinError(6,0.0);
  // R2->SetBinContent(6,100);

  S3->SetBinError(1,TMath::Sqrt(sys_input_C1_J1*S3->GetBinContent(1)*sys_input_C1_J1*S3->GetBinContent(1) + sys_input_pp_J1*S1->GetBinContent(1)*sys_input_pp_J1*S1->GetBinContent(1)));
  S3->SetBinError(2,TMath::Sqrt(sys_input_C1_J2*S3->GetBinContent(1)*sys_input_C1_J2*S3->GetBinContent(1) + sys_input_pp_J2*S1->GetBinContent(1)*sys_input_pp_J2*S1->GetBinContent(1)));
  S3->SetBinError(3,TMath::Sqrt(sys_input_C1_J3*S3->GetBinContent(1)*sys_input_C1_J3*S3->GetBinContent(1) + sys_input_pp_J3*S1->GetBinContent(1)*sys_input_pp_J3*S1->GetBinContent(1)));
  S3->SetBinError(4,TMath::Sqrt(sys_input_C1_J4*S3->GetBinContent(1)*sys_input_C1_J4*S3->GetBinContent(1) + sys_input_pp_J4*S1->GetBinContent(1)*sys_input_pp_J4*S1->GetBinContent(1)));
  S3->SetBinError(5,TMath::Sqrt(sys_input_C1_J5*S3->GetBinContent(1)*sys_input_C1_J5*S3->GetBinContent(1) + sys_input_pp_J5*S1->GetBinContent(1)*sys_input_pp_J5*S1->GetBinContent(1)));
  //S3->SetBinError(6,TMath::Sqrt(sys_input_C1_J6*S3->GetBinContent(1)*sys_input_C1_J6*S3->GetBinContent(1) + sys_input_pp_J6*S1->GetBinContent(1)*sys_input_pp_J6*S1->GetBinContent(1)));
  // S3->SetBinError(6,0.0);
  // // put the last point off the map
  // S3->SetBinContent(6,100);
  // R3->SetBinError(6,0.0);
  // R3->SetBinContent(6,100)
    ;

  S1->SetFillColorAlpha(kGray,0.25);
  S2->SetFillColorAlpha(kRed-4,0.5);
  S3->SetFillColorAlpha(kBlue-4,0.5);

  TCanvas *canv2 = new TCanvas("canv2","canv2",600,600);
  canv2->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,1);
  pad2->SetLeftMargin(0.2);
  pad2->SetBottomMargin(0.2);
  pad2->Draw();
  pad2->cd();
  R2->GetYaxis()->SetTitle("#it{f}_{#it{b}}^{incl}(PbPb) / #it{f}_{#it{b}}^{incl}(pp)");
  R2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  R2->GetXaxis()->SetRangeUser(80,300);
  R2->GetYaxis()->SetRangeUser(0,2);
  R2->SetTitle("");
  R2->SetStats(0);
  //S2->Draw("e2");
  R2->Draw();
  //S3->Draw("e2 same");
  //R2->Draw("same");
  R3->Draw("same");
  la->SetTextSize(0.03);
  la->DrawLatexNDC(0.21,0.92,"#font[62]{CMS }#scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextSize(0.025);
  if(do_mu5) la->DrawLatexNDC(0.42,0.92,"PbPb (323 #mub^{-1}), pp (99 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu7) la->DrawLatexNDC(0.42,0.92,"PbPb (787 #mub^{-1}), pp (274 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu12) la->DrawLatexNDC(0.42,0.92,"PbPb (1689 #mub^{-1}), pp (301 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else{};
  
  

  li->SetLineStyle(7);
  li->DrawLine(80,1,300,1);
  TLegend *leg3 = new TLegend(0.62,0.75,0.85,0.88);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.028);
  leg3->AddEntry(R2,"PbPb 30-90%","p");
  leg3->AddEntry(R3,"PbPb 0-30%","p");
  leg3->Draw();

  TString canv_bRatio_save_string = "";

  if(do_mu5){
    canv_bRatio_save_string = "../../../figures/results/bRatio_mu5.pdf";
  }
  else if(do_mu7){
    canv_bRatio_save_string = "../../../figures/results/bRatio_mu7.pdf";
  }
  else if(do_mu12){
    canv_bRatio_save_string = "../../../figures/results/bRatio_mu12.pdf";
  }
  else{};
  

  canv2->SaveAs(canv_bRatio_save_string);

  
  // TCanvas *canv3 = new TCanvas("canv3","canv3",700,700);
  // canv3->cd();
  // TPad *pad3 = new TPad("pad3","pad3",0,0,1,1);
  // pad3->SetLeftMargin(0.2);
  // pad3->SetBottomMargin(0.2);
  // pad3->Draw();
  // pad3->cd();

  // TH1D *rx2 = (TH1D*) h2->Clone("rx2");
  // TH1D *rx3 = (TH1D*) h3->Clone("rx3");

  // R1->Divide(h1,h1,1,1,"");
  

  
}
