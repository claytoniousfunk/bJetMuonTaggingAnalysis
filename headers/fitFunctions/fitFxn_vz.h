void loadFitFxn_vz(){
fitFxn_vz = new TF1("fitFxn_vz","[0]+[1]*x",-15,15);
fitFxn_vz->SetParameter(0,vzFitParam_0);
fitFxn_vz->SetParameter(1,vzFitParam_1);
}
