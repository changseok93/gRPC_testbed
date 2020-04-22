#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <typeinfo>

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

using my_protobuf::ImageType;
using my_protobuf::TextType;
using my_protobuf::JSONType;
using my_protobuf::transactionTest;

// Logic and data behind the server's behavior.
class transactionTestServiceImpl final : public transactionTest::Service {
  Status ItextOtext(ServerContext* context, const TextType* request,
                          TextType* reply) override {
    reply->set_data(request->data());
    return Status::OK;
  }

  Status IimageOimage(ServerContext* context, const ImageType* request, 
                            ImageType* reply) override {

    reply->set_format(".jpg");
    reply->set_data(request->data());

    /* 
    experimental example
    // load image from local system
    std::ifstream ifs("/home/changseok/grpc_testbed/sample_data/covid-19.jpg", std::ios::binary | std::ios::in);

    // calculate file size
    ifs.seekg(0, ifs.end);
    int length = (int)ifs.tellg();
    ifs.seekg(0, ifs.beg);

    // read image in buffer
    char* buffer = new char [length];
    ifs.read((char*)buffer, length);
    ifs.close();

    // set format & data
    reply->set_format(".jpg");
    reply->set_data(std::string(buffer, length));
    */

    return Status::OK;
  }

  Status IjsonOjson(ServerContext* context, const JSONType* request, JSONType* reply) override {
    reply->set_data(request->data());

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

