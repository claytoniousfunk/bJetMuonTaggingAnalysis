// general analysis options
int isMC_status = 1;
int AASetup_status = 1;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = true; // set TRUE for MuJet and BJet datasets
bool doHiBinReweight = false;
bool doVzReweight = false;
// jet filter
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
// eta-phi mask
bool doEtaPhiMask = true;
