import React, { useState, useEffect } from 'react';
import { View, Text, TextInput, TouchableOpacity, Modal, StyleSheet } from 'react-native';
import { overlay } from 'react-native-paper';
import {useMyContext} from '../Components/MyContext';

  const ScreenLocks: React.FC<{navigation: any}> = ({navigation}) => {
   
    const {
      pCount,
      setPCount,
    } = useMyContext();
  const [isModalVisible, setModalVisible] = useState(false);
  const [previousPCount, setPreviousPCount] = useState(pCount);
  const [constantTimer, setConstantTimer] = useState(null);

  // Replace this with your actual ESP32 notification subscription logic
  useEffect(() => {
    const handlePCountUpdate = (newPCount) => {
      setPCount(newPCount); // Update pCount with the new value from ESP32
    };

    // Example: subscribe to your ESP32 notifications here
    // YourESP32.on('pCountUpdate', handlePCountUpdate);

    return () => {
      // Clean up the subscription here
      // YourESP32.off('pCountUpdate', handlePCountUpdate);
    };
  }, []);

  useEffect(() => {
    // If pCount changes, show the overlay
    if (pCount !== previousPCount) {
      setModalVisible(true); // Show overlay
      setPreviousPCount(pCount);

      // Clear the previous timer if it exists
      if (constantTimer) {
        clearTimeout(constantTimer);
      }

      // Set a timer to deactivate the overlay after 2 seconds of constant value
      const timer = setTimeout(() => {
        setModalVisible(false); // Hide overlay if pCount is constant for 2 seconds
      }, 2000);
      
      setConstantTimer(timer);
    } else {
      // If pCount is constant, clear any previous timer
      if (constantTimer) {
        clearTimeout(constantTimer);
      }
    }

    return () => {
      // Cleanup timer on component unmount or effect re-run
      if (constantTimer) {
        clearTimeout(constantTimer);
      }
    };
  }, [pCount, previousPCount]);

  const handleClosePress = () => {
    setModalVisible(false); // Close the overlay
  };
  return (
    <View style={styles.container}>
        <View style={styles.mainContent}>
          <Text style={styles.title}>Main Screen Content</Text>
          <Text>pCount: {pCount}</Text>
          {/* Additional components go here */}
        </View>
      {isModalVisible && (
         <Modal transparent={true} visible={isModalVisible} animationType="slide">
         <View style={styles.overlay}>
           <View style={styles.modalContent}>
             <Text style={styles.modalText}>Overlay is active</Text>
             {/* Other content can go here */}
             <TouchableOpacity 
               style={styles.closeButton} 
               onPress={handleClosePress}
             >
               <Text style={styles.buttonText}>Close</Text>
             </TouchableOpacity>
           </View>
         </View>
       </Modal>
       )}
      
      
     
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
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'rgba(0, 0, 0, 0.5)', // Semi-transparent background
  },
  modalContent: {
    width: 300,
    padding: 20,
    backgroundColor: 'rgba(255, 255, 255, 0.8)',
    borderRadius: 10,
    alignItems: 'center',
    position: 'relative',
  },
  modalText: {
    marginBottom: 20,
    fontSize: 18,
  },
  closeButton: {
    position: 'absolute',
    bottom: 20,
    right: 20,
    backgroundColor: '#007BFF',
    paddingVertical: 10,
    paddingHorizontal: 15,
    borderRadius: 25,
  },
  buttonText: {
    color: 'white',
    fontSize: 16,
  },
  mainContent: {
    justifyContent: 'center',
    alignItems: 'center',
    padding: 20,
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 20,
  },
});
export default ScreenLocks;
