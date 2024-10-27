import * as React from 'react';
import Box from '@mui/material/Box';
import Card from '@mui/material/Card';
import CardActions from '@mui/material/CardActions';
import CardContent from '@mui/material/CardContent';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';

const bull = (
  <Box
    component="span"
    sx={{ display: 'inline-block', mx: '2px', transform: 'scale(0.8)' }}
  >
    •
  </Box>
);

export default function GenericCard({
  name,
  value
}) {
  return (
    <Card sx={{ width: 250, padding: 2, backgroundColor: '#060c41', borderColor: '#1ba995', borderWidth: 4, borderStyle: 'solid', borderRadius: 10 }}>
      <CardContent>
        {/* <Typography gutterBottom sx={{ color: 'text.secondary', fontSize: 14 }}>
          Word of the Day
        </Typography> */}
        <Typography sx ={{ color: 'white' }} variant="h5" component="div">
          {name}
        </Typography>
        <Typography sx={{ color: 'white'}} variant="h6" >  Count: {value}</Typography>
        {/* <Typography variant="body2">
          well meaning and kindly.
          <br />
          {'"a benevolent smile"'}
        </Typography> */}
      </CardContent>
      {/* <CardActions>
        <Button size="small">Learn More</Button>
      </CardActions> */}
    </Card>
  );
}
