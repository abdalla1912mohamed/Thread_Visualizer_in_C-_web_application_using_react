import * as React from 'react';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import TablePagination from '@mui/material/TablePagination';
import Paper from '@mui/material/Paper';
import { IconButton } from '@mui/material';
import DeleteIcon from '@mui/icons-material/Delete';
import LockIcon from '@mui/icons-material/Lock';
import LockOpenIcon from '@mui/icons-material/LockOpen';


export default function ThreadsTable({threadsData, sendMessage}) {
  const [page, setPage] = React.useState(0);
  const [rowsPerPage, setRowsPerPage] = React.useState(10);

  const handleTerminateThread = (threadID) => {
    sendMessage("D" + threadID);
  }

  const handleLock = (threadID)=>{
    sendMessage("M" + threadID);
  }

  function createData(threadData) {
    return threadData.map(data => ({
      name: data.name,
      threadId: data.threadId,
      status: data.status,
      threadPriority: data.threadPriority,
      activeTime: data.activeTime, // JSON FORMAT 
      isLocked: data.isLocked
    }));
  }
  const rows = createData(threadsData);

  const handleChangePage = (event, newPage) => {
    setPage(newPage);
  };

  const handleChangeRowsPerPage = (event) => {
    setRowsPerPage(+event.target.value);
    setPage(0);
  };

  return (
    <Paper sx={{ width: '100%' }}>
    <TableContainer component={Paper} sx={{ height: ''}}>
      <Table sx={{ minWidth: 650 }} aria-label="simple table">
        <TableHead>
          <TableRow>
            <TableCell>Thread Name </TableCell>
            <TableCell align="right">Thread ID</TableCell>
            <TableCell align="right">Status&nbsp;</TableCell>
            <TableCell align="right">Thread Priority&nbsp;</TableCell>
            <TableCell align="right">Active Time&nbsp;</TableCell>
            <TableCell align="right"> Mutex &nbsp;</TableCell> 
            <TableCell align="right"> Actions&nbsp;</TableCell>
            
          </TableRow>
        </TableHead>
        <TableBody>
          {rows.slice(page * rowsPerPage, page * rowsPerPage + rowsPerPage).map((row) => (
            <TableRow
              key={row.name}
              sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
            >
              <TableCell component="th" scope="row">
                {row.name}
              </TableCell>
              <TableCell align="right">{row.threadId}</TableCell>
              <TableCell align="right">{row.status}</TableCell>
              <TableCell align="right">{row.threadPriority}</TableCell>
              <TableCell align="right">{row.activeTime}</TableCell>
              <TableCell align="right"> 
                {  row.isLocked?<IconButton 
                    onClick={() => handleLock(row.threadId)}
                    aria-label="locked or not locked">
                    <LockIcon />
                </IconButton> : <IconButton 
                    onClick={() => handleLock(row.threadId)}
                    aria-label="locked or not locked">
                    <LockOpenIcon />
                </IconButton> }        </TableCell> 
              <TableCell align="right">
                <IconButton 
                    onClick={() => handleTerminateThread(row.threadId)}
                    aria-label="delete">
                    <DeleteIcon />
                </IconButton>
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
    <TablePagination
    rowsPerPageOptions={[10, 25, 100]}
    component="div"
    count={rows.length}
    rowsPerPage={rowsPerPage}
    page={page}
    onPageChange={handleChangePage}
    onRowsPerPageChange={handleChangeRowsPerPage}
  />
  </Paper>
  );
}