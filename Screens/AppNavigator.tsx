import React from 'react';
import HomeScreen from './HomeScreen';
import ScanningScreen from './ScanningScreen';
import FilesScreen from './FilesScreen';
import TestRunScreen from './TestRunScreen';
import SettingsScreen from './SettingsScreen';
import SplashScreen from './SplashScreen';
import DetailsScreen from './DetailsScreen';
import ExitScreen from './ExitScreen';
import {NavigationContainer} from '@react-navigation/native';
import {createNativeStackNavigator} from '@react-navigation/native-stack';
import {createDrawerNavigator} from '@react-navigation/drawer';
import Icon from 'react-native-vector-icons/FontAwesome';


import { View, Text, Image, StyleSheet, TouchableOpacity } from 'react-native';
import { DrawerContentScrollView, DrawerItemList,DrawerToggleButton } from '@react-navigation/drawer';

const CustomDrawerContent = (props) => {
  return (
    <DrawerContentScrollView {...props}>
      <View style={styles.header}>
        <Image
          source={require('../assets/images/LOGO.png')} // Replace with your icon URL or local file
          style={styles.icon}
        />
        <Text style={styles.name}>Marvel Jacquards</Text>
      </View>
      <DrawerItemList {...props} />
    </DrawerContentScrollView>
  );
};

// const Stack = createStackNavigator();
const Stack = createNativeStackNavigator();
const Drawer = createDrawerNavigator();

const AppDrawer = () => (
  <Drawer.Navigator drawerContent={(props) => <CustomDrawerContent {...props} />}  screenOptions={{
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
      headerLeft: false,
      headerRight: () => <DrawerToggleButton />,
      headerTitleAlign: "center",
  }}>
    <Drawer.Screen name="ScanDevices" component={ScanningScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="spinner" color={color} size={size} />),}}/>
    <Drawer.Screen name="Home" component={HomeScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="home" color={color} size={size} />),}} />
    <Drawer.Screen name="Files" component={FilesScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="file-text" color={color} size={size} />),}} />
    <Drawer.Screen name="TestRun" component={TestRunScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="code-fork" color={color} size={size} />),}} />
    <Drawer.Screen name="Settings" component={SettingsScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="wrench" color={color} size={size} />),}} />
    <Drawer.Screen name="Details" component={DetailsScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="cogs" color={color} size={size} />),}} />
    <Drawer.Screen name="Exit" component={ExitScreen} options={{drawerIcon: ({ color, size }) => (<Icon name="sign-out" color={color} size={size} />),}} />
  </Drawer.Navigator>
);

const AppNavigator: React.FC = () => (
  <NavigationContainer>
    <Stack.Navigator screenOptions={{headerShown: false}}>
      <Stack.Screen name="Splash" component={SplashScreen} />
      <Stack.Screen name="Main" component={AppDrawer} />
      {/* <Stack.Screen name="Login" component={LoginScreen} /> */}
    </Stack.Navigator>
  </NavigationContainer>
);

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
