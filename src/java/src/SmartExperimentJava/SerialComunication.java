package SmartExperimentJava;

import java.awt.EventQueue;

import org.jfree.ui.RefineryUtilities;

import jssc.*;

public class SerialComunication {
	
	
	
	public static void main(String[] args) throws Exception {
		boolean completed = true;		
		
		String[] portNames = SerialPortList.getPortNames();
		CommChannel channel = new SerialCommChannel(portNames[0],9600);	
		GraphicData data = new GraphicData();
		
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(1000);
		System.out.println("Ready.");
		Thread.sleep(1000);
		
		/*EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                DTSCTest demo = new DTSCTest("oh no");
                demo.pack();
                RefineryUtilities.centerFrameOnScreen(demo);
                demo.setVisible(true);
                demo.start();
            }
        });*/
		
		while(completed) {
			String msg = channel.receiveMsg();
			switch(msg) {
			case("IDLE"):
				System.out.println("System is ready!");
				System.out.println("Press start button");
				break;
			case("ERROR"):
				System.out.println("state: "+msg);
				break;
			case("SLEEP"):
				System.out.println("Going in sleep-mode");
				break;
			case("RUNNING"):
				System.out.println("THE EXPERIMENT IS RUNNING");
				
				running(channel);
				break;
			case("COMPLETED"):
				System.out.println("THE EXPERIMENT IS COMPLETED");
				break;
			}
			Thread.sleep(50);
		}
	}
	
	public static void running(CommChannel channel) throws Exception {
		EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                DTSCTest demo = new DTSCTest(channel);
                demo.pack();
                RefineryUtilities.centerFrameOnScreen(demo);
                demo.setVisible(true);
                demo.start();
            }
        });
	}

}
