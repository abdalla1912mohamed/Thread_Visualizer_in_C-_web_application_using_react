import * as React from 'react';
import Box from '@mui/material/Box';
import InputLabel from '@mui/material/InputLabel';
import MenuItem from '@mui/material/MenuItem';
import FormControl from '@mui/material/FormControl';
import Select from '@mui/material/Select';

const DropDown = ({options, value, onChange}) => {
  return (
    <Box sx={{ minWidth: 120 }}>
      <FormControl fullWidth>
        <InputLabel style={{ color: '#FFFFFF' }}>Filter</InputLabel>
        <Select
        style={{
            fontFamily: '"Roboto", "Helvetica", "Arial", sans-serif',
            fontWeight: 400,
            fontSize: '1.5rem',
            lineHeight: 1.334,
            letterSpacing: '0em',
            borderRadius: '15px',
            backgroundColor: '#1ba995'
          }}
          value={value}
          label="Filter"
          onChange={onChange}
        >
            <MenuItem value="F">
                <em>None</em>
            </MenuItem>
          {options.map((option) => (
            <MenuItem 
            key={option.value} 
            value={option.value}>
                {option.label}
            </MenuItem>
        ))}
        </Select>
      </FormControl>
    </Box>
  );
}

export default DropDown
