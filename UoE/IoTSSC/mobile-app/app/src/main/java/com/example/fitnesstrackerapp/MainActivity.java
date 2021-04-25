package com.example.fitnesstrackerapp;

import android.os.Bundle;
import com.androidnetworking.AndroidNetworking;
import com.google.android.material.tabs.TabLayout;
import androidx.viewpager.widget.ViewPager;
import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import com.google.firebase.iid.FirebaseInstanceId;

public class MainActivity extends AppCompatActivity {

    public static final String IP = "http://35.197.244.62:2333/";
    public static final String API_key = "6#fJ5m9BBpjSM&r$heYbLS4GJqcqypjzLCcYLMqJ8M4qAgGLDpA*8&vb$8zNMH^uk8x@&tHDy$Yo5V9a$W&K6GDansQxW!9TjEW6du&4TKB3PsdP#mirTkvHXEm@ZAYQ";

    TabLayout tabLayout;
    ViewPager viewPager;
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        viewPager = findViewById(R.id.view_pager);
        tabLayout = findViewById(R.id.tabs);

        ViewPagerAdapter viewPagerAdapter = new ViewPagerAdapter(getSupportFragmentManager());
        viewPagerAdapter.addFragment(DashboardFragment.getInstance(), "Dashboard");
        viewPagerAdapter.addFragment(StatisticsFragment.getInstance(), "Statistics");

        viewPager.setAdapter(viewPagerAdapter);
        tabLayout.setupWithViewPager(viewPager);

        AndroidNetworking.initialize(getApplicationContext());

        String refreshedToken = FirebaseInstanceId.getInstance().getToken(); // in case of we forget the token.
        Log.d(TAG, "FCM token: " + refreshedToken);
    }

}

