bool isWDecayMuon_raw(double muonPt, double rawJetPt){

	bool result = false;
	if(muonPt/rawJetPt > 0.8) result = true;
	return result;


}
