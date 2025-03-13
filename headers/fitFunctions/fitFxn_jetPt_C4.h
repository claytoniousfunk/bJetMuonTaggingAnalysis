void loadFitFxn_jetPt_C4(){
  fitFxn_jetPt_C4 = new TF1("fitFxn_jetPt_C4","1 + [0]*exp(-[1]*x)",0,500);
  fitFxn_jetPt_C4->SetParameter(0,jetPtFitParam_C4_0);
  fitFxn_jetPt_C4->SetParameter(1,jetPtFitParam_C4_1);
}
