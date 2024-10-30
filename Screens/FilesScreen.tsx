import React, {Component, useState, useEffect} from 'react';
import {
  Button,
  View,
  StyleSheet,
  Text,
  Alert,
  FlatList,
  ScrollView,
  TouchableOpacity,
} from 'react-native';
import {useNavigation} from '@react-navigation/native';
import DocumentPicker from 'react-native-document-picker';
import Icon from 'react-native-vector-icons/FontAwesome';
import {useMyContext} from '../Components/MyContext';
import axios from 'axios';
Icon.loadFont();
const FilesScreen: React.FC<{navigation: any}> = ({navigation}) => {
  const {
    deleteFile
  } = useMyContext();
  useEffect(() => {
    // Show the alert when the component mounts
    Alert.alert(
      'Please Connect to Marvel Wi-fi ',
      "you can't access files without wi-fi connection!",
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
  const deleteBmpFile = async (selectedFile) =>{
    Alert.alert('File Deletion', `You Want to Delete: ${selectedFile}`, [
      {
        text: 'Delete',
        onPress: () => deleteFile(selectedFile),
        style: 'delete',
      },
      {text: 'Cancel', onPress: () => console.log('Deletion Cancelled')},
    ]);
    console.log("File selected for deletion:",selectedFile);
    
  };
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
    } catch (err) {
      console.error('Error uploading file:', err);
    }
  };

  // const deleteFile = async filename => {
  //   try {
  //     // const response = await axios.post(`http://192.168.4.1/delete?filename=${encodedFilename}`);
  //     const response = await axios.post(
  //       `http://192.168.4.1/delete`,
  //       new URLSearchParams({
  //         filename: filename,
  //       }),
  //       {
  //         headers: {
  //           'Content-Type': 'application/x-www-form-urlencoded',
  //         },
  //       },
  //     );
  //     // Show success alert and refresh the file list
  //     Alert.alert('Success', 'File deleted successfully');
  //     fetchFiles(); // Refresh the file list
  //   } catch (error) {
  //     // Show error alert
  //     Alert.alert(
  //       'Error',
  //       error.response ? error.response.data : 'Failed to delete file',
  //     );
  //   }
  // };
  const fetchFiles = async () => {
    setLoading(true);
    try {
      const response = await axios.get('http://192.168.4.1/list-files');
      const fileLines = response.data.split('\n').filter(line => line); // Splitting lines and filtering empty lines
      setFiles(fileLines);
      setError('');
    } catch (err) {
      setError('Error fetching data');
    } finally {
      setLoading(false);
    }
  };

  // Handle file selection
  const handleSelect = filename => {
    setSelectedFile(filename);
    Alert.alert('File Selected', `You selected: ${selectedFile}`, [
      {
        text: 'Delete',
        onPress: () => deleteBmpFile(selectedFile),
        style: 'cancel',
      },
      {text: 'Cancel', onPress: () => console.log('Deletion Cancelled')},
    ]);
  };

  //   <View style={{ flex: 1, padding: 16 }}>
  //   <FlatList
  //     data={files}
  //     keyExtractor={(item) => item.filename}
  //     renderItem={({ item }) => (
  //       <TouchableOpacity
  //         onPress={() => deleteFile(item.filename)}
  //         style={{ padding: 16, borderBottomWidth: 1 }}
  //       >
  //         <Text style={{ fontSize: 18 }}>{item.filename} - {item.size} bytes</Text>
  //       </TouchableOpacity>
  //     )}
  //   />
  // </View>

  // const renderItem = ({ item }) => (
  //   <View style={styles.itemContainer}>
  //     <Text style={styles.fileName}>{item}</Text>

  //     <TouchableOpacity
  //       style={styles.deleteButton}
  //       onPress={() =>handleSelect(item)}
  //     >
  //       <Text style={styles.buttonText}><Icon name="trash-o" size={20} color="#000" /></Text>
  //     </TouchableOpacity>
  //   </View>
  // );

  return (
    <View style={styles.container}>
      {loading && <Text>Loading...</Text>}
      {error && <Text style={styles.error}>{error}</Text>}
      {/* <FlatList
            data={files}
            renderItem={renderItem}
            keyExtractor={(item) => item}
          /> */}
      <FlatList
        keyExtractor={item => item.id}
        data={files}
        renderItem={({item}) => (
          <>
            <TouchableOpacity onPress={() => handleSelect(item)} style={{ flexDirection: 'row', alignItems: 'center', padding:10 }}>
              <Text style={{padding:2, fontSize:14,marginRight: 10,fontWeight: 'bold'}}>{item}</Text>
              <Text></Text><Icon name="trash-o" size={20} color="#FF0000" />
            </TouchableOpacity>
            {/* <TouchableOpacity onPress={() => deleteFile(item)}>
              <Icon name="trash-o" size={20} color="#FF0000" />
            </TouchableOpacity> */}
          </>
        )}
      />
      <Button title="List Files" onPress={fetchFiles} />

      {/* <ScrollView>
            {loading ? (
              <Text>Loading...</Text>
            ) : error ? (
              <Text>{error}</Text>
            ) : (
              <Text>{files}</Text>
            )}
            <Button title="List Files" onPress={fetchFiles} />
          </ScrollView> */}

      <View
        style={{
          flexDirection: 'row',
          padding: 5,
          paddingHorizontal: 5,
          marginHorizontal: 10,
        }}>
        <Button title="Select file" onPress={pickFile} />
        <Text> </Text>
        <Button title="Upload file" onPress={uploadFile} />
      </View>
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
});
