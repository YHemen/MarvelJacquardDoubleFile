import React ,{useState, useEffect} from 'react';
import {
  View,
  Text,
  StyleSheet,
  Dimensions,
  TouchableOpacity,
} from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import {useMyContext} from '../Components/MyContext';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";
const TestRunScreen = () => {
  const {
    currentDevice,
    isConnected,
    writeData,
  } = useMyContext();
  const { t, i18n } = useTranslation();
  const [selectedButton, setSelectedButton] = useState(null); // Track which button is selected
 useEffect(() => {
       // Ensure re-render when language changes
       console.log('Current language:', i18n.language);
     }, [i18n.language]);
  // Function to handle button press
  const handlePress = async (btnval1) => {
    // const btnval = this.btnval1;
    if (currentDevice) {
      setSelectedButton(prevState => {
        const isCurrentlySelected = prevState === btnval1; // Check if currently selected
        if (isCurrentlySelected) {
          writeData('default'); // Handle deselect action
          return null; // Deselect
        } else {
          writeData(btnval1); // Handle select action
          return btnval1; // Select the button
        }
      });
    }
  };
  return (
    <View style={styles.container}>
      <View style={styles.grid}>
      <TouchableOpacity 
      style={[styles.item, selectedButton === 'allu' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('allu')}
    >
      <Text style={styles.itemText}>
        {selectedButton === 'allu' ? 'Deselect' : i18next.t('All Up')}
      </Text>
    </TouchableOpacity>
    
    <TouchableOpacity 
      style={[styles.item, selectedButton === 'alld' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('alld')}
    >
      <Text style={styles.itemText}>
        {selectedButton === 'alld' ? 'Deselect' : i18next.t('All Down')}
      </Text>
    </TouchableOpacity>
    
    <TouchableOpacity 
      style={[styles.item, selectedButton === '8up8d' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('8up8d')}
    >
      <Text style={styles.itemText}>
        {selectedButton === '8up8d' ? 'Deselect' : i18next.t('8 Up 8 Down')}
      </Text>
    </TouchableOpacity>

    <TouchableOpacity 
      style={[styles.item, selectedButton === '1up1d' ? styles.selectedButton : styles.unselectedButton]} 
      onPress={() => handlePress('1up1d')}
    >
      <Text style={styles.itemText}>
        {selectedButton === '1up1d' ? 'Deselect' : i18next.t('1 UP 1 Down')}
      </Text>
    </TouchableOpacity>
      </View>
    </View>
  );
};

const {width} = Dimensions.get('window');
const itemSize = width / 2; // Divide screen width by 3 to fit items

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#EFDBFE',
  },
  grid: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    width: width,
    justifyContent: 'space-between',
    paddingStart: 40,
    paddingEnd: 40,
    paddingTop: 10,
    paddingBottom: 10,
  },
  item: {
    width: itemSize - 80, // Adjust width with padding
    height: itemSize - 60, // Adjust height with padding
    backgroundColor: '#812892',
    justifyContent: 'center',
    alignItems: 'center',
    margin: 18, // Space between items
    borderRadius: 5,
  },
  itemText: {
    color: '#fff',
    fontSize: 16,
  },
  selectedButton: {
    backgroundColor: '#b8219f', // Green for selected
  },
  unselectedButton: {
    backgroundColor: '#812892', // Grey for unselected
  },
});

export default TestRunScreen;
