import React, { useState, useEffect } from 'react';
import { View, StyleSheet, TouchableOpacity, Text } from 'react-native';
import { useTranslation } from 'react-i18next';  // Import the hook
import AsyncStorage from '@react-native-async-storage/async-storage';


const LanguageSelector: React.FC = () => {
  const [currLang, setCurrLang] = useState<string | null>(null);  // Initially set to null to check if language is fetched
  const { t, i18n } = useTranslation();  // Access the i18n instance
  
  // Load the language from AsyncStorage when the component mounts
  useEffect(() => {
    const fetchStoredLanguage = async () => {
      try {
        const storedLang = await AsyncStorage.getItem('language');
        if (storedLang) {
          i18n.changeLanguage(storedLang);  // Change to the stored language if exists
          setCurrLang(storedLang);  // Set the current language state
        } else {
          // Default language if no stored language is found
          i18n.changeLanguage('en');
          setCurrLang('en');
        }
      } catch (error) {
        console.error('Error fetching language from AsyncStorage:', error);
      }
    };

    fetchStoredLanguage();  // Call the function to fetch the language when component mounts
  }, [i18n]);  // Dependency on i18n to avoid infinite re-renders

  // Change language and store it in AsyncStorage
  const changeLanguage = async (lang: string) => {
    console.log(`Changing language to: ${lang}`);
    i18n.changeLanguage(lang);  // Change the language dynamically
    setCurrLang(lang);  // Update the current language state

    try {
      await AsyncStorage.setItem('language', lang);  // Store the selected language in AsyncStorage
      console.log('Stored language:', lang);
    } catch (error) {
      console.error('Error saving language to AsyncStorage:', error);
    }
  };

  // If the language is not yet loaded, show a loading indicator
  if (currLang === null) {
    return <Text>Loading...</Text>;  // You can replace this with any loading indicator
  }

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
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#EFDBFE',
  },
  txt: {
    fontFamily: 'Raleway',
    fontStyle: 'normal',
    fontWeight: '900',
    color: '#FFFFFF',
    alignContent: 'center',
    textAlignVertical: 'center',
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
