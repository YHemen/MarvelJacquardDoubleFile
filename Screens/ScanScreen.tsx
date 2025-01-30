import React, { FC, useState, useCallback, useEffect } from "react";
import { Image,StatusBar,View, RefreshControl, FlatList, StyleSheet, Text } from "react-native";
import { useMyContext } from '../Components/MyContext';

import Animated, {
  useSharedValue,
  withTiming,
  SharedValue,
  Extrapolation,
  interpolate,
  useAnimatedStyle,
  withRepeat,
} from "react-native-reanimated";

export default function ScanScreen() {
const {
      bleDevice,
      isScanning, 
      renderItem,
      startScanning,
      isConnected,
        } = useMyContext();
        const [isRefreshing, setIsRefreshing] = useState(false);
                const [showMainComponent, setShowMainComponent] = useState(false);
                  // Function to handle the refresh
                  const onRefresh = useCallback(() => {
                    setIsRefreshing(true);
                    startScanning();
                    // Simulating an API call or refresh operation
                    setTimeout(() => {
                      setIsRefreshing(false); // Stop refreshing after 2 seconds
                    }, 5000);
                  }, []);
                
                   // Effect to handle showing/hiding MainComponent based on isScanning and isConnected
          useEffect(() => {
            if (!isScanning && isConnected) {
              setShowMainComponent(true);
        
              // Set a timer to hide the component after 8 seconds
              const timer = setTimeout(() => {
                setShowMainComponent(false);
              }, 8000); // 8 seconds (adjust as needed)
        
              // Cleanup the timer when isConnected changes or the component unmounts
              return () => clearTimeout(timer);
            } else {
              // Reset the state if isScanning is true or isConnected becomes false
              setShowMainComponent(false);
            }
          }, [isScanning, isConnected]); // The effect runs when either isScanning or isConnected changes
  return (
    <>
    <StatusBar backgroundColor= "#812892"/>
    <View style={styles.container}>
      <FlatList
        data={isScanning ? [] : bleDevice} // Show an empty list or the actual device list depending on scanning state
        keyExtractor={(item, index) => index.toString()}
        renderItem={renderItem}
        refreshControl={
          <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
        }
        ListFooterComponent={
          isScanning && (
            <View style={styles.ripple}>
              <Image
                source={require('../assets/images/scanning5.gif')}
                style={styles.image}
              />
            </View>
          )
        }
      />
    </View>

    <View style={styles.container}>
      <ProgressIndicator
        duration={1000}
        itemWidth={16}
        itemHeight={8}
        itemsOffset={4}
        topScale={4}
      />
    </View>

    </>
    
  );
}

export const ProgressIndicator: FC<{
  count?: number;
  itemWidth?: number;
  itemHeight?: number;
  duration?: number;
  itemsOffset?: number;
  topScale?: number;
}> = ({
        count = 8,
        itemWidth = 16,
        itemHeight = 4,
        duration = 5000,
        itemsOffset = 4,
        topScale = 4,
      }) => {
  const progress = useSharedValue(0);

  useEffect(() => {
    progress.value = withRepeat(withTiming(1, { duration }), -1, true);
  }, []);

  return (
    <>
    {/* <StatusBar backgroundColor= "#812892"/>
    <View style={styles.container}>
      <FlatList
        data={isScanning ? [] : bleDevice} // Show an empty list or the actual device list depending on scanning state
        keyExtractor={(item, index) => index.toString()}
        renderItem={renderItem}
        refreshControl={
          <RefreshControl refreshing={isRefreshing} onRefresh={onRefresh} />
        }
        ListFooterComponent={
          isScanning && (
            <View style={styles.ripple}>
              <Image
                source={require('../assets/images/scanning5.gif')}
                style={styles.image}
              />
            </View>
          )
        }
      />
    </View> */}
    <View><Text>Connecting Please</Text></View>
    <View
      style={{
        flexDirection: "row",
        justifyContent: "space-between",
        alignItems: "center",
        height: itemHeight * topScale,
        width: (itemWidth + itemsOffset) * count,
      }}
    >
      {[...Array(count)].map((x, index) => (
        <ProgressItem
          key={`progressItem${index}`}
          index={index}
          width={itemWidth}
          height={itemHeight}
          count={count}
          topScale={topScale}
          progress={progress}
        />
      ))}
    </View>
    </>
  );
};

export const ProgressItem: FC<{
  index: number;
  count: number;
  width: number;
  height: number;
  topScale: number;
  progress: SharedValue<number>;
}> = ({ index, width, height, count, topScale, progress }) => {
  const animatedStyle = useAnimatedStyle(() => {
    const parts = 3;
    const wholeCount = count - 1 + 2 * parts;
    const scaleY = interpolate(
      progress.value,
      [
        index / wholeCount,
        (index + parts) / wholeCount,
        (index + 2 * parts) / wholeCount,
      ],
      [1, topScale, 1],
      Extrapolation.CLAMP
    );
    return {
      transform: [{ scaleY }],
    };
  });
  return (
    <Animated.View
      style={[
        {
          width,
          height,
          backgroundColor: "black",
        },
        animatedStyle,
      ]}
    />
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: "#EFDBFE",
    alignItems: "center",
    justifyContent: "center",
  },
  ripple: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    width: '100%', // Ensure that it takes full width
    height: '100%', // Ensure it takes full height
    marginTop: 100,
  },
  image: {
    width: 200,
    height: 200
  },
    rippletxt:{
        // flex: 1,
        justifyContent: 'center',
        alignItems: 'center',
    },
    usrbgc: 
    {
        backgroundColor: '#ffffff',
        width: 100,
        height: 100,
        padding:3,
        alignSelf:"center",
        marginVertical:0,
         elevation:5,
        borderRadius:50,
        flexDirection: 'row',
        // justifyContent: 'space-between',
    },
    usrCard:
    {
        width:"80%",
        marginTop: 160,
        padding:10,
        alignSelf:"center",
        marginVertical:10,
        backgroundColor:'#EFDBFE',
        elevation:0,
        borderRadius:0,
        flexDirection: 'row',
        justifyContent: 'space-between'
    },
    txt: {
        fontFamily: "Raleway", fontStyle: "regular", fontWeight: "900", color: 'white', alignContent: 'center', textAlignVertical: 'center'
    },
    btntxt: {
        fontFamily: "Raleway", fontStyle: "bold", fontWeight: "900"
    },
    btn: {
        width: 100,
        height: 40,
        alignItems: 'center',
        justifyContent: 'center',
        borderRadius: 5,
        backgroundColor: '#812892'
    },
});