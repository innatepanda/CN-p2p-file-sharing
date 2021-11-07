import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame implements ActionListener{
    //JTextField t1,t2,t3; 
    //JButton b;  
    JLabel l4;
    JPanel  q;
    CardLayout crd;    
    JPanel cPane;  
    Gui(){
        cPane =new JPanel();  
        crd = new CardLayout();    
        cPane.setLayout(crd);  
       
        q = new JPanel();
        
        
       
        //p.add(Box.createRigidArea(new Dimension(0,5)));

        

        q = new JPanel();
        q.setLayout(new GridBagLayout());
        GridBagConstraints qgbc = new GridBagConstraints();
            qgbc.insets = new Insets(1, 8, 8, 1);
            qgbc.gridx = 0;
            qgbc.gridy = 0;
        q.setBounds(0,0,500,500);
        //q.setBackground(Color.blue);
        l4=new JLabel("text");
        Login login = (new Login(crd, cPane, this));
        cPane.add(login.getpanel(), "a");
        l4.setText(login.result);
        q.add(l4);
        cPane.add(q, "b");  
        setContentPane(cPane); 
             
            
    }
    public void changeText(String msg)
    {
        l4.setText(msg);
    }
    public void actionPerformed(ActionEvent e) 
    {    
        
        System.out.println("x");
    }
    
       public static void main(String[] args) {  
          Gui g=new Gui();
          g.setSize(500,500);  
          //g.setLayout();  
          g.setVisible(true);
          g.setDefaultCloseOperation(EXIT_ON_CLOSE);    
       } 
}