//
//  swift.swift
//  HelloSwift
//
//  Created by hatlonely on 2016/12/24.
//  Copyright © 2016 hatlonely. All rights reserved.
//

import Foundation

func HelloWorld() {
    print("hello world")
}

func HelloValible() {
    let kPi = 3.14
    var num = 0
    var str = "hatlonely"
    var arr = [1, 2, 3, 4]
    
    var num16: UInt16 = 0
    
    let http404 = (404, "Not Found")
    let http200 = (statusCode: 404, message: "Not Found")
    var (statusCode, message) = http404
}

func HelloString() {
    let url = "http://github.com/"
    for c in url.unicodeScalars {
        print("\(c)")
    }
}

func HelloCollection() {
    if true {
        var li1 = [5, 4, 3, 2, 1]
        li1.append(6)
        print(li1.capacity, li1.count, li1.isEmpty, li1)
        
        var li2 = Array<Int>()
        li2.append(1)
        
        for i in li1 {
            print(i)
        }
        for (idx, val) in li1.enumerated() {
            print(idx, " => ", val)
        }
    }
    
    if true {
        var msi = [
            "one": 1,
            "two": 2,
        ]
        msi["three"] = 3
        print(msi.count, msi.isEmpty, msi["one"]!, msi)
        
        for (key, val) in msi {
            print(key, "=>", val)
        }
        
        for key in msi.keys.sorted() {
            print(key, "=>", msi[key]!)
        }
    }
}

func HelloFunc() {
    if true {
        func Add(x: Int, y: Int) -> Int {
            return x + y
        }
        
        print(Add(x: 1, y: 2))
    }
    
    if true {
        let Add = {
            (x: Int, y: Int) -> Int in
            return x + y
        }
        
        print(Add(1, 2))
    }
}

func HelloEnumeration() {
    enum CompassPoint {
        case North
        case South
        case East
        case West
    }
}

func MainSwift() {
    HelloWorld()
    HelloValible()
    HelloString()
    HelloCollection()
    HelloFunc()
    HelloEnumeration()
}
