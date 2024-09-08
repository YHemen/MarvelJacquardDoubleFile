// MyContext.tsx
import React, { createContext, ReactNode, useContext, useState, useEffect } from 'react';
import BleManager from 'react-native-ble-manager';
// import { bytesToString,stringToBytes } from "convert-string";
// import {bytesToString} from 'utils';
// import { useNavigation } from '@react-navigation/native';
import { Buffer } from 'buffer';
import base64 from 'react-native-base64';
import {StatusBar,View,Text,Image,setError,TextInput, Alert, StyleSheet, PermissionsAndroid, NativeEventEmitter, NativeModules, FlatList, TouchableOpacity, Button} from 'react-native';
import {deviceid,serviceid,caracid,caracid1,caracid2,caracid3,serviceid1,caracid4,caracid5,caracid7} from '../assets/GlobalValues/Global';
// const BleManagerEmitter = new NativeEventEmitter(NativeModules.BleManager);

interface MyContextType {
  someValue: string;
  setSomeValue: (value: string) => void;
  isScanning: boolean;
  setIsScanning: (value: boolean) => void;
  devices: string;
  setDevices: (value: string) => void;
  currentDevices: string;
  setCurrentDevices: (value: null) => void;
  isConnected: boolean;
  setIsConnected: (value: boolean) => void;
}

const MyContext = createContext<MyContextType | undefined>(undefined);

export const MyContextProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
  // const navigation = useNavigation();
  const [strRpm, setStrRpm] = useState(0);
  const[strFiles, setStrFiles] = useState();



  const [deviceid, setDeviceId] = useState('34:85:18:93:E8:A9');
  const [serviceid,setServiceId] = useState('4fafc201-1fb5-459e-8fcc-c5c9c331914b');
  const [caracid,setCaracId] = useState('beb5483e-36e1-4685-b7f5-ea07361b26a8');
  const [caracid1,setCaracId1] = useState('beb5483e-36e1-4686-b7f5-ea07361b26a8');
  const [caracid2,setCaracId2] = useState('beb5483e-36e1-4687-b7f5-ea07361b26a8');
  const [caracid3,setCaracId3] = useState('beb5483e-36e1-4688-b7f5-ea07361b26a8');
  const [serviceid1,setServiceId1] = useState('4fafc202-1fb5-459e-8fcc-c5c9c331914b');
  const [caracid4,setCaracId4] = useState('beb5483e-36e2-4670-b7f5-ea07361b26a8');
  const [caracid5,setCaracId5] = useState('beb5483e-36e2-4671-b7f5-ea07361b26a8');
  const [caracid7,setCaracId7] = useState('beb5483e-36e2-4680-b7f5-ea07361b26a8');
  const [caracid8,setCaracId8] = useState('beb5483e-36e1-4689-b7f5-ea07361b26a8');


    const [isScanning, setIsScanning] = useState(false);
    const [receivedMessage, setReceivedMessage] = useState("");
    const [isConnected, setIsConnected] = useState(false);
    const [selectedDevice, setSelectedDevice] = useState<Peripheral>();
    const [bleDevice, setDevice] = useState([]);
    const [sdFiles, setSdFiles] = useState('MyDesignFiles');
    const [bluetoothDevices,setBluetoothDevices] = useState([]);
    const [bleDevices, setDevices] = useState([]);
    const [currentDevice, setCurrentDevice] = useState<any>(null);
    
    const BleManagerModule=NativeModules.BleManager;
    const BleManagerEmitter = new NativeEventEmitter(BleManagerModule);
 


    useEffect(()=>{
        BleManager.start({ showAlert: false }).then(() => {
            // Success code
            console.log("Module initialized");
          });
    })
    useEffect(()=>{
        BleManager.enableBluetooth()
        .then(()=>{
            console.log("The Bluetooth is already enabled or the user conformed");
            requestPermission();
        })
        .catch(()=>{
            console.log("The user refused to enable bluetooth.!");
        });
    },[])

    useEffect(()=>
        {
            let stopListener=BleManagerEmitter.addListener('BleManagerStopScan',
                ()=>{
                    setIsScanning(false);
                    handleGetConnectedDevices();
                    console.log("Stop");
                },
            );
                // return ()=>stopListener.remove();
            let disconnected = BleManagerEmitter.addListener('BleManagerDisconnectPeripheral',
                peripheral =>{
                    console.log('disconnected Device',peripheral);
                },
            );
            let characteristicValueupdate = BleManagerEmitter.addListener('BleManagerDidUpdateValueForCharacteristic',
                data=>{
                    console.log('Event BleManagerDidUpdateValueForCharacteristic',data);
                    readCharacteristicFromEvent(data);
                    readSdFiles(data);
                },
            );
            let BleManagerDidUpdateState = BleManagerEmitter.addListener("BleManagerDidUpdateState", 
                data => {
                    console.log('Event BleManagerDidUpdateState',data);
              },
            );    
              return()=>{
                stopListener.remove();
                disconnected.remove();
                characteristicValueupdate.remove();
                BleManagerDidUpdateState.remove();
              }
            },[bluetoothDevices]);

           

            const readCharacteristicFromEvent = (data:any)=>{
              const {service, characteristic,value} = data;
      
              if(service===serviceid && characteristic===caracid){
      
                  const sdcardata = bytesToString(value);
      
                  if(sdcardata.endsWith('.bmp')){
                      setSdFiles(sdFiles => [...sdFiles, sdcardata]);
                      console.log("sdcardata0",sdcardata); 
                  }
                  console.log("sdcardata0a",sdcardata);
              }
      
              if(characteristic===caracid1){
                  const lockstatus = bytesToString(value);
                  console.log("sdcardata1",lockstatus); 
              }
          }

    const requestPermission = async()=>{
      const granted =  await PermissionsAndroid.requestMultiple([
            PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
            PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
            PermissionsAndroid.PERMISSIONS.BLUETOOTH_ADVERTISE,
            PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION,
            PermissionsAndroid.PERMISSIONS.ACCESS_COARSE_LOCATION

        ])
        if(granted){
            startScanning();
        }
    }
   const startScanning = ()=>{
    if(!isScanning){
        BleManager.scan([], 5, false).then(() => {
            // Success code
            console.log("Scan started");
            setIsScanning(true);
          }).catch((error:any)=>{
            console.error(error);
          })
    }
    
    }

    const handleGetConnectedDevices=()=>{
        BleManager.getDiscoveredPeripherals([]).then((result:any) => {
            if(result.length===0){
                console.log("No Device Found");
                startScanning();
            }else{
                console.log("Results :",JSON.stringify(result));
                const allDevices = result.filter((item:any)=>item.name!==null)
                setDevice(allDevices);
            }

            // Success code
            console.log("Discovered peripherals: " + result);
          });
    }
    
    

    const renderItem = ({item,index}:any) => {
        return(
            <>
                <View style={styles.bleCard}>
                <Text style={styles.txt}>{item.name}</Text>
                <Text style={styles.txt}>{isConnected}</Text>
                <TouchableOpacity style={styles.btn} onPress={()=> {{currentDevice?.id===item?.id? onDisconnect(item) : onConnect(item)}}}>
                    <Text
                          style={
                            styles.btntxt
                          }>
                          {currentDevice?.id===item?.id? 'Disconnect' : 'Connect'}
                        </Text>
                </TouchableOpacity>
            </View>
            <View><Text>{isConnected}</Text></View>
            
            </>
            
        )
        
    }

    
    const readData = () => {
      // Check if there is a connected device
      console.log(serviceid);
      if (isConnected) {
        console.log(caracid);
        // Read a characteristic value from the device by its service UUID and characteristic UUID
        BleManager.read(deviceid, serviceid, caracid)
          .then((readData) => {
            // const buffer = Buffer.from(readData);
              console.log(readData);
            // // const str = buffer.readFloatLE(0, true);
              const strRpm = bytesToString(readData);
            // Display read value
          //   base64.encode(readData.toString()),
          //   console.log('reading Data',base64.decode(temperatureCharacteristicUUID.readData));
           console.log(`Read value from ${deviceid} - ${serviceid} - ${caracid}: ${strRpm}`);
           setStrRpm(strRpm);
          })
          .catch((err) => {
            // Update error message
            console.log(err.message);
          });
      }
    }

    const sdFilesReadFromClient = () => {
      // Check if there is a connected device
      console.log(serviceid);
      if (isConnected) {
        console.log(caracid8);
        // Read a characteristic value from the device by its service UUID and characteristic UUID
        BleManager.read(deviceid, serviceid, caracid8)
          .then((readData) => {
            // const buffer = Buffer.from(readData);
              console.log(readData);
            // // const str = buffer.readFloatLE(0, true);
              const strFiles = bytesToString(readData);
            // Display read value
          //   base64.encode(readData.toString()),
          //   console.log('reading Data',base64.decode(temperatureCharacteristicUUID.readData));
           console.log(`Read value from ${deviceid} - ${serviceid} - ${caracid8}: ${strFiles}`);
           setStrFiles(strFiles);
          })
          .catch((err) => {
            // Update error message
            console.log(err.message);
          });
      }
    }




    const renderFileItems = () => {
        let items = [];
        for (let i = 0; i < sdFiles.length; i++) {
          items.push(
            <View key={i} style={styles.itemContainer}>
              <Text style={styles.itemText}>{sdFiles[i]}</Text>
              
            </View>
          );
        }
        return items;
      };
    const onConnect=async(item:any)=>{
        try {
        await BleManager.connect(item.id);
        setCurrentDevice(item);
        setIsConnected(true);
        const result = await BleManager.retrieveServices(item.id);
        console.log("result of services ", result);
        onServiceDiscovered(result,item);
        console.log(isConnected);
        console.log(isScanning);
        } catch (error) {
            console.log("onConnect Error..:",error);
        }
    }


    // disconnect from device
 const onDisconnect = async(item:any) => {
    BleManager.disconnect(currentDevice?.id)
    .then(() => {
         setCurrentDevice(null);
         setIsConnected(false);
         clearInterval(item.id);
         console.log("Disconnected from device",item.id);
        //  Alert.alert(`Disconnected from ${item.id}`);
    })
    .catch((error) => {
      // Failure code
      console.log("Error disconnecting:",error);
    });
  };

        const bytesToString=(bytes:any)=>{
            return String.fromCharCode(...bytes);
        }

        // Helper function to convert byte array to string
  const byteArrayToString = (byteArray) => {
    return String.fromCharCode.apply(null, byteArray);
  };



        const onServiceDiscovered=(result:any, item:any)=>{
            const services = result.services;
            const characteristics=result.characteristics;
            services.forEach((service:any)=>{
            const serviceUUID = service.uuid;
            onChangeCharacteristics(serviceUUID, characteristics,item);
            });
        }

        
    const onChangeCharacteristics=(serviceUUID:any, result:any,item:any)=>{
        result.forEach((characteristic:any)=>{
            const characteristicuuid=characteristic.characteristic;
            if(characteristicuuid==='"beb5483e-36e1-4688-b7f5-ea07361b26a8'){
                BleManager.startNotification(item.id, serviceUUID,characteristicuuid).then(()=>{
                    console.log("notification Started..");
                }).catch((error)=>{
                    console.error(error);
                })       
            }
        })
    }



        const readSdFiles = (serviceid, caracid1)=>{
        if(isConnected){
        BleManager.read(deviceid,serviceid,caracid1).then((readSdFiles) => {
            const strdata=bytesToString(readSdFiles)
        console.log('reading Data', strdata);
        }).catch((error)=>{
        console.log(error);
        });
        }
        }

        const readLockStatus = (serviceid1, caracid5)=>{
            if(isConnected){
            BleManager.read(deviceid,serviceid1,caracid5).then((readLockStatus) => {
                const strdata=bytesToString(readLockStatus)
                // if(strdata.startsWith('RPM.')){
                //     console.log('reading Data0', strdata);
                // }
            console.log('reading Data01', strdata);
            }).catch((error)=>{
            console.log(error);
            });
            }
            }

          // const writeData = (serviceid, caracid, value) => {
          //   // Check if there is a connected device
          //   if (isConnected) {
          //     // Write a characteristic value to the device by its service UUID and characteristic UUID
          //     BleManager.write((deviceid, serviceid, caracid, value)
          //       .then(() => {
          //         // Display confirmation message
          //         console.log(`Wrote value to ${deviceid} - ${serviceid} - ${caracid}: ${value}`);
          //       })
          //       .catch((err) => {
          //         // Update error message
          //         setError(err.message);
          //       });
          //   }
          // }


  return (
    // screenView(),
    <MyContext.Provider value={{ 
      bluetoothDevices,
      setBluetoothDevices,
      bleDevice,
      isScanning, 
      setIsScanning,
      isConnected, 
      setIsConnected,
      currentDevice,
      setCurrentDevice,
      sdFiles,
      setSdFiles,
      startScanning,
      onConnect,
      onDisconnect,
      readCharacteristicFromEvent,
      requestPermission,
      renderItem,
      handleGetConnectedDevices,
      onServiceDiscovered,
      onChangeCharacteristics,
      readSdFiles,
      readLockStatus,
      renderFileItems,
      readData,
      strRpm,
      sdFilesReadFromClient,
      strFiles
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
    container:
    {
        flex: 1,
        justifyContent:"center",
        alignItems: "center",
        backgroundColor: '#EFDBFE'
    },
    ripple:{
        // flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
    },
    rippletxt:{
        // flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
    },
    bleCard:
    {
        width:"90%",
        padding:10,
        alignSelf:"center",
        marginVertical:10,
        backgroundColor:'#812892',
        elevation:5,
        borderRadius:5,
        flexDirection: 'row',
        justifyContent: 'space-between'
    },
    txt: {
        fontFamily: "Raleway", fontStyle: "regular", fontWeight: "900", color: '#FFFFFF', alignContent: 'center', textAlignVertical: 'center'
    },
    btntxt: {
        fontFamily: "Raleway", fontStyle: "bold", fontWeight: "900", color: '#812892'
    },
    btn: {
        width: 100,
        height: 40,
        alignItems: 'center',
        justifyContent: 'center',
        borderRadius: 5,
        backgroundColor: '#EFDBFE'
    }
})