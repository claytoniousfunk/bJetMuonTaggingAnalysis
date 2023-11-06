bool passesLeadingGenJetPthatFilter(double jetPt, double pthat){

	bool result = false;

	double x = pthat;

	if(jetPt < (-17.909) + (2.65298)*x + (-0.0133696)*x*x + (6.32235e-05)*x*x*x + (-1.37185e-07)*x*x*x*x + (1.02678e-10)*x*x*x*x*x) result = true;

	return result;

}
