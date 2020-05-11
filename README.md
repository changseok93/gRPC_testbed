# gRPC_testbed
gRPC Image, Json transaction testbed

### current status
<img src="http://changseok2.iptime.org/share/share_imgs/gRPC_testbed_v1.1.svg"></img><br>

### how to test (Python server/client)

1. clone this repository in your $WORKSPACE ( git clone https://github.com/changseok93/grpc_testbed )
2. move to grpc_testbed (cd grpc_testbed/Python)
3. autogenerate gRPC-protobuf3 code [python3 -m grpc_tools.protoc -I ./proto --python_out=. --grpc_python_out=. ./proto/my_protobuf.proto]
4. open another terminal and move to $WORKSPACE/grpc_testbed/Python
5. run server in terminal#1 [python3 my_server.py]
6. run client in terminal#2 [python3 my_client.py]

than you can check result on client side terminal. also server side output directory.

### how to test (C++ server)
1. clone this repository in your $WORKSPACE ( git clone https://github.com/changseok93/grpc_testbed )
2. move to grpc_testbed (cd grpc_testbed/C++/cmake/build)
3. run cmake [cmake -DCMAKE_PREFIX_PATH=../../local ../..]
4. build [make]
5. open another terminal and move to $WORKSPACE/grpc_test/Python
6. run server in terminal#1 [./server]
7. run client in terminal#2 [python3 my_client.py]



### code notation
/proto/my_protobuf.proto : protobuf로 정의된 data 및 transaction 타입

my_protobuf_pb2.py & my_protobuf_pb2_grpc.py : 위의 protobuf file을 compile하여 생성 한 python file (API 를 생성한다고 생각하면 됨)

my_server.py & my_client.py : server 및 client file

thankyou.
