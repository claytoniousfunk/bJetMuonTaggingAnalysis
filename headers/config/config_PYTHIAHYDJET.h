// general analysis options
int isMC_status = 1;
int AASetup_status = 1;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 5;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "collisionEventSelectionAODv2", "phfCoincFilter2Th4", "pclusterCompatibilityFilter"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = false; // set TRUE for MuJet and BJet datasets
// reweighting functions
bool doHiBinReweight = true;
bool doVzReweight = true;
bool doJetPtReweight = true;
// jet-based filters
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
bool doRemoveHYDJETjet = true;
bool doEtaPhiMask = false;
bool doBJetEnergyShift = false;
bool doJERCorrection = false;
bool doHadronPtRelReweight = false;
bool doDRReweight = false;
bool doWeightCut = true;
