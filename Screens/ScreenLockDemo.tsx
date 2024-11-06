import React, { useEffect, useState } from 'react';
import { View, Text, FlatList, ActivityIndicator } from 'react-native';
import axios from 'axios';

const ScreenLockDemo = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get('http://redsap.org/api.php'); // Update the URL to match your local setup
        setData(response.data);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  if (loading) {
    return <ActivityIndicator size="large" color="#0000ff" />;
  }

  if (error) {
    return <Text>Error: {error}</Text>;
  }

  return (
    <View>
      <FlatList
        data={data}
        keyExtractor={(item) => item.user_id} // Assuming user_id is numeric
        renderItem={({ item }) => (
          <View>
            <Text>User ID: {item.usr_id}</Text>
            <Text>User Name: {item.user_name}</Text>
            <Text>User Role: {item.role}</Text>
          </View>
        )}
      />
    </View>
  );
};

export default ScreenLockDemo;

