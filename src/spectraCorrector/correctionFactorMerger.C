



void correctionFactorMerger(){

  TFile *file_CF_pp;
  TFile *file_CF_C1_15, *file_CF_C1_30, *file_CF_C1_40, *file_CF_C1_50;
  TFile *file_CF_C2_15, *file_CF_C2_30, *file_CF_C2_40, *file_CF_C2_50;

  file_CF_pp = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_pp.root");
  file_CF_C1_15 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1_pthat15.root");
  file_CF_C1_30 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1_pthat30.root");
  file_CF_C1_40 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1_pthat40.root");
  file_CF_C1_50 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1_pthat50.root");
  file_CF_C2_15 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2_pthat15.root");
  file_CF_C2_30 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2_pthat30.root");
  file_CF_C2_40 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2_pthat40.root");
  file_CF_C2_50 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2_pthat50.root");

  TH1D *h_CF_1_C1_15, *h_CF_1_C1_30, *h_CF_1_C1_40, *h_CF_1_C1_50;
  TH1D *h_CF_2_C1_15, *h_CF_2_C1_30, *h_CF_2_C1_40, *h_CF_2_C1_50;
  TH1D *h_CF_3_C1_15, *h_CF_3_C1_30, *h_CF_3_C1_40, *h_CF_3_C1_50;
  
  TH1D *h_CF_1_C2_15, *h_CF_1_C2_30, *h_CF_1_C2_40, *h_CF_1_C2_50;
  TH1D *h_CF_2_C2_15, *h_CF_2_C2_30, *h_CF_2_C2_40, *h_CF_2_C2_50;
  TH1D *h_CF_3_C2_15, *h_CF_3_C2_30, *h_CF_3_C2_40, *h_CF_3_C2_50;

  file_CF_C1_15->GetObject("corrFactor_1_C1",h_CF_1_C1_15);
  file_CF_C1_15->GetObject("corrFactor_2_C1",h_CF_2_C1_15);
  file_CF_C1_15->GetObject("corrFactor_3_C1",h_CF_3_C1_15);

  file_CF_C1_30->GetObject("corrFactor_1_C1",h_CF_1_C1_30);
  file_CF_C1_30->GetObject("corrFactor_2_C1",h_CF_2_C1_30);
  file_CF_C1_30->GetObject("corrFactor_3_C1",h_CF_3_C1_30);

  file_CF_C1_40->GetObject("corrFactor_1_C1",h_CF_1_C1_40);
  file_CF_C1_40->GetObject("corrFactor_2_C1",h_CF_2_C1_40);
  file_CF_C1_40->GetObject("corrFactor_3_C1",h_CF_3_C1_40);
  
  file_CF_C1_50->GetObject("corrFactor_1_C1",h_CF_1_C1_50);
  file_CF_C1_50->GetObject("corrFactor_2_C1",h_CF_2_C1_50);
  file_CF_C1_50->GetObject("corrFactor_3_C1",h_CF_3_C1_50);

  file_CF_C2_15->GetObject("corrFactor_1_C2",h_CF_1_C2_15);
  file_CF_C2_15->GetObject("corrFactor_2_C2",h_CF_2_C2_15);
  file_CF_C2_15->GetObject("corrFactor_3_C2",h_CF_3_C2_15);

  file_CF_C2_30->GetObject("corrFactor_1_C2",h_CF_1_C2_30);
  file_CF_C2_30->GetObject("corrFactor_2_C2",h_CF_2_C2_30);
  file_CF_C2_30->GetObject("corrFactor_3_C2",h_CF_3_C2_30);

  file_CF_C2_40->GetObject("corrFactor_1_C2",h_CF_1_C2_40);
  file_CF_C2_40->GetObject("corrFactor_2_C2",h_CF_2_C2_40);
  file_CF_C2_40->GetObject("corrFactor_3_C2",h_CF_3_C2_40);
  
  file_CF_C2_50->GetObject("corrFactor_1_C2",h_CF_1_C2_50);
  file_CF_C2_50->GetObject("corrFactor_2_C2",h_CF_2_C2_50);
  file_CF_C2_50->GetObject("corrFactor_3_C2",h_CF_3_C2_50);



  TH1D *h_CF_1_C1_merge, *h_CF_2_C1_merge, *h_CF_3_C1_merge;
  TH1D *h_CF_1_C2_merge, *h_CF_2_C2_merge, *h_CF_3_C2_merge;

  h_CF_1_C1_merge = (TH1D*) h_CF_1_C1_15->Clone("h_CF_1_C1_merge");
  h_CF_2_C1_merge = (TH1D*) h_CF_2_C1_15->Clone("h_CF_2_C1_merge");
  h_CF_3_C1_merge = (TH1D*) h_CF_3_C1_15->Clone("h_CF_3_C1_merge");

  h_CF_1_C2_merge = (TH1D*) h_CF_1_C2_15->Clone("h_CF_1_C2_merge");
  h_CF_2_C2_merge = (TH1D*) h_CF_2_C2_15->Clone("h_CF_2_C2_merge");
  h_CF_3_C2_merge = (TH1D*) h_CF_3_C2_15->Clone("h_CF_3_C2_merge");

  h_CF_1_C1_merge->SetBinContent(1,h_CF_1_C1_30->GetBinContent(1));
  h_CF_1_C1_merge->SetBinContent(2,h_CF_1_C1_40->GetBinContent(2));
  h_CF_1_C1_merge->SetBinContent(3,h_CF_1_C1_50->GetBinContent(3));

  h_CF_2_C1_merge->SetBinContent(1,h_CF_2_C1_30->GetBinContent(1));
  h_CF_2_C1_merge->SetBinContent(2,h_CF_2_C1_40->GetBinContent(2));
  h_CF_2_C1_merge->SetBinContent(3,h_CF_2_C1_50->GetBinContent(3));

  h_CF_3_C1_merge->SetBinContent(1,h_CF_3_C1_30->GetBinContent(1));
  h_CF_3_C1_merge->SetBinContent(2,h_CF_3_C1_40->GetBinContent(2));
  h_CF_3_C1_merge->SetBinContent(3,h_CF_3_C1_50->GetBinContent(3));

  h_CF_1_C2_merge->SetBinContent(1,h_CF_1_C2_30->GetBinContent(1));
  h_CF_1_C2_merge->SetBinContent(2,h_CF_1_C2_40->GetBinContent(2));
  h_CF_1_C2_merge->SetBinContent(3,h_CF_1_C2_50->GetBinContent(3));

  h_CF_2_C2_merge->SetBinContent(1,h_CF_2_C2_30->GetBinContent(1));
  h_CF_2_C2_merge->SetBinContent(2,h_CF_2_C2_40->GetBinContent(2));
  h_CF_2_C2_merge->SetBinContent(3,h_CF_2_C2_50->GetBinContent(3));

  h_CF_3_C2_merge->SetBinContent(1,h_CF_3_C2_30->GetBinContent(1));
  h_CF_3_C2_merge->SetBinContent(2,h_CF_3_C2_40->GetBinContent(2));
  h_CF_3_C2_merge->SetBinContent(3,h_CF_3_C2_50->GetBinContent(3));

  TFile *wf_C1 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C1_merge.root","recreate");
  h_CF_1_C1_merge->Write("corrFactor_1_C1");
  h_CF_2_C1_merge->Write("corrFactor_2_C1");
  h_CF_3_C1_merge->Write("corrFactor_3_C1");
  wf_C1->Close();

  TFile *wf_C2 = TFile::Open("../../rootFiles/correctionFactors/correctionFactors_C2_merge.root","recreate");
  h_CF_1_C2_merge->Write("corrFactor_1_C2");
  h_CF_2_C2_merge->Write("corrFactor_2_C2");
  h_CF_3_C2_merge->Write("corrFactor_3_C2");
  wf_C2->Close();

  

  

}
