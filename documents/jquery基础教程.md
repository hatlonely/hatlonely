# jquery基础教程

[美] Jonathan Chaffer  Karl Swedberg 著  李松峰 译

```html
<script type="text/javascript"
    src="http://ajax.googleapis.com/ajax/libs/jquery/1.4.0/jquery.min.js">
</script>
```

## 选择元素

```javascript
$("A B")    // 查找A元素下面的所有子节点，包括非直接子节点
$("A > B")  // 查找A元素下面的直接子节点
$("A + B")  // 查找A元素后面的兄弟节点，包括非直接子节点
$("A ~ B")  // 查找A元素后面的兄弟节点，不包括非直接子节点

$("#myId")
$(".myclass")
$("li:first")
$("tr:odd")

$('#selected-plays > li').addClass('horizontal');
$('#selected-plays li:not(.horizontal)').addClass('sub-level');
$('img[alt]'); // 所有带有alt属性的img元素
$('a[href^="mailto"]').addClass('mailto');  // 带有href属性的a元素且以mailto开头
$('a[href$=".pdf"]'.addClass('pdflink'));   // 带有href属性的a元素且以.pdf结尾
// 带有href属性的a元素且以http开头包含henry
$('a[href^="http"][href*="henry"]').addClass('henrylink');
$('div.horizontal:eq(1)');  // 从带有horizontal类的div元素集合中选择第2项
$('tr:even').addClass('alt');   // 位置为偶数（从0开始奇数）的tr标签
$('tr:nth-child(odd)').addClass('alt');     // 相对父元素的位置为奇数的tr标签
$('td:contains(Henry)').addClass('highlight');  // 包含henry的td元素

$('tr').filter(':even').addClass('alt');    // $('tr:even')
$('a').filter(function() {
    return this.hostname && this.hostname != location.hostname;
}).addClass('external');
```

## 事件

```javascript
$(document).ready(function() {
    $('td:contains(Henry)').next().addClass('highlight');
});
$(document).ready(function() {
    $('td:contains(Henry)').nextAll().addClass('highlight');
});
$(document).ready(function() {
    $('td:contaions(Henry)').prev().addClass('highlight');
})

$('td:contains(Henry)') //取得包含Henry的所有单元格
    .parent() //取得它的父元素
    .find('td:eq(1)') //在父元素中查找第2个单元格
    .addClass('highlight') //为该单元格添加hightlight类
    .end() //恢复到包含Henry的单元格的父元素
    .find('td:eq(2)') //在父元素中查找第3个单元格
    .addClass('highlight'); //为该单元格添加hightlight类

$('#switcher h3').hover(function() {
    $(this).addClass('hover');
}, function() {
    $(this).removeclass('hover');
});

$('#switcher button').click(function(event) {
    $(this).addClass('selected');
    event.stopPropagation();
});

event.stopPropagation();
event.preventDefault();
```

## 样式与动画

```javascript
element.css({property: 'value'});
element.hide();
element.show();
element.toggle();
element.fadeIn();
element.fadeOut();
element.fadeTo();
element.slideDown();
element.slideUp();
element.slideToggle();
element.animate({properties}, duration, easing, callback);
element.animate({properties}, {options});
element.animate({
    property1: 'value1',
    property2: 'value2'
}, {
    duration: 'value',
    easing: 'value',
    specialEasing: {
        property1: 'easing1',
        property2: 'easing2'
    },
    complete: function() {
        ...
    },
    queue: true,
    step: callback
});
element.css({position: 'relative'})
    .animate({left: paraWidth - switchWidth}, 'slow')
    .animate({height: '+=20px'}, 'slow')
    .animate({borderWidth: '5px'}, 'slow');
element.css({position: 'relative'})
    .fadeTo('fast', 0.5)
    .animate({left: paraWidth - switcherWidth}, 'slow')
    .fadeTo('slow', 1.0)
    .slideUp('slow')
    .slideDown('slow');
element.css({position: 'relative'})
    .fadeTo('fast', 0.5)
    .animate({
        left: paraWidth - switcherWidth
    }, {
        duration: 'slow',
        queue: false
    })
    .fadeTo('slow', 1.0)
    .slideUp('slow')
    .queue(function(next) {
        element.css({backgroundColor: '#f00'});
        next();
    })
    .slideDown('slow');
```

## 操作DOM元素

```javascript
element.addClass()
element.removeClass();
element.toggleClass();
element.attr();
element.removeAttr();
element.css();
element.prop();

$(document).ready(function() {
    $('div.chapter a').attr({
        rel: 'external',
        title: 'learn more at Wikipedia'
    });
})

$('.my-checkbox').prop('checked');  // 取得属性值
$('.my-checkbox').prop('checked', false);   // 设置属性值
$('<a href="#top">back to top</a>').insertAfter('div.chapter p');

newElement.insertAfter();
newElement.insertBefore();
newElement.prependTo();
newElement.appendTo();
element.wrap();
element.each(function);
element.append();
element.before();
element.html();
element.text();
```

## Ajax

```javascript
$.getJSON('a.json', callback);
$.get('e.php', requestData, function (data) {
    $('#dictionary').html(data);
})
$.post('e.php', requestData, function (data) {
    $('#dictionary').html(data);
})
$(object).serialize();
$(document).ready(function() {
    $('#letter-f form').submit(function (event) {
        event.preventDefault();
        var formValues = $(this).serialize();
        $.get('f.php', formValues, function(data) {
            $('#dictionary').html(data);
        })
    })
})
$(document).ajaxStart(function)
$(document).ajaxStop(function)
$(document).ready(function () {
    $(document).ajaxStart( function() {
        $('#loading').show();
    })
    .ajaxStop(function (){
        $('#loading').hide();
    });
});
element.load('a.html', function () {
    $(this).fadeIn();
});
$.get.done().always().fail();
$.get('z.php', requestData, function (data) {
    $('#dictionary').html(data);
}).fail(function(jqXHR) {
    $('#dictionary').html('An error occured: ' + jqXHR.status)
        .append(jqXHR.responseText);
});

$.ajax({
    url: 'a.html';
    success: function (data) {
        $('#dictionary').html(data);
    }
});

$.extend(defaults, options);
$('#news').find('tr:nth-child(even)').addClass('alt');
elements.filter();
elements.not();
```
