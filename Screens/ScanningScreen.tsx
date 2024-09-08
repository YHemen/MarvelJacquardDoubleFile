import React, {useContext} from 'react';
import {Image,StatusBar,View,Button,FlatList, Text,StyleSheet} from 'react-native';
import { useMyContext } from '../Components/MyContext';


const ScanningScreen =({navigation}) =>{
    const { 
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
        } = useMyContext();
    // const {
        
    //     devices, 
    //     isScanning, 
    //     startScan, 
    //     connectToDevice, 
    //     connectedDevice, 
    //     services, 
    //     characteristics, 
    //     readCharacteristic, 
    //     writeCharacteristic, 
    //     startNotification 
    //   } = useContext(useMyContext);
    
    const handleConnect = (deviceId) => {
        connectToDevice(deviceId);
        navigation.navigate('Home'); // Navigate to the details screen after connecting
      };
    return(
        <>
        <StatusBar backgroundColor= "#812892"/>
        <View style={styles.container}>
            {isScanning?<View style={styles.ripple}>
            <Image source = {require('../assets/images/scanning5.gif')} style={{width: 200, height: 200 }} />
                </View>:<View>
                    <FlatList 
                    data = {bleDevice}
                    keyExtractor={(item,index)=>index.toString()}
                    renderItem={renderItem}
                    />
                    {/* <Text>Test</Text> */}
                    </View>}
            {/* <Text style={styles.rippletxt}>WELCOME TO MARVEL JACQUARD...!</Text> */}
            
        </View>
        </>
    );
}

export default ScanningScreen;
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
        fontFamily: "Raleway", fontStyle: "regular", fontWeight: "900", color: 'white', alignContent: 'center', textAlignVertical: 'center'
    },
    btntxt: {
        fontFamily: "Raleway", fontStyle: "bold", fontWeight: "900"
    },
    btn: {
        width: 100,
        height: 40,
        alignItems: 'center',
        justifyContent: 'center',
        borderRadius: 5,
        backgroundColor: '#812892'
    }
})