package com.example.fitnesstrackerapp;

import android.graphics.Color;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import com.androidnetworking.AndroidNetworking;
import com.androidnetworking.common.Priority;
import com.androidnetworking.error.ANError;
import com.androidnetworking.interfaces.StringRequestListener;
import com.github.mikephil.charting.charts.BarChart;
import com.github.mikephil.charting.components.AxisBase;
import com.github.mikephil.charting.components.Description;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.formatter.IAxisValueFormatter;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class StatisticsFragment extends Fragment {

    private static final long MILLIS_IN_A_DAY = 1000 * 60 * 60 * 24;


    public static StatisticsFragment getInstance(){
        StatisticsFragment statisticsFragment = new StatisticsFragment();
        return statisticsFragment;
    }

    String activityName;
    String titleName = "";

    public void update(View statisticsFragmentView){
        TextView tvChartTitle = (TextView)statisticsFragmentView.findViewById(R.id.textView_chartTitle);
        RadioGroup rgActivity = (RadioGroup)statisticsFragmentView.findViewById(R.id.radioGroup_activity);

        int checkedRadioButtonId = rgActivity.getCheckedRadioButtonId();

        switch (checkedRadioButtonId){
            case R.id.radioButton_run:
                activityName = "run";
                titleName = "Running";
                break;
            case R.id.radioButton_walk:
                activityName = "walk";
                titleName = "Walking";
                break;
            case R.id.radioButton_stair:
                activityName = "stair";
                titleName = "Climbing Stairs";
                break;
            case R.id.radioButton_elevator:
                activityName = "elevator";
                titleName = "Using the elevator";
                break;
        }

        AndroidNetworking.get(MainActivity.IP + "getDailyStats")
                .addQueryParameter("activity", activityName)
                .addHeaders("token", MainActivity.API_key)
                .setPriority(Priority.LOW)
                .build()
                .getAsString(new StringRequestListener() {
                    @Override
                    public void onResponse(String response) {
                        titleName = titleName + " Statistics";
                        tvChartTitle.setText(titleName);

                        String get31DaysResult = "[72,62,23,78,21,10,72]";
                        get31DaysResult = response;
                        String[] splitted31day = get31DaysResult.split(",");
                        splitted31day[0] = splitted31day[0].substring(1);
                        int lastIndex = splitted31day.length - 1;
                        splitted31day[lastIndex] = splitted31day[lastIndex].substring(0, splitted31day[lastIndex].length()-2);

                        //ArrayList xAxis = new ArrayList();
                        ArrayList yAxis = new ArrayList();

                        int i = 0;
                        for (String s : splitted31day){
                            yAxis.add(new BarEntry(i, Integer.parseInt(s)));
                            i++;
                        }

                        BarDataSet barDataSet = new BarDataSet(yAxis, "Daily Seconds");
                        barDataSet.setColor(Color.rgb(0, 155, 0));
                        ArrayList dataSets = new ArrayList();
                        dataSets.add(barDataSet);


                        BarChart chart = (BarChart)statisticsFragmentView.findViewById(R.id.chart);

                        BarData data = new BarData(barDataSet);
                        chart.setData(data);


                        SimpleDateFormat formatter = new SimpleDateFormat("dd/MM");
                        Date date = new Date();

                        // create dates as labels
                        String[] dates = new String[31];
                        dates[6] = formatter.format(date);
                        for (i = 0; i < 6; i++){
                            date = new Date(date.getTime() - MILLIS_IN_A_DAY);
                            dates[5-i] = formatter.format(date);
                        }

                        XAxis xAxis = chart.getXAxis();
                        xAxis.setGranularity(1f);
                        // map labels
                        xAxis.setValueFormatter(new IAxisValueFormatter() {
                            @Override
                            public String getFormattedValue(float value, AxisBase axis) {
                                return dates[(int) value];
                            }
                        });

                        chart.setFocusable(false);
                        Description desc = new Description();
                        desc.setText("");
                        chart.setDescription(desc);
                        chart.animateXY(2000, 2000);
                        chart.invalidate();

                    }
                    @Override
                    public void onError(ANError error) {
                        // handle error
                    }

                });
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View statisticsFragmentView = inflater.inflate(R.layout.fragment_statistics, container, false);
        update(statisticsFragmentView);

        RadioButton radioButton1 = (RadioButton)statisticsFragmentView.findViewById(R.id.radioButton_elevator);
        radioButton1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                update(statisticsFragmentView);
            }
        });

        RadioButton radioButton2 = (RadioButton)statisticsFragmentView.findViewById(R.id.radioButton_run);
        radioButton2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                update(statisticsFragmentView);
            }
        });

        RadioButton radioButton3 = (RadioButton)statisticsFragmentView.findViewById(R.id.radioButton_stair);
        radioButton3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                update(statisticsFragmentView);
            }
        });

        RadioButton radioButton4 = (RadioButton)statisticsFragmentView.findViewById(R.id.radioButton_walk);
        radioButton4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                update(statisticsFragmentView);
            }
        });

        return statisticsFragmentView;
    }
}