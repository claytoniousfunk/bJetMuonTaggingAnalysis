bool passesLeadingGenJetPthatFilter(double jetPt, double pthat){

	bool result = false;

	if(jetPt < 1.488*pthat + 9.157) result = true;

	return result;

}
