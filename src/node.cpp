#include <errno.h>
#include "node.h"


Node::Node(int port) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
}

Node::~Node() {
    close(socket_fd);
}

void Node::Init() {
}

int Node::Run() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        return errno;
    }
    if (bind(socket_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        return errno;
    }
    listen(socket_fd, /* backlog */ 5);
    printf("Node is up.\n");

    while (1) {
        struct sockaddr_in client_address;
        socklen_t client_address_socklen = sizeof(client_address);
        int client_fd;
        client_fd = accept(socket_fd,
                           (struct sockaddr *) &client_address,
                           &client_address_socklen);
        if (client_fd < 0) {
            printf("Error accepting new connection\n");
            return -1;
        }
        printf("New connection from %s:%d\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));
        char buffer[1024] = {0};
        if (read(client_fd, buffer, 1023) >= 0) {
            std::string raw_request(buffer);
            this->HandleRequest(client_fd, raw_request);
        }
        close(client_fd);
    }
    return 0;
}

void Node::HandleRequest(int client_fd, const std::string& raw_request) {
    std::string r = raw_request.substr(0, raw_request.size()-1);
    std::string action = r.substr(0, 4);
    if (action == "SET ") {
        std::string key = r.substr(4, r.find(":") - 4);
        std::string value = r.substr(r.find(":") + 1);
        this->m[key] = value;
    } else if (action == "GET ") {
        std::string key = r.substr(4);
        write(client_fd, this->m[key].c_str(), (this->m[key]).length());
    }
}
