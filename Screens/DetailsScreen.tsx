// screens/DetailsScreen.js

import React, {useState} from 'react';
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
  const onColor = 'green';
  const offColor = 'red';
  const [isOn, setIsOn] = useState();
  const [isOff, setIsOff] = useState();
  const [runningDesign, setRunningDesign] = useState(false);
  const navigation = useNavigation();
  // const [number, setNumber] = useState(500);
  const {
    data,
    sdFiles,
    rpmValue,
    setSdFiles,
    setRpmValue,
    currentDevice,
    isConnected,
    writeData,
    readData,
    strRpm,
    setStrRpm,
    strFiles,
    sdFilesReadFromClient,
    readLockStatus,
    readSdFiles,
    char1Data,
    setChar1Data,
    char2Data,
    setChar2Data,
    char3Data,
    setChar3Data,
    char4Data,
    setChar4Data,
    pCount,
    setPCount,
    writeFileToSelect,
    writeHeightToChange,
    height,
    setHeight,
    width,
    setWidth,
    stringToBytes,
    prevFile,
    setPrevFile,
  } = useMyContext();
 
  
  const handleInputChange = (value) => {
    const numValue = value.replace(/[^0-9]/g,'');
    setPCount(numValue); // Update the state with the new input
    // setPCount(value);
    writeHeightToChange(pCount);
  };
  const handleIncrement = () => {
    
    setPCount(prevHeight => {
      const incrementedHeight = prevHeight + 1;
      // const cpCount = String.fromCharCode(incrementedHeight);
      // console.log('converted after Increment String:', cpCount);
      // console.log(pCount);
      // Write the byte array back to ESP32
      writeHeightToChange(incrementedHeight);

      return incrementedHeight; // Return the new height for state update
      
    });
      // setPCount(prevCount => prevCount + 1);
      // writeHeightToChange(pCount);
      // writeHeightToChange(pCount);
    
  };
  const handleDecrement = () => {
    // setInputValue((prev) => (parseInt(prev) + 1).toString()); // Increment value and convert to string
    setPCount(prevHeight => {
      const decrementdHeight = prevHeight - 1;
      // const cpCount = String.fromCharCode(decrementdHeight);
      // console.log('converted after Decrement String:', cpCount);
      // console.log(pCount);

      writeHeightToChange(decrementdHeight);

      return decrementdHeight; // Return the new height for state update
    });
    // writeHeightToChange(pCount);
  };
  const [bodyFile, setBodyFile] = React.useState('');
  const [borderFile, setBorderFile] = React.useState('');
  const [selected, setSelected] = React.useState();
  

  const handleSelect = value => {
    setPrevFile(value);
    writeFileToSelect(value);
    setPCount(0);
    // console.log(value);
  };

  // Original Convert sdFiles to the format required by SelectList
  const dropdownData = sdFiles.map(file => ({
    key: file, // Unique key for each item
    value: file, // Display value for each item
  }));
  // Experimental Convert sdFiles to the format required by SelectList
  const EdropdownData = sdFiles.map((file, index) => ({
    key: index + 1, // Unique key for each item starting from 1
    value: file,    // Display value for each item
  }));
  //console.log(EdropdownData);
  // Function to render each item
  const renderItem = ({item}) => (
    <View style={styles.itemContainer}>
      <Text style={styles.itemText}>{item.name}</Text>
    </View>
  );

  return (
    <SafeAreaView style={styles.container}>
      <View
        style={{
          height: 300,
          paddingTop: 10,
          paddingBottom: 30,
          position: 'relative',
        }}>
        <View style={{alignSelf: 'center', alignItems: 'center'}}>
          <View>
            <Text style={{fontSize: 20, fontWeight: 'bold'}}>BODY</Text>
          </View>
          {/* <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View> */}
        </View>

        <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 30,
          }}>
          <TouchableOpacity onPress={handleDecrement}>
            <Icon name="chevron-down" size={30} color="#000" />
          </TouchableOpacity>
          <TextInput
            keyboardType="number-pad"
            // value={pCount}
            onChangeText={handleInputChange}
            placeholder='Input Number'
            style={{
              width: 60,
              borderRadius: 5,
              fontSize: 24,
              fontWeight: 'bold',
              color: 'steelblue',
            }} >
            {' '}
            {pCount}
          </TextInput>

{/* <TextInput
        keyboardType="number-pad"
        value={pCount} // Bind the value to pCount
        onChangeText={handleInputChange} // Update state on text change
        placeholder="Enter PicNumber" // Placeholder text
        
      /> */}
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#000" textAlign="right" />
          </TouchableOpacity>
        </View>
        <View>
          <Text style={{textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>
            Width: {width} / height: {height}
          </Text>
        </View>
        <View>
          {/* <SelectList setSelected={(val) => setSelected(val)} data={datas} save="value" dropdownStyles={{height: 150}} />  */}
          {/* <Text style={styles.selectedItem}>Selected Item: {selected}</Text> */}
          <SelectList
            setSelected={handleSelect}
            data={dropdownData}
            save="key"
            // value= {prevFile}
            // placeholder={"Select a file"}
            placeholder={prevFile ? prevFile : "Select File"}
            boxStyles={styles.selectBox}
            dropdownStyles={styles.dropdown}
            dropdownTextStyles={styles.dropdownText}
            placeholderStyle={styles.placeholder}
            selected={prevFile}
          />
          {/* {currentDevice ? (
                  <ActivityIndicator size="large" color="#0000ff" />
                ) : ( */}
          {/* <FlatList
            data={sdFiles}
            renderItem={renderItem}
            keyExtractor={(item) => item.id}
            ListEmptyComponent={<Text>No images available</Text>}
            // ListHeaderComponent={<Text style={styles.header}>My List</Text>}
          /> */}
          <ScrollView>
          <Image
            source={require('../assets/images/body.bmp')}
            style={{height: 156, width: 225}}
          />
          
        </ScrollView>
        </View>
        {/* <ScrollView>
          <Image
            source={require('../assets/images/LOGO.png')}
            style={{height: 306, width: 225}}
          />
          
        </ScrollView> */}
      </View>

      {/* <View style={{height: 300, paddingTop: 20, paddingBottom: 30}}>
         <View><Text style={{fontSize:20}}>Hook Settings</Text></View> 
        <View style={{alignSelf: 'center', alignItems: 'center'}}>
          <View>
            <Text style={{fontSize: 20, fontWeight: 'bold'}}>BORDER-1</Text>
          </View>
        </View>

        <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 30,
          }}>
          <TouchableOpacity onPress={handleDecrement}>
            <Icon name="chevron-down" size={30} color="#000" />
          </TouchableOpacity>
          <TextInput
            keyboardType="number-pad"
            style={{
              width: 50,
              borderRadius: 5,
              fontSize: 24,
              fontWeight: 'bold',
              color: 'steelblue',
            }}>
            {' '}
            {pCount}
          </TextInput>
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#000" textAlign="right" />
          </TouchableOpacity>
        </View>
        <View>
          <Text style={{textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>
            Width: 1056 / height: 2816
          </Text>
        </View>
        <View> */}
          {/* <SelectList
                setSelected={val => setSelected(val)}
                data={datas}
                save="value"
                dropdownStyles={{height: 150}}
              /> */}
          {/* <Text style={styles.selectedItem}>Selected Item: {selected}</Text> */}
          {/* <SelectList
            setSelected={handleSelect}
            data={dropdownData}
            save="key"
            placeholder="Select a file"
            boxStyles={styles.selectBox}
            dropdownStyles={styles.dropdown}
            dropdownTextStyles={styles.dropdownText}
            placeholderStyle={styles.placeholder}
          /> */}
          {/* {currentDevice ? (
        <ActivityIndicator size="large" color="#0000ff" />
      ) : ( */}
          {/* <FlatList
            data={sdFiles}
            renderItem={renderItem}
            keyExtractor={item => item.id}
            ListEmptyComponent={<Text>No images available</Text>}
            // ListHeaderComponent={<Text style={styles.header}>My List</Text>}
          />
        </View>
        <ScrollView>
          <Image
            source={require('../assets/images/border.bmp')}
            style={{height: 126, width: 225}}
          />
        </ScrollView>
      </View> */}

      <View
        style={{
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          paddingHorizontal: 30,
          paddingVertical: 25,
        }}>
        <View>
          <Text style={{fontSize: 30, fontWeight: 'bold', color: 'purple'}}>
            RPM:{rpmValue}
          </Text>
        </View>
        <View
          style={{
            backgroundColor: 'pink',
            borderRadius: 60,
            width: 45,
            alignSelf: 'center',
            alignContent: 'center',
          }}></View>
        {/* <TouchableOpacity onPress={()=>{navigation.navigate(FilesScreen)}}>
              <Text style={{backgroundColor: 'pink', borderRadius: 50, width: 45, height: 45, paddingLeft: 8, paddingTop: 5}}><Icon name="upload" size={30} color="#000" /></Text>
        </TouchableOpacity> */}
      </View>
    </SafeAreaView>
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
