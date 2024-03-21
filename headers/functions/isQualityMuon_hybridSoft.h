bool isQualityMuon_hybridSoft(int muChi2NDF, 
			      double muInnerD0, 
			      double muInnerDz, 
			      int muPixelHits, 
			      int muIsTracker, 
			      int muIsGlobal, 
			      int muTrkLayers){

	bool result = true;
	if(muChi2NDF == -99 ||
	   TMath::Abs(muInnerD0) > 0.3 ||
	   TMath::Abs(muInnerDz) > 20 ||
	   muPixelHits <= 0 ||
	   muIsTracker == 0 ||
	   muIsGlobal == 0 ||
	   muTrkLayers <= 5)
	  result = false;

	return result;
}
