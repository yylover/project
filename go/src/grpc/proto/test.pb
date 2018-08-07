syntax="proto3";

package proto;

message HelloParam {
    string name = 1;
    string msg = 2;
}

message HelloReply {
    string name = 1;
    string reply = 2;
}

service HelloServer {
    rpc Hello(HelloParam) returns (HelloReply){};
}