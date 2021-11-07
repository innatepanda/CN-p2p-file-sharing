import javax.swing.*;  
public class Gui {  
       public static void main(String[] args) {  
            JFrame f=new JFrame();//creating instance of JFrame  
            JTextField t1,t2;  
            t1=new JTextField("Welcome to KIIT.");  
            t1.setBounds(50,100, 200,30);  
            t2=new JTextField("--- Login ---");  
            JButton b=new JButton("click");//creating instance of JButton  
            b.setBounds(50,200,200, 30);  
          
            f.add(b);//adding button in JFrame  
            t2.setBounds(50,150, 200,30);  
            f.add(t1); f.add(t2);
            f.setSize(300,300);  
            f.setLayout(null);  
            f.setVisible(true);
       } 
}