void loadFitFxn_jetPt_C2(){
  fitFxn_jetPt_C2 = new TF1("fitFxn_jetPt_C2","[0] + [1]*exp(-[2]*x)",80,500);
  fitFxn_jetPt_C2->SetParameter(0,jetPtFitParam_C2_0);
  fitFxn_jetPt_C2->SetParameter(1,jetPtFitParam_C2_1);
  fitFxn_jetPt_C2->SetParameter(2,jetPtFitParam_C2_2);
}
