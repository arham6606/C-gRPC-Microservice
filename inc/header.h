#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <mutex>
#include <threads.h>
using namespace std;

#include "../proto/generated/user.grpc.pb.h"
#include "../proto/generated/user.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Service;
using grpc::Status;

using user::CreateUserRequest;
using user::User;
using user::UserResponse;
using user::UserService;

class UserServiceImpl final : public UserService::Service
{
protected:
    unordered_map<int32_t, User> users_db;
    int32_t id_list = 1;
    mutex db_mutex;

public:
    Status CreateUser(ServerContext *context, const CreateUserRequest *request, UserResponse *response) override;
};
