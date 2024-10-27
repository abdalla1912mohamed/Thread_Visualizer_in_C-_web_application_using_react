import React from 'react'
import Button from '@mui/material/Button';

const BoddaButton = ({ sendMessage }) => {
  return (
    <Button
      variant="contained"
      sx={{ backgroundColor: '#1ba995', '&:hover': { backgroundColor: '#158f7b' } }}
      onClick={() => {
        sendMessage("C"); 
        alert('A new thread is created');
        console.log("createThread is sent");
      }}
    >
      Create thread
    </Button>
  );
};

export default BoddaButton;
