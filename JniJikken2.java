import java.util.Calendar;
import java.text.SimpleDateFormat;

public class JniJikken2 implements Runnable {

    public void run() {

        try{
            while(true){

System.out.println("bbb");

//現在日時取得
        Calendar c = Calendar.getInstance();

        //フォーマットを指定
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmssSSS");
        System.out.println(sdf.format(c.getTime()));


                Thread.sleep(10); //3000ミリ秒Sleepする

            }
        }catch(InterruptedException e){}


	}
}
