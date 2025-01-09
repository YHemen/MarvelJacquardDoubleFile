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

int sen1=47;
int sen2=48;
int temp_up_flag=0;
uRTCLib rtc(0x68);
File file ;
File bodyfile ;
File borderfile ;
File root;

String string1="/";
String string2="";
String string3=".bmp";
String string4 = "";
String RPM_String="RPM.";
String previousValue = "";
String previousValue1 = "";
String previousValue2 = "";
String temp_str=".";
String combinedString="";
String combinedString88="";
String total_hook = "";
String result1;
String result2;
String result222;
String lockstatus="locked";
String unlockstatus="unlocked";
std::string receivedData3 ;
std::string selectedFile = ""; 
std::string secondfile = "";
char  comp_string1[]="allu";
char  comp_string2[]="alld";
char  comp_string3[]="8up8d";
char  comp_string4[]="1up1d";
char  comp_string5[]="default";
static int mode_set=0;
String separatedStrings[5];


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
uint16_t card_count=0;
uint16_t connector_count=1;
uint16_t max_cardcount=16;
uint16_t max_connector=16;
// static int width = 0;
// static int height= 0;
static int bodywidth = 0;
static int bodyheight= 0;
static int borderwidth = 0;
static int borderheight= 0;
uint16_t height_var=0;
uint16_t height_var1=0;
uint16_t ttl_hks = 0;
static uint32_t present=0;
static uint32_t prev=53;
static uint32_t present1=0;
static uint32_t prev1=53;
static uint16_t rtc_flag=0;
static int heightcounter_reset=0;

static uint16_t RPM_flag=0;

static uint32_t temp_present=0;
static uint32_t temp_prev=0;

static uint32_t temp_present1=0;
static uint32_t temp_prev1=0;

static int triggerTimeReached = 1;

String filename_without_ext_fun;
String filename_without_ext_fun1;

static uint16_t lockstatus_count=0;
static uint16_t unlockstatus_count=0;
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
static int lock_month=0;
static int lock_year=0;
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

void clearData(struct struc_variable *connector) {
  // Use an array of pointers to the structure variables and set them to 0
  uint8_t* vars[] = { 
    &connector->myVariable1, &connector->myVariable2, &connector->myVariable3,
    &connector->myVariable4, &connector->myVariable5, &connector->myVariable6,
    &connector->myVariable7, &connector->myVariable8, &connector->myVariable9,
    &connector->myVariable10, &connector->myVariable11, &connector->myVariable12,
    &connector->myVariable13, &connector->myVariable14, &connector->myVariable15,
    &connector->myVariable16
  };

  // Iterate over the array of pointers and set each to 0
  for (int i = 0; i < 16; i++) {
    *vars[i] = 0;
  }
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

class MyNotifyCharacteristic: public BLECharacteristicCallbacks {
  public:
    // This function will be called when a notification is sent
    void onNotify(BLECharacteristic * pCharacteristic) override {
      Serial.println("Notification sent.");
    }
};
MyNotifyCharacteristic notifyCallbacks;

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
    }
    file = root.openNextFile();
  }
   Serial.printf("Total BMP file in the Card =");
  Serial.println(bmp_count);
}
uint16_t read16(File &file) {
  uint16_t result;
  // Read the 16-bit value from the current position in the file
  file.read((uint8_t*)&result, sizeof(result));
  return result;
}

uint32_t read32(File &file) {
  uint32_t result;
  // Read the 32-bit value from the current position in the file
  file.read((uint8_t*)&result, sizeof(result));
  return result;
}
// Function to read the width and height of the BMP file
void getBMPDimensions(File &file, int &width, int &height) {
  // Move to the 18th byte (width starts at byte 18)
  file.seek(18);
  width = read32(file);  // Read width (4 bytes)
  
  // Move to the 22nd byte (height starts at byte 22)
  file.seek(22);
  height = read32(file);  // Read height (4 bytes)
  Serial.println(file.name());
  Serial.print("getBMPDimensions Width");
  Serial.println(width);
  Serial.print("getBMPDimensions Height");
  Serial.println(height);
}
  uint8_t readPixel(File &file, uint32_t pixelIndex) {
    // Calculate the offset for the pixel in the BMP file
    uint32_t offset = 54 + (pixelIndex * 3);  // 54 bytes header and 3 bytes per pixel
    file.seek(offset);  // Move to the position of the pixel in the file
    
    // Read 3 bytes (RGB), we only use Red for grayscale
    uint8_t r = file.read();  // Read Red channel (you can also use Green or Blue, but they should be similar in grayscale images)

    // Convert to 1-bit grayscale value (threshold at 128)
    uint8_t grayscaleValue = (r > 127) ? 1 : 0;  // If the pixel is brighter than 128, return 1, otherwise 0
    
    return grayscaleValue;  // Return the 1-bit grayscale value
}

// Function to print the pixel values of an entire row
    void printRowPixels(File &bodyfile, uint32_t bodywidth, uint32_t row) {
    bodyfile.seek(54);  // Skip BMP header (54 bytes)

    // Calculate the row offset, considering any padding that might exist
    uint32_t rowOffset = row * (bodywidth * 3 + (bodywidth * 3) % 4); // Row size including padding
    
    // Seek to the start of the desired row
    bodyfile.seek(54 + rowOffset);

    // Loop through each pixel in the row
    for (uint32_t col = 0; col < bodywidth; col++) {
        // Read the pixel value (R, G, B) and convert to 1-bit grayscale value
        uint8_t pixelValue = readPixel(bodyfile, col);

        // Print the pixel value (0 or 1) for each pixel
        Serial.print(pixelValue);
        Serial.print(" ");
    }

    // Print a newline after each row to separate rows in output
    Serial.println();
}


uint32_t navigateToRow(File &file, uint32_t width, uint32_t height, uint32_t row) { 
    Serial.print(row);
    // Ensure row is within bounds
    if (row >= height) {
        Serial.println("Invalid row number.");
        return 0;  // Return 0 for invalid row
    }

    uint32_t rowSize = (width * 3 + 3) & ~3;  // Ensures row size is 4-byte aligned
    uint32_t rowOffset = 54 + row * rowSize;  // Row start position in the BMP file
    file.seek(rowOffset);  // Seek to the start of the row

    // Read the RGB values of the last pixel in the row (3 bytes: Blue, Green, Red)
    uint8_t blue = file.read();    // Read Blue channel
    uint8_t green = file.read();   // Read Green channel
    uint8_t red = file.read();     // Read Red channel

    // Calculate the grayscale value using the average of the RGB channels
    uint8_t grayscaleValue = (red + green + blue) / 3;

    // Apply a threshold to classify the pixel as black (0) or white (1)
    uint8_t lastPixelValue = (grayscaleValue > 127) ? 1 : 0;

    // Debugging: Print the grayscale value and the last pixel value
    Serial.print("Row ");
    Serial.print(row + 1);  // Row number (1-based index)
    Serial.print(" - Grayscale: ");
    Serial.print(grayscaleValue);
    Serial.print(" - Last Pixel: ");
    Serial.println(lastPixelValue);  // Print the last pixel value (0 or 1)

    return lastPixelValue;  // Return the last pixel value
}


void printLastPixelOfAllRows(File &file, uint32_t width, uint32_t height) {
    // Calculate row size with padding (rounded to multiple of 4)
    uint32_t rowSize = (width * 3 + 3) & ~3;  // Width in bytes + padding to 4-byte boundary
    
    // Loop through each row to get the last pixel
    for (uint32_t row = 0; row < height; row++) {
        // Calculate the offset of the last pixel in the current row
        uint32_t lastPixelOffset = 54 + (row * rowSize) + (rowSize - 3); // last 3 bytes of the row
        
        // Seek to the offset of the last pixel in the current row
        file.seek(lastPixelOffset);

        // Read the RGB values of the last pixel (we only need red for grayscale)
        uint8_t blue = file.read();    // Read Blue channel
        uint8_t green = file.read();   // Read Green channel
        uint8_t red = file.read();     // Read Red channel

        // Calculate the grayscale value using the average of the RGB channels
        uint8_t grayscaleValue = (red + green + blue) / 3;

        // Apply a threshold to classify the pixel as black (0) or white (1)
        uint8_t lastPixelValue = (grayscaleValue > 127) ? 1 : 0;

        // Debugging: Print the grayscale value and the last pixel value
        Serial.print("Row ");
        Serial.print(row + 1);  // Row number (1-based index)
        Serial.print(" - Grayscale: ");
        Serial.print(grayscaleValue);
        Serial.print(" - Last Pixel: ");
        Serial.println(lastPixelValue);  // Print the last pixel value (0 or 1)
    }

}

uint8_t* cardVars[16][16] = {  
 {&e1.myVariable1, &e2.myVariable1, &e3.myVariable1, &e4.myVariable1, &e5.myVariable1, &e6.myVariable1, &e7.myVariable1, &e8.myVariable1, &e9.myVariable1, &e10.myVariable1, &e11.myVariable1, &e12.myVariable1, &e13.myVariable1, &e14.myVariable1, &e15.myVariable1, &e16.myVariable1 },
 {&e1.myVariable2, &e2.myVariable2, &e3.myVariable2, &e4.myVariable2, &e5.myVariable2, &e6.myVariable2, &e7.myVariable2, &e8.myVariable2, &e9.myVariable2, &e10.myVariable2, &e11.myVariable2, &e12.myVariable2, &e13.myVariable2, &e14.myVariable2, &e15.myVariable2, &e16.myVariable2 },
 {&e1.myVariable3, &e2.myVariable3, &e3.myVariable3, &e4.myVariable3, &e5.myVariable3, &e6.myVariable3, &e7.myVariable3, &e8.myVariable3, &e9.myVariable3, &e10.myVariable3, &e11.myVariable3, &e12.myVariable3, &e13.myVariable3, &e14.myVariable3, &e15.myVariable3, &e16.myVariable3 },
 {&e1.myVariable4, &e2.myVariable4, &e3.myVariable4, &e4.myVariable4, &e5.myVariable4, &e6.myVariable4, &e7.myVariable4, &e8.myVariable4, &e9.myVariable4, &e10.myVariable4, &e11.myVariable4, &e12.myVariable4, &e13.myVariable4, &e14.myVariable4, &e15.myVariable4, &e16.myVariable4 },
 {&e1.myVariable5, &e2.myVariable5, &e3.myVariable5, &e4.myVariable5, &e5.myVariable5, &e6.myVariable5, &e7.myVariable5, &e8.myVariable5, &e9.myVariable5, &e10.myVariable5, &e11.myVariable5, &e12.myVariable5, &e13.myVariable5, &e14.myVariable5, &e15.myVariable5, &e16.myVariable5 },
 {&e1.myVariable6, &e2.myVariable6, &e3.myVariable6, &e4.myVariable6, &e5.myVariable6, &e6.myVariable6, &e7.myVariable6, &e8.myVariable6, &e9.myVariable6, &e10.myVariable6, &e11.myVariable6, &e12.myVariable6, &e13.myVariable6, &e14.myVariable6, &e15.myVariable6, &e16.myVariable6 },
 {&e1.myVariable7, &e2.myVariable7, &e3.myVariable7, &e4.myVariable7, &e5.myVariable7, &e6.myVariable7, &e7.myVariable7, &e8.myVariable7, &e9.myVariable7, &e10.myVariable7, &e11.myVariable7, &e12.myVariable7, &e13.myVariable7, &e14.myVariable7, &e15.myVariable7, &e16.myVariable7 },
 {&e1.myVariable8, &e2.myVariable8, &e3.myVariable8, &e4.myVariable8, &e5.myVariable8, &e6.myVariable8, &e7.myVariable8, &e8.myVariable8, &e9.myVariable8, &e10.myVariable8, &e11.myVariable8, &e12.myVariable8, &e13.myVariable8, &e14.myVariable8, &e15.myVariable8, &e16.myVariable8 },
 {&e1.myVariable9, &e2.myVariable9, &e3.myVariable9, &e4.myVariable9, &e5.myVariable9, &e6.myVariable9, &e7.myVariable9, &e8.myVariable9, &e9.myVariable9, &e10.myVariable9, &e11.myVariable9, &e12.myVariable9, &e13.myVariable9, &e14.myVariable9, &e15.myVariable9, &e16.myVariable9 },
 {&e1.myVariable10, &e2.myVariable10, &e3.myVariable10, &e4.myVariable10, &e5.myVariable10, &e6.myVariable10, &e7.myVariable10, &e8.myVariable10, &e9.myVariable10, &e10.myVariable10, &e11.myVariable10, &e12.myVariable10, &e13.myVariable10, &e14.myVariable10, &e15.myVariable10, &e16.myVariable10 },
 {&e1.myVariable11, &e2.myVariable11, &e3.myVariable11, &e4.myVariable11, &e5.myVariable11, &e6.myVariable11, &e7.myVariable11, &e8.myVariable11, &e9.myVariable11, &e10.myVariable11, &e11.myVariable11, &e12.myVariable11, &e13.myVariable11, &e14.myVariable11, &e15.myVariable11, &e16.myVariable11 },
 {&e1.myVariable12, &e2.myVariable12, &e3.myVariable12, &e4.myVariable12, &e5.myVariable12, &e6.myVariable12, &e7.myVariable12, &e8.myVariable12, &e9.myVariable12, &e10.myVariable12, &e11.myVariable12, &e12.myVariable12, &e13.myVariable12, &e14.myVariable12, &e15.myVariable12, &e16.myVariable12 },
 {&e1.myVariable13, &e2.myVariable13, &e3.myVariable13, &e4.myVariable13, &e5.myVariable13, &e6.myVariable13, &e7.myVariable13, &e8.myVariable13, &e9.myVariable13, &e10.myVariable13, &e11.myVariable13, &e12.myVariable13, &e13.myVariable13, &e14.myVariable13, &e15.myVariable13, &e16.myVariable13 },
 {&e1.myVariable14, &e2.myVariable14, &e3.myVariable14, &e4.myVariable14, &e5.myVariable14, &e6.myVariable14, &e7.myVariable14, &e8.myVariable14, &e9.myVariable14, &e10.myVariable14, &e11.myVariable14, &e12.myVariable14, &e13.myVariable14, &e14.myVariable14, &e15.myVariable14, &e16.myVariable14 },
 {&e1.myVariable15, &e2.myVariable15, &e3.myVariable15, &e4.myVariable15, &e5.myVariable15, &e6.myVariable15, &e7.myVariable15, &e8.myVariable15, &e9.myVariable15, &e10.myVariable15, &e11.myVariable15, &e12.myVariable15, &e13.myVariable15, &e14.myVariable15, &e15.myVariable15, &e16.myVariable15 },
 {&e1.myVariable16, &e2.myVariable16, &e3.myVariable16, &e4.myVariable16, &e5.myVariable16, &e6.myVariable16, &e7.myVariable16, &e8.myVariable16, &e9.myVariable16, &e10.myVariable16, &e11.myVariable16, &e12.myVariable16, &e13.myVariable16, &e14.myVariable16, &e15.myVariable16, &e16.myVariable16 },
};

// void processConnector(int bodyPixel, int borderPixel, int &card_count, int &connector_count, int &bitToSet) {
//   // If the body pixel is 0 (black) or 1 (white), process it
//   if (bodyPixel == 0 || bodyPixel == 1) {
//     Serial.print("Body Pixel: ");
//     Serial.println(bodyPixel);
//     Serial.print("Connector_count: ");
//     Serial.println(connector_count);
//     Serial.print("card_count: ");
//     Serial.println(card_count);
//     // Ensure card_count is within bounds (0-15)
//     if (card_count >= 0 && card_count < max_cardcount) {
//       // Set the bit for the current card
//       *cardVars[card_count] |= (1 << bitToSet);
//       Serial.println(bitToSet); 
//       Serial.print("Updated body value (binary) at cardVars[");
//       Serial.print(card_count);
//       Serial.print("]: ");
//       Serial.println(*cardVars[card_count], BIN); 
//     }

//     // Move to next card
//     card_count = (card_count + 1) % max_cardcount;  // Reset card_count after 16 cards
//     if (card_count == 0) {
//       bitToSet = (bitToSet == 0) ? 7 : (bitToSet - 1);  // Reset bit to 7 or move to next bit
//     }
//   }

//   // Similarly, for the border pixel, check and process it
//   if (borderPixel == 0 || borderPixel == 1) {
//     Serial.print("Border Pixel: ");
//     Serial.println(borderPixel);
//     Serial.print("Connector_count: ");
//     Serial.println(connector_count);
//     Serial.print("card_count: ");
//     Serial.println(card_count);
//     // Ensure card_count is within bounds (0-15)
//     if (card_count >= 0 && card_count < 16) {
//       // Set the bit for the current card
//       *cardVars[card_count] |= (1 << bitToSet); 
//       Serial.println(bitToSet); 
//       Serial.print("Updated border value (binary) at cardVars[");
//       Serial.print(card_count);
//       Serial.print("]: ");
//       Serial.println(*cardVars[card_count], BIN);
//     }
//   }

//   // Update connector_count for next time, loop back to 0 after 15
//   connector_count = (connector_count + 1) % max_connector;  // Reset connector_count after 16 connectors
// }
// void processConnectorLogic(int connector_count, int bitToSet) {
//     if (connector_count >= 0 && connector_count < max_connector) {
//         // Loop through each card for the current connector
//         for (int i = 0; i < max_cardcount; i++) {
//             // Dynamically access the appropriate myVariable for the current connector and card
//             *cardVars[connector_count][i] |= (1 << bitToSet);
//         }
//     }
// }
// void processConnector(int bodyPixel, int borderPixel, bool runBorderDesign, int &card_count, int &connector_count, int &bitToSet) {
//     // Process body design if bodyPixel is 1
//     if (bodyPixel == 1) {
//          processConnectorLogic(connector_count, bitToSet); 
//     }

//     // If the control pixel was 0, we also process the border design
//     if (runBorderDesign) {
//         // Process border design if borderPixel is 1
//         if (borderPixel == 1) {
//             // Call the processConnectorLogic to handle the logic for the current connector
//             processConnectorLogic(connector_count, bitToSet);  // Processing border design logic
//         }
//     }

//     // Update the card count and bit position for the current connector
//     card_count = (card_count + 1) % max_cardcount;  // Reset after 16 cards
//     if (card_count == 0) {
//         bitToSet = (bitToSet == 0) ? 7 : (bitToSet - 1);  // Reset the bit to the next position after 8 cards
//     }

//     connector_count = (connector_count + 1) % max_connector;  // Reset after 16 connectors
// }


void readBMPDimensions2(const char* bodyFilename, const char* borderFilename)
{
  bodyfile = SD.open(bodyFilename, FILE_READ);
  borderfile = SD.open(borderFilename, FILE_READ);

  if (bodyfile && borderfile) {  
    getBMPDimensions(bodyfile, bodywidth, bodyheight);
    getBMPDimensions(borderfile, borderwidth, borderheight);
  } else {
    // Error handling if files fail to open
    Serial.println("Error opening one or both files!");
  }
  // Close the files
  bodyfile.close();
  borderfile.close();
}
// Function to read and process the body and border BMP files
void readBMPDimensions(const char* bodyFilename, const char* borderFilename) {
  // Open the body and border files from the SD card
  bodyfile = SD.open(bodyFilename, FILE_READ);
  borderfile = SD.open(borderFilename, FILE_READ);
Serial.print("BODY files!");
Serial.println(bodyfile);
Serial.print("BORDER files!");
Serial.println(borderfile);
  if (!bodyfile || !borderfile) 
  {
    Serial.println("Failed to open one or both files");
    return;
  }

  // Read and validate BMP header
  if (read16(bodyfile) != 0x4D42 || read16(borderfile) != 0x4D42) {
    Serial.println("Not a valid BMP file");
    bodyfile.close();
    borderfile.close();
    return;
  }

if (bodyfile && borderfile) {
    // Seek to the 1537th pixel in the body image (index 1536, 0-based index)
    getBMPDimensions(bodyfile, bodywidth, bodyheight);
    getBMPDimensions(borderfile, borderwidth, borderheight);
    // Check if it's a 1-bit BMP file
     if (read16(bodyfile) != 1 || read16(borderfile) != 1) {
      Serial.println("Only 1-bit BMP files are supported");
      bodyfile.close();
      borderfile.close();
      return;
    }
    //     bodyfile.seek(54);  // Move to the start of pixel data
    // Read the 1537th pixel (control pixel)
    uint8_t bodyControlPixel = readPixel(bodyfile, bodywidth);  // last pixel
    Serial.print("BodyControlPixel");
    Serial.println(bodyControlPixel);
      uint32_t row0=0;
      uint32_t row1=1;
      uint32_t row2=2;
      uint32_t row3=3;
      uint32_t row4=4;
      uint32_t row5=5;
      uint32_t row6=6;
      uint32_t row7=7;
      uint32_t row8=8;
      uint32_t row9=9;

      uint32_t rowValue0 = navigateToRow(bodyfile, bodywidth, bodyheight, row0);
      uint32_t rowValue1 = navigateToRow(bodyfile, bodywidth, bodyheight, row1);
      uint32_t rowValue2 = navigateToRow(bodyfile, bodywidth, bodyheight, row2);
      uint32_t rowValue3 = navigateToRow(bodyfile, bodywidth, bodyheight, row3);
      uint32_t rowValue4 = navigateToRow(bodyfile, bodywidth, bodyheight, row4);
      uint32_t rowValue5 = navigateToRow(bodyfile, bodywidth, bodyheight, row5);
      uint32_t rowValue6 = navigateToRow(bodyfile, bodywidth, bodyheight, row6);
      uint32_t rowValue7 = navigateToRow(bodyfile, bodywidth, bodyheight, row7);
      uint32_t rowValue8 = navigateToRow(bodyfile, bodywidth, bodyheight, row8);
      uint32_t rowValue9 = navigateToRow(bodyfile, bodywidth, bodyheight, row9);
      
      Serial.print("rowValue0");
      Serial.println(rowValue0);
      Serial.print("rowValue1");
      Serial.println(rowValue1);
       Serial.print("rowValue2");
      Serial.println(rowValue2);
       Serial.print("rowValue3");
      Serial.println(rowValue3);
       Serial.print("rowValue4");
      Serial.println(rowValue4);
      Serial.print("rowValue5");
      Serial.println(rowValue5);
      Serial.print("rowValue6");
      Serial.println(rowValue6);
       Serial.print("rowValue7");
      Serial.println(rowValue7);
       Serial.print("rowValue8");
      Serial.println(rowValue8);
       Serial.print("rowValue9");
      Serial.println(rowValue9);
     printLastPixelOfAllRows(bodyfile, bodywidth, bodyheight);
    printRowPixels(bodyfile, bodywidth, 1);
    printRowPixels(borderfile, bodywidth, 1);
    printRowPixels(bodyfile, bodywidth, 2);
    printRowPixels(borderfile, bodywidth, 2);
    printRowPixels(bodyfile, bodywidth, 3);
    printRowPixels(borderfile, bodywidth, 3);
    printRowPixels(bodyfile, bodywidth, 4);
    printRowPixels(borderfile, bodywidth, 4);
   
    // Check if the 1537th pixel is white or black (to run border design)
    bool runBorderDesign = (bodyControlPixel == 1);  // White pixel means run border design
    
    // Initialize connector count, card count, and bit position
    int connector_count = 0;
    int card_count = 0;
    int bitToSet = 7;

    // Now we process all the pixels from both body and border (sequentially)
    // for (int y = 0; y < 1; y++) {  // Loop through rows (1 row in this example)
    //   for (int x = 0; x < bodywidth-1; x++) {  // Process the first 1536 pixels
    //     // Read the body pixel
    //     int bodyPixel = (readPixel(bodyfile, x) == 1) ? 1 : 0;
    //     Serial.print("bodyPixel");
    //     Serial.println(bodyPixel);
    //     // Read the border pixel, but only if the border design is enabled (runBorderDesign)
    //     uint8_t borderPixel = (runBorderDesign) ? (readPixel(borderfile, x) == 1 ? 1 : 0) : 0;
    //     Serial.print("borderPixel");
    //     Serial.println(borderPixel);
    //     // Process the connector for both body and border pixels
    //     processConnector(bodyPixel, borderPixel, runBorderDesign, card_count, connector_count, bitToSet);
        
    //   }
    // }
      //       Serial.println();
      //       Serial.print("Present:=");
      //       Serial.println(prev);
    // Close the files after processing
    bodyfile.close();
    borderfile.close();
  } else {
    // If either file couldn't be opened, print an error message
    Serial.println("Error opening body or border file!");
  }
}
// updated code please do modification according to the below code for above code
// void readBMPDimensions(const char* bodyFilename, const char* borderFilename) 
// {
//     // Open the body and border BMP files
//     bodyfile = SD.open(bodyFilename, FILE_READ);
//     borderfile = SD.open(borderFilename, FILE_READ);
//     Serial.print("BODY files!");
//     Serial.println(bodyfile);
//     Serial.print("BORDER files!");
//     Serial.println(borderfile);

//     if (!bodyfile || !borderfile) {
//         Serial.println("Failed to open one or both files");
//         return;
//     }

//     // Read BMP header and validate (this is a simplified check)
//     if (read16(bodyfile) != 0x4D42 || read16(borderfile) != 0x4D42) {
//         Serial.println("Not a valid BMP file");
//         bodyfile.close();
//         borderfile.close();
//         return;
//     }
//   if(bodyfile && borderfile)
//   {
//       getBMPDimensions(bodyfile, bodywidth, bodyheight);
//       getBMPDimensions(borderfile, borderwidth, borderheight);
//     // Check if it's a 1-bit BMP file
//      if (read16(bodyfile) != 1 || read16(borderfile) != 1) {
//       Serial.println("Only 1-bit BMP files are supported");
//       bodyfile.close();
//       borderfile.close();
//       return;
//     }
//         // Skip header bytes to get to pixel data (assuming standard BMP format)
//       bodyfile.seek(54);
//       borderfile.seek(54);

//     // Variables for processing each pixel
//     int connector_count = 0;
//     int card_count = 0;
//     int bitToSet = 7;

//       for (int y = 0; y < 1; y++) {  
//       for (int x = 0; x < bodywidth; x++) {
//       uint8_t bodyPixel = (readPixel(bodyfile, x) == 1) ? 1 : 0;
//         Serial.println("width");
//         Serial.print(pixelValue);
//       }
//       }
//     // Read body BMP and border BMP pixel data and process accordingly
//     // for (int y = 0; y < 1; y++) {  // Loop through body BMP rows
//     //     for (int x = 0; x < bodywidth; x++) {  // Loop through body BMP columns
//     //         // Read the body pixel (grayscale value of the pixel at position (x, y))
//     //         uint8_t bodyPixel = (readPixel(bodyfile, x) == 1) ? 1 : 0;

//     //         // Check the control pixel (last pixel in the row)
//     //         uint8_t controlPixel = (x == bodywidth - 1) ? bodyPixel : 0;  // Control pixel at the last column
//     //         bool runBorderDesign = (controlPixel == 0);  // Run border design only if control pixel is 0

//     //         uint8_t borderPixel = 0;
//     //         if (runBorderDesign) {
//     //             // Read the border pixel only if border design should run
//     //             borderPixel = (readPixel(borderfile, x) == 1) ? 1 : 0;
//     //         }

//     //         // Process the connector logic for both body and border pixels
//     //         processConnector(bodyPixel, borderPixel, runBorderDesign, card_count, connector_count, bitToSet);
//     //     }
//     // }
//         Serial.println("inside readBMPDimension ");
//     bodyfile.close();
//     borderfile.close();
//     }else {
//     // If either file couldn't be opened, print an error message
//     Serial.println("Error opening body or border file!");
//   }
// }


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
  Serial.print("prcRead Called from 2094");
  if(deviceConnected){
    Serial.print("DevideConnected");
    unsigned long curMillis = millis();
    if((curMillis-prvMillis) >= INTERVAL_READ)
    {
      int valAIO = 230;//nalogRead(PinAnalogIn);
      valNotify = map(valAIO, 0, 4096, 0, 255);
      Serial.println(valNotify);
     
      rqsNotify = true;
      prvMillis = curMillis;
    }
  }
 
}

char* extract_filename_without_extension(const char* full_filename) 
{
       // Find the first occurrence of '/'
    const char* first_slash = strchr(full_filename, '/'); // This will find the first '/'
    
    char* filename_without_ext_mem;

    if (first_slash != NULL) {
        // Allocate memory for the part before the first '/'
        filename_without_ext_mem = (char*)malloc((first_slash - full_filename + 1) * sizeof(char));

        // Copy characters before the first '/'
        strncpy(filename_without_ext_mem, full_filename, first_slash - full_filename);
        filename_without_ext_mem[first_slash - full_filename] = '\0'; // Null-terminate the string
    
    } else {
        // If no '/' is found, return a copy of the full filename
        filename_without_ext_mem = strdup(full_filename);
    }

    return filename_without_ext_mem;
}
// char* extract_filename_without_extension(const char* full_filename) {
//  // Find the last occurrence of '/'
//     const char* last_slash = strrchr(full_filename, '/');
    
//     if (last_slash == NULL) {
//         // No '/' found, return a copy of the original string
//         return strdup(full_filename);
//     }

//     // Find the second-to-last occurrence of '/'
//     const char* second_last_slash = NULL;
//     const char* temp = full_filename;
    
//     // Iterate through the string to find the second-to-last slash
//     while ((temp = strchr(temp + 1, '/')) != NULL) {
//         if (temp == last_slash) {
//             break;  // Found the second-to-last slash
//         }
//         second_last_slash = temp;
//     }

//     // If there's no second-to-last slash, return the part before the last '/'
//     if (second_last_slash == NULL) {
//         size_t len = last_slash - full_filename;
//         char* result = (char*)malloc(len + 1);
//         strncpy(result, full_filename, len);
//         result[len] = '\0';
//         return result;
//     }

//     // If we found the second-to-last slash, extract the part before it
//     size_t len = second_last_slash - full_filename;
//     char* result = (char*)malloc(len + 1);
//     strncpy(result, full_filename, len);
//     result[len] = '\0';

//     return result;
// }
// Function to separate the input string into an array of strings and return it
String* septStr(String input, int &numStrings) {
  numStrings = 0;  // Initialize the number of strings
  String tempString = "";  // Temporary string to store characters until a special character is found

  // Loop through each character in the input string
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);  // Get the character at current index

    // If the character is a delimiter, store the current tempString and reset
    if (c == '/' || c == '&' || c == '.') {
      if (tempString != "") {
        separatedStrings[numStrings++] = tempString;  // Store the separated string
        tempString = "";  // Reset the temporary string
      }
    } else {
      tempString += c;  // Add character to the temporary string
    }
  }
  
  // Store the last tempString (if any) after the loop ends
  if (tempString != "") {
    separatedStrings[numStrings++] = tempString;
  }
  
  return separatedStrings;  // Return the array of separated strings
}

void separateString(String input)
 {
  char *endptr;
  int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }
  Serial.print("Max Card Coount: ");
  Serial.print(max_cardcount);
  Serial.print("Max Connector Coount: ");
  Serial.print(max_connector);
  
  if ((max_cardcount != (uint16_t)strtoul(resultseparatedStrings[1].c_str(), &endptr, 10)) || (max_connector != (uint16_t)strtoul(resultseparatedStrings[2].c_str(), &endptr, 10))) {
  // if(max_cardcount!=strtol(resultseparatedStrings[1].c_str(), &endptr, 10)||max_connector!=strtol(resultseparatedStrings[2].c_str(), &endptr, 10))
  // {

        max_cardcount=(uint16_t)strtoul(resultseparatedStrings[1].c_str(), &endptr, 10);
        max_connector=(uint16_t)strtoul(resultseparatedStrings[2].c_str(), &endptr, 10);

       EEPROMWriteInt(31, max_cardcount);    // Write max_cardcount to address 31 and 32
       EEPROMWriteInt(33, max_connector);    // Write max_connector to address 33 and 34
       EEPROM.commit(); // Commit the data to EEPROM
        Serial.print("Value read from EEPROM at address ");
        Serial.print(31);
        Serial.print(": ");
        Serial.println(max_cardcount);
        Serial.print("Value read from EEPROM at address ");
        Serial.print(33);
        Serial.print(": ");
        Serial.println(max_connector);
      delay(10);

  }else {
    Serial.print("Not entered into the if condition not Matching the values");
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
  int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString2");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }
  
    if( height_var!=strtol(resultseparatedStrings[1].c_str(), &endptr, 10) && strtol(resultseparatedStrings[1].c_str(), &endptr, 10)!=0)
    {
      height_var=strtol(resultseparatedStrings[1].c_str(), &endptr, 10);
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
    if( height_var1!=strtol(resultseparatedStrings[2].c_str(), &endptr, 10) && strtol(resultseparatedStrings[2].c_str(), &endptr, 10)!=0)
    {
      height_var1=strtol(resultseparatedStrings[2].c_str(), &endptr, 10);
        EEPROMWriteInt(25, height_var1);
        EEPROM.commit(); // Commit the data to EEPROM
        Serial.print("height_var1=");
        Serial.println(height_var1);
        prev1=max_cardcount*max_connector*8;
        prev1=prev1*height_var1;
        prev1=prev1*3;
        prev1=prev1+53;
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
   int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString3");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }
  
 filename_without_ext_fun  = String(resultseparatedStrings[1]);
 filename_without_ext_fun1 = String(resultseparatedStrings[2]);
}


void separateString4(String input)
 {
   char *endptr;
 int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString4");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }

Serial.print("RL FLAG  :  ");
Serial.println(resultseparatedStrings[1]);
left_right_flag =strtol(resultseparatedStrings[1].c_str(), &endptr, 10);

EEPROM.write(15, left_right_flag); // Write the data to EEPROM
EEPROM.commit(); // Commit the data to EEPROM
        Serial.print("Value read from EEPROM at address ");
        Serial.print(15);
        Serial.print(": ");
        Serial.println(left_right_flag);
Serial.print("RL FLAG check :  ");
Serial.println(left_right_flag);
        //filename_without_ext_fun = String(separatedStrings3[1]);


}


void separateString5(String input)
 {
   char *endptr;
 int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString5");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }
       left_right_flag =strtol(resultseparatedStrings[1].c_str(), &endptr, 10);

       lock_date=strtol(resultseparatedStrings[0].c_str(), &endptr, 10);
       lock_month=strtol(resultseparatedStrings[1].c_str(), &endptr, 10);
       lock_year=strtol(resultseparatedStrings[2].c_str(), &endptr, 10);
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
 int numStrings = 0;  // Variable to store the number of separated strings
  String* resultseparatedStrings = septStr(input, numStrings);  // Call the function to get the separated strings

  // Now you can use the resultStrings array for further processing
  // For example, print the separated strings
  for (int i = 0; i < numStrings; i++) {
    Serial.print("SeparateString6");
    Serial.println(resultseparatedStrings[i]);  // Print the separated strings
  }
  
 //Print the separated strings
 for (int i = 0; i < 3; i++) 
 {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(resultseparatedStrings[i]);
  }

Serial.println(resultseparatedStrings[1]);
triggerTimeReached =strtol(resultseparatedStrings[1].c_str(), &endptr, 10);


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


// void EEPROMWriteInt(int address, uint16_t value) {
//   EEPROM.write(address, (value >> 24) & 0xFF);      // Write the highest byte
//   EEPROM.write(address + 1, (value >> 16) & 0xFF);  // Write the next highest byte
//   EEPROM.write(address + 2, (value >> 8) & 0xFF);   // Write the next lowest byte
//   EEPROM.write(address + 3, value & 0xFF);          // Write the lowest byte
// }

// int32_t EEPROMReadInt(int address) {
//   uint16_t value = 0;
//   value = ((int32_t)EEPROM.read(address) << 24) |
//           ((int32_t)EEPROM.read(address + 1) << 16) |
//           ((int32_t)EEPROM.read(address + 2) << 8) |
//           (int32_t)EEPROM.read(address + 3);
//   return value;
// }
void EEPROMWriteInt(int address, uint16_t value) {
  EEPROM.write(address, (value >> 8) & 0xFF);  // Write high byte
  EEPROM.write(address + 1, value & 0xFF);     // Write low byte
}

uint16_t EEPROMReadInt(int address) {
  uint16_t value = EEPROM.read(address) << 8;  // Read high byte and shift it to the high part of the 16-bit value
  value |= EEPROM.read(address + 1);           // Read low byte and combine with high byte
  return value;
}
void setup() 
{
   // Initialize EEPROM with a size (e.g., 512 bytes for this example)
  EEPROM.begin(512);

  // Erase the EEPROM memory by writing 0xFF to all addresses
  // for (int i = 0; i < EEPROM.length(); i++) {
  //   EEPROM.write(i, 0x01); // Write 0xFF to each byte
  // }

  // // Commit the changes to EEPROM
  // EEPROM.commit();

  // // Debugging message
  // Serial.println("EEPROM has been erased (filled with 0xFF)");

  // // Optionally, you can verify that all values are set to 0xFF
  // for (int i = 0; i < EEPROM.length(); i++) {
  //   if (EEPROM.read(i) != 0xFF) {
  //     Serial.println("EEPROM not erased correctly!");
  //     break;
  //   }
  // }
  ESP.getFreeHeap();
  ESP.getHeapSize();
  setCpuFrequencyMhz(85);
  Serial.print("Free heap:");
  Serial.println(ESP.getFreeHeap());
  Serial.print("Free heap Size:");
  Serial.println(ESP.getHeapSize());
  /*BLE set power*/ 
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9 ); // Set power for advertising
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9 ); // Set power for scanning
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9 ); // Set default power
   
   if (!EEPROM.begin(512)) {
    Serial.println("Failed to initialize EEPROM");
    return;
  } else if(EEPROM.begin(512)){
    Serial.println("initialized EEPROM succesfully");
  }

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
  BLEDevice::init("Tankihkaa");
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


  pCharacteristic2 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID2,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY 
                      //BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic2->addDescriptor(new BLE2902());

  pCharacteristic3 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID3,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic3->addDescriptor(new BLE2902());

  pCharacteristic4 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID4,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic4->addDescriptor(new BLE2902());

  pCharacteristic5 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID5,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic5->addDescriptor(new BLE2902());

  pCharacteristic6 = pService->createCharacteristic(
                      CHARACTERISTIC_UUID6,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  pCharacteristic6->addDescriptor(new BLE2902());

  pCharacteristic11 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID11,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // Create a BLE Descriptor
  pCharacteristic11->addDescriptor(new BLE2902());

  pCharacteristic22 = pService2->createCharacteristic(
                      CHARACTERISTIC_UUID22,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );
  // Create a BLE Descriptor
  pCharacteristic22->addDescriptor(new BLE2902());

  
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
  int index = 0;
  while (index < sizeof(readData) - 1) {  // Ensure not to overflow the array
    ch = EEPROM.read(address);  // Read the byte from EEPROM

    if (ch == '\0') {
        break;  // Stop reading when null-terminator is found
    }

    readData[index] = ch;  // Store the character in the array
    index++;
    address++;
}

readData[index] = '\0';  // Null-terminate the read data

// Debugging output
Serial.print("First file (body) data read from EEPROM: ");
Serial.println(readData);
result2 = string1 + readData + string3;  // Concatenate strings for result
Serial.println(result2);
  char readData1[100]; // Assuming maximum data length
int address1 = 60;
int index1 = 0;
char ch1;

while (index1 < sizeof(readData1) - 1) {  // Ensure not to overflow the array
    ch1 = EEPROM.read(address1);  // Read the byte from EEPROM

    if (ch1 == '\0') {
        break;  // Stop reading when null-terminator is found
    }

    readData1[index1] = ch1;  // Store the character in the array
    index1++;
    address1++;
}

readData1[index1] = '\0';  // Null-terminate the read data

// Debugging output
Serial.print("Second file (border) data read from EEPROM: ");
Serial.println(readData1);

// Combine the result for mobile app
result1 = string1 + readData1 + string3;  // Concatenate strings for result
Serial.println(result1);
  Serial.print("eeprom read value=");
  Serial.println(result2);
  Serial.println(result1);
  max_cardcount= EEPROMReadInt(31); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1  max_cardcount: ");
  Serial.println(max_cardcount);
  max_connector= EEPROMReadInt(33); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1 max_connector: ");
  Serial.println(max_connector);
 // height_var= 0;// Firstime program un comment this line 
  height_var= EEPROMReadInt(21);// First time program, comment this line 
  // height_var1= 0;// Firstime program un comment this line 
  height_var1= EEPROMReadInt(25);// First time program, comment this line 
  Serial.print("Data read from EEPROM1 body height_var: ");
  Serial.println(height_var);
  prev=max_cardcount*max_connector*8;
  prev=prev*height_var;
  prev=prev*3;
  prev=prev+53;
  Serial.println(prev);
  Serial.print("Data read from EEPROM1 border height_var1: ");
  Serial.println(height_var1);
  prev1=max_cardcount*max_connector*8;
  prev1=prev1*height_var1;
  prev1=prev1*3;
  prev1=prev1+53;
  Serial.println(prev1);
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
            if (fileName.endsWith(".bmp")) 
            {
              pCharacteristic->setValue(fileName.c_str());
              pCharacteristic->notify();
              delay(300); // Delay between notifications
              Serial.println(file.name()); 
            }
             
           // }
            //file.close();
            file = root.openNextFile();
             temp_count=1;
             lockstatus_count=0;
             unlockstatus_count=0;
          }

          char result_pcount[20]; 
          sprintf(result_pcount, "%d,%d", height_var, height_var1);
          pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
          pCharacteristic4->notify();

          Serial.print("Body File: ");
        Serial.println(result2);
        Serial.print("Border File: ");
        Serial.println(result1);
        String f1 = result2.substring(1);
        String f2 = result1.substring(1);
        String Comp2Files = f1+"&"+f2;
        pCharacteristic2 -> setValue(Comp2Files.c_str());
        pCharacteristic2 -> notify();
        Serial.print("Selected Files for Design 1714: ");
        Serial.println(Comp2Files.c_str());

        if (pCharacteristic3) {
          temp_str = ".";
          combinedString = bodywidth + temp_str + bodyheight;
          pCharacteristic3 -> setValue((uint8_t * ) & combinedString, sizeof(combinedString));
          pCharacteristic3 -> notify();
          Serial.print("body and border width and height File for Design 1707: ");
          Serial.println(combinedString.c_str());
          delay(10);
        } else {
          Serial.println("pCharacteristic3 is not initialized!");
        }

        if (pCharacteristic22) {
          temp_str = ".";
          ttl_hks = max_cardcount * max_connector * 8;
          // total_hook = String(ttl_hks);
          total_hook = max_cardcount + temp_str + max_connector + temp_str + ttl_hks;
          pCharacteristic22 -> setValue((uint8_t * ) & total_hook, sizeof(total_hook));
          pCharacteristic22 -> notify();
          Serial.print("card and connector count for Design 1717: ");
          Serial.println(total_hook.c_str());
          delay(10);
        } else {
          Serial.println("pCharacteristic22 is not initialized!");
        }

       }

          	//Serial.println("hello world");
          
          std::string receivedData  = pCharacteristic2->getValue();// Display reading data file selection 
          
          Serial.print("Received Data: ");
          Serial.println(receivedData.c_str());
          const char*full_filename =receivedData.c_str();
          char* filename_without_ext = extract_filename_without_extension(full_filename);
         Serial.println("filename_without_ext");
         Serial.println(filename_without_ext);
        char filename_without_ext1[] = "*UP"; //
        char* result = strstr(filename_without_ext1, filename_without_ext);
        char filename_without_ext11[] = "CH"; //
        char* result11 = strstr(filename_without_ext11, filename_without_ext);
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
        if (result11 != nullptr) //
        {

          Serial.print(" ADD File++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
          separateString3(receivedData.c_str());

          string2 = filename_without_ext_fun;
          string4 = filename_without_ext_fun1;
          String newValue2 = String(string2.c_str());
          String newValue1 = String(string4.c_str());
          Serial.println(" newvalue2***************************====");
          Serial.println(newValue1);
          Serial.println(newValue2);
          char fileName1[40]; // Adjust size as needed
          char fileName2[40];
          snprintf(fileName1, sizeof(fileName1), "/%s.bmp", newValue2);
          snprintf(fileName2, sizeof(fileName2), "/%s.bmp", newValue1);
          // Check if the specific file exists
          if (SD.exists(fileName1) && SD.exists(fileName2)) {
            Serial.print(fileName1);
            Serial.print(fileName2);
            Serial.println(" exists.");
            file_check2 = 1;
          } else {
            file_check2 = 0;
            Serial.print(fileName1);
            Serial.print(fileName2);
            Serial.println(" does not exist.");
          }
          if ((newValue2 != previousValue2) && (file_check2 == 1)) {
            cleardata();
            mem_cpy_set = 1;
            sensor_sel2 = 0;
            previousValue2 = newValue2;
            height_var = 0;
            prev = 53;
            present = 0;
            first_set_flag = 0;
            EEPROMWriteInt(21, height_var);
            EEPROM.commit(); // Commit the data to EEPROM
            // Serial.println(" ************************************************************************************");
          }else if ((newValue1 != previousValue1) && (file_check2 == 1))
          {
            cleardata();
            mem_cpy_set = 1;
            sensor_sel2 = 0;
            previousValue1 = newValue1;
            height_var1 = 0;
            prev1 = 53;
            present1 = 0;
            first_set_flag = 0;
            EEPROMWriteInt(25, height_var1);
            EEPROM.commit(); // Commit the data to EEPROM
          }
          // Serial.println("NANDA NANDA NANDA NANDA NANDA NANDA NANDA");
        } else {
          separateString(receivedData.c_str());
          string2 = filename_without_ext;
          //Serial.print(" ADD File------------------------------------------------------------------------------------------");
        }
        String newValue = String(string2.c_str());
        String newValue1 = String(string4.c_str());
        //Serial.println(" newvalue***************************====");
        // Serial.println(newValue);
        char fileName[20]; // Adjust size as needed
        char fileName1[20];
        snprintf(fileName, sizeof(fileName), "/%s.bmp", newValue);
        snprintf(fileName1, sizeof(fileName1), "/%s.bmp", newValue1);
        // Check if the specific file exists
        if (SD.exists(fileName) && SD.exists(fileName1)) {
          //Serial.print(fileName);
          //Serial.println(" exists.");
          file_check = 1;
        } else {
          file_check = 0;
          //Serial.print(fileName);
          //Serial.println(" does not exist.");
        }
        if ((newValue != previousValue || temp_count2 == 0) && (newValue1 != previousValue1 || temp_count2 == 0) && (file_check == 1)) {
          char result_width[10];
          char result_height[10];
          previousValue = newValue;
          const char * stringValue = previousValue.c_str();
          int length = strlen(stringValue);
          previousValue1 = newValue1;
          Serial.println("String4 File:");
          Serial.print(string4);
          Serial.print(newValue1);
          const char * stringValue1 = previousValue1.c_str();
          int length1 = strlen(stringValue1);
            // Ensure the length of the strings is within limits
            if (length > 100 || length1 > 100) {
              Serial.println("Error: String is too large to fit in EEPROM.");
              return;
            }
           if (length != 0 || length1 != 0) { 
       if (length != 0) {
    // Write the first string to EEPROM starting at address 0
    for (int i = 0; i < length; i++) {
      EEPROM.write(i, previousValue[i]);  // Write each character of the first string
    }
    EEPROM.write(length, '\0');  // Null-terminate the first string in EEPROM
    EEPROM.commit();
    result2 = string1 + previousValue + string3;  // Combine the strings for result2
   }
            Serial.print("Value written to EEPROM at address ");
            Serial.print(0);
            Serial.print(": ");
            Serial.println(previousValue);
   if (length1 != 0) {
    // Write the second string to EEPROM starting at address 60
    for (int i = 0; i < length1; i++) {
      EEPROM.write(60 + i, previousValue1[i]);  // Write each character of the second string
    }
    EEPROM.write(60 + length1, '\0');  // Null-terminate the second string in EEPROM
    EEPROM.commit();
    result1 = string1 + previousValue1 + string3;  // Combine the strings for result1
   }
            
            Serial.print("Value written to EEPROM at address ");
            Serial.print(60);
            Serial.print(": ");
            Serial.println(previousValue1);
            Serial.println("result1");
            Serial.print(result1);
            Serial.println("result2");
            Serial.print(result2);
            if (SD.exists(result2.c_str()) || SD.exists(result1.c_str())) {
              readBMPDimensions2(result2.c_str(), result1.c_str());
            sprintf( result_width, "%d", bodywidth); 
            sprintf( result_height, "%d", bodyheight); 
              char result_pcount[10];
              if (pCharacteristic3) {
                temp_str = ".";
                combinedString = result_width + temp_str + result_height;
                pCharacteristic3 -> setValue((uint8_t * ) & combinedString, sizeof(combinedString));
                pCharacteristic3 -> notify();
                delay(10);
              } else {
                Serial.println("pCharacteristic3 is not initialized!");
              }
              Serial.println("combinedString===========================");
              Serial.println(combinedString);
              // height_var=0;
              sensor_sel = 0;
              sensor_sel1 = 0;
              temp_sens_check = 0;
            }

            //free(filename_without_ext); 
          }
            char result_pcount[20]; 
            sprintf(result_pcount, "%d,%d", height_var, height_var1);
            pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
            pCharacteristic4->notify();
            temp_count2 = 1;
        }
      }
         if (pCharacteristic11 != nullptr) 
        {
          receivedData3  = pCharacteristic11->getValue();// Display reading data file selection
          //Serial.print("Received data: ");
          ////Serial.println(receivedData3.c_str());
         // Serial.println(strcmp(comp_string,receivedData3));
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
                  if(height_var==0 || height_var1==0)
                  {
                    prev=53;
                    prev1=53;
                  }
                  else
                  {
                    prev=max_cardcount*max_connector*8;
                    prev=prev*height_var;
                    prev=prev*3;
                    prev=prev+53;
                    prev1=max_cardcount*max_connector*8;
                    prev1=prev1*height_var1;
                    prev1=prev1*3;
                    prev1=prev1+53;
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
           Serial.print("Value read from EEPROM at address ");
        Serial.print(20);
        Serial.print(": ");
        Serial.println(mode_set);
        }
          value2++;


          if(value2==250)
          {
            value2=0;
          }
          
        }
    }
     
    Serial.println("Am i Calling prcRead");
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
      if(height_var==bodyheight || height_var1==borderheight)
    {
    // height_var=0;
      present=0;
      prev=53;
      present1=0;
      prev1=53;
    }

      readBMPDimensions(result2.c_str(), result1.c_str());
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
    if(height_var==bodyheight || height_var1==borderheight)
    {
      height_var=0;
      height_var1=0;
      pick_clear_flag=1;
    }
    height_var+=1;
    height_var1+=1;
    //EEPROM.write(14, height_var); // Write the data to EEPROM
    EEPROMWriteInt(21, height_var);
    EEPROMWriteInt(25, height_var1);
    EEPROM.commit(); // Commit the data to EEPROM
    Serial.print("Value read from EEPROM at address ");
        Serial.print(21);
        Serial.print(": ");
        Serial.println(height_var);
        Serial.print("Value read from EEPROM at address ");
        Serial.print(25);
        Serial.print(": ");
        Serial.println(height_var1);
   // Serial.print("height111111111111111111111111111111111111111=");
    //Serial.println(height_var);// nanda
          char result_pcount[20]; 
          sprintf(result_pcount, "%d,%d", height_var, height_var1);
          pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
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
    Serial.println(prev1);
    //Serial.print("mem_cpy_set=");
    // Serial.println(mem_cpy_set);
}

else if(sensor1Detected && sensor_sel==1)
{
  uint32_t temp_flag=0;
  uint32_t temp_flag1=0;
  cleardata();
 if(mode_set==0)
 {
  if(pick_clear_flag==0)
  {
  if(height_var==bodyheight)
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
    if(height_var1==borderheight)
    {
      temp_flag1= max_cardcount*max_connector*8;
      temp_flag1=temp_flag1*3;
      temp_flag1=(temp_flag1)*(height_var1)+1;
      prev1=temp_flag1+53;
      temp_flag1=0;
      heightcounter_reset=1;
    }
    else if(heightcounter_reset==1 && height_var1==1)
    {
      prev1=prev1-53;
      prev1=(prev1*2)+53;
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
    temp_flag1= max_cardcount*max_connector*8;
   //Serial.print("heighthe222222222222222222222222222222222222222 Prev==");
   Serial.println(prev1);
  // Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(temp_flag1);
   temp_flag1=temp_flag1*3;
   //Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(temp_flag1);
   prev1=prev1-(temp_flag1*2);  // prev=prev-(4608*2); 
   //Serial.print("heighthe222222222222222222222222222222222222222==");
   Serial.println(prev1);
   readBMPDimensions(result2.c_str(), result1.c_str());
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
      if(height_var==bodyheight || height_var1==borderheight)
          {
            height_var=0;
            height_var1=0;
            pick_clear_flag=1;
          }
          height_var+=1;
          height_var1+=1;
      //EEPROM.write(14, height_var); // Write the data to EEPROM
      EEPROMWriteInt(21, height_var);
      EEPROMWriteInt(25, height_var1);
      EEPROM.commit(); // Commit the data to EEPROM
      Serial.print("Value read from EEPROM at address ");
        Serial.print(21);
        Serial.print(": ");
        Serial.println(height_var);
        Serial.print("Value read from EEPROM at address ");
        Serial.print(25);
        Serial.print(": ");
        Serial.println(height_var1);
          char result_pcount[20]; 
          sprintf(result_pcount, "%d,%d", height_var, height_var1);
          pCharacteristic4->setValue((uint8_t*)&result_pcount, sizeof(result_pcount));
          pCharacteristic4->notify();
      //Serial.print("height22222222222222222222222222222222222222222222222222222=");
      //Serial.println(height_var);//nanda
         // Serial.print("mem_cpy_set13=");
      //Serial.println(mem_cpy_set);
      mem_cpy_set=1;
    }
    sensor_sel2=0;
    sensor2_data();
    sensor_sel1=1;
    temp_sens_check=1;
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
  uint32_t temp_flag1=0;
  cleardata();
   if(mode_set==0)
   {
  if(pick_clear_flag==0)
  {
 if(height_var==bodyheight)
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
    if(height_var1==borderheight)
    {
      temp_flag1= max_cardcount*max_connector*8;
      temp_flag1=temp_flag1*3;
      temp_flag1=(temp_flag1)*(height_var1)+1;
      prev1=temp_flag1+53;
      temp_flag1=0;
      heightcounter_reset=1;
    }
    else if(heightcounter_reset==1 && height_var1==1)
    {
      prev1=prev1-53;
      prev1=(prev1*2)+53;
      heightcounter_reset=0;

    }
  }
   
    temp_flag= max_cardcount*max_connector*8;
    Serial.println(temp_flag);
    temp_flag=temp_flag*3;
    prev=prev-(temp_flag*2);  // prev=prev-(4608*2); 
    Serial.println(prev);
     temp_flag1= max_cardcount*max_connector*8;
    Serial.println(temp_flag1);
    temp_flag1=temp_flag1*3;
    prev1=prev1-(temp_flag1*2);  // prev=prev-(4608*2); 
    Serial.println(prev1);
    readBMPDimensions(result2.c_str(), result1.c_str());
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
