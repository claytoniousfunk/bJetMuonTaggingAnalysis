bool passesLeadingGenJetPthatFilter(double jetPt, double pthat){

	bool result = false;

	if(jetPt < 1.702*pthat + 9.701) result = true;

	return result;

}
