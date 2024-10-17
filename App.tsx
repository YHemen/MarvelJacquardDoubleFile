import React, {useEffect, useState} from 'react';
import { AppState } from 'react-native';
import {MyContextProvider} from './Components/MyContext';
import AppNavigator from './Screens/AppNavigator';

// const [appState, setAppState] = useState(AppState.currentState);
const App: React.FC = () => (
  //   useEffect(() => {
  //   const handleAppStateChange = (nextAppState) => {
  //     if (nextAppState === 'background') {
  //       console.log('App is in the background');
  //       // Save the app state or data here if needed
  //     } else if (nextAppState === 'active') {
  //       console.log('App is in the foreground');
  //       // Restore or refresh the app state here if needed
  //     }
  //     setAppState(nextAppState);
  //   };

  //   AppState.addEventListener('change', handleAppStateChange);

  //   return () => {
  //     AppState.removeEventListener('change', handleAppStateChange);
  //   };
  // }, [])
  <MyContextProvider>
    <AppNavigator />
  </MyContextProvider>
);

export default App;
