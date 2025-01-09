import {MyContextProvider} from './Components/MyContext';
import AppNavigator from './Screens/AppNavigator';
const App: React.FC = () => (

  
  <MyContextProvider>
    <AppNavigator />
  </MyContextProvider>
  
);

export default App;
