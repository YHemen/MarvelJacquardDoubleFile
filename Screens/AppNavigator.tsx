// AppNavigator.tsx
// import React from 'react';
import React, {useState,useEffect, useCallback} from 'react';
import HomeScreen from './HomeScreenSingle';
import ScanningScreen from './ScanningScreen';
import FilesScreen from './FilesScreen';
import TestRunScreen from './TestRunScreen';
import SettingsScreen from './SettingsScreen';
import SplashScreen from './SplashScreen';
import DetailsScreen from './DetailsScreen';
import ExitScreen from './ExitScreen';
import LoadingScreen from './LoadingScreen';
import ProductsScreen from './ProductsScreen';
import ControllerFile from './ControllerFile';
import { useNavigation } from '@react-navigation/native';
import {useMyContext} from '../Components/MyContext';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import { createDrawerNavigator } from '@react-navigation/drawer';
import Icon from 'react-native-vector-icons/FontAwesome';
import { View, Text, Image, StyleSheet, TouchableOpacity } from 'react-native';
import { DrawerContentScrollView, DrawerItemList, DrawerToggleButton } from '@react-navigation/drawer';
import LanguageSelector from '../services/LanguageSelector';
import { useTranslation } from 'react-i18next'; // Import useTranslation at the top
import '../services/i18n';
import i18next from "i18next";
import ScanScreen from './ScanScreen';
// Custom Drawer Content
const CustomDrawerContent = (props) => {
  const { t, i18n } = useTranslation();
  return (
    <DrawerContentScrollView {...props}>
      <View style={styles.header}>
        <Image
          source={require('../assets/images/LOGO.png')} // Replace with your icon URL or local file
          style={styles.icon}
        />
        <Text style={styles.name}>{t('Marvel Jacquards')}</Text>
      </View>
      <DrawerItemList {...props} />
    </DrawerContentScrollView>
  );
};

// Create a Native Stack Navigator and Drawer Navigator
const Stack = createNativeStackNavigator();
const Drawer = createDrawerNavigator();

// AppDrawer component
const AppDrawer = ({isConnected}) => {
  // Place the useTranslation hook here, before the return statement
  const { t } = useTranslation();  // Now you can use 't' for translations inside this component
  // const { isConnected } = useMyContext(); 
    // console.log("isConnected",isConnected);
     // Debugging to ensure isConnected is correctly passed and updated
  useEffect(() => {
    // console.log('Drawer is Connected:', isConnected);
  }, [isConnected]);  // Log whenever isConnected changes
  const navigation = useNavigation(); // Use navigation hook

  // useEffect(() => {
  //   if (isConnected) {
  //     // Navigate to HomeScreen when isConnected becomes true
  //     navigation.navigate('HomeScreen');
  //   }
  // }, [isConnected, navigation]); // Watch for changes in isConnected
  useEffect(() => {
    if (isConnected) {
      // Set a timeout to navigate to HomeScreen after 8 seconds
      const timer = setTimeout(() => {
        navigation.navigate('Home Screen');
      }, 8000); // 8000 milliseconds = 8 seconds
  
      // Clean up the timeout when the component unmounts or isConnected changes
      return () => clearTimeout(timer);
    }
  }, [isConnected, navigation]);

    return (
    <Drawer.Navigator 
      drawerLockMode={isConnected ? 'unlocked' : 'locked'}
      key={isConnected ? 'unlocked' : 'locked'} 
      gestureEnabled={isConnected}
      drawerContent={(props) => <CustomDrawerContent {...props} />}  
      screenOptions={{
        drawerStyle: {
          backgroundColor: '#e8c8ff', // Set the background color here as well if needed
          width: 240,
          height: 751,
        },
        drawerActiveBackgroundColor: '#9f149f', // Background color of the selected item
        drawerActiveTintColor: '#ffffff', // Text color of the selected item
        drawerInactiveBackgroundColor: 'transparent', // Background color of non-selected items
        drawerInactiveTintColor: '#000000', // Text color of non-selected items
        drawerLabelStyle: {
          fontSize: 16,
          fontWeight: 'bold',
        },
        headerStyle: {
          backgroundColor: '#812892',
        },
        headerTintColor: '#fff',
        headerTitleStyle: {
          fontWeight: 'bold',
        },
        drawerPosition: 'right',
        headerLeft: () => (
          isConnected ? (
            <TouchableOpacity onPress={() => console.log('Hamburger clicked!')}>
              <Text style={styles.hamburgerButton}></Text>
            </TouchableOpacity>
          ) : null
        ),
        headerRight: () => (
          isConnected ? (
            <DrawerToggleButton />
          ) : null
        ),
        headerTitleAlign: "center",
      }}
    >
      <Drawer.Screen 
        name="ScanDevices"
        component={ScanningScreen} 
        // options={{
        //   drawerIcon: ({ color, size }) => (<Icon name="spinner" color={color} size={size} />),
        //   title: t('ScanDevices'),
        // }} 
        options={{
          headerLeft: () => (
            isConnected ? (
              <TouchableOpacity onPress={() => console.log('Hamburger clicked!')}>
                 <Text style={styles.hamburgerButton}><Icon name="copy" color="white" size={20} /></Text>
                 <Text style={{color: 'white'}}>Merge</Text>
              </TouchableOpacity>
            ) : null
          ),
          drawerIcon: ({ color, size }) => (<Icon name="spinner" color={color} size={size} />),
          title: t('ScanDevices'),
        }} 
      />
      {/* <Drawer.Screen 
        name= "HomeScreen" 
        // name={t('Home', { defaultValue: 'Home' })}
        component={HomeScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="home" color={color} size={size} />),
          title: t('HomeScreen')
        }} 
      /> */}
      <Drawer.Screen 
        name={t('Home Screen')} 
        component={ControllerFile} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="home" color={color} size={size} />),
        }} 
      /> 
      <Drawer.Screen 
        name={t('Files')} 
        component={FilesScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="file-text" color={color} size={size} />),
        }} 
      />
      <Drawer.Screen 
        name={t('TestRun')} 
        component={TestRunScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="code-fork" color={color} size={size} />),
        }} 
      />
      <Drawer.Screen 
        name={t('Settings')} 
        component={SettingsScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="wrench" color={color} size={size} />),
        }} 
      />
      <Drawer.Screen 
        name={t('Details')} 
        component={DetailsScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="cogs" color={color} size={size} />),
        }} 
      />
      
      {/* <Drawer.Screen 
        name={t('SelectLanguage')} 
        component={LanguageSelector} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="language" color={color} size={size} />),
        }} 
      /> */}
      <Drawer.Screen 
        name={t('ProductsScreen')} 
        component={ProductsScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="shopping-cart" color={color} size={size} />),
        }} 
      />
      {/* <Drawer.Screen 
        name={t('Home Screen')} 
        component={ControllerFile} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="language" color={color} size={size} />),
        }} 
      />  */}
      <Drawer.Screen 
        name={t('SelectLanguage')} 
        component={LanguageSelector} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="language" color={color} size={size} />),
        }} 
      />
      <Drawer.Screen 
        name={t('Exit')} 
        component={ExitScreen} 
        options={{
          drawerIcon: ({ color, size }) => (<Icon name="sign-out" color={color} size={size} />),
        }} 
      />
    </Drawer.Navigator>
  );
};



// AppNavigator component
const AppNavigator: React.FC = () => {
  const { isConnected} = useMyContext(); // Access the context
  return (
    <NavigationContainer>
      <Stack.Navigator screenOptions={{ headerShown: false }}>
        <Stack.Screen name="Splash" component={SplashScreen} />
        <Stack.Screen 
          name="Main" 
          children={() => <AppDrawer isConnected={isConnected} />} // Pass isConnected as prop to AppDrawer
        />
      </Stack.Navigator>
    </NavigationContainer>
  );

};

const styles = StyleSheet.create({
  header: {
    padding: 5,
    alignItems: 'center',
    backgroundColor: '#e8c8ff', // Adjust background color as needed
  },
  icon: {
    width: 130,
    height: 100,
    borderRadius: 20,
    marginBottom: 10,
  },
  name: {
    fontSize: 18,
    fontWeight: 'bold',
    color: '#812892'
  },
});

export default AppNavigator;
