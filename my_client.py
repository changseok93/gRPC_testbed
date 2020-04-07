from __future__ import print_function
import logging

import grpc

import my_protobuf_pb2
import my_protobuf_pb2_grpc

def run():
    input_image = open('input_data.jpg', 'rb')
    input_image = input_image.read()
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = my_protobuf_pb2_grpc.transactionTestStub(channel)
        response = stub.IimageOtext(my_protobuf_pb2.ImageType(format='jpg', data = input_image))
    print('{} send complete'.format(response.result))

if __name__ == '__main__':
    run()
