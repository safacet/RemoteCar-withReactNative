import React, { Component } from 'react';
import { StyleSheet, Text, TouchableOpacity, View } from 'react-native';
import { Accelerometer } from 'expo-sensors';



export default class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      x: 0,
      y: 0,
      z: 0,
    };
  }

  componentDidMount() {
     
      Accelerometer.setUpdateInterval(100)
      this.subscription = Accelerometer.addListener( data => {
        this.setState({ x: data.x, y: data.y, z: data.z })
      });
      this.ws = new WebSocket('wss://echo.websocket.org');
      this.ws.onmessage = (e) => {
        this.ws.send('HTTP GET Request 300')
        console.log('onmessage', e)
      }
      this.ws.onerror = (e) => {
        console.log('error',e)
      }
      this.ws.onmessage = (e) => {
        console.log(e)
      }
  }

  
  
  
  

  render() {
    return (
      <View style={styles.sensor}>
        <Text style={styles.text}>Accelerometer: (in Gs where 1 G = 9.81 m s^-2)</Text>
        <Text style={styles.text}>
          x: {round(this.state.x)} y: {round(this.state.y)}
      </Text>
      </View>
    );
  }
}

function round(n) {
  if (!n) {
    return 0;
  }

  return Math.floor(n * 100) / 100;
}

const styles = StyleSheet.create({
  buttonContainer: {
    flexDirection: 'row',
    alignItems: 'stretch',
    justifyContent: 'center',
    marginTop: 15,
  },
  button: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#eee',
    padding: 10,
  },
  middleButton: {
    borderLeftWidth: 1,
    borderRightWidth: 1,
    borderColor: '#ccc',
  },
  sensor: {
    marginTop: 45,
    paddingHorizontal: 10,
  },
  text: {
    textAlign: 'center',
  },
});