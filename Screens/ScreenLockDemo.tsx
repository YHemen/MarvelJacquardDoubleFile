import React, { useState } from 'react';
import { View, Text, TouchableOpacity, StyleSheet, Modal } from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
const ScreenLockDemo = () => {
  const [isOverlayVisible, setOverlayVisible] = useState(false);

  const toggleOverlay = () => {
    setOverlayVisible(!isOverlayVisible);
  };

  return (
    <View style={styles.container}>
        <Text style={styles.mainContent}>This is the main screen!</Text>
      <TouchableOpacity style={styles.floatingButton} onPress={toggleOverlay}>
        <Text style={styles.buttonText}>
          {isOverlayVisible ? <Icon name="unlock" size={30} color="#FFFFFF" /> : <Icon name="lock" size={30} color="#FFFFFF" />}
        </Text>
      </TouchableOpacity>

      {/* Overlay */}
      {isOverlayVisible && (
        <Modal transparent={true} animationType="fade">
          <View style={styles.overlay}>
            <Text style={styles.overlayText}>Un-Lock to Change Settings</Text>
            <TouchableOpacity style={styles.closeButton} onPress={toggleOverlay}>
              <Text style={styles.buttonText}><Icon name="unlock" size={30} color="#FFFFFF" /></Text>
            </TouchableOpacity>
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
  button: {
    padding: 1,
    backgroundColor: '#007BFF',
    borderRadius: 5,
    marginLeft:10,
  },
  buttonText: {

    color: '#FFFFFF',
    fontSize: 18,
  },
  overlay: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: 'rgba(0, 0, 0, 0.5)', // Semi-transparent background
    
  },
  overlayText: {
    color: '#FFFFFF',
    fontSize: 24,
    marginBottom: 20,
  },
  closeButton: {
    position: 'absolute',
    top: 66, // Adjust for vertical spacing
    right: 6, // Adjust for horizontal spacing
    width: 40,
    height: 40,
    backgroundColor: '#812892',
    borderRadius: 30, // Circular button
    justifyContent: 'center',
    alignItems: 'center',
    elevation: 5, // Android shadow
    shadowColor: '#000', // iOS shadow
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.3,
    shadowRadius: 4,
  },
  floatingButton: {
    position: 'absolute',
    top: 10, // Adjust for vertical spacing
    right: 6, // Adjust for horizontal spacing
    width: 40,
    height: 40,
    backgroundColor: '#812892',
    borderRadius: 30, // Circular button
    justifyContent: 'center',
    alignItems: 'center',
    elevation: 5, // Android shadow
    shadowColor: '#000', // iOS shadow
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.3,
    shadowRadius: 4,
  },
});

export default ScreenLockDemo;
