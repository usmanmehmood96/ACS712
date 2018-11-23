#define currentPin    36

float   volts   =     0;
float   current =     0;

const int numReadings = 500;    // Number of readings for running average

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
float average = 0;              // the average

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < numReadings; i++)
  {
    readings[i] = 0;
  }
}

void loop()
{
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(currentPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings)
  {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  average = total / numReadings;


  volts = (average * 5) / 4096;
  current = ((volts - 2.31)/0.185)*1.38;


  Serial.println(volts); Serial.print("\t"); Serial.println(current);
  delay(1);        // delay in between reads for stability
}
