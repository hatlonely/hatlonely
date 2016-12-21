# vim总结

## 光标移动

- 基本

    ```
    h j k l
    ```

- 词

    ```
    b   向前移动，光标停在第一个字符 (backward)
    w   向后移动，光标停在第一个字符 (word)
    e   向后移动，光标停在最后一个字符 (end of word)
    ```

- 行首或行尾

    ```
    $   移动到行尾
    ^   移动到行首，非空白字符
    0   移动到行首，第一个字符
    ```

- 指定字符

    ```
    f   单行搜索下一个单个字符 (find)
    F   单行搜索上一个单个字符
    t   单行搜索下一个单个字符，光标停在前一个字符 (to)
    T   单行搜索上一个单个字符，光标停在前一个字符
    ```

- 匹配括号

    ```
    %   移动到匹配的括号或移动到括号
    ```

- 移动到指定行

    ```
    G    移动到最后一行
    33G  移动到第 33行
    gg   移动到第一行
    40%  移动到40%
    H    移动到屏幕内第一行 (home)
    M    移动到屏幕内中间 (middle)
    L    移动到屏幕内最后一行 (last)
    ```

- 滚屏

    ```
    <c-u>  向上滚动半屏 (up)
    <c-d>  向下滚动半屏 (down)
    <c-f>  向下滚动一屏 (forward)
    <c-b>  向上滚动一屏 (backward)
    ```

- 简单查找

    ```
    /string      向下查找包含 string的词
    ?string      向上查找包含 string的词
    /\<string\>  向下查找 string
    ?\<string\>  向上查找 string
    n            重复前一次查找
    N            重复前一次相反的查找
    /<up>        之前的查找
    *            向下查找光标所在处的词，全词匹配
    #            向上查找光标所在处的词，全词匹配
    g*           向下查找包含光标所在处的词
    g#           向上查找包含光标所在处的词
    ```

- 标记:

    ```
    m{mark}  讲此处标记为 mark，mark 为一个字母
    `{mark}  跳到标记 mark处，` 是1左边那个键
    '{mark}  跳到标记 mark处所在行行首，'是单引号
     特殊的mark
        '  此次跳转之前的起跳点
        "  上次编辑该文件时光标最后停留的位置
        [  最后一次修改的起始位置
        ]  最后一次修改的结束位置
    ```

- 其他命令

    ```
    :set number    显示行号，左边 (se nu)
    :set nonumber  不显示行号(se nonu)
    :set ruler     显示光标位置，右下角 (se ru)
    :set noruler   不显示光标位置 (se noru)

    :set ignorecase    查找忽略大小写
    :set noignorecase  查找不忽略大小写
    :set hlsearch      查找高亮 (se hls)
    :set nohlserch     关闭查找 (se nohls)
    :set incsearch     键入目标字符串时就开始查找
    :set nowrapscan    搜索过程在文件结束时就停止
    ```

## 简单修改

- 插入

    ```
    i  在当前光标处插入
    I  在当前行第一个非空白字符前插入
    a  在当前光标之后插入
    A  在当前行尾插入
    o  在当前行之下插入
    O  在当前行之上插入
    ```

- 删除

    ```
    d   删除操作符 (delete)
    c   修改操作符，删除之后自动进入插入 (change)
    dd  删除一行
    cc  修改一行
    x   dl ，删除光标处字符
    X   dh ，删除光标左边的字符
    D   d$ ，删除到行尾
    C   c$ ，修改到行尾
    s   cl ，修改光标字符
    S   cc ，修改一整行
    r   替换（删除之后插入并回到 Normal）
    .   执行上一次所执行的更改命令
    ```

- 复制

    ```
    y    复制操作符 (yanking)
    yy   复制一行
    yw   复制word，包含之后空白字符
    ye   复制word，不包含之后空白字符
    yaw  复制word，包含之后空白字符
    yiw  复制word，不包含之后空白字符
    yab  复制一个小括号里面的内容，包括括号本身
    yib  复制一个小括号里面的内容，不包括括号本身
    ya{  复制一个大括号里面的内容，包括括号本身
    yi{  复制一个大括号里面的内容，不包括括号本身
    p    粘贴(put)
    ```

- 对齐

    ```
    =    对齐操作符
    ==   对齐一行
    n==  对齐n行
    =a{  对齐一个大括号里面的内容
    ```

- 大小写替换

    ```
    ~     大小写替换
    g~    大小写替换操作
    g~iw  改变光标处单词大小写
    guiw  光标处单词变成小写
    gUiw  光标处单词变成大写
    ```

- 命令计数器 n+命令

    ```
    一个命令重复执行
    如：4x删除 4个字符
    ```

- 操作命令符 +位移命令符

    ```
    操作如：删除 d，复制y ；位移如：词语 w，$ 行尾
    d$    删除到句尾
    4yy   复制4行
    3dw   3次删除一个单词
    d3w   一次删除 3个单词
    3d2w  3次删除 2个单词
    ```

- 常用删除命令

    ```
    x(dl), X(dh), D(d$), dw, db, diw, daw, dG, dgg
    ```

- visual 模式（主要功能就是选择）

    ```
    v 进入visual模式，移动光标选择操作文本范围
    V 进入visual行模式，选择以行为单位
    <c-v> 进入visual块模式，选择块
    ```

## 查找替换

- 查找命令

    ```
    /, ?, n, N, #, *, g#, g*, gd, gD
    ```

- 替换命令

    ```
    :[n,m]s/[src]/[dst]/[g][c]
    [n,m]  表示一个范围，从 n~m行中查找替换，[n,$]表示从第 n行之后
    %      表示整个文件
    [src]  要查找的词， [dst]要替换的词
    [g]    替换所有的匹配，若没有，只匹配第一个
    [c]    替换前询问
    /      为分隔符，也可以用 +或# 来分隔

    :s/src/dst/         替换当前行第一个 src为dst
    :s/src/dst/g        替换当前行所有 src为dst
    :n,ms/src/dst/      替换n~m行第一个 src为dst
    :n,$s/src/dst/g     替换第n行到最后一行中所有 src为dst
    :%s/src/dst/g       替换整个文件中所有 src为dst
    :%s/src/dst/gc      替换整个文件中所有 src为dst 并询问是否替换
    :%s/\<src\>/dst/gc  与:%s/src/dst/gc一样（全词匹配）
    ```

- 正则匹配

    ```
    *   匹配0以上之前的字符
    \+  匹配1个以上之前字符
    \=  匹配0个或 1个之前字符
    \?  匹配0个或 1个之前字符
    .   匹配任何单个字符
    \<  匹配一个单词的开始
    \>  匹配一个单词的结束
    \s  匹配空白字符 <space>和<tab>
    \S  匹配非空白字符
    \d  数字[0-9]
    \D  非数字[^0-9]
    \x  十六进制数字 [0-9A-Fa-f]
    \X  费十六进制数字 [^0-9A-Fa-f]
    \l  小写字符 [a-z]
    \L  非小写字符 [^a-z]
    \u  大写字符 [A-Z]
    \U  非大写字符 [^A-Z]
    \a  字符[A-Za-z]
    \A  非字符[^A-Za-z]
    []  任何[]中的字符
    ```

- 更多

    ```
    :help pattern
    ```

## 折叠

- 折叠方式

    ```
    manual  手工定义折叠
    indent  更多的缩进表示更高级的折叠
    expr    用表达式来定义折叠
    syntax  用语法高亮来定义折叠
    diff    对没有更改的文本进行折叠
    marker  对文中的标志折叠
    set foldmethod=****   设置折叠方式
    marker方式,需要用标记来标识代码的折叠，系统默认是 {{{和}}}
    ```

- 折叠命令

    ```
    zc      折叠
    zC      对所在范围内所有嵌套的折叠点进行折叠
    zo      展开
    zO      对所在范围内所有嵌套的折叠点展开
    zr, zR  折叠所有
    zm, zM  展开所有
    za, zA  折叠/打开当前折叠
    zi      折叠/展开所有
    [z      到当前打开的折叠开始处
    ]z      到当前打开的折叠末尾处
    zj      向下移动到下一个折叠开始处
    zk      向上移动到前一折叠的结束处
    zf      创建折叠
    zf56G   创建从当前行起到 56行的代码折叠
    10zf    创建从当前行起后 10行的代码折叠
    10zf-   创建从当前行起到之前 10行的代码折叠
    zf%     创建从当前行起到对应匹配的括号
    zd      删除光标下的折叠，仅当 manual或marker 方式有效
    zD      嵌套地删除光标下的折叠，仅当 manual或marker 方式有效
    zE      除去窗口里的所有折叠，仅当 manual或marker 方式有效
    ```

- foldlevel

    ```
    'foldlevel' 是个数值选项：数字越大则打开的折叠更多
    当 'foldlevel' 为 0 时，所有的折叠关闭
    当 'foldlevel' 为正数时，一些折叠关闭
    当 'foldlevel' 很大时，所有的折叠打开
    'foldlevel' 的改变后立即生效。之后，折叠可以被手动地打开和关闭
    ```

## 文件

- 文件操作

    ```
    :w    保存
    :w!   强制保存
    :w filename        将当前缓冲区的内容保存成文件 filename
    :n1, n2, filename  将n1到 n2的内容保存为文件filename
    :q    退出当前窗口，若改动，提示失败
    :q!   强制退出，放弃改动
    :wq   保存后退出
    :wa   保存所有
    :qa   退出所有
    :wqa  保存所有后退出
    ZZ    相当于:wq
    ```

- 编辑另一个文件

    ```
    :edit file
    ```

- 多文件编辑

    ```
    vim filename1 filename2 ...
    :bn  跳转至下一缓冲区 (文件)( 最后一个 ->第一个)
    :bN  跳转到上一缓冲区 (文件)( 第一个->最后一个 )
    :bd  关闭当前缓冲区 (文件)
    :n   跳转至下一文件 ,如当前文件为最后一个,提示错误
    :N   跳转至上一文件 ,如当前文件为第一个,提示错误
    :next, :previous    跳转至下 /上一文件
    :wnext, :wprevious  保存当前文件并跳转至下 /上一文件
    :last, :first       跳转至最后一个 /第一个文件
    :files   列出当前已打开文件
    :args    给出进入 vim时命令行参数；当前正在编辑文件名用 "[]"列出
    ```

- 窗口分隔

    ```
    <c-w>s  水平分割窗口
    <c-w>v  垂直分割窗口
    <c-w>w  切换至另一窗口
    <c-w>h  切换至左侧窗口
    <c-w>j  切换至下方窗口
    <c-w>k  切换至上方窗口
    <c-w>l  切换至右侧窗口
    <c-w>H  移动当前窗口到左边
    <c-w>J  移动当前窗口到下面
    <c-w>K  移动当前窗口到上面
    <c-w>L  移动当前窗口到右边
    :split filename    水平分隔窗口打开 filename
    :vsplit filename   垂直分割窗口打开 filename
    ```

- 标签式编辑

    ```
    :tabnew filename  在新标签中打开
    gt, :tabnext      切换至下一个标签
    gT, :tabprevious  切换至上一个标签
    :tabc             关闭当前标签
    :tabl             切换至最后一个标签
    :tabmove n        切换到第 n个标签，默认标签编号从 0开始
    ```

- 目录

    netrw 插件

    ```
    netrw 插件是vim的标准插件，在 .vimrc中只要设置了
    set nocp " 不与vi兼容
    filetype plugin on " 允许插件
    就可以使用 netrw插件了
    ```

    打开目录

    ```
    Ex[plore]   打开当前目录或指定目录
    Se[xplore]  水平分割并打开当前目录或指定目录
    Ve[xplore]  垂直分割并打开当前目录或指定目录
    Te[xplore]  新建标签并打开当前目录或指定目录
    ```

    目录操作

    ```
    <cr>   进入目录
    <del>  试图删除文件 /目录
    -      上一级目录
    a      在正常显示，隐藏和显示三种方式间切换
    c      使浏览中的目录成为当前目录
    d      建立目录
    D      试图删除目录
    i      在瘦、长、宽、和树形的各种列表中切换
    <c-l>  刷新目录列表
    o      打开新浏览窗口，进入光标所在目录，使用水平分割
    p      预览文件
    P      在前一次使用的窗口里预览
    r      反转排序顺序
    R      给指定文件 /目录换名
    s      选择排序方式：按名字、时间、文件大小排序
    S      指定按名字排序的后缀优先级
    t      在新标签页里打开光标所在文件 /目录
    v      打开新浏览窗口，进入光标所在目录，使用垂直分割
    ```

## 宏

- 创建宏

    ```
    q + <register> + [一系列命令] + q
    <register> 指用户自定义的 a-z中的一个寄存器
    如：qa...q
    ```

- 运行宏

    ```
    @ + <register>    运行寄存器中的宏
    @@                重复运行上一次宏
    10@a              重复运行寄存器 a中的宏10 次

    ```

## MAP

- 映射模式

    ```
    普通模式
    可视模式
    操作符等待模式
    插入模式
    命令行模式
    ```

- 映射模式代号

    ```
    <space>  普通、可视和选择、操作符等待
    n        普通
    v        可视和选择
    s        选择
    x        可视
    o        操作符等待
    !        插入和命令行
    i        插入
    l        插入、命令行和 Lang-Arg模式的":lmap" 映射
    c        命令行
    ```

- 命令

    ```
    map {lhs} {rhs} 把普通、可视和选择、操作符等待模式下的 lhs命令映射成rhs，如：map tn :tabnew
    noremap      noremap对rhs不会重新扫描映射
    unmap {lhs}  取消对lhs的映射
    mapclear     取消所有 map映射
    nmap         只作用于普通模式下的映射
    imap         只作用于插入模式下的映射
    nnoremap     只作用于普通模式下的 noremap
    nunmap       只作用于普通模式下的 unmap
    nmapclear    只作用于普通模式下的 mapclear
    ```

- 特殊参数

    ```
    <buffer>, <slient>, <special>, <script>, <expr>, <unique>
    <silent> 是指执行键绑定时不在命令行上回显
    <unique> 如果该映射或者缩写已经存在，则该命令会失败
    ```

- mapleader

    ```
    mapleader 变量对所有 map映射命令起效
    它的作用是将参数 <leader>替换成mapleader 变量的值
    ```

- 键表

    ```
    <k0>-<k9>  小键盘0-9
    <s-c>      shift + c
    <c-c>      ctrl + c
    <m-c>      alt + c 或 meta + c
    <a-c>      同<m-c>
    <t_xx>     termcap 里的"xx"入口键
    <cr>       回车
    <space>    空格
    <tab>      tab 键
    <up>       方向键上
    <down>     方向键下
    <left>     方向键左
    <right>    方向键右
    ```

## DIFF

- 基本用法

    VIM 的diff模式是依赖于 diff命令

    ```
    # vimdiff FILE_LEFT FILE_RIGHT
    # vim -d FILE_LEFT FILE_RIGHT
    ```

- 分割窗口启动 diff

    ```
    :diffsplit FILE_TOP             水平分割窗口比较文件
    :vertical diffsplit FILE_RIGHT  垂直分割窗口比较文件
    ```

- 命令

    ```
    ]c  跳转到下一差异点
    [c  跳转到上一差异点
    dp, :diffput  把当前文件内容复制到另一文件
    do, :diffget  把另一文件内容复制到当前文件
    :diffupdate   刷新比较结果
    ```

## 会话

- session 和viminfo

    session中保存了所有窗口的视图和全局设置

    viminfo中保存了命令行历史、搜索字符串历史、输入行历史、非空的寄存器内容、文件的位置标记、最近搜索 /替换的模式、缓冲区列表、全局变量等信息

- session

    ```
    :mksession [filename]  创建一个 session文件，省略文件名会自动创建一个名为 Session.vim文件
    :source [filename]     导入 session文件
    ```

    'sessionoptions'选项记录 session中保存的信息。缺省的'sessionoptions' 选项包括 "blank,buffers,curdir,folds,help,options,tabpages,winsize" ，意为session文件会恢复当前编辑环境的空窗口、所有的缓冲区、当前目录、折叠相关的信息、帮助窗口、所有的选项和映射、所有的标签页、窗口大小。

    如果你不希望在session中保存当前路径，而是希望 session文件所在的目录自动成为当前工作目录，那么，需要在 'sessionoptions' 去掉'curdir' , 加入'sesdir' ，这样每次载入 session文件时，这个文件所在的目录，就被设为 VIM的当前工作目录。


- viminfo

    ```
    :wviminfo [filename]  手动创建一个viminfo文件
    :rviminfo [filename]  导入viminfo 文件
    ```

    在VIM退出时，每次都会保存一个 .viminfo文件在用户的主目录。'viminfo' 选项决定 ':wviminfo'命令保存哪些内容，以及保存的数目

## TAB

- 命令

    ```
    set expandtab      在插入时， <tab>键以一定数量的<space>代替
    set tabstop=4      <tab> 被当做的 <space>的数量
    set shiftwidth=4   每次缩进插入的 <space>的数量
    set smarttab       在行前插入 <tab>根据shiftwidth 空格
    set softtabstop=4  输入tab 时插入<tab>和 <space>的混合
    set list           显示<tab>和行尾字符 $
    set listchars=tab:>-,eol:$  <tab> 显示为>-，行尾显示为 $
    ```

- <tab> 替换为<space>

    ```
    :set expandtab
    :retab! 或 :retab
    ```

加!处理所有的 <tab>，若不加只处理行首的<tab>

- <space> 替换为<tab>

    ```
    :set noexpandtab
    :retab! 或 :retab
    ```

## 编码

- encoding

    ```
    set encoding=utf-8
    set langmenu=zh_CN.UTF-8
    language message zh_CN.UTF-8
    ```

    encoding是 VIM内部使用的字符编码方式， VIM内部所有的buffer 、寄存器、脚本中的字符串都使用这个编码。 Vim 在工作的时候，如果编码方式与它的内部编码不一致，它会先把编码转换成内部编码。如果工作用的编码中含有无法转换为内部编码的字符，在这些字符就会丢失。

- termencoding

    termencoding 是 Vim 用于屏幕显示的编码，在显示的时候， Vim 会把内部编码转换为屏幕编码，再用于输出。内部编码中含有无法转换为屏幕编码的字符时，该字符会变成问号，但不会影响对它的编辑操作。如果 termencoding 没有设置，则直接使用 encoding 不进行转换。

- fileencoding

    当 Vim 从磁盘上读取文件的时候，会对文件的编码进行探测。如果文件的编码方式和 Vim 的内部编码方式不同，Vim 就会对编码进行转换。转换完毕后， Vim 会将 fileencoding 选项设置为文件的编码。当 Vim 存盘的时候，如果 encoding 和 fileencoding 不一样， Vim 就会进行编码转换。

- fileencodings

    编码的自动识别是通过设置 fileencodings 实现的，注意是复数形式。 fileencodings 是一个用逗号分隔的列表，列表中的每一项是一种编码的名称。当我们打开文件的时候， VIM 按顺序使用 fileencodings 中的编码进行尝试解码，如果成功的话，就使用该编码方式进行解码，并将 fileencoding 设置为这个值，如果失败的话，就继续试验下一个编码。

    ```
    set fileencodings=utf-8, gb2312
    ```

    如果编码被误判了，就会产生乱码。如果你知道这个文件的正确编码的话，可以在打开文件的时候使用 ++enc=encoding 的方式来打开文件:e ++enc=utf-8 myfile.txt

- fileformat

    unix格式的换行符为 0A（ascii 码）也就是 <LF>，dos 格式的换行符为 0D 0A(也就是<CR><LF>) ，<CR>其实就显示为 ^M，Mac 把回车<CR>作为换行符，文本中既有unix 的换行符，又有 dos的换行符，那么vim会认为你打开的是 unix的，所以，那些dos的换行符就会出现 ^M，办法是：

1. 若你的 vim版本大于7.1 ，并想用 dos显示和保存，如下语句：

    ```
    :e ++ff=dos
    ```

2. 若你的 vim版本小于等于7.1，又想把文章按照 dos格式显示和保存，如下语句：

    ```
    :set ff=dos
    :%s/\r\+$//e

    ```
3. 若你的 vim版本小于等于7.1，又想把文章按照 unix格式显示和保存，如下语句：

    ```
    :set ff=unix
    :%s/\r\+$//e
    ```

## VIMRC

```vim
"""""""""""""""""""""""""""""""""""""""""
"      windows版本gvim
"   最后一次修改： 2013/1/23
"""""""""""""""""""""""""""""""""""""""""

set nocompatible
source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin


"""""""""""""""""""""""""""""""""""""""""
"      基本设置
"""""""""""""""""""""""""""""""""""""""""
set number           "显示行号
set nobackup         "不备份
colorscheme delek    "配色方案
set tabstop=4        "TAB设置
set softtabstop=4
set shiftwidth=4
set foldmethod=marker    "折叠设置
"set foldmethod=syntax
"set foldmethod=indent
set foldlevel=100
set foldclose=all    "关闭所有折叠
set autoindent           "缩进设置
set smartindent
set cindent
set fileformats=dos,unix "设置文件格式


"""""""""""""""""""""""""""""""""""""""""
"      编码和字体
"""""""""""""""""""""""""""""""""""""""""
set fileencodings=gb2312,utf-8
set termencoding=gb2312
set fileencoding=gb2312

set guifont=Consolas:h11:cANSI


"""""""""""""""""""""""""""""""""""""""""
"      常用映射
"""""""""""""""""""""""""""""""""""""""""
let mapleader=","

"标签
nnoremap L :tabnext<cr>
nnoremap H :tabprevious<cr>
nnoremap tn :tabnew
"窗口分隔
nnoremap <c-h> <c-w>h
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-l> <c-w>l
"注释
nnoremap <leader>/ I/*<space><esc>A<space>*/<esc>j
nnoremap <leader>; ^xxx$xxxj
inoremap <leader>/ /*<space><space>*/<left><left><left>
"替换
nnoremap <leader>r :%s/\<\>//gc<left><left><left><left><left><left>
nnoremap <c-f> /\<\><left><left>
"折叠
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<cr>
nmap <leader>cs O#if 0 /*  comment by hl at <c-r>=strftime("%y/%m/%d %H:%M")<cr>  {{{  */<esc>
nmap <leader>ce o#endif /*  comment by hl at <c-r>=strftime("%y/%m/%d %H:%M")<cr>  }}}  */<esc>
"插入模式下方向键
imap <a-j> <down>
imap <a-k> <up>
imap <a-h> <right>
imap <a-l> <left>


"""""""""""""""""""""""""""""""""""""""""
"      ctags 插件
"""""""""""""""""""""""""""""""""""""""""
set tags=tags;
set autochdir
nmap <c-[> <c-t>


"""""""""""""""""""""""""""""""""""""""""
"      taglist 插件
"""""""""""""""""""""""""""""""""""""""""
let Tlist_Ctags_Cmd = 'ctags.exe'
let Tlist_Show_One_File = 1        "同时显示多个文件函数列表
let Tlist_show_Exit_OnlyWindow = 1 "当taglist 是最后一个窗口时，自动退出 vim
let Tlist_Use_Right_Window = 0     "让窗口显示在左边
let Tlist_Process_File_Always = 0  "不要一直处理tags
let Tlist_Auto_Close = 1           " 非当前文件，函数列表折叠隐藏


"""""""""""""""""""""""""""""""""""""""""
"      DoxygenToolkit 插件
"""""""""""""""""""""""""""""""""""""""""
let g:DoxygenToolkit_authorName = "hl - ssdlut"
let g:DoxygenToolkit_briefTag_funcName = "yes"
let g:DoxygenToolkit_emailString = "596150637@qq.com"
let g:DoxygenToolkit_versionString = "1.0"

"let g:DoxygenToolkit_briefTag_pre = "@brief "
"let g:DoxygenToolkit_templateParamTag_pre = "@tparam "
"let g:DoxygenToolkit_paramTag_pre = "@param "
"let g:DoxygenToolkit_returnTag = "@return "
"let g:DoxygenToolkit_throwTag_pre = "@throw "
"let g:DoxygenToolkit_fileTag = "@file "
"let g:DoxygenToolkit_authorTag = "@author "
"let g:DoxygenToolkit_emailTag = "@e-mail "
"let g:DoxygenToolkit_dateTag = "@date "
"let g:DoxygenToolkit_versionTag = "@version "
"let g:DoxygenToolkit_blockTag = "@name "
"let g:DoxygenToolkit_classTag = "@class "
"let g:DoxygenToolkit_commentType = "C"

nnoremap <leader>da :DoxAuthor<cr>
nnoremap <leader>df :Dox<cr>
nnoremap <leader>db :DoxBlock<cr>


"""""""""""""""""""""""""""""""""""""""""
"      omnicppcomplete 插件
"
"       <c-x> 进入补全模式
"       <c-d> 宏定义
"       <c-f> 文件名
"       <c-k> 字典
"       <c-i> 当前文件以及由#include包含进来的文件
"       <c-l> 整个行
"       <c-]> 标记(tags)
"       <c-p> 向前查找, 与没有<c-x>命令时相同
"       <c-n> 向后查找, 与没有<c-x>命令时相同
"       <c-o> 万能补全
"       <c-f> 文件名补全
"       <c-v> VIM命令补全
"       <c-u> 用户定义补全
"""""""""""""""""""""""""""""""""""""""""
imap <leader>s <c-x><c-n>
imap <leader>d <c-x><c-p>
imap <leader>f <c-x><c-o>


"""""""""""""""""""""""""""""""""""""""""
"      功能键映射
"""""""""""""""""""""""""""""""""""""""""
"nmap <F2> :tabnew %:h<cr>
"在新标签中打开当前目录
nmap <F2> :Texplore<cr>
"生成 tags文件
nmap <F3> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<cr>
"打开 taglist，不支持中文路径
nmap <F4> :TlistToggle<cr>
"make需要自己编写 Makefile
nmap <F6> :!nmake<cr>
nmap <F8> :!nmake clean<cr>
nmap <F7> :!nmake run<cr>


"""""""""""""""""""""""""""""""""""""""""
"      对齐
"""""""""""""""""""""""""""""""""""""""""
nnoremap <leader>ch :call SetColorColumn()<cr>
function! SetColorColumn()
    let col_num = virtcol(".")
    let cc_list = split(&cc, ',')
    if count(cc_list, string(col_num)) <= 0
       execute "set cc+=".col_num
    else
       execute "set cc-=".col_num
    endif
endfunction
```


```vim
"""""""""""""""""""""""""""""""""""""""""
"      Linux版本gvim
"   最后一次修改： 2014/3/31
"""""""""""""""""""""""""""""""""""""""""

set nocompatible
filetype on


"""""""""""""""""""""""""""""""""""""""""
"       基本设置
"""""""""""""""""""""""""""""""""""""""""
set number               " 显示行号
set nobackup             " 不备份
colorscheme delek        "配色方案
set tabstop=4            "TAB 设置
set softtabstop=4
set shiftwidth=4
set foldmethod=marker    "折叠设置
"set foldmethod=syntax
"set foldmethod=indent
set foldlevel=100
set foldclose=all        "关闭所有折叠
set autoindent           "缩进设置
set smartindent
set cindent
set fileformats=unix    "设置文件格式


"""""""""""""""""""""""""""""""""""""""""
"       编码和字体设置
"""""""""""""""""""""""""""""""""""""""""
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,gbk

set guifont=Monospace\ Bold\ 10
"set guifont=Consolas\ Regular\ 12


"""""""""""""""""""""""""""""""""""""""""
"       常用映射
"""""""""""""""""""""""""""""""""""""""""
let mapleader=","

"标签
nnoremap L :tabnext<cr>
nnoremap H :tabprevious<cr>
nnoremap tn :tabnew
nnoremap ts :tab split<cr>
"窗口分隔
nnoremap <c-h> <c-w>h
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-l> <c-w>l
"注释
nnoremap <leader>/ I/*<space><esc>A<space>*/<esc>j
nnoremap <leader>; ^xxx$xxxj
inoremap <leader>/ /*<space><space>*/<left><left><left>
"替换
nnoremap <leader>r :%s/\<\>//gc<left><left><left><left><left><left>
nnoremap <c-f> /\<\><left><left>
"折叠
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<cr>
nmap <leader>cs O#if 0 /*  comment by hl at <c-r>=strftime("%y/%m/%d %H:%M")<cr>  {{{  */<esc>
nmap <leader>ce o#endif /*  comment by hl at <c-r>=strftime("%y/%m/%d %H:%M")<cr>  }}}  */<esc>
"插入模式下方向键
imap <a-j> <down>
imap <a-k> <up>
imap <a-h> <right>
imap <a-l> <left>
"make
nnoremap cp :cp<cr>
nnoremap cn :cn<cr>


"""""""""""""""""""""""""""""""""""""""""
"       ctags 插件
"""""""""""""""""""""""""""""""""""""""""
set tags=tags;
set autochdir
"nmap <c-[> <c-t>


"""""""""""""""""""""""""""""""""""""""""
"       taglist 插件
"""""""""""""""""""""""""""""""""""""""""
"let Tlist_Ctags_Cmd = 'ctags.exe'
let Tlist_Show_One_File = 1            " 同时显示多个文件函数列表
let Tlist_Exit_OnlyWindow = 1      "当taglist 是最后一个窗口时，自动退出 vim
let Tlist_Use_Right_Window = 0         "让窗口显示在左边
let Tlist_Process_File_Always = 0      "不要一直处理tags
let Tlist_Auto_Close = 0               " 非当前文件，函数列表折叠隐藏


"""""""""""""""""""""""""""""""""""""""""
"       DoxygenToolkit 插件
"""""""""""""""""""""""""""""""""""""""""
let g:DoxygenToolkit_authorName = "hl - ssdlut"
let g:DoxygenToolkit_briefTag_funcName = "no"
let g:DoxygenToolkit_emailString = "596150637@qq.com"
let g:DoxygenToolkit_versionString = "1.0"

"let g:DoxygenToolkit_briefTag_pre = "@brief "
"let g:DoxygenToolkit_templateParamTag_pre = "@tparam "
"let g:DoxygenToolkit_paramTag_pre = "@param "
"let g:DoxygenToolkit_returnTag = "@return "
"let g:DoxygenToolkit_throwTag_pre = "@throw "
"let g:DoxygenToolkit_fileTag = "@file "
"let g:DoxygenToolkit_authorTag = "@author "
"let g:DoxygenToolkit_emailTag = "@e-mail "
"let g:DoxygenToolkit_dateTag = "@date "
"let g:DoxygenToolkit_versionTag = "@version "
"let g:DoxygenToolkit_blockTag = "@name "
"let g:DoxygenToolkit_classTag = "@class "
"let g:DoxygenToolkit_commentType = "C"

nnoremap <leader>da :DoxAuthor<cr>
nnoremap <leader>df :Dox<cr>
nnoremap <leader>db :DoxBlock<cr>


"""""""""""""""""""""""""""""""""""""""""
"       omnicppcomplete 插件
"
"       <c-x> 进入补全模式
"       <c-d> 宏定义
"       <c-f> 文件名
"       <c-k> 字典
"       <c-i> 当前文件以及由#include包含进来的文件
"       <c-l> 整个行
"       <c-]> 标记(tags)
"       <c-p> 向前查找, 与没有<c-x>命令时相同
"       <c-n> 向后查找, 与没有<c-x>命令时相同
"       <c-o> 万能补全
"       <c-f> 文件名补全
"       <c-v> VIM命令补全
"       <c-u> 用户定义补全
"""""""""""""""""""""""""""""""""""""""""
imap <leader>s <c-x><c-n>
imap <leader>d <c-x><c-p>
imap <leader>f <c-x><c-o>

filetype plugin on
set completeopt=menu,menuone
let g:OmniCpp_SelectFirstItem = 0      "是否自动选择第一个匹配项
let g:OmniCpp_ShowAccess = 1           " 显示访问控制信息
let g:OmniCpp_GlobalScopeSearch = 1    "全局查找控制。0:禁止； 1:允许( 缺省)
let g:OmniCpp_NamespaceSearch = 1      " 0 ,  1 or 2
let g:OmniCpp_DisplayMode = 1
let g:OmniCpp_ShowScopeInAbbr = 0
let g:OmniCpp_ShowPrototypeInAbbr = 1
let g:OmniCpp_MayCompleteDot = 1
let g:OmniCpp_MayCompleteArrow = 1
let g:OmniCpp_MayCompleteScope = 1


"""""""""""""""""""""""""""""""""""""""""
"       功能键映射
"""""""""""""""""""""""""""""""""""""""""
"nmap <F2> :tabnew %:h<cr>
"在新标签中打开当前目录
nmap <F2> :Texplore<cr>
"生成 tags文件
nmap <F3> :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .<cr>
"nmap <F3> :!ctags -R --fields=+lS .<cr>
"打开 taglist，不支持中文路径
nmap <F4> :TlistToggle<cr>
"make需要自己编写 Makefile
nmap <F6> :!make<cr>
nmap <F7> :!make run<cr>
nmap <F8> :!make clean<cr>


"""""""""""""""""""""""""""""""""""""""""
"       对齐
"""""""""""""""""""""""""""""""""""""""""
nnoremap <leader>ch :call SetColorColumn()<cr>
function! SetColorColumn()
    let col_num = virtcol(".")
    let cc_list = split(&cc, ',')
    if count(cc_list, string(col_num)) <= 0
        execute "set cc+=".col_num
    else
        execute "set cc-=".col_num
    endif
endfunction
```
