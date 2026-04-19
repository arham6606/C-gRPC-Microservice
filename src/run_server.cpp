#include "../inc/header.h"

void run()
{
    UserServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server Listening on 0.0.0.0:50051" << endl;
    server->Wait();
}