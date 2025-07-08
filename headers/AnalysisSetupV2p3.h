
//const int NCentralityIndices = 3;
const int NCentralityIndices = 5;
const int NJetPtIndices = 7;
const int NJetFlavorIndices = 7;

//flavors

int isUJet = 1;
int isDJet = 2;
int isSJet = 3;
int isCJet = 4;
int isBJet = 5;
int isGJet = 6;
int isXJet = 7;


const int hiBin_C0_lo = 0;
const int hiBin_C0_hi = 20;
const int hiBin_C1_hi = 60;
const int hiBin_C2_hi = 100;
const int hiBin_C3_hi = 160;
int centEdges[NCentralityIndices] = {hiBin_C0_lo, hiBin_C0_hi, hiBin_C1_hi, hiBin_C2_hi};

/* const int hiBin_C0_lo = 0; */
/* const int hiBin_C0_hi = 60; */
/* const int hiBin_C1_hi = 180; */
/* int centEdges[NCentralityIndices] = {hiBin_C0_lo, hiBin_C0_hi, hiBin_C1_hi}; */


// for PbPb Data scans
const int NPhiBins = 100;
const double phiMin = -TMath::Pi();
const double phiMax = TMath::Pi();

const int NEtaBins = 160;
const double etaMin = -1.6;
const double etaMax = 1.6;

const int NTrkEtaBins = 200;
const double trkEtaMin = -2.0;
const double trkEtaMax = 2.0;

const int NPtBins = 96;
const double jetPtCut = 5.0; // cut on muon jets
const double ptMin = 20.0;
const double ptMax = 500.0;

const int NTrkPtBins = 100;
const double trkPtMin = 0.0;
const double trkPtMax = 20.0;

const int NMuPtBins = 100;
const double muPtMin = 0.0;
const double muPtMax = 100.0;

const double deltaRCut = 0.4;  // muon-matching dR

//double muPtCut = 7.0; // mu5 scans
//double muPtCut = 9.0; // mu7 scans
double muPtCut = 14.0; // mu12 scans

//double muPtMaxCut = 9.0; // mu5 scans
//double muPtMaxCut = 14.0; // mu7 scans
double muPtMaxCut = 1000.0; // mu12 scans

double nuPtCut = 0.0;
double nuPtMaxCut = 1000.0;

//const double pthatcut = 15.0;
const double pthatcut = 20.0;
//const double pthatcut = 25.0;
//const double pthatcut = 30.0;
//const double pthatcut = 45.0;
//const double pthatcut = 40.0;
//const double pthatcut = 50.0;

const int NMuRelPtBins = 100;
const double muRelPtMin = 0.0;
const double muRelPtMax = 10.0;

const int NhiBinBins = 200;
const int hiBinMin = 0;
const int hiBinMax = 200;

const double jetpt_J0_lo = 80.0;
const double jetpt_J0_hi = 100.0;
const double jetpt_J1_hi = 120.0;
const double jetpt_J2_hi = 150.0;
const double jetpt_J3_hi = 200.0;
const double jetpt_J4_hi = 300.0;
const double jetpt_J5_hi = 500.0;

double jetPtEdges[NJetPtIndices] = {jetpt_J0_lo, jetpt_J0_hi, jetpt_J1_hi, jetpt_J2_hi, jetpt_J3_hi, jetpt_J4_hi, jetpt_J5_hi};

const int NVzBins = 60;
const double vzMin = -15.0;
const double vzMax = 15.0;

const double epsilon = 0.03;
const double epsilon_mm = 0.4;

const double d0cut = 0.002;

const double d0_min = -0.2;
const double d0_max = 0.2;
const int Nd0Bins = 800;

const int NpthatBins = 100;
const double pthatMin = 0.0;
const double pthatMax = 500.0;

const double randomCone_dR = 0.4;

const int NpartBins = 200;
const int NpartMin = 0;
const int NpartMax = 200;

// for jets
const int NdRBins = 200;
const double dRBinMin = 0.0;
const double dRBinMax = 0.5; 

// for muons
const int NMudRBins = 100;
const double MudRBinMin = 0.0;
const double MudRBinMax = 0.1; 

const int NptRatioBins = 100;
const double ptRatioMin = 0.0;
const double ptRatioMax = 5.0;


const double massJPsi = 3.0969; // mass of J/Psi particle in GeV
const int NmassJPsiBins = 100;
const double massJPsiMin = 0.8*massJPsi;
const double massJPsiMax = 1.2*massJPsi;

const double massK0 = 0.497; // mass of K0 particle in GeV
const int NmassK0Bins = 100;
const double massK0Min = 0.8*massK0;
const double massK0Max = 1.2*massK0;

const int NinclParentMassBins = 500;
const double parentMassMin = 0.0;
const double parentMassMax = 50.0;

const double massMuon = 0.1056; // mass of muon in GeV

/// weight distributions
const double weightInputLow = 0.0;
const double weightInputHigh = 0.1;
const int NWeightBins = 2000;
const double weightCut = 0.01;

// templates
const int NTemplateIndices = 4;
const string templateIndexNames[NTemplateIndices] = {"nominal","JERSmear","JEUShiftUp","JEUShiftDown"};



