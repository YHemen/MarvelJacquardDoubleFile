// screens/DetailsScreen.js

  import React, { useState } from "react";
  import {SafeAreaView, setNumber,Button, View, Text,LayoutAnimation, StyleSheet, TextInput, TouchableOpacity} from 'react-native';
  import { useNavigation } from '@react-navigation/native';
  import Modal from "react-native-modal";
  import { SlideInDown } from "react-native-reanimated";
  import HomeScreen from "./HomeScreen";
  import Icon from 'react-native-vector-icons/FontAwesome';
  import FilesScreen from "./FilesScreen";
  import { useMyContext } from '../Components/MyContext';
  
  const DetailsScreen: React.FC = () => {
          const onColor = "green";
          const offColor = "red";
          const [isOn, setIsOn] = useState();
          const [isOff, setIsOff] = useState();
      const [runningDesign,setRunningDesign] = useState(false);
      const navigation = useNavigation();
      const [number, setNumber] = useState(500);
      const handleIncrement =() =>{
          setNumber((prevNumber)=> prevNumber + 1);
          };
          const handleDecrement =() =>{
              setNumber((prevNumber)=> prevNumber + 1);
              };
      return(
          <SafeAreaView style={styles.container}>
            <View style={{ height: 180, paddingTop: 30, paddingBottom: 30}}>
            {/* <View><Text style={{fontSize:20}}>Hook Settings</Text></View> */}
            <View style={{alignSelf:'center', alignItems:'center'}}>
              <View><Text style={{fontSize:20, fontWeight: 'bold'}}>BODY</Text></View>
              <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View>
            </View>
              
              <View style={{flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center',paddingHorizontal: 30}}>
              <TouchableOpacity onPress={handleDecrement}>
              <Icon name="chevron-down" size={30} color="#000"/> 
              </TouchableOpacity>
              <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
              <TouchableOpacity onPress={handleIncrement}>
              <Icon name="chevron-up" size={30} color="#000" textAlign="right" /> 
              </TouchableOpacity>
              </View>
              <View><Text style={{textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>960</Text></View>
            </View>

            <View style={{ height: 180, paddingTop: 30, paddingBottom: 30}}>
            {/* <View><Text style={{fontSize:20}}>Hook Settings</Text></View> */}
            <View style={{alignSelf:'center', alignItems:'center'}}>
              <View><Text style={{fontSize:20, fontWeight: 'bold'}}>BORDER-1</Text></View>
              <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View>
            </View>
              
              <View style={{flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center',paddingHorizontal: 30}}>
              <TouchableOpacity onPress={handleDecrement}>
              <Icon name="chevron-down" size={30} color="#000"/> 
              </TouchableOpacity>
              <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
              <TouchableOpacity onPress={handleIncrement}>
              <Icon name="chevron-up" size={30} color="#000" textAlign="right" /> 
              </TouchableOpacity>
              </View>
              <View><Text style={{textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>960</Text></View>
            </View>
            <View style={{ height: 180, paddingTop: 30, paddingBottom: 30}}>
            {/* <View><Text style={{fontSize:20}}>Hook Settings</Text></View> */}
            <View style={{alignSelf:'center', alignItems:'center'}}>
              <View><Text style={{fontSize:20, fontWeight: 'bold'}}>BORDER-2</Text></View>
              <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View>
            </View>
              
              <View style={{flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center',paddingHorizontal: 30}}>
              <TouchableOpacity onPress={handleDecrement}>
              <Icon name="chevron-down" size={30} color="#000"/> 
              </TouchableOpacity>
              <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {number}</TextInput>
              <TouchableOpacity onPress={handleIncrement}>
              <Icon name="chevron-up" size={30} color="#000" textAlign="right" /> 
              </TouchableOpacity>
              </View>
              <View><Text style={{textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>960</Text></View>
            </View>
            <View style={{flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center',paddingHorizontal: 30, paddingVertical: 30}}>
              <View><Text style={{fontSize: 30,fontWeight: 'bold', color: 'purple'}}>RPM:</Text></View>
              <View style={{backgroundColor: 'pink', borderRadius: 60, width: 45, alignSelf: 'center', alignContent: 'center'}}>
              
              </View>
              
              <TouchableOpacity onPress={()=>{navigation.navigate(FilesScreen)}}>
              <Text style={{backgroundColor: 'pink', borderRadius: 50, width: 45, height: 45, paddingLeft: 8, paddingTop: 5}}><Icon name="upload" size={30} color="#000" /></Text>
        </TouchableOpacity>
            </View>
          </SafeAreaView>
             
          );
      }
      export default DetailsScreen;    
      const styles = StyleSheet.create({
          container: {
          flex: 1,
          backgroundColor: '#EFDBFE',
          alignItems: 'center',
          justifyContent: 'center',

          // flex: 1, flexDirection: 'row', justifyContent: 'space-between', alignItems: 'center', paddingHorizontal: 10, 
          },
          btn: {
              width: 200,
              height: 50,
              alignItems: 'center',
              justifyContent: 'center',
              marginLeft: 5,
              marginTop: 5,
              marginBottom: 5,
              marginRight: 5,
              borderRadius: 5,
              backgroundColor: '#3B71CA',
          },
          txt: {
              color: 'white',
          }
      })
  
  