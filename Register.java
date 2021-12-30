import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.util.Scanner;

public class Register implements ActionListener{
    JTextField t1,t2; 
    JButton b,c;  
    JLabel l1,l2,l3;
    JPanel p;
    CardLayout crd;
    JPanel cPane;
    int flag=1;
    public String result="default";
    Gui g;
    Login lg;
    Register(CardLayout crd, JPanel cards, Gui g)
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
          
        t1=new JTextField(20);  
        
        t2=new JTextField(20); 
        l1=new JLabel();l2=new JLabel();l3=new JLabel();
        l1.setFont (l1.getFont ().deriveFont (30.0f));
        l1.setText("Register");  l2.setText("Username");  l3.setText("Password");

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

        b =new JButton("Register");//creating instance of JButton  
        
        //b.addActionListener(this); 
        b.addActionListener(this);
        gbc.gridy++;
        p.add(b, gbc);
        gbc.gridy++;
        
        c =new JButton("Login");
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
        
        String s1=t1.getText();  
        String s2=t2.getText();  
        //Scanner scanner = new Scanner(System.in);
        
           if(e.getSource()==b ){  
           // l4.setText("usr , pass of "+s1+" is: "+s2);
         
            result="usr "+s1+"pass "+s2;
            result+=" is: "+g.sayHello(Integer.parseInt(s1),Integer.parseInt(s2));
            System.out.println(result);
             g.changeText(result);
            crd.next(cPane);  
          }
          if(e.getSource()==c ){   
            //Login login = (new Login(crd, cPane, lg));
           // cPane.add(login.getpanel(), "a");
           
            System.out.println("In login page");
            crd.next(cPane);  
          }
           
       
    }
   
   
}
