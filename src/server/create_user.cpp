#include "../inc/header.h"

// create user request
Status UserServiceImpl::CreateUser(ServerContext *context, const CreateUserRequest *request, UserResponse *response)
{
    lock_guard<mutex> lock(db_mutex);

    if (request->name().empty() || request->email().empty())
    {
        return Status(grpc::INVALID_ARGUMENT, "name and email are required");
    }

    try
    {
        if (db.emailExists(request->email()))
        {
            return Status(grpc::ALREADY_EXISTS, "Email Already Registered");
        }

        int32_t id = db.createUser(request->name(), request->email());

        User users;
        users.set_name(request->name());
        users.set_email(request->email());
        users.set_id(id);
        *response->mutable_user() = users;

        return Status::OK;
    }

    catch (const exception &e)
    {
        return Status(grpc::INTERNAL, e.what());
    }
}
