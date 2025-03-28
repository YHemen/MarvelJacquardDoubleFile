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

const DoubleFile: React.FC = () => {
  const { t, i18n } = useTranslation();
  const [isOverlayVisible, setOverlayVisible] = useState(false);
  // const [fileName, setFileName] = useState(''); // State for file name input
  const [borderImageUri, setBorderImageUri] = useState(null);
  const [bodyImageUri, setBodyImageUri] = useState(null);
  const [loading, setLoading] = useState(false); // To track the loading state
  const [isRefreshing, setIsRefreshing] = useState(false);
 
  const {
    sdFiles,
    rpmValue,
    pCount,
    setPCount,
    pCount1,
    setPCount1,
    writeDoubleFileToSelect,
    writeTwoHeightToChange,
    f1height,
    f1width,
    f2height,
    f2width,
    prevFile,
    setPrevFile,
    nextFile,
    setNextFile,
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
    // getBodyFile(prevFile);
    // getBorderFile(nextFile); // Pass prevFile to getFile
    
    getFile(prevFile, nextFile);
    // Simulating an API call or refresh operation
    setTimeout(() => {
        setIsRefreshing(false); // Stop refreshing after 2 seconds
    }, 2000);
}, [prevFile, nextFile]); // Ensure it refreshes with the latest prevFile value

  const submitPCount = () => {
    const pCountValue = String(pCount);
    const pCount1Value = String(pCount1);
    // const pCountTValue = pCountValue+"/"+pCount1Value;
    writeTwoHeightToChange(pCountValue, pCount1Value);
  };
  const handleInputChange = (value) => {
    const numValue = value.replace(/[^0-9]/g,'');
    setPCount(numValue); // Update the state with the new input

  };
  const handleInputChange2 = (value) => {
    const numValue = value.replace(/[^0-9]/g,'');
    setPCount1(numValue); // Update the state with the new input

  };
 

  // const handleIncrement = () => {
  //   setPCount(prevHeight => {
  //     const incrementedHeight = prevHeight + 1;
  //     return incrementedHeight; // Return the new height for body state update
  //   });
  
  //   setPCount1(prevHeight => {
  //     const incrementedHeight = prevHeight + 1;
  //     return incrementedHeight; // Return the new height for border state update
  //   });
  // };

  // const handleDecrement = () => {
  //   setPCount(prevHeight => {
  //     const incrementedHeight = prevHeight - 1;
  //     return incrementedHeight; // Return the new height for body state update
  //   });
  
  //   setPCount1(prevHeight => {
  //     const incrementedHeight = prevHeight - 1;
  //     return incrementedHeight; // Return the new height for border state update
  //   });
  // };
  
  const handleIncrement = () => {
   
    setPCount(prevHeight => {
      const incrementedHeight = prevHeight === f1height ? 1 : prevHeight + 1;
      return incrementedHeight; // Return the new height for body state update
    });
  
    setPCount1(prevHeight => {
      const incrementedHeight = prevHeight === f2height ? 1 : prevHeight + 1;
      return incrementedHeight; // Return the new height for border state update
    });
  };

  const handleDecrement = () => {
    const minValue = 1;
    setPCount(prevHeight => {
      const incrementedHeight = prevHeight === minValue ? f1height : prevHeight - 1;
      return incrementedHeight; // Return the new height for body state update
    });
  
    setPCount1(prevHeight => {
      const incrementedHeight = prevHeight === minValue ? f2height : prevHeight - 1;
      return incrementedHeight; // Return the new height for border state update
    });
  };


  


  const handleBodyFile = value => {
    setPrevFile(value);
    console.log(value);
 };
 
 const handleBorderFile = value => {
  setNextFile(value);
  console.log(value);
};




  const submitDoublefile = () =>{
    console.log('Home screen',prevFile,nextFile);
    writeDoubleFileToSelect(prevFile,nextFile);
    console.log('bodyFile',prevFile);
    // getBodyFile(prevFile);
    console.log('borderFile',nextFile);
    // getBorderFile(nextFile); 
    getFile(prevFile, nextFile);
    
  }
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
       getFile(prevFile,nextFile);
    // getBodyFile(prevFile);
    // getBorderFile(nextFile);
    }, []); // Empty dependency array to run only on mount
        
    const getFile = async (bodyFile, borderFile) => {
      console.log("Fetching files:", bodyFile, borderFile);
    
      if (!bodyFile || !borderFile) {
        alert('Please enter valid file names with extensions (e.g., body.bmp, border.bmp)');
        return;
      }
    
      try {
        const [bodyResponse, borderResponse] = await Promise.all([
          fetch(`http://192.168.4.1/get-file?name=${bodyFile}`),
          fetch(`http://192.168.4.1/get-file?name=${borderFile}`),
        ]);
    
        console.log("Body Response Status:", bodyResponse.status);
        console.log("Border Response Status:", borderResponse.status);
    
        if (bodyResponse.ok && borderResponse.ok) {
          const bodyImageUrl = `http://192.168.4.1/get-file?name=${bodyFile}`;
          const borderImageUrl = `http://192.168.4.1/get-file?name=${borderFile}`;
    
          setBodyImageUri(bodyImageUrl);
          setBorderImageUri(borderImageUrl);
        } else {
          alert('One or both files not found');
          setBodyImageUri(null);
          setBorderImageUri(null);
        }
      } catch (error) {
        console.error('Error fetching files:', error);
        alert('Error fetching the files');
        setBodyImageUri(null);
        setBorderImageUri(null);
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
          paddingTop: 6,
          paddingBottom: 30,
          position: 'relative',
        }}>
        <View style={{alignSelf: 'center', alignItems: 'center'}}>
          <View>
            <Text style={{fontSize: 20, fontWeight: 'bold', marginBottom: 6}}>{t('BODY')}</Text>
          </View>
          {/* <View><Text style={{fontSize:16,fontStyle:'italic'}}>templates/alternate</Text></View> */}
        </View>

        <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 35,
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
              borderColor:'#F5EDF6',
            }} >
            {' '}
            {pCount}
          </TextInput>
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#812892" textAlign="right" />
          </TouchableOpacity>
          <TouchableOpacity  onPress={submitPCount}  style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 0, marginLeft: 22}} >
        {/* <Icon name="chevron-up" size={30} color="#000" />  */}
        <Text style={{color:'white'}}>{t('ok')}</Text>
        </TouchableOpacity>
        </View>
        <View>
          <Text style={{marginBottom:5, textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>
          {t('Height')}: {f1width} / {t('Width')}: {f1height}
          </Text>
          <View>
            <Text style={{marginBottom: 5, textAlign: 'center', fontWeight: 'bold', fontSize: 12}}>{t('Cards')}: {cardCount} / {t('Connectors')}: {cnCount} / {t('Total Hooks')}: {ttlHook}</Text>
            </View>
        </View>
        <View>
          <SelectList
            setSelected={handleBodyFile}
            data={dropdownData}
            save="key"
            // value= {prevBodyFile}
            // placeholder={"Select a file"}
            placeholder={prevFile ? prevFile : "Select File"}
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
                style={{
                    width: 300,  // Fixed width of 300 units (can adjust as needed)
                    height: 400, // Fixed height of 400 units (can adjust as needed)
                  }}
              >
                <View style={styles.container}>
                {loading ? (
                  <Animated.View style={{ transform: [{ rotate }] }}>
                    <View style={styles.spinner}></View>
                  </Animated.View>
                ) : (
                  bodyImageUri && <Image source={{ uri: bodyImageUri }} style={styles.image} resizeMode="stretch" />
                )}
                {loading && <Text>Loading...</Text>}
              </View>
                  </ScrollView>
        {/* border details with height width piccount */}
        <View>
        <Text style={{alignSelf: 'center', alignItems: 'center',fontSize: 20, fontWeight: 'bold', marginBottom: 6}}>{t('BORDER')}</Text>
          </View>
          <View
          style={{
            flexDirection: 'row',
            justifyContent: 'space-between',
            alignItems: 'center',
            paddingHorizontal: 35,
            marginBottom: 5,
          }}> 
          {/* <Text> PCount:</Text> */}
          <TouchableOpacity onPress={handleDecrement}>
            <Icon name="chevron-down" size={30} color="#812892" />
          </TouchableOpacity>
          <TextInput
            keyboardType="number-pad"
            // value={pCount}
            onChangeText={handleInputChange2}
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
              borderColor:'#F5EDF6',
            }} >
            {' '}
            {pCount1}
          </TextInput>
          <TouchableOpacity onPress={handleIncrement}>
            <Icon name="chevron-up" size={30} color="#812892" textAlign="right" />
          </TouchableOpacity>
          <TouchableOpacity  onPress={submitPCount}  style={{backgroundColor:'purple', width: 50, height: 40, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 0, marginLeft: 22}} >
        {/* <Icon name="chevron-up" size={30} color="#000" />  */}
        <Text style={{color:'white'}}>{t('ok')}</Text>
        </TouchableOpacity>
        </View>
        <View>
          <Text style={{marginBottom:1, textAlign: 'center', fontWeight: 'bold', fontSize: 18}}>
          {t('Height')}: {f2width} / {t('Width')}: {f2height}
          </Text>
          </View>  
        {/* end of border details */}
        
        </View>
        
        <View>
          <SelectList
            setSelected={handleBorderFile}
            data={dropdownData}
            save="key"
            // value= {prevFile}
            // placeholder={"Select a file"}
            placeholder={nextFile ? nextFile : "Select File"}
            boxStyles={styles.selectBox}
            dropdownStyles={styles.dropdown}
            dropdownTextStyles={styles.dropdownText}
            placeholderStyle={styles.placeholder}
            selected={nextFile}
          />
          <ScrollView refreshControl={
                  <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
                }
                style={{
                    width: 300,  // Fixed width of 300 units (can adjust as needed)
                    height: 400, // Fixed height of 400 units (can adjust as needed)
                  }}
              >
                <View style={styles.imgcontainer}>
                {loading ? (
                  <Animated.View style={{ transform: [{ rotate }] }}>
                    <View style={styles.spinner}></View>
                  </Animated.View>
                ) : (
                  borderImageUri && <Image source={{ uri: borderImageUri }} style={styles.image} resizeMode="stretch" />
                )}
                {loading && <Text>Loading...</Text>}
              </View>
                  </ScrollView>
          {/* <ScrollView>
          {borderImageUri && (
        <Image
          source={{ uri: borderImageUri }}
          style={{backgroundColor:'pink', width:335, height:150}}
          resizeMode="stretch"
        />
      )}
          
        </ScrollView> */}
        </View>
      </View>
      <View
        style={{
          flexDirection: 'row',
          justifyContent: 'space-between',
          alignItems: 'center',
          marginLeft: 30,
          marginTop:285,
        }}>
        {/* <View>
          <Text style={{fontSize: 30, fontWeight: 'bold', color: 'purple', marginTop:10}}>
            {rpmValue}
          </Text>
        </View> */}
        <View>
          <Text style={styles.rpmValue}>
            {rpmValue}
          </Text>
        </View>
        <View><TouchableOpacity style={{backgroundColor:'purple', width: 75, height: 40, bottom: -20, borderRadius:5,justifyContent:'space-around', alignItems:'center', marginRight: 0, marginLeft: 12}} onPress={submitDoublefile}><Text style={{color:'white'}}>{t('Submit')}</Text></TouchableOpacity>
          
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
      <TouchableOpacity style={styles.floatingButton} onPress={toggleOverlay}>
        <Text style={styles.buttonText}>
          {isOverlayVisible ? <Icon name="unlock" size={30} color="#FFFFFF" /> : <Icon name="lock" size={30} color="#FFFFFF" />}
        </Text>
      </TouchableOpacity>
    </SafeAreaView>
      {/* <TouchableOpacity style={styles.floatingButton} onPress={toggleOverlay}>
        <Text style={styles.buttonText}>
          {isOverlayVisible ? <Icon name="unlock" size={30} color="#FFFFFF" /> : <Icon name="lock" size={30} color="#FFFFFF" />}
        </Text>
      </TouchableOpacity> */}

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
    bottom: 10, // Adjust for vertical spacing
    right: 15, // Adjust for horizontal spacing
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
    right: -15, // Adjust for horizontal spacing
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
  digitalText: {
    fontSize: 60,
    color: '#00FF00', // Green color for digital look
    fontFamily: 'digital-7', // Use the font name as it appears inside the font file
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
    height: 150,
    marginTop: 0,
  },
  imgcontainer:{
    width: '100%',
    height: 150,
  },
  rpmValue: {
    fontFamily: 'Technology-Bold',
    fontSize: 70,
    color: 'purple',
    position: 'relative',
    marginTop: 5,
    marginLeft: -110,
    marginRight: 10,
    bottom: -10,
  },
});

export default DoubleFile;

// style={{fontSize: 30, fontWeight: 'bold', color: 'purple',    }}