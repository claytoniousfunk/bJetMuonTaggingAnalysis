void loadFitFxn_hiBin(){

  cout << "~~~~ loading hiBin fit function..." << endl;
  
  fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]*TMath::Exp([1]*x) + [2] + [3]*x + [4]*x*x + [5]*x*x*x",0,190);
  fitFxn_hiBin->SetParameter(0,hiBinFitParam_0);
  fitFxn_hiBin->SetParameter(1,hiBinFitParam_1);
  fitFxn_hiBin->SetParameter(2,hiBinFitParam_2);
  fitFxn_hiBin->SetParameter(3,hiBinFitParam_3);
  fitFxn_hiBin->SetParameter(4,hiBinFitParam_4);
  fitFxn_hiBin->SetParameter(5,hiBinFitParam_5);
  fitFxn_hiBin->SetParameter(6,hiBinFitParam_6);
  fitFxn_hiBin->SetParameter(7,hiBinFitParam_7);
  fitFxn_hiBin->SetParameter(8,hiBinFitParam_8);

  cout << "~~~~ ... done!" << endl;
  
}
