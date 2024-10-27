#ifndef Athread_HPP
#define  Athread_HPP 
#include <chrono> 
#include<thread> 
#include<string> 
#include<mutex> 

class AThread       {
public : 
static int  default_id ; 
AThread()  ; 
AThread(const int id)  ; // a constructor 
AThread(const int id , std::string name )  ; 
// make sure when to delete the copy , assignment or use rule of 0,3,5  
   AThread(const AThread& other) = delete; // No copy constructor  
    AThread& operator=(const AThread& other) = delete; // No copy assignment

AThread(AThread&& other) noexcept; // Move constructor
    AThread& operator=(AThread&& other) noexcept; // Move assignment
template<typename Function, typename... Args>
void startAThread(Function&& task, Args&&... args) ;  
//  used variadic tenplates technique in order to pass any function/functor/object/with any num of paramters
void endAThread() ; 
bool isHidden(); 
void setHiddenON(); 
 
void sleep(int milli_seconds);  
double  getActiveTime() ;  
double  getExecutionTIme() ; 
bool is_locked() ; 
void setLock() ; 
std::string getStatus() ; 
std::string getName() ; 
int getId() ; 
~AThread() ;  // destructor 
bool isJoinable(); 
void set_to_joined() ; 

enum class Status {
IDLE, // is created but had not started yet 
RUNNING, // is currenty running and executing a task 
SLEEPING, // is sleeping and inacitve
WAITING, // is waiting for a condition 
BLOCKED, // tried to unlock a mutex is blocked 
TERMINATED, // is TERMINATED or temrinated 

} ; 
void setStatus(Status s) ; 



private : 
std::thread A_thread ; 
 int thread_id ; 
std::chrono::time_point<std::chrono::system_clock>  creation_time ; // creation time of the thread 
std::chrono::time_point<std::chrono::system_clock> start_time;
std::chrono::time_point<std::chrono::system_clock> end_time;
std::chrono::duration<double> execution_time ; // execution time 
std::chrono::duration<double> sleep_time ; 
Status status  ; 
std::string name ;  
bool Locked_M ; 
bool hidden  ; 
std::recursive_mutex A_Rmutex ; // avoid deadlocks 
// add a mutex here  or make it using the mutex manager   



};  

// defining the variadic template function 
template<typename Function, typename... Args>
void AThread::startAThread(Function&& task, Args&&... args) {
    if(status==Status::IDLE || status == Status::BLOCKED){ //  didnot start yet or blocked  
    std::unique_lock<std::recursive_mutex> lock(A_Rmutex) ; 
    this->Locked_M = true ; 
    status = Status::RUNNING; // set status into running 
    start_time = std::chrono::system_clock::now(); // start the time 
    A_thread = std::thread([this, task, ...args = std::forward<Args>(args)]() mutable { // i pass this in order to access the variables 
        task(std::forward<Args>(args)...); 
    });
    this->Locked_M = false ; 
    //  status = Status::IDLE; 
    
     } 


}
















#endif 