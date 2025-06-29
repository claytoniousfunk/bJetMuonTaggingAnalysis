void loadFitFxn_trkptrel(){

  cout << "~~ loading fit function ..." << endl;
  
  fitFxn_trkptrel = new TF1("fitFxn_trkptrel","[0] + [1]*x + [2]*x*x + [3]*x*x*x",0,10);

  fitFxn_trkptrel->SetParameter(0,trkptrelFitParam_0);
  fitFxn_trkptrel->SetParameter(1,trkptrelFitParam_1);
  fitFxn_trkptrel->SetParameter(2,trkptrelFitParam_2);
  fitFxn_trkptrel->SetParameter(3,trkptrelFitParam_3);
 
  fitFxn_trkptrel->SetParError(0,e_trkptrelFitParam_0);
  fitFxn_trkptrel->SetParError(1,e_trkptrelFitParam_1);
  fitFxn_trkptrel->SetParError(2,e_trkptrelFitParam_2);
  fitFxn_trkptrel->SetParError(3,e_trkptrelFitParam_3);
 
  cout << "~~ ... finished!" << endl;
 
}
