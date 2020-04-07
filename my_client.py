from __future__ import print_function
import logging

import grpc

import my_protobuf_pb2
import my_protobuf_pb2_grpc

def run():
    input_image = open('input_data.jpg', 'rb').read()
    input_json = open('input_data.json', 'rb').read()
    input_text = 'COVID19 infector specifications'
    
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = my_protobuf_pb2_grpc.transactionTestStub(channel)
        
        I2I_response = stub.IimageOimage(my_protobuf_pb2.ImageType(format='jpg', data = input_image))
        T2T_response = stub.ItextOtext(my_protobuf_pb2.TextType(data=input_text))
        J2J_response = stub.IjsonOjson(my_protobuf_pb2.JSONType(data=input_json))
        
    print('------------------gRPC & protobuf3 test------------------')
    print('1. Text type transaction test : {}'.format(T2T_response.data))
    print('1. Image type transaction test : {}'.format(I2I_response.data))
    print('1. JSON type transaction test : {}'.format(J2J_response.data))
    print('------------------end of test------------------')
        
        

if __name__ == '__main__':
    run()
