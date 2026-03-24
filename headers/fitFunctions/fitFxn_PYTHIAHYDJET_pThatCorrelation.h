
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C4;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C3;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C2;
TF1 *fitFxn_PYTHIAHYDJET_pThatCorrelation_C1;

void loadFitFxn_PYTHIAHYDJET_pThatCorrelation(){

  cout << "~~ loading pThatCorrelation fit function ..." << endl;

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C4","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x) + [5]*exp(-[6]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C3","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x) + [5]*exp(-[6]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C2","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x) + [5]*exp(-[6]*x)");
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1 = new TF1("fitFxn_PYTHIAHYDJET_pThatCorrelation_C1","[0] + [1]*exp(-[2]*x) + [3]*exp(-[4]*x) + [5]*exp(-[6]*x)");

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(0,39.2182);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(1,-37.6509);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(2,0.00108952);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(3,-2.87353);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(4,-0.00348841);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(5,8.03615);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(6,0.0178147);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(0,2.34625);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(1,1.51253);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(2,0.0226368);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(3,1.51246);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(4,0.0224515);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(5,1.51241);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(6,0.0226223);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(0,2.18765);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(1,1.34995);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(2,0.0112045);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(3,1.20358);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(4,0.0111311);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(5,1.21566);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(6,0.0111009);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(0,1.50201);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(1,1.44542);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(2,0.011139);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(3,1.47793);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(4,0.0111326);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(5,1.33993);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(6,0.00210997);



}
