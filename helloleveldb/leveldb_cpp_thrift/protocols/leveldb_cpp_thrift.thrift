namespace cpp hl
namespace php hl

enum ErrorCode {
    kSucc = 0,
    kFail = 1,
}

exception LeveldbCppThriftException {
    1: ErrorCode errorCode,
    2: string message,
}

service LeveldbCppThrift {
    void levelPut(1: string key, 2: string value) throws (1: LeveldbCppThriftException e),
    void levelDel(1: string key) throws (1: LeveldbCppThriftException e),
    string levelGet(1: string key) throws (1: LeveldbCppThriftException e),
}
