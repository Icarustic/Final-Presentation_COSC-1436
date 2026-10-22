// Final-Presentation_COSC-1436.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <chrono> //Used to track time
#include <Windows.h> //Used to test time tracking
#include <algorithm>

using namespace std;

using Clock = chrono::steady_clock; // Similar to using namespace std;
// Lua Equivilant is os.clock() to set a variable = current time.

/*------Variables-----*/ //These are global variables and do suprisingly work
double Error;
double Measured; //Set via peripheral
double Desired; //Set via Controls
bool Startup = true;
double Derivative;

//Manual Settings
double PIntensity = 5; //Starting point of the correction (immediate correction)
double IIntensity = 2; //How much it increments by to cause change (accumulated correction)
double DIntensity = 10; //Resist Change
// If your PID Correction has a range i.e. 0-15 (redstone)
// You make a range clamp and change the intensity values so it increments meaningfully
// Tune each seperatly, Start with P, then I, then D.

//How to deal with code that reqiures refrencing previous values?
    //Make a temporary value that stores the lastvalue and update it at the end of each run.
    //This allows you to make a time values by using CurrentTime - LastTime = time duration
    //Also allows you to make the derivative by using CurrentError - LastError = Change in Error

/*------Stored Pid Variables------*/
Clock::time_point LastTime; //Cleaner since it dosent set a value to the variable
  //auto LastTime = Clock::now(); 
  //Variable is set here and updated in main,
  //The value is updated when the program is active and not inactive as to prevent the time from accumulating.
double IntegralSum = 0.0; //Holds the Sum of Errors * Time while the program is being run. //Starting value of 0 is set
double LastError = 0.0;


double PidSystem(double Desired, double Measured) //Pid System
{
    auto CurrentTime = Clock::now(); //Stores the current time during the moment the PID is called/started

    double elapsedtime = chrono::duration<double>( //Elapsed time tracks how long ago the program last ran the loop. So it can find the change in time.
        CurrentTime - LastTime).count();

    if (elapsedtime <= 0.0)
    {
        return 0.0; //ends the PID system so you dont divide by 0 or use negative value for the derivative.
    }

    //cout << elapsedtime << endl;

    //Calculate Error
    Error = Desired - Measured; 

    //cout << Error << endl;

    // 1. Proportional       
    double Proportional = (Error * PIntensity);
    cout << "Proportional: " << Proportional << endl;

    // 2. Integral
    IntegralSum += (Error * elapsedtime); 
    //Adds the sum of (Errors*Time) Note: Its both values not just error. 
    //Dosent reqiure storing all Errors to compute, just adds them all together overtime.
    double Integral = IntegralSum * IIntensity;
    cout << "Integral: " << Integral << endl;

    // 3. Derivative
    if (Startup == false) //Neccesary to account for first run having a very small time value
    {
        Derivative = DIntensity * ((Error - LastError) / elapsedtime); //CurrentError = Error, 
    }
    else
    {
        Derivative = 0;
    }
    cout << "Derivative: " << Derivative << endl;

    LastError = Error; //Sets up the Last Error for the next loop.
    LastTime = CurrentTime; //Sets up the starting time point for the next PID loop
    Startup = false;

    return Proportional + Integral + Derivative;
}

int main()
{
    /* ------Blue_Print---- */
    // 1. Altitude Control - Sets Motor Speed
    // 2. Pitch Controls - Normal drones have a feedback to help with thrust being lost due to tilt.
    // 3. Yaw Control 
    // 4. Roll Control - Relative Motor Speeds : Ratios : Defult = 1:1 , Right Roll = 2:1, etc
    // 5. Total Control - Combines (AltitudeThrust with RollThrustRatio) and (YawTilt + PitchTilt)
    // I still need PID for the Yaw,Pitch, and Roll values systems to counter high sensitivity controls leading to jagged movment.

    /*Main*/ 

    // Sets Last time to Current time so it can use a known previous point to calculate time. //Updates it here to be current even though it is set in global.
    LastTime = Clock::now(); //Note make sure it is out of the loop as it is only used during the first loop.

    /*------Altitude------*/
    // Settings (P5,I2,D10)
    // Controls and Sensor would provide the following information:
    double MeasuredAltitude = 0;
    double DesiredAltitude = 5;
    int HoverThrust = 32; //The passive RPM needed to stay stable
    Measured = MeasuredAltitude;
    Desired = DesiredAltitude;
    for (int i = 0; i <= 20; i++)
    {
        Measured = i * 0.5; //Testing code to visulize adjusments as altitude changes.
        cout << "Measured Altitude: " << Measured << endl;
        cout << "Desired Altitude:  " << Desired << endl;

        int ThrustCorrection = PidSystem(Desired, Measured); 
        Sleep(1000); // Lua Equivilant = Sleep(1) //Sperates the Duration between loops by 1 second
        //Thrust = Rpm (Range: -256,256)
        if (ThrustCorrection > 256)
        {
            ThrustCorrection = 256;
        }
        else if (ThrustCorrection < -256)
        {
            ThrustCorrection = -256;
        }
        cout << "AltitudeCorrection/Rpm is " << ThrustCorrection + HoverThrust << endl; // + PassiveThrust (The amount needed to keep the aircraft level/even/stable)
        cout << endl;
    }

    /*------Pitch------*/ 
    // Tilt (Range = -45,45) (Redstone Range: 0,15)
    // DesiredForwardMovment - MeasuredForwardMovment = Pitch Angle //Uses a Speedometer
  

} 
    


