#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/systematicsResults.h"
#include "../../../headers/goldenFileNames.h"


void fraction_plot(bool do_mu5 = 1,
		   bool do_mu7 = 0,
		   bool do_mu12 = 0){

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
    input_PYTHIA          = goldenFile_PYTHIA_mu5;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu5;

  }
  else if(do_mu7){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu7;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu7;
    input_pp_MinBias      = goldenFile_pp_MinBias_mu7;
    input_PbPb_MinBias    = goldenFile_PbPb_MinBias_mu7;
    input_PYTHIA          = goldenFile_PYTHIA_mu7;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu7;

  }
  else if(do_mu12){

    input_pp_SingleMuon   = goldenFile_pp_SingleMuon_mu12;
    input_PbPb_SingleMuon = goldenFile_PbPb_SingleMuon_mu12;
    input_pp_MinBias      = goldenFile_pp_MinBias_mu12;
    input_PbPb_MinBias    = goldenFile_PbPb_MinBias_mu12;
    input_PYTHIA          = goldenFile_PYTHIA_mu12;
    input_PYTHIAHYDJET    = goldenFile_PYTHIAHYDJET_DiJet_mu12;

  }
  else{};


  
  TFile *x1, *x2, *x3;
  x1 = TFile::Open(input_PYTHIA);
  x2 = TFile::Open(input_PYTHIAHYDJET);

  TH2D *Y1, *Y2, *Y3;
  TH1D *y1, *y2, *y3;
  TH1D *b1, *b2, *b3;
  TH1D *b1_add, *b2_add, *b3_add;

  x1->GetObject("h_inclRecoJetPt_flavor",Y1);
  x2->GetObject("h_inclRecoJetPt_flavor_C2",Y2);
  x2->GetObject("h_inclRecoJetPt_flavor_C1",Y3);

  y1 = (TH1D*) Y1->ProjectionX();
  y2 = (TH1D*) Y2->ProjectionX();
  y3 = (TH1D*) Y3->ProjectionX();

  TH1D *binFinder = Y1->ProjectionY();
  double smallShift = 0.01;
  
  b1 = (TH1D*) Y1->ProjectionX("b1",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b1_add = (TH1D*) Y1->ProjectionX("b1_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b1->Add(b1_add);

  b2 = (TH1D*) Y2->ProjectionX("b2",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b2_add = (TH1D*) Y2->ProjectionX("b2_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b2->Add(b2_add);

  b3 = (TH1D*) Y3->ProjectionX("b3",binFinder->FindBin(-5+smallShift),binFinder->FindBin(-4-smallShift));
  b3_add = (TH1D*) Y3->ProjectionX("b3_add",binFinder->FindBin(5+smallShift),binFinder->FindBin(6-smallShift));
  b3->Add(b3_add);



  TH1D *b_truth_pp = (TH1D*) b1->Clone("b_truth_pp");
  b_truth_pp->Divide(b1,y1,1,1,"B");
  
  TH1D *b_truth_C2 = (TH1D*) b2->Clone("b_truth_C2");
  b_truth_C2->Divide(b2,y2,1,1,"B");

  TH1D *b_truth_C1 = (TH1D*) b3->Clone("b_truth_C1");
  b_truth_C1->Divide(b3,y3,1,1,"B");

  b_truth_pp->SetLineColor(kBlack);
  b_truth_pp->SetLineStyle(7);
  b_truth_pp->SetMarkerSize(0);
  b_truth_pp->SetLineWidth(2);

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

  if(do_mu5) b_purity_file_string = "../../../rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-1_mu7-0_mu12-0_mergeB-0_mergeC-1_pTrel-0.0-5.0_cMult-1.0-JERsmear-0.root";
  else if(do_mu7) b_purity_file_string = "../../../rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-0_mu7-1_mu12-0_mergeB-0_mergeC-1_pTrel-0.0-5.0_cMult-1.0-JERsmear-0.root";
  else if(do_mu12) b_purity_file_string = "../../../rootFiles/bPurityResults/bPurityResults_DATA-1_mu5-0_mu7-0_mu12-1_mergeB-0_mergeC-1_pTrel-0.0-5.0_cMult-1.0-JERsmear-0.root";
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

  if(do_mu5){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu5.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu5.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu5.root";
  }
  else if(do_mu7){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu7.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu7.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu7.root";
  }
  else if(do_mu12){
    b_amplifier_pp_file_string = "../tagging_sequence/b_amplifiers/ba_pp_mu12.root";
    b_amplifier_C2_file_string = "../tagging_sequence/b_amplifiers/ba_C2_mu12.root";
    b_amplifier_C1_file_string = "../tagging_sequence/b_amplifiers/ba_C1_mu12.root";
  }
  else{};

  // b-enhancement files
  TFile *fb1, *fb2, *fb3;
  fb1 = TFile::Open(b_amplifier_pp_file_string);
  fb2 = TFile::Open(b_amplifier_C2_file_string);
  fb3 = TFile::Open(b_amplifier_C1_file_string);

  TH1D *ba1, *ba2, *ba3;

  fb1->GetObject("r_corr",ba1);
  fb2->GetObject("r_corr",ba2);
  fb3->GetObject("r_corr",ba3);

  const int M = 6;
  double new_axis[M] = {60,80,120,200,300,500};
  
  TH1D *ba1_R = (TH1D*) ba1->Rebin(M-1,"ba1_R",new_axis);
  TH1D *ba2_R = (TH1D*) ba2->Rebin(M-1,"ba2_R",new_axis);
  TH1D *ba3_R = (TH1D*) ba1->Rebin(M-1,"ba3_R",new_axis);

  divideByBinwidth(ba1_R);
  ba1_R->Scale(5.0); // account for 5-GeV-wide bins

  divideByBinwidth(ba2_R);
  ba2_R->Scale(5.0); // account for 5-GeV-wide bins

  divideByBinwidth(ba3_R);
  ba3_R->Scale(5.0); // account for 5-GeV-wide bins

  h1->Divide(h1,ba1_R,1,1,"");
  h2->Divide(h2,ba2_R,1,1,"");
  h3->Divide(h3,ba3_R,1,1,"");
  
  double marker_size = 1.5;
  int line_width = 3;
  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);
  h1->SetMarkerStyle(53);
  h1->SetMarkerSize(marker_size);

  h2->SetLineColor(kRed-4);
  h2->SetMarkerColor(kRed-4);
  h2->SetMarkerStyle(54);
  h2->SetMarkerSize(marker_size);

  h3->SetLineColor(kBlue-4);
  h3->SetMarkerColor(kBlue-4);
  h3->SetMarkerStyle(55);
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

  double sys_input_pp_J2 = 0.0;
  double sys_input_pp_J3 = 0.0;
  double sys_input_pp_J4 = 0.0;

  double sys_input_C2_J2 = 0.0;
  double sys_input_C2_J3 = 0.0;
  double sys_input_C2_J4 = 0.0;

  double sys_input_C1_J2 = 0.0;
  double sys_input_C1_J3 = 0.0;
  double sys_input_C1_J4 = 0.0;


  if(do_mu5){

    // pp
    sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu5_J2*sys_cFraction_pp_mu5_J2 +
				  sys_lowerBound_pp_mu5_J2*sys_lowerBound_pp_mu5_J2 +
				  sys_bEnhance_pp_mu5_J2*sys_bEnhance_pp_mu5_J2 +
				  sys_cEnhance_pp_mu5_J2*sys_cEnhance_pp_mu5_J2 +
				  sys_JERsmear_pp_mu5_J2*sys_JERsmear_pp_mu5_J2 +
				  sys_centShift_pp_mu5_J2*sys_centShift_pp_mu5_J2);
    
    sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu5_J3*sys_cFraction_pp_mu5_J3 +
				  sys_lowerBound_pp_mu5_J3*sys_lowerBound_pp_mu5_J3 +
				  sys_bEnhance_pp_mu5_J3*sys_bEnhance_pp_mu5_J3 +
				  sys_cEnhance_pp_mu5_J3*sys_cEnhance_pp_mu5_J3 +
				  sys_JERsmear_pp_mu5_J3*sys_JERsmear_pp_mu5_J3 +
				  sys_centShift_pp_mu5_J3*sys_centShift_pp_mu5_J3);

    sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu5_J4*sys_cFraction_pp_mu5_J4 +
				  sys_lowerBound_pp_mu5_J4*sys_lowerBound_pp_mu5_J4 +
				  sys_bEnhance_pp_mu5_J4*sys_bEnhance_pp_mu5_J4 +
				  sys_cEnhance_pp_mu5_J4*sys_cEnhance_pp_mu5_J4 +
				  sys_JERsmear_pp_mu5_J4*sys_JERsmear_pp_mu5_J4 +
				  sys_centShift_pp_mu5_J4*sys_centShift_pp_mu5_J4);

    // C2
    sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J2*sys_cFraction_PbPb_mu5_C2_J2 +
				  sys_lowerBound_PbPb_mu5_C2_J2*sys_lowerBound_PbPb_mu5_C2_J2 +
				  sys_bEnhance_PbPb_mu5_C2_J2*sys_bEnhance_PbPb_mu5_C2_J2 +
				  sys_cEnhance_PbPb_mu5_C2_J2*sys_cEnhance_PbPb_mu5_C2_J2 +
				  sys_JERsmear_PbPb_mu5_C2_J2*sys_JERsmear_PbPb_mu5_C2_J2 +
				  sys_centShift_PbPb_mu5_C2_J2*sys_centShift_PbPb_mu5_C2_J2);
    
    sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J3*sys_cFraction_PbPb_mu5_C2_J3 +
				  sys_lowerBound_PbPb_mu5_C2_J3*sys_lowerBound_PbPb_mu5_C2_J3 +
				  sys_bEnhance_PbPb_mu5_C2_J3*sys_bEnhance_PbPb_mu5_C2_J3 +
				  sys_cEnhance_PbPb_mu5_C2_J3*sys_cEnhance_PbPb_mu5_C2_J3 +
				  sys_JERsmear_PbPb_mu5_C2_J3*sys_JERsmear_PbPb_mu5_C2_J3 +
				  sys_centShift_PbPb_mu5_C2_J3*sys_centShift_PbPb_mu5_C2_J3);

    sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C2_J4*sys_cFraction_PbPb_mu5_C2_J4 +
				  sys_lowerBound_PbPb_mu5_C2_J4*sys_lowerBound_PbPb_mu5_C2_J4 +
				  sys_bEnhance_PbPb_mu5_C2_J4*sys_bEnhance_PbPb_mu5_C2_J4 +
				  sys_cEnhance_PbPb_mu5_C2_J4*sys_cEnhance_PbPb_mu5_C2_J4 +
				  sys_JERsmear_PbPb_mu5_C2_J4*sys_JERsmear_PbPb_mu5_C2_J4 +
				  sys_centShift_PbPb_mu5_C2_J4*sys_centShift_PbPb_mu5_C2_J4);

    // C1
    sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J2*sys_cFraction_PbPb_mu5_C1_J2 +
				  sys_lowerBound_PbPb_mu5_C1_J2*sys_lowerBound_PbPb_mu5_C1_J2 +
				  sys_bEnhance_PbPb_mu5_C1_J2*sys_bEnhance_PbPb_mu5_C1_J2 +
				  sys_cEnhance_PbPb_mu5_C1_J2*sys_cEnhance_PbPb_mu5_C1_J2 +
				  sys_JERsmear_PbPb_mu5_C1_J2*sys_JERsmear_PbPb_mu5_C1_J2 +
				  sys_centShift_PbPb_mu5_C1_J2*sys_centShift_PbPb_mu5_C1_J2);
    
    sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J3*sys_cFraction_PbPb_mu5_C1_J3 +
				  sys_lowerBound_PbPb_mu5_C1_J3*sys_lowerBound_PbPb_mu5_C1_J3 +
				  sys_bEnhance_PbPb_mu5_C1_J3*sys_bEnhance_PbPb_mu5_C1_J3 +
				  sys_cEnhance_PbPb_mu5_C1_J3*sys_cEnhance_PbPb_mu5_C1_J3 +
				  sys_JERsmear_PbPb_mu5_C1_J3*sys_JERsmear_PbPb_mu5_C1_J3 +
				  sys_centShift_PbPb_mu5_C1_J3*sys_centShift_PbPb_mu5_C1_J3);

    sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu5_C1_J4*sys_cFraction_PbPb_mu5_C1_J4 +
				  sys_lowerBound_PbPb_mu5_C1_J4*sys_lowerBound_PbPb_mu5_C1_J4 +
				  sys_bEnhance_PbPb_mu5_C1_J4*sys_bEnhance_PbPb_mu5_C1_J4 +
				  sys_cEnhance_PbPb_mu5_C1_J4*sys_cEnhance_PbPb_mu5_C1_J4 +
				  sys_JERsmear_PbPb_mu5_C1_J4*sys_JERsmear_PbPb_mu5_C1_J4 +
				  sys_centShift_PbPb_mu5_C1_J4*sys_centShift_PbPb_mu5_C1_J4);
  }


  else if(do_mu7){

    // pp
    sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu7_J2*sys_cFraction_pp_mu7_J2 +
				  sys_lowerBound_pp_mu7_J2*sys_lowerBound_pp_mu7_J2 +
				  sys_bEnhance_pp_mu7_J2*sys_bEnhance_pp_mu7_J2 +
				  sys_cEnhance_pp_mu7_J2*sys_cEnhance_pp_mu7_J2 +
				  sys_JERsmear_pp_mu7_J2*sys_JERsmear_pp_mu7_J2 +
				  sys_centShift_pp_mu7_J2*sys_centShift_pp_mu7_J2);
    
    sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu7_J3*sys_cFraction_pp_mu7_J3 +
				  sys_lowerBound_pp_mu7_J3*sys_lowerBound_pp_mu7_J3 +
				  sys_bEnhance_pp_mu7_J3*sys_bEnhance_pp_mu7_J3 +
				  sys_cEnhance_pp_mu7_J3*sys_cEnhance_pp_mu7_J3 +
				  sys_JERsmear_pp_mu7_J3*sys_JERsmear_pp_mu7_J3 +
				  sys_centShift_pp_mu7_J3*sys_centShift_pp_mu7_J3);

    sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu7_J4*sys_cFraction_pp_mu7_J4 +
				  sys_lowerBound_pp_mu7_J4*sys_lowerBound_pp_mu7_J4 +
				  sys_bEnhance_pp_mu7_J4*sys_bEnhance_pp_mu7_J4 +
				  sys_cEnhance_pp_mu7_J4*sys_cEnhance_pp_mu7_J4 +
				  sys_JERsmear_pp_mu7_J4*sys_JERsmear_pp_mu7_J4 +
				  sys_centShift_pp_mu7_J4*sys_centShift_pp_mu7_J4);

    // C2
    sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J2*sys_cFraction_PbPb_mu7_C2_J2 +
				  sys_lowerBound_PbPb_mu7_C2_J2*sys_lowerBound_PbPb_mu7_C2_J2 +
				  sys_bEnhance_PbPb_mu7_C2_J2*sys_bEnhance_PbPb_mu7_C2_J2 +
				  sys_cEnhance_PbPb_mu7_C2_J2*sys_cEnhance_PbPb_mu7_C2_J2 +
				  sys_JERsmear_PbPb_mu7_C2_J2*sys_JERsmear_PbPb_mu7_C2_J2 +
				  sys_centShift_PbPb_mu7_C2_J2*sys_centShift_PbPb_mu7_C2_J2);
    
    sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J3*sys_cFraction_PbPb_mu7_C2_J3 +
				  sys_lowerBound_PbPb_mu7_C2_J3*sys_lowerBound_PbPb_mu7_C2_J3 +
				  sys_bEnhance_PbPb_mu7_C2_J3*sys_bEnhance_PbPb_mu7_C2_J3 +
				  sys_cEnhance_PbPb_mu7_C2_J3*sys_cEnhance_PbPb_mu7_C2_J3 +
				  sys_JERsmear_PbPb_mu7_C2_J3*sys_JERsmear_PbPb_mu7_C2_J3 +
				  sys_centShift_PbPb_mu7_C2_J3*sys_centShift_PbPb_mu7_C2_J3);

    sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C2_J4*sys_cFraction_PbPb_mu7_C2_J4 +
				  sys_lowerBound_PbPb_mu7_C2_J4*sys_lowerBound_PbPb_mu7_C2_J4 +
				  sys_bEnhance_PbPb_mu7_C2_J4*sys_bEnhance_PbPb_mu7_C2_J4 +
				  sys_cEnhance_PbPb_mu7_C2_J4*sys_cEnhance_PbPb_mu7_C2_J4 +
				  sys_JERsmear_PbPb_mu7_C2_J4*sys_JERsmear_PbPb_mu7_C2_J4 +
				  sys_centShift_PbPb_mu7_C2_J4*sys_centShift_PbPb_mu7_C2_J4);

    // C1
    sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J2*sys_cFraction_PbPb_mu7_C1_J2 +
				  sys_lowerBound_PbPb_mu7_C1_J2*sys_lowerBound_PbPb_mu7_C1_J2 +
				  sys_bEnhance_PbPb_mu7_C1_J2*sys_bEnhance_PbPb_mu7_C1_J2 +
				  sys_cEnhance_PbPb_mu7_C1_J2*sys_cEnhance_PbPb_mu7_C1_J2 +
				  sys_JERsmear_PbPb_mu7_C1_J2*sys_JERsmear_PbPb_mu7_C1_J2 +
				  sys_centShift_PbPb_mu7_C1_J2*sys_centShift_PbPb_mu7_C1_J2);
    
    sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J3*sys_cFraction_PbPb_mu7_C1_J3 +
				  sys_lowerBound_PbPb_mu7_C1_J3*sys_lowerBound_PbPb_mu7_C1_J3 +
				  sys_bEnhance_PbPb_mu7_C1_J3*sys_bEnhance_PbPb_mu7_C1_J3 +
				  sys_cEnhance_PbPb_mu7_C1_J3*sys_cEnhance_PbPb_mu7_C1_J3 +
				  sys_JERsmear_PbPb_mu7_C1_J3*sys_JERsmear_PbPb_mu7_C1_J3 +
				  sys_centShift_PbPb_mu7_C1_J3*sys_centShift_PbPb_mu7_C1_J3);

    sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu7_C1_J4*sys_cFraction_PbPb_mu7_C1_J4 +
				  sys_lowerBound_PbPb_mu7_C1_J4*sys_lowerBound_PbPb_mu7_C1_J4 +
				  sys_bEnhance_PbPb_mu7_C1_J4*sys_bEnhance_PbPb_mu7_C1_J4 +
				  sys_cEnhance_PbPb_mu7_C1_J4*sys_cEnhance_PbPb_mu7_C1_J4 +
				  sys_JERsmear_PbPb_mu7_C1_J4*sys_JERsmear_PbPb_mu7_C1_J4 +
				  sys_centShift_PbPb_mu7_C1_J4*sys_centShift_PbPb_mu7_C1_J4);
  }

  else if(do_mu12){

    // pp
    sys_input_pp_J2 = TMath::Sqrt(sys_cFraction_pp_mu12_J2*sys_cFraction_pp_mu12_J2 +
				  sys_lowerBound_pp_mu12_J2*sys_lowerBound_pp_mu12_J2 +
				  sys_bEnhance_pp_mu12_J2*sys_bEnhance_pp_mu12_J2 +
				  sys_cEnhance_pp_mu12_J2*sys_cEnhance_pp_mu12_J2 +
				  sys_JERsmear_pp_mu12_J2*sys_JERsmear_pp_mu12_J2 +
				  sys_centShift_pp_mu12_J2*sys_centShift_pp_mu12_J2);
    
    sys_input_pp_J3 = TMath::Sqrt(sys_cFraction_pp_mu12_J3*sys_cFraction_pp_mu12_J3 +
				  sys_lowerBound_pp_mu12_J3*sys_lowerBound_pp_mu12_J3 +
				  sys_bEnhance_pp_mu12_J3*sys_bEnhance_pp_mu12_J3 +
				  sys_cEnhance_pp_mu12_J3*sys_cEnhance_pp_mu12_J3 +
				  sys_JERsmear_pp_mu12_J3*sys_JERsmear_pp_mu12_J3 +
				  sys_centShift_pp_mu12_J3*sys_centShift_pp_mu12_J3);

    sys_input_pp_J4 = TMath::Sqrt(sys_cFraction_pp_mu12_J4*sys_cFraction_pp_mu12_J4 +
				  sys_lowerBound_pp_mu12_J4*sys_lowerBound_pp_mu12_J4 +
				  sys_bEnhance_pp_mu12_J4*sys_bEnhance_pp_mu12_J4 +
				  sys_cEnhance_pp_mu12_J4*sys_cEnhance_pp_mu12_J4 +
				  sys_JERsmear_pp_mu12_J4*sys_JERsmear_pp_mu12_J4 +
				  sys_centShift_pp_mu12_J4*sys_centShift_pp_mu12_J4);

    // C2
    sys_input_C2_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J2*sys_cFraction_PbPb_mu12_C2_J2 +
				  sys_lowerBound_PbPb_mu12_C2_J2*sys_lowerBound_PbPb_mu12_C2_J2 +
				  sys_bEnhance_PbPb_mu12_C2_J2*sys_bEnhance_PbPb_mu12_C2_J2 +
				  sys_cEnhance_PbPb_mu12_C2_J2*sys_cEnhance_PbPb_mu12_C2_J2 +
				  sys_JERsmear_PbPb_mu12_C2_J2*sys_JERsmear_PbPb_mu12_C2_J2 +
				  sys_centShift_PbPb_mu12_C2_J2*sys_centShift_PbPb_mu12_C2_J2);
    
    sys_input_C2_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J3*sys_cFraction_PbPb_mu12_C2_J3 +
				  sys_lowerBound_PbPb_mu12_C2_J3*sys_lowerBound_PbPb_mu12_C2_J3 +
				  sys_bEnhance_PbPb_mu12_C2_J3*sys_bEnhance_PbPb_mu12_C2_J3 +
				  sys_cEnhance_PbPb_mu12_C2_J3*sys_cEnhance_PbPb_mu12_C2_J3 +
				  sys_JERsmear_PbPb_mu12_C2_J3*sys_JERsmear_PbPb_mu12_C2_J3 +
				  sys_centShift_PbPb_mu12_C2_J3*sys_centShift_PbPb_mu12_C2_J3);

    sys_input_C2_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C2_J4*sys_cFraction_PbPb_mu12_C2_J4 +
				  sys_lowerBound_PbPb_mu12_C2_J4*sys_lowerBound_PbPb_mu12_C2_J4 +
				  sys_bEnhance_PbPb_mu12_C2_J4*sys_bEnhance_PbPb_mu12_C2_J4 +
				  sys_cEnhance_PbPb_mu12_C2_J4*sys_cEnhance_PbPb_mu12_C2_J4 +
				  sys_JERsmear_PbPb_mu12_C2_J4*sys_JERsmear_PbPb_mu12_C2_J4 +
				  sys_centShift_PbPb_mu12_C2_J4*sys_centShift_PbPb_mu12_C2_J4);

    // C1
    sys_input_C1_J2 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J2*sys_cFraction_PbPb_mu12_C1_J2 +
				  sys_lowerBound_PbPb_mu12_C1_J2*sys_lowerBound_PbPb_mu12_C1_J2 +
				  sys_bEnhance_PbPb_mu12_C1_J2*sys_bEnhance_PbPb_mu12_C1_J2 +
				  sys_cEnhance_PbPb_mu12_C1_J2*sys_cEnhance_PbPb_mu12_C1_J2 +
				  sys_JERsmear_PbPb_mu12_C1_J2*sys_JERsmear_PbPb_mu12_C1_J2 +
				  sys_centShift_PbPb_mu12_C1_J2*sys_centShift_PbPb_mu12_C1_J2);
    
    sys_input_C1_J3 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J3*sys_cFraction_PbPb_mu12_C1_J3 +
				  sys_lowerBound_PbPb_mu12_C1_J3*sys_lowerBound_PbPb_mu12_C1_J3 +
				  sys_bEnhance_PbPb_mu12_C1_J3*sys_bEnhance_PbPb_mu12_C1_J3 +
				  sys_cEnhance_PbPb_mu12_C1_J3*sys_cEnhance_PbPb_mu12_C1_J3 +
				  sys_JERsmear_PbPb_mu12_C1_J3*sys_JERsmear_PbPb_mu12_C1_J3 +
				  sys_centShift_PbPb_mu12_C1_J3*sys_centShift_PbPb_mu12_C1_J3);

    sys_input_C1_J4 = TMath::Sqrt(sys_cFraction_PbPb_mu12_C1_J4*sys_cFraction_PbPb_mu12_C1_J4 +
				  sys_lowerBound_PbPb_mu12_C1_J4*sys_lowerBound_PbPb_mu12_C1_J4 +
				  sys_bEnhance_PbPb_mu12_C1_J4*sys_bEnhance_PbPb_mu12_C1_J4 +
				  sys_cEnhance_PbPb_mu12_C1_J4*sys_cEnhance_PbPb_mu12_C1_J4 +
				  sys_JERsmear_PbPb_mu12_C1_J4*sys_JERsmear_PbPb_mu12_C1_J4 +
				  sys_centShift_PbPb_mu12_C1_J4*sys_centShift_PbPb_mu12_C1_J4);
  }
  
  else{};

  
  s1->SetBinError(1,sys_input_pp_J2*s1->GetBinContent(1));
  s1->SetBinError(2,sys_input_pp_J3*s1->GetBinContent(2));
  s1->SetBinError(3,sys_input_pp_J4*s1->GetBinContent(3));
  
  s2->SetBinError(1,sys_input_C2_J2*s2->GetBinContent(1));
  s2->SetBinError(2,sys_input_C2_J3*s2->GetBinContent(2));
  s2->SetBinError(3,sys_input_C2_J4*s2->GetBinContent(3));

  s3->SetBinError(1,sys_input_C1_J2*s3->GetBinContent(1));
  s3->SetBinError(2,sys_input_C1_J3*s3->GetBinContent(2));
  s3->SetBinError(3,sys_input_C1_J4*s3->GetBinContent(3));

  s1->SetFillColorAlpha(kBlack,1.0);
  s1->SetFillStyle(3345);
  s2->SetFillColorAlpha(kRed-4,0.5);
  s3->SetFillColorAlpha(kBlue-4,0.5);




  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.2);
  pad->SetBottomMargin(0.2);
  pad->Draw();
  pad->cd();
  //r2->GetYaxis()->SetTitle("#it{f}_{#it{b}}(PbPb) / #it{f}_{#it{b}}(pp)");
  s1->GetYaxis()->SetTitle("inclusive #font[52]{b}-jet fraction");
  s1->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  s1->GetXaxis()->SetRangeUser(60,200);
  //r2->GetYaxis()->SetRangeUser(0,2);
  s1->GetYaxis()->SetRangeUser(0,0.15);
  s1->SetTitle("");
  s1->SetStats(0);
  s1->Draw("e2");
  s2->Draw("e2 same");
  s3->Draw("e2 same");
  r2->Draw("same");
  r1->Draw("same");
  r3->Draw("same");





  


  TLegend *leg = new TLegend(0.62,0.75,0.85,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.028);
  leg->AddEntry(h1,"pp","p");
  leg->AddEntry(h2,"PbPb 30-90%","p");
  leg->AddEntry(h3,"PbPb 0-30%","p");
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
  

  b_truth_pp->Draw("hist same");
  //b_truth_pp->Rebin(5); b_truth_pp->Scale(1./5.);
  //b_truth_C2->Draw("hist same");
  //b_truth_C1->Draw("hist same");

  TLegend *leg2 = new TLegend(0.22,0.75,0.5,0.88);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.028);
  leg2->AddEntry(b_truth_pp,"PYTHIA","l");
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

  S1->SetBinError(1,sys_input_pp_J2*S1->GetBinContent(1));
  S1->SetBinError(2,sys_input_pp_J3*S1->GetBinContent(2));
  S1->SetBinError(3,sys_input_pp_J4*S1->GetBinContent(3));
  
  
  S2->SetBinError(1,TMath::Sqrt(sys_input_C2_J2*S2->GetBinContent(1)*sys_input_C2_J2*S2->GetBinContent(1) + sys_input_pp_J2*S1->GetBinContent(1)*sys_input_pp_J2*S1->GetBinContent(1)));
  S2->SetBinError(2,TMath::Sqrt(sys_input_C2_J3*S2->GetBinContent(1)*sys_input_C2_J3*S2->GetBinContent(1) + sys_input_pp_J3*S1->GetBinContent(1)*sys_input_pp_J3*S1->GetBinContent(1)));
  S2->SetBinError(3,TMath::Sqrt(sys_input_C2_J4*S2->GetBinContent(1)*sys_input_C2_J4*S2->GetBinContent(1) + sys_input_pp_J4*S1->GetBinContent(1)*sys_input_pp_J4*S1->GetBinContent(1)));

  S3->SetBinError(1,TMath::Sqrt(sys_input_C1_J2*S3->GetBinContent(1)*sys_input_C1_J2*S3->GetBinContent(1) + sys_input_pp_J2*S1->GetBinContent(1)*sys_input_pp_J2*S1->GetBinContent(1)));
  S3->SetBinError(2,TMath::Sqrt(sys_input_C1_J3*S3->GetBinContent(1)*sys_input_C1_J3*S3->GetBinContent(1) + sys_input_pp_J3*S1->GetBinContent(1)*sys_input_pp_J3*S1->GetBinContent(1)));
  S3->SetBinError(3,TMath::Sqrt(sys_input_C1_J4*S3->GetBinContent(1)*sys_input_C1_J4*S3->GetBinContent(1) + sys_input_pp_J4*S1->GetBinContent(1)*sys_input_pp_J4*S1->GetBinContent(1)));

  S1->SetFillColorAlpha(kGray,0.5);
  S2->SetFillColorAlpha(kRed-4,0.5);
  S3->SetFillColorAlpha(kBlue-4,0.5);

  TCanvas *canv2 = new TCanvas("canv2","canv2",700,700);
  canv2->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,1);
  pad2->SetLeftMargin(0.2);
  pad2->SetBottomMargin(0.2);
  pad2->Draw();
  pad2->cd();
  S2->GetYaxis()->SetTitle("#it{f}_{#it{b}}(PbPb) / #it{f}_{#it{b}}(pp)");
  S2->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  S2->GetXaxis()->SetRangeUser(60,200);
  S2->GetYaxis()->SetRangeUser(0,3);
  S2->SetTitle("");
  S2->SetStats(0);
  S2->Draw("e2");
  S3->Draw("e2 same");
  R2->Draw("same");
  R3->Draw("same");
  la->SetTextSize(0.03);
  la->DrawLatexNDC(0.21,0.92,"#font[62]{CMS }#scale[0.8]{#font[52]{Preliminary}}");
  la->SetTextSize(0.025);
  if(do_mu5) la->DrawLatexNDC(0.42,0.92,"PbPb (323 #mub^{-1}), pp (99 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu7) la->DrawLatexNDC(0.42,0.92,"PbPb (787 #mub^{-1}), pp (274 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else if(do_mu12) la->DrawLatexNDC(0.42,0.92,"PbPb (1689 #mub^{-1}), pp (301 pb^{-1}), #sqrt{s_{NN}} = 5.02 TeV");
  else{};
  
  
  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(60,1,200,1);
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
  
 
  
}
