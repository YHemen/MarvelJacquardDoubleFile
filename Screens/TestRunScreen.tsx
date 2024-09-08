import React from 'react';
import {View,Text,StyleSheet,Dimensions, TouchableOpacity} from 'react-native';
import Icon from 'react-native-vector-icons/FontAwesome';
const TestRunScreen =() =>{
    return(
        <View style={styles.container}>
      <View style={styles.grid}>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 1')}>
            <Text style={styles.itemText}><Icon name="angle-double-up" size={20} color="#FFF" /></Text>
          <Text style={styles.itemText}>All UP </Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 2')}>
          <Text style={styles.itemText}><Icon name="angle-double-down" size={20} color="#FFF" /></Text>
          <Text style={styles.itemText}>All Down</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 3')}>
          <Text style={styles.itemText}><Icon name="level-up" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>8 UP</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 4')}>
          <Text style={styles.itemText}><Icon name="level-down" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>8 Down</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 5')}>
        <Text style={styles.itemText}><Icon name="angle-up" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>1 UP</Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 6')}>
        <Text style={styles.itemText}><Icon name="angle-down" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>1 Down </Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 7')}>
        <Text style={styles.itemText}><Icon name="angle-double-up" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>4 UP </Text>
        </TouchableOpacity>
        <TouchableOpacity style={styles.item} onPress={() => alert('Item 7')}>
        <Text style={styles.itemText}><Icon name="angle-double-down" size={20} color="#FFF" /></Text>  
          <Text style={styles.itemText}>4 Down </Text>
        </TouchableOpacity>
      </View>
    </View>
    );
}

const { width } = Dimensions.get('window');
const itemSize = width / 2; // Divide screen width by 3 to fit items

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
     backgroundColor: '#EFDBFE'
  },
  grid: {
    flexDirection: 'row',
    flexWrap: 'wrap',
    width: width,
    justifyContent: 'space-between',
    paddingStart: 40,
    paddingEnd: 40,
    paddingTop: 10,
    paddingBottom: 10
  },
  item: {
    width: itemSize - 80, // Adjust width with padding
    height: itemSize - 60, // Adjust height with padding
    backgroundColor: '#812892',
    justifyContent: 'center',
    alignItems: 'center',
    margin: 18, // Space between items
    borderRadius: 5,
  },
  itemText: {
    color: '#fff',
    fontSize: 16,
  },
});

export default TestRunScreen;

