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
  const [rpmValue, setrpmValue] = useState();
  const [pCount, setPCount] = useState();
  const [data,setData] = useState();
  const [lockedDate, setLockedDate] = useState<{ day: number | null, month: number | null, year: number | null }>({
    day: null,
    month: null,
    year: null,
  });
  const [height, setHeight] = useState('');
  const [width, setWidth] = useState('');
  const [cnCount, setCnCount] = useState('');
  const [cardCount, setCardCount] = useState('');
  const [ttlHook,setTtlHook] = useState('');
  const [designDir,setDesignDir] = useState('');
  const [lockStatus,setLockStatus] = useState('');
  const [custName, setCustName] = useState('');
  const [custPwd, setCustPwd] = useState('');
  const [webData, setWebData] = useState([]);
  const [webDataLocal, setWebDataLocal] = useState('');
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const BleManagerModule = NativeModules.BleManager;
  const BleManagerEmitter = new NativeEventEmitter(BleManagerModule);
  
  useEffect(() => {
    // Ensure re-render when language changes
    console.log('Current language:', i18n.language);
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

//   useEffect(() =>{
//     const requestLocationPermission = async () => {
//   try {
//     const granted = await PermissionsAndroid.request(
//       PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
//       {
//         title: "Location Permission",
//         message: "We need access to your location to scan for Wi-Fi networks",
//         buttonNegative: "Cancel",
//         buttonPositive: "OK",
//       }
//     );
//     if (granted === PermissionsAndroid.RESULTS.GRANTED) {
//       console.log("Location permission granted");
//     } else {
//       console.log("Location permission denied");
//     }
//   } catch (err) {
//     console.warn(err);
//   }
// };

// // Function to connect to Wi-Fi
// const connectToWifi = async () => {
//   await requestLocationPermission();

//   try {
//     // Enable Wi-Fi
//     await WifiManager.setEnabled(true);

//     // Connect to specific Wi-Fi network (replace with your Wi-Fi SSID and password)
//     await WifiManager.connectToProtectedSSID('your_network_ssid', 'your_network_password', false);
//     console.log('Connected to Wi-Fi');
//   } catch (error) {
//     console.error('Failed to connect to Wi-Fi:', error);
//   }
// };

// // Call the function to connect to Wi-Fi
// // connectToWifi();
//   });

  useEffect(() =>{
  const requestLocationPermission = async () => {
  try {
    const granted = await PermissionsAndroid.request(
      PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
      {
        title: "Location Permission",
        message: "We need access to your location to scan for Wi-Fi networks",
        buttonNegative: "Cancel",
        buttonPositive: "OK",
      }
    );
    if (granted === PermissionsAndroid.RESULTS.GRANTED) {
      console.log("Location permission granted");
    } else {
      console.log("Location permission denied");
    }
  } catch (err) {
    console.warn(err);
  }
};
  });

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
  
  const readAllCharDataFromEvent = (data: any)=>{
    const {service,characteristic,value} = data;
    if(service=== serviceid1 && characteristic === caracid1)
    {
        const caracidValue = bytesToString(value);
        if(caracidValue.startsWith('RPM.'))
        {
         setrpmValue(caracidValue);
         console.log('rpmValue',caracidValue); 
        }
        if (caracidValue.endsWith('.bmp')) 
        {
         setSdFiles(currentFiles => [...currentFiles, caracidValue]);
         console.log('SDCardData', caracidValue);
       }
    }
        if (service === serviceid1 && characteristic === caracid3) 
        {
            const caracid3Value = bytesToString(value);
            console.log("Raw byte array:", value); // Log the raw byte array for inspection
            console.log("Converted caracid3Value:", caracid3Value); // Log the result of bytesToString
            const dimensions = caracid3Value.split('.');
            if (dimensions.length === 2) 
            {
                const heightParsed = parseInt(dimensions[0], 10);
                const widthParsed = parseInt(dimensions[1], 10);
                if (!isNaN(heightParsed) && !isNaN(widthParsed))
                {
                    setHeight(heightParsed);  // height
                    setWidth(widthParsed);    // width
                } else {
                    console.error("Failed to parse height and width.");
                }
            } else {
                console.error("Invalid format: expected 'height.width'");
            }
                console.log('caracid3 height:', height);
                console.log('caracid3 width:', width);
        }
                if(service=== serviceid1 && characteristic===caracid4){
                    const caracid4Value = bytesToString(value);
                    const hight_int = parseInt(caracid4Value,10);
                    console.log('hight_var:', caracid4Value);
                    setPCount(hight_int);
                    console.log('hight_int:', hight_int);
                }
                                if(service=== serviceid2 && characteristic===caracid5){
                                const caracid5Value = bytesToString(value);
                                console.log('caracid5:', caracid5Value);
                                }
                                    if(service=== serviceid2 && characteristic===caracid6){
                                        const caracid6Value = bytesToString(value);
                                        console.log('caracid6:', caracid6Value);
                                        }  
                                            if(service=== serviceid2 && characteristic===caracid7){
                                                const caracid7Value = bytesToString(value);
                                                console.log('caracid7:', caracid7Value);
                                                }
                                                    if (service === serviceid2 && characteristic === caracid8) 
                                                    {
                                                        const caracid8Value = bytesToString(value);
                                                        console.log('caracid8:', caracid8Value);
                                                        if (caracid8Value.startsWith('CH/')) 
                                                        {
                                                            const PreviousFile = caracid8Value.substring(3).replace(/^\/+/, '');
                                                            console.log('caracid8:', PreviousFile);
                                                            setPrevFile(PreviousFile);
                                                        }
                                                        if (caracid8Value.startsWith('UN/')) 
                                                        {
                                                            const UserName = caracid8Value.substring(3);
                                                            console.log('caracid8:', UserName);
                                                            setCustName(UserName);
                                                        }
                                                        if (caracid8Value.startsWith('AA/')) 
                                                        {
                                                        const dimensions = caracid8Value.substring(3).split('A');
                                                            if (dimensions.length === 3) 
                                                            {
                                                                const day = parseInt(dimensions[0], 10); // Extract the day value
                                                                const month = parseInt(dimensions[1], 10); // Extract the month value
                                                                const year = parseInt(dimensions[2], 10); // Extract the year value
                                                        
                                                                // Store the values in the respective state variables
                                                                setLockedDate({day, month, year});
                                                        
                                                                // Optionally log the values to verify
                                                                console.log('Day:', day, 'Month:', month, 'Year:', year);
                                                            } else {
                                                                    console.log('Invalid format: Expected 3 components (day, month, year).');
                                                                    }
                                                        }
                                                        if (caracid8Value.startsWith('CTL/')) 
                                                        {
                                                            const dimensions = caracid8Value.trim().substring(4).split('.'); // Use substring(4) to remove 'CTL/'
                                                            console.log("After removing 'CTL/' and splitting by dot:", dimensions);
                                                            if (dimensions.length === 3) 
                                                            {
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
                                                        } else {
                                                        console.error("Input string does not start with 'CTL/'");
                                                        }
                                                    };
} // end of readAllCharDataFromEvent function

 
  // const handleGetConnectedDevices = () => {
  //   BleManager.getDiscoveredPeripherals([]).then((result: any) => {
  //     if (result.length === 0) {
  //       console.log('No Device Found');
  //       startScanning();
  //     } else {
  //       console.log('Results :', JSON.stringify(result));
  //       const allDevices = result.filter((item: any) => item.name !== null);
  //       setDevice(allDevices);
  //       console.log('test Result from Handleconnection', allDevices);
  //     }

  //     // Success code
  //     console.log('Discovered peripherals: ' + result);
  //   });
  // };
  
  
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

  // const handlePress = () => {
  //   if (currentDevice?.id === item?.id) {
  //     if (isConnected) {
  //       onDisconnect(item);
  //       setIsConnected(false); // Update the connection status to false
  //     } else {
  //       onConnect(item);
  //       setIsConnected(true); // Update the connection status to true
  //     }
  //   } else {
  //     onConnect(item);
  //     setIsConnected(true); // Automatically connect if it's not the current device
  //   }
  // };
 
  const renderItem = ({item}: any) => {
    return (
      <>
      {/* <View style={styles.container}> */}
      <ScrollView
  style={styles.scrollView} // Apply flex: 1 to the ScrollView itself
  contentContainerStyle={styles.container} // Apply your content layout style here
  refreshControl={
    <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
  }
>
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
        </ScrollView>
        {/* </View> */}
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
      //  navigation.navigate('Home');
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

        // const newServiceUUIDs = services.map(service => service.uuid);
        // const newCharacteristicUUIDs = characteristics.map(characteristic => characteristic.uuid);
  
        // // Update state with new UUIDs
        // setServiceUUIDs(newServiceUUIDs);
        // setCharacteristicUUIDs(newCharacteristicUUIDs);

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
};

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
    const fname = filename;
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

const writeUserNameToDevice = async (username) => {
  if (isConnected) {
    const rootDir = 'UN/';
    const uname = username;
    const fullName = rootDir + uname;
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

// const deleteFile = async (filename) => {
//   if (isConnected) {
//     const rootDir = 'DL/';
//     const fname = filename;
//     const fullName = rootDir + fname;
//     console.log('Fullfilename with path', fullName);
//     const testRun = stringToBytes(fullName);
//     await BleManager.write(deviceId, serviceid1, caracid2, testRun)
//       .then(() => {
//         const results = bytesToString(testRun);
//         console.log('Function call command sent File', results);
//         ToastAndroid.show("File Deleted Successfully!", ToastAndroid.SHORT);
//       })
//       .catch(error => {
//         console.error('Error sending function call command:', error);
//       });
//   }
// };
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

const setLockDate = async (dval,mval,yval) => {
  if (isConnected) {
    const rootDir = 'AA/';
    const temp_str = 'A';
    const dvalue = dval;
    const mvalue = mval;
    const yvalue = yval;
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

// Fetch data on initial render
  
useEffect(() => {
  const fetchData = async () => {
    try {
      console.log('Fetching data...');
      const response = await axios.get('http://redsap.org/api.php'); // API call
      console.log('Fetched data:', response.data);  // Log the fetched data to check its structure
      
      if (!response.data) {
        throw new Error('No data received');
      }

      setWebData(response.data);  // Update context with fetched data
      setWebDataLocal(response.data);  // Local state update

    } catch (err) {
      console.error('Error occurred:', err);  // Log error for debugging
      setError(err.message);
      setTimeout(() => {
        Alert.alert('Error', `No Internet Connection Something went wrong: ${err.message}`);  // Display error alert
      }, 100); // Delay of 100ms
    } finally {
      setLoading(false);
    }
  };

  fetchData();
}, [setWebData]); // Dependency on setWebData
// While loading, show an activity indicator
if (loading) {
  return (
    <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
      <ActivityIndicator size="large" color="#0000ff" />
    </View>
  );
}
// If there is an error, display the error message without disrupting the UI
// if (error) {
//   return (
//     <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
//       <Text style={{ color: 'red', fontSize: 18 }}>Error: {error}</Text>
//       {/* You can show a fallback UI here */}
//     </View>
//   );
// }
 // Find the user with id: 3
//  const user = webData.find(item => item.id === 3);  // Filter data to find user with id: 3

 // If user with id: 3 exists, display their password, else display an error message
//  const userPassword = user ? user.pwd : 'User not found';
  return (
    // screenView(),
    <>
    <MyContext.Provider
      value={{
        ReadHeightwidth,
        writeHeightToChange,
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
        rpmValue,
        pCount,
        setPCount,  
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
        strFiles,
        data,
        setData,
        height,
        setHeight,
        width,
        setWidth,
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
    writeUserNameToDevice,
    custName,
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
