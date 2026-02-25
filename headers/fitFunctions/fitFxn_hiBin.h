
void loadFitFxn_hiBin_mu5(){

  cout << "~~~~ loading hiBin fit function (mu5)..." << endl;
  
  fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]+ [1]*x + [2]*x*x + [3]*x*x*x",0,160);

  fitFxn_hiBin->SetParameter(0,hiBinFitParam_mu5_0);
  fitFxn_hiBin->SetParameter(1,hiBinFitParam_mu5_1);
  fitFxn_hiBin->SetParameter(2,hiBinFitParam_mu5_2);
  fitFxn_hiBin->SetParameter(3,hiBinFitParam_mu5_3);

  fitFxn_hiBin->SetParError(0,e_hiBinFitParam_mu5_0);
  fitFxn_hiBin->SetParError(1,e_hiBinFitParam_mu5_1);
  fitFxn_hiBin->SetParError(2,e_hiBinFitParam_mu5_2);
  fitFxn_hiBin->SetParError(3,e_hiBinFitParam_mu5_3);

  cout << "~~~~ ... done!" << endl;
  
}

void loadFitFxn_hiBin_mu7(){

  cout << "~~~~ loading hiBin fit function (mu7)..." << endl;
  
  fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]+ [1]*x + [2]*x*x + [3]*x*x*x",0,160);

  fitFxn_hiBin->SetParameter(0,hiBinFitParam_mu7_0);
  fitFxn_hiBin->SetParameter(1,hiBinFitParam_mu7_1);
  fitFxn_hiBin->SetParameter(2,hiBinFitParam_mu7_2);
  fitFxn_hiBin->SetParameter(3,hiBinFitParam_mu7_3);

  fitFxn_hiBin->SetParError(0,e_hiBinFitParam_mu7_0);
  fitFxn_hiBin->SetParError(1,e_hiBinFitParam_mu7_1);
  fitFxn_hiBin->SetParError(2,e_hiBinFitParam_mu7_2);
  fitFxn_hiBin->SetParError(3,e_hiBinFitParam_mu7_3);

  cout << "~~~~ ... done!" << endl;
  
}

void loadFitFxn_hiBin_mu12(){

  cout << "~~~~ loading hiBin fit function (mu12)..." << endl;
  
  fitFxn_hiBin = new TF1("fitFxn_hiBin","[0]+ [1]*x + [2]*x*x + [3]*x*x*x",0,160);

  fitFxn_hiBin->SetParameter(0,hiBinFitParam_mu12_0);
  fitFxn_hiBin->SetParameter(1,hiBinFitParam_mu12_1);
  fitFxn_hiBin->SetParameter(2,hiBinFitParam_mu12_2);
  fitFxn_hiBin->SetParameter(3,hiBinFitParam_mu12_3);

  fitFxn_hiBin->SetParError(0,e_hiBinFitParam_mu12_0);
  fitFxn_hiBin->SetParError(1,e_hiBinFitParam_mu12_1);
  fitFxn_hiBin->SetParError(2,e_hiBinFitParam_mu12_2);
  fitFxn_hiBin->SetParError(3,e_hiBinFitParam_mu12_3);

  cout << "~~~~ ... done!" << endl;
  
}
