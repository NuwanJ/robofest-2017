int[] getSensorReadingsAsAnArray(){	
	/*
		30/08/2017@Nuwan fill the digitalRead(HERE);
	*/

	/*
	(LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)


					    R[7]


					    R[8]


	*/

	static int reading[6];
	reading[0]=digitalRead();
	reading[1]=digitalRead();
	reading[2]=digitalRead();
	reading[3]=digitalRead();
	reading[4]=digitalRead();
	reading[5]=digitalRead();
	return reading;
}

int arrowColorSensorReading(){
	/*
	30/08/2017
	@Nuwan implement this sensor reading 
	*/
/*
	red----> return 0;
	green--> return 1;
	blue---> return 2;
*/
	return 0;
}

void trailAndErrorArrowFollow_Loop(int colorOfBox){

	/*
		30/08/2017
		We have to test this function by keeping the robot POINTED towards an arrow
		The robot should not be on the arrow
	*/

	/*
	Red=0, Green=1, Blue=2
	*/

	while(ture){
		while(arrowColorSensorReading()!=colorOfBox)motorForward(10);
		motorBackward(10);
		while(arrowColorSensorReading()!=colorOfBox)motorForward(1);
		while(sumOfArray(getSensorReadingsAsAnArray(),6)!=0){
			trailAndErrorArrowFollow_Forward();
		}
		while(sumOfArray(getSensorReadingsAsAnArray(),6)==0){
			motorBackward(1);
		}
		while(sumOfArray(getSensorReadingsAsAnArray(),6)!=0){
			trailAndErrorArrowFollow_Backward();
		}
		while(sumOfArray(getSensorReadingsAsAnArray(),6)==0){
			motorForward(1);
		}
		while(sumOfArray(getSensorReadingsAsAnArray(),6)!=0){
			trailAndErrorArrowFollow_Forward();
		}
	}
}

int sumOfArray(int ar[],int n){
	int sum=0;
	for(int i=0;i<n;i++)sum+=ar[i];
	return sum;
}


void trailAndErrorArrowFollow_Forward(){	
	/*
	(LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
Weights:	-3	 -2	  -1   1	2	  3

					    R[7]


					    R[8]


	*/


	int weight[6]={-3,-2,-1,1,2,3};


	int readings[]=getSensorReadingsAsAnArray();
	int weightedSum=0;
	for(int j=0;j<6;j++){
		weightedSum+=reading[j]*weight[j];
	}
	

	//LOGIC -- 1 -- Basic
	if(weightedSum!=0) motorRotate(weightedSum);
	motorForward(2);
}


void trailAndErrorArrowFollow_Backward(){	
	/*
	(LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
Weights:	3	 2	  1    -1	-2	 -3

					    R[7]


					    R[8]


	*/


	int weight[6]={3,2,1,-1,-2,-3};


	int readings[]=getSensorReadingsAsAnArray();
	int weightedSum=0;
	for(int j=0;j<6;j++){
		weightedSum+=reading[j]*weight[j];
	}
	

	//LOGIC -- 1 -- Basic
	if(weightedSum!=0) motorRotate(-1*weightedSum);
	motorBackward(2);
}
