import React,{useEffect} from 'react';
import {View, Text, Alert, Button, BackHandler, Image, StyleSheet} from 'react-native';
import { TouchableOpacity } from 'react-native-gesture-handler';
const ExitScreen =() =>{

    useEffect(() => {
        Alert.alert(
            'Exit App',
            'Are you sure you want to exit?',
            [
              { text: 'Cancel', onPress: () => console.log('Cancel Pressed') },
              { text: 'OK', onPress: () => BackHandler.exitApp() },
            ],
            { cancelable: false }
          );
      }, []);
    const exitApp = () =>{
        Alert.alert(
            'Exit App',
            'Are you sure you want to exit?',
            [
              { text: 'Cancel', onPress: () => console.log('Cancel Pressed') },
              { text: 'OK', onPress: () => BackHandler.exitApp() },
            ],
            { cancelable: false }
          );
    }
    return(
        <View style={styles.container}>
            {/* <Text>Exiting from Marvel Jacquards App please wait...!</Text> */}
            <Image source = {require('../assets/images/LOGO.png')} style={{flexDirection: 'row', width: 250, height: 200, alignContent: 'center', alignSelf: 'center' }} />
            {/* <Button title="Exit App" onPress={exitApp} style={{width: 200, height: 50, justifyContent: 'center', alignItems: 'center',}}/> */}
            <TouchableOpacity style={{width: 130, height: 40, justifyContent: 'center', alignItems: 'center', alignSelf: 'center', backgroundColor: 'purple'}} onPress={exitApp}>
                <Text style={{color:'white', justifyContent: 'center', alignItems: 'center', alignSelf: 'center'}}>EXIT APP</Text>
            </TouchableOpacity>
        </View>
    );
}

export default ExitScreen;

const styles = StyleSheet.create({
    container:
    {
        flex: 1,
        justifyContent:"center",
        alignItems: "center",
        backgroundColor: '#EFDBFE',
    },
})