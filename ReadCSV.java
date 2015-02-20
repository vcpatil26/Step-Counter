
 
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.lang.Math.*;
 
public class ReadCVS {
 
  public static void main(String[] args) {
 
	ReadCVS obj = new ReadCVS();
	obj.run();
 
  }
 
  public void run() {
 
	String csvFile = "/media/3690-15F9/GLOG.CSV";
	BufferedReader br = null;
	String line = "";
	String cvsSplitBy = ",";
        int count=0;
        double ya=0;
	double a=0;
 
	try {
 
		br = new BufferedReader(new FileReader(csvFile));
		int stepFlag=0;
		double prev=0;
		while ((line = br.readLine()) != null) {
			String[] accel = line.split(cvsSplitBy);
 			a=Double.parseDouble(accel[0]);
			ya=Math.round(a*100)/100;
			//if(ya>0.99 && ya<1.01)
			  //{ya=1;}
			
			 if(prev==1)
			{
				if( ya== 1.00)
				{}
				else
				{count++;}
			}
			else
				
				{}
			prev=ya;
			/*if(stepFlag==0){
				if(Math.round(ya*100)/100 == 1.00)
				{ 
					stepFlag=1;
				}
			}
			else{
				if(prev==ya){
					stepFlag=0;
				}
				else{
					if(Math.round(ya*100)/100 == 1.00)
					{
						count ++;
						stepFlag=0;
					}
				}
 			}*/
			//prev=ya;
		}
		int realcount=count-3;
		System.out.println("The step count is "+count);
 
	} catch (FileNotFoundException e) {
		e.printStackTrace();
	} catch (IOException e) {
		e.printStackTrace();
	} finally {
		if (br != null) {
			try {
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
 
	System.out.println("Done");
  }
 
}
