void test_JER_fxn(){
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",10,500);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);

  cout << "f(10) = " << JER_fxn->Eval(10.) << endl;
  cout << "f(60) = " << JER_fxn->Eval(60.) << endl;

  JER_fxn->Draw();
}
