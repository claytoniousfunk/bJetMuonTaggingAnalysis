void loadFitFxn_jetPt(){
  fitFxn_jetPt = new TF1("fitFxn_jetPt","[0]+[1]*x+[2]*x*x+[3]*x*x*x",0,1000);
  fitFxn_jetPt->SetParameter(0,jetPtFitParam_0);
  fitFxn_jetPt->SetParameter(1,jetPtFitParam_1);
  fitFxn_jetPt->SetParameter(2,jetPtFitParam_2);
  fitFxn_jetPt->SetParameter(3,jetPtFitParam_3);
}
