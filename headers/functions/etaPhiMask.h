bool etaPhiMask(double jetEta, double jetPhi){
  bool result = false;
  if((jetEta > -0.3 && jetEta < 1.4) && (jetPhi > 0.4 && jetPhi < 0.8)){
    result = true;
  }
  return result;
}
