#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <deque>
#include "JniJikken.h"

std::deque<int> mydeque;

using namespace std;
 

void *thread_func(void *param)
{

int i = 1;
  while(1){
//printf("%s\n","c thread");
    usleep(10);                            // mutex_lock が判るように sleep を入れる
//    usleep(10);                            // mutex_lock が判るように sleep を入れる
 //   sleep(1);                            // mutex_lock が判るように sleep を入れる
      mydeque.push_back (i);
i++;

if (i > 100000){

i=1;
}

  }

}

void *thread_func2(void *param)
{

  while(1){


//printf("%s\n","d thread");
    usleep(20);                            // mutex_lock が判るように sleep を入れる
//    usleep(10);                            // mutex_lock が判るように sleep を入れる
 //   sleep(1);                            // mutex_lock が判るように sleep を入れる

    int first = mydeque.front();     // 先頭データを取り出しておく
//printf("%s %d\n","first",first);
    mydeque.pop_front(); 

  }

}


JNIEXPORT jbyteArray JNICALL Java_JniJikken_copy
  (JNIEnv *env, jobject thisj, jstring srcj)
{

  pthread_t thread1;
  pthread_t thread2;
  int pid;

  fprintf(stderr , "---Program start---\n");
  pid = getpid();
  fprintf(stderr , "1:pid = %d\n" , pid);
  if(pthread_create(&thread1 , NULL , thread_func , NULL) !=0)  
        perror("pthread_create()");
  fprintf(stderr , "Next line of pthread_create() called. thread ID=%ld\n" , thread1);

  fprintf(stdout , "---thread2 start---\n");

  if(pthread_create(&thread2 , NULL , thread_func2 , NULL) !=0)  
        perror("pthread_create()");
  fprintf(stderr , "Next line of pthread_create() called. thread ID=%ld\n" , thread2);


  pthread_join(thread1 , NULL);  

  pthread_join(thread2 , NULL);  


	return NULL; /*ひとまずコンパイルを通す為、意味のあることは書かない*/
}
