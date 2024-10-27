import * as React from 'react';
import Box from '@mui/material/Box';
import IconButton from '@mui/material/IconButton';
import OutlinedInput from '@mui/material/OutlinedInput';
import InputLabel from '@mui/material/InputLabel';
import InputAdornment from '@mui/material/InputAdornment';
import FormControl from '@mui/material/FormControl';
import SearchIcon from '@mui/icons-material/Search';

export default function SearchBar({onChange}) {
    const [searchValue, setSearchValue] = React.useState("");

    const handleSearchValueChange = (event) => {
        setSearchValue(event.target.value);
    };

    const handleClick = () => {
        onChange("E" + searchValue);
    };

    return (
        <Box sx={{ display: 'flex', flexWrap: 'wrap', width: '100%', backgroundColor: '#FFFFFF' }}>
            <div>
                <FormControl fullWidth sx={{ m: 1}} variant="outlined">
                <InputLabel>Search</InputLabel>
                <OutlinedInput
                    value={searchValue}
                    onChange={handleSearchValueChange} 
                    endAdornment={
                    <InputAdornment position="end">
                        <IconButton
                        onClick={handleClick}
                        edge="end"
                        >
                        {<SearchIcon />}
                        </IconButton>
                    </InputAdornment>
                    }
                    label="Search"
                />
                </FormControl>
            </div>
            
        </Box>
        )
}
