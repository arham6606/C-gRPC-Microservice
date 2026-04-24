#include "../inc/header.h"
#include <grpcpp/grpcpp.h>
#include <thread>
#include <vector>

using grpc::Channel;
using grpc::ClientContext;
using user::DeleteUserRequest;
using user::DeleteUserResponse;
using user::GetUserRequest;
using user::ListUsersRequest;
using user::ListUsersResponse;
using user::UpdateUserRequest;

void send_create_request(int thread_id)
{
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    auto stub = UserService::NewStub(channel);

    CreateUserRequest request;
    request.set_name("Arham_" + to_string(thread_id));
    request.set_email("arham_" + to_string(thread_id)+ "@gmail.com");

    UserResponse response;
    ClientContext ctx;

    Status status = stub->CreateUser(&ctx, request, &response);

    if (status.ok())
    {
        cout << "\n[Thread " << thread_id << "] Created user EMAIL: "
             << response.user().email() << " name: " << response.user().name() << "\n";
    }
    else
    {
        cout << "\n[Thread " << thread_id << "] Error: "
             << status.error_message() << "\n";
    }
}