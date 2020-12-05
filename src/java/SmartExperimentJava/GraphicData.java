package SmartExperimentJava;

import java.util.ArrayList;
import javax.swing.JFrame;


/*tramite questa classe vengono memorizzati i valori di
 * posizione, velocita' e accelerazioni per la durata di tutto l'esperimento
 * al temine venngono cancellati tramite delData().
 */
public class GraphicData extends JFrame {
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

	/*
	 * tramite questi due metodi vengono inviati i dati al grafico
	 */
	public float getSpeed() {
		if(countSpeed<speed.size() && speed.size()>0) {
			return speed.get(countSpeed++);
		}else
			return 0;
	}
	
	public float getAcel() {
		if(countAcel<acel.size() && acel.size()>0) {
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
