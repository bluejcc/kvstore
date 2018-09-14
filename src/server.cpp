#include <iostream>
#include <boost/log/trivial.hpp>
#include "node.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage %s <port>\n", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    Node node(port);
    int ret = node.Run();
    if (ret != 0) {
        printf("Error bringing up node: %d", ret);
    }

    return 0;
}