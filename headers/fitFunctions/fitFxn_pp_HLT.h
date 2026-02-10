
void loadFitFxn_pp_HLT(){

  cout << "~~ loading fit function ..." << endl;

  fitFxn_pp_HLT = new TF1("fitFxn_pp_HLT","[0]",15,100);
  fitFxn_pp_HLT->SetParameter(0,HLTFitParam_0);
  fitFxn_pp_HLT->SetParError(0,e_HLTFitParam_0);

}


