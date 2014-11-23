task autonomous() // this code is for blue team-- the robot starts in the non- skyrise tile and is facing opposite of the wall
{ // most values will not be here, instead fillers (#) will be placed

  int valueA = x; //power levels 
  int valueB = y;
  
    if (SensorValue[Jumper1] == 0) // im guessing this is for the different autonomous? 
    {
      MovingFoward = false; //because this will use the claw, thought it would be easier to code if i do this
      { // move foward untill you reach that cube
          
        	SensorValue[EncoderFrontRight] = 0;
          while(SensorValue[EncoderFrontRight] <= # )
          {
            RightEdge(valueA);
          }
          cubeIntakeClosing = true;
          
