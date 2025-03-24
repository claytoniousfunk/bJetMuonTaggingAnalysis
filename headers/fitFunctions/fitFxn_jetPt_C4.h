void loadFitFxn_jetPt_C4(){
  fitFxn_jetPt_C4 = new TF1("fitFxn_jetPt_C4","[0] + [1]*exp(-[2]*x)",80,500);
  fitFxn_jetPt_C4->SetParameter(0,jetPtFitParam_C3_0);
  fitFxn_jetPt_C4->SetParameter(1,jetPtFitParam_C3_1);
  fitFxn_jetPt_C4->SetParameter(2,jetPtFitParam_C3_2);
}
