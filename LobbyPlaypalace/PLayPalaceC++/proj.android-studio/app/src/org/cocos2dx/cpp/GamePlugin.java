package org.cocos2dx.cpp;

import java.io.ByteArrayOutputStream;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
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

            Bitmap output;

            if (bitmap.getWidth() > bitmap.getHeight()) {
                output = Bitmap.createBitmap(bitmap.getHeight(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
            } else {
                output = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getWidth(), Bitmap.Config.ARGB_8888);
            }

            Canvas canvas = new Canvas(output);

            final int color = 0xff424242;
            final Paint paint = new Paint();
            final Rect rect = new Rect(0, 0, bitmap.getWidth(), bitmap.getHeight());

            float r = 0;

            if (bitmap.getWidth() > bitmap.getHeight()) {
                r = bitmap.getHeight() / 2.0f;
            } else {
                r = bitmap.getWidth() / 2.0f;
            }

            paint.setAntiAlias(true);
            canvas.drawARGB(0, 0, 0, 0);
            paint.setColor(color);
            canvas.drawCircle(r, r, r, paint);
            paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_IN));
            canvas.drawBitmap(bitmap, rect, rect, paint);

            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            output.compress(Bitmap.CompressFormat.PNG, 100, baos);
            byte[] data = baos.toByteArray();

            baos.close();
            output.recycle();
            bitmap.recycle();

            return data;
        }
        catch (Exception e){
            Log.d("Circle Image Failed", e.toString());
        }
        return null;
    }
}
