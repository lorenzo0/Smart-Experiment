package SmartExperimentJava;

import java.awt.EventQueue;

import javax.swing.JFrame;

import org.jfree.ui.RefineryUtilities;

import jssc.*;

public class SerialComunication {
	
	
	
	public static void main(String[] args) throws Exception {
		boolean completed = true;
		float pot=0;
		
		String[] portNames = SerialPortList.getPortNames();
		CommChannel channel = new SerialCommChannel(portNames[0],9600);		
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(1000);
		System.out.println("Ready.");
		Thread.sleep(1000);		
		
		while(completed) {
			String msg = channel.receiveMsg();
			switch(msg) {
			case("CALIBRATION"):
				System.out.println("calibrating sensors...");
			case("IDLE"):
				System.out.println("System is ready!");
				System.out.println("Press start button");
				break;
			case("ERROR"):
				System.out.println("Object not detected");
				break;
			case("SLEEP"):
				System.out.println("Going in sleep-mode");
				break;
			case("RUNNING"):
				System.out.println("THE EXPERIMENT IS RUNNING");
				msg = channel.receiveMsg();
				pot = Float.parseFloat(msg);
				System.out.println(pot);
				running(channel,pot);
				break;
			case("COMPLETED"):
				System.out.println("THE EXPERIMENT IS COMPLETED");
				break;
			}
		}
	}
	
	public static void running(CommChannel channel, float pot ) throws Exception {
		EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
            	DTSCTest demo = new DTSCTest(channel, pot);
            	System.out.println("pot:"+pot);
            	demo.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                demo.pack();
                RefineryUtilities.centerFrameOnScreen(demo);
                demo.setVisible(true);
                demo.start();
            }
        });
	}

}
