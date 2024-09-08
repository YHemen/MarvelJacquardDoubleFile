// HomeScreen.tsx
import React from 'react';
import { View, Text, Button, StyleSheet, FlatList } from 'react-native';
import { useMyContext } from '../Components/MyContext';
import {deviceid, serviceid, caracid} from '../assets/GlobalValues/Global';
const HomeScreen: React.FC<{ navigation: any }> = ({ navigation }) => {
// const HomeScreen: React.FC = ({ navigation }) => {
  const { sdFiles,setSdFiles, currentDevice, isConnected, readData,strRpm,strFiles,sdFilesReadFromClient } = useMyContext();
  
  const handleReadFiles = async () => {
    if (currentDevice) {
        const files = await readData();
        setSdFiles(files);
    }
};

const handlecharuuid1 = async () =>{
  if(currentDevice) {
    const char1 = await sdFilesReadFromClient();
    setSdFiles(char1);
  }
};
  
  return (
    <View style={styles.container}>
      <Text style={{alignSelf:'center'}}>{isConnected ? <Text style={{alignItems: 'center',fontFamily:'verdana', fontSize: 20, fontWeight:'900'}}>{currentDevice?.name}</Text> : 'Jacquard Not Connected..!'}</Text>
      {/* <Text style={{fontFamily:'verdana', fontSize: 20, fontWeight:'900'}}>{currentDevice?.name}</Text> */}
      
            
            <Button title="Read File List" onPress={handleReadFiles} />
            <Text>Files:</Text>
            <Text>{strRpm}</Text>
       
      <Button title="Read Files" onPress={handlecharuuid1} />
      <Text>char1Data:</Text>
      <Text>{strFiles}</Text>
      {/* <Button title="Go to Details" onPress={() => navigation.navigate('Details')} /> */}
    </View>
      
      
  );
};

export default HomeScreen;
const styles = StyleSheet.create({
    container:
    {
        flex: 1,
        justifyContent:"center",
        alignItems: "center",
        backgroundColor: '#EFDBFE'
    },
})