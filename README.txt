Connect the rate table
determine the serial por device
create link:
	ln -s -f /dev/ttyACM0 rate_table
run the code as follows:
	./run_calib > data.rst

This step is only needed if the "actual rate" is unknown 
crate a new data.rst and use cmp_true_rate.m
