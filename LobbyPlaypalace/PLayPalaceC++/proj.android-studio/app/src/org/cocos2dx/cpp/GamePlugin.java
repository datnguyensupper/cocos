package org.cocos2dx.cpp;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.net.Uri;
import android.preference.PreferenceManager.OnActivityResultListener;
import android.graphics.Canvas;
import android.util.Log;

public class GamePlugin{
    private static final int CIRCLE_IMAGE_ACTIVITY = 1;    //Magic Number

    private static boolean initialized = false;

    public static  byte[] circleImage(final byte[] imageData)  {
        if(imageData == null){
            return null;
        }

        try {
            Bitmap bitmap = BitmapFactory.decodeByteArray(imageData, 0, imageData.length);

            Bitmap output = bitmap.copy(bitmap.getConfig(), true);

            int width = bitmap.getWidth();
            int height = bitmap.getHeight();

            Canvas canvas = new Canvas(output);

            final int color = 0xff424242;
            final Paint paint = new Paint();
            final Rect rect = new Rect(0, 0, width, height);

            paint.setAntiAlias(true);
            canvas.drawARGB(0, 0, 0, 0);
            paint.setColor(color);
            canvas.drawCircle(width / 2, height / 2,
                    width / 2, paint);
            paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_IN));
            canvas.drawBitmap(bitmap, rect, rect, paint);

//            int bytes = output.getByteCount();
//
//            ByteBuffer buffer = ByteBuffer.allocate(bytes); //Create a new buffer
//            buffer.order(ByteOrder.nativeOrder());
//            output.copyPixelsToBuffer(buffer); //Move the byte data to the buffer

            byte[] data = null;
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            output.compress(Bitmap.CompressFormat.PNG, 100, baos);
            data = baos.toByteArray();

            bitmap.recycle();

            return data;
        }
        catch (Exception e){
            Log.d("Circle Image Failed", e.toString());
        }
        return null;
    }
}
