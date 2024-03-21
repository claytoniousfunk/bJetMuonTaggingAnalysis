bool passesJetTrkMaxFilter(double jetTrkMax, double jetPt){

  bool result = false;

  double trkMaxFraction = jetTrkMax / jetPt ;
  
  if(trkMaxFraction > 0.01 && trkMaxFraction < 0.98) result = true;

  return result;


}
