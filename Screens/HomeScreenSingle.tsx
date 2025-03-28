import React, {useState,useEffect, useCallback} from 'react';
import {
  SafeAreaView,
  Image,
  View,
  Text,
  StyleSheet,
  TextInput,
  TouchableOpacity,
  Modal ,
  Animated, 
  Easing,
  RefreshControl,
  Alert,
} from 'react-native';
import {SelectList} from 'react-native-dropdown-select-list';
import Icon from 'react-native-vector-icons/FontAwesome';
import {useMyContext} from '../Components/MyContext';
import {ScrollView} from 'react-native-gesture-handler';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';


const HomeScreen: React.FC = () => {
  
  const { t, i18n } = useTranslation();
  const [isOverlayVisible, setOverlayVisible] = useState(false);
  const [imageUri, setImageUri] = useState(null);
  const [loading, setLoading] = useState(false); // To track the loading state
  const [isRefreshing, setIsRefreshing] = useState(false);
  const [text, setText] = useState(false);
  const {
    sdFiles,
    rpmValue,
    pCount,
    setPCount,
    writeFileToSelect,
    writeHeightToChange,
    height,
    width,
    prevFile,
    setPrevFile,
    cardCount,
    cnCount,
    ttlHook,
  } = useMyContext();

useEffect(() => {
    // Ensure re-render when language changes
    console.log('Home Screen Current language:', i18n.language);
  }, [i18n.language]);
  // Function to handle the refresh
  const onRefresh = useCallback(() => {
    setIsRefreshing(true); // Start refreshing
    console.log("Refreshing with file:", prevFile); // Log the file name being passed to getFile
    getFile(prevFile); // Pass prevFile to getFile

    // Simulating an API call or refresh operation
    setTimeout(() => {
        setIsRefreshing(false); // Stop refreshing after 2 seconds
    }, 2000);
}, [prevFile]); // Ensure it refreshes with the latest prevFile value



  const submitPCount = () => {
    const pCountValue=String(pCount);
    writeHeightToChange(pCountValue);
  };
  const handleInputChange = (value) => {
    const numValue = value.replace(/[^0-9]/g,'');
    setPCount(numValue); // Update the state with the new input

  };
  const handleIncrement = () => {
    
    setPCount(prevHeight => {
      const incrementedHeight = prevHeight + 1;
      return incrementedHeight; // Return the new height for state update
      
    });
  };
  const handleDecrement = () => {
    setPCount(prevHeight => {
      const decrementdHeight = prevHeight - 1;
      return decrementdHeight; // Return the new height for state update
    });
  };

  const handleSelect = value => {
    setPrevFile(value);
    writeFileToSelect(value);
    getFile(value);
    // setPCount(0);
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


  const rotateValue = new Animated.Value(0); // Animated value to rotate the spinner

  useEffect(() => {
    // Create a continuous rotation animation
    if (loading) {
      Animated.loop(
        Animated.timing(rotateValue, {
          toValue: 1,
          duration: 1000,
          easing: Easing.linear,
          useNativeDriver: true,
        })
      ).start();
    }
  }, [loading]);

  const rotate = rotateValue.interpolate({
    inputRange: [0, 1],
    outputRange: ['0deg', '360deg'],
  });

  useEffect(() => {
    // Fetch data for the initial prevFile when the component mounts
    getFile(prevFile);
  }, []); // Empty dependency array to run only on mount

  const getFile = async (fileName) => {
    console.log("file selected", fileName);

    if (!fileName) {
      alert('Please enter a file name with extension (e.g., butta.bmp)');
      return;
    }

    setLoading(true); // Set loading to true when the request starts

    try {
      const response = await fetch(`http://192.168.4.1/get-file?name=${fileName}`);
      if (response.ok) {
        // Set the image URL if the file is found
        setImageUri(`http://192.168.4.1/get-file?name=${fileName}`);
        console.log("url", imageUri);
      } else {
        alert('File not found');
        setImageUri(null); // Clear the image if not found
      }
    } catch (error) {
      console.error('Error fetching file:', error);
      alert('Error fetching the file');
      setImageUri(null); // Clear the image in case of error
    } finally {
      setLoading(false); // Set loading to false when the request is complete (success or failure)
    }
  };

  useEffect(() => {
    if (imageUri) {
      console.log("Updated Image URL:", imageUri);
    }
  }, [imageUri]);
  
  const toggleOverlay = () => {
    setOverlayVisible(!isOverlayVisible);
  };
  const handleLongPress = () => {
    // Display the alert box on long press
    Alert.prompt(
      'Input Number',            // Title of the alert box
      'Enter a number:',         // Message displayed in the alert box
      [
        {
          text: 'Cancel',        // Cancel button
          style: 'cancel',
        },
        {
          text: 'OK',            // OK button
          onPress: (inputText) => {
            setPCount(inputText); // Store the input value in pCount state (updates the TextInput)
          },
        },
      ],
      'plain-text',              // Type of input (plain-text here)
      pCount                     // Default value (current pCount value)
    );
  };
  return (
    <View style={styles.container}>
    
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
            <Text style={{fontFamily: 'Poppins-Bold', fontSize: 24, color:  '#000000', marginBottom: 10, fontWeight: 'bold'}}>{t('BODY')}</Text>
          </View>
          {/* <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View> */}
        </View>

        <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 50,
            marginBottom: 10,
          }}> 
          {/* <Text> PCount:</Text> */}
          <TouchableOpacity onPress={handleDecrement}>
            <Icon name="chevron-down" size={30} color="#812892" />
          </TouchableOpacity>
          
          {/* <TouchableOpacity onLongPress={handleLongPress} activeOpacity={0.7}> */}
          <TextInput
            keyboardType="number-pad"
            //  value={pCount}
            onChangeText={handleInputChange}
            placeholder='Input Number'
            maxLength={6}
            editable={true}
            style={{
              width: 80,
              height:46,
              borderRadius: 5,
              fontSize: 24,
              fontWeight: 'bold',
              color: '#812892',
              marginLeft: 10,
              marginRight: 10,
              borderWidth:1,
              borderColor:'#812892',
              textAlign: 'center', // Horizontally center text
              textAlignVertical: 'center',
            }}>
            {' '}
            {pCount}
          </TextInput>
          {/* </TouchableOpacity>   */}
          
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#812892" textAlign="right" />
          </TouchableOpacity>
          <TouchableOpacity  onPress={submitPCount}  style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 0, marginLeft: 22}} >
        {/* <Icon name="chevron-up" size={30} color="#000" />  */}
        <Text style={{color:'white'}}>{t('ok')}</Text>
        </TouchableOpacity>
        </View>
        <View>
          <Text style={{marginBottom:10, textAlign: 'center', fontWeight: 'bold', fontSize: 20, color: '#000000', fontFamily: 'apercumovistarbold'}}>
          {t('Height')}: {width} / {t('Width')}: {height}
          </Text>
          <View>
            <Text style={{marginBottom: 10, textAlign: 'center', fontWeight: 'bold', fontSize: 14, color: '#000000', fontFamily: 'Roboto'}}>{t('Cards')}: {cardCount} / {t('Connectors')}: {cnCount} / {t('Total Hooks')}: {ttlHook}</Text>
            </View>
        </View>
        <View>
          <SelectList
            setSelected={handleSelect}
            data={dropdownData}
            save="key"
            placeholder={prevFile ? prevFile : 'Select File'}
            boxStyles={{color: '#000000', fontFamily: 'Roboto'}}
            dropdownStyles={{color: '#000000', fontFamily: 'Roboto'}}
            dropdownTextStyles={{color: '#000000', fontFamily: 'Roboto'}}
            placeholderStyle={{color: '#000000', fontFamily: 'Roboto'}}
            selectedTextStyles={{color: '#000000', fontFamily: 'Roboto'}}
            selected={prevFile}
          />
          <ScrollView refreshControl={
        <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
      }
    >
      <View style={styles.container}>
      {loading ? (
        <Animated.View style={{ transform: [{ rotate }] }}>
          <View style={styles.spinner}></View>
        </Animated.View>
      ) : (
        imageUri && <Image source={{ uri: imageUri }} style={styles.image} resizeMode="stretch" />
      )}
      {loading && <Text>Loading...</Text>}
    </View>
        </ScrollView>
        </View>
      </View>
      <View
        style={{
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          marginLeft: -220,
          marginTop:270,
        }}>
        <View>
          <Text style={styles.rpmValue}>
        {rpmValue}
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
      </View>
    </SafeAreaView>
      <TouchableOpacity style={styles.floatingButton} onPress={toggleOverlay}>
        <Text style={styles.buttonText}>
          {isOverlayVisible ? <Icon name="unlock" size={30} color="#FFFFFF" /> : <Icon name="lock" size={30} color="#FFFFFF" />}
        </Text>
      </TouchableOpacity>
      {/* Overlay */}
      {isOverlayVisible && (
        <Modal transparent={true} animationType="fade">
          <View style={styles.overlay}>
            <Text style={styles.overlayText}>{t('Un-Lock to Change Settings')}</Text>
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
    // justifyContent: 'center',
    alignItems: 'center',
  },
  digitalText: {
    fontSize: 60,
    color: '#00FF00', // Green color for digital look
    fontFamily: 'digital-7', // Use the font name as it appears inside the font file
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
    bottom: 10, // Adjust for vertical spacing
    right: 8, // Adjust for horizontal spacing
    width: 50,
    height: 50,
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
    bottom: 10, // Adjust for vertical spacing
    right: 8, // Adjust for horizontal spacing
    width: 50,
    height: 50,
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
  spinner: {
    width: 50,
    height: 50,
    borderRadius: 25,
    borderWidth: 5,
    borderColor: '#3498db',
    borderTopColor: 'transparent',
  },
  image: {
    width: '100%',
    height: 250,
    marginTop: 20,
  },
  rpmValue: {
    fontFamily: 'Technology-Bold',
    fontSize: 70,
    color: 'purple',
    position: 'relative',
  },
  
});

export default HomeScreen;