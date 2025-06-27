int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 3;
std::string eventFilters[NeventFilters] = {"pPAprimaryVertexFilter","HBHENoiseFilterResultRun2Loose","pBeamScrapingFilter"};
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = false;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool doJESCorrection = false;
// spectra alterations
bool doBJetNeutrinoEnergyShift = true;
bool doJERCorrection = false;
