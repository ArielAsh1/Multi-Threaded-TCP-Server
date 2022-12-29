//
// Created by orrbb on 24/12/2022.
//
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <vector>
#include "knn.h"
#include "readFromFile.h"

using namespace std;
/**
 * function creates and runs a server, according to its initialized port. It first creates a socket, binds it,
 * and than endlessly listens to input from clients.
 * If the message from client is valid, the server will classify it using KNN algorithm, implemented in previous
 * exercise, and will return to the client the a string classification, according to the CSV file.
 * @param port - port of the server.
 * @param csv - csv file we will train knn on.
 * @return
 */
int runServer(int port, string csv){
    const int server_port = port;
    /*socket creation, sock_stream is a const for TCP */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(-1);
    }
    /* creating the struct for the address */
    struct sockaddr_in server_sin;     /* struct for the address */
    memset(&server_sin, 0, sizeof (server_sin));  /* It copies a single character for a specified number
    * of times to an object (sin)*/
    server_sin.sin_family = AF_INET;   /* address protocol type */
    server_sin.sin_addr.s_addr = INADDR_ANY; /* const for any address */
    server_sin.sin_port = htons(server_port); /* defines the port */
    /* binding the socket to the port and ip_address, while checking it can be done */
    if (bind(sock, (struct sockaddr *) &server_sin, sizeof (server_sin)) < 0) {
        perror("Error binding socket");
        exit(-1);
    }
    /* listens up to 5 clients at a time */
    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket");
        exit(-1);
    }
    while (true) {      /* we were instructed not to close the server. */
        struct sockaddr_in client_sin; /* address struct for the sender info */
        unsigned int addr_len = sizeof (client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len); /* accept creates a new socket
        * for the connecting client */
        if (client_sock < 0) {
            perror("Error accepting client");
            exit(-1);
        }
        char messageBuffer[4096]; /* creates a buffer for the client */
        int expected_data_len = sizeof (messageBuffer); /* maximum length of received data */
        int read_bytes = recv(client_sock, messageBuffer, expected_data_len, 0); /* receive a message from the clients
        * socket into the buffer. */
        if (read_bytes == 0) {
            perror("Connection is closes");
        } else if (read_bytes < 0) {
            perror("Error");
        } else {
            /* if message is -1 we should close client */
            /* if message is invalid, return "invalid input" and continue */

            /**********************************************************************************/
            // classify vector according to file
            // assuming vector is valid and classifies into vector, distance and k
            /* NOTICE!! following variables should be initialized with user's input. */
            vector <float> inputVector = {1,2,3,4};
            string distanceMatric = "MAN";
            int k = 3;
            readFromFile reader(csv);
            reader.read();
            string prediction;
            /* Should perform input check on k (<= .y_train.size) and inputVector (= reader.featuresPerLine).
             * This is the only place we can check it!*/
            /* make sure k value is smaller than the number of samples in given file. */
            if (k >= reader.y_train.size()) {
                cout << "k should be smaller than number of samples" << endl;
                prediction = "invalid input";
                //exit(-1);
            } else if (inputVector.size() != reader.featuresPerLine) {
                cout << "input vector should have " << (reader.featuresPerLine)
                     << " elements, separated by spaces." << endl;
                prediction = "invalid input";
                //exit(-1);
            } else {        /* valid input from user */
                Knn knn = Knn(k, distanceMatric, reader.X_train, reader.y_train);
                prediction = knn.predict(inputVector);
            }
            char* sendMessage = &prediction[0];     /* knn returns a string, and send receives a char[] */
            int sizeOfMessage = sizeof (sendMessage);   /* maximum length of received data */
            /* send the prediction back to client. */
            int sent_bytes = send(client_sock,sendMessage, sizeOfMessage, 0);
            if (sent_bytes < 0) {
                cout << "error sending to client.";
            }
        }
    }
    /* closes the server socket */
    close(sock);
    return 0;
}

int main (int argc, char *argv[]) {
    // should extract csv from arvg, and perform input checks on it

    // should extract port from argv, and perform input checks on it

    string cvs = argv[1];
    int port = atoi(argv[2]);
    runServer(port, cvs);

}
