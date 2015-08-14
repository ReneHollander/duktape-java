duktape-java - A Java binding for [Duktape](http://duktape.org/)
================================================================

Work in progress

# Implemented Features
- Spawn multiple duktape contexts that are isolated from each other
- Access Javascript objects and arrays through Java maps and lists
- Access and modify the Javascript global object
- Execute Javascript from Java
- Register Java functions in Javascript objects
- Invoke Javascript functions from Java
- Invoke Java methods from Javascript
- Error handling of script evalutation/compilation fails
- Getting Javascript errors into Java
- Throwing Javascript errors to Javascript from Java

# WIP Features
- Compiling of scripts
- Unit Tests
- Access Debugger from Java
- Javadoc and documentation
- Examples

# Building
### Native
- `mkdir build && cd build`
- `cmake ../`
- `make`

### Java
- `./gradlew build` or `gradlew.bat build`

# Authors
- Rene Hollander `<rene@rene8888.at>`

# License
The MIT License (MIT)

Copyright (c) 2015 Rene Hollander

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
