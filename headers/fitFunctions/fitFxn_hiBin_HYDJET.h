
void loadFitFxn_hiBin(){

  cout << "~~~~ loading hiBin fit function (mu5)..." << endl;
  
  fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]+ [1]*x + [2]*x*x + [3]*x*x*x",0,160);

  fitFxn_hiBin->SetParameter(0,hiBinFitParam_0);
  fitFxn_hiBin->SetParameter(1,hiBinFitParam_1);
  fitFxn_hiBin->SetParameter(2,hiBinFitParam_2);
  fitFxn_hiBin->SetParameter(3,hiBinFitParam_3);

  fitFxn_hiBin->SetParError(0,e_hiBinFitParam_0);
  fitFxn_hiBin->SetParError(1,e_hiBinFitParam_1);
  fitFxn_hiBin->SetParError(2,e_hiBinFitParam_2);
  fitFxn_hiBin->SetParError(3,e_hiBinFitParam_3);

  cout << "~~~~ ... done!" << endl;
  
}
