#include <stdio.h>
#include <pthread.h>
#include <iostream>

class ThreadTest {
  private:
    pthread_t thread_handler;      // スレッドハンドラ
    pthread_mutex_t mutex; // ミューテックス(排他処理で優先権を決めるやつ)
    int data;
  public:
    ThreadTest(){
      data = 0;
    }

    // data に値を挿入
    // * execute が優先権を保持している間は待機する
    //
    void setData(int i){
      std::cout << "wait mutex" << std::endl;
      pthread_mutex_lock(&(this->mutex));   // 優先権を保持するまで待機
      data = i;
      pthread_mutex_unlock(&(this->mutex)); // 優先権を破棄
      std::cout << "set Data finished!" << std::endl;
    }
    int getData(){ return data; }

    // ランチャ
    //
    static void* executeLauncher(void* args){
      std::cout << "executeLauncher" << std::endl;
      // 引数に渡されたインスタンスを無理やりキャストして、インスタンスメソッドを実行
      reinterpret_cast<ThreadTest*>(args)->execute();
      return (void*)NULL;
    }

    // スレッド開始
    void threadStart(){
      if ((this->thread_handler) == NULL){
        std::cout << "threadStart" << std::endl;
        pthread_mutex_init(&(this->mutex), NULL); // ミューテックスの初期化
        pthread_create(                           // スレッドの生成
            &(this->thread_handler),
            NULL,
            &ThreadTest::executeLauncher,         // スレッドにできるのは、static なメソッドや関数のみ
            this
        );
      }
    }

    // スレッドで実行したいインスタンスメソッド
    //
    void execute(){
      while(1){
        pthread_testcancel();                 // キャンセル要求が来ていたらここで終了
        pthread_mutex_lock(&(this->mutex));   // 優先権を保持するまで待機
        std::cout << "execute" << std::endl;
        std::cout << "Data = " << (this->getData()) << std::endl;
        sleep(10);                            // mutex_lock が判るように sleep を入れる
        pthread_mutex_unlock(&(this->mutex)); // 優先権を破棄
        sleep(1);
      }
    }

    // デストラクタ
    // * 終了時に、スレッドにキャンセル要求を投げる
    //
    ~ThreadTest(){
      std::cout << "destructor start" << std::endl;
      pthread_cancel(this->thread_handler);     // スレッドにキャンセル要求を投げる
      pthread_join(this->thread_handler, NULL); // スレッドが終了するまで待機
      std::cout << "destructor end" << std::endl;
    }
};

int main()
{
  ThreadTest* matrix = new ThreadTest();
  matrix->setData(10);
  matrix->threadStart();
  sleep(1);
  matrix->setData(20);
  sleep(30);
  delete matrix;
}
