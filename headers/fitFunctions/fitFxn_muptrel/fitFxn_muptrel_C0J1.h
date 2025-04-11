void loadFitFxn_muptrel_C0J1(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C0J1 = new TF1("fitFxn_muptrel_C0J1","[0] + [1]*x",0,10);

  fitFxn_muptrel_C0J1->SetParameter(0,muptrelFitParam_C0J1_0);
  fitFxn_muptrel_C0J1->SetParameter(1,muptrelFitParam_C0J1_1);

  fitFxn_muptrel_C0J1->SetParError(0,e_muptrelFitParam_C0J1_0);
  fitFxn_muptrel_C0J1->SetParError(1,e_muptrelFitParam_C0J1_1);

  cout << "~~ ... finished!" << endl;
 
}
