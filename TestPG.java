public class TestPG {
  
  public static void main(String[] args) {

      JniJikken me = new JniJikken();
      JniJikken2 me2 = new JniJikken2();
      Thread t1 = new Thread(me);
      //t1.setPriority(10);
      t1.start();

      Thread t2 = new Thread(me2);
      t2.start();

      try{

        while(true){

System.out.println("aaaaa");

            Thread.sleep(10); //3000ミリ秒Sleepする

        }

        }catch(InterruptedException e){}



  }
 
}
