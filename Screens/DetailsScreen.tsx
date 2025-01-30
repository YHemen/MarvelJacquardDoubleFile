import React, { useState, useEffect } from 'react';
import { View, Text, ScrollView, StyleSheet } from 'react-native';
import { useTranslation } from 'react-i18next'; // Hook to access translation
import '../services/i18n';
import i18next from "i18next";

const DetailsScreen = ({ navigation }) => {
  const { t, i18n } = useTranslation();
  
  useEffect(() => {
    console.log('Current language:', i18n.language);
  }, [i18n.language]);

  const data = [
    { col1: 'Hooks', col2: '448, 640, 960, 1248, 1280, 1344, 1440, 1536, 2688' },
    { col1: 'Module type', col2: 'M5' },
    { col1: 'Lift', col2: 'Double lift type' },
    { col1: 'Drive', col2: 'Chain & Timing pulley with high quality material' },
    { col1: 'Speed', col2: 'Up to 375 RPM' },
    { col1: '1536-Hook', col2: '0.60 KW' },
    { col1: 'Display', col2: '20 Character x 4 line LCD display' },
    { col1: 'Shedding range', col2: '75 to 120 mm' },
    { col1: 'FRAME STRUCTURE', col2: 'Mild Steel' },
    { col1: 'HEIGHT', col2: 'Low Height (Compilable to install in lower height shed)' },
  ];
    
  const items = [
    'High Performance monocontrollers for optimum processing speed',
    'Unlimited Picks for single design in all jacquard',
    'Compatible with all types of design formats and platforms like : .BMP, .EP, .PAT, JCS., UPT., etc…',
    'Facility to put cut-mark at specific length for the elimination of length measurement for cutting.',
    'High speed USB port to Transfer Design / Data from Computer to Jacquard',
    'Pattern your design with desired repeat of each and every design (string) Separately',
    'Auto function to change design automatically as per defined sequence on completion of running design',
    '20 Character x 4 line LCD display to display message like Design Number, Repeat, Pick etc.',
    '32 GB Internal Storage that can load 64000 picks per Design',
    '578 Hook to 768 Hook – 0.35 KW, 864 Hook to 960 Hook – 0.60 KW, 1056 Hook to 1536 Hook – 072 KW,2432 Hook to 2688 Hook – 1.20 KW',
  ];
  return (
    <ScrollView style={styles.container}>
      <View style={styles.footerContainer}>
        <Text style={styles.footerText}>Marvel Jacquards Pvt LTD.</Text>
      </View>
      
      <View style={styles.header}>
        <Text style={styles.headerText}>Client Name:</Text>
        <Text style={styles.headerText}>SreeTextiles</Text>
      </View>
      <View style={styles.header}>
        <Text style={styles.headerText}>Content</Text>
        <Text style={styles.headerText}>Specification</Text>
      </View>

      {/* Rendering data rows */}
      {data.map((item, index) => (
        <View key={index} style={styles.row}>
          <Text style={styles.cell}>{item.col1}</Text>
          <Text style={styles.cell}>{item.col2}</Text>
        </View>
      ))}
      {items.map((item, index) => (
        <View key={index} style={styles.listItem}>
          <Text style={styles.bullet}>•</Text>
          <Text style={styles.itemText}>{item}</Text>
        </View>
      ))}
   
    </ScrollView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    padding: 20,
    paddingBottom: 30, // Added bottom padding to ensure space when scrolling to the end
  },
  header: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    marginBottom: 10,
    backgroundColor: '#f2f2f2',
    fontWeight: 'bold',
  },
  headerText: {
    fontWeight: 'bold',
    alignItems: 'center',
  },
  row: {
    flexDirection: 'row',
    justifyContent: 'space-between',
    paddingVertical: 2, // Increased vertical padding between rows
    marginBottom: 5, // Added margin between rows for better spacing
  },
  cell: {
    flex: 1,
    padding: 2,
    borderWidth: 0,
    backgroundColor: '#ececec',
    // borderColor: '#ccc',
    // textAlign: 'center', // Center align the text for better readability
  },
  listItem: {
    flexDirection: 'row',  // Ensure bullet and text are side by side
    alignItems: 'center',  // Vertically center the bullet and text
    marginBottom: 3,       // Add space between list items
  },
  bullet: {
    marginRight: 10, // Space between bullet and text
    fontSize: 18,    // Bullet size (adjust as needed)
  },
  itemText: {
    fontSize: 16,    // Adjust text size as needed
  },
  footerContainer: {
    backgroundColor: '#f1f1f1',  // Set the background color for the text container
    paddingVertical: 0,          // Add vertical padding for spacing around the text
    marginVertical: 10,          // Add margin to separate from other content
    
  },
  footerText: {
    textAlign: 'center',         // Center align the text horizontally
    fontSize: 18,                // Font size for the text
    fontWeight: 'bold',          // Make the text bold
    textDecorationLine: 'underline', // Underline the text
    textDecorationColor: '#000', // Set underline color (black in this case)
  },
});

export default DetailsScreen;
