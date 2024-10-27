import WebSocket from 'ws';

var address = "ws://localhost:3003";

const ws = new WebSocket(address);

ws.on('open', function open() {
  console.log('Connected to server');
//   ws.send('Client message');
});

ws.on('message', function incoming(data) {
  console.log('Received JSON from server');
  
  // Parse the JSON data
  const jsonData = JSON.parse(data);
  
  console.log(jsonData);
  console.log('name:', jsonData.name);
  console.log('status:', jsonData.status);
  console.log('data:', jsonData.data);
});
