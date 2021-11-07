import javax.swing.*;  
import java.awt.event.*;
public class Gui implements ActionListener{
    JTextField t1,t2,t3; 
    JButton b;  
    JLabel l1;
    public void actionPerformed(ActionEvent e) 
    {    
        
        String s1=t1.getText();  
        String s2=t2.getText();  
        
        if(e.getSource()==b){  
            l1.setText("usr , pass of "+s1+" is: "+s2);
        }
    }
    public void test(){
        JFrame f=new JFrame();//creating instance of JFrame  
            
            t1=new JTextField();  
            t1.setBounds(50,100, 200,30);  
            t2=new JTextField(); 
            l1=new JLabel();  
            l1.setBounds(50,200, 200,30); 
            f.add(l1);
            b =new JButton("click");//creating instance of JButton  
            b.setBounds(50,250,200, 30);  
            b.addActionListener(this);

            f.add(b);//adding button in JFrame  
            t2.setBounds(50,150, 200,30);  
            f.add(t1); f.add(t2);
            f.setSize(500,500);  
            f.setLayout(null);  
            f.setVisible(true);
    }
       public static void main(String[] args) {  
          Gui g=new Gui();
            g.test();
       } 
}
