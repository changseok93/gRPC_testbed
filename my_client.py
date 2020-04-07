from __future__ import print_function
import logging

import grpc

import my_protobuf_pb2
import my_protobuf_pb2_grpc

def run():
    data = open('input_data.jpg', 'rb')
    data = data.read()
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = my_protobuf_pb2_grpc.Image_parserStub(channel)
        response = stub.getImage(my_protobuf_pb2.ImageRequest(File=data))
    print('{} send complete'.format(response.result))

if __name__ == '__main__':
    run()
