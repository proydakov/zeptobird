package com.proydakov.zeptobird;

import android.annotation.TargetApi;
import android.app.NativeActivity;
import android.os.Bundle;
import android.view.View;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.widget.Toast;
import android.util.Log;

public class ZeptoBirdActivity extends NativeActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        TAG = "ZeptoBird";

        Log.v(TAG, "onCreate");
        super.onCreate(savedInstanceState);
        //Hide toolbar
        int SDK_INT = android.os.Build.VERSION.SDK_INT;
        if(SDK_INT >= 19)
        {
            setImmersiveSticky();

            View decorView = getWindow().getDecorView();
            decorView.setOnSystemUiVisibilityChangeListener
                    (new View.OnSystemUiVisibilityChangeListener() {
                @Override
                public void onSystemUiVisibilityChange(int visibility) {
                    setImmersiveSticky();
                }
            });
        }
        playMusic("menu");
    }

    @Override
    protected void onStop() {
        Log.v(TAG, "onStop");
        super.onStop();
        if(mMusicPlayer != null) {
            mMusicPlayer.stop();
        }
    }

    @Override
    protected void onRestart() {
        Log.v(TAG, "onRestart");
        super.onRestart();
        if(mMusicPlayer != null) {
            mMusicPlayer.start();
        }
    }

    @Override
    protected void onDestroy() {
        Log.v(TAG, "onDestroy");
        super.onDestroy();
        if(mMusicPlayer != null) {
            mMusicPlayer.stop();
        }
    }

    @Override
    protected void onPause() {
        Log.v(TAG, "onPause");
        super.onPause();
        if(mMusicPlayer != null) {
            mMusicPlayer.pause();
        }
    }

    @Override
    protected void onResume() {
        Log.v(TAG, "onResume");
        super.onResume();
        if(mMusicPlayer != null) {
            mMusicPlayer.start();
        }

        //Hide toolbar
        int SDK_INT = android.os.Build.VERSION.SDK_INT;
        if(SDK_INT >= 11 && SDK_INT < 14)
        {
            getWindow().getDecorView().setSystemUiVisibility(View.STATUS_BAR_HIDDEN);
        }
        else if(SDK_INT >= 14 && SDK_INT < 19)
        {
            getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_LOW_PROFILE);
        }
        else if(SDK_INT >= 19)
        {
            setImmersiveSticky();
        }

    }

    @TargetApi(19)    
    void setImmersiveSticky() {
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE);
    }

    private void playMusic(String assetName) {
        try {
            AssetFileDescriptor afd =  getAssets().openFd("music/" + assetName + ".mp3");
            mMusicPlayer = new MediaPlayer();
            mMusicPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
            afd.close();
            mMusicPlayer.setLooping(true);
            mMusicPlayer.prepare();
            mMusicPlayer.start();
        }
        catch (Exception ex) {
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_LONG).show();
        }
    }

    MediaPlayer mMusicPlayer;
    String      TAG;
}
