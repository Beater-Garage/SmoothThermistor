/*
 * This file is part of SmoothThermistor.
 *
 * Copyright (c) 2016 Gianni Van Hoecke <gianni.vh@gmail.com>
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * User: Gianni Van Hoecke <gianni.vh@gmail.com>
 * Date: 23/05/16
 * Time: 19:28
 *
 * SmoothThermistor (https://github.com/giannivh/SmoothThermistor)
 * A flexible thermistor reading library.
 */

#include "Arduino.h"
#include "SmoothThermistor.h"
#include <math.h>

//Use the following tool to generate A B and C coefficients: https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html

SmoothThermistor::SmoothThermistor(uint8_t analogPin, uint16_t adcSize, 
                                   uint32_t seriesResistance, uint16_t aCoefficient, uint16_t bCoefficient, uint16_t cCoefficient, 
                                   uint8_t samples, uint8_t fahrenheit) {

    _analogPin = analogPin;
    _adcSize = adcSize;
    _seriesResistance = seriesResistance;
    _aCoefficient = aCoefficient;
	_bCoefficient = bCoefficient;
	_cCoefficient = cCoefficient;
    _samples = samples;
	_fahrenheit = fahrenheit;
}

void SmoothThermistor::useAREF(bool aref) {
  
#if !defined(ESP32) && !defined(ESP8266)
    analogReference(aref? EXTERNAL: DEFAULT);
#endif
  
}

float SmoothThermistor::temperature(void) {

    // take samples
    float average = 0;

    for (uint8_t i = 0; i < _samples; i++) {

        average += analogRead(_analogPin);
        delay(10); //Take analog reading every 10 ms and add the raw value to the average variable
    }

    average /= _samples; //Divide the summed average variable by the number of samples

    // convert the value to resistance, avoid divide by 0 error
	if(average == 0){
		average = 1;
	}
	else{
    average = _seriesResistance * ((pow(2.0, _adcSize) - 1) / average - 1);  //Rearranged voltage divider equation, if average is 0, divide by 0 error possible w/o if else statement
	}

    // Steinhart–Hart equation, based on https://learn.adafruit.com/thermistor/using-a-thermistor
    float inv_steinhart = aCoefficient+bCoefficient*log(average)+cCoefficient*pow(3.0,log(average));
    float steinhart = 1.0 / inv_steinhart; // invert
    steinhart -= 273.15; // convert to celsius
	if(fahrenheit){
		steinhart *= (9/5);
		steinhart += 32;
	}
	
    return steinhart;
}
