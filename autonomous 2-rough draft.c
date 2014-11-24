task autonomous() // this code is for blue team-- the robot starts in the non- skyrise tile and is facing opposite of the wall
{ // most values will not be here, instead fillers (#) will be placed

  int valueA = x; //power levels 
  int valueB = y;
  
    if (SensorValue[Jumper2] == 0) // im guessing this is for the different autonomous? 
    {
      MovingFoward = false; //because this will use the claw, thought it would be easier to code if i do this
      { // move foward untill you reach that cube
          
        	SensorValue[EncoderFrontRight] = 0;
          while(SensorValue[EncoderFrontRight] <= # )
          {
            RightEdge(valueA);
          }
          
          RightEdge(0);
          wait1Msec (defaultDelay);
          
          cubeIntakeClosing = true; //not sure how this works
          
          SensorValue[EncoderFrontRight] = 0;  //move back
          while(SensorValue[EncoderFrontRight] <= -# )
          {
            ForBack(-valueA);
          }
          
          ForBack(0);
          wait1Msec (defaultDelay);
          
          int moveUpTo = #;
          int savedLeftValue = SensorValue[armPotentiometerLeft];
          int savedRightValue = SensorValue[armPotentiometerRight];
          while(SensorValue[armPotentiometerLeft] < savedLeftValue + moveUpTo
            && SensorValue[armPotentiometerRight] < savedRightValue + moveUpTo)
          {
            Lift(-#); //Lift goes up
          }
          Lift (0);
          wait1Msec(#);
          
          GyroRotate( # );
          wait1Msec(#);
          
          while(SensorValue[armPotentiometerLeft] < savedLeftValue + moveUpTo
            && SensorValue[armPotentiometerRight] < savedRightValue + moveUpTo)
          {
            Lift(#); //Lift goes up
          }
          Lift (0);
          wait1Msec(#); // add less delay so claw releases whilemoving down
          
          cubeIntakeClosing = false;
