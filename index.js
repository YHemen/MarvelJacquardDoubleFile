/**
 * @format
 */

import {AppRegistry} from 'react-native';
import App from './App';
import {name as appName} from './app.json';

AppRegistry.registerComponent(appName, () => App);
if (!__DEV__) 
{
console.log = () => {}; // Disable console.log
console.warn = () => {}; // Disable console.warn
console.error = () => {}; // Disable console.error
}