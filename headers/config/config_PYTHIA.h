// general analysis options
int isMC_status = 1;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pPAprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = false;
bool doVzReweight = true;
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
bool doRemoveHYDJETjet = true;
bool doEtaPhiMask = false;
bool doJetPtReweight = true;




