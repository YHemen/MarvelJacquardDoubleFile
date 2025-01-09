import React, { useEffect, useState, useCallback } from 'react';
import { View, Text, FlatList, ActivityIndicator, RefreshControl } from 'react-native';
import axios from 'axios';
import { useMyContext } from '../Components/MyContext';

const ScreenLockDemo: React.FC = () => {
  const { webData, setWebData} = useMyContext();  // Context to manage data
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [refreshing, setRefreshing] = useState(false);

  // Fetch data on initial render
  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get('http://redsap.org/api.php'); // API call
        console.log('Fetched data:', response.data);  // Log the fetched data to check its structure
        setWebData(response.data);  // Update context with fetched data
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    };

    fetchData();
  }, [setWebData]); // Dependency on setWebData

  // Handle pull-to-refresh 
  const onRefresh = useCallback(() => {
    setRefreshing(true);

    // Make an actual API call to fetch new data when refreshing
    axios.get('http://redsap.org/api.php')  // Use your actual API URL
      .then((response) => {
        // Update the context with the new data
        setWebData(response.data);
      })
      .catch((err) => {
        // Handle errors here if needed
        setError(err.message);
      })
      .finally(() => {
        // Stop the refreshing animation
        setRefreshing(false);
      });
  }, [setWebData]);  // Dependencies to ensure useCallback has correct references

  // Loading state
  if (loading) {
    return <ActivityIndicator size="large" color="#0000ff" />;
  }

  // Error state
  if (error) {
    return <Text>Error: {error}</Text>;
  }

  // Find the user with id: "2" (string comparison)
  const user = webData.find(item => item.usr_id === "2");  // Use string comparison for usr_id

  // If user with id: "2" exists, display their password, else display an error message
  const userPassword = user ? user.usr_pwd : 'User not found';
  setUserPass(userPassword);
  return (
    <View style={{ flex: 1 }}>
      <FlatList
        data={webData}  // Use webData from context
        keyExtractor={(item) => item.usr_id.toString()}  // Correct keyExtractor based on data structure
        renderItem={({ item }) => (
          <View style={{ padding: 10, borderBottomWidth: 1 }}>
            <Text>User ID: {item.usr_id}</Text>
            <Text>User Name: {item.usr_name}</Text>
            <Text>User Role: {item.usr_role}</Text>
            <Text>User Password: {item.usr_pwd}</Text>
          </View>
        )}
        refreshControl={
          <RefreshControl
            refreshing={refreshing}
            onRefresh={onRefresh}  // Refresh callback
          />
        }
      />

      {/* Display the password for user with ID "2" */}
      <View style={{ padding: 20 }}>
        <Text style={{ fontSize: 16, fontWeight: 'bold' }}>Password for User ID 2:</Text>
        <Text>{userPassword}</Text>
      </View>
    </View>
  );
};

export default ScreenLockDemo;
