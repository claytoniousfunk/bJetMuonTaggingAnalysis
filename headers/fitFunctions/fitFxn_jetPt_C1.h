void loadFitFxn_jetPt_C1(){
  fitFxn_jetPt_C1 = new TF1("fitFxn_jetPt_C1","[0]+[1]*x",0,500);
  fitFxn_jetPt_C1->SetParameter(0,jetPtFitParam_C1_0);
  fitFxn_jetPt_C1->SetParameter(1,jetPtFitParam_C1_1);
}
