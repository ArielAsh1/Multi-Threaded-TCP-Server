# Multi-Threaded TCP server- KNN Algorithm

A C++ implementation of a multi-threaded TCP server.  
The server uses the KNN machine learning algorithm to allow clients classify new samples, based on input dataset.  
Server can handle multiple clients simultaneously. 


**to compile and run perform the following commands:**  
Open 2 terminals (1- for server side, 2- for client side):  
On both Terminals 1 & 2:
1. git init  
2. git clone
3. make  
4. **On Terminal 1 (server):** recieves 2 arguments-   
./server.out port  
5. **On terminal 2 (client):** recieves 3 arguments-   
./client.out server ip server_port


For example:
<p float="left">
Client side (with the menu printed):
<img width="370" alt="image" src="https://user-images.githubusercontent.com/112930532/215842204-d997fb52-d259-49d4-a18d-3a7c476d8724.png">
Server side:
<img width="200" alt="image" src="https://user-images.githubusercontent.com/112930532/215843348-131db083-7029-45cc-9043-8471ff0da799.png">

**Server should be initialized before client!**
On this exercise, we implemented a Menu for client side, that maintains communication between the two sides, still using TCP protocol. Server side will handle the calculations and the all the necessary information, and will send client information when asked, according to the menu. <br>
Server will still use KNN algorithem to classify labels, but now can classify a file of vectors, and to send that information back to Client, where client can print it to screen, or save it to a local file. <br>
Also, Server can now handle multipy clients simutaniasly, using Threads. <br>
Client can end communication with server when inserting 8, that will close the socket between the client and server, and will end the program on client side.<br>
Client can always connect back to server (that loop endessly, waiting for new clients), using the terminal code provided above.

Port should be the same for server and client, and between 1024 and 65535.
Ip address should be valid address: 4 numbers, from 0 to 255, separated by dots.

The code comprised of couple of key classes, and runs simultaneously both server and client side. Both user functions from helperFunctions.cpp for various reasons, mainly for input check.<br>
Server side will use CLI class to handle the menu and its commands, implementing the Command design pattern:<br>
**Command 1**: user should insert 2 valid paths to classification files. One should be classified - the train set, and the other should not - Test set. 
Files contanining different number of features (=columns), will not be accepted.<br>

**Command 2**: user should insert k and a distance metric, separated in a single space. K should be a positive integer, and distance metric should be a valid distance metric: AUC, MAN, CHB, CAN, MIN. <br>
Note: K value should be lower than the number of rows in the input classified files, for KNN algorithem to run. If k is set after command 1 is executed, program will print invalid input in this scenario. <br>
If k was set before command 1, and its value is indeed bigger than number of rows, running command 3 will set K to be the maximun value it can be, meaning - number of rows. <br>

**Command 3**: choosing command 3 will classify the Unclassified data, using KNN algorithem with values setting in command 2. 
If files were not uploaded, fitting message will apear. <br>

**Command 4**: Server will send client the classified label for each row from the data.

**Command 5**: user should give a path containing the new file(with fime name) he wish to download the classification into, for example: "C:\Users\some_name\Desktop\filename.csv", or path in linux syntax, if project is run from a linux based system. <br>

Like previous exercises, server also uses Knn class that implemants the KNN algorithem, with the use of distancematric class, which holds the distance matrics from the previous exercise.

Client side will print the menu for the user, and will send user's input to server, or print the message from the server.
Server side will use Readfromfile.cpp to read the input csv file and ensure the input for KNN class will be accurate,

For convinience reasons, we added the classified csv file to the repository, so cloning it will result of cloning said files as well.

Example:  
choose 3: <img width="349" alt="image" src="https://user-images.githubusercontent.com/112930532/215844424-ac32221d-ba37-4b37-bda2-7a3cbfd10c25.png">
choose 4: <img width="149" alt="image" src="https://user-images.githubusercontent.com/112930532/215844286-32ac9baa-2f52-4863-9bfb-637877da58b7.png">
choose 5: <img width="244" alt="image" src="https://user-images.githubusercontent.com/112930532/215844023-5704434a-8837-44f7-aa83-496426a12dad.png">


