import React, { useState } from 'react';
import { View, Text, StyleSheet, TouchableOpacity } from 'react-native';
import i18next from 'i18next';
import { useTranslation } from 'react-i18next';
import { DrawerContentScrollView, DrawerItemList } from '@react-navigation/drawer';
import Icon from 'react-native-vector-icons/FontAwesome';
import { Dropdown } from 'react-native-dropdown-select-list';

// Custom Drawer Content Component
const CustomDrawerContent = (props) => {
  const { t } = useTranslation();
  const [selectedLanguage, setSelectedLanguage] = useState(i18next.language); // Initially selected language
  
  // List of languages for dropdown
  const languages = [
    { label: 'English', value: 'en' },
    { label: 'Telugu', value: 'te' },
    { label: 'Kannada', value: 'kn' },
    { label: 'Hindi', value: 'hi' },
  ];

  // Function to change the language
  const handleLanguageChange = (languageCode: string) => {
    i18next.changeLanguage(languageCode);
    setSelectedLanguage(languageCode); // Update the selected language state
  };

  return (
    <DrawerContentScrollView {...props}>
      <View style={styles.header}>
        <Icon name="bars" size={30} color="#812892" />
        <Text style={styles.name}>Marvel Jacquards</Text>
      </View>

      {/* Language Dropdown */}
      <View style={styles.languageSelector}>
        <Text style={styles.languageLabel}>{t('change-lang')}</Text>
        <Dropdown
          data={languages}
          value={selectedLanguage}
          onChange={item => handleLanguageChange(item.value)}
          labelField="label"
          valueField="value"
          placeholder="Select Language"
          style={styles.dropdown}
          textStyle={styles.dropdownText}
        />
      </View>

      <DrawerItemList {...props} />
    </DrawerContentScrollView>
  );
};

const styles = StyleSheet.create({
  header: {
    padding: 5,
    alignItems: 'center',
    backgroundColor: '#e8c8ff',
  },
  name: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#812892',
  },
  languageSelector: {
    marginVertical: 20,
    paddingHorizontal: 10,
    alignItems: 'center',
  },
  languageLabel: {
    fontSize: 16,
    color: '#333',
    marginBottom: 10,
  },
  dropdown: {
    width: 200,
    backgroundColor: '#fff',
    borderRadius: 5,
    paddingVertical: 10,
    paddingHorizontal: 15,
    borderWidth: 1,
    borderColor: '#812892',
  },
  dropdownText: {
    fontSize: 16,
    color: '#333',
  },
});

export default CustomDrawerContent;
