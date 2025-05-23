void loadFitFxn_mupt(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_mupt = new TF1("fitFxn_mupt","[0]*TMath::Exp([1]*x) + [2]*TMath::Exp([3]*x) + [4]",0,10);

  fitFxn_mupt->SetParameter(0,muptFitParam_0);
  fitFxn_mupt->SetParameter(1,muptFitParam_1);
  fitFxn_mupt->SetParameter(2,muptFitParam_2);
  fitFxn_mupt->SetParameter(3,muptFitParam_3);
  fitFxn_mupt->SetParameter(4,muptFitParam_4);
 
  fitFxn_mupt->SetParError(0,e_muptFitParam_0);
  fitFxn_mupt->SetParError(1,e_muptFitParam_1);
  fitFxn_mupt->SetParError(2,e_muptFitParam_2);
  fitFxn_mupt->SetParError(3,e_muptFitParam_3);
  fitFxn_mupt->SetParError(4,e_muptFitParam_4);
 
  cout << "~~ ... finished!" << endl;
 
}
