
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C4;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C3;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C2;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C1;

void loadFitFxn_PYTHIAHYDJET_pThatCorrelation(){

  cout << "~~ loading pThatCorrelation fit function ..." << endl;

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C4","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C3","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C2","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C1","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x)");

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(0,0.545654);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(1,1.31207);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(2,0.0570922);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(3,1.40783);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(4,0.000761268);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(0,1.58572);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(1,5.44996);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(2,0.091947);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(3,0.615958);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(4,0.00734935);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(0,1.59274);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(1,0.755352);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(2,0.00805109);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(3,6.91006);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(4,0.0749407);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(0,1.57299);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(1,6.45753);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(2,0.0565195);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(3,0.782851);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(4,0.00658546);



}
