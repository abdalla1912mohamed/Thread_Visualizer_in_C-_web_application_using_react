import { Box, Card, CardContent, Slider, Typography } from '@mui/material';
import React, { useEffect } from 'react'
import GenericCard from './Card';

function StatusDashboard({ sleepCount =0 , blockedCount=0 , runCount=0 ,idleCount=0 , terminatedCount =0  }) {
// takes prop and arguments of the threads states count 
let threadCount = sleepCount+blockedCount+runCount+idleCount+terminatedCount ;
    useEffect(() => {
        console.log("inside status dashboard " + threadCount)
    }, [sleepCount , blockedCount , runCount ,idleCount , terminatedCount]) // rerun effect when count changes

    return (
        <>
            <Box sx={{
                display: 'flex',
                flexDirection: 'row',
                justifyContent: 'flex-start',
                gap: 2,
            }}>
                <Card sx={{ width: 350, padding: 2, backgroundColor: '#060c41', borderColor: '#1ba995', borderWidth: 4, borderStyle: 'solid', borderRadius: 10 }}>
                    <CardContent>
                        {/* <Typography sx={{ color: 'white' }} variant="h4" component="div">Threads info:</Typography> */}
                        <Typography sx={{ color: 'white' }} variant="h5" component="div">Total threads: {threadCount}</Typography>
                        <Slider
                            aria-label="Temperature"
                            //defaultValue={0}
                            // getAriaValueText={valuetext}
                            valueLabelDisplay="auto"
                            // shiftStep={30}
                            // step={10}
                            // marks
                            value={threadCount}
                            min={0}
                            max={512}
                            disabled 
                        />
                           <Typography sx={{ color: 'white' }} variant="h7" component="div"> Remaining Thread Capacity : {512-threadCount}</Typography>
                    </CardContent>
                </Card>
                <GenericCard name={"Sleeping Threads"} value={sleepCount} />
                <GenericCard name={"Blocked Threads"} value={blockedCount} />
                <GenericCard name={"Running Threads"} value={runCount} />
                <GenericCard name={"Idle Threads"} value={idleCount} />
                <GenericCard name={"Terminated Threads"} value={terminatedCount} />
            </Box>
        </>
    )
}

export default StatusDashboard;
