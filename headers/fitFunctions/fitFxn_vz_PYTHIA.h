void loadFitFxn_vz(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_vz = new TF1("fitFxn_vz","[0] + [1]*x + [2]*x*x + [3]*x*x*x",-15,15);

  fitFxn_vz->SetParameter(0,vzFitParam_0);
  fitFxn_vz->SetParameter(1,vzFitParam_1);
  fitFxn_vz->SetParameter(2,vzFitParam_2);
  fitFxn_vz->SetParameter(3,vzFitParam_3);

  fitFxn_vz->SetParError(0,e_vzFitParam_0);
  fitFxn_vz->SetParError(1,e_vzFitParam_1);
  fitFxn_vz->SetParError(2,e_vzFitParam_2);
  fitFxn_vz->SetParError(3,e_vzFitParam_3);

  cout << "~~ ... finished!" << endl;
 
}
