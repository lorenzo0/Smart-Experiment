package SmartExperimentJava;


import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Random;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.DynamicTimeSeriesCollection;
import org.jfree.data.time.Second;
import org.jfree.data.xy.XYDataset;

public class DTSCTest extends JFrame {

    /**
	 * 
	 */
	//private static final long serialVersionUID = 1L;
	private final String START = "Start";
	private final String STOP = "Stop";
    private Timer timer;
    GraphicData data = new GraphicData();
    Random random = new Random();
    
    String msg;
    float pot=0;
    int count = 2;
    
    public DTSCTest(CommChannel channel, float pot){	
        super("Grapichs");
        pot = this.pot;
        
        final DynamicTimeSeriesCollection datasetSpeed =
            new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetSpeed.setTimeBase(new Second(0, 0, 0, 1, 1, 2011));
        datasetSpeed.addSeries(new float[1], 0, "SPEED");
        
        final DynamicTimeSeriesCollection datasetAcel =
                new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetAcel.setTimeBase(new Second(0, 0, 0, 1, 1, 2020));
        datasetAcel.addSeries(new float[1], 0, "ACELERATION");
        
        final DynamicTimeSeriesCollection datasetPos =
                new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetPos.setTimeBase(new Second(0, 0, 0, 1, 1, 2020));
        datasetPos.addSeries(new float[1], 0, "POS");
            
        JFreeChart chartSpeed = createChart(datasetSpeed, "SPEED", "Time (s)", "Speed (mm/s)");
        JFreeChart chartAcel = createChart(datasetAcel, "ACELERATION", "Time (s)", "Aceleration (mm/s^2)");
        JFreeChart chartPos = createChart(datasetPos, "POSITION", "Time (s)", "Position (mm)");
        final JButton run = new JButton(STOP);
        run.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                String cmd = e.getActionCommand();
                if (STOP.equals(cmd)) {
                    timer.stop();
                    run.setText(START);
                } else {
                    timer.start();
                    run.setText(STOP);
                }
            }
        });

        JPanel btnPanel = new JPanel(new FlowLayout());
        btnPanel.add(run);
        this.add(btnPanel, BorderLayout.SOUTH);
        
        JPanel graphicsPanel = new JPanel(new GridLayout()); 
        graphicsPanel.add(new ChartPanel(chartPos));
        graphicsPanel.add(new ChartPanel(chartSpeed));
        graphicsPanel.add(new ChartPanel(chartAcel));

        this.add(graphicsPanel, BorderLayout.CENTER );
        
        //(int)pot
        timer = new Timer(400, new ActionListener() { 

            float[] newDataSpeed = new float[1];
            float[] newDataAcel = new float[1];
            float[] newDataPos = new float[1];

            @Override
            public void actionPerformed(ActionEvent e) {
            	try {
            		msg = channel.receiveMsg();
            		System.out.println("MSG "+msg);
				} catch (InterruptedException e1) {e1.printStackTrace();}
            	
            	if (msg.equals("COMPLETED")) {
            		timer.stop();
            		data.delData();
            	}else {
            		System.out.println("else");
            		String[] splitMsg = msg.split("\\|",3);
            		data.addPos(Float.parseFloat(splitMsg[0]));
            		data.addSpeed(Float.parseFloat(splitMsg[1]));
            		data.addAcel(Float.parseFloat(splitMsg[2]));
            		newDataPos[0] = Float.parseFloat(splitMsg[0]);		            	
            	}
            	System.out.println("COUNT"+count);
            	newDataSpeed[0] = data.getSpeed();
            	newDataAcel[0] = data.getAcel();
            	datasetPos.advanceTime();
                datasetPos.appendData(newDataPos);
                datasetSpeed.advanceTime();
                datasetSpeed.appendData(newDataSpeed);
                datasetAcel.advanceTime();
                datasetAcel.appendData(newDataAcel);
            }
        });
    }


	private JFreeChart createChart(final XYDataset dataset, String title, String xlabel, String ylabel) {
        
    	final JFreeChart result = ChartFactory.createTimeSeriesChart(title, xlabel, ylabel, dataset, true, true, false);
    	
        final XYPlot plot = result.getXYPlot();
        plot.setBackgroundPaint( new Color(153,203,255));
        
        DateAxis axis = (DateAxis) plot.getDomainAxis();
        
        axis.setFixedAutoRange(10000);
        axis.setDateFormatOverride(new SimpleDateFormat("ss.SS"));
        return result;
    }

    public void start() {
        timer.start();
    }
}
