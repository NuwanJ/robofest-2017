
int [6][6] history;
int currentIndex=5; //This is how this should start


int[] getSensorReadingsAsAnArray(){
	//30/08/2017 @Nuwan please complete this function!
	
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

void trailAndErrorArrowFollow_Loop(){
	/*
		30/08/2017
		We have to test this function by keeping the robot near an arrow
		(at least one sensor should give a reading at the start)
	*/
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
	motorForward(30);


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





void arrowFollowingLoop(){
	
	/*
	(LEFT) R[0] R[1] R[2] R[3] R[4] R[5]  (Right)
Weights:	-3	 -2	  -1   1	2	  3

					    R[7]


					    R[8]


	*/


	int weight[6]={-3,-2,-1,1,2,3};


	currentIndex=(currentIndex+1)%6;
	int temp[]=getSensorReadingsAsAnArray();
	for(int i=0;i<6;i++){
		history[currentIndex][i]=temp[currentIndex][i];
	}

	//This logic could be implemented efficiently but this would do for now :-)
	int weightedSums[6];
	for(int i=0;i<6;i++){
		weightedSums[i]=0;
		for(int j=0;j<6;j++){
			weightedSums[i]+=history[(currentIndex-i+6)%6]*weight[j];
		}
	}

	//LOGIC -- 1 -- Basic
	if(weightedSums[0]<0){
		//turn left
	}
	else if(weightedSums[0]>0){
		//turn right
	}
	else{
		//go forward
	}



	//LOGIC -- 2 -- Considering the trend







}