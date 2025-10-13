int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString hltString = "hltTree";
TString muonTreeString = "muonTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter","pclusterCompatibilityFilter"};
bool doJetTrkMaxFilter = false;
bool doEtaPhiMask = false;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyMinBiasTrigger = false;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;
// spectra alterations
bool doBJetNeutrinoEnergyShift = false;
bool doJERCorrection = false;
// options for systematic studies
bool apply_JER_smear = true;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
