void loadFitFxn_hadronPtRel(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_hadronPtRel = new TF1("fitFxn_hadronPtRel","[0] + [1]*x + [2]*x*x + [3]*x*x*x + [4]*x*x*x*x",0,10);

  fitFxn_hadronPtRel->SetParameter(0,hadronPtRelFitParam_0);
  fitFxn_hadronPtRel->SetParameter(1,hadronPtRelFitParam_1);
  fitFxn_hadronPtRel->SetParameter(2,hadronPtRelFitParam_2);
  fitFxn_hadronPtRel->SetParameter(3,hadronPtRelFitParam_3);
  fitFxn_hadronPtRel->SetParameter(4,hadronPtRelFitParam_4);

  fitFxn_hadronPtRel->SetParError(0,e_hadronPtRelFitParam_0);
  fitFxn_hadronPtRel->SetParError(1,e_hadronPtRelFitParam_1);
  fitFxn_hadronPtRel->SetParError(2,e_hadronPtRelFitParam_2);
  fitFxn_hadronPtRel->SetParError(3,e_hadronPtRelFitParam_3);
  fitFxn_hadronPtRel->SetParError(4,e_hadronPtRelFitParam_4);

  cout << "~~ ... finished!" << endl;
 
}
