void loadFitFxn_muptrel_C2J1(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C2J1 = new TF1("fitFxn_muptrel_C2J1","[0] + [1]*x",0,10);

  fitFxn_vz->SetParameter(0,muptrelFitParam_C2J1_0);
  fitFxn_vz->SetParameter(1,muptrelFitParam_C2J1_1);

  fitFxn_vz->SetParError(0,e_muptrelFitParam_C2J1_0);
  fitFxn_vz->SetParError(1,e_muptrelFitParam_C2J1_1);

  cout << "~~ ... finished!" << endl;
 
}
