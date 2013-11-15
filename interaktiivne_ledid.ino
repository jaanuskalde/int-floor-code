//GND mosfets are on lines 48-53

//+ are from 22-33 and 34-45

const uint8_t delay_time = 2;
#define PIEZO_SENSITIVITY 4

uint8_t output[144] =
{
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
  
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW
};

/*{
  HIGH, LOW,HIGH,HIGH, LOW, LOW, HIGH,HIGH,HIGH, LOW, LOW, LOW,
  HIGH,HIGH,HIGH,HIGH, LOW, LOW,  LOW, LOW,HIGH,HIGH,HIGH,HIGH,
  HIGH, LOW, LOW, LOW, LOW, LOW, HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,
   LOW, LOW, LOW, LOW, LOW, LOW, HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,
  HIGH, LOW, LOW, LOW, LOW, LOW,  LOW, LOW,HIGH,HIGH,HIGH,HIGH,
  HIGH,HIGH,HIGH,HIGH, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
  
  HIGH,HIGH,HIGH,HIGH,HIGH,HIGH, HIGH,HIGH,HIGH, LOW, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW, HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,
  HIGH,HIGH,HIGH, LOW, LOW, LOW,  LOW, LOW, LOW, LOW, LOW, LOW,
  HIGH,HIGH,HIGH,HIGH,HIGH,HIGH, HIGH,HIGH,HIGH,HIGH, LOW, LOW,
   LOW, LOW, LOW, LOW, LOW, LOW,  LOW, LOW, LOW, LOW,HIGH,HIGH,
  HIGH,HIGH,HIGH,HIGH,HIGH,HIGH, HIGH,HIGH,HIGH, LOW, LOW, LOW
};*/

const uint8_t red[12] =
{
  0,3,  36,39, 50,53, 14,17, 25,28, 61, 64
};

const uint8_t green[12] =
{
  1,4, 12,15, 48,51, 62, 65, 26,29,  37,40
};

const uint8_t blue[12] =
{
  2,5, 13,16, 49,52, 60, 63, 24,27,  38,41
};


void setup()
{
  for (int i = 46; i<=53;i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }

  for (int i = 22; i<=47;i++)
  {
    pinMode(i,OUTPUT);
//    digitalWrite(i,HIGH);
  }
  Serial.begin(115200);
}

int i = 22;
int e = 48;
void loop()
{
  //deal with piesos
  uint8_t piesos[4] = {(uint8_t) (analogRead(A1)/PIEZO_SENSITIVITY/16),(uint8_t) (analogRead(A2)/PIEZO_SENSITIVITY),(uint8_t) (analogRead(A3)/PIEZO_SENSITIVITY),(uint8_t) (analogRead(A4)/PIEZO_SENSITIVITY)};
  for (char i=0;i<12;i++)//loop that checks piesos
  {
    if (i < piesos[3]) output[blue[i]] = HIGH; else output[blue[i]] = LOW;
    if (i < piesos[2]) output[blue[i]+6] = HIGH; else output[blue[i]+6] = LOW;
    if (i < piesos[1]) output[blue[i]+72] = HIGH; else output[blue[i]+72] = LOW;
    if (i < piesos[0]) output[blue[i]+78] = HIGH; else output[blue[i]+78] = LOW;
  }
  
  //deal with center weigth sensitive resistor
  uint8_t weight = (uint8_t) ((analogRead(A0)-200)/64);
  for (char i=0;i<12;i++)
  {
    if (i < weight)
    {
      output[green[i]] = HIGH;
      output[green[i]+6] = HIGH;
      output[green[i]+72] = HIGH;
      output[green[i]+78] = HIGH;
      output[red[i]] = LOW;
      output[red[i]+6] = LOW;
      output[red[i]+72] = LOW;
      output[red[i]+78] = LOW;
    }
    else
    {
      output[green[i]] = LOW;
      output[green[i]+6] = LOW;
      output[green[i]+72] = LOW;
      output[green[i]+78] = LOW;
      output[red[i]] = HIGH;
      output[red[i]+6] = HIGH;
      output[red[i]+72] = HIGH;
      output[red[i]+78] = HIGH;      
    }

  }
  
  for (char e=0;e<6;e++)
  {
    for (char i=0;i<12;i++) digitalWrite(i+24,output[i+12*(e+6)]);
    for (char i=0;i<12;i++) digitalWrite(i+36,output[i+12*e]);
    digitalWrite(48+e,HIGH);
    delay(delay_time);
    digitalWrite(48+e,LOW);
  }
}
