#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotentiometerLeft, sensorPotentiometer)
#pragma config(Sensor, in2,    armPotentiometerRight, sensorPotentiometer)
#pragma config(Sensor, in3,    GyroDown,       sensorNone)
#pragma config(Sensor, in5,    CubeIntakePotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl7,  SonarSensor,    sensorSONAR_mm)
#pragma config(Sensor, dgtl11, Jumper1,        sensorDigitalIn)
#pragma config(Sensor, dgtl12, Jumper2,        sensorDigitalIn)
#pragma config(Sensor, I2C_1,  FrontLeftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  FrontRightEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  RightLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  LeftLiftEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           CrayonIntake,  tmotorVex393, openLoop)
#pragma config(Motor,  port2,           FrontLeft,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port3,           FrontRight,    tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port4,           BackRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port5,           BackLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port6,           RightLift1,    tmotorVex393, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port7,           RightLift2,    tmotorVex393, openLoop)
#pragma config(Motor,  port8,           LeftLift1,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           LeftLift2,     tmotorVex393, openLoop, reversed, encoder, encoderPort, I2C_4, 1000)
#pragma config(Motor,  port10,          CubeIntake,    tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

////////////////////////////////////////////////////
/// Autonomous mode - Using
void SonarRotate(int distance, int power);
void StopMoving();
void EncoderRotate(int power);
void EncoderRotateSmart(int power);
void EncoderLiftUp(int power, int leftTarget, int rightTarget);
void EncoderLiftDown(int power, int leftTarget, int rightTarget);
void Claw(int power);
void PickUpSkyrise(int duration);
void ReleaseSkyrise(int duration);
void StopLift();
void AdjustAutoLiftUp(int originalPower);
void AdjustLiftUpSmart(int originalPower);
int AdjustBatteryLevel(int OriginalPower);

////////////////////////////////////////////////////
/// Drive mode
int GetLeftPower(int movingUp, int movingDown);
int GetRightPower(int movingUp, int movingDown);
int AdjustLiftPower(int pot1, int pot2);
int ReverseIfNeeded(int power);

bool MovingForward = true;
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
 	// SensorType[GyroDown] = sensorNone;

 	// wait1Msec(1000);
 	//Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 	// SensorType[GyroDown] = sensorGyro;

 	wait1Msec(2000);

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
		int sshortDelay = 25;
		int shortDelay = 50;
		int defaultDelay = 100;
		int offset = 150;

		//////////////////////
		/// RED RED RED RED RED
		int sonarRotationOriginalPower = 48;
		int gyroRotationOriginalPower = 43;

		/*if (SensorValue[Jumper1] == 1)
		{ 
			//////////////////////
			/// BLUE BLUE BLUE BLUE
			sonarRotationOriginalPower = 48;
			gyroRotationOriginalPower = 43;
		}*/
		
		ClearTimer(T3);
		
						
		for (int i = 0; i <= 6; i++)
		{
			// pick up skyrise
			PickUpSkyrise(700);
			wait1Msec (defaultDelay);
	
			nMotorEncoder(LeftLift2) = 0;
			nMotorEncoder(RightLift1) = 0;
	
				
			switch (i)
			{
				case 0:
				case 1: offset = 100; break;
				case 2: offset = 150; break;
				case 3: offset = 300; break;
				case 4: offset = 400; break;
				case 5: offset = 520; break;
				case 6: offset = 680; break;
			}
			
			
			int left = -1550 - (offset * i);
			int right = -1550 - (offset * i);
			
			EncoderLiftUp(-127, left, right); // Lift up
	 		wait1Msec(defaultDelay);
	
			nMotorEncoder(FrontRight) = 0;
			nMotorEncoder(FrontLeft) = 0;
	
			// rotate to the skyrise base
			int sonarRotationPower = AdjustBatteryLevel(sonarRotationOriginalPower);
			SonarRotate(300, sonarRotationPower);
			wait1Msec (defaultDelay);
		
			int heightToDrop = 120;
			if (0 == i)
			{
				left = 0;
				right = 0;
				heightToDrop = 0;
			}
			else if (1 == i)
			{
				heightToDrop = 200;
			}
			
			EncoderLiftDown(50, left + heightToDrop , right + heightToDrop); //Lift down
			
			wait1Msec (defaultDelay);
	
			ReleaseSkyrise(500);
			writeDebugStreamLine("T3 - %d: %d	", i, time1[T3]);

			wait1Msec(shortDelay);
	
			EncoderLiftDown(60, 0, 0); //Lift down
			wait1Msec(sshortDelay);
	
	//		gyroRotationAngle = SensorValue[GyroDown];
	
	
	
			// rotate to the autoload

			int gyroRotationPower = AdjustBatteryLevel(gyroRotationOriginalPower);
	
			EncoderRotate(gyroRotationPower);
//			wait1Msec(defaultDelay);
	
		}
}

int AdjustBatteryLevel(int OriginalPower)
{
	float AdjustBatteryLevel = nImmediateBatteryLevel;
  float BatteryOffset =	6000 / AdjustBatteryLevel;
  int WantedPower = OriginalPower * BatteryOffset;


	writeDebugStreamLine("(AjustBattery) BatterLevel: %d - OriginalPower: %d - WantedPower: %d", AdjustBatteryLevel, OriginalPower, WantedPower);


  return WantedPower;
}


void EncoderLiftUp(int power, int leftTarget, int rightTarget)
{
	while(nMotorEncoder(LeftLift2) > leftTarget
				|| nMotorEncoder(RightLift1) > rightTarget)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

//			writeDebugStreamLine("(LiftUp) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();
		wait1Msec(100);
		
		int adjustPower = 38;
		AdjustAutoLiftUp(adjustPower);
}

void EncoderLiftDown(int power, int leftTarget, int rightTarget)
{
	while(nMotorEncoder(LeftLift2) < leftTarget
				|| nMotorEncoder(RightLift1) < rightTarget)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();
}

bool PickUpCube(int value,int power) //pick cube up and stuff
{
	  ClearTimer(T2);
		if (SensorValue[CubeIntakePotentiometer] >= value || SensorValue[CubeIntakePotentiometer] < 300)
		{
			return true;
		}

		while(SensorValue[CubeIntakePotentiometer] < value)
		{
		    motor[CubeIntake] = -power;
		    if (time1[T2] > 1000)
		    {
		    	motor[CubeIntake] = 0;
		    	return false;
		    }
		}

		motor[CubeIntake] = 0;
		return true;
}

void ReleaseCube(int value,int power)
{
		if (SensorValue[CubeIntakePotentiometer] <= value)
		{
			return;
		}

		while(SensorValue[CubeIntakePotentiometer] > value)
		{
		    motor[CubeIntake] = power;
		}

		motor[CubeIntake] = 0;
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
	bool cubeIntakeTaking = false;
	bool crayonIntakeTaking = false;

	bool adjustIfWant = false;

	while (true)
	{
		// ClearTimer(T2);
		// while (time1[T2] < 100){}
		
		if (vexRT[Btn7U] == 1)
		{
		 // reverse direction
		   MovingForward = !MovingForward;
		}
		
		if (vexRT[Btn7U] == 1 && -1650 > nMotorEncoder(LeftLift2) && nMotorEncoder(LeftLift2) > -5600)
		{
    	// adjust lift only if it meets a certain condition
			int adjustPower = 45;
    	AdjustLiftUpSmart(adjustPower);
		}
		
		int power2 = vexRT[Ch2]; // forward, backward
		int power4 = vexRT[Ch4]; // rotate
		int power7 = 60; // shift
		
		power2 = ReverseIfNeeded(power2);
		power7 = ReverseIfNeeded(power7);
		
		int btn7r = vexRT[Btn7R]; // shift
		int btn7l = vexRT[Btn7L]; // shift
		
		//standard drive motor block
		motor[FrontLeft] = power2 + power4 + btn7r * power7 - btn7l * power7;
		motor[FrontRight] = power2 - power4 - btn7r * power7 + btn7l * power7;
		motor[BackRight] = power2 - power4 + btn7r * power7 - btn7l * power7;
		motor[BackLeft] = power2 + power4 - btn7r * power7 + btn7l * power7;

		if (nMotorEncoder(LeftLift2) >= 0 || nMotorEncoder(RightLift1) >= 0)
		{
			// Assume the lift is completely folded
			nMotorEncoder(LeftLift2) = nMotorEncoder(RightLift1) = 0;
		}
	  int btn8r = vexRT[Btn8R]; // lift adjust
	  int btn8l = vexRT[Btn8L]; // lift adjust

	  int btn8d = vexRT[Btn8D]; // lift down
	  int btn8u = vexRT[Btn8U]; // lift up

	  if (nMotorEncoder(LeftLift2) < -5680 || nMotorEncoder(RightLift1) < -5680)
		{ 
			  // stop when the lift is too high
				btn8u = 0;
		}
				
		int lp = 127;
		int rp = 127;

		if (adjustIfWant == true)
		{
			lp = GetLeftPower(btn8u, btn8d);
			rp = GetRightPower(btn8u, btn8d);
	
			if (lp + rp > 0)
			{
				writeDebugStreamLine("lp:rp => (%d : %d)", lp, rp);
			}
		}
		  
		motor[LeftLift1] =  (btn8d - btn8u) * lp + btn8l * 25 - btn8r * 25;
		motor[LeftLift2] =  (btn8d - btn8u) * lp + btn8l * 25 - btn8r * 25;
		motor[RightLift1] = (btn8d - btn8u) * rp + btn8r * 25 - btn8l * 25;
		motor[RightLift2] = (btn8d - btn8u) * rp + btn8r * 25 - btn8l * 25;
	
    if (btn8d + btn8u + btn8r + btn8l == 0)
    {
			lp = 0;
			rp = 0;
	
			motor[LeftLift1] = motor[LeftLift2] = lp;
			motor[RightLift1] = motor[RightLift2] = rp;
		}

		int btn5u = vexRT[Btn5U]; // take cube
		int btn5d = vexRT[Btn5D]; // release cube

		if (btn5d == 1)
		{
			cubeIntakeTaking = false;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5u == 1)
		{
			cubeIntakeTaking = true;
			motor[CubeIntake] = (btn5u - btn5d) * 127;
		}
		else if (btn5u == 0 && btn5d == 0 && cubeIntakeTaking)
		{
				motor[CubeIntake] = -40;
		}
		else if (btn5u == 0 && btn5d == 0 && !cubeIntakeTaking)
		{
				motor[CubeIntake] = 0;
		}

		int btn6u = vexRT[Btn6U]; // take skyrise
		int btn6d = vexRT[Btn6D]; // release skyrise

		if (btn6d == 1)
		{
			crayonIntakeTaking = false;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 1)
		{
			crayonIntakeTaking = true;
			motor[CrayonIntake] = (btn6u - btn6d) * 127;
		}
		else if (btn6u == 0 && btn6d == 0 && crayonIntakeTaking)
		{
				motor[CrayonIntake] = 30;
		}
		else if (btn6u == 0 && btn6d == 0 && !crayonIntakeTaking)
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
/// GetPowers
/// Calculate the power for lifts based on the sensor values
/////////////////////////////////////////////////////////////////////////////////////////////
int GetLeftPower(int movingUp, int movingDown)
{
	// No buttons pressed
	if (movingUp + movingDown == 0) return 0;
	
	const int fullPowerUp = 127;
	const int fullPowerDown = 127;
//	const float delta = 0.6;
//	const float delta_Down = 0.6;

	int leftPot = nMotorEncoder(LeftLift2) * -1;
	int rightPot = nMotorEncoder(RightLift1) * -1;
    // On moving up
  if (movingUp == 1)
	{
	  // when started moving, give full power.
		if (1650 > leftPot)
		{
			return fullPowerUp;
		}

		// when the right is higher, give full power
		if (leftPot <= rightPot)
		{
			return fullPowerUp;
		}
		else
		{
      // when the left is higher, slow down
			return AdjustLiftPower(rightPot, leftPot);
		}
	}
    // On moving down
	else if (movingDown == 1)
	{
    // when the left is higher, give full power
		if (leftPot >= rightPot)
		{
			return fullPowerDown;
		}
		else
		{
			// when the right is higher, slow down
     	return AdjustLiftPower(leftPot, rightPot);
		}
	}

	return 0;
}

int GetRightPower(int movingUp, int movingDown)
{
	// No buttons pressed
	if (movingUp + movingDown == 0) return 0;
	
	const int fullPowerUp = 127;
	const int fullPowerDown = 127;

	int leftPot = nMotorEncoder(LeftLift2) * -1;
	int rightPot = nMotorEncoder(RightLift1) * -1;

  if (movingUp == 1)
	{
	  // when started moving, give full power.
		if (1650 > leftPot)
		{
			return fullPowerUp;
		}

		// when the left is higher, give full power
		if (rightPot <= leftPot)
		{
			return fullPowerUp;
		}
		else
		{
      // when the right is higher, slow down
     	return AdjustLiftPower(leftPot, rightPot);
		}
	}
    // On moving down
	else if (movingDown == 1)
	{
    // when the right is higher, give full power
		if (rightPot >= leftPot)
		{
			return fullPowerDown;
		}
		else
		{
			// when the left is higher, slow down
			return AdjustLiftPower(rightPot, leftPot);
		}
	}

	return 0;
}

int AdjustLiftPower(int pot1, int pot2)
{
	const int fullPower = 127;

	 float offset = (pot1 / pot2) * 100;
	 int power = (fullPower * offset) / 100;
	 return power;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                               Functions Below
//
//
/////////////////////////////////////////////////////////////////////////////////////////////
void Rotate(int power)
{
    motor[FrontLeft] = power;
    motor[FrontRight] = -power;
    motor[BackRight] = -power;
    motor[BackLeft] = power;
}

void StopMoving()
{
		motor[FrontLeft] = 0;
		motor[FrontRight] = 0;
		motor[BackRight] = 0;
		motor[BackLeft] = 0;
}

void SonarRotate(int distance, int power)
{
	if (distance <= 0) return;

	if (SensorValue[Jumper1] == 1)
	{ // RED
		power = -power;
		// power = -30;
		while (SensorValue[SonarSensor] > distance)
		{
			Rotate(power);
		}
	}

	StopMoving();
//	return SensorValue[GyroDown];
}


void EncoderRotate(int power)
{
	int left = nMotorEncoder(FrontLeft);

	left = left / 8;
	if (power <= 0) return;

	if (left < 0)
	{ // RED
		while (nMotorEncoder(FrontLeft) < left)
		{
			Rotate(power);
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

void AdjustAutoLiftUp(int originalPower)
{
		int power = AdjustBatteryLevel(originalPower) * -1;

		if (nMotorEncoder(LeftLift2) > nMotorEncoder(RightLift1))
		{
			while(nMotorEncoder(LeftLift2)> nMotorEncoder(RightLift1))
			{
					if (vexRT[Btn8D] + vexRT[Btn8U] + vexRT[Btn8R] + vexRT[Btn8L] > 0) 
					{ // return if a button is pressed
						break;
					}

			    motor[LeftLift1] = power;
			    motor[LeftLift2] = power;
	//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
			}
			
			StopLift();
	}
	else
	{
		while(nMotorEncoder(RightLift1) > nMotorEncoder(LeftLift2))
		{
				if (vexRT[Btn8D] + vexRT[Btn8U] + vexRT[Btn8R] + vexRT[Btn8L] > 0)
				{ // return if a button is pressed
						break;
				}
					
		    motor[RightLift1] = power;
		    motor[RightLift2] = power;
//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}
		
		StopLift();
	}
}

void EncoderRotateSmart(int power)
{
	if (power <= 0) return;

	int current = nMotorEncoder(FrontLeft);
	int offset = 0;
	if (current < 0)
	{ // RED
		while (current + offset < 0)
		{
			int previous = current;
			Rotate(power);
			int current = nMotorEncoder(FrontLeft);
			
			offset = current - previous;
			// if (current + offset > 0) break;
		}
	}

	StopMoving();
}

void AdjustLiftUpSmart(int originalPower)
{
	int power = AdjustBatteryLevel(originalPower) * -1;
	int offset = 0;

	int leftPot = nMotorEncoder(LeftLift2);
	int rightPot = nMotorEncoder(RightLift1);

	if (leftPot > rightPot)
	{
		int current = leftPot;

		while(current + offset > rightPot)
		{
			if (vexRT[Btn8D] + vexRT[Btn8U] + vexRT[Btn8R] + vexRT[Btn8L] > 0) 
			{ // return if a button is pressed
				break;
			}

			int previous = current;

	    motor[LeftLift1] = power;
	    motor[LeftLift2] = power;
	    
	    int current = nMotorEncoder(LeftLift2);
	    
	    offset = current - previous;
	    // if (current + offset < nMotorEncoder(RightLift1)) break;
	    
//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}
		
		StopLift();
	}
	else
	{
		int current = rightPot;
	
		while(current + offset > leftPot)
		{
				if (vexRT[Btn8D] + vexRT[Btn8U] + vexRT[Btn8R] + vexRT[Btn8L] > 0)
				{ // return if a button is pressed
						break;
				}
	
				int previous = current;
									
		    motor[RightLift1] = power;
		    motor[RightLift2] = power;
		    
		    int current = nMotorEncoder(RightLift1);
		    
		    offset = current - previous;
		    // if (current + offset < nMotorEncoder(LeftLift2)) break;
		    
	//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}
		
		StopLift();
	}
}
