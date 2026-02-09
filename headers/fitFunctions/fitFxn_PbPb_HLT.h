
void loadFitFxn_PbPb_HLT(){

  cout << "~~ loading fit function ..." << endl;

  fitFxn_PbPb_HLT_C4 = new TF1("fitFxn_PbPb_HLT_C4","[0] - ([0] - [1])*TMath::Exp(-par[2]*x)",15,100);
  fitFxn_PbPb_HLT_C3 = new TF1("fitFxn_PbPb_HLT_C3","[0] - ([0] - [1])*TMath::Exp(-par[2]*x)",15,100);
  fitFxn_PbPb_HLT_C2 = new TF1("fitFxn_PbPb_HLT_C2","[0] - ([0] - [1])*TMath::Exp(-par[2]*x)",15,100);
  fitFxn_PbPb_HLT_C1 = new TF1("fitFxn_PbPb_HLT_C1","[0] - ([0] - [1])*TMath::Exp(-par[2]*x)",15,100);

  fitFxn_PbPb_HLT_C4->SetParameter(0,HLTFitParam_C4_0);
  fitFxn_PbPb_HLT_C4->SetParameter(1,HLTFitParam_C4_1);
  fitFxn_PbPb_HLT_C4->SetParameter(2,HLTFitParam_C4_2);
  fitFxn_PbPb_HLT_C4->SetParError(0,e_HLTFitParam_C4_0);
  fitFxn_PbPb_HLT_C4->SetParError(1,e_HLTFitParam_C4_1);
  fitFxn_PbPb_HLT_C4->SetParError(2,e_HLTFitParam_C4_2);

  fitFxn_PbPb_HLT_C3->SetParameter(0,HLTFitParam_C3_0);
  fitFxn_PbPb_HLT_C3->SetParameter(1,HLTFitParam_C3_1);
  fitFxn_PbPb_HLT_C3->SetParameter(2,HLTFitParam_C3_2);
  fitFxn_PbPb_HLT_C3->SetParError(0,e_HLTFitParam_C3_0);
  fitFxn_PbPb_HLT_C3->SetParError(1,e_HLTFitParam_C3_1);
  fitFxn_PbPb_HLT_C3->SetParError(2,e_HLTFitParam_C3_2);

  fitFxn_PbPb_HLT_C2->SetParameter(0,HLTFitParam_C2_0);
  fitFxn_PbPb_HLT_C2->SetParameter(1,HLTFitParam_C2_1);
  fitFxn_PbPb_HLT_C2->SetParameter(2,HLTFitParam_C2_2);
  fitFxn_PbPb_HLT_C2->SetParError(0,e_HLTFitParam_C2_0);
  fitFxn_PbPb_HLT_C2->SetParError(1,e_HLTFitParam_C2_1);
  fitFxn_PbPb_HLT_C2->SetParError(2,e_HLTFitParam_C2_2);

  fitFxn_PbPb_HLT_C1->SetParameter(0,HLTFitParam_C1_0);
  fitFxn_PbPb_HLT_C1->SetParameter(1,HLTFitParam_C1_1);
  fitFxn_PbPb_HLT_C1->SetParameter(2,HLTFitParam_C1_2);
  fitFxn_PbPb_HLT_C1->SetParError(0,e_HLTFitParam_C1_0);
  fitFxn_PbPb_HLT_C1->SetParError(1,e_HLTFitParam_C1_1);
  fitFxn_PbPb_HLT_C1->SetParError(2,e_HLTFitParam_C1_2);

}


