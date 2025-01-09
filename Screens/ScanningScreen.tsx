import React, {useEffect} from 'react';
import {Image,StatusBar,View,Button,FlatList, Text,StyleSheet} from 'react-native';
import { useMyContext } from '../Components/MyContext';

const ScanningScreen =() =>{
    const {
      bleDevice,
      isScanning, 
      renderItem,
      
        } = useMyContext();
        
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
                    </View>}
                    
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
    }
})