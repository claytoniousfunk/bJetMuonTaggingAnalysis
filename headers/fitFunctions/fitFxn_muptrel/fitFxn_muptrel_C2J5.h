void loadFitFxn_muptrel_C2J5(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C2J5 = new TF1("fitFxn_muptrel_C2J5","[0] + [1]*x",0,10);

  fitFxn_muptrel_C2J5->SetParameter(0,muptrelFitParam_C2J5_0);
  fitFxn_muptrel_C2J5->SetParameter(1,muptrelFitParam_C2J5_1);

  fitFxn_muptrel_C2J5->SetParError(0,e_muptrelFitParam_C2J5_0);
  fitFxn_muptrel_C2J5->SetParError(1,e_muptrelFitParam_C2J5_1);

  cout << "~~ ... finished!" << endl;
 
}
