import React, {useState,useEffect} from 'react';
import {
  SafeAreaView,
  Image,
  View,
  Text,
  StyleSheet,
  TextInput,
  TouchableOpacity,
  Modal ,
} from 'react-native';
import {SelectList} from 'react-native-dropdown-select-list';
import Icon from 'react-native-vector-icons/FontAwesome';
import {useMyContext} from '../Components/MyContext';
import {ScrollView} from 'react-native-gesture-handler';
const HomeScreen: React.FC = () => {
  const [isOverlayVisible, setOverlayVisible] = useState(false);
  const [fileName, setFileName] = useState(''); // State for file name input
  const [imageUri, setImageUri] = useState(null);
 
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

  useEffect(() => {
    // Fetch data for the initial prevFile when the component mounts
    getFile(prevFile);
}, []); // Empty dependency array to run only on mount
  const getFile = async (fileName) => {
    console.log("file selected",fileName);
    if (!fileName) {
      alert('Please enter a file name with extension (e.g., butta.bmp)');
      return;
    }

    try {
      const response = await fetch(`http://192.168.4.1/get-file?name=${fileName}`);
      if (response.ok) {
        
        // Use the response URL directly without creating a blob URL
        setImageUri(`http://192.168.4.1/get-file?name=${fileName}`);
        console.log("url",imageUri);
      } else {
        alert('File not found');
        setImageUri(null); // Clear the image if not found
      }
    } catch (error) {
      console.error('Error fetching file:', error);
      alert('Error fetching the file');
    }
  };
  const toggleOverlay = () => {
    setOverlayVisible(!isOverlayVisible);
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
            <Text style={{fontSize: 20, fontWeight: 'bold', marginBottom: 20}}>BODY</Text>
          </View>
          {/* <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View> */}
        </View>

        <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 14,
            marginBottom: 5,
          }}> 
          {/* <Text> PCount:</Text> */}
          <TouchableOpacity onPress={handleDecrement}>
            <Icon name="chevron-down" size={30} color="#812892" />
          </TouchableOpacity>
          <TextInput
            keyboardType="number-pad"
            // value={pCount}
            onChangeText={handleInputChange}
            placeholder='Input Number'
            style={{
              width: 60,
              height:46,
              borderRadius: 5,
              fontSize: 24,
              fontWeight: 'bold',
              color: '#812892',
              marginLeft: 10,
              marginRight: 10,
              borderWidth:1,
              borderColor:'#812892',
            }} >
            {' '}
            {pCount}
          </TextInput>
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#812892" textAlign="right" />
          </TouchableOpacity>
          <TouchableOpacity  onPress={submitPCount}  style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 0, marginLeft: 22}} >
        {/* <Icon name="chevron-up" size={30} color="#000" />  */}
        <Text style={{color:'white'}}>OK</Text>
        </TouchableOpacity>
        </View>
        <View>
          <Text style={{marginBottom:5, textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>
          height: {width} / Width: {height}
          </Text>
          <View>
            <Text style={{marginBottom: 5, textAlign: 'center', fontWeight: 'bold', fontSize: 12}}>Cards: {cardCount} / CN: {cnCount} / Total Hooks: {ttlHook}</Text>
            </View>
        </View>
        <View>
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
          <ScrollView>
          {imageUri && (
        <Image
          source={{ uri: imageUri }}
          style={{backgroundColor:'pink', width:335, height:150}}
          resizeMode="stretch"
        />
      )}
          
        </ScrollView>
        </View>
        {/* <View>
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
          <ScrollView>
          {imageUri && (
        <Image
          source={{ uri: imageUri }}
          style={{backgroundColor:'pink', width:335, height:150}}
          resizeMode="stretch"
        />
      )}
          
        </ScrollView>
        </View> */}
      </View>
      <View
        style={{
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          marginLeft: 60,
          marginTop:310,
        }}>
        <View>
          <Text style={{fontSize: 30, fontWeight: 'bold', color: 'purple', marginTop:10}}>
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
    // justifyContent: 'center',
    alignItems: 'center',
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
    top: 57, // Adjust for vertical spacing
    left: 6, // Adjust for horizontal spacing
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
    top: 1, // Adjust for vertical spacing
    left: 6, // Adjust for horizontal spacing
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

export default HomeScreen;
