// MyContext.tsx
import React, {
  createContext,
  ReactNode,
  useContext,
  useState,
  useEffect,
  useCallback,
} from 'react';
import BleManager from 'react-native-ble-manager';
import {Buffer} from 'buffer';
import AsyncStorage from '@react-native-async-storage/async-storage';

import {
  View,
  ScrollView,
  RefreshControl,
  Text,
  StyleSheet,
  PermissionsAndroid,
  NativeEventEmitter,
  NativeModules,
  TouchableOpacity,
  ToastAndroid,
  FlatList, 
  ActivityIndicator,
  Alert,
} from 'react-native';
import axios from 'axios';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";
interface MyContextType {
  isScanning: boolean;
  setIsScanning: (value: boolean) => void;
  isConnected: boolean;
  setIsConnected: (value: boolean) => void;
  bleDevice: string;
  setDevice: (value: string) => void;
  currentDevices: string;
  setCurrentDevices: (value: null) => void;
  strRpm: string;
  setStrRpm: (value: null) => void;
  strFiles: string;
  setStrFiles: (value: null) => void;
}

const MyContext = createContext<MyContextType | undefined>(undefined);

export const MyContextProvider: React.FC<{children: ReactNode}> = ({
  children,
}) => {
  const { t, i18n } = useTranslation();
  
  const [strRpm, setStrRpm] = useState(0);
  const [strFiles, setStrFiles] = useState();
  const [imageData, setImageData] = useState();
  let serviceid1 ="4fafc201-1fb5-459e-8fcc-c5c9c331914b";
  let caracid1 = "beb5483e-36e1-4685-b7f5-ea07361b26a8";
  let caracid2 = "beb5483e-36e1-4686-b7f5-ea07361b26a8";
  let caracid3 = "beb5483e-36e1-4687-b7f5-ea07361b26a8";
  let caracid4 = "beb5483e-36e1-4688-b7f5-ea07361b26a8";
  let serviceid2 = "4fafc202-1fb5-459e-8fcc-c5c9c331914b";
  let caracid7 = "beb5483e-36e2-4670-b7f5-ea07361b26a8";
  let caracid8 = "beb5483e-36e2-4671-b7f5-ea07361b26a8";
  let caracid6 = "beb5483e-36e2-4680-b7f5-ea07361b26a8"; 
  let caracid5 = "beb5483e-36e1-4689-b7f5-ea07361b26a8";
  const [isScanning, setIsScanning] = useState<boolean>(false);
  const [isConnected, setIsConnected] = useState<boolean>(false);
  const [bleDevice, setDevice] = useState([]);
  const [bluetoothDevices, setBluetoothDevices] = useState([]);
  const [currentDevice, setCurrentDevice] = useState<any>(null);
  const [deviceId, setDeviceId] = useState(null);
  const [sdFiles, setSdFiles] = useState([]);
  const [prevFile,setPrevFile] = useState();
  const [nextFile, setNextFile] = useState();
  const [rpmValue, setrpmValue] = useState();
  const [pCount, setPCount] = useState<number | undefined>(undefined);  // or just use `useState<number>(0)` if you want an initial value
  const [pCount1, setPCount1] = useState<number | undefined>(undefined);
  // const [pCount, setPCount] = useState();
  // const [pCount1, setPCount1] = useState();
  const [data,setData] = useState();
  const [lockedDate, setLockedDate] = useState<{ day: number | null, month: number | null, year: number | null }>({
    day: null,
    month: null,
    year: null,
  });

  const [f1height, setF1height] = useState<number | undefined>(undefined);
  const [f1width, setF1width] = useState<number | undefined>(undefined);
  const [f2height, setF2height] = useState<number | undefined>(undefined);
  const [f2width, setF2width] = useState<number | undefined>(undefined);
  const [cnCount, setCnCount] = useState('');
  const [cardCount, setCardCount] = useState('');
  const [ttlHook, setTtlHook] = useState('');
  const [designDir, setDesignDir] = useState('');
  const [lockStatus, setLockStatus] = useState('');
  const [custName, setCustName] = useState('');
  const [custPwd, setCustPwd] = useState('');
  const [webData, setWebData] = useState<Array<{ usr_id: string, usr_name: string, usr_pwd: string }>>([]);
  const [currLang, setCurrLang] = useState<string | null>('en');
  const [webDataLocal, setWebDataLocal] = useState('');
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [localNamed, setLocalNamed] = useState<string | null>(null);
  const [isDataInAsyncStorage, setIsDataInAsyncStorage] = useState(false);
  
  const BleManagerModule = NativeModules.BleManager;
  const BleManagerEmitter = new NativeEventEmitter(BleManagerModule);
  
  useEffect(() => {
    // Ensure re-render when language changes
    console.log('Current language:', i18n.language);
    console.log('changedLanguage',currLang);
    // saveLanguageToAsyncStorage();
  }, [i18n.language]);
  

  useEffect(() => {
    BleManager.start({showAlert: false}).then(() => {
      // Success code
      console.log('BLEManager initialized');
     
    });
  },[]);
  useEffect(() => {
    BleManager.enableBluetooth()
      .then(() => {
        console.log('The Bluetooth is already enabled or the user conformed');
        requestPermission();
      })
      .catch(() => {
        console.log('The user refused to enable bluetooth.!');
      });
  }, []);


  useEffect(() => {
    let stopListener = BleManagerEmitter.addListener(
      'BleManagerStopScan',
      () => {
        setIsScanning(false);
        handleGetConnectedDevices();
        console.log('Stop');
      },
    );
    
    let disconnected = BleManagerEmitter.addListener(
      'BleManagerDisconnectPeripheral',
      peripheral => {
        console.log('disconnected Device 177', peripheral);
        setIsConnected(false);
      },
    );
    let characteristicValueupdate = BleManagerEmitter.addListener(
      'BleManagerDidUpdateValueForCharacteristic',
      data => {
        console.log('Event BleManagerDidUpdateValueForCharacteristic', data);
        setData(data);
        readAllCharDataFromEvent(data);
      },
    );
    let BleManagerDidUpdateState = BleManagerEmitter.addListener(
      'BleManagerDidUpdateState',
      data => {
        console.log('Event BleManagerDidUpdateState', data);
      },
    );
    return () => {
      stopListener.remove();
      disconnected.remove();
      characteristicValueupdate.remove();
      BleManagerDidUpdateState.remove();
    };
  }, [bluetoothDevices]);


  const requestPermission = async () => {
    const granted = await PermissionsAndroid.requestMultiple([
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
      PermissionsAndroid.PERMISSIONS.BLUETOOTH_ADVERTISE,
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION,

    ]);
    if (granted) {
      startScanning();
    }
  };
  const startScanning = () => {
    if (!isScanning) {
      setIsScanning(true);
      setDevice([]);
      BleManager.scan([], 5, false)
        .then(() => {
          // Success code
          console.log('Scan started');
          // setIsScanning(true);
        })
        .catch((error) => {
          console.error('Error starting scan:', error);
          setIsScanning(false);
        });
    }
  };
  
  useEffect(() => {
    console.log('Machine Lock Status:', lockStatus);
  }, [lockStatus]);


  const readAllCharDataFromEvent = (data: any) => {
    //start of readAllCharDataFromEvent
    const {service, characteristic, value} = data;
    if (service === serviceid1 && characteristic === caracid1) {
      const caracidValue = bytesToString(value);
      if (caracidValue.startsWith('RPM.')) {
        const rpmParts = caracidValue.split('.'); // Splits "RPM.0" into ["RPM", "0"]
        const rpmNumber = rpmParts[1]; // Access the second part (i.e., the "0" part)
        console.log('RPM Number:', rpmNumber);
        setrpmValue(rpmNumber);
        console.log('rpmValue', caracidValue);
      }
      if (caracidValue.endsWith('.bmp')) {
        setSdFiles(currentFiles => {
          // Check if the file already exists in sdFiles before adding it
          if (!currentFiles.includes(caracidValue)) {
            return [...currentFiles, caracidValue]; // Only add if not already present
          }
          return currentFiles; // Return the existing list if the file is a duplicate
        });
        console.log('SDCardData', caracidValue);
      }
      if (caracidValue.startsWith('LS/')) {
        const lsnotify = caracidValue.substring(3).replace(/^\/+/, '');
        console.log('caracid Lock Status:', lsnotify);
        setLockStatus(lsnotify);
        console.log('Machine Lock Status', lockStatus);
      }
    } // end of Caracid1
  
    if (service === serviceid1 && characteristic === caracid3) {
      // Convert byte array to string
      const caracid3Value = bytesToString(value);
      console.log('Raw byte array:', value); // Log the raw byte array for inspection
      console.log('Converted caracid3Value:', caracid3Value); // Log the result of bytesToString
  
      // Split the value by dot (.) to get all the height and width values
      const dimensions = caracid3Value.split('.');
  
      // Ensure we have exactly 4 values (height1, width1, height2, width2)
      if (dimensions.length === 4) {
        // Parse f1height and f1width
        const heightParsedF1 = parseInt(dimensions[0], 10);
        const widthParsedF1 = parseInt(dimensions[1], 10);
        if (!isNaN(heightParsedF1) && !isNaN(widthParsedF1)) {
          setF1height(heightParsedF1); // Set f1 height
          setF1width(widthParsedF1); // Set f1 width
        } else {
          console.error('Failed to parse height and width for f1.');
        }
  
        // Parse f2height and f2width
        const heightParsedF2 = parseInt(dimensions[2], 10);
        const widthParsedF2 = parseInt(dimensions[3], 10);
        if (!isNaN(heightParsedF2) && !isNaN(widthParsedF2)) {
          setF2height(heightParsedF2); // Set f2 height
          setF2width(widthParsedF2); // Set f2 width
        } else {
          console.error('Failed to parse height and width for f2.');
        }
      } else {
        console.error("Invalid format: expected 'height1.width1.height2.width2'");
      }
    } // end of caracid3

    if (service === serviceid1 && characteristic === caracid4) {
      const caracid4Value = bytesToString(value);
    
      // Split the value by dot (.) to get all the height and width values
      const dimensions = caracid4Value.split('.');
    
      // Ensure we have exactly 2 values (pcount, pcount1)
      if (dimensions.length === 2) {
        // Parse pic1 and pic2
        const piccount1 = parseInt(dimensions[0], 10);
        const piccount2 = dimensions[1] === "" ? 0 : parseInt(dimensions[1], 10); // Handle empty string for piccount2
    
        if (!isNaN(piccount1) && !isNaN(piccount2)) {
          setPCount(piccount1); // Set pic1
          setPCount1(piccount2); // Set pic2
        } else {
          console.error('Failed to parse height and width for f1.');
        }
    
        // Ensure you log the updated values
        console.log('pcount:', piccount1);
        console.log('pcount1:', piccount2);
      }
    }    // end of caracid4
    if (service === serviceid2 && characteristic === caracid5) {
      const caracid5Value = bytesToString(value);
      console.log('caracid5:', caracid5Value);
    } // end of caracid5
    if (service === serviceid2 && characteristic === caracid6) {
      const caracid6Value = bytesToString(value);
      console.log('caracid6:', caracid6Value);
    } //end of caracid6
    if (service === serviceid2 && characteristic === caracid7) {
      const caracid7Value = bytesToString(value);
      console.log('caracid7:', caracid7Value);
    } // end of caracid7
    
    if (service === serviceid2 && characteristic === caracid8) {
      const caracid8Value = bytesToString(value);
      console.log('caracid8 Data:', caracid8Value);
      
      if (caracid8Value.startsWith('CH/')) {
        const PreviousFile = caracid8Value.substring(3).replace(/^\/+/, ''); // Remove leading slashes
        console.log('caracid8 prevFile:', PreviousFile);
    
        // Use `let` to allow reassignment
        let cleanedFile = PreviousFile.replace(/\//g, '.'); // Replace slashes with dots
        cleanedFile = cleanedFile.replace(/^\.+/, ''); // Remove any leading dots
        cleanedFile = cleanedFile.replace(/\.+$/, ''); // Remove any trailing dots
    
        console.log('Cleaned File:', cleanedFile);
    
        // Remove any consecutive dots (..)
        cleanedFile = cleanedFile.replace(/\.\./g, '.');
    
        // Split the string based on the dot separator
        const fileParts = cleanedFile.split('.');
    
        // Check if there are the expected parts for the filenames
        if (fileParts.length >= 2) {
            // Handle the first file (33f.bmp)
            const firstFile = fileParts[0] + '.' + fileParts[1]; // e.g., 33f.bmp
            
            // Handle the second file (brd.bmp), if it exists
            const secondFile = fileParts.slice(2).join('.'); // Join remaining parts into the second file
    
            console.log('First File:', firstFile);
            console.log('Second File:', secondFile);
            const secfile = secondFile+"p";
    
            // Set the files as needed
            setPrevFile(firstFile); // Set first filename to state variable
            setNextFile(secfile); // Set second filename to state variable
        } else {
            console.log('Filename pattern is not as expected.');
        }
    }
      if (caracid8Value.startsWith('AA/')) {
        const dimensions = caracid8Value.substring(3).split('A');
        if (dimensions.length === 3) {
          const day = parseInt(dimensions[0], 10); // Extract the day value
          const month = parseInt(dimensions[1], 10); // Extract the month value
          const year = parseInt(dimensions[2], 10); // Extract the year value
          // Store the values in the respective state variables
          setLockedDate({day, month, year});
  
          // Optionally log the values to verify
          console.log('Day:', day, 'Month:', month, 'Year:', year);
        } else {
          console.log(
            'Invalid format: Expected 3 components (day, month, year).',
          );
        }
      }
      if (caracid8Value.trim().startsWith('CTL/')) {
        const dimensions = caracid8Value.trim().substring(4).split('.'); // Use substring(4) to remove 'CTL/'
        console.log("After removing 'CTL/' and splitting by dot:", dimensions);
        if (dimensions.length === 3) {
          const cardCount = parseInt(dimensions[0], 10); // card count
          const cnCount = parseInt(dimensions[1], 10); // connector count
          const ttlHook = parseInt(dimensions[2], 10); // total hooks
          console.log('Card Count:', cardCount);
          console.log('Connector Count:', cnCount);
          console.log('Total Hooks:', ttlHook);
          setCardCount(cardCount);
          setCnCount(cnCount);
          setTtlHook(ttlHook);
        } else {
          console.error(
            "Invalid format: expected 'CARD.CONNECTOR.THOOK', but got",
            dimensions,
          );
        }
      }
    } // end of caracid8
  }; //end of readAllCharDataFromEvent
  
  
  //filter only ble devices start with marveljacquard
  const handleGetConnectedDevices = () => {
    BleManager.getDiscoveredPeripherals([]).then((result: any) => {
      if (result.length === 0) {
        console.log('No Device Found');
        startScanning();
      } else {
        console.log('Results :', JSON.stringify(result));
  //       const filteredDevices = result.filter((item: any) => item.name && item.name.startsWith('Mj'));
  const filteredDevices = result.filter((item: any) => item.name && (item.name.startsWith('Mj') || item.name.startsWith('Marvel')));
        setDevice(filteredDevices);
        console.log('Filtered Devices from HandleConnection', filteredDevices);
        filteredDevices.forEach(bleDevice => {
          console.log('Local Name of the Device:', bleDevice.advertising?.localName);
          setLocalNamed(bleDevice.advertising?.localName)
           // Only call fetchData if there is no data in AsyncStorage (i.e., if isDataInAsyncStorage is false)
        if (!isDataInAsyncStorage) {
          fetchData(bleDevice.advertising?.localName);  // Fetch data only if AsyncStorage is empty
        }
          
      });
      }
   
      // Success code
      console.log('Discovered peripherals: ' + result);
    });
  };
   

  useEffect(() => {
    // Show alert whenever isConnected changes
    if (isConnected) {
      // Alert.alert(i18next.t('Connected'), `${bleDevice.name} ${i18next.t('is now connected')}`);
      ToastAndroid.show("Device Connected Succesfully!", ToastAndroid.SHORT);
    } else {
      // Alert.alert(i18next.t('Disconnected'), `${bleDevice.name} ${i18next.t('is now disconnected')}`);
      ToastAndroid.show("Device is Disconnected!", ToastAndroid.SHORT);
    }
  }, [isConnected]); // This will run every time isConnected changes

   
  const renderItem = ({item}: any) => {
    return (
      <>
      <View style={styles.container}>
     
<View style={styles.bleCard}>
          <Text style={styles.txt}>{item.name}</Text>
          {/* <Text style={styles.txt}>{isConnected}</Text> */}
          <TouchableOpacity
            style={styles.btn}
            onPress={() => {
              {
                currentDevice?.id === item?.id
                  ? (isConnected ? onDisconnect(item) : onConnect(item))
                  : onConnect(item)
              }
            }}>
            <Text style={styles.btntxt}>
  {currentDevice?.id === item?.id
    ? (isConnected ? i18next.t('Disconnect') : i18next.t('Connect')) 
    : i18next.t('Connect')} 
</Text>
          </TouchableOpacity>
        </View>
        
        </View>
      </>
    );
  };

  
  const onConnect = async (item: any) => {
    try {
      await BleManager.connect(item.id);
      setCurrentDevice(item);
      setDeviceId(item.id);
      setIsConnected(true);
      const result = await BleManager.retrieveServices(item.id);
      console.log('DeviceId is:..', item.id);
      await discoverServices(item.id);
      console.log('Successfully retrieved services for', item.id);
      console.log('result of services ', result);

      // Fetch the local name from the result variable
    const devicenameis = result.advertising.localName;
    if (devicenameis) {
      console.log('Device Local Name: ', devicenameis);
      // setLocalNamed(devicenameis); // Set the local name in your state variable
      // fetchData(devicenameis);
    } else {
      console.log('Local Name not found');
    }

    } catch (error) {
      console.log('onConnect Error..:', error);
    }
  };
  
  // disconnect from device
  const onDisconnect = async (item: any) => {
    BleManager.disconnect(currentDevice?.id)
      .then(() => {
        setCurrentDevice(null);
        setIsConnected(false);
        clearInterval(item.id);
        console.log('Disconnected from device', item.id);
        // navigation.navigate('ScanningScreen');
      })
      .catch(error => {
        // Failure code
        console.log('Error disconnecting:', error);
      });
  };

  const bytesToString = (bytes: any) => {
    return String.fromCharCode(...bytes);
  };
  // Convert a string to a byte array
const stringToBytes = (str) => {
  // Create a buffer from the string
  const buffer = Buffer.from(str, 'utf8');
  // Convert buffer to an array of numbers (bytes)
  return Array.from(buffer);
};

  // Helper function to convert byte array to string
  const byteArrayToString = byteArray => {
    return String.fromCharCode.apply(null, byteArray);
  };
  // convert intToByteArray 
  function intToByteArray(value) {
    let byteArray = new Uint8Array(4); // Assuming a 4-byte integer
    let dataView = new DataView(byteArray.buffer);
    dataView.setUint32(0, value, true); // true for little-endian
    return byteArray;
  }

  const discoverServices = async (deviceId) => {
    try {
        const peripheralInfo = await BleManager.retrieveServices(deviceId);
        console.log('Peripheral Info:', peripheralInfo);

        const services = peripheralInfo.services;
        const characteristics = peripheralInfo.characteristics;
        services.forEach((service) => {
            const serviceUUID = service.uuid;
            onChangeCharacteristics(serviceUUID, characteristics, deviceId);
        });
    } catch (error) {
        console.error('Failed to retrieve services:', error);
    }
};

const onChangeCharacteristics = (serviceUUID, result, deviceId) => {
    const service1Characteristics = [caracid1, caracid2, caracid3, caracid4, caracid6];
    const service2Characteristics = [ caracid7, caracid8];

    result.forEach((characteristic) => {
        const characteristicUUID = characteristic.characteristic;

        if (serviceUUID === serviceid1 && service1Characteristics.includes(characteristicUUID)) {
            BleManager.startNotification(deviceId, serviceUUID, characteristicUUID)
                .then(() => {
                    console.log(`Notification started for ${serviceUUID} - ${characteristicUUID}`);
                })
                .catch(error => {
                    console.error(`Failed to start notification for ${characteristicUUID}:`, error);
                });
        } else if (serviceUUID === serviceid2 && service2Characteristics.includes(characteristicUUID)) {
            BleManager.startNotification(deviceId, serviceUUID, characteristicUUID)
                .then(() => {
                    console.log(`Notification started for ${serviceUUID} - ${characteristicUUID}`);
                })
                .catch(error => {
                    console.error(`Failed to start notification for ${characteristicUUID}:`, error);
                });
        }
    });
};

const [isRefreshing, setIsRefreshing] = useState(false);

  // Function to handle the refresh
  const onRefresh = useCallback(() => {
    setIsRefreshing(true);
    startScanning();
    // Simulating an API call or refresh operation
    setTimeout(() => {
      setIsRefreshing(false); // Stop refreshing after 2 seconds
    }, 5000);
  }, []);


const ReadHeightwidth = async Dimensions => {
  if(isConnected){
    BleManager.read(deviceId, serviceid1, caracid3)
    .then(heightwidth => {
      const strdata = bytesToString(heightwidth);
      if(strdata.includes('locked')){
          console.log('reading LockStatus inside', strdata);
          // setLockStatus(strdata);
      }
      console.log('reading Height Width', strdata);
    })
    .catch(error => {
      console.log(error);
    });
  }
}

const writeHeightToChange = async (picNum) => {
  if (isConnected) {
    const rootDir = '*UP/';
    const myCount = picNum;
    const picCount = rootDir + myCount;
    console.log("converted pcount value",picCount);
    const testRun = stringToBytes(picCount);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent PicCount', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
}; // end of single pic change
// start of double pic change
const writeTwoHeightToChange = async (picNum1, picNum2) => {
  if (isConnected) {
    const rootDir = '*UP/';
    const myCount1 = picNum1;
    const myCount2 = picNum2;

    const picCount = rootDir + myCount1+ "/" + myCount2;
    console.log("converted pcount value",picCount);
    const testRun = stringToBytes(picCount);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent PicCount', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};
// end of double pic change

const writeData = async (name) => {
  if (isConnected) {
    // const str = "CALL_FUNCTION";
    const testRun = stringToBytes(name);
    await BleManager.write(deviceId, serviceid2, caracid7, testRun)
    .then(() => {
      const results = bytesToString(testRun);
      console.log('Function call command sent',results);
      })
      .catch((error) => {
        console.error('Error sending function call command:', error);
      });
  }
};
const writeFileToSelect = async (filename) => {
  if (isConnected) {
    const rootDir = 'CH/';
    const fname = filename.replace(/\.[^/.]+$/, '');
    const fullName = rootDir + fname;
    console.log('Fullfilename with path', fullName);
    const testRun = stringToBytes(fullName);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};

const writeDoubleFileToSelect = async (bodyFile, borderFile) => {
  if (isConnected) {
    const rootDir = 'CH/';
    const f1 = bodyFile.replace(/\.[^/.]+$/, '');
    const f2 = borderFile.replace(/\.[^/.]+$/, '');
    // const f1 = bodyFile.replace(/\.[^/.]+$/, '');
    // const f2 = borderFile.replace(/\.[^/.]+$/, '');
    const fullName = rootDir + f1+"/"+f2;
    console.log('Fullfilename with path', fullName);
    const testRun = stringToBytes(fullName);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};

const deleteFile = async (filename) => {
  if (isConnected) {
    const rootDir = 'DL/';
    const nameWithoutExtension = filename.replace(/\.bmp$/, "");
    console.log("without extension",nameWithoutExtension);
    const fname = filename;
    const fullName = rootDir + fname;
    console.log('Fullfilename with path', fullName);
    const testRun = stringToBytes(fullName);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
        ToastAndroid.show("File Deleted Successfully!", ToastAndroid.SHORT);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};


const writeClcnCount = async (countvalue) => {
  if (isConnected) {
    const testRun = stringToBytes(countvalue);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};
const leftRightSelect = async (lrval) => {
  if (isConnected) {
    const rootDir = 'LR/';
    const lrvalue = lrval;
    const full_lrval = rootDir + lrvalue;
    console.log('Fullfilename with path', full_lrval);
    const testRun = stringToBytes(full_lrval);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};

const setLockDate = async (dval, mval, yval) => {
  if (isConnected) {
    const rootDir = 'AA/';
    const temp_str = 'A';
    console.log(dval);
    // Trim any unwanted spaces
    const dvalue = dval.trim();  // Trimming spaces
    const mvalue = mval.trim();  // Trimming spaces
    const yvalue = yval.trim();  // Trimming spaces

    // Concatenate the date values correctly
    const full_dtval = rootDir + dvalue + temp_str + mvalue + temp_str + yvalue;

    console.log('Full Date Value with path', full_dtval);
    const testRun = stringToBytes(full_dtval);
    await BleManager.write(deviceId, serviceid1, caracid2, testRun)
      .then(() => {
        const results = bytesToString(testRun);
        console.log('Function call command sent File', results);
      })
      .catch(error => {
        console.error('Error sending function call command:', error);
      });
  }
};

const unLockMachine = async () => {
  if (isConnected) {
    // const str = "CALL_FUNCTION";
    const unlockme = stringToBytes("MU/1");
    await BleManager.write(deviceId, serviceid1, caracid2, unlockme)
    .then(() => {
      const results = bytesToString(unlockme);
      console.log('Function call command sent',results);
      setLockStatus(results);
      })
      .catch((error) => {
        console.error('Error sending function call command:', error);
      });
  }
};

useEffect(() => {
  const checkAsyncStorage = async () => {
    const cachedData = await AsyncStorage.getItem('localName'); // Replace with your key
    if (cachedData) {
      setIsDataInAsyncStorage(true);  // Data found in AsyncStorage
      const parsedData = JSON.parse(cachedData);
      setWebData(parsedData);
      setWebDataLocal(parsedData);
      console.log('user Id,{userData[0].usr_id}');
    } else {
      setIsDataInAsyncStorage(false); // No data in AsyncStorage
    }
  };

  checkAsyncStorage();
}, []);

  
  const fetchData = async (localName: string) => {
    const source = axios.CancelToken.source();
    try {
      console.log('Fetching data for localName:', localName);
      setLoading(true);
  
      // Check if data is present in AsyncStorage first
      const cachedData = await AsyncStorage.getItem(localName);
      if (cachedData) {
        // If data exists in AsyncStorage, use it and avoid fetching
        console.log('Using cached data:', JSON.parse(cachedData));
        const parsedData = JSON.parse(cachedData);
        setWebData(parsedData);  // Set context with cached data
        setWebDataLocal(parsedData);
        setIsDataInAsyncStorage(true);  // Data exists in AsyncStorage
        setLoading(false);  // Stop loading
        return;  // Exit the function early
      }
  
      // Set a timeout to limit the wait time for the API call
      const timeoutId = setTimeout(() => {
        source.cancel('Request timed out'); // Cancel the request after the timeout
      }, 5000); // Timeout after 5 seconds (5000 ms)
  
      // If no cached data, proceed with API request
      const response = await axios.get('http://redsap.org/apis.php', {
        params: { localName },
        cancelToken: source.token,
      });
  
      clearTimeout(timeoutId);
      console.log('Fetched data:', response.data);
  
      // If fetched data is valid, update context and store it in AsyncStorage
      if (response.data) {
        setWebData(response.data);  // Update context with fetched data
        setWebDataLocal(response.data);
        
        // Store the fetched data in AsyncStorage for future use
        await AsyncStorage.setItem(localName, JSON.stringify(response.data));
        setIsDataInAsyncStorage(true);  // Mark that data is now in AsyncStorage
      } else {
        throw new Error('No data received');
      }
  
    } catch (err) {
      if (axios.isCancel(err)) {
        console.log('Request cancelled due to timeout');
      } else {
        console.error('Error occurred:', err);
        setError(err.message);
        setTimeout(() => {
          Alert.alert('Error', `Something went wrong: ${err.message}`);
        }, 100);
      }
    } finally {
      setLoading(false);
    }
  };
  


// While loading, show an activity indicator
// UseEffect to log `webData` after it has been updated
useEffect(() => {
  if (webData && webData.usr_name) {
    console.log('Stored in useState WebData:', webData.usr_name);
  }
}, [webData]);  // This effect runs whenever `webData` changes

if (loading) {
  return (
    <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
      <ActivityIndicator size="large" color="#0000ff" />
    </View>
  );
}


  
  return (
    // screenView(),
    <>
    <MyContext.Provider
      value={{
        ReadHeightwidth,
        writeHeightToChange,
        writeTwoHeightToChange,
        stringToBytes,
        bleDevice,
        isScanning,
        setIsScanning,
        isConnected,
        setIsConnected,
        currentDevice,
        setCurrentDevice,
        sdFiles,
        setSdFiles,
        prevFile,
        setPrevFile,
        nextFile,
        setNextFile,
        rpmValue,
        pCount,
        setPCount,
        pCount1, 
        setPCount1,
        startScanning,
        onConnect,
        onDisconnect,
        requestPermission,
        renderItem,
        handleGetConnectedDevices,
        onChangeCharacteristics,
        writeData,
        strRpm,
        setStrRpm,
        writeFileToSelect,
        writeDoubleFileToSelect,
        strFiles,
        data,
        setData,
        f1height,
        setF1height,
        f1width,
        setF1width,
        f2height,
        setF2height,
        f2width,
        setF2width,
         webData,
         setWebData,
         webDataLocal,
         setWebDataLocal,
        imageData,
        unLockMachine,
        lockStatus,
        setLockStatus,
        cnCount,
    setCnCount,
    cardCount,
    setCardCount,
    ttlHook,
    setTtlHook,
    writeClcnCount,
    deleteFile,
    designDir,
    setDesignDir,
    leftRightSelect,
    setLockDate,
    lockedDate, 
    setLockedDate,
    custName,
    localNamed,
    setCustName,
    custPwd,
    setCustPwd,
      }}>
      {children}
    </MyContext.Provider>
     <View >
         
        <FlatList
          data={webData} // Use webData from context
          keyExtractor={(item) => item.usr_id.toString()} // Correct keyExtractor based on data structure
          renderItem={() => null}  // Don't render any item (return null)
          
        />
      </View> 

    </>
  );
};

export const useMyContext = () => {
  const context = useContext(MyContext);
  if (context === undefined) {
    throw new Error('useMyContext must be used within a MyContextProvider');
  }
  return context;
};

const styles = StyleSheet.create({
  scrollView: {
    flex: 1, 
  },
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#EFDBFE',
  },
 
  bleCard: {
    width: '90%',
    padding: 10,
    alignSelf: 'center',
    marginVertical: 10,
    backgroundColor: '#812892',
    elevation: 5,
    borderRadius: 5,
    flexDirection: 'row',
    justifyContent: 'space-between',
  },
  txt: {
    fontFamily: 'Raleway',
    fontStyle: 'normal',
    fontWeight: '900',
    color: '#FFFFFF',
    alignContent: 'center',
    textAlignVertical: 'center',
  },
  btntxt: {
    fontFamily: 'Raleway',
    fontStyle: 'normal',
    fontWeight: '900',
    color: '#812892',
  },
  btn: {
    width: 100,
    height: 40,
    alignItems: 'center',
    justifyContent: 'center',
    borderRadius: 5,
    backgroundColor: '#EFDBFE',
  },
});
