void loadFitFxn_muptrel_C1J6(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C1J6 = new TF1("fitFxn_muptrel_C1J6","[0] + [1]*x",0,10);

  fitFxn_muptrel_C1J6->SetParameter(0,muptrelFitParam_C1J6_0);
  fitFxn_muptrel_C1J6->SetParameter(1,muptrelFitParam_C1J6_1);

  fitFxn_muptrel_C1J6->SetParError(0,e_muptrelFitParam_C1J6_0);
  fitFxn_muptrel_C1J6->SetParError(1,e_muptrelFitParam_C1J6_1);

  cout << "~~ ... finished!" << endl;
 
}
