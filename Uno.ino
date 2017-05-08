//Final code for uno.
#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// Working 
 
char c1=' ',c2=' ';//below lines define the pins for the motor and the electromagnetic relay.
int x=0,y=0;
int pwm1=11; 
int in1=10;
int in2=9;
int in3=8;
int in4=7;
int pwm2=6;
int relay_in1= 5;
int relay_gnd= 12;
int relay_vcc= 13;
void setup() 
{
    Serial.begin(38400);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
 
    // HC-05 default serial speed for AT mode is 38400
    BTserial.begin(9600);
  pinMode(pwm1,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(relay_in1,OUTPUT);
  pinMode(relay_gnd,OUTPUT);
  pinMode(relay_vcc,OUTPUT);
}
 
void loop()
{
  digitalWrite(relay_gnd,LOW);
  digitalWrite(relay_vcc,HIGH);
  digitalWrite(relay_in1,HIGH);
     BTserial.write('x');//When the bluetooth writes x then the master bluetooth will send x reading of accelerometer as that is how we have written the logic of the program.
     
     while(!BTserial.available());

        c1 = BTserial.read();
        x=(int)c1;
        
        if(x<0)
        {
          x=map(x,-128,-1,-1,-128);//the readings of the accelerometer are high when pwm to be given is low and vice versa. Hence we have mapped the readings in this way.
        }
        else
        {
          x=map(x,0,127,127,0);
        }


        
        Serial.print("  x: ");
        Serial.print(x);
        BTserial.flush();
       Serial.flush();
   
     BTserial.write('y');
      while(!BTserial.available());
        c2 = BTserial.read();
        y=(int)c2;
        if(y<0)
        {
         y=map(y,-128,-1,-1,-128);
        }
        else
        {
         y=map(y,0,127,127,0);
        }
        Serial.print("  y: ");
         Serial.print(y);
         Serial.println(" ");
        BTserial.flush();
        Serial.flush();
     

    


//Below we have the logic for driving the car in the required direction based on the values of x and y obtained( which are the accelerations)
//in1,in2,in3 and in4 are the pins for the polarity of the motor and pwm1,pwm2 allow us to provide the required pwm.
    if(y>15)
    {
        if(x<-30)
       {


            
            digitalWrite(in1,HIGH);
            digitalWrite(in2,HIGH);
            digitalWrite(in3,HIGH);
            digitalWrite(in4,LOW);
            
       }
       else if(x>30)
       {
            digitalWrite(in1,LOW);
            digitalWrite(in2,HIGH);
            digitalWrite(in3,HIGH);
            digitalWrite(in4,HIGH);

            
       }
       else
    {

           digitalWrite(in1,LOW);
           digitalWrite(in2,HIGH);
           digitalWrite(in3,HIGH);
           digitalWrite(in4,LOW);
           
     }

          analogWrite(pwm1,y);
          analogWrite(pwm2,y);
    } 





    
    else if(y<-15)
    { 
        if(x<-30)
        {
 

       
               digitalWrite(in1,HIGH);
             digitalWrite(in2,HIGH);
             digitalWrite(in3,LOW);
             digitalWrite(in4,HIGH);  
        }
        else if(x>30)
        {

                digitalWrite(in1,HIGH);
             digitalWrite(in2,LOW);
             digitalWrite(in3,HIGH);
             digitalWrite(in4,HIGH);
           
        }
        else
        {

            digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH);
      }

        y=(-y);

           
        analogWrite(pwm1,y);
        analogWrite(pwm2,19.0*y/20.0);
    }



    else 
    {

         digitalWrite(in1,HIGH);
         digitalWrite(in2,HIGH);
         digitalWrite(in3,HIGH);
         digitalWrite(in4,HIGH);
    }

  
}
