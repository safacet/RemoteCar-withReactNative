import React, { Component } from 'react';
import {
  StyleSheet,
  Text,
  TouchableOpacity,
  View,
  StatusBar,
} from 'react-native';
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

  connect = () => {
    ws = new WebSocket('ws://192.168.1.100:81');

    ws.onopen = () => {
      // connection opened
      ws.send("!")
    };

    ws.onmessage = (e) => {
      // a message was received
      console.log("message", e.data);
    };

    ws.onerror = (e) => {
      // an error occurred
      console.log("error", e);
    };

    ws.onclose = (e) => {
      // connection closed
      console.log("close", e);
    };
  }

  disconnect = () => {
    ws = null;
  }


  componentDidMount() {


    Accelerometer.setUpdateInterval(120)
    this.subscription = Accelerometer.addListener(data => {
      this.setState({ x: data.x, y: data.y, z: data.z });
      try {
        this.dats = round(data.y) + '/' + round(data.x) + '?!';
        ws.send(this.dats);
      } catch {} 
    });
  }






  render() {
    return (
      <View style = {styles.mainContainer}>
        <StatusBar hidden = {false} barStyle = "default" />
      
      <View style={styles.sensor} >
        <Text style={styles.text}>Accelerometer:</Text>
        <Text style={styles.text}>
          x: {round(this.state.x)} y: {round(this.state.y)}
        </Text>
      </View>

      <View style={styles.buttonContainer} >
        <TouchableOpacity style = {styles.button}
         onPress={this.connect} 
         >
          
            <Text>CONNECT</Text>
          
        </TouchableOpacity>

        <TouchableOpacity style = {styles.button}
        
        onPress = {this.disconnect} >
            <Text> DISCONNECT </Text>
        </TouchableOpacity>
      </View>
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
    marginTop: 25,
    height: 50,
    marginHorizontal:25,
  },
  button: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#eee'
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
  mainContainer: {
    flexDirection: 'column',
    marginTop:100,
  }
});