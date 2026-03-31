
TF1 *fitFxn_PYTHIA_pThatCorrelation;

void loadFitFxn_PYTHIA_pThatCorrelation(){

  cout << "~~ loading pThatCorrelation fit function ..." << endl;

  fitFxn_PYTHIA_pThatCorrelation = new TF1("fitFxn_PYTHIA_pThatCorrelation","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x) + [5]*exp(-[6]*x)");


  fitFxn_PYTHIA_pThatCorrelation->SetParameter(0,15.7105);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(1,-3.78501);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(2,-7.93281e-05);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(3,-9.43729);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(4,-8.15843e-05);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(5,3.12788);
  fitFxn_PYTHIA_pThatCorrelation->SetParameter(6,0.0536565);


}
