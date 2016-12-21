# nodejs指南

BYVoid 编著

Node.js是一个基于Chrome JavaScript运行时建立的平台， 用于方便地搭建响应速度快、易于扩展的网络应用。Node.js 使用事件驱动， 非阻塞I/O 模型而得以轻量和高效，非常适合在分布式设备上运行的数据密集型的实时应用。

## Node.js简介

- Node.js，或者Node，是一个可以让javascript在服务器端运行的平台
- Node.js最大的特点就是采用异步式的I/O与事件驱动的架构设计，所有的磁盘I/O、网络通信、数据库查询都以非阻塞的方式请求，返回的结果由事件循环来处理
- Node.js采用异步I/O和事件驱动来代替多线程，带来了客观的性能提升
- CommonJS试图定义一套普通应用程序使用的API，从而填补JavaScript标准库过于简单的不足，Node.js实现了CommonJS规范

## 安装和配置Node.js

- npm是由Node.js官方提供的第三方包管理器
- n是一个十分简洁的Node多版本管理器

## Node.js快速入门

- Node.js命令行工具

    ```
    $ node
    > console.log('Hello world!');
    ```

- 建立http服务器

    ```javascript@lineNum
    // app.js
    var http = require('http');

    http.createServer(function (req, res) {
        res.writeHead(200, {
            'Content-Type': 'text/html'
        });
        res.write('<h1>Node.js</h1>');
        res.end('<p>Hello world!</p>');
    }).listen(3000);

    console.log("Http server is listening at port 3000");
    ```
- supervisor可以监视你对代码的改动并重新启动Node.js

    ```
    npm install supervisor
    ```

- 异步I/O与事件编程

    ```javascript@lineNum
    var fs = require('fs');

    // 异步方式读文件
    fs.readFile('file.txt', 'utf-8', function (err, data) {
        if (err) {
            console.error(err);
        } else {
            console.log(data);
        }
    });

    // 同步方式读文件
    var data = fs.readFileSync('file.txt', 'utf-8');
    console.log(data);

    // 事件
    var EventEmitter = require('events').EventEmitter;
    var event = new EventEmitter();

    event.on('some_event', function () {
        console.log('some_event occured.');
    });

    setTimeout(function () {
        event.emit('some_event');
    }, 1000);
    ```
- Node.js事件循环机制

    ![event_loops](/event_loops.jpg)

- 模块和包

    Node.js提供require函数来调用其他模块

    ```javascript@lineNum
    // 创建模块helloModule.js

    var name;
    exports.setName = function (n) {
        name = n;
    };
    exports.sayHello = function () {
        console.log('Hello ' + name + '!');
    };
    ```

    ```javascript@lineNum
    // 使用模块getModule.js
    var helloModule = require('helloModule');
    helloModule.setName('hatlonely');
    helloModule.sayHello();     // output: Hello hatlonely!
    ```

    ```javascript@lineNum
    // 封装一个对象的模块singleObject.js
    function Hello() {
        var name;

        this.setName = function (n) {
            name = n;
        }
        this.sayHello = function () {
            console.log('Hello ' + name + '!');
        }
    }

    exports.Hello = Hello;
    ```

    ```javascript@lineNum
    // singleObject.js需要通过require('singleObject').Hello来获取Hello对象
    // 简化版hello.js
    funciton Hello() {
        var name;

        this.setName = function (n) {
            name = n;
        }
        this.sayHello = function () {
            console.log('Hello ' + name + '!');
        }
    }

    module.exports = Hello;     // 这样可以直接通过require('hello')来获得Hello对象
    ```

- package.json

    package.json是CommoJS规定的用来描述包的文件

    Node.js调用包时，会检查package.json中的main字段，如果不存在，会尝试寻找index.js或index.node作为包的接口

    ```javascript@lineNum
    {
        "name": "mypackage",        // 包的名字
        "description": "Sample package for CommonJS. This package demonstrates"
            + " the required elements of a CommonJS packages.",     // 简要说明
        "version": "0.7.0",         // 版本
        "keywords": [               // 关键字数组，用于搜索
            "package",
            "example"
        ],
        "maintainers": [{           // 维护者数组
            "name": "Bill Smith",
            "email": "bill@example.com"
        }],
        "contributors": [{          // 贡献者
            "name": "BYVoid",
            "web": "http://www.byvoid.com/"
        }],
        "bugs": {                   // 提交bug的地址
            "mail": "dev@example.com",
            "web": "http://www.example.com/bugs"
        },
        "licenses": [{              // 许可证
            "type": "GPLv2",
            "url": "http://www.example.org/licenses/gpl.html"
        }],
        "repositories": [{          // 仓库托管数组
            "type": "git",
            "url": "http://github.com/BYVoid/mypackage.git"
        }],
        "dependencies": [{          // 包依赖
            "webkit": "1.2",
            "ssl": {
                "gnutls": ["1.0", "2.0"],
                "openssl": 0.9.8
            }
        }]
    }
    ```

## Node.js核心模块

### 全局对象

ECMAScript定义的全局变量满足：

- 在最外层定义的变量
- 全局对象的属性
- 隐式定义的变量

```javascript
process.argv    // 命令行参数数组，第一个参数是node，的二个参数是脚本名
process.stdout, process.stdin.resume()
process.nextTick(callback);
process.platform, process.pid, process.execPath, process.memoryUsage()

console.log(), console.error(), console.trace()
```
### util

```javascript
util.inherits(constructor, superConstructor)
util.inspect(object, [showHidden], [depth], [colors]);
```

### events

```javascript
event.EventEmitter;
EventEmitter.on(event, listener);
EventEmitter.emit(event, [arg1], [arg2], [...]);
EventEmitter.once(event, listener);
EventEmitter.removeListener(event, listener);
EventEmitter.removeAllListener([event]);

emitter = new event.EventEmitter();
emitter.on('some_event', function () {
    console.log('some event happen');
})
emitter.emit('some_event');

// EventEmitter定义了一个特殊的事件error
emitter.emit('error');
```

### fs

```javascript
fs.readFile('file.txt', function (err, data) {
    if (err) {
        console.error(err);
    } else {
        console.log(data);
    }
});

fs.readFile(filename, [options], callback)
fs.readFileSync(filename, [options])
fs.writeFile(filename, data, [options], callback)
fs.writeFileSync(filename, data, [options])
```

## Node.js进阶话题

### 模块加载机制

1. 如果module是一个核心模块，直接加载，结束
2. 如果module以"/"，"./"，"../"开头，按路径加载module，结束
3. 按路径./node_module/module加载
    - 如果加载成功，结束
    - 加载失败，寻找父目录中的node_module
    - 重复这一过程，直到找到

### 控制流

```javascript@lineNum
var fs = require('fs');
var files = ['a.txt', 'b.txt', 'c.txt'];

// 陷阱，i的值为3，file[i]为undefined
for (var i = 0; i < files.length; i++) {
    fs.readFile(file[i], 'utf-8', function (err, contents) {
        console.log(file[i] + ': ' + contents);
    });
}

// 创建闭包
for (var i = 0; i < files.length; i++) {
    (function (i) {
        fs.readFile(file[i], 'utf-8', function (err, contents) {
            console.log(file[i] + ': ' + contents);
        })
    })(i);
}

// array.forEach
files.forEach(function (filename) {
    fs.readFile(filename, 'utf-8', function (err, contents) {
        console.log(filename + ': ' + contents);
    });
});
```

## 链接

- [nodejs官网](http://nodejs.org/)
- [npm官网](https://www.npmjs.org/)
- [nodejs API](http://nodejs.org/api/)
