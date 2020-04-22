#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#ifdef BAZEL_BUILD
#include "examples/protos/my_protobuf.grpc.pb.h"
#else
#include "my_protobuf.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// using my_protobuf::ImageType;
using my_protobuf::TextType;
// using my_protobuf::JSONType;
using my_protobuf::transactionTest;

// Logic and data behind the server's behavior.
class transactionTestServiceImpl final : public transactionTest::Service {
  Status ItextOtext(ServerContext* context, const TextType* request,
                  TextType* reply) override {
    std::string prefix("Hello world");
    reply->set_data(prefix);
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("localhost:50051");
  transactionTestServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
