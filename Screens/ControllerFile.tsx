import React, { useState, useEffect } from 'react';
import { View, Text, TouchableOpacity, StyleSheet } from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
import AsyncStorage from '@react-native-async-storage/async-storage'; // Import AsyncStorage
import SingleFile from './SingleFile';
import DoubleFile from './DoubleFile';

const ControllerFile = () => {
  const [screenName, setScreenName] = useState('DoubleFile');  // State to store current screen name

  // Fetch the screenName from AsyncStorage when the component mounts
  useEffect(() => {
    const fetchScreenName = async () => {
      try {
        const storedScreenName = await AsyncStorage.getItem('screenName');
        if (storedScreenName) {
          setScreenName(storedScreenName);
        }
      } catch (error) {
        console.error('Error fetching screen name from AsyncStorage:', error);
      }
    };

    fetchScreenName();
  }, []); // Empty dependency array ensures this runs only once when the component mounts

  // Toggle the screen and store the screenName in AsyncStorage
  const toggleScreen = async () => {
    const newScreen = screenName === 'SingleFile' ? 'DoubleFile' : 'SingleFile';
    setScreenName(newScreen);
    try {
      await AsyncStorage.setItem('screenName', newScreen); // Save the new screen name to AsyncStorage
    } catch (error) {
      console.error('Error saving screen name to AsyncStorage:', error);
    }
  };

  return (
    <View style={styles.container}>
      <TouchableOpacity
        onPress={toggleScreen}
        style={[styles.toggleButton, { backgroundColor: screenName === 'SingleFile' ? '#812892' : '#DA498D' }]}  // Purple for SingleFile, Pink for DoubleFile
      >
        <Text style={styles.buttonText}>
          {/* Icon placed beside the text */}
          <Icon
            name={screenName === 'DoubleFile' ? 'files-o' : 'file-o'} // Different icon for each screen
            size={20}
            color="white"
            style={styles.icon}
          />
          {/* Dynamic Text */}
          {screenName}
        </Text>
      </TouchableOpacity>

      {/* Conditionally render the first or second screen */}
      {screenName === 'SingleFile' ? <DoubleFile /> : <SingleFile />}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  toggleButton: {
    position: 'absolute',  // This places the button in the absolute position
    top: 1,               // Adjust the top value to your liking (distance from top edge)
    left: 6,              // Positioned to the left edge
    padding: 10,
    borderRadius: 5,
    zIndex: 1,            // Ensure the button stays on top of other components
  },
  buttonText: {
    color: 'white',
    fontSize: 16,
    flexDirection: 'row',  // Ensure the icon and text are aligned horizontally
    alignItems: 'center',  // Vertically align icon and text in the center
  },
  icon: {
    marginRight: 8,  // Spacing between the icon and the text
  },
});

export default ControllerFile;
