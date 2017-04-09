public class JniJikken implements Runnable {

	private native byte[] copy(String src);

    public void run() {
		System.loadLibrary("JniJikken");

		String src = "testテスト";

System.out.println("copy mae");

		byte[] dst = this.copy(src);
System.out.println("copy ato");

		System.out.println(dst);
	}
}
