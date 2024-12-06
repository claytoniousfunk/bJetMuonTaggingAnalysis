void loadFitFxn_dR(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_dR = new TF1("fitFxn_dR","[0] + [1]*x",0,0.4);

  fitFxn_dR->SetParameter(0,dRFitParam_0);
  fitFxn_dR->SetParameter(1,dRFitParam_1);

  fitFxn_dR->SetParError(0,e_dRFitParam_0);
  fitFxn_dR->SetParError(1,e_dRFitParam_1);

  cout << "~~ ... finished!" << endl;
 
}
