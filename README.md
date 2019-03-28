It's an asymmetric coroutine library (like lua).

You can use coroutine_open to open a schedule first, and then create coroutine in that schedule. 

You should call coroutine_resume in the thread that you call coroutine_open, and you can't call it in a coroutine in the same schedule.

Coroutines in the same schedule share the stack , so you can create many coroutines without worry about memory.

But switching context will copy the stack the coroutine used.

Read source for detail.

------------------------------------------------------------------------------------------

云风实现的协程简单明了,非常适合入门协程. 云风的实现主要基于ucontext组件，避免自己实现堆栈切换。

笔者在这里fork了云风的coroutine库,根据自己的理解为代码添加了注释,方便自己理解协程的工作原理.

thread/UContext.{h|c|S} 是一种用户态线程（协程）的简单实现，线程（协程）的切换需要用户手工完成。  
