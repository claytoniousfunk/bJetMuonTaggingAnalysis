void loadFitFxn_vz(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_vz = new TF1("fitFxn_vz","[0] + [1]*x",-15,15);

  fitFxn_vz->SetParameter(0,vzFitParam_0);
  fitFxn_vz->SetParameter(1,vzFitParam_1);
  

  fitFxn_vz->SetParError(0,e_vzFitParam_0);
  fitFxn_vz->SetParError(1,e_vzFitParam_1);
  

  cout << "~~ ... finished!" << endl;
 
}
