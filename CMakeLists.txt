cmake_minimum_required(VERSION 3.15)
project(UserService)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)

add_executable(server
    ${SRC_FILES}
    generated/user.pb.cc
    generated/user.grpc.pb.cc
)

target_include_directories(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include      # Your headers
    ${CMAKE_CURRENT_SOURCE_DIR}/proto        # Proto files
    ${CMAKE_CURRENT_SOURCE_DIR}/generated    # Generated headers
)

target_link_libraries(server
    gRPC::grpc++
    protobuf::libprotobuf
)