import React, {useState, useCallback, useEffect} from 'react';
import {Image,StatusBar,View, RefreshControl, FlatList, StyleSheet } from 'react-native';
import { useMyContext } from '../Components/MyContext';
import LoadingScreen from './LoadingScreen';
import { useNavigation } from '@react-navigation/native';


const ScanningScreen =(props) =>{
    const {
      bleDevice,
      isScanning, 
      renderItem,
      startScanning,
      isConnected,
        } = useMyContext();
        const navigation = useNavigation();
        const [isRefreshing, setIsRefreshing] = useState(false);
        const [showMainComponent, setShowMainComponent] = useState(false);
          // Function to handle the refresh
          const onRefresh = useCallback(() => {
            setIsRefreshing(true);
            startScanning();
            // Simulating an API call or refresh operation
            setTimeout(() => {
              setIsRefreshing(false); // Stop refreshing after 2 seconds
            }, 5000);
          }, []);
        

          // useEffect to navigate when isConnected changes to true
  useEffect(() => {
    if (isConnected) {
      // Navigate to HomeScreen after successful connection
      navigation.navigate('Home Screen');
    }
  }, [isConnected, navigation]); // Dependency on isConnected and navigation

           // Effect to handle showing/hiding MainComponent based on isScanning and isConnected
  useEffect(() => {
    if (!isScanning && isConnected) {
      setShowMainComponent(true);

      // Set a timer to hide the component after 8 seconds
      const timer = setTimeout(() => {
        setShowMainComponent(false);
      }, 8000); // 8 seconds (adjust as needed)

      // Cleanup the timer when isConnected changes or the component unmounts
      return () => clearTimeout(timer);
    } else {
      // Reset the state if isScanning is true or isConnected becomes false
      setShowMainComponent(false);
    }
  }, [isScanning, isConnected]); // The effect runs when either isScanning or isConnected changes

    return(
        <>
        
        <StatusBar backgroundColor= "#812892"/>
        
        {/* <View style={styles.container}>
          <ScrollView
            style={styles.scrollView} // Apply flex: 1 to the ScrollView itself
            contentContainerStyle={styles.container} // Apply your content layout style here
            refreshControl={
              <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
            }
          >
            {isScanning?<View style={styles.ripple}>
            <Image source = {require('../assets/images/scanning5.gif')} style={{width: 200, height: 200 }} />
                </View>:<View>
                    <FlatList 
                    data = {bleDevice}
                    keyExtractor={(item,index)=>index.toString()}
                    renderItem={renderItem}
                    />
                    </View>}
                    
          </ScrollView>
            
                   </View> */}

<View style={styles.container}>
  <FlatList
    data={isScanning ? [] : bleDevice} // Show an empty list or the actual device list depending on scanning state
    keyExtractor={(item, index) => index.toString()}
    renderItem={renderItem}
    refreshControl={
      <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
    }
    ListFooterComponent={
      isScanning && (
        <View style={styles.ripple}>
          <Image
            source={require('../assets/images/mjscan1.gif')}
            style={styles.image}
          />
        </View>
      )
    }
  />
</View>


<View style={styles.container}>
      {showMainComponent ? <MainComponent /> : null}
    </View>
   
        </>
    );
}


const MainComponent = () => (
  
  <View style={{height: 50}}>
      <View>
        <LoadingScreen />
      </View>
  </View>
  
);

export default ScanningScreen;
const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: '#EFDBFE'
  },
  ripple: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    width: '100%', // Ensure that it takes full width
    height: '100%', // Ensure it takes full height
    marginTop: 100,
  },
  image: {
    width: 200,
    height: 200
  },
    rippletxt:{
        // flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
    },
    usrbgc: 
    {
        backgroundColor: '#ffffff',
        width: 100,
        height: 100,
        padding:3,
        alignSelf:"center",
        marginVertical:0,
         elevation:5,
        borderRadius:50,
        flexDirection: 'row',
        // justifyContent: 'space-between',
    },
    usrCard:
    {
        width:"80%",
        marginTop: 160,
        padding:10,
        alignSelf:"center",
        marginVertical:10,
        backgroundColor:'#EFDBFE',
        elevation:0,
        borderRadius:0,
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
    },
    
});