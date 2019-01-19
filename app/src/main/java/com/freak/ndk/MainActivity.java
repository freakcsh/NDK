package com.freak.ndk;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
public String name="测试jni开发";
    private int[] source={1,4,0,7,33,11};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(getMes());
        getArray(source);
        for (int i=0;i<source.length;i++){
            Log.e("TAG",source[i]+"\n");
        }
    }

    public String getName(){
        return "1234";
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String stringFromMyJNI();
    public native String getMes();
    public native void getArray(int [] array);
    //引用解决的是什么问题？什么时候通知jvm回收JNI对象
    public native void getLocalReference();
}
