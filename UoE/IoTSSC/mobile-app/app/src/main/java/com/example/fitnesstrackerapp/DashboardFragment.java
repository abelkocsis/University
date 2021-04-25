package com.example.fitnesstrackerapp;

import android.graphics.Color;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import com.androidnetworking.AndroidNetworking;
import com.androidnetworking.common.Priority;
import com.androidnetworking.error.ANError;
import com.androidnetworking.interfaces.StringRequestListener;

import java.util.Timer;
import java.util.TimerTask;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link DashboardFragment} factory method to
 * create an instance of this fragment.
 */
public class DashboardFragment extends Fragment {

    private boolean isActive = false;

    public static DashboardFragment getInstance(){
        DashboardFragment dashboardFragment = new DashboardFragment();
        return dashboardFragment;
    }

    public DashboardFragment() {
        // Required empty public constructor
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    private void  update(View dashboardFragmentView){
        TextView tvConnection = (TextView)dashboardFragmentView.findViewById(R.id.connection);
        ImageView ivConnection = (ImageView)dashboardFragmentView.findViewById(R.id.imageView_connection);
        ImageView ivAct = (ImageView)dashboardFragmentView.findViewById(R.id.imageView_activity);
        TextView tvAct = (TextView)dashboardFragmentView.findViewById(R.id.textView_activity);

        AndroidNetworking.get(MainActivity.IP + "isActive")
                .addHeaders("token", MainActivity.API_key)
                .setPriority(Priority.HIGH)
                .build()
                .getAsString(new StringRequestListener() {
                    @Override
                    public void onResponse(String response) {
                        if (response.equals("True")) {
                            isActive = true;
                            tvConnection.setText("Connected");
                            ivConnection.setImageResource(R.drawable.tick);
                            AndroidNetworking.get(MainActivity.IP + "getPrediction")
                                    .addHeaders("token", MainActivity.API_key)
                                    .setPriority(Priority.HIGH)
                                    .build()
                                    .getAsString(new StringRequestListener() {
                                        @Override
                                        public void onResponse(String response) {

                                            int imageResource = 0;
                                            String text = "";
                                            String colour = "#000000";

                                            switch (response){
                                                case "WALK":
                                                    imageResource = R.drawable.walk;
                                                    text = "Walking";
                                                    colour = "#81CFFF";
                                                    break;
                                                case "RUN":
                                                    imageResource = R.drawable.run;
                                                    text = "Running";
                                                    colour = "#007EFF";
                                                    break;
                                                case "ELEVATOR":
                                                    imageResource = R.drawable.elevator;
                                                    text ="Elevator";
                                                    colour = "#81CFFF";
                                                    break;
                                                case "STAIR":
                                                    imageResource = R.drawable.stair;
                                                    text = "Climbing stairs";
                                                    colour = "#007EFF";
                                                    break;
                                                default:
                                                    imageResource = R.drawable.idle;
                                                    text = "Idle";
                                                    colour = "#DEF2FE";
                                                    break;
                                            }
                                            ivAct.setImageResource(imageResource);
                                            tvAct.setText(text);
                                            dashboardFragmentView.setBackgroundColor(Color.parseColor(colour));
                                            if (!text.equals("Idle")){
                                                updateBars(dashboardFragmentView);
                                            }
                                        }
                                        @Override
                                        public void onError(ANError error) {
                                            // handle error
                                        }
                                    });
                        }
                        else{
                            isActive = false;
                            tvConnection.setText("Not connected");
                            ivConnection.setImageResource(R.drawable.cross);
                            tvAct.setText("Idle");
                            ivAct.setImageResource(R.drawable.idle);
                            dashboardFragmentView.setBackgroundColor(Color.parseColor("#DEF2FE"));

                        }

                    }
                    @Override
                    public void onError(ANError error) {
                        isActive = false;
                        tvConnection.setText("Not connected");
                        ivConnection.setImageResource(R.drawable.cross);
                        tvAct.setText("Idle");
                        ivAct.setImageResource(R.drawable.idle);
                        dashboardFragmentView.setBackgroundColor(Color.parseColor("#DEF2FE"));
                    }
                });
    }

    private boolean previousActive = false;
    private int ubsCounter = 0;

    private  void updateBarsSometimes(View dashboardFragmentView){
        if (!isActive){
            previousActive = false;
            if (ubsCounter == 5){
                updateBars(dashboardFragmentView);
                ubsCounter = 0;
            }
            else {
                ubsCounter++;
            }
        }
       else if (!previousActive){
            previousActive = isActive;
            updateBars(dashboardFragmentView);
       }
    }

    private void updateBars(View dashboardFragmentView){
        AndroidNetworking.get(MainActivity.IP + "getNextMilestonesAndLevels")
                .setPriority(Priority.LOW)
                .addHeaders("token", MainActivity.API_key)
                .build()
                .getAsString(new StringRequestListener() {
                    @Override
                    public void onResponse(String response) {
                        // get NextMilestones and Levels
                        String resultMilestonesAndLevels = "[1,60,1,60,1,60]";
                        resultMilestonesAndLevels = response;
                        String[] milestonesString = resultMilestonesAndLevels.split(",");

                        String walkLevel = milestonesString[0].substring(1);
                        int walkPrevMilestone = Integer.parseInt(milestonesString[1]);
                        int walkNextMilestone = Integer.parseInt(milestonesString[2]);
                        String runLevel = milestonesString[3];
                        int runPrevMilestone = Integer.parseInt(milestonesString[4]);
                        int runNextMilestone = Integer.parseInt(milestonesString[5]);
                        String  stairLevel = milestonesString[6];
                        int stairPrevMilestone = Integer.parseInt(milestonesString[7]);
                        int stairNextMilestone = Integer.parseInt(milestonesString[8].substring(0, milestonesString[8].length()-2));


                        // getSum
                        AndroidNetworking.get(MainActivity.IP + "getSum")
                                .setPriority(Priority.LOW)
                                .addHeaders("token", MainActivity.API_key)
                                .build()
                                .getAsString(new StringRequestListener() {
                                    @Override
                                    public void onResponse(String response) {
                                        String getSumResult = "[1,null,48,26,62,34,34]";
                                        getSumResult = response;
                                        String[] sumString = getSumResult.split(",");
                                        int walkSum = Integer.parseInt(sumString[3]);
                                        int runSum = Integer.parseInt(sumString[4]);
                                        int stairSum = Integer.parseInt(sumString[5]);


                                        String levelWalkString = "Walking - Level " + walkLevel;
                                        String levelRunString = "Running - Level " + runLevel;
                                        String levelStairString = "Climbing stairs - Level " + stairLevel;
                                        int divider = 1;
                                        String unit = " sec";
                                        String walkProgressString = (walkSum / divider) + " / " + (walkNextMilestone / divider) + unit;
                                        String runProgressString = (runSum / divider) + " / " + (runNextMilestone / divider) + unit;
                                        String stairProgressString = (stairSum / divider) + " / " + (stairNextMilestone / divider) + unit;

                                        float wRelSum = (walkSum - walkPrevMilestone);
                                        int walkProgress = (int)((wRelSum / (walkNextMilestone - walkPrevMilestone)) * 100);
                                        float rRelSum = (runSum - runPrevMilestone);
                                        int runProgress = (int)((rRelSum / (runNextMilestone - runPrevMilestone)) * 100);
                                        float sRelSum = (stairSum - stairPrevMilestone);
                                        int stairProgress = (int)((sRelSum / (stairNextMilestone - stairPrevMilestone)) * 100);

                                        //update

                                        TextView tvLevelWalk = (TextView)dashboardFragmentView.findViewById(R.id.textView_walkingLevel);
                                        TextView tvLevelRun = (TextView)dashboardFragmentView.findViewById(R.id.textView_runLevel);
                                        TextView tvLevelStair = (TextView)dashboardFragmentView.findViewById(R.id.textView_stairLevel);
                                        tvLevelWalk.setText(levelWalkString);
                                        tvLevelRun.setText(levelRunString);
                                        tvLevelStair.setText(levelStairString);

                                        TextView tvProgressWalk = (TextView)dashboardFragmentView.findViewById(R.id.textView_WalkingProgress);
                                        tvProgressWalk.setText(walkProgressString);
                                        TextView tvProgressRun = (TextView)dashboardFragmentView.findViewById(R.id.textView_runProgress);
                                        tvProgressRun.setText(runProgressString);
                                        TextView tvProgressStair = (TextView)dashboardFragmentView.findViewById(R.id.textView_stairProgress);
                                        tvProgressStair.setText(stairProgressString);

                                        ProgressBar pbWalk = (ProgressBar)dashboardFragmentView.findViewById(R.id.progressBar_walk);
                                        pbWalk.setProgress(walkProgress);
                                        ProgressBar pbRun = (ProgressBar)dashboardFragmentView.findViewById(R.id.progressBar_run);
                                        pbRun.setProgress(runProgress);
                                        ProgressBar pbStair = (ProgressBar)dashboardFragmentView.findViewById(R.id.progressBar_stair);
                                        pbStair.setProgress(stairProgress);
                                    }
                                    @Override
                                    public void onError(ANError error) {
                                        // handle error
                                    }

                                });
                    }
                    @Override
                    public void onError(ANError error) {
                    }

                });
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View dashboardFragmentView = inflater.inflate(R.layout.fragment_dashboard, container, false);

        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
                                      @Override
                                      public void run() {
                                          update(dashboardFragmentView);
                                      }
                                  },
                0, 1000);
        timer.scheduleAtFixedRate(new TimerTask() {
                                      @Override
                                      public void run() {
                                          updateBarsSometimes(dashboardFragmentView);
                                      }
                                  },
                0, 1000);
        updateBars(dashboardFragmentView);

        // Inflate the layout for this fragment
        return dashboardFragmentView;
    }
}