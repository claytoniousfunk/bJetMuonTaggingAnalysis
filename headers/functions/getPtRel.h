double getPtRel(double MuonPt, double MuonEta, double MuonPhi, double JetPt, double JetEta, double JetPhi)
{

	double Muon_Px = MuonPt * TMath::Cos(MuonPhi);
	double Muon_Py = MuonPt * TMath::Sin(MuonPhi);
	double Muon_Pz = MuonPt * TMath::SinH(MuonEta);

	double Jet_Px = JetPt * TMath::Cos(JetPhi);
	double Jet_Py = JetPt * TMath::Sin(JetPhi);
	double Jet_Pz = JetPt * TMath::SinH(JetEta);

	float lj_x = Jet_Px;
	float lj_y = Jet_Py;
	float lj_z = Jet_Pz;

	// absolute values squared
	float lj2 = lj_x * lj_x + lj_y * lj_y + lj_z * lj_z;

	//float lep2 = lep.px()*lep.px()+lep.py()*lep.py()+lep.pz()*lep.pz();
	float lep2 = Muon_Px * Muon_Px + Muon_Py * Muon_Py + Muon_Pz * Muon_Pz;

	// projection vec(mu) to lepjet axis
	float lepXlj = Muon_Px * lj_x + Muon_Py * lj_y + Muon_Pz * lj_z;

	// absolute value squared and normalized
	float pLrel2 = lepXlj * lepXlj / lj2;
	float pTrel2 = lep2 - pLrel2;

	return (pTrel2 > 0) ? std::sqrt(pTrel2) : 0.0;
}
