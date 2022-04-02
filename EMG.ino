//#include <LED_Bar.h>

//LED_Bar bar(9, 8);

int max_analog_dta      = 300;              // max analog data
int min_analog_dta      = 100;              // min analog data
int static_analog_dta   = 0;                // static analog data


// get analog value
int getAnalog(int pin)
{
    long sum = 0;
    
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pin);
    }
    
    int dta = sum>>5;
    
    max_analog_dta = dta>max_analog_dta ? dta : max_analog_dta;         // if max data
    min_analog_dta = min_analog_dta>dta ? dta : min_analog_dta;         // if min data
    
    return sum>>5;
}

void setup()
{
    Serial.begin(115200);
    long sum = 0;
  //Serial.println("setUp");
    for(int i=0; i<=10; i++)
    {
        for(int j=0; j<100; j++)
        {
            sum += getAnalog(A7);
            delay(1);
        }
        
       // bar.setLevel(10-i);
    }
    
    sum /= 1100;
    
    static_analog_dta = sum;

    Serial.print("static_analog_dta = ");
    Serial.println(static_analog_dta);
   // pinMode(20,OUTPUT);
}

int level       = 5;
int level_buf   = 5;
void loop()
{
//digitalWrite(20,HIGH);
    int val = getAnalog(A7);   // get Analog value
    //Serial.print("A1= ");
    //Serial.println(analogRead(A7));
    //Serial.print("A1=");
    //Serial.println(analogRead(A1));
    
    int level2;
    
    if(val>static_analog_dta)                   // larger than static_analog_dta
    {
        level2 = 5 + map(val, static_analog_dta, max_analog_dta, 0, 5);
        
    }
    else 
    {
        level2 = 5 - map(val, min_analog_dta, static_analog_dta, 0, 5);
    }
    
    // to smooth the change of led bar
    if(level2 > level)
    {
        level++;
    }
    else if(level2 < level)
    {
        level--;
    }

    if(level != level_buf)
    {
        level_buf = level;
        
        //bar.setLevel(level);
    }
    //this is where you should be reading the values from in the code, if you do it anywhere else it gives garabage values
    //level is the variable that needs to be transfered, it has a range of 1-10
    Serial.println(level);
    delay(10);
}
