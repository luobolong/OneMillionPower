# One Million Power

Someone asked me a question, will a PC freeze while calculating 10 to the 100 million power, and if yes, is this program some kind of computer virus? The answer is simply no if we are talking about modern computers and modern operating systems. Basically OS is responsible for allocating system resources when a program needs them. As for CPU, we call it CPU scheduling, that is, a process of determining which process will own CPU for execution while another process is on hold, so the program that is doing the complex calculation won't have full use of CPU, but it may occupy a large portion of computing resources. The same logic is applied if we run program which contains an infinite loop.

Then how about memory? If we store this large number (10 to the 100 million power) in binary, by calculation, it won't occupy much. We denote the number of digits as `k`. So we have

`k = ROUND(10^8/lg(2)) = 332192810 bits = 39.6 MB`

Of course it generates some temporary variables for arithmetic operations such as addition, but the maximum memory in use is no more than three times of that.

Howerver, it's an interesting question that lured me into trying to implement it. To save time and reduce complexity, I reduced the power to one million, which is still a large number. It's best to use assembly language for the fastest speed for sure, but for programming speed I used C++ with Visual Studio in Windows just for simulation. There are some points of my program.

- Obviously, none of the built-in data types can store such large numbers, so I must define my own. The custom type uses `std::bitset` as the basic data structure (it's defined as unsigned), plus an `unsigned long long` type variable to represent the data length.
- This program doesn't use *Fast Power Algorithm*, as known as [Modular exponentiation](https://en.wikipedia.org/wiki/Modular_exponentiation), and it simply does a million multiplications to see how well it can do. Multiplication in binary refered as [Binary multiplier](https://en.wikipedia.org/wiki/Binary_multiplier) is nothing but shift and addition. In our case, `10` in decimal is represented as `1010` in binary. So when we want to multiply a number by 10, we can just simply left shift the number by 3 and 1 bits repectively and add them together, and the sum is the result. So what the program does is just to repeat the above process in each iteration of the exponential computation. The larger the result number in each iteration becomes, the slower the computation is.
- The digits or size of the `std::bitset` data `k` shall be larger than `3321929 bits = 405 KB`, as I want to represent a number of `10^(10^6)`. It's fine to allocate the size as `512 KB`, and the stack size assigned by Visual Studio can be set as `2 MB`, which is fairly enough to avoid stack overflow.
- It's noted that this program is single threaded. I haven't thought of a strategy for multithreading optimization. In theory, it only occupies one CPU core, so its CPU usage is low.

It's just for fun anyway. No copyright. This is just a blog.
