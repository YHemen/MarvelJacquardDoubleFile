import React, { useState, useEffect } from "react";
import {Modal, SafeAreaView, setNumber,Button, View, Text,LayoutAnimation, StyleSheet, TextInput, TouchableOpacity, ToastAndroid} from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import { useMyContext } from '../Components/MyContext';
import { useFocusEffect } from '@react-navigation/native';
const SettingsScreen:React.FC<{navigation: any}> = ({navigation}) => {
    // const HomeScreen: React.FC = ({ navigation }) => {
    const {
      unLockMachine,
      currentDevice,
      isConnected,
      readLockStatus,
      lockStatus,
      cnCount,
      setCnCount,
      cardCount,
      setCardCount,
      ttlHook,
    setTtlHook,
    writeClcnCount,
    designDir,
    setDesignDir,
    leftRightSelect,
    prevFile,
    } = useMyContext();
    const onColor = 'green';
  const offColor = 'red';
  const [isOn, setIsOn] = useState();
  const [isOff, setIsOff] = useState();
  const [isLockOn, setIsLockOn] = useState();
  const [isLockOff, setIsLockOff] = useState();
  const [runningDesign, setRunningDesign] = useState(false);
  const [modalVisible, setModalVisible] = useState(false);
  const [inputText, setInputText] = useState('');
  const [errorMessage, setErrorMessage] = useState('');
  const initialValue = 8;
const finalValue = 22;

useEffect(() => {
  // Show the overlay when the component mounts
  setModalVisible(true);
}, []);

const correctPassword = 'mySecret'; // Define your authentication value here
useFocusEffect(
  React.useCallback(() => {
    setModalVisible(true); // Show the modal whenever the screen is focused
    setInputText('');
  }, [])
);
const handleBackPress = () => {
  if (modalVisible) {
    setModalVisible(false); // Optional: Close the modal before navigating
    setInputText('');
    navigation.navigate('Home'); // Navigate to the Home screen
    return true; // Prevent closing the modal
  }
  return false; // Allow closing if the modal is not visible
};
const handleSubmit = () => {
  // Check if the input matches the correct password
  if (inputText === correctPassword) {
    setModalVisible(false); // Close the modal if the input is correct
    setErrorMessage(''); // Clear any error message
    setInputText(''); // Clear the input
    ToastAndroid.show("login Successful!", ToastAndroid.SHORT);
  } else {
    setErrorMessage('Invalid password. Please try again.'); // Show error message
    console.log('Invalid password. Please try again.'); // Show error message
    // Alert.alert(
    //   'Owner', // Title
    //   'Invalid password. Please try again.', // Message
    //   [{ text: 'OK', onPress: () => console.log('OK Pressed') }] // Button
    // );
  }
};

const handleIncrement = () => {
    // Find the next number in the sequence
    if (cardCount < finalValue) {
        let nextValue;

        if (cardCount === 0) {
          nextValue = 8;
      }
       else if (cardCount === 8) {
            nextValue = 12;
        } else if (cardCount === 12) {
            nextValue = 16;
        } else if (cardCount === 16) {
            nextValue = 18;
        } else if (cardCount === 18) {
            nextValue = 22;
        }

        if (nextValue) {
            setCardCount(nextValue); // Update cardCount directly
        }
    }
};

const handleDecrement = () => {
    // Find the previous number in the sequence
    let prevValue;

    if (cardCount === 22) {
        prevValue = 18;
    } else if (cardCount === 18) {
        prevValue = 16;
    } else if (cardCount === 16) {
        prevValue = 12;
    } else if (cardCount === 12) {
        prevValue = 8;
    } else if (cardCount === 8) {
      prevValue = 0;
  }

    if (prevValue) {
        setCardCount(prevValue); // Update cardCount directly
    }
}

  const handleConnectorIncrement = () => {
    setCnCount(prevCnCount => {
        if (prevCnCount < 16) {
            return prevCnCount + 1; // Increment if less than 16
        }
        return prevCnCount; // Return the same value if already 16
    });
};

  const handleConnectorDecrement = () => {
    setCnCount(prevCnCount => {
      if (prevCnCount > 1) {
          return prevCnCount - 1; // Increment if less than 16
      }
      return prevCnCount; // Return the same value if already 16
  });
  };
  
  const submitCardConCount = () => {
    const temp_str = '/';
    const cardCount_string = String(cardCount);
    const cnCount_string = String(cnCount);
    const myFile = prevFile.endsWith('.bmp') ? prevFile.replace('.bmp', '') : prevFile;
    const countvalue= myFile+temp_str+cardCount_string+"&"+ cnCount_string;
    writeClcnCount(countvalue);
    console.log("Current File", myFile);
    console.log("CardCount",cardCount);
    console.log("Connector Count", cnCount);
    console.log("countvalue", countvalue);
  };
  const lrMsg = (lrvalue) => {
    const lrstringvalue = String(lrvalue);
        console.log("state is ", lrstringvalue);
        leftRightSelect(lrstringvalue);
        setDesignDir(lrstringvalue);
  };
  const [day, setDay] = useState('');
  const [month, setMonth] = useState('');
  const [year, setYear] = useState('');
  const [formattedDate, setFormattedDate] = useState('');
  const handleDateSubmit = () => {
    const date = new Date(`${year}-${month}-${day}`);
    
    if (!isNaN(date)) {
        const formatted = date.toLocaleDateString(); // Format the date
        setFormattedDate(formatted); 
    } else {
      alert('Invalid date. Please check your inputs.');
    }
  };
  const changeCustName =() =>{
    ToastAndroid.show("Customer Name changed!", ToastAndroid.SHORT);
  }
    return(
        <SafeAreaView style={styles.container}>
            <View><Text style={{fontSize:20}}>User Settings</Text></View>
            <View style={{flexDirection: "row", marginBottom:10}} >
                
            <View style={styles.inputContainer}>
        <TextInput
          style={{width:120}}
          placeholder="Customer Name"
        />
        <Icon name="user" size={20} color="#812892" style={styles.icon} />
      </View>
      <View style={styles.inputContainer}>
        <TextInput
          style={{width:120}}
          placeholder="Password"
        />
        <Icon name="lock" size={20} color="#812892" style={styles.icon} />
      </View>

      <TouchableOpacity onPress={changeCustName} style={{alignItems: 'center',justifyContent: 'space-evenly', paddingHorizontal: 10, backgroundColor:'#812892',width: 40,
            height: 40,
            borderRadius: 5,
            borderColor: 'purple',
            borderWidth:1,
            marginLeft: 10,
            marginRight: 10,
            padding: 10,
            marginTop:10,}}>
      <View style={{flexDirection:"row",alignItems:'center'}}>
        <Icon name="save" size={20} color="#EFDBFE" />
      
      </View>
       
      </TouchableOpacity></View>
      <View><Text style={{fontSize:20}}>Hook Settings</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-evenly', paddingHorizontal: 10 }}>
        <Text style={{ textAlign: 'left', marginRight: 10 }}>Card Count     :</Text>
      <TouchableOpacity onPress={handleDecrement}>
        <Icon name="chevron-down" size={30} color="#812892" />
      </TouchableOpacity>
      <TextInput
            keyboardType="number-pad"style={{ width: 50, borderRadius: 5, fontSize: 24, 
fontWeight: 'bold', color: '#812892', textAlign: 'center', 
marginHorizontal: 10 }}>
            {' '}
            {cardCount}
          </TextInput>
      <TouchableOpacity onPress={handleIncrement} >
        <Icon name="chevron-up" size={30} color="#812892" />
      </TouchableOpacity>
      

    </View>
    
      
      <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
      <Text>Connector Count: </Text>
        <TouchableOpacity onPress={handleConnectorDecrement} >
        <Icon name="chevron-down" size={30} color="#812892" /> 
        </TouchableOpacity>
        {/* <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {incrementCount.toString()}</TextInput> */}
        <TextInput
            keyboardType="number-pad"style={{ width: 50, borderRadius: 5, fontSize: 24, 
fontWeight: 'bold', color: '#812892', textAlign: 'center', 
marginHorizontal: 10 }}>
            {' '}
            {cnCount}
          </TextInput>
        <TouchableOpacity onPress={handleConnectorIncrement}  >
        <Icon name="chevron-up" size={30} color="#812892" /> 
        </TouchableOpacity> 
       
        
      
        
    </View>
    <View style={{ flexDirection:'row',flex: 1, justifyContent: 'space-around', alignItems: 'center', marginBottom:10}}>
        <Text>TOTAL HOOKS:</Text>
        <Text>{ttlHook}</Text>
        <TouchableOpacity onPress={submitCardConCount} style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 1, marginLeft: 30}} >
        {/* <Icon name="chevron-up" size={30} color="#812892" />  */}
        <Text style={{color:'white'}}>Save</Text>
        </TouchableOpacity>
    </View>
    
    <View><Text style={{fontSize:20}}>Design Left and Right</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
        <View>
        <TouchableOpacity style={{height: 40, width: 150, borderRadius: 15, borderWidth: 1,overflow: 'hidden',padding:1, borderColor: isOn?onColor:offColor}} onPress={()=>{LayoutAnimation.easeInEaseOut();setIsOn(!isOn); lrMsg(isOn ? 1 : 2);}}>
                <View style={{borderRadius: 15,alignItem:'center',justifyContent: 'center',height: '100%', width: '50%', backgroundColor:isOn?onColor:offColor, alignSelf: isOn?'flex-end':'flex-start'}}><Text style={{alignItem:'center',justifyContent:'center',color:'white',fontSize:12, fontWeight:'800',fontStyle:'normal'}}>{isOn?'LEFT-RIGHT':'RIGHT-LEFT'}</Text></View>
                </TouchableOpacity>
    </View>
    </View>

    <View><Text style={{fontSize:20, marginBottom:20}}>Set Running Lock Date</Text></View>
    <View style={styles.container}>
      <View style={styles.inputRow}>
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="DD"
          maxLength={2}
          value={day}
          onChangeText={setDay}
        />
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="MM"
          maxLength={2}
          value={month}
          onChangeText={setMonth}
        />
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="YYYY"
          maxLength={4}
          value={year}
          onChangeText={setYear}
        />
        <TouchableOpacity onPress={handleDateSubmit} style={{backgroundColor:'purple', width: 80, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 1, marginLeft: 20}} >
        {/* <Icon name="chevron-up" size={30} color="#812892" />  */}
        <Text style={{color:'white'}}>Submit</Text>
        </TouchableOpacity>
      </View>
      
    </View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around'}}>
         <Text style={{marginRight: 10,justifyContent:'center',alignItems:'center', fontSize:20}}>Lock Date:</Text> 
    <Text style={{justifyContent:'center',alignItems:'center', fontSize:20}}>{formattedDate.toString()}</Text>
    </View>
    <View style={styles.container} >
    
     
    </View>
    <View>
        <TouchableOpacity style={{height: 40, width: 120, borderRadius: 25, borderWidth: 1,overflow: 'hidden',padding:1, borderColor: isLockOn?onColor:offColor}} onPress={()=>{LayoutAnimation.easeInEaseOut();setIsLockOn(!isLockOn);}}>
                <View style={{borderRadius: 25,alignItem:'center',justifyContent: 'center',height: '100%', width: '50%', backgroundColor:isLockOn?onColor:offColor, alignSelf: isLockOn?'flex-end':'flex-start'}}>
                    <Text style={{alignItem:'center',justifyContent:'center',color:'white',fontSize:12, fontWeight:'800',fontStyle:'normal',marginLeft: 16}}>{isLockOn?<Icon name="lock" size={30} color="#ffffff" />:<Icon name="unlock" size={30} color="#ffffff" />}</Text>
                </View>
                </TouchableOpacity>
    </View> 
    <Modal
        transparent={true}
        animationType="slide"
        visible={modalVisible}
        onRequestClose={handleBackPress}
      >
        <View style={styles.overlay}>
          <View style={styles.modalContent}>
            <TextInput
              style={styles.textInput}
              placeholder="Enter Password"
              value={inputText}
              onChangeText={setInputText}
              secureTextEntry 
            />
            {errorMessage ? <Text style={styles.errorText}>{errorMessage}</Text> : null}
            <TouchableOpacity style={styles.btn} onPress={handleSubmit}>
              <Text style={styles.buttonText}>Submit</Text>
            </TouchableOpacity>
          </View>
        </View>
      </Modal>
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
    label: {
        fontSize: 16,
        marginBottom: 5,
      },
      inputRow: {
        flexDirection: 'row',
        justifyContent: 'center',
        alignItems: 'center',
        marginBottom: 20,
      },
      input: {
        height: 40,
        width: 60, // Adjust width as needed
        borderColor: '#ccc',
        borderWidth: 1,
        borderRadius: 5,
        paddingHorizontal: 5,
        marginHorizontal: 2, // Space between inputs
        textAlign: 'center',
      },
      button: {
        backgroundColor: 'steelblue',
        padding: 10,
        borderRadius: 5,
        alignItems: 'center',
      },
      buttonText: {
        color: '#fff',
        fontSize: 16,
      },
      result: {
        marginTop: 20,
        fontSize: 18,
      },
      
      inputContainer: {
        flex: 1,
        marginHorizontal: 2, // Space between inputs
        flexDirection: 'row',
    alignItems: 'center',
    borderWidth: 1,
    borderColor: '#ccc',
    borderRadius: 5,
    paddingHorizontal: 2,
    width: '100%',
    height: 45,
    marginTop: 10
      },
      box: {
        height: 500,
        width: 350,
        justifyContent: 'center',
        alignItems: 'center',
        borderWidth: 2, // Set the border width
        borderColor: '#812892', // Set the border color
        borderRadius: 10, // Set the border radius (optional)
        margin: 10, // Space between boxes
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
      textInput: {
        height: 40,
        borderColor: 'gray',
        borderWidth: 1,
        marginBottom: 15,
        paddingHorizontal: 10,
      },
      errorText:{
        color: 'red',
        fontWeight: 'bold',
      },
      btn: {
        backgroundColor: '#812892',
        padding: 8,
        borderRadius: 5,
        alignItems: 'center',
      },
})