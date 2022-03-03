#Excercises 3
The button operate in two states open and closed therefore it is employed to generate digital signal. However during the button is pressed then generated signal is unspecified due to mechanical vibration of button conntancts. The signal is fast switched beetween two states and electronical system can interpret this likes multiple signal not a single signal. To avoid this is corporated several method and this actions are named "debouncing". 

Software debouncing method is accomplished by constatly checking change of input signal. If the state has changed then the time starts counting. When the change has not occurred for a specified time (debouncing delay), the button state is in the final steady state and can proper read it's digital state. 

Consider the push button connected to microcontroler input with pull-up resitor (if presset then make connection between gnd) then pseudocode like as:
	
```c
void main()
{
	// initial button state
	currentState = HIGH;
	previousState = HIGH;
	lastChangeTime = 0;
	debounceDelay = 10;
	
	while(1)
	{
		// main loop
		
		// chect if change button state and reset time counter
		currentState = ReadButtonState()
		if( currentState != previousState ){
			lastChangeTime = millis();
			previousState = currentState;
		}
			
		// check if lastChangeTime be greater than debounceDelay 
		if( (millis() - lastChangeTime) > debounceDelay && previousState == LOW)
		{
			// button state has been pressed
		}
		
	}
}
```

In hardware "debouncing" methods is using low-pass filter on microcontroler input. This filter is create with capacitor and resistor. The capacitor, named "deboucing capacitor", is connected between MCU input and ground. The resistor connected is between MCU input and push button connector. This circuit makes that response signal after the button pressing is smoothed.
