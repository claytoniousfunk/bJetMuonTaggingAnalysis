void loadFitFxn_jetPt_C1(){
  fitFxn_jetPt_C1 = new TF1("fitFxn_jetPt_C1","[0] + [1]*exp(-[2]*x)",80,500);
  fitFxn_jetPt_C1->SetParameter(0,jetPtFitParam_C1_0);
  fitFxn_jetPt_C1->SetParameter(1,jetPtFitParam_C1_1);
  fitFxn_jetPt_C1->SetParameter(2,jetPtFitParam_C1_2);
}
