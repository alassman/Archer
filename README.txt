Set Up MC configurations in EEPROM using RoboteQ PC utility
under Configurtation tab:
Inputs/Outputs:
	1.) set command priorities so that serial is number 1
	2.) set encoder 1 as feedback and check the "1" box
		2a.) this box is to indicate which motor channel it is to be used for
	3.) set pulses/rev
	4.) repeat for encoder 2 but checking the "2" box after feedback
	5.) make sure all other inputs are disabbled, specifically Pulse inputs because they share pins with the encoder inputs
Power Output:
	1.) set Max Speed to max RPM of the motor
	2.) set operating mode to closed loop speed
