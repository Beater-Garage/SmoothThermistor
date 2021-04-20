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
 * Time: 19:27
 *
 * SmoothThermistor (https://github.com/giannivh/SmoothThermistor)
 * A flexible thermistor reading library.
 *
 * Steinhart-Hart updates by Beater-Garage
 *
 */

#ifndef SmoothThermistor_h
#define SmoothThermistor_h

#include "Arduino.h"

#define DEFAULT_SERIES_RESISTANCE   10000
//Default coefficients generated from Delphi 12146312 temp sensor
#define DEFAULT_A_COEFFICIENT    	0.002108508173
#define DEFAULT_B_COEFFICIENT    	0.000079792
#define DEFAULT_C_COEFFICIENT    	0.0000006535076315
#define DEFAULT_SAMPLES             10
#define ADC_SIZE_8_BIT              8
#define ADC_SIZE_10_BIT             10
#define ADC_SIZE_12_BIT             12
#define ADC_SIZE_16_BIT             16
#define DEFAULT_UNIT				FALSE //TRUE for fahrenheit


class SmoothThermistor {
  public:

    /**
     * @param analogPin          The analog pin where the thermistor is connected to.
     * @param adcSize            The ADC size. This is usually ADC_SIZE_10_BIT.
     * @param seriesResistance   The value of the series resistor.
     * @param aCoefficient    	 The A coefficient of the thermistor.
     * @param bCoefficient    	 The B coefficient of the thermistor.
     * @param cCoefficient    	 The C coefficient of the thermistor.
     * @param samples            The number of samples to take for temperature smoothing.
	 * @param fahrenheit         TRUE to return value in fahrenheit.
     */
    SmoothThermistor(uint8_t analogPin,
                     uint16_t adcSize = ADC_SIZE_10_BIT,
                     uint32_t seriesResistance = DEFAULT_SERIES_RESISTANCE,
                     float aCoefficient = DEFAULT_A_COEFFICIENT,
                     float bCoefficient = DEFAULT_B_COEFFICIENT,
                     float cCoefficient = DEFAULT_C_COEFFICIENT,
                     uint8_t samples = DEFAULT_SAMPLES,
					 bool fahrenheit = DEFAULT_UNIT);

    void useAREF(bool aref);
    float temperature(void);

  private:

    uint8_t  _analogPin;
    uint16_t _adcSize;
    uint32_t _seriesResistance;
    float _aCoefficient;
    float _bCoefficient;
    float _cCoefficient;
    uint8_t  _samples;
	bool fahrenheit;
};

#endif
