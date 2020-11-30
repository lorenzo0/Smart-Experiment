package SmartExperimentJava;


import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Random;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.Timer;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.DynamicTimeSeriesCollection;
import org.jfree.data.time.Second;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;

public class DTSCTest extends ApplicationFrame {

    private final String TITLE = "Speed Graphic";
    private final String START = "Start";
    private final String STOP = "Stop";
    private Timer timer;
    private GraphicData data = new GraphicData();
    private Random random = new Random();
    String msg;
    float rand;
    int count = -1;
    
    public DTSCTest(CommChannel channel){	
        super("SPEED");
        final DynamicTimeSeriesCollection dataset =
            new DynamicTimeSeriesCollection(1, 500, new Second());
        dataset.setTimeBase(new Second(0, 0, 0, 1, 1, 2011));
        dataset.addSeries(new float[1], 0, TITLE);
        JFreeChart chart = createChart(dataset);

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

    	//CommChannel channel = new SerialCommChannel("COM3",9600);
        this.add(new ChartPanel(chart), BorderLayout.CENTER);
        JPanel btnPanel = new JPanel(new FlowLayout());
        btnPanel.add(run);
        this.add(btnPanel, BorderLayout.SOUTH);

        timer = new Timer(1000, new ActionListener() {

            float[] newData = new float[1];

            @Override
            public void actionPerformed(ActionEvent e) {
            	//count++;
            	try {
					msg = channel.receiveMsg();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
            	System.out.println(msg);
            	//rand = random.nextFloat();
            	data.addPos(Float.parseFloat(msg));
            	newData[0] = data.getSpeed();
                dataset.advanceTime();
                dataset.appendData(newData);
            }
        });
    }


    private JFreeChart createChart(final XYDataset dataset) {
        final JFreeChart result = ChartFactory.createTimeSeriesChart(
            "Speed cm/s", "Time(s)", "Position(cm)", dataset, true, true, false);
        final XYPlot plot = result.getXYPlot();
        
        DateAxis axis = (DateAxis) plot.getDomainAxis();
        axis.setFixedAutoRange(10000);
        axis.setDateFormatOverride(new SimpleDateFormat("ss.SS"));
        
        /*ValueAxis domain = plot.getDomainAxis();
        domain.setAutoRange(true);
        ValueAxis range = plot.getRangeAxis();
        range.setRange(0, 80);*/
        return result;
    }

    public void start() {
        timer.start();
    }

    /*public static void main(final String[] args) {
        EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                DTSCTest demo = new DTSCTest("Speed cm/s");
                demo.pack();
                RefineryUtilities.centerFrameOnScreen(demo);
                demo.setVisible(true);
                demo.start();
            }
        });
    }*/
}