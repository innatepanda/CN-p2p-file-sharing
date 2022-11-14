import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.util.Scanner;

public class Login implements ActionListener{
    JTextField t1,t2; 
    JButton b,c;  
    JLabel l1,l2,l3,msg1,msg2;
    JPanel p;
    CardLayout crd;
    JPanel cPane;
    int flag=1;
    public String s1="str",s2;
    public String result="default";
    Gui g;
    GridBagConstraints gbc;
    Login(CardLayout crd, JPanel cards, Gui g)
    {
        this.g=g;
        this.crd=crd;
        this.cPane=cards;
        p = new JPanel();
        p.setLayout(new GridBagLayout());
        gbc = new GridBagConstraints();
            gbc.insets = new Insets(8, 8, 8,8);
            gbc.gridx = 0;
            gbc.gridy = 0;
        p.setBounds(0,0,500,500);
        p.setBackground(Color.white);
          
        t1=new JTextField(20);  
        
        t2=new JTextField(20); 
        l1=new JLabel();l2=new JLabel();l3=new JLabel();
        l1.setFont (l1.getFont ().deriveFont (30.0f));
        l1.setText("Login");
        gbc.gridx=1;  p.add(l1, gbc);
        gbc.gridx=0;  gbc.gridy++; 
         
        l2.setText("Username");  
        p.add(l2, gbc); gbc.gridx++;
        p.add(t1, gbc);   
        gbc.gridy++;
        msg1=new JLabel();
        gbc.gridx=1; p.add(msg1,gbc);
        gbc.gridy++;
        
        l3.setText("Password");
        gbc.gridx=0;
        p.add(l3, gbc); gbc.gridx++;
        p.add(t2, gbc); gbc.gridy++;
        msg2=new JLabel();
        gbc.gridx=1; p.add(msg2,gbc);
        gbc.gridy++;
        b =new JButton("Login");//creating instance of JButton  
        
        //b.addActionListener(this); 
        b.addActionListener(this);
        gbc.gridy++;
        p.add(b, gbc);
        gbc.gridy++;
        
        c =new JButton("Register");
        c.addActionListener(this);
        gbc.gridy++;
        p.add(c, gbc);
        gbc.gridy++;
        //p.add(l4, gbc);
    }

    public JPanel getpanel()
    {
        return p;
    }
    public void actionPerformed(ActionEvent e) 
    {    
        
         s1=t1.getText();  
         s2=t2.getText();  
        //Scanner scanner = new Scanner(System.in);
        
           if(e.getSource()==b ){  
           if(s1.length()>3 && s2.length()>3){
		    result=g.Auth(s1,s2,1);
		    if(result.substring(0,3).equals("200")){
		       g.changeUsername(s1);
		        
		       System.out.println("username: "+g.username);
		       System.out.println(result);
		      
		       // crd.next(cPane);  
		       crd.show(cPane,"b");
		    }
		    else{
		        
		        msg1.setText("Incorrect usern,please try again "+result);
		        
		    }
            }
            else msg1.setText("Username or password too short (>3)");
            
          }
          if(e.getSource()==c ){  
            System.out.println("In register page");
            crd.next(cPane);  
          }
           
       
    }
   
   
}
