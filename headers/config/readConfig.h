
void readConfig(){

  cout << endl << " <<<<<< reading configuration <<<<<<<<< " << endl;
  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl << endl;
  cout << "    Events:  " << endl;
  cout << "           pThat > " << pthatcut << endl; 
  cout << "    Jet analyzer: " << jetTreeString << endl;
  cout << "                  " << jetPtCut << " < jet pt < "<< ptMax << " GeV" << endl;
  cout << "           |jet eta| < " << etaMax << endl;
  cout << "                   R = " << epsilon_mm << endl; 
  cout << "    mouns:" << endl;
  cout << "             muon pt > " << muPtCut << endl;
  cout << "          |muon eta| < " << trkEtaMax << endl << endl;
  cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< " << endl << endl;


  
    


}
