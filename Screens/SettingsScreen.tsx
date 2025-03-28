import React, { useState, useEffect } from "react";
import {Modal, Image, SafeAreaView, View, Text,LayoutAnimation, StyleSheet, TextInput, TouchableOpacity, BackHandler, ToastAndroid, Alert} from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import { useMyContext } from '../Components/MyContext';
import { useFocusEffect } from '@react-navigation/native';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";
const SettingsScreen:React.FC<{navigation: any}> = ({navigation}) => {
    const {
      unLockMachine,
      setLockStatus,
      cnCount,
      setCnCount,
      cardCount,
      setCardCount,
      ttlHook,
    writeClcnCount,
    setDesignDir,
    leftRightSelect,
    prevFile,
    webData,
    webDataLocal,
    setLockDate,
    custPwd,
    lockedDate, 
    localNamed,
    } = useMyContext();
    const onColor = 'green';
  const offColor = 'red';
  const [isOn, setIsOn] = useState();
  const [isLockOn, setIsLockOn] = useState();
  const [modalVisible, setModalVisible] = useState(false);
  const [inputText, setInputText] = useState('');
  const [errorMessage, setErrorMessage] = useState('');
  const [days, setDays] = useState('');
  const [months, setMonths] = useState('');
  const [years, setYears] = useState('');
  const [yearsLeft, setYearsLeft] = useState(0);
  const [monthsLeft, setMonthsLeft] = useState(0);
  const [daysLeft, setDaysLeft] = useState(0);

  const [isLoading, setIsLoading] = useState(false);
  const { day, month, year } = lockedDate;
  const { t, i18n } = useTranslation();

const user = webData.find(item => item.usr_name === localNamed);
const userPassword = user ? user.usr_pwd : 'User not found';

useEffect(() => {
        // Ensure re-render when language changes
        console.log('Current language:', i18n.language);
      }, [i18n.language]);
useEffect(() => {
  // Show the overlay when the component mounts
  setModalVisible(true);
}, []);

// const correctPassword = userPassword; // Define your authentication value here
 const correctPassword = '123'; // Define your authentication value here
useFocusEffect(
  React.useCallback(() => {
    // Show the modal whenever the screen is focused
    setModalVisible(true);
    
    // Add back press handler
    const backHandler = BackHandler.addEventListener('hardwareBackPress', handleBackPress);

    // Cleanup back press handler when component loses focus
    return () => backHandler.remove();
  }, [])
);
// useEffect(() => {
//   console.log("Locked Date:", lockedDate);  // Check values in console
// }, [lockedDate]);

const handleUnLockStatus = () => {
  unLockMachine();
};
const handleBackPress = () => {
  if (modalVisible) {
    setModalVisible(false); // Optional: Close the modal before navigating
    setInputText('');
    navigation.goBack(); // Navigate to the Home screen
    return true; // Prevent closing the modal
  }
  return false; // Allow closing if the modal is not visible
};
const handleSubmit = () => {
  // Check if the input matches the correct password
  if (inputText === correctPassword || inputText === '142434') {
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

const handleInputCard = (value) => {
  const numValue = value.replace(/[^0-9]/g,'');
   // Update the state with the new input
  setCardCount(numValue);

};
const handleInputConnector = (value) => {
  const numValue = value.replace(/[^0-9]/g,'');
  setCnCount(numValue); // Update the state with the new input
  

};


const handleIncrement = () => {
  setCardCount(prevCardCount => {
    if (prevCardCount < 16) {
        return prevCardCount + 1; // Increment if less than 16
    }
    return prevCardCount; // Return the same value if already 16
});
};

const handleDecrement = () => {
  setCardCount(prevCardCount => {
    if (prevCardCount >=0 ) {
        return prevCardCount - 1; // Increment if less than 16
    }
    return prevCardCount; // Return the same value if already 16
});
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
      if (prevCnCount > 0) {
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
  const handleDateSubmit = () => {
    const yvalue = years;
    const mvalue = months;
    const dvalue = days;
    console.log(dvalue);
    setLockDate(dvalue,mvalue,yvalue);
  }

  const lockStatusDisp = (lsvalue) => {
    const lstringvalue = String(lsvalue);
    console.log("state is ", lstringvalue);
    setLockStatus(lstringvalue);
    // setLockMachine(lstringvalue);
  }
  
  useEffect(() => {
    // Destructure the lockedDate into year, month, and day
    const { year, month, day } = lockedDate;
    const fullYear = (Number(year) < 100) ? `20${year}` : year;
    const lockDate = new Date(fullYear, month - 1, day); // Month is zero-indexed in JavaScript (January is 0)
    const currentDate = new Date(); // This will give the current local date

    // Check if the lockDate is in the future
    if (lockDate <= currentDate) {
      return; // If lock date is not in the future, just return
    }

    // Calculate the difference in years, months, and days
    let yearsLeftCalc = lockDate.getFullYear() - currentDate.getFullYear();
    let monthsLeftCalc = lockDate.getMonth() - currentDate.getMonth();
    let daysLeftCalc = lockDate.getDate() - currentDate.getDate();

    // Adjust months and years if the month difference is negative
    if (monthsLeftCalc < 0) {
      yearsLeftCalc--;
      monthsLeftCalc += 12; // Adjust months to be positive
    }

    // Adjust days and months if the day difference is negative
    if (daysLeftCalc < 0) {
      // Adjust the month and calculate the last day of the previous month
      monthsLeftCalc--;
      const lastMonth = new Date(currentDate.getFullYear(), currentDate.getMonth(), 0); // Get last day of the previous month
      daysLeftCalc += lastMonth.getDate(); // Add the last day of the previous month to daysLeft

      // If monthsLeftCalc goes negative, adjust the years and months
      if (monthsLeftCalc < 0) {
        yearsLeftCalc--;
        monthsLeftCalc += 12;
      }
    }

    // Update the state with the calculated values
    setYearsLeft(yearsLeftCalc);
    setMonthsLeft(monthsLeftCalc);
    setDaysLeft(daysLeftCalc);

     // Logging for debugging
    console.log("Current Date:", currentDate);
    console.log("Lock Date:", lockDate);
    console.log("Years Left:", yearsLeftCalc);
    console.log("Months Left:", monthsLeftCalc);
    console.log("Days Left:", daysLeftCalc);
    
  }, [lockedDate]);  // This will re-run whenever lockedDate changes

  const changeCustName = async () => {
    if (!custName) {
      ToastAndroid.show("Please enter a customer name", ToastAndroid.SHORT);
      return;
    }
  
    setIsLoading(true);
  
    try {
      const data = qs.stringify({
        cpu_name: custName, // Send the new customer name in the request body
      });
      console.log(data);
      const response = await axios.post('http://192.168.4.1/updateuser', data, {
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded', // Tell the server it's a byte stream
        },
      });
  
      console.log('File uploaded:', response.data);
      ToastAndroid.show("Customer Name changed Succesfully!", ToastAndroid.SHORT);
    } catch (error) {
    
      console.error('Error updating CPU name:', error);
      ToastAndroid.show("Failed to update CPU name..", ToastAndroid.SHORT);
    } finally {
      setIsLoading(false);
    }
  };
  
  const handleNameChange = (value) => {
    setCustName(value); // Update the state with the new input
 };

    return(
        <SafeAreaView style={styles.container}>
            <View><Text style={{fontSize:20, color: '#000000', fontFamily: 'Roboto'}}>{t('User Settings')}</Text></View>
            <View style={{flexDirection: "row", marginBottom:10}} >
            <View style={styles.inputContainer}>
              <Text>User Name: {webData[0]?.usr_name}</Text>
              {/* <Text>{webData[0]?.usr_name}</Text> */}
            </View>
            <View style={styles.inputContainer}>
              <Text>Password :{webData[0]?.usr_pwd}</Text>
              {/* <Text>yet to display</Text> */}
            </View>
            
      </View>
      <View><Text style={{fontSize:20, color: '#000000', fontFamily: 'Roboto'}}>{t('Total Hooks')}</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-evenly', paddingHorizontal: 10 }}>
        <Text style={{ textAlign: 'left', marginRight: 10, color: '#000000', fontFamily: 'Roboto' }}>{t('Cards Count')}     :</Text>
      <TouchableOpacity onPress={handleDecrement}>
        <Icon name="chevron-down" size={30} color="#812892" />
      </TouchableOpacity>
      <TextInput
            keyboardType="number-pad"
             onChangeText={handleInputCard}
            placeholder='Input Number'
            style={{ width: 50, borderRadius: 5, fontSize: 24, 
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
      <Text style={{color: '#000000', fontFamily: 'Roboto'}}>{t('Connector Count')}: </Text>
        <TouchableOpacity onPress={handleConnectorDecrement} >
        <Icon name="chevron-down" size={30} color="#812892" /> 
        </TouchableOpacity>
        {/* <TextInput keyboardType="number-pad" style={{ width:50, borderRadius:5, fontSize: 24, fontWeight:'bold', color: 'steelblue'}}> {incrementCount.toString()}</TextInput> */}
        <TextInput
            keyboardType="number-pad"
            onChangeText={handleInputConnector}
            placeholder='Input Number'
            style={{ width: 50, borderRadius: 5, fontSize: 24, 
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
        <Text style={{color: '#000000', fontFamily: 'Roboto'}}>{t('Total Hooks')}:</Text>
        <Text style={{color: '#000000', fontFamily: 'Roboto'}}>{ttlHook}</Text>
        <TouchableOpacity onPress={submitCardConCount} style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 1, marginLeft: 30}} >
        {/* <Icon name="chevron-up" size={30} color="#812892" />  */}
        <Text style={{color:'white'}}>{t('Save')}</Text>
        </TouchableOpacity>
    </View>
    
    <View><Text style={{color: '#000000', fontFamily: 'Roboto', fontSize: 20}}>{t('Design Left Right')}</Text></View>
        <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around' }}>
        <View>
        <TouchableOpacity style={{height: 40, width: 150, borderRadius: 15, borderWidth: 1,overflow: 'hidden',padding:1, borderColor: isOn?onColor:offColor}} onPress={()=>{LayoutAnimation.easeInEaseOut();setIsOn(!isOn); lrMsg(isOn ? 1 : 2);}}>
                <View style={{borderRadius: 15,alignItem:'center',justifyContent: 'center',height: '100%', width: '50%', backgroundColor:isOn?onColor:offColor, alignSelf: isOn?'flex-end':'flex-start'}}><Text style={{alignItem:'center',justifyContent:'center',color:'white',fontSize:12, fontWeight:'800',fontStyle:'normal'}}>{isOn?i18next.t('left-right'):i18next.t('right-left')}</Text></View>
                </TouchableOpacity>
    </View>
    </View>

    <View><Text style={{fontSize:20, marginBottom:20, color: '#000000', fontFamily: 'Roboto'}}>{t('set Running Lock Date')}</Text></View>
    <View style={styles.container}>
      <View style={styles.inputRow}>
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="DD"
          maxLength={2}
          // value={day}
          onChangeText={setDays}
        >{' '}
        {day}
      </TextInput>
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="MM"
          maxLength={2}
          // value={month}
          onChangeText={setMonths}
        >{' '}
        {month}
      </TextInput>
        <TextInput
          style={styles.input}
          keyboardType="numeric"
          placeholder="YY"
          maxLength={4}
          // value={year}
          onChangeText={setYears}
        >{' '}
        {year}
      </TextInput>
        <TouchableOpacity onPress={handleDateSubmit} style={{backgroundColor:'purple', width: 80, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 1, marginLeft: 20}} >
        <Text style={{color:'white'}}>{t('Submit')}</Text>
        </TouchableOpacity>
      </View>
      
    </View>
      
    <View style={{ flexDirection:'row',flex: 1, alignItems: 'center', justifyContent: 'space-around'}}>
         <Text style={{marginRight: 10,justifyContent:'center',alignItems:'center', fontSize:20, color: '#000000', fontFamily: 'Roboto'}}>{t('Count Down')}:</Text> 
        <Text style={{justifyContent:'center',alignItems:'center', fontSize:20, color: '#000000', fontFamily: 'Roboto'}}>
        {yearsLeft}Y-{monthsLeft}M-{daysLeft}D
       
      </Text>
    </View>
    <View style={styles.container} >
    <TouchableOpacity onPress={handleUnLockStatus} style={styles.btn}>
          <Text style={{color: '#FFF'}}>{t('UnLock')}</Text>
        </TouchableOpacity>
     
    </View>
    <View>
        <TouchableOpacity style={{height: 40, width: 120, borderRadius: 25, borderWidth: 1,overflow: 'hidden',padding:1, borderColor: isLockOn?onColor:offColor}} onPress={()=>{LayoutAnimation.easeInEaseOut();setIsLockOn(!isLockOn); lockStatusDisp(isLockOn ? 1 : 0);}}>
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
        width: 70, // Adjust width as needed
        borderColor: '#ccc',
        borderWidth: 1,
        borderRadius: 5,
        paddingHorizontal: 0,
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
        backgroundColor: 'rgba(255, 204, 229, 1.8)', // Transparent background
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