void loadFitFxn_muptrel_C0J2(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_muptrel_C0J2 = new TF1("fitFxn_muptrel_C0J2","[0] + [1]*x",0,10);

  fitFxn_muptrel_C0J2->SetParameter(0,muptrelFitParam_C0J2_0);
  fitFxn_muptrel_C0J2->SetParameter(1,muptrelFitParam_C0J2_1);

  fitFxn_muptrel_C0J2->SetParError(0,e_muptrelFitParam_C0J2_0);
  fitFxn_muptrel_C0J2->SetParError(1,e_muptrelFitParam_C0J2_1);

  cout << "~~ ... finished!" << endl;
 
}
