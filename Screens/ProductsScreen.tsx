import React, { useEffect } from 'react';
import { useNavigation } from '@react-navigation/native';
import { BackHandler, View, Text, FlatList, Image, StyleSheet, TouchableOpacity, Linking } from 'react-native';

const categories = [
  {
    id: '1',
    name: 'Electronic Jacquard Spare Parts',
    products: [
      { 
        id: '1', 
        name: 'Ciel Card', 
        image: require('../assets/images/clcard.jpg'),  // Local image from assets
        link: 'https://redsap.org'  // Example URL
      },
      { id: '2', name: 'Module', 
        image: require('../assets/images/module.jpg'), 
        link: 'https://redsap.org' 
      },
      { id: '3', name: 'Magnet', 
        image: require('../assets/images/magnet.jpg'), 
        link: 'https://redsap.org'
      },
      { id: '4', name: 'Bush', 
        image: require('../assets/images/bush.jpg'), 
        link: 'https://redsap.org'
      },
      { id: '5', name: 'Harness Thread', 
        image: require('../assets/images/harnessthread.jpg'), 
        link: 'https://redsap.org'
      },
      { id: '6', name: 'DataBus', 
        image: require('../assets/images/databus1.jpg'), 
        link: 'https://redsap.org'
      },
    ],
  },
  {
    id: '2',
    name: 'Electronic Jacquard Machines',
    products: [
      { 
        id: '7', 
        name: 'Power Loom', 
        image: require('../assets/images/jacquard.jpg'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '8', 
        name: 'Rapier', 
        image: require('../assets/images/jacquard.jpg'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '9', 
        name: 'Sulzer Loom', 
        image: require('../assets/images/jacquard.jpg'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '10', 
        name: 'LED Display', 
        image: require('../assets/images/DisplayLed1.jpg'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '11', 
        name: 'crowPanel', 
        image: require('../assets/images/crowPanel.jpg'), // Local image from assets
        link: 'https://redsap.org'
      },
    ],
  },
  {
    id: '3',
    name: 'Services',
    products: [
      { 
        id: '12', 
        name: 'Installation', 
        image: require('../assets/images/install.png'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '13', 
        name: 'Repair', 
        image: require('../assets/images/repair.png'), // Local image from assets
        link: 'https://redsap.org'
      },
      { 
        id: '14', 
        name: 'Replacement', 
        image: require('../assets/images/replacement1.png'), // Local image from assets
        link: 'https://redsap.org'
      },
    ],
  },
];

const ProductsScreen = () => {
  const navigation = useNavigation();

  // Handle back press event for navigation
  useEffect(() => {
    const handleBackPress = () => {
      navigation.navigate('Home Screen');
      return true;
    };
    BackHandler.addEventListener('hardwareBackPress', handleBackPress);

    return () => {
      BackHandler.removeEventListener('hardwareBackPress', handleBackPress);
    };
  }, [navigation]);

  // Handle product press to open the link
  const handleProductPress = (url) => {
    Linking.openURL(url).catch((err) => console.error("Failed to open URL", err));
  };

  // Render individual product items
  const renderProduct = ({ item }) => {
    return (
      <TouchableOpacity
        style={styles.productCard}
        onPress={() => handleProductPress(item.link)} // Open URL on press
      >
        <Image
          source={item.image}  // Local image loaded via require
          style={styles.productImage}
        />
        <Text style={styles.productName}>{item.name}</Text>
      </TouchableOpacity>
    );
  };

  // Render categories and products
  const renderCategory = ({ item }) => {
    return (
      <View style={styles.categoryContainer}>
        <Text style={styles.categoryTitle}>{item.name}</Text>
        <FlatList
          data={item.products}
          renderItem={renderProduct}
          keyExtractor={(product) => product.id}
          horizontal
          showsHorizontalScrollIndicator={false}
          contentContainerStyle={styles.productList}
        />
      </View>
    );
  };

  return (
    <View style={styles.container}>
      <FlatList
        data={categories}
        renderItem={renderCategory}
        keyExtractor={(category) => category.id}
        style={styles.container}
      />

      <View style={styles.footer}>
        <Text style={styles.footerText}>Address: 123 Marvel St, Muddireddypalli, Country</Text>
        <Text style={styles.footerText}>Phone: +123 456 7890</Text>
      </View>
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    paddingTop: 10,
    paddingHorizontal: 10,
  },
  categoryContainer: {
    marginBottom: 20,
    alignItems: 'center',
    justifyContent: 'center',
  },
  categoryTitle: {
    fontSize: 18,
    fontWeight: 'bold',
    marginBottom: 10,
    alignItems: 'center',
    justifyContent: 'center',
    color: '#812892',
  },
  productList: {
    paddingLeft: 5,
  },
  productCard: {
    width: 120,
    marginRight: 10,
    backgroundColor: '#fff',
    borderRadius: 10,
    padding: 10,
    justifyContent: 'center',
    alignItems: 'center',
    elevation: 5,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.8,
    shadowRadius: 3,
  },
  productImage: {
    width: 100,
    height: 100,
    borderRadius: 10,
  },
  productName: {
    marginTop: 8,
    textAlign: 'center',
    fontSize: 14,
    fontWeight: '600',
  },
  footer: {
    paddingVertical: 0,
    alignItems: 'center',
    marginTop: 0,
  },
  footerText: {
    fontSize: 12,
    color: '#333',
    fontWeight: 'bold',
  },
});

export default ProductsScreen;
