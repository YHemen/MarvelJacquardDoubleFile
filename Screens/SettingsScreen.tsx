import React, { useState } from "react";
import {SafeAreaView, setNumber,Button, View, Text,LayoutAnimation, StyleSheet, TextInput, TouchableOpacity} from 'react-native';
import { useNavigation } from '@react-navigation/native';
import Modal from "react-native-modal";
import { SlideInDown } from "react-native-reanimated";
import HomeScreen from "./HomeScreen";
import Icon from 'react-native-vector-icons/FontAwesome';
import FilesScreen from "./FilesScreen"
import { useMyContext } from '../Components/MyContext';

const SettingsScreen: React.FC = () => {
    const { someValue, setSomeValue } = useMyContext();
    return(
        <SafeAreaView style={styles.container}>
        <View><Text style={{fontSize:20}}>Hook Settings</Text></View>
        <View><Text style={{fontSize:20, fontWeight: 'bold'}}>BODY</Text></View>
        <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-evenly', paddingHorizontal: 10 }}>
        <Text style={{textAlign:'left'}}>CL:</Text>
        <TouchableOpacity onPress={handleDecrement}>
        <Icon name="chevron-down" size={30} color="#000"/> 
        </TouchableOpacity>
        <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
        <TouchableOpacity onPress={handleIncrement}>
        <Icon name="chevron-up" size={30} color="#000" textAlign="right" /> 
        </TouchableOpacity>
        
    </View>
    <View>
        <Text style={{fontSize:16}}>960</Text>
        </View>
      
      <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
      <Text>CN:</Text>
        <TouchableOpacity onPress={handleDecrement}>
        <Icon name="chevron-down" size={30} color="#000" /> 
        </TouchableOpacity>
        <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
        <TouchableOpacity onPress={handleIncrement}>
        <Icon name="chevron-up" size={30} color="#000" /> 
        </TouchableOpacity>
        
      
        
    </View>
    <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
        <Text>HOOKS:</Text>
        <TouchableOpacity onPress={handleDecrement}>
        <Icon name="chevron-down" size={30} color="#000" /> 
        </TouchableOpacity>
        <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
        <TouchableOpacity onPress={handleIncrement}>
        <Icon name="chevron-up" size={30} color="#000" /> 
        </TouchableOpacity>
        
    </View>
    
    <View><Text style={{fontSize:20}}>Design Left and Right</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
         <TouchableOpacity onPress={handleDecrement} style={{backgroundColor:'purple', width: 80, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 40}}>
        <Text style={{justifyContent:'center',alignItems:'center', color:'white', fontSize:15}}>LEFT</Text>
        </TouchableOpacity>
        <TouchableOpacity onPress={handleIncrement} style={{backgroundColor:'purple', width: 80, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 10}}>
        <Text style={{justifyContent:'center',alignItems:'center', color:'white', fontSize:15}}>RIGHT</Text>
        </TouchableOpacity>
        {/* <Button
          title="LEFT"
          color={'black'}
          disabled={runningDesign }
        //   onPress={() => {
        //     navigation.navigate('About');
          //}}
          
        />  */}
        
    </View>

    <View><Text style={{fontSize:20}}>Running Lock Date</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
         <Text style={{marginRight: 10,justifyContent:'center',alignItems:'center', fontSize:20}}>Lock Date:</Text> 
    <Text style={{justifyContent:'center',alignItems:'center', fontSize:20}}>12-4-2026</Text>
    </View>
    <View>
    {/* <TouchableOpacity onPress={handleIncrement} style={{backgroundColor:'purple', width: 80, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 10}}>
        <Text style={{justifyContent:'center',alignItems:'center', color:'white', fontSize:15}}>UN-LOCK</Text>
        </TouchableOpacity> */}
        <TouchableOpacity style={{height: 40, width: 120, borderRadius: 25, borderWidth: 1,overflow: 'hidden',padding:1, borderColor: isOn?onColor:offColor}} onPress={()=>{LayoutAnimation.easeInEaseOut();setIsOn(!isOn);}}>
                <View style={{borderRadius: 25,alignItem:'center',justifyContent: 'center',height: '100%', width: '50%', backgroundColor:isOn?onColor:offColor, alignSelf: isOn?'flex-end':'flex-start'}}><Text style={{alignItem:'center',justifyContent:'center',color:'white',fontSize:12, fontWeight:'800',fontStyle:'normal'}}>{isOn?'LOCK':'UNLOCK'}</Text></View>
                </TouchableOpacity>
    </View>
        </SafeAreaView>
    );
}

export default SettingsScreen;
const styles = StyleSheet.create({
    container:
    {
        flex: 1,
        justifyContent:"center",
        alignItems: "center",
        backgroundColor: '#EFDBFE'
    },
})