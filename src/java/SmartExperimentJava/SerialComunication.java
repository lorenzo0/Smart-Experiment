package SmartExperimentJava;

import java.awt.EventQueue;

import javax.swing.JFrame;

import org.jfree.ui.RefineryUtilities;

import jssc.*;

public class SerialComunication {
	
	/*
	 * tramite il main (una volta calibrati tutti i sensori di arduino) gestiamo i 
	 * messaggi ricevuti. In base allo stato in cui si trova l'esperimento viene visualizzato
	 * il messaggio relativo tramite terminale 
	 */
	
	public static void main(String[] args) throws Exception {
		float pot=0;
		
		String[] portNames = SerialPortList.getPortNames();
		CommChannel channel = new SerialCommChannel(portNames[0],9600);	
		
		System.out.println("Waiting Arduino for rebooting and calibrating: ");		
		Thread.sleep(1000);
		System.out.println(".");
		Thread.sleep(1000);
		System.out.println(".");
		Thread.sleep(1000);
		System.out.println(".");
		Thread.sleep(1000);
		System.out.println(".");
		Thread.sleep(1000);
		System.out.println(".");
		Thread.sleep(1000);
		System.out.println(".");
		System.out.println("SYSTEM IS READY.");
			
		
		while(true) {
			String msg = channel.receiveMsg();
			switch(msg) {
			case("IDLE"):
				System.out.println("IDLE Press start button");
				break;
			case("ERROR"):
				System.out.println("ERROR: Object not detected");
				break;
			case("SLEEP"):
				System.out.println("SLEEP: Going in sleep-mode");
				break;
			case("RUNNING"):
				/*
				 * una volta entrato in stato di running tramite il metodo running(...) 
				 * viene visualizzato il pannello contenente i tre grafici 
				 * 
				 * ogni volta che l'esperimento ricomincia viene visualizzato un nuovo grafico
				 */
				System.out.println("THE EXPERIMENT IS RUNNING");
				msg = channel.receiveMsg();
				pot = Float.parseFloat(msg);
				running(channel, pot);
				break;
			case("COMPLETED"):
				System.out.println("THE EXPERIMENT IS COMPLETED");
				break;
			}
		}
	}
	
	public static void running(CommChannel channel,float pot) throws Exception {
		Viewer demo = new Viewer(channel, pot);
		EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
            	demo.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                demo.pack();
                RefineryUtilities.centerFrameOnScreen(demo);
                demo.setVisible(true);
                demo.start();
            }
        });
		demo.stop();
	}

}
