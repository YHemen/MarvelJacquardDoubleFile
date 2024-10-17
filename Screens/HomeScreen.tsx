// HomeScreen.tsx
import React, {useState} from 'react';
import {
  View,
  Text,
  Button,
  StyleSheet,
  FlatList,
  TouchableOpacity,
  Image,
  ActivityIndicator,
} from 'react-native';
import {SelectList} from 'react-native-dropdown-select-list';
import {useMyContext} from '../Components/MyContext';

const HomeScreen: React.FC<{navigation: any}> = ({navigation}) => {
  // const HomeScreen: React.FC = ({ navigation }) => {
  const {
    unLockMachine,
    rpmValue,
    sdFiles,
    setSdFiles,
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
    lockStatus,
    readDims,
    width,
    setWidth,
    height,
    setHeight,
    imageData,
    writeFileToSelect,
    ReadHeightwidth,
    
  } = useMyContext();
  const [selectedFile, setSelectedFile] = useState(null);
  const [files, setFiles] = useState([]);
  const [imageUri, setImageUri] = useState(null);
  const handleUnLockStatus = () => {
    unLockMachine();
  };
  const [selectedButton, setSelectedButton] = useState(null); // Track which button is selected
 
  const handleAction = (action) => {
    console.log(`${action} action performed`);
    // Add any additional operations based on the action here
  };

  // Function to handle button press
  const handlePress = async (btnval) => {
    if (currentDevice) {
      setSelectedButton(prevState => {
        const isCurrentlySelected = prevState === btnval; // Check if currently selected
        if (isCurrentlySelected) {
          handleAction('default'); // Handle deselect action
          return null; // Deselect
        } else {
          handleAction(btnval); // Handle select action
          return btnval; // Select the button
        }
      });
    }
  };
  
  return (
    <View style={styles.container}>
    <TouchableOpacity 
      style={[styles.button, selectedButton === 'allu' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('allu')}
    >
      <Text style={styles.buttonText}>
        {selectedButton === 'allu' ? 'Deselect' : 'Select All Up'}
      </Text>
    </TouchableOpacity>
    
    <TouchableOpacity 
      style={[styles.button, selectedButton === 'alld' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('alld')}
    >
      <Text style={styles.buttonText}>
        {selectedButton === 'alld' ? 'Deselect' : 'Select All Down'}
      </Text>
    </TouchableOpacity>
    
    <TouchableOpacity 
      style={[styles.button, selectedButton === '8up8d' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('8up8d')}
    >
      <Text style={styles.buttonText}>
        {selectedButton === '8up8d' ? 'Deselect' : 'Select 8 Up 8 Down'}
      </Text>
    </TouchableOpacity>

    <TouchableOpacity 
      style={[styles.button, selectedButton === '1up1d' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('1up1d')}
    >
      <Text style={styles.buttonText}>
        {selectedButton === '1up1d' ? 'Deselect' : 'Select 1 Up 1 Down'}
      </Text>
    </TouchableOpacity>
  </View>
  );
};
export default HomeScreen;
const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  button: {
    padding: 15,
    borderRadius: 5,
    alignItems: 'center',
    margin: 10,
  },
  selectedButton: {
    backgroundColor: '#b8219f', // Green for selected
  },
  unselectedButton: {
    backgroundColor: '#ddd', // Grey for unselected
  },
  buttonText: {
    fontSize: 18,
    color: '#fff',
  },
});