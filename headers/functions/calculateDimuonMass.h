
#include "TLorentzVector.h"

double calculateDimuonMass(double pt1, double eta1, double phi1,
                           double pt2, double eta2, double phi2) {

    TLorentzVector mu1, mu2;
    mu1.SetPtEtaPhiM(pt1, eta1, phi1, 0.105658);
    mu2.SetPtEtaPhiM(pt2, eta2, phi2, 0.105658);

    return (mu1 + mu2).M();
}



/* double calculateDimuonMass(double pt1, double eta1, double phi1, double pt2, double eta2, double phi2, UInt_t runNumber, UInt_t lumiSection, ULong64_t evtNumber){ */

/*   std::cout << "Run = " << runNumber << "\n"; */
/*   std::cout << "Lumisection = " << lumiSection << "\n"; */
/*   std::cout << "Event = " << evtNumber << "\n"; */
    
/*   double result = -1.0; */

/*   double m_mu = 0.105658; // muon mass in GeV */

/*   result = TMath::Sqrt(2*m_mu*m_mu + 2*pt1*pt2*(TMath::CosH(eta1-eta2) - TMath::Cos(phi1-phi2))); */

/*   std::cout << "dimuonMass(" << pt1 << ", " << eta1 << ", " << phi1 << " | " << pt2 << ", " << eta2 << ", " << phi2 << ") = " << result << "\n"; */

/*   return result; */


/* } */

/* double calculateDimuonMass(double pt1, double eta1, double phi1, double pt2, double eta2, double phi2){ */
    
/*   double result = -1.0; */

/*   double m_mu = 0.105658; // muon mass in GeV */

/*   result = TMath::Sqrt(2*m_mu*m_mu + 2*pt1*pt2*(TMath::CosH(eta1-eta2) - TMath::Cos(phi1-phi2))); */

/*   return result; */


/* } */
