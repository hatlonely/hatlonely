# Objective-C基础教程

Soctt Knaster & Waqar Malik & Mark Dalrymple 著 周庆成 译

## 对C的拓展

- 编程环境Mac OS X下的Xcode
- Hello Objective-C

    ```objectivec
    #import <Foundation/Foundation.h>
    int main(int argc, char *argv[]) {
        NSLog(@"Hello Objective-C!");
        return 0;
    }
    ```
- BOOL类型YES, NO

## 面向对象基础

- **类**（class）是一种表示对象类型的结构体
- **对象**（object）是一种包含值和指向其类的隐藏指针的结构
- **实例**（instance）对象的另一种称呼
- **消息**（message）是对象可以执行的操作，[shape draw]shap发送draw消息
- **方法**（method）是为了响应消息而运行的代码
- **方法调度**（method dispatcher）Objective-C的一种机制，用来推测执行什么方法以响应某个特定的消息
- **接口**（interface）是类为对象提供的特征描述
- **实现**（implementation）是使接口能正常工作的代码

```objectivec
@interface Circle: NSObject {
@private
    ShapeColor fillColor;
    ShapeRect bounds;
}
- (void) setFillColor: (ShapeColor) fillColor;
- (void) setBounds: (ShapeRect) bounds;
- (void) draw;
@end // Circle

@implementation Circle
- (void) setFillColor: (ShapeColor) fc {
    fillColor = fc;
}
- (void) setBounds: (ShapeRect) b {
    bounds = b;
}
- (void) draw {
    NSLog(@"drawing a circle at (%d, %d, %d, %d) in %@",
        bounds.x, bounds.y, bounds.width, bounds.height,
        colorName(fillColor));
}
@end Circle

int main(int argc, char *argv[]) {
    id shape;
    ShapeRect rect = {0, 0, 10, 30};
    shape = [Circle new];
    [shape setBounds: rect];
    [shape setFillColor: kRedColor];
    [shape draw];

    return 0;
}
```

## 继承

- **超类**（super class）是继承的类，Circle类的超类是Shape
- **父类**（parent class）超类的另一种表达
- **子类**（subclass）是执行继承的类，Circle类是Shape的子类
- **孩子类**（child class）子类的另一种表达
- 如果想改变方法的实现需要**重写**（override）继承的方法，draw
- **super**关键字调用超类的实现，[super setFillColor]

```objectivec
@interface Shape: NSObject {
    ShapeColor fillColor;
    ShapeRect bounds;
}
- (void) setFillColor: (ShapeColor) fillColor;
- (void) setBounds: (ShapeRect) bounds;
- (void) draw;
@end // Shape

@implementation Shape
- (void) setFillColor: (ShapeColor) fc {
    fillColor = fc;
}
- (void) setBounds: (ShapeRect) b {
    bounds = b;
}
- (void) draw {
    // nothing to do
}
@end // Shape

@interface Circle: Shape
@end // Circle

@implementation Circle
- (void) draw {
    NSLog(@"drawing a circle at (%d, %d, %d, %d) in %@",
        bounds.x, bounds.y, bounds.width, bounds.height,
        colorName(fillColor));
}
@end // Circle

@interface Rectangle: Shape
@end // Rectangle

@implementation Rectangle
- (void) draw {
    NSLog(@"drawing a rectangle at (%d, %d, %d, %d) in %@",
        bounds.x, bounds.y, bounds.width, bounds.height,
        colorName(fillColor));
}
@end // Rectangle
```

## 组合

- 继承的类之间的关系是“是一个”，圆是一个形状
- 组合和类之间的关系是“有一个”，车有一个引擎

```objectivec
@interface Tire: NSObject
@end // Tire

@implementation Tire
- (NSString *) description {
    return @"I am a tire. I last a while";
}
@end // Tire

@interface Engine: NSObject
@end // Engine

@implementation Engine
- (NSString *) description {
    return @"I am an engine. Vrooom!";
}
@end // Engine

@interface Car: NSObject {
    Engine *engine;
    Tire *tires[4];
}
- (void) print;
@end // Car

@implementation Car
- (id) init {
    if (self = [super init]) {
        engine = [Engine new];
        for (int i = 0; i < 4; i++) {
            tires[i] = [Tire new];
        }
    }
    return self;
}
- (void) print {
    NSLog(@"%@", engine);
    for (int i = 0; i < 4; i++) {
        NSLog(@"%@", tires[i]);
    }
}
@end // Car

int main(int argc, char *argv[]) {
    Car *car;
    car = [Car new];
    [car print];

    return 0;
}
```

## 源文件组织

- 头文件.h中存放类的@interface指令，公共struct定义，enum常量，#defines和extern全局变量等
- 所有实现内容存放在与类同名但以.m为后缀的文件中，.mm文件为Objective-C++文件
- @class关键字告诉编译器，这是一个类
- @interface，@implementation，#import

## Foundation Kit介绍

Foundation是两类UI框架（UIKit和AppKit）的基础，用#import <Foundation/Foundation.h>导入

- 范围NSRange

    ```objectivec
    typedef struct _NSRange {
        unsigned int location;
        unsigned int length;
    } NSRange;

    NSRange range = NSMakeRange(17, 4);
    ```

- 几何数据

    CG前缀是Core Graphics框架提供，用来进行2D渲染的

    ```objectivec
    struct CGPoint {
        float x;
        float y;
    };
    struct CGSize {
        float width;
        float height;
    };
    struct CGRect {
        CGPoint origin;
        CGSize size;
    }
    ```

- 字符串

    ```objectivec
    // 不可变字符串 NSString
    + (id) stringWithFormat: (NSString *) format, ...;
    - (NSUInteger) length;
    - (BOOL) isEqualToString: (NSString *) aString;
    - (NSComparisonResult) compare: (NSString *) aString
        option: (NSStringCompareOptions) mask;
        // mark选项如下：
        //  NSCaseInsensitiveSearch: 不区分大小写
        //  NSLiteralSearch: 区分大小写
        //  NSNumericSearch: 比较字符串个数，"100"大于"99"

    enum {
        NSOrderedAscending = -1,
        NSOrderedSame,
        NSOrderedDescending
    };
    typedef NSInteger NSComparisonResult;

    - (BOOL) hasPrefix: (NSString *) aString;
    - (BOOL) hasSuffix: (NSString *) aString;
    - (NSRange) rangeOfString: (NSString *) aString;

    // 可变字符串 NSMutableString
    - (void) appendString: (NSString *) aString;
    - (void) appendFormat: (NSString *) format, ...;
    - (void) deleteCharactersInRange: (NSRange) aRange;
    ```

- 集合

    ```objectivec
    // 不可变数组 NSArray
    NSArray *array = [NSArray arrayWithObject: @"one", @"two", @"three", nil];
    NSArray *array = @[@"one", @"two", @"three"];

    - (NSUInteger) count;
    - (id) objectAtIndex: (NSUInteger) index;

    NSString *string = @"oop:ack:bork:greeble:ponies";
    NSArray *chunks = [string componentsSeparateByString: @":"];

    // 可变数组 NSMutableArray
    + (id) arrayWithCapacity: (NSUInteger) numItems;
    - (void) addObject: (id) anObject;
    - (void) removeObjectAtIndex: (NSUInteger) index;
    ```

- 枚举

    ```objectivec
    - (id) nextObject;

    // 遍历数组
    NSEnumerator *enumerator = [array objectEnumerator];
    while (id thingie = [enumerator nextObject]) {
        NSLog(@"I found %@", thingie);
    }

    // 从后往前遍历数组
    NSEnumerator *enumerator = [array reverseObjectEnumerator];

    // 快速枚举
    for (NSString *string in array) {
        NSLog(@"I found %@", string);
    }

    // 代码块枚举，可以让循环并发进行
    NSArray: - (void) enumerateObjectsUsingBlock: (void (^)(id obj, NSUInteger idx, BOOL *stop)) block;

    [array enumerateObjectUsingBlock: ^(NSString *string, NSUInteger index, BOOL *stop) {
        NSLog(@"I found %@", string);
    }]
    ```

- 字典

    ```objectivec
    // 不可变字典 NSDictionary
    + (id) dictionaryWithObjectsAndKeys: (id) firstObject, ...;

    Tire *t[4];
    NSDictionary *tires = [NSDictionary dictionaryWithObjectsAndKeys:
        t[0], @"front-left", t[1], @"front-right"
        t[2], @"back-left", t[3], @"back-right", nil];
    NSDictionary *tires = @{@"front-left": t[0],
        @"front-right": t[1], @"back-left": t[2], @"back-right": t[3]};

    Tire tire = [tires objectForKey: @"back-left"];
    Tire tire = tires[@"back-left"];

    // 可变字典 NSMutableDictionary
    NSMutableDictionary *tires = [NSMutableDictionary dictionary];
    [tires setObject: t[0], forKey: @"front-left"];
    [tires setObject: t[1], forKey: @"front-right"];
    [tires setObject: t[2], forKey: @"back-left"];
    [tires setObject: t[3], forKey: @"back-right"];
    [tires removeObjectForKey: @"back-right"];
    ```

- 数值

    ```objectivec
    // NSNumber

    + (NSNumber *) numberWithChar: (char) value;
    + (NSNumber *) numberWithInt: (int) value;
    + (NSNumber *) numberWithFloat: (float) value;
    + (NSNumber *) numberWithBool: (BOOL) value;

    number = @'x';      // 字符
    number = @12345     // 整型
    number = @12345ul   // 无符号长整型
    number = @12345ll   // long long
    number = @123.45f   // 单精度浮点
    number = @123.45    // 双精度浮点
    number = @YES       // BOOL

    - (char) charValue
    - (int) intValue
    - (float) floatValue
    - (BOOL) boolValue
    - (NSString *) stringValue
    ```

- NSValue

    ```objectivec
    NSRect rect = NSMakeRect(1, 2, 30, 40);
    NSValue *value = [NSValue valueWithBytes: &rect objCType: @encode(NSRect)];
    [value getValue: &rect];
    ```

- NSArray中不能放nil值，可以放NSNull

## 内存管理

1. 对象生命周期

    - 引用计数

        ```objectivec
        - (id) retain;                  // 引用计数器+1
        - (void) release;               // 引用计数器-1
        - (NSUInteger) retainCount;     // 获得引用计数器
        ```

    - 对象的所有者负责清理对象
    - 自动释放池

        ```objectivec
        // 自动释放池 autorelease
        - (NSString *) description {
            NSString *desc;
            desc = [[NSString alloc] initWithFormat: @"I am %d years old.", 4];
            return [desc autorelease];
        }

        // NSAutoreleasePool创建自动释放池
        NSAutoreleasePool *pool;
        pool = [NSAutoreleasePool new];
        // ...  这里所有的变量都会放如pool中
        [pool release];
        ```

2. Coco的内存管理规则

    - 当使用new/alloc/copy方法创建一个对象时，该对象保留引用计数器的值1
    - 通过其他方法获得对象时，假设该对象的应用计数器的值是1，而且已经被设置为自动释放了
    - 如果retain了某个对象，就需要retain或者autorelease对象，而且retain和release的使用次数应该相等
    - 自动引用计数ARC
    - 弱应用weak

3. 异常

    ```objectivec
    @try {
        // code you want to execute that might throw an exception.
    } @catch (NSException *exception) {
        // code to execute that handles exception.
    } @finally {
        // code that will always be executed. Typically for cleanup.
    }
    ```

## 对象初始化

alloc为对象分配内存，init为对象初始化

## 使用属性值

```objectivec
@interface AllWeatherRadial: Tire {
    float rainHandling;
    float snowHandling;
}
@property float rainHandling;
@property float snowHandling;
@end // AllWeatherRadial

@implementation AllWeatherRadial
@synthesize rainHandling;
@synthesize snowHandling;
@end // AllWeatherRadial

[tire setRainHandling: 20];
[tire setSnowHandling: 28];
tire.rainHandling = 20;
tire.snowHandling = 28;

// @property (copy | retain | assign | nonatomic | readwrite | readonly) type prop
@property (readwrite, copy) NSString *name;
@property (readonly) NSString *licenseNumber;

// 属性没有对应的变量，由计算的出，如身体质量指数由身高和体重得出
@property (readyonly) float bodyMassIndex;
@dynamic bodyMassIndex;
- (float) bodyMassIndex {
    // compute and return bodyMassIndex
}
```

## 类别

利用Objective-C的动态运行时分配机制，为现有的类添加新的方法，这些方法被称为**类别**，程序员习惯把类别文件代码放在单独的文件中，文件名为类名称+类别名称。

```objectivec
@interface NSString (NumberConvenience)
- (NSNumber *) lengthAsNumber;
@end // NumberConvenience

@implementation NSString (NumberConvenience)
- (NSNumber *) lengthAsNumber {
    NSUinteger length = [self length];
    return [NSNumber numberWithUnsignedInt: length];
}
@end // NumberConvenience
```

## 协议

正式的协议就像Java的接口一样

```objectivec
@protocol NSCopying     // 协议声明
- (id) copyWithZone: (NSZone *) zone;
@end // NSCopying

@protocol MySuperDuberProtocol <MyParentProtocol>   // 协议继承
@end // MySuperDuberProtocol

@interface Car: NSObject <NSCopying, NSCoding> {   // 采用NSCopying协议
    // instance variables
}
// methods
@end // Car

@implementation Car
// methods
@end

// 参数object必须实现了NSCopying协议
- (void) setObjectValue: (id <NSCopying>) object;
```

## 代码块和并发性

### 代码块

```objectivec
void (*func)(void);     // 函数声明
void (^block)(void);    // 代码块声明

// <returntype> (^blockname)(arguments) = ^(arguments){ body; };

// 使用代码块
int (^square_block)(int number) = ^(int number) {
    return (number * number);
};
int result = square_block(5);

// 直接使用代码块
NSArray *sortedArray = [array sortedArrayUsingComparator:
    ^(NSString *object1, NSString *object2) {
    return [object1 compare: object2];
}];

// 代码块和函数类似，但是可以使用同一范围内声明的变量，并且作为常量使用
```

### 并发

```objectivec
// 同步
@synchronized(object) {
    // critical section
}

// 后台执行
- (void) myBackgroundMethod: (id) myObject {
    @autorelease {
        NSLog(@"My Background Method");
    }
}
[self performSelectorInBackground: @selector(myBackgroundMethod)
    withObject: argumentObject];
```

## 文件加载与保存

**属性列表**（property list）对象。这些属性列表类是NSArray、NSDictionary、NSString、NSNumber、NSDate、NSData，以及他们的可修改形态（前缀为Mutable的类）

```objectivec
// NSDate
NSDate *yesterday = [NSDate dateWithTimeIntervalSinceNow: - (24 * 60 * 60)];

// NSData
const char *string = "Hi there, this is a C string!";
NSData *data = [NSData dataWithBytes: string length: strlen(string) + 1];
NSLog(@"%d byte string is '%s'", [data length], [data bytes]);

// 写入和读取属性列表
NSArray *phrase = [NSArray arrayWithObject: @"I", @"seem", @"to", @"be", @"a", @"verb", nil];
[phrase writeToFile: @"/tmp/verbiage.xml" atomically: YES];
NSArray *phrase2 = [NSArray arrayWithContentsOffline: @"/tmp/verbiage.xml"];
NSLog(@"%@", phrase2);
```

编码与解码，也叫序列化与反序列化

```objectivec
@protocol NSCoding
- (void) encodeWithCoder: (NSCoder *) encoder;
- (id) initWithCoder: (NSCoder *) decoder;
@end // NSCoding

@interface Thingie: NSObject <NSCoding> {
    NSString *name;
    int magicNumber;
    float shoeSize;
    NSMutableArray *subThingies;
}
@property (copy) NSString *name;
@property int magicNumber;
@property float shoeSize;
@property (retain) NSMutableArray *subThingies;
- (id) initWithName: (NSString *) n magicNumber: (int) mn shoeSize: (float) ss;
@end // Thingie

@implementation Thingle
@synthesize name;
@synthesize magicNumber;
@synthesize shoeSize;
@synthesize subThingies;
- (id) initWithName: (NSString *) n magicNumber: (int) mn shoeSize: (float) ss {
    if (self = [super init]) {
        self.name = n;
        self.magicNumber = mn;
        self.shoeSize = ss;
        self.subThingies = [NSMutableArray array];
    }
    return self;
}
- (void) delloc {
    [name release];
    [subThingies release];
    [super dealloc];
}
- (void) encodeWithCoder: (NSCoder *) encoder {
    [encoder encodeObject: name forKey: @"name"];
    [encoder encodeInt: magicNumber forKey: @"magicNumber"];
    [encoder encodeFloat: shoeSize forKey: @"shoeSize"];
    [encoder encodeObject: subThingies forKey: @"subThingies"];
}
- (void) initWithCoder: (NSCoder *) decoder {
    if (self = [super init]) {
        self.name = [decoder decodeObjectForKey: @"name"];
        self.magicNumber = [decoder decodeIntForKey: @"magicNumber"];
        self.shoeSize = [decode decodeFloatForKey: @"shoeSize"];
        self.subThingies = [decode decodeObjectForKey: @"subThingies"];
    }
}
- (NSString *) description {
    NSString *description = [NSString stringWithFormat: @"%@: %d/%.1f %@",
        name, magicNumber, shoeSize, subThingies];
    return description;
}
@end // Thingle

Thingie *thing = [[Thingie alloc] initWithName: @"thing"
        magicNumber: 42 shoeSize: 10.5];
NSData *freezeDried = [NSKeyedArchiver archivedDataWithRootObject: thing];  // 编码
Thingie *thing2 = [NSKeyedUnarchiver unarchiveObjectWithData: freezeDired]; // 解码
```

## 键值编码

```objectivec
[car valueForKey: @"name"];     // car.name
[car valueForKeyPath: @"engine.horsepower"]  // car.engine.horsepower
[car valueForKeyPath: @"tires.pressure"];    // car.tires.pressure
[garage valueForKeyPath: @"cars.@count"];    // count(garage.cars)
[garage valueForKeyPath: @"cars.@sum.mileage"]  // sum(garage.cars.mileage)
[garage valueForKeyPath: @"cars.@avg.mileage"]  // avg(garage.cars.mileage)
[garage valueForKeyPath: @"cars.@min.mileage"]  // min(garage.cars.mileage)
[garage valueForKeyPath: @"cars.@max.mileage"]  // max(garage.cars.mileage)
// distinctUnionOfObjects(garage.cars.make)
[garage valueForKeyPath: @"cars.@distinctUnionOfObjects.make"]
```

## NSPredicate

```objectivec
NSPredicate *predicate = [NSPredicate predicateWithFormat: @"%K == %@", @"name", @"Herbie"];
results = [cars filteredArrayUsingPredicate: predicate];

NSPredicate *predicateTemplate = [NSPredicate predicateWithFormat: @"name == $NAME"];
NSDictionary *varDict = [NSDictionary dictionaryWithObjectAndKeys: @"Herbie", @"NAME", nil];
predicate = [predicateTemplate predicateWithSubstitutionVariables: varDict];

// AND, OR, NOT, &&, ||, !
// SELF IN %@
// BEGINWITH, ENDWITH, CONTAINS, LIKE
NSPredicate *predicate =
    [NSPredicate predicateWithFormat: @"name LIKE '???er*'", @"name", @"Herbie"];
NSPredicate *predicate =
    [NSPredicate predicateWithFormat: @"name BEGINSWITH 'abc'", @"name", @"Herbie"];
NSPredicate *predicate =
    [NSPredicate predicateWithFormat: @"name ENDSWITH 'xyz'", @"name", @"Herbie"];
NSPredicate *predicate =
    [NSPredicate predicateWithFormat: @"name CONTAINS 'mn'", @"name", @"Herbie"];
```
