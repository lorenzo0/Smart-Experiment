package SmartExperimentJava;

import java.util.ArrayList;
import javax.swing.JFrame;

public class GraphicData extends JFrame {
	/**
	 * 
	 */
	//private static final long serialVersionUID = 1L;
	ArrayList<Float> speed;
	ArrayList<Float> pos;
	ArrayList<Float> acel;

	int countSpeed, countAcel;
		
	public GraphicData() {
		speed = new ArrayList<Float>();
		pos = new ArrayList<Float>();
		acel = new ArrayList<Float>();

		countSpeed = 0;
		countAcel=0;
	}

	public void addPos(float val){
		pos.add(val);
	}
	
	public void addSpeed(float val){
		speed.add(val);
	}
	
	public void addAcel(float val){
		acel.add(val);
	}

	public float getSpeed() {
		if(countSpeed<speed.size() && speed.size()>0) {
			//System.out.println("SPEED "+speed.get(countSpeed)+"   "+ countSpeed);
			return speed.get(countSpeed++);
		}else
			return 0;
	}
	
	public float getAcel() {
		if(countAcel<acel.size() && acel.size()>0) {
			//System.out.println("ACELERATION "+acel.get(countAcel)+"   "+ countAcel);
			return acel.get(countAcel++);
		}else
			return 0;
	}
	
	public void delData() {
		pos.clear();
		speed.clear();
		acel.clear();
		countAcel = 0;
		countSpeed= 0;
	}

}
