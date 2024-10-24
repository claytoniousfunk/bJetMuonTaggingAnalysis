void loadFitFxn_muptrel_C1J3(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C1J3 = new TF1("fitFxn_muptrel_C1J3","[0] + [1]*x",0,10);

  fitFxn_muptrel_C1J3->SetParameter(0,muptrelFitParam_C1J3_0);
  fitFxn_muptrel_C1J3->SetParameter(1,muptrelFitParam_C1J3_1);

  fitFxn_muptrel_C1J3->SetParError(0,e_muptrelFitParam_C1J3_0);
  fitFxn_muptrel_C1J3->SetParError(1,e_muptrelFitParam_C1J3_1);

  cout << "~~ ... finished!" << endl;
 
}
