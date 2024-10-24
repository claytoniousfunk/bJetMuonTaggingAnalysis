void loadFitFxn_muptrel_C2J4(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C2J4 = new TF1("fitFxn_muptrel_C2J4","[0] + [1]*x",0,10);

  fitFxn_muptrel_C2J4->SetParameter(0,muptrelFitParam_C2J4_0);
  fitFxn_muptrel_C2J4->SetParameter(1,muptrelFitParam_C2J4_1);

  fitFxn_muptrel_C2J4->SetParError(0,e_muptrelFitParam_C2J4_0);
  fitFxn_muptrel_C2J4->SetParError(1,e_muptrelFitParam_C2J4_1);

  cout << "~~ ... finished!" << endl;
 
}
