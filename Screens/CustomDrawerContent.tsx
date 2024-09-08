import React from 'react';
import { View, Button, StyleSheet } from 'react-native';
import { DrawerContentScrollView, DrawerItemList } from '@react-navigation/drawer';
import { useAuth } from '../context/AuthContext';

const CustomDrawerContent = (props) => {
    const { logout } = useAuth();

    const handleLogout = async () => {
        await logout();
        props.navigation.navigate('Login'); // Navigate to Login screen after logout
    };

    return (
        <DrawerContentScrollView {...props}>
            <View style={styles.container}>
                <DrawerItemList {...props} />
                <Button title="Logout" onPress={handleLogout} />
            </View>
        </DrawerContentScrollView>
    );
};

const styles = StyleSheet.create({
    container: {
        flex: 1,
        justifyContent: 'flex-end',
        padding: 16,
    },
});

export default CustomDrawerContent;
