import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame implements ActionListener{
    JTextField t1,t2,t3; 
    JButton b;  
    JLabel l1;
    JPanel p, q;
    CardLayout crd;    
    JPanel cPane;  
    Gui(){
        //cPane = getContentPane(); 
        cPane=new JPanel();
        setLayout(crd);
        crd = new CardLayout();    
        cPane.setLayout(crd);  
        
        p = new JPanel();
        p.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
            gbc.insets = new Insets(1, 8, 8, 1);
            gbc.gridx = 0;
            gbc.gridy = 0;
        p.setBounds(0,0,500,500);
        //p.setBackground(Color.black);
        q = new JPanel();
        q.setLayout(new GridBagLayout());
        GridBagConstraints qgbc = new GridBagConstraints();
            qgbc.insets = new Insets(1, 8, 8, 1);
            qgbc.gridx = 0;
            qgbc.gridy = 0;
        q.setBounds(0,0,500,500);
        q.setBackground(Color.black);
        
        
        t1=new JTextField(20);  
        
        t2=new JTextField(20); 
        
        l1=new JLabel();  
        l1.setText("Login");
        
        p.add(l1, gbc);
        //p.add(Box.createRigidArea(new Dimension(0,5)));
        gbc.gridy++;
        p.add(t1, gbc);
        gbc.gridy++;
        p.add(t2, gbc);
        b =new JButton("click");//creating instance of JButton  
        
        b.addActionListener(this); 
        gbc.gridy++;
        p.add(b, gbc);
    // cPane.add(l1);
        cPane.add(p, "a");
        cPane.add(q, "b");  
        setContentPane(cPane); 

            
    }
    public void actionPerformed(ActionEvent e) 
    {    
        
        String s1=t1.getText();  
        String s2=t2.getText();  
        
        if(e.getSource()==b){  
            l1.setText("usr, pass "+s1+" is: "+s2);
            
            crd.next(cPane);
        }
    }
    
       public static void main(String[] args) {  
          Gui g=new Gui();
          g.setSize(500,500);  
          
          g.setVisible(true);
          g.setDefaultCloseOperation(EXIT_ON_CLOSE);    
       } 
}