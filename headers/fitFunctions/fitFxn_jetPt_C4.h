void loadFitFxn_jetPt_C4(){
  fitFxn_jetPt = new TF1("fitFxn_jetPt","[0]+[1]*x",0,500);
  fitFxn_jetPt->SetParameter(0,jetPtFitParam_C4_0);
  fitFxn_jetPt->SetParameter(1,jetPtFitParam_C4_1);
}
