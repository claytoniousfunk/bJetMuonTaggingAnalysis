
void loadFitFxn_pp_HLT(){

  cout << "~~ loading fit function ..." << endl;

  fitFxn_pp_HLT = new TF1("fitFxn_pp_HLT","[0] - ([0] - [1])*exp(-[2]*x)",15,100);

  fitFxn_pp_HLT->SetParameter(0,HLTFitParam_0);
  fitFxn_pp_HLT->SetParameter(1,HLTFitParam_1);
  fitFxn_pp_HLT->SetParameter(2,HLTFitParam_2);
  
  fitFxn_pp_HLT->SetParError(0,e_HLTFitParam_0);
  fitFxn_pp_HLT->SetParError(1,e_HLTFitParam_1);
  fitFxn_pp_HLT->SetParError(2,e_HLTFitParam_2);

}


