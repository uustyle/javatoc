#!/bin/sh

javac JniJikken.java JniJikken2.java TestPG.java
g++ -fPIC -I /usr/local/java/include -I/usr/local/java/include/linux -shared -o libJniJikken.so JniJikken.cpp  -lpthread
