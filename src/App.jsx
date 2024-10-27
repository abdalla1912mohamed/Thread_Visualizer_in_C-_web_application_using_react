import { useEffect, useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import BoddaButton from './components/Button'
import './App.css'
import GenericCard from './components/Card'
import { Box, TextField } from '@mui/material'
import StatusDashboard from './components/StatusDashboard'
import ThreadsTable from './components/ThreadsTable'
import useWebSocket from 'react-use-websocket';
import DropDown from './components/DropDown'
import SearchBar from './components/SearchBar'
function App() {
  const[threadCount,setThreadCount] = useState(0);
  const [idleCount, setIdleCount] = useState(0);
  const [runCount, SetRunCount] = useState(0);
  const [sleepCount, setSleepCount] = useState(0);
  const [blockedCount, setBlockedCount] = useState(0);
  const [terminatedCount, SetTerminatedCount] = useState(0);
  const[threadsData,setThreadsData] = useState([]) ; 

  const [selectedValue, setSelectedValue] = useState('F');

  const {
    sendMessage,
    lastMessage,
  } = useWebSocket("ws://localhost:3004", {
    onOpen: () => {
      console.log('opened');
      sendMessage(selectedValue)
    },
    //Will attempt to reconnect on all close events, such as server shutting down
    shouldReconnect: (closeEvent) => true,
    onError: (error) => console.log("Error " + error)
  });

  const handleChange = (event) => {
    setSelectedValue(event.target.value);
  };

  const updateSelectedValue = (value) => {
    setSelectedValue(value);
  };


  useEffect(() => {
    if (lastMessage) {
      let parsedData = JSON.parse(lastMessage.data)
      setThreadCount(parsedData.threadCount)
      setIdleCount(parsedData.idleCount)
      SetRunCount(parsedData.runCount)
      setSleepCount(parsedData.sleepCount)
      setBlockedCount(parsedData.blockedCount) // sum of the threads from the json 
      SetTerminatedCount(parsedData.terminatedCount)
      setThreadsData(parsedData.threadsData)

      const intervalId = setInterval(() => {
        sendMessage(selectedValue); 
      }, 500); 

      return () => {
        clearInterval(intervalId);
      };
    }
  }, [lastMessage]);

  const options = [
    { label: 'Idle', value: 'I' },
    { label: 'Running', value: 'R' },
    { label: 'Sleeping', value: 'S' },
    { label: 'Terminated', value: 'T' },
    { label: 'Blocked', value: 'B' }
  ];

  return (
    <>
      <Box sx={{
        backgroundColor: '#060c41',
        minHeight: '100vh'
      }}>

        <Box sx={{
          p: 2,
          display: 'flex',
          flexDirection: 'column',
          gap: 3,
        }}>
          <StatusDashboard sleepCount={sleepCount} blockedCount={blockedCount} 
        runCount = {runCount} idleCount = {idleCount}  terminatedCount={terminatedCount}/>
          <Box sx={{
            display: 'flex',
            flexDirection: 'row',
            justifyContent: 'space-between',
            gap: 2
          }}>
            <BoddaButton  sendMessage = {sendMessage} />
            <SearchBar 
            sendMessage = {sendMessage} 
            onChange={updateSelectedValue}></SearchBar>
            <DropDown 
              options={options}
              value={selectedValue}
              onChange={handleChange}>
            </DropDown>
          </Box>
          <ThreadsTable  threadsData ={threadsData} sendMessage={sendMessage}/>
        </Box>
      </Box>
    </>
  )
}

export default App
