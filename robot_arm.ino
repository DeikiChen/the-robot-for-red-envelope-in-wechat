#include <Servo.h>


Servo myservo1;  
Servo myservo2;
Servo myservo3;

//定义舵机管脚
int servo1pin=13;
int servo2pin=12;
int servo3pin=11;
//定义按钮管脚
int key=47;


int value_x,value_x_old;
int value_y,value_y_old;
int value_z,value_z_old;

int data_x[20];
int data_y[20];
int data_z[20];
int max_data[20];
int count,run_count;

int key_flag=0;
char val;

void setup() {
Serial.begin(9600);
myservo1.attach(servo1pin);  
myservo2.attach(servo2pin);  
myservo3.attach(servo3pin);
  
myservo1.write(0);               
myservo2.write(0);
myservo3.write(0);

value_x_old=analogRead(0)/5.6;
value_y_old=analogRead(1)/5.6;
value_z_old=analogRead(2)/5.6;

pinMode(key,INPUT);
  //填写机械臂舵机移动的角度
  data_x[0]=0;data_y[0]=0;data_z[0]=0;
  data_x[1]=83;data_y[1]=0;data_z[1]=0;
  data_x[2]=83;data_y[2]=145;data_z[2]=0;
  data_x[3]=82;data_y[3]=70;data_z[3]=0;
  data_x[4]=96;data_y[4]=70;data_z[4]=0;
  data_x[5]=96;data_y[5]=151;data_z[5]=0;
  data_x[6]=136;data_y[6]=70;data_z[6]=0;
  data_x[7]=136;data_y[7]=70;data_z[7]=0;
  data_x[8]=136;data_y[8]=70;data_z[8]=0;
  data_x[9]=136;data_y[9]=150;data_z[9]=0;
  data_x[10]=0;data_y[10]=0;data_z[10]=0;
  //填写机械臂移动总数
  run_count=11;
}
void loop()
{
      if(Serial.available() > 0) 
      {
        char data = Serial.read();
        char str[2];
        str[0] = data;
        str[1] = '\0';
        val=str[0];
        if(str[0]=='A')
         {
           Serial.println("Start up");
         }
       }
   //////////////////////////////
    if(key_flag==0)
     {  
       value_x=analogRead(0)/5.6;
       value_y=analogRead(1)/5.6;
       value_z=analogRead(2)/5.6;

         if(abs(value_x-value_x_old)>=1)
            {
              myservo1.write(value_x);  
            }
           if(abs(value_y-value_y_old)>=1)
            {
              myservo2.write(value_y);
            } 
          
           if(abs(value_z-value_z_old)>=1)
            {
               myservo3.write(value_z);            
            } 
            value_x_old=value_x;
            value_y_old=value_y;
            value_z_old=value_z;
       }
//////////////////////////////////////////
      if(digitalRead(key)==HIGH&&key_flag==0)
       {
              delay(20);
              if(digitalRead(key)==HIGH)
              {
                delay(20);
                  if(digitalRead(key)==HIGH)
                  {
                    while(digitalRead(key));                    
                    count=count+1;
                    Serial.print("Setup A:");              
                    Serial.print("X:");
                    Serial.print(value_x,DEC); 
                    Serial.print("   ");
                    Serial.print("Y:");
                    Serial.print(value_y,DEC); 
                    Serial.print("   ");  
                    Serial.print("Z:");
                    Serial.print(value_z,DEC);  
                    Serial.print("   ");
                    Serial.println(count);                                  
                  }
              }
         }
  ////////////////////////////////////////////////
     if(val=='A')
      {  
        Serial.println("The robot arm is running...");
        ////run the setup 1///////////////////////////////////////////////
       
        
        key_flag=1;
        Serial.println("Setup A:");
        for(int i;i<run_count;i++)
        {   
           Serial.println(i);
           delay(300);
          if(data_x[i]>data_y[i])
              max_data[i]=data_x[i];
          else 
              max_data[i]=data_y[i];
          if(data_z[i]>max_data[i])
              max_data[i]=data_z[i];                
           if(i==0)
            {
              myservo1.write(data_x[i]); 
              myservo2.write(data_y[i]);
              myservo3.write(data_z[i]);                        
              delay(max_data[i]/0.3);
            }
            else
            {
              myservo1.write(data_x[i]); 
              myservo2.write(data_y[i]);
              myservo3.write(data_z[i]);       
              delay((abs(max_data[i]-max_data[i-1]))/0.3);
            }
        }
       key_flag=0;
       val=0;
      }
}
        

