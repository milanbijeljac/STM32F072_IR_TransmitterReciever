/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <TemperatureCalculation.h>

/* **************************************************
 *					DEFINES 					    *
 *************************************************  */

#define V_REF 5u        /* Reference voltage */

#define R1    10000.0f  /* Resistance at temperature T1 (in ohms) */
#define T1    25.0f     /* Temperature at R1 (in Celsius) */

#define R2    12500.0f  /* Resistance at temperature T2 (in ohms) */
#define T2    30.0f     /* Temperature at R2 (in Celsius) */

float Temp_f_CalculateTemperature(uint16 u_adcRead)
{
	float f_voltage     = 0.0f;
	float f_resistance  = 0.0f;
	float f_temperature = 0.0f;

    f_voltage = (u_adcRead / 4095.0) * V_REF;

    f_resistance = (V_REF * 10000.0 / f_voltage) - 10000.0;

    float m  = (T2 - T1) / (R2 - R1);

    float b = T1 - m * R1;

    f_temperature = m * f_resistance + b;

    return f_temperature;
}
