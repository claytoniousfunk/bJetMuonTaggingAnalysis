
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

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(0,-3.79489);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(1,-237.275);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(2,0.116184);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(3,6.35004);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(4,0.000176468);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(5,216.407);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C4->SetParameter(6,0.106815);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(0,2.12517);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(1,1.58888);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(2,0.0247889);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(3,1.58871);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(4,0.0248018);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(5,1.58867);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C3->SetParameter(6,0.0248328);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(0,2.03426);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(1,1.41446);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(2,0.0161761);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(3,1.40181);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(4,0.016162);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(5,1.411);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C2->SetParameter(6,0.0161729);

  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(0,2.09711);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(1,1.37895);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(2,0.0150651);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(3,1.37701);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(4,0.0145071);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(5,1.38058);
  fitFxn_PYTHIAHYDJET_pThatCorrelation_C1->SetParameter(6,0.0148503);



}
