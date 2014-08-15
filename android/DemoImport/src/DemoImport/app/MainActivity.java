// Copyright (c) 2014, LGPL 2.1 license, https://github.com/touchvg/DemoImport

package DemoImport.app;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import rhcad.touchvg.IGraphView;
import rhcad.touchvg.IViewHelper;
import rhcad.touchvg.ViewFactory;
import DemoImport.core.GlyphParser;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup;

public class MainActivity extends Activity {
    private static final String TAG = "vgdemo";
    private static final String PATH = "mnt/sdcard/DemoImport";
    private static final String EXAMPLE1 = "example1.json";
    private IViewHelper hlp = ViewFactory.createHelper();

    static {
        System.loadLibrary("glyph");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setupExamples();

        hlp.createSurfaceView(this, (ViewGroup) findViewById(R.id.frame), null);
        hlp.getGraphView().setOnFirstRegenListener(new IGraphView.OnFirstRegenListener() {
            @Override
            public void onFirstRegen(IGraphView view) {
                hlp.zoomToExtent();
            }
        });

        GlyphParser.loadFile(hlp.cmdViewHandle(), new File(PATH, EXAMPLE1).getPath());
        hlp.setCommand("select");
    }

    private void setupExamples() {
        final byte[] buffer = new byte[1024];
        final File dest = new File(PATH, EXAMPLE1);
        int n;

        new File(PATH).mkdir();
        if (!dest.exists()) {
            final InputStream is = getResources().openRawResource(R.raw.example1);

            try {
                final FileOutputStream os = new FileOutputStream(dest.getPath());
                while ((n = is.read(buffer)) > 0) {
                    os.write(buffer, 0, n);
                }
                os.close();
            } catch (FileNotFoundException e) {
                Log.e(TAG, "FileNotFound", e);
            } catch (IOException e) {
                Log.e(TAG, "IOException", e);
            }
        }
    }

    @Override
    public void onDestroy() {
        hlp.onDestroy();
        super.onDestroy();
    }

    @Override
    public void onPause() {
        hlp.onPause();
        super.onPause();
    }

    @Override
    public void onResume() {
        hlp.onResume();
        super.onResume();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        hlp.onSaveInstanceState(outState, PATH);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        hlp.onRestoreInstanceState(savedInstanceState);
    }
}
