void loadFitFxn_hadronPtRel(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_hadronPtRel = new TF1("fitFxn_hadronPtRel","[0] + [1]*x",0,10);

  fitFxn_hadronPtRel->SetParameter(0,hadronPtRelFitParam_0);
  fitFxn_hadronPtRel->SetParameter(1,hadronPtRelFitParam_1);

  fitFxn_hadronPtRel->SetParError(0,e_hadronPtRelFitParam_0);
  fitFxn_hadronPtRel->SetParError(1,e_hadronPtRelFitParam_1);

  cout << "~~ ... finished!" << endl;
 
}
