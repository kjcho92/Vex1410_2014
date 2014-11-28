#pragma config(Sensor, in1,    armPotentiometerLeft, sensorPotentiometer)
#pragma config(Sensor, in2,    armPotentiometerRight, sensorPotentiometer)
#pragma config(Sensor, in3,    GyroDown,       sensorNone)
#pragma config(Sensor, in4,    GyroUp,         sensorNone)
#pragma config(Sensor, in5,    CubeIntakePotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  EncoderFrontLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoderFrontRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  EncoderBackLeft, sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  EncoderBackRight, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, Jumper1,        sensorDigitalIn)
#pragma config(Sensor, dgtl12, Jumper2,        sensorDigitalIn)
#pragma config(Motor,  port1,           CrayonIntake,  tmotorVex393, openLoop)
#pragma config(Motor,  port2,           FrontLeft,     tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port3,           FrontRight,    tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port4,           BackRight,     tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port5,           BackLeft,      tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           LeftLift1,     tmotorVex393, openLoop)
#pragma config(Motor,  port7,           LeftLift2,     tmotorVex393, openLoop)
#pragma config(Motor,  port8,           RightLift1,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           RightLift2,    tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          CubeIntake,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//int gyrotestval;
//int jumper1testval;
//int jumper2testval;

//int filterjoystick (int joystick);

int DefaultLeftValue = 0;
int DefaultRightValue = 0;

////////////////////////////////////////////////////
/// Autonomous mode
void ForBack(int power, int distance);
void LeftRight(int power, int distance);
void StopMoving();
void MoveDiagonal(int power, int distance);
void Rotate(int power);
void PickUpSkyrise(int duration);
void ReleaseSkyrise(int duration);
void Claw(int power);
void StopLift();
void AdjustAutoLift(int height);
void LiftUp(float power, int left, int right);
void LiftDown(float power, int left, int right);
void GyroRotate(int angle);
////////////////////////////////////////////////////


////////////////////////////////////////////////////
/// Drive mode
int LiftAdjust(int thisP, int otherP);
int GetLeftPower(float leftPot, float rightPot);
int GetRightPower(float leftPot, float rightPot);

int ReverseIfNeeded(int power);

float GetLeftValue();
float GetRightValue();
void AdjustLift();

bool MovingForward = true;
////////////////////////////////////////////////////


typedef enumWord {
    Adjusted = 0,
		Up = 1,
    Down = 2
} ACTIONS;

ACTIONS PreviousAction;

/////////////////////////////////////////////////////////////////////////////////////////
//																																										 //
//                          Pre-Autonomous Functions																	 //
//																																										 //
// You may want to perform some actions before the competition starts. Do them in the	 //
// following function.																																 //
//																																										 //
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  //bStopTasksBetweenModes = true;

	//Completely clear out any previous sensor readings by setting the port to "sensorNone"
 	//SensorType[GyroDown] = sensorNone;
	//SensorType[GyroUp] = sensorNone;
 	//wait1Msec(1000);
 	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 	SensorType[GyroDown] = sensorGyro;
 	SensorType[GyroUp] = sensorGyro;
 	wait1Msec(1000);

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

////////////////////////////////////////////////////////////////////////////////////////////////
//																																														//
//                                 Autonomous Task																						//
//																																														//
// This task is used to control your robot during the autonomous phase of a VEX Competition.	//
// You must modify the code to add your own robot specific commands here.											//
//																																														//
////////////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
		ClearTimer(T3);

		int valM = 70;
		int valS = 150;
		int defaultDelay = 100;
		// BLUE: 750 ?
		int defaultGyroRotate = -850;
		// int rotateV = 1150;

		//static bool adjacent = false; //true if square next to drivers

			if (SensorValue[Jumper2] == 1) //run the first autonomous
			{
					// move Diagonal to put the cube
					// was 130
					MoveDiagonal(valM, 140);
					wait1Msec (defaultDelay);

					// move forward to the autoload
					// -33 for BLUE
					ForBack(-valM, -45);
					wait1Msec (defaultDelay);

					// LeftRight(valM, 1);
					// wait1Msec (defaultDelay);

					// rotate to face the autoload
					// 330 for BLUE
					GyroRotate(335);
					wait1Msec (defaultDelay * 2);

					// move forward to the autoload
					// -33 for BLUE

					// pick up skyrise
					PickUpSkyrise(650);

					// Lift up
					int moveUpTo = 420;
					int savedLeftValue = SensorValue[armPotentiometerLeft];
	 				int savedRightValue = SensorValue[armPotentiometerRight];
					LiftUp(-127, savedLeftValue + moveUpTo, savedRightValue + moveUpTo); // Lift up
					wait1Msec(300);

					// rotate to the skyrise base
					GyroRotate(defaultGyroRotate);
					wait1Msec(300);

					// lift down to the base
					LiftDown(127, savedLeftValue, savedRightValue); //Lift our 	robot down
					wait1Msec(defaultDelay);

					ReleaseSkyrise(550);
					// wait1Msec(defaultDelay);


					writeDebugStream("T3 - 0: %d	", time1[T3]);

					//////////////////////////////////////////////////////////////
					///2nd round
					//////////////////////////////////////////////////////////////
					for (int i = 1; i <= 1; i++)
					{
						GyroRotate(-defaultGyroRotate);
						wait1Msec (defaultDelay * 2);

						PickUpSkyrise(650);
						// wait1Msec(500);

						int differenceMoveUp = moveUpTo + (60 * i);
						int leftHeight = savedLeftValue + differenceMoveUp;
						int rightHeight = savedRightValue + differenceMoveUp;
						LiftUp(-127, leftHeight, rightHeight); //Lift up
						wait1Msec(300);

											// rotate to the skyrise base

						GyroRotate(defaultGyroRotate);
						wait1Msec(300);

						LiftDown(30, leftHeight - 270, rightHeight - 270); //Lift our 	robot down
						wait1Msec(defaultDelay);

						ReleaseSkyrise(100);

						// lift down to the base
						LiftDown(127, savedLeftValue, savedRightValue); //Lift our 	robot down


						writeDebugStreamLine("T3 - %d: %d	", i, time1[T3]);
					}
			}


}

/////////////////////////////////////////////////////////////////////////////////////////////////
//																																														 //
//                                 User Control Task																					 //
//																																														 //
// This task is used to control your robot during the user control phase of a VEX Competition. //
// You must modify the code to add your own robot specific commands here.											 //
//																																														 //
/////////////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	bool armPotentiometerUsed = true;

	bool cubeIntakeClosing = false;
	bool crayonIntakeClosing = false;

  const int power7 = 50;
	 //DefaultLeftValue = SensorValue[armPotentiometerLeft];
	 //DefaultRightValue = SensorValue[armPotentiometerRight];

	// DefaultLeftValue = 1864;
	// DefaultRightValue = 1902;
  DefaultLeftValue = 1700;
	DefaultRightValue = 1753;


	while (true)
	{
        // reverse when moving backward
     if (vexRT[Btn7U] == 1) MovingForward = true;
     else if(vexRT[Btn7D] == 1) MovingForward = false;


     int filtered2 = vexRT[Ch2];
     int filtered4 = vexRT[Ch4];

		// Button7
    filtered2 = ReverseIfNeeded(filtered2);
        // filtered4 = ReverseIfNeeded(filtered4);
    int power7r = ReverseIfNeeded(power7);

    int btn7r = vexRT[Btn7R];
    int btn7l = vexRT[Btn7L];

		//standard drive motor block
		motor[FrontLeft] = filtered2 + filtered4 + btn7r * power7r - btn7l * power7r;
		motor[FrontRight] = filtered2 - filtered4 - btn7r * power7r + btn7l * power7r;
		motor[BackRight] = filtered2 - filtered4 + btn7r * power7r - btn7l * power7r;
		motor[BackLeft] = filtered2 + filtered4 - btn7r * power7r + btn7l * power7r;

		float leftPot = GetLeftValue();
  	float rightPot = GetRightValue();

  	if (leftPot <= 0 || rightPot <= 0)
  	{
			armPotentiometerUsed = false;
		}
		else
		{
			armPotentiometerUsed = true;
		}

		int lp = 127;
		int rp = 127;

		if (armPotentiometerUsed == true)
		{
			lp = GetLeftPower(leftPot, rightPot);
			rp = GetRightPower(leftPot, rightPot);
		}

		if (lp != 0 && rp != 0)
		{
		    writeDebugStream("lp: %d	", lp);
		    writeDebugStreamLine("rp: %d", rp);
	    }


	  int btn8r = vexRT[Btn8R];
	  int btn8l = vexRT[Btn8L];

    if (btn8r + btn8l > 0)
    {
			SensorType[GyroUp] = 0;
    }

	  // lp = 127;
	  // rp = 127;

	  // int temp = lp;
	  // lp = rp;
	  // rp = temp;
		motor[LeftLift1] =  (vexRT[Btn8D] - vexRT[Btn8U]) * lp + btn8l * 25 - btn8r * 25;
		motor[LeftLift2] =  (vexRT[Btn8D] - vexRT[Btn8U]) * lp + btn8l * 25 - btn8r * 25;
		motor[RightLift1] = (vexRT[Btn8D] - vexRT[Btn8U]) * rp + btn8r * 25 - btn8l * 25;
		motor[RightLift2] = (vexRT[Btn8D] - vexRT[Btn8U]) * rp + btn8r * 25 - btn8l * 25;

        // adjust when we stops
		if (armPotentiometerUsed == true)
		{
			// AdjustLift();
		}


		int btn5u = vexRT[Btn5U];
		int btn5d = vexRT[Btn5D];

		if (btn5u == 1)
		{
			cubeIntakeClosing = false;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5d == 1)
		{
			cubeIntakeClosing = true;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5u == 0 && btn5d == 0 && cubeIntakeClosing)
		{
				motor[CubeIntake] = -20;
		}
		else if (btn5u == 0 && btn5d == 0 && !cubeIntakeClosing)
		{
				motor[CubeIntake] = 0;
		}


		int btn6u = vexRT[Btn6U];
		int btn6d = vexRT[Btn6D];

		if (btn6d == 1)
		{
			crayonIntakeClosing = false;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 1)
		{
			crayonIntakeClosing = true;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 0 && btn6d == 0 && crayonIntakeClosing)
		{
				motor[CrayonIntake] = 25;
		}
		else if (btn6u == 0 && btn6d == 0 && !crayonIntakeClosing)
		{
				motor[CrayonIntake] = 0;
		}
	}
}

int ReverseIfNeeded(int power)
{
    return MovingForward ? power : -power;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// GetValues
/// Get Potentiometer values
/////////////////////////////////////////////////////////////////////////////////////////////
float GetLeftValue()
{
	int sValue = SensorValue[armPotentiometerLeft];
	float value = (sValue * 1) - DefaultLeftValue;
	if (value <0) value = 0;

		return value;
}

float GetRightValue()
{
		int sValue = SensorValue[armPotentiometerRight];
		float value =  sValue - DefaultRightValue;
		if (value <0) value = 0;

		return value;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// GetPowers
/// Calculate the power for lifts based on the sensor values and the current actions
/////////////////////////////////////////////////////////////////////////////////////////////
int GetLeftPower(float leftPot, float rightPot)
{
	const int fullPower = 127;
	const int fullPower_Down = 100;
	const float delta = 0.6;
	const float delta_Down = 0.6;

    // No buttons pressed
	if (vexRT[Btn8D] == 0 && vexRT[Btn8U] == 0) return 0;

    // On moving up
    if (vexRT[Btn8U] == 1)
	{
        // moving up
        PreviousAction = Up;

        // if we just started moving, we need full power.
		if (leftPot <= 500)
		{
			return fullPower;
		}

        // when the right lift is higher, we need full power for the left
		if (leftPot <= rightPot)
		{
			return fullPower;
		}
		else
		{
            // when the left is higher, we need to slow down the left
            // the delta is a magic number. we need even less power for left while the other one is catching up
			float offset = (rightPot / leftPot) * 100 * delta;
			int power = (fullPower * offset) / 100;
			return power;
		}
	}
    // On moving down
	else if (vexRT[Btn8D] == 1)
	{
        // moving down
        PreviousAction = Down;

        // if the current is higher than the other, need full power. but we still don't need 127.
		if (leftPot >= rightPot)
		{
			if (leftPot <= 400)
			{
				// need to slow down?;
			}
			return fullPower_Down;
		}
		else
		{
			float offset = (leftPot / rightPot) * delta_Down;
			int power = (fullPower_Down * offset);
			return power;
		}
	}

	return 0;
}

int GetRightPower(float leftPot, float rightPot)
{
	const int fullPower = 127;
	const int fullPower_Down = 100;
	const float delta = 0.6;
	const float delta_Down = 0.6;

	if (vexRT[Btn8D] == 0 && vexRT[Btn8U] == 0) return 0;

	if (vexRT[Btn8U] == 1)
	{
		PreviousAction = Up;
		if (rightPot <= 500)
		{
			return fullPower;
		}

		if (leftPot >= rightPot)
		{
			return fullPower;
		}
		else
		{
			float offset = (leftPot / rightPot) * 100 * delta;
			int power = (fullPower * offset) / 100;
			return power;
		}
	}
	else if (vexRT[Btn8D] == 1)
	{
    PreviousAction = Down;
		if (leftPot <= rightPot)
		{
			if (rightPot <= 400)
			{
                // need to slow down
			}
			return fullPower_Down;
		}
		else
		{
			float offset = (rightPot / leftPot) * delta_Down;
			int power = (fullPower_Down * offset);
			return power;
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// Adjust lifts
/// Adjust the lifts whenever we release the buttons.
/////////////////////////////////////////////////////////////////////////////////////////////
void AdjustLift()
{
    // any buttons pressed? if so, returns;
	if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

    // already adjusted? if so, returns;
	if (PreviousAction == Adjusted) return;

	motor[LeftLift1] = 0;
	motor[LeftLift2] = 0;

	motor[RightLift1] = 0;
	motor[RightLift2] = 0;

	float leftPot = GetLeftValue();
  float rightPot = GetRightValue();

    // skip adjustment, if the lifts are too low or too higt.
  if (leftPot <= 100 || rightPot <=100 || leftPot >= 1500 || rightPot >= 1500)
  {
  	return;
  }

    // offset = tolerance
  int offset = 10;
  int offset_Down = 5;

    // power values that we need for up and down
	int power = -33;
	int power_Down = -35; // adjust by moving up even for down. found it is more stable. use positive values to adjust by moving down.

    if (leftPot == rightPot) return;

    ClearTimer(T1);


    // in case of moving up
    if (PreviousAction == Up)
    {
		if (leftPot > rightPot)
		{
            // when the left is higher, move up the right until the right + offset is not lower than the left.
			while (leftPot > rightPot + offset)
			{
					if (time1[T1] > 1000) return;

				  if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;
					motor[RightLift1] = motor[RightLift2] = power;

					leftPot = GetLeftValue();
			    rightPot = GetRightValue();
			}
		}
		else if (leftPot < rightPot)
		{
			while (leftPot + offset < rightPot)
			{
				if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

					motor[LeftLift1] = motor[LeftLift2] = power;

					leftPot = GetLeftValue();
    			rightPot = GetRightValue();
			}
		}
	}
	else if (PreviousAction == Down)
	{
        // ok, for down. even more interesting
        // let's wait for 1.3 secs. (until the lift completely stops)
	    // ClearTimer(T1);
			// while (time1[T1] < 1300){}

    leftPot = GetLeftValue();
    rightPot = GetRightValue();

		if (leftPot > rightPot)
		{
			while (leftPot  > rightPot + offset_Down)
			{
				if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

				 motor[RightLift1] = motor[RightLift2] = power_Down;

                // uncommend the block below if we want to adjust by moving down.
                // then we might need the delays
                // motor[LeftLift1] = power_Down;
				// motor[LEftLift2] = power_Down;

				// ClearTimer(T1);
				// while (time1[T1] < 300){}

				 leftPot = GetLeftValue();
				 rightPot = GetRightValue();
			}
		}
		else if (leftPot < rightPot)
		{
			while (leftPot + offset_Down < rightPot)
			{
				 if (time1[T1] > 1000) return;

         if (vexRT[Btn8D] != 0 || vexRT[Btn8U] != 0) return;

				 motor[LeftLift1] = motor[LeftLift2] = power_Down;

                // uncommend the block below if we want to adjust by moving down.
				// motor[RightLift1] = power_Down;
				// motor[RightLift2] = power_Down;



				 leftPot = GetLeftValue();
				 rightPot = GetRightValue();
			}
		}
	}

	motor[LeftLift1] = 0;
	motor[LeftLift2] = 0;
	motor[RightLift1] = 0;
	motor[RightLift2] = 0;

    // finish the adjustment
    PreviousAction = Adjusted;
}


int LiftAdjust (int thisP, int otherP)
{
	const int tolerance = 10;
	int scaletolerance = ((thisP + otherP) / 2 - 1550) / 200;
	if (thisP > otherP + (tolerance - scaletolerance))
	{
		return 1 + (1 * (thisP - otherP)) / 1;
	}
	else if (thisP + (tolerance - scaletolerance) < otherP)
	{
		return -1 + (1 * (thisP - otherP)) / 1;
	}
	else
	{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                               Functions Below
//
//
/////////////////////////////////////////////////////////////////////////////////////////////
void ForBack(int power, int distance)
{
	SensorValue[EncoderFrontLeft] = 0 ;
	while(SensorValue[EncoderFrontLeft] > distance)
	{
		motor[FrontLeft] = power;
		motor[FrontRight] = power;
		motor[BackRight] = power;
		motor[BackLeft] = power;
	}

	StopMoving();
}

void StopMoving()
{
		motor[FrontLeft] = 0;
		motor[FrontRight] = 0;
		motor[BackRight] = 0;
		motor[BackLeft] = 0;
}

void MoveDiagonal(int power, int distance)
{
	if (power > 0) // When power is 0, we should stop immediately
	{
		if (SensorValue[Jumper1] == 0) //Jumper 1 == 0 means that we are red. Otherwise, it means that we are blue
		{
			SensorValue[EncoderFrontRight] = 0;
			while(SensorValue[EncoderFrontRight] <= distance)
			{
				motor[FrontRight] = -power;
				motor[BackLeft] = -power;
			}
		}
		else
		{
			SensorValue[EncoderFrontLeft] = 0;
			while(SensorValue[EncoderFrontLeft] >= -distance)
			{
				motor[FrontLeft] = -power;
				motor[BackRight] = -power;
			}
		}
	}

	StopMoving();
}

void LeftRight(int power, int distance)
{
	if (power != 0) // When power is 0, we should stop immediately
	{
		if (SensorValue[Jumper1] == 0) //Jumper 1 == 0 means that we are red. Otherwise, it means that we are blue
		{ // Red
			power = -power;
			SensorValue[EncoderFrontRight] = 0;
			while(SensorValue[EncoderFrontRight] > -distance)
			{
		   	motor[FrontLeft] = power;
		    motor[FrontRight] = -power;
		    motor[BackRight] = power;
		    motor[BackLeft] = -power;
		   }
		}
		else
		{
			SensorValue[EncoderFrontRight] = 0;
			while(SensorValue[EncoderFrontRight] < distance)
			{
		   	motor[FrontLeft] = power;
		    motor[FrontRight] = -power;
		    motor[BackRight] = power;
		    motor[BackLeft] = -power;
		   }
		}
	}

	StopMoving();
}

void Rotate(int power)
{
//	if (SensorValue[Jumper1] == 0)
//	{
//		power = -power;
//	}
    motor[FrontLeft] = power;
    motor[FrontRight] = -power;
    motor[BackRight] = -power;
    motor[BackLeft] = power;
}

void GyroRotate(int angle)
{
	SensorValue[GyroDown] = 0;
	int power = 50;

	if (SensorValue[Jumper1] == 1)
	{	// Blue
		angle = -angle;
		power = -power;
	}

	if (angle > 0)
	{
		while (SensorValue[GyroDown] < angle)
		{
			Rotate(power);
		}
	}
	else
	{
		while (SensorValue[GyroDown] > angle)
		{
			Rotate(-power);
		}
	}

	StopMoving();
}

void PickUpSkyrise(int duration)
{
		Claw(127);
		wait1Msec(duration);
		Claw(30);
}

void ReleaseSkyrise(int duration)
{
		Claw(-127);
		wait1Msec(duration);
		Claw(0);
}

void Claw(int power)
{
    motor[CrayonIntake] = power;
}

void StopLift()
{
		motor[LeftLift1] = 0;
    motor[RightLift1] = 0;
		motor[LeftLift2] = 0;
    motor[RightLift2] = 0;
}

void AdjustAutoLift(int height)
{
		float power = -100;

		while (SensorValue[armPotentiometerLeft] < height)
		{
			  motor[LeftLift1] = power;
		    motor[LeftLift2] = power;
		}

		motor[LeftLift1] = 0;
		motor[LeftLift2] = 0;


		//while (SensorValue[armPotentiometerRight] < height)
		//{
		//	  motor[RightLift1] = power;
		//    motor[RightLift2] = power;
		//}

		//motor[RightLift1] = 0;
		//motor[RightLift2] = 0;

}

void LiftUp(float power, int left, int right)
{
		float lp = power;
		float rp = power * 0.75;

		while(SensorValue[armPotentiometerLeft] < left
				&& SensorValue[armPotentiometerRight] < right)
		{
		    motor[LeftLift1] = lp;
		    motor[RightLift1] = rp;
		    motor[LeftLift2] = lp;
		    motor[RightLift2] = rp;
		}

		StopLift();
	//	AdjustAutoLift(SensorValue[armPotentiometerRight]);
}

void LiftDown(float power, int left, int right)
{
	float lp = power;
	float rp = power * 0.8;

		while(SensorValue[armPotentiometerLeft] > left
				&& SensorValue[armPotentiometerRight] > right)
		{
		    motor[LeftLift1] = lp;
		    motor[RightLift1] = rp;
		    motor[LeftLift2] = lp;
		    motor[RightLift2] = rp;
		}

		StopLift();
}
