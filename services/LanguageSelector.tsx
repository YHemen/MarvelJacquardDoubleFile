import React, {useEffect} from 'react';
import { View, StyleSheet, TouchableOpacity, Text } from 'react-native';
import { useTranslation } from 'react-i18next';  // Import the hook
import i18next from "i18next";
// import AsyncStorage from '@react-native-async-storage/async-storage';

const LanguageSelector: React.FC = () => {
  const { t, i18n  } = useTranslation();  // Access the i18n instance

  const changeLanguage = (lang: string) => {
    console.log(`Changing language to: ${lang}`);
    i18n.changeLanguage(lang);  // Change the language dynamically
    console.log('Loaded resources:', i18next.store.data);
  };

   // Change language and store it in AsyncStorage
  //  const changeLanguage = async (lang: string) => {
  //   console.log(`Changing language to: ${lang}`);
  //   i18n.changeLanguage(lang);  // Change the language dynamically
  //   await AsyncStorage.setItem('language', lang);  // Save the selected language to AsyncStorage
  //   console.log('Loaded resources:', i18next.store.data);
  // };

  
  return (
    <View style={styles.container}>
      <TouchableOpacity style={styles.btn} onPress={() => changeLanguage('en')}>
        <Text style={styles.txt}>English</Text>
      </TouchableOpacity>
      <TouchableOpacity style={styles.btn} onPress={() => changeLanguage('te')}>
        <Text style={styles.txt}>Telugu</Text>
      </TouchableOpacity>
      <TouchableOpacity style={styles.btn} onPress={() => changeLanguage('kn')}>
        <Text style={styles.txt}>Kannada</Text>
      </TouchableOpacity>
      <TouchableOpacity style={styles.btn} onPress={() => changeLanguage('hi')}>
        <Text style={styles.txt}>Hindi</Text>
      </TouchableOpacity>
      <TouchableOpacity style={styles.btn} onPress={() => changeLanguage('ta')}>
        <Text style={styles.txt}>Tamil</Text>
      </TouchableOpacity>
      
    </View>
  );
};

const styles = StyleSheet.create({
  scrollView: {
    flex: 1, // Make the ScrollView take up the entire screen
  },
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#EFDBFE',
  },
  
  bleCard: {
    width: '90%',
    padding: 10,
    alignSelf: 'center',
    marginVertical: 10,
    backgroundColor: '#812892',
    elevation: 5,
    borderRadius: 5,
    flexDirection: 'row',
    justifyContent: 'space-between',
  },
  txt: {
    fontFamily: 'Raleway',
    fontStyle: 'normal',
    fontWeight: '900',
    color: '#FFFFFF',
    alignContent: 'center',
    textAlignVertical: 'center',
  },
  btntxt: {
    fontFamily: 'Raleway',
    fontStyle: 'normal',
    fontWeight: '900',
    color: '#812892',
  },
  btn: {
    width: 100,
    height: 40,
    alignItems: 'center',
    justifyContent: 'center',
    borderRadius: 5,
    backgroundColor: '#812892',

    padding: 10,
    alignSelf: 'center',
    marginVertical: 10,
    
    elevation: 5,
    
  },
});

export default LanguageSelector;
