
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

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(0,2.04789);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(1,-32.92);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(2,0.200712);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(3,0.847653);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(4,0.00766832);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(5,15.8325);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(6,0.100201);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(0,2.1268);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(1,1.62948);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(2,0.0260511);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(3,1.63425);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(4,0.0260048);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(5,1.60643);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(6,0.0260837);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(0,2.05742);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(1,1.41284);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(2,0.0171152);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(3,1.41062);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(4,0.0169273);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(5,1.3924);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(6,0.017028);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(0,2.10577);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(1,1.37656);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(2,0.0153566);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(3,1.3767);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(4,0.0153869);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(5,1.34397);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(6,0.014386);



}
