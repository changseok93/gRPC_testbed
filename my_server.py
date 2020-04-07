from concurrent import futures
import logging

import grpc

import my_protobuf_pb2
import my_protobuf_pb2_grpc


class ImageIO(my_protobuf_pb2_grpc.Image_parserServicer):
    def __init__(self):
        self.file_counter = 1

    def getImage(self, img, context):
        file = open('output_data_{}.jpg'.format(self.file_counter), 'wb')
        file.write(img.File)
        file.close()
        self.file_counter+=1
        return my_protobuf_pb2.ImageReply(result="thank you very much!")

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    my_protobuf_pb2_grpc.add_Image_parserServicer_to_server(ImageIO(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    serve()
