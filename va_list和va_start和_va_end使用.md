- [在C中, 无法列出传递函数的所有实参的类型和数目时, 可以用省略号指定参数表](#sec-1)
- [函数参数的传递原理](#sec-2)
- [例子](#sec-3)

# 在C中, 无法列出传递函数的所有实参的类型和数目时, 可以用省略号指定参数表<a id="sec-1"></a>

```C
void foo(...);
void foo(para_lits, ...);
```

# 函数参数的传递原理<a id="sec-2"></a>

函数参数是以数据结构:栈的形式存取, 从右至左入栈.

首先是参数的内存存放格式：参数存放在内存的堆栈段中, 在执行函数的时候, 从最后一个开始入栈.因此栈底高地址, 栈顶低地址, 举个例子如下： void func(int x, float y, char z); 那么, 调用函数的时候, 实参 char z 先进栈, 然后是 float y, 最后是 int x, 因此在内存中变量的存放次序是 x->y->z, 因此, 从理论上说, 我们只要探测到任意一个变量的地址, 并且知道其他变量的类型, 通过指针移位运算, 则总可以顺藤摸瓜找到其他的输入变量. 下面是 <stdarg.h> 里面重要的几个宏定义如下： typedef char\* va\_list; void va\_start ( va\_list ap, prev\_param ); *\* ANSI version \** type va\_arg ( va\_list ap, type ); void va\_end ( va\_list ap ); va\_list 是一个字符指针, 可以理解为指向当前参数的一个指针, 取参必须通过这个指针进行.

1.  在调用参数表之前, 定义一个 va\_list 类型的变量, (假设va\_list 类型变量被定义为ap)；
2.  然后应该对ap 进行初始化, 让它指向可变参数表里面的第一个参数, 这是通过 va\_start 来实现的, 第一个参数是 ap 本身, 第二个参数是在变参表前面紧挨着的一个变量,即“&#x2026;”之前的那个参数；
3.  然后是获取参数, 调用va\_arg, 它的第一个参数是ap, 第二个参数是要获取的参数的指定类型, 然后返回这个指定类型的值, 并且把 ap 的位置指向变参表的下一个变量位置；
4.  获取所有的参数之后, 我们有必要将这个 ap 指针关掉, 以免发生危险, 方法是调用 va\_end, 他是输入的参数 ap 置为 NULL, 应该养成获取完参数表之后关闭指针的习惯.说白了, 就是让我们的程序具有健壮性.通常va\_start和va\_end是成对出现.

# 例子<a id="sec-3"></a>

```C
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

int demo(char *msg, ...)
{
    va_list argp;        /* 定义保存函数参数的结构 */
    int argno = 0;
    char *parameter;       
    va_start(argp, msg); /* argp指向传入的第一个可选参数, msg是最后一个确定的参数 */

    while(1)
    {
        parameter = va_arg(argp, char*);
        if (strcmp(parameter, "") == 0)
        {
            break;
        }
        printf("Parameter #%d is: %s\n", argno, parameter);
        argno++;
    }
    va_end(argp);

    return 0;
}

int main(void)
{
    demo("DEMO", "This", "is", "a", "demo!", "");

    return 0;
}
```

    - Parameter #0 is: This
    - Parameter #1 is: is
    - Parameter #2 is: a
    - Parameter #3 is: demo!
