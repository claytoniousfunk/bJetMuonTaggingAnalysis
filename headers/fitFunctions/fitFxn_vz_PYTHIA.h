int N_vzFitParam = 4;

void loadFitFxn_vz_mu5(){

  cout << "~~ loading fit function (mu5) ..." << endl;
  
  fitFxn_vz = new TF1("fitFxn_vz","[0] + [1]*x + [2]*x*x + [3]*x*x*x",-15,15);

  fitFxn_vz->SetParameter(0,vzFitParam_mu5_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu5_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu5_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu5_3);

  fitFxn_vz->SetParError(0,e_vzFitParam_mu5_0);
  fitFxn_vz->SetParError(1,e_vzFitParam_mu5_1);
  fitFxn_vz->SetParError(2,e_vzFitParam_mu5_2);
  fitFxn_vz->SetParError(3,e_vzFitParam_mu5_3);

  cout << "~~ ... finished!" << endl;
 
}

void loadFitFxn_vz_mu7(){

  cout << "~~ loading fit function (mu7) ..." << endl;
  
  fitFxn_vz = new TF1("fitFxn_vz","[0] + [1]*x + [2]*x*x + [3]*x*x*x",-15,15);

  fitFxn_vz->SetParameter(0,vzFitParam_mu7_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu7_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu7_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu7_3);

  fitFxn_vz->SetParError(0,e_vzFitParam_mu7_0);
  fitFxn_vz->SetParError(1,e_vzFitParam_mu7_1);
  fitFxn_vz->SetParError(2,e_vzFitParam_mu7_2);
  fitFxn_vz->SetParError(3,e_vzFitParam_mu7_3);

  cout << "~~ ... finished!" << endl;
 
}

void loadFitFxn_vz_mu12(){

  cout << "~~ loading fit function (mu12) ..." << endl;
  
  fitFxn_vz = new TF1("fitFxn_vz","[0] + [1]*x + [2]*x*x + [3]*x*x*x",-15,15);

  fitFxn_vz->SetParameter(0,vzFitParam_mu12_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu12_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu12_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu12_3);

  fitFxn_vz->SetParError(0,e_vzFitParam_mu12_0);
  fitFxn_vz->SetParError(1,e_vzFitParam_mu12_1);
  fitFxn_vz->SetParError(2,e_vzFitParam_mu12_2);
  fitFxn_vz->SetParError(3,e_vzFitParam_mu12_3);

  cout << "~~ ... finished!" << endl;
 
}
