public class HelloJNI {
  static {
    // ライブラリのロード。あとで作るlib***.soの***と一致させます。
    System.loadLibrary("hello");
  }

  // nativeメソッドの宣言
  public native void hello();

  public static void main(String[] args) {
    HelloJNI hello = new HelloJNI();
    hello.hello();
  }
}
