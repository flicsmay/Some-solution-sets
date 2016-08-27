###内部定义
在一个定义函数体内内嵌的其他的定义叫做内部定义，如下：

	(define (f x)
	  (define (even? n)
	    (if (= n 0)
	        true
	        (odd? (- n 1))))
	  (define (odd? n)
	    (if (= n 0)
	        false
	        (even? (- n 1))))
	  <rest of body of f>)

可以看到在这里两个内部的定义互相调用会发生一些问题，因为我们是期望他们是同时定义的。

	(lambda <vars>
	  (define u <e1>)
	  (define v <e2>)
	  <e3>)

在这里，书上的做法是将内部定义（如上）转化为先预定义后实定义（如下，有一种C语言的感觉了），这里的 *\*unassigned\** 单纯的只是个字符串而已。 人感觉就是声明的样子,原描述如下:

>where *\*unassigned** is a special symbol that causes looking up a variable to signal an error if an attempt is made to use the value of the not-yet-assigned variable.

	(lambda <vars>
	  (let ((u '*unassigned*)
	        (v '*unassigned*))
	    (set! u <e1>)
	    (set! v <e2>)
	    <e3>))

其实也就是用 *let* 和 *set!* 在sheme中实现了声明。

