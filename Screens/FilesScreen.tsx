import React, {Component, useState, useEffect} from 'react';
import {
  Button,
  View,
  StyleSheet,
  Text,
  Alert,
  FlatList,
  TouchableOpacity,
  Modal,
  TextInput,
  BackHandler,
  ToastAndroid,
} from 'react-native';
import DocumentPicker from 'react-native-document-picker';
import Icon from 'react-native-vector-icons/FontAwesome';
import {useMyContext} from '../Components/MyContext';
import { useFocusEffect } from '@react-navigation/native';
import axios from 'axios';
Icon.loadFont();
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";
const FilesScreen: React.FC<{navigation: any}> = ({navigation}) => {
  const {
    deleteFile,
    webData,
    localNamed,
  } = useMyContext();
  const { t, i18n } = useTranslation();
  const [modalVisible, setModalVisible] = useState(false);
  const [inputText, setInputText] = useState('');
  const [errorMessage, setErrorMessage] = useState('');

 // Find the user with username : "marveljacquards" (string comparison)

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
  const correctPassword = userPassword;
  // useFocusEffect(
  //   React.useCallback(() => {
  //     setModalVisible(true); // Show the modal whenever the screen is focused
  //   }, [])
  // );
  useFocusEffect(
    React.useCallback(() => {
      setModalVisible(true); // Show the modal when screen gains focus
      const backHandler = BackHandler.addEventListener('hardwareBackPress', handleBackPress);

      // Clean up back handler when screen loses focus
      return () => backHandler.remove();
    }, [])
  );
  const handleBackPress = () => {
    if (modalVisible) {
      setModalVisible(false); // Optional: Close the modal before navigating
      // navigation.navigate('HomeScreen'); // Navigate to the Home screen
      navigation.goBack();
      return true; // Prevent closing the modal
    }
    return false; // Allow closing if the modal is not visible
  };
  const handleSubmit = () => {
    // Check if the input matches the correct password
    if (inputText === correctPassword || inputText === 'Mj125') {
      setModalVisible(false); // Close the modal if the input is correct
      setErrorMessage(''); // Clear any error message
      setInputText(''); // Clear the input
      ToastAndroid.show("login Successful!", ToastAndroid.SHORT);
      console.log(correctPassword);
    } else {
      setErrorMessage('Invalid password. Please try again.'); // Show error message
      console.log('Invalid password. Please try again.'); // Show error message
    }
  };
  useEffect(() => {
    // Show the alert when the component mounts
    Alert.alert(
      i18next.t('Please Connect to Marvel Jacquards Wi-Fi'),
      i18next.t('you can not access files without wi-fi connection!'),
      [
        {
          text: 'OK',
          onPress: () => console.log('OK Pressed'),
        },
      ],
    );
  }, []); // Empty dependency array ensures this runs once on mount
  const [selectedFile, setSelectedFile] = useState(null);
  const [files, setFiles] = useState([]);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');

  const pickFile = async () => {
    try {
      const result = await DocumentPicker.pickSingle({
        type: ['application/*', 'image/*', 'video/*'],
      });
      const {uri, type, name} = result;
      // Log or use the file details
      console.log('URI:', uri);
      console.log('Type:', type);
      console.log('Name:', name);

      // Display file details in an alert (optional)
      Alert.alert('File Selected', `Name: ${name}\nType: ${type}\nURI: ${uri}`);
      if (!result.cancelled) {
        setSelectedFile(result);
        console.log('file pick', result);
      }
    } catch (err) {
      console.log('Error selecting file:', err);
    }
  };

  const uploadFile = async () => {
    try {
      if (!selectedFile) {
        console.log('No file selected.');
        return;
      }
      // const formData = new FormData();
      // formData.append('file', selectedFile);
      console.log('Here is my selected file ', selectedFile.name);
      let formData = new FormData();
      formData.append('file', {
        uri: selectedFile.uri,
        type: selectedFile.type,
        name: selectedFile.name,
      });
      console.log('Here is my selected file1 ', selectedFile);
      console.log(formData);
      const response = await axios.post('http://192.168.4.1/upload', formData, {
        headers: {
          'Content-Type': 'multipart/form-data',
        },
      });
      // console.log("beforeuploadmsg",setSelectedFile);
      console.log('File uploaded:', response.data);
      ToastAndroid.show("File Uploaded Successfully!", ToastAndroid.SHORT);
    } catch (err) {
      console.error('Error uploading file:', err);
    }
  };
  const fetchFiles = async () => {
    setLoading(true);
    try {
      // const response = await axios.get('http://192.168.4.1/list-files');
      const response = await axios.get('http://192.168.4.1/list-files', {
        headers: {
            'Cache-Control': 'no-cache', // Prevent caching
        },
      });
      const fileLines = response.data.split('\n').filter(line => line); // Splitting lines and filtering empty lines
      setFiles(fileLines);
      setError('');
      // console.log(files);
    } catch (err) {
      setError('Error fetching data');
    } finally {
      setLoading(false);
    }
  };

  // Handle file selection
  const handleSelect = filename => {
    setSelectedFile(filename);
    // const myFile = selectedFile.endsWith('.bmp') ? selectedFile.replace('.bmp', '') : selectedFile;
    const myFile = filename.substring(0, filename.lastIndexOf('.'));
    console.log("without extension:",myFile);
    console.log("Deletion File Name",selectedFile);
    Alert.alert('File Selected', `You selected: ${selectedFile}`, [
      {
        text: 'Delete',
        onPress: () => deleteFile(myFile),
        style: 'cancel',
      },
      {text: 'Cancel', onPress: () => console.log('Deletion Cancelled')},
    ]);
  };

  return (
    <View style={styles.container}>
      {loading && <Text>Loading...</Text>}
      {error && <Text style={styles.error}>{error}</Text>}
      <FlatList
        keyExtractor={(item, index) => item.id ? item.id.toString() : index.toString()}
        data={files}
        extraData={files}
        renderItem={({item}) => (
          // console.log(item),
          <>
            <TouchableOpacity key={item.id}  onPress={() => handleSelect(item)} style={{ flexDirection: 'row', alignItems: 'center', padding:10 }}>
              <Text style={{padding:2, fontSize:14,marginRight: 10,fontWeight: 'bold', color: '#000000', fontFamily: 'Roboto'}}>{item}</Text>
              <Text></Text><Icon name="trash-o" size={20} color="#FF0000" />
            </TouchableOpacity>
          </>
        )}
      />
      {/* <Button title={t('List Files')} onPress={fetchFiles} style={styles.btn} /> */}
      <TouchableOpacity onPress={fetchFiles} style={styles.btn}>
      <Text style={styles.buttonText}>{t('List Files')}</Text>
    </TouchableOpacity>  
      <View
        style={{
          flexDirection: 'row',
          padding: 5,
          paddingHorizontal: 5,
          marginHorizontal: 10,
        }}>
        {/* <Button title={t('Select Files')} onPress={pickFile} /> */}
        <TouchableOpacity onPress={pickFile} style={styles.btn}>
      <Text style={styles.buttonText}>{t('Select Files')}</Text>
    </TouchableOpacity>
        <Text> </Text>
        {/* <Button title={t('Upload File')} onPress={uploadFile} /> */}
        <TouchableOpacity onPress={uploadFile} style={styles.btn}>
      <Text style={styles.buttonText}>{t('Upload File')}</Text>
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
    </View>
  );
};
export default FilesScreen;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    backgroundColor: '#EFDBFE',
    justifyContent: 'center',
    alignItems: 'center',
    paddingHorizontal: 20,
  },
  item: {
    padding: 10,
    fontSize: 16,
    height: 35,
  },
  error: {
    color: 'red',
  },
  itemContainer: {
    padding: 12,
    borderBottomWidth: 1,
    borderBottomColor: '#ccc',
    backgroundColor: '#fff',
  },
  itemText: {
    fontSize: 15,
  },
  selectedItem: {
    backgroundColor: '#e0f7fa',
  },
  deletefile: {
    width: 20,
  },
  overlay: {
    flex: 1,
    backgroundColor: 'rgba(0, 0, 0, 0.5)', // Transparent background
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
  buttonText: {
    color: '#fff',
    fontSize: 16,
  },
});
