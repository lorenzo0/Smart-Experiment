package SmartExperimentJava;

import java.util.ArrayList;
import java.util.Random;
import javax.swing.JFrame;
import java.time.*;
//import jssc.*;

public class GraphicData extends JFrame {
	final ArrayList<Float> speed;
	final ArrayList<Float> pos;
	final ArrayList<Float> acel;
	final ArrayList<Long> t;
	int countSpeed, countAcel;
	
	private long MILLIS;
	private float SPEED, ACEL;
	
	Clock clock = Clock.systemDefaultZone();
	Random random = new Random();
	
	public GraphicData() {
		speed = new ArrayList<Float>();
		pos = new ArrayList<Float>();
		acel = new ArrayList<Float>();
		t = new ArrayList<Long>();
		
		MILLIS = 0;
		SPEED = 0;
		ACEL = 0;
		countSpeed = 0;
		countAcel=0;
		
		/*speed.add(0.5f);
		speed.add(15f);
		speed.add(30f);
		speed.add(50f);*/
	}
	
	public void addSpeed(int i){
		SPEED = Math.abs(((pos.get(i-1) - pos.get(i))*100) / ((t.get(i) - t.get(i-1))/1000));
		speed.add(SPEED);
		/*if (speed.size()>1) {
			System.out.println("Speed "+ (speed.size()-1));
			addAcel(speed.size()-1);
		}*/
	}
	
	public void addPos(float val){
		pos.add(val);
		MILLIS=clock.millis();
		t.add(MILLIS);
		if (pos.size()>1) {
			System.out.println("pos "+(pos.size()-1));
			addSpeed(pos.size()-1);
		}
	}
	
	public void addAcel(int i){
		ACEL= ((speed.get(i-1) - speed.get(i)) / (( t.get(i) - t.get(i-2))/1000));
		acel.add(Math.abs(ACEL));
	}

	public float getSpeed() {
		if(countSpeed<speed.size()&& speed.size()>0) {
			System.out.println(speed.get(countSpeed)+"   "+ countSpeed);
			return speed.get(countSpeed++);
		}else
			return 0;
	}
	
	public float getAcel() {
		if(countAcel<acel.size() && acel.size()>0)
			return speed.get(countAcel++);
		else
			return 0;
	}
}
