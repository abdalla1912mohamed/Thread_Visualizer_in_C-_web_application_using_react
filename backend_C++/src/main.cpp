#include"AthreadManager.hpp" 
#include "ATthread.hpp"
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <uWS/uWS.h>



void printIdAndLockStatus(const std::vector<ThreadInfo>& threads) {
    std::cout << "Thread ID and Lock Status:\n";
    for (const auto& thread : threads) {
        std::cout << "Thread ID: " << thread.threadId 
                  << ", Locked: " << (thread.isLocked ? "Yes" : "No") << "\n";
    }
}



void A(int x) {

std::this_thread::sleep_for(std::chrono::milliseconds(x)); 
// runninggggg} 

}
void init(){

 auto & manager = AThreadManager::getInstance( 512) ; 
// Create the AThreadManager instance with a maximum of 5 threads
   
   for(int i = 0 ; i<10 ;i++){
    manager.AddThread() ; 
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000)); 

  //  manager.getThreadsArray()[i].setStatus(AThread::Status::RUNNING) ; 
    manager.getThreadsArray()[i].startAThread(A,10000);     
    // workingggg 
                   //     manager.getThreadsArray()[i].setStatus(AThread::Status::TERMINATED)         ; 
   }
   for(int i = 10 ; i<15 ; i++){
    manager.AddThread() ; 
    manager.SleepThread(i, 3000) ;
   }
   
    for(auto &e : manager.getThreadsArray()){
            e.endAThread() ; // waiting for all threadsss
    }
    manager.getThreadsArray()[1].setStatus(AThread::Status::SLEEPING);
    manager.SleepThread(1,  5000); 
       manager.getThreadsArray()[1].setStatus(AThread::Status::TERMINATED);
 

}




int main(int argc , char ** argv){

char action ; 
uWS::Hub h; 
    AThreadManager& manager = AThreadManager::getInstance(512);
AThread b ; 
b.startAThread(init) ;  
std::cout<<      manager.getThreadsArray()[1].getStatus()<<std::endl ; 
//b.endAThread() ; 
std::cout<<      manager.getThreadsArray()[1].getStatus()<<std::endl ; 
/*
   // Create the AThreadManager instance with a maximum of 5 threads
    AThreadManager& manager = AThreadManager::getInstance(5);
   for(int i = 0 ; i<10 ;i++){
    manager.AddThread() ; 
    manager.getThreadsArray()[i].endAThread() ; 
   }
   for(int i = 0 ; i<10 ;i++){
    manager.AddThread() ; 
    manager.getThreadsArray()[i].setStatus(AThread::Status::RUNNING) ; 
    manager.getThreadsArray()[i].startAThread(A,10000);     
                   //     manager.getThreadsArray()[i].setStatus(AThread::Status::TERMINATED)         ; 
   }
   
    for(auto &e : manager.getThreadsArray()){
            e.endAThread() ; 
    }
    manager.getThreadsArray()[1].setStatus(AThread::Status::SLEEPING);
    manager.SleepThread(1,  5000); 
        manager.getThreadsArray()[5].setStatus(AThread::Status::SLEEPING);
    manager.SleepThread(5, 5000) ; 

   // Set up HTTP request handler
    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t length, size_t remainingBytes) {
        std::string response = "Hello World";

        // Construct the full HTTP response string including headers
        std::string httpResponse = 
            "HTTP/1.1 200 OK\r\n" // adjust the cross platform to solve any upcoming  error 
            "Access-Control-Allow-Origin: *\r\n"
            "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
            "Access-Control-Allow-Headers: Content-Type\r\n"
            "Content-Length: " + std::to_string(response.length()) + "\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n" + response;

        // Send the response to the client
        res->write(httpResponse.c_str(), httpResponse.length()); 
        res->end();
    });
 */

  // Define WebSocket connection handler  , capture the manageerrrrrr   
    h.onConnection([&h , &manager](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        std::cout << "Client connected" << std::endl;


});

   h.onMessage([&action , &manager](uWS::WebSocket<uWS::SERVER> ws, char *message, size_t length, uWS::OpCode opCode) { // ON message 
     //  std::cout << "Received message: " << std::string(message, length) << std::endl;
       std::string sub; 
       int id  ; 
       json p ; 
       ThreadInfo t ; 
       json response = manager.toJson(); 
                 std::string j =  response.dump() ; 
        action = (std::string(message, length))[0] ; 
        std::cout<<"action"<<" "<<action <<std::endl; 
        switch(action){
     case 'C' : manager.AddThread() ;
                manager.UpdateThreadInfo(); 
                   response = manager.toJson(); 
                  j =  response.dump() ; //create
              ws.send(j.c_str(), j.length(), uWS::OpCode::TEXT);
              break ; 
     case 'E' :    sub = (std::string(message, length)).substr(1,length-1) ; 
                    id = std::stoi(sub) ; 
              // find
     
          t =  manager.findThread( id) ; 
          p=  manager.infotoJson(t) ; 
          sub = p.dump() ; 
           ws.send(sub.c_str(), sub.length(), uWS::OpCode::TEXT);
              break ; 
    case 'D' :  //delete 
                 sub = (std::string(message, length)).substr(1,length-1) ; 
                    id = std::stoi(sub) ; 
                manager.RemoveThreadInfo( id) ; 
                manager.getThreadsArray()[id].endAThread();
                response = manager.toJson() ; 
                j = response.dump();
                 ws.send(j.c_str(), j.length(), uWS::OpCode::TEXT);
                  break ; 
    case 'M' :     sub = (std::string(message, length)).substr(1,length-1) ; 
                    id = std::stoi(sub) ; 
                    manager.getThreadsArray()[id-1].setLock() ; 
// mutex xlock
                  break;
    default:       response =manager.toJson(action) ;
                    j = response.dump() ; 
                    ws.send(j.c_str(), j.length(), uWS::OpCode::TEXT);
                     break ; 

        }
    
    });

     if (h.listen(3004)) {
        std::cout << "Listening on port 3004" << std::endl;
    } else {
        std::cerr << "Failed to listen on port 3004" << std::endl;
        return 1;
    }
std::cout<<      manager.getThreadsArray()[1].getStatus()<<std::endl ; 
    // Run the event loop
    h.run();




    return 0 ; 
}












