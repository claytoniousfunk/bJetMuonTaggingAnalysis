int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 1;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter"};
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = false;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool doJESCorrection = false;
// spectra alterations
bool doBJetNeutrinoEnergyShift = false;
bool doJERCorrection = false;
