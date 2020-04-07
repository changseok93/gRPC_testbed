from concurrent import futures
import logging

import grpc

import my_protobuf_pb2
import my_protobuf_pb2_grpc


class transactionTest(my_protobuf_pb2_grpc.transactionTestServicer):
    def __init__(self):
        self.call_counter = 1

    def IimageOimage(self, ImageType, context):
        file = open('output/output_data.{}'.format(ImageType.format), 'wb')
        file.write(ImageType.data)
        file.close()
        return my_protobuf_pb2.ImageType(format = ImageType.format, data = ImageType.data)
    
    def ItextOtext(self, TextType, context):
        file = open('output/README.txt', 'wb')
        file.write(TextType.data)
        file.close()
        return my_protobuf_pb2.TextType(data = TextType.data)
    
    def IjsonOjson(self, JSONType, context):
        file = open('output/output_data.json', 'wb')
        file.write(JSONType.data)
        file.close()
        return my_protobuf_pb2.JSONType(data = JSONType.data)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    my_protobuf_pb2_grpc.add_transactionTestServicer_to_server(transactionTest(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
