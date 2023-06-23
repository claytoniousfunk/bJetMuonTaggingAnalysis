bool triggerIsOn(int triggerValue, int prescaleValue){

	bool result = true;
	if(triggerValue == 0 || prescaleValue == 0) result = false;
	return result;

}
