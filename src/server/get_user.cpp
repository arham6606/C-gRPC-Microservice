#include "../inc/header.h"

Status UserServiceImpl::GetUser(ServerContext *context, const GetUserRequest *request, UserResponse *response)
{
    lock_guard<mutex>lock(db_mutex);

    auto it = users_db.find(request->id());
    if(it == users_db.end())
    {
        return Status(grpc::NOT_FOUND,"User Not Found");
    }

    *response->mutable_user() = it->second;
    return Status::OK;
}