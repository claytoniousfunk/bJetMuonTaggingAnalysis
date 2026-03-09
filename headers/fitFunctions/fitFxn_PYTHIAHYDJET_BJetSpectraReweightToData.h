


void loadFitFxn_PYTHIAHYDJET_BJetSpectraReweightToData(){

  cout << "~~ loading fit function ..." << endl;

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4 = new TF1("fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4","[0] + ([1] - [0])*exp(-[2]*x)");
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3 = new TF1("fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3","[0] + ([1] - [0])*exp(-[2]*x)");
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2 = new TF1("fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2","[0] + ([1] - [0])*exp(-[2]*x)");
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1 = new TF1("fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1","[0] + ([1] - [0])*exp(-[2]*x)");
  

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParameter(0,BJetSpectraReweightToData_C4_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParameter(1,BJetSpectraReweightToData_C4_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParameter(2,BJetSpectraReweightToData_C4_2);

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParError(0,e_BJetSpectraReweightToData_C4_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParError(1,e_BJetSpectraReweightToData_C4_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C4->SetParError(2,e_BJetSpectraReweightToData_C4_2);
  
  ///////////////////////////////////////////////////////////////////////////////////////////////

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParameter(0,BJetSpectraReweightToData_C3_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParameter(1,BJetSpectraReweightToData_C3_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParameter(2,BJetSpectraReweightToData_C3_2);

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParError(0,e_BJetSpectraReweightToData_C3_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParError(1,e_BJetSpectraReweightToData_C3_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C3->SetParError(2,e_BJetSpectraReweightToData_C3_2);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParameter(0,BJetSpectraReweightToData_C2_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParameter(1,BJetSpectraReweightToData_C2_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParameter(2,BJetSpectraReweightToData_C2_2);

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParError(0,e_BJetSpectraReweightToData_C2_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParError(1,e_BJetSpectraReweightToData_C2_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C2->SetParError(2,e_BJetSpectraReweightToData_C2_2);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParameter(0,BJetSpectraReweightToData_C1_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParameter(1,BJetSpectraReweightToData_C1_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParameter(2,BJetSpectraReweightToData_C1_2);

  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParError(0,e_BJetSpectraReweightToData_C1_0);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParError(1,e_BJetSpectraReweightToData_C1_1);
  fitFxn_PYTHIAHYDJET_BJetSpectraReweightToData_C1->SetParError(2,e_BJetSpectraReweightToData_C1_2);






}
