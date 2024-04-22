void loadFitFxn_jetPt(){
  fitFxn_jetPt = new TF1("fitFxn_jetPt","[0]+[1]*TMath::Exp([2]*x)",0,500);
  fitFxn_jetPt->SetParameter(0,jetPtFitParam_0);
  fitFxn_jetPt->SetParameter(1,jetPtFitParam_1);
  fitFxn_jetPt->SetParameter(2,jetPtFitParam_2);
}
