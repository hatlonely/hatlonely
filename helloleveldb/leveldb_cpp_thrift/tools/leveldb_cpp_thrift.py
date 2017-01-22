#!/usr/bin/env python3

import sys
from py.leveldb_cpp_thrift import LeveldbCppThrift
from thrift.transport import TSocket
from thrift.protocol import TCompactProtocol


def help():
    print('{0} <host:port> <get|put|del> <key> [value]'.format(sys.argv[0]))
    print('  {0} 127.0.0.1:2017 put name hatlonely'.format(sys.argv[0]))
    print('  {0} 127.0.0.1:2017 get name'.format(sys.argv[0]))
    print('  {0} 127.0.0.1:2017 del name'.format(sys.argv[0]))


def main():
    if len(sys.argv) < 4:
        help()
        return 255
    hostport = sys.argv[1].split(':')
    host = hostport[0]
    port = 2017
    if len(hostport) >= 2:
        port = int(hostport[1])
    operation = sys.argv[2]
    transport = TSocket.TSocket(host, port)
    protocol = TCompactProtocol.TCompactProtocol(transport)
    client = LeveldbCppThrift.Client(protocol)
    transport.open()
    if operation == 'put':
        if len(sys.argv) < 5:
            help()
            return 255
        print(client.levelPut(sys.argv[3], sys.argv[4]))
    elif operation == 'get':
        if len(sys.argv) < 4:
            help()
            return 255
        print(client.levelGet(sys.argv[3]))
    elif operation == 'del':
        if len(sys.argv) < 4:
            help()
            return 255
        print(client.levelDel(sys.argv[3]))
    else:
        help()
        return 255


if __name__ == '__main__':
    main()
