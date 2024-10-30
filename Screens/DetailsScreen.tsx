// screens/DetailsScreen.js

import React, {useState,useEffect} from 'react';
import {
  SafeAreaView,
  Image,
  setNumber,
  Button,
  View,
  Text,
  LayoutAnimation,
  StyleSheet,
  TextInput,
  TouchableOpacity,
  FlatList,
} from 'react-native';
import {useNavigation} from '@react-navigation/native';
import {SelectList} from 'react-native-dropdown-select-list';
import Modal from 'react-native-modal';
import {SlideInDown} from 'react-native-reanimated';
import HomeScreen from './HomeScreen';
import Icon from 'react-native-vector-icons/FontAwesome';
import FilesScreen from './FilesScreen';
import {useMyContext} from '../Components/MyContext';
import {ScrollView} from 'react-native-gesture-handler';

const DetailsScreen: React.FC = () => {
  
  return (
    <View>
      <Text>Details</Text>
    </View>
       
  );
};
export default DetailsScreen;
const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#EFDBFE',
    alignItems: 'center',

    // justifyContent: 'center',

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
  },
});
