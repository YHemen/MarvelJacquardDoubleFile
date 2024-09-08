import React,{useContext} from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';
import { createDrawerNavigator } from '@react-navigation/drawer';

import SplashScreen from './Screens/SplashScreen';
import LogInScreen from './Screens/LogInScreen';
import HomeScreen from './Screens/HomeScreen'; // Example screen
import SettingsScreen from './Screens/SettingsScreen'; // Example screen
import { MyContextProvider,MyContext } from './Components/MyContext';

const Stack = createNativeStackNavigator();
const Drawer = createDrawerNavigator();

// const AppDrawer = () => (
//     <Drawer.Navigator>
//         <Drawer.Screen name="Home" component={HomeScreen} />
//         <Drawer.Screen name="Settings" component={SettingsScreen} />
//     </Drawer.Navigator>
// );

const App = () => (
 
    <NavigationContainer>
      <MyContextProvider>
        {/* <Stack.Navigator screenOptions={{ headerShown: false }}>
            <Stack.Screen name="Splash" component={SplashScreen} />
            <Stack.Screen name="Login" component={LogInScreen} />
            <Stack.Screen name="AppDrawer" component={AppDrawer} />
        </Stack.Navigator> */}
        <Drawer.Navigator>
        <Drawer.Screen name="Home" component={HomeScreen} />
        <Drawer.Screen name="Settings" component={SettingsScreen} />
    </Drawer.Navigator>
        </MyContextProvider>  
    </NavigationContainer>
);

export default App;
