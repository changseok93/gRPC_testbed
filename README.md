# gRPC_testbed
gRPC Image, Json transaction testbed



### how to test

1. clone this repository in your WORKSPACE ( git clone https://github.com/changseok93/grpc_testbed )
2. move to grpc_testbed (cd grpc_testbed)
3. python3 -m grpc_tools.protoc -I ./proto --python_out=. --grpc_python_out=. ./proto/my_protobuf.proto
4. open another terminal and move to $WORKSPACE/grpc_testbed
5. start server in terminal#1 (python3 my_server.py)
6. start client in terminal#2 (python3 my_client.py)

than you can check result on client side terminal. also server side output directory.


thankyou.
