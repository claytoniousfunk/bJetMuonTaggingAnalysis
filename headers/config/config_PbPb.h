int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString hltString = "hltTree";
TString muonTreeString = "muonTree";
////// event filters
const int NeventFilters_HardProbes = 2;
std::string eventFilters_HardProbes[NeventFilters_HardProbes] = {"pprimaryVertexFilter","pclusterCompatibilityFilter"};
const int NeventFilters_SingleMuon = 5;
std::string eventFilters_SingleMuon[NeventFilters_SingleMuon] = {"pprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "collisionEventSelectionAODv2", "phfCoincFilter2Th4", "pclusterCompatibilityFilter"};
const int NeventFilters_MinBias = 2;
std::string eventFilters_MinBias[NeventFilters_MinBias] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
// jet options
bool doJetTrkMaxFilter = false;
bool doEtaPhiMask = false;
// High Level Triggers (HLTs)
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyJet100Trigger = false;
bool applyMinBiasTrigger = true;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;
// spectra alterations
bool doBJetNeutrinoEnergyShift = false;
bool doJERCorrection = false;
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// select dataset
bool doSingleMuonSample = false;
bool doMinBiasSample = true;
bool doHardProbesSample = false;
