const int getCentBin(int hiBin)
{
  int result = -1;
  if (hiBin >= 0 && hiBin < 10)
    result = 1;
  else if (hiBin >= 10 && hiBin < 20)
    result = 2;
  else if (hiBin >= 20 && hiBin < 30)
    result = 3;
  else if (hiBin >= 30 && hiBin < 40)
    result = 4;
  else if (hiBin >= 40 && hiBin < 50)
    result = 5;
  else if (hiBin >= 50 && hiBin < 60)
    result = 6;
  else if (hiBin >= 60 && hiBin < 70)
    result = 7;
  else if (hiBin >= 70 && hiBin < 80)
    result = 8;
  else if (hiBin >= 80 && hiBin < 90)
    result = 9;
  else if (hiBin >= 90 && hiBin < 100)
    result = 10;
  else if (hiBin >= 100 && hiBin <= 180)
    result = 11;
  else {} ;
  return result;
}	
