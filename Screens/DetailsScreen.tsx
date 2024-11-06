import React, { useState, useEffect } from 'react';
import { View, Text, TextInput, Button, Modal, StyleSheet, Alert, ToastAndroid } from 'react-native';
import { useFocusEffect } from '@react-navigation/native';

const DetailsScreen = ({ navigation }) => {
  const [modalVisible, setModalVisible] = useState(false);
  const [inputText, setInputText] = useState('');
  const [errorMessage, setErrorMessage] = useState('');
  useEffect(() => {
    // Show the overlay when the component mounts
    setModalVisible(true);
  }, []);

  const correctPassword = 'mySecret'; // Define your authentication value here
  useFocusEffect(
    React.useCallback(() => {
      setModalVisible(true); // Show the modal whenever the screen is focused
    }, [])
  );
  const handleBackPress = () => {
    if (modalVisible) {
      setModalVisible(false); // Optional: Close the modal before navigating
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
  const data = [
    { col1: 'Hooks', col2: '448, 640, 960, 1248, 1280, 1344, 1440, 1536, 2688' },
    { col1: 'Module type', col2: 'M5' },
    { col1: 'Lift', col2: 'Double lift type' },
    { col1: 'Drive', col2: 'Chain & Timing pulley with high quality material' },
    { col1: 'Speed', col2: 'Up to 375 RPM' },
    { col1: '1536-Hook', col2: '0.60 KW' },
    { col1: 'Display', col2: '20 Character x 4 line LCD display' },
    { col1: 'Shedding range', col2: '75 to 120 mm' },
    { col1: 'FRAME STRUCTURE', col2: 'Mild Steel' },
    { col1: 'HEIGHT', col2: 'Low Height (Compilable to install in lower height shed)' },
  ];

    const items = [
      'High Performance monocontrollers for optimum processing speed',
      'Unlimited Picks for single design in all jacquard',
      'Compatible with all types of design formats and platforms like : .BMP, .EP, .PAT, JCS., UPT., etc…',
      'Facility to put cut-mark at specific length for the elimination of length measurement for cutting.',
      'High speed USB port to Transfer Design / Data from Computer to Jacquard',
      'Pattern your design with desired repeat of each and every design (string) Separately',
      'Auto function to change design automatically as per defined sequence on completion of running design',
      '20 Character x 4 line LCD display to display message like Design Number, Repeat, Pick etc.',
      '32 GB Internal Storage that can load 64000 picks per Design',
      '578 Hook to 768 Hook – 0.35 KW, 864 Hook to 960 Hook – 0.60 KW, 1056 Hook to 1536 Hook – 072 KW,2432 Hook to 2688 Hook – 1.20 KW',
    ];
  return (
    
    
    <View style={styles.container}>
      <View style={styles.header}>
        <Text style={styles.headerText}>Client Name:</Text>
        <Text style={styles.headerText}>SreeTextiles</Text>
      </View>
       <View style={styles.header}>
        <Text style={styles.headerText}>Content</Text>
        <Text style={styles.headerText}>Specification</Text>
      </View>
      {data.map((item, index) => (
        <View key={index} style={styles.row}>
          <Text style={styles.cell}>{item.col1}</Text>
          <Text style={styles.cell}>{item.col2}</Text>
        </View>
      ))}
      {/* {items.map((item, index) => (
        <View key={index} style={styles.listItem}>
          <Text style={styles.bullet}>•</Text>
          <Text style={styles.itemText}>{item}</Text>
        </View>
      ))} */}
      <View><Text>Marvel Jacquards Pvt LTD.</Text></View>
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
            <Button style={styles.btn} title="Submit" onPress={handleSubmit} />
          </View>
        </View>
      </Modal>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
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
    width: '70%',
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
    backgroundColor: '#3B71CA',
  },
  header: {
    flexDirection: 'row',
    backgroundColor: '#f0f0f0',
    padding: 10,
    marginBottom: 5,
  },
  headerText: {
    flex: 1,
    fontWeight: 'bold',
  },
  row: {
    flexDirection: 'row',
    padding: 10,
    borderBottomWidth: 1,
    borderBottomColor: '#ddd',
  },
  cell: {
    flex: 1,
  },
});

export default DetailsScreen;
