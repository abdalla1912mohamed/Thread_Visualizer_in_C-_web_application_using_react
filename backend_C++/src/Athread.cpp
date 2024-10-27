#include"ATthread.hpp" 
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include<iostream>


std::recursive_mutex m ; 
 int AThread::default_id = 0 ;
AThread::AThread(): thread_id((++default_id)), name("A"+std::to_string(default_id)), status(Status::IDLE), Locked_M(false),hidden(false) {
creation_time = std::chrono::system_clock::now()  ; 


}

AThread::AThread( const int id ) : thread_id((id)) , status(Status::IDLE), Locked_M(false) , name("A"+std::to_string(id)) , hidden(false)    {
creation_time = std::chrono::system_clock::now()  ; 

}  
AThread::AThread(const int id , std::string name ) :    thread_id((id)) , status(Status::IDLE), Locked_M(false) , name(name) ,hidden(false){
creation_time = std::chrono::system_clock::now()  ; 
}

// Move constructor
AThread::AThread(AThread&& other) noexcept
    : A_thread(std::move(other.A_thread)),
      thread_id(other.thread_id),
      creation_time(other.creation_time),
      start_time(other.start_time),
      end_time(other.end_time),
      execution_time(other.execution_time),
      sleep_time(other.sleep_time),
      status(other.status),
      name(std::move(other.name)),
      Locked_M(other.Locked_M),
      hidden(other.hidden) {
    
    other.Locked_M = false;
    other.status = Status::IDLE;
}

// Move assignment operator
AThread& AThread::operator=(AThread&& other) noexcept {
    if (this != &other) {
        if (A_thread.joinable()) {
            A_thread.join();
        }

        A_thread = std::move(other.A_thread);
        thread_id = other.thread_id;
        creation_time = other.creation_time;
        start_time = other.start_time;
        end_time = other.end_time;
        execution_time = other.execution_time;
        sleep_time = other.sleep_time;
        status = other.status;
        name = std::move(other.name);
        Locked_M = other.Locked_M;
        hidden = other.hidden;

        // Reset other to a default state
        other.Locked_M = false;
        other.status = Status::IDLE;
    }
    return *this;
}

void AThread::set_to_joined() {
    if(A_thread.joinable()){
    this->A_thread.join() ;
    } 
}
bool AThread::isJoinable(){
    return A_thread.joinable() ; 
}
bool AThread::isHidden() {
    return hidden ; 
}; 
void AThread::setHiddenON(){
hidden = true ; 
}
 
AThread::~AThread(){
    if( A_thread.joinable()){
        
       // destructor makes sure it joins the thread  
       A_thread.join() ; 
      // setStatus(Status::TERMINATED) ; 
       end_time = std::chrono::system_clock::now() ; 
    }
    setStatus(Status::TERMINATED) ; 
    auto d = end_time - start_time ;
     
    // std::cout<<" \n thread took "<< d.count()/1e9<<"\n" ; 
}

void AThread::setStatus(Status s ) {
  std::unique_lock<std::recursive_mutex> lock(A_Rmutex) ; 
    this->Locked_M = true ;
status = s ; 
this->Locked_M = false ; 
}
std:: string AThread::getStatus(){
switch(status){
case Status::BLOCKED : 
                      return "BLOCKED" ; 
                      break ; 

case Status::IDLE : 
                      return "IDLE" ; 
                      break ; 
case Status::RUNNING : 
                      return "RUNNING" ; 
                      break ; 
case Status::SLEEPING : 
                      return "SLEEPING" ; 
                      break ; 
case Status::TERMINATED : 
                      return "TERMINATED" ; 
                      break ; 

 default :  return "UNIDENTIFIED" ;
                       
}




}

void AThread::sleep(int milliseconds){
      
    auto old_status = status ; 
    status = Status::SLEEPING ; 
std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)) ; 
status = old_status ; 

}
void AThread::setLock()
{
    if(status==Status::RUNNING || status==Status::IDLE)
    Locked_M = true  ;  
}
bool AThread::is_locked(){
    return Locked_M ; 
}


double AThread::getExecutionTIme(){
if(status == Status::TERMINATED){
      end_time = std::chrono::system_clock::now() ; 
    auto duration = end_time - start_time ; 
    return duration.count() ; 
} 
    return getActiveTime();


}

std::string AThread::getName(){


return name ; 

}

int AThread::getId(){
    return thread_id ; 
}


double AThread::getActiveTime(){
auto now_time = std::chrono::system_clock::now() ; 
auto duration = now_time - creation_time ;  // no need for a mutex as it reads only the value 
return duration.count() ; 

}


void AThread::endAThread(){

    std::unique_lock<std::recursive_mutex> lock(A_Rmutex) ; 
    this->Locked_M = true ; 
if(A_thread.joinable()&& this->status==Status::RUNNING){
A_thread.join() ; 

}
this->status=Status::TERMINATED ; 
this->end_time = std::chrono::system_clock::now() ; 
this->execution_time = end_time - start_time ; 
this->Locked_M = false ;  
}

void exampleTask(AThread * A) {
     
     // coordinate with the threads_manager class in order to make sure if it was blocked or not  
    if(m.try_lock()){
    std::unique_lock<std::recursive_mutex> lock(m ) ; 
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate a task that runs for 3 seconds
}else {
A->setStatus(AThread::Status::BLOCKED) ; 
 std::this_thread::sleep_for(std::chrono::milliseconds(100)) ; 

}



}
/*
int main() {
    AThread A;
    AThread B  ; 
    // Start the thread with the example task
    A.startAThread(exampleTask, &A);
    B.startAThread(exampleTask,&B) ; 
    // Wait a bit to ensure the thread starts executing
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    std::cout << "Thread ID: " << A.getId() << std::endl;
    std::cout << "Thread Name: " << A.getName() << std::endl;
    std::cout << "Thread Status: " << A.getStatus() << std::endl;
    std::cout << "Execution Time: " << A.getExecutionTIme() << " seconds" << std::endl;
    A.endAThread() ; 
    B.endAThread() ; 
  std::cout << "Thread ID: " << B.getId() << std::endl;
    std::cout << "Thread Name: " << B.getName() << std::endl;
    std::cout << "Thread Status: " << B.getStatus() << std::endl;
    std::cout << "Execution Time: " << B.getExecutionTIme() << " seconds" << std::endl;
    return 0;
}*/