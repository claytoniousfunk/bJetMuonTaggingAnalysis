void loadFitFxn_trkptrel(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_hadronPtRel = new TF1("fitFxn_trkptrel","[0] + [1]*x + [2]*x*x + [3]*x*x*x",0,10);

  fitFxn_hadronPtRel->SetParameter(0,trkptrelFitParam_0);
  fitFxn_hadronPtRel->SetParameter(1,trkptrelFitParam_1);
  fitFxn_hadronPtRel->SetParameter(2,trkptrelFitParam_1);
  fitFxn_hadronPtRel->SetParameter(3,trkptrelFitParam_1);
 
  fitFxn_hadronPtRel->SetParError(0,e_trkptrelFitParam_0);
  fitFxn_hadronPtRel->SetParError(1,e_trkptrelFitParam_1);
  fitFxn_hadronPtRel->SetParError(2,e_trkptrelFitParam_1);
  fitFxn_hadronPtRel->SetParError(3,e_trkptrelFitParam_1);
 
  cout << "~~ ... finished!" << endl;
 
}
