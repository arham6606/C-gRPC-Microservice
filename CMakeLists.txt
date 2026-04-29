cmake_minimum_required(VERSION 3.15)
project(UserService)

set(CMAKE_CXX_STANDARD 17)

# Use pkg-config for apt-installed gRPC and protobuf
find_package(PkgConfig REQUIRED)
pkg_check_modules(GRPC REQUIRED grpc++)
pkg_check_modules(PROTOBUF REQUIRED protobuf)
pkg_check_modules(PQXX REQUIRED libpqxx)

file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp"
    "src/server/*.cpp"
)

add_executable(server
    ${SRC_FILES}
    proto/generated/user.pb.cc
    proto/generated/user.grpc.pb.cc
)

add_executable(client
    client-testing/client.cpp
    proto/generated/user.pb.cc
    proto/generated/user.grpc.pb.cc
)

target_include_directories(client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/generated
    ${CMAKE_CURRENT_SOURCE_DIR}/client-testing
    ${GRPC_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${PQXX_INCLUDE_DIRS}
)

target_link_libraries(client
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${PQXX_LIBRARIES}
)

target_include_directories(server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/proto/generated
    ${GRPC_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${PQXX_INCLUDE_DIRS}

)

target_link_libraries(server
    ${GRPC_LIBRARIES}
    ${PROTOBUF_LIBRARIES}
    ${PQXX_LIBRARIES}

)