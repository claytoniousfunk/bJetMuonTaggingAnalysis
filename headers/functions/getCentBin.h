const int getCentBin(int hiBin)
{
	int result = -1;
	if (hiBin >= hiBin_C0_lo && hiBin <= hiBin_C0_hi)
		result = 1;
	else if (hiBin > hiBin_C0_hi && hiBin <= hiBin_C1_hi)
		result = 2;
	else if (hiBin > hiBin_C1_hi && hiBin <= hiBin_C2_hi)
		result = 3;
	else
		;
	return result;
}	
