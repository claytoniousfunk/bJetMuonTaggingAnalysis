double getDr(double eta1, double phi1, double eta2, double phi2)
{
	double result = -1.0;
	double dEta = eta1-eta2;
	double dPhi = acos(cos(phi1 - phi2));
	result = sqrt(dEta*dEta + dPhi*dPhi);
	return result;
}
