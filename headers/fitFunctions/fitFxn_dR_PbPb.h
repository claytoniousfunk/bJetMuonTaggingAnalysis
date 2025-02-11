void loadFitFxn_dR(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_dR = new TF1("fitFxn_dR","[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x",0,0.4);

  fitFxn_dR->SetParameter(0,dRFitParam_0);
  fitFxn_dR->SetParameter(1,dRFitParam_1);
  fitFxn_dR->SetParameter(2,dRFitParam_2);
  fitFxn_dR->SetParameter(3,dRFitParam_3);
  fitFxn_dR->SetParameter(4,dRFitParam_4);

  fitFxn_dR->SetParError(0,e_dRFitParam_0);
  fitFxn_dR->SetParError(1,e_dRFitParam_1);
  fitFxn_dR->SetParError(2,e_dRFitParam_2);
  fitFxn_dR->SetParError(3,e_dRFitParam_3);
  fitFxn_dR->SetParError(4,e_dRFitParam_4);

  cout << "~~ ... finished!" << endl;
 
}
