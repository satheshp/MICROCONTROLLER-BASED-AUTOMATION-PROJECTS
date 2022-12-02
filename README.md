# MICROCONTROLLER-BASED-AUTOMATION-PROJECTS

Here we uploaded two project code

1.INTERFACING DHT11 WITH PIC16F877A
2.INTERFACING LM35 WITH PIC16F877A



1.INTERFACING DHT11 WITH PIC16F877A



The data from Dht11 consists of decimal and integral parts combined together.
We can verify the data by checking the checksum value with the received data.
This can be done because, if everything is proper and if the sensor has transmitted proper data,
then the checksum should be the sum of “8bit integral RH data+8bit decimal RHdata+8bit integral T data+8bit decimal T data”.

The communication with the DHT11 sensor is done inside the while loop where the start signal is submitted to the sensor. 
After that, the find_response function is triggered.
If the Check_bit is 1 then the further communication is carried otherwise the LCD will show error dialog.


The program was written using CCS compiler and simulated using Proteus Software.

We have used a 16x2 LCD to display the temperature and humidity values that we measure from DHT11. 
The LCD is interfaced in 4 wire and both the sensor and LCD are powered by a 5V external power supply.

Depending on the 40bit data, the read_dht11 is called 5 times (5 times x 8bit) and
stored the data as per the data format provided in the datasheet. 
The checksum status is also checked and if errors are found, it will also notify in the LCD. Finally, 
the data is converted and transmitted to the 16x2 character LCD.





2.INTERFACING LM35 WITH PIC16F877A

The LM35 Temperature Sensor has Zero offset voltage, which means that the Output = 0V,  at 0 °C. 
Thus for the maximum temperature value (150 °C), the maximum output voltage of the sensor would be 150 * 10 mV = 1.5V.  
If we use the supply voltage (5V) as the Vref+ for Analog to Digital Conversion (ADC) the resolution will be poor as the input voltage will goes only up to 1.5V and 
the power supply voltage variations may affects ADC output. 
So it is better to use a stable low voltage above 1.5 as Vref+. 
We should supply Negative voltage instead of GND to LM35 for measuring negative Temperatures.


The output of the LM35 temperature sensor is connected to analog channel 0 (AN0) of the PIC16F877A.
In this project the pic17f877a  runs with crystal oscillator 20MHZ
The C code below was tested with CCS PIC C compiler 

Reading voltage quantity using the ADC gives us a number between 0 and 1023 (10-bit resolution), 0V is represented by 0 and 5V is represented by 1023.
Converting back the ADC digital value is easy and we can use the following equation for that conversion:
Voltage (in Volts) = ADC reading * 5 / 1023
Multiplying the previous result by 100 (LM35 scale factor is 10mV/°C = 0.01V/°C) will gives the actual temperature


It can also converted into Celsius by below conversion
Temperature(°C) = ADC reading * 0.489
where 0.489 = 500 / 1023

If the temperature above optimum level blink the led .

The program was written using CCS compiler and simulated using Proteus Software. 

The output of the LM35 temperature sensor is connected to analog channel 0 (AN0) of the PIC16F877A.
We have used a 16x2 LCD to display the temperature and values that we measure from LM35.

The LCD is interfaced in 4 wire and both the sensor and LCD are powered by a 5V external power supply.
