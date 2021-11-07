import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame implements ActionListener{
    JTextField t1,t2,t3; 
    JButton b;  
    JLabel l1,l2,l3,l4;
    JPanel p, q;
    CardLayout crd;    
    JPanel cPane;  
    Gui(){
        cPane =new JPanel();  
        crd = new CardLayout();    
        cPane.setLayout(crd);  
        p = new JPanel();
        q = new JPanel();
        p.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
            gbc.insets = new Insets(8, 8, 8, 8);
            gbc.gridx = 0;
            gbc.gridy = 0;
        p.setBounds(0,0,500,500);
        p.setBackground(Color.white);
          
        t1=new JTextField(20);  
        
        t2=new JTextField(20); 
        
        l1=new JLabel();l2=new JLabel();l3=new JLabel();l4=new JLabel();
        l1.setFont (l1.getFont ().deriveFont (30.0f));
        l1.setText("Login");  l2.setText("Username");  l3.setText("Password");
        //p.add(Box.createRigidArea(new Dimension(0,5)));
        gbc.gridx=1;  p.add(l1, gbc);
        gbc.gridx=0;

        gbc.gridy++;
        p.add(l2, gbc);
        gbc.gridx++;
        p.add(t1, gbc);

        gbc.gridy++;
        gbc.gridx=0;
        p.add(l3, gbc);
        
        gbc.gridx++;
        p.add(t2, gbc);
        b =new JButton("click");//creating instance of JButton  
        
        b.addActionListener(this); 
        gbc.gridy++;
        p.add(b, gbc);
        gbc.gridy++;
        p.add(l4, gbc);

        q = new JPanel();
        q.setLayout(new GridBagLayout());
        GridBagConstraints qgbc = new GridBagConstraints();
            qgbc.insets = new Insets(1, 8, 8, 1);
            qgbc.gridx = 0;
            qgbc.gridy = 0;
        q.setBounds(0,0,500,500);
        q.setBackground(Color.black);
        
        cPane.add(p, "a");
        cPane.add(q, "b");  
        setContentPane(cPane); 
             
            
    }
    public void actionPerformed(ActionEvent e) 
    {    
        
        String s1=t1.getText();  
        String s2=t2.getText();  
        
        if(e.getSource()==b){  
            l4.setText("usr , pass of "+s1+" is: "+s2);
            crd.next(cPane);  
        }
    }
    
       public static void main(String[] args) {  
          Gui g=new Gui();
          g.setSize(500,500);  
          //g.setLayout();  
          g.setVisible(true);
          g.setDefaultCloseOperation(EXIT_ON_CLOSE);    
       } 
}