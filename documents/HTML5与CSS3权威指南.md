# HTML5与CSS3权威指南

陆凌牛 著

## Web时代的变迁

```html
<form><p><label>Search: <input name=search autofocus></label></p>

<!-- html4 -->
<div id="header"> ... </div>
<div id="nav"> ... </div>
<div class="article"> ... </div>
<div id="side-bar"> ... </div>
<div id="footer"> ... </div>

<!-- html5 -->
<header> ... </header>
<nav> ... </nav>
<article> ... </article>
<aside> ... </aside>
<footer> ... </footer>
```

## HTML5与HTML4的区别


```html
<!DOCTYPE html>
<meta charset="UTF-8">
<title>HTML5标记示例</title>
<p>这段代码是根据HTML5语法编写的</p>
```

1. DOCTYPE声明

    ```html
    <!DOCTYPE html>
    ```

2. 指定字符编码

    ```html
    html4: <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    html5: <meta charset="UTF-8">
    ```

3. 可以省略的标记

    ```
    不允许写结束标记的元素
    area, base, br, col, command, embed, hr, img, input,
    keygen, link, meta, param, source, track, wbr

    可以省略结束标记的元素
    li, dt, dd, p, rt, rp, optgrou, option, colgroup, thread,
    tbody, tfoot, tr, td, th

    可以省略全部标记的元素
    html, head, body, colgroup, tbody
    ```

4. boolean

    ```html
    <input type="checkbox" checked>              // checked = true
    <input type="checkbox" checkbox="">          // checked = true
    <input type="checkbox" checkbox="checked">   // checked = true
    <input type="checkbox">                      // checked = false
    ```

5. 当属性值不包括空字符串、<>='"时，属性两遍的引号可以省略
6. 新增和废除

    ```
    新增元素
    section, article, aside, header, hgroup, footer, nav, figure,
    video, audio, embed, mark, progress, time, ruby, rt, rp, wbr,
    canvas, command, details, detalist, datagrid, keygen, output,
    source, menu

    新增input元素类型
    email, url, number, range, Date Pickers

    废除元素
    basefont, big, center, font, s, strike, tt, u
    frameset, frame, noframes
    applet, bgsound, blink, marquee
    rb, acronym, isindex, listing, xmp, nextid, plaintext
    ```

7. 全局属性

    ```
    contentEditable     允许用户编辑元素的内容
    designMode          指定整个页面是否可编辑
    hidden              隐藏
    spellcheck          拼写检查
    tabindex            敲击tab键来获得焦点
    ```

## 绘制图形

```javascript
// 获得canvas 和 context
function draw(id) {
    var canvas = document.getElementById(id);
    if (!canvas) {
        return false;
    }

    var context = canvas.getContext('2d');
    context.fillStyle = '#EEEEFF';
    context.fillRect(50, 50, 100, 100);
}

context.fillStyle = 'blue | rgba(255, 0, 0, 0.25) | #ff0000';     // 填充颜色
context.strokeStyle = 'red';    // 边框颜色
context.linewidth = '2px';      // 线宽
context.fillRect(x, y, width, height)       // 绘制矩形
context.strokeRect(x, y, width, height)     // 绘制矩形边框

context.beginPath()     // 开始创建路径
context.arc(x, y, radius, startAngle, endAngle, anticlockwise)  // 创建弧形路线
context.closePath()     // 关闭路径
context.fill()          // 填充路径
context.moveTo()        // 将光标移动到某点
context.lineTo()        // 绘制一条直线

context.bezierCurveTo   // 绘制贝济埃曲线

context.createLinerGradient(xStart, yStart, xEnd, yEnd);    // 绘制渐变
context.addColorStop(offset, color)     // 添加渐变颜色
context.createRedialGradient(xStart, yStrat, radiusStart,
    xEnd, yEnd, radiusEnd)      // 径向渐变

context.translate(x, y)     // 移动坐标原点
context.scale(x, y)         // 缩放
context.rotate(angle)       // 旋转

context.transform(m11, m12, m21, m22, dx, dy);  // 矩阵变换

context.globalCompositeOperation = 'type' // 图形组合方式
    type = source-over | source-in | destination-in
        | source-out | destination-out
        | source-atop | desination-atop
        | lighter | xor | copy

context.shadowOffsetX = 10  // 阴影横向偏移量
context.shadowOffsetY = 10  // 阴影纵向偏移量
context.shadowColor = 'rgba(100, 100, 100, 0.5)' // 阴影颜色
context.shadowBlur = 4      // 阴影模糊范围

image = new Image();
image.src = 'image.png';
context.drawImage(image, x, y);
context.drawImage(image, x, y, w, h);
context.drawImage(image, sx, sy, sw, sh, dx, dy, dw, dh);   // 图像复制
context.createPattern(image, type)  // 图像平铺
    type = no-repeat | repeat-x | repeat-y | repeat
context.clip()  // 图像剪裁
var imageData = context.getImageData(sx, sy, sw, sh);   // 获取像素

context.fillText(text, x, y, [maxWidth]);       // 绘制文字
context.strokeText(text, x, y, [maxwidth]);     // 绘制文字轮廓
context.font = 'Consola'
context.textAlign = 'start | end | left | right | center';
context.textBaseline = 'top | hanging | middle | alphabetic | ideographic | button';
var metrics = context.measureText(text);        // 获取文字的宽度
context.save();     // 保存当前状态
context.restore();  // 恢复到之前状态
```

## 多媒体播放

1. html5与html4的差别

    ```html
    html4 播放视频
    <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000"
        width="425" height="344" codebase="swflash.cab#version=6,0,40,0">
        <param name="allowFullScreen" value="true" />
        <param name="allowscriptaccess" value="always" />
        <param name="allowfullscreen" value="true" />
        <embed type="application/x-shookwave-flash"
            width="425"
            height="344"
            src="p.swf"
            allowscriptaccess="always"
            allowfullscreen="true">
        </embed>
    </object>

    html5
    <audio src="http://xxxx/xxx.mp3">您的浏览器不支持audio</audio>
    <video width="640" height="360" src="http://xxxx/xxx.mp4">
        您的浏览器不支持video
    </video>
    <video>
        <source src="sample.ogv" type="video/ogg; codecs='theora, vorbis'">
        <source src="sample.mov" type="video/quicktime">
    </video>
    ```

2. 属性

    ```
    src         URL地址
    autoplay    自动播放
    preload     预加载
    poster      video，视频不可用时用图片代替
    loop        循环播放
    controls    进度条
    width       宽度
    height      高度
    error       错误
    networkstate    当前网络的状态
        NETWORK_EMPTY       0初始状态
        NETWORK_IDLE        1尚未建立连接
        NETWORK_LOADING     2数据加载中
        NETWORK_NO_SOURCE   3没有支持的编码格式
    currentSrc  当前媒体URL地址
    buffered    缓存
    readyState  就绪状态
        HAVE_NOTHING        0没有可播放数据
        HAVE_METADATA       1获取到足够的媒体数据，当前播放位置没有有效媒体数据
        HAVE_CURRENT_DATA   2当前位置可以播放，但是没有获取到可以让播放器前进的数据
        HAVE_FUTURE_DATA    3当前帧是播放的最后一帧
        HAVE_ENOUGH_DATA    4可以播放
    seeking与seekable
    currentTime, startTime, duration
    played, paused, ended
    defaultPlaybackRate, playbackRate
    volume, muted
    ```

3. 方法

    ```javascript
    play, pause, load, cunPlayType('' | 'maybe' | 'probably');
    addEventListener(type, listener, useCapture);
    video.addEventListener('error', function() {
        // do something;
    }, false);
    ```

## 本地存储

### Web Storage

1. cookies存储永久数据的问题：

    - cookies大小限制为4KB
    - cookies随http事务一起发送，浪费带宽
    - cookies比较复杂

2. Web Storage分为两种

    - sessionStorage将数据保存在session中
    - localStorage将数据保存在客户端本地的硬件设备上

3. 方法

    ```javascript
    sessionStorage.setItem(key, value);         // 保存数据
    var value = sessionStorage.getItem(key);    // 读取数据

    localStorage.setItem(key, value);           // 保存数据
    localStorage.getItem(key);                  // 读取数据
    ```

### 本地数据库

```javascript
var db = openDatabase('mydb', '1.0', 'TestDB', 2 * 1024 * 1024);

db.transaction(function (tx) {
    tx.executeSql('CREATE TABLE IF NOT EXISTS LOGS (id unique, Log)');
});

tx.executeSql(sqlquery, [], dataHandler, errorHandler);
    function dataHandler(transaction, results)
    function errorHandler(transaction, errmsg)
```

## 离线应用程序

```bash
CACHE MANIFEST
#version 7

# 需要被缓存的文件
CACHE
other.html
hello.js
images/photo.jpg

# 显式指定不进行本地缓存的文件
NETWORK
http://xxxx/xxxx
notoffline.asp
*

# 指定两个资源文件，第一个是在线访问的资源文件
# 第二个是不能在线访问的本地缓存备用资源文件
FALLBACK
online.js locale.js

CACHE
newhello.html
newhello.js
```

浏览器与服务器的交互过程

1. 浏览器请求访问http://xxxx/xxxx/
2. 服务器返回index.html
3. 浏览器解析index.html，请求页面上的所有资源文件，包括HTML文件，图像文件，css文件，Javascript文件，以及manifest文件
4. 服务器返回所有资源文件
5. 浏览器处理manifest，请求manifest中所有要求本地缓存的文件，包括index.html本身
6. 服务器返回所有要求本地缓存的文件
7. 浏览器对本地缓存进行更新，保存所有要求缓存的资源文件，并触发一个事件，通知本地缓存被更新

    ```javascript
    applicationCaches.onUpdateReady = function() {
        // 本地缓存已被更新
        applications.swapCache();
    }
    ```

## 通信API

### 跨文档消息通信

```javascript
window1.addEventListener('message', function() {...}, false);
window2.postMessage(message, targetOrigin);
```

### Web Sockets通信

```javascript
var webSocket = new WebSocket('ws://localhost:8005/socket');
webSocket.send('data');
webSocket.onmessage = function(event) {
    var data = event.data;
    ...
}
webSocket.onopen = function(event) {
    // 开始通信时的处理
}
webSocket.onclose = function(event) {
    // 通信结束时的处理
}
webSocket.close()
```

## 使用Web Workers处理线程

```html
// html5
<script type="text/javascript">
    var worker = new Worker('SumCalculate.js');

    worker.onmessage = function(event) {
        alert('合计的值为' + event.data + '。');
    }

    function calculate() {
        var num = parseInt(document.getElementById('num').value, 10);
        worker.postMessage(num);
    }
<script>

// SumCalculate.js
onmessage = function(event) {
    var num = event.data;
    var sum = 0;
    for (var i = 0; i <= num; i++) {
        sum += i;
    }
    postMessage(sum);
}
```

## 获取地理位置信息

### Geolocation API

```javascript
navigator.geolocation.getCurrentPosition(function (position) {
    // 获取成功时的处理
}, function (error) {
    // 错误处理
});

int watchCurrentPostion(onSuccess, onError, options);
void clearWatch(watched);

position对象属性
    latitude    纬度
    longitude   经度
    altitude    海拔
    accuracy    经纬度精度
    altitudeAccurancy   海拔高度精度
    heading     设备的前进方向
    speed       设备的前进速度
    timestamp   时间戳
```

### Google Map API

```html
// 1. 导入Google Map API脚本
<script type="text/javascript" src="http://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY&sensor=SET_TO_TRUE_OR_FALSE" />

// 2. 设置地图参数
// 指定一个google地图上的坐标点
var latlng = new google.maps.LatLng(coords.latitude, coords.longitude);
var myOptions = {
    zoom: 14,       // 放大倍数
    center: latlng  // 地图中心点
    mapTypeId: google.maps.MaptypeId.ROADMAP    // 地图类型
}

// 3. 创建地图
var mymap = new google.maps.Map(document.getElementById('map'), myOptions);

// 4. 在地图上创建标记
var marker = new google.maps.Marker({
    postion: latlng,
    map: mymap
});

// 5. 设置标注窗口并指定标注窗口中注释文字
var infoWindow = new google.maps.InfoWindow({
    content: '当前位置'
});

// 6. 打开标注窗口
infoWindow.open(mymap, marker);
```


## 元素参考

```bash
# HTML5结构
article     代表文档、页面或应用程序中独立的、完整的、可以独自被外部引用的内容
section     section中的内容可以单独存储到数据库或word文档中，由标题和内容组成
nav         用作页面导航的链接组
aside       表示当前页面或文章的附属部分
time        定义时间或日期
header      具有引导和导航作用的结构
hgroup      将标题及其子标题进行分组的
footer      上层父级内容区域或是一个根区域的脚注
address     用在文档中呈现联系信息，包括文档作者或文档维护者的名字，网站，邮箱等

# 表单与文件
form        表单
input       输入
figure      元素的组合，表示网页上独立的内容
figcaption  表示figure元素的标题
details     将画面上局部区域进行展开和收缩
mark        页面中需要突出显示或者高亮显示
progress    表示一个任务的完成进度
meter       表示规定范围的数值
dl          定义术语的列表
dt          术语的标题
dd          术语的内容
cite        表示作品的标题
small       “小子印刷体”

# 绘制图形
canvas      画布

# 多媒体
video       视频
audio       音频
```

## CSS3选择器

### 属性选择器

```
[attr=val]      // 属性的值为val
[attr^=val]     // 属性的值以val开头
[attr*=val]     // 属性的值包含val
[attr$=val]     // 属性的值以val结尾
```

### 结构性伪类选择器

```
p:first-line
p:first-letter
element:before  // 在元素之前插入
element:after   // 在元素之后插入
:root  // 文档最顶层元素，在html中指<html>页面
:not   // 排除元素
:empty // 当元素空白时的样式
:target     // 用户点击超链接，跳转到target元素后起作用
:first-child, last-child, nth-child, nth-last-child  // 子元素
:nth-of-type, nth-last-of-type // 同类型的子元素

body *:not(h2) {...}
li:nth-child(4n+2) {...}
li:nth-child(odd) {...}
li:nth-child(even) {...}
element:nth-child(1):nth-last-child(1) {...} // 只有一个子元素
```

### UI状态伪元素

```
:havor      // 鼠标移动到元素
:active     // 鼠标按下还未松开
:focus      // 元素获得焦点
:enable     // 元素处于可用状态
:disable    // 元素处于不可用状态
:read-only, read-write
:checked, default, indeterminate
:selection  // 元素处于选中状态
```

## 使用选择器在页面插入内容

```css
/* 将alt属性作为图像的标题显示 */
img:after {
    content: attr(alt);
    display: block;
    text-align: center;
    margin-top: 5px;
}
/* 标题连续编号 */
h2 {
  counter-increment: h2counter;
  counter-reset: h3counter;
}
h3 {
  counter-increment: h3counter;
  counter-reset: h4counter;
}
h2:before {
  content: counter(h2counter)'  ';
}
h3:before {
  content: counter(h2counter)'.'counter(h3counter)'  ';
}
```

## 文字与字体相关样式

```css
/* 文字添加阴影text-shadow */
div {
    /* x偏移，y偏移，模糊半径，颜色 */
    text-shadow: 5px, 5px, 5px, gray；
    color: navy;
    font-size: 50px;
    font-weight: bold;
    font-family: 宋体;
}

/* 自动换行word-break */
div {
    /**
     *  normal      使用浏览器默认规则
     *  keep-all    只能在半角空格或连字符换行
     *  break-all   允许在单词内换行
     */
    word-break: keep-all;

    /* 长单词与url地址自动换行 */
    word-wrap: break-word;
}

/* 使用服务器端字体 */
@font-face {
    font-family: WebFont;
    src: url('font/Fontin_Sans_R_45b.otf') format("opentype");
    font-weight: normal;
}
```

## 盒相关样式

```css
/* inline, block, inline-block, inline-table,   */
/* list-item, run-in, compact, none             */

div {
    display: inline-block;
}

div {
    overflow-x: hidden;     /* x方向溢出隐藏 */
    overflow-y: scroll;     /* y方向溢出滚动 */
    text-overflow: ellipsis;    /* 超出显示省略号 */
}

div {
    white-space: nowrap;    /* 不允许换行 */
}

div {
    /* x偏移，y偏移，模糊半径，颜色 */
    box-shadow: 10px, 10px, 10px, gray;     /* 盒阴影效果 */
}

/* box-sizing: content-box | padding-box | border-box; */
```

## 与背景和边框相关的样式

```
background-clip     指定背景的显示范围
    broder          包含边框
    padding         不包含边框
background-origin   指定绘制背景图像时的起点
    broder          左上角
    padding         内部补白区域的左上角
    content         内容的左上角
background-size     指定背景中图像的尺寸
background-break    指定背景图像进行平铺时循环的方式
    bounding-box    在整个背景中进行平铺
    each-box        每一行平铺
    continuous      下一行的图像紧接着上一行中的图像继续平铺
background-image    背景图像
    url(photo.png)
background-repeat   重复方式
    repeat | repeat-x | repeat-y | no-repeat | inherit

border-image        边框图像
    url(border_image.png) top-width right-width bottom-width left-width
border-radius       边框圆角

div {
    border: 1px solid #ccc;
    border-radius: 5px;
    box-shadow: #aaa 0px 0px 7px;
}
```

## 变形处理

```css
div {
    /* 平移，旋转，缩放 */
    transform: translate(150px, 200px) rotate(45deg) scale(1.5);
}
```

## 动画功能

```css
/* transition 平滑过渡 */
div {
    background: #FFFF00;
    color: #000000;
    width: 300px;
    transition: background-color 1s linear, color 1s linear, width 1s linear;
}

div:hover {
    background: #003366;
    color: #FFFFFF;
    width: 400px;
}

/* animation 功能 */
@-webkit-keyframes fadein {
    0% {
        opacity: 0;
        background-color: white;
    }
    100% {
        opacity: 1;
        background-color: white;
    }
}
body {
    animation-name: fadein;
    animation-duration: 5s;
    animation-timing-function: linear;
    animation-iteration-count: 1;
}
```

## 布局相关样式

```css
div {
    column-count: 2;
    column-width: 20em;
}
```

## Media Queries相关样式

```css
@media screen and (min-width: 1000px) {
    #container {
        width: 1000px;
    }
    #wrapper {
        width: 700px;
        float: left;
    }
    #main {
        width: 560px;
        float: right;
    }
    #sub01 {
        width: 200px;
        float: left;
    }
    #sub02 {
        width: 200px;
        float: right;
    }
}
@media screen and (min-width: 640px) and (max-width: 999px) {
    #container {
        width: 640px;
    }
    #wrapper {
        width: 640px;
        float: none;
    }
    #main {
        width: 420px;
        float: right;
    }
    p {
        line-height: 400px;
    }
    #sub01 {
        width: 200px;
        float: left;
    }
    #sub02 {
        width: 200px;
        float: none;
        clear: both;
        line-height: 150px;
    }
}
@media screen and (max-width: 639px) {
    #container {
        width: 100%;
    }
    #wrapper {
        width: 100%;
        float: none;
    }
    body {
        margin: 20px;
    }
    #main {
        width: 100%;
        float: none;
    }
    p {
        line-height: 300px;
    }
    #sub01 {
        width: 100%;
        float: none;
        line-height: 100px;
    }
    #sub01 {
        width: 100%;
        float: none;
        line-height: 100px;
    }
}
```

## 其他重要样式和属性

```
opacity         透明度 0~1
transparent     完全透明
resize          允许用户改变元素大小，none | both | horizontal | vertical | inherit
```
