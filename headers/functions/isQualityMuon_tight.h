bool isQualityMuon_tight(int muChi2NDF, 
		double muInnerD0, 
		double muInnerDz, 
		int muMuonHits, 
		int muPixelHits, 
		int muIsGlobal,
		int muIsPF, 
		int muStations, 
		int muTrkLayers){

	bool result = true;
	if(muChi2NDF == -99 ||
			muChi2NDF > 10 ||
			TMath::Abs(muInnerD0) > 0.2 ||
			TMath::Abs(muInnerDz) > 0.5 ||
			muMuonHits <= 0 ||
			muPixelHits <= 0 ||
			muIsGlobal == 0 ||
			muIsPF == 0 ||
			muStations  <= 1 ||
			muTrkLayers <= 5)
		result = false;

	return result;
}
