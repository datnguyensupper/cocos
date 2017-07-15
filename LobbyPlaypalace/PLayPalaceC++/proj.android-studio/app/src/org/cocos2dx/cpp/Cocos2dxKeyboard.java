package org.cocos2dx.cpp;

import android.content.ClipboardManager;
import android.content.ClipData;
import android.content.Context;
import org.cocos2dx.lib.Cocos2dxHelper;

public class Cocos2dxKeyboard{
    
    public static void copyString2ClipBoard(final String arg1)  {
        System.out.println("String" + arg1);
        if(arg1 == null) return;

        Cocos2dxHelper.getActivity().runOnUiThread(new Runnable() {
            public void run() {
                ClipboardManager clipboard = (ClipboardManager) Cocos2dxHelper.getActivity().getSystemService(Context.CLIPBOARD_SERVICE);
                ClipData clip = ClipData.newPlainText(arg1, arg1);
                clipboard.setPrimaryClip(clip);
            }
        });
    }

}
