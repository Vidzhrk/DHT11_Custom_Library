#include "DHT11.h"
DHT11::DHT11(uint8_t pin) {
    _pin = pin;
}
int DHT11::check_response(){
  // MC sending wake up signal to dht
  pinMode(_pin,OUTPUT);
  digitalWrite(_pin,LOW);
  delay(18);
  digitalWrite(_pin,HIGH);
  delayMicroseconds(30);
  
  
  //chk dht response
  pinMode(_pin,INPUT);
  int response=digitalRead(_pin);
  unsigned long time1=micros();
  unsigned long time2;
  while(response==HIGH){
    response=digitalRead(_pin);//timeout shld be given
    time2=micros();
    if((time2-time1)>150){
      
      delay(1000);
      return 0;
    }
  }
  time1=micros();
  time2=micros();
  while(time2-time1<100){
    time2=micros();
    response=digitalRead(_pin);
    if(time2-time1>70){
      if (response==HIGH){
        break;
      }
      else{
          response=digitalRead(_pin);
        }
      }
    }
  if(time2-time1>100){
    
    delay(1000);
    return 0;
  }
  
  time1=micros();
  time2=micros();
  while(time2-time1<100){
    time2=micros();
    response=digitalRead(_pin);
    if(time2-time1>70){
      if (response==HIGH){
        break;
      }
      
      }
    }
  if(time2-time1>100){
    
    delay(1000);
    return 0;
  }
  return 1;
}
int DHT11::receive_data(){
  int response;
  unsigned long time1;
  unsigned long time2;
  int count;
  for(int i=0;i<5;i++){
    count=0;
    while(count<8){
      time1=micros();
      response=digitalRead(_pin);
      while(response==HIGH){
      response=digitalRead(_pin);
      time2=micros();
      if((time2-time1)>150){
       
        delay(1000);
        return 0;
    }
      }
      int bit;
      time1=micros();
      time2=micros();
      
      //checking if the bit is 0 or 1
      while(time2-time1<70){
        time2=micros();
        response=digitalRead(_pin);
        if(time2-time1>30){
          if (response==HIGH){
            break;
          }
          else{
              response=digitalRead(_pin);
            }
          }
      }
      if(time2-time1>70){
        
        delay(1000);
        return 0;
      }
      time1=micros();
      while(digitalRead(_pin)==HIGH){
        time2=micros();
      }
      if(time2-time1>55){
        bit=1;
      }
      else{
        bit=0;
      }
      
      if(bit==1){
        answer[i]=(answer[i]<<1|1);
      }
      else if(bit==0){
        answer[i]=(answer[i]<<1);
      }
      count++;
    }
  }
  return 1;
}

int DHT11::read_temperature (){
  return answer[2];
}
int DHT11::read_humidity (){
  return answer[0];
}
int DHT11::checksum(){
  uint8_t checksum=(answer[0]+answer[1]+answer[2]+answer[3])& 0xFF;
  if(answer[4]==checksum){
    
    return 1;
  }
  else{
    
    delay(1000);
    return 0;
  }
  
}
