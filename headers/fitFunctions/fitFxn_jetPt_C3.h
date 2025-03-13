void loadFitFxn_jetPt_C3(){
  fitFxn_jetPt_C3 = new TF1("fitFxn_jetPt_C3","[0]+[1]*x",0,500);
  fitFxn_jetPt_C3->SetParameter(0,jetPtFitParam_C3_0);
  fitFxn_jetPt_C3->SetParameter(1,jetPtFitParam_C3_1);
}
