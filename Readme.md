# PerfTracer

PerfTracer is a performance tracker eg. profiler that relies on source code instrumentation rather than performance sampling. GCC instrumentation eg. -finstrument-functions is used to inject performance counting mechanism which is rdtsc based. It is written in C++ 11 so its aplications are limited to pojects created using this programming language.

### Usage

1. Copy trace.cpp to your project (the one you want to trace performance)
2. Modify Makefile / CMakeLists.txt so that:
- *All traced modules should be comiled with -finstrument-functions compilation flag*
- *Linking of binary should be against dl lib eg. -ldl*
Example CMakeLists.txt is part of this project

### TODO:
- TSC clock frequency detection based on /proc/cpuinfo
- Conversion to kcachegrind format
- Make it thread safe
- Add ULT (main.cpp) RDTSC in foo vs trace.cpp RDTSC for the same function 

### License
Copyright (c) 2016, Jacek Czaja
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

