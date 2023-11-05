int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "ak4PFJetAnalyzer";
TString muonTreeString = "ggHiNtuplizerGED";
TString hltString = "hltanalysis";
const int NeventFilters = 3;
std::string eventFilters[NeventFilters] = {"pPAprimaryVertexFilter","HBHENoiseFilterResultRun2Loose","pBeamScrapingFilter"};
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = true;


