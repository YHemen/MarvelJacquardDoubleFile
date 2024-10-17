#include <BLEDevice.h>
#include <stdlib.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <string.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "SD_MMC.h"
#include "uRTCLib.h"
#include<EEPROM.h>
#include <iostream>

#define EN_Pin 35//20
#define clk_Pin 8//21
#define data_Pin1  45
#define data_Pin2  37
#define data_Pin3 38
#define data_Pin4 39
#define data_Pin5 40
#define data_Pin6  41
#define data_Pin7  42
#define data_Pin8  1
#define data_Pin9  4
#define data_Pin10  5
#define data_Pin11  6
#define data_Pin12  7
#define data_Pin13  15
#define data_Pin14  16
#define data_Pin15  17
#define data_Pin16  18



void Data_passing(int con_size);
void cleardata(void);
void Data_passing_clear();
void data_process();
unsigned long previousMillis = 0;
const long interval = 300; // interval at which to check if the task is complete (milliseconds)

/*#define SCK  14 // dev board 
#define MISO  12
#define MOSI  13
#define CS  15*/


#define SCK  14 // original cpu board 
#define MISO  10
#define MOSI  12
#define CS  13

#define bit_length  16
#define PinAnalogIn 36


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // USING 
#define SERVICE_UUID2       "4fafc202-1fb5-459e-8fcc-c5c9c331914b"

#define CHARACTERISTIC_UUID  "beb5483e-36e1-4685-b7f5-ea07361b26a8" // SD DATA SENDING 
#define CHARACTERISTIC_UUID2 "beb5483e-36e1-4686-b7f5-ea07361b26a8" // sd files read from client 
#define CHARACTERISTIC_UUID3 "beb5483e-36e1-4687-b7f5-ea07361b26a8" // width
#define CHARACTERISTIC_UUID4 "beb5483e-36e1-4688-b7f5-ea07361b26a8" // height
#define CHARACTERISTIC_UUID5 "beb5483e-36e1-4689-b7f5-ea07361b26a8" // 
#define CHARACTERISTIC_UUID6 "beb5483e-36e2-4680-b7f5-ea07361b26a8" // 

#define CHARACTERISTIC_UUID11 "beb5483e-36e2-4670-b7f5-ea07361b26a8" // sd files read from client modes

#define CHARACTERISTIC_UUID22 "beb5483e-36e2-4671-b7f5-ea07361b26a8" // sd files read from client modes



#define temp_number 128
#define number_of_cards1 temp_number /// 16*8

int  sen1=47;
int  sen2=48;
int temp_up_flag=0;
uRTCLib rtc(0x68);
File file ;
File root;

String string1="/";
String string2="";
String string3=".bmp";
String RPM_String="RPM.";
String previousValue = "";
String previousValue2 = "";
String temp_str=".";
String combinedString="";
String combinedString88="";
String result2;
String result222;
String lockstatus="locked";
String unlockstatus="unlocked";
std::string receivedData3 ;
std::string selectedFile; 
char  comp_string1[]="allu";
char  comp_string2[]="alld";
char  comp_string3[]="8up8d";
char  comp_string4[]="1up1d";
char  comp_string5[]="default";
static int mode_set=0;
String separatedStrings[3];
String separatedStrings2[3];
String separatedStrings3[3];
String separatedStrings4[3];
String separatedStrings5[3];
String separatedStrings6[3];


BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic2 = NULL;
BLECharacteristic* pCharacteristic3 = NULL;
BLECharacteristic* pCharacteristic4 = NULL;
BLECharacteristic* pCharacteristic5 = NULL;
BLECharacteristic* pCharacteristic6 = NULL;
BLECharacteristic* pCharacteristic11 = NULL;
BLECharacteristic* pCharacteristic22 = NULL;

bool deviceConnected = false;
bool oldDeviceConnected = false;
volatile bool sensor1Triggered = false;  // sensor1 detaction 
volatile bool sensor2Triggered = false;
uint32_t value = 0;
static int card_count=0;
static int connector_count=1;
static int max_cardcount=16;
static int max_connector=16;
static int width = 0;
static int height= 0;
static int height_var=0;
static uint32_t present=0;
static uint32_t prev=53;
static uint16_t rtc_flag=0;
static int heightcounter_reset=0;

static uint16_t RPM_flag=0;

static uint32_t temp_present=0;
static uint32_t temp_prev=0;


static int triggerTimeReached = 1;

String filename_without_ext_fun;

static int lockstatus_count=0;
static int unlockstatus_count=0;
static int mem_cpy_set=1;
static int pick_clear_flag=0;


int sensor_sel=0;
int sensor_sel1=0;
int sensor_sel2=0;
int bitToSet = 1;    // Replace with the bit you want to set (0-based index)

int temp_count=0;
int temp_count2=0;
int temp_sens_check=0; 
int mode_zero_flag=0;

static int bmp_count=0;
static int left_right_flag=1;
static int lock_date=0;
static int    lock_month=0;
static int  lock_year=0;
static int first_set_flag=0;

unsigned int rpm1, rpm2, rpm3;
unsigned long lastTime1, lastTime2, lastTime3;

volatile unsigned int count1, count2, count3;
volatile bool sensor1Detected = false;    // Flag to indicate sensor1 detection
volatile bool sensor1NotDetected = false; // Flag to indicate sensor1 not detected
volatile bool sensor2Detected = false;    // Flag to indicate sensor2 detection
volatile bool sensor2NotDetected = false; // Flag to indicate sensor2 not detected

int8_t shiftIn1(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder); 
void shiftOut1(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
void shiftOut2(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6,uint8_t data7,uint8_t data8,
              uint8_t data9,uint8_t data10,uint8_t data11,uint8_t data12,uint8_t data13,uint8_t data14,uint8_t data15,uint8_t dat16);

void test_8up_8down1();
void test_8up_8down2();
void test_4up_4down();
void test_4down_4up();
void test_1down_1up();
void test_1up_1down();
void all_down();
void all_up();
void sensor1_data();
void sensor2_data();

void UART_DATA_PROCESS();
bool rqsNotify;
unsigned long prvMillis;
//#define INTERVAL_READ 1000
#define INTERVAL_READ 300
int valNotify;
#define MAX_VALNOTIFY 255
int value2=1;
int ain = 0;
char* filename_without_ext_mem;


const int maxStringLength = 20;
const char* fileName = "foo.txt"; // Change this to the name of your binary file
// Define the termination character
char terminationChar = '\n';
// Create a buffer to store the received string
char receivedString[maxStringLength];
int stringIndex = 0;
SPIClass spi = SPIClass(HSPI);
std::string dynamicString = "Initial Value getting displayed hello123456789 my self Nanda";
float temperature=23.5;
static int file_check=0;
static int file_check2=0;


struct struc_variable
  {
  uint8_t myVariable1 = 0;
  uint8_t myVariable2 = 0;
  uint8_t myVariable3 = 0;
  uint8_t myVariable4 = 0;
  uint8_t myVariable5 = 0;
  uint8_t myVariable6 = 0;
  uint8_t myVariable7 = 0;
  uint8_t myVariable8 = 0;
  uint8_t myVariable9 = 0;
  uint8_t myVariable10 = 0;
  uint8_t myVariable11= 0;
  uint8_t myVariable12= 0;
  uint8_t myVariable13= 0;
  uint8_t myVariable14= 0;
  uint8_t myVariable15= 0;
  uint8_t myVariable16= 0;
  }e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16;


  void clearData(struct struc_variable *connector) 
  {
    // Assign default values or clear memory
    connector->myVariable1 = 0;
    connector->myVariable2 = 0;
    connector->myVariable3 = 0;
    connector->myVariable4 = 0;
    connector->myVariable5 = 0;
    connector->myVariable6 = 0;
    connector->myVariable7 = 0;
    connector->myVariable8 = 0;
    connector->myVariable9 = 0;
    connector->myVariable10 = 0;
    connector->myVariable11= 0;
    connector->myVariable12 = 0;
    connector->myVariable13 = 0;
    connector->myVariable14 = 0;
    connector->myVariable15 = 0;
    connector->myVariable16 = 0;
    
  }

int8_t shiftIn1(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) 
{
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i)
   {
		digitalWrite(clockPin, HIGH);
		if (bitOrder == LSBFIRST)///
			value |= digitalRead(dataPin) << i;
		else
			value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, LOW);
	}
	return value;
}

void shiftOut1(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;
  //uint64_t val;

	for (i = 0; i < 8; i++)  
  {
    
		if (bitOrder == LSBFIRST) ///
    {
			digitalWrite(dataPin, val & 1);
			val >>= 1;
		} 
    else 
    {	
			digitalWrite(dataPin, (val & 128) != 0);
			val <<= 1;
		}
			
		digitalWrite(clockPin, HIGH);
    delayMicroseconds(0.5);  // for esp32 optimization 
		digitalWrite(clockPin, LOW);		
	}
}


void shiftOut2(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6,uint8_t data7,uint8_t data8,
              uint8_t data9,uint8_t data10,uint8_t data11,uint8_t data12,uint8_t data13,uint8_t data14,uint8_t data15,uint8_t data16)
{
	uint8_t i=0;
  //uint64_t val;
  //digitalWrite(EN_Pin, HIGH);
	for (i = 0; i < 8; i++)  
  {
    
	  digitalWrite(data_Pin1, (data1 & 128) != 0);
		data1 <<= 1;
    digitalWrite(data_Pin2, (data2 & 128) != 0);
		data2 <<= 1;
    digitalWrite(data_Pin3, (data3 & 128) != 0);
		data3 <<= 1;
    digitalWrite(data_Pin4, (data4 & 128) != 0);
		data4 <<= 1;
    digitalWrite(data_Pin5, (data5 & 128) != 0);
		data5 <<= 1;
    digitalWrite(data_Pin6, (data6 & 128) != 0);
		data6 <<= 1;
    digitalWrite(data_Pin7, (data7 & 128) != 0);
		data7 <<= 1;
    digitalWrite(data_Pin8, (data8 & 128) != 0);
		data8 <<= 1;
    digitalWrite(data_Pin9, (data9 & 128) != 0);
		data9 <<= 1;
    digitalWrite(data_Pin10, (data10 & 128) != 0);
		data10 <<= 1;
    digitalWrite(data_Pin11, (data11 & 128) != 0);
		data11 <<= 1;
    digitalWrite(data_Pin12, (data12 & 128) != 0);
		data12 <<= 1;
    digitalWrite(data_Pin13, (data13 & 128) != 0);
		data13 <<= 1;
    digitalWrite(data_Pin14, (data14 & 128) != 0);
		data14 <<= 1;
    digitalWrite(data_Pin15, (data15 & 128) != 0);
		data15 <<= 1;
    digitalWrite(data_Pin16, (data16 & 128) != 0);
		data16 <<= 1;
    delayMicroseconds(1);  // for esp32 optimization
		digitalWrite(clk_Pin, HIGH);
    delayMicroseconds(1);  // for esp32 optimization
		digitalWrite(clk_Pin, LOW);		
   // delayMicroseconds(1);  // for esp32 optimization		
	}
    //digitalWrite(EN_Pin, LOW);
    //delay(3);
}

void shiftOut3(uint8_t data1,uint8_t data2,uint8_t data3,uint8_t data4,uint8_t data5,uint8_t data6,uint8_t data7,uint8_t data8,
              uint8_t data9,uint8_t data10,uint8_t data11,uint8_t data12,uint8_t data13,uint8_t data14,uint8_t data15,uint8_t data16)
{
	uint8_t i=0;
  //uint64_t val;
   
	for (i = 0; i < 8; i++)  
  {
   
   
	  digitalWrite(data_Pin1, (data1 & 1));
		data1 >>= 1;
    digitalWrite(data_Pin2, (data2 & 1));
		data2 >>= 1;
    digitalWrite(data_Pin3, (data3 & 1) );
		data3 >>= 1;
    digitalWrite(data_Pin4, (data4 & 1) );
		data4 >>= 1;
    digitalWrite(data_Pin5, (data5 & 1) );
		data5 >>= 1;
    digitalWrite(data_Pin6, (data6 & 1));
		data6 >>= 1;
    digitalWrite(data_Pin7, (data7 & 1) );
		data7 >>= 1;
    digitalWrite(data_Pin8, (data8 & 1) );
		data8 >>= 1;
    digitalWrite(data_Pin9, (data9 & 1) );
		data9 >>= 1;
    digitalWrite(data_Pin10, (data10 & 1) );
		data10 >>= 1;
    digitalWrite(data_Pin11, (data11 & 1) );
		data11 >>= 1;
    digitalWrite(data_Pin12, (data12 & 1) );
		data12 >>= 1;
    digitalWrite(data_Pin13, (data13 & 1) );
		data13 >>= 1;
    digitalWrite(data_Pin14, (data14 & 1) );
		data14 >>= 1;
    digitalWrite(data_Pin15, (data15 & 1) );
		data15 >>= 1;
    digitalWrite(data_Pin16, (data16 & 1) );
		data16 >>= 1;
    delayMicroseconds(1);  // for esp32 optimization
		digitalWrite(clk_Pin, HIGH);
    delayMicroseconds(0.5);
		digitalWrite(clk_Pin, LOW);
    //delayMicroseconds(1);		
	}
    
    
}

class MyNotifyCharacteristic : public BLECharacteristicCallbacks {
public:
    // This function will be called when a notification is sent
    void onNotify(BLECharacteristic *pCharacteristic) override {
        Serial.println("Notification sent.");
    }

    // This function will send a notification with the combined string
    void notifyWidthHeightCharacteristic(const String &combinedString) {
        pCharacteristic3->setValue(combinedString.c_str()); // Set value as a C-string
        pCharacteristic3->notify();
        Serial.print("Notification sent: ");
        Serial.println(combinedString.c_str());
    }

    // Set the characteristic to use for notifications
    void setCharacteristic(BLECharacteristic *characteristic) {
        pCharacteristic3 = characteristic;
    }
};

MyNotifyCharacteristic notifyCallbacks;
// class writeHeightCallbacks : public BLECharacteristicCallbacks {
// public:
//     void onWrite(BLECharacteristic *pCharacteristic) override {
//         std::string height_var = pCharacteristic2->getValue();
//         Serial.print("Received write: ");
//         Serial.println(height_var.c_str());
//         writeHeightToEEPROM(height_var);
//     }
// };
    class WriteFileCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string filename = pCharacteristic4->getValue();
        Serial.print("Received write: ");
        Serial.println(filename.c_str());
        writeStringToEEPROM(filename);
        readBMPDimensions(filename.c_str());
        readBMPDimensions2(filename.c_str());
        
        // EEPROM.write(filename); // Write the data to EEPROM
        // EEPROM.commit();
        // Serial.print("filename written to EEPROM: ");
        //     Serial.println(filename);
        //  int length = strlen(filename);
  
        //       for (int i = 0; i < length; i++) 
        //       {
        //           EEPROM.write(i, filename[i]); // Write each character of the string to EEPROM
        //       }
        //     EEPROM.write(length, '\0'); // Null-terminate the string in EEPROM
        //     EEPROM.commit(); // Commit the data to EEPROM
       

    }

    void onRead(BLECharacteristic *pCharacteristic) override {
        // Optional: handle read requests
        
    }

};

void writeStringToEEPROM(const std::string &filename) {
    int length = filename.length(); // Get the length of the string
    
    // Ensure we do not exceed the EEPROM size
    if (length + 1 > EEPROM.length()) {
        Serial.println("String is too long to fit in EEPROM");
        return;
    }

    for (int i = 0; i < length; i++) {
        EEPROM.write(i, filename[i]); // Write each character of the string to EEPROM
    }
    EEPROM.write(length, '\0'); // Null-terminate the string in EEPROM
    EEPROM.commit(); // Commit the data to EEPROM
    height_var=0;
    EEPROM.write(21,height_var);
    EEPROM.commit();
}
void writeHeightToEEPROM(const std::string &height_var) {
    // Convert string to integer
    int height = std::stoi(height_var);

    // Check if height is within the range of uint8_t
    if (height < 0 || height > 255) {
        Serial.println("Height value out of range (0-255).");
        return;
    }

    // Write the height as a byte to EEPROM
    EEPROM.write(21, static_cast<uint8_t>(height));
    EEPROM.commit(); // Commit the changes to EEPROM
}
void listDir(fs::FS &fs, const char * dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);


  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }


  File file = root.openNextFile();
  while(file)
  {
    if(file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.println(file.name());
      String fileName = file.name();
       if (fileName.endsWith(".bmp")) 
            {
              bmp_count+=1;
            }
      //Serial.print("  SIZE: ");
      //Serial.println(file.size());
    }
    file = root.openNextFile();
  }
   Serial.printf("Total BMP file in the Card =");
  Serial.println(bmp_count);
}


void createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}


void removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

uint16_t read16() {
  uint16_t result;
  file.read((uint8_t*)&result, sizeof(result));
  return result;
}

// Helper function to read a 32-bit little-endian integer from the BMP file
uint32_t read32() {
  uint32_t result;
  file.read((uint8_t*)&result, sizeof(result));
  return result;
}
void readBMPDimensions2(const char* filename)
{
   file = SD.open(filename, FILE_READ);
  
  if(file)
  {
    file.seek(18);
    width = read32();
    height = read32();
    Serial.print("Width: ");
    Serial.println(width);
    Serial.print("Height: ");
    Serial.println(height);
    // Check if it's a 1-bit BMP file
  }
  file.close();
}
void readBMPDimensions(const char* filename)
{
   Serial.print("File-Name=");
    Serial.println(filename);
  file = SD.open(filename, FILE_READ);
  if (!file) 
  {
    Serial.println("Failed to open BMP file");
    return;
  }

  // Read and validate BMP header
  if(read16() != 0x4D42) 
  {
    Serial.println("Not a valid BMP file");
    file.close();
    return;
  }
  if(file)
  {
    file.seek(18);
    width = read32();
    height = read32();
    Serial.print("Width: ");
    Serial.println(width);
    Serial.print("Height: ");
    Serial.println(height);
    // trial & error
           
         temp_str=".";
          combinedString = width +temp_str+height;
          // notifyWidthHeightCharacteristic(combinedString);
          notifyCallbacks.notifyWidthHeightCharacteristic(combinedString);
          pCharacteristic3->setValue((uint8_t*)&combinedString, sizeof(combinedString));
          pCharacteristic3->notify();
          pCharacteristic2->setValue(selectedFile.c_str());
          pCharacteristic2->notify();
          Serial.println(selectedFile.c_str());
    // Check if it's a 1-bit BMP file
    if(read16() != 1) 
    {
      Serial.println("Only 1-bit BMP files are supported");
      file.close();
      return;
    }
    
      // Calculate the number of bytes per row (including padding)
    int bytesPerRow = (width + 7) / 8;
    file.seek(54);  // Move to the start of pixel data
    // Read and print pixel data
   // Serial.println("Pixel Data:");
    for (int y = 0; y < 1; y++) 
    {
      bitToSet=7;
      card_count=0;
      connector_count=1;
      Serial.print( "prev=");
      Serial.println( prev);
      for (int x = 0; x < width; x++) 
       {
          if(card_count==max_cardcount)
            {
              card_count =0;
              if(bitToSet==0)
              {
                if( connector_count== max_connector)
                {
                    connector_count=0;
                }
            
             }
             bitToSet--;
            }
      present=prev+3;
      file.seek(present);  // Move to the start of pixel data
      prev=present;
      //Serial.print("data in 54");
      uint8_t grayscaleValue = file.read() ? 0 : 1;

      byte data = grayscaleValue;
      if(data== 0 ||data==1)
      {
       //Serial.print( data);//nanda
        if(connector_count==1)
        {
          // Serial.println("connector1");
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable1 |= (1 << bitToSet);
              }
             //Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
               //Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable1 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable1 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable1 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable1 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable1 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable1 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable1 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable1 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable1 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==2)
        {
           //Serial.println("connector2");
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable2 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable2 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable2 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable2 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable2 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable2 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable2 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable2 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable2 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==3)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable3 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable3 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable3 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable3 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable3 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable3 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable3 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable3 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==4)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable4 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable4 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable4 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable4 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable4 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable4 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable4 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable4 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   


        else if(connector_count==5)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable5 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable5 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable5 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable5 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable5 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable5 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable5 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable5 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   

        else if(connector_count==6)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable6 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable6 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable6 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable6 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable6 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable6 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable6 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable6 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==7)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable7 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable7 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable7 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable7 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable7 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable7 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable7 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable7 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==8)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable8 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable8 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable8 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable8 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable8 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable8 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable8 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable8 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   

        else if(connector_count==9)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable9 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable9 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable9 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable9 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable9 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable9 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable9 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable9 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==10)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable10 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable10 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable10 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable10 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable10 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable10|= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable10 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable10 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==11)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable11 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable11 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable11 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable11 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable11|= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable11 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable11 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable11 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==12)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable12 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable12 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable12 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable12 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable12|= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable12 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable12 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable12 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==13)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable13 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable13 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable13 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable13 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable13 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable13 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable13 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable13 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
        else if(connector_count==14)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable14 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable14 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable14 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable14 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
              {
                e12.myVariable14 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable14 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable14 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable14 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   

        else if(connector_count==15)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable15 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable15 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable15 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable15 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
             {
                e12.myVariable15 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable15 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable15 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable15 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   

        else if(connector_count==16)
        {
            switch(card_count)
            {
              case 0:
              if (data== 1)
              {
                e1.myVariable16 |= (1 << bitToSet);
              }
             //  Serial.println(bitToSet);
              card_count=1;
             
              break;
              case 1:
              // Serial.println(card_count);
              if (data== 1)
              {
                e2.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=2;
              break;
              case 2:
              if (data== 1)
              {
                e3.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=3;
              break;
              case 3:
              if (data== 1)
              {
                e4.myVariable16 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=4;
              break;
              case 4:
              if (data== 1)
              {
                e5.myVariable16 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=5;
              break;
              case 5:
              if (data== 1)
              {
                e6.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=6;
              break;
              case 6:
              if (data== 1)
              {
                e7.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=7;
              break;
              case 7:
              if (data== 1)
              {
                e8.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=8;
              break;
              case 8:
              if (data== 1)
              {
                e9.myVariable16 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=9;
              break;
              case 9:
              if (data== 1)
              {
                e10.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=10;
              break;
              case 10:
              if (data== 1)
              {
                e11.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=11;
              break;
              case 11:
              if (data== 1)
               {
                e12.myVariable16 |= (1 << bitToSet);
              }
              //Serial.println(bitToSet);
              card_count=12;
              break;
              case 12:
              if (data== 1)
              {
                e13.myVariable16 |= (1 << bitToSet);
              }
              // Serial.println(bitToSet);
              card_count=13;
              break;
              case 13:
              if (data== 1)
              {
                e14.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=14;
              break;
              case 14:
              if (data== 1)
              {
                e15.myVariable16 |= (1 << bitToSet);
              }
               //Serial.println(bitToSet);
              card_count=15;
              break;
              case 15:
              if (data== 1)
              {
                e16.myVariable16 |= (1 << bitToSet);
                
              }
               //Serial.println(bitToSet);
               card_count=16;
              break;
              default :
              break;
            }   
        }   
      }
        if(bitToSet==0&&card_count==max_cardcount)
        { 
			     bitToSet=7;
           card_count =0;
           if( connector_count== max_connector)
           {
            connector_count=0;
           }
           if(connector_count==1)
            {
                connector_count=2;
               //Serial.println("Connector");
                //Serial.print(connector_count);
            }   
             else if(connector_count==2)
              {
                connector_count=3;
                // Serial.println("Connector");
                //Serial.print(connector_count);
              }
             else if(connector_count==3)
             {
				      connector_count=4;
              //Serial.println("Cnct");
              //Serial.print(connector_count);
             }
            else if(connector_count==4)
             {
				      connector_count=5;
              // Serial.println("Con");
              //Serial.print(connector_count);
             }
            else if(connector_count==5)
            {
				      connector_count=6;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==6)
            {
				      connector_count=7;
             // Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==7)
            {
				      connector_count=8;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==8)
            {
				      connector_count=9;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==9)
            {
				      connector_count=10;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==10)
            {
				      connector_count=11;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==11)
            {
				      connector_count=12;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==12)
            {
				      connector_count=13;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==13)
            {
				      connector_count=14;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
            else if(connector_count==14)
            {
				      connector_count=15;
              //Serial.println("Connector");
             //Serial.print(connector_count);
            }
             else if(connector_count==15)
            {
				      connector_count=16;
              //Serial.println("Connector");
              //Serial.print(connector_count);
            }
        }
      
      //Serial.print(" ");
      //uint8_t pixelData = bmpFile.read();

    }
      Serial.println();
      Serial.print("Present:=");
      Serial.println(prev);
    }

    if(height_var==height)
    {
      //height_var=0;
     // present=0;
     //prev=4661;
      //Serial.println("helloooonandaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa:=");
     // pick_clear_flag=1;
    }
   

   /*Serial.println("Data in array1:");
   Serial.println(e1.myVariable16,BIN);
   Serial.println("Data in array2:");
   Serial.println(e2.myVariable16,BIN);
   Serial.println("Data in array3:");
   Serial.println(e3.myVariable16,BIN);
   Serial.println("Data in array4:");
   Serial.println(e4.myVariable16,BIN);
   Serial.println("Data in array5:");
   Serial.println(e5.myVariable16,BIN);
   Serial.println("Data in array6:");
   Serial.println(e6.myVariable16,BIN);
   Serial.println("Data in array7:");
   Serial.println(e7.myVariable16,BIN);
   Serial.println("Data in array8:");
   Serial.println(e8.myVariable16,BIN);

    Serial.println("Data in array9:");
   Serial.println(e9.myVariable16,BIN);
   Serial.println("Data in array10:");
   Serial.println(e10.myVariable3,BIN);
   Serial.println("Data in array11:");
   Serial.println(e11.myVariable16,BIN);

   Serial.println("Data in array12:");
   Serial.println(e12.myVariable16,BIN);*/
 /////////////////////////////////////////////////////
    
     file.close();
  }
   

}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);


  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}


void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);


  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)){
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}


void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}


void deleteFile(fs::FS &fs, const char * path)
{
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
    temp_count=0;
  } else {
    Serial.println("Delete failed");
  }
}


void testFileIO(fs::FS &fs, const char * path)
{
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;
  if(file){
    len = file.size();
    size_t flen = len;
    start = millis();
    while(len){
      size_t toRead = len;
      if(toRead > 512){
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }


  file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }


  size_t i;
  start = millis();
  for(i=0; i<2048; i++){
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}


class MyServerCallbacks: public BLEServerCallbacks
{
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;


      rqsNotify = false;
      prvMillis = millis();
      Serial.println("Device connected");
      
      temp_count=0;
      temp_count2=0;
    };


    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      rqsNotify = false;
      Serial.println("Device disconnected");
      temp_count=0;
      temp_count2=0;
    }
};


void prcRead()
{
  if(deviceConnected){
    unsigned long curMillis = millis();
    if((curMillis-prvMillis) >= INTERVAL_READ)
    {
      int valAIO = 230;//nalogRead(PinAnalogIn);
      valNotify = map(valAIO, 0, 4096, 0, 255);
      //Serial.println(valNotify);
     
      rqsNotify = true;
      prvMillis = curMillis;
    }
  }
 
}

char* extract_filename_without_extension(const char* full_filename) 
{
   
    const char* last_dot = strrchr(full_filename, '/'); // Find the last occurrence of '.'

    if (last_dot != NULL) {
        // Allocate memory for the filename without extension
        filename_without_ext_mem = (char*)malloc((last_dot - full_filename + 1) * sizeof(char));

        // Copy characters before the last dot
        strncpy(filename_without_ext_mem, full_filename, last_dot - full_filename);
        filename_without_ext_mem[last_dot - full_filename] = '\0'; // Null-terminate the string
    } else {
        // If no dot found, just duplicate the full filename
        filename_without_ext_mem = strdup(full_filename);
    }

    return filename_without_ext_mem;
}

void separateString(String input)
 {
  char *endptr;
  int index = 0; // Index to keep track of the separated strings
  String tempString = ""; // Temporary string to store characters until a special character is found
  
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == '&' || c == '.') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings[index] = tempString;
  }
  
  // Print the separated strings
 /* for (int i = 0; i < 3; i++) {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings[i]);
  }*/

  if(max_cardcount!=strtol(separatedStrings[1].c_str(), &endptr, 10)||max_connector!=strtol(separatedStrings[2].c_str(), &endptr, 10))
  {

  max_cardcount=strtol(separatedStrings[1].c_str(), &endptr, 10);
  max_connector=strtol(separatedStrings[2].c_str(), &endptr, 10);

      EEPROM.write(10, max_cardcount); // Write the data to EEPROM
      EEPROM.commit(); // Commit the data to EEPROM
      delay(2);
      EEPROM.write(12, max_connector); // Write the data to EEPROM
      EEPROM.commit(); // Commit the data to EEPROM
      delay(2);
     // Serial.print("Maximum Card count=");
     // Serial.println(max_cardcount);
     // Serial.print("Maximum Connector count=");
     // Serial.println(max_connector);
  }


if (*endptr != '\0') {
    // Error handling: Input string contains invalid characters
    //printf("Error: Input string contains invalid characters\n");
} else {
    // Conversion successful, max_cardcount now holds the integer value
    //printf("max_cardcount: %ld\n", max_cardcount);
}


}


void separateString2(String input)
 {
    char *endptr;
    int index = 0; // Index to keep track of the separated strings
    String tempString = ""; // Temporary string to store characters until a special character is found
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == '&' || c == '.') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings2[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings2[index] = tempString;
  }
  
  if( height_var!=strtol(separatedStrings2[1].c_str(), &endptr, 10) && strtol(separatedStrings2[1].c_str(), &endptr, 10)!=0)
  {
      height_var=strtol(separatedStrings2[1].c_str(), &endptr, 10);
      //EEPROM.write(14, height_var); // Write the data to EEPROM
      EEPROMWriteInt(21, height_var);
      EEPROM.commit(); // Commit the data to EEPROM
      Serial.print("height_var=");
      Serial.println(height_var);
      prev=max_cardcount*max_connector*8;
      prev=prev*height_var;
      prev=prev*3;
      prev=prev+53;
      sensor_sel=0;
      sensor_sel1=0;
      temp_sens_check=0;
      mem_cpy_set=1;
      //Data_passing_clear();
      cleardata();
      //Data_passing_clear();
  }
if (*endptr != '\0') {
    // Error handling: Input string contains invalid characters
    //printf("Error: Input string contains invalid characters\n");
} else {
    // Conversion successful, max_cardcount now holds the integer value
    //printf("max_cardcount: %ld\n", max_cardcount);
}


}


void separateString3(String input)
 {
  char *endptr;
  int index = 0; // Index to keep track of the separated strings
  String tempString = ""; // Temporary string to store characters until a special character is found
  
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == '&' || c == '.') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings3[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings3[index] = tempString;
  }
  
 //Print the separated strings
 /*for (int i = 0; i < 3; i++) {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings3[i]);
  }*/

        filename_without_ext_fun = String(separatedStrings3[1]);
   

}


void separateString4(String input)
 {
  char *endptr;
  int index = 0; // Index to keep track of the separated strings
  String tempString = ""; // Temporary string to store characters until a special character is found
  
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == '&' || c == '.') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings4[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings4[index] = tempString;
  }
  
 //Print the separated strings
/* for (int i = 0; i < 3; i++) 
 {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings4[i]);
  }*/
Serial.print("RL FLAG  :  ");
Serial.println(separatedStrings4[1]);
left_right_flag =strtol(separatedStrings4[1].c_str(), &endptr, 10);


EEPROM.write(15, left_right_flag); // Write the data to EEPROM
EEPROM.commit(); // Commit the data to EEPROM
Serial.print("RL FLAG check :  ");
Serial.println(left_right_flag);
        //filename_without_ext_fun = String(separatedStrings3[1]);


}


void separateString5(String input)
 {
  char *endptr;
  int index = 0; // Index to keep track of the separated strings
  String tempString = ""; // Temporary string to store characters until a special character is found
  
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == 'A' || c == 'A'||c == 'A') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings5[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings5[index] = tempString;
  }
  
 //Print the separated strings
 /*for (int i = 0; i < 4; i++) {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings5[i]);
  }*/

       left_right_flag =strtol(separatedStrings4[1].c_str(), &endptr, 10);

       lock_date=strtol(separatedStrings5[0].c_str(), &endptr, 10);
       lock_month=strtol(separatedStrings5[1].c_str(), &endptr, 10);
       lock_year=strtol(separatedStrings5[2].c_str(), &endptr, 10);
       Serial.print("Date =");
       Serial.println(lock_date);

       Serial.print("lock_month =");
       Serial.println(lock_month);
       Serial.print("lock_year =");
       Serial.println(lock_year);

       EEPROM.write(16, lock_date); // Write the data to EEPROM
       EEPROM.commit(); // Commit the data to EEPROM

       EEPROM.write(17, lock_month); // Write the data to EEPROM
       EEPROM.commit(); // Commit the data to EEPROM

       EEPROM.write(18, lock_year); // Write the data to EEPROM
       EEPROM.commit(); // Commit the data to EEPROM

}
void separateString6(String input)
 {
  char *endptr;
  int index = 0; // Index to keep track of the separated strings
  String tempString = ""; // Temporary string to store characters until a special character is found
  
  // Loop through each character of the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i); // Get the character at current index
    
    // Check if the character is a special character
    if (c == '/' || c == '&' || c == '.') {
      // If temporary string is not empty, store it in the array
      if (tempString != "") {
        separatedStrings6[index++] = tempString;
        tempString = ""; // Reset the temporary string
      }
    } else {
      tempString += c; // Add character to the temporary string
    }
  }
  
  // Store the last string in the array
  if (tempString != "") {
    separatedStrings6[index] = tempString;
  }
  
 //Print the separated strings
 for (int i = 0; i < 3; i++) 
 {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings4[i]);
  }

Serial.println(separatedStrings6[1]);
triggerTimeReached =strtol(separatedStrings6[1].c_str(), &endptr, 10);


EEPROM.write(19, triggerTimeReached); // Write the data to EEPROM
EEPROM.commit(); // Commit the data to EEPROM
Serial.print("triggerTimeReached :  ");
Serial.println(triggerTimeReached);
        //filename_without_ext_fun = String(separatedStrings3[1]);

  if(unlockstatus_count==0)
  {
  pCharacteristic->setValue(unlockstatus.c_str());
  pCharacteristic->notify();
  }
  unlockstatus_count=1;

}

void IRAM_ATTR handleSensor1Change() {
    if (digitalRead(sen1) == LOW) {
     
        sensor1Detected = true;
        sensor1NotDetected = false;
       // Serial.println("sensor1Detected");
    } else {
       //Data_passing_clear();
        sensor1Detected = false;
        sensor1NotDetected = true;
        // Serial.println("sensor1NotDetected");
    }
    count1++;
  count2++;
  count3++;
}

void IRAM_ATTR handleSensor2Change() {
 
    if (digitalRead(sen2) == LOW) {
        sensor2Detected = true;
        sensor2NotDetected = false;
        // Serial.println("sensor2Detected");
    } else {
       //Data_passing_clear();
        sensor2Detected = false;
        sensor2NotDetected = true;
        //Serial.println("sensor2NotDetected");
    }
}


void EEPROMWriteInt(int address, int32_t value) {
  EEPROM.write(address, (value >> 24) & 0xFF);      // Write the highest byte
  EEPROM.write(address + 1, (value >> 16) & 0xFF);  // Write the next highest byte
  EEPROM.write(address + 2, (value >> 8) & 0xFF);   // Write the next lowest byte
  EEPROM.write(address + 3, value & 0xFF);          // Write the lowest byte
}

int32_t EEPROMReadInt(int address) {
  int32_t value = 0;
  value = ((int32_t)EEPROM.read(address) << 24) |
          ((int32_t)EEPROM.read(address + 1) << 16) |
          ((int32_t)EEPROM.read(address + 2) << 8) |
          (int32_t)EEPROM.read(address + 3);
  return value;
}






void setup() 
{
  ESP.getFreeHeap();
  ESP.getHeapSize();
  setCpuFrequencyMhz(85);
  /*BLE set power*/ 
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9 ); // Set power for advertising
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9 ); // Set power for scanning
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9 ); // Set default power

  EEPROM.begin(25);
  Serial.begin(115200);
  pinMode(EN_Pin, OUTPUT);
  pinMode(clk_Pin, OUTPUT);
  pinMode(data_Pin1, OUTPUT);
  pinMode(data_Pin2, OUTPUT);
  pinMode(data_Pin3, OUTPUT);
  pinMode(data_Pin4, OUTPUT);
  pinMode(data_Pin5, OUTPUT);
  pinMode(data_Pin6, OUTPUT);
  pinMode(data_Pin7, OUTPUT);
  pinMode(data_Pin8, OUTPUT);
  pinMode(data_Pin9, OUTPUT);
  pinMode(data_Pin10, OUTPUT);
  pinMode(data_Pin11, OUTPUT);
  pinMode(data_Pin12, OUTPUT);
  pinMode(data_Pin13, OUTPUT);
  pinMode(data_Pin14, OUTPUT);
  pinMode(data_Pin15, OUTPUT);
  pinMode(data_Pin16, OUTPUT);
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);

 //attachInterrupt(digitalPinToInterrupt(sen1), countPulses, FALLING); // Attach interrupt to falling edge of sensor 1
  count1 = count2 = count3 = 0;
  rpm1 = rpm2 = rpm3 = 0;
  lastTime1 = lastTime2 = lastTime3 = millis(); // Initialize lastTime
  attachInterrupt(digitalPinToInterrupt(sen1), handleSensor1Change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sen2), handleSensor2Change, CHANGE);

  for(int i=1;i<=7;i++)
  {
    test_8up_8down2();
    delay(337);
    Data_passing_clear();
    test_8up_8down1();
    delay(337);
    Data_passing_clear();
    Serial.println(i);
  }
// RTC setup//
 Serial.println("Check1");
 URTCLIB_WIRE.begin(3, 2); // D3 and D4 on ESP8266
//rtc.set(0, 44, 07, 6, 22, 6, 24); // initial timing setup (second,minute,hour,dayOfWeek,date,month,year)
//  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  spi.begin(SCK, MISO, MOSI, CS);
 Serial.println("check4");
  if(!SD.begin(CS,spi,80000000)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }
 Serial.println("check2");
  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  listDir(SD, "/", 0);
  // Create the BLE Device
  BLEDevice::init("Marvel CPU Board1");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLEService *pService2 = pServer->createService(SERVICE_UUID2);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyNotifyCharacteristic());

  pCharacteristic2 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID2,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                      //BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic2->addDescriptor(new BLE2902());
 pCharacteristic2->setCallbacks(new MyNotifyCharacteristic());
//  pCharacteristic2->setCallbacks(new writeHeightCallbacks());
 
  pCharacteristic3 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID3,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic3->addDescriptor(new BLE2902());
pCharacteristic3->setCallbacks(new MyNotifyCharacteristic());
notifyCallbacks.setCharacteristic(pCharacteristic3);
  pCharacteristic4 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID4,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic4->addDescriptor(new BLE2902());
pCharacteristic4->setCallbacks(new MyNotifyCharacteristic());
pCharacteristic4->setCallbacks(new WriteFileCallbacks());
  pCharacteristic5 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID5,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic5->addDescriptor(new BLE2902());
 pCharacteristic5->setCallbacks(new MyNotifyCharacteristic());
  
  pCharacteristic6 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID6,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic6->addDescriptor(new BLE2902());
pCharacteristic6->setCallbacks(new MyNotifyCharacteristic());
  pCharacteristic11 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID11,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // Create a BLE Descriptor
  pCharacteristic11->addDescriptor(new BLE2902());
pCharacteristic11->setCallbacks(new MyNotifyCharacteristic());
  pCharacteristic22 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID22,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // Create a BLE Descriptor
  pCharacteristic22->addDescriptor(new BLE2902());
pCharacteristic22->setCallbacks(new MyNotifyCharacteristic());
  // Start the service
  pService->start();
  pService2->start();
  // Start advertising

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->addServiceUUID(SERVICE_UUID2);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
  File root = SD.open("/");
  char readData[100]; // Assuming maximum data length
  int address = 0;
  char ch;
  while ((ch = EEPROM.read(address)) != '\0' && address < 100)
  { // Read until null character or EEPROM size limit
    readData[address] = ch;
    Serial.println("eeprom read value22");
    address++;
  }
  readData[address] = '\0'; // Null-terminate the read data
  Serial.print("Data read from EEPROM: ");
  Serial.println(readData);
  Serial.println(sizeof(readData));
    //sddata.data15=readData;
  // memcpy(&string2, readData, sizeof(readData));

  // result2=string1+readData+string3;  this is for control board i.e esp32 client
  result2=readData;  // this is for mobile app
  Serial.print("eeprom read value=");
  Serial.println(result2);
  max_cardcount= EEPROM.read(10); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1  max_cardcount: ");
  Serial.println(max_cardcount);
  max_connector= EEPROM.read(12); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1 max_connector: ");
  Serial.println(max_connector);
 // height_var= 0;// Firstime program un comment this line 
  height_var= EEPROMReadInt(21);// First time program, comment this line 
  Serial.print("Data read from EEPROM1 height_var: ");
  Serial.println(height_var);
  int digit_int = atoi(readData);
  prev=max_cardcount*max_connector*8;
  //Serial.print("previous value=============================: ");
 // Serial.println(prev);
  prev=prev*height_var;
  //Serial.print("previous value=============================: ");
  //Serial.println(prev);
  prev=prev*3;
  prev=prev+53;
  //Serial.print("previous value=============================: ");
  Serial.println(prev);
  left_right_flag=EEPROM.read(15); // Read the data from EEPROM
  EEPROM.read(15); // Read the data from EEPROM
  Serial.print("left_right_flag ");
  Serial.println(left_right_flag);

/*machine Lock*/
  lock_date=EEPROM.read(16); // Read the data from EEPROM
  lock_month=EEPROM.read(17);
  lock_year=EEPROM.read(18);
  triggerTimeReached=EEPROM.read(19);
  mode_set=EEPROM.read(20);
  Serial.print("Mode=");
  Serial.println(mode_set);

}

void loop()
 {
   if(sensor1NotDetected == true|| sensor2NotDetected == true)
   {
        Data_passing_clear();
        sensor1NotDetected=false;
        sensor2NotDetected=false;
        //Serial.printf("Free heap: %d bytes\n", esp_get_free_heap_size());

   }

  unsigned long currentTime = millis();
  unsigned long elapsedTime1 = currentTime - lastTime1;
  unsigned long elapsedTime2 = currentTime - lastTime2;
  unsigned long elapsedTime3 = currentTime - lastTime3;

  if (elapsedTime1 >= 1000 && elapsedTime2 >= 1000 && elapsedTime3 >= 1000) { // Calculate RPM every second
    char result_RPM[10];
    RPM_flag+=1;
    //detachInterrupt(digitalPinToInterrupt(sen1)); // Disable interrupts
    rpm1 = (count1 * 60 * 1000) / (elapsedTime1 ); // Assuming 20 pulses per revolution and elapsed time in milliseconds
    rpm2 = (count2 * 60 * 1000) / (elapsedTime2 );
    rpm3 = (count3 * 60 * 1000) / (elapsedTime3); //
    unsigned int avgRPM = (rpm1 + rpm2 + rpm3) / 3; // Calculate average RPM
    avgRPM=avgRPM*1.3;

    //Serial.print("Average RPM: ");
    //Serial.println(avgRPM);
    count1 = count2 = count3 = 0; // Reset counters
    lastTime1 = lastTime2 = lastTime3 = currentTime; // Update lastTime
    //attachInterrupt(digitalPinToInterrupt(sen1), countPulses, CHANGE); // Attach interrupt to falling edge of sensor 1 again

     sprintf( result_RPM, "%d", avgRPM); 
        combinedString88 = RPM_String +result_RPM;


          if(RPM_flag==20)
          {
          pCharacteristic->setValue((uint8_t*)&combinedString88, sizeof(combinedString88));
          pCharacteristic->notify();
          RPM_flag=0;

          }
  
  }
  

 // result2=string1+readData+string3;
    // digitalWrite(EN_Pin, HIGH);
 if(lock_year==rtc.year()&&lock_month==rtc.month()&&lock_date==rtc.day())
  {
     
     triggerTimeReached =0;
     EEPROM.write(19, triggerTimeReached); // Write the data to EEPROM
     EEPROM.commit();

      //Serial.print("left_right_flag  : ");
  }

///**********RTC*****************//
rtc_flag+=1;
if(rtc_flag==60000)
{
  if(triggerTimeReached)
  {
        rtc_flag=0;
  }

  rtc.refresh();
	/*Serial.print("RTC DateTime: ");
	Serial.print(rtc.year());
	Serial.print('/');
	Serial.print(rtc.month());
	Serial.print('/');
	Serial.print(rtc.day());

	Serial.print(' ');

	Serial.print(rtc.hour());
	Serial.print(':');
	Serial.print(rtc.minute());
	Serial.print(':');
	Serial.print(rtc.second());

	Serial.print(" DOW: ");
	Serial.print(rtc.dayOfWeek());

	Serial.print(" - Temp: ");
	Serial.print(rtc.temp()  / 100);

	Serial.println();*/
}


///**********RTC*****************//
 char file1[6]="F1";
 char file2[6]="F2";
 char file3[6]="F3";

    // notify changed value
    
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }

    if (deviceConnected) 
    {
      //Serial.println("start connected");
        if(rqsNotify)
        {
          rqsNotify = false;
          value = valNotify;
       
       if(temp_count==0)
       {
      
         delay(1500);
        
          root = SD.open("/");
          File file = root.openNextFile();
          int x=0;
          while (file) 
          { 
            x+=1;
            String fileName = file.name();
           // Serial.print( "x value=");
           // Serial.print( x); 

            // if(x<=bmp_count)
            //{
            if (fileName.endsWith(".bmp")) 
            {
              pCharacteristic->setValue(fileName.c_str());
              pCharacteristic->notify();
              delay(300); // Delay between notifications
              Serial.println(file.name());
              //const char* full_filename = file.name();
             // char* filename_without_ext = extract_filename_without_extension(full_filename);
              //Serial.println(filename_without_ext);
              //free(filename_without_ext); 
            }
             
           // }
            //file.close();
            file = root.openNextFile();
             temp_count=1;
             lockstatus_count=0;
             unlockstatus_count=0;
          }

          char result_pcount[10]; 
          sprintf( result_pcount, "%d", height_var); 
          pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
          // pCharacteristic4->setValue((uint8_t*)&height_var, 4);
          pCharacteristic4->notify();
       }

          	//Serial.println("hello world");

          std::string receivedData  = pCharacteristic2->getValue();// Display reading data file selection 
         
        selectedFile = (receivedData.find(".bmp") != -1) ? receivedData : selectedFile;

         
         
         
        //  WriteFileCallbacks();
         // Serial.print("Received data: ");
          //Serial.println(receivedData.c_str());
         
        const char*full_filename =receivedData.c_str();
        char* filename_without_ext = extract_filename_without_extension(full_filename);
        //// Serial.println("filename_without_ext");
      ////  Serial.println(filename_without_ext);
        char filename_without_ext1[] = "*UP"; //
        char* result = strstr(filename_without_ext1, filename_without_ext);
        char filename_without_ext11[] = "CH"; //
        char* result1 = strstr(filename_without_ext11, filename_without_ext);
        char filename_without_ext22[] = "DL";   // dlete option check 
        char* result22 = strstr(filename_without_ext22, filename_without_ext);

        char filename_without_ext33[] = "LR";   // left to right design chnage 
        char* result33 = strstr(filename_without_ext33, filename_without_ext);
        

        char filename_without_ext44[] = "AA";   // left to right design chnage 
        char* result44 = strstr(filename_without_ext44, filename_without_ext);

        char filename_without_ext55[] = "MU";   // left to right design chnage 
        char* result55 = strstr(filename_without_ext55, filename_without_ext);
      
          if (filename_without_ext_fun) 
         {
          free(filename_without_ext_mem);
         }


         if (result != nullptr) 
         { 
               //if(temp_up_flag==1)
               //{

               //Serial.print("Before height_var=");//nanda
              // Serial.println(height_var);
               separateString2(receivedData.c_str());
                //Serial.print(" delete File=================================");
               //}
               temp_up_flag=1;
         }
        
         else if(result22 != nullptr)   // delete file option 
         {
             separateString3(receivedData.c_str());
             string2=filename_without_ext_fun;
             result222=string1+string2+string3;
             Serial.print(" delete File=");
             Serial.println(result222);
             //readBMPDimensions2(result2.c_str());
               deleteFile(SD, result222.c_str());
         }
          else if(result33 != nullptr)
         {
             separateString4(receivedData.c_str());
         }

         else  if(result44 != nullptr)
         {
             separateString5(receivedData.c_str());
              Serial.println(" Lock date =");
             //Serial.println(result2);
         }

         else if(result55!=nullptr)
         {
          separateString6(receivedData.c_str());
          lockstatus_count=0;
         }
         
        else
        {
        if(result1 != nullptr) //
         { 

           //Serial.print(" ADD File++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
               separateString3(receivedData.c_str());
              
               string2=filename_without_ext_fun;
               String newValue2 = String(string2.c_str());
               //Serial.println(" newvalue2***************************====");
               //Serial.println(newValue2);
               char fileName1[40]; // Adjust size as needed
              snprintf(fileName1, sizeof(fileName1), "/%s.bmp", newValue2);
        // Check if the specific file exists
             if (SD.exists(fileName1)) {
              //Serial.print(fileName1);
              //Serial.println(" exists.");
               file_check2=1;
              } else {
                file_check2=0;
               // Serial.print(fileName1);
                //Serial.println(" does not exist.");
              }
                 if((newValue2 != previousValue2) && (file_check2==1))
                 {
                      cleardata();
                      mem_cpy_set=1;
                      sensor_sel2=0;
                      previousValue2=newValue2;
                      height_var=0;
                      prev=53;
                      present=0;
                      first_set_flag=0;
                      //EEPROM.write(14, height_var); // Write the data to EEPROM
                      EEPROMWriteInt(21, height_var);
                      EEPROM.commit(); // Commit the data to EEPROM
                     // Serial.println(" ************************************************************************************");
                 }
              // Serial.println("NANDA NANDA NANDA NANDA NANDA NANDA NANDA");
         }
        else
         {
            separateString(receivedData.c_str());
            string2=filename_without_ext;
            //Serial.print(" ADD File------------------------------------------------------------------------------------------");
         }
        String newValue = String(string2.c_str());
        //Serial.println(" newvalue***************************====");
       // Serial.println(newValue);
        char fileName[20]; // Adjust size as needed
        snprintf(fileName, sizeof(fileName), "/%s.bmp", newValue);
        // Check if the specific file exists
        if (SD.exists(fileName)) {
          //Serial.print(fileName);
          //Serial.println(" exists.");
          file_check=1;
        } else {
          file_check=0;
          //Serial.print(fileName);
          //Serial.println(" does not exist.");
        }
        if((newValue != previousValue||temp_count2==0)&& (file_check==1))
        {
           char result_width[10];
           char result_height[10]; 
           
          // height_var=0;
          // sensor_sel=0;
          // sensor_sel1=0;
          // temp_sens_check=0;
           previousValue = newValue;
           const char* stringValue=previousValue.c_str();
           int length = strlen(stringValue);
          if(length!=0)
          {

              for (int i = 0; i < length; i++) 
              {
                  EEPROM.write(i, previousValue[i]); // Write each character of the string to EEPROM
              }
            EEPROM.write(length, '\0'); // Null-terminate the string in EEPROM
            EEPROM.commit(); // Commit the data to EEPROM

          result2=string1+previousValue+string3;
          //Serial.println("result22222222222222222222222222222222222222222222");
          // Serial.println(result2);
         //readBMPDimensions2(result2.c_str());

          if (SD.exists(result2.c_str()))
          {
           readBMPDimensions2(result2.c_str());
           sprintf( result_width, "%d", width); 
           sprintf( result_height, "%d", height); 
          char result_pcount[10]; 
           temp_str=".";
          combinedString = result_width +temp_str+result_height;
          // notifyWidthHeightCharacteristic(combinedString);
          notifyCallbacks.notifyWidthHeightCharacteristic(combinedString);
          pCharacteristic3->setValue((uint8_t*)&combinedString, sizeof(combinedString));
          pCharacteristic3->notify();
          pCharacteristic2->setValue(selectedFile.c_str());
          pCharacteristic2->notify();
          Serial.println("combinedString==========================="); 
          Serial.println(combinedString);

           Serial.print("Selected File for Design: ");
          Serial.println(selectedFile.c_str());
                    // height_var=0;
           sensor_sel=0;
           sensor_sel1=0;
           temp_sens_check=0;
          }
          
          //free(filename_without_ext); 
          }
          char result_pcount[10]; 
          sprintf( result_pcount, "%d", height_var); 
          pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
          // pCharacteristic4->setValue((uint8_t*)&height_var, 4);
          pCharacteristic4->notify();
          temp_count2=1;
        }
        }
         if (pCharacteristic11 != nullptr) 
        {
          receivedData3  = pCharacteristic11->getValue();// Display reading data file selection
          // Serial.print("Received data: ");
          // Serial.println(receivedData3.c_str());
          //Serial.println(strcmp(comp_string,receivedData3));
           const char* receivedDataCStr = receivedData3.c_str();
          if (strcmp(receivedDataCStr, comp_string5) == 0)
           {
               mode_set=0;
              
               if(mode_zero_flag==1)
               {
                  mem_cpy_set=1;
                  mode_zero_flag=0;
                  //Serial.print("Received dataaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa: ");
                  sensor_sel=0;
                  sensor_sel1=0;
                  if(height_var==0)
                  {
                    prev=53;
                  }
                  else
                  {
                    prev=max_cardcount*max_connector*8;
                    prev=prev*height_var;
                    prev=prev*3;
                    prev=prev+53;
                  }
               }
 
           } 
          else if (strcmp(receivedDataCStr, comp_string1) == 0)
           {
               mode_set=1;
               mode_zero_flag=1;
               
           } 
          else if (strcmp(receivedDataCStr, comp_string2) == 0)
           {
               mode_set=2;
               mode_zero_flag=1;
           } 
           else if (strcmp(receivedDataCStr, comp_string3) == 0)
           {
               mode_set=3;
               mode_zero_flag=1;
           } 
           else if (strcmp(receivedDataCStr, comp_string4) == 0)
           {
               mode_set=4;
               mode_zero_flag=1;
           } 
           else
           {
               mode_set=0;
               //mode_zero_flag=1;
           }
            EEPROM.write(20, mode_set); // Write the data to EEPROM
            EEPROM.commit(); // Commit the data to EEPROM
            //Serial.print("Mode_Set=");
           // Serial.println(mode_set);
        }
          value2++;


          if(value2==250)
          {
            value2=0;
          }
          
        }
    }
     

    prcRead();

  // UART_DATA_PROCESS();
    //
       if(sensor1NotDetected == true|| sensor2NotDetected == true)
   {
        Data_passing_clear();
        sensor1NotDetected=false;
        sensor2NotDetected=false;
       // Serial.printf("Free heap: %d bytes\n", esp_get_free_heap_size());//nanda

   }
  if(mem_cpy_set==1 && mode_set==0)
  {
      if(height_var==height)
    {
    // height_var=0;
      present=0;
      prev=53;
     
    }

      
      readBMPDimensions(result2.c_str());
      mem_cpy_set=0;
  }
  data_process();
     if(sensor1NotDetected == true|| sensor2NotDetected == true)
   {
        Data_passing_clear();
        sensor1NotDetected=false;
        sensor2NotDetected=false;
      //Serial.printf("Free heap: %d bytes\n", esp_get_free_heap_size());//nanda

   }

  // Serial.println("height_var............................===========");
   //Serial.println(height_var);


 }

void UART_DATA_PROCESS()
{
  if (Serial.available() > 0)
  {
    char incomingChar = Serial.read(); // Read the incoming character


    // Check if the received character is the termination character
    if (incomingChar == terminationChar)
    {
      // Null-terminate the string
      receivedString[stringIndex] = '\0';


      // Compare the received string with a predefined string
      if (strcmp(receivedString, "Hello") == 0)
      {
        Serial.println("Received: Hello");
      } else if (strcmp(receivedString, "World") == 0)
      {
        Serial.println("Received: World");
      } else
      {
        //Serial.println("Unknown command");
      }


      // Reset the string index for the next string
      stringIndex = 0;
    }
}
}
void Data_passing_clear() // 
{

      digitalWrite(EN_Pin, HIGH);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      //delay(1);
      digitalWrite(EN_Pin, LOW);
      delay(1);
      digitalWrite(EN_Pin, LOW);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      //delay(1);
      digitalWrite(EN_Pin, HIGH);
      delay(3);
}

void Data_passing(int con_size)
{

if(left_right_flag==2)
{

//digitalWrite(EN_Pin, LOW);
digitalWrite(EN_Pin, HIGH);
shiftOut2(e16.myVariable1,e16.myVariable2,e16.myVariable3,e16.myVariable4,e16.myVariable5,e16.myVariable6,e16.myVariable7,e16.myVariable8,
          e16.myVariable9,e16.myVariable10,e16.myVariable11,e16.myVariable12,e16.myVariable13,e16.myVariable14,e16.myVariable15,e16.myVariable16);

shiftOut2(e15.myVariable1,e15.myVariable2,e15.myVariable3,e15.myVariable4,e15.myVariable5,e15.myVariable6,e15.myVariable7,e15.myVariable8,
          e15.myVariable9,e15.myVariable10,e15.myVariable11,e15.myVariable12,e15.myVariable13,e15.myVariable14,e15.myVariable15,e15.myVariable16); 


shiftOut2(e14.myVariable1,e14.myVariable2, e14.myVariable3,e14.myVariable4,e14.myVariable5,e14.myVariable6,e14.myVariable7,e14.myVariable8,
          e14.myVariable9,e14.myVariable10,e14.myVariable11,e14.myVariable12,e14.myVariable13,e14.myVariable14,e14.myVariable15,e14.myVariable16);


shiftOut2(e13.myVariable1,e13.myVariable2,e13.myVariable3,e13.myVariable4,e13.myVariable5,e13.myVariable6,e13.myVariable7,e13.myVariable8,
          e13.myVariable9,e13.myVariable10,e13.myVariable11,e13.myVariable12,e13.myVariable13,e13.myVariable14,e13.myVariable15,e13.myVariable16);

shiftOut2(e12.myVariable1,e12.myVariable2,e12.myVariable3,e12.myVariable4,e12.myVariable5,e12.myVariable6,e12.myVariable7,e12.myVariable8,
          e12.myVariable9,e12.myVariable10,e12.myVariable11,e12.myVariable12,e12.myVariable13,e12.myVariable14,e12.myVariable15,e12.myVariable16);

shiftOut2(e11.myVariable1,e11.myVariable2,e11.myVariable3,e11.myVariable4,e11.myVariable5,e11.myVariable6,e11.myVariable7,e11.myVariable8,
          e11.myVariable9,e11.myVariable10,e11.myVariable11,e11.myVariable12,e11.myVariable13,e11.myVariable14,e11.myVariable15,e11.myVariable16); 


shiftOut2(e10.myVariable1,e10.myVariable2, e10.myVariable3,e10.myVariable4,e10.myVariable5,e10.myVariable6,e10.myVariable7,e10.myVariable8,
          e10.myVariable9,e10.myVariable10,e10.myVariable11,e10.myVariable12,e10.myVariable13,e10.myVariable14,e10.myVariable15,e10.myVariable16);


shiftOut2(e9.myVariable1,e9.myVariable2,e9.myVariable3,e9.myVariable4,e9.myVariable5,e9.myVariable6,e9.myVariable7,e9.myVariable8,
          e9.myVariable9,e9.myVariable10,e9.myVariable11,e9.myVariable12,e9.myVariable13,e9.myVariable14,e9.myVariable15,e9.myVariable16);

shiftOut2(e8.myVariable1,e8.myVariable2,e8.myVariable3,e8.myVariable4,e8.myVariable5,e8.myVariable6,e8.myVariable7,e8.myVariable8,
          e8.myVariable9,e8.myVariable10,e8.myVariable11,e8.myVariable12,e8.myVariable13,e8.myVariable14,e8.myVariable15,e8.myVariable16);

shiftOut2(e7.myVariable1,e7.myVariable2,e7.myVariable3,e7.myVariable4,e7.myVariable5,e7.myVariable6,e7.myVariable7,e7.myVariable8,
          e7.myVariable9,e7.myVariable10,e7.myVariable11,e7.myVariable12,e7.myVariable13,e7.myVariable14,e7.myVariable15,e7.myVariable16); 

shiftOut2(e6.myVariable1,e6.myVariable2,e6.myVariable3,e6.myVariable4,e6.myVariable5,e6.myVariable6,e6.myVariable7,e6.myVariable8,
          e6.myVariable9,e6.myVariable10,e6.myVariable11,e6.myVariable12,e6.myVariable13,e6.myVariable14,e6.myVariable15,e6.myVariable16);

shiftOut2(e5.myVariable1,e5.myVariable2,e5.myVariable3,e5.myVariable4,e5.myVariable5,e5.myVariable6,e5.myVariable7,e5.myVariable8,
          e5.myVariable9,e5.myVariable10,e5.myVariable11,e5.myVariable12,e5.myVariable13,e5.myVariable14,e5.myVariable15,e5.myVariable16);

shiftOut2(e4.myVariable1,e4.myVariable2,e4.myVariable3,e4.myVariable4,e4.myVariable5,e4.myVariable6,e4.myVariable7,e4.myVariable8,
          e4.myVariable9,e4.myVariable10,e4.myVariable11,e4.myVariable12,e4.myVariable13,e4.myVariable14,e4.myVariable15,e4.myVariable16);


shiftOut2(e3.myVariable1,e3.myVariable2,e3.myVariable3,e3.myVariable4,e3.myVariable5,e3.myVariable6,e3.myVariable7,e3.myVariable8,
          e3.myVariable9,e3.myVariable10,e3.myVariable11,e3.myVariable12,e3.myVariable13,e3.myVariable14,e3.myVariable15,e3.myVariable16);

shiftOut2(e2.myVariable1,e2.myVariable2,e2.myVariable3,e2.myVariable4,e2.myVariable5,e2.myVariable6,e2.myVariable7,e2.myVariable8,
          e2.myVariable9,e2.myVariable10,e2.myVariable11,e2.myVariable12,e2.myVariable13,e2.myVariable14,e2.myVariable15,e2.myVariable16);

shiftOut2(e1.myVariable1,e1.myVariable2,e1.myVariable3,e1.myVariable4,e1.myVariable5,e1.myVariable6,e1.myVariable7,e1.myVariable8,
          e1.myVariable9,e1.myVariable10,e1.myVariable11,e1.myVariable12,e1.myVariable13,e1.myVariable14,e1.myVariable15,e1.myVariable16);
          digitalWrite(EN_Pin, LOW);

 delay(3);
  //digitalWrite(EN_Pin, HIGH);
   Serial.println("Unknown command");

}
else
{
//digitalWrite(EN_Pin, LOW);
//delay(10);
digitalWrite(EN_Pin, HIGH);
shiftOut3(e1.myVariable1,e1.myVariable2,e1.myVariable3,e1.myVariable4,e1.myVariable5,e1.myVariable6,e1.myVariable7,e1.myVariable8,
          e1.myVariable9,e1.myVariable10,e1.myVariable11,e1.myVariable12,e1.myVariable13,e1.myVariable14,e1.myVariable15,e1.myVariable16);
		  
shiftOut3(e2.myVariable1,e2.myVariable2,e2.myVariable3,e2.myVariable4,e2.myVariable5,e2.myVariable6,e2.myVariable7,e2.myVariable8,
          e2.myVariable9,e2.myVariable10,e2.myVariable11,e2.myVariable12,e2.myVariable13,e2.myVariable14,e2.myVariable15,e2.myVariable16);
		  
shiftOut3(e3.myVariable1,e3.myVariable2,e3.myVariable3,e3.myVariable4,e3.myVariable5,e3.myVariable6,e3.myVariable7,e3.myVariable8,
          e3.myVariable9,e3.myVariable10,e3.myVariable11,e3.myVariable12,e3.myVariable13,e3.myVariable14,e3.myVariable15,e3.myVariable16);
		  
shiftOut3(e4.myVariable1,e4.myVariable2,e4.myVariable3,e4.myVariable4,e4.myVariable5,e4.myVariable6,e4.myVariable7,e4.myVariable8,
          e4.myVariable9,e4.myVariable10,e4.myVariable11,e4.myVariable12,e4.myVariable13,e4.myVariable14,e4.myVariable15,e4.myVariable16);
		  
shiftOut3(e5.myVariable1,e5.myVariable2,e5.myVariable3,e5.myVariable4,e5.myVariable5,e5.myVariable6,e5.myVariable7,e5.myVariable8,
          e5.myVariable9,e5.myVariable10,e5.myVariable11,e5.myVariable12,e5.myVariable13,e5.myVariable14,e5.myVariable15,e5.myVariable16);
		  
shiftOut3(e6.myVariable1,e6.myVariable2,e6.myVariable3,e6.myVariable4,e6.myVariable5,e6.myVariable6,e6.myVariable7,e6.myVariable8,
          e6.myVariable9,e6.myVariable10,e6.myVariable11,e6.myVariable12,e6.myVariable13,e6.myVariable14,e6.myVariable15,e6.myVariable16);
		  
shiftOut3(e7.myVariable1,e7.myVariable2,e7.myVariable3,e7.myVariable4,e7.myVariable5,e7.myVariable6,e7.myVariable7,e7.myVariable8,
          e7.myVariable9,e7.myVariable10,e7.myVariable11,e7.myVariable12,e7.myVariable13,e7.myVariable14,e7.myVariable15,e7.myVariable16);
		  
shiftOut3(e8.myVariable1,e8.myVariable2,e8.myVariable3,e8.myVariable4,e8.myVariable5,e8.myVariable6,e8.myVariable7,e8.myVariable8,
          e8.myVariable9,e8.myVariable10,e8.myVariable11,e8.myVariable12,e8.myVariable13,e8.myVariable14,e8.myVariable15,e8.myVariable16);
		  
shiftOut3(e9.myVariable1,e9.myVariable2,e9.myVariable3,e9.myVariable4,e9.myVariable5,e9.myVariable6,e9.myVariable7,e9.myVariable8,
          e9.myVariable9,e9.myVariable10,e9.myVariable11,e9.myVariable12,e9.myVariable13,e9.myVariable14,e9.myVariable15,e9.myVariable16);
		  
shiftOut3(e10.myVariable1,e10.myVariable2, e10.myVariable3,e10.myVariable4,e10.myVariable5,e10.myVariable6,e10.myVariable7,e10.myVariable8,
          e10.myVariable9,e10.myVariable10,e10.myVariable11,e10.myVariable12,e10.myVariable13,e10.myVariable14,e10.myVariable15,e10.myVariable16);


shiftOut3(e11.myVariable1,e11.myVariable2,e11.myVariable3,e11.myVariable4,e11.myVariable5,e11.myVariable6,e11.myVariable7,e11.myVariable8,
          e11.myVariable9,e11.myVariable10,e11.myVariable11,e11.myVariable12,e11.myVariable13,e11.myVariable14,e11.myVariable15,e11.myVariable16);

shiftOut3(e12.myVariable1,e12.myVariable2,e12.myVariable3,e12.myVariable4,e12.myVariable5,e12.myVariable6,e12.myVariable7,e12.myVariable8,
          e12.myVariable9,e12.myVariable10,e12.myVariable11,e12.myVariable12,e12.myVariable13,e12.myVariable14,e12.myVariable15,e12.myVariable16); 	

shiftOut3(e13.myVariable1,e13.myVariable2,e13.myVariable3,e13.myVariable4,e13.myVariable5,e13.myVariable6,e13.myVariable7,e13.myVariable8,
          e13.myVariable9,e13.myVariable10,e13.myVariable11,e13.myVariable12,e13.myVariable13,e13.myVariable14,e13.myVariable15,e13.myVariable16);
		  
shiftOut3(e14.myVariable1,e14.myVariable2, e14.myVariable3,e14.myVariable4,e14.myVariable5,e14.myVariable6,e14.myVariable7,e14.myVariable8,
          e14.myVariable9,e14.myVariable10,e14.myVariable11,e14.myVariable12,e14.myVariable13,e14.myVariable14,e14.myVariable15,e14.myVariable16);


shiftOut3(e15.myVariable1,e15.myVariable2,e15.myVariable3,e15.myVariable4,e15.myVariable5,e15.myVariable6,e15.myVariable7,e15.myVariable8,
          e15.myVariable9,e15.myVariable10,e15.myVariable11,e15.myVariable12,e15.myVariable13,e15.myVariable14,e15.myVariable15,e15.myVariable16);

shiftOut3(e16.myVariable1,e16.myVariable2,e16.myVariable3,e16.myVariable4,e16.myVariable5,e16.myVariable6,e16.myVariable7,e16.myVariable8,
          e16.myVariable9,e16.myVariable10,e16.myVariable11,e16.myVariable12,e16.myVariable13,e16.myVariable14,e16.myVariable15,e16.myVariable16); 
digitalWrite(EN_Pin, LOW);	  

delay(3);
}
    
}

void cleardata(void)
{
    clearData(&e1);
    clearData(&e2);
    clearData(&e3);
    clearData(&e4);
    clearData(&e5);
    clearData(&e6);
    clearData(&e7);
    clearData(&e8);
    clearData(&e9);
    clearData(&e10);
    clearData(&e11);
    clearData(&e12);
    clearData(&e13);
    clearData(&e14);
    clearData(&e15);
    clearData(&e16);
}

void all_up()
{
  Data_passing_clear();
}

void all_down()
{
      digitalWrite(EN_Pin, HIGH);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      digitalWrite(EN_Pin, LOW);
      delay(3);
}

void test_8up_8down1()
{


       digitalWrite(EN_Pin, HIGH);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      digitalWrite(EN_Pin, LOW);
      delay(3);
}

void test_8up_8down2()
{


      digitalWrite(EN_Pin, HIGH);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
      shiftOut2(0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
      shiftOut2(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);  
      digitalWrite(EN_Pin, LOW);
      delay(3);
 //delay(10);
}


void test_1up_1down()
{
      digitalWrite(EN_Pin, HIGH);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      shiftOut2(0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA);
      digitalWrite(EN_Pin, LOW);
     delay(3);
}

void test_1down_1up()
{
      digitalWrite(EN_Pin, HIGH);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      shiftOut2(0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55);
      digitalWrite(EN_Pin, LOW);
      delay(3);
}

void test_4up_4down()
{
     
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      delay(3);
}

void test_4down_4up()
{
    
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      shiftOut2(0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0);
      delay(3);
}



void sensor1_data()
{
   if( mode_set==0)
  {
    Data_passing(max_connector);
    delay(0.3);
    Serial.println("Mode0");
  }
  else if(mode_set==1)
  {
    all_up();
  }
  else if(mode_set==2)
  {
    all_down();
  }
  else if(mode_set==3)
  {
    test_8up_8down1();
  }
  else if(mode_set==4)
  {
    test_1up_1down();
  }
  sensor1Detected=false;
  cleardata();  
}

void sensor2_data()
{ 
   if( mode_set==0)
  {
    Data_passing(max_connector);
    delay(0.3);
    Serial.println("Mode0");
  }
  else if(mode_set==1)
  {
    all_up();
    Serial.println("Mode1");
  }
  else if(mode_set==2)
  {
      all_down();
      Serial.println("Mode2");
  }
  else if(mode_set==3)
  {
    Serial.println("Mode3");
    test_8up_8down2();
  }
  else if(mode_set==4)
  {
    Serial.println("Mode4");
    test_1down_1up();
    
  }
  sensor2Detected=false;
  //Data_passing_clear();
  cleardata();
  //Data_passing_clear();
}

void data_process()
{
  if(triggerTimeReached==1)
{
if(sensor1Detected && sensor_sel==0 )
{  
  if(mode_set==0)
    {
    sensor_sel1=0;
    pick_clear_flag=0;
    if(mode_set==0)
    {
    if(height_var==height)
    {
      height_var=0;
      pick_clear_flag=1;
    }
    height_var+=1;

    //EEPROM.write(14, height_var); // Write the data to EEPROM
    EEPROMWriteInt(21, height_var);
    EEPROM.commit(); // Commit the data to EEPROM
   // Serial.print("height111111111111111111111111111111111111111=");
    //Serial.println(height_var);// nanda
    char result_pcount[10]; 
    sprintf( result_pcount, "%d", height_var); 
    pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
    // pCharacteristic4->setValue((uint8_t*)&height_var, 4);
    pCharacteristic4->notify();
    }
    //Serial.print("mem_cpy_set11=");
    //Serial.println(mem_cpy_set);
    mem_cpy_set=1;
    }
    sensor_sel2=0;
    sensor1_data();
    sensor_sel=1;
    temp_sens_check=1;
    cleardata();
    //Serial.print("pret111111111111111111111111111111111111111=");
    Serial.println(prev);
    //Serial.print("mem_cpy_set=");
    //Serial.println(mem_cpy_set);
}

else if(sensor1Detected && sensor_sel==1)
{
  uint32_t temp_flag=0;
  cleardata();
 if(mode_set==0)
 {
  if(pick_clear_flag==0)
  {
  if(height_var==height)
    {
      temp_flag= max_cardcount*max_connector*8;
      temp_flag=temp_flag*3;
      temp_flag=(temp_flag)*(height_var)+1;
      prev=temp_flag+53;
      temp_flag=0;
      heightcounter_reset=1;
    }
    else if(heightcounter_reset==1 && height_var==1)
    {
      prev=prev-53;
      prev=(prev*2)+53;
      heightcounter_reset=0;

    }
  }
    
   temp_flag= max_cardcount*max_connector*8;
   //Serial.print("heighthe222222222222222222222222222222222222222 Prev==");
   Serial.println(prev);
  // Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(temp_flag);
   temp_flag=temp_flag*3;
   //Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(temp_flag);
   prev=prev-(temp_flag*2);  // prev=prev-(4608*2); 
   //Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(prev);
   readBMPDimensions(result2.c_str());
      // Serial.print("mem_cpy_set12=");
    //Serial.println(mem_cpy_set);
   mem_cpy_set=1;
 }

   sensor1_data();
   cleardata();
   //Data_passing_clear();
       //Serial.print("mem_cpy_set=");
    //Serial.println(mem_cpy_set);
   
}
else if(sensor2Detected && sensor_sel1==0)
{
    pick_clear_flag=0;
    sensor_sel=0;
    if(mode_set==0)
    {
      if(height_var==height)
      {
        height_var=0;
        pick_clear_flag=1;
      }
      height_var+=1;
      //EEPROM.write(14, height_var); // Write the data to EEPROM
      EEPROMWriteInt(21, height_var);
      EEPROM.commit(); // Commit the data to EEPROM
      char result_pcount[10]; 
      sprintf( result_pcount, "%d", height_var); 
      pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
      pCharacteristic4->notify();
      //Serial.print("height22222222222222222222222222222222222222222222222222222=");
      //Serial.println(height_var);//nanda
         // Serial.print("mem_cpy_set13=");
    //Serial.println(mem_cpy_set);
      mem_cpy_set=1;
    }
    sensor2_data();
    sensor_sel1=1;
    cleardata();
    //Data_passing_clear();
    //Serial.print("pre22222222222222222222222222222222222222222222222222222=");
    Serial.println(prev);
       // Serial.print("mem_cpy_set=");
    //Serial.println(mem_cpy_set);
 
}
else if(sensor2Detected &&sensor_sel1==1)//else if(digitalRead(sen2) == LOW&&sensor_sel1==1&&temp_sens_check==1)
{
  uint32_t temp_flag=0;
  cleardata();
   if(mode_set==0)
   {
  if(pick_clear_flag==0)
  {
 if(height_var==height)
    {
      temp_flag= max_cardcount*max_connector*8;
      temp_flag=temp_flag*3;
      temp_flag=(temp_flag)*(height_var+1);
      prev=temp_flag+53;
      temp_flag=0;
    heightcounter_reset=1;
    }
    else if(heightcounter_reset==1 && height_var==1)
    {
      prev=prev-53;
      prev=(prev*2)+53;
      heightcounter_reset=0;
    }
  }
   
    temp_flag= max_cardcount*max_connector*8;
    Serial.println(temp_flag);
    temp_flag=temp_flag*3;
    prev=prev-(temp_flag*2);  // prev=prev-(4608*2); 
    Serial.println(prev);
    readBMPDimensions(result2.c_str());
        //Serial.print("mem_cpy_set14=");
    //Serial.println(mem_cpy_set);
    mem_cpy_set=1;
   }
    sensor2_data();
    cleardata();
       // Serial.print("mem_cpy_set=");
    //Serial.println(mem_cpy_set);
}
}
else
{
  if(lockstatus_count==0)
  {
  pCharacteristic->setValue(lockstatus.c_str());
  pCharacteristic->notify();
  unlockstatus_count=0;
  }
  lockstatus_count=1;
  
  if(rtc_flag==60000)
{

  rtc_flag=0;
  Serial.println( "Machine locked");
}
}
sensor1Triggered=false;
sensor2Triggered=false;

}

void sensorISR1() {
  sensor1Triggered = true; // Set sensor1Triggered flag in interrupt service routine
  //data_process();`
 // sensor1Triggered=false;
}


void sensorISR2() {
  sensor2Triggered = true; // Set sensor2Triggered flag in interrupt service routine
  //data_process();
  //sensor2Triggered=false;
}