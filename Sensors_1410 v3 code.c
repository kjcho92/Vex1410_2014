#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotentiometerLeft, sensorNone)
#pragma config(Sensor, in2,    yAccel,         sensorAccelerometer)
#pragma config(Sensor, in3,    xAccel,         sensorAccelerometer)
#pragma config(Sensor, in5,    lightSensor,    sensorNone)
#pragma config(Sensor, dgtl7,  SonarSensor,    sensorSONAR_mm)
#pragma config(Sensor, dgtl10, Jumper3,        sensorDigitalIn)
#pragma config(Sensor, dgtl11, Jumper2,        sensorDigitalIn)
#pragma config(Sensor, dgtl12, Jumper1,        sensorDigitalIn)
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
void EncoderRotateSmart(int power);
void EncoderLiftUp(int index, int power, int target);
void EncoderLiftDown(int sequence, int power, int target);
void Claw(int power);
void PickUpSkyrise(int duration);
void ReleaseSkyrise(int duration);
void StopLift();
void AdjustLiftUpSmart(int timeout, int threshold, int originalPower);
int AdjustBatteryLevel(int OriginalPower);

////////////////////////////////////////////////////
/// Autonomous mode - Not using
// void ForBack(int power, int distance);
// void ReleaseCube(int duration,int power);
// void AdjustAutoLiftUp(int originalPower);

////////////////////////////////////////////////////
/// Drive mode
int GetLeftPower(int movingUp, int movingDown);
int GetRightPower(int movingUp, int movingDown);
int AdjustLiftPower(int value);
int ReverseIfNeeded(int power);

int AdjustLiftPowerOld(int pot1, int pot2);

bool MovingForward = false;

const	int sshortDelay = 25;
const	int shortDelay = 50;
const int defaultDelay = 100;

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
		if (SensorValue[Jumper2] == 0)
		{
			nMotorEncoder(RightLift1) = 0;
			EncoderLiftUp(0, -70, -1500); // Lift up

			wait1Msec (1000);

		//	EncoderLiftDown(0, 80, -200); //Lift down
			wait1Msec(sshortDelay);

			return;
		}

		//////////////////////
		/// RED RED RED RED RED
		int sonarRotationOriginalPower = 44;
		int gyroRotationOriginalPower = 90;
		int iterationcount = 1;

		if (SensorValue[Jumper1] == 0)
		{
			//////////////////////
			/// BLUE BLUE BLUE BLUE
			sonarRotationOriginalPower = 44;
			gyroRotationOriginalPower = 90;
			iterationcount = 1;
		}

		ClearTimer(T3);

		int powerFortakingSkyrise = 700;
		for (int i = 0; i <= iterationcount; i++)
		{
			// if want to manually reset the position uncomment below
			/*
			if (6 == i)
			{
					wait1Msec (1500); // 1.5 secs
			}
			*/

			// pick up skyrise
			PickUpSkyrise(powerFortakingSkyrise); //700 -> 500
			powerFortakingSkyrise = 700;
			wait1Msec (defaultDelay);

			nMotorEncoder(LeftLift2) = 0;
			nMotorEncoder(RightLift1) = 0;

			int offset = 0;

			switch (i)
			{
				case 0: offset = -1600; break;
				case 1: offset = -1700; break;
				case 2: offset = -2000; break;
				case 3: offset = -2600; break;
				case 4: offset = -3300; break;
				case 5: offset = -4500; break;
				case 6: offset = -5700; break;
			}

			EncoderLiftUp(i, -127, offset); // Lift up
	 		wait1Msec(defaultDelay);

			nMotorEncoder(FrontRight) = 0;
			nMotorEncoder(FrontLeft) = 0;

			// rotate to the skyrise base
			int sonarRotationPower = AdjustBatteryLevel(sonarRotationOriginalPower);

			/*
			if (0 == i)
			{
				sonarRotationPower = sonarRotationPower;
			}*/
			/*else if (i >= 1)
			{
				int val = 3 + i;

				int increasing = AdjustBatteryLevel(val);
				sonarRotationPower = sonarRotationPower + increasing;
				writeDebugStreamLine("sonarRotationPower (%d), increasing (%d)", sonarRotationPower, increasing);
			}*/

			SonarRotate(220, sonarRotationPower);
			wait1Msec (defaultDelay);

			int heightToDrop = 250;
			if (0 == i)
			{
				heightToDrop = -offset;
			}
			else if (1 == i)
			{
				heightToDrop = 1100;
			}


			EncoderLiftDown(0, 50, offset + heightToDrop); //Lift down

			wait1Msec (defaultDelay);

			ReleaseSkyrise(30); // 300 -> 30
			writeDebugStreamLine("T3 - %d: %d	", i, time1[T3]);

			wait1Msec(shortDelay);

			EncoderLiftDown(1, 80, 0); //Lift down
			wait1Msec(sshortDelay);

			int gyroRotationPower = AdjustBatteryLevel(gyroRotationOriginalPower);

/*
			if (i >= 1)
			{
				int val = 3 + i;
				int increasing = AdjustBatteryLevel(val);
				gyroRotationPower = gyroRotationPower + increasing;
				writeDebugStreamLine("gyroRotationPower (%d), increasing (%d)", gyroRotationPower, increasing);
			}
*/
			// rotate to the autoload
			EncoderRotateSmart(gyroRotationPower);
			wait1Msec(sshortDelay); // didn't have this. might not need.
		}
}

int AdjustBatteryLevel(int OriginalPower)
{
	float AdjustBatteryLevel = nImmediateBatteryLevel;
  float BatteryOffset =	6000 / AdjustBatteryLevel;
  int WantedPower = OriginalPower * BatteryOffset;
//	writeDebugStreamLine("(AjustBattery) BatterLevel: %d - OriginalPower: %d - WantedPower: %d", AdjustBatteryLevel, OriginalPower, WantedPower);
  return WantedPower;
}

void EncoderLiftUp(int index, int power, int target)
{
	while(nMotorEncoder(RightLift1) > target)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

//			writeDebugStreamLine("(LiftUp) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();


		writeDebugStreamLine("xAccel: (%d)", SensorValue[xAccel]);

		if (index > 1)
		{
			wait1Msec(50);
    	int adjustPower = 21;
			AdjustLiftUpSmart(3, 7, adjustPower);
		}
		// int adjustPower = 38;
		// AdjustAutoLiftUp(adjustPower);
}


void EncoderLiftDown(int sequence, int power, int target)
{
	bool closingClaw = false;
	ClearTimer(T2);

	if (sequence == 1)
	{
		closingClaw = true;
		Claw(-127);
	}

	while(nMotorEncoder(RightLift1) < target)
		{
		    motor[LeftLift1] = power;
		    motor[RightLift1] = power;
		    motor[LeftLift2] = power;
		    motor[RightLift2] = power;

		    if (closingClaw && time100[T2] > 2)
		    {
					Claw(0);
					closingClaw = false;
		    }

//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();

		if (closingClaw)
		{
			while (time100[T2] <= 3) {};
			Claw(0);
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
	bool cubeIntakeTaking = false;
	bool crayonIntakeTaking = false;

	bool previousDown = false;

	bool adjustIfWant = true;
	bool accelUsed = true;

	while (true)
	{
		adjustIfWant = (SensorValue[Jumper3] == 1) ? true : false;
		accelUsed = true;
		if (SensorValue[yAccel] < -1000 || SensorValue[xAccel] < -900)
		{
			accelUsed = false;
		}

		if (vexRT[Btn7U] == 1 && time1[T2] > 500)
		{
		 // reverse direction
		   MovingForward = !MovingForward;
		   ClearTimer(T2);
		}

		if (accelUsed == true && vexRT[Btn7D] == 1 /*&& 980 < SensorValue[yAccel] && SensorValue[yAccel] < 1130 */)
		{
    	// adjust lift only if it meets a certain condition
			int adjustPower = 25;
    	AdjustLiftUpSmart(20, 3, adjustPower);
		}

		int power2 = vexRT[Ch2]; // forward, backward
		int power4 = vexRT[Ch4]; // rotate
		int power7 = 60; // shift

		power2 = ReverseIfNeeded(power2);
		// power7 = ReverseIfNeeded(power7);

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

	  if (btn8r + btn8l)
	  {
	  	SensorValue[xAccel] = 0;
	  }

	  int btn8d = vexRT[Btn8D]; // lift down
	  int btn8u = vexRT[Btn8U]; // lift up


	  if (btn8d != 0)
	  {
	  			previousDown = true;
		}

	  if (accelUsed == true && SensorValue[yAccel] <= -55)
		{
			  // stop when the lift is too high
				btn8u = 0;
		}

		int lp = 77;
		int rp = 77;

		if (accelUsed == true && adjustIfWant == true)
		{
			if (SensorValue[yAccel] >= -13)
			{
				lp = 77;
				rp = 77;

				if (btn8d > 0)
				{
					lp = 50;
					rp = 50;
				}
			}
			else
			{
				lp = GetLeftPower(btn8u, btn8d);
				rp = GetRightPower(btn8u, btn8d);
			}

			if (btn8u + btn8d > 0 && lp + rp > 0 /*&& lp + rp < (127 *2)*/)
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
/*
			if (previousDown == true && SensorValue[yAccel] <-5 && accelUsed == true && adjustIfWant == true)
			{ // adjust after down
				previousDown = false;
				int adjustPowerDown = 15;
    		AdjustLiftUpSmart(20, 8, adjustPowerDown);
			}
*/
		}

		int btn5u = vexRT[Btn5U]; // take cube
		int btn5d = vexRT[Btn5D]; // release cube

		if (btn5d == 1)
		{
			cubeIntakeTaking = false;
			motor[CubeIntake] = (btn5d - btn5u) * 127;
		}
		else if (btn5u == 1)
		{
			cubeIntakeTaking = true;
			motor[CubeIntake] = (btn5d - btn5u) * 127;
		}
		else if (btn5u == 0 && btn5d == 0 && cubeIntakeTaking)
		{
				// motor[CubeIntake] = -40;
				motor[CubeIntake] = 0;
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

	int height = SensorValue[yAccel] * -1;
	int value = SensorValue[xAccel];
	// int rightPot = nMotorEncoder(RightLift1) * -1;
    // On moving up
  if (movingUp == 1)
	{
	  // when started moving, give full power.
		if (8 > height || abs(value) <= 5)
		{
			return fullPowerUp;
		}


		/*
				if (value < 0)
		{// xAccel is "-". left is lower
			motor[LeftLift1] = power;
	    motor[LeftLift2] = power;
		}
*/

		if (value < 0)
		{ // left is lower
			return fullPowerUp;
		}
		else
		{
      // when the left is higher, slow down
			return AdjustLiftPower(abs(value));
		}
	}
    // On moving down
	else if (movingDown == 1)
	{
		return fullPowerDown;
    // when the left is higher, give full power
		if (value > 0)
		{ // left is higher
			return fullPowerDown;
		}
		else
		{
			// when the right is higher, slow down
     	return AdjustLiftPower(abs(value));
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

	int height = SensorValue[yAccel] * -1;
	int value = SensorValue[xAccel];

  if (movingUp == 1)
	{
	  // when started moving, give full power.
		if (8 > height || abs(value) <= 5)
		{
			return fullPowerUp;
		}

		// when the left is higher, give full power
		if (value > 0)
		{// right is lower
			return fullPowerUp;
		}
		else
		{
      // when the right is higher, slow down
     	return AdjustLiftPower(abs(value));
		}
	}
    // On moving down
	else if (movingDown == 1)
	{
			return fullPowerDown;

    // when the right is higher, give full power
		if (value < 0)
		{// right is higher
			return fullPowerDown;
		}
		else
		{
			// when the left is higher, slow down
			return AdjustLiftPower(abs(value));
		}
	}

	return 0;
}


int AdjustLiftPower(int value)
{
	const int fullPower = 127;

	// float offset = (2 / value) * 100;
	int power = fullPower - (value * 3);
	if (power < 0) power = 0;
	return power;
}

int AdjustLiftPowerOld(int pot1, int pot2)
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
	}
	Rotate(power);
	wait1Msec (1000);

	// power = -30;
	while (abs(SensorValue[SonarSensor]) > distance /*&& abs(nMotorEncoder(FrontLeft)) < 450 */)
	{
		Rotate(power);
	}

	StopMoving();
}

void ReleaseCube(int duration,int power)
{
		motor[CubeIntake] = power;
		wait1Msec(duration);
		motor[CubeIntake] = 0;
}

void PickUpSkyrise(int duration)
{
		Claw(127);
		wait1Msec(duration);
		Claw(70); // 30 -> 70
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

void PickUpCube(int duration) //pick cube up and stuff
{
    motor[CubeIntake] = -127;
    wait1Msec(duration);
    motor[CubeIntake] = -30;
}

void ReleaseCube(int duration)
{
    motor[CubeIntake] = 127;
    wait1Msec(duration);
    motor[CubeIntake] = 0;
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

			  	writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
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

	//
//			writeDebugStreamLine("(LiftDown) LEFT: %d , RIGHT: %d", nMotorEncoder(LeftLift2), nMotorEncoder(RightLift1));
		}

		StopLift();
	}
}

void EncoderRotateSmart(int power)
{
	if (power <= 0) return;

	int current = nMotorEncoder(FrontLeft);
	float offset = 0;
	if (current < 0)
	{ // RED
		while (current + offset < 0)
		{
			int previous = current;
			Rotate(power);
			int current = nMotorEncoder(FrontLeft);

			offset = current - previous;
			offset = offset * 1.8; // 1.7 => 1.3
			// if (current + offset > 0) break;
		}
	}
	else
	{ // BLUE
		power = -power;
		while (current + offset > 0)
		{
			int previous = current;
			Rotate(power);
			int current = nMotorEncoder(FrontLeft);

			offset = current - previous;
			offset = offset * 1.5;
		}
	}

	StopMoving();
}

void ForBack(int power, int distance)
{
	if (power <= 0) return;

	int current = abs(nMotorEncoder(FrontLeft));
	float offset = 0;

	// RED only for programming skill
	// power = -power;
	while (current + offset < distance)
	{
		int previous = current;

		motor[FrontLeft] = power;
		motor[FrontRight] = power;
		motor[BackRight] = power;
		motor[BackLeft] = power;

		int current = abs(nMotorEncoder(FrontLeft));

		offset = current - previous;
		offset = offset * 1.6;
	}

	StopMoving();
}

void AdjustLiftUpSmart(int timeout, int threshold, int originalPower)
{
	int power = AdjustBatteryLevel(originalPower) * -1;
	int value = SensorValue[xAccel];

	if (-threshold < value && value < threshold) return;

	float offset = 0;
	int current = abs(value);
	int original = value;

	ClearTimer(T2);

	while(current - offset > 0)
	{
		if (vexRT[Btn8D] + vexRT[Btn8U] + vexRT[Btn8R] + vexRT[Btn8L] > 0)
		{ // return if a button is pressed
			break;
		}

		int previous = current;


		if (value < 0)
		{// xAccel is "-". left is lower
			motor[LeftLift1] = power;
	    motor[LeftLift2] = power;
	    if (time100[T2] > timeout)
	  	{
	  		break;
	  	}
		}
		else
		{// xAccel is "+". left is higher
			motor[RightLift1] = power;
			motor[RightLift2] = power;
			if (time100[T2] > timeout)
	  	{
	  		break;
	  	}
		}

    current = abs(SensorValue[xAccel]);

    offset =  (previous - current) * 2;
	}

	StopLift();
	writeDebugStreamLine("AdjustLift original (%d) , current (%d), offset (%d), xAccel (%d)", original, current, offset, SensorValue[xAccel]);
}
