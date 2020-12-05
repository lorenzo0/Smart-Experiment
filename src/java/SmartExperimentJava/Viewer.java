package SmartExperimentJava;


import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
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

/*
 * questa classe (con l'utilizzo di jfreechart) implementa il grafico in tempo reale
 * della posizione, velocita' ed accelerazione.
 */

public class Viewer extends JFrame {

    private Timer timer;
    GraphicData data = new GraphicData();
    
    String msg = "";
    float pot=0;
    
    public Viewer(CommChannel channel, float pot){	
        super("Grapichs");
        this.pot=pot;
        /*
         * per realizzare questo tipo di grafico è necessario creare un 
         * dataSet che viene aggiornato ogni volta che viene rilevato un nuovo dato,
         * questo aggiornamento viene gestito dal timer 
         */
        final DynamicTimeSeriesCollection datasetSpeed =
            new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetSpeed.setTimeBase(new Second(0, 0, 0, 1, 1, 2020));
        datasetSpeed.addSeries(new float[1], 0, "SPEED");
        
        final DynamicTimeSeriesCollection datasetAcel =
                new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetAcel.setTimeBase(new Second(0, 0, 0, 1, 1, 2020));
        datasetAcel.addSeries(new float[1], 0, "ACCELERATION");
        
        final DynamicTimeSeriesCollection datasetPos =
                new DynamicTimeSeriesCollection(1, 500, new Second());
        datasetPos.setTimeBase(new Second(0, 0, 0, 1, 1, 2020));
        datasetPos.addSeries(new float[1], 0, "POS");
            
        JFreeChart chartSpeed = createChart(datasetSpeed, "SPEED", "Time (s)", "Speed (mm/s)");
        JFreeChart chartAcel = createChart(datasetAcel, "ACCELERATION", "Time (s)", "Acceleration (mm/s^2)");
        JFreeChart chartPos = createChart(datasetPos, "POSITION", "Time (s)", "Position (mm)");
       
        
        JPanel graphicsPanel = new JPanel(new GridLayout()); 
        graphicsPanel.add(new ChartPanel(chartPos));
        graphicsPanel.add(new ChartPanel(chartSpeed));
        graphicsPanel.add(new ChartPanel(chartAcel));

        this.add(graphicsPanel, BorderLayout.CENTER );
        data.delData();
        
        /*
         * tramite l'action listener relativo al timer, che parte periodicamente 
         * (tempo gestito dal potenziometro di arduino che passa il valore a java tramite seriale <pot>),
         * è possibile aggiornare i dati del grafico in tempo reale
         */
        
        timer = new Timer((int)pot, new ActionListener() { 

            float[] newDataSpeed = new float[1];
            float[] newDataAcel = new float[1];
            float[] newDataPos = new float[1];

            @Override
            public void actionPerformed(ActionEvent e) {
            		try {
	            		msg = channel.receiveMsg();
            		} catch (InterruptedException e1) {e1.printStackTrace();}
            		if (msg.equals("COMPLETED")) {
            			/*
            			 * nel caso in cui il messaggio sia "COMPLETED" l'esperimento è completato
            			 * il timer viene terminato in modo da non leggere più messaggi dal seriale
            			 * i dati vengono eliminati
            			 */
            			((Timer)e.getSource()).stop();
            			System.out.println("THE EXPERIMENT IS COMPLETED");
            			data.delData();
            		}else {
            			/*
            			 * arduino invia il messaggio usando il pattern
            			 *posizione|velocita'|accelerazione 
            			 *che viene separato da java tramite lo split           
            			 */
	            		String[] splitMsg = msg.split("\\|",3);
	            		data.addPos(Float.parseFloat(splitMsg[0]));
	            		data.addSpeed(Float.parseFloat(splitMsg[1]));
	            		data.addAcel(Float.parseFloat(splitMsg[2]));
	            		
	            		newDataPos[0] = Float.parseFloat(splitMsg[0]);		            
		            	newDataSpeed[0] = data.getSpeed();
		            	newDataAcel[0] = data.getAcel();
		            	
		            	datasetPos.advanceTime();
		                datasetPos.appendData(newDataPos);
		                
		                datasetSpeed.advanceTime();
		                datasetSpeed.appendData(newDataSpeed);
		                
		                datasetAcel.advanceTime();
		                datasetAcel.appendData(newDataAcel);
            		}
            }
        });
        
    }

    /*
     * tramite questo metodo si creano le strutture dei grafici
     */
    
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
