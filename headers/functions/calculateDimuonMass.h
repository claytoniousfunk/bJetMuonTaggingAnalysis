

double calculateDimuonMass(double pt1, double eta1, double phi1, double pt2, double eta2, double phi2){

  double result = -1.0;

  double m_mu = 0.105658; // muon mass in GeV

  result = TMath::Sqrt(2*m_mu*m_mu + 2*pt1*pt2*(TMath::CosH(eta1-eta2) - TMath::Cos(phi1-phi2)));

  return result;


}
