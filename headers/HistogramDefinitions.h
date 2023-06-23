// user includes

#include "/home/clayton/Analysis/code/headers/AnalysisSetup.h"



//const int NJetIndices = 4;
//const int NJetFlavorIndices = 3;
//const int NCentralityIndices = 3;


// JETS FORMAT
// TH1D *h_jetpt[centralityIndex][jetPtIndex][jetFlavorIndex]

//TH1D *h_jetpt[5][5][4];


// JETS
//h_jetpt[0][0][0] = new TH1D("h_jetpt_000","h_jetpt_000",NPtBins,ptMin,ptMax);
/*
	TH1D *h_jetpt[0][1][0] = new TH1D("h_jetpt_010","h_jetpt_010",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][1][1] = new TH1D("h_jetpt_011","h_jetpt_011",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][1][2] = new TH1D("h_jetpt_012","h_jetpt_012",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][1][3] = new TH1D("h_jetpt_013","h_jetpt_013",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][1][4] = new TH1D("h_jetpt_014","h_jetpt_014",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[0][2][0] = new TH1D("h_jetpt_020","h_jetpt_020",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][2][1] = new TH1D("h_jetpt_021","h_jetpt_021",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][2][2] = new TH1D("h_jetpt_022","h_jetpt_022",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][2][3] = new TH1D("h_jetpt_023","h_jetpt_023",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][2][4] = new TH1D("h_jetpt_024","h_jetpt_024",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[0][3][0] = new TH1D("h_jetpt_030","h_jetpt_030",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][3][1] = new TH1D("h_jetpt_031","h_jetpt_031",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][3][2] = new TH1D("h_jetpt_032","h_jetpt_032",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][3][3] = new TH1D("h_jetpt_033","h_jetpt_033",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][3][4] = new TH1D("h_jetpt_034","h_jetpt_034",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[0][4][0] = new TH1D("h_jetpt_040","h_jetpt_040",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][4][1] = new TH1D("h_jetpt_041","h_jetpt_041",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][4][2] = new TH1D("h_jetpt_042","h_jetpt_042",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][4][3] = new TH1D("h_jetpt_043","h_jetpt_043",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[0][4][4] = new TH1D("h_jetpt_044","h_jetpt_044",NPtBins,ptMin,ptMax);

TH1D *h_jetpt[1][0][0] = new TH1D("h_jetpt_100","h_jetpt_100",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[1][1][0] = new TH1D("h_jetpt_110","h_jetpt_110",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][1][1] = new TH1D("h_jetpt_111","h_jetpt_111",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][1][2] = new TH1D("h_jetpt_112","h_jetpt_112",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][1][3] = new TH1D("h_jetpt_113","h_jetpt_113",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][1][4] = new TH1D("h_jetpt_114","h_jetpt_114",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[1][2][0] = new TH1D("h_jetpt_120","h_jetpt_120",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][2][1] = new TH1D("h_jetpt_121","h_jetpt_121",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][2][2] = new TH1D("h_jetpt_122","h_jetpt_122",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][2][3] = new TH1D("h_jetpt_123","h_jetpt_123",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][2][4] = new TH1D("h_jetpt_124","h_jetpt_124",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[1][3][0] = new TH1D("h_jetpt_130","h_jetpt_130",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][3][1] = new TH1D("h_jetpt_131","h_jetpt_131",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][3][2] = new TH1D("h_jetpt_132","h_jetpt_132",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][3][3] = new TH1D("h_jetpt_133","h_jetpt_133",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][3][4] = new TH1D("h_jetpt_134","h_jetpt_134",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[1][4][0] = new TH1D("h_jetpt_140","h_jetpt_140",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][4][1] = new TH1D("h_jetpt_141","h_jetpt_141",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][4][2] = new TH1D("h_jetpt_142","h_jetpt_142",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][4][3] = new TH1D("h_jetpt_143","h_jetpt_143",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[1][4][4] = new TH1D("h_jetpt_144","h_jetpt_144",NPtBins,ptMin,ptMax);

TH1D *h_jetpt[2][0][0] = new TH1D("h_jetpt_200","h_jetpt_200",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[2][1][0] = new TH1D("h_jetpt_210","h_jetpt_210",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][1][1] = new TH1D("h_jetpt_211","h_jetpt_211",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][1][2] = new TH1D("h_jetpt_212","h_jetpt_212",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][1][3] = new TH1D("h_jetpt_213","h_jetpt_213",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][1][4] = new TH1D("h_jetpt_214","h_jetpt_214",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[2][2][0] = new TH1D("h_jetpt_220","h_jetpt_220",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][2][1] = new TH1D("h_jetpt_221","h_jetpt_221",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][2][2] = new TH1D("h_jetpt_222","h_jetpt_222",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][2][3] = new TH1D("h_jetpt_223","h_jetpt_223",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][2][4] = new TH1D("h_jetpt_224","h_jetpt_224",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[2][3][0] = new TH1D("h_jetpt_230","h_jetpt_230",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][3][1] = new TH1D("h_jetpt_231","h_jetpt_231",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][3][2] = new TH1D("h_jetpt_232","h_jetpt_232",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][3][3] = new TH1D("h_jetpt_233","h_jetpt_233",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][3][4] = new TH1D("h_jetpt_234","h_jetpt_234",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[2][4][0] = new TH1D("h_jetpt_240","h_jetpt_240",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][4][1] = new TH1D("h_jetpt_241","h_jetpt_241",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][4][2] = new TH1D("h_jetpt_242","h_jetpt_242",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][4][3] = new TH1D("h_jetpt_243","h_jetpt_243",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[2][4][4] = new TH1D("h_jetpt_244","h_jetpt_244",NPtBins,ptMin,ptMax);


TH1D *h_jetpt[3][0][0] = new TH1D("h_jetpt_300","h_jetpt_300",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[3][1][0] = new TH1D("h_jetpt_310","h_jetpt_310",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][1][1] = new TH1D("h_jetpt_311","h_jetpt_311",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][1][2] = new TH1D("h_jetpt_312","h_jetpt_312",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][1][3] = new TH1D("h_jetpt_313","h_jetpt_313",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][1][4] = new TH1D("h_jetpt_314","h_jetpt_314",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[3][2][0] = new TH1D("h_jetpt_320","h_jetpt_320",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][2][1] = new TH1D("h_jetpt_321","h_jetpt_321",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][2][2] = new TH1D("h_jetpt_322","h_jetpt_322",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][2][3] = new TH1D("h_jetpt_323","h_jetpt_323",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][2][4] = new TH1D("h_jetpt_324","h_jetpt_324",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[3][3][0] = new TH1D("h_jetpt_330","h_jetpt_330",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][3][1] = new TH1D("h_jetpt_331","h_jetpt_331",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][3][2] = new TH1D("h_jetpt_332","h_jetpt_332",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][3][3] = new TH1D("h_jetpt_333","h_jetpt_333",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][3][4] = new TH1D("h_jetpt_334","h_jetpt_334",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[3][4][0] = new TH1D("h_jetpt_340","h_jetpt_340",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][4][1] = new TH1D("h_jetpt_341","h_jetpt_341",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][4][2] = new TH1D("h_jetpt_342","h_jetpt_342",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][4][3] = new TH1D("h_jetpt_343","h_jetpt_343",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[3][4][4] = new TH1D("h_jetpt_344","h_jetpt_344",NPtBins,ptMin,ptMax);

TH1D *h_jetpt[4][0][0] = new TH1D("h_jetpt_400","h_jetpt_400",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[4][1][0] = new TH1D("h_jetpt_410","h_jetpt_410",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][1][1] = new TH1D("h_jetpt_411","h_jetpt_411",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][1][2] = new TH1D("h_jetpt_412","h_jetpt_412",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][1][3] = new TH1D("h_jetpt_413","h_jetpt_413",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][1][4] = new TH1D("h_jetpt_414","h_jetpt_414",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[4][2][0] = new TH1D("h_jetpt_420","h_jetpt_420",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][2][1] = new TH1D("h_jetpt_421","h_jetpt_421",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][2][2] = new TH1D("h_jetpt_422","h_jetpt_422",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][2][3] = new TH1D("h_jetpt_423","h_jetpt_423",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][2][4] = new TH1D("h_jetpt_424","h_jetpt_424",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[4][3][0] = new TH1D("h_jetpt_430","h_jetpt_430",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][3][1] = new TH1D("h_jetpt_431","h_jetpt_431",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][3][2] = new TH1D("h_jetpt_432","h_jetpt_432",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][3][3] = new TH1D("h_jetpt_433","h_jetpt_433",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][3][4] = new TH1D("h_jetpt_434","h_jetpt_434",NPtBins,ptMin,ptMax);
	TH1D *h_jetpt[4][4][0] = new TH1D("h_jetpt_440","h_jetpt_440",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][4][1] = new TH1D("h_jetpt_441","h_jetpt_441",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][4][2] = new TH1D("h_jetpt_442","h_jetpt_442",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][4][3] = new TH1D("h_jetpt_443","h_jetpt_443",NPtBins,ptMin,ptMax);
		TH1D *h_jetpt[4][4][4] = new TH1D("h_jetpt_444","h_jetpt_444",NPtBins,ptMin,ptMax);



*/


