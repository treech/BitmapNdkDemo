package com.treech.bitmap.ndkdemo

import android.graphics.Bitmap
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.treech.bitmap.ndkdemo.databinding.ActivityMainBinding
import java.nio.Buffer
import java.nio.ByteBuffer
import kotlin.experimental.and


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()

        val bitmap = Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888)
        bitmap.eraseColor(-0xcc9967) // AARRGGBB

        val bytes = ByteArray(bitmap.width * bitmap.height * 4)
        val dst: Buffer = ByteBuffer.wrap(bytes)
        bitmap.copyPixelsToBuffer(dst)
        // ARGB_8888 真实的存储顺序是 R-G-B-A
        Log.d(TAG, "R: " + Integer.toHexString((bytes[0].toInt() and 0xff)))
        Log.d(TAG, "G: " + Integer.toHexString((bytes[1].toInt() and 0xff)))
        Log.d(TAG, "B: " + Integer.toHexString((bytes[2].toInt() and 0xff)))
        Log.d(TAG, "A: " + Integer.toHexString((bytes[3].toInt() and 0xff)))
        passBitmap(bitmap)
    }

    /**
     * A native method that is implemented by the 'ndkdemo' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    external fun passBitmap(bitmap:Bitmap)

    companion object {
        // Used to load the 'ndkdemo' library on application startup.
        init {
            System.loadLibrary("ndkdemo")
        }

        private const val TAG = "MainActivity"
    }
}