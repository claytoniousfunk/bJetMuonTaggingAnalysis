
double left_margin_value;
double bottom_margin_value;
double top_margin_value;

TPad* pad_set_margins(TPad* pad){

  left_margin_value = 0.2;
  bottom_margin_value = 0.2;
  top_margin_value = 0.2;
  
  pad->SetLeftMargin(left_margin_value);
  pad->SetBottomMargin(bottom_margin_value);
  pad->SetTopMargin(top_margin_value);

  return pad;

}


TPad* pad_set_margins_bottom(TPad* pad){

  left_margin_value = 0.2;
  bottom_margin_value = 0.2;
  top_margin_value = 0.0;
  
  pad->SetLeftMargin(left_margin_value);
  pad->SetBottomMargin(bottom_margin_value);
  pad->SetTopMargin(top_margin_value);

  return pad;

}

TPad* pad_set_margins_top(TPad* pad){

  left_margin_value = 0.2;
  bottom_margin_value = 0.0;
  top_margin_value = 0.2;
  
  pad->SetLeftMargin(left_margin_value);
  pad->SetBottomMargin(bottom_margin_value);
  pad->SetTopMargin(top_margin_value);

  return pad;

}
