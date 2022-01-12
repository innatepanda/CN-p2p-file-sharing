import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.util.Scanner;

public class Home implements ActionListener{
    JTextField t1,t2; 
    JButton logout,delete,add;  
    JLabel l1,l2,l3;
    JPanel p;
    CardLayout crd;
    JPanel cPane;
    int flag=1;
    public String result="default";
    Gui g;
    
    Home(CardLayout crd, JPanel cards, Gui g)
    {
        this.g=g;
        this.crd=crd;
        this.cPane=cards;
        p = new JPanel();
        p.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
            gbc.insets = new Insets(8, 8, 8, 8);
            gbc.gridx = 0;
            gbc.gridy = 0;
        p.setBounds(0,0,500,500);
        p.setBackground(Color.white);
          
     
        l1=new JLabel();
        l1.setFont (l1.getFont ().deriveFont (30.0f));
        l1.setText("Welcome"+g.username); 

        gbc.gridx=1;  p.add(l1, gbc);
        gbc.gridx=0;

        
        logout =new JButton("Logout");
        logout.addActionListener(this);
        gbc.gridy++;
        p.add(logout,gbc);
        gbc.gridx++;
        
        add =new JButton("Add new file");//creating instance of JButton  
        
        //b.addActionListener(this); 
        add.addActionListener(this);
        gbc.gridy++;
        p.add(add, gbc);
        gbc.gridx++;
        
        delete=new JButton("Delete file");
        delete.addActionListener(this);
        gbc.gridy++;
        p.add(delete, gbc);
        gbc.gridy++;
        //p.add(l4, gbc);
    }

    public JPanel getpanel()
    {
        return p;
    }
    public void actionPerformed(ActionEvent e) 
    {    
        
        String s1=t1.getText();  
        String s2=t2.getText();  
        //Scanner scanner = new Scanner(System.in);
        
           if(e.getSource()==logout ){  
               g.Auth(g.username,"password",-1);
               //crd.show(cPane,"b");
           }
           if(e.getSource()==add ){  
          
               crd.show(cPane,"b");
           }
           if(e.getSource()==delete ){  
          
               crd.show(cPane,"b");
           }
         
            else
            System.out.print("err - " +result);
            
            
          
       
    }
   
   
}
