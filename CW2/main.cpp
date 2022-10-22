#include "mbed.h"
#include "C12832.h"
#include "DHT.h"
#include <ctime>
#include <math.h>

#define SPI_MOSI p5 
#define SPI_SCK p7 
#define SPI_MISO p6



Serial rn41(p9,p10,9600); 


DigitalIn PIR2(p15);
DigitalIn PIR1(p16); 
DigitalIn PIR4(p17);
DigitalIn PIR3(p18);
DigitalIn PIR5(p19);
DigitalOut led1(LED1);
DigitalOut led3(LED3);

#ifndef M_PI
#define M_PI 3.1415
#endif

    PwmOut port21(p21);
    PwmOut port22(p22);
    PwmOut port23(p23);
    PwmOut port24(p24);
    PwmOut port25(p25);
    PwmOut port26(p26);

 
bool Power_Up_68910(PwmOut light, PwmOut Light6, PwmOut Light8){

    float f = 0.0;
    while (f <= 180) {
    light = (sin( (f + 270.0) * M_PI / 180.0) + 1.0)/2;
    Light6 = sin( (f + 270.0) * M_PI / 180.0) + 1.0;
    Light8 = sin( (f + 270.0) * M_PI / 180.0) + 1.0;
    
        f += 1.0;
        wait(0.01);
    }
    return 1;

};            

bool Power_Down_Right(PwmOut Light6, PwmOut Light8, PwmOut light){

    float f = 0.0;
    while (f <= 90) {
    Light6 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light8 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    
        f += 1.0;
        wait(0.01);
    }
    return 1;

};

bool Power_Down_68910(PwmOut light, PwmOut Light6,  PwmOut Light8){

    float f = 0.0;
    while (f <= 90) {
    light = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light6 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light8 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    
        f += 1.0;
        wait(0.01);
    }
    return 1;

};
bool Power_Up_Left (PwmOut Light1, PwmOut Light2, PwmOut light){

    float f = 0.0;
    while (f <= 180) {
    Light1 = (sin( (f + 270.0) * M_PI / 180.0) + 1.0)/2;
    Light2 = (sin( (f + 270.0) * M_PI / 180.0) + 1.0)/2;
    light = (sin( (f + 270.0) * M_PI / 180.0) + 1.0)/2;
    
        f += 1.0;
        wait(0.01);
    }

    return 1;
};
bool Power_Down_Left (PwmOut Light1, PwmOut Light2, PwmOut Light3){
    float f = 0.0;
    while (f <= 90) {
    Light1 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light2 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light3 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;

        f += 1.0;
        wait(0.01);
    }
    return 0;
};

bool Power_Up_Merge (PwmOut light, PwmOut Light6 ,PwmOut Light8){
    float f = 0.0;
    while (f <= 180) {
    light = sin( (f + 270.0) * M_PI / 180.0) + 1.0;
    Light6 = sin( (f + 270.0) * M_PI / 180.0) + 1.0;
    Light8 = sin( (f + 270.0) * M_PI / 180.0) + 1.0;
        f += 1.0;
        wait(0.01);
    }
    return 0;
};
bool Power_Down_Merge (PwmOut light, PwmOut Light6  ,PwmOut Light8){
    float f = 0.0;
    while (f <= 90) {
    light = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light6 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;
    Light8 = sin( (f + 180.0) * M_PI / 180.0) + 1.0;

        f += 1.0;
        wait(0.01);
    }
    return 0;
};



C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);

DHT sensor(p20,SEN11301P);

Timer t1;
int counter=0;
int counter2=0;


float velocity;

Ticker LCD_Ticker1, LCD_Ticker2;

void update_LCD(){int err;
    lcd.cls();
    lcd.locate(0,0);
    err = sensor.readData();
    if(err==0){
        if (sensor.ReadTemperature(CELCIUS) < 2 ){
        lcd.cls();
        lcd.printf("Caution Ice on road\r\n");
        rn41.printf("Caution Ice on road\r\n");
        lcd.printf("Temperature is %4.2f C \r\n", sensor.ReadTemperature(CELCIUS));
        rn41.printf("Temperature is %4.2f C \r\n", sensor.ReadTemperature(CELCIUS));
        
        }

        if (sensor.ReadHumidity() >80 ){
        lcd.cls();
        lcd.printf("Caution Visability Low\r\n");
        rn41.printf("Caution Visability Low\r\n");
        
        lcd.printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
        rn41.printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
        }

        else {
        

    
    lcd.printf("Temperature is %4.2f C \r\n", sensor.ReadTemperature(CELCIUS));
    rn41.printf("Temperature is %4.2f C \r\n", sensor.ReadTemperature(CELCIUS));
    lcd.printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
    rn41.printf("Humidity is %4.2f \r\n",sensor.ReadHumidity());
    lcd.printf("Dew point (fast) is %4.2f",sensor.CalcdewPointFast(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
    rn41.printf("Dew point (fast) is %4.2f",sensor.CalcdewPointFast(sensor.ReadTemperature(CELCIUS), sensor.ReadHumidity()));
    }
    }
    
    
}

void update_LCD2(){
    lcd.cls();
    lcd.locate(0,0);
    lcd.printf("Speed in m/s ... %.4f m/s \r\n", velocity); 
    rn41.printf("Speed in m/s ... %.4f m/s \r\n", velocity); 

    lcd.printf(" Counter %d\r\n", velocity, counter2);  
    //rn41.printf(" Counter %d\r\n", velocity, counter2);  
    //lcd.printf(" Counter %d", counter );
    lcd.printf("Elapsed time: %.4f",t1.read());
    rn41.printf("Elapsed time: %.4f",t1.read());
}
int main() {
        

    rn41.printf("Welcome to JAD Limited\n\r");
    int pir1_triggered = 0;
    int pir3_triggered = 0;
    int pir5_triggered = 0;

    LCD_Ticker1.attach(&update_LCD, 5);
    wait(2.5);

    LCD_Ticker2.attach(&update_LCD2, 5);


    while (1) {    

    if (PIR1 == 1){
        t1.start();
        led1 = 1;
        counter++;
        counter2=counter/17;
    }
    
        
    if (PIR2 == 1){
        t1.stop();
        led3 = 1;}

        velocity=(0.4/t1.read());//v=d/t
        //velocity=velocity*3.6;//kph


    if (PIR5==1 && !pir5_triggered){
        pir5_triggered = 1;        
        Power_Up_Merge (port24, port25, port26);
        rn41.printf ("PIR 5 \r\n");
        }

        

        if (PIR4==1 && pir3_triggered){
        pir3_triggered = 0;
        wait(4);
        Power_Down_Merge(port24, port25, port26);
        rn41.printf("PIR 4 \r\n");
        }

    
    if (PIR1==1 && !pir1_triggered){
        pir1_triggered = 1;        
        Power_Up_Left (port21,port22,port23);
        rn41.printf ("PIR 1 \r\n");
        }


        if (PIR2==1 && pir1_triggered){
        pir1_triggered = 0;
        wait(4);
        Power_Down_Left(port21,port22,port23);
        rn41.printf("PIR 2 \r\n");

        }



    
    

    if (PIR3==1 && !pir3_triggered){
        pir3_triggered = 1;        
        Power_Up_68910 (port24,port25, port26);
        rn41.printf ("PIR 3 \r\n");
        }

        

        if (PIR4==1 && pir3_triggered){
        pir3_triggered = 0;
        wait(4);
        Power_Down_68910(port24, port25, port26);
        rn41.printf("PIR 4 \r\n");
        }
        
    if (rn41.readable()) {     // if data available

      char x=rn41.getc();      // get data

    }
}
}

