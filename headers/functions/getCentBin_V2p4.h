const int getCentBin(int hiBin)
{
  int result = -1;
  if (hiBin >= hiBin_C0_lo && hiBin <= hiBin_C0_hi)
    result = 1;
  else if (hiBin > hiBin_C0_hi && hiBin <= hiBin_C1_hi)
    result = 2;
  else if (hiBin > hiBin_C1_hi && hiBin <= hiBin_C2_hi)
    result = 3;
  else if (hiBin > hiBin_C2_hi && hiBin <= hiBin_C3_hi)
    result = 4;
  else if (hiBin > hiBin_C3_hi && hiBin <= hiBin_C4_hi)
    result = 5;
  else if (hiBin > hiBin_C4_hi && hiBin <= hiBin_C5_hi)
    result = 6;
  else if (hiBin > hiBin_C5_hi && hiBin <= hiBin_C6_hi)
    result = 7;
  else if (hiBin > hiBin_C6_hi && hiBin <= hiBin_C7_hi)
    result = 8;
  else
    ;
  return result;
}	
