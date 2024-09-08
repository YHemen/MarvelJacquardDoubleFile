// App.tsx
import React from 'react';
import { NavigationContainer } from '@react-navigation/native';
import { MyContextProvider } from './Components/MyContext';
import AppNavigator from './Screens/AppNavigator';

const App: React.FC = () => (
  <MyContextProvider>
    {/* <NavigationContainer> */}
      <AppNavigator />
    {/* </NavigationContainer> */}
  </MyContextProvider>
);

export default App;
