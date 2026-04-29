#include "../inc/header.h"

Status UserServiceImpl::GetUser(ServerContext *context, const GetUserRequest *request, UserResponse *response)
{
    lock_guard<mutex> lock(db_mutex);

    try
    {
        auto [id, name, email] = db.getUser(request->id());
        User user;
        user.set_id(id);
        user.set_name(name);
        user.set_email(email);
        *response->mutable_user() = user;

        return Status::OK;
    }
    catch (const std::exception &e)
    {
        return Status(grpc::NOT_FOUND, e.what());
    }
}