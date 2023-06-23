int getJetPtBin(double jetpt){
	int result = -1;
	if(jetpt >= jetpt_J0_lo && jetpt < jetpt_J0_hi) result = 1;
	else if(jetpt >= jetpt_J0_hi && jetpt < jetpt_J1_hi) result = 2;
	else if(jetpt >= jetpt_J1_hi && jetpt < jetpt_J2_hi) result = 3;
	else if(jetpt >= jetpt_J2_hi && jetpt < jetpt_J3_hi) result = 4;
	else if(jetpt >= jetpt_J3_hi && jetpt < jetpt_J4_hi) result = 5;
	else if(jetpt >= jetpt_J4_hi && jetpt < jetpt_J5_hi) result = 6;
	else ;
	return result;
}
