
int N_vzFitParam = 4;

void loadFitFxn_vz_mu5(){

  fitFxn_vz = new TF1("fitFxn_vz","[0]+[1]*x+[2]*x*x+[3]*x*x*x",-15,15);
  fitFxn_vz->SetParameter(0,vzFitParam_mu5_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu5_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu5_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu5_3);

}

void loadFitFxn_vz_mu7(){

  fitFxn_vz = new TF1("fitFxn_vz","[0]+[1]*x+[2]*x*x+[3]*x*x*x",-15,15);
  fitFxn_vz->SetParameter(0,vzFitParam_mu7_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu7_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu7_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu7_3);

}

void loadFitFxn_vz_mu12(){

  fitFxn_vz = new TF1("fitFxn_vz","[0]+[1]*x+[2]*x*x+[3]*x*x*x",-15,15);
  fitFxn_vz->SetParameter(0,vzFitParam_mu12_0);
  fitFxn_vz->SetParameter(1,vzFitParam_mu12_1);
  fitFxn_vz->SetParameter(2,vzFitParam_mu12_2);
  fitFxn_vz->SetParameter(3,vzFitParam_mu12_3);

}
