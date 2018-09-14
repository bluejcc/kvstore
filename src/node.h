//
// Created by vincent on 9/14/18.
//

#include <vector>
#include <sys/socket.h>
#include <map>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#ifndef KVSTORE_NODE_H
#define KVSTORE_NODE_H

class Node {
public:
    std::map<std::string, std::string> m;
    int socket_fd;
    struct sockaddr_in address;
    // TODO: std::vector<int> client_fds;

    Node(int port);
    ~Node();
    void Init();
    int Run();
    void HandleRequest(int client_fd, const std::string &msg);
};


#endif //KVSTORE_NODE_H
