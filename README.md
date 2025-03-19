#=> Ask FM System (C++)
  
  
  
- A Q&A platform inspired by Ask FM, built with modern C++.

   @ Overview:                                                                                                                              
     
     This project simulates a simplified Ask FM-style system where users can:                                                                                            
     
     // * Sign up and log in with credentials.                                                                                                                           
     
     // * Ask questions to other users (with optional threaded replies).                                                                                                 
     
     // * Answer questions directed to them.                                                                                                                                                                          
     
     // * Delete questions they’ve asked.                                                                                                                           
                                                                                                                                                
     // * View public feeds of questions and answers.                                                                                                               
                                                                                                                                        
     // * Persist data to text files (Users.txt and Questions.txt).                                                                                                 
                                                                                                                       
                                                                                                                                                                    
   @ Features:                                                 
     * User Management:
       // - Secure SignUp/signIn with (username,password,email).
       // - Unique member IDs and static member tracking.
     * Question System:
       // - Parent/Thread question hierarichy.
       // - Automatic question ID generation.
     * Error Handling:
       // - Custom Exceptions (DataFileCorruptionException , InvalidPasswordException)
     * Class Manager for system:
       // - Ask manager class to manage the operations.
     * Singleton design pattern:
       // - AskSystemManager ensures a single system instance.

   @ Project Structure:
      ├── include/  
      │   ├── question.h          # Question class declaration  
      │   ├── user.h              # User class declaration  
      │   ├── ask_manager.h           # System manager (singleton)  
      │   └── custom_exceptions.h # Custom error classes  
      ├── src/  
      │   ├── question.cpp      # Question class logic  
      │   ├── user.cpp          # User class logic  
      │   ├── ask_manager.cpp       # System manager logic  
      │   └── main.cpp          # Entry point  
      └── DataBase/  
      ├── Users.txt         # User data storage  
      └── Questions.txt     # Question data storage  
