#include "arduinoFFT.h"
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 4096 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
 
void setup() 
{
    Serial.begin(9600); //Baud rate for the Serial Monitor
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
}
 
void loop() 
{  
    //Sample SAMPLES times/
    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        //remaining wait time between samples if necessary/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    //Perform FFT on samples/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    
    //Find peak frequency and print peak/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

#define SAMPLING_FREQUENCY 8192
    for(int l=0; l<SAMPLES; l++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[l] = analogRead(1); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[l] = 0; //Makes imaginary term 0 always

        //remaining wait time between samples if necessary/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    //Perform FFT on samples/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    
    //Find peak frequency and print peak/
    double peak1 = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
#define SAMPLING_FREQUENCY 12100
    for(int m=0; m<SAMPLES; m++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[m] = analogRead(2); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[m] = 0; //Makes imaginary term 0 always

        //remaining wait time between samples if necessary/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    //Perform FFT on samples/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    
    //Find peak frequency and print peak/
    double peak2 = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    
    //while(1); 
    //Serial.println(peak);     //Print out the most dominant frequency.
    if(peak >= 2000 && peak1 >= 4000 && peak2 >=5900){
    //Script stops here. Hardware reset required./
    
    Serial.println(peak);
    Serial.println(peak1);
    Serial.println(peak2);        
    delay(5000);
    while (0); //do one time
    }
}