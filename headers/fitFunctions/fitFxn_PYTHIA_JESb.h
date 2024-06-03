void loadFitFxn_PYTHIA_JESb(){
  fitFxn_PYTHIA_JESb = new TF1("fitFxn_PYTHIA_JESb","([0] + [1]*x + [2]*x*x) / ([3] + [4]*x + [5]*x*x)",0,500);
  fitFxn_PYTHIA_JESb->SetParameter(0,JESbFitParam_0);
  fitFxn_PYTHIA_JESb->SetParameter(1,JESbFitParam_1);
  fitFxn_PYTHIA_JESb->SetParameter(2,JESbFitParam_2);
  fitFxn_PYTHIA_JESb->SetParameter(3,JESbFitParam_3);
  fitFxn_PYTHIA_JESb->SetParameter(4,JESbFitParam_4);
  fitFxn_PYTHIA_JESb->SetParameter(5,JESbFitParam_5);
}
