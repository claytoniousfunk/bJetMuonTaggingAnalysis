void loadFitFxn_PYTHIA_JERCorrection(){

  fitFxn_PYTHIA_JERCorrection = new TF1("fitFxn_PYTHIA_JERCorrection","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);

  fitFxn_PYTHIA_JERCorrection->SetParameter(0,JERCorrectionParam_0);
  fitFxn_PYTHIA_JERCorrection->SetParameter(1,JERCorrectionParam_1);
  fitFxn_PYTHIA_JERCorrection->SetParameter(2,JERCorrectionParam_2);
  fitFxn_PYTHIA_JERCorrection->SetParameter(3,JERCorrectionParam_3);
  fitFxn_PYTHIA_JERCorrection->SetParameter(4,JERCorrectionParam_4);
  fitFxn_PYTHIA_JERCorrection->SetParameter(5,JERCorrectionParam_5);


}
