void loadFitFxn_jetPt_C2(){
  fitFxn_jetPt_C2 = new TF1("fitFxn_jetPt_C2","1 + [0]*exp(-[1]*x)",0,500);
  fitFxn_jetPt_C2->SetParameter(0,jetPtFitParam_C2_0);
  fitFxn_jetPt_C2->SetParameter(1,jetPtFitParam_C2_1);
}
