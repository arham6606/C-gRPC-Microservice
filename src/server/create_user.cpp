#include "../inc/header.h"

// create user request
Status UserServiceImpl::CreateUser(ServerContext *context, const CreateUserRequest *request, UserResponse *response)
{
    lock_guard<mutex> lock(db_mutex);

    if (request->name().empty() || request->email().empty())
    {
        return Status(grpc::INVALID_ARGUMENT, "name and email are required");
    }

    for (auto &[id, user] : users_db)
    {

        if (user.email() == request->email())
        {
            return Status(grpc::ALREADY_EXISTS, "Email already registerd");
        }
    }

    User users;
    users.set_name(request->name());
    users.set_email(request->email());
    users.set_id(id_list);

    users_db[id_list] = users;
    id_list++;
    *response->mutable_user() = users;
    return Status::OK;
}
