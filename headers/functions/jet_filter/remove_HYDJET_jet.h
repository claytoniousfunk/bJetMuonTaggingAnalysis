

bool remove_HYDJET_jet(double pThat, double pTjet){

  // true if jet is from HYDJET
  // derived from Matt Nguyen's study
  
  bool result = false;

  //if(pThat < 0.35 * pTjet) result = true;
  //if(pThat < 0.4 * pTjet) result = true;
  if(pThat < 0.45 * pTjet) result = true;

  return result;

}
