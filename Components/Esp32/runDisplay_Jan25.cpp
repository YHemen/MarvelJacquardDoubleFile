#include <Arduino.h>
#include <U8g2lib.h>
#include <Keypad.h>
#include "BLEDevice.h"
#include <Wire.h>
#include<EEPROM.h>
#include<string.h>
#include <WiFi.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include <HardwareSerial.h>
#define RXD2 16
#define TXD2 17
#define CMDBUFFER_SIZE 5

#define TARGET_MAC_ADDRESS "34:85:18:94:1D:DD" 
#define bleServerName "Marvelraghu34"
void Welcome_Scrn();
void Menue_Scrn();
void Alldesign_Scrn();
void Settings_Scrn();
void Dsn_Left_Right_Scrn();
void Lock_Noti_Scrn();
void System_Dsn_Scrn();
void Dlt_Dsn_Scrn();
void admin_Scrn();
void Running_Scrn();
void Connecting_Scrn();
void Connection_issue_Scrn();
void Connected_Scrn();


const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

static int file_slct=0;
static int temp_runscrn=1;
static int conec_cnt=0;
static int delet_screen=0;
static int cl_cnt=0;
static int16_t ttl_hks=0;
static int tog_slct=0;
static int tog_slct1=0;
static int tog_slct2=0;
static int tog_slct3=0;
static int myInt =0;
static int screen_admin=0;
int temp_curs=0;
static int count_date=1;
static int count_month=1;
static int count_year=24;
static int admin_lock_flag=0;
static int up_value_flag1=0;
static int up_value_flag2=0;
static int tick_loop=0;
static uint32_t temp_count_tick=0;
static int tick_flag=0;
String temp_str="/";
String combinedString="";
String combinedString33="";
char result_conec_cnt[10];
char result_cl_cnt[10]; 
char Lock_status_char[] = "locked";   // left to right design chnage 
char unLock_status_char[] = "unlocked-";   // left to right design chnage
char filename_without_RPM[] = "RPM"; //
String separatedStrings[3];
int active_state=0;
static int machine_lock_status=1; //0=locked,1=unlocked;
static int left_right_flag=1;
static int decimal_number1 = 97; // Example decimal number
static int decimal_number2 = 97; // Example decimal number
static int decimal_number3 = 97; // Example decimal number
static int decimal_number4 = 97; // Example decimal number
static int decimal_number5 = 97; // Example decimal number
static int decimal_number6 = 97; // Example decimal number
static int decimal_number11 = 97; // Example decimal number
static int decimal_number22 = 97; // Example decimal number
static int decimal_number33 = 97; // Example decimal number
static int decimal_number44 = 97; // Example decimal number
static int decimal_number55 = 97; // Example decimal number
static int decimal_number66 = 97; // Example decimal number
static int reboot_count=0;
static int connection_flag=0;

  // Convert decimal number to character

int pas_array1[] = {9, 7, 3, 8, 7, 9}; //
int pas_array2[] ={0, 0, 0, 0, 0, 0};

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {47, 21, 14, 13}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {12, 11, 10, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );





char c;
char processCharInput(char* cmdBuffer, const char c)
{
 //Store the character in the input buffer
 if (c >= 32 && c <= 126) //Ignore control characters and special ascii characters
 {
   if (strlen(cmdBuffer) < CMDBUFFER_SIZE)
   {
     strncat(cmdBuffer, &c, 1);   //Add it to the buffer
   }
   else  
   {  
     return '\n';
   }
 }
 else if ((c == 8 || c == 127) && cmdBuffer[0] != 0) //Backspace
 {

   cmdBuffer[strlen(cmdBuffer)-1] = 0;
 }

 return c;
}

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 5, /* CS=*/ 6, /* reset=*/ 7);
//U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

//U8G2_KS0108_128X64_F u8g2(U8G2_R0, 7, 6, 5, 4, 3, 2, 8, 9, /*enable=*/ A2, /*dc=*/ A0, /*cs0=*/ 10, /*cs1=*/ 11, /*cs2=*/ U8X8_PIN_NONE, /* reset=*/  12); 	// Set R/W to low!


// End of constructor list
static char cmdBuffer[10] = "";
char mn,sub,sub22,set,flag,flag1,flag2,flag3,sub1;
char prev_flag, prev_sub;
int screen=0,prev_screen=0;
int key_set=0;

int address = 0;
int address2 = 2;





//Default Temperature is in Celsius
//Comment the next line for Temperature in Fahrenheit
#define temperatureCelsius

//BLE Server name (the other ESP32 name running the server sketch)
// #define bleServerName "Marvel CPU Board1"

/* UUID's of the service, characteristic that we want to read*/
// BLE Service
static BLEUUID bleServiceUUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID bleServiceUUID2("4fafc202-1fb5-459e-8fcc-c5c9c331914b");


static BLEUUID temperatureCharacteristicUUID("beb5483e-36e1-4685-b7f5-ea07361b26a8"); // sd data reading 
static BLEUUID humidityCharacteristicUUID("beb5483e-36e1-4686-b7f5-ea07361b26a8"); // SD data sending data to server
static BLEUUID widthCharacteristicUUID("beb5483e-36e1-4687-b7f5-ea07361b26a8"); // width 

static BLEUUID heightCharacteristicUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"); // height 

static BLEUUID modeCharacteristicUUID("beb5483e-36e2-4670-b7f5-ea07361b26a8"); // modes
static BLEUUID pcountCharacteristicUUID("beb5483e-36e2-4671-b7f5-ea07361b26a8"); // modes



//Flags stating if should begin connecting and if the connection is up
static boolean doConnect = false;
static boolean connected = false;

//Address of the peripheral device. Address will be found during scanning...
static BLEAddress *pServerAddress;
 
//Characteristicd that we want to read
static BLERemoteCharacteristic* temperatureCharacteristic;
static BLERemoteCharacteristic* humidityCharacteristic;
static BLERemoteCharacteristic* heightCharacteristic;
static BLERemoteCharacteristic* widthCharacteristic;
static BLERemoteCharacteristic* modeCharacteristic;
static BLERemoteCharacteristic* pcountCharacteristic;




//Activate notify
const uint8_t notificationOn[] = {0x1, 0x0};
const uint8_t notificationOff[] = {0x0, 0x0};

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)


//Variables to store temperature and humidity
char* temperatureChar;
char* humidityChar;
char* heightchar;
//char* widthchar;

char* heightChar;
char* widthChar;
char* filename_without_ext_mem;

//Flags to check whether new temperature and humidity readings are available
boolean newTemperature = false;
boolean newHumidity = false;

struct SDdata
{
  char data1[30];
  char data2[30];
  char data3[30];
  char data4[30];
  char data5[30];
  char data6[30];
  char data7[30];
  char data8[30];
  char data9[30];
  char data10[30];
  char data11[30];
  char data12[30];
  char data13[30];
  char data14[30];
  char data15[30];
  char data16[30];
  char data17[30];
  char data18[30];
  char data19[30];
  char data20[30];
  char data21[520];
  char data22[30];
};
SDdata sddata;

struct Mddata
{
  char data1[15]="allu";
  char data2[15]="alld";
  char data3[15]="8up8d";
  char data4[15]="1up1d";
  char data5[15]="default";
};
Mddata mddata;

struct Bmpdata
{
  char data1[15];  // width
  char data2[15]; //height
  char data3[15]; // Running Count 
  char data4[15]; // RPM 
};
Bmpdata bmpdata;

//Connect to the BLE Server that has the name, Service, and Characteristics
bool connectToServer(BLEAddress pAddress) 
{
   BLEClient* pClient = BLEDevice::createClient();
 
  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");
 


  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(bleServiceUUID);
  BLERemoteService* pRemoteService2 = pClient->getService(bleServiceUUID2);
 if (pRemoteService == nullptr || pRemoteService2 == nullptr) 
 {
    if (pRemoteService == nullptr) {
        Serial.print("Failed to find service with UUID: ");
        Serial.println(bleServiceUUID.toString().c_str());
    }
    if (pRemoteService2 == nullptr) {
        Serial.print("Failed to find service with UUID: ");
        Serial.println(bleServiceUUID2.toString().c_str());
    }
    return false;
}




 
  // Obtain a reference to the characteristics in the service of the remote BLE server.
  temperatureCharacteristic = pRemoteService->getCharacteristic(temperatureCharacteristicUUID);
  humidityCharacteristic = pRemoteService->getCharacteristic(humidityCharacteristicUUID);
  heightCharacteristic = pRemoteService->getCharacteristic(heightCharacteristicUUID);
  widthCharacteristic = pRemoteService->getCharacteristic(widthCharacteristicUUID);
  modeCharacteristic = pRemoteService2->getCharacteristic(modeCharacteristicUUID);
  pcountCharacteristic = pRemoteService2->getCharacteristic(pcountCharacteristicUUID);






  if (temperatureCharacteristic == nullptr || humidityCharacteristic == nullptr|| heightCharacteristic==nullptr||widthCharacteristic==nullptr||modeCharacteristic==nullptr|| pcountCharacteristic==nullptr) 
  {
    Serial.print("Failed to find our characteristic UUID");
    return false;
  }
  Serial.println(" - Found our characteristics");
 
  //Assign callback functions for the Characteristics
  temperatureCharacteristic->registerForNotify(temperatureNotifyCallback);
  humidityCharacteristic->registerForNotify(humidityNotifyCallback);

   heightCharacteristic->registerForNotify(heightNotifyCallback);
  widthCharacteristic->registerForNotify(widthNotifyCallback);
   modeCharacteristic->registerForNotify(modeNotifyCallback);
  // pcountCharacteristic->registerForNotify(pcountNotifyCallback);

  return true;
}

//Callback function that gets called, when another device's advertisement has been received


 class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    BLEAddress targetAddress(TARGET_MAC_ADDRESS);
    // Check if the device name matches the target name and the MAC address matches
    if (advertisedDevice.getName() == bleServerName && advertisedDevice.getAddress() == targetAddress) {
      // Stop the scan, as we've found the target device
      advertisedDevice.getScan()->stop();
      // Store the address of the found device
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      // Set the flag to indicate we should attempt a connection
      doConnect = true;
      Serial.println("Device found. Connecting!");
    }
  }
};

 char* extract_filename_without_extension(const char* full_filename) 
{
    const char* last_dot = strrchr(full_filename, '.'); // Find the last occurrence of '.'

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
static void temperatureNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) 
                                        {
 
  temperatureChar = (char*)pData;
   Serial.print("temperatureChar data");
  Serial.println(temperatureChar);

  char* result1 = strstr(Lock_status_char, temperatureChar);
   char* result2 = strstr(unLock_status_char, temperatureChar);
  

   

        if (result1 != nullptr) 
         { // Check if the received string contains '*1'
              //Serial.println("LED ON");
                Serial.println("machine_lockeddddd");
                machine_lock_status=0; // locked
         }
         else if (result2 != nullptr) 
         { // Check if the received string contains '*1'
              //Serial.println("LED ON");
                Serial.println("machine unlocked");
                machine_lock_status=1; // unlocked 
         }
         else
         {
            const char* full_filename = (char*)pData;
            char* filename_without_ext = extract_filename_without_extension(full_filename);
            //if (filename_without_ext_mem) 
             //{
                free(filename_without_ext_mem);
             //}
             Serial.print("filename_without_ext");
            Serial.println(filename_without_ext);
            char* result3 = strstr(filename_without_RPM, filename_without_ext);
          if(result3 != nullptr)
          {
              separateString(temperatureChar);
          }
          else
          {
              myInt+=1;
    if(myInt<=21)
    {
                   
    switch(myInt)
    {

    
      case 1: 
            memcpy(&sddata.data1, filename_without_ext, sizeof(filename_without_ext)+1);
          // Serial.println(sddata.data1);
           Serial.println(filename_without_ext);

            break;
      case 2: 
            memcpy(&sddata.data2, filename_without_ext, sizeof(filename_without_ext)+1);
            //Serial.println(sddata.data2);
            Serial.println(filename_without_ext);
            break;      
      case 3: 
            memcpy(&sddata.data3, filename_without_ext, sizeof(filename_without_ext)+1);
            //Serial.println(sddata.data3);
            Serial.println(filename_without_ext);
            break;

      case 4: 
            memcpy(&sddata.data4, filename_without_ext, sizeof(filename_without_ext)+1);
            //Serial.println(sddata.data4);
            Serial.println(filename_without_ext);
            break;
      case 5: 
            memcpy(&sddata.data5, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data5);
            break;      
      case 6: 
            memcpy(&sddata.data6, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data6);
            break;
      case 7: 
            memcpy(&sddata.data7, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data7);
            break;
            
      case 8: 
            memcpy(&sddata.data8, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data8);
            break;      
      case 9: 
            memcpy(&sddata.data9, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data9);
            break;
      case 10: 
            memcpy(&sddata.data10, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println("data10=");
            Serial.println(sddata.data10);
            break;

      case 11: 
            memcpy(&sddata.data11, filename_without_ext, sizeof(filename_without_ext)+1);
             Serial.println("data12=");
            Serial.println(sddata.data11);
            break;
      case 12: 
            memcpy(&sddata.data12, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data12);
      case 13: 

            memcpy(&sddata.data13, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data13);
      case 14: 
             memcpy(&sddata.data14, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data14);

      case 15: 
            memcpy(&sddata.data15, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println("data10=");
            Serial.println(sddata.data15);
            break;

      case 16: 
            memcpy(&sddata.data16, filename_without_ext, sizeof(filename_without_ext)+1);
             Serial.println("data12=");
            Serial.println(sddata.data16);
            break;
      case 17: 
            memcpy(&sddata.data17, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data17);
      case 18: 

            memcpy(&sddata.data18, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data18);
      case 19: 
             memcpy(&sddata.data19, filename_without_ext, sizeof(filename_without_ext)+1);
            Serial.println(sddata.data19);
      case 20: 
             
            Serial.println(sddata.data20);

            break;      
      default :
            break;

    }
    //free(filename_without_ext);
    if(myInt==20)
    {
      //myInt=0;
    }
    }
 
         }
 
          }
            
    
  //Serial.println(temperatureChar);

}


static void humidityNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                    uint8_t* pData, size_t length, bool isNotify) 
{
 
 // humidityChar = (char*)pData;

  std::string value = pBLERemoteCharacteristic->readValue();
      int intValue = atoi(value.c_str());
      Serial.print("Received integer value: ");
      Serial.println(intValue);
  
}



static void modeNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) 
                                        {
    char* height1 = (char*)pData;
             
  Serial.print("Received Width value: ");
      Serial.println(height1);

}

static void heightNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) 
                                        {
  char* height = (char*)pData;
             
  //Serial.print("Received Width value: ");
  // int decimalValue = atoi(height);
 // Serial.print("EE-height");//nanda
  tick_flag=0;
  //Serial.println(height);

  memcpy(&bmpdata.data3, height, sizeof(height)+1);
  //Serial.printf("Free heap: %d bytes\n", esp_get_free_heap_size());

}

 static void widthNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) 
                                        {
                                         
 char* width = (char*)pData;
 
 String string1 = "";
String string2 = "";

  Serial.print("Received HIght value: ");
 // Serial.println(width);
  
//const char* full_filename = (char*)pData;
  
 const char* combinedString =width;
  if (combinedString) {
      // Parse the combined string into two separate strings
      char* pData = (char*)combinedString;
      char* string11 = strtok(pData, "."); // Assuming a space separates the two strings
      char* string22 = strtok(NULL, " ");

      if (string1 && string2) {
        Serial.println("String 1: " + String(string11));
        memcpy(&bmpdata.data1, string11, sizeof(string11)+1);
        Serial.println("String 2: " + String(string22));
        memcpy(&bmpdata.data2, string22, sizeof(string22)+1);
       // Running_Scrn();

      } else {
        Serial.println("Error parsing combined string.");
      }
    }
                            
                                        }

 /*static void pcountNotifyCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, 
                                        uint8_t* pData, size_t length, bool isNotify) 
                                        {                                    
 char* pcount = (char*)pData;

  Serial.print("Received Pcount value: ");
  Serial.println(pcount);
  memcpy(&bmpdata.data3, pcount, sizeof(pcount)+1);

 }*/
                                        

void sendDataToServer() {
  if (humidityCharacteristic != nullptr) {
    // Your data to be sent
    String data = "Hello, server!";
    // Write the data to the characteristic
    humidityCharacteristic->writeValue(data.c_str(), data.length());
    Serial.println("Data sent: " + data);
  } else {
    Serial.println("Characteristic not available for sending data");
  }
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
  
 //Print the separated strings
 for (int i = 0; i < 3; i++) {
    Serial.print("String ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(separatedStrings[i]);
  }

        //filename_without_ext_fun = String(separatedStrings3[1]);
   

}
char key;
void setup(void) 
{
  ESP.getFreeHeap();
  ESP.getHeapSize();
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9 ); // Set power for advertising
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9 ); // Set power for scanning
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9 ); // Set default power
  EEPROM.begin(32);
  reboot_count=EEPROM.read(23); // Read the data from EEPROM
  Serial.print("reboot count");
  Serial.println(reboot_count);

//if(reboot_count!=3)
//{
  /* reboot_count=3;
   EEPROM.write(23, reboot_count);
  EEPROM.commit(); // Commit the data to EEPROM
  decimal_number1=110;
  decimal_number2=97;
  decimal_number3=110;
  decimal_number4=100;
  decimal_number5=97;
  decimal_number11=110;
  decimal_number22=97;
  decimal_number33=110;
  decimal_number44=100;
  decimal_number55=97;

  EEPROM.write(13, decimal_number1); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(14, decimal_number2); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(15, decimal_number3); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(16, decimal_number4); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(17, decimal_number5); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);

  EEPROM.write(18, decimal_number11); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(19, decimal_number22); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(20, decimal_number33); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(21, decimal_number44); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(22, decimal_number55); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
//}
  */
  

  
  u8g2.begin();
  BLEDevice::init("");
  Serial.begin(9600);
  WiFi.disconnect(true); // Disconnect and remove saved credentials
  WiFi.mode(WIFI_OFF);   // Turn off the WiFi hardware
  Serial.println("WiFi turned off.");
  Serial.println("Starting Arduino BLE Client application...");
  Welcome_Scrn();
  delay(1000);
  Connecting_Scrn();
 
  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(10);

  //memcpy(&sddata.data15, sddata.data1, sizeof(sddata.data15)+1);
  //Serial.println(sddata.data15);
  char readData[100]; // Assuming maximum data length
  int address = 0;
  int address2 = 101;
  char ch;
  while ((ch = EEPROM.read(address)) != '\0' && address < 100) { // Read until null character or EEPROM size limit
    readData[address] = ch;
    address++;
  }
  readData[address] = '\0'; // Null-terminate the read data
  Serial.print("Data read from EEPROM: ");
  Serial.println(readData);
  Serial.println(sizeof(readData));
  //sddata.data15=readData;
  memcpy(&sddata.data21, readData, sizeof(readData));
  sub1='e';


  cl_cnt= EEPROM.read(10); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1: ");
  Serial.println(cl_cnt);

   conec_cnt= EEPROM.read(12); // Read the data from EEPROM
  Serial.print("Data read from EEPROM1: ");
  Serial.println(conec_cnt);
  ttl_hks=conec_cnt*cl_cnt*8;

decimal_number1=EEPROM.read(13); // Read the data from EEPROM
decimal_number2=EEPROM.read(14); // Read the data from EEPROM
decimal_number3=EEPROM.read(15); // Read the data from EEPROM
decimal_number4=EEPROM.read(16); // Read the data from EEPROM
decimal_number5=EEPROM.read(17); // Read the data from EEPROM

decimal_number11=EEPROM.read(18); // Read the data from EEPROM
decimal_number22=EEPROM.read(19); // Read the data from EEPROM
decimal_number33=EEPROM.read(20); // Read the data from EEPROM
decimal_number44=EEPROM.read(21); // Read the data from EEPROM
decimal_number55=EEPROM.read(22); // Read the data from EEPROM
left_right_flag=EEPROM.read(23); 
count_date=EEPROM.read(24); 
count_month=EEPROM.read(25); 
count_year=EEPROM.read(26); 





///First time//
/*
 decimal_number1=110;
  decimal_number2=97;
  decimal_number3=110;
  decimal_number4=100;
  decimal_number5=97;
  decimal_number11=110;
  decimal_number22=97;
  decimal_number33=110;
  decimal_number44=100;
  decimal_number55=97;
  count_date=1;
  count_month=2;
  count_year=25;


  EEPROM.write(13, decimal_number1); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(14, decimal_number2); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(15, decimal_number3); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(16, decimal_number4); // Write the data to EEPROM
   EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(17, decimal_number5); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);

  EEPROM.write(18, decimal_number11); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(19, decimal_number22); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(20, decimal_number33); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(21, decimal_number44); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);
  EEPROM.write(22, decimal_number55); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  delay(10);

      EEPROM.write(24, count_date); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  
  EEPROM.write(25, count_month); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  
  EEPROM.write(26, count_year); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
*/
   
}

void loop(void)
{

   key= keypad.getKey();
  if (doConnect == true) 
  {
    Serial.println("We are now connected to the BLE Server");
    key_set=1;

    if (connectToServer(*pServerAddress)) 
    {
      Serial.println("We are now connected to the BLE Server.");
      //Activate the Notify property of each Characteristic
     
     // temperatureCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
     // humidityCharacteristic->getDescriptor(BLEUUID((uint16_t)0x2902))->writeValue((uint8_t*)notificationOn, 2, true);
      connected = true;
    } else 
    {
      Serial.println("We have failed to connect to the server; Restart your device to scan for nearby BLE server again.");
    }
    doConnect = false;
    delay(500);
    Connected_Scrn();
    delay(4000);
    Running_Scrn();
    Serial.println("screenscreen");

    
      //Serial.print("Data send to cpu  from EEPROM: ");
      String data = sddata.data21;
      // Write the data to the characteristic
     sprintf( result_cl_cnt, "%d", cl_cnt); 
      sprintf( result_conec_cnt, "%d", conec_cnt); 
     combinedString = data.c_str()+temp_str+result_cl_cnt+"&"+ result_conec_cnt;
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
     // humidityCharacteristic->writeValue(data.c_str(), data.length());
      Serial.println("Data sent: " + combinedString);
      connection_flag=1;

  }
  else if(key_set==0 &&doConnect == false )
  {
     Connection_issue_Scrn();
     temp_runscrn=0;
  }

  /*if(doConnect == false && connection_flag==1)
  {

     Serial.println("Dissconnection");
  }*/
 
  if (key && key_set==1)
  {
    Serial.println(key);
    Serial.println(sub);

    if(key=='A'&& sub1=='z')
    {
      if(temp_curs==8)
      {
          temp_curs=1;
      }
       temp_curs+=1;
       /*if(temp_curs>=2)
       {
        up_value_flag2=0;
        up_value_flag1=0;

       }*/
    }
      if((temp_curs==1&& sub1=='z')&&( key=='0'|| key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'))
      {
        String temp_str1="*UP/";
         Serial.println("helllllllllllllllllllllllllllllllllllllllllllllllllllllllll");
        char input=key;
        if (input >= '0' && input <= '9') 
        {
           input=input - '0';
        }

      tick_loop+=1;
      switch(tick_loop)
      {
        case 1 : 
        temp_count_tick=0;
        temp_count_tick=temp_count_tick+input;

        Serial.print("tempcount==");
        Serial.println(temp_count_tick);

        break;
        case 2 :
        temp_count_tick=(10*temp_count_tick)+input;
        Serial.print("tempcount==");
        Serial.println(temp_count_tick);
        break;
        case 3 :
        temp_count_tick=(10*temp_count_tick)+input;
        Serial.print("tempcount==");
        Serial.println(temp_count_tick);
        break;
        case 4 :
        temp_count_tick=(10*temp_count_tick)+input;
        Serial.print("tempcount==");
        Serial.println(temp_count_tick);
        break;
        case 5 :
        temp_count_tick=(10*temp_count_tick)+input;
        Serial.print("tempcount==");
        Serial.println(temp_count_tick);
        break;
        case 6 :
        temp_count_tick=(10*temp_count_tick)+input;
        Serial.print("tempcount==");
        Serial.println(temp_count_tick);
        break;
        default :
        break;
      }

      sprintf( bmpdata.data3, "%d", temp_count_tick); 

       String data = bmpdata.data3;

     combinedString = temp_str1+ data.c_str();

      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());

     // humidityCharacteristic->writeValue(data.c_str(), data.length());

      Serial.println("Data sent: " + combinedString);

     //humidityCharacteristic->writeValue(bmpdata.data3, length);

      Serial.println(combinedString);
      }

    if(temp_curs==1&& sub1=='z'&&key=='C')
    {
        char *endptr;

      String temp_str1="*UP/";

         Serial.println("UP");

    // Your data to be sent

      String data1 = "UP";

      

      int check=strtol(bmpdata.data3, &endptr, 10);

     //check+=1;

     String data22 = bmpdata.data2;

      Serial.println(data22.c_str());

    if(check==strtol(data22.c_str(), &endptr, 10))

     {

     check=0;

     }

     check+=1;

     sprintf( bmpdata.data3, "%d", check); 

       String data = bmpdata.data3;

     combinedString = temp_str1+ data.c_str();

      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());

     // humidityCharacteristic->writeValue(data.c_str(), data.length());

      Serial.println("Data sent: " + combinedString);

     //humidityCharacteristic->writeValue(bmpdata.data3, length);

      Serial.println(combinedString);
       Serial.println("he22222222222222222222222222222222222222222222222222222222222222222222222222222222222");
      
    }

    else if(temp_curs==1&& sub1=='z'&&key=='D')
    {
      char *endptr;

      String temp_str1="*UP/";

         Serial.println("DW");



     int check=strtol(bmpdata.data3, &endptr, 10);

     if(check>0)

     {

     check-=1;

     }

     sprintf( bmpdata.data3, "%d", check); 

       String data = bmpdata.data3;

     combinedString = temp_str1+ data.c_str();

      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());

     // humidityCharacteristic->writeValue(data.c_str(), data.length());

      Serial.println("Data sent: " + combinedString);

     //humidityCharacteristic->writeValue(bmpdata.data3, length);
      Serial.println(combinedString);
      Serial.println("he333333333333333333333333333333333333333333333333333");
    }

    if(key=='B'&& sub1=='z')
    {
        temp_curs=0;
         String data = sddata.data21;
      // Write the data to the characteristic
     sprintf( result_cl_cnt, "%d", cl_cnt); 
      sprintf( result_conec_cnt, "%d", conec_cnt); 
     combinedString = data.c_str()+temp_str+result_cl_cnt+"&"+ result_conec_cnt;
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
     // humidityCharacteristic->writeValue(data.c_str(), data.length());
      Serial.println("Data sentmmmmmmmmmm: " + combinedString);
      tick_loop=0;
      tick_flag=1;
    }

    
    if(key=='5'&& sub1=='z' && temp_curs!=1 ) 
     {  
      Serial.print("myint1=");
      Serial.println(myInt);

         //sendDataToServer();
          if(file_slct<myInt)
          {
              file_slct+=1;
          }
          else 
          file_slct=1;
          memset(&sddata.data21, 0, sizeof(sddata.data21));
          switch(file_slct)
          {
          case 1:
           memcpy(&sddata.data21, sddata.data1, sizeof(sddata.data1));
           Serial.println("numer=1");
           break;
           case 2:
           memcpy(&sddata.data21, sddata.data2, sizeof(sddata.data2));
            Serial.println("numer=2");
           break;
           case 3:
           memcpy(&sddata.data21, sddata.data3, sizeof(sddata.data3));
           Serial.println("numer=3");
           break;
           case 4:
           memcpy(&sddata.data21, sddata.data4, sizeof(sddata.data4));
           Serial.println("numer=4");
           break;
           case 5:
           memcpy(&sddata.data21, sddata.data5, sizeof(sddata.data5));
           Serial.println("numer=5");
           break;
           case 6:
           memcpy(&sddata.data21, sddata.data6, sizeof(sddata.data6));
           Serial.println("numer=6");
           break;
           case 7:
           memcpy(&sddata.data21, sddata.data7, sizeof(sddata.data7));
           Serial.println("numer=7");
           break;
           case 8:
           memcpy(&sddata.data21, sddata.data8, sizeof(sddata.data8));
           Serial.println("numer=8");
           break;
           case 9:
           memcpy(&sddata.data21, sddata.data9, sizeof(sddata.data9));
           Serial.println("numer=9");
           break;
           case 10:
           memcpy(&sddata.data21, sddata.data10, sizeof(sddata.data10));
           Serial.println("numer=10");
           break;
           case 11:
           memcpy(&sddata.data21, sddata.data11, sizeof(sddata.data11));
           Serial.println("numer=11");
           
           break;
           case 12:
           memcpy(&sddata.data21, sddata.data12, sizeof(sddata.data12));
           Serial.println("numer=12");
           break;
           case 13:
           memcpy(&sddata.data21, sddata.data13, sizeof(sddata.data13));
           Serial.println("numer=13");
           break;
           case 14:
           memcpy(&sddata.data21, sddata.data13, sizeof(sddata.data13));
           Serial.println("numer=14");
           break; 
           case 15:
           memcpy(&sddata.data21, sddata.data15, sizeof(sddata.data15));
           Serial.println("numer=15");
           
           break;
           case 16:
           memcpy(&sddata.data21, sddata.data16, sizeof(sddata.data16));
           Serial.println("numer=16");
           break;
           case 17:
           memcpy(&sddata.data21, sddata.data17, sizeof(sddata.data17));
           Serial.println("numer=17");
           break;
           case 18:
           memcpy(&sddata.data21, sddata.data18, sizeof(sddata.data18));
           Serial.println("numer=18");
           break; 
           case 19:
           memcpy(&sddata.data21, sddata.data19, sizeof(sddata.data19));
           Serial.println("numer=19");
           break;
           case 20:
           memcpy(&sddata.data21, sddata.data20, sizeof(sddata.data20));
           Serial.println("numer=20");
           break;             

           default:
           memcpy(&sddata.data21, sddata.data1, sizeof(sddata.data1));
           break;
          }


           int length = strlen(sddata.data21);
  
              for (int i = 0; i < length; i++) 
              {
                  EEPROM.write(i, sddata.data21[i]); // Write each character of the string to EEPROM
              }
            EEPROM.write(length, '\0'); // Null-terminate the string in EEPROM
            EEPROM.commit(); // Commit the data to EEPROM


    if (humidityCharacteristic != nullptr) 
    {

      String combinedString1="";
      // Your data to be sent
      String temp_str11="CH/";
      String data = sddata.data21;
      combinedString =temp_str11+data;

      // humidityCharacteristic->writeValue(data.c_str(), data.length());
       //delay(30);
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
      //Serial.println("Data sent: " +temp_str11+ data);
      //
     
      //Serial.println("Data sent: " + data);
    }
      Running_Scrn();
      Serial.println("screenscreenscreen");
      
      sub1='z'; 
     }
    if(key=='*')
    {
      temp_runscrn=0;
      Menue_Scrn();
      prev_screen=screen;
      mn='a';
      set='1';
      flag='1';
      sub='z';
      sub1='z';
    flag1='@';
     flag2='@';
     flag3='@';
     sub22='@';
      
      screen=1;
    }
    else if(key=='#'||temp_runscrn==1 )
    {
      Running_Scrn();
      prev_screen=screen;
      sub='z';
      flag='0';
      sub1='z';
      flag1='@';
     flag2='@';
     flag3='@';
     sub22='@';
      Serial.println("screen");
      temp_runscrn=1;
    
      //screen=2;
    }
    else if(key=='0')
    {
      screen=prev_screen;
      Serial.println(screen);
      temp_runscrn=0;
    }
    else if(key=='1')
    {
      //prev_sub=sub;
      sub='a';
      temp_runscrn=0;
      
    }
    else if(key=='2')
    {
      temp_runscrn=0;
     // prev_sub=sub;
      sub='b';
      Serial.println("pressed2");
      Serial.println(sub);
      Serial.println(mn);
      Serial.println(set);

    }
    else if(key=='3')
    {
      temp_runscrn=0;
      prev_sub=sub;
      sub='c';
      Serial.println(prev_sub);
    }
    else if(key=='4')
    {
      temp_runscrn=0;
      prev_sub=sub;
      sub='d';
    }
    else if(key=='5')
    {
      temp_runscrn=0;
      prev_sub=sub;
      sub='e';
    }
    
  }
  else if(key=='#'||temp_runscrn==1 )
    {
      temp_runscrn=1;
      Running_Scrn();
      prev_screen=screen;
      sub='z';
      flag='0';
       sub1='z';
       sub22='@';
      flag1='@';
     flag2='@';
     flag3='@';
      //screen=2;

      //Serial.println("Anotherscreen");
    }

    
   /* if(up_value_flag1==1)
    {
        Serial.println("Up_enable");
        char *endptr;
      String temp_str1="*UP/";
         Serial.println("UP");
    // Your data to be sent
      String data1 = "UP";

     
      
      int check=strtol(bmpdata.data3, &endptr, 10);
     //check+=1;
     String data22 = bmpdata.data2;

      Serial.println(data22.c_str());
    if(check==strtol(data22.c_str(), &endptr, 10))
     {
     check=0;
     }
     check+=1;
     sprintf( bmpdata.data3, "%d", check); 
       String data = bmpdata.data3;
     combinedString = temp_str1+ data.c_str();
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
     // humidityCharacteristic->writeValue(data.c_str(), data.length());
      Serial.println("Data sent: " + combinedString);
     //humidityCharacteristic->writeValue(bmpdata.data3, length);
      Serial.println(combinedString);
      delay(400);

    }
    else if(up_value_flag1==2)
    {
       Serial.println("Up_disable");
    }
    if(up_value_flag2==1)
    {
        Serial.println("Down_enable");
                  char *endptr;
      String temp_str1="*UP/";
         Serial.println("DW");

     int check=strtol(bmpdata.data3, &endptr, 10);
     if(check>0)
     {
     check-=1;
     }
     sprintf( bmpdata.data3, "%d", check); 
       String data = bmpdata.data3;
     combinedString = temp_str1+ data.c_str();
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
     // humidityCharacteristic->writeValue(data.c_str(), data.length());
      Serial.println("Data sent: " + combinedString);
     //humidityCharacteristic->writeValue(bmpdata.data3, length);
      Serial.println(combinedString);
       delay(400);
    }
    else if(up_value_flag2==2)
    {
       Serial.println("Down_disable");
    }*/
   
if(mn=='a'&&set=='1' && flag=='1')
{
  if(sub=='a')
  {
      prev_screen=screen;
      Alldesign_Scrn();
      sub='0';
      screen=2;
      flag='2';
     
  }
  else if(sub=='b' && flag2!='3')
  {
     prev_screen=screen;
     Settings_Scrn();
     screen=3;
     flag='3';
     flag1='3';
    sub='0';
     flag2='3';
     flag3='3';
  }
  else if(sub=='c')
  {
    prev_screen=screen;
    System_Dsn_Scrn(); 
    screen=4;
     flag='4';
     sub='0';
  }
  else if(sub=='d')
  {
    
      sub='@';
      flag='5';
      // Serial.println("printf");
      screen=5;
      flag='5';
      Serial.println("printf");
      Serial.println(sub);

  }
  else if(sub=='e')
  {


  /*char* char_ptr1;
  char* char_ptr2 ;
  char* char_ptr3;
  char* char_ptr4;
  char* char_ptr5 ;
  char* char_ptr6;*/

  if(admin_lock_flag==1)
  {

    prev_screen=screen;
    admin_Scrn();
    screen=6;
    flag='6' ;

    Serial.println("printf");
  }
  else
  {
    flag='7';
  }




  // Convert decimal number to character
/*ascii_char1 = decimal_number1; // Convert decimal number to ASCII character
  ascii_char2 = decimal_number2; // Convert decimal number to ASCII character
 ascii_char3 = decimal_number3; // Convert decimal number to ASCII character
 ascii_char4 = decimal_number4; // Convert decimal number to ASCII character
ascii_char5 = decimal_number5; // Convert decimal number to ASCII character
 ascii_char6 = decimal_number6; // Convert decimal number to ASCII character*/


 }
}



//setting screen//
 else if((flag1=='3')&&(sub=='a')) // SETTING 
  {

     flag2='@';
     flag3='@';
     sub22='@';
      Hocksetting_Scrn();

       if(key=='A')
         {
          if(tog_slct==0)
          {
            tog_slct=1;
          }
          else 
          {
            tog_slct=0;
          }
          }
      if(key=='C')
      {
        if(tog_slct==1)
        {
        if(conec_cnt<16)
        {
            conec_cnt+=1;
        }
        }
        else
        {
          if(cl_cnt<12)
        {
            cl_cnt+=1;
        }
        }

          
      }
      else if(key=='D')
      {
         if(tog_slct==1)
        {
        if(conec_cnt>0)
        {
          conec_cnt-=1;
        }
        }
        else
        {
        if(cl_cnt>0)
          {
            cl_cnt-=1;
          }
        }
      }
      Serial.print("Connector =");
      Serial.println(conec_cnt);
      Serial.println(prev_sub);

      ttl_hks=cl_cnt*conec_cnt*8;

      EEPROM.write(10, cl_cnt); // Write the data to EEPROM
      EEPROM.commit(); // Commit the data to EEPROM
      delay(2);
      EEPROM.write(12, conec_cnt); // Write the data to EEPROM
      EEPROM.commit(); // Commit the data to EEPROM
      delay(2);
  

  }
  else if((flag=='5')&&(sub=='@')) // SETTING
  {
     prev_screen=screen;
     // Serial.println("printf");
    if(key=='A')
      {
          if(tog_slct1==0)
          {
            tog_slct1=1;
          }
          else 
          {
            tog_slct1=0;
          }

           Serial.println(tog_slct1);
      }
	 if(tog_slct1==0)
	 {
			Dlt_Dsn_Scrn();
      Serial.println("print1");
	 }
	 else if(tog_slct1==1)
	 {
       //Serial.println("print2");
			u8g2.clearBuffer();					// clear the internal memory
			u8g2.setFont(u8g2_font_5x7_tr);
			u8g2.drawStr(5,15,"Select design to Delete");	// write something to the internal memory
			u8g2.drawStr(10,40,"File:");	// write something to the internal memory
			u8g2.drawStr(40,40,sddata.data22);	// write something to the internal memory
      u8g2.drawStr(10,55,"Press ok to delete");	// write something to the internal memory
      u8g2.sendBuffer();
	 }

 

	
	
	 if(key=='C')
      {

        if(delet_screen<myInt)
        {
            delet_screen+=1;
        }
      }   
      else if(key=='D')
      {
        if(delet_screen>0)
        {
          delet_screen-=1;
        }
	  }
	
	  switch(delet_screen)
	  {
	  
	  case 1: 
	     memcpy(&sddata.data22, sddata.data1, sizeof(sddata.data1));
       
		 break;
		 case 2:
		 memcpy(&sddata.data22, sddata.data2, sizeof(sddata.data2));
		 break;
         case 3:
		 memcpy(&sddata.data22, sddata.data3, sizeof(sddata.data3));
		 break;
		 case 4: 
	     memcpy(&sddata.data22, sddata.data4, sizeof(sddata.data4));
		 break;
		 case 5:
		 memcpy(&sddata.data22, sddata.data5, sizeof(sddata.data5));
		 break;
         case 6:
		 memcpy(&sddata.data22, sddata.data6, sizeof(sddata.data6));
		 break; 
		 case 7: 
	     memcpy(&sddata.data22, sddata.data7, sizeof(sddata.data7));
		 break;
		 case 8:
		 memcpy(&sddata.data22, sddata.data8, sizeof(sddata.data8));
		 break;
         case 9:
		 memcpy(&sddata.data22, sddata.data9, sizeof(sddata.data10));
		 break;
		 case 10: 
	     memcpy(&sddata.data22, sddata.data11, sizeof(sddata.data11));
		 break;
		 case 11:
		 memcpy(&sddata.data22, sddata.data12, sizeof(sddata.data12));
		 break;
         case 12:
		 memcpy(&sddata.data22, sddata.data13, sizeof(sddata.data13));
		 break;
		 case 13: 
	     memcpy(&sddata.data22, sddata.data13, sizeof(sddata.data13));
		 break;
		 case 14:
		 memcpy(&sddata.data22, sddata.data14, sizeof(sddata.data14));
		 break;
         case 15:
		 memcpy(&sddata.data22, sddata.data15, sizeof(sddata.data15));
		 break;
		 case 16: 
	     memcpy(&sddata.data22, sddata.data16, sizeof(sddata.data16));
		 break;
		 case 17:
		 memcpy(&sddata.data22, sddata.data17, sizeof(sddata.data17));
		 break;
         case 18:
		 memcpy(&sddata.data22, sddata.data18, sizeof(sddata.data18));
		 break;	 
		 case 19: 
	     memcpy(&sddata.data22, sddata.data19, sizeof(sddata.data19));
		 break;
		 case 20:
		 memcpy(&sddata.data22, sddata.data20, sizeof(sddata.data20));
		 break; 
     default:
      memcpy(&sddata.data22, sddata.data1, sizeof(sddata.data1));
      break;

	   
	  }
     if(key=='B')
      {
      String combinedString22="";
      // Your data to be sent
      String temp_str11="DL/";
      String data = sddata.data22;
      combinedString22 =temp_str11+data;
      humidityCharacteristic->writeValue(combinedString22.c_str(), combinedString22.length());
     
    // doConnect=false;
     // delay(500);
      // doConnect=true;

      /* switch(delet_screen)
	  {
	  
	  case 1: 
    memset(&sddata.data1, 0, sizeof(sddata.data1));

		 break;
		 case 2:
		 memset(&sddata.data2, 0, sizeof(sddata.data2));
		 break;
         case 3:
		 memset(&sddata.data3, 0, sizeof(sddata.data3));
		 break;
		 case 4: 
	     memset(&sddata.data4, 0, sizeof(sddata.data4));
		 break;
		 case 5:
		 memset(&sddata.data5, 0, sizeof(sddata.data5));
		 break;
         case 6:
		 memset(&sddata.data6, 0, sizeof(sddata.data6));
		 break; 
		 case 7: 
	     memset(&sddata.data7, 0, sizeof(sddata.data7));
		 break;
		 case 8:
		 memset(&sddata.data8, 0, sizeof(sddata.data8));
		 break;
         case 9:
		 memset(&sddata.data9, 0, sizeof(sddata.data9));
		 break;
		 case 10: 
	     memset(&sddata.data10, 0, sizeof(sddata.data10));
		 break;
		 case 11:
		 memset(&sddata.data11, 0, sizeof(sddata.data11));
		 break;
         case 12:
		 memset(&sddata.data12, 0, sizeof(sddata.data12));
		 break;
		 case 13: 
	     memset(&sddata.data13, 0, sizeof(sddata.data13));
		 break;
		 case 14:
		 memset(&sddata.data14, 0, sizeof(sddata.data14));
		 break;
         case 15:
		 memset(&sddata.data15, 0, sizeof(sddata.data15));
		 break;
		 case 16: 
	     memset(&sddata.data16, 0, sizeof(sddata.data16));
		 break;
		 case 17:
		 memset(&sddata.data17, 0, sizeof(sddata.data17));
		 break;
         case 18:
		 memset(&sddata.data18, 0, sizeof(sddata.data18));
		 break;	 
		 case 19: 
	     memset(&sddata.data19, 0, sizeof(sddata.data19));
		 break;
		 case 20:
		 memset(&sddata.data20, 0, sizeof(sddata.data20));
		 break;   
      }*/

        myInt=0;
  }
  }
  else if((flag2=='3')&&(sub=='b')) // design left to right 
  {
     flag1='@';
     flag3='@';
     sub22='p';
      Serial.println("hellow11");
       Serial.println(flag2);
         Serial.println(sub22);
         sub='@';
         flag2='4';


  }
  else if((flag2=='4')&&(sub22=='p')) // design left to right 
  {
     flag1='@';
     flag3='@';
     

     if(active_state==0)
      {
           Dsn_Left_Right_Scrn();
      }
      if(key=='2')  // right side selection 
      {
          Dsn_right_Scrn();
          active_state=2;
          left_right_flag=2;

      }
      if(key=='1')
      {
       //  Serial.println("hellow");
       //  Serial.println(flag2);
       //  Serial.println(sub22);
         Dsn_Left_Scrn();
          active_state=1;
          left_right_flag=1;
      }
     
      if(key=='B')
      {

           char left_right_flag_char[10]; 
          active_state=0;
          String combinedString44="";
         // Your data to be sent
         String temp_str55="LR/"; // left right design selection

         sprintf( left_right_flag_char, "%d", left_right_flag);
         String data = left_right_flag_char;
         combinedString44 =temp_str55+data;
         humidityCharacteristic->writeValue(combinedString44.c_str(), combinedString44.length());
          EEPROM.write(23, left_right_flag); // Write the data to EEPROM
          EEPROM.commit(); // Commit the data to EEPROM
      }

     
  }
  else if((flag3=='3')&&(sub=='c'))
  {
     flag1='@';
     flag2='@';
     sub22='@';
     
     
      Running_Lock_Scrn();

      if(key=='A')
         {

            if(tog_slct2==3)
            {
               tog_slct2=0;
            }
            if(tog_slct2<=4)
            {
               tog_slct2+=1;
            }
          }


      if(key=='C' && tog_slct2==1)  // date setting 
      {

        if(count_date==31)
        {
          count_date=1;
        }
        else if(count_date<32)
        {
          count_date+=1;
        } 
      }

      else if(key=='D' && tog_slct2==1)  // date setting 
      {
        if(count_date>0)
        {
          count_date-=1;
        }
      }
      else if(key=='C' && tog_slct2==2)  // month setting 
      {

        if(count_month==12)
        {
          count_month=1;
        }
        else if(count_month<13)
        {
          count_month+=1;
        }
        
      }
      else if(key=='D' && tog_slct2==2)  // month setting 
      {
        if(count_month>0)
        {
          count_month-=1;
        }
      }
      else if(key=='C' && tog_slct2==3)  // month setting 
      {

        if(count_year==29)
        {
          count_year=24;
        }
        else if(count_year<30)
        {
          count_year+=1;
        }
        
      }

      else if(key=='D' && tog_slct2==3)  // month setting 
      {
        if( count_year>0)
        {
          count_year-=1;
        }

      }


      

  }

  else if((flag=='4')&&(sub=='a')) // SETTING 
  {
      u8g2.clearBuffer();					// clear the internal memory
      u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
      u8g2.drawStr(12,12,"Sysytem Design");	// write something to the internal memory
      u8g2.drawStr(40,40,"All Up");	// write something to the internal memory
      u8g2.sendBuffer();					// transfer internal memory to the display

      if (modeCharacteristic != nullptr) 
    {
    // Your data to be sent
    String data = mddata.data1;
    // Write the data to the characteristic
    modeCharacteristic->writeValue(data.c_str(), data.length());
    Serial.println("Data sent: " + data);
    }
  }
  else if((flag=='4')&&(sub=='b')) // SETTING 
  {
     u8g2.clearBuffer();					// clear the internal memory
      u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
      u8g2.drawStr(12,12,"Sysytem Design");	// write something to the internal memory
      u8g2.drawStr(30,40,"All Down");	// write something to the internal memory
      u8g2.sendBuffer();					// transfer internal memory to the display
        if (modeCharacteristic != nullptr) 
    {
    // Your data to be sent
    String data = mddata.data2;
    // Write the data to the characteristic
    modeCharacteristic->writeValue(data.c_str(), data.length());
    Serial.println("Data sent: " + data);
    }
  }
  else if((flag=='4')&&(sub=='c')) // SETTING 
  {
      u8g2.clearBuffer();					// clear the internal memory
      u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
      u8g2.drawStr(12,12,"Sysytem Design");	// write something to the internal memory
      u8g2.drawStr(30,40,"8 Up & 8 Down");	// write something to the internal memory
      u8g2.sendBuffer();					// transfer internal memory to the display

        if (modeCharacteristic != nullptr) 
    {
    // Your data to be sent
    String data = mddata.data3;
    // Write the data to the characteristic
    modeCharacteristic->writeValue(data.c_str(), data.length());
    Serial.println("Data sent: " + data);
    }
  }
  else if((flag=='4')&&(sub=='d')) // SETTING 
  {
      u8g2.clearBuffer();					// clear the internal memory
      u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
      u8g2.drawStr(12,12,"Sysytem Design");	// write something to the internal memory
      u8g2.drawStr(30,40,"1 Up & 1 Down");	// write something to the internal memory
      u8g2.sendBuffer();					// transfer internal memory to the display
        if (modeCharacteristic != nullptr) 
    {
    // Your data to be sent
    String data = mddata.data4;
    // Write the data to the characteristic
    modeCharacteristic->writeValue(data.c_str(), data.length());
    Serial.println("Data sent: " + data);
    }
  }

if(flag=='6')
{
   
    //Serial.println("hellow world");

  

    if(key=='1')
    {
      screen_admin=1;

    }
    if(key=='2')
    {
      screen_admin=2;
    }

    if(key=='3')
    {
      screen_admin=3;
    }


    if(key=='B')
    {
      if(screen_admin==3)
      {
        String temp_str33="MU/"; // Machine unlock 
        String temp_str66="A"; // date 
        //String data = sddata.data22;
        combinedString33 =temp_str33+"1";
        humidityCharacteristic->writeValue(combinedString33.c_str(), combinedString33.length());
      }
      else if(screen_admin==1||screen_admin==1)
      {

      }
      screen_admin=0;
      tog_slct3=0;
    }

    if(screen_admin==1 )
    {


        if(key=='A')
         {
            if(tog_slct3<7)
            {
              tog_slct3+=1;
              if(tog_slct3==6)
              {
                tog_slct3=1;
              }
            }
        }
        if(key=='C')
        {
          switch(tog_slct3)
          {
            case 1:
            if(decimal_number1<=123)
            {
              if(decimal_number1==122)
              {
                decimal_number1=97;
              }
                decimal_number1+=1;
                EEPROM.write(13, decimal_number1); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM

            }
            break;
            case 2:
            if(decimal_number2<=123)
            {
              if(decimal_number2==122)
              {
                decimal_number2=97;
              }
                decimal_number2+=1;
                EEPROM.write(14, decimal_number2); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM


            }
            break;    
            case 3:
            if(decimal_number3<=123)
            {
              if(decimal_number3==122)
              {
                decimal_number3=97;
              }
                decimal_number3+=1;
                EEPROM.write(15, decimal_number3); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM


            }
            break;        
            case 4:
            if(decimal_number4<=123)
            {
              if(decimal_number4==122)
              {
                decimal_number4=97;
              }
                decimal_number4+=1;
                EEPROM.write(16, decimal_number4); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM

            }
            break; 
            case 5:
            if(decimal_number5<=123)
            {
              if(decimal_number5==122)
              {
                decimal_number5=97;
              }
                decimal_number5+=1;
                EEPROM.write(17, decimal_number5); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            default:
            break;
        }

        }
          
  
      if(key=='D')
      {
        switch(tog_slct3)
          {
            case 1:
            if(decimal_number1>96)
            {
                decimal_number1-=1;
                EEPROM.write(13, decimal_number1); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;
            case 2:
            if(decimal_number2>96)
            {

                decimal_number2-=1;
                EEPROM.write(14, decimal_number2); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;    
            case 3:
            if(decimal_number3>96)
            {
              
                decimal_number3-=1;
                EEPROM.write(15, decimal_number3); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;        
          
            case 4:
            if(decimal_number4>96)
            {

                decimal_number4-=1;
                EEPROM.write(16, decimal_number4); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            case 5:
            if(decimal_number5>96)
            {
                decimal_number5-=1;
                EEPROM.write(17, decimal_number5); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            default:
            break;
      }
      }
 
        admin_Scrn2();
    }
    else if (screen_admin==2)
    {

       if(key=='A')
         {
            if(tog_slct3<7)
            {
              tog_slct3+=1;
              if(tog_slct3==6)
              {
                tog_slct3=1;
              }
            }
        }
        if(key=='C')
        {
          switch(tog_slct3)
          {
            case 1:
            if(decimal_number11<=123)
            {
              if(decimal_number11==122)
              {
                decimal_number11=97;
              }
                decimal_number11+=1;
                EEPROM.write(18, decimal_number11); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM

            }
            break;
            case 2:
            if(decimal_number22<=123)
            {
              if(decimal_number22==122)
              {
                decimal_number22=97;
              }
                decimal_number22+=1;
                EEPROM.write(19, decimal_number22); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM


            }
            break;    
            case 3:
            if(decimal_number33<=123)
            {
              if(decimal_number33==122)
              {
                decimal_number33=97;
              }
                decimal_number33+=1;
                EEPROM.write(20, decimal_number33); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM


            }
            break;        
            case 4:
            if(decimal_number44<=123)
            {
              if(decimal_number44==122)
              {
                decimal_number44=97;
              }
                decimal_number44+=1;
                EEPROM.write(21, decimal_number44); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM

            }
            break; 
            case 5:
            if(decimal_number55<=123)
            {
              if(decimal_number55==122)
              {
                decimal_number55=97;
              }
                decimal_number55+=1;
                EEPROM.write(22, decimal_number55); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            default:
            break;
        }

        }
          
  
      if(key=='D')
      {
        switch(tog_slct3)
          {
            case 1:
            if(decimal_number11>96)
            {
                decimal_number11-=1;
                EEPROM.write(18, decimal_number11); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;
            case 2:
            if(decimal_number22>96)
            {

                decimal_number22-=1;
                EEPROM.write(19, decimal_number22); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;    
            case 3:
            if(decimal_number33>96)
            {
              
                decimal_number33-=1;
                EEPROM.write(20, decimal_number33); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break;        
          
            case 4:
            if(decimal_number44>96)
            {

                decimal_number44-=1;
                EEPROM.write(21, decimal_number44); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            case 5:
            if(decimal_number55>96)
            {
                decimal_number55-=1;
                EEPROM.write(22, decimal_number55); // Write the data to EEPROM
                EEPROM.commit(); // Commit the data to EEPROM
            }
            break; 
            default:
            break;
      }
      }
        admin_Scrn3();
    }
    else if(screen_admin==3)
    {
      admin_Scrn4();
    }
    else
    {
        admin_Scrn();
    }
}
if(flag=='7')
{
  admin_mode();


}
}



void Welcome_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(16,10,"Jerusha Enterprises");	// write something to the internal memory
  u8g2.drawStr(40,24,"Welcome");	// write something to the internal memory
  u8g2.drawStr(55,38,"To");	// write something to the internal memory
  u8g2.drawStr(19,50,"Morvel Jacquard");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display


  //delay(10000);  
}

void Menue_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(19,10,"Morvel Jacquard");	// write something to the internal memory
  //u8g2.drawBox(5, 20, 5, 20);
  u8g2.drawStr(5,20,"1.All Design");	// write something to the internal memory
  u8g2.drawStr(5,30,"2.Settings");	// write something to the internal memory
  u8g2.drawStr(5,40,"3.System Design");	// write something to the internal memory
  u8g2.drawStr(5,50,"4.Delete Designs");	// write something to the internal memory
  u8g2.drawStr(5,61,"5.Pass & User Name Set");	// write something to the internal memory
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  
}

void Alldesign_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawStr(30,7,"All Design");	// write something to the internal memory
  
  u8g2.drawStr(5,17,"1.");	// write something to the internal memory
  u8g2.drawStr(5,24,"2.");	// write something to the internal memory
  u8g2.drawStr(5,31,"3.");	// write something to the internal memory
  u8g2.drawStr(5,38,"4.");	// write something to the internal memory
  u8g2.drawStr(5,45,"5.");	// write something to the internal memory
  u8g2.drawStr(5,52,"6.");	// write something to the internal memory
  u8g2.drawStr(5,59,"7.");	// write something to the internal memory

  u8g2.drawStr(45,17,"8.");	// write something to the internal memory
  u8g2.drawStr(45,24,"9.");	// write something to the internal memory
  u8g2.drawStr(45,31,"10.");	// write something to the internal memory
  u8g2.drawStr(45,38,"11.");	// write something to the internal memory
  u8g2.drawStr(45,45,"12.");	// write something to the internal memory
  u8g2.drawStr(45,52,"13.");	// write something to the internal memory
  u8g2.drawStr(45,59,"14.");	// write something to the internal memory

  u8g2.drawStr(15,17,sddata.data1);	// write something to the internal memory
  u8g2.drawStr(15,24,sddata.data2);	// write something to the internal memory
  u8g2.drawStr(15,31,sddata.data3);	// write something to the internal memory
  u8g2.drawStr(15,38,sddata.data4);	// write something to the internal memory
  u8g2.drawStr(15,45,sddata.data5);	// write something to the internal memory
  u8g2.drawStr(15,52,sddata.data6);	// write something to the internal memory
  u8g2.drawStr(15,59,sddata.data7);	// write something to the internal memory

  u8g2.drawStr(60,17,sddata.data8);	// write something to the internal memory
  u8g2.drawStr(60,24,sddata.data9);	// write something to the internal memory
  u8g2.drawStr(60,31,sddata.data10);	// write something to the internal memory
  u8g2.drawStr(60,38,sddata.data11);	// write something to the internal memory
  u8g2.drawStr(60,45,sddata.data12);	// write something to the internal memory
  u8g2.drawStr(60,52,sddata.data13);	// write something to the internal memory
  u8g2.drawStr(60,59,sddata.data14);	// write something to the internal memory
  
  //u8g2.drawStr(5,61,"5.Delete Designs");	// write something to the internal memory
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  

}

void Settings_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(30,10,"Settings");	// write something to the internal memory
  u8g2.drawStr(5,22,"1.Hook Setting");	// write something to the internal memory
  u8g2.drawStr(5,34,"2.Design Left & Right");	// write something to the internal memory
  u8g2.drawStr(5,46,"3.Running lock Date");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  


}

void Dsn_Left_Right_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(20,10,"Design Left & Right");	// write something to the internal memory
  u8g2.drawStr(5,22,"1.Left");	// write something to the internal memory
  u8g2.drawStr(5,34,"2.Right");	// write something to the internal memory
  u8g2.drawStr(5,50,"Present Format :");	// write something to the internal memory
  if(left_right_flag==2)
  {
    u8g2.drawStr(90,50,"Right");	// write something to the internal memory
  }
  else //if(left_right_flag==1)
  {
    u8g2.drawStr(90,50,"Left");	// write something to the internal memory
  }
  
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  

}

void Dsn_Left_Scrn()

{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(20,10,"Design Left & Right");	// write something to the internal memory
  u8g2.drawStr(5,34,"Left side design Start");	// write something to the internal memory
  u8g2.drawStr(5,50,"Press Ok to select");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  

}

void Dsn_right_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(20,10,"Design Left & Right");	// write something to the internal memory
  u8g2.drawStr(5,34,"Right side design Start");	// write something to the internal memory
  u8g2.drawStr(5,55,"Press Ok to select");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  

}


void Running_Lock_Scrn()
{
 /* u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(20,10,"Running lock Date");	// write something to the internal memory

  u8g2.drawStr(5,22,"Running Date:");	// write something to the internal memory
  u8g2.drawStr(5,34,"Running Time:");	// write something to the internal memory
   u8g2.drawStr(5,46,"Lock Date:");	// write something to the internal memory
  u8g2.drawStr(5,58,"Lock Time:");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display */


  String count_date_str = String(count_date);
  String count_month_str = String(count_month);
  String count_year_str = String(count_year);
   

// Convert String to C-style string
const char* count_date_cstr = count_date_str.c_str();
const char* count_month_cstr = count_month_str.c_str();
const char* count_year_cstr = count_year_str.c_str();


  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(20,10,"Running lock Date");	// write something to the internal memory

  u8g2.drawStr(5,22,"Lock Date   :");	// write something to the internal memory
  u8g2.drawStr(70,22,count_date_cstr);	// write something to the internal memory

  u8g2.drawStr(5,34,"Lock Month :");	// write something to the internal memory
  u8g2.drawStr(70,34,count_month_cstr);	// write something to the internal memory

  u8g2.drawStr(5,46,"Lock year   :");	// write something to the internal memory
  u8g2.drawStr(70,46,count_year_cstr);	// write something to the internal memory
  u8g2.drawStr(5,58,"Lock ON:");	// write something to the internal memory
  u8g2.drawStr(55,58,count_date_cstr);	// write something to the internal memory
  u8g2.drawStr(65,58,"/");	// write something to the internal memory
  u8g2.drawStr(76,58,count_month_cstr);	// write something to the internal memory
  u8g2.drawStr(87,58,"/");	// write something to the internal memory
  u8g2.drawStr(93,58,count_year_cstr);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display 


       


  if(key=='B')
  {

          
    EEPROM.write(24, count_date); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  
  EEPROM.write(25, count_month); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
  
  EEPROM.write(26, count_year); // Write the data to EEPROM
  EEPROM.commit(); // Commit the data to EEPROM
        String temp_str33="AA/"; // date 
        String temp_str66="A"; // date 
        //String data = sddata.data22;
        combinedString33 =temp_str33+count_date_cstr+ temp_str66+count_month_cstr+temp_str66+count_year_cstr;
        humidityCharacteristic->writeValue(combinedString33.c_str(), combinedString33.length());
  }
     
}


void Lock_Noti_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  
  u8g2.drawStr(5,22,"Machine Is Locked ");	// write something to the internal memory
  u8g2.drawStr(5,34,"Balance Money Pay");	// write something to the internal memory
   u8g2.drawStr(5,46,"Contact Company");	// write something to the internal memory
  u8g2.drawStr(5,58,"Ph:");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  
}


void System_Dsn_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(30,10,"System Design");	// write something to the internal memory
  u8g2.drawStr(5,22,"1.All Up");	// write something to the internal memory
  u8g2.drawStr(5,34,"2.All Down");	// write something to the internal memory
  u8g2.drawStr(5,46,"3.8 Up & 8 Down");	// write something to the internal memory
  u8g2.drawStr(5,58,"4.1 Up & 1 Down");	// write something to the internal memory
  //u8g2.drawStr(5,61,"5.Delete Designs");	// write something to the internal memory
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
   

}

void Dlt_Dsn_Scrn()
{
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_5x7_tr);
  u8g2.drawStr(30,7,"Delete Designs");	// write something to the internal memory
  
  u8g2.drawStr(5,17,"1.");	// write something to the internal memory
  u8g2.drawStr(5,24,"2.");	// write something to the internal memory
  u8g2.drawStr(5,31,"3.");	// write something to the internal memory
  u8g2.drawStr(5,38,"4.");	// write something to the internal memory
  u8g2.drawStr(5,45,"5.");	// write something to the internal memory
  u8g2.drawStr(5,52,"6.");	// write something to the internal memory
  u8g2.drawStr(5,59,"7.");	// write something to the internal memory

  u8g2.drawStr(40,17,"8.");	// write something to the internal memory
  u8g2.drawStr(40,24,"9.");	// write something to the internal memory
  u8g2.drawStr(40,31,"10.");	// write something to the internal memory
  u8g2.drawStr(40,38,"11.");	// write something to the internal memory
  u8g2.drawStr(40,45,"12.");	// write something to the internal memory
  u8g2.drawStr(40,52,"13.");	// write something to the internal memory
  u8g2.drawStr(40,59,"14.");	// write something to the internal memory

  u8g2.drawStr(15,17,sddata.data1);	// write something to the internal memory
  u8g2.drawStr(15,24,sddata.data2);	// write something to the internal memory
  u8g2.drawStr(15,31,sddata.data3);	// write something to the internal memory
  u8g2.drawStr(15,38,sddata.data4);	// write something to the internal memory
  u8g2.drawStr(15,45,sddata.data5);	// write something to the internal memory
  u8g2.drawStr(15,52,sddata.data6);	// write something to the internal memory
  u8g2.drawStr(15,59,sddata.data7);	// write something to the internal memory

  u8g2.drawStr(55,17,sddata.data8);	// write something to the internal memory
  u8g2.drawStr(55,24,sddata.data9);	// write something to the internal memory
  u8g2.drawStr(55,31,sddata.data10);	// write something to the internal memory
  u8g2.drawStr(55,38,sddata.data11);	// write something to the internal memory
  u8g2.drawStr(55,45,sddata.data12);	// write something to the internal memory
  u8g2.drawStr(55,52,sddata.data13);	// write something to the internal memory
  u8g2.drawStr(55,59,sddata.data14);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display admin_Scrn
}

void admin_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Pass & User Name Set");	// write something to the internal memory
  u8g2.drawStr(5,25,"1.User Name");	// write something to the internal memory
 /* u8g2.drawStr(45,25,char_ptr1);	// write something to the internal memory
  u8g2.drawStr(52,25,char_ptr2);	// write something to the internal memory
  u8g2.drawStr(59,25,char_ptr3);	// write something to the internal memory
  u8g2.drawStr(66,25,char_ptr4);	// write something to the internal memory
  u8g2.drawStr(73,25,char_ptr5);	// write something to the internal memory*/
  u8g2.drawStr(5,37,"2.Password ");	// write something to the internal memory
  u8g2.drawStr(5,49,"3.Machine Unlock ");	// write something to the internal memory

  //u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display


   //Serial.println("continous data");

  /*delete[] char_ptr1;
  delete[] char_ptr2;
  delete[] char_ptr3;
  delete[] char_ptr4;
  delete[] char_ptr5; */    
  
}


void admin_mode()
{
  //u8g2.begin();
  static int x=0;
  static int intValue=0;
  static int loop=0;

 // Serial.print("x=");
 // Serial.println(x);
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(30,12,"Admin Mode");	// write something to the internal memory
  u8g2.drawStr(5,35,"Enter Password :");	// write something to the internal memory
  
  if((key=='1'|| key=='2'|| key=='3'|| key=='4'|| key=='5'|| key=='6'|| key=='7'|| key=='8'|| key=='9'|| key=='0')&&x<7)
  {
    x+=1;
     //intValue = key- '0';
     
     if(loop<1)
     {
       loop+=1;

     }
    
     
  }
  if(x==2)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
     u8g2.drawStr(90,35,"*");	// write something to the internal memory
     if(loop==1)
     {
        pas_array2[0]=intValue;
     }
     loop=0;
     
  }
  else if(x==3)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
    u8g2.drawStr(90,35,"**");	// write something to the internal memory
         if(loop==1)
     {
        pas_array2[1]=intValue;
     }
     loop=0;
  }
  else if(x==4)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
    u8g2.drawStr(90,35,"***");	// write something to the internal memory
         if(loop==1)
     {
        pas_array2[2]=intValue;
     }
     loop=0;
  }
  else if(x==5)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
    u8g2.drawStr(90,35,"****");	// write something to the internal memory
         if(loop==1)
     {
        pas_array2[3]=intValue;
     }
     loop=0;
  }
  else if(x==6)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
    u8g2.drawStr(90,35,"*****");	// write something to the internal memory
         if(loop==1)
     {
        pas_array2[4]=intValue;
     }
     loop=0;
  }
  else if(x==7)
  {
     intValue = key- '0';
     Serial.print("intValue=");
     Serial.println(intValue);
    u8g2.drawStr(90,35,"******");	// write something to the internal memory
         if(loop==1)
     {
        pas_array2[5]=intValue;
     }
     loop=0;
  }
  u8g2.drawStr(5,55,"Press Ok to confirm ");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display  


  if(key=='B'&&x==7)
  {
    

  Serial.print("pas_array2[0]==");
 Serial.println(pas_array2[0]);
 Serial.print("pas_array2[1]==");
 Serial.println(pas_array2[1]);
   Serial.print("pas_array2[2]==");
 Serial.println(pas_array2[2]);
   Serial.print("pas_array2[3]==");
 Serial.println(pas_array2[3]);
   Serial.print("pas_array2[4]==");
 Serial.println(pas_array2[4]);
   Serial.print("pas_array2[5]==");
 Serial.println(pas_array2[5]);

    
  bool arraysEqual = memcmp(pas_array1, pas_array2, sizeof(pas_array1)) == 0;
  
  // Output result
  if (arraysEqual) 
  {
    Serial.println("Password Matched ");
    x=0;
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
    u8g2.drawStr(30,12,"Admin Mode");	// write something to the internal memory
    u8g2.drawStr(5,35,"Entered Password corrcet");	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display  
    delay (1000);
    prev_screen=screen;
    admin_Scrn();
    screen=6;
    flag='6';
  } 
  else {
    Serial.println("Password Not mached .");
    x=1;
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
    u8g2.drawStr(30,12,"Admin Mode");	// write something to the internal memory
    u8g2.drawStr(2,35,"Entered Password Wrong");	// write something to the internal memory
    u8g2.drawStr(5,55,"try Again");	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display  
    delay (1000);
  }
  }
   //Serial.println("Mode2");
}


void admin_Scrn2()
{

  char* char_ptr1;
  char* char_ptr2 ;
  char* char_ptr3;
  char* char_ptr4;
  char* char_ptr5 ;
  char* char_ptr6;
  char_ptr1= new char[2]; 
  char_ptr2= new char[2]; 
  char_ptr3= new char[2]; 
  char_ptr4= new char[2]; 
  char_ptr5= new char[2]; 
  char_ptr6= new char[2]; 


  char ascii_char1=decimal_number1;
  char ascii_char2=decimal_number2; 
  char ascii_char3=decimal_number3;
  char ascii_char4=decimal_number4;
  char ascii_char5=decimal_number5 ;
  char ascii_char6=decimal_number6;

  char_ptr1[0] = ascii_char1; // As
  char_ptr2[0] = ascii_char2; // As
  char_ptr3[0] = ascii_char3; // As
  char_ptr4[0] = ascii_char4; // As
  char_ptr5[0] = ascii_char5; // As
  char_ptr6[0] = ascii_char6; // As

  char_ptr1[1] = '\0'; // Null terminate the string
  char_ptr2[1] = '\0'; // Null terminate the string
  char_ptr3[1] = '\0'; // Null terminate the string
  char_ptr4[1] = '\0'; // Null terminate the string
  char_ptr5[1] = '\0'; // Null terminate the string
  char_ptr6[1] = '\0'; // Null terminate the string

  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"User Name Setting");	// write something to the internal memory
  u8g2.drawStr(5,35,"User Name: ");	// write something to the internal memory
  u8g2.drawStr(70,35,char_ptr1);	// write something to the internal memory
  u8g2.drawStr(77,35,char_ptr2);	// write something to the internal memory
  u8g2.drawStr(84,35,char_ptr3);	// write something to the internal memory
  u8g2.drawStr(91,35,char_ptr4);	// write something to the internal memory
  u8g2.drawStr(98,35,char_ptr5);	// write something to the internal memory
  u8g2.drawStr(5,60,"After Changes Select Ok");	// write something to the internal memory
  //u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display


   //Serial.println("continous data");change 

  delete[] char_ptr1;
  delete[] char_ptr2;
  delete[] char_ptr3;
  delete[] char_ptr4;
  delete[] char_ptr5; 
  delete[] char_ptr6;     
  
}

void admin_Scrn4()
{
   
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Machine Unlock");	// write something to the internal memory
  u8g2.drawStr(5,35,"Press Ok to unlock");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

}

void admin_Scrn3()
{
   char* char_ptr11;
  char* char_ptr22 ;
  char* char_ptr33;
  char* char_ptr44;
  char* char_ptr55 ;
  char* char_ptr66;
  char_ptr11= new char[2]; 
  char_ptr22= new char[2]; 
  char_ptr33= new char[2]; 
  char_ptr44= new char[2]; 
  char_ptr55= new char[2]; 
  char_ptr66= new char[2]; 


  char ascii_char11=decimal_number11;
  char ascii_char22=decimal_number22; 
  char ascii_char33=decimal_number33;
  char ascii_char44=decimal_number44;
  char ascii_char55=decimal_number55 ;
  char ascii_char66=decimal_number66;

  char_ptr11[0] = ascii_char11; // As
  char_ptr22[0] = ascii_char22; // As
  char_ptr33[0] = ascii_char33; // As
  char_ptr44[0] = ascii_char44; // As
  char_ptr55[0] = ascii_char55; // As
  char_ptr66[0] = ascii_char66; // As

  char_ptr11[1] = '\0'; // Null terminate the string
  char_ptr22[1] = '\0'; // Null terminate the string
  char_ptr33[1] = '\0'; // Null terminate the string
  char_ptr44[1] = '\0'; // Null terminate the string
  char_ptr55[1] = '\0'; // Null terminate the string
  char_ptr66[1] = '\0'; // Null terminate the string

  /*//u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Password setting");	// write something to the internal memory
  u8g2.drawStr(5,35,"Password: ");	// write something to the internal memory
  u8g2.drawStr(70,35,char_ptr11);	// write something to the internal memory
  u8g2.drawStr(77,35,char_ptr22);	// write something to the internal memory
  u8g2.drawStr(84,35,char_ptr33);	// write something to the internal memory
  u8g2.drawStr(91,35,char_ptr44);	// write something to the internal memory
  u8g2.drawStr(98,35,char_ptr55);	// write something to the internal memory
  u8g2.drawStr(5,60,"After Changes Select Ok");	// write something to the internal memory
  //u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display*/

  if(tog_slct3>=1)
  {
                //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Password setting");	// write something to the internal memory
  u8g2.drawStr(5,35,"Password: ");	// write something to the internal memory
  u8g2.drawStr(70,35,char_ptr11);	// write something to the internal memory
  u8g2.drawStr(77,35,char_ptr22);	// write something to the internal memory
  u8g2.drawStr(84,35,char_ptr33);	// write something to the internal memory
  u8g2.drawStr(91,35,char_ptr44);	// write something to the internal memory
  u8g2.drawStr(98,35,char_ptr55);	// write something to the internal memory
  u8g2.drawStr(5,60,"After Changes Select Ok");	// write something to the internal memory
  //u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  }
  else
  {
        //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Password setting");	// write something to the internal memory
  u8g2.drawStr(5,35,"Password: ");	// write something to the internal memory

  u8g2.drawStr(70,35,"*");	// write something to the internal memory
  u8g2.drawStr(77,35,"*");	// write something to the internal memory
  u8g2.drawStr(84,35,"*");	// write something to the internal memory
  u8g2.drawStr(91,35,"*");	// write something to the internal memory
  u8g2.drawStr(98,35,"*");	// write something to the internal memory
  u8g2.drawStr(5,60,"After Changes Select Ok");	// write something to the internal memory
  //u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

  }

  delete[] char_ptr11;
  delete[] char_ptr22;
  delete[] char_ptr33;
  delete[] char_ptr44;
  delete[] char_ptr55; 
  delete[] char_ptr66;    
  
}


/*void Hocksetting_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Hook Setting");	// write something to the internal memory
  u8g2.drawStr(5,25,"User Name");	// write something to the internal memory
  u8g2.drawStr(5,37,"Pass: ");	// write something to the internal memory
  u8g2.drawStr(5,49,"File No");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
   
}*/


void Hocksetting_Scrn()
{

  String conec_cnt_str = String(conec_cnt);
  String conec_cnt_str2 = String(cl_cnt);
 
   String hks_cnt_str = String(ttl_hks);
// Convert String to C-style string
const char* conec_cnt_cstr = conec_cnt_str.c_str();
const char* conec_cnt_cstr2 = conec_cnt_str2.c_str();
const char* hks_cnt_cstr2 = hks_cnt_str.c_str();
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(12,12,"Hook Setting");	// write something to the internal memory
  u8g2.drawStr(5,30,"cl=");	// write something to the internal memory
  u8g2.drawStr(25,30,conec_cnt_cstr2);	// write something to the internal memory
  u8g2.drawStr(40,30,"cn=");	// write something to the internal memory
  //String(sensorValue)
  u8g2.drawStr(60,30,conec_cnt_cstr);	// write something to the internal memory
  u8g2.drawStr(75,30,"hks=");	// write something to the internal memory
  u8g2.drawStr(105,30,hks_cnt_cstr2);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

   //Serial.print("Data send to cpu  from EEPROM: ");
      String data = sddata.data21;
      // Write the data to the characteristic
     sprintf( result_cl_cnt, "%d", cl_cnt); 
      sprintf( result_conec_cnt, "%d", conec_cnt); 
     combinedString = data.c_str()+temp_str+result_cl_cnt+"&"+ result_conec_cnt;
      humidityCharacteristic->writeValue(combinedString.c_str(), combinedString.length());
     // humidityCharacteristic->writeValue(data.c_str(), data.length());
      Serial.println("Data sent: " + combinedString);
   
}

void Running_Scrn()
{
  
  char* char_ptr1;
  char* char_ptr2 ;
  char* char_ptr3;
  char* char_ptr4;
  char* char_ptr5 ;
  char* char_ptr6;
  char_ptr1= new char[2]; 
  char_ptr2= new char[2]; 
  char_ptr3= new char[2]; 
  char_ptr4= new char[2]; 
  char_ptr5= new char[2]; 
  char_ptr6= new char[2]; 
  char ascii_char1=decimal_number1;
  char ascii_char2=decimal_number2; 
  char ascii_char3=decimal_number3;
  char ascii_char4=decimal_number4;
  char ascii_char5=decimal_number5 ;
  char ascii_char6=decimal_number6;

  char_ptr1[0] = ascii_char1; // As
  char_ptr2[0] = ascii_char2; // As
  char_ptr3[0] = ascii_char3; // As
  char_ptr4[0] = ascii_char4; // As
  char_ptr5[0] = ascii_char5; // As
  char_ptr6[0] = ascii_char6; // As

  char_ptr1[1] = '\0'; // Null terminate the string
  char_ptr2[1] = '\0'; // Null terminate the string
  char_ptr3[1] = '\0'; // Null terminate the string
  char_ptr4[1] = '\0'; // Null terminate the string
  char_ptr5[1] = '\0'; // Null terminate the string
  char_ptr6[1] = '\0'; // Null terminate the string
  String hks_cnt_str = String(ttl_hks);
   const char* hks_cnt_cstr2 = hks_cnt_str.c_str();

   const char* RPM_String22 = separatedStrings[1].c_str();
 
   //Serial.println(" Running String 1: " );
  // Serial.println(bmpdata.data1);
   //Serial.println("Running String 2 : ");
   //Serial.println( bmpdata.data2);
   //Serial.println("Data sent: " + data);
  // Serial.println("Data sent: " + data);

  if(machine_lock_status==1)
  {

  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(19,10,"Morvel Jacquard");	// write something to the internal memory
  u8g2.drawStr(5,23,"F1:");	// write something to the internal memory
  u8g2.drawStr(55,23,"RPM:");	// write something to the internal memory

  u8g2.drawStr(85,23, RPM_String22);	// write something to the internal memory

  u8g2.drawStr(20,23,sddata.data21);	// write something to the internal memory

  u8g2.drawStr(5,37,bmpdata.data1);	// write something to the internal memory
  u8g2.drawStr(30,37,"/");	// write something to the internal memory
  u8g2.drawStr(40,37,bmpdata.data2);	// write something to the internal memory

  u8g2.drawStr(85,37,bmpdata.data3);	// write something to the internal memory

  u8g2.drawStr(5,50,"TL Hook:");	// write something to the internal memory
  u8g2.drawStr(55,50,hks_cnt_cstr2);	// write something to the internal memory

  if(tick_flag==1)
  {
    u8g2.drawStr(95,50,"P-OK");	// write something to the internal memory
  }

  

 //const char* char_ptr = " "; // Create a string with single_char and null terminator

  //char_ptr[0] = ascii_char; // As
  //char_ptr[1] = '\0'; // Null terminate the string
  u8g2.drawStr(5,61,"LM Name:");	// write something to the internal memory
  u8g2.drawStr(65,61,char_ptr1);	// write something to the internal memory
  u8g2.drawStr(75,61,char_ptr2);	// write something to the internal memory
  u8g2.drawStr(85,61,char_ptr3);	// write something to the internal memory
  u8g2.drawStr(95,61,char_ptr4);	// write something to the internal memory
  u8g2.drawStr(105,61,char_ptr5);	// write something to the internal memory

  delete[] char_ptr1; 
  delete[] char_ptr2; 
  delete[] char_ptr3; 
  delete[] char_ptr4; 
  delete[] char_ptr5; 
  delete[] char_ptr6; 

  u8g2.sendBuffer();					// transfer internal memory to the display

    
  }
   if(machine_lock_status==0)
  {

  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(19,10,"Morvel Jacquard");	// write something to the internal memory
  u8g2.drawStr(5,40,"Machine Locked Contact:");	// write something to the internal memory
  u8g2.drawStr(5,60,"Ph:9738798524");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  }
  
    if (modeCharacteristic != nullptr) 
    {
    // Your data to be sent
    String data = mddata.data5;
    // Write the data to the characteristic
    modeCharacteristic->writeValue(data.c_str(), data.length());
    //Serial.println("Data sent: " + data);
    }

  sub1='z';



 
   
}


void Connecting_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(19,10,"Morvel Jacquard");	// write something to the internal memory
  u8g2.drawStr(20,30,"Please wait");	// write something to the internal memory
  u8g2.drawStr(5,40,"Connecting to CPU......");	// write something to the internal memory
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  
   
}


void Connection_issue_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(23,10,"Morvel Jacquard");	// write something to the internal memory
  u8g2.drawStr(10,22,"Connection Failled");	// write something to the internal memory 
  u8g2.drawStr(10,35,"Sleleted Device Not Found");	// write something to the internal memory
  u8g2.drawStr(35,45,"Check CPU Power");	// write something to the internal memory
  u8g2.drawStr(15,58,"Restart The CPU");	// write something to the internal memory

  
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  //delay(10000);  
   
}

void Connected_Scrn()
{
  //u8g2.begin();
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont( u8g2_font_ncenR08_tf);	// choose a suitable font//u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(19,10,"Morvel Jacquard");	// write something to the internal memory
  u8g2.drawStr(5,40,"Connected To CPU");	// write something to the internal memory
  //u8g2.drawStr(5,58,"4.DELETE DESIGNS");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
   
}