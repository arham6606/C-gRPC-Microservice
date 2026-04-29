#pragma once
#include "../database/db.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>
using namespace std;

#include "../proto/generated/user.grpc.pb.h"
#include "../proto/generated/user.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Service;
using grpc::Status;

using user::CreateUserRequest;
using user::GetUserRequest;
using user::User;
using user::UserResponse;
using user::UserService;

void run();

class UserServiceImpl final : public UserService::Service
{
protected:
    mutex db_mutex;
    Database db;

public:
    UserServiceImpl() : db("dbname=userservice user=postgres password=1234 host=localhost") {}

    Status CreateUser(ServerContext *context, const CreateUserRequest *request, UserResponse *response) override;

    Status GetUser(ServerContext *context, const GetUserRequest *request, UserResponse *response) override;
};
