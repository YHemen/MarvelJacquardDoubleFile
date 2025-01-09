import React,{useEffect} from 'react';
import {View, Text, Alert, Button, BackHandler, Image, StyleSheet} from 'react-native';
import { TouchableOpacity } from 'react-native-gesture-handler';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";
const ExitScreen =() =>{
    const { t, i18n } = useTranslation();
    useEffect(() => {
          // Ensure re-render when language changes
          console.log('Current language:', i18n.language);
        }, [i18n.language]);
    useEffect(() => {
        Alert.alert(
            i18next.t('EXIT APP'),
            i18next.t('Are you sure you want to exit?'),
            // {t('EXIT APP')},
            // {t('Are you sure you want to exit?')},
            [
              { text: i18next.t('Cancel'), onPress: () => console.log('Cancel Pressed') },
              { text: i18next.t('ok'), onPress: () => BackHandler.exitApp() },
            ],
            { cancelable: false }
          );
      }, []);
    const exitApp = () =>{
        Alert.alert(
            i18next.t('EXIT APP'),
            i18next.t('Are you sure you want to exit?'),
            [
                { text: i18next.t('Cancel'), onPress: () => console.log('Cancel Pressed') },
                { text: i18next.t('ok'), onPress: () => BackHandler.exitApp() },
            ],
            { cancelable: false }
          );
    }
    return(
        <View style={styles.container}>
            {/* <Text>Exiting from Marvel Jacquards App please wait...!</Text> */}
            <Image source = {require('../assets/images/LOGO.png')} style={{flexDirection: 'row', width: 250, height: 200, alignContent: 'center', alignSelf: 'center' }} />
            {/* <Button title="Exit App" onPress={exitApp} style={{width: 200, height: 50, justifyContent: 'center', alignItems: 'center',}}/> */}
            <TouchableOpacity style={{width: 130, height: 40, justifyContent: 'center', alignItems: 'center', alignSelf: 'center', backgroundColor: 'purple'}} onPress={exitApp}>
                <Text style={{color:'white', justifyContent: 'center', alignItems: 'center', alignSelf: 'center'}}>{t('EXIT APP')}</Text>
            </TouchableOpacity>
        </View>
    );
}

export default ExitScreen;

const styles = StyleSheet.create({
    container:
    {
        flex: 1,
        justifyContent:"center",
        alignItems: "center",
        backgroundColor: '#EFDBFE',
    },
})