import React, {useEffect, useState} from 'react';
import {Image,StatusBar,View,Button,FlatList, Text,StyleSheet, Modal, TouchableOpacity } from 'react-native';
import * as Animatable from 'react-native-animatable';
import Icon from 'react-native-vector-icons/FontAwesome';
import { useMyContext } from '../Components/MyContext';
import HomeScreen from './HomeScreen';
import globalStyles from '../assets/GlobalValues/Global';

// Sample components
const LockedComponent = () => (
    <>
  <View style={styles.innerContainer}>
    <Text style={globalStyles.text}><Icon name="lock" size={120} color="#812892" /></Text>
    <Animatable.Image animation="zoomInDown" source={require('../assets/images/LOGO.png')} />
  </View>
  <View>
    
            <Modal transparent={true} animationType="fade">
              <View style={styles.overlay}>
                <TouchableOpacity style={styles.closeButton}>
                  <Text style={styles.buttonText}><Icon name="lock" size={55} color="#FFFFFF" /></Text>
                </TouchableOpacity>
                <Text style={globalStyles.text} style={{color: '#FFFFFF'}}>To Un-Lock Machine Contact..!</Text>
              </View>
            </Modal>
    
  </View>
  </>
);

const LogoAddressComponent = () => (
  <View style={styles.innerContainer}>
    <Animatable.Image animation="zoomInDown" source={require('../assets/images/LOGO.png')} />
    <Text style={globalStyles.text}><Icon name="venus" size={25} color="#812892" /> Communication Address</Text>
    <Text style={globalStyles.text}>JERUSHA ENTERPRIPRISES </Text>
    <View style={{width:'90%', borderBottomColor: 'purple', borderRadius: 5, alignItems:"center"}}>
    
     <Text style={globalStyles.text}>BEHIND LAKSHMI NARASIMHA KALYANAMANTAPAM,</Text>
     <Text style={globalStyles.text}>DHAN ROAD, MUDDIREDDY PALLI</Text>
     <Text style={globalStyles.text}>HINDUPUR, SRI SATYA SAI DIST</Text>
     <Text style={globalStyles.text}>ANDHRA PRADESH, PIN CODE: 515201</Text>
    </View>
    <View>
    <Text style={globalStyles.text}><Icon name="mobile-phone" size={25} color="#812892" />7337006557</Text>
     <Text style={globalStyles.text}><Icon name="whatsapp" size={25} color="#812892" />8008355899</Text>
    </View>
    <View>
    <Text style={globalStyles.text}><Icon name="envelope" size={25} color="#812892" />jerushaenterprises@gmail.com</Text>
    <Text style={globalStyles.text}><Icon name="globe" size={25} color="#812892" />www.jerushaenterprises.com</Text>
    </View>
  </View>
);

const MainComponent = () => (
  
  <View style={{height: 400}}>
      <View style={styles.innerContainer}>
        <HomeScreen />
      </View>
  </View>
  
);

const MainApp = () => {
  // The state should be inside the functional component
  // const [isConnected, setIsConnected] = useState(true);
  const [lockStatus, setLockStatus] = useState('unlocked'); // Set the initial status as 'unlocked'
 const {
      bleDevice,
      isScanning, 
      renderItem,
      isConnected,
        } = useMyContext();
  return (
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
                        </View>}
                        <View><Text>hello </Text></View>
                       </View>
                       <View style={styles.container}>
      {
        lockStatus === 'locked' 
          ? <LockedComponent />
          : lockStatus === 'unlocked' 
            ? isConnected 
              ? <MainComponent />
              : <LogoAddressComponent />
            : null // default case if none of the conditions are met
      }
    </View>
            </>
    
  );
};

// Example usage of MainApp component
export default function Example() {
  return <MainApp />;
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#EFDBFE',

  },
  innerContainer: {
    marginTop: -215,
    justifyContent: 'center',
    alignItems: 'center',
  },
  overlay: {
    flex: 1,
    backgroundColor: 'rgba(0, 0, 0, 0.5)', // Transparent background
    justifyContent: 'center',
    alignItems: 'center',
  },
  modalContent: {
    width: '80%',
    backgroundColor: 'white',
    padding: 20,
    borderRadius: 10,
    elevation: 5,
  },
  
});