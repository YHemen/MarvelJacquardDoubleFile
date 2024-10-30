// MyContext.tsx
import React, {
    createContext,
    ReactNode,
    useContext,
    useState,
    useEffect,
  } from 'react';
  import BleManager from 'react-native-ble-manager';
  import WifiManager from 'react-native-wifi-reborn';
  
  
  // import { bytesToString,stringToBytes } from "convert-string";
  // import {bytesToString} from 'utils';
  // import { useNavigation } from '@react-navigation/native';
  import {Buffer} from 'buffer';
  import base64 from 'react-native-base64';
  import {
    
    View,
    Text,
    Image,
    setError,
    TextInput,
    Alert,
    StyleSheet,
    PermissionsAndroid,
    NativeEventEmitter,
    NativeModules,
    FlatList,
    TouchableOpacity,
    Button,
    Dimensions,
  } from 'react-native';
  
  // const BleManagerEmitter = new NativeEventEmitter(NativeModules.BleManager);
  
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
    // const navigation = useNavigation();
    const [strRpm, setStrRpm] = useState(0);
    const [strFiles, setStrFiles] = useState();
    const [imageData, setImageData] = useState();
  
    //const [deviceid, setDeviceId] = useState('34:85:18:94:15:41');
    // const [deviceid, setDeviceId] = useState('34:85:18:94:1D:DD');
    // const [serviceid, setServiceId] = useState(
    //   '4fafc201-1fb5-459e-8fcc-c5c9c331914b',
    // );
    // const [caracid, setCaracId] = useState(
    //   'beb5483e-36e1-4685-b7f5-ea07361b26a8',
    // );
    // const [caracid1, setCaracId1] = useState(
    //   'beb5483e-36e1-4686-b7f5-ea07361b26a8',
    // );
    // const [caracid2, setCaracId2] = useState(
    //   'beb5483e-36e1-4687-b7f5-ea07361b26a8',
    // );
    // const [caracid3, setCaracId3] = useState(
    //   'beb5483e-36e1-4688-b7f5-ea07361b26a8',
    // );
    // const [serviceid1, setServiceId1] = useState(
    //   '4fafc202-1fb5-459e-8fcc-c5c9c331914b',
    // );
    // const [caracid4, setCaracId4] = useState(
    //   'beb5483e-36e2-4670-b7f5-ea07361b26a8',
    // );
    // const [caracid5, setCaracId5] = useState(
    //   'beb5483e-36e2-4671-b7f5-ea07361b26a8',
    // );
    // const [caracid7, setCaracId7] = useState(
    //   'beb5483e-36e2-4680-b7f5-ea07361b26a8',
    // );
    // const [caracid8, setCaracId8] = useState(
    //   'beb5483e-36e1-4689-b7f5-ea07361b26a8',
    // );
    let deviceid ="34:85:18:94:1D:D9";
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
    const [selectedDevice, setSelectedDevice] = useState<Peripheral>();
    const [bleDevice, setDevice] = useState([]);
    const [bluetoothDevices, setBluetoothDevices] = useState([]);
    // const [bleDevices, setDevices] = useState([]);
    const [currentDevice, setCurrentDevice] = useState<any>(null);
    const [sdFiles, setSdFiles] = useState([]);
    const [prevFile,setPrevFile] = useState();
    const [rpmValue, setrpmValue] = useState();
    const [pCount, setPCount] = useState();
    const [char1Data, setChar1Data] = useState('');
    const [char2Data, setChar2Data] = useState('');
    const [char3Data, setChar3Data] = useState('');
    const [char4Data, setChar4Data] = useState('');
    const [char5Data, setChar5Data] = useState('');
    const [char7Data, setChar7Data] = useState('');
    const [char8Data, setChar8Data] = useState('');
    const [data,setData] = useState();
    const [height, setHeight] = useState('');
    const [width, setWidth] = useState('');
    const [cnCount, setCnCount] = useState();
    const [cardCount, setCardCount] = useState(8);
    const [ttlHook,setTtlHook] = useState();
    const BleManagerModule = NativeModules.BleManager;
    const BleManagerEmitter = new NativeEventEmitter(BleManagerModule);
  
    useEffect(() => {
      BleManager.start({showAlert: false}).then(() => {
        // Success code
        console.log('BLEManager initialized');
        // enableWifi();
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
          console.log('disconnected Device', peripheral);
          setIsConnected(false);
        },
      );
      let characteristicValueupdate = BleManagerEmitter.addListener(
        'BleManagerDidUpdateValueForCharacteristic',
        data => {
          console.log('Event BleManagerDidUpdateValueForCharacteristic', data);
          setData(data);
          readAllCharDataFromEvent(data);
          // readCharacteristicFromEvent(data);
          // readSdFiles(data);
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
  
    // const requestPermission = async () => {
    //   try {
    //     const granted = await PermissionsAndroid.requestMultiple([
    //       PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
    //       PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
    //       PermissionsAndroid.PERMISSIONS.BLUETOOTH_ADVERTISE,
    //       PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
    //       PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION,
    //       PermissionsAndroid.PERMISSIONS.ACCESS_WIFI_STATE,
    //       PermissionsAndroid.PERMISSIONS.CHANGE_WIFI_STATE,
    //     ]);
    
    //     // Check if all permissions were granted
    //     const allPermissionsGranted = Object.values(granted).every(
    //       status => status === PermissionsAndroid.RESULTS.GRANTED
    //     );
    
    //     if (allPermissionsGranted) {
    //       // Start Wi-Fi enabling logic
    //       await enableWifi();
    //       // Start BLE scanning
    //       startScanning();
    //     } else {
    //       console.log("Some permissions were denied");
    //     }
    //   } catch (err) {
    //     console.warn(err);
    //   }
    // };
    
    // const enableWifi = async () => {
    //   try {
    //     const isEnabled = await WifiManager.isEnabled();
    //     if (!isEnabled) {
    //       await WifiManager.setEnabled(true);
    //       console.log("Wi-Fi enabled");
    //     } else {
    //       console.log("Wi-Fi is already enabled");
    //     }
    //   } catch (error) {
    //     console.error("Failed to enable Wi-Fi:", error);
    //   }
    // };
    
  
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
        BleManager.scan([], 5, false)
          .then(() => {
            // Success code
            console.log('Scan started');
            setIsScanning(true);
          })
          .catch((error: any) => {
            console.error(error);
          });
      }
    };
    const readAllCharDataFromEvent = (data: any)=>{
      const {service,characteristic,value} = data;
      if(service=== serviceid1 && characteristic === caracid1){
       const caracidValue = bytesToString(value);
       if(caracidValue.startsWith('RPM.')){
        setrpmValue(caracidValue);
        console.log('rpmValue',caracidValue); 
       }
       if (caracidValue.endsWith('.bmp')) {
        setSdFiles(currentFiles => [...currentFiles, caracidValue]);
        console.log('SDCardData', caracidValue);
      }
      }
      if(service=== serviceid1 && characteristic===caracid2){
      const caracid2Value = bytesToString(value);
      const PreviousFile = caracid2Value.substring(1);
      console.log('caracid2:', PreviousFile);
      setPrevFile(PreviousFile);
      }
      if(service=== serviceid1 && characteristic===caracid3){
        const caracid3Value = bytesToString(value);
        console.log("width&Height", caracid3Value);
        const dimensions = caracid3Value.split('.');
          
          if (dimensions.length === 2) {
              setHeight(dimensions[0]); // height
              setWidth(dimensions[1]);   // width
          } else {
              console.error("Invalid format: expected 'height.width'");
          }
        console.log('caracid3 height:', height);
        console.log('caracid3: width:', width);
        }
      if(service=== serviceid1 && characteristic===caracid4){
          const caracid4Value = bytesToString(value);
          const hight_int = parseInt(caracid4Value,10);
          console.log('hight_var:', caracid4Value);
          setPCount(hight_int);
          console.log('hight_int:', hight_int);
        }
        if(service=== serviceid2 && characteristic===caracid6){
          const caracid6Value = bytesToString(value);
          console.log('caracid6:', caracid6Value);
          }
          if(service=== serviceid2 && characteristic===caracid5){
            const caracid5Value = bytesToString(value);
            console.log('caracid5:', caracid5Value);
            }  
            if(service=== serviceid2 && characteristic===caracid7){
              const caracid7Value = bytesToString(value);
              console.log('caracid7:', caracid7Value);
              }
              if(service=== serviceid2 && characteristic===caracid8){
                const caracid8Value = bytesToString(value);
                console.log('caracid8:', caracid8Value);
                const dimensions = caracid8Value.trim().split('.');
                // console.log("Split dimensions:", dimensions);
          if (dimensions.length === 3) {
              setCardCount(parseInt(dimensions[0], 10)); // card count
              setCnCount(parseInt(dimensions[1], 10));   // connector count
              setTtlHook(parseInt(dimensions[2], 10));  // total Hook 
          } else {
              console.error("Invalid format: expected 'height.width'");
          }
  //         console.log("Card Count:", dimensions[0].trim());
  // console.log("Connector Count:", dimensions[1].trim());
  // console.log("Total Hook:", dimensions[2].trim());
        console.log('caracid8 card:', cardCount);
        console.log('caracid8: connector:', cnCount);
        console.log('caracid8: Total Hooks:', ttlHook);
                }
    }
  
   
    const handleGetConnectedDevices = () => {
      BleManager.getDiscoveredPeripherals([]).then((result: any) => {
        if (result.length === 0) {
          console.log('No Device Found');
          startScanning();
        } else {
          console.log('Results :', JSON.stringify(result));
          const allDevices = result.filter((item: any) => item.name !== null);
          setDevice(allDevices);
          console.log('test Result from Handleconnection', allDevices);
        }
  
        // Success code
        console.log('Discovered peripherals: ' + result);
      });
    };
  
    const renderItem = ({item}: any) => {
      return (
        <>
          <View style={styles.bleCard}>
            <Text style={styles.txt}>{item.name}</Text>
            <Text style={styles.txt}>{isConnected}</Text>
            <TouchableOpacity
              style={styles.btn}
              onPress={() => {
                {
                  currentDevice?.id === item?.id
                    ? (isConnected ? onDisconnect(item) : onConnect(item))
                    : onConnect(item)
                }
                // {
                //   currentDevice?.id === item?.id
                //     ? onDisconnect(item)
                //     : onConnect(item);
                // }
              }}>
              <Text style={styles.btntxt}>
                {/* {currentDevice?.id === item?.id ? 'Disconnect' : 'Connect'} */}
                {currentDevice?.id === item?.id ? (isConnected ? 'Disconnect' : 'Connect') 
    : 'Connect'}
              </Text>
            </TouchableOpacity>
          </View>
          <View>
            <Text>{isConnected}</Text>
          </View>
        </>
      );
    };
  
    
    const onConnect = async (item: any) => {
      try {
        await BleManager.connect(item.id);
        setCurrentDevice(item);
        setIsConnected(true);
        const result = await BleManager.retrieveServices(item.id);
        console.log('DeviceId is:..', item.id);
        // console.log('DeviceId is:..', deviceid);
        
        console.log('result of services ', result);
        discoverServices(deviceid);
        console.log('onconnect method',isConnected);
        console.log('onconnect method',isScanning);
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
          //  Alert.alert(`Disconnected from ${item.id}`);
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
      const service1Characteristics = [caracid1, caracid2, caracid3, caracid4,caracid5, caracid6];
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
  
  const ReadHeightwidth = async Dimensions => {
    if(isConnected){
      BleManager.read(deviceid, serviceid1, caracid3)
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
      await BleManager.write(deviceid, serviceid1, caracid2, testRun)
        .then(() => {
          const results = bytesToString(testRun);
          console.log('Function call command sent PicCount', results);
        })
        .catch(error => {
          console.error('Error sending function call command:', error);
        });
    }
  };
  // const writeFileToSelect = async (filename) => {
  //   if (!isConnected) {
  //     console.log('Device is not connected.');
  //     return;
  //   }
  //   const filenameWithoutExtension = removeExtension(filename);
  //   console.log(filenameWithoutExtension); 
  //   const rootDir = '/';
  //   const fname = filename;
  //   const fullName = rootDir + fname;
  //   console.log('Full filename with path', fullName);
  //   const testRun = stringToBytes(filenameWithoutExtension);
    
  //   console.log('Attempting to write data to:', deviceid);
  //   console.log('Service ID:', serviceid1);
  //   console.log('Characteristic ID:', caracid2);
  //   console.log('Data to send:', testRun);
  
  //   try {
  //     await BleManager.writeWithoutResponse(deviceid, serviceid1, caracid2, testRun);
  //     const results = bytesToString(testRun);
  //     console.log('Function call command sent File', results);
  //   } catch (error) {
  //     console.error('Error sending function call command:', error);
  //   }
  // };
  // const removeExtension = (filename) => {
  //   // Use lastIndexOf to find the position of the last dot
  //   const lastDotIndex = filename.lastIndexOf('.');
    
  //   // If there's no dot, return the original filename
  //   if (lastDotIndex === -1) return filename;
  
  //   // Return the substring before the last dot
  //   return filename.substring(0, lastDotIndex);
  // };
  const writeData = async (name) => {
    if (isConnected) {
      // const str = "CALL_FUNCTION";
      const testRun = stringToBytes(name);
      await BleManager.write(deviceid, serviceid2, caracid7, testRun)
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
      await BleManager.write(deviceid, serviceid1, caracid2, testRun)
        .then(() => {
          const results = bytesToString(testRun);
          console.log('Function call command sent File', results);
        })
        .catch(error => {
          console.error('Error sending function call command:', error);
        });
    }
  };
  const writeClcnCount = async (countvalue) => {
    if (isConnected) {
      const testRun = stringToBytes(countvalue);
      await BleManager.write(deviceid, serviceid1, caracid2, testRun)
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
      await BleManager.write(deviceid, serviceid1, caracid2, unlockme)
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
    return (
      // screenView(),
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
          // readCharacteristicFromEvent,
          requestPermission,
          renderItem,
          handleGetConnectedDevices,
          // onServiceDiscovered,
          onChangeCharacteristics,
          // renderFileItems,
          // readData,
          writeData,
          strRpm,
          setStrRpm,
          writeFileToSelect,
          strFiles,
          data,
          setData,
          char1Data,
          setChar1Data,
          char2Data,
          setChar2Data,
          char3Data,
          setChar3Data,
          char4Data,
          setChar4Data,
          height,
          setHeight,
          width,
          setWidth,
          imageData,
          unLockMachine,
          cnCount,
      setCnCount,
      cardCount,
      setCardCount,
      ttlHook,
      setTtlHook,
      writeClcnCount,
        }}>
        {children}
      </MyContext.Provider>
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
    container: {
      flex: 1,
      justifyContent: 'center',
      alignItems: 'center',
      backgroundColor: '#EFDBFE',
    },
    ripple: {
      // flex: 1,
      justifyContent: 'center',
      alignItems: 'center',
    },
    rippletxt: {
      // flex: 1,
      justifyContent: 'center',
      alignItems: 'center',
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
  